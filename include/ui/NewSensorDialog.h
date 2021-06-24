#pragma once

#include <memory>
#include <QtWidgets/QDialog>
#include "db/storage.h"
#include "designer/ui_newsensor.h"
#include "entities/Sensor.h"

/**
 * A dialog used to add sensors to the global database.
 */
class NewSensorDialog: public QDialog {
    Q_OBJECT

private:
    Ui::NewSensor ui;
    std::shared_ptr<Storage> storage;

private slots:
    void applyChanges();

signals:
    /**
     * Signal fired to notify that a new sensor has been added.
     */
    void sensorAdded(Sensor sensor);

public:
    /**
     * Constructs a `NewSensorDialog` instance.
     * @param parent see Qt docs.
     * @param f see Qt docs.
     */
    explicit NewSensorDialog(std::shared_ptr<Storage> _storage, QWidget* parent = nullptr,
                             Qt::WindowFlags f = Qt::WindowFlags());
    ~NewSensorDialog() override = default;
};
