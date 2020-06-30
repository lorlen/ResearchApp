#ifndef PROJEKT_MAINWINDOW_H
#define PROJEKT_MAINWINDOW_H


#include <vector>
#include <QWidget>
#include "ui/ui_main.h"
#include "ui/ui_addresearch.h"
#include "ui/ui_selectresearch.h"
#include "research/research.h"

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
    Research* loadedResearch = nullptr;
    std::vector<ResearchPoint*> tempPoints;
    int checkedPoints = 0;
    bool blankResearch = true;

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
    void appendPoint(ResearchPoint* point, bool blank);
    void newPoint();
    void editPoint();
    void deletePoint();
    void applyChanges();

public:
    MainWindow();
};


#endif //PROJEKT_MAINWINDOW_H
