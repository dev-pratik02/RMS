/********************************************************************************
** Form generated from reading UI file 'pos.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POS_H
#define UI_POS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pos
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QPushButton *btn_place_order;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QComboBox *pos_table_dropdown;
    QMenuBar *menubar;

    void setupUi(QMainWindow *pos)
    {
        if (pos->objectName().isEmpty())
            pos->setObjectName("pos");
        pos->resize(800, 600);
        centralwidget = new QWidget(pos);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(240, 60, 381, 31));
        QFont font;
        font.setPointSize(30);
        label->setFont(font);
        btn_place_order = new QPushButton(centralwidget);
        btn_place_order->setObjectName("btn_place_order");
        btn_place_order->setGeometry(QRect(330, 320, 101, 32));
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(300, 230, 181, 32));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);

        pos_table_dropdown = new QComboBox(widget);
        pos_table_dropdown->setObjectName("pos_table_dropdown");

        horizontalLayout->addWidget(pos_table_dropdown);

        pos->setCentralWidget(centralwidget);
        menubar = new QMenuBar(pos);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 24));
        pos->setMenuBar(menubar);

        retranslateUi(pos);

        QMetaObject::connectSlotsByName(pos);
    } // setupUi

    void retranslateUi(QMainWindow *pos)
    {
        pos->setWindowTitle(QCoreApplication::translate("pos", "POS", nullptr));
        label->setText(QCoreApplication::translate("pos", "Select a table to place order", nullptr));
        btn_place_order->setText(QCoreApplication::translate("pos", "Place Order", nullptr));
        label_2->setText(QCoreApplication::translate("pos", "Table no:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class pos: public Ui_pos {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POS_H
