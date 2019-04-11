#include "cheliangweixiudelegate.h"
#include "cheliangweixiuguanli.h"
#include <QDebug>
extern mymysql db;

cheliangweixiuDelegate::cheliangweixiuDelegate(cheliangweixiuguanli *clwx_wx, int gongyingshang_wx, int peijianxinghao_wx,QObject *parent):
    QItemDelegate(parent)
{

    this->clwx_dl = clwx_wx;
    this->gongyingshang_dl = gongyingshang_wx;
    this->peijianxinghao_dl = peijianxinghao_wx;


}
//weixiuName 维修厂商,peijianmode 配件型号 ,weixiuplate 维修厂地
//返回该QComboBox控件
QWidget *cheliangweixiuDelegate::createEditor(QWidget *parent,const QStyleOptionViewItem &option,const QModelIndex &index) const
{
    if(index.column() == gongyingshang_dl){
        QComboBox *editor = new QComboBox(parent);
        editor->setEditable(true);
        const char *weixiuchepaiSQL = "select Supplier from RepairingVehicleMulti group by Supplier;";
        db.sql_fillComboBoxItem(weixiuchepaiSQL,editor);
        connect(editor, SIGNAL(currentTextChanged(QString)),this, SLOT(commitEditor()));
        return editor;
    }else if(index.column() == peijianxinghao_dl){
        QComboBox *editor = new QComboBox(parent);
        editor->setEditable(true);
        QString weixiuchepaiSQL = QString("select Fitting_Mode from RepairingVehicleMulti where Supplier='%1' group by Fitting_Mode;").arg(index.model()->index(index.row(),0,QModelIndex()).data().toString().toStdString().data());
        db.sql_fillComboBoxItem(weixiuchepaiSQL.toStdString().data(),editor);

        connect(editor, SIGNAL(currentTextChanged(QString)),this, SLOT(commitEditor()));
        return editor;
    }else if(index.column() == 2 || index.column() == 3){
        QLineEdit *editor = new QLineEdit(parent);
        connect(editor, SIGNAL(textChanged(QString)),this, SLOT(commitEditor1()));
        return editor;
    }else{
        return QItemDelegate::createEditor(parent,option,index);
    }
}

//设置控件的值
void cheliangweixiuDelegate::setEditorData(QWidget *editor,const QModelIndex &index) const
{
    if(index.column() == gongyingshang_dl){
        //返回该索引的模型，继而返回该模型中此索引的编辑角色数据
        QString str = index.model()->data(index, Qt::EditRole).toString();
        //给控件赋值
        QComboBox *comBox = qobject_cast<QComboBox*>(editor);
        comBox->setCurrentText(str);
    }
    else{
        QItemDelegate::setEditorData(editor,index);
    }

}
//weixiuName 维修厂商,peijianmode 配件型号 ,weixiuplate 维修厂地
//设置model的值
void cheliangweixiuDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const
{
    if(index.column() == gongyingshang_dl){
        QComboBox *comBox = qobject_cast<QComboBox*>(editor);
        QString str = comBox->currentText();

        //设置原料规格
        QString fillSQL = QString("select weixiuName from weixiuchangshangSQL where weixiuName='%1';").arg(str);
        QString fillItem = db.sql_fetchrow_plus(fillSQL.toStdString().data(),0);

        //QString fillItem2 = db.sql_fetchrow_plus(fillSQL.toStdString().data(),1);
        qDebug()<<fillSQL<<fillItem;

        //设置模型的数据
        model->setData(index, str, Qt::EditRole);
        //model->setData(model->index(index.row(),1,QModelIndex()),fillItem,Qt::EditRole);
    } else if(index.column() == 2){
        QLineEdit *lineEdit = qobject_cast<QLineEdit*>(editor);
        QString str = lineEdit->text();
        QString str1 = model->data(model->index(index.row(),3)).toString();
        double total = str.toDouble()*str1.toDouble();

        //设置模型的数据
        model->setData(index, str, Qt::EditRole);
        if(total!=0){
            model->setData(model->index(index.row(),4,QModelIndex()),QString::number(total),Qt::EditRole);
        }
    }else if(index.column() == 3){
        QLineEdit *lineEdit = qobject_cast<QLineEdit*>(editor);
        QString str = lineEdit->text();
        QString str1 = model->data(model->index(index.row(),2)).toString();
        double total = str.toDouble()*str1.toDouble();

        //设置模型的数据
        model->setData(index, str, Qt::EditRole);
        if(total!=0){
            model->setData(model->index(index.row(),4,QModelIndex()),QString::number(total),Qt::EditRole);
        }
    }
    else{
        QItemDelegate::setModelData(editor,model,index);
    }

}

void cheliangweixiuDelegate::commitEditor()
{
    QComboBox *comBox = qobject_cast<QComboBox*>(sender());
    emit commitData(comBox); //提交该控件的值
}
void cheliangweixiuDelegate::commitEditor1()
{
    QLineEdit *lineEidt = qobject_cast<QLineEdit*>(sender());
    emit commitData(lineEidt); //提交该控件的值
}
