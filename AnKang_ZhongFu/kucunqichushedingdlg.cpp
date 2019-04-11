#include "kucunqichushedingdlg.h"

extern mymysql db;

kucunqichushedingDlg::kucunqichushedingDlg(QWidget *parent) :
    QDialog(parent)
{
    tabWidget = new QTabWidget(this);
    tabWidget->resize(1000,700);
    //lilunkucunqichusheding = new QWidget(this);
    cangweitiaozheng = new QWidget(this);
    cangweitiaozhengjilv = new QWidget(this);

    //creatTabPage1();
    creatTabPage2();
    creatTabPage3();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tabWidget);
}

kucunqichushedingDlg::~kucunqichushedingDlg()
{
    delete model;
    delete twomodel;
    delete threemodel;
    delete timer;
}

void kucunqichushedingDlg::refresh()
{
    //db.showview(SQL1,view,&model);
    db.showview(SQL2,twoview,&twomodel);
}

void kucunqichushedingDlg::keyPressEvent(QKeyEvent *event)
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

void kucunqichushedingDlg::creatTabPage1()
{
    SQL1 = "select MaterialNumber 原料编号,Material 原料名称,Specifications 规格,\
            FORMAT(Quantity,2) 数量（kg）,Time 截止日期 from TheoreticalInventorySetting;";

    QLabel *label1 = new QLabel(tr("原料编号"),this);
    label1->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label2 = new QLabel(tr("原料名称"),this);
    label2->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label3 = new QLabel(tr("数量（kg）"),this);
    label3->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

    lineEdit1 = new QLineEdit(this);
    lineEdit1->setEnabled(false);
    lineEdit1->setStyleSheet("color:black");
    lineEdit2 = new QLineEdit(this);
    lineEdit2->setEnabled(false);
    lineEdit2->setStyleSheet("color:black");
    lineEdit3 = new QLineEdit(this);

    tiaozhengqueren = new QPushButton(tr("调整确认"));
    tiaozhengqueren->setEnabled(false);
    tiaozhengqueren->setStyleSheet("color:black");
    connect(tiaozhengqueren,SIGNAL(clicked()),this,SLOT(on_tiaozhengqueren()));


    view = new QTableView(this);
    connect(view,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick()));
    db.showview(SQL1,view,&model);
    view->setColumnWidth(0,200);
    view->setColumnWidth(1,200);
    view->setColumnWidth(2,200);
    view->setColumnWidth(3,200);
    view->setColumnWidth(4,200);

    QGridLayout *layout1 = new QGridLayout;
    layout1->addWidget(label1,0,0);
    layout1->addWidget(lineEdit1,0,1);
    layout1->addWidget(label2,1,0);
    layout1->addWidget(lineEdit2,1,1);
    layout1->addWidget(label3,2,0);
    layout1->addWidget(lineEdit3,2,1);
    layout1->addWidget(tiaozhengqueren,2,2);
    layout1->setColumnStretch(0,0);
    layout1->setColumnStretch(1,1);
    layout1->setColumnStretch(2,1);
    layout1->setColumnStretch(3,0);
    layout1->setColumnStretch(4,2);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(layout1);
    vlayout->addWidget(view);


    lilunkucunqichusheding->setLayout(vlayout);
    tabWidget->addTab(lilunkucunqichusheding,tr("理论库存期初设定"));
}

