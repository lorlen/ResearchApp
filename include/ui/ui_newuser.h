/********************************************************************************
** Form generated from reading UI file 'newuser.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWUSER_H
#define UI_NEWUSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_NewUser
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *displayName;
    QLabel *label_2;
    QLineEdit *login;
    QLabel *label_3;
    QLineEdit *password;
    QLabel *label_4;
    QLineEdit *retypePassword;
    QCheckBox *isAdmin;
    QLabel *status;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *NewUser)
    {
        if (NewUser->objectName().isEmpty())
            NewUser->setObjectName(QString::fromUtf8("NewUser"));
        NewUser->setWindowModality(Qt::ApplicationModal);
        NewUser->resize(500, 250);
        NewUser->setModal(true);
        gridLayout = new QGridLayout(NewUser);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(NewUser);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        displayName = new QLineEdit(NewUser);
        displayName->setObjectName(QString::fromUtf8("displayName"));

        gridLayout->addWidget(displayName, 0, 1, 1, 2);

        label_2 = new QLabel(NewUser);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        login = new QLineEdit(NewUser);
        login->setObjectName(QString::fromUtf8("login"));

        gridLayout->addWidget(login, 1, 1, 1, 2);

        label_3 = new QLabel(NewUser);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        password = new QLineEdit(NewUser);
        password->setObjectName(QString::fromUtf8("password"));
        password->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(password, 2, 1, 1, 2);

        label_4 = new QLabel(NewUser);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        retypePassword = new QLineEdit(NewUser);
        retypePassword->setObjectName(QString::fromUtf8("retypePassword"));
        retypePassword->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(retypePassword, 3, 1, 1, 2);

        isAdmin = new QCheckBox(NewUser);
        isAdmin->setObjectName(QString::fromUtf8("isAdmin"));

        gridLayout->addWidget(isAdmin, 4, 0, 1, 3);

        status = new QLabel(NewUser);
        status->setObjectName(QString::fromUtf8("status"));

        gridLayout->addWidget(status, 5, 0, 1, 2);

        buttonBox = new QDialogButtonBox(NewUser);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 5, 2, 1, 1);

        gridLayout->setColumnStretch(1, 1);
        gridLayout->setColumnStretch(2, 1);

        retranslateUi(NewUser);
        QObject::connect(buttonBox, SIGNAL(accepted()), NewUser, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NewUser, SLOT(reject()));

        QMetaObject::connectSlotsByName(NewUser);
    } // setupUi

    void retranslateUi(QDialog *NewUser)
    {
        NewUser->setWindowTitle(QCoreApplication::translate("NewUser", "Add new user", nullptr));
        label->setText(QCoreApplication::translate("NewUser", "Display name:", nullptr));
        label_2->setText(QCoreApplication::translate("NewUser", "Login:", nullptr));
        label_3->setText(QCoreApplication::translate("NewUser", "Password:", nullptr));
        label_4->setText(QCoreApplication::translate("NewUser", "Retype password:", nullptr));
        isAdmin->setText(QCoreApplication::translate("NewUser", "Administrator", nullptr));
        status->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class NewUser: public Ui_NewUser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWUSER_H
