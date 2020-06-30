#include <algorithm>

#include "ui/EditResearchersDialog.h"
#include "ui/NewUserDialog.h"
#include "ui/ListItemWithID.h"
#include "globals.h"

EditResearchersDialog::EditResearchersDialog(Research* research, QWidget* parent, Qt::WindowFlags f)
        : QDialog{parent, f}, ui{}, research{research} {
    ui.setupUi(this);

    ui.researchTitle->setText(QString("Research title: ") + research->get_researchTitle().c_str());

    auto allUsers = globals::db.get_users();
    auto currentUsers = research->get_users_ID();

    for (const auto& user: allUsers) {
        if (std::find(currentUsers.begin(), currentUsers.end(), user.first) == currentUsers.end()) {
            auto* item = new ListItemWithID{user.first, user.second.c_str()};
            ui.allResearchers->addItem(item);
        }
    }

    for (const auto& userID: currentUsers) {
        auto* item = new ListItemWithID(userID, globals::db.get_user(userID)->get_name().c_str());
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
    connect(ui.currentResearchers, &QListWidget::itemSelectionChanged, this, &EditResearchersDialog::updateButtons);
}

void EditResearchersDialog::updateButtons() {
    ui.addButton->setEnabled(ui.allResearchers->currentRow() >= 0);
    ui.deleteButton->setEnabled(ui.allResearchers->currentRow() >= 0 || ui.currentResearchers->currentRow() >= 0);
}

void EditResearchersDialog::appendUser(unsigned int id) {
    auto* item = new ListItemWithID{id, globals::db.get_user_name(id).c_str()};
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
    auto* item = dynamic_cast<ListItemWithID*>(ui.allResearchers->currentItem());

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
        auto* item = dynamic_cast<ListItemWithID*>(ui.allResearchers->currentItem());

        if (item != nullptr) {
            globals::db.remove_user(item->getID());
            delete ui.allResearchers->takeItem(ui.allResearchers->currentRow());
        }
    }

    updateButtons();
}

void EditResearchersDialog::applyChanges() {
    std::vector<unsigned int> userIDs;

    for (int i = 0; i < ui.currentResearchers->count(); i++) {
        auto* item = dynamic_cast<ListItemWithID*>(ui.currentResearchers->item(i));
        userIDs.push_back(item->getID());
    }

    research->set_users(userIDs);
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
