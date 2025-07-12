/********************************************************************************
** Form generated from reading UI file 'forgotpass.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORGOTPASS_H
#define UI_FORGOTPASS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_forgotpass
{
public:
    QLineEdit *form_phone;
    QLabel *label;
    QLineEdit *form_name;
    QLineEdit *form_dob;
    QLineEdit *form_cpass;
    QLineEdit *formemail;
    QLineEdit *form_pass;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;

    void setupUi(QDialog *forgotpass)
    {
        if (forgotpass->objectName().isEmpty())
            forgotpass->setObjectName("forgotpass");
        forgotpass->resize(800, 600);
        form_phone = new QLineEdit(forgotpass);
        form_phone->setObjectName("form_phone");
        form_phone->setGeometry(QRect(270, 214, 221, 31));
        label = new QLabel(forgotpass);
        label->setObjectName("label");
        label->setGeometry(QRect(290, 40, 221, 24));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(16);
        font.setBold(true);
        label->setFont(font);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        form_name = new QLineEdit(forgotpass);
        form_name->setObjectName("form_name");
        form_name->setGeometry(QRect(270, 160, 221, 31));
        form_dob = new QLineEdit(forgotpass);
        form_dob->setObjectName("form_dob");
        form_dob->setGeometry(QRect(270, 324, 221, 31));
        form_cpass = new QLineEdit(forgotpass);
        form_cpass->setObjectName("form_cpass");
        form_cpass->setGeometry(QRect(270, 434, 221, 31));
        formemail = new QLineEdit(forgotpass);
        formemail->setObjectName("formemail");
        formemail->setGeometry(QRect(270, 269, 221, 31));
        form_pass = new QLineEdit(forgotpass);
        form_pass->setObjectName("form_pass");
        form_pass->setGeometry(QRect(270, 379, 221, 31));
        widget = new QWidget(forgotpass);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(121, 151, 138, 321));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial")});
        font1.setPointSize(12);
        label_2->setFont(font1);

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(widget);
        label_3->setObjectName("label_3");
        label_3->setFont(font1);

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(widget);
        label_4->setObjectName("label_4");
        label_4->setFont(font1);

        verticalLayout->addWidget(label_4);

        label_5 = new QLabel(widget);
        label_5->setObjectName("label_5");
        label_5->setFont(font1);

        verticalLayout->addWidget(label_5);

        label_6 = new QLabel(widget);
        label_6->setObjectName("label_6");
        label_6->setFont(font1);

        verticalLayout->addWidget(label_6);

        label_7 = new QLabel(widget);
        label_7->setObjectName("label_7");
        label_7->setFont(font1);

        verticalLayout->addWidget(label_7);


        retranslateUi(forgotpass);

        QMetaObject::connectSlotsByName(forgotpass);
    } // setupUi

    void retranslateUi(QDialog *forgotpass)
    {
        forgotpass->setWindowTitle(QCoreApplication::translate("forgotpass", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("forgotpass", "Reset Password Form", nullptr));
        label_2->setText(QCoreApplication::translate("forgotpass", "Name:", nullptr));
        label_3->setText(QCoreApplication::translate("forgotpass", "Phone no:", nullptr));
        label_4->setText(QCoreApplication::translate("forgotpass", "Email:", nullptr));
        label_5->setText(QCoreApplication::translate("forgotpass", "Date Of Birth:", nullptr));
        label_6->setText(QCoreApplication::translate("forgotpass", "New Password:", nullptr));
        label_7->setText(QCoreApplication::translate("forgotpass", "Confirm Password:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class forgotpass: public Ui_forgotpass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORGOTPASS_H