void kucunqichushedingDlg::creatTabPage2()
{
    SQL2 = "select PositionNumber 仓位编号,PositionName 仓位名称,MaterialNumber 原料编号,\
            Material 原料名称,FORMAT(Quantity,2) 数量（kg）,DepartmentName 所属部门,Unit 机组,Factory 厂地,Time 截止日期, \
            Quantity from InventoryQueryTmp;";

    QLabel *label1 = new QLabel(tr("仓位编号"),this);
    label1->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label2 = new QLabel(tr("仓位名称"),this);
    label2->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label3 = new QLabel(tr("原料编号"),this);
    label3->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label4 = new QLabel(tr("原料名称"),this);
    label4->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label5 = new QLabel(tr("调整时间"),this);
    label5->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label6 = new QLabel(tr("账面数量"),this);
    label6->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label7 = new QLabel(tr("盘点数量"),this);
    label7->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

    twolineEdit1 = new QLineEdit(this);
    twolineEdit1->setEnabled(false);
    twolineEdit1->setStyleSheet("color:black");
    twolineEdit2 = new QLineEdit(this);
    twolineEdit2->setEnabled(false);
    twolineEdit2->setStyleSheet("color:black");
    twolineEdit3 = new QLineEdit(this);
    twolineEdit3->setEnabled(false);
    twolineEdit3->setStyleSheet("color:black");
    twolineEdit4 = new QLineEdit(this);
    twolineEdit4->setEnabled(false);
    twolineEdit4->setStyleSheet("color:black");
    twolineEdit6 = new QLineEdit(this);
    twolineEdit6->setEnabled(false);
    twolineEdit6->setStyleSheet("color:black");
    twolineEdit7 = new QLineEdit(this);

    twodatetime = new QLineEdit(this);
    twodatetime->setEnabled(false);
    twodatetime->setStyleSheet("color:black");

    timer = new QTimer(this);
    timer->setInterval(1000);
    timer->start();
    connect(timer,SIGNAL(timeout()),this,SLOT(setTimeDate()));


    twocangwei = new QPushButton(tr("仓位调整"),this);
    twocangwei->setEnabled(false);
    twocangwei->setStyleSheet("color:black");
    connect(twocangwei,SIGNAL(clicked()),this,SLOT(on_twocangwei()));

    twoview = new QTableView(this);
    connect(twoview,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick2()));
    db.showview(SQL2,twoview,&twomodel);
    twoview->setColumnHidden(9,true);

    QGridLayout *layout1 = new QGridLayout;
    layout1->addWidget(label1,0,0);
    layout1->addWidget(twolineEdit1,0,1);
    layout1->addWidget(label2,0,2);
    layout1->addWidget(twolineEdit2,0,3);
    layout1->addWidget(label3,0,4);
    layout1->addWidget(twolineEdit3,0,5);
    layout1->addWidget(label4,0,6);
    layout1->addWidget(twolineEdit4,0,7);
    layout1->addWidget(label5,1,0);
    layout1->addWidget(twodatetime,1,1);
    layout1->addWidget(label6,1,2);
    layout1->addWidget(twolineEdit6,1,3);
    layout1->addWidget(label7,1,4);
    layout1->addWidget(twolineEdit7,1,5);
    layout1->addWidget(twocangwei,1,6,1,2);
    layout1->setColumnStretch(0,0);
    layout1->setColumnStretch(1,1);
    layout1->setColumnStretch(2,0);
    layout1->setColumnStretch(3,1);
    layout1->setColumnStretch(4,0);
    layout1->setColumnStretch(5,1);
    layout1->setColumnStretch(6,0);
    layout1->setColumnStretch(7,1);
    layout1->setColumnStretch(8,2);


    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(layout1);
    vlayout->addWidget(twoview);



    cangweitiaozheng->setLayout(vlayout);

    tabWidget->addTab(cangweitiaozheng,tr("仓位调整"));
}

void kucunqichushedingDlg::creatTabPage3()
{
    SQL3 = "select PositionNumber 仓位编号,PositionName 仓位名称,MaterialNumber 原料编号,\
            Material 原料名称,FORMAT(BookQuantity,2) 账面数量,FORMAT(PhysicalInventory,2) 盘点数量,FORMAT(OverageNumber,2) 盘盈数量,\
            DepartmentName 部门名称,SubordinateUnit 所属机组,AdjustingTime 调整时间 from PositionAdjustmentRecord where \
            AdjustingTime='222';";

    QLabel *label1 = new QLabel(tr("调整时间"),this);
    label1->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label2 = new QLabel(tr("截至"),this);
    label1->setAlignment(Qt::AlignCenter);

    threedate1 = new QDateEdit(QDate::currentDate(),this);
    threedate1->setCalendarPopup(true);
    threedate2 = new QDateEdit(QDate::currentDate(),this);
    threedate2->setCalendarPopup(true);

    threechaxun = new QPushButton(tr("查询"),this);
    connect(threechaxun,SIGNAL(clicked()),this,SLOT(on_threechaxun()));

    threeview = new QTableView(this);
    db.showview(SQL3,threeview,&threemodel);
    threeview->setColumnWidth(9,150);

    QGridLayout *layout1 = new QGridLayout;
    layout1->addWidget(label1,0,0);
    layout1->addWidget(threedate1,0,1);
    layout1->addWidget(label2,0,2);
    layout1->addWidget(threedate2,0,3);
    layout1->addWidget(threechaxun,0,4);
    layout1->setColumnStretch(0,0);
    layout1->setColumnStretch(1,1);
    layout1->setColumnStretch(2,0);
    layout1->setColumnStretch(3,1);
    layout1->setColumnStretch(4,1);
    layout1->setColumnStretch(5,3);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(layout1);
    vlayout->addWidget(threeview);

    cangweitiaozhengjilv->setLayout(vlayout);
    tabWidget->addTab(cangweitiaozhengjilv,tr("仓位调整记录"));
}

