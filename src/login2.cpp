#include "login2.h"
#include "ui_login2.h"
#include "mainwindow.h"
//#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

bool temp::optEnable = false;

 login2::login2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login2)
{
    ui->setupUi(this);
    this->setWindowTitle("登录界面");


//    //新建数据库
//    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
//    QStringList list = QSqlDatabase::drivers();
//    qDebug()<<list;
//    db.setDatabaseName("testDB.db");
//    if(!db.open())
//    {
//    qDebug()<<"失败原因： "<<db.lastError().text();
//    }
//    else
//    {
//        qDebug()<<"连接成功!!!";
//    }
//    QSqlQuery query;
//    QString sql = "select * from test2";
//    query.exec(sql);

//    //获取填入的用户名和密码
//    QString name = ui->lineEdit_user->text();
//    QString password = ui->lineEdit_passward->text();

//    QString str=QString("select * from User where Name='%1' and Password='%2'").arg(name).arg(password);
//        query = new QSqlQuery;
//        query->exec(str);
//        query->last();
//        int record=query->at()+1;
//        if(record==0)
//        {
//            QMessageBox::information(this,"提示","用户或密码不对",QMessageBox::Ok);
//        }



}

login2::~login2()
{
    delete ui;
}
void login2::on_pushButton_clicked()
{
      if (ui->lineEdit_user->text().trimmed() == tr("20000001")
              && ui->lineEdit_passward->text() == tr("1111"))
      {
          temp::optEnable = true;
//        accept();

       m = new MainWindow;
       m->show();
       this->hide();
      }

      else
      {
          QMessageBox::warning(this,"提示","用户名或密码输入错误");
//         QMessageBox message(QMessageBox::warning("提示", " <font size = '10' color = 'white' > 用户名或密码输入错误</font>", QMessageBox::Yes | QMessageBox::No, NULL );
//         message.exec();

      }

}
