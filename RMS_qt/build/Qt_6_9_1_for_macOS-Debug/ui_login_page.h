/********************************************************************************
** Form generated from reading UI file 'login_page.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_PAGE_H
#define UI_LOGIN_PAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_login_page
{
public:
    QLabel *welcomeback;
    QLabel *pleaseenterdetails;
    QLabel *label_2;
    QLineEdit *input_userid;
    QLabel *label_3;
    QLineEdit *input_password;
    QPushButton *btn_login;
    QLabel *label;
    QLabel *label_4;
    QLabel *label_pic;
    QLabel *label_pic1;

    void setupUi(QDialog *login_page)
    {
        if (login_page->objectName().isEmpty())
            login_page->setObjectName("login_page");
        login_page->resize(800, 600);
        welcomeback = new QLabel(login_page);
        welcomeback->setObjectName("welcomeback");
        welcomeback->setGeometry(QRect(120, 140, 231, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(16);
        welcomeback->setFont(font);
        pleaseenterdetails = new QLabel(login_page);
        pleaseenterdetails->setObjectName("pleaseenterdetails");
        pleaseenterdetails->setGeometry(QRect(130, 190, 181, 20));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial")});
        pleaseenterdetails->setFont(font1);
        label_2 = new QLabel(login_page);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(110, 250, 81, 21));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Arial")});
        font2.setPointSize(12);
        label_2->setFont(font2);
        input_userid = new QLineEdit(login_page);
        input_userid->setObjectName("input_userid");
        input_userid->setGeometry(QRect(110, 290, 211, 31));
        label_3 = new QLabel(login_page);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(110, 360, 101, 20));
        label_3->setFont(font2);
        input_password = new QLineEdit(login_page);
        input_password->setObjectName("input_password");
        input_password->setGeometry(QRect(110, 400, 211, 31));
        btn_login = new QPushButton(login_page);
        btn_login->setObjectName("btn_login");
        btn_login->setGeometry(QRect(150, 460, 131, 51));
        btn_login->setStyleSheet(QString::fromUtf8("background-color: red;\n"
"color: white;\n"
""));
        label = new QLabel(login_page);
        label->setObjectName("label");
        label->setGeometry(QRect(170, 530, 121, 31));
        label->setFont(font2);
        label_4 = new QLabel(login_page);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(190, 570, 63, 20));
        label_pic = new QLabel(login_page);
        label_pic->setObjectName("label_pic");
        label_pic->setGeometry(QRect(372, -1, 421, 571));
        label_pic1 = new QLabel(login_page);
        label_pic1->setObjectName("label_pic1");
        label_pic1->setGeometry(QRect(132, 20, 161, 101));

        retranslateUi(login_page);

        QMetaObject::connectSlotsByName(login_page);
    } // setupUi

    void retranslateUi(QDialog *login_page)
    {
        login_page->setWindowTitle(QCoreApplication::translate("login_page", "Login ", nullptr));
        welcomeback->setText(QCoreApplication::translate("login_page", "WELCOME BACK", nullptr));
        pleaseenterdetails->setText(QCoreApplication::translate("login_page", "Please enter your details!!!", nullptr));
        label_2->setText(QCoreApplication::translate("login_page", "User id:", nullptr));
        label_3->setText(QCoreApplication::translate("login_page", "Password:", nullptr));
        btn_login->setText(QCoreApplication::translate("login_page", "Login", nullptr));
        label->setText(QCoreApplication::translate("login_page", "Designed by:", nullptr));
        label_4->setText(QCoreApplication::translate("login_page", "----------", nullptr));
        label_pic->setText(QString());
        label_pic1->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class login_page: public Ui_login_page {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_PAGE_H
