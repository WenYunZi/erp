#ifndef MYCHECKBOXDELEGATE_H
#define MYCHECKBOXDELEGATE_H

#include <QItemDelegate>
#include <QCheckBox>
#include <QString>
#include <QEvent>
#include <QMouseEvent>
#include "mymysql.h"

class myCheckBoxDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit myCheckBoxDelegate(int ColumnNo, QObject *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option,const QModelIndex &index);

private:
    int ColumnNo;

};

#endif // MYCHECKBOXDELEGATE_H
