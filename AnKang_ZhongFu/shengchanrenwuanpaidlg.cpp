#include "shengchanrenwuanpaidlg.h"
#include "shengchanxinxidlg.h"

extern mymysql db;
extern QString userName;
extern myTCPsocket *sockClient;
extern pubfunc pub;

shengchanrenwuanpaiDlg::shengchanrenwuanpaiDlg(QWidget *parent) :
    QDialog(parent)
{

    tabWidget = new QTabWidget(this);
    shengchanrenwuanpai = new QWidget(this);
    yianpaiweishengchan = new QWidget(this);
    shengchantongzhichaxun = new QWidget(this);
    fahuobufang = new QWidget(this);
    bufangjilu = new QWidget(this);
    zhuanliaochuli = new QWidget(this);
    zhuanliaojilu = new QWidget(this);
    gongdicheliangfenbu = new QWidget(this);
    zuofeijilu = new QWidget(this);

    page3Open = false;
    page4Open = false;
    page5Open = false;
    page6Open = false;
    page7Open = false;
    page8Open = false;
    page9Open = false;

    creatTabPage1();
    creatTabPage2();
    creatTabPage3();
    creatTabPage4();
    creatTabPage5();
    creatTabPage6();
    creatTabPage7();
    creatTabPage8();
    creatTabPage9();


    connect(tabWidget,SIGNAL(currentChanged(int)),this,SLOT(on_tabWidget(int)));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tabWidget);
}

shengchanrenwuanpaiDlg::~shengchanrenwuanpaiDlg()
{
    delete model;
    delete twomodel;
}

void shengchanrenwuanpaiDlg::refresh()
{
    on_chaxunrenwudan();
    db.showview_num(SQL4,fourview,&fourmodel,0);

    disconnect(oneVehicleCombox,SIGNAL(currentTextChanged(QString)),this,SLOT(oneVehicleComboxResponse()));
    QString fillVehicleCombox = QString("SELECT CONCAT(A.CheNo,' (',B.VehicleXingHao,' ',A.CheState,IF(A.CheState='剩料',C.strengthGrade,''),')') FROM inHouseVehicle A\
                LEFT JOIN ConcreteVehicleInformation B ON (A.CheNo = B.Vehiclenumber) LEFT JOIN (SELECT * FROM (SELECT Volume,LicensePlateNumber,strengthGrade FROM TankWeighing ORDER by \
                GrossWeightTime desc) subtable GROUP BY LicensePlateNumber) C ON (C.LicensePlateNumber=A.CheNo) WHERE A.paiduiState = '' ORDER BY A.CheTime");
    QString text;
    if(!oneVehicleCombox->currentText().isEmpty()){
        text = oneVehicleCombox->currentText();
    }
    oneVehicleCombox->clear();
    db.sql_fillComboBoxItem(fillVehicleCombox,oneVehicleCombox);
    oneVehicleCombox->setCurrentText(text);
    connect(oneVehicleCombox,SIGNAL(currentTextChanged(QString)),this,SLOT(oneVehicleComboxResponse()));
}

void shengchanrenwuanpaiDlg::keyPressEvent(QKeyEvent *event)
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

void shengchanrenwuanpaiDlg::creatTabPage1()
{
    SQL1 = "select TaskNumber 任务单号,Customer 实际客户,Customer 发货客户,Engineering 工程名称,PouringPosition 浇筑部位,PouringMethod 浇筑方法,StrengthGrade 强度等级,\
            Template 配合比模板,PlannedQuantity 计划方量,ContractCompletion 完成方量,fahuocheci 发货车次,HasBeenUnderTask 安排方量,CumulativeNumber 安排车次,\
            Contacts 联系人,ContactNumber 联系电话,SupplyTime 供货时间,Slump 坍落度,Remarks 备注,ContractNumber 合同编号,ConstructionSite 工程地址 from ProductionTaskList limit 0;";

    QLabel *oneTaskListLabel  = new QLabel(tr("任务单"),this);
    oneTaskListLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *oneStrengthGradeLabel  = new QLabel(tr("强度等级"),this);
    oneStrengthGradeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *oneConstructionSiteLabel = new QLabel(tr("工程地址"),this);
    oneConstructionSiteLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *oneContactLabel  = new QLabel(tr("联系人"),this);
    oneContactLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *oneRealCustomerLabel  = new QLabel(tr("实际客户"),this);
    oneRealCustomerLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *oneFaHuoCustomerLabel = new QLabel(tr("发货客户"),this);
    oneFaHuoCustomerLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    QLabel *onePouringPositionLabel  = new QLabel(tr("浇筑部位"),this);
    onePouringPositionLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *oneTelephoneLabel  = new QLabel(tr("联系电话"),this);
    oneTelephoneLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *oneEngineerLabel  = new QLabel(tr("工程"),this);
    oneEngineerLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *onePouringMethodLabel  = new QLabel(tr("浇筑方法"),this);
    onePouringMethodLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *oneLeiJiFLLabel  = new QLabel(tr("累计方量"),this);
    oneLeiJiFLLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *oneSlumpLabel = new QLabel(tr("坍落度"),this);
    oneSlumpLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *oneSupplyTimeLabel = new QLabel(tr("供货时间"),this);
    oneSupplyTimeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *oneDepartmentLabel = new QLabel(tr("生产部门"),this);
    oneDepartmentLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *oneUnitLabel = new QLabel(tr("机组"),this);
    oneUnitLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *oneFahuoFlLabel = new QLabel(tr("发货方量"),this);
    oneFahuoFlLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *oneMotarVolumeLabel = new QLabel(tr("含砂浆"),this);
    oneMotarVolumeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *oneProductTimeLabel = new QLabel(tr("生产时间"),this);
    oneProductTimeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *oneDeliveryVehicle = new QLabel(tr("送货车辆"),this);
    oneDeliveryVehicle->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *oneDriverLabel = new QLabel(tr("司机"),this);
    oneDriverLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *ActualProductionVolumeLabel = new QLabel(tr("实际生产方量"),this);
    ActualProductionVolumeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *oneRemainingMaterialLabel = new QLabel(tr("剩料"),this);
    oneRemainingMaterialLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *oneFuHaoLabel = new QLabel(tr("--"),this);
    oneFuHaoLabel->setAlignment(Qt::AlignCenter);
    QLabel *oneLeijiCheCiLabel = new QLabel(tr("累计车次"),this);
    oneLeijiCheCiLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    QLabel *oneAnPaiFlLabel = new QLabel(tr("安排方量"),this);
    oneAnPaiFlLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    QLabel *oneAnPaiCheCiLabel = new QLabel(tr("安排车次"),this);
    oneAnPaiCheCiLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    QLabel *oneXuKaiVolumeLabel = new QLabel(tr("虚开"),this);
    oneXuKaiVolumeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);


    QLabel *oneAddCheliangLabel = new QLabel(tr("添加车辆"),this);
    oneAddCheliangLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *oneDelCheliangLabel = new QLabel(tr("删除车辆"),this);
    oneDelCheliangLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);


    oneAddCheliangLineEdit  = new QLineEdit(this);
    oneDelCheliangLineEdit  = new QLineEdit(this);

    oneAddCheliangBtn = new QPushButton(tr("添加确认"),this);
//    oneAddCheliangBtn->setEnabled(false);
    connect(oneAddCheliangBtn,SIGNAL(clicked()),this,SLOT(on_oneAddCheliangBtn()));
    oneDelCheliangBtn = new QPushButton(tr("删除确认"),this);
//    oneDelCheliangBtn->setEnabled(false);
    connect(oneDelCheliangBtn,SIGNAL(clicked()),this,SLOT(on_oneDelCheliangBtn()));

    oneBuDaShuiPiaoBtn = new QPushButton(tr("补打水票"),this);
//    oneDelCheliangBtn->setEnabled(false);
    connect(oneBuDaShuiPiaoBtn,SIGNAL(clicked()),this,SLOT(on_oneBuDaShuiPiaoBtn()));


    qitaxinxiBtn = new QPushButton(tr("其他信息"),this);
    connect(qitaxinxiBtn,SIGNAL(clicked()),this,SLOT(on_qitaxinxiBtn()));




    lastVehicleInfoLabel = new QLabel(this);
    lastVehicleInfoLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    TodayPlanVolumeLabel = new QLabel(this);

    oneTaskListLineEdit  = new QLineEdit(this);
    oneTaskListLineEdit->setReadOnly(true);
    oneStrengthGradeLineEdit  = new QLineEdit(this);
    oneStrengthGradeLineEdit->setReadOnly(true);
    oneConstructionSiteLineEdit = new QLineEdit(this);
    oneConstructionSiteLineEdit->setReadOnly(true);
    oneContactLineEdit  = new QLineEdit(this);
    oneContactLineEdit->setReadOnly(true);
    oneRealCustomerLineEdit  = new QLineEdit(this);
    oneRealCustomerLineEdit->setReadOnly(true);
    onePouringPositionLineEdit  = new QLineEdit(this);
//    onePouringPositionLineEdit->setReadOnly(true);
    oneTelephoneLineEdit  = new QLineEdit(this);
    oneTelephoneLineEdit->setReadOnly(true);
    oneEngineerLineEdit  = new QLineEdit(this);
    oneEngineerLineEdit->setReadOnly(true);
    onePouringMethodLineEdit  = new QLineEdit(this);
//    onePouringMethodLineEdit->setReadOnly(true);
    oneLeiJiFLLineEdit  = new QLineEdit(this);
    oneFaHuoCustomerLineEdit = new QLineEdit(this);
    oneFaHuoCustomerLineEdit->setReadOnly(true);
    oneSlumpLineEdit = new QLineEdit(this);
    oneSlumpLineEdit->setReadOnly(true);
    oneSupplyTimeLineEdit = new QLineEdit(this);
    oneSupplyTimeLineEdit->setReadOnly(true);
    oneShippingVolumeLineEdit = new QLineEdit(this);
    QRegExp regx("^[-+]?\\d+(\\.\\d+)?$");

    QValidator *validator = new QRegExpValidator(regx, oneShippingVolumeLineEdit );
    oneShippingVolumeLineEdit->setValidator( validator );

    oneMotarVolumeLineEdit = new QLineEdit(this);
    QRegExp regx1("^[-+]?\\d+(\\.\\d+)?$");

    QValidator *validator2 = new QRegExpValidator(regx1, oneMotarVolumeLineEdit );
    oneMotarVolumeLineEdit->setValidator( validator2 );

    ActualProductionVolumeLineEdit = new QLineEdit(this);
    ActualProductionVolumeLineEdit->setReadOnly(true);
    oneRemainingMaterialLineEdit = new QLineEdit(this);
    QRegExp regx3("^[-+]?\\d+(\\.\\d+)?$");

    QValidator *validator3 = new QRegExpValidator(regx3, oneRemainingMaterialLineEdit );
    oneRemainingMaterialLineEdit->setValidator( validator3 );

    oneLeijiCheCiLineEdit = new QLineEdit(this);
    oneAnPaiFlLineEdit = new QLineEdit(this);
    oneAnPaiCheCiLineEdit = new QLineEdit(this);
    oneXuKaiVolumeLineEdit = new QLineEdit(this);
    QRegExp regx4("^[-+]?\\d+(\\.\\d+)?$");

    QValidator *validator4 = new QRegExpValidator(regx4, oneXuKaiVolumeLineEdit );
    oneXuKaiVolumeLineEdit->setValidator( validator4 );

    oneProductPartCombox = new QComboBox(this);
    oneProductPartCombox->addItem(tr("生产部"));

    oneUnitCombox = new QComboBox(this);
    oneUnitCombox->setStyleSheet("color:black");
    db.sql_fillComboBoxItem("select UnitName from UnitSetting",oneUnitCombox);
    connect(oneUnitCombox,SIGNAL(currentIndexChanged(int)),this,SLOT(ActualProductionVolume()));

    oneVehicleCombox = new QComboBox(this);
    oneVehicleCombox->setEditable(true);
    QString fillVehicleCombox = QString("SELECT CONCAT(A.CheNo,' (',B.VehicleXingHao,' ',A.CheState,IF(A.CheState='剩料',C.strengthGrade,''),')') FROM inHouseVehicle A\
                LEFT JOIN ConcreteVehicleInformation B ON (A.CheNo = B.Vehiclenumber) LEFT JOIN (SELECT * FROM (SELECT Volume,LicensePlateNumber,strengthGrade FROM TankWeighing ORDER by \
                GrossWeightTime desc) subtable GROUP BY LicensePlateNumber) C ON (C.LicensePlateNumber=A.CheNo) WHERE A.paiduiState = '' ORDER BY A.CheTime");
//    QString fillVehicleCombox = "select LicensePlate from ConcreteVehicleInformation group by LicensePlate";
    qDebug()<<fillVehicleCombox;
    db.sql_fillComboBoxItem(fillVehicleCombox.toStdString().data(),oneVehicleCombox);
    connect(oneVehicleCombox,SIGNAL(currentTextChanged(QString)),this,SLOT(oneVehicleComboxResponse()));

    oneDriverCombox = new QComboBox(this);
    oneDriverCombox->setEditable(true);
    //db.sql_fillComboBoxItem("select Driver1 from ConcreteVehicleInformation group by Driver1",oneDriverCombox);

    oneProjectCombox = new myComboBox(this);
    db.sql_fillComboBoxItem3("select ProjectName from SalesContractCustomerEngineeringForm group by ProjectName",oneProjectCombox);

    onePouringPositionCombox = new myComboBox(this);
    db.sql_fillComboBoxItem3("select PouringPosition from productiontasklist group by PouringPosition",onePouringPositionCombox);

    oneProductDatetimeEdit = new QDateTimeEdit(QDateTime::currentDateTime(),this);
    oneProductDatetimeEdit->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
    oneProductDatetimeEdit->setCalendarPopup(true);
    oneProductDatetimeEdit->setEnabled(false);
    oneProductDatetimeEdit->setStyleSheet("color:black");

    oneSendtime1DateEdit = new QDateEdit(QDate::currentDate().addDays(-1),this);
    oneSendtime1DateEdit->setCalendarPopup(true);
    oneSendtime2DateEdit = new QDateEdit(QDate::currentDate(),this);
    oneSendtime2DateEdit->setCalendarPopup(true);

    view = new QTableView(this);
    connect(view,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick()));

    //设置view1的右键菜单
    yincangAct = new QAction(tr("隐藏"),this);
    yincangAct->setIcon(QIcon(":/image/shanchu.png"));
    chexiaoyincangAct = new QAction(tr("撤销隐藏"),this);
    chexiaoyincangAct->setIcon(QIcon(":/image/zengjia.png"));
    connect(yincangAct,SIGNAL(triggered()),this,SLOT(on_yincangAct()));
    connect(chexiaoyincangAct,SIGNAL(triggered()),this,SLOT(on_chexiaoyincangAct()));
    view->addAction(yincangAct);
    view->addAction(chexiaoyincangAct);
    view->setContextMenuPolicy(Qt::ActionsContextMenu);

    oneGongChengCheckBox = new QCheckBox(tr("工程名称"),this);
    onePouringPositionCheckBox = new QCheckBox(tr("浇筑部位"),this);
    oneXiaFaTimecheckBox = new QCheckBox(tr("下发时间"),this);
    oneXiaFaTimecheckBox->setCheckState(Qt::Checked);

