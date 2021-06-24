#pragma once

#include <memory>
#include <QtWidgets/QDialog>
#include "db/storage.h"
#include "designer/ui_sensorlist.h"
#include "entities/Research.h"

/**
 * A dialog used to view sensors used in the selected research.
 */
class SensorListDialog: public QDialog {
    Ui::SensorList ui;
    std::shared_ptr<Storage> storage;

public:
    /**
     * Constructs a `SensorListDialog` instance.
     * @param researchId the id of current research.
     * @param parent see Qt docs.
     * @param f see Qt docs.
     */
    explicit SensorListDialog(std::shared_ptr<Storage> _storage, decltype(Research::id) researchId,
                              QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
};
