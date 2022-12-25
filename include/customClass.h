/*********************************************
* 自定义类文件，可以在此放置自定义模型类及其他
*********************************************/
#ifndef CUSTOMCLASS_H
#define CUSTOMCLASS_H

#include <QObject>
#include <QSqlQueryModel>

/*******************************************************
 *
 *
*******************************************************/
class CustomSqlQueryModel : public QSqlQueryModel
{
    public:
       CustomSqlQueryModel(QObject *parent = 0);

// QAbstractItemModel interface
    public:
       QVariant data(const QModelIndex &index, int role) const override;
};


/*******************************************************
 *
 *
*******************************************************/

#endif // CUSTOMCLASS_H