//    oneHideCompletecheckBox = new QCheckBox(tr("隐藏已完成"),this);
//    oneHideProductingCheckBox = new QCheckBox(tr("隐藏正在生产"),this);
    oneHideCheck = new QCheckBox(tr("显示隐藏的任务单"),this);

    tongzhishengchanBtn = new QPushButton(tr("通知生产"),this);
    connect(tongzhishengchanBtn,SIGNAL(clicked()),this,SLOT(on_tongzhishengchan()));

    chexiaoshengchanBtn = new QPushButton(tr("撤销生产"),this);
    chexiaoshengchanBtn->setEnabled(false);
    connect(chexiaoshengchanBtn,SIGNAL(clicked()),this,SLOT(on_chexiaoshengchan()));

    chaxunBtn = new QPushButton(tr("查询"),this);
    connect(chaxunBtn,SIGNAL(clicked()),this,SLOT(on_chaxunrenwudan()));

    zuofeiBtn = new QPushButton(tr("任务作废"),this);
    connect(zuofeiBtn,SIGNAL(clicked()),this,SLOT(on_zuofeiBtn()));

    zhuanliaoBtn = new QPushButton(tr("转料处理"),this);
    connect(zhuanliaoBtn,SIGNAL(clicked()),this,SLOT(on_zhuanliaochuliBtn()));

    QGridLayout *layout1 = new QGridLayout;
    layout1->addWidget(oneTaskListLabel,0,0);
    layout1->addWidget(oneTaskListLineEdit,0,1);
    layout1->addWidget(oneStrengthGradeLabel,0,2);
    layout1->addWidget(oneStrengthGradeLineEdit,0,3);
    layout1->addWidget(oneContactLabel,0,4);
    layout1->addWidget(oneContactLineEdit,0,5);
    layout1->addWidget(oneConstructionSiteLabel,0,6);
    layout1->addWidget(oneConstructionSiteLineEdit,0,7);
    layout1->addWidget(oneRealCustomerLabel,1,0);
    layout1->addWidget(oneRealCustomerLineEdit,1,1);
    layout1->addWidget(onePouringPositionLabel,1,2);
    layout1->addWidget(onePouringPositionLineEdit,1,3);
    layout1->addWidget(oneTelephoneLabel,1,4);
    layout1->addWidget(oneTelephoneLineEdit,1,5);
    layout1->addWidget(oneSupplyTimeLabel,1,6);
    layout1->addWidget(oneSupplyTimeLineEdit,1,7);
    layout1->addWidget(oneFaHuoCustomerLabel,2,0);
    layout1->addWidget(oneFaHuoCustomerLineEdit,2,1);
    layout1->addWidget(onePouringMethodLabel,2,2);
    layout1->addWidget(onePouringMethodLineEdit,2,3);
    layout1->addWidget(oneLeiJiFLLabel,2,4);
    layout1->addWidget(oneLeiJiFLLineEdit,2,5);
    layout1->addWidget(oneAnPaiFlLabel,2,6);
    layout1->addWidget(oneAnPaiFlLineEdit,2,7);
    layout1->addWidget(oneEngineerLabel,3,0);
    layout1->addWidget(oneEngineerLineEdit,3,1);
    layout1->addWidget(oneSlumpLabel,3,2);
    layout1->addWidget(oneSlumpLineEdit,3,3);
    layout1->addWidget(oneLeijiCheCiLabel,3,4);
    layout1->addWidget(oneLeijiCheCiLineEdit,3,5);
    layout1->addWidget(oneAnPaiCheCiLabel,3,6);
    layout1->addWidget(oneAnPaiCheCiLineEdit,3,7);
    layout1->setColumnStretch(0,0);
    layout1->setColumnStretch(1,1);
    layout1->setColumnStretch(2,0);
    layout1->setColumnStretch(3,1);
    layout1->setColumnStretch(4,0);
    layout1->setColumnStretch(5,1);
    layout1->setColumnStretch(6,0);
    layout1->setColumnStretch(7,1);

    QGridLayout *layout2 = new QGridLayout;
    layout2->addWidget(oneDepartmentLabel,0,0);
    layout2->addWidget(oneProductPartCombox,0,1);
    layout2->addWidget(oneUnitLabel,0,2);
    layout2->addWidget(oneUnitCombox,0,3);
    layout2->addWidget(oneFahuoFlLabel,0,4);
    layout2->addWidget(oneShippingVolumeLineEdit,0,5);
    layout2->addWidget(oneMotarVolumeLabel,0,6);
    layout2->addWidget(oneMotarVolumeLineEdit,0,7);
    layout2->addWidget(tongzhishengchanBtn,0,8);
    layout2->addWidget(oneProductTimeLabel,1,0);
    layout2->addWidget(oneProductDatetimeEdit,1,1);
    layout2->addWidget(oneDeliveryVehicle,1,2);
    layout2->addWidget(oneVehicleCombox,1,3);
    layout2->addWidget(oneDriverLabel,1,4);
    layout2->addWidget(oneDriverCombox,1,5);
    layout2->addWidget(ActualProductionVolumeLabel,1,6);
    layout2->addWidget(ActualProductionVolumeLineEdit,1,7);
    layout2->addWidget(chexiaoshengchanBtn,1,8);
    layout2->addWidget(oneRemainingMaterialLabel,2,0);
    layout2->addWidget(oneRemainingMaterialLineEdit,2,1);
    layout2->addWidget(oneXuKaiVolumeLabel,2,2);
    layout2->addWidget(oneXuKaiVolumeLineEdit,2,3);
    layout2->addWidget(TodayPlanVolumeLabel,2,5,1,3);


    layout2->setColumnStretch(0,0);
    layout2->setColumnStretch(1,1);
    layout2->setColumnStretch(2,0);
    layout2->setColumnStretch(3,1);
    layout2->setColumnStretch(4,0);
    layout2->setColumnStretch(5,1);
    layout2->setColumnStretch(6,0);
    layout2->setColumnStretch(7,1);
    layout2->setColumnStretch(8,0);

    QHBoxLayout *subHLayout = new QHBoxLayout;
    subHLayout->addWidget(oneAddCheliangLabel);
    subHLayout->addWidget(oneAddCheliangLineEdit);
    subHLayout->addWidget(oneAddCheliangBtn);
    subHLayout->addWidget(oneDelCheliangLabel);
    subHLayout->addWidget(oneDelCheliangLineEdit);
    subHLayout->addWidget(oneDelCheliangBtn);
    subHLayout->addWidget(oneBuDaShuiPiaoBtn);
    subHLayout->addWidget(qitaxinxiBtn);
    subHLayout->addStretch(2);



    QHBoxLayout *layout3 = new QHBoxLayout;
    layout3->addWidget(oneGongChengCheckBox,0);
    layout3->addWidget(oneProjectCombox,2);
    layout3->addWidget(onePouringPositionCheckBox,0);
    layout3->addWidget(onePouringPositionCombox,2);
    layout3->addWidget(oneXiaFaTimecheckBox,0);
    layout3->addWidget(oneSendtime1DateEdit,1);
    layout3->addWidget(oneFuHaoLabel,0);
    layout3->addWidget(oneSendtime2DateEdit,1);
    layout3->addWidget(chaxunBtn,1);
    layout3->addWidget(oneHideCheck,0);
    layout3->addWidget(zuofeiBtn,1);
    layout3->addWidget(zhuanliaoBtn,1);
    layout3->addSpacing(300);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addLayout(layout1,1);
    vlayout->addSpacing(20);
    vlayout->addLayout(layout2,1);
    vlayout->addSpacing(20);
    vlayout->addLayout(subHLayout,1);
    vlayout->addSpacing(20);
    vlayout->addWidget(lastVehicleInfoLabel);
    vlayout->addLayout(layout3,1);
    vlayout->addWidget(view,1);

    shengchanrenwuanpai->setLayout(vlayout);
    tabWidget->addTab(shengchanrenwuanpai,tr("生产任务安排"));

    on_chaxunrenwudan();
}

void shengchanrenwuanpaiDlg::creatTabPage2()
{
    SQL2 = "select RecordNumber 发货序号,Customer 实际客户,FaHuoCustomer 发货客户,Unit 生产机组,Engineering 工程,PouringPosition 浇筑部位,\
            PouringMethod 浇筑方法,StrengthGrade 强度等级,ShippingVolume 发货方量,IF(VolumeMortar='',0,VolumeMortar) 砂浆方量,DeliveryVehicle 送货车辆,Driver 司机,\
            CumulativeNumber 累计车次,CumulativeVolume 累计方量,ProductionTime 生产时间,Slump 坍落度,Contacts 联系人,ContactNumber 联系电话,\
            WhetherDelivery  是否发货,SupplyTime 供货时间,ProductionDepartment 生产部门,Unit 机组,ActualProductionVolume 实际生产方量,\
            RemainingMaterial 剩料,InformPeople 通知人,TaskList 任务单,ConstructionSite 施工地点 from ProductionNotice A LEFT JOIN (SELECT * FROM RunStateTab) B ON (A.RecordNumber=B.recordNo) \
            where Confirmor='否'";

    SQL22 = "select RecordNumber 发货序号,Customer 实际客户,FaHuoCustomer 发货客户,Engineering 工程,Unit 生产机组,B.panshu 当前盘数,B.volume 完成方量,PouringPosition 浇筑部位,\
            PouringMethod 浇筑方法,StrengthGrade 强度等级,ShippingVolume 发货方量,ActualProductionVolume 生产方量,RemainingMaterial 剩料,\
            IF(VolumeMortar='',0,VolumeMortar) 砂浆方量,DeliveryVehicle 送货车辆,Driver 司机,CumulativeNumber 累计车次,CumulativeVolume 累计方量,Slump 坍落度,\
            InformPeople 通知人,TaskList 任务单 from ProductionNotice A LEFT JOIN (SELECT * FROM RunStateTab) B ON (A.RecordNumber=B.recordNo) \
            where B.panshu is not null";

    QLabel *twoProductingRecordLabel  = new QLabel(tr("发货序号"),this);
    twoProductingRecordLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

    twoview = new QTableView(this);
    connect(twoview,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick2()));

    twoProductingView = new QTableView(this);
    connect(twoProductingView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(on_doubleClickTwoProductingView(QModelIndex)));

    twoRefreshRunStateTimer = new QTimer(this);
    connect(twoRefreshRunStateTimer,SIGNAL(timeout()),this,SLOT(on_twoRefreshRunStateTimer()));

    twoProductingRecordNoLineEdit = new QLineEdit(this);
    twoProductingRecordNoLineEdit->setFixedWidth(120);
//    twoProductingRecordNoLineEdit->setReadOnly(true);

    twoSetProductedBtn = new QPushButton(tr("标记为已完成"),this);
    twoSetProductedBtn->setFixedWidth(150);
    connect(twoSetProductedBtn,SIGNAL(clicked()),this,SLOT(on_twoSetProductedBtn()));

    QHBoxLayout *WeiShengChanGroupBoxLayout = new QHBoxLayout;
    WeiShengChanGroupBoxLayout->addWidget(twoview);

    QHBoxLayout *subZhengZaiShengChanGroupBoxLayout = new QHBoxLayout;
    subZhengZaiShengChanGroupBoxLayout->addStretch(20);
    subZhengZaiShengChanGroupBoxLayout->addWidget(twoProductingRecordLabel,0);
    subZhengZaiShengChanGroupBoxLayout->addWidget(twoProductingRecordNoLineEdit,1);
    subZhengZaiShengChanGroupBoxLayout->addWidget(twoSetProductedBtn,1);

    QVBoxLayout *ZhengZaiShengChanGroupBoxLayout = new QVBoxLayout;
    ZhengZaiShengChanGroupBoxLayout->addWidget(twoProductingView);
    ZhengZaiShengChanGroupBoxLayout->addLayout(subZhengZaiShengChanGroupBoxLayout);

    QGroupBox *WeiShengChanGroupBox = new QGroupBox(this);
    WeiShengChanGroupBox->setTitle(tr("未生产单车任务"));
    WeiShengChanGroupBox->setLayout(WeiShengChanGroupBoxLayout);

    QGroupBox *ZhengZaiShengChanGroupBox = new QGroupBox(this);
    ZhengZaiShengChanGroupBox->setTitle(tr("正在生产单车任务"));
    ZhengZaiShengChanGroupBox->setLayout(ZhengZaiShengChanGroupBoxLayout);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(WeiShengChanGroupBox,5);
    vlayout->addWidget(ZhengZaiShengChanGroupBox,4);

    yianpaiweishengchan->setLayout(vlayout);
    tabWidget->addTab(yianpaiweishengchan,tr("生产监控/追加生产"));
}

void shengchanrenwuanpaiDlg::creatTabPage3()
{
    SQL3 = "select RecordNumber 发货序号,Unit 机组,Customer 实际客户,FaHuoCustomer 发货客户,Engineering 工程名称,PouringPosition 浇筑部位,PouringMethod 浇筑方法,\
            StrengthGrade 强度等级,ShippingVolume 发货方量,ActualProductionVolume 实际生产方量,RemainingMaterial 剩料,CumulativeNumber 累计车次,CumulativeVolume 累计方量,\
            IF(VolumeMortar='',0,VolumeMortar) 砂浆方量,DeliveryVehicle 送货车辆,Driver 司机,ProductionTime 生产时间,Slump 坍落度,Contacts 联系人,ContactNumber 联系电话,\
            SupplyTime 供货时间,ProductionDepartment 生产部门,TaskList 任务单,InformPeople 通知人,WhetherCancel 转料状态 from ProductionNotice limit 0";

    QString SQL32 = QString("select RecordNumber 发货序号,DeliveryVehicle 送货车辆,Unit 机组,ReceiptVolume 发货方量,CumulativeNumber 累计车次,CumulativeVolume 累计方量,OutboundTime 出站时间,WhetherCancel 转料状态 from ProductionNotice limit 0");

    threeEngineerCheckBox = new QCheckBox(tr("工程名称"),this);
    threeProductTimeCheckBox = new QCheckBox(tr("生产时间"),this);
    threeProductTimeCheckBox->setCheckState(Qt::Checked);
    threeVehicleCheckBox = new QCheckBox(tr("车辆"),this);
    threeProductUnitCheckBox = new QCheckBox(tr("生产机组"),this);
    threeInfoManCheckBox = new QCheckBox(tr("通知人"),this);

    threeEngineerCombox = new myComboBox(this);

    threeVehicleCombox = new QComboBox(this);

    threeProductUnitCombox = new QComboBox(this);

    threeInfoManCombox = new QComboBox(this);

    threeview = new QTableView(this);
    connect(threeview,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick3()));

    threeProductNoticeView = new QTableView(this);
    db.showview(SQL32,threeProductNoticeView,&threeProductNoticeModel);
    threeProductNoticeView->setColumnHidden(7,true);
    threeProductNoticeView->setColumnWidth(0,65);
    threeProductNoticeView->setColumnWidth(1,65);
    threeProductNoticeView->setColumnWidth(2,65);
    threeProductNoticeView->setColumnWidth(3,65);
    threeProductNoticeView->setColumnWidth(4,65);
    threeProductNoticeView->setColumnWidth(5,65);
    threeProductNoticeView->setColumnWidth(6,130);

    QLabel *label = new QLabel(tr("——"),this);
    label->setAlignment(Qt::AlignCenter);
    QLabel *warninglabel  = new QLabel(tr("转出记录为红色，转入记录为绿色，其他正常发货记录为白色"),this);
    warninglabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    warninglabel->setStyleSheet("color:red");

    threeProductTime1 = new QDateTimeEdit(this);
    threeProductTime1->setDate(QDate::currentDate());
    threeProductTime1->setCalendarPopup(true);
    threeProductTime2 = new QDateTimeEdit(this);
    threeProductTime2->setDate(QDate::currentDate().addDays(1));
    threeProductTime2->setCalendarPopup(true);

    threeFindBtn = new QPushButton(tr("查询"),this);
    threeFindBtn->setFixedWidth(120);
    connect(threeFindBtn,SIGNAL(clicked()),this,SLOT(on_threeFindBtn()));

    QGridLayout *layout1 = new QGridLayout;
    layout1->addWidget(threeEngineerCheckBox,0,0);
    layout1->addWidget(threeEngineerCombox,0,1);
    layout1->addWidget(threeProductTimeCheckBox,0,2);
    layout1->addWidget(threeProductTime1,0,3);
    layout1->addWidget(label,0,4);
    layout1->addWidget(threeProductTime2,0,5);
    layout1->addWidget(threeFindBtn,0,6,2,1,Qt::AlignVCenter);
    layout1->addWidget(warninglabel,0,7,2,1,Qt::AlignVCenter);
    layout1->addWidget(threeVehicleCheckBox,1,0);
    layout1->addWidget(threeVehicleCombox,1,1);
    layout1->addWidget(threeProductUnitCheckBox,1,2);
    layout1->addWidget(threeProductUnitCombox,1,3);
    layout1->addWidget(threeInfoManCheckBox,1,4);
    layout1->addWidget(threeInfoManCombox,1,5);
    layout1->setColumnStretch(0,0);
    layout1->setColumnStretch(1,1);
    layout1->setColumnStretch(2,0);
    layout1->setColumnStretch(3,1);
    layout1->setColumnStretch(4,0);
    layout1->setColumnStretch(5,1);
    layout1->setColumnStretch(6,1);
    layout1->setColumnStretch(7,3);

    QHBoxLayout *ViewLayout = new QHBoxLayout;
    ViewLayout->addWidget(threeview,3);
    ViewLayout->addWidget(threeProductNoticeView,2);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addLayout(layout1);
    vlayout->addLayout(ViewLayout);

    shengchantongzhichaxun->setLayout(vlayout);
    tabWidget->addTab(shengchantongzhichaxun,tr("生产通知查询"));
}

