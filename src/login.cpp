#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setWindowTitle("登录界面");
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{

       m = new MainWindow;
       m->show();

      // QMessageBox::information(this,"提示","用户名或密码输入错误");

}
