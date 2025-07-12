/********************************************************************************
** Form generated from reading UI file 'menuiteminfo.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENUITEMINFO_H
#define UI_MENUITEMINFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_menuiteminfo
{
public:
    QLabel *menuiteminfo_2;
    QLabel *ITEMNAME;
    QLineEdit *lineeditone;
    QLabel *itemid;
    QLineEdit *lineedittwo;
    QLabel *price;
    QLineEdit *lineeditthree;
    QLabel *preparetime;
    QLineEdit *lineeditfour;
    QLabel *vegnonveg;
    QLineEdit *lineeditfive;
    QLabel *description;
    QPlainTextEdit *plaintexteditone;
    QLabel *ingredients;
    QPlainTextEdit *plaintextedittwo;
    QPushButton *Save;
    QPushButton *CANCEL;

    void setupUi(QDialog *menuiteminfo)
    {
        if (menuiteminfo->objectName().isEmpty())
            menuiteminfo->setObjectName("menuiteminfo");
        menuiteminfo->resize(800, 600);
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        menuiteminfo->setFont(font);
        menuiteminfo_2 = new QLabel(menuiteminfo);
        menuiteminfo_2->setObjectName("menuiteminfo_2");
        menuiteminfo_2->setGeometry(QRect(270, -10, 281, 51));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial")});
        font1.setPointSize(16);
        font1.setBold(true);
        font1.setItalic(false);
        menuiteminfo_2->setFont(font1);
        menuiteminfo_2->setAlignment(Qt::AlignmentFlag::AlignCenter);
        ITEMNAME = new QLabel(menuiteminfo);
        ITEMNAME->setObjectName("ITEMNAME");
        ITEMNAME->setGeometry(QRect(40, 40, 111, 20));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Arial")});
        font2.setPointSize(12);
        ITEMNAME->setFont(font2);
        lineeditone = new QLineEdit(menuiteminfo);
        lineeditone->setObjectName("lineeditone");
        lineeditone->setGeometry(QRect(40, 70, 701, 26));
        itemid = new QLabel(menuiteminfo);
        itemid->setObjectName("itemid");
        itemid->setGeometry(QRect(40, 110, 101, 20));
        itemid->setFont(font2);
        lineedittwo = new QLineEdit(menuiteminfo);
        lineedittwo->setObjectName("lineedittwo");
        lineedittwo->setGeometry(QRect(40, 150, 701, 26));
        price = new QLabel(menuiteminfo);
        price->setObjectName("price");
        price->setGeometry(QRect(40, 190, 101, 20));
        price->setFont(font2);
        lineeditthree = new QLineEdit(menuiteminfo);
        lineeditthree->setObjectName("lineeditthree");
        lineeditthree->setGeometry(QRect(40, 220, 701, 26));
        preparetime = new QLabel(menuiteminfo);
        preparetime->setObjectName("preparetime");
        preparetime->setGeometry(QRect(40, 260, 161, 20));
        preparetime->setFont(font2);
        lineeditfour = new QLineEdit(menuiteminfo);
        lineeditfour->setObjectName("lineeditfour");
        lineeditfour->setGeometry(QRect(40, 300, 701, 26));
        vegnonveg = new QLabel(menuiteminfo);
        vegnonveg->setObjectName("vegnonveg");
        vegnonveg->setGeometry(QRect(40, 330, 211, 31));
        vegnonveg->setFont(font2);
        lineeditfive = new QLineEdit(menuiteminfo);
        lineeditfive->setObjectName("lineeditfive");
        lineeditfive->setGeometry(QRect(40, 370, 701, 26));
        description = new QLabel(menuiteminfo);
        description->setObjectName("description");
        description->setGeometry(QRect(40, 400, 151, 31));
        description->setFont(font2);
        plaintexteditone = new QPlainTextEdit(menuiteminfo);
        plaintexteditone->setObjectName("plaintexteditone");
        plaintexteditone->setGeometry(QRect(40, 440, 711, 31));
        ingredients = new QLabel(menuiteminfo);
        ingredients->setObjectName("ingredients");
        ingredients->setGeometry(QRect(40, 480, 131, 31));
        ingredients->setFont(font2);
        plaintextedittwo = new QPlainTextEdit(menuiteminfo);
        plaintextedittwo->setObjectName("plaintextedittwo");
        plaintextedittwo->setGeometry(QRect(40, 510, 711, 31));
        Save = new QPushButton(menuiteminfo);
        Save->setObjectName("Save");
        Save->setGeometry(QRect(490, 560, 93, 29));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Arial")});
        font3.setPointSize(10);
        font3.setBold(true);
        font3.setItalic(false);
        Save->setFont(font3);
        CANCEL = new QPushButton(menuiteminfo);
        CANCEL->setObjectName("CANCEL");
        CANCEL->setGeometry(QRect(160, 560, 93, 29));
        CANCEL->setFont(font3);

        retranslateUi(menuiteminfo);

        QMetaObject::connectSlotsByName(menuiteminfo);
    } // setupUi

    void retranslateUi(QDialog *menuiteminfo)
    {
        menuiteminfo->setWindowTitle(QCoreApplication::translate("menuiteminfo", "Dialog", nullptr));
        menuiteminfo_2->setText(QCoreApplication::translate("menuiteminfo", "MENU ITEM INFO", nullptr));
        ITEMNAME->setText(QCoreApplication::translate("menuiteminfo", "Item Name:", nullptr));
        itemid->setText(QCoreApplication::translate("menuiteminfo", "Item Id:", nullptr));
        price->setText(QCoreApplication::translate("menuiteminfo", "Price:", nullptr));
        preparetime->setText(QCoreApplication::translate("menuiteminfo", "Preparation Time:", nullptr));
        vegnonveg->setText(QCoreApplication::translate("menuiteminfo", "Veg/Non-Veg:", nullptr));
        description->setText(QCoreApplication::translate("menuiteminfo", "Description:", nullptr));
        ingredients->setText(QCoreApplication::translate("menuiteminfo", "Ingredients:", nullptr));
        Save->setText(QCoreApplication::translate("menuiteminfo", "SAVE", nullptr));
        CANCEL->setText(QCoreApplication::translate("menuiteminfo", "CANCEL", nullptr));
    } // retranslateUi

};

namespace Ui {
    class menuiteminfo: public Ui_menuiteminfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENUITEMINFO_H
