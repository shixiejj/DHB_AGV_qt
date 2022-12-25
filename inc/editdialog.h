#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>
#include <QSqlRecord>

namespace Ui {
class editDialog;
}

class editDialog : public QDialog
{
    Q_OBJECT

public:
    explicit editDialog(QWidget *parent = nullptr);
    ~editDialog();

    void    setUpdateRecord(QSqlRecord &recData); //更新记录
    void    setInsertRecord(QSqlRecord &recData); //插入记录
    QSqlRecord  getRecordData();//获取录入的数据

private:
    Ui::editDialog *ui;
    QSqlRecord  mRecord; //保存一条记录的数据
};

#endif // EDITDIALOG_H
