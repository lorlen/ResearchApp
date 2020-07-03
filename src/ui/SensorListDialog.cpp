#include "ui/SensorListDialog.h"
#include "globals.h"

SensorListDialog::SensorListDialog(const std::shared_ptr<Research>& research, QWidget* parent, Qt::WindowFlags f)
        : QDialog{parent, f}, ui{} {
    ui.setupUi(this);

    connect(ui.okButton, &QPushButton::clicked, this, &SensorListDialog::close);

    for (const auto& point: research->researchPoints()) {
        for (const auto& sensor_weak: point.sensors()) {
            auto* item = new QListWidgetItem{};
            auto sensor = sensor_weak.lock();
            item->setText((sensor->label() + " (" + sensor->type() + "; " + sensor->unit() + ")").c_str());
            ui.sensorList->addItem(item);
        }
    }
}
