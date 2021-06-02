#include "ui/EditActionDialog.h"

#include <vector>

#include "db/StorageManager.h"
#include "entities/Action.h"
#include "ui/NewSensorDialog.h"
#include "ui/ListItemWithData.h"

EditActionDialog::EditActionDialog(const Action& action, QWidget* parent, Qt::WindowFlags f)
        : QDialog{parent, f}, ui{}, action{action} {
    using namespace sqlite_orm;

    ui.setupUi(this);

    auto storage = StorageManager::get();

    if (action.id > 0) {
        ui.actionTitle->setText(action.title.c_str());
        ui.requiredMeasurement->setChecked(action.isRequired);

        auto sensor_cols = columns(&Sensor::id, &Sensor::label, &Sensor::type, &Sensor::unit);
        auto notUsedSensors = storage.select(except(select(sensor_cols),
                                                    select(sensor_cols,
                                                           inner_join<SensorUsage>(using_(&Sensor::id)),
                                                           where(c(&SensorUsage::actionId) == action.id))));

        auto usedSensors = storage.get_all<Sensor>(inner_join<SensorUsage>(using_(&Sensor::id)),
            where(c(&SensorUsage::actionId) == action.id));

        for (const auto& row: notUsedSensors) {
            Sensor sensor{std::get<0>(row), std::get<1>(row), std::get<2>(row), std::get<3>(row)};
            auto* item = new ListItemWithData<i64>{sensor.id, sensor.description().c_str()};
            ui.allSensors->addItem(item);
        }

        for (const auto& sensor: usedSensors) {
            auto* item = new ListItemWithData<i64>{sensor.id, sensor.description().c_str()};
            ui.currentSensors->addItem(item);
        }
    } else {
        for (const auto& sensor: storage.iterate<Sensor>()) {
            auto* item = new ListItemWithData<i64>{sensor.id, sensor.description().c_str()};
            ui.allSensors->addItem(item);
        }

        this->action.id = storage.insert(action);
        newAction = true;
    }

    updateButtons();

    ui.allSensors->installEventFilter(this);
    ui.currentSensors->installEventFilter(this);

    connect(ui.newButton, &QPushButton::clicked, this, &EditActionDialog::newSensor);
    connect(ui.addButton, &QPushButton::clicked, this, &EditActionDialog::addSensor);
    connect(ui.deleteButton, &QPushButton::clicked, this, &EditActionDialog::deleteSensor);
    connect(ui.allSensors, &QListWidget::itemSelectionChanged, this, &EditActionDialog::updateButtons);
    connect(ui.allSensors, &QListWidget::itemDoubleClicked, this, &EditActionDialog::addSensor);
    connect(ui.currentSensors, &QListWidget::itemSelectionChanged, this, &EditActionDialog::updateButtons);
    connect(ui.currentSensors, &QListWidget::itemDoubleClicked, this, &EditActionDialog::deleteSensor);
    connect(this, &QDialog::accepted, this, &EditActionDialog::applyChanges);
    connect(this, &QDialog::rejected, this, &EditActionDialog::cancelChanges);
}

void EditActionDialog::updateButtons() {
    ui.addButton->setEnabled(ui.allSensors->currentRow() >= 0);
    ui.deleteButton->setEnabled(ui.allSensors->currentRow() >= 0 || ui.currentSensors->currentRow() >= 0);
}

void EditActionDialog::appendSensor(const Sensor& sensor) {
    auto* item = new ListItemWithData<i64>{sensor.id, sensor.description().c_str()};
    ui.allSensors->addItem(item);
    updateButtons();
}

void EditActionDialog::newSensor() {
    auto* dialog = new NewSensorDialog{this};
    connect(dialog, &NewSensorDialog::sensorAdded, this, &EditActionDialog::appendSensor);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->show();
}

void EditActionDialog::addSensor() {
    if (ui.allSensors->currentRow() >= 0) {
        ui.currentSensors->addItem(ui.allSensors->takeItem(ui.allSensors->currentRow()));
        updateButtons();
    }
}

void EditActionDialog::deleteSensor() {
    if (ui.allSensors->currentRow() < 0 && ui.currentSensors->currentRow() >= 0) {
        ui.allSensors->addItem(ui.currentSensors->takeItem(ui.currentSensors->currentRow()));
    }
    else if (ui.currentSensors->currentRow() < 0 && ui.allSensors->currentRow() >= 0) {
        auto* item = dynamic_cast<ListItemWithData<i64>*>(ui.allSensors->currentItem());

        if (item != nullptr) {
            StorageManager::get().remove<Sensor>(item->itemData());
            delete ui.allSensors->takeItem(ui.allSensors->currentRow());
        }
    }

    updateButtons();
}

void EditActionDialog::applyChanges() {
    using namespace sqlite_orm;

    auto storage = StorageManager::get();

    storage.transaction([&] {
        action.title = ui.actionTitle->text().toStdString();
        action.isRequired = ui.requiredMeasurement->isChecked();

        storage.update(action);

        std::vector<i64> currentSensors;
        currentSensors.reserve(ui.currentSensors->count());

        for (int i = 0; i < ui.currentSensors->count(); i++) {
            currentSensors.push_back(dynamic_cast<ListItemWithData<i64>*>(ui.currentSensors->item(i))->itemData());
        }

        auto previousSensors = storage.select(&SensorUsage::sensorId,
                                              where(c(&SensorUsage::actionId) == action.id));

        std::vector<i64> sensorsToAdd;
        std::vector<i64> sensorsToDelete;

        std::set_difference(currentSensors.begin(), currentSensors.end(), previousSensors.begin(),
                            previousSensors.end(), std::back_inserter(sensorsToAdd));
        std::set_difference(previousSensors.begin(), previousSensors.end(), currentSensors.begin(),
                            currentSensors.end(), std::back_inserter(sensorsToDelete));

        storage.remove_all<SensorUsage>(where(c(&SensorUsage::actionId) == action.id
                                        and in(&SensorUsage::sensorId, sensorsToDelete)));

        std::vector<SensorUsage> usages;
        std::transform(sensorsToAdd.begin(), sensorsToAdd.end(), std::back_inserter(usages),
                       [&](auto sensorId) { return SensorUsage{action.id, sensorId}; });

        storage.replace_range(usages.begin(), usages.end());

        return true;
    });

    emit actionModified(action);
}

void EditActionDialog::cancelChanges() {
    if (newAction) {
        StorageManager::get().remove<Action>(action.id);
    }
}

bool EditActionDialog::eventFilter(QObject* obj, QEvent* event) {
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
