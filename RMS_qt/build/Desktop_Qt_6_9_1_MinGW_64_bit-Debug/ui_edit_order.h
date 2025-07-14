/********************************************************************************
** Form generated from reading UI file 'edit_order.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDIT_ORDER_H
#define UI_EDIT_ORDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>

QT_BEGIN_NAMESPACE

class Ui_edit_order
{
public:
    QFrame *frame;

    void setupUi(QDialog *edit_order)
    {
        if (edit_order->objectName().isEmpty())
            edit_order->setObjectName("edit_order");
        edit_order->resize(800, 600);
        frame = new QFrame(edit_order);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(50, 19, 711, 561));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);

        retranslateUi(edit_order);

        QMetaObject::connectSlotsByName(edit_order);
    } // setupUi

    void retranslateUi(QDialog *edit_order)
    {
        edit_order->setWindowTitle(QCoreApplication::translate("edit_order", "Edit Order", nullptr));
    } // retranslateUi

};

namespace Ui {
    class edit_order: public Ui_edit_order {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDIT_ORDER_H
