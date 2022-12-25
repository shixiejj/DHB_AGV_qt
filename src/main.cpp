#include "mainwindow.h"
#include <QApplication>
#include "login.h"
#include "firstwindow.h"
#include "firstwindow2.h"
#include "XStateClient.h"
#include <QDebug>
#include <iostream>
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    firstwindow2 s;
    s.show();

//    w.show();

    return a.exec();
}
