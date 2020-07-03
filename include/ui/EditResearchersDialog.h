#ifndef RESEARCHAPP_EDITRESEARCHERSDIALOG_H
#define RESEARCHAPP_EDITRESEARCHERSDIALOG_H


#include <QtWidgets/QDialog>
#include "ui/ui_editresearchers.h"
#include "research/Research.h"

/**
 * A modal dialog to edit researchers assigned to a research.
 */
class EditResearchersDialog: public QDialog {
private:
    Ui::EditResearchers ui;
    std::shared_ptr<Research> research;

private slots:
    void updateButtons();
    void appendUser(std::string login);
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
    explicit EditResearchersDialog(std::shared_ptr<Research> research, QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
};


#endif //RESEARCHAPP_EDITRESEARCHERSDIALOG_H
