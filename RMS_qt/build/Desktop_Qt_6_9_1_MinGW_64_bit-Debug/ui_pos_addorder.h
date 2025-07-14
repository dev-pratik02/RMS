/********************************************************************************
** Form generated from reading UI file 'pos_addorder.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POS_ADDORDER_H
#define UI_POS_ADDORDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_POS_AddOrder
{
public:

    void setupUi(QDialog *POS_AddOrder)
    {
        if (POS_AddOrder->objectName().isEmpty())
            POS_AddOrder->setObjectName("POS_AddOrder");
        POS_AddOrder->resize(1280, 800);

        retranslateUi(POS_AddOrder);

        QMetaObject::connectSlotsByName(POS_AddOrder);
    } // setupUi

    void retranslateUi(QDialog *POS_AddOrder)
    {
        POS_AddOrder->setWindowTitle(QCoreApplication::translate("POS_AddOrder", "Add order", nullptr));
    } // retranslateUi

};

namespace Ui {
    class POS_AddOrder: public Ui_POS_AddOrder {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POS_ADDORDER_H
