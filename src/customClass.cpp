/*********************************************
 * 此文件为数据库模型自定义
 * 自定义模型以实现显示需求
 * v1.0 添加文字居中属性
 * 2022.12.20 添加不同属性更换颜色功能
*********************************************/
#include "customClass.h"
#include "mainwindow.h"

CustomSqlQueryModel::CustomSqlQueryModel(QObject *parent) : QSqlQueryModel(parent)
{}

//重写data函数以实现文字居中，index为当前文本索引，role为设置类型
QVariant CustomSqlQueryModel::data(const QModelIndex &index, int role) const
{
    //添加居中属性
    QVariant value = QSqlQueryModel::data(index, role);
    if (Qt::TextAlignmentRole == role) {
        value = Qt::AlignCenter;
    }
    //根据执行进度更改文本颜色
    if(Qt::ForegroundRole == role && (this->headerData(index.column(),Qt::Horizontal).toString() == "任务状态")){
        if(index.data() == "待执行"){
            value = QBrush(Qt::green);
        }
        else if(index.data() == "已执行"){
            value = QBrush(Qt::white);
        }
        else{
            value = QBrush(Qt::yellow);
        }
    }
    return value;
}


