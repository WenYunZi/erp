#include "fahuoquerendlg.h"

extern mymysql db;
extern QString userName;
extern pubfunc pub;
extern QString PRODUCTUNITNO;
extern myTCPsocket *sockClient;

fahuoquerenDlg::fahuoquerenDlg(QWidget *parent) :
    QDialog(parent)
{
    m_report = new QAxObject(this);//报表主体对象
    m_report->setControl("{4764040E-4222-4DEC-9F2E-82D46E212B3A}");

    UnitNo = QString("%1#机组").arg(PRODUCTUNITNO);
    tabWidget   = new QTabWidget(this);
    tabWidget->resize(1000,700);
    fahuoqueren = new QWidget(this);
    fahuochaxun = new QWidget(this);


    library = new QLibrary("MyReportDll",this);

    creatTabPage1();
    creatTabPage2();


    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tabWidget);
}

fahuoquerenDlg::~fahuoquerenDlg()
{
    delete model;
    delete twomodel;
}

void fahuoquerenDlg::refresh()
{
    db.showview(SQL1.toStdString().data(),view,&model);
}

void fahuoquerenDlg::keyPressEvent(QKeyEvent *event)
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

void fahuoquerenDlg::creatTabPage1()
{
    if(PRODUCTUNITNO.isEmpty()){
        SQL1 = QString("select RecordNumber 发货序号,FaHuoCustomer 发货客户,Engineering 工程,DeliveryVehicle 送货车辆,Driver 司机,ShippingVolume 发货方量,ActualProductionVolume 实际生产方量,\
                       RemainingMaterial 剩料,VolumeMortar 砂浆方量,CumulativeNumber 累计车次,CumulativeVolume 累计方量,PouringPosition 浇筑部位,PouringMethod 浇筑方法,StrengthGrade 强度等级,\
                       TemplateName 配合比模板名称,ProductionTime 生产时间,Slump 坍落度,Unit 机组,InformPeople 通知人,Capacity 容重,TaskList 任务单,ContractNumber 合同编号,ConstructionSite 工程地址 from ProductionNotice \
                       where WhetherDelivery='否';");
    }
    else{
        SQL1 = QString("select RecordNumber 发货序号,FaHuoCustomer 发货客户,Engineering 工程,DeliveryVehicle 送货车辆,Driver 司机,ShippingVolume 发货方量,ActualProductionVolume 实际生产方量,\
                       RemainingMaterial 剩料,VolumeMortar 砂浆方量,CumulativeNumber 累计车次,CumulativeVolume 累计方量,PouringPosition 浇筑部位,PouringMethod 浇筑方法,StrengthGrade 强度等级,\
                       TemplateName 配合比模板名称,ProductionTime 生产时间,Slump 坍落度,Unit 机组,InformPeople 通知人,Capacity 容重,TaskList 任务单,ContractNumber 合同编号,ConstructionSite 工程地址 from ProductionNotice \
                       where WhetherDelivery='否' and Unit=%1;").arg(UnitNo);
    }

    QLabel *CustomerLabel  = new QLabel(tr("客户名称"),this);
    CustomerLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *StrengthGradeLabel  = new QLabel(tr("强度等级"),this);
    StrengthGradeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *VehicleLabel  = new QLabel(tr("送货车辆"),this);
    VehicleLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *EngineerNameLabel  = new QLabel(tr("工程名称"),this);
    EngineerNameLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *PourPositionLabel  = new QLabel(tr("浇筑部位"),this);
    PourPositionLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *DriverLabel  = new QLabel(tr("司机"),this);
    DriverLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *PourMethodLabel  = new QLabel(tr("浇筑方法"),this);
    PourMethodLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *ContactLabel  = new QLabel(tr("联系人"),this);
    ContactLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *TaskListLabel = new QLabel(tr("任务单"),this);
    TaskListLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *ConstructionSiteLabel = new QLabel(tr("工程地址"),this);
    ConstructionSiteLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *SlumpLabel = new QLabel(tr("坍落度"),this);
    SlumpLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *TelephoneLabel = new QLabel(tr("联系电话"),this);
    TelephoneLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *OutBoundTimeLabel = new QLabel(tr("出站时间"),this);
    OutBoundTimeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *ShippingVolumeLabel = new QLabel(tr("本车方量"),this);
    ShippingVolumeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *OperatorLabel = new QLabel(tr("操作人"),this);
    OperatorLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *TemplateLabel = new QLabel(tr("配合比名称"),this);
    TemplateLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *UnitNoLabel = new QLabel(tr("机组"),this);
    UnitNoLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *RemainMatLabel = new QLabel(tr("剩料"),this);
    RemainMatLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *UnitWeightLabel = new QLabel(tr("容重"),this);
    UnitWeightLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *CumulationNumberLabel = new QLabel(tr("累计车次"),this);
    CumulationNumberLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *CompleteVolumeLabel = new QLabel(tr("已完成方量"),this);
    CompleteVolumeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

    QLabel *BeizhuLabel = new QLabel(tr("备注"),this);
    BeizhuLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

    QLabel *InstructLabel1 = new QLabel(tr("生产任务安排"),this);
    InstructLabel1->setAlignment(Qt::AlignLeft|Qt::AlignBottom);
    QLabel *WarningLabel = new QLabel(tr("如果要打印的出车单记录不显示，请点击刷新按钮"),this);
    WarningLabel->setAlignment(Qt::AlignLeft|Qt::AlignBottom);
    WarningLabel->setStyleSheet("color:red");


    OutBoundTime = new QDateTimeEdit(QDateTime::currentDateTime(),this);
    OutBoundTime->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
    OutBoundTime->setCalendarPopup(true);

    CustomerLineEdit  = new QLineEdit(this);
//    CustomerLineEdit->setEnabled(false);
    CustomerLineEdit->setStyleSheet("color:black");
    StrengthGradeLineEdit  = new QLineEdit(this);
//    StrengthGradeLineEdit->setEnabled(false);
    StrengthGradeLineEdit->setStyleSheet("color:black");

    EngineerNameLineEdit  = new QLineEdit(this);
//    EngineerNameLineEdit->setEnabled(false);
    EngineerNameLineEdit->setStyleSheet("color:black");
    PourPositionLineEdit  = new QLineEdit(this);
//    PourPositionLineEdit->setEnabled(false);
    PourPositionLineEdit->setStyleSheet("color:black");


    ContactLineEdit  = new QLineEdit(this);
//    ContactLineEdit->setEnabled(false);
    ContactLineEdit->setStyleSheet("color:black");
    TaskListLineEdit = new QLineEdit(this);
//    TaskListLineEdit->setEnabled(false);
    TaskListLineEdit->setStyleSheet("color:red");
    SlumpLineEdit = new QLineEdit(this);
//    SlumpLineEdit->setEnabled(false);
    SlumpLineEdit->setStyleSheet("color:black");
    TelephoneLineEdit = new QLineEdit(this);
//    TelephoneLineEdit->setEnabled(false);
    TelephoneLineEdit->setStyleSheet("color:black");
    ConstructionSiteLineEdit = new QLineEdit(this);
//    ConstructionSiteLineEdit->setEnabled(false);
    ConstructionSiteLineEdit->setStyleSheet("color:black");
    ShippingVolumeLineEdit = new QLineEdit(this);
//    ShippingVolumeLineEdit->setEnabled(false);
    ShippingVolumeLineEdit->setStyleSheet("color:blue");
    OperatorLineEdit = new QLineEdit(this);
//    OperatorLineEdit->setEnabled(false);
    OperatorLineEdit->setStyleSheet("color:blue");
    TemplateLineEdit = new QLineEdit(this);
//    TemplateLineEdit->setEnabled(false);
    TemplateLineEdit->setStyleSheet("color:black");
    UnitNoLineEdit = new QLineEdit(this);
//    UnitNoLineEdit->setEnabled(false);
    UnitNoLineEdit->setStyleSheet("color:blue");
    RemainMatLineEdit = new QLineEdit(this);
//    RemainMatLineEdit->setEnabled(false);
    RemainMatLineEdit->setStyleSheet("color:black");
    UnitWeightLineEdit = new QLineEdit(this);
//    UnitWeightLineEdit->setEnabled(false);
    UnitWeightLineEdit->setStyleSheet("color:black");
    CumulationNumberLineEdit = new QLineEdit(this);
//    CumulationNumberLineEdit->setEnabled(false);
    CumulationNumberLineEdit->setStyleSheet("color:black");
    CompleteVolumeLineEdit = new QLineEdit(this);
//    CompleteVolumeLineEdit->setEnabled(false);
    CompleteVolumeLineEdit->setStyleSheet("color:black");

    BeizhuLineEdit = new QLineEdit(this);
//    CompleteVolumeLineEdit->setEnabled(false);
    BeizhuLineEdit->setStyleSheet("color:black");


    VehicleCombox  = new QComboBox(this);
    VehicleCombox->setEditable(true);
    db.sql_fillComboBoxItem("select Vehiclenumber from ConcreteVehicleInformation order by Vehiclenumber+0",VehicleCombox);
    connect(VehicleCombox,SIGNAL(currentTextChanged(QString)),this,SLOT(on_VehicleCombox()));


    DriverCombox  = new QComboBox(this);
    DriverCombox->setEditable(true);
    db.sql_fillComboBoxItem("select Driver1 from ConcreteVehicleInformation order by Vehiclenumber+0",DriverCombox);

    PourMethodCombox  = new QLineEdit(this);
//    PourMethodCombox->setEnabled(false);
//    db.sql_fillComboBoxItem("select PouringMethod from PouringMethod",PourMethodCombox);

    PrintBtn = new QPushButton(tr("打印"),this);
    PrintBtn->setFixedWidth(120);
    connect(PrintBtn,SIGNAL(clicked()),this,SLOT(on_print()));

    shuaxinBtn = new QPushButton(tr("刷新"),this);
    shuaxinBtn->setFixedWidth(120);
    connect(shuaxinBtn,SIGNAL(clicked()),this,SLOT(on_shuaxinBtn()));

    view = new QTableView(this);
    db.showview(SQL1.toStdString().data(),view,&model);
    connect(view,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick()));

    QGridLayout *layout1 = new QGridLayout;
    layout1->addWidget(CustomerLabel,0,0);
    layout1->addWidget(CustomerLineEdit,0,1);
    layout1->addWidget(StrengthGradeLabel,0,2);
    layout1->addWidget(StrengthGradeLineEdit,0,3);
    layout1->addWidget(VehicleLabel,0,4);
    layout1->addWidget(VehicleCombox,0,5);
    layout1->addWidget(EngineerNameLabel,1,0);
    layout1->addWidget(EngineerNameLineEdit,1,1);
    layout1->addWidget(PourPositionLabel,1,2);
    layout1->addWidget(PourPositionLineEdit,1,3);
    layout1->addWidget(DriverLabel,1,4);
    layout1->addWidget(DriverCombox,1,5);
    layout1->addWidget(ConstructionSiteLabel,2,0);
    layout1->addWidget(ConstructionSiteLineEdit,2,1);
    layout1->addWidget(PourMethodLabel,2,2);
    layout1->addWidget(PourMethodCombox,2,3);
    layout1->addWidget(ContactLabel,2,4);
    layout1->addWidget(ContactLineEdit,2,5);
    layout1->addWidget(TaskListLabel,3,0);
    layout1->addWidget(TaskListLineEdit,3,1);
    layout1->addWidget(SlumpLabel,3,2);
    layout1->addWidget(SlumpLineEdit,3,3);
    layout1->addWidget(TelephoneLabel,3,4);
    layout1->addWidget(TelephoneLineEdit,3,5);
    layout1->addWidget(OutBoundTimeLabel,4,0);
    layout1->addWidget(OutBoundTime,4,1);
    layout1->addWidget(ShippingVolumeLabel,4,2);
    layout1->addWidget(ShippingVolumeLineEdit,4,3);
    layout1->addWidget(OperatorLabel,4,4);
    layout1->addWidget(OperatorLineEdit,4,5);
    layout1->addWidget(TemplateLabel,5,0);
    layout1->addWidget(TemplateLineEdit,5,1);

    layout1->addWidget(CompleteVolumeLabel ,5,2);
    layout1->addWidget(CompleteVolumeLineEdit ,5,3);

    layout1->addWidget(RemainMatLabel,5,4);
    layout1->addWidget(RemainMatLineEdit,5,5);
    layout1->addWidget(UnitWeightLabel,6,0);
    layout1->addWidget(UnitWeightLineEdit,6,1);
    layout1->addWidget(CumulationNumberLabel,6,2);
    layout1->addWidget(CumulationNumberLineEdit,6,3);
    layout1->addWidget(UnitNoLabel,6,4);
    layout1->addWidget(UnitNoLineEdit,6,5);

    layout1->addWidget(BeizhuLabel,7,0);
    layout1->addWidget(BeizhuLineEdit,7,1,1,5);

    QHBoxLayout *layout2 = new QHBoxLayout;
    layout2->addStretch(20);
    layout2->addSpacing(15);
    layout2->addWidget(PrintBtn,1);
    layout2->addStretch(20);

    QHBoxLayout *layout3 = new QHBoxLayout;
    layout3->addWidget(InstructLabel1,0);
    layout3->addWidget(shuaxinBtn,1);
    layout3->addWidget(WarningLabel,0);
    layout3->addStretch(20);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(layout1);
    vlayout->addSpacing(20);
    vlayout->addLayout(layout2);
    vlayout->addLayout(layout3);
    vlayout->addWidget(view);

    fahuoqueren->setLayout(vlayout);
    tabWidget->addTab(fahuoqueren,tr("发货确认"));
}