void shengchanrenwuanpaiDlg::creatTabPage4()
{
    SQL4 = "select RecordNumber 发货序号,TaskList 任务单,Customer 实际客户,FaHuoCustomer 发货客户,Engineering 工程名称,PouringPosition 浇筑部位,\
            PouringMethod 浇筑方法,StrengthGrade 强度等级,round(ShippingVolume-VolumeMortar,1) 砼补方,IF(VolumeMortar='',0,VolumeMortar) 砂浆补方,DeliveryVehicle 送货车辆,Driver 司机,\
            CumulativeNumber 累计车次,CumulativeVolume 累计方量,ProductionTime 补方时间,Slump 坍落度,Contacts 联系人,ContactNumber 联系电话,\
            WhetherDelivery  是否发货,SupplyTime 供货时间,ProductionDepartment 生产部门,Unit 机组,ActualProductionVolume 实际生产方量,\
            RemainingMaterial 剩料,InformPeople 通知人 from bufangNotice where WhetherDocument='否' and TIMESTAMPDIFF(MINUTE,OutboundTime,NOW()) < 180 \
            order by RecordNumber desc limit 100;";

    QLabel *RecordNumLabel  = new QLabel(tr("发货序号"),this);
    RecordNumLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *RealCustomerLabel  = new QLabel(tr("实际客户"),this);
    RealCustomerLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *FaHuoCustomerLabel  = new QLabel(tr("发货客户"),this);
    FaHuoCustomerLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *EngineerLabel  = new QLabel(tr("工程"),this);
    EngineerLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *TongVolumeLabel  = new QLabel(tr("砼(含砂浆)补方"),this);
    TongVolumeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *MotarVolumeLabel  = new QLabel(tr("砂浆补方"),this);
    MotarVolumeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *UnitNoLabel  = new QLabel(tr("机组"),this);
    UnitNoLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

    fourRecordNoLineEdit  = new QLineEdit(this);
    fourRecordNoLineEdit->setEnabled(false);
    fourRecordNoLineEdit->setStyleSheet("color:red");
    fourRealCustomerLineEdit  = new QLineEdit(this);
    fourRealCustomerLineEdit->setEnabled(false);
    fourRealCustomerLineEdit->setStyleSheet("color:black");
    fourFaHuoCustomerLineEdit  = new QLineEdit(this);
    fourFaHuoCustomerLineEdit->setEnabled(false);
    fourFaHuoCustomerLineEdit->setStyleSheet("color:black");
    fourEngineerLineEdit  = new QLineEdit(this);
    fourEngineerLineEdit->setEnabled(false);
    fourEngineerLineEdit->setStyleSheet("color:black");
    fourTongVolumeLineEdit  = new QLineEdit(this);
    fourTongVolumeLineEdit->setEnabled(false);
    fourTongVolumeLineEdit->setStyleSheet("color:black");
    fourMotarLineEdit  = new QLineEdit(this);
    fourMotarLineEdit->setStyleSheet("color:black");

    fourUnitNoComBox = new QComboBox(this);
    fourUnitNoComBox->setStyleSheet("color:black");

    fourview = new QTableView(this);
    connect(fourview,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick4()));

    bufangBtn = new QPushButton(tr("补方"),this);
    bufangBtn->setFixedWidth(150);
    connect(bufangBtn,SIGNAL(clicked()),this,SLOT(on_bufangBtn()));
    hulueBtn = new QPushButton(tr("忽略"),this);
    hulueBtn->setFixedWidth(150);
    connect(hulueBtn,SIGNAL(clicked()),this,SLOT(on_hulueBtn()));

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(RecordNumLabel,0);
    hlayout->addWidget(fourRecordNoLineEdit,1);
    hlayout->addWidget(RealCustomerLabel,0);
    hlayout->addWidget(fourRealCustomerLineEdit,1);
    hlayout->addWidget(FaHuoCustomerLabel,0);
    hlayout->addWidget(fourFaHuoCustomerLineEdit,2);
    hlayout->addWidget(EngineerLabel,0);
    hlayout->addWidget(fourEngineerLineEdit,2);
    hlayout->addWidget(TongVolumeLabel,0);
    hlayout->addWidget(fourTongVolumeLineEdit,1);
    hlayout->addWidget(MotarVolumeLabel,0);
    hlayout->addWidget(fourMotarLineEdit,1);
    hlayout->addWidget(UnitNoLabel,0);
    hlayout->addWidget(fourUnitNoComBox,1);

    QHBoxLayout *hlayout2 = new QHBoxLayout;
    hlayout2->addStretch(50);
    hlayout2->addWidget(bufangBtn,2,Qt::AlignRight);
    hlayout2->addWidget(hulueBtn,2,Qt::AlignRight);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(hlayout);
    vlayout->addLayout(hlayout2);
    vlayout->addWidget(fourview);

    fahuobufang->setLayout(vlayout);
    tabWidget->addTab(fahuobufang,tr("发货补方"));
}

void shengchanrenwuanpaiDlg::creatTabPage5()
{
    SQL5 = "select RecordNumber 发货序号,TaskList 任务单,Customer 客户名称,FaHuoCustomer 客户名称,Engineering 工程名称,PouringPosition 浇筑部位,\
            PouringMethod 浇筑方法,StrengthGrade 强度等级,round(ShippingVolume-VolumeMortar,1) 砼补方,IF(VolumeMortar='',0,VolumeMortar) 砂浆补方,DeliveryVehicle 送货车辆,Driver 司机,\
            CumulativeNumber 累计车次,CumulativeVolume 累计方量,ProductionTime 补方时间,Slump 坍落度,Contacts 联系人,ContactNumber 联系电话,\
            WhetherDelivery  是否发货,SupplyTime 供货时间,ProductionDepartment 生产部门,Unit 机组,ActualProductionVolume 实际生产方量,\
            RemainingMaterial 剩料,InformPeople 通知人 from bufangNotice limit 0;";

    QLabel *label1  = new QLabel(tr("日期"),this);
    label1->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label2  = new QLabel(tr("-"),this);
    label2->setAlignment(Qt::AlignCenter);

    fivedateTimeEdit1 = new QDateTimeEdit(this);
    fivedateTimeEdit1->setDate(QDate::currentDate());
    fivedateTimeEdit1->setTime(QTime::fromString("00:00:00","hh:mm:ss"));
    fivedateTimeEdit1->setCalendarPopup(true);
    fivedateTimeEdit2 = new QDateTimeEdit(this);
    fivedateTimeEdit2->setDate(QDate::currentDate().addDays(1));
    fivedateTimeEdit2->setTime(QTime::fromString("00:00:00","hh:mm:ss"));
    fivedateTimeEdit2->setCalendarPopup(true);

    fiveCheckBox1 = new QCheckBox(tr("客户名称"),this);
    fiveCheckBox2 = new QCheckBox(tr("工程名称"),this);

    fiveCombox1 = new QComboBox(this);

    fiveCombox2 = new QComboBox(this);

    fiveBtn = new QPushButton(tr("查询"),this);
    connect(fiveBtn,SIGNAL(clicked()),this,SLOT(on_fiveChaxunBtn()));

    fiveview = new QTableView(this);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(label1,0);
    hlayout->addWidget(fivedateTimeEdit1);
    hlayout->addWidget(label2,0);
    hlayout->addWidget(fivedateTimeEdit2);
    hlayout->addWidget(fiveCheckBox1,0);
    hlayout->addWidget(fiveCombox1,1);
    hlayout->addWidget(fiveCheckBox2,0);
    hlayout->addWidget(fiveCombox2,1);
    hlayout->addWidget(fiveBtn,1);
    hlayout->addStretch(3);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(fiveview);

    bufangjilu->setLayout(vlayout);
    tabWidget->addTab(bufangjilu,tr("补方记录查询"));
}

void shengchanrenwuanpaiDlg::creatTabPage6()
{
    SQL6 = "select RecordNumber 发货序号,TaskList 任务单,Customer 客户名称,Engineering 工程名称,PouringPosition 浇筑部位,PouringMethod 浇筑方法,StrengthGrade 强度等级,\
            ShippingVolume 发货方量,ActualProductionVolume 实际生产方量,RemainingMaterial 剩料,IF(VolumeMortar='',0,VolumeMortar) 砂浆方量,DeliveryVehicle 送货车辆,\
            Driver 司机,CumulativeNumber 累计车次,CumulativeVolume 累计方量,ProductionTime 生产时间,Slump 坍落度,Contacts 联系人,ContactNumber 联系电话,SupplyTime 供货时间,\
            ProductionDepartment 生产部门,Unit 机组,InformPeople 通知人,WhetherCancel 转料状态 from ProductionNotice where WhetherDelivery='是' order by RecordNumber desc limit 0;";

    SQL62 = "select RecordNumber 发货序号,TaskList 任务单,Customer 客户名称,Engineering 工程名称,PouringPosition 浇筑部位,PouringMethod 浇筑方法,StrengthGrade 强度等级,\
            ShippingVolume 发货方量,ActualProductionVolume 实际生产方量,RemainingMaterial 剩料,IF(VolumeMortar='',0,VolumeMortar) 砂浆方量,DeliveryVehicle 送货车辆,\
            Driver 司机,CumulativeNumber 累计车次,CumulativeVolume 累计方量,ProductionTime 生产时间,Slump 坍落度,Contacts 联系人,ContactNumber 联系电话,SupplyTime 供货时间,\
            ProductionDepartment 生产部门,Unit 机组,InformPeople 通知人,WhetherCancel 转料状态 from zhuanliaoNotice where WhetherDelivery='是' order by RecordNumber desc limit 100;";

    QLabel *RecordNumberLabel  = new QLabel(tr("出车单号"),this);
    RecordNumberLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *OriginalNoLabel  = new QLabel(tr("砼来源：记录号"),this);
    OriginalNoLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *CustomerLabel  = new QLabel(tr("客户名称"),this);
    CustomerLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *EngineerLabel  = new QLabel(tr("工程名称"),this);
    EngineerLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *VehicleLabel  = new QLabel(tr("车辆"),this);
    VehicleLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *ShippingVolumeLabel  = new QLabel(tr("发货方量"),this);
    ShippingVolumeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *ReceiptVolumeLabel  = new QLabel(tr("签收方量"),this);
    ReceiptVolumeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *TargetNoLabel  = new QLabel(tr("砼去向："),this);
    TargetNoLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);


    QLabel *InstructionLabel  = new QLabel(tr("1、出车单号询问司机，该单号在纸质出车单的生产日期一栏中\n\
2、输入出车单号后，点击查询按钮后上表中会出现将要进行转料处理的出车单，双击鼠标选中该条记录出现在砼来源中，在签收方量中输入工地签收方量数，如果为整车转则签收方量为0\n\
3、点击第一个标签页（生产任务安排），安排该车次（第2步中选中的）转入到的新工地，该步骤同派车操作一样，区别在于填写好派车信息后点击转料处理按钮而不是通知生产按钮。\n\
   注意：点击转料处理按钮前请确认安排方量和安排车次准确无误！！！\n\
4、点击转料处理按钮会自动跳转到第六个标签页（转料处理），并且砼去向表格中会出现转入工地的信息，确认无误后点击确认转料按钮。\n\如果转入信息错误则在砼去向表格中鼠标右击错误信息点击删除,重复第3步操作。\n\
5、如果为相同方量的转料则不需要进行补方操作；如果转料处理需要补方（例如5方转10方），在进行完第4步操作后通知司机过磅做发货处理，然后在第四个标签页（发货补方）中做补方操作\n\
6、打印新的出车单：第七个标签页（剩转料记录）中，找到退回记录号为第1步中输入的记录号的那一行，查看该行记录的转入记录号则为新的出车单号，将该出车单号电话通知站上让其打印即可"),this);
    InstructionLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    InstructionLabel->setStyleSheet("color:red");

    sixRecordNumLineEdit = new QLineEdit(this);

    sixOriginalNoLineEdit = new QLineEdit(this);
    sixOriginalNoLineEdit->setReadOnly(true);
    sixCustomerLineEdit = new QLineEdit(this);
    sixCustomerLineEdit->setReadOnly(true);
    sixEngineerLineEdit = new QLineEdit(this);
    sixEngineerLineEdit->setReadOnly(true);
    sixVehicleLineEdit = new QLineEdit(this);
    sixVehicleLineEdit->setReadOnly(true);
    sixShippingVolumeLineEdit = new QLineEdit(this);
    sixShippingVolumeLineEdit->setReadOnly(true);
    sixReceiptVolumeLineEdit = new QLineEdit(this);

    sixFindBtn = new QPushButton(tr("查询"),this);
    sixFindBtn->setFixedWidth(120);
    connect(sixFindBtn,SIGNAL(clicked()),this,SLOT(on_sixFindBtn()));

    sixConfirmTransferBtn = new QPushButton(tr("确认转料"),this);
    connect(sixConfirmTransferBtn,SIGNAL(clicked()),this,SLOT(on_sixConfirmTransferBtn()));

    sixOriginalView = new QTableView(this);
    connect(sixOriginalView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick6()));

    sixTargetView = new QTableView(this);

    //设置sixview2的右键菜单
    shanchuAction = new QAction(tr("删除"),this);
    shanchuAction->setIcon(QIcon(":/image/shanchu.png"));
    connect(shanchuAction,SIGNAL(triggered()),this,SLOT(Decreasing()));
    sixTargetView->addAction(shanchuAction);
    sixTargetView->setContextMenuPolicy(Qt::ActionsContextMenu);

    QHBoxLayout *hlayout1 = new QHBoxLayout;
    hlayout1->addWidget(RecordNumberLabel,0);
    hlayout1->addWidget(sixRecordNumLineEdit,1);
    hlayout1->addWidget(sixFindBtn,1);
    hlayout1->addStretch(7);

    QVBoxLayout *vlayout1 = new QVBoxLayout;
    vlayout1->addLayout(hlayout1);
    vlayout1->addWidget(sixOriginalView);
    vlayout1->addWidget(InstructionLabel);

    QHBoxLayout *hlayout2 = new QHBoxLayout;
    hlayout2->addWidget(OriginalNoLabel,0);
    hlayout2->addWidget(sixOriginalNoLineEdit,1);
    hlayout2->addWidget(CustomerLabel,0);
    hlayout2->addWidget(sixCustomerLineEdit,2);
    hlayout2->addWidget(EngineerLabel,0);
    hlayout2->addWidget(sixEngineerLineEdit,2);
    hlayout2->addWidget(VehicleLabel,0);
    hlayout2->addWidget(sixVehicleLineEdit,1);
    hlayout2->addWidget(ShippingVolumeLabel,0);
    hlayout2->addWidget(sixShippingVolumeLineEdit,1);
    hlayout2->addWidget(ReceiptVolumeLabel,0);
    hlayout2->addWidget(sixReceiptVolumeLineEdit,1);
    hlayout2->addWidget(sixConfirmTransferBtn,1);
    hlayout2->addStretch(7);


    QVBoxLayout *vlayout2 = new QVBoxLayout;
    vlayout2->addLayout(hlayout2);
    vlayout2->addSpacing(10);
    vlayout2->addWidget(TargetNoLabel,0);
    vlayout2->addWidget(sixTargetView);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(vlayout1);
    vlayout->addSpacing(10);
    vlayout->addLayout(vlayout2);

    zhuanliaochuli->setLayout(vlayout);
    tabWidget->addTab(zhuanliaochuli,tr("转料处理"));
}

void shengchanrenwuanpaiDlg::creatTabPage7()
{
    SQL7 = "select OperatingTime 操作时间,ReturnRecordNo 退回记录号,ReturnVehicle 退回车牌号,ReturnEngineer 退回工程名称,ReturnStrengthGrade 退回等级,\
            ReturnShippingVolume 退回发货方量,ReturnReceiptVolume 退回签收方量,ReturnProductVolume 退回生产方量,ReturnVolume 退回方量,ReturnZuoFeiVolume 作废方量,\
            IntoRecordNo 转入记录号,IntoVehicle 转入车牌号,IntoEngineer 转入工程名称,IntoStrengthGrade 转入等级,IntoVolume 转入方量,IntoBufangVolume 补方方量,IntoShippingVolume 转入发货方量,\
            Type 剩转类型,Operator 操作人 from TransferMaterialRecord limit 0";

    QLabel *label1  = new QLabel(tr("日期"),this);
    label1->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label2  = new QLabel(tr("-"),this);
    label2->setAlignment(Qt::AlignCenter);

    sevendateTimeEdit1 = new QDateTimeEdit(this);
    sevendateTimeEdit1->setDate(QDate::currentDate());
    sevendateTimeEdit1->setTime(QTime::fromString("00:00:00","hh:mm:ss"));
    sevendateTimeEdit1->setCalendarPopup(true);
    sevendateTimeEdit2 = new QDateTimeEdit(this);
    sevendateTimeEdit2->setDate(QDate::currentDate().addDays(1));
    sevendateTimeEdit2->setTime(QTime::fromString("00:00:00","hh:mm:ss"));
    sevendateTimeEdit2->setCalendarPopup(true);

    sevenBtn = new QPushButton(tr("查询"),this);
    connect(sevenBtn,SIGNAL(clicked()),this,SLOT(on_sevenChaxunBtn()));

    sevenview = new QTableView(this);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(label1,0);
    hlayout->addWidget(sevendateTimeEdit1,1);
    hlayout->addWidget(label2,0);
    hlayout->addWidget(sevendateTimeEdit2,1);
    hlayout->addWidget(sevenBtn,1);
    hlayout->addStretch(6);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(sevenview);

    zhuanliaojilu->setLayout(vlayout);
    tabWidget->addTab(zhuanliaojilu,tr("剩转料记录"));
}

void shengchanrenwuanpaiDlg::creatTabPage8()
{
    SQL8 = "SELECT\
            RecordNumber 出车单号,\
            Unit 生产机组,\
            DeliveryVehicle 车号,\
            ProductionTime 出站时间,\
            MID(TIMEDIFF(NOW(), ProductionTime),1,8) 耗时,\
            FaHuoCustomer 客户,\
            Engineering 工程,\
            PouringPosition 浇筑部位,\
            StrengthGrade 强度等级,\
            PouringMethod 浇筑方法,\
            ShippingVolume 发货方量,\
            CumulativeNumber 本车车次,\
            CumulativeVolume 累计方量\
        FROM\
            (SELECT * FROM ProductionNotice ORDER BY RecordNumber DESC) A\
        LEFT JOIN (SELECT * FROM inHouseVehicle) B ON (A.DeliveryVehicle = B.CheNo)\
        WHERE\
            TIMESTAMPDIFF(MINUTE,ProductionTime,NOW()) < 300 AND B.CheNo IS NULL and A.WhetherCancel!='转出'\
        GROUP BY\
            DeliveryVehicle\
        ORDER BY\
            Engineering,\
            FaHuoCustomer,\
            TaskList,\
            OutboundTime desc limit 0;";


    eightview = new QTableView(this);

    eightBtn = new QPushButton(tr("刷新"),this);
    eightBtn->setFixedWidth(150);
    connect(eightBtn,SIGNAL(clicked()),this,SLOT(on_eightShuaXin()));

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(eightBtn,1,Qt::AlignLeft);
    vlayout->addWidget(eightview);

    gongdicheliangfenbu->setLayout(vlayout);
    tabWidget->addTab(gongdicheliangfenbu,tr("工地车辆分布情况"));
}

