/********************************************************************************
** Form generated from reading UI file 'categories.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CATEGORIES_H
#define UI_CATEGORIES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_categories
{
public:
    QLabel *label;
    QTableWidget *tableWidget;
    QLabel *MENUMANAGEMENT;
    QPushButton *btn_addcategory;

    void setupUi(QDialog *categories)
    {
        if (categories->objectName().isEmpty())
            categories->setObjectName("categories");
        categories->resize(800, 600);
        label = new QLabel(categories);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 110, 82, 18));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(12);
        font.setBold(true);
        label->setFont(font);
        tableWidget = new QTableWidget(categories);
        if (tableWidget->columnCount() < 5)
            tableWidget->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(45, 141, 701, 411));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(false);
        tableWidget->setFont(font1);
        tableWidget->horizontalHeader()->setMinimumSectionSize(20);
        tableWidget->horizontalHeader()->setDefaultSectionSize(141);
        MENUMANAGEMENT = new QLabel(categories);
        MENUMANAGEMENT->setObjectName("MENUMANAGEMENT");
        MENUMANAGEMENT->setGeometry(QRect(230, 30, 311, 24));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Arial")});
        font2.setPointSize(16);
        font2.setBold(true);
        font2.setItalic(false);
        MENUMANAGEMENT->setFont(font2);
        MENUMANAGEMENT->setAlignment(Qt::AlignmentFlag::AlignCenter);
        btn_addcategory = new QPushButton(categories);
        btn_addcategory->setObjectName("btn_addcategory");
        btn_addcategory->setGeometry(QRect(560, 100, 184, 26));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Arial")});
        font3.setPointSize(12);
        font3.setBold(true);
        font3.setItalic(false);
        btn_addcategory->setFont(font3);

        retranslateUi(categories);

        QMetaObject::connectSlotsByName(categories);
    } // setupUi

    void retranslateUi(QDialog *categories)
    {
        categories->setWindowTitle(QCoreApplication::translate("categories", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("categories", "Categories:", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("categories", "Categoty Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("categories", "Category Id", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("categories", "No. of Items", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("categories", "Description", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("categories", "Action", nullptr));
        MENUMANAGEMENT->setText(QCoreApplication::translate("categories", "CATEGORIES MANAGEMENT", nullptr));
        btn_addcategory->setText(QCoreApplication::translate("categories", "ADD NEW CATEGORY", nullptr));
    } // retranslateUi

};

namespace Ui {
    class categories: public Ui_categories {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CATEGORIES_H
