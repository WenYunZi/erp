#ifndef CHELIANGWEIXIUDELEGATE_H
#define CHELIANGWEIXIUDELEGATE_H

#include <QItemDelegate>
#include <QItemDelegate>
#include <QComboBox>
#include <QString>
#include <QLineEdit>
#include <QListView>
#include "mymysql.h"

class cheliangweixiuguanli;

class cheliangweixiuDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit cheliangweixiuDelegate(cheliangweixiuguanli *clwx_wx, int gongyingshang_wx, int peijianxinghao_wx,QObject *parent = 0);

    //返回一个编辑控件，用来编辑指定项的数据
    QWidget *createEditor(QWidget *parent,const QStyleOptionViewItem &option,const QModelIndex &index) const;
    //将Model中数据赋值到控件上
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    //设定模型数据，根据指定项中对应编辑控件的数据
    void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const;

private:
    int gongyingshang_dl;
    int peijianxinghao_dl ;

    cheliangweixiuguanli *clwx_dl;


private slots:
    void commitEditor();
    void commitEditor1();

};

#endif // CHELIANGWEIXIUDELEGATE_H
