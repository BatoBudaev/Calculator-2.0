QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 console

INCLUDEPATH += $$PWD/View

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../Model/s21_bank.cpp \
    ../Model/s21_model.cpp \
    ../Model/s21_stack.cpp \
    credit.cpp \
    deposit.cpp \
    graph.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    ../Controller/s21_controller.cpp

HEADERS += \
    ../Model/s21_bank.h \
    ../Model/s21_stack.h \
    ../Model/s21_model.h \
    credit.h \
    deposit.h \
    graph.h \
    mainwindow.h \
    qcustomplot.h \
    ../Controller/s21_controller.h

FORMS += \
    credit.ui \
    deposit.ui \
    graph.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
