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

SOURCES += main.cpp\
    communicate.cpp \
    customClass.cpp \
    drawdraw.cpp \
    editdialog.cpp \
    editwidget.cpp \
    function.cpp \
        mainwindow.cpp \
    device_con.cpp \
    login2.cpp \
    firstwindow2.cpp \
    mythread.cpp \
    mythread2.cpp \
    mythread3.cpp \
    amr_b_dispatch.cpp \
    amr_d_dispatch.cpp \
    global_variables.cpp \
    mythread4.cpp \
    XStateClient.cpp \
    XData.cpp \
    showunitywindowsinqt.cpp

HEADERS  += mainwindow.h \
    car.h \
    communicate.h \
    customClass.h \
    device_con.h \
    drawdraw.h \
    editdialog.h \
    editwidget.h \
    login2.h \
    firstwindow2.h \
    mythread.h \
    mythread2.h \
    mythread3.h \
    amr_b_dispatch.h \
    amr_d_dispatch.h \
    global_variables.h \
    mythread4.h \
    XData.h \
    XStateClient.h \
    showunitywindowsinqt.h

FORMS    += mainwindow.ui \
    device_con.ui \
    editdialog.ui \
    editwidget.ui \
    login2.ui \
    firstwindow2.ui \

//win32:RC_FILE = ICO.rc

RESOURCES += \
    res.qrc

LIBS += -lws2_32