void fahuoquerenDlg::creatTabPage2()
{
    SQL2 = "select RecordNumber 发货序号,FaHuoCustomer 发货客户,Engineering 工程,DeliveryVehicle 送货车辆,Driver 司机,ShippingVolume 发货方量,ActualProductionVolume 实际生产方量,\
            RemainingMaterial 剩料,VolumeMortar 砂浆方量,CumulativeNumber 累计车次,CumulativeVolume 累计方量,PouringPosition 浇筑部位,PouringMethod 浇筑方法,StrengthGrade 强度等级,\
            TemplateName 配合比模板名称,ProductionTime 生产时间,Slump 坍落度,Unit 机组,InformPeople 通知人,Capacity 容重,TaskList 任务单,ContractNumber 合同编号,ConstructionSite 工程地址 from ProductionNotice \
            where WhetherDelivery='是' limit 0";

    twoEngineerCheckBox = new QCheckBox(tr("工程名称"),this);
    twoProductTimeCheckBox = new QCheckBox(tr("生产时间"),this);
    twoProductTimeCheckBox->setCheckState(Qt::Checked);
    twoVehicleCheckBox = new QCheckBox(tr("车辆"),this);
    twoUnitCheckBox = new QCheckBox(tr("生产机组"),this);

    twoEngineerCombox = new QComboBox(this);
    const char *filltwocomBox1 = "select Engineering from ProductionNotice group by Engineering;";
    db.sql_fillComboBoxItem(filltwocomBox1,twoEngineerCombox);
    twoVehicleCombox = new QComboBox(this);
    const char *filltwocomBox2 = "select LicensePlate from ConcreteVehicleInformation;";
    db.sql_fillComboBoxItem(filltwocomBox2,twoVehicleCombox);
    twoUnitCombox = new QComboBox(this);
    const char *filltwocomBox3 = "select UnitName from UnitSetting;";
    db.sql_fillComboBoxItem(filltwocomBox3,twoUnitCombox);

    twoview = new QTableView(this);
    db.showview_num(SQL2,twoview,&twomodel,0);
    connect(twoview,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick2()));

    QLabel *label = new QLabel(tr("--"),this);
    label->setAlignment(Qt::AlignCenter);

    twoProductTime1 = new QDateTimeEdit(this);
    twoProductTime1->setDate(QDate::currentDate());
    twoProductTime1->setCalendarPopup(true);
    twoProductTime2 = new QDateTimeEdit(this);
    twoProductTime2->setDate(QDate::currentDate().addDays(1));
    twoProductTime2->setCalendarPopup(true);

    twoFindBtn = new QPushButton(tr("查询"),this);
    twoFindBtn->setFixedWidth(120);
    connect(twoFindBtn,SIGNAL(clicked()),this,SLOT(on_fahuochaxun()));

    QGridLayout *layout1 = new QGridLayout;
    layout1->addWidget(twoEngineerCheckBox,0,0);
    layout1->addWidget(twoEngineerCombox,0,1);
    layout1->addWidget(twoProductTimeCheckBox,0,2);
    layout1->addWidget(twoProductTime1,0,3);
    layout1->addWidget(label,0,4);
    layout1->addWidget(twoProductTime2,0,5);
    layout1->addWidget(twoFindBtn,0,6,2,1,Qt::AlignVCenter);
    layout1->addWidget(twoVehicleCheckBox,1,0);
    layout1->addWidget(twoVehicleCombox,1,1);
    layout1->addWidget(twoUnitCheckBox,1,2);
    layout1->addWidget(twoUnitCombox,1,3);
    layout1->setColumnStretch(0,0);
    layout1->setColumnStretch(1,1);
    layout1->setColumnStretch(2,0);
    layout1->setColumnStretch(3,1);
    layout1->setColumnStretch(4,0);
    layout1->setColumnStretch(5,1);
    layout1->setColumnStretch(6,1);
    layout1->setColumnStretch(7,3);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(layout1);
    vlayout->addWidget(twoview);

    on_fahuochaxun();

    fahuochaxun->setLayout(vlayout);
    tabWidget->addTab(fahuochaxun,tr("发货查询"));
}


