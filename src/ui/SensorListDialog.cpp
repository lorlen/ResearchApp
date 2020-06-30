#include "ui/SensorListDialog.h"
#include "globals.h"

SensorListDialog::SensorListDialog(Research* research, QWidget* parent, Qt::WindowFlags f)
        : QDialog{parent, f}, ui{} {
    ui.setupUi(this);

    connect(ui.okButton, &QPushButton::clicked, this, &SensorListDialog::close);

    for (auto& point: research->get_researchPoints()) {
        for (auto& sensor: globals::db.get_research_point_sensors(research->get_research_ID(), point->get_researchPoint_ID())) {
            auto* item = new QListWidgetItem{};
            item->setText(sensor.second.c_str());
            ui.sensorList->addItem(item);
        }
    }
}
