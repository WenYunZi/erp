#include "cheliangweixiuguanli.h"
#include <QDateTime>
#include <qmap.h>
#include <string.h>
#include <QString>
#include <QVariant>

extern mymysql db;
extern myTCPsocket *sockClient;
extern QString userName;

cheliangweixiuguanli::cheliangweixiuguanli(QWidget *parent) :
    QDialog(parent)
{
    tabWidget = new QTabWidget;
    waichuweixiuduizhangdan = new QWidget;
    weixiujilu = new QWidget;
    cheliangweixiuribaobiao = new QWidget;
    jiayoumingxiliangbiao = new QWidget;
    xingchejilubiao = new QWidget;
    kaohezongbiao = new QWidget;
//    peizhiyemian = new QWidget;


    creatTabPage1();
    creatTabPage2();
    creatTabPage22();
    creatTabPage3();
    creatTabPage4();
    creatTabPage5();
//    creatTabPage6();


    view2Excel = new myExcel(this);
    QVBoxLayout *ZongLayout = new QVBoxLayout(this);
    ZongLayout->addWidget(tabWidget);
}

cheliangweixiuguanli::~cheliangweixiuguanli()
{

}


void cheliangweixiuguanli::refresh()
{

}

void cheliangweixiuguanli::keyPressEvent(QKeyEvent *event)
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

void cheliangweixiuguanli::creatTabPage1()
{
    SQL = "select Input_Time 维修时间,CheNO 车号,Mode 更改配件名称及规格,Fee 工时费,UseMan 使用人,Time 录入时间, person 记录人,Custom 供货方 from cheliangweixiuhaofa";

    createAction();
    createTool();

    QLabel *weixiushijianLabel = new QLabel(tr("维修时间:"),this);
    weixiushijianLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *chehaoLabel = new QLabel(tr("车号:"),this);
    chehaoLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *sijiLabel = new QLabel(tr("使用人:"),this);
    sijiLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *peijianLabel = new QLabel(tr("更换配件名称:"),this);
    peijianLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *gongshifeiLabel = new QLabel(tr("工时费:"),this);
    gongshifeiLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *gonghuofangLabel = new QLabel(tr("供货方:"),this);
    gonghuofangLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *lurushijianLabel = new QLabel(tr("录入时间:"),this);
    lurushijianLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    weixiushijianlineEdit = new QLineEdit(this);
    weixiushijianlineEdit->setStyleSheet("color:black");
    chepaihaocomBox1 = new myComboBox(this);
    chepaihaocomBox1->setEditable(true);
    const char *weixiuchepaiSQL1 = "select LicensePlate from ConcreteVehicleInformation group by LicensePlate;";
    db.sql_fillComboBoxItem(weixiuchepaiSQL1,chepaihaocomBox1);
    connect(chepaihaocomBox1,SIGNAL(currentTextChanged(QString)),this,SLOT(chepai2ON_xingming1()));

    gonghuofangcomBox = new myComboBox(this);
    const char *gonghuofangSQL = "select distinct Custom from cheliangweixiuhaofa;";
    db.sql_fillComboBoxItem(gonghuofangSQL,gonghuofangcomBox);
    sijiBox = new myComboBox;
    sijiBox->setEditable(true);
    const char *chepaiSQL = "select Driver1 from ConcreteVehicleInformation group by Driver1;";
    db.sql_fillComboBoxItem(chepaiSQL,sijiBox);
//    connect(sijiBox,SIGNAL(currentTextChanged(QString)),this,SLOT(ON_xingming2chepai1()));
    weiXiuStateComBox = new myComboBox(this);
    weiXiuStateComBox->setEditable(true);
    const char *fillSQL1 = "SELECT distinct Mode FROM cheliangweixiuhaofa";
    db.sql_fillComboBoxItem(fillSQL1,weiXiuStateComBox);
    gongshifeiLineEdit = new QLineEdit(this);
    gongshifeiLineEdit->setEnabled(true);
    gonghuofangLineEdit = new QLineEdit(this);
    gonghuofangLineEdit->setEnabled(true);
    lurushijianlineEdit = new QLineEdit(this);
    lurushijianlineEdit->setReadOnly(true);


    QHBoxLayout *luruHLayout11 = new QHBoxLayout;//布局头部
    luruHLayout11->addWidget(weixiushijianLabel,0);
    luruHLayout11->addWidget(weixiushijianlineEdit,2);
    luruHLayout11->addWidget(chehaoLabel,0);
    luruHLayout11->addWidget(chepaihaocomBox1,1);
    luruHLayout11->addWidget(sijiLabel,0);
    luruHLayout11->addWidget(sijiBox,1);
    luruHLayout11->addWidget(gonghuofangLabel,0);
    luruHLayout11->addWidget(gonghuofangLineEdit,1);
    luruHLayout11->addWidget(gongshifeiLabel,0);
    luruHLayout11->addWidget(gongshifeiLineEdit,1);

    QHBoxLayout *luruHLayout12 = new QHBoxLayout;//布局头部
    luruHLayout12->addWidget(peijianLabel,0);
    luruHLayout12->addWidget(weiXiuStateComBox,3);
    luruHLayout12->addWidget(lurushijianLabel,0);
    luruHLayout12->addWidget(lurushijianlineEdit,2);
    luruHLayout12->addStretch(2);

    QVBoxLayout *uplayout = new QVBoxLayout;
    uplayout->addWidget(toolBar,0);
    uplayout->addLayout(luruHLayout11,1);
    uplayout->addLayout(luruHLayout12,1);
//    uplayout->addSpacing(10);

    QGroupBox *upBox = new QGroupBox;
    upBox->setLayout(uplayout);

    shijianCheckBox = new QCheckBox(tr("维修时间"),this);
    shijianDateEdit1 = new QDateEdit(QDate::currentDate().addDays(-1),this);
    shijianDateEdit1->setCalendarPopup(true);
    QLabel *fengeLabel = new QLabel(tr("--"),this);
    fengeLabel->setAlignment(Qt::AlignCenter);
    shijianDateEdit2 = new QDateEdit(QDate::currentDate(),this);
    shijianDateEdit2->setCalendarPopup(true);
    gonghuofangCheckBox = new QCheckBox(tr("供货方"),this);
    chaxunBtn = new QPushButton(tr("查询"),this);
    chaxunBtn->setShortcut(Qt::Key_Enter);//设置快捷键小键盘的enter键
    chaxunBtn->setFixedWidth(120);
    connect(chaxunBtn,SIGNAL(clicked()),this,SLOT(on_chaxunBtn()));
    daochuBtn = new QPushButton(tr("导出"),this);  
    daochuBtn->setFixedWidth(120);
    connect(daochuBtn,SIGNAL(clicked()),this,SLOT(on_toExcell()));
    QLabel *zongjiLabel = new QLabel(tr("总计:"),this);
    zongjiLabel2 = new QLabel(this);
//    connect(key11,SIGNAL(activated()),this,SLOT(on_chaxunBtn()));//连接到指定槽函数
//    connect(key12,SIGNAL(activated()),this,SLOT(on_chaxunBtn()));//连接到指定槽函数

    threeview = new QTableView(this);
//    db.showview(SQL,threeview,&threemodel);
    connect(threeview,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick()));
    connect(threeview,SIGNAL(clicked(QModelIndex)),this,SLOT(ON_Sum1()));
    threeview->setColumnWidth(2,200);
    threeview->setColumnWidth(5,150);

    QHBoxLayout *hlayout1 = new QHBoxLayout;
    hlayout1->addWidget(shijianCheckBox,0);
    hlayout1->addWidget(shijianDateEdit1,1);
    hlayout1->addWidget(fengeLabel,0);
    hlayout1->addWidget(shijianDateEdit2,1);
    hlayout1->addWidget(gonghuofangCheckBox,0);
    hlayout1->addWidget(gonghuofangcomBox,1);
    hlayout1->addWidget(chaxunBtn,0);
    hlayout1->addWidget(daochuBtn,0);
    hlayout1->addWidget(zongjiLabel,0);
    hlayout1->addWidget(zongjiLabel2,0);
    hlayout1->addStretch(3);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addLayout(hlayout1);

    vlayout->addWidget(threeview,1);

    QGroupBox *downBox = new QGroupBox;
    downBox->setLayout(vlayout);

    QVBoxLayout *updownLayout = new QVBoxLayout(this);
    updownLayout->addWidget(upBox,1);
    updownLayout->addWidget(downBox,5);

    waichuweixiuduizhangdan->setLayout(updownLayout);
//    tabWidget->addTab(waichuweixiuduizhangdan,tr("外出维修对账单"));
}

void cheliangweixiuguanli::creatTabPage2()
{
    TabPageSQL2 = "select MaintenanceTime 维修时间,LicenseNumber 车号,Parts 更改配件名称及规格,Num 数量,Unit 单位,UserPeople 使用人, Remarks 备注,Time 录入时间,People 录入人 from MaintenanceRecordHaofa";
    createAction2();
    createTool2();
    QLabel *weixiushijianLabel21 = new QLabel(tr("维修时间:"),this);
    weixiushijianLabel21->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *weixiushijianLabel22 = new QLabel(tr("维修时间:"),this);
    weixiushijianLabel22->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *chehaoLabel21 = new QLabel(tr("车号:"),this);
    chehaoLabel21->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *peijianLabel2 = new QLabel(tr("更换配件名称及规格:"),this);
    peijianLabel2->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *shuliang2 = new QLabel(tr("数量:"),this);
    shuliang2->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *danwei2 = new QLabel(tr("单位:"),this);
    danwei2->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *shiyongrenLabel2 = new QLabel(tr("使用人:"),this);
    shiyongrenLabel2->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *beizhuLabel2 = new QLabel(tr("备注:"),this);
    beizhuLabel2->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *lurushijianLabel2 = new QLabel(tr("录入时间:"),this);
    lurushijianLabel2->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    chehaoCheckBox21 = new QCheckBox(tr("车号"),this);
    chehaoComBox21 = new myComboBox(this);
    const char *chehaoSQL21 = "select LicensePlate from ConcreteVehicleInformation group by LicensePlate";
    db.sql_fillComboBoxItem(chehaoSQL21,chehaoComBox21);

    weixiushijianlineEdit2 = new QLineEdit(this);
    weixiushijianlineEdit2->setStyleSheet("color:black");
    chepaihaocomBox2 = new myComboBox(this);
    const char *weixiuchepaiSQL2 = "select LicensePlate from ConcreteVehicleInformation group by LicensePlate";
    db.sql_fillComboBoxItem(weixiuchepaiSQL2,chepaihaocomBox2);
    connect(chepaihaocomBox2,SIGNAL(currentTextChanged(QString)),this,SLOT(ON_chepai2xingming2()));
    weiXiuStateComBox2 = new myComboBox(this);
    weiXiuStateComBox2->setEditable(true);
    const char *fillSQL2 = "SELECT distinct Parts FROM MaintenanceRecordHaofa";
    db.sql_fillComboBoxItem(fillSQL2,weiXiuStateComBox2);

    shuliangLineEdit2 = new QLineEdit(this);
    shuliangLineEdit2->setEnabled(true);

    danweiComBox2 = new myComboBox(this);
    const char *danweiSQL2 = "select distinct Unit from MaintenanceRecordHaofa;";
    db.sql_fillComboBoxItem(danweiSQL2,danweiComBox2);

    shiyongrenComBox2 = new myComboBox(this);
    shiyongrenComBox2->setEditable(true);       
    const char *shiyongrenSQL2 = "select Driver1 from ConcreteVehicleInformation group by Driver1;";
    db.sql_fillComboBoxItem(shiyongrenSQL2,shiyongrenComBox2);
//    connect(shiyongrenComBox2,SIGNAL(currentTextChanged(QString)),this,SLOT(ON_xingming2chepai2()));

    beizhulineEdit2 = new QLineEdit(this);
    beizhulineEdit2->setReadOnly(true);
    lurushijianlineEdit2 = new QLineEdit(this);
    lurushijianlineEdit2->setReadOnly(true);


    QHBoxLayout *weixiujiluHLayout = new QHBoxLayout;//布局头部
    weixiujiluHLayout->addWidget(weixiushijianLabel21);
    weixiujiluHLayout->addWidget(weixiushijianlineEdit2,2);
    weixiujiluHLayout->addWidget(chehaoLabel21);
    weixiujiluHLayout->addWidget(chepaihaocomBox2,1);
    weixiujiluHLayout->addWidget(peijianLabel2);
    weixiujiluHLayout->addWidget(weiXiuStateComBox2,3);
    weixiujiluHLayout->addWidget(shuliang2);
    weixiujiluHLayout->addWidget(shuliangLineEdit2);
    weixiujiluHLayout->addWidget(danwei2);
    weixiujiluHLayout->addWidget(danweiComBox2,1);
    weixiujiluHLayout->addWidget(shiyongrenLabel2);
    weixiujiluHLayout->addWidget(shiyongrenComBox2,1);
//    weixiujiluHLayout->addStretch(2);

    QHBoxLayout *weixiujiluHLayout2 = new QHBoxLayout;//布局头部
    weixiujiluHLayout2->addWidget(beizhuLabel2,0);
    weixiujiluHLayout2->addWidget(beizhulineEdit2,2);
    weixiujiluHLayout2->addWidget(lurushijianLabel2,0);
    weixiujiluHLayout2->addWidget(lurushijianlineEdit2,1);
    weixiujiluHLayout2->addStretch(2);

    QVBoxLayout *uplayout2 = new QVBoxLayout;
    uplayout2->addWidget(toolBar2,0);
    uplayout2->addLayout(weixiujiluHLayout,1);
    uplayout2->addLayout(weixiujiluHLayout2,1);
    uplayout2->addSpacing(10);

    QGroupBox *upBox2 = new QGroupBox;
    upBox2->setLayout(uplayout2);

    shijianDateEdit21 = new QDateEdit(QDate::currentDate().addDays(-1),this);
    shijianDateEdit21->setCalendarPopup(true);
    QLabel *fengeLabe2 = new QLabel(tr("--"),this);
    fengeLabe2->setAlignment(Qt::AlignCenter);
    shijianDateEdit22 = new QDateEdit(QDate::currentDate(),this);
    shijianDateEdit22->setCalendarPopup(true);

    weixiujiluBtn2 = new QPushButton(tr("维修记录单"),this);
    weixiujiluBtn2->setShortcut(Qt::Key_Enter);
    weixiujiluBtn2->setFixedWidth(120);
    connect(weixiujiluBtn2,SIGNAL(clicked()),this,SLOT(on_chaxunBtn2()));

    peijianchaxunBtn2 = new QPushButton(tr("物品用量单"),this);
    peijianchaxunBtn2->setFixedWidth(120);
    connect(peijianchaxunBtn2,SIGNAL(clicked()),this,SLOT(on_peijianBtn2()));

    daochuBtn2 = new QPushButton(tr("导出"),this);
    daochuBtn2->setFixedWidth(120);
    connect(daochuBtn2,SIGNAL(clicked()),this,SLOT(on_toExcell2()));
    QLabel *zongjiLabe2 = new QLabel(tr("总计:"),this);
    zongjiLabe22 = new QLabel(this);

    Tableview2 = new QTableView(this);
//    db.showview(TabPageSQL2,Tableview2,&TableviewModel2);
    connect(Tableview2,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick2()));
    connect(Tableview2,SIGNAL(clicked(QModelIndex)),this,SLOT(ON_Sum2()));

    Tableview2->setColumnWidth(2,200);
    Tableview2->setColumnWidth(5,150);

    QHBoxLayout *hlayout2 = new QHBoxLayout;
    hlayout2->addWidget(weixiushijianLabel22,0);
    hlayout2->addWidget(shijianDateEdit21,0);
    hlayout2->addWidget(fengeLabe2,0);
    hlayout2->addWidget(shijianDateEdit22,0);
    hlayout2->addWidget(chehaoCheckBox21,0);
    hlayout2->addWidget(chehaoComBox21,1);


    hlayout2->addWidget(weixiujiluBtn2,0);
    hlayout2->addWidget(peijianchaxunBtn2,0);
    hlayout2->addWidget(daochuBtn2,0);
    hlayout2->addWidget(zongjiLabe2,0);
    hlayout2->addWidget(zongjiLabe22,0);
    hlayout2->addStretch(3);

    QVBoxLayout *vlayout2 = new QVBoxLayout;
    vlayout2->addLayout(hlayout2);

    vlayout2->addWidget(Tableview2,1);

    QGroupBox *downBox2 = new QGroupBox;
    downBox2->setLayout(vlayout2);

    QVBoxLayout *updownLayout2 = new QVBoxLayout(this);
    updownLayout2->addWidget(upBox2,1);
    updownLayout2->addWidget(downBox2,5);

    weixiujilu->setLayout(updownLayout2);