void fahuoquerenDlg::ShowSupplyclick()
{
    int row = view->currentIndex().row();
    CustomerLineEdit->setText(model->item(row,1)->text());
    EngineerNameLineEdit->setText(model->item(row,2)->text());
    VehicleCombox->setCurrentText(model->item(row,3)->text());
    DriverCombox->setCurrentText(model->item(row,4)->text());
    ShippingVolumeLineEdit->setText(model->item(row,5)->text());
    RemainMatLineEdit->setText(model->item(row,7)->text());
    CumulationNumberLineEdit->setText(model->item(row,9)->text());
    qDebug()<<CumulationNumberLineEdit->text();
    CompleteVolumeLineEdit->setText(model->item(row,10)->text());
    PourPositionLineEdit->setText(model->item(row,11)->text());
//    PourMethodCombox->setCurrentText(model->item(row,12)->text());
    StrengthGradeLineEdit->setText(model->item(row,13)->text());
    TemplateLineEdit->setText(model->item(row,14)->text());
    ProductionTime = model->item(row,15)->text();
    SlumpLineEdit->setText(model->item(row,16)->text());
    UnitNoLineEdit->setText(model->item(row,17)->text());
    UnitWeightLineEdit->setText(model->item(row,19)->text());
    TaskListLineEdit->setText(model->item(row,20)->text());
    OperatorLineEdit->setText(userName);
    RecordNumber = model->item(row,0)->text();
    ContractNumber = model->item(row,21)->text();
    ConstructionSiteLineEdit->setText(model->item(row,22)->text());
    PourMethodCombox->setText(model->item(row,12)->text());


    OutBoundTime->setDateTime(QDateTime::currentDateTime());

//    QString searchSQL = QString("select ContractCompletion,fahuocheci from ProductionTaskList where TaskNumber='%1';").arg(TaskListLineEdit->text());
//    CompleteVolumeLineEdit->setText(db.sql_fetchrow_plus(searchSQL.toStdString().data(),0));
//    CumulationNumberLineEdit->setText(db.sql_fetchrow_plus(searchSQL.toStdString().data(),1));
}

