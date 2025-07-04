/********************************************************************************
** Form generated from reading UI file 'table_management.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABLE_MANAGEMENT_H
#define UI_TABLE_MANAGEMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_table_management
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QPushButton *btn_edittable;
    QTableWidget *table_Tablelist;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *table_management)
    {
        if (table_management->objectName().isEmpty())
            table_management->setObjectName("table_management");
        table_management->resize(800, 600);
        table_management->setMinimumSize(QSize(800, 600));
        table_management->setMaximumSize(QSize(800, 600));
        centralwidget = new QWidget(table_management);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 0, 711, 21));
        label->setStyleSheet(QString::fromUtf8("font: 700 12pt \"Arial\";\n"
"background-color:rgb(34,199,205);\n"
"color:white;\n"
""));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(710, 0, 101, 21));
        label_2->setStyleSheet(QString::fromUtf8("font: 700 12pt \"Arial\";\n"
"background-color:rgb(34,199,205);\n"
"color:white;\n"
"\n"
""));
        btn_edittable = new QPushButton(centralwidget);
        btn_edittable->setObjectName("btn_edittable");
        btn_edittable->setGeometry(QRect(640, 220, 101, 31));
        btn_edittable->setStyleSheet(QString::fromUtf8("\n"
"\n"
"QPushButton {\n"
"    background-color: rgb(0,123,255);\n"
"    color: white;                \n"
"    border: none;\n"
"    padding: 6px 12px;\n"
"    font: 700 12pt \"Arial\";\n"
"    font-weight: bold;\n"
"    border-radius: 6px;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: rgb(102,191,255); \n"
"    color: white;\n"
"}\n"
""));
        table_Tablelist = new QTableWidget(centralwidget);
        if (table_Tablelist->columnCount() < 6)
            table_Tablelist->setColumnCount(6);
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(12);
        font.setBold(true);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font);
        table_Tablelist->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font);
        table_Tablelist->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font);
        table_Tablelist->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font);
        table_Tablelist->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFont(font);
        table_Tablelist->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setFont(font);
        table_Tablelist->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        table_Tablelist->setObjectName("table_Tablelist");
        table_Tablelist->setGeometry(QRect(10, 260, 791, 321));
        table_Tablelist->setStyleSheet(QString::fromUtf8(""));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 240, 91, 16));
        label_3->setStyleSheet(QString::fromUtf8("font: 700 12pt \"Arial\";"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(50, 80, 181, 41));
        label_4->setStyleSheet(QString::fromUtf8("font: 700 12pt \"Arial\";\n"
"background-color:yellow;\n"
"border-radius:20;\n"
"border:solid;\n"
"border:2px solid rgb(0,0,0);"));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(570, 80, 151, 41));
        label_5->setStyleSheet(QString::fromUtf8("font: 700 12pt \"Arial\";\n"
"background-color:yellow;\n"
"border-radius:20;\n"
"border:2px solid rgb(0,0,0);"));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(310, 80, 161, 41));
        label_6->setStyleSheet(QString::fromUtf8("font: 700 12pt \"Arial\";\n"
"background-color:yellow;\n"
"border-radius:20;\n"
"border:2px solid rgb(0,0,0);\n"
""));
        table_management->setCentralWidget(centralwidget);
        menubar = new QMenuBar(table_management);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 18));
        table_management->setMenuBar(menubar);
        statusbar = new QStatusBar(table_management);
        statusbar->setObjectName("statusbar");
        table_management->setStatusBar(statusbar);

        retranslateUi(table_management);

        QMetaObject::connectSlotsByName(table_management);
    } // setupUi

    void retranslateUi(QMainWindow *table_management)
    {
        table_management->setWindowTitle(QCoreApplication::translate("table_management", "table_management", nullptr));
        label->setText(QCoreApplication::translate("table_management", "Table Management", nullptr));
        label_2->setText(QCoreApplication::translate("table_management", "Manager", nullptr));
        btn_edittable->setText(QCoreApplication::translate("table_management", "Edit Table", nullptr));
        QTableWidgetItem *___qtablewidgetitem = table_Tablelist->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("table_management", "Table No.", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = table_Tablelist->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("table_management", "Seats", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = table_Tablelist->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("table_management", "Status", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = table_Tablelist->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("table_management", "Order Id", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = table_Tablelist->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("table_management", "Time Seated", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = table_Tablelist->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("table_management", "Remarks", nullptr));
        label_3->setText(QCoreApplication::translate("table_management", "Table List:", nullptr));
        label_4->setText(QCoreApplication::translate("table_management", "  Total No. of Tables:", nullptr));
        label_5->setText(QCoreApplication::translate("table_management", "  Taken Tables:", nullptr));
        label_6->setText(QCoreApplication::translate("table_management", "  Available Tables:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class table_management: public Ui_table_management {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABLE_MANAGEMENT_H
