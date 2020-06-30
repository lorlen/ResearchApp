#include <algorithm>
#include <sstream>
#include <vector>

#include "ui/EditPointDialog.h"
#include "ui/NewSensorDialog.h"
#include "ui/ListItemWithID.h"
#include "globals.h"

static std::string getSensorDesc(Sensor* sensor) {
    std::ostringstream stream;
    stream << sensor->get_sensorLabel() << " (" << sensor->get_sensorType() << "; " << sensor->get_sensorUnit() << ")";
    return stream.str();
}

EditPointDialog::EditPointDialog(ResearchPoint* point, bool blank, QWidget* parent, Qt::WindowFlags f)
        : QDialog{parent, f}, ui{}, point{point}, blank{blank} {
    ui.setupUi(this);

    ui.pointInfo->setText(point->get_researchPointTitle().c_str());
    ui.requiredMeasurement->setChecked(point->is_requiredMeasurement());

    auto pointSensors = point->get_sensors();

    for (auto sensor: globals::db.get_sensors_pointers()) {
        if (std::find(pointSensors.begin(), pointSensors.end(), sensor->get_sensor_ID()) == pointSensors.end()) {
            auto* item = new ListItemWithID{sensor->get_sensor_ID(), getSensorDesc(sensor).c_str()};
            ui.allSensors->addItem(item);
        }
    }

    for (auto sensorID: pointSensors) {
        auto* sensor = globals::db.get_sensor(sensorID);
        auto* item = new ListItemWithID{sensor->get_sensor_ID(), getSensorDesc(sensor).c_str()};
        ui.currentSensors->addItem(item);
    }

    updateButtons();

    ui.allSensors->installEventFilter(this);
    ui.currentSensors->installEventFilter(this);

    connect(ui.newButton, &QPushButton::clicked, this, &EditPointDialog::newSensor);
    connect(ui.addButton, &QPushButton::clicked, this, &EditPointDialog::addSensor);
    connect(ui.deleteButton, &QPushButton::clicked, this, &EditPointDialog::deleteSensor);
    connect(ui.allSensors, &QListWidget::itemSelectionChanged, this, &EditPointDialog::updateButtons);
    connect(ui.currentSensors, &QListWidget::itemSelectionChanged, this, &EditPointDialog::updateButtons);
    connect(this, &QDialog::accepted, this, &EditPointDialog::applyChanges);
    connect(this, &QDialog::rejected, this, [this]() { if (this->blank) delete this->point; });
}

void EditPointDialog::updateButtons() {
    ui.addButton->setEnabled(ui.allSensors->currentRow() >= 0);
    ui.deleteButton->setEnabled(ui.allSensors->currentRow() >= 0 || ui.currentSensors->currentRow() >= 0);
}

void EditPointDialog::appendSensor(unsigned int id) {
    auto* sensor = globals::db.get_sensor(id);
    auto* item = new ListItemWithID{id, getSensorDesc(sensor).c_str()};
    ui.allSensors->addItem(item);
    updateButtons();
}

void EditPointDialog::newSensor() {
    auto* dialog = new NewSensorDialog{this};
    connect(dialog, &NewSensorDialog::sensorAdded, this, &EditPointDialog::appendSensor);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->show();
}

void EditPointDialog::addSensor() {
    if (ui.allSensors->currentRow() >= 0) {
        ui.currentSensors->addItem(ui.allSensors->takeItem(ui.allSensors->currentRow()));
        updateButtons();
    }
}

void EditPointDialog::deleteSensor() {
    if (ui.allSensors->currentRow() < 0 && ui.currentSensors->currentRow() >= 0) {
        ui.allSensors->addItem(ui.currentSensors->takeItem(ui.currentSensors->currentRow()));
    }
    else if (ui.currentSensors->currentRow() < 0 && ui.allSensors->currentRow() >= 0) {
        auto* item = dynamic_cast<ListItemWithID*>(ui.allSensors->currentItem());

        if (item != nullptr) {
            globals::db.delete_sensor(item->getID());
            delete ui.allSensors->takeItem(ui.allSensors->currentRow());
        }
    }

    updateButtons();
}

void EditPointDialog::applyChanges() {
    std::vector<unsigned int> sensorIDs;
    sensorIDs.reserve(ui.currentSensors->count());

    for (int i = 0; i < ui.currentSensors->count(); i++) {
        sensorIDs.push_back(dynamic_cast<ListItemWithID*>(ui.currentSensors->item(i))->getID());
    }

    point->change_researchPointTitle(ui.pointInfo->text().toStdString());
    point->set_required(ui.requiredMeasurement->isChecked());
    point->set_sensors(sensorIDs);

    emit pointModified(point, blank);
}

bool EditPointDialog::eventFilter(QObject* obj, QEvent* event) {
    if (event->type() == QEvent::FocusIn) {
        if (obj == ui.allSensors)
            ui.currentSensors->setCurrentRow(-1);
        else if (obj == ui.currentSensors)
            ui.allSensors->setCurrentRow(-1);
        updateButtons();
    }
    return false;
}
