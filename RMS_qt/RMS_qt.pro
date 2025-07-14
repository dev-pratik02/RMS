QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add_tables.cpp \
    edit.cpp \
    editing_table.cpp \
    main.cpp \
    mainwindow.cpp \
    table.cpp

HEADERS += \
    add_tables.h \
    edit.h \
    editing_table.h \
    mainwindow.h \
    table.h

FORMS += \
    add_tables.ui \
    edit.ui \
    editing_table.ui \
    mainwindow.ui \
    table.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
