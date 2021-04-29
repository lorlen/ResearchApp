#include <algorithm>
#include <cmath>

#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>

#include "ui/MainWindow.h"
#include "ui/LoginWindow.h"
#include "ui/SensorListDialog.h"
#include "ui/EditResearchersDialog.h"
#include "ui/EditPointDialog.h"
#include "globals.h"
#include "research/Research.h"

MainWindow::MainWindow() : mainUi{}, addUi{}, selectUi{} {
    mainUi.setupUi(this);
    addUi.setupUi(mainUi.pageAdd);
    selectUi.setupUi(mainUi.pageSelect);
    setWindowTitle(mainUi.stackedWidget->currentWidget()->windowTitle());
    move(QApplication::desktop()->geometry().center() - rect().center());

    connect(mainUi.calendarWidget, &QCalendarWidget::selectionChanged, this, &MainWindow::changeDate);
    connect(selectUi.sensorButton, &QPushButton::clicked, this, &MainWindow::showSensors);
    connect(selectUi.addButton, &QPushButton::clicked, this, &MainWindow::toggleDisplayedPage);
    connect(selectUi.editButton, &QPushButton::clicked, this, &MainWindow::toggleDisplayedPage);
    connect(selectUi.deleteButton, &QPushButton::clicked, this, &MainWindow::deleteResearch);
    connect(selectUi.logoutButton, &QPushButton::clicked, this, &MainWindow::logout);
    connect(selectUi.checklist, &QListWidget::itemChanged, this, [this](QListWidgetItem* item) {
        loadedResearch->researchPoints()[selectUi.checklist->row(item)].checked(item->checkState() == Qt::Checked);
        updateProgress();
    });

    connect(addUi.startDate, &QDateEdit::userDateChanged, mainUi.calendarWidget, &QCalendarWidget::setSelectedDate);
    connect(addUi.editResearchersButton, &QPushButton::clicked, this, &MainWindow::manageResearchers);
    connect(addUi.newPointButton, &QPushButton::clicked, this, &MainWindow::newPoint);
    connect(addUi.editPointButton, &QPushButton::clicked, this, &MainWindow::editPoint);
    connect(addUi.deletePointButton, &QPushButton::clicked, this, &MainWindow::deletePoint);
    connect(addUi.okButton, &QPushButton::clicked, this, &MainWindow::applyChanges);
    connect(addUi.cancelButton, &QPushButton::clicked, this, &MainWindow::toggleDisplayedPage);
    connect(addUi.checklist, &QListWidget::itemSelectionChanged, this, &MainWindow::updateButtons);

    mainUi.calendarWidget->setSelectedDate(QDate::currentDate());

    loadResearch();
}

void MainWindow::toggleDisplayedPage() {
    mainUi.stackedWidget->setCurrentIndex(1 - mainUi.stackedWidget->currentIndex());
    setWindowTitle(mainUi.stackedWidget->currentWidget()->windowTitle());
    loadResearch();
}

void MainWindow::changeDate() {
    if (mainUi.stackedWidget->currentIndex() == 0) {
        loadResearch();
    }
    else {
        addUi.startDate->setDate(mainUi.calendarWidget->selectedDate());
    }
}

void MainWindow::loadResearch() {
    auto researches = globals::db.getResearchesByStartDate(mainUi.calendarWidget->selectedDate());

    blankResearch = researches.empty();
    loadedResearch = blankResearch ? std::make_shared<Research>() : researches[0];

    if (mainUi.stackedWidget->currentIndex() == 0) {
        selectUi.sensorButton->setEnabled(!blankResearch);
        selectUi.addButton->setEnabled(blankResearch && globals::db.currentUser()->admin());
        selectUi.editButton->setEnabled(!blankResearch && globals::db.currentUser()->admin());
        selectUi.deleteButton->setEnabled(!blankResearch && globals::db.currentUser()->admin());

        selectUi.researchTitle->setText(QString("Title: ") + loadedResearch->title().c_str());
        selectUi.researchInfo->setText(loadedResearch->info().c_str());

        if (!blankResearch) {
            selectUi.startDate->setText(QString("Start date: ") + loadedResearch->startDate().toISOString().c_str());
            selectUi.endDate->setText(QString("End date: ") + loadedResearch->endDate().toISOString().c_str());
        }
        else {
            selectUi.startDate->setText(QString("Start date:"));
            selectUi.endDate->setText(QString("End date:"));
        }

        bool isAllowedToCheck = globals::db.currentUser()->admin() ||
                                loadedResearch->isAssignedTo(globals::db.currentUser());

        selectUi.checklist->clear();

        for (const auto& point: loadedResearch->researchPoints()) {
            auto* item = new QListWidgetItem{};
            item->setText(point.title().c_str());
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable);

            if (!isAllowedToCheck) {
                item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
            }

            item->setCheckState(point.checked() ? Qt::Checked : Qt::Unchecked);
            selectUi.checklist->addItem(item);
        }

        updateProgress();
    }
    else {
        addUi.researchTitle->setText(loadedResearch->title().c_str());
        addUi.researchInfo->setText(loadedResearch->title().c_str());

        if (!blankResearch) {
            addUi.startDate->setDate(loadedResearch->startDate());
            addUi.endDate->setDate(loadedResearch->endDate());
        }
        else {
            addUi.startDate->setDate(mainUi.calendarWidget->selectedDate());
            addUi.endDate->setDate(QDate::currentDate());
        }

        addUi.checklist->clear();

        for (const auto& point: loadedResearch->researchPoints()) {
            auto* item = new QListWidgetItem{};
            item->setText(point.title().c_str());
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
            item->setCheckState(point.checked() ? Qt::Checked : Qt::Unchecked);
            addUi.checklist->addItem(item);
        }

        updateButtons();
    }
}

