#include "firstwindow.h"
#include "ui_firstwindow.h"
#include "login.h"
#include "ui_login.h"
#include "login2.h"
#include "ui_login2.h"

FirstWindow::FirstWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FirstWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("智能物流系统初始化界面");
}

FirstWindow::~FirstWindow()
{
    delete ui;
}

void FirstWindow::on_pushButton_clicked()
{
    login = new Login;
    login->show();
    log = new login2;
    log->show();
}
