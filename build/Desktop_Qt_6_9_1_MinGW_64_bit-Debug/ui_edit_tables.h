/********************************************************************************
** Form generated from reading UI file 'edit_tables.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDIT_TABLES_H
#define UI_EDIT_TABLES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_Edit_tables
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QTableWidget *edit_table;
    QPushButton *btn_back;
    QPushButton *btn_addtables;

    void setupUi(QDialog *Edit_tables)
    {
        if (Edit_tables->objectName().isEmpty())
            Edit_tables->setObjectName("Edit_tables");
        Edit_tables->resize(800, 600);
        Edit_tables->setMinimumSize(QSize(800, 600));
        Edit_tables->setMaximumSize(QSize(800, 600));
        label = new QLabel(Edit_tables);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 801, 21));
        label->setStyleSheet(QString::fromUtf8("font: 700 12pt \"Arial\";\n"
"background-color:rgb(34,199,205);\n"
"color:white;"));
        label_2 = new QLabel(Edit_tables);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(720, 0, 81, 20));
        label_2->setStyleSheet(QString::fromUtf8("font: 700 12pt \"Arial\";\n"
"background-color:rgb(34,199,205);\n"
"color:white;"));
        label_3 = new QLabel(Edit_tables);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 50, 101, 21));
        label_3->setStyleSheet(QString::fromUtf8("font: 700 12pt \"Arial\";"));
        edit_table = new QTableWidget(Edit_tables);
        if (edit_table->columnCount() < 6)
            edit_table->setColumnCount(6);
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(12);
        font.setBold(true);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font);
        edit_table->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font);
        edit_table->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font);
        edit_table->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font);
        edit_table->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFont(font);
        edit_table->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setFont(font);
        edit_table->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        edit_table->setObjectName("edit_table");
        edit_table->setGeometry(QRect(10, 91, 781, 451));
        btn_back = new QPushButton(Edit_tables);
        btn_back->setObjectName("btn_back");
        btn_back->setGeometry(QRect(370, 560, 61, 21));
        btn_back->setStyleSheet(QString::fromUtf8("font: 12pt \"Arial\";\n"
"pushButton:{\n"
"background-color:black;\n"
"color:white;\n"
"}\n"
"pushButton:Hover{\n"
"background-color:white;\n"
"color:black;\n"
"}\n"
""));
        btn_addtables = new QPushButton(Edit_tables);
        btn_addtables->setObjectName("btn_addtables");
        btn_addtables->setGeometry(QRect(610, 40, 121, 31));
        btn_addtables->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: yellow;\n"
"    color: black;\n"
"    border: none;\n"
"    padding: 6px 12px;\n"
"    font-weight: bold;\n"
"    border-radius: 15px;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color:rgb(255,255,200);\n"
"}\n"
""));

        retranslateUi(Edit_tables);

        QMetaObject::connectSlotsByName(Edit_tables);
    } // setupUi

    void retranslateUi(QDialog *Edit_tables)
    {
        Edit_tables->setWindowTitle(QCoreApplication::translate("Edit_tables", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Edit_tables", "   Table Management > Edit Tables", nullptr));
        label_2->setText(QCoreApplication::translate("Edit_tables", "Manager", nullptr));
        label_3->setText(QCoreApplication::translate("Edit_tables", "Tables List:", nullptr));
        QTableWidgetItem *___qtablewidgetitem = edit_table->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("Edit_tables", "Table No.", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = edit_table->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("Edit_tables", "Seats", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = edit_table->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("Edit_tables", "Table Quality", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = edit_table->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("Edit_tables", "Table Location", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = edit_table->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("Edit_tables", "Orientations", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = edit_table->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("Edit_tables", "Action", nullptr));
        btn_back->setText(QCoreApplication::translate("Edit_tables", "back", nullptr));
        btn_addtables->setText(QCoreApplication::translate("Edit_tables", "Add new Tables", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Edit_tables: public Ui_Edit_tables {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDIT_TABLES_H