void MainWindow::showSensors() {
    auto* sensorListDialog = new SensorListDialog{loadedResearch, this};
    sensorListDialog->setAttribute(Qt::WA_DeleteOnClose);
    sensorListDialog->show();
}

void MainWindow::logout() {
    globals::db.logOut();
    auto* loginWindow = new LoginWindow{};
    loginWindow->setAttribute(Qt::WA_DeleteOnClose);
    loginWindow->show();
    close();
}

void MainWindow::updateProgress() {
    int progress = loadedResearch->researchPoints().empty() ? 0 :
                   (int) std::round(100. * loadedResearch->countCheckedPoints() / loadedResearch->researchPoints().size());
    selectUi.researchProgress->setValue(progress);
}

void MainWindow::deleteResearch() {
    if (!blankResearch) {
        globals::db.deleteResearch(loadedResearch->id());
        loadResearch();
    }
}

void MainWindow::updateButtons() {
    addUi.editPointButton->setEnabled(addUi.checklist->currentRow() >= 0);
    addUi.deletePointButton->setEnabled(addUi.checklist->currentRow() >= 0);
}

void MainWindow::manageResearchers() {
    loadedResearch->title(addUi.researchTitle->text().toStdString());
    auto* editResearchersDialog = new EditResearchersDialog{loadedResearch, this};
    editResearchersDialog->setAttribute(Qt::WA_DeleteOnClose);
    editResearchersDialog->show();
}

void MainWindow::appendPoint(const ResearchPoint& point, bool blank) {
    if (blank) {
        auto* item = new QListWidgetItem{point.title().c_str()};
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        loadedResearch->addResearchPoint(point);
        addUi.checklist->addItem(item);
    }
    else {
        addUi.checklist->currentItem()->setText(point.title().c_str());
        loadedResearch->researchPoints()[addUi.checklist->currentRow()] = point;
    }

    updateButtons();
}

void MainWindow::newPoint() {
    tempPoint = ResearchPoint();
    auto* editPointDialog = new EditPointDialog{tempPoint, true, this};
    connect(editPointDialog, &EditPointDialog::pointModified, this, &MainWindow::appendPoint);
    editPointDialog->setAttribute(Qt::WA_DeleteOnClose);
    editPointDialog->show();
}

void MainWindow::editPoint() {
    if (addUi.checklist->currentRow() >= 0) {
        auto& point = loadedResearch->researchPoints()[addUi.checklist->currentRow()];
        auto* editPointDialog = new EditPointDialog{point, false, this};
        connect(editPointDialog, &EditPointDialog::pointModified, this, &MainWindow::appendPoint);
        editPointDialog->setAttribute(Qt::WA_DeleteOnClose);
        editPointDialog->show();
    }
}

void MainWindow::deletePoint() {
    if (addUi.checklist->currentRow() >= 0) {
        globals::db.deleteResearchPoint(loadedResearch, addUi.checklist->currentRow());
        delete addUi.checklist->takeItem(addUi.checklist->currentRow());

        updateButtons();
    }
}

void MainWindow::applyChanges() {
    for (size_t i = 0; i < loadedResearch->researchPoints().size(); i++) {
        loadedResearch->researchPoints()[i].checked(addUi.checklist->item((int) i)->checkState() == Qt::Checked);
    }

    loadedResearch->title(addUi.researchTitle->text().toStdString());
    loadedResearch->startDate(addUi.startDate->date());
    loadedResearch->endDate(addUi.endDate->date());
    loadedResearch->info(addUi.researchInfo->toPlainText().toStdString());

    if (blankResearch) {
        // note: we don't support multiple researches with the same start date
        for (const auto& research: globals::db.getResearchesByStartDate(addUi.startDate->date())) {
            globals::db.deleteResearch(research);
        }

        globals::db.addResearch(*loadedResearch);
    }

    blankResearch = false;

    toggleDisplayedPage();
}
