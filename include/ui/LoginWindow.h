#pragma once

#include <QtWidgets/QWidget>
#include "designer/ui_login.h"

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
