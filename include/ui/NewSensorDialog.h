#pragma once

#include <QtWidgets/QDialog>
#include "designer/ui_newsensor.h"

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
    void sensorAdded(size_t id);

public:
    /**
     * Constructs a `NewSensorDialog` instance.
     * @param parent see Qt docs.
     * @param f see Qt docs.
     */
    explicit NewSensorDialog(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~NewSensorDialog() override = default;
};