//    tabWidget->addTab( weixiujilu,tr("维修记录单"));
}

void cheliangweixiuguanli::creatTabPage22()
{
    TabPageSQL22 = "select LicenseNumber 车号,Maintenance 维修保养明细,KilometreNumber 公里数,RepairPersonnel 维修人员,DriverSignature 驾驶员签字,EntryTime 录入时间,InputPerson 录入人 from VehicleMaintenanceDailyReport";
    createAction22();
    createTool22();

    QLabel *LicenseNumberLabel = new QLabel(tr("车号:"),this);
    LicenseNumberLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    QLabel *MaintenanceDateLabel = new QLabel(tr("维修日期:"),this);
    MaintenanceDateLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    QLabel *MaintenanceLabel = new QLabel(tr("维修、保养明细:"),this);
    MaintenanceLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    QLabel *KilometreNumberLabel = new QLabel(tr("公里数:"),this);
    KilometreNumberLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    QLabel *RepairPersonnelLabel = new QLabel(tr("维修人员:"),this);
    RepairPersonnelLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    QLabel *DriverSignatureLabel = new QLabel(tr("驾驶员签字:"),this);
    DriverSignatureLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    QLabel *EntryTimeLabel = new QLabel(tr("录入时间:"),this);
    EntryTimeLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    chaxunBtn22 = new QPushButton(tr("查询"),this);
    chaxunBtn22->setShortcut(Qt::Key_Enter);
    chaxunBtn22->setFixedWidth(120);
    connect(chaxunBtn22,SIGNAL(clicked()),this,SLOT(on_chaxunBtn22()));

    LicenseNumberLineEdit22 = new QLineEdit(this);
    MaintenanceDateEdit22 = new QLineEdit(this);
    MaintenanceLineEdit22 = new QLineEdit(this);
    KilometreNumberLineEdit22 = new QLineEdit(this);
    RepairPersonnelLineEdit22 = new QLineEdit(this);
    DriverSignatureLineEdit22 = new QLineEdit(this);
    EntryTimeLineEdit22 = new QLineEdit(this);

    Tableview22 = new QTableView(this);
//    db.showview(TabPageSQL2,Tableview2,&TableviewModel2);
    connect(Tableview22,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick22()));


    QHBoxLayout *UpHLayout22 = new QHBoxLayout;
    UpHLayout22->addWidget(LicenseNumberLabel,0);
    UpHLayout22->addWidget(LicenseNumberLineEdit22,0);

    UpHLayout22->addWidget(MaintenanceDateLabel,0);
    UpHLayout22->addWidget(MaintenanceDateEdit22,0);

    UpHLayout22->addWidget(KilometreNumberLabel,0);
    UpHLayout22->addWidget(KilometreNumberLineEdit22,0);

    UpHLayout22->addWidget(RepairPersonnelLabel,0);
    UpHLayout22->addWidget(RepairPersonnelLineEdit22,0);

    UpHLayout22->addWidget(DriverSignatureLabel,0);
    UpHLayout22->addWidget(DriverSignatureLineEdit22,0);

    UpHLayout22->addWidget(EntryTimeLabel,0);
    UpHLayout22->addWidget(EntryTimeLineEdit22,1);

    QHBoxLayout *UpHLayout23 = new QHBoxLayout;
    UpHLayout23->addWidget(MaintenanceLabel,0);
    UpHLayout23->addWidget(MaintenanceLineEdit22,3);

    QVBoxLayout *UpLayout22 = new QVBoxLayout;
    UpLayout22->addWidget(toolBar22,0);
    UpLayout22->addLayout(UpHLayout22);
    UpLayout22->addLayout(UpHLayout23);

    QGroupBox *upBox21 = new QGroupBox;
    upBox21->setLayout(UpLayout22);

    QVBoxLayout *DownLayout23 = new QVBoxLayout;
    DownLayout23->addWidget(chaxunBtn22);
    DownLayout23->addWidget(Tableview22);

    QGroupBox *downBox22 = new QGroupBox;
    downBox22->setLayout(DownLayout23);

    QVBoxLayout *UpLayout24 = new QVBoxLayout;
    UpLayout24->addWidget(upBox21);
    UpLayout24->addWidget(downBox22);

    cheliangweixiuribaobiao->setLayout(UpLayout24);
//    tabWidget->addTab(cheliangweixiuribaobiao,tr("车辆维修日报表"));
}

void cheliangweixiuguanli::creatTabPage3()
{
    TabPageSQL3 = "SELECT site 站点,OilDate 日期,LicenseNumber 车号,RefuelingTime 时间,FuelQuantity 加油量（公升）,FullName 姓名,Tanker 加油人,KilometreNumber 公里数, Remarks 备注,InputPerson 录入人,EntryTime 录入时间,RefuelingMethod 加油方式 FROM RefuelingList";
    createAction3();
    createTool3();

    QLabel *zhanLabel3 = new QLabel(tr("选择站点:"),this);
    zhanLabel3->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *jiayoufangshiLabel3 = new QLabel(tr("加油方式:"),this);
    jiayoufangshiLabel3->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *riqiLabel32 = new QLabel(tr("日期:"),this);
    riqiLabel32->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *riqiLabel3 = new QLabel(tr("日期:"),this);
    riqiLabel3->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *chehaoLabel3 = new QLabel(tr("车号:"),this);
    chehaoLabel3->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *shijianLabel3 = new QLabel(tr("时间:"),this);
    shijianLabel3->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *jiayouliangLabel3 = new QLabel(tr("加油量（公升）:"),this);
    jiayouliangLabel3->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *xingmingLabel3 = new QLabel(tr("姓名:"),this);
    xingmingLabel3->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *jiayourenLabel3 = new QLabel(tr("加油人:"),this);
    jiayourenLabel3->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *gonglishuLabel3 = new QLabel(tr("公里数:"),this);
    gonglishuLabel3->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *beizhuLabel3 = new QLabel(tr("备注:"),this);
    beizhuLabel3->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *lurushijianLabel3 = new QLabel(tr("录入时间:"),this);
    lurushijianLabel3->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *lururenLabel3 = new QLabel(tr("录入人:"),this);
    lururenLabel3->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    zhandianComBox3 = new myComboBox(this);
    const char *zhandianSQL3 = "select Site from SiteFuelTableHaofa;";
    db.sql_fillComboBoxItem(zhandianSQL3,zhandianComBox3);
    jiayoufangshiComBox3 = new myComboBox(this);
    const char *jiayoufangshiSQL3 = "select Fuel from SiteFuelTableHaofa;";
    db.sql_fillComboBoxItem(jiayoufangshiSQL3,jiayoufangshiComBox3);

    riqiLineEdit3 = new QLineEdit(this);
    chepaihaoComBox3 = new myComboBox(this);
    const char *chepaihaoSQL3 = "select LicensePlate from ConcreteVehicleInformation group by LicensePlate;";
    db.sql_fillComboBoxItem(chepaihaoSQL3,chepaihaoComBox3);
    connect(chepaihaoComBox3,SIGNAL(currentTextChanged(QString)),this,SLOT(ON_chepai2xingming3()));
    jiayoushijianLineEdit3 = new QLineEdit(this);
    jiayoushijianLineEdit3->setStyleSheet("color:black");
    jiayouliangLineEdit3 = new QLineEdit(this);
    xingmingComBox3 = new myComboBox(this);
    const char *xingmingSQL3 = "select Driver1 from ConcreteVehicleInformation group by Driver1;";
    db.sql_fillComboBoxItem(xingmingSQL3,xingmingComBox3);
//    connect(xingmingComBox3,SIGNAL(currentTextChanged(QString)),this,SLOT(ON_xingming2chepai3()));
    jiayourenComBox3 = new myComboBox(this);
    const char *jiayourenSQL3 = "select distinct Tanker from RefuelingList;";
    db.sql_fillComboBoxItem(jiayourenSQL3,jiayourenComBox3);
    gonglishuLineEdit3 = new QLineEdit(this);

    beizhuLineEdit3 = new QLineEdit(this);
    lurushijianLineEdit3 = new QLineEdit(this);
    lurushijianLineEdit3->setReadOnly(true);
    lururenLineEdit3 = new QLineEdit(this);
    lururenLineEdit3->setReadOnly(true);
/********************************down****************************************/
    shijianDateEdit31 = new QDateEdit(QDate::currentDate().addDays(-1),this);
    shijianDateEdit31->setCalendarPopup(true);
    QLabel *fengeLabe3 = new QLabel(tr("--"),this);
    fengeLabe3->setAlignment(Qt::AlignCenter);
    shijianDateEdit32 = new QDateEdit(QDate::currentDate(),this);
    shijianDateEdit32->setCalendarPopup(true);

    xuanzezhandianCheckBox = new QCheckBox(tr("选择站点"),this);
    zhandianComBox32 = new myComboBox(this);
    const char *zhandianSQL32 = "select Site from SiteFuelTableHaofa;";
    db.sql_fillComboBoxItem(zhandianSQL32,zhandianComBox32);
    jiayoufangshiCheckBox = new QCheckBox(tr("加油方式"),this);
    jiayoufangshiComBox32 = new myComboBox(this);
    const char *jiayoufangshiSQL32 = "select Fuel from SiteFuelTableHaofa;";
    db.sql_fillComboBoxItem(jiayoufangshiSQL32,jiayoufangshiComBox32);

    chehaoCheckBox32 = new QCheckBox(tr("车号"),this);
    chehaoComBox32 = new myComboBox(this);
    const char *chehaoSQL32 = "select LicensePlate from ConcreteVehicleInformation group by LicensePlate;";
    db.sql_fillComboBoxItem(chehaoSQL32,chehaoComBox32);

    chaxunBtn3 = new QPushButton(tr("查询"),this);
    chaxunBtn3->setShortcut(Qt::Key_Enter);
    chaxunBtn3->setFixedWidth(80);
    connect(chaxunBtn3,SIGNAL(clicked()),this,SLOT(on_chaxunBtn3()));

    huizongBtn3 = new QPushButton(tr("汇总"),this);
//    huizongBtn3->setShortcut(Qt::Key_Enter);
    huizongBtn3->setFixedWidth(80);
    connect(huizongBtn3,SIGNAL(clicked()),this,SLOT(on_huizongBtn3()));


//    QShortcut *key1=new QShortcut(QKeySequence(Qt::Key_Return),this);//创建一个快捷键"Key_Return"键
//    QShortcut *key2=new QShortcut(QKeySequence(Qt::Key_Enter),this);//创建一个快捷键"Key_Return"键
//    connect(key1,SIGNAL(activated()),this,SLOT(on_chaxunBtn3()));//连接到指定槽函数
//    connect(key2,SIGNAL(activated()),this,SLOT(on_chaxunBtn3()));//连接到指定槽函数

    daochuBtn3 = new QPushButton(tr("导出"),this);
    daochuBtn3->setFixedWidth(80);
    connect(daochuBtn3,SIGNAL(clicked()),this,SLOT(on_toExcell3()));
    QLabel *zongjiLabe3 = new QLabel(tr("总计:"),this);
    zongjiLabe32 = new QLabel(this);

    Tableview3 = new QTableView(this);
//    db.showview(TabPageSQL3,Tableview3,&TableviewModel3);
    connect(Tableview3,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick3()));
    connect(Tableview3,SIGNAL(clicked(QModelIndex)),this,SLOT(ON_Sum3()));
    Tableview3->setColumnWidth(2,200);
    Tableview3->setColumnWidth(5,150);
/**************************************************************************/

    QHBoxLayout *jiayouHLayout31 = new QHBoxLayout;//布局头部1
    jiayouHLayout31->addWidget(zhanLabel3,0);
    jiayouHLayout31->addWidget(zhandianComBox3,1);
    jiayouHLayout31->addWidget(jiayoufangshiLabel3,0);
    jiayouHLayout31->addWidget(jiayoufangshiComBox3,1);
    jiayouHLayout31->addStretch(3);
    QHBoxLayout *jiayouHLayout32 = new QHBoxLayout;//布局头部2
    jiayouHLayout32->addWidget(riqiLabel3,0);
    jiayouHLayout32->addWidget(riqiLineEdit3,2);
    jiayouHLayout32->addWidget(chehaoLabel3,0);
    jiayouHLayout32->addWidget(chepaihaoComBox3,2);
    jiayouHLayout32->addWidget(shijianLabel3,0);
    jiayouHLayout32->addWidget(jiayoushijianLineEdit3,2);
    jiayouHLayout32->addWidget(jiayouliangLabel3,0);
    jiayouHLayout32->addWidget(jiayouliangLineEdit3,2);
    jiayouHLayout32->addWidget(xingmingLabel3,0);
    jiayouHLayout32->addWidget(xingmingComBox3,2);
    jiayouHLayout32->addWidget(jiayourenLabel3,0);
    jiayouHLayout32->addWidget(jiayourenComBox3,2);
    jiayouHLayout32->addWidget(gonglishuLabel3,0);
    jiayouHLayout32->addWidget(gonglishuLineEdit3,2);

    QHBoxLayout *jiayouHLayout33 = new QHBoxLayout;//布局头部3
    jiayouHLayout33->addWidget(beizhuLabel3,0);
    jiayouHLayout33->addWidget(beizhuLineEdit3,3);
    jiayouHLayout33->addWidget(lurushijianLabel3,0);
    jiayouHLayout33->addWidget(lurushijianLineEdit3,1);
    jiayouHLayout33->addWidget(lururenLabel3,0);
    jiayouHLayout33->addWidget(lururenLineEdit3,1);

    QVBoxLayout *UpLayout3 = new QVBoxLayout;
    UpLayout3->addWidget(toolBar3,0);
    UpLayout3->addLayout(jiayouHLayout31,1);
    UpLayout3->addLayout(jiayouHLayout32,1);
    UpLayout3->addLayout(jiayouHLayout33,1);

    QHBoxLayout *DownhHlayout3 = new QHBoxLayout;
    DownhHlayout3->addWidget(riqiLabel32,0);
    DownhHlayout3->addWidget(shijianDateEdit31,1);
    DownhHlayout3->addWidget(fengeLabe3,0);
    DownhHlayout3->addWidget(shijianDateEdit32,1);
    DownhHlayout3->addWidget(xuanzezhandianCheckBox,0);
    DownhHlayout3->addWidget(zhandianComBox32,1);
    DownhHlayout3->addWidget(jiayoufangshiCheckBox,0);
    DownhHlayout3->addWidget(jiayoufangshiComBox32,1);
    DownhHlayout3->addWidget(chehaoCheckBox32,0);
    DownhHlayout3->addWidget(chehaoComBox32,1);
    DownhHlayout3->addWidget(chaxunBtn3,1);
    DownhHlayout3->addWidget(huizongBtn3,1);
    DownhHlayout3->addWidget(daochuBtn3,1);
    DownhHlayout3->addWidget(zongjiLabe3,0);
    DownhHlayout3->addWidget(zongjiLabe32,1);

    QVBoxLayout *DownVLayout3 = new QVBoxLayout(this);
    DownVLayout3->addLayout(DownhHlayout3);
    DownVLayout3->addWidget(Tableview3);

    QGroupBox *UpBox = new QGroupBox;
    UpBox->setLayout(UpLayout3);

    QGroupBox *DownBox = new QGroupBox;
    DownBox->setLayout(DownVLayout3);

    QVBoxLayout *UpDownLayout3 = new QVBoxLayout(this);
    UpDownLayout3->addWidget(UpBox,1);
    UpDownLayout3->addWidget(DownBox,4);

    jiayoumingxiliangbiao->setLayout(UpDownLayout3);
