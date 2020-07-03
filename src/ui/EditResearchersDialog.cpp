#include <algorithm>

#include "ui/EditResearchersDialog.h"
#include "ui/NewUserDialog.h"
#include "ui/ListItemWithData.h"
#include "globals.h"

EditResearchersDialog::EditResearchersDialog(std::shared_ptr<Research> research, QWidget* parent, Qt::WindowFlags f)
        : QDialog{parent, f}, ui{}, research{research} {
    ui.setupUi(this);

    ui.researchTitle->setText(QString("Research title: ") + research->title().c_str());

    auto currentUsers = research->assignedUsers();

    for (const auto& [id, user]: globals::db.users()) {
        if (std::find_if(currentUsers.begin(), currentUsers.end(), [&user](auto e) { return *e.lock() == *user; }) == currentUsers.end()) {
            auto* item = new ListItemWithData<std::string>{id, user->displayName().c_str()};
            ui.allResearchers->addItem(item);
        }
    }

    for (auto user_weak: currentUsers) {
        auto user = user_weak.lock();
        auto* item = new ListItemWithData<std::string>(user->id(), user->displayName().c_str());
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

void EditResearchersDialog::appendUser(std::string login) {
    auto* item = new ListItemWithData<std::string>{login, globals::db.users().at(login)->displayName().c_str()};
    ui.allResearchers->addItem(item);
    updateButtons();
}

void EditResearchersDialog::newUser() {
    auto* dialog = new NewUserDialog{this};
    connect(dialog, &NewUserDialog::userAdded, this, &EditResearchersDialog::appendUser);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->show();
}

void EditResearchersDialog::addResearcher() {
    auto* item = dynamic_cast<ListItemWithData<std::string>*>(ui.allResearchers->currentItem());

    if (item != nullptr) {
        ui.allResearchers->takeItem(ui.allResearchers->currentRow());
        ui.currentResearchers->addItem(item);
    }

    updateButtons();
}

void EditResearchersDialog::deleteResearcher() {
    if (ui.allResearchers->currentRow() < 0 && ui.currentResearchers->currentRow() >= 0) {
        ui.allResearchers->addItem(ui.currentResearchers->takeItem(ui.currentResearchers->currentRow()));
    }
    else if (ui.currentResearchers->currentRow() < 0 && ui.allResearchers->currentRow() >= 0) {
        auto* item = dynamic_cast<ListItemWithData<std::string>*>(ui.allResearchers->currentItem());

        if (item != nullptr) {
            globals::db.deleteUser(item->data());
            delete ui.allResearchers->takeItem(ui.allResearchers->currentRow());
        }
    }

    updateButtons();
}

void EditResearchersDialog::applyChanges() {
    std::vector<std::shared_ptr<User>> users;

    for (int i = 0; i < ui.currentResearchers->count(); i++) {
        auto* item = dynamic_cast<ListItemWithData<std::string>*>(ui.currentResearchers->item(i));
        users.push_back(globals::db.users().at(item->data()));
    }

    research->assignedUsers(users);
}

bool EditResearchersDialog::eventFilter(QObject* obj, QEvent* event) {
    if (event->type() == QEvent::FocusIn) {
        if (obj == ui.allResearchers)
            ui.currentResearchers->setCurrentRow(-1);
        else if (obj == ui.currentResearchers)
            ui.allResearchers->setCurrentRow(-1);
        updateButtons();
    }
    return false;
}
