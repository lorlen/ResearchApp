#pragma once

#include <QtWidgets/QDialog>
#include "designer/ui_sensorlist.h"
#include "entities/Research.h"

/**
 * A dialog used to view sensors used in the selected research.
 */
class SensorListDialog: public QDialog {
    Ui::SensorList ui;

public:
    /**
     * Constructs a `SensorListDialog` instance.
     * @param researchId the id of current research.
     * @param parent see Qt docs.
     * @param f see Qt docs.
     */
    explicit SensorListDialog(decltype(Research::id) researchId, QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
};