//    tabWidget->addTab(jiayoumingxiliangbiao,tr("加油明细表"));
}

void cheliangweixiuguanli::creatTabPage4()
{
    TabPageSQL41 ="select mid(OutboundTime,1,10) 日期,DeliveryVehicle 车号,Driver 姓名,Engineering 到达工地,Customer 客户名称,COUNT(1) 车次,SUM(CASE WHEN PouringMethod='吊罐' THEN 1 ELSE 0 END) 吊,  0 剩料补金额数, 0 绕修补公里数,PlantName 备注,Mileage 里程, SUM(Mileage) 总里程 DrivingRecordTable.Time,修改时间 from ProductionNotice,DrivingRecordTable GROUP BY Driver, MID(OutboundTime,1,10),Engineering";
    createAction4();
    createTool4();

    QLabel *shijianLabel4 = new QLabel(tr("时间:"),this);
    shijianLabel4->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *chehaoLabel4 = new QLabel(tr("车号:"),this);
    chehaoLabel4->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *xingmingLabel4 = new QLabel(tr("姓名:"),this);
    xingmingLabel4->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *daodagongdiLabel4 = new QLabel(tr("到达工地:"),this);
    daodagongdiLabel4->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *checiLabel4 = new QLabel(tr("车次:"),this);
    checiLabel4->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *diaoLabel4 = new QLabel(tr("吊:"),this);
    diaoLabel4->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *shengliaobujineshuLabel4 = new QLabel(tr("剩料补金额数:"),this);
    shengliaobujineshuLabel4->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *raoxiubugonglishuLabel4 = new QLabel(tr("绕修补公里数:"),this);
    raoxiubugonglishuLabel4->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *beizhuLabel4 = new QLabel(tr("备注:"),this);
    beizhuLabel4->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *lichengLabel4 = new QLabel(tr("里程:"),this);
    lichengLabel4->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *zonglichengLabel4 = new QLabel(tr("总里程:"),this);//只显示不插入到数据库
    zonglichengLabel4->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *xiugaishijianLabel4 = new QLabel(tr("修改时间:"),this);//只显示不插入到数据库
    xiugaishijianLabel4->setAlignment(Qt::AlignVCenter|Qt::AlignRight);


    shijianLineEdit4 = new QLineEdit(this);
    shijianLineEdit4->setReadOnly(true);
    chehaoLineEdit4 = new QLineEdit(this);
    chehaoLineEdit4->setReadOnly(true);
    xingmingLineEdit4 = new QLineEdit(this);
    xingmingLineEdit4->setReadOnly(true);
    daodagongdiLineEdit4 = new QLineEdit(this);
    daodagongdiLineEdit4->setReadOnly(true);
    checiLineEdit4 = new QLineEdit(this);
    checiLineEdit4->setReadOnly(true);
    diaoLineEdit4 = new QLineEdit(this);
    diaoLineEdit4->setReadOnly(true);
    shengliaobujineshuLineEdit4 = new QLineEdit(this);
//    shengliaobujineshuLineEdit4->setReadOnly(true);
    raoxiubugonglishuLineEdit4 = new QLineEdit(this);
//    raoxiubugonglishuLineEdit4->setReadOnly(true);
    beizhuLineEdit4 = new QLineEdit(this);
//    beizhuLineEdit4->setReadOnly(true);
    lichengLineEdit4 = new QLineEdit(this);
    connect(lichengLineEdit4,SIGNAL(textChanged(QString)),this,SLOT(on_zonglicheng4()));
    zonglichengLineEdit4 = new QLineEdit(this);
    zonglichengLineEdit4->setReadOnly(true);
    xiugaishijianLineEdit4 = new QLineEdit(this);
    xiugaishijianLineEdit4->setReadOnly(true);

/********************************down****************************************/
    QLabel *riqiLabel4 = new QLabel(tr("日期:"),this);
    riqiLabel4->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    shijianDateEdit41 = new QDateEdit(QDate::currentDate().addDays(-1),this);
    shijianDateEdit41->setCalendarPopup(true);
    QLabel *fengeLabe4 = new QLabel(tr("--"),this);
    fengeLabe4->setAlignment(Qt::AlignCenter);
    shijianDateEdit42 = new QDateEdit(QDate::currentDate(),this);
    shijianDateEdit42->setCalendarPopup(true);

    jiashiyuanCheckBox4 = new QCheckBox(tr("车号"),this);
    jiashiyuanComBox4 = new myComboBox(this);
    const char *jiashiyuanSQL4 = "select distinct DeliveryVehicle from ProductionNotice;";
    db.sql_fillComboBoxItem(jiashiyuanSQL4,jiashiyuanComBox4);

    jiashiyuanSiJiCheckBox4 = new QCheckBox(tr("司机"),this);
    jiashiyuanSiJiComBox4 = new myComboBox(this);
    const char *jiashiyuanSiJiSQL4 = "select distinct Driver from ProductionNotice;";
    db.sql_fillComboBoxItem(jiashiyuanSiJiSQL4,jiashiyuanSiJiComBox4);


    chaxunBtn4 = new QPushButton(tr("行车记录表"),this);
    chaxunBtn4->setShortcut(Qt::Key_Enter);
    chaxunBtn4->setFixedWidth(120);
    connect(chaxunBtn4,SIGNAL(clicked()),this,SLOT(on_chaxunBtn4()));

    yunjuchaxunBtn4 = new QPushButton(tr("运距记录表"),this);
    yunjuchaxunBtn4->setFixedWidth(120);
    yunjuchaxunBtn4->setHidden(true);
    connect(yunjuchaxunBtn4,SIGNAL(clicked()),this,SLOT(on_yunjuchaxunBtn4()));

    daochuBtn4 = new QPushButton(tr("导出"),this);
    daochuBtn4->setFixedWidth(120);
    connect(daochuBtn4,SIGNAL(clicked()),this,SLOT(on_toExcell4()));
    QLabel *zongjiLabe4 = new QLabel(tr("总计:"),this);
    zongjiLabe42 = new QLabel(this);
    QLabel *zongjineLabe4 = new QLabel(tr("总金额:"),this);
    zongjineLabe42 = new QLabel(this);


    Tableview4 = new QTableView(this);
//    connect(Tableview4,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick4()));
    connect(Tableview4,SIGNAL(clicked(QModelIndex)),this,SLOT(ON_Sum4()));
    Tableview4->setColumnWidth(3,230);
    Tableview4->setColumnWidth(4,60);
    Tableview4->setColumnWidth(5,60);
    Tableview4->setColumnWidth(8,60);
    Tableview4->setColumnWidth(9,60);
    Tableview4->setColumnWidth(10,60);

/**************************************************************************/
    QHBoxLayout *jiayouHLayout41 = new QHBoxLayout;//布局头部1
    jiayouHLayout41->addWidget(shijianLabel4,0);
    jiayouHLayout41->addWidget(shijianLineEdit4,1);
    jiayouHLayout41->addWidget(chehaoLabel4,0);
    jiayouHLayout41->addWidget(chehaoLineEdit4,1);
    jiayouHLayout41->addWidget(xingmingLabel4,0);
    jiayouHLayout41->addWidget(xingmingLineEdit4,1);
    jiayouHLayout41->addWidget(daodagongdiLabel4,0);
    jiayouHLayout41->addWidget(daodagongdiLineEdit4,1);
    jiayouHLayout41->addWidget(checiLabel4,0);
    jiayouHLayout41->addWidget(checiLineEdit4,1);
    jiayouHLayout41->addWidget(diaoLabel4,0);
    jiayouHLayout41->addWidget(diaoLineEdit4,1);

    QHBoxLayout *jiayouHLayout42 = new QHBoxLayout;//布局头部2
    jiayouHLayout42->addWidget(shengliaobujineshuLabel4,0);
    jiayouHLayout42->addWidget(shengliaobujineshuLineEdit4,1);
    jiayouHLayout42->addWidget(raoxiubugonglishuLabel4,0);
    jiayouHLayout42->addWidget(raoxiubugonglishuLineEdit4,1);
    jiayouHLayout42->addWidget(beizhuLabel4,0);
    jiayouHLayout42->addWidget(beizhuLineEdit4,1);
    jiayouHLayout42->addWidget(lichengLabel4,0);
    jiayouHLayout42->addWidget(lichengLineEdit4,1);
    jiayouHLayout42->addWidget(zonglichengLabel4,0);
    jiayouHLayout42->addWidget(zonglichengLineEdit4,1);
    jiayouHLayout42->addWidget(xiugaishijianLabel4,0);
    jiayouHLayout42->addWidget(xiugaishijianLineEdit4,1);

    QVBoxLayout *UpLayout4 = new QVBoxLayout;
    UpLayout4->addWidget(toolBar4,0);
    UpLayout4->addLayout(jiayouHLayout41,1);
    UpLayout4->addLayout(jiayouHLayout42,1);

    QHBoxLayout *DownhHlayout4 = new QHBoxLayout;
    DownhHlayout4->addWidget(riqiLabel4,0);
    DownhHlayout4->addWidget(shijianDateEdit41,1);
    DownhHlayout4->addWidget(fengeLabe4,0);
    DownhHlayout4->addWidget(shijianDateEdit42,1);
    DownhHlayout4->addWidget(jiashiyuanCheckBox4,0);
    DownhHlayout4->addWidget(jiashiyuanComBox4,1);
    DownhHlayout4->addWidget(jiashiyuanSiJiCheckBox4,0);
    DownhHlayout4->addWidget(jiashiyuanSiJiComBox4,1);
    DownhHlayout4->addWidget(chaxunBtn4,1);
//    DownhHlayout4->addWidget(yunjuchaxunBtn4,1);
    DownhHlayout4->addWidget(daochuBtn4,1);
    DownhHlayout4->addWidget(zongjiLabe4,0);
    DownhHlayout4->addWidget(zongjiLabe42,1);
    DownhHlayout4->addWidget(zongjineLabe4,1);
    DownhHlayout4->addWidget(zongjineLabe42,1);

    QVBoxLayout *DownVLayout4 = new QVBoxLayout;
    DownVLayout4->addLayout(DownhHlayout4);
    DownVLayout4->addWidget(Tableview4);

    QGroupBox *UpBox4 = new QGroupBox;
    UpBox4->setLayout(UpLayout4);

    QGroupBox *DownBox4 = new QGroupBox;
    DownBox4->setLayout(DownVLayout4);

    QVBoxLayout *UpDownLayout4 = new QVBoxLayout(this);
    UpDownLayout4->addWidget(UpBox4,1);
    UpDownLayout4->addWidget(DownBox4,4);

    xingchejilubiao->setLayout(UpDownLayout4);
    tabWidget->addTab(xingchejilubiao,tr("外租车费用表"));
}

