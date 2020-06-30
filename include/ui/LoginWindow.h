#ifndef PROJEKT_LOGINWINDOW_H
#define PROJEKT_LOGINWINDOW_H


#include <QtWidgets/QWidget>
#include "ui/ui_login.h"

/**
 * A window shown at application startup, prompting the user to log in to the
 * application.
 */
class LoginWindow: public QWidget {
private:
    Ui::Login ui;

private slots:
    void tryLogin();

public:
    LoginWindow();
};


#endif //PROJEKT_LOGINWINDOW_H
