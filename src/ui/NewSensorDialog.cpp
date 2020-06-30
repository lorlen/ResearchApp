#include "ui/NewSensorDialog.h"
#include "globals.h"

NewSensorDialog::NewSensorDialog(QWidget* parent, Qt::WindowFlags f)
        : QDialog{parent, f}, ui{} {
    ui.setupUi(this);

    connect(this, &QDialog::accepted, this, &NewSensorDialog::applyChanges);
}

void NewSensorDialog::applyChanges() {
    int id = globals::db.add_sensor(
            ui.sensorLabel->text().toStdString(),
            ui.sensorType->text().toStdString(),
            ui.sensorUnit->text().toStdString()
    );

    emit sensorAdded(id);
}
