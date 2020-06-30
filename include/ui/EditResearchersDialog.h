#ifndef PROJEKT_EDITRESEARCHERSDIALOG_H
#define PROJEKT_EDITRESEARCHERSDIALOG_H


#include <QtWidgets/QDialog>
#include "ui/ui_editresearchers.h"
#include "research/research.h"

/**
 * A modal dialog to edit researchers assigned to a research.
 */
class EditResearchersDialog: public QDialog {
private:
    Ui::EditResearchers ui;
    Research* research;

private slots:
    void updateButtons();
    void appendUser(unsigned int id);
    void newUser();
    void addResearcher();
    void deleteResearcher();
    void applyChanges();

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

public:
    /**
     * Constructs an `EditResearchersDialog` instance.
     * @param research research for which modify the researchers.
     * @param parent see Qt docs.
     * @param f see Qt docs.
     */
    explicit EditResearchersDialog(Research* research, QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
};


#endif //PROJEKT_EDITRESEARCHERSDIALOG_H
