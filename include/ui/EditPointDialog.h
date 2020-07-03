#ifndef RESEARCHAPP_EDITPOINTDIALOG_H
#define RESEARCHAPP_EDITPOINTDIALOG_H


#include <QtWidgets/QDialog>
#include "ui/ui_editpoint.h"
#include "research/ResearchPoint.h"

/**
 * A modal dialog used to create or edit research points.
 */
class EditPointDialog: public QDialog {
    Q_OBJECT

private:
    Ui::EditResearchPoint ui;
    ResearchPoint& point;
    bool blank;

private slots:
    void updateButtons();
    void appendSensor(size_t id);
    void newSensor();
    void addSensor();
    void deleteSensor();
    void applyChanges();

signals:
    /**
     * Signal fired to notify that a research point has been modified by the user.
     * @param point research point that has been modified.
     * @param blank if this was a newly created research point.
     */
    void pointModified(ResearchPoint& point, bool blank);

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

public:
    /**
     * Constructs an `EditPointDialog` instance.
     * @param point research point to modify. Must be heap-allocated.
     * @param blank if this is a newly created research point.
     * @param parent see Qt docs.
     * @param f see Qt docs.
     */
    explicit EditPointDialog(ResearchPoint& point, bool blank, QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~EditPointDialog() override = default;
};


#endif //RESEARCHAPP_EDITPOINTDIALOG_H
