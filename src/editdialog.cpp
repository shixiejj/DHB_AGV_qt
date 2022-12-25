#include "editdialog.h"
#include "ui_editdialog.h"

editDialog::editDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("任务配置");
    ui->showOffer->setAlignment(Qt::AlignCenter);
    ui->editPriority->lineEdit()->setAlignment(Qt::AlignCenter);
    ui->comboBox_207->lineEdit()->setAlignment(Qt::AlignCenter);
    ui->comboBox_208->lineEdit()->setAlignment(Qt::AlignCenter);
    ui->comboBox_209->lineEdit()->setAlignment(Qt::AlignCenter);
    ui->comboBox_210->lineEdit()->setAlignment(Qt::AlignCenter);
    ui->comboBox_211->lineEdit()->setAlignment(Qt::AlignCenter);
    ui->comboBox_212->lineEdit()->setAlignment(Qt::AlignCenter);
}

editDialog::~editDialog()
{
    delete ui;
}

void editDialog::setUpdateRecord(QSqlRecord &recData)
{
    mRecord=recData;
    ui->showOffer->setEnabled(false); //员工编号不允许编辑
    setWindowTitle("任务编辑");

//根据recData的数据更新界面显示
    ui->showOffer->setText(recData.value("offerID").toString());
    ui->editPriority->setCurrentText(recData.value("offerPriority").toString());

}

QSqlRecord editDialog::getRecordData()
{ //"确定"按钮后，界面数据保存到记录mRecord
   // mRecord.setValue("offerID",ui->showOffer->text());
    mRecord.setValue("offerPriority",ui->editPriority->currentText());

    return  mRecord; //以记录作为返回值
}
