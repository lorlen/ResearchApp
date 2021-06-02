#include "ui/MainWindow.h"

#include <algorithm>
#include <cmath>

#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>
#include <optional>

#include "db/LoginManager.h"
#include "db/StorageManager.h"
#include "ui/ListItemWithData.h"
#include "ui/LoginWindow.h"
#include "ui/SensorListDialog.h"
#include "ui/EditResearchersDialog.h"
#include "ui/EditActionDialog.h"

MainWindow::MainWindow() : mainUi{}, addUi{}, selectUi{} {
    mainUi.setupUi(this);
    addUi.setupUi(mainUi.pageAdd);
    selectUi.setupUi(mainUi.pageSelect);
    setWindowTitle(mainUi.stackedWidget->currentWidget()->windowTitle());
    move(QApplication::desktop()->geometry().center() - rect().center());

    connect(mainUi.calendarWidget, &QCalendarWidget::selectionChanged, this, &MainWindow::changeDate);
    connect(selectUi.sensorButton, &QPushButton::clicked, this, &MainWindow::showSensors);
    connect(selectUi.addButton, &QPushButton::clicked, this, &MainWindow::enterEditMode);
    connect(selectUi.editButton, &QPushButton::clicked, this, &MainWindow::enterEditMode);
    connect(selectUi.deleteButton, &QPushButton::clicked, this, &MainWindow::deleteResearch);
    connect(selectUi.logoutButton, &QPushButton::clicked, this, &MainWindow::logout);
    connect(selectUi.checklist, &QListWidget::itemChanged, this, [this](QListWidgetItem* item) {
        using namespace sqlite_orm;

        StorageManager::get().update_all(set(c(&Action::isChecked) = item->checkState() == Qt::Checked),
                                         where(c(&Action::ordinal) == selectUi.checklist->row(item)));
        updateProgress();
    });

    connect(addUi.startDate, &QDateEdit::userDateChanged, mainUi.calendarWidget, &QCalendarWidget::setSelectedDate);
    connect(addUi.editResearchersButton, &QPushButton::clicked, this, &MainWindow::manageResearchers);
    connect(addUi.newActionButton, &QPushButton::clicked, this, &MainWindow::newAction);
    connect(addUi.editActionButton, &QPushButton::clicked, this, &MainWindow::editAction);
    connect(addUi.deleteActionButton, &QPushButton::clicked, this, &MainWindow::deleteAction);
    connect(addUi.okButton, &QPushButton::clicked, this, &MainWindow::applyChanges);
    connect(addUi.cancelButton, &QPushButton::clicked, this, &MainWindow::cancelChanges);
    connect(addUi.checklist, &QListWidget::itemSelectionChanged, this, &MainWindow::updateButtons);

    mainUi.calendarWidget->setSelectedDate(QDate::currentDate());

    enterSelectMode();
}

void MainWindow::setDisplayedPage(int index) {
    mainUi.stackedWidget->setCurrentIndex(index);
    setWindowTitle(mainUi.stackedWidget->currentWidget()->windowTitle());
}

void MainWindow::enterSelectMode() {
    using namespace sqlite_orm;

    auto storage = StorageManager::get();

    auto researches = storage.get_all<Research>(
        where(c(&Research::startDate) == Date(mainUi.calendarWidget->selectedDate()))
    );

    auto loadedResearch = researches.empty() ? std::nullopt : std::make_optional(researches[0]);

    researchId = loadedResearch.has_value() ? loadedResearch->id : -1;
    newResearch = !loadedResearch.has_value();

    std::vector<Action> researchActions;

    selectUi.sensorButton->setEnabled(loadedResearch.has_value());
    selectUi.addButton->setEnabled(!loadedResearch.has_value() && LoginManager::currentUser()->isAdmin);
    selectUi.editButton->setEnabled(loadedResearch.has_value() && LoginManager::currentUser()->isAdmin);
    selectUi.deleteButton->setEnabled(loadedResearch.has_value() && LoginManager::currentUser()->isAdmin);

    if (loadedResearch.has_value()) {
        researchActions = storage.get_all<Action>(where(c(&Action::researchId) == loadedResearch->id),
                                                  order_by(&Action::ordinal));
        selectUi.researchTitle->setText(QString("Title: ") + loadedResearch->title.c_str());
        selectUi.researchInfo->setText(loadedResearch->info.c_str());
        selectUi.startDate->setText(QString("Start date: ") + loadedResearch->startDate.toISOString().c_str());
        selectUi.endDate->setText(QString("End date: ") + loadedResearch->endDate.toISOString().c_str());
    } else {
        selectUi.researchTitle->setText("Title: ");
        selectUi.researchInfo->setText("");
        selectUi.startDate->setText("Start date:");
        selectUi.endDate->setText("End date:");
    }

    auto assignedCount = storage.count<User>(inner_join<Assignment>(using_(&User::id)),
                                             inner_join<Research>(using_(&Research::id)),
                                             where(c(&User::id) == LoginManager::currentUser()->id
                                                   and c(&Research::id) == loadedResearch->id));

    bool isAllowedToCheck = LoginManager::currentUser()->isAdmin || assignedCount > 0;

    selectUi.checklist->clear();

    for (const auto& action: researchActions) {
        auto* item = new ListItemWithData<i64>{action.id, action.title.c_str()};
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);

        if (!isAllowedToCheck) {
            item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
        }

        item->setCheckState(action.isChecked ? Qt::Checked : Qt::Unchecked);
        selectUi.checklist->addItem(item);
    }

    updateProgress();
    setDisplayedPage(0);
}

