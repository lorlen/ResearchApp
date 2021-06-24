#pragma once

#include <memory>
#include <QtWidgets/QWidget>
#include "db/storage.h"
#include "designer/ui_login.h"

/**
 * A window shown at application startup, prompting the user to log in to the
 * application.
 */
class LoginWindow: public QWidget {
private:
    Ui::Login ui;
    std::shared_ptr<Storage> storage;

private slots:
    void tryLogin();

public:
    LoginWindow(std::shared_ptr<Storage> _storage);
};