void shengchanrenwuanpaiDlg::creatTabPage9()
{
    SQL9 = "select RecordNumber 发货序号,TaskList 任务单,Customer 客户名称,FaHuoCustomer 发货客户,Engineering 工程,PouringPosition 浇筑部位,\
            PouringMethod 浇筑方法,StrengthGrade 强度等级,ShippingVolume 发货方量,IF(VolumeMortar='',0,VolumeMortar) 砂浆方量,DeliveryVehicle 送货车辆,Driver 司机,\
            CumulativeNumber 累计车次,CumulativeVolume 累计方量,ProductionTime 生产时间,Slump 坍落度,Contacts 联系人,ContactNumber 联系电话,\
            WhetherDelivery 是否打印出车单,SupplyTime 作废时间,ProductionDepartment 生产部门,Unit 机组,ActualProductionVolume 实际生产方量,\
            RemainingMaterial 剩料,InformPeople 作废操作人 from zuofeiNotice order by RecordNumber desc limit 0;";

    ninecheckBox1 = new QCheckBox(tr("工程"),this);
    ninecheckBox2 = new QCheckBox(tr("生产时间"),this);
    ninecheckBox3 = new QCheckBox(tr("车辆"),this);
    ninecheckBox4 = new QCheckBox(tr("生产机组"),this);
    ninecheckBox5 = new QCheckBox(tr("通知人"),this);

    ninecombo1 = new myComboBox(this);

    ninecombo2 = new QComboBox(this);
    ninecombo2->setEditable(true);

    ninecombo3 = new QComboBox(this);

    ninecombo4 = new QComboBox(this);

    nineview = new QTableView(this);

    QLabel *label = new QLabel(tr("--"),this);
    label->setAlignment(Qt::AlignCenter);

    ninedate1 = new QDateTimeEdit(this);
    ninedate1->setDate(QDate::currentDate());
    ninedate1->setCalendarPopup(true);

    ninedate2 = new QDateTimeEdit(this);
    ninedate2->setDate(QDate::currentDate().addDays(1));
    ninedate2->setCalendarPopup(true);

    nineBtn = new QPushButton(tr("查询"),this);
    connect(nineBtn,SIGNAL(clicked()),this,SLOT(on_ninechaxun()));

    QGridLayout *layout1 = new QGridLayout;
    layout1->addWidget(ninecheckBox1,0,0);
    layout1->addWidget(ninecombo1,0,1);
    layout1->addWidget(ninecheckBox2,0,2);
    layout1->addWidget(ninedate1,0,3);
    layout1->addWidget(label,0,4);
    layout1->addWidget(ninedate2,0,5);
    layout1->addWidget(nineBtn,0,6,2,1,Qt::AlignVCenter);
    layout1->addWidget(ninecheckBox3,1,0);
    layout1->addWidget(ninecombo2,1,1);
    layout1->addWidget(ninecheckBox4,1,2);
    layout1->addWidget(ninecombo3,1,3);
    layout1->addWidget(ninecheckBox5,1,4);
    layout1->addWidget(ninecombo4,1,5);
    layout1->setColumnStretch(0,0);
    layout1->setColumnStretch(1,1);
    layout1->setColumnStretch(2,0);
    layout1->setColumnStretch(3,1);
    layout1->setColumnStretch(4,0);
    layout1->setColumnStretch(5,1);
    layout1->setColumnStretch(6,1);
    layout1->setColumnStretch(7,3);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addLayout(layout1);
    vlayout->addWidget(nineview);

    zuofeijilu->setLayout(vlayout);
    tabWidget->addTab(zuofeijilu,tr("作废记录查询"));
}

void shengchanrenwuanpaiDlg::setModelStyle(QStandardItemModel *model)
{
    int columnCount = model->columnCount();
    int rowCount    = model->rowCount();
    for(int i = 0; i < rowCount; i++){
        for(int j = 0; j < columnCount; j++){
            if(model->item(i,9)->text().toDouble() == 0){
                model->item(i,j)->setBackground(QBrush(QColor(200,100,100)));//红
            }else{
                if(model->item(i,9)->text().toDouble() < model->item(i,8)->text().toDouble()){
                    model->item(i,j)->setBackground(QBrush(QColor(100,200,200)));//蓝
                }
                if(model->item(i,9)->text().toDouble() >= model->item(i,8)->text().toDouble()){
                    model->item(i,j)->setBackground(QBrush(QColor(255,255,0)));//黄
                }
            }
        }
    }
}

void shengchanrenwuanpaiDlg::setPage3ModelStyle(QStandardItemModel *model)
{
    int columnCount = model->columnCount();
    int rowCount    = model->rowCount();
    for(int i = 0; i < rowCount; i++){
        for(int j = 0; j < columnCount; j++){
            if(model->item(i,24)->text() == "转入"){
                model->item(i,j)->setBackground(QBrush(QColor(100,200,100)));//绿
            }
            else if(model->item(i,24)->text() == "转出"){
                model->item(i,j)->setBackground(QBrush(QColor(200,100,100)));//红
            }
            else{
                model->item(i,j)->setBackground(QBrush(QColor(255,255,255)));//白
            }
        }
    }
}

void shengchanrenwuanpaiDlg::ShowSupplyclick()
{
    disconnect(oneShippingVolumeLineEdit,SIGNAL(textChanged(QString)),this,SLOT(ActualProductionVolume()));
    disconnect(oneMotarVolumeLineEdit,SIGNAL(textChanged(QString)),this,SLOT(ActualProductionVolume()));
    disconnect(oneXuKaiVolumeLineEdit,SIGNAL(textChanged(QString)),this,SLOT(ActualProductionVolume()));
    disconnect(oneRemainingMaterialLineEdit,SIGNAL(textChanged(QString)),this,SLOT(ActualProductionVolume()));

    zuofeiBtn->setEnabled(true);
    zhuanliaoBtn->setEnabled(true);
    oneShippingVolumeLineEdit->setEnabled(true);
    oneMotarVolumeLineEdit->setEnabled(true);
    oneRemainingMaterialLineEdit->setEnabled(true);
    oneUnitCombox->setEnabled(true);
    oneVehicleCombox->setEnabled(true);
    oneVehicleCombox->setEditable(true);
    oneDriverCombox->setEnabled(true);
    tongzhishengchanBtn->setEnabled(true);
    chexiaoshengchanBtn->setEnabled(false);

    oneAnPaiCheCiLineEdit->setEnabled(true);
    oneAnPaiFlLineEdit->setEnabled(true);

    oneUnitCombox->setCurrentIndex(0);



    int row = view->currentIndex().row();
    oneProductDatetimeEdit->setDateTime(QDateTime::currentDateTime());
    oneTaskListLineEdit->setText(model->item(row,0)->text());
    oneRealCustomerLineEdit->setText(model->item(row,1)->text());
    oneFaHuoCustomerLineEdit->setText(model->item(row,2)->text());
    oneEngineerLineEdit->setText(model->item(row,3)->text());
    onePouringPositionLineEdit->setText(model->item(row,4)->text());
//    onePouringMethodLineEdit->setText(model->item(row,5)->text());
    jiaozhufangfa = model->item(row,5)->text();
    oneStrengthGradeLineEdit->setText(model->item(row,6)->text());
    peihebimubanmingcheng = model->item(row,7)->text();
    PlannedQuantity = model->item(row,8)->text();
    oneLeiJiFLLineEdit->setText(model->item(row,9)->text());
    oneLeijiCheCiLineEdit->setText(model->item(row,10)->text());
    oneAnPaiFlLineEdit->setText(model->item(row,11)->text());
    yianpairenwuliang = model->item(row,11)->text();
    oneAnPaiCheCiLineEdit->setText(model->item(row,12)->text());
    yianpaicheci = model->item(row,12)->text();
    oneContactLineEdit->setText(model->item(row,13)->text());
    oneTelephoneLineEdit->setText(model->item(row,14)->text());
    oneSupplyTimeLineEdit->setText(model->item(row,15)->text());
    oneSlumpLineEdit->setText(model->item(row,16)->text());
    oneEngineerLineEdit->setToolTip(oneEngineerLineEdit->text());
    ContractNumber = model->item(row,18)->text();
    oneConstructionSiteLineEdit->setText(model->item(row,19)->text());
    onePouringMethodLineEdit->setText(model->item(row,5)->text());

    oneShippingVolumeLineEdit->clear();
    oneMotarVolumeLineEdit->clear();
    ActualProductionVolumeLineEdit->clear();
    oneRemainingMaterialLineEdit->clear();
    oneXuKaiVolumeLineEdit->clear();

    oneVehicleCombox->setCurrentIndex(0);
    oneDriverCombox->setCurrentIndex(0);
    oneProductDatetimeEdit->setDateTime(QDateTime::currentDateTime());

    connect(oneShippingVolumeLineEdit,SIGNAL(textChanged(QString)),this,SLOT(ActualProductionVolume()));
    connect(oneMotarVolumeLineEdit,SIGNAL(textChanged(QString)),this,SLOT(ActualProductionVolume()));
    connect(oneXuKaiVolumeLineEdit,SIGNAL(textChanged(QString)),this,SLOT(ActualProductionVolume()));
    connect(oneRemainingMaterialLineEdit,SIGNAL(textChanged(QString)),this,SLOT(ActualProductionVolume()));

    QString searchSQL = QString("select CONCAT('上车信息:  车牌号:',DeliveryVehicle,' ',Driver,'  发货方量:',ShippingVolume,'  砂浆方量:',VolumeMortar,\
                                '  剩料:',RemainingMaterial,'  生产方量:',ActualProductionVolume,'  生产时间:',ProductionTime,'  机组:',Unit ) from \
                                ProductionNotice where TaskList='%1' and ActualProductionVolume!='0' order by ProductionTime desc limit 1").arg(oneTaskListLineEdit->text());
    lastVehicleInfoLabel->setText(db.sql_fetchrow_plus(searchSQL,0));
}

void shengchanrenwuanpaiDlg::ShowSupplyclick2()
{
    oneShippingVolumeLineEdit->setEnabled(false);
    oneShippingVolumeLineEdit->setStyleSheet("color:black");
    oneMotarVolumeLineEdit->setEnabled(false);
    oneMotarVolumeLineEdit->setStyleSheet("color:black");
    oneRemainingMaterialLineEdit->setEnabled(false);
    oneRemainingMaterialLineEdit->setStyleSheet("color:black");
    zuofeiBtn->setEnabled(false);
    zhuanliaoBtn->setEnabled(false);
    oneProductPartCombox->setEnabled(false);
    oneProductPartCombox->setStyleSheet("color:black");
    oneUnitCombox->setEnabled(false);
    oneUnitCombox->setStyleSheet("color:black");
    oneVehicleCombox->setEnabled(false);
    oneVehicleCombox->setStyleSheet("color:black");
    oneVehicleCombox->setEditable(true);
    oneDriverCombox->setEnabled(false);
    oneDriverCombox->setStyleSheet("color:black");
    tongzhishengchanBtn->setEnabled(false);
    chexiaoshengchanBtn->setEnabled(true);

    oneAnPaiCheCiLineEdit->setEnabled(false);
    oneAnPaiFlLineEdit->setEnabled(false);
    oneLeiJiFLLineEdit->setEnabled(false);
    oneLeijiCheCiLineEdit->setEnabled(false);

    int row = twoview->currentIndex().row();
    oneRealCustomerLineEdit->setText(twomodel->item(row,1)->text());
    oneFaHuoCustomerLineEdit->setText(twomodel->item(row,2)->text());
    oneUnitCombox->setCurrentText(twomodel->item(row,3)->text());
    oneEngineerLineEdit->setText(twomodel->item(row,4)->text());
    onePouringPositionLineEdit->setText(twomodel->item(row,5)->text());
    onePouringMethodLineEdit->setText(twomodel->item(row,6)->text());
    oneStrengthGradeLineEdit->setText(twomodel->item(row,7)->text());

    oneMotarVolumeLineEdit->setText(twomodel->item(row,9)->text());
    oneVehicleCombox->setCurrentText(twomodel->item(row,10)->text());
    oneDriverCombox->setCurrentText(twomodel->item(row,11)->text());
    oneProductDatetimeEdit->setDateTime(QDateTime::fromString(twomodel->item(row,14)->text(),"yyyy-MM-dd hh:mm"));
    oneSlumpLineEdit->setText(twomodel->item(row,15)->text());
    oneContactLineEdit->setText(twomodel->item(row,16)->text());
    oneTelephoneLineEdit->setText(twomodel->item(row,17)->text());
    oneSupplyTimeLineEdit->setText(twomodel->item(row,19)->text());
    oneProductPartCombox->setCurrentText(twomodel->item(row,20)->text());
    ActualProductionVolumeLineEdit->setText(twomodel->item(row,22)->text());
    oneRemainingMaterialLineEdit->setText(twomodel->item(row,23)->text());
    oneTaskListLineEdit->setText(twomodel->item(row,25)->text());
    oneConstructionSiteLineEdit->setText(twomodel->item(row,26)->text());

    QString chaxunSQL = QString("select ContractCompletion,fahuocheci,CumulativeNumber,HasBeenUnderTask from ProductionTaskList where TaskNumber='%1';").arg(oneTaskListLineEdit->text());
    oneLeiJiFLLineEdit->setText(db.sql_fetchrow_plus(chaxunSQL.toStdString().data(),0));
    oneLeijiCheCiLineEdit->setText(db.sql_fetchrow_plus(chaxunSQL.toStdString().data(),1));
    oneAnPaiFlLineEdit->setText(db.sql_fetchrow_plus(chaxunSQL.toStdString().data(),3));
    oneAnPaiCheCiLineEdit->setText(db.sql_fetchrow_plus(chaxunSQL.toStdString().data(),2));

    fahuojiluhao = twomodel->item(row,0)->text();//发货记录号

    oneShippingVolumeLineEdit->setText(twomodel->item(row,8)->text());

    tabWidget->setCurrentIndex(0);
}

void shengchanrenwuanpaiDlg::on_doubleClickTwoProductingView(QModelIndex index)
{
    twoProductingRecordNoLineEdit->setText(index.model()->index(index.row(),0).data().toString());
    twoUnitNo = index.model()->index(index.row(),4).data().toString().left(1);
}

void shengchanrenwuanpaiDlg::ShowSupplyclick3()
{
    int row = threeview->currentIndex().row();
    QString searchSQL = QString("select RecordNumber 发货序号,DeliveryVehicle 送货车辆,Unit 机组,ReceiptVolume 发货方量,CumulativeNumber 累计车次,CumulativeVolume 累计方量,OutboundTime 出站时间,WhetherCancel 转料状态 from ProductionNotice where TaskList='%1'")
            .arg(threemodel->item(row,22)->text());
    db.showview(searchSQL,threeProductNoticeView,&threeProductNoticeModel);

    setPage3ModelStyle(threemodel);

    int columnCount1 = threemodel->columnCount();
    for(int i = 0; i < columnCount1; i++){
        threemodel->item(row,i)->setBackground(QBrush(QColor(114,184,254)));//蓝
    }

    int columnCount2 = threeProductNoticeModel->columnCount();
    int rowCount2    = threeProductNoticeModel->rowCount();
    for(int i = 0; i < rowCount2; i++){
        for(int j = 0; j < columnCount2; j++){
            if(threeProductNoticeModel->item(i,0)->text() == threemodel->item(row,0)->text()){
                threeProductNoticeModel->item(i,j)->setBackground(QBrush(QColor(114,184,254)));//蓝
            }
            else if(threeProductNoticeModel->item(i,7)->text() == "转出"){
                threeProductNoticeModel->item(i,j)->setBackground(QBrush(QColor(200,100,100)));//红
            }
            else if(threeProductNoticeModel->item(i,7)->text() == "转入"){
                threeProductNoticeModel->item(i,j)->setBackground(QBrush(QColor(100,200,100)));//绿
            }
            else{
                threeProductNoticeModel->item(i,j)->setBackground(QBrush(QColor(255,255,255)));//白
            }
        }
    }
}

void shengchanrenwuanpaiDlg::ShowSupplyclick4()
{
    int row = fourview->currentIndex().row();
    fourRecordNoLineEdit->setText(fourmodel->item(row,0)->text());
    fourRealCustomerLineEdit->setText(fourmodel->item(row,2)->text());
    fourFaHuoCustomerLineEdit->setText(fourmodel->item(row,3)->text());
    fourEngineerLineEdit->setText(fourmodel->item(row,4)->text());
    fourTongVolumeLineEdit->setText(fourmodel->item(row,8)->text());
    fourMotarLineEdit->setText(fourmodel->item(row,9)->text());
    fourUnitNoComBox->setCurrentText(fourmodel->item(row,21)->text());
    cheHao = fourmodel->item(row,10)->text();
}

void shengchanrenwuanpaiDlg::ShowSupplyclick6()
{
    int row = sixOriginalView->currentIndex().row();
    sixOriginalNoLineEdit->setText(sixOriginalModel->item(row,0)->text());
    sixCustomerLineEdit->setText(sixOriginalModel->item(row,2)->text());
    sixEngineerLineEdit->setText(sixOriginalModel->item(row,3)->text());
    sixVehicleLineEdit->setText(sixOriginalModel->item(row,11)->text());
    sixShippingVolumeLineEdit->setText(sixOriginalModel->item(row,7)->text());
    sixTaskNumber = sixOriginalModel->item(row,1)->text();
    sixBiaoHao = sixOriginalModel->item(row,6)->text();
    sixShengChanLiang = sixOriginalModel->item(row,8)->text();
}

