/********************************************************************************
** Form generated from reading UI file 'main.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_H
#define UI_MAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Main
{
public:
    QHBoxLayout *horizontalLayout;
    QCalendarWidget *calendarWidget;
    QStackedWidget *stackedWidget;
    QWidget *pageSelect;
    QWidget *pageAdd;

    void setupUi(QWidget *Main)
    {
        if (Main->objectName().isEmpty())
            Main->setObjectName(QString::fromUtf8("Main"));
        Main->resize(1000, 550);
        horizontalLayout = new QHBoxLayout(Main);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        calendarWidget = new QCalendarWidget(Main);
        calendarWidget->setObjectName(QString::fromUtf8("calendarWidget"));
        calendarWidget->setFirstDayOfWeek(Qt::Monday);

        horizontalLayout->addWidget(calendarWidget);

        stackedWidget = new QStackedWidget(Main);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        pageSelect = new QWidget();
        pageSelect->setObjectName(QString::fromUtf8("pageSelect"));
        stackedWidget->addWidget(pageSelect);
        pageAdd = new QWidget();
        pageAdd->setObjectName(QString::fromUtf8("pageAdd"));
        stackedWidget->addWidget(pageAdd);

        horizontalLayout->addWidget(stackedWidget);

        horizontalLayout->setStretch(0, 3);
        horizontalLayout->setStretch(1, 5);

        retranslateUi(Main);

        QMetaObject::connectSlotsByName(Main);
    } // setupUi

    void retranslateUi(QWidget *Main)
    {
        Main->setWindowTitle(QCoreApplication::translate("Main", "Research selection", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Main: public Ui_Main {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_H