void cheliangweixiuguanli::creatTabPage5()
{

    TabPageSQL5 ="SELECT ProductionNotice.DeliveryVehicle 车号,\
            ProductionNotice.Driver 驾驶员,\
            ReceiptVolume 方量,\
            SUM(CASE WHEN ProductionNotice.PouringMethod='吊罐' THEN 1 ELSE 0 END) 吊罐次数,\
            0 补助金额,\
            0 + COUNT(1)*41 + SUM(CASE WHEN ProductionNotice.PouringMethod='吊罐' THEN 1 ELSE 0 END)*9 合计金额,\
            SUM(ProductionNotice.Mileage)考核里程,\
            DrivingRecordTable.MendingTheNumberOfKilometers 调整里程,\
            RefuelingList.FuelQuantity 实际耗油,\
            RefuelingList.FuelQuantity / ((SUM(ProductionNotice.Mileage) +IF(DrivingRecordTable.MendingTheNumberOfKilometers IS NULL,0,DrivingRecordTable.MendingTheNumberOfKilometers)) / 100)百公里耗油,\
            (45- RefuelingList.FuelQuantity / (SUM(ProductionNotice.Mileage) +IF(DrivingRecordTable.MendingTheNumberOfKilometers IS NULL,0,DrivingRecordTable.MendingTheNumberOfKilometers)) * 100)*((SUM(ProductionNotice.Mileage) +IF(DrivingRecordTable.MendingTheNumberOfKilometers IS NULL,0,DrivingRecordTable.MendingTheNumberOfKilometers)) / 100) 节油数,\
            ((45- RefuelingList.FuelQuantity / (SUM(ProductionNotice.Mileage) +IF(DrivingRecordTable.MendingTheNumberOfKilometers IS NULL,0,DrivingRecordTable.MendingTheNumberOfKilometers)) * 100)*((SUM(ProductionNotice.Mileage) +IF(DrivingRecordTable.MendingTheNumberOfKilometers IS NULL,0,DrivingRecordTable.MendingTheNumberOfKilometers)) / 100))*5 奖励,\
            0 超级奖励,\
            300 + COUNT(1)*41 + SUM(CASE WHEN ProductionNotice.PouringMethod='吊罐' THEN 1 ELSE 0 END)*9 + ((45- RefuelingList.FuelQuantity / (SUM(ProductionNotice.Mileage) +IF(DrivingRecordTable.MendingTheNumberOfKilometers IS NULL,0,DrivingRecordTable.MendingTheNumberOfKilometers)) * 100)*((SUM(ProductionNotice.Mileage) +IF(DrivingRecordTable.MendingTheNumberOfKilometers IS NULL,0,DrivingRecordTable.MendingTheNumberOfKilometers)) / 100))*5 + 0 工资\
            from ProductionNotice , DrivingRecordTable , RefuelingList WHERE ProductionNotice.Driver = DrivingRecordTable.FullName AND DrivingRecordTable.FullName = RefuelingList.FullName and MID(ProductionNotice.OutboundTime,1,10) = '2017-12-07' order by ProductionNotice.Driver";

    createAction5();
    createTool5();

    QLabel *chehaoLabel5 = new QLabel(tr("车号:"),this);
    chehaoLabel5->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *jiashiyuanLabel5 = new QLabel(tr("驾驶员:"),this);
    jiashiyuanLabel5->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *yunshucishuLabel5 = new QLabel(tr("运输次数:"),this);
    yunshucishuLabel5->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *diaoguancishuLabel5 = new QLabel(tr("吊罐次数:"),this);
    diaoguancishuLabel5->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *buzhujineLabel5 = new QLabel(tr("补助金额:"),this);
    buzhujineLabel5->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *hejijineshuLabel5 = new QLabel(tr("合计金额:"),this);
    hejijineshuLabel5->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *kaohelichengLabel5 = new QLabel(tr("考核里程:"),this);
    kaohelichengLabel5->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *tiaozhenglichengLabel5 = new QLabel(tr("调整里程:"),this);
    tiaozhenglichengLabel5->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *shijihaoyouLabel5 = new QLabel(tr("实际耗油:"),this);
    shijihaoyouLabel5->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *baigonglihaoyouLabel5 = new QLabel(tr("百公里耗油:"),this);
    baigonglihaoyouLabel5->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *jieyoushuLabel5 = new QLabel(tr("节油数:"),this);
    jieyoushuLabel5->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *jiangliLabel5 = new QLabel(tr("奖励:"),this);
    jiangliLabel5->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *chaoejiangliLabel5 = new QLabel(tr("超额奖励:"),this);
    chaoejiangliLabel5->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *gongziLabel5 = new QLabel(tr("工资:"),this);
    gongziLabel5->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    chehaoLineEdit5 = new QLineEdit(this);
    chehaoLineEdit5->setReadOnly(true);
    jiashiyuanLineEdit5 = new QLineEdit(this);
    jiashiyuanLineEdit5->setReadOnly(true);
    yunshucishuLineEdit5 = new QLineEdit(this);
    yunshucishuLineEdit5->setReadOnly(true);
    diaoguancishuLineEdit5 = new QLineEdit(this);
    diaoguancishuLineEdit5->setReadOnly(true);
    buzhujineLineEdit5 = new QLineEdit(this);
    buzhujineLineEdit5->setReadOnly(true);
    hejijineshuLineEdit5 = new QLineEdit(this);
    hejijineshuLineEdit5->setReadOnly(true);
    kaohelichengLineEdit5 = new QLineEdit(this);
    kaohelichengLineEdit5->setReadOnly(true);
    tiaozhenglichengLineEdit5 = new QLineEdit(this);
    tiaozhenglichengLineEdit5->setReadOnly(true);
    shijihaoyouLineEdit5 = new QLineEdit(this);
    shijihaoyouLineEdit5->setReadOnly(true);
    baigonglihaoyouLineEdit5 = new QLineEdit(this);
    baigonglihaoyouLineEdit5->setReadOnly(true);
    jieyoushuLineEdit5 = new QLineEdit(this);
    jieyoushuLineEdit5->setReadOnly(true);
    jiangliLineEdit5 = new QLineEdit(this);
    jiangliLineEdit5->setReadOnly(true);
    chaoejiangliLineEdit5 = new QLineEdit(this);
    chaoejiangliLineEdit5->setReadOnly(true);
    gongziLineEdit5 = new QLineEdit(this);
    gongziLineEdit5->setReadOnly(true);

    QLabel *riqiLabel5 = new QLabel(tr("日期:"),this);
    riqiLabel5->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    shijianDateEdit51 = new QDateEdit(QDate::currentDate().addDays(-1),this);
    shijianDateEdit51->setCalendarPopup(true);
    QLabel *fengeLabe5 = new QLabel(tr("--"),this);
    fengeLabe5->setAlignment(Qt::AlignCenter);
    shijianDateEdit52 = new QDateEdit(QDate::currentDate(),this);
    shijianDateEdit52->setCalendarPopup(true);

    jiashiyuanCheckBox5 = new QCheckBox(tr("车号"),this);
    jiashiyuanComBox5 = new myComboBox(this);
    const char *jiashiyuanSQL5 = "select distinct DeliveryVehicle from ProductionNotice;";
    db.sql_fillComboBoxItem(jiashiyuanSQL5,jiashiyuanComBox5);

    jiashiyuanSiJiCheckBox5 = new QCheckBox(tr("司机"),this);
    jiashiyuanSiJiComBox5 = new myComboBox(this);
    const char *jiashiyuanSiJiSQL5 = "select distinct Driver from ProductionNotice;";
    db.sql_fillComboBoxItem(jiashiyuanSiJiSQL5,jiashiyuanSiJiComBox5);



    Tableview5 = new QTableView(this);
//    connect(Tableview5,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick5()));
    connect(Tableview5,SIGNAL(clicked(QModelIndex)),this,SLOT(ON_Sum5()));
    Tableview5->setColumnWidth(3,100);
    Tableview5->setColumnWidth(0,300);

    chaxunBtn5 = new QPushButton(tr("查询"),this);
    chaxunBtn5->setShortcut(Qt::Key_Enter);
    chaxunBtn5->setFixedWidth(120);

    connect(chaxunBtn5,SIGNAL(clicked()),this,SLOT(on_chaxunBtn5()));

    daochuBtn5 = new QPushButton(tr("导出"),this);
    daochuBtn5->setFixedWidth(120);
    connect(daochuBtn5,SIGNAL(clicked()),this,SLOT(on_toExcell5()));
    QLabel *zongjiLabe5 = new QLabel(tr("总计:"),this);
    zongjiLabe52 = new QLabel(this);



/**************************************************************************/
    QHBoxLayout *jiayouHLayout51 = new QHBoxLayout;//布局头部1
    jiayouHLayout51->addWidget(chehaoLabel5,0);
    jiayouHLayout51->addWidget(chehaoLineEdit5,1);
    jiayouHLayout51->addWidget(jiashiyuanLabel5,0);
    jiayouHLayout51->addWidget(jiashiyuanLineEdit5,1);
    jiayouHLayout51->addWidget(yunshucishuLabel5,0);
    jiayouHLayout51->addWidget(yunshucishuLineEdit5,1);
    jiayouHLayout51->addWidget(diaoguancishuLabel5,0);
    jiayouHLayout51->addWidget(diaoguancishuLineEdit5,1);
    jiayouHLayout51->addWidget(buzhujineLabel5,0);
    jiayouHLayout51->addWidget(buzhujineLineEdit5,1);
    jiayouHLayout51->addWidget(hejijineshuLabel5,0);
    jiayouHLayout51->addWidget(hejijineshuLineEdit5,1);
    jiayouHLayout51->addWidget(kaohelichengLabel5,0);
    jiayouHLayout51->addWidget(kaohelichengLineEdit5,1);

    QHBoxLayout *jiayouHLayout52 = new QHBoxLayout;//布局头部2
    jiayouHLayout52->addWidget(tiaozhenglichengLabel5,0);
    jiayouHLayout52->addWidget(tiaozhenglichengLineEdit5,1);
    jiayouHLayout52->addWidget(shijihaoyouLabel5,0);
    jiayouHLayout52->addWidget(shijihaoyouLineEdit5,1);
    jiayouHLayout52->addWidget(baigonglihaoyouLabel5,0);
    jiayouHLayout52->addWidget(baigonglihaoyouLineEdit5,1);
    jiayouHLayout52->addWidget(jieyoushuLabel5,0);
    jiayouHLayout52->addWidget(jieyoushuLineEdit5,1);
    jiayouHLayout52->addWidget(jiangliLabel5,0);
    jiayouHLayout52->addWidget(jiangliLineEdit5,1);
    jiayouHLayout52->addWidget(chaoejiangliLabel5,0);
    jiayouHLayout52->addWidget(chaoejiangliLineEdit5,1);
    jiayouHLayout52->addWidget(gongziLabel5,0);
    jiayouHLayout52->addWidget(gongziLineEdit5,1);


    QStringList cf = db.CreatStrList("SELECT *FROM cheliangyunshufeiyongshezhi");
    QString diaoguanjiage = cf.at(0);
    QString dacheyunfei = cf.at(1);
    QString xiaocheyunfei = cf.at(2);
    QString dacheyouhao = cf.at(3);
    QString xiaocheyouhao = cf.at(4);

    QString biaoqian5 = QString("运费标准:大车运费'%1'元/次,小车运费'%2'元/次,吊灌'%3'元/次 油耗标准:大车'%4'升/百公里油耗,小车'%5'升/百公里油耗").arg(dacheyunfei,xiaocheyunfei,diaoguanjiage,dacheyouhao,xiaocheyouhao);


    QLabel *shuoming5 = new QLabel(biaoqian5,this);
    shuoming5->setStyleSheet("color:red"); // 设置QLabel背景的颜色
    QHBoxLayout *UpHLayout51 = new QHBoxLayout;
    UpHLayout51->addWidget(toolBar5,0);
    UpHLayout51->addWidget(shuoming5,0);
    UpHLayout51->addStretch(3);

    QVBoxLayout *UpLayout5 = new QVBoxLayout;
    UpLayout5->addLayout(UpHLayout51,0);
    UpLayout5->addLayout(jiayouHLayout51,1);
    UpLayout5->addLayout(jiayouHLayout52,1);

    QHBoxLayout *DownhHlayout5 = new QHBoxLayout;
    DownhHlayout5->addWidget(riqiLabel5,0);
    DownhHlayout5->addWidget(shijianDateEdit51,1);
    DownhHlayout5->addWidget(fengeLabe5,0);
    DownhHlayout5->addWidget(shijianDateEdit52,1);
    DownhHlayout5->addWidget(jiashiyuanCheckBox5,0);
    DownhHlayout5->addWidget(jiashiyuanComBox5,1);
    DownhHlayout5->addWidget(jiashiyuanSiJiCheckBox5,0);
    DownhHlayout5->addWidget(jiashiyuanSiJiComBox5,1);
    DownhHlayout5->addWidget(chaxunBtn5,1);
    DownhHlayout5->addWidget(daochuBtn5,1);
    DownhHlayout5->addWidget(zongjiLabe5,0);
    DownhHlayout5->addWidget(zongjiLabe52,1);

    QVBoxLayout *DownVLayout5 = new QVBoxLayout;
    DownVLayout5->addLayout(DownhHlayout5);
    DownVLayout5->addWidget(Tableview5);

    QGroupBox *UpBox5 = new QGroupBox;
    UpBox5->setLayout(UpLayout5);

    QGroupBox *DownBox5 = new QGroupBox;
    DownBox5->setLayout(DownVLayout5);


    QVBoxLayout *UpDownLayout5 = new QVBoxLayout(this);
//    UpDownLayout5->addWidget(UpBox5,1);
    UpDownLayout5->addWidget(DownBox5,4);

    kaohezongbiao->setLayout(UpDownLayout5);
    tabWidget->addTab(kaohezongbiao,tr("自家车费用表"));
}

void cheliangweixiuguanli::creatTabPage6()
{
   tabWidget->addTab(peizhiyemian,tr("价格配置页面"));
}

void cheliangweixiuguanli::on_newAction()
{
    weixiushijianlineEdit->setEnabled(true);
    saveAction->setEnabled(true);
    updateAction->setEnabled(false);
    deleteAction->setEnabled(false);

    weixiushijianlineEdit->clear();
    chepaihaocomBox1->setCurrentIndex(0);
    sijiBox->setCurrentIndex(0);

    gongshifeiLineEdit->clear();
    gonghuofangLineEdit->clear();

    weixiushijianlineEdit->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    weiXiuStateComBox->setCurrentIndex(0);

    lurushijianlineEdit->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
}

void cheliangweixiuguanli::on_mingxichaxun()
{
    shijianCheckBox = new QCheckBox(tr("维修时间"),this);
    chepaiCheckBox = new QCheckBox(tr("车号"),this);

    QString shijian,chepai;
    if(shijianCheckBox->checkState() == 2){
        shijian = QString(" and Input_Time between '%1' and '%2'").arg(shijianDateEdit1->date().toString("yyyy-MM-dd"),shijianDateEdit2->date().toString("yyyy-MM-dd"));
    }
    if(chepaiCheckBox->checkState() == 2){
        chepai = QString(" and CheNO '%1'").arg(threechepaihaocomBox->currentText());
    }

    QString searchSQL = QString("select Input_Time 维修时间,CheNO 车号,Mode 更改配件名称及规格,Fee 工时费,UseMan 使用人,Time 录入时间, person 记录人,Custom 供货方 from cheliangweixiuhaofa where NO is not null %1 %2").arg(shijian,chepai);
    db.showview(searchSQL.toStdString().data(),threeview,&threemodel);
}

void cheliangweixiuguanli::on_saveAction()
{
    if(weixiushijianlineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请检查时间是否存在"),0,0,0);
        return;
    }
    if(chepaihaocomBox1->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择车号"),0,0,0);
        return;
    }
    if(sijiBox->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择司机"),0,0,0);
        return;
    }
    if(weiXiuStateComBox->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入车辆维修项目"),0,0,0);
        return;
    }

    if(gongshifeiLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("工时费不完整"),0,0,0);
        return;
    }

    if(gonghuofangLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("供货方不完整"),0,0,0);
        return;
    }


    QString saveSQL = QString("insert into cheliangweixiuhaofa (Input_Time,CheNO,Mode,Fee,UseMan,Time, person,Custom) values ('%1','%2','%3','%4','%5','%6','%7','%8');")
                .arg(weixiushijianlineEdit->text(),chepaihaocomBox1->currentText(),weiXiuStateComBox->currentText(),gongshifeiLineEdit->text(),sijiBox->currentText(),QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"),userName,gonghuofangLineEdit->text());
    int res = db.sql_exec(saveSQL.toStdString().data());

    if(res == 0){
        QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
        on_chaxunBtn();
        weixiushijianlineEdit->clear();
        chepaihaocomBox1->setCurrentIndex(0);
        sijiBox->setCurrentIndex(0);
        weiXiuStateComBox->setCurrentIndex(0);
        gongshifeiLineEdit->clear();
        gonghuofangLineEdit->clear();
        lurushijianlineEdit->clear();
    }

}

