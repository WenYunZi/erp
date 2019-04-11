#include "fucaichukudelegate.h"

extern mymysql db;

fucaichukuDelegate::fucaichukuDelegate(int column1, QObject *parent) :
    QItemDelegate(parent)
{
    this->column1 = column1;
}

//返回该QComboBox控件

QWidget *fucaichukuDelegate::createEditor(QWidget *parent,const QStyleOptionViewItem &option,const QModelIndex &index) const
{
    if(index.column() == column1){
        QComboBox *editor = new QComboBox(parent);
        QString searchSQL = QString("select MaterialName from AuxiliaryInventory group by MaterialName;");
        db.sql_fillComboBoxItem(searchSQL.toStdString().data(),editor);
        connect(editor, SIGNAL(currentTextChanged(QString)),this, SLOT(commitEditor()));
        return editor;
    }
    else if(index.column() == 0 || index.column() == 2 || index.column() == 3 || index.column() == 5 || index.column() == 7 || index.column() == 8){
        return NULL;
    }
    else if(index.column() == 4){
        QComboBox *editor = new QComboBox(parent);
        QString searchSQL = QString("select Specifications from AuxiliaryInventory where MaterialName='%1';")
                .arg(index.model()->data(index.model()->index(index.row(),1)).toString());
        db.sql_fillComboBoxItem(searchSQL.toStdString().data(),editor);
        connect(editor, SIGNAL(currentTextChanged(QString)),this, SLOT(commitEditor()));
        return editor;
    }
    else if(index.column() == 6){
        QLineEdit *editor = new QLineEdit(parent);
        connect(editor, SIGNAL(textChanged(QString)),this, SLOT(commitEditor1()));
        return editor;
    }
    else if(index.column() == 7){
        QLineEdit *editor = new QLineEdit(parent);
        connect(editor, SIGNAL(textChanged(QString)),this, SLOT(commitEditor1()));
        return editor;
    }
    else if(index.column() == 9){
        QComboBox *editor = new QComboBox(parent);
        QString searchSQL = QString("select SupplierName from AuxiliaryMaterialSupplier;");
        db.sql_fillComboBoxItem(searchSQL.toStdString().data(),editor);
        connect(editor, SIGNAL(currentTextChanged(QString)),this, SLOT(commitEditor()));
        return editor;
    }
    else{
        return QItemDelegate::createEditor(parent,option,index);
    }
}

//设置控件的值
void fucaichukuDelegate::setEditorData(QWidget *editor,const QModelIndex &index) const
{
    if(index.column() == column1){
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
void fucaichukuDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const
{
    if(index.column() == column1){
        QComboBox *comBox = qobject_cast<QComboBox*>(editor);
        QString str = comBox->currentText();


        QString fillSQL = QString("select AuxiliaryNumber,GenericClass,SubordinateClass,MaterialSpecifications,Company from AuxiliaryMaterialSetting where MaterialName='%1';").arg(str);
        //设置辅材编号
        QString fillItem1 = db.sql_fetchrow_plus(fillSQL.toStdString().data(),0);
        //设置所属大类
        QString fillItem2 = db.sql_fetchrow_plus(fillSQL.toStdString().data(),1);
        //设置所属小类
        QString fillItem3 = db.sql_fetchrow_plus(fillSQL.toStdString().data(),2);
        //设置规格
        QString fillItem4 = db.sql_fetchrow_plus(fillSQL.toStdString().data(),3);
        //设置单位
        QString fillItem5 = db.sql_fetchrow_plus(fillSQL.toStdString().data(),4);

        QString fillSQL2 = QString("select round(Price,2) from AuxiliaryInventory where MaterialName='%1';").arg(str);
        //设置单价
        QString fillItem6 = db.sql_fetchrow_plus(fillSQL2.toStdString().data(),0);

        //设置模型的数据
        model->setData(index, str, Qt::EditRole);
        model->setData(model->index(index.row(),0,QModelIndex()),fillItem1,Qt::EditRole);
        model->setData(model->index(index.row(),2,QModelIndex()),fillItem2,Qt::EditRole);
        model->setData(model->index(index.row(),3,QModelIndex()),fillItem3,Qt::EditRole);
        model->setData(model->index(index.row(),4,QModelIndex()),fillItem4,Qt::EditRole);
        model->setData(model->index(index.row(),5,QModelIndex()),fillItem5,Qt::EditRole);
        model->setData(model->index(index.row(),7,QModelIndex()),fillItem6,Qt::EditRole);
    }
    else if(index.column() == 4){
        QComboBox *comBox = qobject_cast<QComboBox*>(editor);
        QString str = comBox->currentText();

        QString fillSQL = QString("select AuxiliaryNumber from AuxiliaryMaterialSetting where MaterialName='%1' and MaterialSpecifications='%2';")
                        .arg(model->data(model->index(index.row(),1),Qt::EditRole).toString(),str);
        //设置辅材编号
        QString fillItem1 = db.sql_fetchrow_plus(fillSQL.toStdString().data(),0);

        //设置模型的数据
        model->setData(index, str, Qt::EditRole);
        model->setData(model->index(index.row(),0,QModelIndex()),fillItem1,Qt::EditRole);
    }
    else if(index.column() == 6){
        QLineEdit *lineEdit = qobject_cast<QLineEdit*>(editor);
        QString str = lineEdit->text();
        QString str1 = model->data(model->index(index.row(),7)).toString();
        double total = str.toDouble()*str1.toDouble();

        //设置模型的数据
        model->setData(index, str, Qt::EditRole);
        if(total!=0){
            model->setData(model->index(index.row(),8,QModelIndex()),QString::number(total),Qt::EditRole);
        }
    }
    else if(index.column() == 7){
        QLineEdit *lineEdit = qobject_cast<QLineEdit*>(editor);
        QString str = lineEdit->text();
        QString str1 = model->data(model->index(index.row(),6)).toString();
        double total = str.toDouble()*str1.toDouble();

        //设置模型的数据
        model->setData(index, str, Qt::EditRole);
        if(total!=0){
            model->setData(model->index(index.row(),8,QModelIndex()),QString::number(total),Qt::EditRole);
        }
    }
    else{
        QItemDelegate::setModelData(editor,model,index);
    }

}

void fucaichukuDelegate::commitEditor()
{
    QComboBox *comBox = qobject_cast<QComboBox*>(sender());
    emit commitData(comBox); //提交该控件的值
}

void fucaichukuDelegate::commitEditor1()
{
    QLineEdit *lineEidt = qobject_cast<QLineEdit*>(sender());
    emit commitData(lineEidt); //提交该控件的值
}
