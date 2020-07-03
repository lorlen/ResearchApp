/********************************************************************************
** Form generated from reading UI file 'sensorlist.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENSORLIST_H
#define UI_SENSORLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_SensorList
{
public:
    QGridLayout *gridLayout;
    QPushButton *okButton;
    QSpacerItem *horizontalSpacer;
    QListWidget *sensorList;

    void setupUi(QDialog *SensorList)
    {
        if (SensorList->objectName().isEmpty())
            SensorList->setObjectName(QString::fromUtf8("SensorList"));
        SensorList->setWindowModality(Qt::ApplicationModal);
        SensorList->resize(400, 250);
        SensorList->setModal(true);
        gridLayout = new QGridLayout(SensorList);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        okButton = new QPushButton(SensorList);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        gridLayout->addWidget(okButton, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        sensorList = new QListWidget(SensorList);
        sensorList->setObjectName(QString::fromUtf8("sensorList"));
        sensorList->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(sensorList, 0, 0, 1, 2);


        retranslateUi(SensorList);

        QMetaObject::connectSlotsByName(SensorList);
    } // setupUi

    void retranslateUi(QDialog *SensorList)
    {
        SensorList->setWindowTitle(QCoreApplication::translate("SensorList", "Sensor list", nullptr));
        okButton->setText(QCoreApplication::translate("SensorList", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SensorList: public Ui_SensorList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENSORLIST_H
