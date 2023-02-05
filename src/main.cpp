#include "mainwindow.h"
#include <QApplication>
#include "login2.h"
#include "XStateClient.h"
#include <QDebug>
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    MainWindow w;
    login2 l;
    l.show();

//    QList<QString> userName;
//    QList<QString> userPassword;
//    userName<<"dhblab"<<"罗佳"<<"甲方"<<"Alice";
//    userPassword<<"123"<<"456"<<"456"<<"456";
//    QList<int> permission={1,0,0,0};
//    w.DisplayUserInfo(userName,userPassword,permission);
//    w.show();

    return a.exec();
}
