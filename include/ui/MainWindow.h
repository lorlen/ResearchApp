#pragma once

#include <memory>
#include <optional>
#include <vector>
#include <QWidget>
#include "db/storage.h"
#include "designer/ui_main.h"
#include "designer/ui_addresearch.h"
#include "designer/ui_selectresearch.h"
#include "entities/Research.h"
#include "entities/Action.h"

/**
 * Main window of the application. It has two modes: select mode and add mode.
 * In the select mode, available to unprivileged users, one can browse through
 * available researches, view their information and check research actions.
 * In the add mode, an administrator can add or edit researches.
 */
class MainWindow: public QWidget {
private:
    Ui::Main mainUi;
    Ui::AddResearch addUi;
    Ui::SelectResearch selectUi;
    std::shared_ptr<Storage> storage;
    decltype(Research::id) researchId = -1;
    bool newResearch = true;

private slots:
    void setDisplayedPage(int index);
    void enterSelectMode();
    void enterEditMode();
    void changeDate();

    void showSensors();
    void logout();
    void updateProgress();
    void deleteResearch();

    void updateButtons();
    void manageResearchers();
    void appendAction(const Action& action);
    void newAction();
    void editAction();
    void deleteAction();
    void applyChanges();
    void cancelChanges();

public:
    MainWindow(std::shared_ptr<Storage> _storage);
};
