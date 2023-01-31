#include "mainwindow.h"
#include <QApplication>
#include "login2.h"
#include "XStateClient.h"
#include <QDebug>
#include <iostream>
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    login2 l;
    l.show();

//    w.show();

    return a.exec();
}
