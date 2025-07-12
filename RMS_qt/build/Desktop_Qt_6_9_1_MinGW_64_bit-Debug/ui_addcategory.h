/********************************************************************************
** Form generated from reading UI file 'addcategory.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDCATEGORY_H
#define UI_ADDCATEGORY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_addcategory
{
public:
    QLabel *DESCRIPTION;
    QLabel *ITEMNAME;
    QLineEdit *category_name;
    QLabel *label;
    QPushButton *btn_reset;
    QLineEdit *category_id;
    QPushButton *btn_add;
    QPlainTextEdit *category_description;
    QLabel *ADDMENUITEM;
    QLabel *PRICE;
    QLineEdit *item_no;

    void setupUi(QDialog *addcategory)
    {
        if (addcategory->objectName().isEmpty())
            addcategory->setObjectName("addcategory");
        addcategory->resize(800, 600);
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(12);
        addcategory->setFont(font);
        DESCRIPTION = new QLabel(addcategory);
        DESCRIPTION->setObjectName("DESCRIPTION");
        DESCRIPTION->setGeometry(QRect(79, 250, 114, 18));
        DESCRIPTION->setFont(font);
        ITEMNAME = new QLabel(addcategory);
        ITEMNAME->setObjectName("ITEMNAME");
        ITEMNAME->setGeometry(QRect(80, 125, 113, 18));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial")});
        font1.setPointSize(12);
        font1.setBold(false);
        font1.setItalic(false);
        ITEMNAME->setFont(font1);
        category_name = new QLineEdit(addcategory);
        category_name->setObjectName("category_name");
        category_name->setGeometry(QRect(80, 85, 661, 22));
        label = new QLabel(addcategory);
        label->setObjectName("label");
        label->setGeometry(QRect(80, 60, 144, 18));
        label->setFont(font);
        btn_reset = new QPushButton(addcategory);
        btn_reset->setObjectName("btn_reset");
        btn_reset->setGeometry(QRect(218, 550, 93, 29));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Arial")});
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setItalic(false);
        btn_reset->setFont(font2);
        category_id = new QLineEdit(addcategory);
        category_id->setObjectName("category_id");
        category_id->setGeometry(QRect(80, 150, 661, 22));
        btn_add = new QPushButton(addcategory);
        btn_add->setObjectName("btn_add");
        btn_add->setGeometry(QRect(518, 550, 93, 29));
        btn_add->setFont(font2);
        category_description = new QPlainTextEdit(addcategory);
        category_description->setObjectName("category_description");
        category_description->setGeometry(QRect(79, 275, 661, 241));
        ADDMENUITEM = new QLabel(addcategory);
        ADDMENUITEM->setObjectName("ADDMENUITEM");
        ADDMENUITEM->setGeometry(QRect(278, 20, 223, 24));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Arial")});
        font3.setPointSize(16);
        font3.setBold(true);
        font3.setItalic(false);
        ADDMENUITEM->setFont(font3);
        ADDMENUITEM->setAlignment(Qt::AlignmentFlag::AlignCenter);
        PRICE = new QLabel(addcategory);
        PRICE->setObjectName("PRICE");
        PRICE->setGeometry(QRect(80, 185, 133, 18));
        PRICE->setFont(font);
        item_no = new QLineEdit(addcategory);
        item_no->setObjectName("item_no");
        item_no->setGeometry(QRect(80, 210, 661, 22));

        retranslateUi(addcategory);

        QMetaObject::connectSlotsByName(addcategory);
    } // setupUi

    void retranslateUi(QDialog *addcategory)
    {
        addcategory->setWindowTitle(QCoreApplication::translate("addcategory", "Dialog", nullptr));
        DESCRIPTION->setText(QCoreApplication::translate("addcategory", "DESCRIPTION:", nullptr));
        ITEMNAME->setText(QCoreApplication::translate("addcategory", "CATEGORY ID:", nullptr));
        label->setText(QCoreApplication::translate("addcategory", "CATEGORY NAME:", nullptr));
        btn_reset->setText(QCoreApplication::translate("addcategory", "RESET", nullptr));
        btn_add->setText(QCoreApplication::translate("addcategory", "ADD", nullptr));
        category_description->setPlainText(QString());
        ADDMENUITEM->setText(QCoreApplication::translate("addcategory", "ADD NEW CATEGORY", nullptr));
        PRICE->setText(QCoreApplication::translate("addcategory", "DISPLAY ORDER:", nullptr));
        item_no->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class addcategory: public Ui_addcategory {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDCATEGORY_H
