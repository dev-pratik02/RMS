/********************************************************************************
** Form generated from reading UI file 'signup.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNUP_H
#define UI_SIGNUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_signup
{
public:
    QLabel *label;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *form_phone;
    QLineEdit *form_name;
    QLineEdit *form_dob;
    QLineEdit *form_cpass;
    QLineEdit *formemail;
    QLineEdit *form_pass;

    void setupUi(QDialog *signup)
    {
        if (signup->objectName().isEmpty())
            signup->setObjectName("signup");
        signup->resize(800, 600);
        label = new QLabel(signup);
        label->setObjectName("label");
        label->setGeometry(QRect(300, 50, 181, 24));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(16);
        font.setBold(true);
        label->setFont(font);
        widget = new QWidget(signup);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(61, 111, 141, 321));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial")});
        font1.setPointSize(12);
        label_2->setFont(font1);

        verticalLayout_2->addWidget(label_2);

        label_3 = new QLabel(widget);
        label_3->setObjectName("label_3");
        label_3->setFont(font1);

        verticalLayout_2->addWidget(label_3);

        label_4 = new QLabel(widget);
        label_4->setObjectName("label_4");
        label_4->setFont(font1);

        verticalLayout_2->addWidget(label_4);

        label_5 = new QLabel(widget);
        label_5->setObjectName("label_5");
        label_5->setFont(font1);

        verticalLayout_2->addWidget(label_5);

        label_6 = new QLabel(widget);
        label_6->setObjectName("label_6");
        label_6->setFont(font1);

        verticalLayout_2->addWidget(label_6);

        label_7 = new QLabel(widget);
        label_7->setObjectName("label_7");
        label_7->setFont(font1);

        verticalLayout_2->addWidget(label_7);

        form_phone = new QLineEdit(signup);
        form_phone->setObjectName("form_phone");
        form_phone->setGeometry(QRect(211, 175, 221, 31));
        form_name = new QLineEdit(signup);
        form_name->setObjectName("form_name");
        form_name->setGeometry(QRect(210, 123, 221, 31));
        form_dob = new QLineEdit(signup);
        form_dob->setObjectName("form_dob");
        form_dob->setGeometry(QRect(211, 285, 221, 31));
        form_cpass = new QLineEdit(signup);
        form_cpass->setObjectName("form_cpass");
        form_cpass->setGeometry(QRect(211, 395, 221, 31));
        formemail = new QLineEdit(signup);
        formemail->setObjectName("formemail");
        formemail->setGeometry(QRect(211, 230, 221, 31));
        form_pass = new QLineEdit(signup);
        form_pass->setObjectName("form_pass");
        form_pass->setGeometry(QRect(211, 340, 221, 31));

        retranslateUi(signup);

        QMetaObject::connectSlotsByName(signup);
    } // setupUi

    void retranslateUi(QDialog *signup)
    {
        signup->setWindowTitle(QCoreApplication::translate("signup", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("signup", "Registration Form", nullptr));
        label_2->setText(QCoreApplication::translate("signup", "Name:", nullptr));
        label_3->setText(QCoreApplication::translate("signup", "Phone no:", nullptr));
        label_4->setText(QCoreApplication::translate("signup", "Email:", nullptr));
        label_5->setText(QCoreApplication::translate("signup", "Date Of Birth:", nullptr));
        label_6->setText(QCoreApplication::translate("signup", "Password:", nullptr));
        label_7->setText(QCoreApplication::translate("signup", "Confirm Password:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class signup: public Ui_signup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUP_H
