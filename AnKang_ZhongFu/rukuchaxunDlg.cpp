#include "rukuchaxunDlg.h"

extern mymysql db;

rukuchaxunDlg::rukuchaxunDlg(QWidget *parent) :
    QDialog(parent)
{
    tabWidget = new QTabWidget;
    lilunkucun = new QWidget;
    kucunchaxun = new QWidget;
    jiecundianchaxun = new QWidget;
    lishikucunchaxun = new QWidget;

    //creatTabPage1();
    creatTabPage2();
    creatTabPage3();
    creatTabPage4();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tabWidget);
}

rukuchaxunDlg::~rukuchaxunDlg()
{
    delete model;
    delete twomodel;
    delete threemodel;
    delete fourmodel;
}

void rukuchaxunDlg::refresh()
{

}

void rukuchaxunDlg::keyPressEvent(QKeyEvent *event)
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

void rukuchaxunDlg::creatTabPage1()
{
    SQL1 = "select MaterialNumber 原料编号,Material 原料名称,Specifications 规格,FORMAT(Quantity,2) 数量（kg）,Time 截止日期 from TheoreticalInventoryTMP;";

    QLabel *label1 = new QLabel(tr("查询时间至"),this);
    label1->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

    datetime = new QDateTimeEdit(QDateTime::currentDateTime(),this);
    datetime->setDisplayFormat("yyyy-MM-dd");
    datetime->setCalendarPopup(true);

    chaxun = new QPushButton(tr("查询"),this);
    connect(chaxun,SIGNAL(clicked()),this,SLOT(on_chaxun()));

    view = new QTableView(this);
    db.showview(SQL1,view,&model);
    view->setColumnWidth(0,200);
    view->setColumnWidth(1,200);
    view->setColumnWidth(2,200);
    view->setColumnWidth(3,200);
    view->setColumnWidth(4,200);

    QHBoxLayout *layout1 = new QHBoxLayout;
    layout1->addWidget(label1,0);
    layout1->addWidget(datetime,1);
    layout1->addWidget(chaxun,1);
    layout1->addStretch(5);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addLayout(layout1);
    vlayout->addWidget(view);

    lilunkucun->setLayout(vlayout);
    tabWidget->addTab(lilunkucun,tr("理论库存"));
}

void rukuchaxunDlg::creatTabPage2()
{
    SQL2 = "select PositionNumber 仓位编号,PositionName 仓位名称,MaterialNumber 原料编号,Material 原料名称,FORMAT(Quantity,2) 数量（kg）,DepartmentName 所属部门,\
            Unit 机组,Factory 厂地,Time 截止日期 from InventoryQueryTmp;";

    twoshuaxin = new QPushButton(tr("刷新"),this);
    connect(twoshuaxin,SIGNAL(clicked()),this,SLOT(on_twoshuaxin()));

    twobaocun = new QPushButton(tr("保存库存结存"),this);
    twobaocun->setHidden(true);
    connect(twobaocun,SIGNAL(clicked()),this,SLOT(on_twobaocun()));

    twoqitaxinxi = new QPushButton(tr("其他信息"),this);
    connect(twoqitaxinxi,SIGNAL(clicked()),this,SLOT(on_twoqitaxinxi()));

    twoCombox = new QComboBox(this);
    const char *fillSQL1 = "select PlantName from FactorySetting;";
    db.sql_fillComboBoxItem(fillSQL1,twoCombox);
    twoCombox->setCurrentIndex(1);

    twoview = new QTableView(this);
    twoview->setHidden(true);
    db.showview(SQL2,twoview,&twomodel);//显示表格

    QHBoxLayout *layout1 = new QHBoxLayout;
    layout1->addWidget(twoqitaxinxi,1);
    layout1->addWidget(twoshuaxin,1);
    layout1->addWidget(twoCombox,1);
    layout1->addStretch(5);

    int warehouse_num;
    //SQL字段顺序要求：仓位名称、原料名称、库存、最大库存
    QString SQL = QString("SELECT A.PositionName, A.Material,Quantity,InventoryCeiling,FORMAT(Quantity, 2),Type,A.unit\
            FROM InventoryQueryTmp A LEFT JOIN (SELECT InventoryCeiling,PositionName FROM PositionSetting) B \
            ON (A.PositionName = B.PositionName) LEFT JOIN (SELECT Type,Material FROM MaterialSetting ) C \
            ON (A.Material = C.Material) WHERE (Type='水泥' OR Type='矿粉' OR Type='粉煤灰' OR Type='减水剂' OR Type='外加剂' OR \
            Type='膨胀剂') and A.Factory='%1' ORDER BY A.PositionName;")
            .arg(twoCombox->currentText());
    db.newWareHouseWidget(SQL,wareHouseList,&warehouse_num,this);

    twolayout = new QGridLayout;
    twolayout->setColumnStretch(0,1);
    twolayout->setColumnStretch(1,1);
    twolayout->setColumnStretch(2,1);
    twolayout->setColumnStretch(3,1);
    twolayout->setColumnStretch(4,1);
    twolayout->setColumnStretch(5,1);
    twolayout->setColumnStretch(6,1);
    twolayout->setColumnStretch(7,1);
    twolayout->setColumnStretch(8,1);
    twolayout->setRowStretch(0,1);
    twolayout->setRowStretch(1,1);
    twolayout->setRowStretch(2,1);
    twolayout->setRowStretch(3,1);

    int j=0,k=0,m=0,n=0;
    for(int i = 0; i < warehouse_num; i++){
        if(wareHouseList[i]->Unit == "1#机组"){
            twolayout->addWidget(wareHouseList[i],0,j);
            j++;
        }
        else if(wareHouseList[i]->Unit == "2#机组"){
            twolayout->addWidget(wareHouseList[i],1,k);
            k++;
        }else if(wareHouseList[i]->Unit == "3#机组"){
            twolayout->addWidget(wareHouseList[i],2,m);
            m++;
        }else if(wareHouseList[i]->Unit == "4#机组"){
            twolayout->addWidget(wareHouseList[i],3,n);
            n++;
        }
    }

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addLayout(layout1);
    vlayout->addLayout(twolayout);

    kucunchaxun->setLayout(vlayout);
    tabWidget->addTab(kucunchaxun,tr("库存查询"));
}

