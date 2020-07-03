#include "ui/NewUserDialog.h"
#include "globals.h"

NewUserDialog::NewUserDialog(QWidget* parent, Qt::WindowFlags f)
        : QDialog{parent, f}, ui{} {
    ui.setupUi(this);

    updateButtons();

    connect(ui.login, &QLineEdit::textChanged, this, &NewUserDialog::validateLogin);
    connect(ui.password, &QLineEdit::textChanged, this, &NewUserDialog::validatePass);
    connect(ui.retypePassword, &QLineEdit::textChanged, this, &NewUserDialog::validateRetypePass);
}

void NewUserDialog::setValid(QLineEdit* line, bool& prop, bool valid, QString message) {
    prop = valid;
    line->setStyleSheet(valid ? "" : "background-color: rgb(255, 128, 128)");

    if (!valid)
        ui.status->setText("<span style=\"color: red\">" + message + "</span>");
    else
        ui.status->setText("");

    updateButtons();
}

void NewUserDialog::updateButtons() {
    auto okButton = ui.buttonBox->button(QDialogButtonBox::Ok);
    bool valid = loginValid && passValid && retypePassValid;

    okButton->setAutoDefault(valid);
    okButton->setDefault(valid);
    okButton->setEnabled(valid);
}

void NewUserDialog::validateLogin() {
    bool isUserInDb = false;

    if (!ui.login->text().isEmpty()) {
        for (const auto& [id, user]: globals::db.users()) {
            if (ui.login->text() == user->login().c_str()) {
                isUserInDb = true;
                break;
            }
        }
    }

    if (isUserInDb)
        setValid(ui.login, loginValid, false, "User already exists");
    else if (ui.login->text().isEmpty())
        setValid(ui.login, loginValid, false, "Login must not be empty");
    else
        setValid(ui.login, loginValid, true, "");
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
    User user(
            ui.login->text().toStdString(),
            ui.displayName->text().toStdString(),
            ui.password->text().toStdString(),
            ui.isAdmin->isChecked()
    );

    emit userAdded(globals::db.addUser(user));
    close();
}
