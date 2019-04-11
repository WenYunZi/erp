#include "caigouhetongshenhedelegate.h"
#include <QDebug>

extern mymysql db;

caigouhetongshenhedelegate::caigouhetongshenhedelegate(caigouhetongshenhebiangengDlg *cghtsh_window, int materialColumn, QObject *parent) :
    QItemDelegate(parent)
{
    this->cghtsh = cghtsh_window;
    this->materialColumn = materialColumn;
}

//返回该QComboBox控件
QWidget *caigouhetongshenhedelegate::createEditor(QWidget *parent,const QStyleOptionViewItem &option,const QModelIndex &index) const
{
    if(index.column() == materialColumn){
        QComboBox *editor = new QComboBox(parent);
        editor->setView(new QListView());
        editor->addItem(tr(""));
        QString searchSQL = QString("select MainMaterial from SupplierFile where Name='%1';").arg(cghtsh->combox->currentText());
        QString materName = db.sql_fetchrow_plus(searchSQL.toStdString().data(),0);
        int count = materName.count(" ");
        for(int i = 0; i < count; i++){
            editor->addItem(materName.section(" ",i,i));
        }
        connect(editor, SIGNAL(currentTextChanged(QString)),this, SLOT(commitEditor()));
        return editor;
    }
    else if(index.column() == 1 || index.column() == 2){
        return NULL;
    }
    else{
        return QItemDelegate::createEditor(parent,option,index);
    }
}

//设置控件的值
void caigouhetongshenhedelegate::setEditorData(QWidget *editor,const QModelIndex &index) const
{
    if(index.column() == materialColumn){
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

//设置model的值
void caigouhetongshenhedelegate::setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const
{
    if(index.column() == materialColumn){
        QComboBox *comBox = qobject_cast<QComboBox*>(editor);
        QString str = comBox->currentText();

        //设置原料规格
        QString fillSQL = QString("select SpecificationModel,ID from MaterialSetting where Material='%1';").arg(str);
        QString fillItem = db.sql_fetchrow_plus(fillSQL.toStdString().data(),0);
        QString fillItem2 = db.sql_fetchrow_plus(fillSQL.toStdString().data(),1);
        qDebug()<<fillSQL<<fillItem<<fillItem2;

        //设置模型的数据
        model->setData(index, str, Qt::EditRole);
        model->setData(model->index(index.row(),1,QModelIndex()),fillItem,Qt::EditRole);
        model->setData(model->index(index.row(),2,QModelIndex()),"吨",Qt::EditRole);
        model->setData(model->index(index.row(),6,QModelIndex()),fillItem2,Qt::EditRole);
    }else{
        QItemDelegate::setModelData(editor,model,index);
    }

}

void caigouhetongshenhedelegate::commitEditor()
{
    QComboBox *comBox = qobject_cast<QComboBox*>(sender());
    emit commitData(comBox); //提交该控件的值
}
