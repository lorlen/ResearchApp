/********************************************************************************
** Form generated from reading UI file 'editresearchers.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITRESEARCHERS_H
#define UI_EDITRESEARCHERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_EditResearchers
{
public:
    QGridLayout *gridLayout;
    QPushButton *deleteButton;
    QListWidget *currentResearchers;
    QListWidget *allResearchers;
    QPushButton *addButton;
    QLabel *researchTitle;
    QLabel *label_2;
    QPushButton *newUserButton;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *EditResearchers)
    {
        if (EditResearchers->objectName().isEmpty())
            EditResearchers->setObjectName(QString::fromUtf8("EditResearchers"));
        EditResearchers->setWindowModality(Qt::ApplicationModal);
        EditResearchers->resize(500, 500);
        EditResearchers->setModal(true);
        gridLayout = new QGridLayout(EditResearchers);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        deleteButton = new QPushButton(EditResearchers);
        deleteButton->setObjectName(QString::fromUtf8("deleteButton"));

        gridLayout->addWidget(deleteButton, 1, 3, 1, 1);

        currentResearchers = new QListWidget(EditResearchers);
        currentResearchers->setObjectName(QString::fromUtf8("currentResearchers"));

        gridLayout->addWidget(currentResearchers, 2, 2, 1, 2);

        allResearchers = new QListWidget(EditResearchers);
        allResearchers->setObjectName(QString::fromUtf8("allResearchers"));

        gridLayout->addWidget(allResearchers, 2, 0, 1, 2);

        addButton = new QPushButton(EditResearchers);
        addButton->setObjectName(QString::fromUtf8("addButton"));

        gridLayout->addWidget(addButton, 1, 2, 1, 1);

        researchTitle = new QLabel(EditResearchers);
        researchTitle->setObjectName(QString::fromUtf8("researchTitle"));

        gridLayout->addWidget(researchTitle, 0, 0, 1, 4);

        label_2 = new QLabel(EditResearchers);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        newUserButton = new QPushButton(EditResearchers);
        newUserButton->setObjectName(QString::fromUtf8("newUserButton"));

        gridLayout->addWidget(newUserButton, 1, 1, 1, 1);

        buttonBox = new QDialogButtonBox(EditResearchers);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 3, 0, 1, 4);

        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 1);
        gridLayout->setColumnStretch(2, 1);
        gridLayout->setColumnStretch(3, 1);

        retranslateUi(EditResearchers);
        QObject::connect(buttonBox, SIGNAL(accepted()), EditResearchers, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), EditResearchers, SLOT(reject()));

        QMetaObject::connectSlotsByName(EditResearchers);
    } // setupUi

    void retranslateUi(QDialog *EditResearchers)
    {
        EditResearchers->setWindowTitle(QCoreApplication::translate("EditResearchers", "Manage researchers", nullptr));
        deleteButton->setText(QCoreApplication::translate("EditResearchers", "Delete", nullptr));
        addButton->setText(QCoreApplication::translate("EditResearchers", "Add", nullptr));
        researchTitle->setText(QCoreApplication::translate("EditResearchers", "Research title:", nullptr));
        label_2->setText(QCoreApplication::translate("EditResearchers", "Members", nullptr));
        newUserButton->setText(QCoreApplication::translate("EditResearchers", "New user", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditResearchers: public Ui_EditResearchers {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITRESEARCHERS_H
