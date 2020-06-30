#ifndef PROJEKT_NEWSENSORDIALOG_H
#define PROJEKT_NEWSENSORDIALOG_H


#include <QtWidgets/QDialog>
#include "ui/ui_newsensor.h"
#include "research/researchpoint.h"

/**
 * A dialog used to add sensors to the global database.
 */
class NewSensorDialog: public QDialog {
    Q_OBJECT

private:
    Ui::NewSensor ui;

private slots:
    void applyChanges();

signals:
    /**
     * Signal fired to notify that a new sensor has been added.
     * @param id ID of the sensor added.
     */
    void sensorAdded(unsigned int id);

public:
    /**
     * Constructs a `NewSensorDialog` instance.
     * @param parent see Qt docs.
     * @param f see Qt docs.
     */
    explicit NewSensorDialog(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~NewSensorDialog() override = default;
};


#endif //PROJEKT_NEWSENSORDIALOG_H
