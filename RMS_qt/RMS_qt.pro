QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = RMS_qt
TEMPLATE = app

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add_tables.cpp \
    addcategory.cpp \
    addmenuitem.cpp \
    addstaff.cpp \
    category.cpp \
    change_password.cpp \
    checkout.cpp \
    databasemanager.cpp \
    edit_order.cpp \
    edit.cpp \
    editcategory.cpp \
    editing_table.cpp \
    editmenuitem.cpp \
    editstaff.cpp \
    forgotpass.cpp \
    globals.cpp \
    login_page.cpp \
    mainwindow.cpp \
    menu.cpp \
    orders.cpp \
    OrdersWidget.cpp \
    pos_addorder.cpp \
    pos.cpp \
    profile.cpp \
    signup.cpp \
    staff.cpp \
    table.cpp \
    users.cpp \
    utils.cpp \
    main.cpp

HEADERS += \
    add_tables.h \
    addcategory.h \
    addmenuitem.h \
    addstaff.h \
    category.h \
    change_password.h \
    checkout.h \
    databasemanager.h \
    edit_order.h \
    edit.h \
    editcategory.h \
    editing_table.h \
    editmenuitem.h \
    editstaff.h \
    forgotpass.h \
    globals.h \
    login_page.h \
    mainwindow.h \
    menu.h \
    orders.h \
    OrdersWidget.h \
    pos_addorder.h \
    pos.h \
    profile.h \
    signup.h \
    staff.h \
    table.h \
    users.h \
    utils.h

FORMS += \
    add_tables.ui \
    addcategory.ui \
    addmenuitem.ui \
    addstaff.ui \
    category.ui \
    change_password.ui \
    checkout.ui \
    edit_order.ui \
    edit.ui \
    editcategory.ui \
    editing_table.ui \
    editmenuitem.ui \
    editstaff.ui \
    forgotpass.ui \
    login_page.ui \
    mainwindow.ui \
    menu.ui \
    orders.ui \
    pos_addorder.ui \
    pos.ui \
    profile.ui \
    signup.ui \
    staff.ui \
    table.ui \
    users.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
