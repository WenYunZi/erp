#include "kucunxinxidlg.h"

extern mymysql db;

kucunxinxiDlg::kucunxinxiDlg(QWidget *parent) :
    QDialog(parent)
{
    QDesktopWidget *desktop = QApplication::desktop();
    this->setObjectName(tr("kucunxinxiDlg"));
    this->setStyleSheet("QDialog[objectName=\"kucunxinxiDlg\"]{border: 3px solid rgb(6,17,153);}");
    this->setWindowFlags(Qt::Popup);
    this->setFixedSize(1000,600);
    this->move(desktop->width()/2 - this->width()/2,desktop->height()/2 - this->height()/2);

    SQL = "select PositionNumber 仓位编号,PositionName 仓位名称,MaterialNumber 原料编号,Material 原料名称,FORMAT(Quantity,2) 数量（kg）,\
            DepartmentName 所属部门,Unit 机组,Factory 厂地,Time 截止日期 from InventoryQueryTmp;";

    shuaxinBtn = new QPushButton("刷新",this);
    connect(shuaxinBtn,SIGNAL(clicked()),this,SLOT(on_shuaxinBtn()));
    saveKuCunBtn = new QPushButton("保存库存结构",this);
    connect(saveKuCunBtn,SIGNAL(clicked()),this,SLOT(on_saveKuCunBtn()));

    view = new QTableView(this);
    db.showview(SQL,view,&model);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(shuaxinBtn,1);
    hlayout->addWidget(saveKuCunBtn,1);
    hlayout->addStretch(4);
    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(view);
}

void kucunxinxiDlg::on_shuaxinBtn()
{
    db.showview(SQL,view,&model);//显示表格
}

void kucunxinxiDlg::on_saveKuCunBtn()
{
    int res = QMessageBox::question(this,tr("提示信息"),tr("保存库存结存？"),QMessageBox::Yes,QMessageBox::No);
    if(res == QMessageBox::Yes){
        //将临时库存表中的信息拷贝至实际临时库存节点表中
        const char *copyTmpTableToTmp1TableSQL = "insert into JieCunDianQueryTmp(PositionNumber,PositionName,MaterialNumber,\
                                        Material,Quantity,DepartmentName,Unit,Factory,Time) (select * from InventoryQueryTmp);";
        db.sql_exec(copyTmpTableToTmp1TableSQL);
        //将临时库存节点表中的时间更新至当前时间
        QString updateTimeSQL = QString("update JieCunDianQueryTmp set Date='%1';").arg(QTime::currentTime().toString("hh:mm"));
        db.sql_exec(updateTimeSQL.toStdString().data());
        //将临时库存节点表中的信息拷贝至实际库存节点表中
        const char *copySQL = "insert into JieCunDianQuery (select * from JieCunDianQueryTmp);";
        db.sql_exec(copySQL);
        //清空临时库存节点表中的信息
        const char *clearSQL = "delete from JieCunDianQueryTmp;";
        db.sql_exec(clearSQL);
    }else{
        return;
    }
}
