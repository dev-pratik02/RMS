/********************************************************************************
** Form generated from reading UI file 'add_tables.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADD_TABLES_H
#define UI_ADD_TABLES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Add_tables
{
public:
    QPushButton *btn_save;
    QLabel *label;
    QPushButton *btn_reset;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLineEdit *lineEdit_1;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QTextEdit *textEdit;
    QLineEdit *lineEdit_2;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;

    void setupUi(QDialog *Add_tables)
    {
        if (Add_tables->objectName().isEmpty())
            Add_tables->setObjectName("Add_tables");
        Add_tables->resize(800, 600);
        Add_tables->setMinimumSize(QSize(800, 600));
        Add_tables->setMaximumSize(QSize(800, 600));
        btn_save = new QPushButton(Add_tables);
        btn_save->setObjectName("btn_save");
        btn_save->setGeometry(QRect(530, 490, 81, 21));
        btn_save->setStyleSheet(QString::fromUtf8("font: 12pt \"Arial\";\n"
"font:  12pt \"Arial\";\n"
"PushButton:{\n"
"background-color:blue;\n"
"color-white;\n"
"\n"
"}\n"
"pushButton:Pressed{\n"
"background-color:rgb(255,255,200);\n"
"}"));
        label = new QLabel(Add_tables);
        label->setObjectName("label");
        label->setGeometry(QRect(330, 0, 151, 31));
        label->setStyleSheet(QString::fromUtf8("font: 700 16pt \"Arial\";\n"
"background-color:rgb(120,120,120);\n"
"color:white;"));
        btn_reset = new QPushButton(Add_tables);
        btn_reset->setObjectName("btn_reset");
        btn_reset->setGeometry(QRect(170, 490, 81, 21));
        btn_reset->setStyleSheet(QString::fromUtf8("font:  12pt \"Arial\";"));
        formLayoutWidget = new QWidget(Add_tables);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(110, 80, 581, 331));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_1 = new QLineEdit(formLayoutWidget);
        lineEdit_1->setObjectName("lineEdit_1");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, lineEdit_1);

        lineEdit_3 = new QLineEdit(formLayoutWidget);
        lineEdit_3->setObjectName("lineEdit_3");

        formLayout->setWidget(5, QFormLayout::ItemRole::FieldRole, lineEdit_3);

        lineEdit_4 = new QLineEdit(formLayoutWidget);
        lineEdit_4->setObjectName("lineEdit_4");

        formLayout->setWidget(7, QFormLayout::ItemRole::FieldRole, lineEdit_4);

        lineEdit_5 = new QLineEdit(formLayoutWidget);
        lineEdit_5->setObjectName("lineEdit_5");

        formLayout->setWidget(9, QFormLayout::ItemRole::FieldRole, lineEdit_5);

        textEdit = new QTextEdit(formLayoutWidget);
        textEdit->setObjectName("textEdit");

        formLayout->setWidget(11, QFormLayout::ItemRole::FieldRole, textEdit);

        lineEdit_2 = new QLineEdit(formLayoutWidget);
        lineEdit_2->setObjectName("lineEdit_2");

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, lineEdit_2);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName("label_2");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, label_2);

        label_3 = new QLabel(formLayoutWidget);
        label_3->setObjectName("label_3");

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, label_3);

        label_4 = new QLabel(formLayoutWidget);
        label_4->setObjectName("label_4");

        formLayout->setWidget(4, QFormLayout::ItemRole::FieldRole, label_4);

        label_5 = new QLabel(formLayoutWidget);
        label_5->setObjectName("label_5");

        formLayout->setWidget(6, QFormLayout::ItemRole::FieldRole, label_5);

        label_6 = new QLabel(formLayoutWidget);
        label_6->setObjectName("label_6");

        formLayout->setWidget(8, QFormLayout::ItemRole::FieldRole, label_6);

        label_7 = new QLabel(formLayoutWidget);
        label_7->setObjectName("label_7");

        formLayout->setWidget(10, QFormLayout::ItemRole::FieldRole, label_7);


        retranslateUi(Add_tables);

        QMetaObject::connectSlotsByName(Add_tables);
    } // setupUi

    void retranslateUi(QDialog *Add_tables)
    {
        Add_tables->setWindowTitle(QCoreApplication::translate("Add_tables", "Dialog", nullptr));
        btn_save->setText(QCoreApplication::translate("Add_tables", "Save", nullptr));
        label->setText(QCoreApplication::translate("Add_tables", "   ADD TABLES", nullptr));
        btn_reset->setText(QCoreApplication::translate("Add_tables", "Reset", nullptr));
        label_2->setText(QCoreApplication::translate("Add_tables", "Table No.", nullptr));
        label_3->setText(QCoreApplication::translate("Add_tables", "Seats", nullptr));
        label_4->setText(QCoreApplication::translate("Add_tables", "Table location", nullptr));
        label_5->setText(QCoreApplication::translate("Add_tables", "Table Orientation", nullptr));
        label_6->setText(QCoreApplication::translate("Add_tables", "Table type", nullptr));
        label_7->setText(QCoreApplication::translate("Add_tables", "Description", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Add_tables: public Ui_Add_tables {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADD_TABLES_H
