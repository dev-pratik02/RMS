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
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_forgotpass
{
public:
    QLineEdit *line_phone;
    QLabel *label;
    QLineEdit *line_name;
    QLineEdit *line_confirmpass;
    QLineEdit *line_email;
    QLineEdit *line_newpass;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QPushButton *btn_confirm;
    QDateEdit *date_dob;

    void setupUi(QDialog *forgotpass)
    {
        if (forgotpass->objectName().isEmpty())
            forgotpass->setObjectName("forgotpass");
        forgotpass->resize(800, 600);
        line_phone = new QLineEdit(forgotpass);
        line_phone->setObjectName("line_phone");
        line_phone->setGeometry(QRect(270, 214, 221, 31));
        label = new QLabel(forgotpass);
        label->setObjectName("label");
        label->setGeometry(QRect(290, 40, 221, 24));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(16);
        font.setBold(true);
        label->setFont(font);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        line_name = new QLineEdit(forgotpass);
        line_name->setObjectName("line_name");
        line_name->setGeometry(QRect(270, 160, 221, 31));
        line_confirmpass = new QLineEdit(forgotpass);
        line_confirmpass->setObjectName("line_confirmpass");
        line_confirmpass->setGeometry(QRect(270, 434, 221, 31));
        line_email = new QLineEdit(forgotpass);
        line_email->setObjectName("line_email");
        line_email->setGeometry(QRect(270, 269, 221, 31));
        line_newpass = new QLineEdit(forgotpass);
        line_newpass->setObjectName("line_newpass");
        line_newpass->setGeometry(QRect(270, 379, 221, 31));
        layoutWidget = new QWidget(forgotpass);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(121, 151, 138, 321));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial")});
        font1.setPointSize(12);
        label_2->setFont(font1);

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName("label_3");
        label_3->setFont(font1);

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName("label_4");
        label_4->setFont(font1);

        verticalLayout->addWidget(label_4);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName("label_5");
        label_5->setFont(font1);

        verticalLayout->addWidget(label_5);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName("label_6");
        label_6->setFont(font1);

        verticalLayout->addWidget(label_6);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName("label_7");
        label_7->setFont(font1);

        verticalLayout->addWidget(label_7);

        btn_confirm = new QPushButton(forgotpass);
        btn_confirm->setObjectName("btn_confirm");
        btn_confirm->setGeometry(QRect(410, 510, 80, 24));
        btn_confirm->setFont(font1);
        date_dob = new QDateEdit(forgotpass);
        date_dob->setObjectName("date_dob");
        date_dob->setGeometry(QRect(270, 324, 221, 31));

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
        btn_confirm->setText(QCoreApplication::translate("forgotpass", "Confirm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class forgotpass: public Ui_forgotpass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORGOTPASS_H
