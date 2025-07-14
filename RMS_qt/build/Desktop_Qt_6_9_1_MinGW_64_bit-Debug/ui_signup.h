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
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_signup
{
public:
    QLabel *label;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *line_phone;
    QLineEdit *line_name;
    QLineEdit *line_confirmpass;
    QLineEdit *line_email;
    QLineEdit *line_password;
    QPushButton *btn_confirm;
    QDateEdit *date_dob;

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
        layoutWidget = new QWidget(signup);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(61, 111, 141, 321));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial")});
        font1.setPointSize(12);
        label_2->setFont(font1);

        verticalLayout_2->addWidget(label_2);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName("label_3");
        label_3->setFont(font1);

        verticalLayout_2->addWidget(label_3);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName("label_4");
        label_4->setFont(font1);

        verticalLayout_2->addWidget(label_4);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName("label_5");
        label_5->setFont(font1);

        verticalLayout_2->addWidget(label_5);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName("label_6");
        label_6->setFont(font1);

        verticalLayout_2->addWidget(label_6);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName("label_7");
        label_7->setFont(font1);

        verticalLayout_2->addWidget(label_7);

        line_phone = new QLineEdit(signup);
        line_phone->setObjectName("line_phone");
        line_phone->setGeometry(QRect(211, 175, 221, 31));
        line_name = new QLineEdit(signup);
        line_name->setObjectName("line_name");
        line_name->setGeometry(QRect(210, 123, 221, 31));
        line_confirmpass = new QLineEdit(signup);
        line_confirmpass->setObjectName("line_confirmpass");
        line_confirmpass->setGeometry(QRect(211, 395, 221, 31));
        line_email = new QLineEdit(signup);
        line_email->setObjectName("line_email");
        line_email->setGeometry(QRect(211, 230, 221, 31));
        line_password = new QLineEdit(signup);
        line_password->setObjectName("line_password");
        line_password->setGeometry(QRect(211, 340, 221, 31));
        btn_confirm = new QPushButton(signup);
        btn_confirm->setObjectName("btn_confirm");
        btn_confirm->setGeometry(QRect(350, 470, 80, 24));
        btn_confirm->setFont(font1);
        date_dob = new QDateEdit(signup);
        date_dob->setObjectName("date_dob");
        date_dob->setGeometry(QRect(210, 284, 221, 31));

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
        btn_confirm->setText(QCoreApplication::translate("signup", "Confirm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class signup: public Ui_signup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUP_H
