QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    member.cpp \
    p_member.cpp \
    product.cpp \
    product_list.cpp \
    warehouse_function.cpp

HEADERS += \
    mainwindow.h \
    member.h \
    p_member.h \
    product.h \
    product_list.h \
    node.h \
    list_sorted.h \
    linked_list_functions.h \
    warehouse_function.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    day1.txt \
    day2.txt \
    day3.txt \
    day4.txt \
    day5.txt \
    names.txt \
    warehouse_shoppers.txt

RESOURCES += \
    textfiles.qrc
