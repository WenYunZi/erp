#include "mydelegate.h"
#include <QDebug>

extern mymysql db;

mydelegate::mydelegate(int materialColumn, int unitMaterialColumn, const char *unitNo, QObject *parent) :
    QItemDelegate(parent)
{
    this->materialColumn = materialColumn;
    this->unitMaterialColumn = unitMaterialColumn;
    if(unitNo){
        this->unitNo = (char *)unitNo;
    }
}

//返回该QComboBox控件
QWidget *mydelegate::createEditor(QWidget *parent,const QStyleOptionViewItem &option,\
                                  const QModelIndex &index) const
{
    if(index.column() == materialColumn){
        QComboBox *editor = new QComboBox(parent);
        const char *fillSQL = "select Material from MaterialSetting;";
        db.sql_fillComboBoxItem(fillSQL,editor);
        connect(editor, SIGNAL(currentTextChanged(QString)),this, SLOT(commitEditor()));
        return editor;
    }
    if(this->unitNo){
        if(index.column() == unitMaterialColumn){
                QComboBox *editor = new QComboBox(parent);
                QString fillSQL = QString("select UnitMaterial from UnitMaterialCorrespondsToERPMaterial where ProductionUnit='%1' \
                                          and ERPmaterial='%2';").arg(unitNo,index.model()->index(index.row(),0,QModelIndex()).data().toString().toStdString().data());
                db.sql_fillComboBoxItem(fillSQL.toStdString().data(),editor);
                connect(editor, SIGNAL(currentTextChanged(QString)),this, SLOT(commitEditor()));
                return editor;
            }
        else{
            return QItemDelegate::createEditor(parent,option,index);
        }
    }
    else{
        return QItemDelegate::createEditor(parent,option,index);
    }
}

//设置控件的值
void mydelegate::setEditorData(QWidget *editor,const QModelIndex &index) const
{
    if(index.column() == materialColumn){
        //返回该索引的模型，继而返回该模型中此索引的编辑角色数据
        QString str = index.model()->data(index, Qt::EditRole).toString();
        //给控件赋值
        QComboBox *comBox = qobject_cast<QComboBox*>(editor);
        comBox->setCurrentText(str);
    }else{
        QItemDelegate::setEditorData(editor,index);
    }

}

//设置model的值
void mydelegate::setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const
{
    if(index.column() == materialColumn){
        QComboBox *comBox = qobject_cast<QComboBox*>(editor);
        QString str = comBox->currentText();

        //设置原料类型，原料价格
        QString fillSQL = QString("select Type,UnitPrice from MaterialSetting where Material='%1';").arg(str);
        QString fillItem = db.sql_fetchrow_plus(fillSQL.toStdString().data(),0);
        QString fillJiage = db.sql_fetchrow_plus(fillSQL.toStdString().data(),1);

        //设置模型的数据
        model->setData(index, str, Qt::EditRole);
        model->setData(model->index(index.row(),2,QModelIndex()),fillItem,Qt::EditRole);
        model->setData(model->index(index.row(),3,QModelIndex()),fillJiage,Qt::EditRole);
    }
    if(index.column() == unitMaterialColumn){
        QComboBox *comBox = qobject_cast<QComboBox*>(editor);
        QString str = comBox->currentText();

        //设置对应字段
        QString fillSQL2 = QString("select CorrespondingField from UnitMaterialSetting where SubordinateUnit='%1' and Material='%2';").arg(this->unitNo,str);
        QString fillItem2 = db.sql_fetchrow_plus(fillSQL2.toStdString().data(),0);

        //设置模型的数据
        model->setData(index, str, Qt::EditRole);
        model->setData(model->index(index.row(),5,QModelIndex()),fillItem2,Qt::EditRole);
    }

    else{
        QItemDelegate::setModelData(editor,model,index);
    }

}

void mydelegate::commitEditor()
{
    QComboBox *comBox = qobject_cast<QComboBox*>(sender());
    emit commitData(comBox); //提交该控件的值
}
