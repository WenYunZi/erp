#include "fucaikucundlg.h"
#include <QDebug>

extern mymysql db;

fucaikucunDlg::fucaikucunDlg(QWidget *parent) :
    QDialog(parent)
{
    SQL = "SELECT AuxiliaryNumber 辅材编号,MaterialName 辅材名称,Specifications 规格,Number 数量,\
            Company 单位,Price 单价,AmountOfMoney 金额,GenericClass 所属大类,SubordinateClass 所属小类\
            FROM AuxiliaryInventory where AuxiliaryNumber is null;";

    checkBox1 = new QCheckBox(tr("辅材名称"),this);
    checkBox2 = new QCheckBox(tr("类别"),this);
    comBox1 = new QComboBox(this);
    const char *fillSQL1 = "select MaterialName from AuxiliaryMaterialSetting group by MaterialName";
    db.sql_fillComboBoxItem(fillSQL1,comBox1);
    comBox2 = new QComboBox(this);
    const char *fillSQL2 = "select GenericClass from AuxiliaryMaterialSetting group by GenericClass";
    db.sql_fillComboBoxItem(fillSQL2,comBox2);
    chaxun = new QPushButton(tr("查询"),this);
    connect(chaxun,SIGNAL(clicked()),this,SLOT(on_chaxun()));

    view = new QTableView(this);
    db.showview(SQL,view,&model);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(checkBox1,0);
    hlayout->addWidget(comBox1,1);
    hlayout->addWidget(checkBox2,0);
    hlayout->addWidget(comBox2,1);
    hlayout->addWidget(chaxun,1);
    hlayout->addStretch(5);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(view);
}

void fucaikucunDlg::refresh()
{
    on_chaxun();
}

void fucaikucunDlg::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Escape:
           event->ignore();
           break;
        default:
           QDialog::keyPressEvent(event);
    }
}

void fucaikucunDlg::on_chaxun()
{
    QString fucainame,leibie;
    if(checkBox1->checkState() == 2){
        fucainame = QString(" and MaterialName='%1'").arg(comBox1->currentText());
    }
    if(checkBox2->checkState() == 2){
        leibie = QString(" and GenericClass='%2'").arg(comBox2->currentText());
    }

    QString deleteSQL = QString("delete from AuxiliaryInventory where Number='0';");
    db.sql_exec(deleteSQL.toStdString().data());

    QString searchSQL = QString("SELECT AuxiliaryNumber 辅材编号,MaterialName 辅材名称,Specifications 规格,Number 数量,Company 单位,round(Price,2) 单价,AmountOfMoney 金额,GenericClass 所属大类,SubordinateClass 所属小类 FROM AuxiliaryInventory where bak is null%1%2;").arg(fucainame,leibie);
    db.showview(searchSQL.toStdString().data(),view,&model);
}
