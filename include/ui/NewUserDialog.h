#ifndef RESEARCHAPP_NEWUSERDIALOG_H
#define RESEARCHAPP_NEWUSERDIALOG_H


#include "ui_newuser.h"

/**
 * A dialog used to create new users.
 */
class NewUserDialog: public QDialog {
    Q_OBJECT

private:
    Ui::NewUser ui;
    bool loginValid = false;
    bool passValid = false;
    bool retypePassValid = false;
    void setValid(QLineEdit* line, bool& prop, bool valid, const QString& message);

private slots:
    void updateButtons();
    void validateLogin();
    void validatePass();
    void validateRetypePass();
    void accept() override;

signals:
    /**
     * Signal fired to notify that a new user was successfully added.
     * @param id ID of the new user.
     */
    void userAdded(std::string login);

public:
    /**
     * Constructs a `NewUserDialog` instance.
     * @param parent see Qt docs.
     * @param f see Qt docs.
     */
    explicit NewUserDialog(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
};


#endif //RESEARCHAPP_NEWUSERDIALOG_H
