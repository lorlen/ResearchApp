#pragma once

#include <QtWidgets/QDialog>
#include "designer/ui_editaction.h"
#include "entities/Action.h"
#include "entities/Research.h"

/**
 * A modal dialog used to create or edit research actions.
 */
class EditActionDialog: public QDialog {
    Q_OBJECT

private:
    Ui::EditAction ui;
    Action action;
    bool newAction = false;

private slots:
    void updateButtons();
    void appendSensor(const Sensor& sensor);
    void newSensor();
    void addSensor();
    void deleteSensor();
    void applyChanges();
    void cancelChanges();

signals:
    /**
     * Signal fired to notify that a research action has been modified by the user.
     * @param action research action that has been modified.
     */
    void actionModified(Action action);

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

public:
    /**
     * Constructs an `EditActionDialog` instance.
     * @param action research action to modify.
     * @param parent see Qt docs.
     * @param f see Qt docs.
     */
    explicit EditActionDialog(const Action& action, QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~EditActionDialog() override = default;
};
