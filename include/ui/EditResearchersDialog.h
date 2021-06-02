#pragma once

#include <QtWidgets/QDialog>
#include "designer/ui_editresearchers.h"
#include "entities/Research.h"
#include "entities/User.h"

/**
 * A modal dialog to edit researchers assigned to a research.
 */
class EditResearchersDialog: public QDialog {
private:
    Ui::EditResearchers ui;
    decltype(Research::id) researchId;

private slots:
    void updateButtons();
    void appendUser(User user);
    void newUser();
    void addResearcher();
    void deleteResearcher();
    void applyChanges();

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

public:
    /**
     * Constructs an `EditResearchersDialog` instance.
     * @param researchers vector of researchers to modify.
     * @param parent see Qt docs.
     * @param f see Qt docs.
     */
    explicit EditResearchersDialog(decltype(Research::id) researchId, const std::string& title,
                                   QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
};