void rukuchaxunDlg::creatTabPage3()
{
    SQL3 = "select Time 结存日期,Date 结存时间,PositionName 仓位名称,Material 原料名称,\
            FORMAT(Quantity,2) 库存（kg）,Unit 机组,Factory 厂地 from JieCunDianQuery where Time='222';";

    QLabel *label1 = new QLabel(tr("--"),this);
    label1->setAlignment(Qt::AlignCenter);
    threecheckBox1 = new QCheckBox(tr("仓位名称"),this);

    threedate1 = new QDateEdit(QDate::currentDate(),this);
    threedate1->setCalendarPopup(true);
    threedate2 = new QDateEdit(QDate::currentDate(),this);
    threedate2->setCalendarPopup(true);

    threecombo1 = new QComboBox(this);
    const char *fillThreeCombo1SQL = "select PositionName from PositionSetting;";
    db.sql_fillComboBoxItem(fillThreeCombo1SQL,threecombo1);

    threechaxun = new QPushButton(tr("查询"),this);
    connect(threechaxun,SIGNAL(clicked()),this,SLOT(on_threechaxun()));

    threeview = new QTableView(this);
    db.showview(SQL3,threeview,&threemodel);

    QGridLayout *layout1 = new QGridLayout;
    layout1->addWidget(threedate1,0,0);
    layout1->addWidget(label1,0,1);
    layout1->addWidget(threedate2,0,2);
    layout1->addWidget(threecheckBox1,0,3);
    layout1->addWidget(threecombo1,0,4);
    layout1->addWidget(threechaxun,0,5);
    layout1->setColumnStretch(0,1);
    layout1->setColumnStretch(1,0);
    layout1->setColumnStretch(2,1);
    layout1->setColumnStretch(3,0);
    layout1->setColumnStretch(4,1);
    layout1->setColumnStretch(5,1);
    layout1->setColumnStretch(6,4);


    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addLayout(layout1);
    vlayout->addWidget(threeview);


    jiecundianchaxun->setLayout(vlayout);

    tabWidget->addTab(jiecundianchaxun,tr("结存点查询"));
}

void rukuchaxunDlg::creatTabPage4()
{
    SQL4 = "select PositionNumber 仓位编号,PositionName 仓位名称,MaterialNumber 原料编号,\
            Material 原料名称,FORMAT(Quantity,2) 数量（kg）,DepartmentName 所属部门,Unit 机组,Factory 厂地,Time 截止日期 \
            from InventoryQuery where Time='222';";

    fourdatetime = new QDateTimeEdit(QDateTime::currentDateTime().addDays(-1),this);
    fourdatetime->setDisplayFormat("yyyy-MM-dd");
    fourdatetime->setCalendarPopup(true);
    fourdatetime->setMaximumDate(QDate::currentDate().addDays(-1));

    fourchaxun = new QPushButton(tr("查询"),this);
    connect(fourchaxun,SIGNAL(clicked()),this,SLOT(on_fourchaxun()));

    fourview = new QTableView(this);
    db.showview(SQL4,fourview,&fourmodel);

    QGridLayout *layout1 = new QGridLayout;
    layout1->addWidget(fourdatetime,0,0);
    layout1->addWidget(fourchaxun,0,1);
    layout1->setColumnStretch(0,1);
    layout1->setColumnStretch(1,1);
    layout1->setColumnStretch(2,4);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addLayout(layout1);
    vlayout->addWidget(fourview);

    lishikucunchaxun->setLayout(vlayout);
    tabWidget->addTab(lishikucunchaxun,tr("历史库存查询"));
}