void cheliangweixiuguanli::on_updateAction()//2017-11-6 修改
{
    if(weixiushijianlineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请检查时间是否存在"),0,0,0);
        return;
    }
    if(chepaihaocomBox1->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择车号"),0,0,0);
        return;
    }
    if(sijiBox->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择司机"),0,0,0);
        return;
    }
    if(weiXiuStateComBox->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入车辆维修项目"),0,0,0);
        return;
    }

    if(gongshifeiLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("工时费不完整"),0,0,0);
        return;
    }
    if(gonghuofangLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("供货方不完整"),0,0,0);
        return;
    }

    //update
    QString saveSQL = QString("update cheliangweixiuhaofa set Input_Time='%1',CheNO = '%2',Mode='%3',Fee='%4',UseMan='%5',Custom ='%6' WHERE Time='%7';")
                .arg(weixiushijianlineEdit->text(),chepaihaocomBox1->currentText(),weiXiuStateComBox->currentText(),gongshifeiLineEdit->text(),sijiBox->currentText(),gonghuofangLineEdit->text(),lurushijianlineEdit->text());


    int res = db.sql_exec(saveSQL.toStdString().data());
    if(res == -1 ){
        if((strstr(db.geterror(),"TimeID")) != NULL){
            QMessageBox::information(this,tr("错误"),tr("请检查时间是否重复"),0,0,0);
            return;
        }
    }
    else if(res == 0 ){

        QMessageBox::information(this,tr("提示信息"),tr("修改成功"),0,0,0);
        on_chaxunBtn();
        weixiushijianlineEdit->clear();
        chepaihaocomBox1->setCurrentIndex(0);
        sijiBox->setCurrentIndex(0);
        weiXiuStateComBox->setCurrentIndex(0);
        gongshifeiLineEdit->clear();
        gonghuofangLineEdit->clear();
        lurushijianlineEdit->clear();
    }
}

void cheliangweixiuguanli::on_deleteAction()
{
    QString deleteSQL = QString("delete from cheliangweixiuhaofa where Time='%1';").arg(lurushijianlineEdit->text());
    int res = db.sql_exec(deleteSQL.toStdString().data());

    if(res == 0){
        QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
        on_chaxunBtn();
        weixiushijianlineEdit->clear();
        chepaihaocomBox1->setCurrentIndex(0);
        sijiBox->setCurrentIndex(0);
        weiXiuStateComBox->setCurrentIndex(0);
        gongshifeiLineEdit->clear();
        gonghuofangLineEdit->clear();
        lurushijianlineEdit->clear();
    }
}

void cheliangweixiuguanli::createAction()
{
    newAction = new QAction(tr("新增"),this);
    newAction->setIcon(QIcon(":/image/new.png"));
    connect(newAction,SIGNAL(triggered()),this,SLOT(on_newAction()));
    saveAction = new QAction(tr("保存"),this);
    saveAction->setEnabled(false);
    saveAction->setIcon(QIcon(":/image/save.png"));
    connect(saveAction,SIGNAL(triggered()),this,SLOT(on_saveAction()));

    newAction->setShortcut(Qt::Key_F12);//设置快捷键字母键盘的enter键
    saveAction->setShortcut(Qt::Key_Return);//设置快捷键字母键盘的enter键

    updateAction = new QAction(tr("修改"),this);
    updateAction->setEnabled(false);
    updateAction->setIcon(QIcon(":/image/update.png"));
    connect(updateAction,SIGNAL(triggered()),this,SLOT(on_updateAction()));

    deleteAction = new QAction(tr("删除"),this);
    deleteAction->setEnabled(false);
    deleteAction->setIcon(QIcon(":/image/delete.png"));
    connect(deleteAction,SIGNAL(triggered()),this,SLOT(on_deleteAction()));
}

void cheliangweixiuguanli::createTool()
{
    toolBar = new QToolBar(this);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar->addAction(newAction);
    toolBar->addAction(saveAction);
    toolBar->addAction(updateAction);
    toolBar->addAction(deleteAction);
}

void cheliangweixiuguanli::chepai2ON_xingming1()
{
    QString shiyongrenstr = QString("select Driver1 from ConcreteVehicleInformation where LicensePlate = '%1'").arg(chepaihaocomBox1->currentText());
    sijiBox->setCurrentText(db.sql_fetchrow_plus(shiyongrenstr.toStdString().data(),0));
    sijiBox->setEditable(true);
}

void cheliangweixiuguanli::ON_xingming2chepai1()
{
    QString chepaistr = QString("select LicensePlate from ConcreteVehicleInformation where Driver1 = '%1'").arg(sijiBox->currentText());
    chepaihaocomBox1->setCurrentText(db.sql_fetchrow_plus(chepaistr.toStdString().data(),0));
    chepaihaocomBox1->setEditable(true);
}

void cheliangweixiuguanli::on_chaxunBtn()
{
    QString shijian,gonghuofang;
    if(shijianCheckBox->checkState() == 2){
        shijian = QString(" and Input_Time between '%1' and '%2'").arg(shijianDateEdit1->date().toString("yyyy-MM-dd"),shijianDateEdit2->date().toString("yyyy-MM-dd"));
    }
    if(gonghuofangCheckBox->checkState() == 2){
        gonghuofang = QString(" and Custom = '%1'").arg(gonghuofangcomBox->currentText());
    }

    QString searchSQL = QString("select Input_Time 维修时间,CheNO 车号,Mode 更改配件名称及规格,Fee 工时费,UseMan 使用人,Time 录入时间, person 记录人 ,Custom 供货方 from cheliangweixiuhaofa where CheNO is not null %1 %2").arg(shijian,gonghuofang);
    db.showview(searchSQL.toStdString().data(),threeview,&threemodel);
}

void cheliangweixiuguanli::ShowSupplyclick()
{
    weixiushijianlineEdit->setEnabled(true);
    newAction->setEnabled(true);
    saveAction->setEnabled(false);
    updateAction->setEnabled(true);
    deleteAction->setEnabled(true);

    int row = threeview->currentIndex().row();

    /****************************************************************************/
//    double sum1 = 0;
//    for(int i = 0;i<row;i++){
//        sum1+=threemodel->item(i,3)->text().toDouble();
//    }

//    gonghuofangcomBox->setCurrentText(QString::number(sum1,10, 4));
    /**************************************************************************/

    weixiushijianlineEdit->setText(threemodel->item(row,0)->text());//维修时间
    chepaihaocomBox1->setCurrentText(threemodel->item(row,1)->text());//车号
    weiXiuStateComBox->setCurrentText(threemodel->item(row,2)->text());//维修项目
    gongshifeiLineEdit->setText(threemodel->item(row,3)->text());//工时费
    sijiBox->setCurrentText(threemodel->item(row,4)->text());//使用人
    lurushijianlineEdit->setText(threemodel->item(row,5)->text());//维修编号
    gonghuofangLineEdit->setText(threemodel->item(row,6)->text());//供货方
}

void cheliangweixiuguanli::ON_Sum1()
{

    int row = threeview->currentIndex().row();
    int column = threeview->currentIndex().column();
    /****************************************************************************/
    double sum1 = 0;
    for(int i = 0;i<=row;i++){
        sum1+=threemodel->item(i,column)->text().toDouble();
//        zongjilineEdit->setText(QString::number(sum1,10, 4));
        zongjiLabel2->setText(QString::number(sum1,10, 4));

    }
    /**************************************************************************/
}

void cheliangweixiuguanli::createAction2()
{
    newAction2 = new QAction(tr("新增"),this);
    newAction2->setIcon(QIcon(":/image/new.png"));
    connect(newAction2,SIGNAL(triggered()),this,SLOT(on_newAction2()));
    saveAction2 = new QAction(tr("保存"),this);
    saveAction2->setEnabled(false);
    saveAction2->setIcon(QIcon(":/image/save.png"));
    connect(saveAction2,SIGNAL(triggered()),this,SLOT(on_saveAction2()));

    newAction2->setShortcut(Qt::Key_F12);//设置快捷键字母键盘的enter键
    saveAction2->setShortcut(Qt::Key_Return);//设置快捷键字母键盘的enter键

    updateAction2 = new QAction(tr("修改"),this);
    updateAction2->setEnabled(false);
    updateAction2->setIcon(QIcon(":/image/update.png"));
    connect(updateAction2,SIGNAL(triggered()),this,SLOT(on_updateAction2()));

    deleteAction2 = new QAction(tr("删除"),this);
    deleteAction2->setEnabled(false);
    deleteAction2->setIcon(QIcon(":/image/delete.png"));
    connect(deleteAction2,SIGNAL(triggered()),this,SLOT(on_deleteAction2()));
}

void cheliangweixiuguanli::createTool2()
{
    toolBar2 = new QToolBar(this);
    toolBar2->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar2->addAction(newAction2);
    toolBar2->addAction(saveAction2);
    toolBar2->addAction(updateAction2);
    toolBar2->addAction(deleteAction2);
}

void cheliangweixiuguanli::on_toExcell()
{
    view2Excel->Table2ExcelByHtml(threeview,"外出维修对账单");
}

void cheliangweixiuguanli::on_toExcell2()
{
    view2Excel->Table2ExcelByHtml(Tableview2,"维修记录");
}

void cheliangweixiuguanli::on_peijianBtn2()
{

    disconnect(Tableview2,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick2()));

    QString shijian2,chehao2;
    if(chehaoCheckBox21->checkState() == 2){
        chehao2 = QString(" and LicenseNumber = '%1'").arg(chehaoComBox21->currentText());
    }

    shijian2 = QString(" and MaintenanceTime between '%1' and '%2'").arg(shijianDateEdit21->date().toString("yyyy-MM-dd"),shijianDateEdit22->date().toString("yyyy-MM-dd"));
    QString searchSQL = QString("select Parts 更改配件名称及规格,SUM(Num) 数量,Unit 单位,Remarks 备注 from MaintenanceRecordHaofa where Parts is not null %1 %2 Group by Parts").arg(shijian2,chehao2);
    db.showview(searchSQL.toStdString().data(),Tableview2,&TableviewModel2);
}

void cheliangweixiuguanli::on_newAction2()
{
    weixiushijianlineEdit2->setEnabled(true);
    saveAction2->setEnabled(true);
    updateAction2->setEnabled(false);
    deleteAction2->setEnabled(false);

    weixiushijianlineEdit2->clear();
    shuliangLineEdit2->clear();
    danweiComBox2->setCurrentIndex(0);
    shiyongrenComBox2->setCurrentIndex(0);
    beizhulineEdit2->clear();
    beizhulineEdit2->setReadOnly(false);

    weixiushijianlineEdit2->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    weiXiuStateComBox2->setCurrentIndex(0);

    lurushijianlineEdit2->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
}

void cheliangweixiuguanli::on_saveAction2()
{
    if(weixiushijianlineEdit2->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请检查维修时间是否存在"),0,0,0);
        return;
    }
    if(chepaihaocomBox2->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择车号"),0,0,0);
        return;
    }

    if(weiXiuStateComBox2->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入配件名称及规格"),0,0,0);
        return;
    }

    if(shuliangLineEdit2->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入配件数量"),0,0,0);
        return;
    }

    if(danweiComBox2->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入配件单位"),0,0,0);
        return;
    }
    if(shiyongrenComBox2->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入使用人"),0,0,0);
        return;
    }

    QString saveSQL = QString("insert into MaintenanceRecordHaofa (MaintenanceTime,LicenseNumber,Parts,Num,Unit,UserPeople, Remarks,Time,People) values ('%1','%2','%3','%4','%5','%6','%7','%8','%9');")
                .arg(weixiushijianlineEdit2->text(),chepaihaocomBox2->currentText(),weiXiuStateComBox2->currentText(),shuliangLineEdit2->text(),danweiComBox2->currentText(),shiyongrenComBox2->currentText(),beizhulineEdit2->text(),QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"),userName);
    int res = db.sql_exec(saveSQL.toStdString().data());

    if(res == 0){
        on_chaxunBtn2();
        QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
        weixiushijianlineEdit2->clear();
        chepaihaocomBox2->setCurrentIndex(0);
        weiXiuStateComBox2->setCurrentIndex(0);
        shuliangLineEdit2->clear();
        danweiComBox2->setCurrentIndex(0);
        shiyongrenComBox2->setCurrentIndex(0);
        beizhulineEdit2->clear();
        lurushijianlineEdit2->clear();
    }
}

void cheliangweixiuguanli::on_updateAction2()
{
    if(weixiushijianlineEdit2->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请检查维修时间是否存在"),0,0,0);
        return;
    }
    if(chepaihaocomBox2->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择车号"),0,0,0);
        return;
    }

    if(weiXiuStateComBox2->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入配件名称及规格"),0,0,0);
        return;
    }

    if(shuliangLineEdit2->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入配件数量"),0,0,0);
        return;
    }

    if(danweiComBox2->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入配件单位"),0,0,0);
        return;
    }
    if(shiyongrenComBox2->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入使用人"),0,0,0);
        return;
    }
    QString saveSQL = QString("update MaintenanceRecordHaofa set MaintenanceTime = '%1',LicenseNumber= '%2',Parts= '%3',Num= '%4',Unit= '%5',UserPeople= '%6', Remarks= '%7' WHERE Time='%8';")
                .arg(weixiushijianlineEdit2->text(),chepaihaocomBox2->currentText(),weiXiuStateComBox2->currentText(),shuliangLineEdit2->text(),danweiComBox2->currentText(),shiyongrenComBox2->currentText(),beizhulineEdit2->text(),lurushijianlineEdit2->text());
    int res = db.sql_exec(saveSQL.toStdString().data());

    if(res == 0){
        QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
        on_chaxunBtn2();
        weixiushijianlineEdit2->clear();
        chepaihaocomBox2->setCurrentIndex(0);
        weiXiuStateComBox2->setCurrentIndex(0);
        shuliangLineEdit2->clear();
        danweiComBox2->setCurrentIndex(0);
        shiyongrenComBox2->setCurrentIndex(0);
        beizhulineEdit2->clear();
        lurushijianlineEdit2->clear();
    }
}

void cheliangweixiuguanli::on_deleteAction2()
{
    QString deleteSQL = QString("delete from MaintenanceRecordHaofa where Time='%1';").arg(lurushijianlineEdit2->text());
    int res = db.sql_exec(deleteSQL.toStdString().data());

    if(res == 0){
        QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
        on_chaxunBtn2();
        weixiushijianlineEdit2->clear();
        chepaihaocomBox2->setCurrentIndex(0);
        weiXiuStateComBox2->setCurrentIndex(0);
        shuliangLineEdit2->clear();
        danweiComBox2->setCurrentIndex(0);
        shiyongrenComBox2->setCurrentIndex(0);
        beizhulineEdit2->clear();
        lurushijianlineEdit2->clear();
    }
}

void cheliangweixiuguanli::ON_chepai2xingming2()
{
    QString shiyongrenstr = QString("select Driver1 from ConcreteVehicleInformation where LicensePlate = '%1'").arg(chepaihaocomBox2->currentText());
    shiyongrenComBox2->setCurrentText(db.sql_fetchrow_plus(shiyongrenstr.toStdString().data(),0));
}

void cheliangweixiuguanli::ON_xingming2chepai2()
{
    QString chepaistr = QString("select LicensePlate from ConcreteVehicleInformation where Driver1 = '%1'").arg(shiyongrenComBox2->currentText());
    chepaihaoComBox3->setCurrentText(db.sql_fetchrow_plus(chepaistr.toStdString().data(),0));
}

void cheliangweixiuguanli::on_chaxunBtn2()
{  
    connect(Tableview2,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick2()));
    QString shijian2,chehao2;
    if(chehaoCheckBox21->checkState() == 2){
        chehao2 = QString(" and LicenseNumber = '%1'").arg(chehaoComBox21->currentText());
    }

    shijian2 = QString(" and MaintenanceTime between '%1' and '%2'").arg(shijianDateEdit21->date().toString("yyyy-MM-dd"),shijianDateEdit22->date().toString("yyyy-MM-dd"));
    QString searchSQL = QString("select MaintenanceTime 维修时间,LicenseNumber 车号,Parts 更改配件名称及规格,Num 数量,Unit 单位,UserPeople 使用人, Remarks 备注,Time 录入时间,People 录入人 from MaintenanceRecordHaofa where LicenseNumber is not null %1 %2").arg(shijian2,chehao2);
    db.showview(searchSQL.toStdString().data(),Tableview2,&TableviewModel2);
}

