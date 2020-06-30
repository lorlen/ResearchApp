#include <algorithm>
#include <cmath>

#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>

#include "ui/MainWindow.h"
#include "ui/LoginWindow.h"
#include "ui/SensorListDialog.h"
#include "ui/EditResearchersDialog.h"
#include "ui/EditPointDialog.h"
#include "ui/ListItemWithID.h"
#include "globals.h"
#include "research/research.h"

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
        item->checkState() == Qt::Checked ? ++checkedPoints : --checkedPoints;
        int id = tempPoints[selectUi.checklist->row(item)]->get_researchPoint_ID();
        globals::db.set_checkbox(loadedResearch->get_research_ID(), id, item->checkState() == Qt::Checked);
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
    QDate qDate = mainUi.calendarWidget->selectedDate();
    Date date{qDate.year(), qDate.month(), qDate.day()};
    auto researches = globals::db.get_researchs_s_d_pointers(date);

    Research* research = nullptr;
    std::string title, info;
    QDate* start = nullptr;
    QDate* end = nullptr;
    bool isAllowedToCheck = false;

    if (!researches.empty())
        research = researches[0];

    if (blankResearch)
        delete loadedResearch;

    blankResearch = research == nullptr;
    loadedResearch = blankResearch ? new Research{} : research;
    checkedPoints = 0;
    tempPoints.clear();

    if (!blankResearch) {
        Date startDate = research->get_start_date();
        Date endDate = research->get_deadline_date();
        title  = research->get_researchTitle();
        info   = research->get_state();
        start  = new QDate{startDate.year(), startDate.month(), startDate.day()};
        end    = new QDate{endDate.year(), endDate.month(), endDate.day()};
        tempPoints = research->get_researchPoints_sorted();

        auto users = research->get_users_ID();
        isAllowedToCheck = globals::db.is_admin()
                || std::find(users.begin(), users.end(), globals::db.get_currently_loged()->get_id()) != users.end();
    }

    if (mainUi.stackedWidget->currentIndex() == 0) {
        selectUi.sensorButton->setEnabled(!blankResearch);
        selectUi.addButton->setEnabled(blankResearch && globals::db.is_admin());
        selectUi.editButton->setEnabled(!blankResearch && globals::db.is_admin());
        selectUi.deleteButton->setEnabled(!blankResearch && globals::db.is_admin());

        selectUi.researchTitle->setText(QString("Title: ") + title.c_str());
        selectUi.researchInfo->setText(info.c_str());

        if (start != nullptr)
            selectUi.startDate->setText(QString("Start date: ") + start->toString(Qt::ISODate));
        else
            selectUi.startDate->setText(QString("Start date: "));
        if (end != nullptr)
            selectUi.endDate->setText(QString("End date: ") + end->toString(Qt::ISODate));
        else
            selectUi.endDate->setText(QString("End date: "));

        selectUi.checklist->clear();

        for (auto point: tempPoints) {
            auto* item = new QListWidgetItem{};
            item->setText(point->get_researchPointTitle().c_str());
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
            if (!isAllowedToCheck)
                item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
            item->setCheckState(point->is_checked() ? Qt::Checked : Qt::Unchecked);
            selectUi.checklist->addItem(item);
            checkedPoints += point->is_checked();
        }

        updateProgress();
    }
    else {
        addUi.researchTitle->setText(title.c_str());
        addUi.researchInfo->setText(info.c_str());
        if (start != nullptr)
            addUi.startDate->setDate(*start);
        else
            addUi.startDate->setDate(mainUi.calendarWidget->selectedDate());
        if (end != nullptr)
            addUi.endDate->setDate(*end);
        else
            addUi.endDate->setDate(QDate::currentDate());

        addUi.checklist->clear();

        for (auto point: tempPoints) {
            auto* item = new QListWidgetItem{};
            item->setText(point->get_researchPointTitle().c_str());
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
            item->setCheckState(point->is_checked() ? Qt::Checked : Qt::Unchecked);
            addUi.checklist->addItem(item);
        }

        updateButtons();
    }

    delete start;
    delete end;
}