void fahuoquerenDlg::ShowSupplyclick2()
{
    int row = twoview->currentIndex().row();
    qDebug()<<"start:"<<twomodel->item(row,1)->text()<<":end";
    CustomerLineEdit->setText(twomodel->item(row,1)->text());
    EngineerNameLineEdit->setText(twomodel->item(row,2)->text());
    VehicleCombox->setCurrentText(twomodel->item(row,3)->text());
    DriverCombox->setCurrentText(twomodel->item(row,4)->text());
    ShippingVolumeLineEdit->setText(twomodel->item(row,5)->text());
    RemainMatLineEdit->setText(twomodel->item(row,7)->text());
    CumulationNumberLineEdit->setText(twomodel->item(row,9)->text());
    qDebug()<<CumulationNumberLineEdit->text();
    CompleteVolumeLineEdit->setText(twomodel->item(row,10)->text());
    PourPositionLineEdit->setText(twomodel->item(row,11)->text());
//    PourMethodCombox->setCurrentText(twomodel->item(row,12)->text());
    StrengthGradeLineEdit->setText(twomodel->item(row,13)->text());
    TemplateLineEdit->setText(twomodel->item(row,14)->text());
//    ProductionTime = twomodel->item(row,15)->text();
    SlumpLineEdit->setText(twomodel->item(row,16)->text());
    UnitNoLineEdit->setText(twomodel->item(row,17)->text());
    UnitWeightLineEdit->setText(twomodel->item(row,19)->text());
    TaskListLineEdit->setText(twomodel->item(row,20)->text());
    OperatorLineEdit->setText(userName);
    RecordNumber = twomodel->item(row,0)->text();
    ContractNumber = twomodel->item(row,21)->text();
    ConstructionSiteLineEdit->setText(twomodel->item(row,22)->text());
    PourMethodCombox->setText(twomodel->item(row,12)->text());
//    OutBoundTime->setDateTime(twomodel->item(row,15)->text());
    OutBoundTime->setDateTime(QDateTime::fromString(twomodel->item(row,15)->text(), "yyyy-MM-dd hh:mm:ss"));


    QString searchSQL = QString("select Remarks from ProductionTaskList where TaskNumber='%1';").arg(TaskListLineEdit->text());
    BeizhuLineEdit->setText(db.sql_fetchrow_plus(searchSQL.toStdString().data(),0));
//    CompleteVolumeLineEdit->setText(db.sql_fetchrow_plus(searchSQL.toStdString().data(),0));
//    CumulationNumberLineEdit->setText(db.sql_fetchrow_plus(searchSQL.toStdString().data(),1));



    tabWidget->setCurrentIndex(0);
}

