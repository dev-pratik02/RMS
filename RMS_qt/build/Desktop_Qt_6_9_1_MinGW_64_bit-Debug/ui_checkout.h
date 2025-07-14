/********************************************************************************
** Form generated from reading UI file 'checkout.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHECKOUT_H
#define UI_CHECKOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>

QT_BEGIN_NAMESPACE

class Ui_checkout
{
public:
    QFrame *frame;

    void setupUi(QDialog *checkout)
    {
        if (checkout->objectName().isEmpty())
            checkout->setObjectName("checkout");
        checkout->resize(900, 700);
        frame = new QFrame(checkout);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(40, 20, 820, 660));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        retranslateUi(checkout);

        QMetaObject::connectSlotsByName(checkout);
    } // setupUi

    void retranslateUi(QDialog *checkout)
    {
        checkout->setWindowTitle(QCoreApplication::translate("checkout", "Checkout", nullptr));
    } // retranslateUi

};

namespace Ui {
    class checkout: public Ui_checkout {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHECKOUT_H
