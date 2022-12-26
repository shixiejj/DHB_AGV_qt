#-------------------------------------------------
#
# Project created by QtCreator 2022-10-19T14:58:40
#
#-------------------------------------------------

QT       += core gui sql network
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = agv-qt-1020-1
TEMPLATE = app

DESTDIR = $$PWD/bin

INCLUDEPATH += ./inc

SOURCES += src/main.cpp\
    src/communicate.cpp \
    src/customClass.cpp \
    src/drawdraw.cpp \
    src/editdialog.cpp \
    src/editwidget.cpp \
    src/function.cpp \
       src/mainwindow.cpp \
    src/device_con.cpp \
    src/login2.cpp \
    src/firstwindow2.cpp \
    src/mythread.cpp \
    src/mythread2.cpp \
    src/mythread3.cpp \
    src/amr_b_dispatch.cpp \
    src/amr_d_dispatch.cpp \
    src/global_variables.cpp \
    src/mythread4.cpp \
    src/XStateClient.cpp \
    src/XData.cpp \
    src/showunitywindowsinqt.cpp

HEADERS  += inc/mainwindow.h \
    inc/car.h \
    inc/communicate.h \
    inc/customClass.h \
    inc/device_con.h \
    inc/drawdraw.h \
    inc/editdialog.h \
    inc/editwidget.h \
    inc/login2.h \
    inc/firstwindow2.h \
    inc/mythread.h \
    inc/mythread2.h \
    inc/mythread3.h \
    inc/amr_b_dispatch.h \
    inc/amr_d_dispatch.h \
    inc/global_variables.h \
    inc/mythread4.h \
    inc/XData.h \
    inc/XStateClient.h \
    inc/showunitywindowsinqt.h

FORMS    += ui/mainwindow.ui \
    ui/device_con.ui \
    ui/editdialog.ui \
    ui/editwidget.ui \
    ui/login2.ui \
    ui/firstwindow2.ui \

//win32:RC_FILE = ICO.rc

RESOURCES += \
    res.qrc

LIBS += -lws2_32
