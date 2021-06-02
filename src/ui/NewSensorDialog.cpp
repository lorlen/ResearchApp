#include "ui/NewSensorDialog.h"

#include "db/StorageManager.h"

NewSensorDialog::NewSensorDialog(QWidget* parent, Qt::WindowFlags f)
        : QDialog{parent, f}, ui{} {
    ui.setupUi(this);

    connect(this, &QDialog::accepted, this, &NewSensorDialog::applyChanges);
}

void NewSensorDialog::applyChanges() {
    Sensor sensor {
        -1,
        ui.sensorLabel->text().toStdString(),
        ui.sensorType->text().toStdString(),
        ui.sensorUnit->text().toStdString()
    };
    sensor.id = StorageManager::get().insert(sensor);
    emit sensorAdded(sensor);
}