void shengchanrenwuanpaiDlg::oneVehicleComboxResponse()
{
    oneVehicleCombox->setCurrentText(oneVehicleCombox->currentText().section(" ",0,0));

    QString searchCheState = QString("select CheState from inHouseVehicle where CheNo='%1'").arg(oneVehicleCombox->currentText());
    bool whetherRemainMaterial = db.sql_fetchrow_plus(searchCheState,0).contains("剩料");
    if(whetherRemainMaterial){
        QString searchSL = QString("select Volume,DanHao from TankWeighing where LicensePlateNumber='%1' and whetherCancel='否' and RecordNumber like '%sl%' \
                                   order by GrossWeightTime desc limit 1;").arg(oneVehicleCombox->currentText().section(" ",0,0));
        oneRemainingMaterialLineEdit->setText(db.sql_fetchrow_plus(searchSL,0));
        shengliaodanhao = db.sql_fetchrow_plus(searchSL.toStdString().data(),1);
    }else{
        oneRemainingMaterialLineEdit->setText("0");
    }

    oneDriverCombox->clear();
    QString searchDriverSQL = QString("select VehicleXingHao,Driver1,Driver2 from ConcreteVehicleInformation where Vehiclenumber='%1';").arg(oneVehicleCombox->currentText());
    db.sql_fillComboBoxItem2(searchDriverSQL,oneDriverCombox);

    QString searchSQL = QString("select Driver1,VehicleXingHao from ConcreteVehicleInformation where Vehiclenumber='%1';").arg(oneVehicleCombox->currentText());
    QStringList resultStr = db.CreatStrList(searchSQL);
    if(resultStr.count() == 2){
        oneDriverCombox->setCurrentText(resultStr.at(0));
        VehicleVolume = resultStr.at(1);
        VehicleVolume = VehicleVolume.replace(QString("方"),"");
    }
    //填充最大方量
    QString searchZuidaFanglangSQL = QString("select VehicleXingHao from ConcreteVehicleInformation where Vehiclenumber='%1';").arg(oneVehicleCombox->currentText());
    QString ZuiDaFangLiang = db.sql_fetchrow_plus(searchZuidaFanglangSQL,0);

    oneShippingVolumeLineEdit->setText(ZuiDaFangLiang.left(ZuiDaFangLiang.length() - 1));


}

void shengchanrenwuanpaiDlg::ActualProductionVolume()
{
    //发货方量
    double num1 = oneShippingVolumeLineEdit->text().toDouble();
    //剩料
    double num2 = 0;
    if(!(oneRemainingMaterialLineEdit->text().isEmpty())){
        num2 = oneRemainingMaterialLineEdit->text().toDouble();
    }

    //已安排方量
    double num3 = yianpairenwuliang.toDouble() + oneShippingVolumeLineEdit->text().toDouble();

    //已安排车次
    int num4 = 0;
    if(oneShippingVolumeLineEdit->text().isEmpty()){
        num4 = yianpaicheci.toInt();
    }else{
        num4 = yianpaicheci.toInt() + 1;
    }

    //砂浆方量
    double num5 = 0;

    //虚开方
    double num6 = 0;
    if(!(oneXuKaiVolumeLineEdit->text().isEmpty())){
        num6 = oneXuKaiVolumeLineEdit->text().toDouble();
    }

    ActualProductionVolumeLineEdit->setText(QString::number(num1 - num2 - num5 - num6));
    oneAnPaiFlLineEdit->setText(QString::number(num3));
    oneAnPaiCheCiLineEdit->setText(QString::number(num4));
}

