#include "ui/SensorListDialog.h"

#include <sqlite_orm/sqlite_orm.h>

#include "entities/Research.h"
#include "entities/Action.h"
#include "entities/SensorUsage.h"

SensorListDialog::SensorListDialog(std::shared_ptr<Storage> _storage, decltype(Research::id) researchId,
                                   QWidget* parent, Qt::WindowFlags f)
        : QDialog{parent, f}, ui{}, storage{std::move(_storage)} {
    using namespace sqlite_orm;
    
    ui.setupUi(this);

    connect(ui.okButton, &QPushButton::clicked, this, &SensorListDialog::close);

    auto sensors = storage->get_all<Sensor>(inner_join<SensorUsage>(using_(&Sensor::id)),
                                                         inner_join<Action>(using_(&Action::id)),
                                                         where(c(&Action::researchId) == researchId),
                                                         group_by(&Sensor::id));

    for (const auto& sensor: sensors) {
        auto* item = new QListWidgetItem{};
        item->setText((sensor.label + " (" + sensor.type + "; " + sensor.unit + ")").c_str());
        ui.sensorList->addItem(item);
    }
}
