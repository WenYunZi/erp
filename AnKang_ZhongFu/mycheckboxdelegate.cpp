#include "mycheckboxdelegate.h"

myCheckBoxDelegate::myCheckBoxDelegate(int ColumnNo,QObject *parent) :
    QItemDelegate(parent)
{
    this->ColumnNo = ColumnNo;
}

void myCheckBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,const QModelIndex &index) const
{
    if(index.column() == ColumnNo){
        QStyleOptionViewItem myOption = option;
        //绘制复选框，并根据index的Qt::CheckStateRole值改变状态
        QRect r((myOption.rect.left()+myOption.rect.right())/2-8,
                myOption.rect.top()+myOption.rect.height()/2-8,16,16);
        if(index.data(Qt::EditRole).toInt() == 0){
            Qt::CheckState checkstate=static_cast<Qt::CheckState>(0);
            drawCheck(painter, myOption,r,checkstate);
        }
        if(index.data(Qt::EditRole).toInt() == 2){
            Qt::CheckState checkstate=static_cast<Qt::CheckState>(2);
            drawCheck(painter, myOption,r,checkstate);
        }
    }else{
        QItemDelegate::paint(painter,option,index);
    }
}


bool myCheckBoxDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if(index.column() == ColumnNo){
        if(event->type() == QEvent::KeyPress){
            return false;
        }
        if(event->type() == QEvent::MouseButtonRelease){
            QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);
            //只有左键点击才有效
            if(mouse_event->button() != Qt::LeftButton){
                return false;
            }
            //根据当前单元格的选中状态来在 选中/未选中 之间切换
            QVariant value = index.data(Qt::EditRole);
            int stateNum = 0;
            if(value.toInt() == 0){
                stateNum = 2;
            }
            else if(value.toInt() == 2){
                stateNum = 0;
            }
            Qt::CheckState state = (static_cast<Qt::CheckState>(stateNum));
            //设置当前单元格的选中状态
            bool ok = model->setData(index,state, Qt::CheckStateRole);
            //设置model的值
            model->setData(index,QString::number(stateNum),Qt::EditRole);
            return ok;
        }
    }else{
        return QItemDelegate::editorEvent(event,model,option,index);
    }
    return false;
}
