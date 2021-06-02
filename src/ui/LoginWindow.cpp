#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>
#include <QtWidgets/QPushButton>

#include "db/exceptions.h"
#include "db/LoginManager.h"
#include "ui/LoginWindow.h"
#include "ui/MainWindow.h"

LoginWindow::LoginWindow() : ui{} {
    ui.setupUi(this);
    ui.loginline->setFocus();
    move(QApplication::desktop()->geometry().center() - rect().center());
    connect(ui.loginButton, &QPushButton::clicked, this, &LoginWindow::tryLogin);
    connect(ui.loginline, &QLineEdit::returnPressed, this, &LoginWindow::tryLogin);
    connect(ui.passline, &QLineEdit::returnPressed, this, &LoginWindow::tryLogin);
}

void LoginWindow::tryLogin() {
    auto user = LoginManager::logIn(ui.loginline->text().toStdString(), ui.passline->text().toStdString());

    if (user.has_value()) {
        hide();
        auto* mainWindow = new MainWindow{};
        mainWindow->setAttribute(Qt::WA_DeleteOnClose);
        mainWindow->show();
    } else {
        ui.invalidPassword->setText("<span style=\"color: red\">Invalid username or password</span>");
    }
}