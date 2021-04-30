#ifndef RESEARCHAPP_SENSORLISTDIALOG_H
#define RESEARCHAPP_SENSORLISTDIALOG_H


#include <QtWidgets/QDialog>
#include "designer/ui_sensorlist.h"
#include "research/Research.h"

/**
 * A dialog used to view sensors used in the selected research.
 */
class SensorListDialog: public QDialog {
    Ui::SensorList ui;

public:
    /**
     * Constructs a `SensorListDialog` instance.
     * @param research the currently selected research.
     * @param parent see Qt docs.
     * @param f see Qt docs.
     */
    explicit SensorListDialog(const std::shared_ptr<Research>& research, QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
};


#endif //RESEARCHAPP_SENSORLISTDIALOG_H