void MainWindow::showSensors() {
    auto* sensorListDialog = new SensorListDialog{loadedResearch, this};
    sensorListDialog->setAttribute(Qt::WA_DeleteOnClose);
    sensorListDialog->show();
}

void MainWindow::logout() {
    globals::db.log_out();
    auto* loginWindow = new LoginWindow{};
    loginWindow->setAttribute(Qt::WA_DeleteOnClose);
    loginWindow->show();
    close();
}

void MainWindow::updateProgress() {
    selectUi.researchProgress->setValue((int) std::round(100 * checkedPoints / ((double) tempPoints.size())));
}

void MainWindow::deleteResearch() {
    if (!blankResearch) {
        globals::db.remove_research(loadedResearch->get_research_ID());
        loadResearch();
    }
}

void MainWindow::updateButtons() {
    addUi.editPointButton->setEnabled(addUi.checklist->currentRow() >= 0);
    addUi.deletePointButton->setEnabled(addUi.checklist->currentRow() >= 0);
}

void MainWindow::manageResearchers() {
    loadedResearch->change_researchTitle(addUi.researchTitle->text().toStdString());
    auto* editResearchersDialog = new EditResearchersDialog{loadedResearch, this};
    editResearchersDialog->setAttribute(Qt::WA_DeleteOnClose);
    editResearchersDialog->show();
}

void MainWindow::appendPoint(ResearchPoint* point, bool blank) {
    if (blank) {
        auto* item = new QListWidgetItem{point->get_researchPointTitle().c_str()};
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        point->set_researchPoint_ID(globals::db.get_next_point_id());
        tempPoints.push_back(point);
        addUi.checklist->addItem(item);
    }
    else {
        addUi.checklist->currentItem()->setText(point->get_researchPointTitle().c_str());
        tempPoints[addUi.checklist->currentRow()] = point;
    }

    updateButtons();
}

void MainWindow::newPoint() {
    auto* editPointDialog = new EditPointDialog{new ResearchPoint{}, true, this};
    connect(editPointDialog, &EditPointDialog::pointModified, this, &MainWindow::appendPoint);
    editPointDialog->setAttribute(Qt::WA_DeleteOnClose);
    editPointDialog->show();
}

void MainWindow::editPoint() {
    if (addUi.checklist->currentRow() >= 0) {
        auto* point = tempPoints[addUi.checklist->currentRow()];
        auto* editPointDialog = new EditPointDialog{point, false, this};
        connect(editPointDialog, &EditPointDialog::pointModified, this, &MainWindow::appendPoint);
        editPointDialog->setAttribute(Qt::WA_DeleteOnClose);
        editPointDialog->show();
    }
}

void MainWindow::deletePoint() {
    if (addUi.checklist->currentRow() >= 0) {
        tempPoints.erase(tempPoints.begin() + addUi.checklist->currentRow());
        delete addUi.checklist->takeItem(addUi.checklist->currentRow());

        updateButtons();
    }
}

void MainWindow::applyChanges() {
    QDate start = addUi.startDate->date();
    QDate end = addUi.endDate->date();

    for (size_t i = 0; i < tempPoints.size(); i++) {
        tempPoints[i]->set_order(i);
        tempPoints[i]->set_checked(addUi.checklist->item(i)->checkState() == Qt::Checked);
    }

    loadedResearch->change_researchTitle(addUi.researchTitle->text().toStdString());
    loadedResearch->set_s_date(Date{start.year(), start.month(), start.day()});
    loadedResearch->set_d_date(Date{end.year(), end.month(), end.day()});
    loadedResearch->set_state(addUi.researchInfo->toPlainText().toStdString());
    loadedResearch->set_researchPoints(tempPoints);
    loadedResearch->set_author(globals::db.get_currently_loged()->get_id());

    if (blankResearch) {
        // note: we don't support multiple researches with the same start date
        for (const auto& research: globals::db.get_researchs_s_d(Date{start.year(), start.month(), start.day()})) {
            globals::db.remove_research(research.first);
        }

        globals::db.add_research(loadedResearch);
    }
    else {
        globals::db.modify_research(loadedResearch->get_research_ID(), loadedResearch);
    }

    blankResearch = false;

    toggleDisplayedPage();
}