void fahuoquerenDlg::on_VehicleCombox()
{
    QString searchSQL = QString("select Driver1 from ConcreteVehicleInformation where Vehiclenumber ='%1'").arg(VehicleCombox->currentText());
    DriverCombox->setCurrentText(db.sql_fetchrow_plus(searchSQL,0));
}

void fahuoquerenDlg::on_print()
{ 
    if(CustomerLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("错误"),tr("请选择一个出车单"),0,0,0);
        return;
    }

    QString RenwudanNoString = QString("select TaskList from ProductionNotice where RecordNumber=%1").arg(RecordNumber);
    QStringList RenwudanNoList = db.CreatStrList(RenwudanNoString);


    QString JiHuaFangLiang = QString("select PlannedQuantity from productiontasklist where TaskNumber=%1").arg(RenwudanNoList.at(0));
    QStringList JiHuaFangLiangList = db.CreatStrList(JiHuaFangLiang);
    qDebug()<<JiHuaFangLiangList.at(0);

    //备注
    QString beizhu = QString("select Remarks from productiontasklist where TaskNumber=%1").arg(RenwudanNoList.at(0));
    QStringList beizhuList = db.CreatStrList(beizhu);
    QString Linshi = BeizhuLineEdit->text();
    BeizhuLineEdit->setText(beizhuList.at(0) + " " + Linshi);

    //获取工程运费和单价
    QString searchDataSQL = QString("select Distance,PricePerParty from ProductionTaskList where TaskNumber = '%1'").arg(TaskListLineEdit->text());
    QString Distance = db.sql_fetchrow_plus(searchDataSQL,0);
    QString Price = db.sql_fetchrow_plus(searchDataSQL,1);

    //获取运费价格
    QString searchFreightPrice = QString("select Freight from ConcreteCarFreightSet where MinimumMileage+0<=%1 and MaximumMileage+0>=%1").arg(Distance);
    QString FreightPrice = db.sql_fetchrow_plus(searchFreightPrice,0);

    QVariantList params1,params2,params3,params4,params5,params6,params7,params8,params9,params10,params11,params12,params13,params14,params15,params16,params17,params18,params19,params20;
    params1<<"GCMC"<<QString("\"")+EngineerNameLineEdit->text()+QString("\"");
    params2<<"SGDW"<<QString("\"")+CustomerLineEdit->text()+QString("\"");
    params3<<"SGBW"<<QString("\"")+PourPositionLineEdit->text()+QString("\"");
    params4<<"QDUDJ"<<QString("\"")+StrengthGradeLineEdit->text()+QString("\"");
    params5<<"JBZ"<<QString("\"")+UnitNoLineEdit->text()+QString("\"");
    params6<<"CHENO"<<QString("\"")+VehicleCombox->currentText()+QString("\"");
    params7<<"SJNAME"<<QString("\"")+DriverCombox->currentText()+QString("\"");
    params8<<"TLD"<<QString("\"")+SlumpLineEdit->text()+QString("\"");
