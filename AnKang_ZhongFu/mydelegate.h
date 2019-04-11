#ifndef MYDELEGATE_H
#define MYDELEGATE_H

#include <QItemDelegate>
#include <QComboBox>
#include <QString>
#include "mymysql.h"

class mydelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit mydelegate(int materialColumn, int unitMaterialColumn, const char *unitNo = NULL, QObject *parent = 0);

    //返回一个编辑控件，用来编辑指定项的数据
    QWidget *createEditor(QWidget *parent,const QStyleOptionViewItem &option,const QModelIndex &index) const;
    //将Model中数据赋值到控件上
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    //设定模型数据，根据指定项中对应编辑控件的数据
    void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const;

private:
    int materialColumn;
    int unitMaterialColumn;
    char *unitNo = NULL;

private slots:
    void commitEditor();
};

#endif // MYDELEGATE_H
