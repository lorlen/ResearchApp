/********************************************************************************
** Form generated from reading UI file 'addresearch.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDRESEARCH_H
#define UI_ADDRESEARCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddResearch
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QPushButton *editResearchersButton;
    QDateEdit *endDate;
    QPushButton *deletePointButton;
    QLabel *label_6;
    QLabel *label_2;
    QPushButton *okButton;
    QLabel *label_5;
    QDateEdit *startDate;
    QLabel *label_4;
    QTextEdit *researchInfo;
    QListWidget *checklist;
    QLabel *label_3;
    QPushButton *newPointButton;
    QLabel *label;
    QPushButton *editPointButton;
    QPushButton *cancelButton;
    QLineEdit *researchTitle;

    void setupUi(QWidget *AddResearch)
    {
        if (AddResearch->objectName().isEmpty())
            AddResearch->setObjectName(QString::fromUtf8("AddResearch"));
        AddResearch->resize(610, 532);
        verticalLayout = new QVBoxLayout(AddResearch);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        editResearchersButton = new QPushButton(AddResearch);
        editResearchersButton->setObjectName(QString::fromUtf8("editResearchersButton"));

        gridLayout->addWidget(editResearchersButton, 4, 2, 1, 1);

        endDate = new QDateEdit(AddResearch);
        endDate->setObjectName(QString::fromUtf8("endDate"));

        gridLayout->addWidget(endDate, 1, 4, 1, 1);

        deletePointButton = new QPushButton(AddResearch);
        deletePointButton->setObjectName(QString::fromUtf8("deletePointButton"));

        gridLayout->addWidget(deletePointButton, 5, 4, 1, 1);

        label_6 = new QLabel(AddResearch);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 5, 0, 1, 2);

        label_2 = new QLabel(AddResearch);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        okButton = new QPushButton(AddResearch);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        gridLayout->addWidget(okButton, 7, 0, 1, 1);

        label_5 = new QLabel(AddResearch);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 2);

        startDate = new QDateEdit(AddResearch);
        startDate->setObjectName(QString::fromUtf8("startDate"));
        startDate->setToolTipDuration(-1);

        gridLayout->addWidget(startDate, 1, 1, 1, 1);

        label_4 = new QLabel(AddResearch);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        researchInfo = new QTextEdit(AddResearch);
        researchInfo->setObjectName(QString::fromUtf8("researchInfo"));
        researchInfo->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));

        gridLayout->addWidget(researchInfo, 3, 0, 1, 5);

        checklist = new QListWidget(AddResearch);
        checklist->setObjectName(QString::fromUtf8("checklist"));

        gridLayout->addWidget(checklist, 6, 0, 1, 5);

        label_3 = new QLabel(AddResearch);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 3, 1, 1);

        newPointButton = new QPushButton(AddResearch);
        newPointButton->setObjectName(QString::fromUtf8("newPointButton"));

        gridLayout->addWidget(newPointButton, 5, 2, 1, 1);

        label = new QLabel(AddResearch);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        editPointButton = new QPushButton(AddResearch);
        editPointButton->setObjectName(QString::fromUtf8("editPointButton"));

        gridLayout->addWidget(editPointButton, 5, 3, 1, 1);

        cancelButton = new QPushButton(AddResearch);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        gridLayout->addWidget(cancelButton, 7, 4, 1, 1);

        researchTitle = new QLineEdit(AddResearch);
        researchTitle->setObjectName(QString::fromUtf8("researchTitle"));

        gridLayout->addWidget(researchTitle, 0, 1, 1, 4);

        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 1);
        gridLayout->setColumnStretch(2, 1);
        gridLayout->setColumnStretch(3, 1);
        gridLayout->setColumnStretch(4, 1);

        verticalLayout->addLayout(gridLayout);

        QWidget::setTabOrder(researchTitle, startDate);
        QWidget::setTabOrder(startDate, endDate);
        QWidget::setTabOrder(endDate, researchInfo);
        QWidget::setTabOrder(researchInfo, editResearchersButton);
        QWidget::setTabOrder(editResearchersButton, newPointButton);
        QWidget::setTabOrder(newPointButton, editPointButton);
        QWidget::setTabOrder(editPointButton, deletePointButton);
        QWidget::setTabOrder(deletePointButton, checklist);
        QWidget::setTabOrder(checklist, okButton);
        QWidget::setTabOrder(okButton, cancelButton);

        retranslateUi(AddResearch);

        QMetaObject::connectSlotsByName(AddResearch);
    } // setupUi

    void retranslateUi(QWidget *AddResearch)
    {
        AddResearch->setWindowTitle(QCoreApplication::translate("AddResearch", "Add/Edit research", nullptr));
        editResearchersButton->setText(QCoreApplication::translate("AddResearch", "Edit", nullptr));
        endDate->setDisplayFormat(QCoreApplication::translate("AddResearch", "dd.MM.yyyy", nullptr));
        deletePointButton->setText(QCoreApplication::translate("AddResearch", "Delete", nullptr));
        label_6->setText(QCoreApplication::translate("AddResearch", "Checklist:", nullptr));
        label_2->setText(QCoreApplication::translate("AddResearch", "Start date:", nullptr));
        okButton->setText(QCoreApplication::translate("AddResearch", "OK", nullptr));
        label_5->setText(QCoreApplication::translate("AddResearch", "Manage researchers:", nullptr));
        startDate->setDisplayFormat(QCoreApplication::translate("AddResearch", "dd.MM.yyyy", nullptr));
        label_4->setText(QCoreApplication::translate("AddResearch", "Information:", nullptr));
        label_3->setText(QCoreApplication::translate("AddResearch", "End date:", nullptr));
        newPointButton->setText(QCoreApplication::translate("AddResearch", "New point", nullptr));
        label->setText(QCoreApplication::translate("AddResearch", "Title:", nullptr));
        editPointButton->setText(QCoreApplication::translate("AddResearch", "Edit", nullptr));
        cancelButton->setText(QCoreApplication::translate("AddResearch", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddResearch: public Ui_AddResearch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDRESEARCH_H