//    params9<<"JZFS"<<QString("\"")+PourMethodCombox->currentText()+QString("\"");
    params9<<"JZFS"<<QString("\"")+PourMethodCombox->text()+QString("\"");
    params10<<"CHECI"<<QString("\"")+CumulationNumberLineEdit->text()+QString("\"");
    params11<<"SCRQ"<<QString("\"")+OutBoundTime->text().section(' ',0,0)+QString("\"");
    params12<<"CZSJ"<<QString("\"")+OutBoundTime->text().section(' ',1,1)+QString("\"");
    params13<<"PHBNO"<<QString("\"")+TemplateLineEdit->text()+QString("\"");
    params14<<"BCFL"<<QString("\"")+ShippingVolumeLineEdit->text()+QString("\"");
    params15<<"LJFL"<<QString("\"")+CompleteVolumeLineEdit->text()+QString("\"");
    params16<<"FHR"<<QString("\"")+OperatorLineEdit->text()+QString("\"");

    params17<<"RWDH"<<QString("\"")+RenwudanNoList.at(0)+QString("\"");
    params18<<"JHFL"<<QString("\"")+JiHuaFangLiangList.at(0)+QString("\"");
    params19<<"YJ"<<QString("\"")+Distance+QString("\"");

    params20<<"BZ"<<QString("\"")+BeizhuLineEdit->text()+QString("\"");

    //打印发货单
    m_report->dynamicCall("LoadReportFromFile(QString)", "report/CurOut.fr3");
    m_report->dynamicCall("SetVariable(QString, QVariant)", params1);
    m_report->dynamicCall("SetVariable(QString, QVariant)", params2);
    m_report->dynamicCall("SetVariable(QString, QVariant)", params3);
    m_report->dynamicCall("SetVariable(QString, QVariant)", params4);
    m_report->dynamicCall("SetVariable(QString, QVariant)", params5);
    m_report->dynamicCall("SetVariable(QString, QVariant)", params6);
    m_report->dynamicCall("SetVariable(QString, QVariant)", params7);
    m_report->dynamicCall("SetVariable(QString, QVariant)", params8);
    m_report->dynamicCall("SetVariable(QString, QVariant)", params9);
    m_report->dynamicCall("SetVariable(QString, QVariant)", params10);
    m_report->dynamicCall("SetVariable(QString, QVariant)", params11);
    m_report->dynamicCall("SetVariable(QString, QVariant)", params12);
    m_report->dynamicCall("SetVariable(QString, QVariant)", params13);
    m_report->dynamicCall("SetVariable(QString, QVariant)", params14);
    m_report->dynamicCall("SetVariable(QString, QVariant)", params15);
    m_report->dynamicCall("SetVariable(QString, QVariant)", params16);

    m_report->dynamicCall("SetVariable(QString, QVariant)", params17);
    m_report->dynamicCall("SetVariable(QString, QVariant)", params18);
    m_report->dynamicCall("SetVariable(QString, QVariant)", params19);
    m_report->dynamicCall("SetVariable(QString, QVariant)", params20);
    m_report->dynamicCall("PrepareReport(bool)", "true");

    keybd_event(VK_RETURN,0,0,0);
    keybd_event(VK_RETURN,0,KEYEVENTF_KEYUP,0);

    m_report->dynamicCall("PrintReport()");

    //更新生产通知单和运费
    QString panduanSQL = QString("select RecordNumber from ProductionNotice where RecordNumber=%1 and WhetherDelivery='是'").arg(RecordNumber);
    int ret = db.row_count(panduanSQL);
    if(ret == 0){
        //事务开始
        db.sql_exec("begin");
        //更新发货单
        QString updateSQL = QString("update ProductionNotice set WhetherDelivery='是',OutboundTime='%1',caozuoyuan='%3',PouringMethod='%4',Price='%5',Mileage='%6',FreightPrice='%7' where RecordNumber=%2")
                .arg(OutBoundTime->dateTime().toString("yyyy-MM-dd hh:mm:ss"),RecordNumber,OperatorLineEdit->text(),PourMethodCombox->text())
                .arg(Price,Distance,FreightPrice);
        int res = db.sql_exec(updateSQL);
        if(res == -1){
            db.sql_exec("rollback");
            return;
        }
        if(ShippingVolumeLineEdit->text() == "水票")
        {
            QString updateSQL = QString("update ProductionNotice set Confirmor='是' where RecordNumber=%1")
                    .arg(RecordNumber);
            int res = db.sql_exec(updateSQL);
            if(res == -1){
                db.sql_exec("rollback");
                return;
            }
            QString updateSQL2 = QString("delete from inhousevehicle where  CheNo='%1'")
                    .arg(VehicleCombox->currentText());
            int res2 = db.sql_exec(updateSQL2);
            if(res2 == -1){
                db.sql_exec("rollback");
                return;
            }
        }
        //更新总任务单中的已完成任务量，发货车次
        QString updateTaskListSQL = QString("update ProductionTaskList set fahuocheci='%1',ContractCompletion='%2' where TaskNumber='%3';")
                .arg(CumulationNumberLineEdit->text(),CompleteVolumeLineEdit->text(),TaskListLineEdit->text());
        res = db.sql_exec(updateTaskListSQL);
        if(res == -1){
            db.sql_exec("rollback");
            return;
        }
        //事务结束
        db.sql_exec("commit");
    }

    CustomerLineEdit->clear();
    EngineerNameLineEdit->clear();
    VehicleCombox->clear();
    DriverCombox->clear();
    ShippingVolumeLineEdit->clear();
    RemainMatLineEdit->clear();
    PourPositionLineEdit->clear();
    PourMethodCombox->clear();
    StrengthGradeLineEdit->clear();
    TemplateLineEdit->clear();
    ProductionTime.clear();
    SlumpLineEdit->clear();
    UnitNoLineEdit->clear();
    UnitWeightLineEdit->clear();
    TaskListLineEdit->clear();
    RecordNumber.clear();
    ContractNumber.clear();
    CompleteVolumeLineEdit->clear();
    CumulationNumberLineEdit->clear();
    ConstructionSiteLineEdit->clear();
    BeizhuLineEdit->clear();
    OperatorLineEdit->clear();
    sockClient->send_Msg3();
}

