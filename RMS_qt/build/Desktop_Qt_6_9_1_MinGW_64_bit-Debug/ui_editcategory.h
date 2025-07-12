/********************************************************************************
** Form generated from reading UI file 'editcategory.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITCATEGORY_H
#define UI_EDITCATEGORY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_editcategory
{
public:
    QLabel *ADDMENUITEM;
    QPushButton *btn_edit;
    QPlainTextEdit *category_description;
    QLabel *PRICE;
    QLabel *DESCRIPTION;
    QLineEdit *category_name;
    QLabel *label;
    QPushButton *btn_reset;
    QLabel *ITEMNAME;
    QLineEdit *item_no;
    QLineEdit *category_id;

    void setupUi(QDialog *editcategory)
    {
        if (editcategory->objectName().isEmpty())
            editcategory->setObjectName("editcategory");
        editcategory->resize(800, 600);
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(12);
        editcategory->setFont(font);
        ADDMENUITEM = new QLabel(editcategory);
        ADDMENUITEM->setObjectName("ADDMENUITEM");
        ADDMENUITEM->setGeometry(QRect(268, 20, 223, 24));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial")});
        font1.setPointSize(16);
        font1.setBold(true);
        font1.setItalic(false);
        ADDMENUITEM->setFont(font1);
        ADDMENUITEM->setAlignment(Qt::AlignmentFlag::AlignCenter);
        btn_edit = new QPushButton(editcategory);
        btn_edit->setObjectName("btn_edit");
        btn_edit->setGeometry(QRect(508, 550, 93, 29));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Arial")});
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setItalic(false);
        btn_edit->setFont(font2);
        category_description = new QPlainTextEdit(editcategory);
        category_description->setObjectName("category_description");
        category_description->setGeometry(QRect(69, 280, 661, 221));
        PRICE = new QLabel(editcategory);
        PRICE->setObjectName("PRICE");
        PRICE->setGeometry(QRect(70, 190, 133, 18));
        PRICE->setFont(font);
        DESCRIPTION = new QLabel(editcategory);
        DESCRIPTION->setObjectName("DESCRIPTION");
        DESCRIPTION->setGeometry(QRect(69, 255, 114, 18));
        DESCRIPTION->setFont(font);
        category_name = new QLineEdit(editcategory);
        category_name->setObjectName("category_name");
        category_name->setGeometry(QRect(70, 85, 661, 22));
        label = new QLabel(editcategory);
        label->setObjectName("label");
        label->setGeometry(QRect(70, 60, 144, 18));
        label->setFont(font);
        btn_reset = new QPushButton(editcategory);
        btn_reset->setObjectName("btn_reset");
        btn_reset->setGeometry(QRect(208, 550, 93, 29));
        btn_reset->setFont(font2);
        ITEMNAME = new QLabel(editcategory);
        ITEMNAME->setObjectName("ITEMNAME");
        ITEMNAME->setGeometry(QRect(70, 125, 113, 18));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Arial")});
        font3.setPointSize(12);
        font3.setBold(false);
        font3.setItalic(false);
        ITEMNAME->setFont(font3);
        item_no = new QLineEdit(editcategory);
        item_no->setObjectName("item_no");
        item_no->setGeometry(QRect(70, 215, 661, 22));
        category_id = new QLineEdit(editcategory);
        category_id->setObjectName("category_id");
        category_id->setGeometry(QRect(70, 150, 661, 22));

        retranslateUi(editcategory);

        QMetaObject::connectSlotsByName(editcategory);
    } // setupUi

    void retranslateUi(QDialog *editcategory)
    {
        editcategory->setWindowTitle(QCoreApplication::translate("editcategory", "Dialog", nullptr));
        ADDMENUITEM->setText(QCoreApplication::translate("editcategory", " EDIT CATEGORY", nullptr));
        btn_edit->setText(QCoreApplication::translate("editcategory", "EDIT", nullptr));
        category_description->setPlainText(QString());
        PRICE->setText(QCoreApplication::translate("editcategory", "DISPLAY ORDER:", nullptr));
        DESCRIPTION->setText(QCoreApplication::translate("editcategory", "DESCRIPTION:", nullptr));
        label->setText(QCoreApplication::translate("editcategory", "CATEGORY NAME:", nullptr));
        btn_reset->setText(QCoreApplication::translate("editcategory", "RESET", nullptr));
        ITEMNAME->setText(QCoreApplication::translate("editcategory", "CATEGORY ID:", nullptr));
        item_no->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class editcategory: public Ui_editcategory {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITCATEGORY_H