void rukuchaxunDlg::on_chaxun()
{
    if(datetime->date().toString("yyyy-MM-dd") != date.currentDate().toString("yyyy-MM-dd")){
        QString chaxunAll = QString("select MaterialNumber 原料编号,Material 原料名称,Specifications 规格,FORMAT(Quantity,2) 数量（kg）,\
                                    Time 截止日期 from allTheoreticalInventory where Time='%1';").arg(datetime->date().toString("yyyy-MM-dd"));
        db.showview(chaxunAll.toStdString().data(),view,&model);
    }else{
        db.showview(SQL1,view,&model);
    }
}

void rukuchaxunDlg::on_twoshuaxin()
{
    int warehouse_num;

    QString SQL = QString("SELECT A.PositionName, A.Material,A.Quantity,B.InventoryCeiling,FORMAT(A.Quantity, 2),C.Type,A.unit\
                      FROM InventoryQueryTmp A LEFT JOIN (SELECT InventoryCeiling, PositionName FROM PositionSetting) B ON (\
                      A.PositionName = B.PositionName)LEFT JOIN (\
                      SELECT Type, Material FROM MaterialSetting) C ON (A.Material = C.Material)\
                      WHERE (   C.Type = '水泥'\
                                OR C.Type = '矿粉'\
                                OR C.Type = '粉煤灰'\
                                OR C.Type = '减水剂'\
                                OR C.Type = '外加剂'\
                                OR C.Type = '膨胀剂') and A.Factory='%1' ORDER BY A.PositionName")
            .arg(twoCombox->currentText());
    db.newWareHouseWidget(SQL,wareHouseList,&warehouse_num,this);

    int j=0,k=0,m=0,n=0;
    for(int i = 0; i < warehouse_num; i++){
        if(wareHouseList[i]->Unit == "1#机组"){
            twolayout->addWidget(wareHouseList[i],0,j);
            j++;
        }
        else if(wareHouseList[i]->Unit == "2#机组"){
            twolayout->addWidget(wareHouseList[i],1,k);
            k++;
        }else if(wareHouseList[i]->Unit == "3#机组"){
            twolayout->addWidget(wareHouseList[i],2,m);
            m++;
        }else if(wareHouseList[i]->Unit == "4#机组"){
            twolayout->addWidget(wareHouseList[i],3,n);
            n++;
        }
    }
}

void rukuchaxunDlg::on_twobaocun()//保存库存结构
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

void rukuchaxunDlg::on_twoqitaxinxi()
{
    kucunxinxiDlg *kucunDlg = new kucunxinxiDlg(this);
    kucunDlg->show();
}

void rukuchaxunDlg::on_threechaxun()//结存点查询
{
    QString PositionName;
    if(threecheckBox1->checkState() == 2){
        PositionName = QString(" and PositionName='%1'").arg(threecombo1->currentText());
    }
    QString threechaxunSQL = QString("select Time 结存日期,Date 结存时间,PositionName 仓位名称,Material 原料名称,\
                                     FORMAT(Quantity,2) 库存（kg）,Unit 机组,Factory 厂地 from JieCunDianQuery \
                                     where Time between '%1' and '%2' %3;")
                        .arg(threedate1->date().toString("yyyy-MM-dd"),threedate2->date().toString("yyyy-MM-dd"),PositionName);
    db.showview(threechaxunSQL.toStdString().data(),threeview,&threemodel);
}

void rukuchaxunDlg::on_fourchaxun()//历史库存查询
{
    QString fourchaxunSQL = QString("select PositionNumber 仓位编号,PositionName 仓位名称,MaterialNumber 原料编号,Material 原料名称,\
                                    FORMAT(Quantity,2) 数量（kg）,DepartmentName 所属部门,Unit 机组,Factory 厂地,Time 截止日期 \
                                    from InventoryQuery where Time='%1';").arg(fourdatetime->date().toString("yyyy-MM-dd"));
    db.showview(fourchaxunSQL.toStdString().data(),fourview,&fourmodel);
}
