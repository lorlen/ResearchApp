/********************************************************************************
** Form generated from reading UI file 'editpoint.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITPOINT_H
#define UI_EDITPOINT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_EditResearchPoint
{
public:
    QGridLayout *gridLayout;
    QLabel *label_2;
    QListWidget *allSensors;
    QListWidget *currentSensors;
    QPushButton *deleteButton;
    QPushButton *addButton;
    QLineEdit *pointInfo;
    QPushButton *newButton;
    QLabel *label;
    QCheckBox *requiredMeasurement;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *EditResearchPoint)
    {
        if (EditResearchPoint->objectName().isEmpty())
            EditResearchPoint->setObjectName(QString::fromUtf8("EditResearchPoint"));
        EditResearchPoint->setWindowModality(Qt::ApplicationModal);
        EditResearchPoint->resize(500, 500);
        EditResearchPoint->setModal(true);
        gridLayout = new QGridLayout(EditResearchPoint);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(EditResearchPoint);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        allSensors = new QListWidget(EditResearchPoint);
        allSensors->setObjectName(QString::fromUtf8("allSensors"));

        gridLayout->addWidget(allSensors, 4, 0, 1, 2);

        currentSensors = new QListWidget(EditResearchPoint);
        currentSensors->setObjectName(QString::fromUtf8("currentSensors"));

        gridLayout->addWidget(currentSensors, 4, 2, 1, 2);

        deleteButton = new QPushButton(EditResearchPoint);
        deleteButton->setObjectName(QString::fromUtf8("deleteButton"));

        gridLayout->addWidget(deleteButton, 3, 3, 1, 1);

        addButton = new QPushButton(EditResearchPoint);
        addButton->setObjectName(QString::fromUtf8("addButton"));

        gridLayout->addWidget(addButton, 3, 2, 1, 1);

        pointInfo = new QLineEdit(EditResearchPoint);
        pointInfo->setObjectName(QString::fromUtf8("pointInfo"));

        gridLayout->addWidget(pointInfo, 1, 0, 1, 4);

        newButton = new QPushButton(EditResearchPoint);
        newButton->setObjectName(QString::fromUtf8("newButton"));

        gridLayout->addWidget(newButton, 3, 1, 1, 1);

        label = new QLabel(EditResearchPoint);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 4);

        requiredMeasurement = new QCheckBox(EditResearchPoint);
        requiredMeasurement->setObjectName(QString::fromUtf8("requiredMeasurement"));

        gridLayout->addWidget(requiredMeasurement, 2, 0, 1, 4);

        buttonBox = new QDialogButtonBox(EditResearchPoint);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 5, 0, 1, 4);

        QWidget::setTabOrder(pointInfo, requiredMeasurement);
        QWidget::setTabOrder(requiredMeasurement, newButton);
        QWidget::setTabOrder(newButton, addButton);
        QWidget::setTabOrder(addButton, deleteButton);
        QWidget::setTabOrder(deleteButton, allSensors);
        QWidget::setTabOrder(allSensors, currentSensors);

        retranslateUi(EditResearchPoint);
        QObject::connect(buttonBox, SIGNAL(accepted()), EditResearchPoint, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), EditResearchPoint, SLOT(reject()));

        QMetaObject::connectSlotsByName(EditResearchPoint);
    } // setupUi

    void retranslateUi(QDialog *EditResearchPoint)
    {
        EditResearchPoint->setWindowTitle(QCoreApplication::translate("EditResearchPoint", "Edit research point", nullptr));
        label_2->setText(QCoreApplication::translate("EditResearchPoint", "Sensors", nullptr));
        deleteButton->setText(QCoreApplication::translate("EditResearchPoint", "Delete", nullptr));
        addButton->setText(QCoreApplication::translate("EditResearchPoint", "Add", nullptr));
        newButton->setText(QCoreApplication::translate("EditResearchPoint", "New", nullptr));
        label->setText(QCoreApplication::translate("EditResearchPoint", "Information:", nullptr));
        requiredMeasurement->setText(QCoreApplication::translate("EditResearchPoint", "Required measurement", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EditResearchPoint: public Ui_EditResearchPoint {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITPOINT_H
