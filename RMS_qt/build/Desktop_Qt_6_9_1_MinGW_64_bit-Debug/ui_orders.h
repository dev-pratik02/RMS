/********************************************************************************
** Form generated from reading UI file 'orders.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ORDERS_H
#define UI_ORDERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_orders
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QWidget *cardContainer;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *orders)
    {
        if (orders->objectName().isEmpty())
            orders->setObjectName("orders");
        orders->resize(800, 600);
        centralwidget = new QWidget(orders);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 0, 58, 16));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(700, 0, 58, 16));
        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(50, 49, 701, 501));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 699, 499));
        cardContainer = new QWidget(scrollAreaWidgetContents);
        cardContainer->setObjectName("cardContainer");
        cardContainer->setGeometry(QRect(50, 29, 551, 341));
        scrollArea->setWidget(scrollAreaWidgetContents);
        orders->setCentralWidget(centralwidget);
        menubar = new QMenuBar(orders);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 24));
        orders->setMenuBar(menubar);
        statusbar = new QStatusBar(orders);
        statusbar->setObjectName("statusbar");
        orders->setStatusBar(statusbar);

        retranslateUi(orders);

        QMetaObject::connectSlotsByName(orders);
    } // setupUi

    void retranslateUi(QMainWindow *orders)
    {
        orders->setWindowTitle(QCoreApplication::translate("orders", "Orders", nullptr));
        label->setText(QCoreApplication::translate("orders", "Orders", nullptr));
        label_2->setText(QCoreApplication::translate("orders", "Manager", nullptr));
    } // retranslateUi

};

namespace Ui {
    class orders: public Ui_orders {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ORDERS_H
