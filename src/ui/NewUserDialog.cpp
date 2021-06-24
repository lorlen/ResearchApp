#include "ui/NewUserDialog.h"

#include <QtWidgets/QPushButton>

#include "db/LoginManager.h"
#include "sqlite_orm/sqlite_orm.h"

NewUserDialog::NewUserDialog(std::shared_ptr<Storage> _storage, QWidget* parent, Qt::WindowFlags f)
        : QDialog{parent, f}, ui{}, storage{std::move(_storage)} {
    ui.setupUi(this);

    updateButtons();

    connect(ui.login, &QLineEdit::textChanged, this, &NewUserDialog::validateLogin);
    connect(ui.password, &QLineEdit::textChanged, this, &NewUserDialog::validatePass);
    connect(ui.retypePassword, &QLineEdit::textChanged, this, &NewUserDialog::validateRetypePass);
}

void NewUserDialog::setValid(QLineEdit* line, bool& prop, bool valid, const QString& message) {
    prop = valid;
    line->setStyleSheet(valid ? "" : "background-color: rgb(255, 128, 128)");

    if (!valid) {
        ui.status->setText("<span style=\"color: red\">" + message + "</span>");
    } else {
        ui.status->setText("");
    }

    updateButtons();
}

void NewUserDialog::updateButtons() {
    auto* okButton = ui.buttonBox->button(QDialogButtonBox::Ok);
    bool valid = loginValid && passValid && retypePassValid;

    okButton->setAutoDefault(valid);
    okButton->setDefault(valid);
    okButton->setEnabled(valid);
}

void NewUserDialog::validateLogin() {
    using namespace sqlite_orm;

    if (storage->count<User>(where(c(&User::login) == ui.login->text().toStdString())) > 0) {
        setValid(ui.login, loginValid, false, "User already exists");
    } else if (ui.login->text().isEmpty()) {
        setValid(ui.login, loginValid, false, "Login must not be empty");
    } else {
        setValid(ui.login, loginValid, true, "");
    }
}

void NewUserDialog::validatePass() {
    setValid(ui.password, passValid, !ui.password->text().isEmpty(), "Password must not be empty");
}

void NewUserDialog::validateRetypePass() {
    setValid(
            ui.retypePassword,
            retypePassValid,
            !ui.retypePassword->text().isEmpty() && ui.retypePassword->text() == ui.password->text(),
            "Both passwords must match"
    );
}

void NewUserDialog::accept() {
    auto user = LoginManager::registerUser(
        ui.login->text().toStdString(),
        ui.displayName->text().toStdString(),
        ui.password->text().toStdString()
    );

    emit userAdded(*user);
    close();
}
