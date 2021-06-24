#include "ui/NewSensorDialog.h"

NewSensorDialog::NewSensorDialog(std::shared_ptr<Storage> _storage, QWidget* parent, Qt::WindowFlags f)
        : QDialog{parent, f}, ui{}, storage{std::move(_storage)} {
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
    sensor.id = storage->insert(sensor);
    emit sensorAdded(sensor);
}
