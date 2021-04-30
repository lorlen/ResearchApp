#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>
#include <QtWidgets/QPushButton>

#include "db/Database.h"
#include "db/exceptions.h"
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
    try {
        globals::db.logIn(ui.loginline->text().toStdString(), ui.passline->text().toStdString());
        hide();
        auto* mainWindow = new MainWindow{};
        mainWindow->setAttribute(Qt::WA_DeleteOnClose);
        mainWindow->show();
    }
    catch (const UserNotFoundException&) {
        ui.invalidPassword->setText("<span style=\"color: red\">Invalid username or password</span>");
    }
}