void cheliangweixiuguanli::ShowSupplyclick2()
{
    weixiushijianlineEdit2->setEnabled(true);
    newAction2->setEnabled(true);
    saveAction2->setEnabled(false);
    updateAction2->setEnabled(true);
    deleteAction2->setEnabled(true);

    int row = Tableview2->currentIndex().row();

    weixiushijianlineEdit2->setText(TableviewModel2->item(row,0)->text());//维修时间
    chepaihaocomBox2->setCurrentText(TableviewModel2->item(row,1)->text());//车号
    weiXiuStateComBox2->setCurrentText(TableviewModel2->item(row,2)->text());//维修项目
    shuliangLineEdit2->setText(TableviewModel2->item(row,3)->text());//数量
    danweiComBox2->setCurrentText(TableviewModel2->item(row,4)->text());//单位
    shiyongrenComBox2->setCurrentText(TableviewModel2->item(row,5)->text());//使用人
    beizhulineEdit2->setText(TableviewModel2->item(row,6)->text());//备注
    lurushijianlineEdit2->setText(TableviewModel2->item(row,7)->text());//录入时间
}

void cheliangweixiuguanli::ON_Sum2()
{

    int row = Tableview2->currentIndex().row();
    int column = Tableview2->currentIndex().column();
    double sum2 = 0;
    for(int i = 0;i<=row;i++){
        sum2+=TableviewModel2->item(i,column)->text().toDouble();
        zongjiLabe22->setText(QString::number(sum2,10, 4));
    }

}

void cheliangweixiuguanli::createAction22()
{
    newAction22 = new QAction(tr("新增"),this);
    newAction22->setIcon(QIcon(":/image/new.png"));
    connect(newAction22,SIGNAL(triggered()),this,SLOT(on_newAction22()));
    saveAction22 = new QAction(tr("保存"),this);
    saveAction22->setEnabled(false);
    saveAction22->setIcon(QIcon(":/image/save.png"));
    connect(saveAction22,SIGNAL(triggered()),this,SLOT(on_saveAction22()));

    newAction22->setShortcut(Qt::Key_F12);//设置快捷键字母键盘的enter键
    saveAction22->setShortcut(Qt::Key_Return);//设置快捷键字母键盘的enter键

    updateAction22 = new QAction(tr("修改"),this);
    updateAction22->setEnabled(false);
    updateAction22->setIcon(QIcon(":/image/update.png"));
    connect(updateAction22,SIGNAL(triggered()),this,SLOT(on_updateAction22()));

    deleteAction22 = new QAction(tr("删除"),this);
    deleteAction22->setEnabled(false);
    deleteAction22->setIcon(QIcon(":/image/delete.png"));
    connect(deleteAction22,SIGNAL(triggered()),this,SLOT(on_deleteAction22()));
}

void cheliangweixiuguanli::createTool22()
{
    toolBar22 = new QToolBar(this);
    toolBar22->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar22->addAction(newAction22);
    toolBar22->addAction(saveAction22);
    toolBar22->addAction(updateAction22);
    toolBar22->addAction(deleteAction22);
}

void cheliangweixiuguanli::on_newAction22()
{
    saveAction22->setEnabled(true);
    LicenseNumberLineEdit22->clear();
    MaintenanceDateEdit22->setText(QDateTime::currentDateTime().toString("MM-dd"));
    MaintenanceLineEdit22->clear();
    KilometreNumberLineEdit22->clear();
    RepairPersonnelLineEdit22->clear();
    DriverSignatureLineEdit22->clear();
    EntryTimeLineEdit22->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

}

void cheliangweixiuguanli::on_saveAction22()
{

    if(LicenseNumberLineEdit22->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("车号不存在"),0,0,0);
        return;
    }
    if(MaintenanceDateEdit22->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("日期不存在"),0,0,0);
        return;
    }
    if(MaintenanceLineEdit22->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("维修保养明细不存在"),0,0,0);
        return;
    }
    if(KilometreNumberLineEdit22->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("公里数不存在"),0,0,0);
        return;
    }
    if(RepairPersonnelLineEdit22->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("维修人员不存在"),0,0,0);
        return;
    }
    if(DriverSignatureLineEdit22->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("驾驶员签字不存在"),0,0,0);
        return;
    }
    if(EntryTimeLineEdit22->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("录入时间不存在"),0,0,0);
        return;
    }

    QString saveSQL22 = QString("insert into VehicleMaintenanceDailyReport(LicenseNumber,Maintenance,KilometreNumber,RepairPersonnel,DriverSignature,EntryTime,InputPerson)\
                               values ('%1','%2','%3','%4','%5','%6','%7');")
    .arg(LicenseNumberLineEdit22->text(), MaintenanceLineEdit22->text(),KilometreNumberLineEdit22->text(),RepairPersonnelLineEdit22->text(),
        DriverSignatureLineEdit22->text(), EntryTimeLineEdit22->text())
    .arg(userName);

    int res = db.sql_exec(saveSQL22.toStdString().data());

    if(res == 0){
            QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
            on_chaxunBtn22();
            LicenseNumberLineEdit22->clear();
            MaintenanceDateEdit22->clear();
            MaintenanceLineEdit22->clear();
            KilometreNumberLineEdit22->clear();
            RepairPersonnelLineEdit22->clear();
            DriverSignatureLineEdit22->clear();
            EntryTimeLineEdit22->clear();
        }

}

void cheliangweixiuguanli::on_updateAction22()
{
    if(LicenseNumberLineEdit22->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("车号不存在"),0,0,0);
        return;
    }
//    if(MaintenanceDateEdit22->text().isEmpty()){
//        QMessageBox::information(this,tr("提示信息"),tr("日期不存在"),0,0,0);
//        return;
//    }
    if(MaintenanceLineEdit22->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("维修保养明细不存在"),0,0,0);
        return;
    }
    if(KilometreNumberLineEdit22->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("公里数不存在"),0,0,0);
        return;
    }
    if(RepairPersonnelLineEdit22->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("维修人员不存在"),0,0,0);
        return;
    }
    if(DriverSignatureLineEdit22->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("驾驶员签字不存在"),0,0,0);
        return;
    }
    if(EntryTimeLineEdit22->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("录入时间不存在"),0,0,0);
        return;
    }

    QString saveSQL22 = QString("update VehicleMaintenanceDailyReport set LicenseNumber = '%1',Maintenance = '%2',KilometreNumber = '%3',RepairPersonnel = '%4',DriverSignature = '%5',EntryTime = '%6',InputPerson = '%7';")
    .arg(LicenseNumberLineEdit22->text(), MaintenanceLineEdit22->text(),KilometreNumberLineEdit22->text(),RepairPersonnelLineEdit22->text(),
        DriverSignatureLineEdit22->text(), EntryTimeLineEdit22->text())
    .arg(userName);

    int res = db.sql_exec(saveSQL22.toStdString().data());

    if(res == 0){
            QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
            on_chaxunBtn22();
            LicenseNumberLineEdit22->clear();
            MaintenanceDateEdit22->clear();
            MaintenanceLineEdit22->clear();
            KilometreNumberLineEdit22->clear();
            RepairPersonnelLineEdit22->clear();
            DriverSignatureLineEdit22->clear();
            EntryTimeLineEdit22->clear();
        }
}

void cheliangweixiuguanli::on_deleteAction22()
{
    QString saveSQL22 = QString("delete from VehicleMaintenanceDailyReport where EntryTime = '%1'").arg( EntryTimeLineEdit22->text());

    int res = db.sql_exec(saveSQL22.toStdString().data());

    if(res == 0){
            QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
            on_chaxunBtn22();
            LicenseNumberLineEdit22->clear();
            MaintenanceDateEdit22->clear();
            MaintenanceLineEdit22->clear();
            KilometreNumberLineEdit22->clear();
            RepairPersonnelLineEdit22->clear();
            DriverSignatureLineEdit22->clear();
            EntryTimeLineEdit22->clear();
        }
}

void cheliangweixiuguanli::ShowSupplyclick22()
{
    newAction22->setEnabled(true);
    saveAction22->setEnabled(false);
    updateAction22->setEnabled(true);
    deleteAction22->setEnabled(true);

    int row = Tableview22->currentIndex().row();

    LicenseNumberLineEdit22->setText(TableviewModel22->item(row,0)->text());
    MaintenanceLineEdit22->setText(TableviewModel22->item(row,1)->text());
    KilometreNumberLineEdit22->setText(TableviewModel22->item(row,2)->text());
    RepairPersonnelLineEdit22->setText(TableviewModel22->item(row,3)->text());
    DriverSignatureLineEdit22->setText(TableviewModel22->item(row,4)->text());
    EntryTimeLineEdit22->setText(TableviewModel22->item(row,5)->text());


}

void cheliangweixiuguanli::on_chaxunBtn22()
{
    QString searchSQL22 = QString("select LicenseNumber 车号,Maintenance 维修保养明细,KilometreNumber 公里数,RepairPersonnel 维修人员,DriverSignature 驾驶员签字,EntryTime 录入时间,InputPerson 录入人 from VehicleMaintenanceDailyReport");

    db.showview(searchSQL22.toStdString().data(),Tableview22,&TableviewModel22);
}

void cheliangweixiuguanli::createAction3()
{
    newAction3 = new QAction(tr("新增"),this);
    newAction3->setIcon(QIcon(":/image/new.png"));
    connect(newAction3,SIGNAL(triggered()),this,SLOT(on_newAction3()));
    saveAction3 = new QAction(tr("保存"),this);
    saveAction3->setEnabled(false);
    saveAction3->setIcon(QIcon(":/image/save.png"));
    connect(saveAction3,SIGNAL(triggered()),this,SLOT(on_saveAction3()));

    newAction3->setShortcut(Qt::Key_F12);//设置快捷键字母键盘的enter键
    saveAction3->setShortcut(Qt::Key_Return);//设置快捷键字母键盘的enter键

    updateAction3 = new QAction(tr("修改"),this);
    updateAction3->setEnabled(false);
    updateAction3->setIcon(QIcon(":/image/update.png"));
    connect(updateAction3,SIGNAL(triggered()),this,SLOT(on_updateAction3()));

    deleteAction3 = new QAction(tr("删除"),this);
    deleteAction3->setEnabled(false);
    deleteAction3->setIcon(QIcon(":/image/delete.png"));
    connect(deleteAction3,SIGNAL(triggered()),this,SLOT(on_deleteAction3()));
}

void cheliangweixiuguanli::createTool3()
{
    toolBar3 = new QToolBar(this);
    toolBar3->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar3->addAction(newAction3);
    toolBar3->addAction(saveAction3);
    toolBar3->addAction(updateAction3);
    toolBar3->addAction(deleteAction3);
}

void cheliangweixiuguanli::on_toExcell3()
{
    view2Excel->Table2ExcelByHtml(Tableview3,"加油明细表");
}

void cheliangweixiuguanli::on_newAction3()
{
    saveAction3->setEnabled(true);
    updateAction3->setEnabled(false);
    deleteAction3->setEnabled(false);

    zhandianComBox3->setCurrentIndex(2);
    jiayoufangshiComBox3->setCurrentIndex(2);
    riqiLineEdit3->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    chepaihaoComBox3->setCurrentIndex(0);
    jiayoushijianLineEdit3->setText(QDateTime::currentDateTime().toString("hh:mm"));
    jiayouliangLineEdit3->clear();
    xingmingComBox3->setCurrentIndex(0);
    jiayourenComBox3->setCurrentIndex(0);
    gonglishuLineEdit3->clear();
    beizhuLineEdit3->clear();
    lurushijianLineEdit3->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    lururenLineEdit3->setText(userName);
}

void cheliangweixiuguanli::on_saveAction3()
{

    if(zhandianComBox3->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择东/西站"),0,0,0);
        return;
    }
    if(jiayoufangshiComBox3->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择加油方式"),0,0,0);
        return;
    }

    if(riqiLineEdit3->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请检查日期是否存在"),0,0,0);
        return;
    }

    if(chepaihaoComBox3->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入车牌号"),0,0,0);
        return;
    }

    if(jiayoushijianLineEdit3->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入时间"),0,0,0);
        return;
    }

    if(jiayouliangLineEdit3->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入加油量"),0,0,0);
        return;
    }
    if(xingmingComBox3->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入姓名"),0,0,0);
        return;
    }

    QString saveSQL3 = QString("insert into RefuelingList(site,OilDate,LicenseNumber,RefuelingTime,FuelQuantity,FullName,Tanker,KilometreNumber,Remarks,InputPerson,EntryTime,RefuelingMethod)\
                               values ('%1','%2','%3','%4','%5','%6','%7','%8','%9','%10','%11','%12');")
    .arg(zhandianComBox3->currentText(),riqiLineEdit3->text(),chepaihaoComBox3->currentText(),jiayoushijianLineEdit3->text(),jiayouliangLineEdit3->text())
    .arg(xingmingComBox3->currentText(),jiayourenComBox3->currentText(),gonglishuLineEdit3->text(),beizhuLineEdit3->text(),userName,lurushijianLineEdit3->text(),jiayoufangshiComBox3->currentText());

    int res = db.sql_exec(saveSQL3.toStdString().data());

    if(res == 0){
            QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
            on_chaxunBtn3();
            zhandianComBox3->setCurrentIndex(0);
            jiayoufangshiComBox3->setCurrentIndex(0);
            riqiLineEdit3->clear();
            chepaihaoComBox3->setCurrentIndex(0);
            jiayoushijianLineEdit3->clear();
            jiayouliangLineEdit3->clear();
            xingmingComBox3->setCurrentIndex(0);
            jiayourenComBox3->setCurrentIndex(0);
            gonglishuLineEdit3->clear();
            beizhuLineEdit3->clear();
            lurushijianLineEdit3->clear();
            lururenLineEdit3->clear();
        }

}

