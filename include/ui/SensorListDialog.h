#ifndef PROJEKT_SENSORLISTDIALOG_H
#define PROJEKT_SENSORLISTDIALOG_H


#include <QtWidgets/QDialog>
#include "ui/ui_sensorlist.h"
#include "research/research.h"

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
    explicit SensorListDialog(Research* research, QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
};


#endif //PROJEKT_SENSORLISTDIALOG_H
