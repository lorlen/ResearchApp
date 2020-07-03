/********************************************************************************
** Form generated from reading UI file 'newsensor.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWSENSOR_H
#define UI_NEWSENSOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_NewSensor
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *sensorLabel;
    QLabel *label_2;
    QLineEdit *sensorType;
    QLabel *label_3;
    QLineEdit *sensorUnit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *NewSensor)
    {
        if (NewSensor->objectName().isEmpty())
            NewSensor->setObjectName(QString::fromUtf8("NewSensor"));
        NewSensor->setWindowModality(Qt::ApplicationModal);
        NewSensor->resize(400, 180);
        NewSensor->setModal(true);
        gridLayout = new QGridLayout(NewSensor);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(NewSensor);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        sensorLabel = new QLineEdit(NewSensor);
        sensorLabel->setObjectName(QString::fromUtf8("sensorLabel"));

        gridLayout->addWidget(sensorLabel, 0, 1, 1, 1);

        label_2 = new QLabel(NewSensor);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        sensorType = new QLineEdit(NewSensor);
        sensorType->setObjectName(QString::fromUtf8("sensorType"));

        gridLayout->addWidget(sensorType, 1, 1, 1, 1);

        label_3 = new QLabel(NewSensor);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        sensorUnit = new QLineEdit(NewSensor);
        sensorUnit->setObjectName(QString::fromUtf8("sensorUnit"));

        gridLayout->addWidget(sensorUnit, 2, 1, 1, 1);

        buttonBox = new QDialogButtonBox(NewSensor);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 3, 0, 1, 2);


        retranslateUi(NewSensor);
        QObject::connect(buttonBox, SIGNAL(accepted()), NewSensor, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NewSensor, SLOT(reject()));

        QMetaObject::connectSlotsByName(NewSensor);
    } // setupUi

    void retranslateUi(QDialog *NewSensor)
    {
        NewSensor->setWindowTitle(QCoreApplication::translate("NewSensor", "Add new sensor", nullptr));
        label->setText(QCoreApplication::translate("NewSensor", "Label:", nullptr));
        label_2->setText(QCoreApplication::translate("NewSensor", "Type:", nullptr));
        label_3->setText(QCoreApplication::translate("NewSensor", "Unit:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NewSensor: public Ui_NewSensor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWSENSOR_H
