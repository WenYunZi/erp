#ifndef FUCAICHUKUDELEGATE_H
#define FUCAICHUKUDELEGATE_H

#include <QItemDelegate>
#include <QComboBox>
#include <QLineEdit>
#include <QModelIndex>
#include <QString>
#include "mymysql.h"

class fucaichukuDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit fucaichukuDelegate(int column1, QObject *parent = 0);

    //返回一个编辑控件，用来编辑指定项的数据
    QWidget *createEditor(QWidget *parent,const QStyleOptionViewItem &option,const QModelIndex &index) const;
    //将Model中数据赋值到控件上
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    //设定模型数据，根据指定项中对应编辑控件的数据
    void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const;

private:
    int column1;

private slots:
    void commitEditor();
    void commitEditor1();

};

#endif // FUCAICHUKUDELEGATE_H
