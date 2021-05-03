#pragma once

#include <vector>
#include <QWidget>
#include "designer/ui_main.h"
#include "designer/ui_addresearch.h"
#include "designer/ui_selectresearch.h"
#include "research/Research.h"

/**
 * Main window of the application. It has two modes: select mode and add mode.
 * In the select mode, available to unprivileged users, one can browse through
 * available researches, view their information and check research points.
 * In the add mode, an administrator can add or edit researches.
 */
class MainWindow: public QWidget {
private:
    Ui::Main mainUi;
    Ui::AddResearch addUi;
    Ui::SelectResearch selectUi;
    std::shared_ptr<Research> loadedResearch = nullptr;
    bool blankResearch = true;
    ResearchPoint tempPoint;

private slots:
    void toggleDisplayedPage();
    void changeDate();
    void loadResearch();

    void showSensors();
    void logout();
    void updateProgress();
    void deleteResearch();

    void updateButtons();
    void manageResearchers();
    void appendPoint(const ResearchPoint& point, bool blank);
    void newPoint();
    void editPoint();
    void deletePoint();
    void applyChanges();

public:
    MainWindow();
};
