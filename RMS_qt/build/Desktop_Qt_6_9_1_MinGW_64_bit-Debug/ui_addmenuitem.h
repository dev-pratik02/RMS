/********************************************************************************
** Form generated from reading UI file 'addmenuitem.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDMENUITEM_H
#define UI_ADDMENUITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_addmenuitem
{
public:
    QLabel *ADDMENUITEM;
    QPushButton *btn_save;
    QPushButton *btn_reset;
    QWidget *widget;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *ITEMNAME;
    QLabel *PRICE_2;
    QLabel *PRICE;
    QLabel *DESCRIPTION;
    QLineEdit *item_id;
    QLineEdit *item_name;
    QLineEdit *item_category;
    QLineEdit *item_price;
    QPlainTextEdit *item_description;
    QLabel *label_2;
    QLabel *image_preview;
    QPushButton *image_upload;

    void setupUi(QDialog *addmenuitem)
    {
        if (addmenuitem->objectName().isEmpty())
            addmenuitem->setObjectName("addmenuitem");
        addmenuitem->resize(800, 600);
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        addmenuitem->setFont(font);
        ADDMENUITEM = new QLabel(addmenuitem);
        ADDMENUITEM->setObjectName("ADDMENUITEM");
        ADDMENUITEM->setGeometry(QRect(280, 10, 241, 41));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial")});
        font1.setPointSize(16);
        font1.setBold(true);
        font1.setItalic(false);
        ADDMENUITEM->setFont(font1);
        ADDMENUITEM->setAlignment(Qt::AlignmentFlag::AlignCenter);
        btn_save = new QPushButton(addmenuitem);
        btn_save->setObjectName("btn_save");
        btn_save->setGeometry(QRect(520, 560, 93, 29));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Arial")});
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setItalic(false);
        btn_save->setFont(font2);
        btn_reset = new QPushButton(addmenuitem);
        btn_reset->setObjectName("btn_reset");
        btn_reset->setGeometry(QRect(220, 560, 93, 29));
        btn_reset->setFont(font2);
        widget = new QWidget(addmenuitem);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(110, 80, 611, 426));
        formLayout = new QFormLayout(widget);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName("label");
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Arial")});
        font3.setPointSize(12);
        label->setFont(font3);

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label);

        ITEMNAME = new QLabel(widget);
        ITEMNAME->setObjectName("ITEMNAME");
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Arial")});
        font4.setPointSize(12);
        font4.setBold(false);
        font4.setItalic(false);
        ITEMNAME->setFont(font4);

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, ITEMNAME);

        PRICE_2 = new QLabel(widget);
        PRICE_2->setObjectName("PRICE_2");
        PRICE_2->setFont(font3);

        formLayout->setWidget(6, QFormLayout::ItemRole::LabelRole, PRICE_2);

        PRICE = new QLabel(widget);
        PRICE->setObjectName("PRICE");
        PRICE->setFont(font3);

        formLayout->setWidget(8, QFormLayout::ItemRole::LabelRole, PRICE);

        DESCRIPTION = new QLabel(widget);
        DESCRIPTION->setObjectName("DESCRIPTION");
        DESCRIPTION->setFont(font3);

        formLayout->setWidget(10, QFormLayout::ItemRole::LabelRole, DESCRIPTION);

        item_id = new QLineEdit(widget);
        item_id->setObjectName("item_id");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, item_id);

        item_name = new QLineEdit(widget);
        item_name->setObjectName("item_name");

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, item_name);

        item_category = new QLineEdit(widget);
        item_category->setObjectName("item_category");

        formLayout->setWidget(6, QFormLayout::ItemRole::FieldRole, item_category);

        item_price = new QLineEdit(widget);
        item_price->setObjectName("item_price");

        formLayout->setWidget(8, QFormLayout::ItemRole::FieldRole, item_price);

        item_description = new QPlainTextEdit(widget);
        item_description->setObjectName("item_description");

        formLayout->setWidget(10, QFormLayout::ItemRole::FieldRole, item_description);

        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");
        label_2->setFont(font3);

        formLayout->setWidget(4, QFormLayout::ItemRole::LabelRole, label_2);

        image_preview = new QLabel(widget);
        image_preview->setObjectName("image_preview");

        formLayout->setWidget(4, QFormLayout::ItemRole::FieldRole, image_preview);

        image_upload = new QPushButton(widget);
        image_upload->setObjectName("image_upload");

        formLayout->setWidget(5, QFormLayout::ItemRole::FieldRole, image_upload);


        retranslateUi(addmenuitem);

        QMetaObject::connectSlotsByName(addmenuitem);
    } // setupUi

    void retranslateUi(QDialog *addmenuitem)
    {
        addmenuitem->setWindowTitle(QCoreApplication::translate("addmenuitem", "Dialog", nullptr));
        ADDMENUITEM->setText(QCoreApplication::translate("addmenuitem", "ADD MENU ITEM", nullptr));
        btn_save->setText(QCoreApplication::translate("addmenuitem", "ADD", nullptr));
        btn_reset->setText(QCoreApplication::translate("addmenuitem", "RESET", nullptr));
        label->setText(QCoreApplication::translate("addmenuitem", "ITEM ID:", nullptr));
        ITEMNAME->setText(QCoreApplication::translate("addmenuitem", "ITEM NAME:", nullptr));
        PRICE_2->setText(QCoreApplication::translate("addmenuitem", "Category:", nullptr));
        PRICE->setText(QCoreApplication::translate("addmenuitem", "PRICE:", nullptr));
        DESCRIPTION->setText(QCoreApplication::translate("addmenuitem", "DESCRIPTION:", nullptr));
        item_category->setText(QString());
        item_price->setText(QString());
        item_description->setPlainText(QString());
        label_2->setText(QCoreApplication::translate("addmenuitem", "ITEM PHOTO:", nullptr));
        image_preview->setText(QString());
        image_upload->setText(QCoreApplication::translate("addmenuitem", "Upload image", nullptr));
    } // retranslateUi

};

namespace Ui {
    class addmenuitem: public Ui_addmenuitem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDMENUITEM_H
