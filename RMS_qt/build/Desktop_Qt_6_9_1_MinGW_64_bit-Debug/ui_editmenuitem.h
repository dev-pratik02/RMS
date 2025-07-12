/********************************************************************************
** Form generated from reading UI file 'editmenuitem.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITMENUITEM_H
#define UI_EDITMENUITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_editmenuitem
{
public:
    QPushButton *btn_reset;
    QPushButton *btn_save;
    QLabel *EDITMENUITEM;
    QWidget *widget;
    QFormLayout *formLayout;
    QLabel *item_id_2;
    QLabel *ITEMNAME;
    QLineEdit *item_id;
    QLineEdit *item_name;
    QLabel *PRICE;
    QLineEdit *item_price;
    QLabel *DESCRIPTION;
    QLineEdit *item_description;
    QLineEdit *item_category;
    QLabel *PRICE_2;
    QLabel *label_2;
    QPushButton *image_upload;
    QLabel *image_preview;

    void setupUi(QDialog *editmenuitem)
    {
        if (editmenuitem->objectName().isEmpty())
            editmenuitem->setObjectName("editmenuitem");
        editmenuitem->resize(800, 600);
        btn_reset = new QPushButton(editmenuitem);
        btn_reset->setObjectName("btn_reset");
        btn_reset->setGeometry(QRect(210, 550, 93, 29));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(12);
        font.setBold(true);
        font.setItalic(false);
        btn_reset->setFont(font);
        btn_save = new QPushButton(editmenuitem);
        btn_save->setObjectName("btn_save");
        btn_save->setGeometry(QRect(510, 550, 93, 29));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial")});
        font1.setPointSize(11);
        font1.setBold(true);
        font1.setItalic(false);
        btn_save->setFont(font1);
        EDITMENUITEM = new QLabel(editmenuitem);
        EDITMENUITEM->setObjectName("EDITMENUITEM");
        EDITMENUITEM->setGeometry(QRect(290, 20, 241, 41));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Arial")});
        font2.setPointSize(16);
        font2.setBold(true);
        font2.setItalic(false);
        EDITMENUITEM->setFont(font2);
        EDITMENUITEM->setAlignment(Qt::AlignmentFlag::AlignCenter);
        widget = new QWidget(editmenuitem);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(80, 110, 631, 381));
        formLayout = new QFormLayout(widget);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(0, 0, 0, 0);
        item_id_2 = new QLabel(widget);
        item_id_2->setObjectName("item_id_2");
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Arial")});
        font3.setPointSize(12);
        item_id_2->setFont(font3);

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, item_id_2);

        ITEMNAME = new QLabel(widget);
        ITEMNAME->setObjectName("ITEMNAME");
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Arial")});
        font4.setPointSize(12);
        font4.setBold(false);
        font4.setItalic(false);
        ITEMNAME->setFont(font4);

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, ITEMNAME);

        item_id = new QLineEdit(widget);
        item_id->setObjectName("item_id");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, item_id);

        item_name = new QLineEdit(widget);
        item_name->setObjectName("item_name");

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, item_name);

        PRICE = new QLabel(widget);
        PRICE->setObjectName("PRICE");
        PRICE->setFont(font3);

        formLayout->setWidget(8, QFormLayout::ItemRole::LabelRole, PRICE);

        item_price = new QLineEdit(widget);
        item_price->setObjectName("item_price");

        formLayout->setWidget(8, QFormLayout::ItemRole::FieldRole, item_price);

        DESCRIPTION = new QLabel(widget);
        DESCRIPTION->setObjectName("DESCRIPTION");
        DESCRIPTION->setFont(font3);

        formLayout->setWidget(10, QFormLayout::ItemRole::LabelRole, DESCRIPTION);

        item_description = new QLineEdit(widget);
        item_description->setObjectName("item_description");

        formLayout->setWidget(10, QFormLayout::ItemRole::FieldRole, item_description);

        item_category = new QLineEdit(widget);
        item_category->setObjectName("item_category");

        formLayout->setWidget(7, QFormLayout::ItemRole::FieldRole, item_category);

        PRICE_2 = new QLabel(widget);
        PRICE_2->setObjectName("PRICE_2");
        PRICE_2->setFont(font3);

        formLayout->setWidget(7, QFormLayout::ItemRole::LabelRole, PRICE_2);

        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");
        label_2->setFont(font3);

        formLayout->setWidget(4, QFormLayout::ItemRole::LabelRole, label_2);

        image_upload = new QPushButton(widget);
        image_upload->setObjectName("image_upload");

        formLayout->setWidget(5, QFormLayout::ItemRole::FieldRole, image_upload);

        image_preview = new QLabel(widget);
        image_preview->setObjectName("image_preview");

        formLayout->setWidget(4, QFormLayout::ItemRole::FieldRole, image_preview);


        retranslateUi(editmenuitem);

        QMetaObject::connectSlotsByName(editmenuitem);
    } // setupUi

    void retranslateUi(QDialog *editmenuitem)
    {
        editmenuitem->setWindowTitle(QCoreApplication::translate("editmenuitem", "Dialog", nullptr));
        btn_reset->setText(QCoreApplication::translate("editmenuitem", "RESET", nullptr));
        btn_save->setText(QCoreApplication::translate("editmenuitem", "SAVE", nullptr));
        EDITMENUITEM->setText(QCoreApplication::translate("editmenuitem", "EDIT MENU ITEM", nullptr));
        item_id_2->setText(QCoreApplication::translate("editmenuitem", "ITEM ID:", nullptr));
        ITEMNAME->setText(QCoreApplication::translate("editmenuitem", "ITEM NAME:", nullptr));
        PRICE->setText(QCoreApplication::translate("editmenuitem", "PRICE:", nullptr));
        item_price->setText(QString());
        DESCRIPTION->setText(QCoreApplication::translate("editmenuitem", "DESCRIPTION:", nullptr));
        item_description->setText(QString());
        item_category->setText(QString());
        PRICE_2->setText(QCoreApplication::translate("editmenuitem", "CATEGORY:", nullptr));
        label_2->setText(QCoreApplication::translate("editmenuitem", "ITEM PHOTO:", nullptr));
        image_upload->setText(QCoreApplication::translate("editmenuitem", "Upload image", nullptr));
        image_preview->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class editmenuitem: public Ui_editmenuitem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITMENUITEM_H
