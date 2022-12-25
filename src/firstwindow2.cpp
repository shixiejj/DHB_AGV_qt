#include "firstwindow2.h"
#include "ui_firstwindow2.h"
#include "login.h"
//#include "ui_login.h"
#include "login2.h"
#include "ui_login2.h"

firstwindow2::firstwindow2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::firstwindow2)
{
    ui->setupUi(this);
    this->setWindowTitle("多AMR调度控制系统");
}

firstwindow2::~firstwindow2()
{
    delete ui;
}
void firstwindow2::on_pushButton_clicked()
{
    log = new login2;
    log->show();

}