void fahuoquerenDlg::on_fahuochaxun()
{
    QString gongcheng,shijian,cheliang,shengchanjizu,querenren;

    if(twoEngineerCheckBox->checkState() == 2){
        gongcheng = QString(" and Engineering='%1'").arg(twoEngineerCombox->currentText());
    }
    if(twoProductTimeCheckBox->checkState() == 2){
        shijian = QString(" and ProductionTime between '%1' and '%2'").arg(twoProductTime1->dateTime().toString("yyyy-MM-dd hh:mm"),twoProductTime2->dateTime().toString("yyyy-MM-dd hh:mm"));
    }
    if(twoVehicleCheckBox->checkState() == 2){
        cheliang = QString(" and DeliveryVehicle='%1'").arg(twoVehicleCombox->currentText());
    }
    if(twoUnitCheckBox->checkState() == 2){
        shengchanjizu = QString(" and Unit='%1'").arg(twoUnitCombox->currentText());
    }

    QString chaxunSQL = QString("select RecordNumber 发货序号,FaHuoCustomer 发货客户,Engineering 工程,DeliveryVehicle 送货车辆,Driver 司机,ShippingVolume 发货方量,ActualProductionVolume 实际生产方量,\
                                RemainingMaterial 剩料,VolumeMortar 砂浆方量,CumulativeNumber 累计车次,CumulativeVolume 累计方量,PouringPosition 浇筑部位,PouringMethod 浇筑方法,StrengthGrade 强度等级,\
                                TemplateName 配合比模板名称,ProductionTime 生产时间,Slump 坍落度,Unit 机组,InformPeople 通知人,Capacity 容重,TaskList 任务单,ContractNumber 合同编号,ConstructionSite 工程地址 from ProductionNotice \
                                where WhetherDelivery='是' %1%2%3%4%5 order by RecordNumber desc;")
            .arg(gongcheng,shijian,cheliang,shengchanjizu,querenren);

    db.showview_num(chaxunSQL.toStdString().data(),twoview,&twomodel,0);
}

void fahuoquerenDlg::on_shuaxinBtn()
{
    db.showview(SQL1.toStdString().data(),view,&model);
}