void cheliangweixiuguanli::on_updateAction3()
{
    if(zhandianComBox3->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择东/西站"),0,0,0);
        return;
    }
    if(jiayoufangshiComBox3->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择加油方式"),0,0,0);
        return;
    }

    if(riqiLineEdit3->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请检查日期是否存在"),0,0,0);
        return;
    }

    if(chepaihaoComBox3->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入车牌号"),0,0,0);
        return;
    }

    if(jiayoushijianLineEdit3->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入时间"),0,0,0);
        return;
    }

    if(jiayouliangLineEdit3->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入加油量"),0,0,0);
        return;
    }
    if(xingmingComBox3->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入姓名"),0,0,0);
        return;
    }

    QString saveSQL3 = QString("update RefuelingList set site = '%1',OilDate = '%2',LicenseNumber = '%3',RefuelingTime = '%4',FuelQuantity = '%5',FullName = '%6',Tanker = '%7',KilometreNumber = '%8',Remarks = '%9',InputPerson = '%10',EntryTime = '%11',RefuelingMethod = '%12' where EntryTime = '%13'")
            .arg(zhandianComBox3->currentText(),riqiLineEdit3->text(),chepaihaoComBox3->currentText(),jiayoushijianLineEdit3->text(),jiayouliangLineEdit3->text())
            .arg(xingmingComBox3->currentText(),jiayourenComBox3->currentText(),gonglishuLineEdit3->text(),beizhuLineEdit3->text(),userName,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"),jiayoufangshiComBox3->currentText(),lurushijianLineEdit3->text());

    int res = db.sql_exec(saveSQL3.toStdString().data());

    if(res == 0){
            QMessageBox::information(this,tr("提示信息"),tr("修改成功"),0,0,0);
            on_chaxunBtn3();
            zhandianComBox3->setCurrentIndex(0);
            jiayoufangshiComBox3->setCurrentIndex(0);
            riqiLineEdit3->clear();
            chepaihaoComBox3->setCurrentIndex(0);
            jiayoushijianLineEdit3->clear();
            jiayouliangLineEdit3->clear();
            xingmingComBox3->setCurrentIndex(0);
            jiayourenComBox3->setCurrentIndex(0);
            gonglishuLineEdit3->clear();
            beizhuLineEdit3->clear();
            lurushijianLineEdit3->clear();
            lururenLineEdit3->clear();
        }

}

void cheliangweixiuguanli::on_deleteAction3()
{
    QString deleteSQL = QString("delete from RefuelingList where EntryTime='%1';").arg(lurushijianLineEdit3->text());
    int res = db.sql_exec(deleteSQL.toStdString().data());

    if(res == 0){
        QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
        on_chaxunBtn3();
        zhandianComBox3->setCurrentIndex(0);
        jiayoufangshiComBox3->setCurrentIndex(0);
        riqiLineEdit3->clear();
        chepaihaoComBox3->setCurrentIndex(0);
        jiayoushijianLineEdit3->clear();
        jiayouliangLineEdit3->clear();
        xingmingComBox3->setCurrentIndex(0);
        jiayourenComBox3->setCurrentIndex(0);
        gonglishuLineEdit3->clear();
        beizhuLineEdit3->clear();
        lurushijianLineEdit3->clear();
        lururenLineEdit3->clear();
    }
}

void cheliangweixiuguanli::ON_chepai2xingming3()
{
    QString xingmingstr = QString("select Driver1 from ConcreteVehicleInformation where LicensePlate = '%1'").arg(chepaihaoComBox3->currentText());
    xingmingComBox3->setCurrentText(db.sql_fetchrow_plus(xingmingstr.toStdString().data(),0));
}

void cheliangweixiuguanli::ON_xingming2chepai3()
{
    QString chepaistr = QString("select LicensePlate from ConcreteVehicleInformation where Driver1 = '%1'").arg(xingmingComBox3->currentText());
    chepaihaoComBox3->setCurrentText(db.sql_fetchrow_plus(chepaistr.toStdString().data(),0));
}

void cheliangweixiuguanli::ON_Sum3()
{
    int row = Tableview3->currentIndex().row();
    int column = Tableview3->currentIndex().column();
    double sum3 = 0;
    for(int i = 0;i<=row;i++){
        sum3+=TableviewModel3->item(i,column)->text().toDouble();
        zongjiLabe32->setText(QString::number(sum3,10, 4));
    }
}

void cheliangweixiuguanli::on_chaxunBtn3()
{
    QString shijianStr3,zhandianStr3,jiayoufangshiStr3,chehaoStr32;
    shijianStr3 = QString(" and OilDate between '%1' and '%2'").arg(shijianDateEdit31->date().toString("yyyy-MM-dd"),shijianDateEdit32->date().toString("yyyy-MM-dd"));

    if(xuanzezhandianCheckBox->checkState() == 2){
        zhandianStr3 = QString(" and site = '%1'").arg(zhandianComBox32->currentText());
    }
    if(jiayoufangshiCheckBox->checkState() == 2){
        jiayoufangshiStr3 = QString(" and RefuelingMethod = '%1'").arg(jiayoufangshiComBox32->currentText());
    }
    if(chehaoCheckBox32->checkState() == 2){
        chehaoStr32 = QString(" and LicenseNumber = '%1'").arg(chehaoComBox32->currentText());
    }
    QString searchSQL3 = QString("SELECT site 站点,OilDate 日期,LicenseNumber 车号,RefuelingTime 时间,FuelQuantity 加油量（公升）,FullName 姓名,Tanker 加油人,KilometreNumber 公里数, Remarks 备注,InputPerson 录入人,EntryTime 录入时间,RefuelingMethod 加油方式 FROM RefuelingList where LicenseNumber is not null %1%2%3%4 order by OilDate,site").arg(shijianStr3,zhandianStr3,jiayoufangshiStr3,chehaoStr32);

    db.showview(searchSQL3.toStdString().data(),Tableview3,&TableviewModel3);
}

void cheliangweixiuguanli::on_huizongBtn3()
{
    QString shijianStr3,zhandianStr3,jiayoufangshiStr3,chehaoStr32;
    shijianStr3 = QString(" and OilDate between '%1' and '%2'").arg(shijianDateEdit31->date().toString("yyyy-MM-dd"),shijianDateEdit32->date().toString("yyyy-MM-dd"));

    if(xuanzezhandianCheckBox->checkState() == 2){
        zhandianStr3 = QString(" and site = '%1'").arg(zhandianComBox32->currentText());
    }
    if(jiayoufangshiCheckBox->checkState() == 2){
        jiayoufangshiStr3 = QString(" and RefuelingMethod = '%1'").arg(jiayoufangshiComBox32->currentText());
    }
    if(chehaoCheckBox32->checkState() == 2){
        chehaoStr32 = QString(" and LicenseNumber = '%1'").arg(chehaoComBox32->currentText());
    }
    QString searchSQL3 = QString("SELECT FullName 姓名,LicenseNumber 车号,SUM(FuelQuantity) 加油量（公升）, Remarks 备注 FROM RefuelingList where LicenseNumber is not null %1%2%3%4 GROUP BY LicenseNumber order by OilDate,site").arg(shijianStr3,zhandianStr3,jiayoufangshiStr3,chehaoStr32);
//    qDebug()<<searchSQL3;
    db.showview(searchSQL3.toStdString().data(),Tableview3,&TableviewModel3);
}

void cheliangweixiuguanli::ShowSupplyclick3()
{
    newAction3->setEnabled(true);
    saveAction3->setEnabled(false);
    updateAction3->setEnabled(true);
    deleteAction3->setEnabled(true);

    int row = Tableview3->currentIndex().row();

    zhandianComBox3->setCurrentText(TableviewModel3->item(row,0)->text());
    riqiLineEdit3->setText(TableviewModel3->item(row,1)->text());
    chepaihaoComBox3->setCurrentText(TableviewModel3->item(row,2)->text());
    jiayoushijianLineEdit3->setText(TableviewModel3->item(row,3)->text());
    jiayouliangLineEdit3->setText(TableviewModel3->item(row,4)->text());
    xingmingComBox3->setCurrentText(TableviewModel3->item(row,5)->text());
    jiayourenComBox3->setCurrentText(TableviewModel3->item(row,6)->text());
    gonglishuLineEdit3->setText(TableviewModel3->item(row,7)->text());
    beizhuLineEdit3->setText(TableviewModel3->item(row,8)->text());
    lurushijianLineEdit3->setText(TableviewModel3->item(row,10)->text());
    lururenLineEdit3->setText(TableviewModel3->item(row,9)->text());
    jiayoufangshiComBox3->setCurrentText(TableviewModel3->item(row,11)->text());
}

void cheliangweixiuguanli::createAction4()
{
    updateAction4 = new QAction(tr("修改"),this);
    updateAction4->setEnabled(false);
    updateAction4->setIcon(QIcon(":/image/update.png"));
    connect(updateAction4,SIGNAL(triggered()),this,SLOT(on_updateAction4()));
}

void cheliangweixiuguanli::createTool4()
{
    toolBar4 = new QToolBar(this);
    toolBar4->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar4->addAction(updateAction4);

}

void cheliangweixiuguanli::on_updateAction4()
{

    if(lichengLineEdit4->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入里程数"),0,0,0);
        return;
    }


    QString saveSQL4 = QString("update ProductionNotice set Mileage = '%1',PlantName = '%5' where mid(OutboundTime,1,10) = '%2' and DeliveryVehicle = '%3' and Engineering = '%4'")
            .arg(lichengLineEdit4->text(),shijianLineEdit4->text(),chehaoLineEdit4->text(),daodagongdiLineEdit4->text(),beizhuLineEdit4->text());

    qDebug()<<saveSQL4;
    int res1 = 0;

    if(xiugaishijianLineEdit4->text().isEmpty()){
        xiugaishijianLineEdit4->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    }
    if(!shengliaobujineshuLineEdit4->text().isEmpty() || !raoxiubugonglishuLineEdit4->text().isEmpty()){
        QString saveSQL42 = QString("replace into DrivingRecordTable (DrivingDate,LicenseNumber,FullName,ArriveAtTheSite,AmountOfRemnantGold,MendingTheNumberOfKilometers,Time) values('%1','%2','%3','%4','%5','%6','%7')")
                .arg(shijianLineEdit4->text(),chehaoLineEdit4->text(),xingmingLineEdit4->text(),daodagongdiLineEdit4->text(),shengliaobujineshuLineEdit4->text(),raoxiubugonglishuLineEdit4->text(),xiugaishijianLineEdit4->text());
        qDebug()<<saveSQL42;
        res1 = db.sql_exec(saveSQL42.toStdString().data());
    }

    int res = db.sql_exec(saveSQL4.toStdString().data());

    if(res == 0 && res1 == 0){
            QMessageBox::information(this,tr("提示信息"),tr("修改成功"),0,0,0);
            on_chaxunBtn4();

            updateAction4->setEnabled(false);

            shijianLineEdit4->clear();
            chehaoLineEdit4->clear();
            xingmingLineEdit4->clear();
            daodagongdiLineEdit4->clear();
            checiLineEdit4->clear();
            diaoLineEdit4->clear();
            shengliaobujineshuLineEdit4->clear();
            raoxiubugonglishuLineEdit4->clear();
            beizhuLineEdit4->clear();
            lichengLineEdit4->clear();
            zonglichengLineEdit4->clear();
            xiugaishijianLineEdit4->clear();
        }

}

void cheliangweixiuguanli::on_toExcell4()
{
    view2Excel->Table2ExcelByHtml(Tableview4,"行车记录表");
}

void cheliangweixiuguanli::on_chaxunBtn4()
{
//    connect(Tableview4,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick4()));
    QString shijian4,jiashiyuan4,jiashiyuansiji4;

    shijian4 = QString(" and OutboundTime between '%1' and '%2'").arg(shijianDateEdit41->date().toString("yyyy-MM-dd 00:00:00"),shijianDateEdit42->date().toString("yyyy-MM-dd 23:59:59"));
    if(jiashiyuanCheckBox4->checkState() == 2){
        jiashiyuan4 = QString(" and DeliveryVehicle = '%1'").arg(jiashiyuanComBox4->currentText());
    }
    if(jiashiyuanSiJiCheckBox4->checkState() == 2){
        jiashiyuansiji4 = QString(" and Driver = '%1'").arg(jiashiyuanSiJiComBox4->currentText());
    }
    QString searchSQL = QString("select mid(OutboundTime,1,10) 日期,DeliveryVehicle 车号,Driver 姓名,Engineering 到达工地,Customer 客户名称,1 车次,ReceiptVolume 方量,PlantName 备注,ProductionNotice.Mileage 里程, \
                                DrivingRecordTable.Time 修改时间 from ProductionNotice LEFT JOIN (\
                                                                 SELECT\
                                                                     *\
                                                                 FROM\
                                                                     ConcreteVehicleInformation\
                                                                 GROUP BY\
                                                                     Vehiclenumber\
                                                             ) D ON D.Vehiclenumber = DeliveryVehicle LEFT JOIN DrivingRecordTable on mid(OutboundTime,1,10)=DrivingRecordTable.DrivingDate AND \
                                DeliveryVehicle = DrivingRecordTable.LicenseNumber AND Driver = DrivingRecordTable.FullName AND Engineering = DrivingRecordTable.ArriveAtTheSite \
                                WHERE DeliveryVehicle is not null AND D.VehicleType = '租用车辆' %1%2%3 ").arg(shijian4,jiashiyuan4,jiashiyuansiji4);
    qDebug()<<searchSQL;
    db.showview(searchSQL.toStdString().data(),Tableview4,&TableviewModel4);
    int rowCount = TableviewModel4->rowCount();
    double SUMVolume = 0;//总方量
    double SUMPrice = 0;//总金额
    double signalPrice1 = 0;//单价1
    double signalPrice2 = 0;//单价2
    for(int row = 0;row < rowCount;row ++){


        double str=TableviewModel4->data(TableviewModel4->index(row,6)).toDouble();//第row行第6列的内容：方量
        double yunju =TableviewModel4->data(TableviewModel4->index(row,8)).toDouble();//运距

         //运费1
        if(yunju <= 15){//当运距小于等于15
            signalPrice1 = 26.2;
        }else{
            signalPrice1 = (yunju-15)*2 + 26.2;
        }
        //运费2
        if(yunju <= 15){
            signalPrice2 = 23;
        }else{
            signalPrice2 = (yunju-15)*1.4 + 23;
        }

        SUMVolume = SUMVolume + str;
        if(str == 0){//签收方量==0时
            continue;
        }
        if(SUMVolume <= 1000)
        {
            SUMPrice += str * signalPrice1;
        }else{
            if(SUMVolume - 1000 <= str){

                SUMPrice += (SUMVolume-1000 ) * signalPrice2 + (str -(SUMVolume -1000))* signalPrice1 ;
            }else{

                SUMPrice += str * signalPrice2;
            }
        }
    }
    qDebug()<<SUMPrice;
//    zongjineLabe42->setText(SUMPrice);
    zongjineLabe42->setText(QString::number(SUMPrice));
}

void cheliangweixiuguanli::on_yunjuchaxunBtn4()
{
//    disconnect(Tableview4,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick4()));
    QString shijian4,jiashiyuan4,jiashiyuansiji4;
    shijian4 = QString(" and OutboundTime between '%1' and '%2'").arg(shijianDateEdit41->date().toString("yyyy-MM-dd 00:00:00"),shijianDateEdit42->date().toString("yyyy-MM-dd 23:59:59"));
    if(jiashiyuanCheckBox4->checkState() == 2){
        jiashiyuan4 = QString(" and DeliveryVehicle = '%1'").arg(jiashiyuanComBox4->currentText());
    }
    if(jiashiyuanSiJiCheckBox4->checkState() == 2){
        jiashiyuansiji4 = QString(" and Driver = '%1'").arg(jiashiyuanSiJiComBox4->currentText());
    }
    QString searchSQL = QString("select Engineering 到达工地,COUNT(1) 车次,Mileage 运距, SUM(Mileage) 考核里程,PlantName 备注 from ProductionNotice where ReceiptVolume != '0' and Engineering is not null %1%2%3 GROUP BY Engineering").arg(shijian4,jiashiyuan4,jiashiyuansiji4);
    db.showview(searchSQL.toStdString().data(),Tableview4,&TableviewModel4);
}

void cheliangweixiuguanli::ShowSupplyclick4()
{
    updateAction4->setEnabled(true);

    int row = Tableview4->currentIndex().row();
    shijianLineEdit4->setText(TableviewModel4->item(row,0)->text());
    chehaoLineEdit4->setText(TableviewModel4->item(row,1)->text());
    xingmingLineEdit4->setText(TableviewModel4->item(row,2)->text());
    daodagongdiLineEdit4->setText(TableviewModel4->item(row,3)->text());
    checiLineEdit4->setText(TableviewModel4->item(row,5)->text());
    diaoLineEdit4->setText(TableviewModel4->item(row,6)->text());
    shengliaobujineshuLineEdit4->setText(TableviewModel4->item(row,7)->text());
    raoxiubugonglishuLineEdit4->setText(TableviewModel4->item(row,8)->text());
    beizhuLineEdit4->setText(TableviewModel4->item(row,9)->text());
    lichengLineEdit4->setText(TableviewModel4->item(row,10)->text());
    zonglichengLineEdit4->setText(TableviewModel4->item(row,11)->text());
    xiugaishijianLineEdit4->setText(TableviewModel4->item(row,12)->text());
}

void cheliangweixiuguanli::on_zonglicheng4()
{
    zonglichengLineEdit4->setText(QString::number(checiLineEdit4->text().toDouble() * lichengLineEdit4->text().toDouble()));
}

void cheliangweixiuguanli::ON_Sum4()
{
    int row = Tableview4->currentIndex().row();
    int column = Tableview4->currentIndex().column();
    double sum4 = 0;
    for(int i = 0;i<=row;i++){
        sum4+=TableviewModel4->item(i,column)->text().toDouble();
        zongjiLabe42->setText(QString::number(sum4,10, 4));
    }
}

void cheliangweixiuguanli::createAction5()
{
    updateAction5 = new QAction(tr("修改"),this);
    updateAction5->setEnabled(false);
    updateAction5->setIcon(QIcon(":/image/update.png"));
    connect(updateAction5,SIGNAL(triggered()),this,SLOT(on_updateAction5()));
}

void cheliangweixiuguanli::createTool5()
{
    toolBar5 = new QToolBar(this);
    toolBar5->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar5->addAction(updateAction5);
}

void cheliangweixiuguanli::on_toExcell5()
{
    view2Excel->Table2ExcelByHtml(Tableview5,"驾驶员考核总表");
}

void cheliangweixiuguanli::on_updateAction5()
{

}

void cheliangweixiuguanli::on_chaxunBtn5()
{

    QString shijian5,jiashiyuan5,jiashiyuansiji5;

    shijian5 = QString(" and OutboundTime between '%1' and '%2' and RefuelingList.OilDate between '%1' and '%2' and IF(DrivingRecordTable.DrivingDate is null,OutboundTime,DrivingRecordTable.DrivingDate) between '%1' and '%2' ").arg(shijianDateEdit51->date().toString("yyyy-MM-dd"),shijianDateEdit52->date().toString("yyyy-MM-dd"));

    if(jiashiyuanCheckBox5->checkState() == 2){
        jiashiyuan5 = QString(" and DeliveryVehicle = '%1'").arg(jiashiyuanComBox5->currentText());
    }
    if(jiashiyuanSiJiCheckBox5->checkState() == 2){
        jiashiyuansiji5 = QString(" and Driver = '%1'").arg(jiashiyuanSiJiComBox5->currentText());
    }

///    合计金额 = 运输次数 * (大车)45(元)/(小车)41(元) + 吊罐次数 * 9(元) + 补助金额【剩料补金额】
///    工资 = 合计金额 + 奖励【（()45(升)\(大车)50(升) - 耗油量/（(考核运距+调整运距)/100）） * 5()】 + 超级奖励【暂时设为0】
///    ROUND(,2)四舍五入
/******************************************************************************************
自家车

外租车

******************************************************************************************/
/*    ///2018-04-11
    //大车运费 35 小车运费 26 大车 50 小车 45
    QStringList cf = db.CreatStrList("SELECT *FROM cheliangyunshufeiyongshezhi");
    QString diaoguanjiage = cf.at(0);
    QString dacheyunfei = cf.at(1);
    QString xiaocheyunfei = cf.at(2);
    QString dacheyouhao = cf.at(3);
    QString xiaocheyouhao = cf.at(4);
    QString jianglijine = cf.at(5);
    QString chengfajine = cf.at(6);
    //大车运费 35 小车运费 26 大车 50 小车 45
     QString searchSQL5 = QString("SELECT DeliveryVehicle 车号,\
        Driver 驾驶员, \
        COUNT(1) 运输次数,       \
        SUM(CASE WHEN PouringMethod='吊罐' THEN 1 ELSE 0 END) 吊罐次数,\
        C.BUJINE 补助金额,\
        ROUND(COUNT(1) * (CASE WHEN D.VehicleXingHao = '16方' THEN '%5' ELSE '%6' END) + \
        SUM(CASE WHEN PouringMethod='吊罐' THEN 1 ELSE 0 END) * '%4' + IF(C.BUJINE IS NULL,0,C.BUJINE),2) 合计金额,  \
        SUM(A.Mileage) 考核里程,\
        C.TIAOZHENGLICHENG 调整里程,\
        B.JIAYOULIANG 实际耗油,\
        ROUND(B.JIAYOULIANG / ((SUM(A.Mileage) + IF(C.TIAOZHENGLICHENG is null,0,C.TIAOZHENGLICHENG)) /100),2) 百公里耗油,\
        ROUND(((CASE WHEN D.VehicleXingHao = '16方' THEN '%7' ELSE '%8' END)-\
        (B.JIAYOULIANG) / ((SUM(A.Mileage) + IF(C.TIAOZHENGLICHENG is null,0,C.TIAOZHENGLICHENG)) / 100))*\
        ((SUM(A.Mileage) + IF(C.TIAOZHENGLICHENG is null,0,C.TIAOZHENGLICHENG)) / 100),2) 节油数,\
        ROUND(IF(((CASE WHEN D.VehicleXingHao = '16方' THEN '%7' ELSE '%8' END) - \
        (B.JIAYOULIANG) / ((SUM(A.Mileage) +IF (C.TIAOZHENGLICHENG IS NULL,0,C.TIAOZHENGLICHENG)) / 100)) * \
        ((SUM(A.Mileage) + IF (C.TIAOZHENGLICHENG IS NULL,0,C.TIAOZHENGLICHENG)) / 100)>0,\
        ((CASE WHEN D.VehicleXingHao = '16方' THEN '%7' ELSE '%8' END) - (B.JIAYOULIANG) / ((SUM(A.Mileage) +\
        IF (C.TIAOZHENGLICHENG IS NULL,0,C.TIAOZHENGLICHENG)) / 100)) * ((SUM(A.Mileage) + \
        IF (C.TIAOZHENGLICHENG IS NULL,0,C.TIAOZHENGLICHENG)) / 100)*'%9',\
        ((CASE WHEN D.VehicleXingHao = '16方' THEN '%7' ELSE '%8' END) - (B.JIAYOULIANG) / ((SUM(A.Mileage) +\
        IF (C.TIAOZHENGLICHENG IS NULL,0,C.TIAOZHENGLICHENG)) / 100)) * ((SUM(A.Mileage) + \
        IF (C.TIAOZHENGLICHENG IS NULL,0,C.TIAOZHENGLICHENG)) / 100)*'%10'),2) 奖励,  \
        0 超级奖励,\
        ROUND(COUNT(1) * (CASE WHEN D.VehicleXingHao = '16方' THEN '%5' ELSE '%6' END) + \
        SUM(CASE WHEN PouringMethod = '吊罐' THEN 1 ELSE 0 END) * '%4' + IF (C.BUJINE IS NULL, 0, C.BUJINE) + \
        IF(IF(((CASE WHEN D.VehicleXingHao = '16方' THEN '%7' ELSE '%8' END) - (B.JIAYOULIANG) / ((SUM(A.Mileage) +\
        IF (C.TIAOZHENGLICHENG IS NULL,0,C.TIAOZHENGLICHENG)) / 100)) * ((SUM(A.Mileage) + \
        IF (C.TIAOZHENGLICHENG IS NULL,0,C.TIAOZHENGLICHENG)) / 100)>0,\
        ((CASE WHEN D.VehicleXingHao = '16方' THEN '%7' ELSE '%8' END) - (B.JIAYOULIANG) / ((SUM(A.Mileage) +\
        IF (C.TIAOZHENGLICHENG IS NULL,0,C.TIAOZHENGLICHENG)) / 100)) * ((SUM(A.Mileage) + \
        IF (C.TIAOZHENGLICHENG IS NULL,0,C.TIAOZHENGLICHENG)) / 100)*'%9',\
        ((CASE WHEN D.VehicleXingHao = '16方' THEN '%7' ELSE '%8' END) - (B.JIAYOULIANG) / \
        ((SUM(A.Mileage) +IF (C.TIAOZHENGLICHENG IS NULL,0,C.TIAOZHENGLICHENG)) / 100)) * \
        ((SUM(A.Mileage) + IF (C.TIAOZHENGLICHENG IS NULL,0,C.TIAOZHENGLICHENG)) / 100)*'%10') IS NULL,0,\
        IF(((CASE WHEN D.VehicleXingHao = '16方' THEN '%7' ELSE '%8' END) - (B.JIAYOULIANG) / ((SUM(A.Mileage) +\
        IF (C.TIAOZHENGLICHENG IS NULL,0,C.TIAOZHENGLICHENG)) / 100)) * ((SUM(A.Mileage) + \
        IF (C.TIAOZHENGLICHENG IS NULL,0,C.TIAOZHENGLICHENG)) / 100)>0,\
        ((CASE WHEN D.VehicleXingHao = '16方' THEN '%7' ELSE '%8' END) - (B.JIAYOULIANG) / ((SUM(A.Mileage) +\
        IF (C.TIAOZHENGLICHENG IS NULL,0,C.TIAOZHENGLICHENG)) / 100)) * ((SUM(A.Mileage) + \
        IF (C.TIAOZHENGLICHENG IS NULL,0,C.TIAOZHENGLICHENG)) / 100)*'%9',\
        ((CASE WHEN D.VehicleXingHao = '16方' THEN '%7' ELSE '%8' END) - (B.JIAYOULIANG) / ((SUM(A.Mileage) +\
        IF (C.TIAOZHENGLICHENG IS NULL,0,C.TIAOZHENGLICHENG)) / 100)) * ((SUM(A.Mileage) + \
        IF (C.TIAOZHENGLICHENG IS NULL,0,C.TIAOZHENGLICHENG)) / 100)*'%10')) + 0,2) 工资\
        from ProductionNotice A\
        LEFT JOIN (SELECT *,ROUND(SUM(FuelQuantity),2) JIAYOULIANG FROM RefuelingList  \
        WHERE OilDate BETWEEN '%1' AND '%2' GROUP BY FullName) B \
        ON A.Driver = B.FullName \
        LEFT JOIN (SELECT *,ROUND(SUM(MendingTheNumberOfKilometers),2) TIAOZHENGLICHENG ,\
        SUM(AmountOfRemnantGold) BUJINE FROM DrivingRecordTable \
        WHERE DrivingDate BETWEEN '%1' AND '%2' GROUP BY FullName)C \
        ON A.Driver = if(C.FullName is null,Driver,C.FullName) \
        LEFT JOIN ( SELECT * FROM ConcreteVehicleInformation GROUP BY LicensePlate) D \
        ON D.LicensePlate = A.DeliveryVehicle\
        WHERE ReceiptVolume != '0' and MID(OutboundTime,1,10) BETWEEN '%1' AND '%2'%3 \
        GROUP BY Driver ORDER BY DeliveryVehicle")
        .arg(shijianDateEdit51->date().toString("yyyy-MM-dd"),shijianDateEdit52->date().toString("yyyy-MM-dd"),jiashiyuan5).arg(diaoguanjiage,dacheyunfei,xiaocheyunfei,dacheyouhao,xiaocheyouhao).arg(jianglijine,chengfajine);
*/
    QString searchSQL5 = QString("SELECT Engineering 工程地址,\
        DeliveryVehicle 车号,\
        Driver 驾驶员,\
        A.Mileage 公里数,\
        ReceiptVolume 方量,\
        ROUND(\
            1 * (\
                CASE\
                WHEN A.Mileage <= 10 AND D.VehicleType = '自有车辆' THEN\
                    '20'\
                WHEN A.Mileage BETWEEN 10 and 20 AND D.VehicleType = '自有车辆' THEN\
                    '30'\
                WHEN A.Mileage >20 AND D.VehicleType = '自有车辆' THEN\
                    30+(A.Mileage-20)\
                END\
            ) ,2) 合计金额\
    FROM\
        ProductionNotice A\
    LEFT JOIN (\
        SELECT\
            *\
        FROM\
            ConcreteVehicleInformation\
    ) D ON D.Vehiclenumber = A.DeliveryVehicle\
    WHERE\
    MID(OutboundTime, 1, 10) BETWEEN '%1'\
    AND '%2' AND D.VehicleType = '自有车辆' %3 %4\
    ORDER BY\
        DeliveryVehicle")
    .arg(shijianDateEdit51->date().toString("yyyy-MM-dd"),shijianDateEdit52->date().toString("yyyy-MM-dd"),jiashiyuan5,jiashiyuansiji5);
    qDebug()<<searchSQL5;

    db.showview(searchSQL5.toStdString().data(),Tableview5,&TableviewModel5);
}

void cheliangweixiuguanli::ShowSupplyclick5()
{
    updateAction5->setEnabled(true);

    int row = Tableview5->currentIndex().row();
    chehaoLineEdit5->setText(TableviewModel5->item(row,0)->text());
    jiashiyuanLineEdit5->setText(TableviewModel5->item(row,1)->text());
    yunshucishuLineEdit5->setText(TableviewModel5->item(row,2)->text());
    diaoguancishuLineEdit5->setText(TableviewModel5->item(row,3)->text());
    buzhujineLineEdit5->setText(TableviewModel5->item(row,4)->text());
    hejijineshuLineEdit5->setText(TableviewModel5->item(row,5)->text());
    kaohelichengLineEdit5->setText(TableviewModel5->item(row,6)->text());
    tiaozhenglichengLineEdit5->setText(TableviewModel5->item(row,7)->text());
    shijihaoyouLineEdit5->setText(TableviewModel5->item(row,8)->text());
    baigonglihaoyouLineEdit5->setText(TableviewModel5->item(row,9)->text());
    jieyoushuLineEdit5->setText(TableviewModel5->item(row,10)->text());
    jiangliLineEdit5->setText(TableviewModel5->item(row,11)->text());
    chaoejiangliLineEdit5->setText(TableviewModel5->item(row,12)->text());
    gongziLineEdit5->setText(TableviewModel5->item(row,13)->text());
}

void cheliangweixiuguanli::ON_Sum5()
{
    int row = Tableview5->currentIndex().row();
    int column = Tableview5->currentIndex().column();
    double sum5 = 0;
    for(int i = 0;i<=row;i++){
        sum5 += TableviewModel5->item(i,column)->text().toDouble();
        zongjiLabe52->setText(QString::number(sum5,10, 4));
    }
}