void kucunqichushedingDlg::ShowSupplyclick()
{
    int row = view->currentIndex().row();

    lineEdit1->setText(model->item(row,0)->text());
    lineEdit2->setText(model->item(row,1)->text());
    lineEdit3->setText(model->item(row,3)->text());
    tiaozhengqueren->setEnabled(true);
}

void kucunqichushedingDlg::on_tiaozhengqueren()
{
    QString tiaozhengSQL = QString("update TheoreticalInventorySetting set Quantity='%1',Time='%2' where MaterialNumber='%3';")
            .arg(lineEdit3->text(),QDate::currentDate().toString("yyyy-MM-dd"),lineEdit1->text());
    int res = db.sql_exec(tiaozhengSQL.toStdString().data());
    if(res == 0){
        int row = view->currentIndex().row();
        double updateCount = lineEdit3->text().toDouble() - model->item(row,3)->text().toDouble();//计算理论库存
        QString updatelilunkucunSQL = QString("update TheoreticalInventoryTMP set Quantity=Quantity+'%1' where MaterialNumber='%2';")
                                .arg(QString::number(updateCount,'f',2),lineEdit1->text());
        int res = db.sql_exec(updatelilunkucunSQL.toStdString().data());
        if(res == 0){
            db.showview(SQL1,view,&model);//显示表格
            tiaozhengqueren->setEnabled(false);
            QMessageBox::information(this,tr("提示信息"),tr("调整成功"),0,0,0);
        }
    }
}

void kucunqichushedingDlg::on_twocangwei()
{
    if(twolineEdit7->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入盘点数量"),0,0,0);
        return;
    }
    QString cangweitiaozhengSQL = QString("update InventoryQueryTmp set Quantity='%1' where PositionNumber='%2';").arg(twolineEdit7->text(),twolineEdit1->text());
    db.sql_exec(cangweitiaozhengSQL.toStdString().data());
    db.showview(SQL2,twoview,&twomodel);

    double count = twolineEdit7->text().toDouble() - twolineEdit6->text().toDouble();
    QString cangweitiaozhengjilvSQL = QString("insert into PositionAdjustmentRecord (PositionNumber,PositionName,MaterialNumber,\
                                              Material,BookQuantity,PhysicalInventory,OverageNumber,DepartmentName,SubordinateUnit,\
                                              AdjustingTime) values ('%1','%2','%3','%4','%5','%6','%7','%8','%9','%10');")
                                .arg(twolineEdit1->text(),twolineEdit2->text(),twolineEdit3->text(),twolineEdit4->text(),
                                     twolineEdit6->text(),twolineEdit7->text(),QString::number(count,'f',2),DepartmentName,SubordinateUnit)
                                .arg(twodatetime->text());
    db.sql_exec(cangweitiaozhengjilvSQL.toStdString().data());

    QMessageBox::information(this,tr("提示信息"),tr("调整成功"),0,0,0);
    twocangwei->setEnabled(false);
    twolineEdit7->clear();
    twolineEdit1->clear();
    twolineEdit2->clear();
    twolineEdit3->clear();
    twolineEdit4->clear();
    twolineEdit6->clear();
}

void kucunqichushedingDlg::ShowSupplyclick2()
{
    twocangwei->setEnabled(true);
    twolineEdit7->clear();
    twolineEdit7->setFocus();
    int row = twoview->currentIndex().row();
    twolineEdit1->setText(twomodel->item(row,0)->text());
    twolineEdit2->setText(twomodel->item(row,1)->text());
    twolineEdit3->setText(twomodel->item(row,2)->text());
    twolineEdit4->setText(twomodel->item(row,3)->text());
    twolineEdit6->setText(twomodel->item(row,9)->text());
    DepartmentName = twomodel->item(row,5)->text();
    SubordinateUnit = twomodel->item(row,6)->text();
}

void kucunqichushedingDlg::setTimeDate()
{
    twodatetime->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
}

void kucunqichushedingDlg::on_threechaxun()
{
    QString threechaxunSQL = QString("select PositionNumber 仓位编号,PositionName 仓位名称,MaterialNumber 原料编号,Material 原料名称,\
                                     FORMAT(BookQuantity,2) 账面数量,FORMAT(PhysicalInventory,2) 盘点数量,FORMAT(OverageNumber,2) 盘盈数量,\
                                     DepartmentName 部门名称,SubordinateUnit 所属机组,AdjustingTime 调整时间 from PositionAdjustmentRecord \
                                     where AdjustingTime between '%1' and '%2';")
            .arg(threedate1->date().toString("yyyy-MM-dd"),threedate2->date().addDays(1).toString("yyyy-MM-dd"));
    db.showview(threechaxunSQL.toStdString().data(),threeview,&threemodel);
}