void MainWindow::enterEditMode() {
    using namespace sqlite_orm;

    auto storage = StorageManager::get();

    addUi.checklist->clear();

    if (researchId > 0) {
        auto loadedResearch = storage.get<Research>(researchId);
        auto researchActions = storage.get_all<Action>(where(c(&Action::researchId) == researchId));

        addUi.researchTitle->setText(loadedResearch.title.c_str());
        addUi.researchInfo->setText(loadedResearch.title.c_str());
        addUi.startDate->setDate(loadedResearch.startDate);
        addUi.endDate->setDate(loadedResearch.endDate);

        for (const auto& action: researchActions) {
            auto* item = new ListItemWithData<i64>{action.id, action.title.c_str()};
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
            item->setCheckState(action.isChecked ? Qt::Checked : Qt::Unchecked);
            addUi.checklist->addItem(item);
        }
    } else {
        researchId = storage.insert(Research{});

        addUi.researchTitle->setText("");
        addUi.researchInfo->setText("");
        addUi.startDate->setDate(mainUi.calendarWidget->selectedDate());
        addUi.endDate->setDate(QDate::currentDate());
    }

    updateButtons();
    setDisplayedPage(1);
}

void MainWindow::changeDate() {
    if (mainUi.stackedWidget->currentIndex() == 0) {
        enterSelectMode();
    }
    else {
        addUi.startDate->setDate(mainUi.calendarWidget->selectedDate());
    }
}

void MainWindow::showSensors() {
    auto* sensorListDialog = new SensorListDialog{researchId, this};
    sensorListDialog->setAttribute(Qt::WA_DeleteOnClose);
    sensorListDialog->show();
}

void MainWindow::logout() {
    LoginManager::logOut();
    auto* loginWindow = new LoginWindow{};
    loginWindow->setAttribute(Qt::WA_DeleteOnClose);
    loginWindow->show();
    close();
}

void MainWindow::updateProgress() {
    int sum = 0;

    for (auto i = 0; i < selectUi.checklist->count(); i++) {
        sum += int(selectUi.checklist->item(i)->checkState() == Qt::Checked);
    }

    int progress = selectUi.checklist->count() == 0 ? 0 : (int) std::round(100. * sum / selectUi.checklist->count());
    selectUi.researchProgress->setValue(progress);
}

void MainWindow::deleteResearch() {
    if (researchId > 0) {
        StorageManager::get().remove<Research>(researchId);
        enterSelectMode();
    }
}

void MainWindow::updateButtons() {
    addUi.editActionButton->setEnabled(addUi.checklist->currentRow() >= 0);
    addUi.deleteActionButton->setEnabled(addUi.checklist->currentRow() >= 0);
}

void MainWindow::manageResearchers() {
    auto* editResearchersDialog = new EditResearchersDialog{researchId, addUi.researchTitle->text().toStdString(), this};
    editResearchersDialog->setAttribute(Qt::WA_DeleteOnClose);
    editResearchersDialog->show();
}

void MainWindow::appendAction(const Action& action) {
    if (action.ordinal >= addUi.checklist->count()) {
        auto* item = new ListItemWithData<i64>{action.id, action.title.c_str()};
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        addUi.checklist->addItem(item);
    } else {
        addUi.checklist->currentItem()->setText(action.title.c_str());
    }

    updateButtons();
}

void MainWindow::newAction() {
    Action action{};
    action.ordinal = addUi.checklist->count();
    action.researchId = researchId;

    auto* editActionDialog = new EditActionDialog{action, this};
    connect(editActionDialog, &EditActionDialog::actionModified, this, &MainWindow::appendAction);
    editActionDialog->setAttribute(Qt::WA_DeleteOnClose);
    editActionDialog->show();
}

void MainWindow::editAction() {
    if (addUi.checklist->currentRow() >= 0) {
        auto action = StorageManager::get().get<Action>(
            dynamic_cast<ListItemWithData<i64>*>(addUi.checklist->currentItem())->itemData());

        auto* editActionDialog = new EditActionDialog{action, this};
        connect(editActionDialog, &EditActionDialog::actionModified, this, &MainWindow::appendAction);
        editActionDialog->setAttribute(Qt::WA_DeleteOnClose);
        editActionDialog->show();
    }
}

void MainWindow::deleteAction() {
    using namespace sqlite_orm;

    if (addUi.checklist->currentRow() >= 0) {
        auto storage = StorageManager::get();
        storage.remove_all<Action>(where(c(&Action::ordinal) == addUi.checklist->currentRow()));
        storage.update_all(set(c(&Action::ordinal) = c(&Action::ordinal) - 1),
                           where(c(&Action::ordinal) > addUi.checklist->currentRow()));

        delete addUi.checklist->takeItem(addUi.checklist->currentRow());

        updateButtons();
    }
}

void MainWindow::applyChanges() {
    Research research {
        researchId,
        addUi.researchTitle->text().toStdString(),
        addUi.startDate->date(),
        addUi.endDate->date(),
        addUi.researchInfo->toPlainText().toStdString(),
        LoginManager::currentUser()->id
    };

    StorageManager::get().update(research);

    enterSelectMode();
}

void MainWindow::cancelChanges() {
    if (newResearch) {
        StorageManager::get().remove<Research>(researchId);
    }

    enterSelectMode();
}
