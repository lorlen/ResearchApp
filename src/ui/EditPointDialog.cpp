#include <algorithm>
#include <sstream>
#include <vector>

#include "db/Database.h"
#include "ui/EditPointDialog.h"
#include "ui/NewSensorDialog.h"
#include "ui/ListItemWithData.h"

static std::string getSensorDesc(const Sensor& sensor) {
    std::ostringstream stream;
    stream << sensor.label() << " (" << sensor.type() << "; " << sensor.unit() << ")";
    return stream.str();
}

EditPointDialog::EditPointDialog(ResearchPoint& point, bool blank, QWidget* parent, Qt::WindowFlags f)
        : QDialog{parent, f}, ui{}, point{point}, blank{blank} {
    ui.setupUi(this);

    ui.pointInfo->setText(point.title().c_str());
    ui.requiredMeasurement->setChecked(point.required());

    const auto& pointSensors = point.sensors();

    for (const auto& [id, sensor]: globals::db.sensors()) {
        if (std::find_if(pointSensors.begin(), pointSensors.end(),
            [&sensor = sensor](auto e) { return *e.lock() == *sensor; }) == pointSensors.end())
        {
            auto* item = new ListItemWithData<size_t>{sensor->id(), getSensorDesc(*sensor).c_str()};
            ui.allSensors->addItem(item);
        }
    }

    for (const auto& sensor: pointSensors) {
        auto* item = new ListItemWithData<size_t>{sensor.lock()->id(), getSensorDesc(*sensor.lock()).c_str()};
        ui.currentSensors->addItem(item);
    }

    updateButtons();

    ui.allSensors->installEventFilter(this);
    ui.currentSensors->installEventFilter(this);

    connect(ui.newButton, &QPushButton::clicked, this, &EditPointDialog::newSensor);
    connect(ui.addButton, &QPushButton::clicked, this, &EditPointDialog::addSensor);
    connect(ui.deleteButton, &QPushButton::clicked, this, &EditPointDialog::deleteSensor);
    connect(ui.allSensors, &QListWidget::itemSelectionChanged, this, &EditPointDialog::updateButtons);
    connect(ui.allSensors, &QListWidget::itemDoubleClicked, this, &EditPointDialog::addSensor);
    connect(ui.currentSensors, &QListWidget::itemSelectionChanged, this, &EditPointDialog::updateButtons);
    connect(ui.currentSensors, &QListWidget::itemDoubleClicked, this, &EditPointDialog::deleteSensor);
    connect(this, &QDialog::accepted, this, &EditPointDialog::applyChanges);
}

void EditPointDialog::updateButtons() {
    ui.addButton->setEnabled(ui.allSensors->currentRow() >= 0);
    ui.deleteButton->setEnabled(ui.allSensors->currentRow() >= 0 || ui.currentSensors->currentRow() >= 0);
}

void EditPointDialog::appendSensor(size_t id) {
    auto* item = new ListItemWithData<size_t>{id, getSensorDesc(*globals::db.sensors().at(id)).c_str()};
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
        auto* item = dynamic_cast<ListItemWithData<size_t>*>(ui.allSensors->currentItem());

        if (item != nullptr) {
            globals::db.deleteSensor(item->data());
            delete ui.allSensors->takeItem(ui.allSensors->currentRow());
        }
    }

    updateButtons();
}

void EditPointDialog::applyChanges() {
    std::vector<std::shared_ptr<Sensor>> sensors;
    sensors.reserve(ui.currentSensors->count());

    for (int i = 0; i < ui.currentSensors->count(); i++) {
        sensors.push_back(globals::db.sensors().at(dynamic_cast<ListItemWithData<size_t>*>(ui.currentSensors->item(i))->data()));
    }

    point.title(ui.pointInfo->text().toStdString());
    point.required(ui.requiredMeasurement->isChecked());
    point.sensors(sensors);

    emit pointModified(point, blank);
}

bool EditPointDialog::eventFilter(QObject* obj, QEvent* event) {
    if (event->type() == QEvent::FocusIn) {
        if (obj == ui.allSensors) {
            ui.currentSensors->setCurrentRow(-1);
        } else if (obj == ui.currentSensors) {
            ui.allSensors->setCurrentRow(-1);
        }

        updateButtons();
    }
    return false;
}
