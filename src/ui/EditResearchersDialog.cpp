#include <algorithm>

#include "ui/EditResearchersDialog.h"
#include "ui/NewUserDialog.h"
#include "ui/ListItemWithData.h"

EditResearchersDialog::EditResearchersDialog(std::shared_ptr<Storage> _storage, decltype(Research::id) researchId,
                                             const std::string& title, QWidget* parent, Qt::WindowFlags f)
        : QDialog{parent, f}, ui{}, storage{std::move(_storage)}, researchId{researchId} {
    using namespace sqlite_orm;

    ui.setupUi(this);
    ui.researchTitle->setText(QString("Research title: ") + title.c_str());

    auto user_cols = columns(&User::id, &User::displayName);
    auto nonAssignedUsers = storage->select(except(select(user_cols),
                                                  select(user_cols, inner_join<Assignment>(using_(&User::id)),
                                                         where(c(&Assignment::researchId) == researchId))));

    auto assignedUsers = storage
        ->get_all<User>(inner_join<Assignment>(using_(&User::id)), where(c(&Assignment::researchId) == researchId));

    for (const auto& row: nonAssignedUsers) {
        auto* item = new ListItemWithData<i64>{std::get<0>(row), std::get<1>(row).c_str()};
        ui.allResearchers->addItem(item);
    }

    for (const auto& user: assignedUsers) {
        auto* item = new ListItemWithData<i64>(user.id, user.displayName.c_str());
        ui.currentResearchers->addItem(item);
    }

    updateButtons();

    ui.allResearchers->installEventFilter(this);
    ui.currentResearchers->installEventFilter(this);

    connect(this, &QDialog::accepted, this, &EditResearchersDialog::applyChanges);
    connect(ui.newUserButton, &QPushButton::clicked, this, &EditResearchersDialog::newUser);
    connect(ui.addButton, &QPushButton::clicked, this, &EditResearchersDialog::addResearcher);
    connect(ui.deleteButton, &QPushButton::clicked, this, &EditResearchersDialog::deleteResearcher);
    connect(ui.allResearchers, &QListWidget::itemSelectionChanged, this, &EditResearchersDialog::updateButtons);
    connect(ui.allResearchers, &QListWidget::itemDoubleClicked, this, &EditResearchersDialog::addResearcher);
    connect(ui.currentResearchers, &QListWidget::itemSelectionChanged, this, &EditResearchersDialog::updateButtons);
    connect(ui.currentResearchers, &QListWidget::itemDoubleClicked, this, &EditResearchersDialog::deleteResearcher);
}

void EditResearchersDialog::updateButtons() {
    ui.addButton->setEnabled(ui.allResearchers->currentRow() >= 0);
    ui.deleteButton->setEnabled(ui.allResearchers->currentRow() >= 0 || ui.currentResearchers->currentRow() >= 0);
}

void EditResearchersDialog::appendUser(User user) {
    auto* item = new ListItemWithData<i64>{user.id, user.displayName.c_str()};
    ui.allResearchers->addItem(item);
    updateButtons();
}

void EditResearchersDialog::newUser() {
    auto* dialog = new NewUserDialog{storage, this};
    connect(dialog, &NewUserDialog::userAdded, this, &EditResearchersDialog::appendUser);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->show();
}

void EditResearchersDialog::addResearcher() {
    auto* item = dynamic_cast<ListItemWithData<i64>*>(ui.allResearchers->currentItem());

    if (item != nullptr) {
        ui.allResearchers->takeItem(ui.allResearchers->currentRow());
        ui.currentResearchers->addItem(item);
    }

    updateButtons();
}

void EditResearchersDialog::deleteResearcher() {
    using namespace sqlite_orm;

    if (ui.allResearchers->currentRow() < 0 && ui.currentResearchers->currentRow() >= 0) {
        ui.allResearchers->addItem(ui.currentResearchers->takeItem(ui.currentResearchers->currentRow()));
    }
    else if (ui.currentResearchers->currentRow() < 0 && ui.allResearchers->currentRow() >= 0) {
        auto* item = dynamic_cast<ListItemWithData<i64>*>(ui.allResearchers->currentItem());

        if (item != nullptr) {
            storage->remove<User>(item->itemData());
            delete ui.allResearchers->takeItem(ui.allResearchers->currentRow());
        }
    }

    updateButtons();
}

void EditResearchersDialog::applyChanges() {
    using namespace sqlite_orm;

    storage->transaction([&] {
        std::vector<i64> currentUsers;
        currentUsers.reserve(ui.currentResearchers->count());

        for (int i = 0; i < ui.currentResearchers->count(); i++) {
            currentUsers.push_back(dynamic_cast<ListItemWithData<i64>*>(ui.currentResearchers->item(i))->itemData());
        }

        auto previousUsers = storage->select(&Assignment::userId,
                                            where(c(&Assignment::researchId) == researchId));

        std::vector<i64> usersToAdd;
        std::vector<i64> usersToDelete;

        std::set_difference(currentUsers.begin(), currentUsers.end(), previousUsers.begin(),
                            previousUsers.end(), std::back_inserter(usersToAdd));
        std::set_difference(previousUsers.begin(), previousUsers.end(), currentUsers.begin(),
                            currentUsers.end(), std::back_inserter(usersToDelete));

        storage->remove_all<Assignment>(where(c(&Assignment::researchId) == researchId
                                             and in(&Assignment::userId, usersToDelete)));

        std::vector<Assignment> assignments;
        std::transform(usersToAdd.begin(), usersToAdd.end(), std::back_inserter(assignments),
                       [&](auto userId) { return Assignment{researchId, userId}; });

        storage->replace_range(assignments.begin(), assignments.end());

        return true;
    });

}

bool EditResearchersDialog::eventFilter(QObject* obj, QEvent* event) {
    if (event->type() == QEvent::FocusIn) {
        if (obj == ui.allResearchers) {
            ui.currentResearchers->setCurrentRow(-1);
        } else if (obj == ui.currentResearchers) {
            ui.allResearchers->setCurrentRow(-1);
        }
        
        updateButtons();
    }
    return false;
}