void shengchanrenwuanpaiDlg::on_oneAddCheliangBtn()
{
    if(oneAddCheliangLineEdit->text().isEmpty()){
        return;
    }
    QString SelectCheliangSQL = QString("select LicensePlate from concretevehicleinformation where Vehiclenumber = '%1'").arg(oneAddCheliangLineEdit->text());

    QString AddCheliangSQL = QString("insert into inhousevehicle (ID,CheNo,CheTime,CheState) values('%1','%2','%3','普通');")
            .arg(db.sql_fetchrow_plus(SelectCheliangSQL,0),oneAddCheliangLineEdit->text(),QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    int res = db.sql_exec(AddCheliangSQL);
    if(res == -1){
        QMessageBox::information(this,tr("提示信息"),tr("添加车辆失败"),0,0,0);;
        return;
    }else{
        QMessageBox::information(this,tr("提示信息"),tr("添加车辆成功"),0,0,0);
        oneAddCheliangLineEdit->clear();
    }
}

void shengchanrenwuanpaiDlg::on_oneDelCheliangBtn()
{
    if(oneDelCheliangLineEdit->text().isEmpty()){
        return;
    }
    QString DelCheliangSQL = QString("delete from inhousevehicle where CheNo = '%1';")
            .arg(oneDelCheliangLineEdit->text());
    int res = db.sql_exec(DelCheliangSQL);
    if(res == -1){
        QMessageBox::information(this,tr("提示信息"),tr("删除车辆失败"),0,0,0);;
        return;
    }else{
        QMessageBox::information(this,tr("提示信息"),tr("删除车辆成功"),0,0,0);
        oneDelCheliangLineEdit->clear();
    }
}

void shengchanrenwuanpaiDlg::on_oneBuDaShuiPiaoBtn()
{
    if(oneTaskListLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择一个任务单"),0,0,0);
        return;
    }
    if(oneProductPartCombox->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择生产部门"),0,0,0);
        return;
    }
    if(oneUnitCombox->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择生产机组"),0,0,0);
        return;
    }
    if(oneVehicleCombox->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择送货车辆"),0,0,0);
        return;
    }




    int res = QMessageBox::question(this,tr("提示信息"),tr("通知机组生产？"),QMessageBox::Yes,QMessageBox::No);
    if(res == QMessageBox::Yes){
        double SUMWGT = 0;
        QString searchrongzhongSQL = QString("select MAT1,MAT2,MAT3,MAT4,MAT5,MAT6,MAT7,MAT8,MAT9,MAT10,MAT11,MAT12,MAT13,MAT14,MAT15,MAT16,MAT17,MAT18,\
                                              MAT19,MAT20 from rwPEIFANG where TaskList='%1' AND StateNo='%2'")
                                .arg(oneTaskListLineEdit->text(),QString::number(oneUnitCombox->currentIndex()));
        QStringList resultStr = db.CreatStrList(searchrongzhongSQL);
        if(resultStr.count() == 20){
            for(int i = 0; i < 20; i++){
                SUMWGT += resultStr.at(i).toDouble();
            }
        }
        rongzhong = QString::number(SUMWGT);

        oneShippingVolumeLineEdit->setText("0");

        //事务开始
        db.sql_exec("begin");

        QString shifouxianjin = QString("select Remarks from customerfiles where CustomerName = '%1'").arg(oneRealCustomerLineEdit->text());
        if(db.sql_fetchrow_plus(shifouxianjin,0) == "现金"){
            shifouxianjin = "是";
            qDebug()<<shifouxianjin;
        }else{
            shifouxianjin = "否";
            qDebug()<<shifouxianjin;
        }



        //插入单车生产任务
        QString saveSQL = QString("insert into ProductionNotice (TaskList,StrengthGrade,Contacts,Customer,PouringPosition,ContactNumber,Engineering,PouringMethod,\
                                  ArrangedVolume,ConstructionSite,Slump,SupplyTime,ProductionDepartment,Unit,ShippingVolume,VolumeMortar,ProductionTime,DeliveryVehicle,\
                                  Driver,ActualProductionVolume,RemainingMaterial,InformPeople,TemplateName,Capacity,ReceiptVolume,ContractNumber,OutboundTime,\
                                  CumulativeNumber,CumulativeVolume,FaHuoCustomer) values ('%1','%2','%3','%4','%5','%6','%7','%8','%9','%10','%11','%12','%13',\
                                  '%14','%15','%16','%17','%18','%19','%20','%21','%22','%23','%24','%25','%26','%27','%28','%29','%30','%31');")
        .arg(oneTaskListLineEdit->text(),oneStrengthGradeLineEdit->text(),oneContactLineEdit->text(),oneRealCustomerLineEdit->text(),onePouringPositionLineEdit->text(),oneTelephoneLineEdit->text(),\
             oneEngineerLineEdit->text(),onePouringMethodLineEdit->text(),oneLeiJiFLLineEdit->text())
        .arg(oneConstructionSiteLineEdit->text(),oneSlumpLineEdit->text(),oneSupplyTimeLineEdit->text(),oneProductPartCombox->currentText(),oneUnitCombox->currentText(),\
             "水票",oneMotarVolumeLineEdit->text(),oneProductDatetimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"),oneVehicleCombox->currentText())
        .arg(oneDriverCombox->currentText(),ActualProductionVolumeLineEdit->text(),oneRemainingMaterialLineEdit->text(),userName,peihebimubanmingcheng,rongzhong,oneShippingVolumeLineEdit->text())
        .arg(ContractNumber,oneProductDatetimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"),oneAnPaiCheCiLineEdit->text(),oneAnPaiFlLineEdit->text(),oneFaHuoCustomerLineEdit->text()).arg(shifouxianjin);
        res = db.sql_exec(saveSQL);
        if(res == -1){
            db.sql_exec("rollback");
            return;
        }
        //更新生产任务单中的车次信息
        QString updateSQL = QString("update ProductionTaskList set CumulativeNumber='%1' where TaskNumber='%2';")
                .arg(oneAnPaiCheCiLineEdit->text(),oneTaskListLineEdit->text());
        res = db.sql_exec(updateSQL);
        if(res == -1){
            db.sql_exec("rollback");
            return;
        }

        disconnect(oneShippingVolumeLineEdit,SIGNAL(textChanged(QString)),this,SLOT(ActualProductionVolume()));
        disconnect(oneRemainingMaterialLineEdit,SIGNAL(textChanged(QString)),this,SLOT(ActualProductionVolume()));


        //事务结束
        db.sql_exec("commit");


        if(oneRemainingMaterialLineEdit->text().toDouble()>0 && oneXuKaiVolumeLineEdit->text().toDouble()>0){
            sockClient->send_Msg1("发货确认",QString("%4#机组:%1车发货%2方(剩料%3方)(虚开%5方)")
                                  .arg(oneVehicleCombox->currentText(),oneShippingVolumeLineEdit->text(),oneRemainingMaterialLineEdit->text())
                                  .arg(oneUnitCombox->currentIndex()).arg(oneXuKaiVolumeLineEdit->text()).toStdString().data());
        }
        else if(oneRemainingMaterialLineEdit->text().toDouble()>0){
            sockClient->send_Msg1("发货确认",QString("%4#机组:%1车发货%2方(剩料%3方)")
                                  .arg(oneVehicleCombox->currentText(),oneShippingVolumeLineEdit->text(),oneRemainingMaterialLineEdit->text()).arg(oneUnitCombox->currentIndex()).toStdString().data());
        }
        else if(oneXuKaiVolumeLineEdit->text().toDouble()>0){
            sockClient->send_Msg1("发货确认",QString("%4#机组:%1车发货%2方(虚开%3方)")
                                  .arg(oneVehicleCombox->currentText(),oneShippingVolumeLineEdit->text(),oneXuKaiVolumeLineEdit->text()).arg(oneUnitCombox->currentIndex()).toStdString().data());
        }
        else{
            sockClient->send_Msg1("发货确认",QString("%4#机组:%1车发货%2方")
                                  .arg(oneVehicleCombox->currentText(),oneShippingVolumeLineEdit->text()).arg(oneUnitCombox->currentIndex()).toStdString().data());
        }


        QMessageBox::information(this,tr("提示信息"),tr("通知成功"),0,0,0);
        sockClient->send_Msg3();//发送刷新消息

        oneTaskListLineEdit->clear();
        oneStrengthGradeLineEdit->clear();
        oneContactLineEdit->clear();
        oneRealCustomerLineEdit->clear();
        onePouringPositionLineEdit->clear();
        oneTelephoneLineEdit->clear();
        oneEngineerLineEdit->clear();
        onePouringMethodLineEdit->clear();
        oneLeiJiFLLineEdit->clear();
        oneFaHuoCustomerLineEdit->clear();
        oneSlumpLineEdit->clear();
        oneSupplyTimeLineEdit->clear();
        oneShippingVolumeLineEdit->clear();
        oneMotarVolumeLineEdit->clear();
        ActualProductionVolumeLineEdit->clear();
        oneRemainingMaterialLineEdit->clear();
        oneLeijiCheCiLineEdit->clear();
        oneAnPaiFlLineEdit->clear();
        oneAnPaiCheCiLineEdit->clear();
        oneXuKaiVolumeLineEdit->clear();
        oneConstructionSiteLineEdit->clear();

        oneUnitCombox->setCurrentIndex(0);
        oneVehicleCombox->setCurrentIndex(0);
        oneDriverCombox->setCurrentIndex(0);


    }
    else if(res == QMessageBox::No){
        return;
    }
}

void shengchanrenwuanpaiDlg::on_qitaxinxiBtn()
{
    shengchanxinxiDlg *shengchanxinxidlg = new shengchanxinxiDlg(oneTaskListLineEdit->text(),this);
    shengchanxinxidlg->exec();
    delete shengchanxinxidlg;
}

void shengchanrenwuanpaiDlg::on_tongzhishengchan()
{
    if(oneTaskListLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择一个任务单"),0,0,0);
        return;
    }
    if(oneProductPartCombox->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择生产部门"),0,0,0);
        return;
    }
    if(oneUnitCombox->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择生产机组"),0,0,0);
        return;
    }
    if(oneVehicleCombox->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择送货车辆"),0,0,0);
        return;
    }
    if(oneShippingVolumeLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请指定生产方量"),0,0,0);
        return;
    }
    if(onePouringMethodLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请指定浇筑方式"),0,0,0);
        return;
    }

    if(oneLeiJiFLLineEdit->text().toDouble() + oneShippingVolumeLineEdit->text().toDouble() != oneAnPaiFlLineEdit->text().toDouble()){
        int res = QMessageBox::question(this,tr("提示信息"),tr("累计方量异常，是否通知生产？"),QMessageBox::Yes,QMessageBox::No);
        if(res == QMessageBox::Yes){

        }else{
            return;
        }
    }

    if(oneLeijiCheCiLineEdit->text().toInt() + 1 != oneAnPaiCheCiLineEdit->text().toInt()){
        int res = QMessageBox::question(this,tr("提示信息"),tr("累计车次异常，是否通知生产？"),QMessageBox::Yes,QMessageBox::No);
        if(res == QMessageBox::Yes){

        }else{
            return;
        }
    }


    //2018-01-24 add (&& condition)
    if(ActualProductionVolumeLineEdit->text().toDouble() == 0 && oneRemainingMaterialLineEdit->text().toDouble() == 0){
        QMessageBox::information(this,tr("提示信息"),tr("实际生产方量为0，禁止下发单车任务"),0,0,0);
        return;
    }

    QString shifouxianjin = QString("select Remarks from customerfiles where CustomerName = '%1'").arg(oneRealCustomerLineEdit->text());
    if(db.sql_fetchrow_plus(shifouxianjin,0) == "现金"){
        shifouxianjin = "是";
        qDebug()<<shifouxianjin;
    }else{
        shifouxianjin = "否";
        qDebug()<<shifouxianjin;
    }


    int res = QMessageBox::question(this,tr("提示信息"),tr("通知机组生产？"),QMessageBox::Yes,QMessageBox::No);
    if(res == QMessageBox::Yes){
        double SUMWGT = 0;
        QString searchrongzhongSQL = QString("select MAT1,MAT2,MAT3,MAT4,MAT5,MAT6,MAT7,MAT8,MAT9,MAT10,MAT11,MAT12,MAT13,MAT14,MAT15,MAT16,MAT17,MAT18,\
                                              MAT19,MAT20 from rwPEIFANG where TaskList='%1' AND StateNo='%2'")
                                .arg(oneTaskListLineEdit->text(),QString::number(oneUnitCombox->currentIndex()));
        QStringList resultStr = db.CreatStrList(searchrongzhongSQL);
        if(resultStr.count() == 20){
            for(int i = 0; i < 20; i++){
                SUMWGT += resultStr.at(i).toDouble();
            }
        }
        rongzhong = QString::number(SUMWGT);

        //判断本车发货方量最大值
        if(VehicleVolume.toDouble()<ActualProductionVolumeLineEdit->text().toDouble()+oneRemainingMaterialLineEdit->text().toDouble()){
            QMessageBox::information(this,tr("提示信息"),tr("超出本车运输最大方量"),0,0,0);
            return;
        }

        //事务开始
        db.sql_exec("begin");

        //插入单车生产任务
        QString saveSQL = QString("insert into ProductionNotice (TaskList,StrengthGrade,Contacts,Customer,PouringPosition,ContactNumber,Engineering,PouringMethod,\
                                  ArrangedVolume,ConstructionSite,Slump,SupplyTime,ProductionDepartment,Unit,ShippingVolume,VolumeMortar,ProductionTime,DeliveryVehicle,\
                                  Driver,ActualProductionVolume,RemainingMaterial,InformPeople,TemplateName,Capacity,ReceiptVolume,ContractNumber,OutboundTime,\
                                  CumulativeNumber,CumulativeVolume,FaHuoCustomer,MortarTotal) values ('%1','%2','%3','%4','%5','%6','%7','%8','%9','%10','%11','%12','%13',\
                                  '%14','%15','%16','%17','%18','%19','%20','%21','%22','%23','%24','%25','%26','%27','%28','%29','%30','%31');")
        .arg(oneTaskListLineEdit->text(),oneStrengthGradeLineEdit->text(),oneContactLineEdit->text(),oneRealCustomerLineEdit->text(),onePouringPositionLineEdit->text(),oneTelephoneLineEdit->text(),\
             oneEngineerLineEdit->text(),onePouringMethodLineEdit->text(),oneLeiJiFLLineEdit->text())
        .arg(oneConstructionSiteLineEdit->text(),oneSlumpLineEdit->text(),oneSupplyTimeLineEdit->text(),oneProductPartCombox->currentText(),oneUnitCombox->currentText(),\
             oneShippingVolumeLineEdit->text(),oneMotarVolumeLineEdit->text(),oneProductDatetimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"),oneVehicleCombox->currentText())
        .arg(oneDriverCombox->currentText(),ActualProductionVolumeLineEdit->text(),oneRemainingMaterialLineEdit->text(),userName,peihebimubanmingcheng,rongzhong,oneShippingVolumeLineEdit->text())
        .arg(ContractNumber,oneProductDatetimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"),oneAnPaiCheCiLineEdit->text(),oneAnPaiFlLineEdit->text(),oneFaHuoCustomerLineEdit->text(),shifouxianjin);
        res = db.sql_exec(saveSQL);
        if(res == -1){
            db.sql_exec("rollback");
            return;
        }
        //更新生产任务单中的方量信息
        QString updateSQL = QString("update ProductionTaskList set CumulativeNumber='%1',HasBeenUnderTask='%2',PouringMethod='%3',PouringPosition='%4' where TaskNumber='%5';")
                .arg(oneAnPaiCheCiLineEdit->text(),oneAnPaiFlLineEdit->text(),onePouringMethodLineEdit->text(),onePouringPositionLineEdit->text(),oneTaskListLineEdit->text());
        res = db.sql_exec(updateSQL);
        if(res == -1){
            db.sql_exec("rollback");
            return;
        }

        disconnect(oneShippingVolumeLineEdit,SIGNAL(textChanged(QString)),this,SLOT(ActualProductionVolume()));
        disconnect(oneRemainingMaterialLineEdit,SIGNAL(textChanged(QString)),this,SLOT(ActualProductionVolume()));

        QString updateChe = QString("update inHouseVehicle set paiduiState='%1',paiduiTime='%2' where CheNo='%3';")
                .arg(oneUnitCombox->currentIndex()).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"),oneVehicleCombox->currentText());
        res = db.sql_exec(updateChe);
        if(res == -1){
            db.sql_exec("rollback");
            return;
        }


        //事务结束
        db.sql_exec("commit");

        //查找记录单号
        QString searchSQL = QString("select RecordNumber from ProductionNotice where ProductionTime='%1'")
                .arg(oneProductDatetimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
        QString RecordNumber = db.sql_fetchrow_plus(searchSQL,0);

        //2018-01-24 add for RemainingMaterial = ActualProductionVolume
        if(oneRemainingMaterialLineEdit->text().toDouble() !=0 && ActualProductionVolumeLineEdit->text().toDouble() == 0){

            QString updateRN = QString("update ProductionNotice set Confirmor = '是' where RecordNumber = '%1'").arg(RecordNumber);
            qDebug()<<updateRN;
            db.sql_exec(updateRN);
        }
        //更新剩料记录
        if(oneRemainingMaterialLineEdit->text().toDouble() != 0){
            QString updateShengliao = QString("update TransferMaterialRecord set IntoVolume='%1',IntoEngineer='%2',IntoStrengthGrade='%3',IntoShippingVolume='%4',IntoRecordNo='%5',\
                                              Operator='%6',IntoVehicle='%7' where ReturnRecordNo='%8'")
                    .arg(oneRemainingMaterialLineEdit->text(),oneEngineerLineEdit->text(),oneStrengthGradeLineEdit->text(),oneShippingVolumeLineEdit->text(),RecordNumber,userName,
                         oneVehicleCombox->currentText(),shengliaodanhao);
            db.sql_exec(updateShengliao);
        }

        if(oneRemainingMaterialLineEdit->text().toDouble()>0 && oneXuKaiVolumeLineEdit->text().toDouble()>0){
            sockClient->send_Msg1("发货确认",QString("%4#机组:%1车发货%2方(剩料%3方)(虚开%5方)")
                                  .arg(oneVehicleCombox->currentText(),oneShippingVolumeLineEdit->text(),oneRemainingMaterialLineEdit->text())
                                  .arg(oneUnitCombox->currentIndex()).arg(oneXuKaiVolumeLineEdit->text()).toStdString().data());
        }
        else if(oneRemainingMaterialLineEdit->text().toDouble()>0){
            sockClient->send_Msg1("发货确认",QString("%4#机组:%1车发货%2方(剩料%3方)")
                                  .arg(oneVehicleCombox->currentText(),oneShippingVolumeLineEdit->text(),oneRemainingMaterialLineEdit->text()).arg(oneUnitCombox->currentIndex()).toStdString().data());
        }
        else if(oneXuKaiVolumeLineEdit->text().toDouble()>0){
            sockClient->send_Msg1("发货确认",QString("%4#机组:%1车发货%2方(虚开%3方)")
                                  .arg(oneVehicleCombox->currentText(),oneShippingVolumeLineEdit->text(),oneXuKaiVolumeLineEdit->text()).arg(oneUnitCombox->currentIndex()).toStdString().data());
        }
        else{
            sockClient->send_Msg1("发货确认",QString("%4#机组:%1车发货%2方")
                                  .arg(oneVehicleCombox->currentText(),oneShippingVolumeLineEdit->text()).arg(oneUnitCombox->currentIndex()).toStdString().data());
        }

        if(QString::number(yianpaicheci.toInt()+1) != oneAnPaiCheCiLineEdit->text()){
            QString insertSQL = QString("insert into Recording (Name,Content,Optime) values ('%1','%2','%3')").arg(userName,RecordNumber+" 累计车次:"+QString::number(yianpaicheci.toInt()+1)+"→"+oneAnPaiCheCiLineEdit->text(),QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            db.sql_exec(insertSQL);
        }
        if(QString::number(yianpairenwuliang.toDouble()+oneShippingVolumeLineEdit->text().toDouble())!=oneAnPaiFlLineEdit->text()){
            QString insertSQL2 = QString("insert into Recording (Name,Content,Optime) values ('%1','%2','%3')").arg(userName,RecordNumber+" 累计方量:"+QString::number(yianpairenwuliang.toDouble()+oneShippingVolumeLineEdit->text().toDouble())+"→"+oneAnPaiFlLineEdit->text(),QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            db.sql_exec(insertSQL2);
        }
        if(jiaozhufangfa != onePouringMethodLineEdit->text()){
            QString insertSQL2 = QString("insert into Recording (Name,Content,Optime) values ('%1','%2','%3')").arg(userName,RecordNumber+" 浇筑方法:"+jiaozhufangfa+"→"+onePouringMethodLineEdit->text(),QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            db.sql_exec(insertSQL2);
        }


        //插入send单车任务表SendProductNotice
        QString insertSQL = QString("insert into SendProductNotice (RecordNum,Unit) values ('%1','%2');").arg(RecordNumber,QString::number(oneUnitCombox->currentIndex()));
        db.sql_exec(insertSQL);
        on_chaxunrenwudan();
        QMessageBox::information(this,tr("提示信息"),tr("通知成功"),0,0,0);
        sockClient->send_Msg3();//发送刷新消息

        oneTaskListLineEdit->clear();
        oneStrengthGradeLineEdit->clear();
        oneContactLineEdit->clear();
        oneRealCustomerLineEdit->clear();
        onePouringPositionLineEdit->clear();
        oneTelephoneLineEdit->clear();
        oneEngineerLineEdit->clear();
        onePouringMethodLineEdit->clear();
        oneLeiJiFLLineEdit->clear();
        oneFaHuoCustomerLineEdit->clear();
        oneSlumpLineEdit->clear();
        oneSupplyTimeLineEdit->clear();
        oneShippingVolumeLineEdit->clear();
        oneMotarVolumeLineEdit->clear();
        ActualProductionVolumeLineEdit->clear();
        oneRemainingMaterialLineEdit->clear();
        oneLeijiCheCiLineEdit->clear();
        oneAnPaiFlLineEdit->clear();
        oneAnPaiCheCiLineEdit->clear();
        oneXuKaiVolumeLineEdit->clear();
        oneConstructionSiteLineEdit->clear();

        oneUnitCombox->setCurrentIndex(0);
        oneVehicleCombox->setCurrentIndex(0);
        oneDriverCombox->setCurrentIndex(0);


    }
    else if(res == QMessageBox::No){
        return;
    }

}

void shengchanrenwuanpaiDlg::on_chexiaoshengchan()
{
    if(oneTaskListLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择要撤销的任务单"),0,0,0);
        return;
    }

    int res = QMessageBox::question(this,tr("提示信息"),tr("是否要撤销生产任务？"),QMessageBox::Yes,QMessageBox::No);
    if(res == QMessageBox::Yes){

        //加入到作废记录
        QString insertzuofeiSQL = QString("insert into zuofeiNotice (select * from ProductionNotice where RecordNumber=%1)").arg(fahuojiluhao);
        db.sql_exec(insertzuofeiSQL);
        QString updatezuofeiSQL = QString("update zuofeiNotice set SupplyTime='%1',InformPeople='%2' where RecordNumber=%3")
                .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"),userName,fahuojiluhao);
        db.sql_exec(updatezuofeiSQL);

        db.sql_exec("begin;");
        //删除生产通知单
        QString chexiaoSQL = QString("delete from ProductionNotice where RecordNumber=%1;").arg(fahuojiluhao.toInt());
        int res = db.sql_exec(chexiaoSQL);
        if(res == -1){
            db.sql_exec("rollback");
            return;
        }
        QString updateNoticeSQL = QString("UPDATE ProductionNotice SET CumulativeNumber=CumulativeNumber-'1',CumulativeVolume=CumulativeVolume-'%1' \
                                          where TaskList='%2' and RecordNumber>%3")
                .arg(oneShippingVolumeLineEdit->text(),oneTaskListLineEdit->text(),fahuojiluhao);
        res = db.sql_exec(updateNoticeSQL);
        if(res == -1){
            db.sql_exec("rollback");
            return;
        }
        //更新任务单中的累计方量和累积车次
        double yianpaifangliang = oneAnPaiFlLineEdit->text().toDouble() - oneShippingVolumeLineEdit->text().toDouble();
        QString updateSQL = QString("update ProductionTaskList set HasBeenUnderTask='%1',CumulativeNumber=CumulativeNumber-'1' where TaskNumber='%3';")
                .arg(QString::number(yianpaifangliang),oneTaskListLineEdit->text());
        res = db.sql_exec(updateSQL);
        if(res == -1){
            db.sql_exec("rollback");
            return;
        }

        QString updateChe = QString("update inHouseVehicle set paiduiState='',paiduiTime='' where CheNo='%1';").arg(oneVehicleCombox->currentText());
        res = db.sql_exec(updateChe);
        if(res == -1){
            db.sql_exec("rollback");
            return;
        }

        db.sql_exec("commit;");

        //更新剩料记录
        if(oneRemainingMaterialLineEdit->text().toDouble() != 0){
            QString updateShengliao = QString("update TransferMaterialRecord set IntoVolume='',IntoEngineer='',IntoStrengthGrade='',IntoShippingVolume='',IntoRecordNo='',Operator='' where IntoRecordNo='%1'")
                    .arg(fahuojiluhao);
            db.sql_exec(updateShengliao);
        }

        //删除追加生产记录
        QString deleteZhuiJiaSQL = QString("delete from ZhuiJiaRecord where RecordNo='%1'").arg(fahuojiluhao);
        db.sql_exec(deleteZhuiJiaSQL);

        //删除单车任务表SendProductNotice中的相应记录
        QString insertSQL = QString("delete from SendProductNotice where RecordNum='%1';").arg(fahuojiluhao);
        db.sql_exec(insertSQL);

        sockClient->send_Msg3();
        on_chaxunrenwudan();
        QMessageBox::information(this,tr("提示信息"),tr("撤销生产任务成功"),0,0,0);
    }
    if(res == QMessageBox::No){
        return;
    }

    oneTaskListLineEdit->clear();
    oneStrengthGradeLineEdit->clear();
    oneContactLineEdit->clear();
    oneRealCustomerLineEdit->clear();
    onePouringPositionLineEdit->clear();
    oneTelephoneLineEdit->clear();
    oneEngineerLineEdit->clear();
    onePouringMethodLineEdit->clear();
    oneLeiJiFLLineEdit->clear();
    oneFaHuoCustomerLineEdit->clear();
    oneSlumpLineEdit->clear();
    oneSupplyTimeLineEdit->clear();
    oneShippingVolumeLineEdit->clear();
    oneMotarVolumeLineEdit->clear();
    ActualProductionVolumeLineEdit->clear();
    oneRemainingMaterialLineEdit->clear();
    oneLeijiCheCiLineEdit->clear();
    oneAnPaiFlLineEdit->clear();
    oneAnPaiCheCiLineEdit->clear();
    oneXuKaiVolumeLineEdit->clear();
    oneUnitCombox->setCurrentIndex(0);
    oneVehicleCombox->setCurrentIndex(0);
    oneDriverCombox->setCurrentIndex(0);
    oneVehicleCombox->setEditable(false);
    oneConstructionSiteLineEdit->clear();
}

void shengchanrenwuanpaiDlg::on_chaxunrenwudan()
{
    QString kehu,Time,hide,jiaozhufangshi;
    if(oneGongChengCheckBox->checkState() == 2){
        kehu = QString(" and Engineering like '%%1%'").arg(oneProjectCombox->currentText());
    }
    if(oneXiaFaTimecheckBox->checkState() == 2){
        Time = QString(" and SendTime between '%1' and '%2'").arg(oneSendtime1DateEdit->date().toString("yyyy-MM-dd"),oneSendtime2DateEdit->date().addDays(1).toString("yyyy-MM-dd"));
    }
    if(oneHideCheck->checkState() == 2){
        hide = QString(" and SettlementCycle='1'");
    }
    else if(oneHideCheck->checkState() == 0){
        hide = QString(" and SettlementCycle='0'");
    }
    if(onePouringPositionCheckBox->checkState() == 2){
        jiaozhufangshi = QString(" and PouringPosition='%1'").arg(onePouringPositionCombox->currentText());
    }

    QString chaxunSQL = QString("select TaskNumber 任务单号,Customer 实际客户,Customer 发货客户,Engineering 工程名称,PouringPosition 浇筑部位,PouringMethod 浇筑方法,StrengthGrade 强度等级,\
                                Template 配合比模板,PlannedQuantity 计划方量,ContractCompletion 完成方量,fahuocheci 发货车次,HasBeenUnderTask 安排方量,CumulativeNumber 安排车次,\
                                Contacts 联系人,ContactNumber 联系电话,SupplyTime 供货时间,Slump 坍落度,Remarks 备注,ContractNumber 合同编号,ConstructionSite 工程地址 from ProductionTaskList where WhetherCheck='是' and \
                                WhetherSend='是' and WhetherReceive='是' and TzdCheck='是' and TzdSend='是' and WhetherInvalid='' %1 %2 %3 %4")
                        .arg(kehu,Time,hide,jiaozhufangshi);
    db.showview(chaxunSQL,view,&model);
    setModelStyle(model);

//    QString searchSQL = QString("select ROUND(SUM(PlannedQuantity),1),ROUND(SUM(ContractCompletion),1) from ProductionTaskList where WhetherCheck='是' and WhetherSend='是' and WhetherReceive='是' and TzdCheck='是' and TzdSend='是' %1;").arg(Time);
//    QString PlanVolume = db.sql_fetchrow_plus(searchSQL.toStdString().data(),0);
//    QString CompleteVolume = db.sql_fetchrow_plus(searchSQL.toStdString().data(),1);

    QString selectCon = QString("SELECT COUNT(1),SUM(ShippingVolume) FROM ProductionNotice WHERE WhetherDelivery = '是' and ProductionTime >= '%1' ORDER BY RecordNumber DESC;").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd 00:00:00"));
    QString PlanVolume = db.sql_fetchrow_plus(selectCon.toStdString().data(),0);
    QString CompleteVolume = db.sql_fetchrow_plus(selectCon.toStdString().data(),1);

    TodayPlanVolumeLabel->setText(QString("累计车次:")+PlanVolume+QString("  ")+QString("完成方量:")+CompleteVolume);
}

void shengchanrenwuanpaiDlg::on_zuofeiBtn()
{
    int res = QMessageBox::question(this,tr("提示信息"),tr("请确认该任务单已完成后再进行作废操作,作废后该任务将不能继续派车"),QMessageBox::Yes,QMessageBox::No);
    if(res == QMessageBox::Yes){
        if(oneTaskListLineEdit->text().isEmpty()){
            QMessageBox::information(this,tr("提示信息"),tr("请选择要作废的任务"),0,0,0);
            return;
        }
        QString invalidSQL = QString("update ProductionTaskList set WhetherInvalid='是' where TaskNumber='%1';").arg(oneTaskListLineEdit->text());
        int res = db.sql_exec(invalidSQL);
        if(res == 0){
            sockClient->send_Msg3();//发送刷新消息
            oneTaskListLineEdit->clear();
            oneStrengthGradeLineEdit->clear();
            oneContactLineEdit->clear();
            oneRealCustomerLineEdit->clear();
            onePouringPositionLineEdit->clear();
            oneTelephoneLineEdit->clear();
            oneEngineerLineEdit->clear();
            onePouringMethodLineEdit->clear();
            oneLeiJiFLLineEdit->clear();
            oneFaHuoCustomerLineEdit->clear();
            oneSlumpLineEdit->clear();
            oneSupplyTimeLineEdit->clear();
            oneShippingVolumeLineEdit->clear();
            oneMotarVolumeLineEdit->clear();
            ActualProductionVolumeLineEdit->clear();
            oneXuKaiVolumeLineEdit->clear();
            oneRemainingMaterialLineEdit->clear();
            oneLeijiCheCiLineEdit->clear();
            oneAnPaiFlLineEdit->clear();
            oneAnPaiCheCiLineEdit->clear();
            oneUnitCombox->setCurrentIndex(0);
            oneVehicleCombox->setCurrentIndex(0);
            oneDriverCombox->setCurrentIndex(0);
            QMessageBox::information(this,tr("提示信息"),tr("作废成功"),0,0,0);
        }
    }else{
        return;
    }
}

void shengchanrenwuanpaiDlg::on_zhuanliaochuliBtn()
{
    if(oneTaskListLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择一个任务单"),0,0,0);
        return;
    }
    if(oneProductPartCombox->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择生产部门"),0,0,0);
        return;
    }
    if(oneUnitCombox->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择生产机组"),0,0,0);
        return;
    }
    if(oneVehicleCombox->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择送货车辆"),0,0,0);
        return;
    }
    if(oneShippingVolumeLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请指定生产方量"),0,0,0);
        return;
    }

    int res = QMessageBox::question(this,tr("提示信息"),tr("确认进行转料操作？"),QMessageBox::Yes,QMessageBox::No);
    if(res == QMessageBox::Yes){
        double SUMWGT = 0;
        rongzhong.clear();
        QString searchrongzhongSQL = QString("select * from rwPEIFANG where TaskList='%1' AND StateNo='%2'").arg(oneTaskListLineEdit->text(),QString::number(oneUnitCombox->currentIndex()));
        for(int i = 1; i < 21; i++){
            SUMWGT += db.sql_fetchrow_plus(searchrongzhongSQL,i).toDouble();
        }
        rongzhong = QString::number(SUMWGT);

        //事务开始
        db.sql_exec("begin");

        //查找运费
        QString searchFreightPrice = QString("select Freight from ConcreteCarFreightSet where cast(MinimumMileage as SIGNED INTEGER)<='%1' and cast(MaximumMileage as SIGNED INTEGER)>='%1';").arg(Distance);
        QString FreightPrice = db.sql_fetchrow_plus(searchFreightPrice,0);

        //插入转料生产任务
        QString saveSQL = QString("insert into zhuanliaoNotice (TaskList,StrengthGrade,Contacts,Customer,PouringPosition,\
                                  ContactNumber,Engineering,PouringMethod,ArrangedVolume,ConstructionSite,Slump,SupplyTime,\
                                  ProductionDepartment,Unit,ShippingVolume,VolumeMortar,ProductionTime,DeliveryVehicle,\
                                  Driver,ActualProductionVolume,RemainingMaterial,InformPeople,TemplateName,Capacity,\
                                  ReceiptVolume,Price,ContractNumber,Mileage,OutboundTime,CumulativeNumber,CumulativeVolume,\
                                  FaHuoCustomer,FreightPrice) values ('%1','%2','%3','%4','%5','%6','%7','%8','%9','%10','%11','%12','%13',\
                                  '%14','%15','%16','%17','%18','%19','%20','%21','%22','%23','%24','%25','%26','%27','%28','%29','%30','%31','%32','%33');")
        .arg(oneTaskListLineEdit->text(),oneStrengthGradeLineEdit->text(),oneContactLineEdit->text(),oneRealCustomerLineEdit->text(),onePouringPositionLineEdit->text(),oneTelephoneLineEdit->text(),\
             oneEngineerLineEdit->text(),onePouringMethodLineEdit->text(),oneLeiJiFLLineEdit->text())
        .arg(oneFaHuoCustomerLineEdit->text(),oneSlumpLineEdit->text(),oneSupplyTimeLineEdit->text(),oneProductPartCombox->currentText(),oneUnitCombox->currentText(),\
             oneShippingVolumeLineEdit->text(),"0",oneProductDatetimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"),oneVehicleCombox->currentText())
        .arg(oneDriverCombox->currentText(),"0",oneRemainingMaterialLineEdit->text(),userName,peihebimubanmingcheng,rongzhong,oneShippingVolumeLineEdit->text(),PricePerParty)
        .arg(ContractNumber,Distance,oneProductDatetimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"),oneAnPaiCheCiLineEdit->text(),oneAnPaiFlLineEdit->text(),oneFaHuoCustomerLineEdit->text(),FreightPrice);
        res = db.sql_exec(saveSQL);
        if(res == -1){
            db.sql_exec("rollback");
            return;
        }
        //更新生产任务单中的方量信息
        QString updateSQL = QString("update ProductionTaskList set CumulativeNumber='%1',HasBeenUnderTask='%2' where TaskNumber='%3';")
                .arg(oneAnPaiCheCiLineEdit->text(),oneAnPaiFlLineEdit->text(),oneTaskListLineEdit->text());
        res = db.sql_exec(updateSQL);
        if(res == -1){
            db.sql_exec("rollback");
            return;
        }
        disconnect(oneShippingVolumeLineEdit,SIGNAL(textChanged(QString)),this,SLOT(ActualProductionVolume()));
        disconnect(oneRemainingMaterialLineEdit,SIGNAL(textChanged(QString)),this,SLOT(ActualProductionVolume()));

        //事务结束
        db.sql_exec("commit");

        db.showview_num(SQL62,sixTargetView,&sixTargetModel,0);

        QMessageBox::information(this,tr("提示信息"),tr("操作成功"),0,0,0);
        sockClient->send_Msg3();
        tabWidget->setCurrentIndex(5);


        oneTaskListLineEdit->clear();
        oneStrengthGradeLineEdit->clear();
        oneContactLineEdit->clear();
        oneRealCustomerLineEdit->clear();
        onePouringPositionLineEdit->clear();
        oneTelephoneLineEdit->clear();
        oneEngineerLineEdit->clear();
        onePouringMethodLineEdit->clear();
        oneLeiJiFLLineEdit->clear();
        oneFaHuoCustomerLineEdit->clear();
        oneSlumpLineEdit->clear();
        oneSupplyTimeLineEdit->clear();
        oneShippingVolumeLineEdit->clear();
        oneMotarVolumeLineEdit->clear();
        ActualProductionVolumeLineEdit->clear();
        oneXuKaiVolumeLineEdit->clear();
        oneRemainingMaterialLineEdit->clear();
        oneLeijiCheCiLineEdit->clear();
        oneAnPaiFlLineEdit->clear();
        oneAnPaiCheCiLineEdit->clear();
        oneUnitCombox->setCurrentIndex(0);
        oneVehicleCombox->setCurrentIndex(0);
        oneDriverCombox->setCurrentIndex(0);
    }
    else if(res == QMessageBox::No){
        return;
    }
}

void shengchanrenwuanpaiDlg::on_yincangAct()
{
    int row = view->currentIndex().row();
    QString taskListNum = model->item(row,0)->text();
    QString updateSQL = QString("update productiontasklist set SettlementCycle='1' where TaskNumber='%1'").arg(taskListNum);
    db.sql_exec(updateSQL);
    on_chaxunrenwudan();
}

void shengchanrenwuanpaiDlg::on_chexiaoyincangAct()
{
    int row = view->currentIndex().row();
    QString taskListNum = model->item(row,0)->text();
    QString updateSQL = QString("update productiontasklist set SettlementCycle='0' where TaskNumber='%1'").arg(taskListNum);
    db.sql_exec(updateSQL);
    on_chaxunrenwudan();
}

void shengchanrenwuanpaiDlg::on_twoRefreshRunStateTimer()
{
    db.showview_num(SQL2,twoview,&twomodel,0);
    db.showview_num(SQL22,twoProductingView,&twoProductingModel,0);
}

void shengchanrenwuanpaiDlg::on_twoSetProductedBtn()
{
    QString SelectProSQL = QString("select DeliveryVehicle from productionnotice where RecordNumber='%1';")
            .arg(twoProductingRecordNoLineEdit->text());
    qDebug()<<'SelectProSQL'<<SelectProSQL;
    QString CheHao = db.sql_fetchrow_plus(SelectProSQL,0);

        //删除大屏显示表
    QString DeleteinhousevehicleSQL = QString("delete from inhousevehicle where CheNo='%1';")
            .arg(CheHao);
     qDebug()<<'DeleteinhousevehicleSQL:'<<DeleteinhousevehicleSQL;
    db.sql_exec(DeleteinhousevehicleSQL);

    //
    QString DeleterunstatetabSQL = QString("delete from runstatetab;");
     qDebug()<<'DeleteinhousevehicleSQL:'<<DeleterunstatetabSQL;
    db.sql_exec(DeleterunstatetabSQL);

    QString updateProSQL = QString("update productionnotice set Confirmor='是' where RecordNumber='%1';")
            .arg(twoProductingRecordNoLineEdit->text());
    int res2 = db.sql_exec(updateProSQL);
     qDebug()<<'updateProSQL'<<updateProSQL;
    if(res2 == -1){
        db.sql_exec("rollback");
        return;
    }
//删除sendproductnotice表
    QString deleteRunStateSQL = QString("delete from sendproductnotice where RecordNum='%1';")
            .arg(twoProductingRecordNoLineEdit->text());
    int res3 = db.sql_exec(deleteRunStateSQL);
     qDebug()<<deleteRunStateSQL;
    if(res3 == -1){
        db.sql_exec("rollback");
        return;
    }

    sockClient->send_Msg2(twoUnitNo.toInt(),"",QString("update DcRwTab set SFWC=-1 where DJBHOrder=%1").arg(twoProductingRecordNoLineEdit->text()).toStdString().data());
    twoProductingRecordNoLineEdit->clear();
}

void shengchanrenwuanpaiDlg::on_threeFindBtn()
{
    QString gongcheng,shijian,cheliang,shengchanjizu,tongzhiren;

    if(threeEngineerCheckBox->checkState() == 2){
        gongcheng = QString(" and Engineering='%1'").arg(threeEngineerCombox->currentText());
    }
    if(threeProductTimeCheckBox->checkState() == 2){
        shijian = QString(" and ProductionTime between '%1' and '%2'")
                .arg(threeProductTime1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),threeProductTime2->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
    }
    if(threeVehicleCheckBox->checkState() == 2){
        cheliang = QString(" and DeliveryVehicle='%1'").arg(threeVehicleCombox->currentText());
    }
    if(threeProductUnitCheckBox->checkState() == 2){
        shengchanjizu = QString(" and Unit='%1'").arg(threeProductUnitCombox->currentText());
    }
    if(threeInfoManCheckBox->checkState() == 2){
        tongzhiren = QString(" and InformPeople='%1'").arg(threeInfoManCombox->currentText());
    }

    QString chaxunSQL = QString("select RecordNumber 发货序号,Unit 机组,Customer 实际客户,FaHuoCustomer 发货客户,Engineering 工程名称,PouringPosition 浇筑部位,PouringMethod 浇筑方法,\
                                StrengthGrade 强度等级,ShippingVolume 发货方量,ActualProductionVolume 实际生产方量,RemainingMaterial 剩料,CumulativeNumber 累计车次,CumulativeVolume 累计方量,\
                                IF(VolumeMortar='',0,VolumeMortar) 砂浆方量,DeliveryVehicle 送货车辆,Driver 司机,ProductionTime 生产时间,Slump 坍落度,Contacts 联系人,ContactNumber 联系电话,\
                                SupplyTime 供货时间,ProductionDepartment 生产部门,TaskList 任务单,InformPeople 通知人,WhetherCancel 转料状态 from ProductionNotice where WhetherDelivery='是' %1%2%3%4%5 order by RecordNumber desc;")
            .arg(gongcheng,shijian,cheliang,shengchanjizu,tongzhiren);
    db.showview_num(chaxunSQL,threeview,&threemodel,0);
    threeview->sortByColumn(0,Qt::DescendingOrder);
    setPage3ModelStyle(threemodel);
}

void shengchanrenwuanpaiDlg::on_bufangBtn()
{
    if(fourRecordNoLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择补方单号"),0,0,0);
        return;
    }
    int res = QMessageBox::question(this,tr("提示信息"),tr("是否补方？"),QMessageBox::Yes|QMessageBox::No);
    if(res == QMessageBox::Yes)
    {
        QString updateSQL = QString("update bufangNotice set VolumeMortar='%4',WhetherDocument='是',InformPeople='%1',Unit='%2' where RecordNumber=%3")
                .arg(userName,fourUnitNoComBox->currentText(),fourRecordNoLineEdit->text(),fourMotarLineEdit->text());
        db.sql_exec(updateSQL);

        QString insertBUFANG = QString("insert into bufangReact (number,unit) values ('%1','%2')").arg(fourRecordNoLineEdit->text(),QString::number(fourUnitNoComBox->currentIndex()));
        db.sql_exec(insertBUFANG);

        QString insertSQL = QString("insert into inHouseVehicle (ID,CheNo,CheTime,paiduiState,paiduiTime) values (%1,'%2','%3','%4','%3');")
                .arg(QTime::currentTime().toString("hhmmss"),cheHao,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(fourUnitNoComBox->currentIndex());
        db.sql_exec(insertSQL);

        sockClient->send_Msg3();
    }
    fourRecordNoLineEdit->clear();
    fourRealCustomerLineEdit->clear();
    fourFaHuoCustomerLineEdit->clear();
    fourEngineerLineEdit->clear();
    fourTongVolumeLineEdit->clear();
    fourUnitNoComBox->setCurrentIndex(0);
}

void shengchanrenwuanpaiDlg::on_hulueBtn()
{
    if(fourRecordNoLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择补方单号"),0,0,0);
        return;
    }
    int res = QMessageBox::question(this,tr("提示信息"),tr("是否忽略该车补方？"),QMessageBox::Yes|QMessageBox::No);
    if(res == QMessageBox::Yes)
    {
        QString deleteSQL = QString("delete from bufangNotice where RecordNumber=%1").arg(fourRecordNoLineEdit->text());
        db.sql_exec(deleteSQL);
        sockClient->send_Msg3();
    }
    fourRecordNoLineEdit->clear();
    fourRealCustomerLineEdit->clear();
    fourFaHuoCustomerLineEdit->clear();
    fourEngineerLineEdit->clear();
    fourTongVolumeLineEdit->clear();
}

void shengchanrenwuanpaiDlg::on_fiveChaxunBtn()
{
    QString kehu,gongcheng;
    if(fiveCheckBox1->checkState() == 2){
        kehu = QString(" and FaHuoCustomer='%1' ").arg(fiveCombox1->currentText());
    }
    if(fiveCheckBox2->checkState() == 2){
        gongcheng = QString(" and Engineering='%1' ").arg(fiveCombox2->currentText());
    }

    QString searchSQL = QString("select RecordNumber 发货序号,TaskList 任务单,Customer 客户名称,FaHuoCustomer 发货客户,Engineering 工程,PouringPosition 浇筑部位,\
                                PouringMethod 浇筑方法,StrengthGrade 强度等级,ShippingVolume 发货方量,IF(VolumeMortar='',0,VolumeMortar) 砂浆方量,DeliveryVehicle 送货车辆,Driver 司机,\
                                CumulativeNumber 累计车次,CumulativeVolume 累计方量,ProductionTime 补方时间,Slump 坍落度,Contacts 联系人,ContactNumber 联系电话,\
                                WhetherDelivery  是否发货,SupplyTime 供货时间,ProductionDepartment 生产部门,Unit 机组,ActualProductionVolume 实际生产方量,\
                                RemainingMaterial 剩料,InformPeople 通知人 from bufangNotice where WhetherDocument='是' and ProductionTime between '%1' and '%2' %3 %4;")
            .arg(fivedateTimeEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),fivedateTimeEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),kehu,gongcheng);
    db.showview_num(searchSQL,fiveview,&fivemodel,0);
}





void shengchanrenwuanpaiDlg::on_sixFindBtn()
{
    QString RecordNumber;
    if(sixRecordNumLineEdit->text().isEmpty()){
        RecordNumber = "0";
    }else{
        RecordNumber = sixRecordNumLineEdit->text();
    }

    QString searchSQL = QString("select RecordNumber 发货序号,TaskList 任务单,Customer 客户名称,Engineering 工程名称,PouringPosition 浇筑部位,PouringMethod 浇筑方法,StrengthGrade 强度等级,\
                                ShippingVolume 发货方量,ActualProductionVolume 实际生产方量,RemainingMaterial 剩料,IF(VolumeMortar='',0,VolumeMortar) 砂浆方量,DeliveryVehicle 送货车辆,\
                                Driver 司机,CumulativeNumber 累计车次,CumulativeVolume 累计方量,ProductionTime 生产时间,Slump 坍落度,Contacts 联系人,ContactNumber 联系电话,SupplyTime 供货时间,\
                                ProductionDepartment 生产部门,Unit 机组,InformPeople 通知人,WhetherCancel 转料状态 from ProductionNotice where RecordNumber=%1 and WhetherCancel!='转出';").arg(RecordNumber);
    db.showview_num(searchSQL,sixOriginalView,&sixOriginalModel,0);
}

void shengchanrenwuanpaiDlg::on_sevenChaxunBtn()
{
    QString searchSQL = QString("select OperatingTime 操作时间,ReturnRecordNo 退回记录号,ReturnVehicle 退回车牌号,ReturnEngineer 退回工程名称,ReturnStrengthGrade 退回等级,\
                                ReturnShippingVolume 退回发货方量,ReturnReceiptVolume 退回签收方量,ReturnProductVolume 退回生产方量,ReturnVolume 退回方量,ReturnZuoFeiVolume 作废方量,\
                                IntoRecordNo 转入记录号,IntoVehicle 转入车牌号,IntoEngineer 转入工程名称,IntoStrengthGrade 转入等级,IntoVolume 转入方量,ActualProductionVolume 补方方量,IntoShippingVolume 转入发货方量,\
                                Type 剩转类型,Operator 操作人 from TransferMaterialRecord A LEFT JOIN (SELECT RecordNumber,ActualProductionVolume FROM bufangNotice) B ON (A.IntoRecordNo=B.RecordNumber) where OperatingTime between '%1' and '%2'")
                    .arg(sevendateTimeEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),sevendateTimeEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
    db.showview(searchSQL,sevenview,&sevenmodel);
}

void shengchanrenwuanpaiDlg::on_sixConfirmTransferBtn()
{
    if(sixOriginalNoLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择要转料的单车任务"),0,0,0);
        return;
    }
    if(sixReceiptVolumeLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入该转料车的签收方量"),0,0,0);
        return;
    }
    if(sixTargetModel->rowCount() == 0){
        QMessageBox::information(this,tr("提示信息"),tr("请选择要转发到的工地和车辆"),0,0,0);
        return;
    }

    //更新转出的派车单
    QString updateSQL = QString("update ProductionNotice set ReceiptVolume='%1',WhetherCancel='转出' where RecordNumber=%2").arg(sixReceiptVolumeLineEdit->text(),sixOriginalNoLineEdit->text());
    db.sql_exec(updateSQL);

    //更新转出的总任务单中的已完成任务量，发货车次
    if(sixReceiptVolumeLineEdit->text().toDouble() == 0){
        QString updateTaskListSQL = QString("update ProductionTaskList set fahuocheci=fahuocheci-1,ContractCompletion=ContractCompletion-'%1',CumulativeNumber=CumulativeNumber-1,\
                                            HasBeenUnderTask=HasBeenUnderTask-'%1' where TaskNumber='%2';").arg(sixShippingVolumeLineEdit->text(),sixTaskNumber);
        db.sql_exec(updateTaskListSQL);
    }
    else if(sixReceiptVolumeLineEdit->text().toDouble() > 0){
        QString updateTaskListSQL = QString("update ProductionTaskList set ContractCompletion=ContractCompletion-'%1',HasBeenUnderTask=HasBeenUnderTask-'%1' where TaskNumber='%2';")
                .arg(QString::number(sixShippingVolumeLineEdit->text().toDouble()-sixReceiptVolumeLineEdit->text().toDouble()),sixTaskNumber);
        db.sql_exec(updateTaskListSQL);
    }

    //进行转料操作
    int rowCount = sixTargetModel->rowCount();
    for(int i = 0; i < rowCount; i++){
        //插入转入派车单
        QString insertSQL = QString("insert into ProductionNotice (TaskList,StrengthGrade,Contacts,Customer,FaHuoCustomer,PouringPosition,ContactNumber,Engineering,PouringMethod,\
                                    ArrangedVolume,ConstructionSite,Slump,SupplyTime,ProductionDepartment,Unit,ShippingVolume,ReceiptVolume,VolumeMortar,ProductionTime,DeliveryVehicle,\
                                    Driver,ActualProductionVolume,RemainingMaterial,WhetherDelivery,WhetherDocument,WhetherCancel,InformPeople,TemplateName,Capacity,CumulativeNumber,\
                                    CumulativeVolume,OutboundTime,Confirmor,PlantName,Price,totalPrice,Flag,MortarPrice,MortarTotal,SettlementTime,ContractNumber,Mileage,FreightPrice,\
                                    TotalFreight,SettlementMark,SupplementaryPrescription,PenaltyAmount,FreightSettlementTime) \
                                    select TaskList,StrengthGrade,Contacts,Customer,FaHuoCustomer,PouringPosition,ContactNumber,Engineering,PouringMethod,\
                ArrangedVolume,ConstructionSite,Slump,SupplyTime,ProductionDepartment,Unit,ShippingVolume,ReceiptVolume,VolumeMortar,ProductionTime,DeliveryVehicle,\
                Driver,ActualProductionVolume,RemainingMaterial,WhetherDelivery,WhetherDocument,'转入',InformPeople,TemplateName,Capacity,CumulativeNumber,\
                CumulativeVolume,OutboundTime,Confirmor,PlantName,Price,totalPrice,Flag,MortarPrice,MortarTotal,SettlementTime,ContractNumber,Mileage,FreightPrice,\
                TotalFreight,SettlementMark,SupplementaryPrescription,PenaltyAmount,FreightSettlementTime from zhuanliaoNotice where RecordNumber=%1;").arg(sixTargetModel->item(i,0)->text());
        db.sql_exec(insertSQL);

        //删除中间表记录
        QString deleteSQL = QString("delete from zhuanliaoNotice where RecordNumber=%1").arg(sixTargetModel->item(i,0)->text());
        db.sql_exec(deleteSQL);

        //更新转入的总任务单中的已完成任务量，发货车次
        QString updateTaskListSQL = QString("update ProductionTaskList set fahuocheci=fahuocheci+1,ContractCompletion=ContractCompletion+'%1' where TaskNumber='%2';").arg(sixTargetModel->item(i,7)->text(),sixTargetModel->item(i,1)->text());
        db.sql_exec(updateTaskListSQL);

        //获取插入的转入记录的记录号
        QString searchRecordNumber = QString("select RecordNumber,DeliveryVehicle from ProductionNotice where ProductionTime='%1'").arg(sixTargetModel->item(i,15)->text());
        QString RecordNumber = db.sql_fetchrow_plus(searchRecordNumber,0);
        QString DeliveryVehicle = db.sql_fetchrow_plus(searchRecordNumber,1);

        //插入转料记录
        QString insertzhuanliaoSQL = QString("insert into TransferMaterialRecord (OperatingTime,ReturnRecordNo,ReturnVehicle,ReturnEngineer,ReturnStrengthGrade,ReturnShippingVolume,\
                                             ReturnReceiptVolume,ReturnProductVolume,ReturnVolume,IntoVolume,IntoEngineer,IntoStrengthGrade,IntoShippingVolume,IntoRecordNo,Operator,IntoVehicle,Type) values (\
                                    '%1','%2','%3','%4','%5','%6','%7','%8','%9','%10','%11','%12','%13','%14','%15','%16','转料')")
                .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"),sixOriginalNoLineEdit->text(),DeliveryVehicle,sixEngineerLineEdit->text(),sixBiaoHao,
                     sixShippingVolumeLineEdit->text(),sixReceiptVolumeLineEdit->text(),sixShengChanLiang,QString::number(sixShippingVolumeLineEdit->text().toDouble()-sixReceiptVolumeLineEdit->text().toDouble()))
                .arg(QString::number(sixShippingVolumeLineEdit->text().toDouble()-sixReceiptVolumeLineEdit->text().toDouble()),sixTargetModel->item(i,3)->text(),
                     sixTargetModel->item(i,6)->text(),sixTargetModel->item(i,7)->text(),RecordNumber,userName,sixTargetModel->item(i,11)->text());
        db.sql_exec(insertzhuanliaoSQL);

        //更新消耗记录号
        if(sixReceiptVolumeLineEdit->text().toDouble() == 0){
            QString updateSQL = QString("update HISTDATA set bsqk='%1' where bsqk='%2'").arg(RecordNumber,sixOriginalNoLineEdit->text());
            db.sql_exec(updateSQL);
            QString updateSQL1 = QString("update HISTDATA2 set recordNo='%1' where recordNo='%2'").arg(RecordNumber,sixOriginalNoLineEdit->text());
            db.sql_exec(updateSQL1);
        }
    }

    sixRecordNumLineEdit->clear();
    on_sixFindBtn();
    db.showview_num(SQL62,sixTargetView,&sixTargetModel,0);
    sixOriginalNoLineEdit->clear();
    sixCustomerLineEdit->clear();
    sixEngineerLineEdit->clear();
    sixVehicleLineEdit->clear();
    sixShippingVolumeLineEdit->clear();
    sixReceiptVolumeLineEdit->clear();
    QMessageBox::information(this,tr("提示信息"),tr("操作成功"),0,0,0);
    sockClient->send_Msg3();
}

void shengchanrenwuanpaiDlg::Decreasing()
{
    if(!sixTargetView->currentIndex().isValid()){
        QMessageBox::information(this,tr("提示信息"),tr("没有要撤销的转料"),0,0,0);
        return;
    }

    int row = sixTargetView->currentIndex().row();

    int res = QMessageBox::question(this,tr("提示信息"),tr("是否要撤销该车转料？"),QMessageBox::Yes,QMessageBox::No);
    if(res == QMessageBox::Yes){
        db.sql_exec("begin;");
        //删除生产通知单
        QString chexiaoSQL = QString("delete from zhuanliaoNotice where RecordNumber=%1;").arg(sixTargetModel->item(row,0)->text());
        int res = db.sql_exec(chexiaoSQL);
        if(res == -1){
            db.sql_exec("rollback");
            return;
        }
        QString updateNoticeSQL = QString("UPDATE zhuanliaoNotice SET CumulativeNumber=CumulativeNumber-'1',CumulativeVolume=CumulativeVolume-'%1' \
                                          where TaskList='%2' and RecordNumber>%3")
                .arg(sixTargetModel->item(row,7)->text(),sixTargetModel->item(row,1)->text(),sixTargetModel->item(row,0)->text());
        res = db.sql_exec(updateNoticeSQL);
        if(res == -1){
            db.sql_exec("rollback");
            return;
        }

        //查找累计方量
        QString chaxunSQL = QString("select HasBeenUnderTask from ProductionTaskList where TaskNumber='%1';").arg(sixTargetModel->item(row,1)->text());
        QString leijifangliang = db.sql_fetchrow_plus(chaxunSQL,0);

        //更新任务单中的累计方量和累积车次
        double yianpaifangliang = leijifangliang.toDouble() - sixTargetModel->item(row,7)->text().toDouble();
        QString updateSQL = QString("update ProductionTaskList set HasBeenUnderTask='%1',CumulativeNumber=CumulativeNumber-'1' where TaskNumber='%3';")
                .arg(QString::number(yianpaifangliang),sixTargetModel->item(row,1)->text());
        res = db.sql_exec(updateSQL);
        if(res == -1){
            db.sql_exec("rollback");
            return;
        }

        db.sql_exec("commit;");

        sockClient->send_Msg3();
        db.showview_num(SQL62,sixTargetView,&sixTargetModel,0);
        QMessageBox::information(this,tr("提示信息"),tr("撤销转料任务成功"),0,0,0);
    }
    if(res == QMessageBox::No){
        return;
    }
}

void shengchanrenwuanpaiDlg::on_eightShuaXin()
{
    QString searchSQL = "SELECT\
            RecordNumber 出车单号,\
            Unit 生产机组,\
            DeliveryVehicle 车号,\
            ProductionTime 出站时间,\
            MID(TIMEDIFF(NOW(), ProductionTime),1,8) 耗时,\
            FaHuoCustomer 客户,\
            Engineering 工程,\
            PouringPosition 浇筑部位,\
            StrengthGrade 强度等级,\
            PouringMethod 浇筑方法,\
            ShippingVolume 发货方量,\
            CumulativeNumber 本车车次,\
            CumulativeVolume 累计方量\
        FROM\
            (SELECT * FROM ProductionNotice ORDER BY RecordNumber DESC) A\
        LEFT JOIN (SELECT * FROM inHouseVehicle) B ON (A.DeliveryVehicle = B.CheNo)\
        WHERE\
            TIMESTAMPDIFF(MINUTE,ProductionTime,NOW()) < 300 AND B.CheNo IS NULL and A.WhetherCancel!='转出'\
        GROUP BY\
            DeliveryVehicle\
        ORDER BY\
            Engineering,\
            FaHuoCustomer,\
            TaskList,\
            OutboundTime desc";

    db.showview(searchSQL,eightview,&eightmodel);
}

void shengchanrenwuanpaiDlg::on_ninechaxun()
{
    QString gongcheng,shijian,cheliang,shengchanjizu,tongzhiren;

    if(ninecheckBox1->checkState() == 2){
        gongcheng = QString(" and Engineering='%1'").arg(ninecombo1->currentText());
    }
    if(ninecheckBox2->checkState() == 2){
        shijian = QString(" and ProductionTime between '%1' and '%2'")
                .arg(ninedate1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),ninedate2->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
    }
    if(ninecheckBox3->checkState() == 2){
        cheliang = QString(" and DeliveryVehicle='%1'").arg(ninecombo2->currentText());
    }
    if(ninecheckBox4->checkState() == 2){
        shengchanjizu = QString(" and Unit='%1'").arg(ninecombo3->currentText());
    }
    if(ninecheckBox5->checkState() == 2){
        tongzhiren = QString(" and InformPeople='%1'").arg(ninecombo4->currentText());
    }

    QString chaxunSQL = QString("select RecordNumber 发货序号,TaskList 任务单,Customer 客户名称,FaHuoCustomer 发货客户,Engineering 工程,PouringPosition 浇筑部位,\
                                PouringMethod 浇筑方法,StrengthGrade 强度等级,ShippingVolume 发货方量,IF(VolumeMortar='',0,VolumeMortar) 砂浆方量,DeliveryVehicle 送货车辆,Driver 司机,\
                                CumulativeNumber 累计车次,CumulativeVolume 累计方量,ProductionTime 生产时间,Slump 坍落度,Contacts 联系人,ContactNumber 联系电话,\
                                WhetherDelivery  是否打印出车单,SupplyTime 作废时间,ProductionDepartment 生产部门,Unit 机组,ActualProductionVolume 实际生产方量,\
                                RemainingMaterial 剩料,InformPeople 作废操作人 from zuofeiNotice where RecordNumber is not null %1%2%3%4%5 order by RecordNumber desc limit 1000;")
            .arg(gongcheng,shijian,cheliang,shengchanjizu,tongzhiren);

    db.showview_num(chaxunSQL,nineview,&ninemodel,0);
}

void shengchanrenwuanpaiDlg::on_tabWidget(int index)
{
    if(index == 1){
        db.showview_num(SQL2,twoview,&twomodel,0);
        db.showview_num(SQL22,twoProductingView,&twoProductingModel,0);
        twoRefreshRunStateTimer->start(5000);
    }
    else if(index == 2){
        if(page3Open == false){
            db.sql_fillComboBoxItem("select Engineering from ProductionNotice group by Engineering",threeEngineerCombox);
            db.sql_fillComboBoxItem("select Vehiclenumber from ConcreteVehicleInformation",threeVehicleCombox);
            db.sql_fillComboBoxItem("select UnitName from UnitSetting",threeProductUnitCombox);
            db.sql_fillComboBoxItem("select RealName from UserManagement where SubordinateDepartment='调度室'",threeInfoManCombox);
            on_threeFindBtn();
            page3Open = true;
        }
        twoRefreshRunStateTimer->stop();
    }
    else if(index == 3){
        if(page4Open == false){
            db.sql_fillComboBoxItem("select UnitName from UnitSetting",fourUnitNoComBox);
            db.showview_num(SQL4,fourview,&fourmodel,0);
            fourview->setColumnHidden(1,true);
            fourview->setColumnHidden(6,true);
            fourview->setColumnHidden(12,true);
            fourview->setColumnHidden(13,true);
            fourview->setColumnHidden(15,true);
            fourview->setColumnHidden(16,true);
            fourview->setColumnHidden(17,true);
            fourview->setColumnHidden(18,true);
            fourview->setColumnHidden(19,true);
            fourview->setColumnHidden(20,true);
            fourview->setColumnHidden(22,true);
            fourview->setColumnHidden(23,true);
            fourview->setColumnWidth(14,150);
            page4Open = true;
        }
        twoRefreshRunStateTimer->stop();
    }
    else if(index == 4){
        if(page5Open == false){
            db.sql_fillComboBoxItem("select FaHuoCustomer from bufangNotice group by FaHuoCustomer",fiveCombox1);
            db.sql_fillComboBoxItem("select Engineering from bufangNotice group by Engineering",fiveCombox2);
            db.showview_num(SQL5,fiveview,&fivemodel,0);
            fiveview->setColumnHidden(1,true);
            fiveview->setColumnHidden(2,true);
            fiveview->setColumnHidden(6,true);
            fiveview->setColumnHidden(12,true);
            fiveview->setColumnHidden(13,true);
            fiveview->setColumnHidden(15,true);
            fiveview->setColumnHidden(16,true);
            fiveview->setColumnHidden(17,true);
            fiveview->setColumnHidden(18,true);
            fiveview->setColumnHidden(19,true);
            fiveview->setColumnHidden(20,true);
            fiveview->setColumnHidden(22,true);
            fiveview->setColumnHidden(23,true);
            fiveview->setColumnWidth(14,150);
            page5Open = true;
        }
        twoRefreshRunStateTimer->stop();
    }
    else if(index == 5){
        if(page6Open == false){
            db.showview_num(SQL6,sixOriginalView,&sixOriginalModel,0);
            sixOriginalView->setColumnWidth(8,150);
            db.showview_num(SQL62,sixTargetView,&sixTargetModel,0);
            page6Open = true;
        }
        twoRefreshRunStateTimer->stop();
    }
    else if(index == 6){
        if(page7Open == false){
            db.showview(SQL7,sevenview,&sevenmodel);
            sevenview->setColumnWidth(0,150);
            page7Open = true;
        }
        twoRefreshRunStateTimer->stop();
    }
    else if(index == 7){
        if(page8Open == false){
            on_eightShuaXin();
            eightview->setColumnWidth(3,150);
            page8Open = true;
        }
        twoRefreshRunStateTimer->stop();
    }
    else if(index == 8){
        if(page9Open == false){
            db.sql_fillComboBoxItem("select Engineering from zuofeiNotice group by Engineering",ninecombo1);
            db.sql_fillComboBoxItem("select LicensePlate from ConcreteVehicleInformation",ninecombo2);
            db.sql_fillComboBoxItem("select UnitName from UnitSetting",ninecombo3);
            db.sql_fillComboBoxItem("select RealName from UserManagement where SubordinateDepartment='调度室'",ninecombo4);
            db.showview_num(SQL9,nineview,&ninemodel,0);
            page9Open = true;
        }
        twoRefreshRunStateTimer->stop();
    }
    else{
        twoRefreshRunStateTimer->stop();
    }
}
