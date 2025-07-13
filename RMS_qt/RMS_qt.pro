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
    OrdersWidget.cpp \
    databasemanager.cpp \
    main.cpp \
    mainwindow.cpp \
    orders.cpp   \
    checkout.cpp  \
    edit_order.cpp \
    pos.cpp \
    pos_addorder.cpp

HEADERS += \
    OrdersWidget.h \
    databasemanager.h \
    mainwindow.h \
    orders.h    \
    checkout.h  \
    edit_order.h \
    pos.h \
    pos_addorder.h

FORMS += \
    mainwindow.ui \
    orders.ui  \
    checkout.ui  \
    edit_order.ui \
    pos.ui \
    pos_addorder.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
