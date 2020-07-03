/********************************************************************************
** Form generated from reading UI file 'selectresearch.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTRESEARCH_H
#define UI_SELECTRESEARCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectResearch
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *startDate;
    QLabel *endDate;
    QListWidget *checklist;
    QPushButton *sensorButton;
    QLabel *researchTitle;
    QProgressBar *researchProgress;
    QLabel *label_6;
    QLabel *label_2;
    QTextBrowser *researchInfo;
    QLabel *label_3;
    QLabel *label;
    QPushButton *logoutButton;
    QPushButton *deleteButton;
    QPushButton *editButton;
    QPushButton *addButton;

    void setupUi(QWidget *SelectResearch)
    {
        if (SelectResearch->objectName().isEmpty())
            SelectResearch->setObjectName(QString::fromUtf8("SelectResearch"));
        SelectResearch->resize(610, 532);
        verticalLayout = new QVBoxLayout(SelectResearch);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        startDate = new QLabel(SelectResearch);
        startDate->setObjectName(QString::fromUtf8("startDate"));

        gridLayout->addWidget(startDate, 1, 0, 1, 2);

        endDate = new QLabel(SelectResearch);
        endDate->setObjectName(QString::fromUtf8("endDate"));

        gridLayout->addWidget(endDate, 1, 3, 1, 2);

        checklist = new QListWidget(SelectResearch);
        checklist->setObjectName(QString::fromUtf8("checklist"));

        gridLayout->addWidget(checklist, 6, 0, 1, 5);

        sensorButton = new QPushButton(SelectResearch);
        sensorButton->setObjectName(QString::fromUtf8("sensorButton"));

        gridLayout->addWidget(sensorButton, 4, 1, 1, 1);

        researchTitle = new QLabel(SelectResearch);
        researchTitle->setObjectName(QString::fromUtf8("researchTitle"));

        gridLayout->addWidget(researchTitle, 0, 0, 1, 5);

        researchProgress = new QProgressBar(SelectResearch);
        researchProgress->setObjectName(QString::fromUtf8("researchProgress"));
        researchProgress->setValue(0);

        gridLayout->addWidget(researchProgress, 4, 3, 1, 2);

        label_6 = new QLabel(SelectResearch);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 4, 0, 1, 1);

        label_2 = new QLabel(SelectResearch);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 4, 2, 1, 1);

        researchInfo = new QTextBrowser(SelectResearch);
        researchInfo->setObjectName(QString::fromUtf8("researchInfo"));
        researchInfo->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(researchInfo, 3, 0, 1, 5);

        label_3 = new QLabel(SelectResearch);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label = new QLabel(SelectResearch);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 5, 0, 1, 1);

        logoutButton = new QPushButton(SelectResearch);
        logoutButton->setObjectName(QString::fromUtf8("logoutButton"));

        gridLayout->addWidget(logoutButton, 7, 4, 1, 1);

        deleteButton = new QPushButton(SelectResearch);
        deleteButton->setObjectName(QString::fromUtf8("deleteButton"));

        gridLayout->addWidget(deleteButton, 7, 2, 1, 1);

        editButton = new QPushButton(SelectResearch);
        editButton->setObjectName(QString::fromUtf8("editButton"));

        gridLayout->addWidget(editButton, 7, 1, 1, 1);

        addButton = new QPushButton(SelectResearch);
        addButton->setObjectName(QString::fromUtf8("addButton"));

        gridLayout->addWidget(addButton, 7, 0, 1, 1);

        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 1);
        gridLayout->setColumnStretch(2, 1);
        gridLayout->setColumnStretch(3, 1);
        gridLayout->setColumnStretch(4, 1);

        verticalLayout->addLayout(gridLayout);

        QWidget::setTabOrder(sensorButton, checklist);
        QWidget::setTabOrder(checklist, addButton);
        QWidget::setTabOrder(addButton, editButton);
        QWidget::setTabOrder(editButton, deleteButton);
        QWidget::setTabOrder(deleteButton, logoutButton);

        retranslateUi(SelectResearch);

        QMetaObject::connectSlotsByName(SelectResearch);
    } // setupUi

    void retranslateUi(QWidget *SelectResearch)
    {
        SelectResearch->setWindowTitle(QCoreApplication::translate("SelectResearch", "Research Selection", nullptr));
        startDate->setText(QCoreApplication::translate("SelectResearch", "Start date:", nullptr));
        endDate->setText(QCoreApplication::translate("SelectResearch", "End date:", nullptr));
        sensorButton->setText(QCoreApplication::translate("SelectResearch", "Show", nullptr));
        researchTitle->setText(QCoreApplication::translate("SelectResearch", "Title:", nullptr));
#if QT_CONFIG(tooltip)
        researchProgress->setToolTip(QCoreApplication::translate("SelectResearch", "Research progress", nullptr));
#endif // QT_CONFIG(tooltip)
        label_6->setText(QCoreApplication::translate("SelectResearch", "Sensors", nullptr));
        label_2->setText(QCoreApplication::translate("SelectResearch", "Progress:", nullptr));
        label_3->setText(QCoreApplication::translate("SelectResearch", "Information:", nullptr));
        label->setText(QCoreApplication::translate("SelectResearch", "Checklist:", nullptr));
        logoutButton->setText(QCoreApplication::translate("SelectResearch", "Logout", nullptr));
        deleteButton->setText(QCoreApplication::translate("SelectResearch", "Delete", nullptr));
        editButton->setText(QCoreApplication::translate("SelectResearch", "Edit", nullptr));
        addButton->setText(QCoreApplication::translate("SelectResearch", "Add new", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectResearch: public Ui_SelectResearch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTRESEARCH_H
