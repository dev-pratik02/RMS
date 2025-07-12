/********************************************************************************
** Form generated from reading UI file 'menu.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENU_H
#define UI_MENU_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_menu
{
public:
    QWidget *centralwidget;
    QLabel *MENUMANAGEMENT;
    QLabel *menuitems;
    QPushButton *btn_addmenu;
    QTableWidget *tableWidget;
    QPushButton *btn_category;
    QMenuBar *menubar;
    QMenu *menuMenu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *menu)
    {
        if (menu->objectName().isEmpty())
            menu->setObjectName("menu");
        menu->resize(800, 600);
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(12);
        font.setItalic(true);
        menu->setFont(font);
        centralwidget = new QWidget(menu);
        centralwidget->setObjectName("centralwidget");
        MENUMANAGEMENT = new QLabel(centralwidget);
        MENUMANAGEMENT->setObjectName("MENUMANAGEMENT");
        MENUMANAGEMENT->setGeometry(QRect(270, 20, 271, 51));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial")});
        font1.setPointSize(16);
        font1.setBold(true);
        font1.setItalic(false);
        MENUMANAGEMENT->setFont(font1);
        MENUMANAGEMENT->setAlignment(Qt::AlignmentFlag::AlignCenter);
        menuitems = new QLabel(centralwidget);
        menuitems->setObjectName("menuitems");
        menuitems->setGeometry(QRect(40, 180, 121, 31));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Arial")});
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setItalic(false);
        menuitems->setFont(font2);
        btn_addmenu = new QPushButton(centralwidget);
        btn_addmenu->setObjectName("btn_addmenu");
        btn_addmenu->setGeometry(QRect(580, 170, 171, 31));
        btn_addmenu->setFont(font2);
        tableWidget = new QTableWidget(centralwidget);
        if (tableWidget->columnCount() < 6)
            tableWidget->setColumnCount(6);
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
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setEnabled(true);
        tableWidget->setGeometry(QRect(30, 230, 751, 221));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy);
        tableWidget->setBaseSize(QSize(0, 0));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Arial")});
        font3.setPointSize(12);
        font3.setBold(false);
        font3.setItalic(false);
        font3.setStrikeOut(false);
        font3.setKerning(false);
        font3.setStyleStrategy(QFont::PreferDefault);
        font3.setHintingPreference(QFont::PreferDefaultHinting);
        tableWidget->setFont(font3);
        tableWidget->setMouseTracking(false);
        tableWidget->setTabletTracking(false);
        tableWidget->horizontalHeader()->setMinimumSectionSize(28);
        tableWidget->horizontalHeader()->setDefaultSectionSize(148);
        tableWidget->horizontalHeader()->setHighlightSections(true);
        tableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableWidget->verticalHeader()->setDefaultSectionSize(29);
        btn_category = new QPushButton(centralwidget);
        btn_category->setObjectName("btn_category");
        btn_category->setGeometry(QRect(580, 110, 171, 31));
        btn_category->setFont(font2);
        menu->setCentralWidget(centralwidget);
        menubar = new QMenuBar(menu);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 23));
        menuMenu = new QMenu(menubar);
        menuMenu->setObjectName("menuMenu");
        menu->setMenuBar(menubar);
        statusbar = new QStatusBar(menu);
        statusbar->setObjectName("statusbar");
        menu->setStatusBar(statusbar);

        menubar->addAction(menuMenu->menuAction());

        retranslateUi(menu);

        QMetaObject::connectSlotsByName(menu);
    } // setupUi

    void retranslateUi(QMainWindow *menu)
    {
        menu->setWindowTitle(QCoreApplication::translate("menu", "MainWindow", nullptr));
        MENUMANAGEMENT->setText(QCoreApplication::translate("menu", "MENU MANAGEMENT ", nullptr));
        menuitems->setText(QCoreApplication::translate("menu", "Menu Items:", nullptr));
        btn_addmenu->setText(QCoreApplication::translate("menu", "Add Menu Item:", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("menu", "Item ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("menu", "Item Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("menu", "Price", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("menu", "Category", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("menu", "Description", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("menu", "Action", nullptr));
        btn_category->setText(QCoreApplication::translate("menu", "Categories:", nullptr));
        menuMenu->setTitle(QCoreApplication::translate("menu", "Menu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class menu: public Ui_menu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENU_H
