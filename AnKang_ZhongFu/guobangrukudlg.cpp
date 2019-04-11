#include "guobangrukudlg.h"


extern mymysql db;
extern pubfunc pub;
extern QString whetherCheckSend;
extern QString userName;
extern myTCPsocket *sockClient;

guobangrukuDlg::guobangrukuDlg(QWidget *parent) :
    QDialog(parent)
{
    tabWidget = new QTabWidget(this);
    caigourukudan = new QWidget(this);
    rukudanchaxun = new QWidget(this);
    guancheguobang = new QWidget(this);
    guancheguobangjilv = new QWidget(this);
    dibangcanshushezhi = new QWidget(this);

    library = new QLibrary("MyReportDll");

    creatTabPage1();
    creatTabPage2();
    creatTabPage3();
    creatTabPage4();
    creatTabPage5();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tabWidget);
}

guobangrukuDlg::~guobangrukuDlg()
{
    delete model;
    delete twomodel;
    delete threemodel;
    delete fourmodel;
}

void guobangrukuDlg::refresh()
{
    db.showview(SQL1,view,&model);//显示表格
    setModelStyle(model);
    db.showview(SQL3,threeview,&threemodel);
    setModelStyle3(threemodel);
}

void guobangrukuDlg::keyPressEvent(QKeyEvent *event)
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

void guobangrukuDlg::creatTabPage1()//采购入库单
{
    createAction1();
    createTool1();

    SQL1 = "select StorageList 入库单,Material 原料,SpecificationModel 规格,Position 仓位,Supplier 供应商,\
            LicensePlateNumber 车牌号,GrossWeight 毛重,GrossWeightTime 称毛重时间,Tare 皮重,\
            TareTime 称皮重时间,StorageKG 净重,Buckle 扣重,StorageKG 入库（KG）,StorageCube 入库（方）,\
            DeliveryNote 送货单号,DeliveryMan 送货人,Telephone 电话,Remarks 备注,Storagefactory 入库厂地,\
            ContractNumber  合同编号,PlaceOfOrigin 产地,Time,GBMAN 过磅人 from PurchaseReceipt where WhetherCheck='否';";

    QLabel *recordNoLabel = new QLabel(tr("入库单"),this);
    recordNoLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *MatNameLabel = new QLabel(tr("原料名称"),this);
    MatNameLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *SupplierLabel = new QLabel(tr("供应商"),this);
    SupplierLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *PositionLabel = new QLabel(tr("仓位名称"),this);
    PositionLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *NetWeightLabel = new QLabel(tr("净重"),this);
    NetWeightLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *DeliveryNoLabel = new QLabel(tr("送货单号"),this);
    DeliveryNoLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *RemarksLabel = new QLabel(tr("备注"),this);
    RemarksLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *PlantNameLabel = new QLabel(tr("入库厂地"),this);
    PlantNameLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *SpecificationLabel = new QLabel(tr("规格"),this);
    SpecificationLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *GrossWeightTimeLabel = new QLabel(tr("称毛重时间"),this);
    GrossWeightTimeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *NetWeightTimeLabel = new QLabel(tr("称皮重时间"),this);
    NetWeightTimeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *BuckleLabel = new QLabel(tr("扣重"),this);
    BuckleLabel->setStyleSheet("color:red");
    BuckleLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *LicensePlateLabel = new QLabel(tr("车牌号"),this);
    LicensePlateLabel->setStyleSheet("color:red");
    LicensePlateLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *StorageKGLabel = new QLabel(tr("入库重量"),this);
    StorageKGLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *DeliveryManLabel = new QLabel(tr("送货人"),this);
    DeliveryManLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *StorageCubeLabel = new QLabel(tr("折方"),this);
    StorageCubeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *TelephoneLabel = new QLabel(tr("电话"),this);
    TelephoneLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *WarningLabel = new QLabel(tr("注意：底色为蓝色的记录未称皮重"));
    WarningLabel->setStyleSheet("color:red");

    QFont ft;
    ft.setPixelSize(70);
    QLabel *LCDlabel = new QLabel(tr("KG"),this);
    LCDlabel->setFont(ft);
    LCDlabel->setStyleSheet("color:green");//设置字体颜色为红色

    oneRecordNoLineEdit = new QLineEdit(this);
    oneRecordNoLineEdit->setEnabled(false);
    oneRecordNoLineEdit->setStyleSheet("color:red");
    oneGrossWeightLineEdit = new QLineEdit(this);
    oneGrossWeightLineEdit->setEnabled(true);
    oneGrossWeightLineEdit->setStyleSheet("color:black");
    oneGrossWeightTimeLineEdit = new QLineEdit(this);
    oneGrossWeightTimeLineEdit->setEnabled(true);
    oneGrossWeightTimeLineEdit->setStyleSheet("color:black");
    oneTareWeightLineEdit = new QLineEdit(this);
    oneTareWeightLineEdit->setEnabled(true);
    oneTareWeightLineEdit->setStyleSheet("color:black");
    oneNetWeightTimeLineEdit = new QLineEdit(this);
    oneNetWeightTimeLineEdit->setEnabled(true);
    oneNetWeightTimeLineEdit->setStyleSheet("color:black");
    oneNetWeightLineEdit = new QLineEdit(this);
    oneNetWeightLineEdit->setEnabled(true);
    oneNetWeightLineEdit->setStyleSheet("color:black");
    oneBuckleLineEdit = new QLineEdit(this);
    oneStorageKGLineEdit = new QLineEdit(this);
    oneStorageKGLineEdit->setEnabled(false);
    oneStorageKGLineEdit->setStyleSheet("color:black");
    oneStorageCubeLineEdit = new QLineEdit(this);
//    oneStorageCubeLineEdit->setEnabled(false);
    oneStorageCubeLineEdit->setStyleSheet("color:black");
    oneDeliveryNoLineEdit = new QLineEdit(this);
    oneDeliveryManLineEdit = new QLineEdit(this);
    oneTelephoneLineEdit = new QLineEdit(this);
    oneRemarksLineEdit = new QLineEdit(this);

    oneLicensePlateLineEdit = new MyCompleterLineEdit(oneDeliveryManLineEdit,oneTelephoneLineEdit,this);

    onePlantNameComBox = new QComboBox(this);
    onePlantNameComBox->setStyleSheet("color:black");
    onePlantNameComBox->setEnabled(false);
    const char *fillSQL1 = "select PlantName from FactorySetting;";
    db.sql_fillComboBoxItem(fillSQL1,onePlantNameComBox);
    onePlantNameComBox->setCurrentText(pub.readPlantName());

    oneMatNameComBox = new QComboBox(this);
    oneMatNameComBox->setStyleSheet("color:black");
    oneMatNameComBox->setEnabled(false);
    const char *fillSQL2 = "select MaterialName from PurchaseMaterialList group by MaterialName;";
    db.sql_fillComboBoxItem(fillSQL2,oneMatNameComBox);

    oneSupplierComBox = new QComboBox(this);
    oneSupplierComBox->setStyleSheet("color:black");
    oneSupplierComBox->setEnabled(false);

    onePositionNameComBox = new QComboBox(this);
    onePositionNameComBox->setStyleSheet("color:black");

    onePositionNameComBox->setEnabled(false);

    oneSpecificationComBox = new QComboBox(this);
    oneSpecificationComBox->setStyleSheet("color:black");
    oneSpecificationComBox->setEditable(true);
    oneSpecificationComBox->setEnabled(false);

    oneGrossWeightBtn = new QPushButton(tr("称毛重"),this);
    connect(oneGrossWeightBtn,SIGNAL(clicked()),this,SLOT(on_chengmaozhong()));
    oneTareWeightBtn = new QPushButton(tr("称皮重"),this);
    connect(oneTareWeightBtn,SIGNAL(clicked()),this,SLOT(on_chengpizhong()));
    oneSaveGrossWeightBtn = new QPushButton(tr("保存毛重"),this);
    oneSaveGrossWeightBtn->setHidden(true);
    connect(oneSaveGrossWeightBtn,SIGNAL(clicked()),this,SLOT(on_baocunmaozhong()));//当按下保存毛重按钮时插入一条数据
    oneSaveNetWeightBtn = new QPushButton(tr("保存皮重"),this);
    oneSaveNetWeightBtn->setHidden(true);
    connect(oneSaveNetWeightBtn,SIGNAL(clicked()),this,SLOT(on_baocunpizhong()));

    oneGrossWeightBtn->setEnabled(false);
    oneTareWeightBtn->setEnabled(false);
    oneSaveGrossWeightBtn->setEnabled(false);
    oneSaveNetWeightBtn->setEnabled(false);


    view = new QTableView(this);
    connect(view,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick1()));
    db.showview(SQL1,view,&model);//显示表格
    setModelStyle(model);
    view->setColumnWidth(7,120);
    view->setColumnWidth(9,120);
    view->setColumnHidden(21,true);

    LCDnumber = new QLCDNumber(this);
    LCDnumber->setSegmentStyle(QLCDNumber::Flat);
    QPalette lcdpat = LCDnumber->palette();//调色板
    lcdpat.setColor(QPalette::Normal,QPalette::WindowText,Qt::green);
    LCDnumber->setPalette(lcdpat);//设置当前窗口的调色板
    LCDnumber->setStyleSheet("background-color: black");
    LCDnumber->setDigitCount(6);
    LCDnumber->display(0);

    video = new PlayViedo(this);

    QHBoxLayout *lcdhLayout = new QHBoxLayout;
    lcdhLayout->addWidget(LCDnumber,1);
    lcdhLayout->addWidget(LCDlabel,0);

    connect(oneGrossWeightLineEdit,SIGNAL(textChanged(QString)),this,SLOT(NetWeightDisplay()));
    connect(oneTareWeightLineEdit,SIGNAL(textChanged(QString)),this,SLOT(NetWeightDisplay()));
    connect(oneNetWeightLineEdit,SIGNAL(textChanged(QString)),this,SLOT(StorageQuantityDispaly()));
    connect(oneBuckleLineEdit,SIGNAL(textChanged(QString)),this,SLOT(StorageQuantityDispaly()));
    connect(oneMatNameComBox,SIGNAL(currentTextChanged(QString)),this,SLOT(combo2Correspond()));

    QWidget *BtnWidget = new QWidget(this);
    QHBoxLayout *BtnLayout = new QHBoxLayout;
    BtnLayout->addWidget(oneSaveGrossWeightBtn);
    BtnLayout->addWidget(oneSaveNetWeightBtn);
    BtnLayout->setMargin(0);
    BtnWidget->setLayout(BtnLayout);

    QGridLayout *layout1 = new QGridLayout;
    layout1->addLayout(lcdhLayout,0,0,3,6);

    layout1->addWidget(video,0,6,12,4);

    layout1->addWidget(recordNoLabel,3,0);
    layout1->addWidget(oneRecordNoLineEdit,3,1);
    layout1->addWidget(PlantNameLabel,3,2);
    layout1->addWidget(onePlantNameComBox,3,3);
    layout1->addWidget(LicensePlateLabel,3,4);
    layout1->addWidget(oneLicensePlateLineEdit,3,5);

    layout1->addWidget(MatNameLabel,4,0);
    layout1->addWidget(oneMatNameComBox,4,1);
    layout1->addWidget(SpecificationLabel,4,2);
    layout1->addWidget(oneSpecificationComBox,4,3);
    layout1->addWidget(DeliveryNoLabel,4,4);
    layout1->addWidget(oneDeliveryNoLineEdit,4,5);

    layout1->addWidget(SupplierLabel,5,0);
    layout1->addWidget(oneSupplierComBox,5,1);
    layout1->addWidget(PositionLabel,5,2);
    layout1->addWidget(onePositionNameComBox,5,3);
    layout1->addWidget(DeliveryManLabel,5,4);
    layout1->addWidget(oneDeliveryManLineEdit,5,5);

    layout1->addWidget(oneGrossWeightBtn,6,0);
    layout1->addWidget(oneGrossWeightLineEdit,6,1);
    layout1->addWidget(GrossWeightTimeLabel,6,2);
    layout1->addWidget(oneGrossWeightTimeLineEdit,6,3);
    layout1->addWidget(TelephoneLabel,6,4);
    layout1->addWidget(oneTelephoneLineEdit,6,5);

    layout1->addWidget(oneTareWeightBtn,7,0);
    layout1->addWidget(oneTareWeightLineEdit,7,1);
    layout1->addWidget(NetWeightTimeLabel,7,2);
    layout1->addWidget(oneNetWeightTimeLineEdit,7,3);
    layout1->addWidget(StorageCubeLabel,7,4);
    layout1->addWidget(oneStorageCubeLineEdit,7,5);

    layout1->addWidget(NetWeightLabel,8,0);
    layout1->addWidget(oneNetWeightLineEdit,8,1);
    layout1->addWidget(BuckleLabel,8,2);
    layout1->addWidget(oneBuckleLineEdit,8,3);
    layout1->addWidget(StorageKGLabel,8,4);
    layout1->addWidget(oneStorageKGLineEdit,8,5);

    layout1->addWidget(RemarksLabel,9,0);
    layout1->addWidget(oneRemarksLineEdit,9,1,1,5);

    layout1->addWidget(BtnWidget,10,1,1,3);
    layout1->addWidget(WarningLabel,11,1,1,2);

    layout1->setColumnStretch(0,0);
    layout1->setColumnStretch(1,1);
    layout1->setColumnStretch(2,0);
    layout1->setColumnStretch(3,1);
    layout1->setColumnStretch(4,0);
    layout1->setColumnStretch(5,1);
    layout1->setColumnStretch(6,1);
    layout1->setColumnStretch(7,1);
    layout1->setColumnStretch(8,1);
    layout1->setColumnStretch(9,1);
    layout1->setSpacing(10);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(toolBar1);
    vlayout->addLayout(layout1);
    vlayout->addWidget(view);

    caigourukudan->setLayout(vlayout);
    tabWidget->addTab(caigourukudan,tr("采购入库单"));
}

void guobangrukuDlg::creatTabPage2()//入库单查询
{
    SQL2 = "select StorageList 入库单,Material 原料,SpecificationModel 规格,Position 仓位,Supplier 供应商,LicensePlateNumber 车牌号,\
            GrossWeight 毛重,GrossWeightTime 称毛重时间,Tare 皮重,TareTime 称皮重时间,StorageKG 净重,Buckle 扣重,StorageKG 入库（KG）,\
            StorageCube 入库（方）,DeliveryNote 送货单号,DeliveryMan 送货人,Telephone 电话,Remarks 备注,Storagefactory 入库厂地,PlaceOfOrigin 产地,\
            ContractNumber 合同编号,GBMAN 过磅人 from PurchaseReceipt limit 0";

    QLabel *twoStorageTimeLabel = new QLabel(tr("入库时间"),this);
    twoStorageTimeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *twoFuHaoLabel = new QLabel(tr("--"),this);
    twoFuHaoLabel->setAlignment(Qt::AlignCenter);
    QLabel *twoStoragePlantNameLabel = new QLabel(tr("入库厂地"),this);
    twoStoragePlantNameLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

    twoMaterialNameCheckBox = new QCheckBox(tr("原料名称"),this);
    twoSupplierCheckBox = new QCheckBox(tr("供应商"),this);

    QLabel *totalTrainLabel = new QLabel(tr("总车数:"),this);
    totalTrainLabelNum = new QLabel(this);

    twoFindBtn = new QPushButton(tr("查询"),this);
    connect(twoFindBtn,SIGNAL(clicked()),this,SLOT(on_twoFindBtn()));


    twodt1 = new QDateEdit(QDate::currentDate(),this);
    twodt1->setCalendarPopup(true);
    twodt2 = new QDateEdit(QDate::currentDate().addDays(+1),this);
    twodt2->setCalendarPopup(true);

    twoPlantNameCombox = new myComboBox(this);
    db.sql_fillComboBoxItem("select PlantName from FactorySetting",twoPlantNameCombox);

    twoMaterialCombox = new myComboBox(this);
    db.sql_fillComboBoxItem("select Material from MaterialSetting",twoMaterialCombox);

    twoSupplierCombox = new myComboBox(this);
    db.sql_fillComboBoxItem("select Name from SupplierFile",twoSupplierCombox);

    twoview = new QTableView(this);
    db.showview(SQL2,twoview,&twomodel);//显示表格
    twoview->setColumnWidth(4,300);
    twoview->setColumnWidth(7,110);
    twoview->setColumnWidth(9,110);
    connect(twoview,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick2()));

    QGridLayout *layout1 = new QGridLayout;
    layout1->addWidget(twoStorageTimeLabel,0,0);
    layout1->addWidget(twodt1,0,1);
    layout1->addWidget(twoFuHaoLabel,0,2);
    layout1->addWidget(twodt2,0,3);
    layout1->addWidget(twoStoragePlantNameLabel,0,4);
    layout1->addWidget(twoPlantNameCombox,0,5);
    layout1->addWidget(twoFindBtn,0,6,2,1,Qt::AlignVCenter);
    layout1->addWidget(twoMaterialNameCheckBox,1,0);
    layout1->addWidget(twoMaterialCombox,1,1);
    layout1->addWidget(twoSupplierCheckBox,1,2);
    layout1->addWidget(twoSupplierCombox,1,3);
    layout1->addWidget(totalTrainLabel,1,4);
    layout1->addWidget(totalTrainLabelNum,1,5);
    layout1->setColumnStretch(0,0);
    layout1->setColumnStretch(1,1);
    layout1->setColumnStretch(2,0);
    layout1->setColumnStretch(3,1);
    layout1->setColumnStretch(4,0);
    layout1->setColumnStretch(5,1);
    layout1->setColumnStretch(6,1);
    layout1->setColumnStretch(7,3);
    layout1->setColumnStretch(8,1);
    layout1->setColumnStretch(9,1);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(layout1);
    vlayout->addWidget(twoview);

    rukudanchaxun->setLayout(vlayout);
    tabWidget->addTab(rukudanchaxun,tr("入库单查询"));

    on_twoFindBtn();
}

void guobangrukuDlg::creatTabPage3()//罐车过磅
{
    createAction3();
    createTool3();

    SQL3 = QString("select RecordNumber  记录编号,LicensePlateNumber 车牌号,Driver 司机,Volume 方量,strengthGrade 强度等级,NetWeight 净重,BulkDensity 容重,GrossWeight 毛重,\
            GrossWeightTime 称毛重时间,Tare 皮重,TareTime 称皮重时间,Customer 客户,engineering 工程,\
            Unit 生产机组,WeighPeople 过磅人,Remarks 备注 from TankWeighing where GrossWeightTime between '%1' and '%2';")
            .arg(QDate::currentDate().toString("yyyy-MM-dd"),QDate::currentDate().addDays(1).toString("yyyy-MM-dd"));

    QLabel *RecordNoLabel = new QLabel(tr("记录编号"),this);
    RecordNoLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *VehicleLabel = new QLabel(tr("车牌号"),this);
    VehicleLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *CustomerNameLabel = new QLabel(tr("客户名称"),this);
    CustomerNameLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *EngineerLabel = new QLabel(tr("工程名称"),this);
    EngineerLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *GrossWeightTimeLabel = new QLabel(tr("称毛重时间"),this);
    GrossWeightTimeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *TareWeightTimeLabel = new QLabel(tr("称皮重时间"),this);
    TareWeightTimeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *NetWeightLabel = new QLabel(tr("净重"),this);
    NetWeightLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *UnitWeightLabel = new QLabel(tr("容重"),this);
    UnitWeightLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *VolumeLabel = new QLabel(tr("折算方量"),this);
    VolumeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *StrengthGradeLabel = new QLabel(tr("强度等级"),this);
    StrengthGradeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *WeightPersonLabel = new QLabel(tr("过磅人"),this);
    WeightPersonLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *RemarksLabel = new QLabel(tr("备注"),this);
    RemarksLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *WeightRecordLabel = new QLabel(tr("过磅记录："),this);
    WeightRecordLabel->setAlignment(Qt::AlignLeft|Qt::AlignBottom);
    QLabel *TareWeightLabel = new QLabel(tr("皮重"),this);
    TareWeightLabel->setAlignment(Qt::AlignRight|Qt::AlignBottom);

    QFont ft;
    ft.setPixelSize(70);
    QLabel *LCDlabel = new QLabel(tr("KG"),this);
    LCDlabel->setFont(ft);
    LCDlabel->setStyleSheet("color:red");//设置字体颜色为红色

    threeManualInPutCheckBox = new QCheckBox(tr("手动录入"),this);

    threeGrossWeightBtn = new QPushButton(tr("称毛重"),this);
    threeGrossWeightBtn->setEnabled(false);
    threeGrossWeightBtn->setStyleSheet("color:black");
    connect(threeGrossWeightBtn,SIGNAL(clicked()),this,SLOT(on_chengmaozhong3()));

    threeSaveGrossWeightBtn = new QPushButton(tr("保存毛重"),this);
    threeSaveGrossWeightBtn->setEnabled(false);
    threeSaveGrossWeightBtn->setStyleSheet("color:black");
    connect(threeSaveGrossWeightBtn,SIGNAL(clicked()),this,SLOT(on_baocunmaozhong3()));

    threeTareWeightBtn = new QPushButton(tr("称皮重"),this);
    threeTareWeightBtn->setHidden(true);
    threeTareWeightBtn->setEnabled(false);
    threeTareWeightBtn->setStyleSheet("color:black");
    connect(threeTareWeightBtn,SIGNAL(clicked()),this,SLOT(on_chengpizhong3()));

    threeSaveTareWeightBtn = new QPushButton(tr("保存皮重"),this);
    threeSaveTareWeightBtn->setEnabled(false);
    threeSaveTareWeightBtn->setHidden(true);
    threeSaveTareWeightBtn->setStyleSheet("color:black");
    connect(threeSaveTareWeightBtn,SIGNAL(clicked()),this,SLOT(on_baocunpizhong3()));

    threeLicensePlateCombox = new myComboBox(this);
    const char *fillSQL1 = "select Vehiclenumber from ConcreteVehicleInformation;";
    db.sql_fillComboBoxItem(fillSQL1,threeLicensePlateCombox);
    connect(threeLicensePlateCombox,SIGNAL(editTextChanged(QString)),this,SLOT(on_threeLicensePlateCombox()));

    threeRecordNoLineEdit = new QLineEdit(this);
    threeRecordNoLineEdit->setEnabled(false);
    threeRecordNoLineEdit->setStyleSheet("color:red");
    threeCustomerNameLineEdit = new QLineEdit(this);
    threeCustomerNameLineEdit->setEnabled(false);
    threeCustomerNameLineEdit->setStyleSheet("color:black");
    threeEngineerLineEdit = new QLineEdit(this);
    threeEngineerLineEdit->setEnabled(false);
    threeEngineerLineEdit->setStyleSheet("color:black");
    threeGrossWeightLineEdit = new QLineEdit(this);
    threeGrossWeightLineEdit->setStyleSheet("color:black");
    threeGrossWeightTimeLineEdit = new QLineEdit(this);
    threeGrossWeightTimeLineEdit->setEnabled(false);
    threeGrossWeightTimeLineEdit->setStyleSheet("color:black");
    threeTareWeightLineEdit = new QLineEdit(this);
    threeTareWeightLineEdit->setEnabled(false);
    threeTareWeightLineEdit->setStyleSheet("color:black");
    threeTareWeightTimeLineEdit = new QLineEdit(this);
    threeTareWeightTimeLineEdit->setEnabled(false);
    threeTareWeightTimeLineEdit->setStyleSheet("color:black");
    threeNetWeightLineEdit = new QLineEdit(this);
    threeNetWeightLineEdit->setEnabled(false);
    threeNetWeightLineEdit->setStyleSheet("color:black");
    threeUnitWeightLineEdit = new QLineEdit(this);
    threeUnitWeightLineEdit->setEnabled(false);
    threeUnitWeightLineEdit->setStyleSheet("color:black");
    threeVolumeLineEdit = new QLineEdit(this);
    threeVolumeLineEdit->setEnabled(false);
    threeVolumeLineEdit->setStyleSheet("color:black");
    threeStrengthGradeLineEdit = new QLineEdit(this);
    threeStrengthGradeLineEdit->setEnabled(false);
    threeStrengthGradeLineEdit->setStyleSheet("color:black");
    threeWeightPersonLineEdit = new QLineEdit(this);
    threeWeightPersonLineEdit->setEnabled(false);
    threeWeightPersonLineEdit->setStyleSheet("color:black");
    threeWeightPersonLineEdit->setText(userName);
    threeRemarksLineEdit = new QLineEdit(this);
    threeRemarksLineEdit->setEnabled(false);
    threeRemarksLineEdit->setStyleSheet("color:black");
    threeDriverLineEdit = new QLineEdit(this);
    threeDriverLineEdit->setFixedWidth(60);
    threeDriverLineEdit->setEnabled(false);
    threeDriverLineEdit->setStyleSheet("color:black");

    threeLCDnumber = new QLCDNumber(this);
    threeLCDnumber->setSegmentStyle(QLCDNumber::Flat);
    QPalette lcdpat = threeLCDnumber->palette();//调色板
    lcdpat.setColor(QPalette::Normal,QPalette::WindowText,Qt::red);
    threeLCDnumber->setPalette(lcdpat);//设置当前窗口的调色板
    threeLCDnumber->setStyleSheet("background-color: black");
    threeLCDnumber->setDigitCount(6);

    threeview = new QTableView(this);
    db.showview(SQL3,threeview,&threemodel);
    setModelStyle3(threemodel);
    connect(threeview,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick3()));
    threeview->setColumnWidth(8,120);
    threeview->setColumnWidth(10,120);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(RecordNoLabel,0,0);
    layout->addWidget(threeRecordNoLineEdit,0,1);
    layout->addWidget(VehicleLabel,0,2);
    layout->addWidget(threeLicensePlateCombox,0,3);
    layout->addWidget(threeDriverLineEdit,0,4);
    layout->addWidget(threeLCDnumber,0,5,4,3);
    layout->addWidget(LCDlabel,0,8,4,1);
    layout->addWidget(CustomerNameLabel,1,0);
    layout->addWidget(threeCustomerNameLineEdit,1,1);
    layout->addWidget(EngineerLabel,1,2);
    layout->addWidget(threeEngineerLineEdit,1,3,1,2);
    layout->addWidget(threeGrossWeightBtn,2,0);
    layout->addWidget(threeGrossWeightLineEdit,2,1);
    layout->addWidget(GrossWeightTimeLabel,2,2);
    layout->addWidget(threeGrossWeightTimeLineEdit,2,3);
    layout->addWidget(threeSaveGrossWeightBtn,2,4);
    layout->addWidget(TareWeightLabel,3,0);
    layout->addWidget(threeTareWeightLineEdit,3,1);
    layout->addWidget(TareWeightTimeLabel,3,2);
    layout->addWidget(threeTareWeightTimeLineEdit,3,3);
    layout->addWidget(threeManualInPutCheckBox,3,4);
    layout->addWidget(NetWeightLabel,4,0);
    layout->addWidget(threeNetWeightLineEdit,4,1);
    layout->addWidget(UnitWeightLabel,4,2);
    layout->addWidget(threeUnitWeightLineEdit,4,3);
    layout->addWidget(VolumeLabel,4,4);
    layout->addWidget(threeVolumeLineEdit,4,5);
    layout->addWidget(StrengthGradeLabel,4,6);
    layout->addWidget(threeStrengthGradeLineEdit,4,7);
    layout->addWidget(WeightPersonLabel,5,0);
    layout->addWidget(threeWeightPersonLineEdit,5,1);
    layout->addWidget(RemarksLabel,5,2);
    layout->addWidget(threeRemarksLineEdit,5,3,1,4);
    layout->setSpacing(10);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(toolBar3);
    vlayout->addLayout(layout);
    vlayout->addSpacing(20);
    vlayout->addWidget(WeightRecordLabel);
    vlayout->addWidget(threeview);

    guancheguobang->setLayout(vlayout);
    tabWidget->addTab(guancheguobang,tr("罐车过磅"));
}

void guobangrukuDlg::creatTabPage4()//罐车过磅记录查询
{
    SQL4 = "select RecordNumber 记录编号,LicensePlateNumber 车牌号,Driver 司机,Volume 方量,strengthGrade 强度等级,NetWeight 净重,BulkDensity 容重,GrossWeight 毛重,\
            GrossWeightTime 称毛重时间,Tare 皮重,TareTime 称皮重时间,Customer 客户,engineering 工程,\
            Unit 生产机组,WeighPeople 过磅人,Remarks 备注 from TankWeighing;";

    QLabel *label1 = new QLabel(tr("过磅时间"),this);
    label1->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label2 = new QLabel(tr("--"),this);
    label2->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

    fourcheckBox = new QCheckBox(tr("车牌号"),this);

    fourchaxun = new QPushButton(tr("查询"),this);
    connect(fourchaxun,SIGNAL(clicked()),this,SLOT(on_fourchaxun()));

    fourdate1 = new QDateEdit(this);
    fourdate1->setDate(QDate::currentDate());
    fourdate1->setCalendarPopup(true);
    fourdate2 = new QDateEdit(this);
    fourdate2->setDate(QDate::currentDate());
    fourdate2->setCalendarPopup(true);

    fourcombo = new QComboBox(this);
    const char *fillSQL = "select LicensePlate from ConcreteVehicleInformation;";
    db.sql_fillComboBoxItem(fillSQL,fourcombo);

    fourview = new QTableView(this);
    //db.showview(SQL4,fourview,&fourmodel);
    connect(fourview,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick4()));
    fourview->setColumnWidth(1,120);
    fourview->setColumnWidth(8,120);
    fourview->setColumnWidth(10,120);

    QGridLayout *layout1 = new QGridLayout;
    layout1->addWidget(label1,0,0);
    layout1->addWidget(fourdate1,0,1);
    layout1->addWidget(label2,0,2);
    layout1->addWidget(fourdate2,0,3);
    layout1->addWidget(fourcheckBox,0,4);
    layout1->addWidget(fourcombo,0,5);
    layout1->addWidget(fourchaxun,0,6);
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
    vlayout->addWidget(fourview);

    guancheguobangjilv->setLayout(vlayout);
    tabWidget->addTab(guancheguobangjilv,tr("罐车过磅记录查询"));

    on_fourchaxun();
}

void guobangrukuDlg::creatTabPage5()//地磅参数设置
{
    QLabel *label2 = new QLabel(tr("通信串口"),this);
    label2->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label3 = new QLabel(tr("波特率"),this);
    label3->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label4 = new QLabel(tr("数据位"),this);
    label4->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label5 = new QLabel(tr("停止位"),this);
    label5->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *DeliveryNoLabel = new QLabel(tr("奇偶校正"),this);
    DeliveryNoLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label7 = new QLabel(tr("起始位"),this);
    label7->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label8 = new QLabel(tr("截取位数"),this);
    label8->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

    QLabel *DVRLabel = new QLabel(tr("刻录机IP"),this);
    DVRLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *IPC1Label = new QLabel(tr("摄像头1通道"),this);
    IPC1Label->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *IPC2Label = new QLabel(tr("摄像头2通道"),this);
    IPC2Label->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *IPC3Label = new QLabel(tr("摄像头3通道"),this);
    IPC3Label->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

    DVRIPLineEdit = new QLineEdit(this);
    IPC1LineEdit = new QLineEdit(pub.read_IPC1(),this);
    IPC2LineEdit = new QLineEdit(pub.read_IPC2(),this);
    IPC3LineEdit = new QLineEdit(pub.read_IPC3(),this);

    DVRIPLineEdit->setText(pub.read_DVR_IP());


    fiveUpdateBtn = new QPushButton(tr("修改"),this);
    connect(fiveUpdateBtn,SIGNAL(clicked()),this,SLOT(on_fiveUpdateBtn()));

    serial = new QSerialPort(this);

    fivecombo1 = new QComboBox(this);
    fivecombo1->setView(new QListView(this));
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())//查找可用的串口
    {
        serial->setPort(info);
        if(serial->open(QIODevice::ReadWrite))
        {
            fivecombo1->addItem(serial->portName());
            serial->close();
        }
    }

    fivecombo1->setCurrentIndex(pub.read_SerialNumber().toInt());

    fivecombo2 = new QComboBox(this);
    fivecombo2->setView(new QListView(this));
    fivecombo2->addItem(tr("1200"));
    fivecombo2->addItem(tr("2400"));
    fivecombo2->addItem(tr("4800"));
    fivecombo2->addItem(tr("9600"));
    fivecombo2->addItem(tr("19200"));
    fivecombo2->setCurrentIndex(pub.read_BaudRate().toInt());

    fivecombo3 = new QComboBox(this);
    fivecombo3->setView(new QListView(this));
    fivecombo3->addItem(tr("5"));
    fivecombo3->addItem(tr("6"));
    fivecombo3->addItem(tr("7"));
    fivecombo3->addItem(tr("8"));
    fivecombo3->setCurrentIndex(pub.read_DataBits().toInt());

    fivecombo4 = new QComboBox(this);
    fivecombo4->setView(new QListView(this));
    fivecombo4->addItem(tr("One"));
    fivecombo4->addItem(tr("OnePointFive"));
    fivecombo4->addItem(tr("Two"));
    fivecombo4->setCurrentIndex(pub.read_StopBit().toInt());

    fivecombo5 = new QComboBox(this);
    fivecombo5->setView(new QListView(this));
    fivecombo5->addItem(tr("None"));
    fivecombo5->addItem(tr("Odd"));
    fivecombo5->addItem(tr("Even"));
    fivecombo5->addItem(tr("Mark"));
    fivecombo5->addItem(tr("Space"));
    fivecombo5->setCurrentIndex(pub.read_ParityCorrection().toInt());

    fivelineEdit6 = new QLineEdit(this);
    fivelineEdit6->setText(pub.read_StartBit());

    fivelineEdit7 = new QLineEdit(this);
    fivelineEdit7->setText(pub.read_InterceptDigit());

    dakaichuankou = new QPushButton(tr("打开串口"),this);
    connect(dakaichuankou,SIGNAL(clicked()),this,SLOT(on_dakaichuankou()));
    guanbichuankou = new QPushButton(tr("关闭串口"),this);
    guanbichuankou->setHidden(true);
    connect(guanbichuankou,SIGNAL(clicked()),this,SLOT(on_guanbichuankou()));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label2,1,0);
    layout->addWidget(label3,2,0);
    layout->addWidget(label4,3,0);
    layout->addWidget(label5,4,0);
    layout->addWidget(DeliveryNoLabel,5,0);
    layout->addWidget(label7,6,0);
    layout->addWidget(label8,6,2);
    layout->addWidget(fivecombo1,1,1,1,3);
    layout->addWidget(fivecombo2,2,1,1,3);
    layout->addWidget(fivecombo3,3,1,1,3);
    layout->addWidget(fivecombo4,4,1,1,3);
    layout->addWidget(fivecombo5,5,1,1,3);
    layout->addWidget(fivelineEdit6,6,1);
    layout->addWidget(fivelineEdit7,6,3);
    layout->addWidget(dakaichuankou,7,1,1,3);
    layout->addWidget(guanbichuankou,7,1,1,3);

    QGridLayout *layout2 = new QGridLayout;
    layout2->addWidget(DVRLabel,0,0);
    layout2->addWidget(DVRIPLineEdit,0,1);
    layout2->addWidget(IPC1Label,1,0);
    layout2->addWidget(IPC1LineEdit,1,1);
    layout2->addWidget(IPC2Label,2,0);
    layout2->addWidget(IPC2LineEdit,2,1);
    layout2->addWidget(IPC3Label,3,0);
    layout2->addWidget(IPC3LineEdit,3,1);
    layout2->addWidget(fiveUpdateBtn,4,1);

    QGroupBox *box = new QGroupBox(this);
    box->setTitle(tr("地磅参数设置后请不要随意改动，后果自负"));
    box->setLayout(layout);
    box->setFixedSize(300,400);

    QGroupBox *box2 = new QGroupBox(this);
    box2->setTitle(tr("监控参数设置后请不要随意改动，后果自负"));
    box2->setLayout(layout2);
    box2->setFixedSize(300,400);


    QHBoxLayout *hlayout = new QHBoxLayout(this);
    hlayout->addWidget(box,Qt::AlignLeft);
    hlayout->addWidget(box2,Qt::AlignLeft);
    hlayout->setAlignment(Qt::AlignTop);
    hlayout->addStretch(10);

    dibangcanshushezhi->setLayout(hlayout);
    tabWidget->addTab(dibangcanshushezhi,tr("地磅参数设置"));

    on_dakaichuankou();
}

void guobangrukuDlg::createAction1()
{
    newAction1 = new QAction(tr("新增"),this);
    newAction1->setIcon(QIcon(":/image/new.png"));
    connect(newAction1,SIGNAL(triggered()),this,SLOT(on_newAction1_plus()));
    updateAction1 = new QAction(tr("修改"),this);
    updateAction1->setEnabled(false);
    updateAction1->setIcon(QIcon(":/image/update.png"));
    connect(updateAction1,SIGNAL(triggered()),this,SLOT(on_updateAction1()));
    deleteAction1 = new QAction(tr("删除"),this);
    deleteAction1->setEnabled(false);
    deleteAction1->setIcon(QIcon(":/image/delete.png"));
    connect(deleteAction1,SIGNAL(triggered()),this,SLOT(on_deleteAction1()));
    checkAction1= new QAction(tr("审核"),this);
    checkAction1->setEnabled(false);
    checkAction1->setIcon(QIcon(":/image/check.png"));
    connect(checkAction1,SIGNAL(triggered()),this,SLOT(on_checkAction1()));
    printAction1 = new QAction(tr("打印"),this);
    printAction1->setEnabled(false);
    printAction1->setIcon(QIcon(":/image/printer.png"));
    connect(printAction1,SIGNAL(triggered()),this,SLOT(on_printAction1()));
}

void guobangrukuDlg::createTool1()
{
    toolBar1 = new QToolBar(this);
    toolBar1->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar1->addAction(newAction1);
    toolBar1->addAction(updateAction1);
    toolBar1->addAction(deleteAction1);
    toolBar1->addAction(checkAction1);
    toolBar1->addAction(printAction1);
}

void guobangrukuDlg::createAction3()
{
    newAction3 = new QAction(tr("发货"),this);
    newAction3->setIcon(QIcon(":/image/new.png"));
    connect(newAction3,SIGNAL(triggered()),this,SLOT(on_newAction3_plus()));
    slAction3 = new QAction(tr("剩料"),this);
    slAction3->setIcon(QIcon(":/image/new.png"));
    connect(slAction3,SIGNAL(triggered()),this,SLOT(on_slAction3()));
    updateAction3 = new QAction(tr("修改"),this);
    updateAction3->setIcon(QIcon(":/image/update.png"));
    connect(updateAction3,SIGNAL(triggered()),this,SLOT(on_updateAction3()));
    deleteAction3 = new QAction(tr("删除"),this);
    deleteAction3->setEnabled(false);
    deleteAction3->setIcon(QIcon(":/image/delete.png"));
    connect(deleteAction3,SIGNAL(triggered()),this,SLOT(on_deleteAction3()));
    printAction3 = new QAction(tr("打印"),this);
    printAction3->setEnabled(false);
    printAction3->setIcon(QIcon(":/image/printer.png"));
    connect(printAction3,SIGNAL(triggered()),this,SLOT(on_printAction3()));
    cancelAction3 = new QAction(tr("剩料作废"),this);
    cancelAction3->setEnabled(false);
    cancelAction3->setIcon(QIcon(":/image/cancel.png"));
    connect(cancelAction3,SIGNAL(triggered()),this,SLOT(on_cancelAction3()));
}

void guobangrukuDlg::createTool3()
{
    toolBar3 = new QToolBar(this);
    toolBar3->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar3->addAction(newAction3);
    toolBar3->addAction(slAction3);
    toolBar3->addAction(updateAction3);
    toolBar3->addAction(printAction3);
    toolBar3->addAction(cancelAction3);
}

void guobangrukuDlg::setModelStyle(QStandardItemModel *model)
{
    int columnCount = model->columnCount();
    int rowCount    = model->rowCount();
    for(int i = 0; i < rowCount; i++){
        for(int j = 0; j < columnCount; j++){
            if(!model->item(i,9) || model->item(i,9)->text().isEmpty()){
                model->item(i,j)->setBackground(QBrush(QColor(100,200,200)));
            }
        }
    }
}

void guobangrukuDlg::setModelStyle3(QStandardItemModel *model)
{
    int columnCount = model->columnCount();
    int rowCount    = model->rowCount();
    for(int i = 0; i < rowCount; i++){
        for(int j = 0; j < columnCount; j++){
            if(!model->item(i,9) || model->item(i,9)->text().isEmpty()){
                model->item(i,j)->setBackground(QBrush(QColor(100,200,200)));
            }
        }
    }
}

void guobangrukuDlg::on_newAction1()
{
    disconnect(oneBuckleLineEdit,SIGNAL(textChanged(QString)),this,SLOT(StorageQuantityDispaly()));
    disconnect(oneNetWeightLineEdit,SIGNAL(textChanged(QString)),this,SLOT(StorageQuantityDispaly()));
    disconnect(oneTareWeightLineEdit,SIGNAL(textChanged(QString)),this,SLOT(NetWeightDisplay()));
    disconnect(oneGrossWeightLineEdit,SIGNAL(textChanged(QString)),this,SLOT(NetWeightDisplay()));
    disconnect(oneMatNameComBox,SIGNAL(currentTextChanged(QString)),this,SLOT(combo2Correspond()));
    updateAction1->setEnabled(false);
    deleteAction1->setEnabled(false);
    checkAction1->setEnabled(false);
    printAction1->setEnabled(false);
    oneGrossWeightBtn->setEnabled(true);
    oneTareWeightBtn->setEnabled(false);
    oneSaveGrossWeightBtn->setEnabled(true);
    oneSaveNetWeightBtn->setEnabled(false);
    oneMatNameComBox->setEnabled(true);
    oneSupplierComBox->setEnabled(true);
    onePositionNameComBox->setEnabled(true);
    oneSpecificationComBox->setEnabled(true);

    oneGrossWeightLineEdit->setEnabled(false);
    oneNetWeightLineEdit->setEnabled(false);

    oneRecordNoLineEdit->clear();
    oneGrossWeightLineEdit->clear();
    oneGrossWeightTimeLineEdit->clear();
    oneNetWeightLineEdit->clear();
    oneNetWeightTimeLineEdit->clear();
    oneTareWeightLineEdit->clear();
    oneBuckleLineEdit->clear();
    oneStorageKGLineEdit->clear();
    oneStorageCubeLineEdit->clear();
    oneDeliveryNoLineEdit->clear();
    oneLicensePlateLineEdit->clear();
    oneDeliveryManLineEdit->clear();
    oneTelephoneLineEdit->clear();
    oneRemarksLineEdit->clear();
    oneMatNameComBox->clear();
    oneSupplierComBox->clear();
    onePositionNameComBox->clear();
    oneSpecificationComBox->clear();
    const char *fillSQL2 = "select MaterialName from PurchaseMaterialList group by MaterialName;";
    db.sql_fillComboBoxItem(fillSQL2,oneMatNameComBox);
    connect(oneBuckleLineEdit,SIGNAL(textChanged(QString)),this,SLOT(StorageQuantityDispaly()));
    connect(oneNetWeightLineEdit,SIGNAL(textChanged(QString)),this,SLOT(StorageQuantityDispaly()));
    connect(oneTareWeightLineEdit,SIGNAL(textChanged(QString)),this,SLOT(NetWeightDisplay()));
    connect(oneGrossWeightLineEdit,SIGNAL(textChanged(QString)),this,SLOT(NetWeightDisplay()));
    connect(oneMatNameComBox,SIGNAL(currentTextChanged(QString)),this,SLOT(combo2Correspond()));
}

void guobangrukuDlg::on_newAction1_plus()
{
    disconnect(oneBuckleLineEdit,SIGNAL(textChanged(QString)),this,SLOT(StorageQuantityDispaly()));
    disconnect(oneNetWeightLineEdit,SIGNAL(textChanged(QString)),this,SLOT(StorageQuantityDispaly()));
    disconnect(oneTareWeightLineEdit,SIGNAL(textChanged(QString)),this,SLOT(NetWeightDisplay()));
    disconnect(oneGrossWeightLineEdit,SIGNAL(textChanged(QString)),this,SLOT(NetWeightDisplay()));
    disconnect(oneMatNameComBox,SIGNAL(currentTextChanged(QString)),this,SLOT(combo2Correspond()));
    updateAction1->setEnabled(false);
    deleteAction1->setEnabled(false);
    checkAction1->setEnabled(false);
    printAction1->setEnabled(false);
    oneGrossWeightBtn->setEnabled(true);
    oneTareWeightBtn->setEnabled(false);
    oneSaveGrossWeightBtn->setEnabled(true);
    oneSaveNetWeightBtn->setEnabled(false);
    oneMatNameComBox->setEnabled(true);
    oneSupplierComBox->setEnabled(true);
    onePositionNameComBox->setEnabled(true);
    oneSpecificationComBox->setEnabled(true);

    oneRecordNoLineEdit->setText(pub.newListNo());//新增一个入库单号
    oneGrossWeightLineEdit->setEnabled(false);
    oneTareWeightLineEdit->setEnabled(false);

    oneGrossWeightLineEdit->clear();
    oneGrossWeightTimeLineEdit->clear();
    oneNetWeightLineEdit->clear();
    oneNetWeightTimeLineEdit->clear();
    oneTareWeightLineEdit->clear();
    oneBuckleLineEdit->clear();
    oneStorageKGLineEdit->clear();
    oneStorageCubeLineEdit->clear();
    oneDeliveryNoLineEdit->clear();
    oneLicensePlateLineEdit->clear();
    oneDeliveryManLineEdit->clear();
    oneTelephoneLineEdit->clear();
    oneRemarksLineEdit->clear();
    oneMatNameComBox->clear();
    oneSupplierComBox->clear();
    onePositionNameComBox->clear();
    oneSpecificationComBox->clear();
    const char *fillSQL2 = "select MaterialName from PurchaseMaterialList group by MaterialName;";
    db.sql_fillComboBoxItem(fillSQL2,oneMatNameComBox);
    connect(oneBuckleLineEdit,SIGNAL(textChanged(QString)),this,SLOT(StorageQuantityDispaly()));
    connect(oneNetWeightLineEdit,SIGNAL(textChanged(QString)),this,SLOT(StorageQuantityDispaly()));
    connect(oneTareWeightLineEdit,SIGNAL(textChanged(QString)),this,SLOT(NetWeightDisplay()));
    connect(oneGrossWeightLineEdit,SIGNAL(textChanged(QString)),this,SLOT(NetWeightDisplay()));
    connect(oneMatNameComBox,SIGNAL(currentTextChanged(QString)),this,SLOT(combo2Correspond()));
}

void guobangrukuDlg::on_updateAction1()
{
    if(oneMatNameComBox->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择原料名称"),0,0,0);
        return;
    }
    else if(oneSupplierComBox->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择供应商"),0,0,0);
        return;
    }

    QString update1SQL = QString("update PurchaseReceipt set Buckle='%1',StorageKG='%2',StorageCube='%3',\
                                 DeliveryMan='%5',Telephone='%6',Remarks='%7',GrossWeight='%8',Tare='%9',\
                                 Material='%10',Supplier='%11',Position='%12',SpecificationModel='%13',LicensePlateNumber='%14' where StorageList='%15';")
            .arg(oneBuckleLineEdit->text(),oneStorageKGLineEdit->text(),oneStorageCubeLineEdit->text(),oneDeliveryManLineEdit->text(),
                 oneTelephoneLineEdit->text(),oneRemarksLineEdit->text(),oneGrossWeightLineEdit->text(),oneTareWeightLineEdit->text())
            .arg(oneMatNameComBox->currentText(),oneSupplierComBox->currentText(),onePositionNameComBox->currentText(),oneSpecificationComBox->currentText(),oneLicensePlateLineEdit->text())
            .arg(oneRecordNoLineEdit->text());

    int res = db.sql_exec(update1SQL);
    if(res == 0){
        db.showview(SQL1,view,&model);//显示表格
        setModelStyle(model);
        on_newAction1();
        oneRecordNoLineEdit->clear();
        QMessageBox::information(this,tr("提示信息"),tr("修改成功"),0,0,0);
    }
}

void guobangrukuDlg::on_deleteAction1()
{
    int res = QMessageBox::question(this,tr("提示信息"),tr("是否删除？"),QMessageBox::Yes|QMessageBox::No);
    if(res == QMessageBox::Yes)
    {
        QString delete1SQL = QString("delete from PurchaseReceipt where StorageList='%1';").arg(oneRecordNoLineEdit->text());
        int res = db.sql_exec(delete1SQL);
        if(res == 0){
            db.showview(SQL1,view,&model);//显示表格
            setModelStyle(model);
            on_newAction1();
            oneRecordNoLineEdit->clear();
            QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
        }
    }
    else {
        return;
    }
}

void guobangrukuDlg::on_checkAction1()
{
    QString check1SQL = QString("update PurchaseReceipt set WhetherCheck='是' where StorageList='%1';").arg(oneRecordNoLineEdit->text());
    int res = db.sql_exec(check1SQL);
    if(res == 0){
        db.showview(SQL1,view,&model);//显示表格
        db.showview(SQL2,twoview,&twomodel);//显示表格
        setModelStyle(model);

        //更新实际库存数量
        QString updateKucunSQL = QString("update InventoryQueryTmp set Quantity=Quantity+'%1' where PositionName='%2';")
                .arg(oneStorageKGLineEdit->text(),onePositionNameComBox->currentText());
        db.sql_exec(updateKucunSQL);

        //更新入库单中材料价格,计量单位
        QString fetchDataSQL = QString("select Price from PurchaseMaterialList where MaterialName='%1' and Supplier='%2' and DateTime<'%3' order by DateTime desc limit 1")
                        .arg(oneMatNameComBox->currentText(),oneSupplierComBox->currentText(),oneGrossWeightTimeLineEdit->text());

        QString Price = db.sql_fetchrow_plus(fetchDataSQL,0);

        QString updatePriceSQL = QString("update PurchaseReceipt set UnitPrice='%1' where StorageList='%2'").arg(Price,oneRecordNoLineEdit->text());

        db.sql_exec(updatePriceSQL);

        on_newAction1();
        oneRecordNoLineEdit->clear();
        QMessageBox::information(this,tr("提示信息"),tr("审核成功"),0,0,0);
    }
}

void guobangrukuDlg::on_printAction1()
{
    QString printSQL = QString("SELECT *,StorageKG/StorageCube FROM PurchaseReceipt WHERE StorageList='%1';").arg(oneRecordNoLineEdit->text());
    if(library->load()){
        typedef void  (*pFunc)(const char *,const char *);
        pFunc function=(pFunc)library->resolve("printReport");
        if(function){
            function("report/report14.fr3",printSQL.toLocal8Bit().data());
        }
    }
    else{
        QMessageBox::information(this,tr("错误"),library->errorString());
    }
}

void guobangrukuDlg::on_newAction3()
{
    printAction3->setEnabled(true);
    updateAction3->setEnabled(true);
    deleteAction3->setEnabled(false);
    threeGrossWeightBtn->setEnabled(true);
    threeSaveGrossWeightBtn->setEnabled(true);
    threeTareWeightBtn->setEnabled(false);
    threeSaveTareWeightBtn->setEnabled(false);
    threeLicensePlateCombox->setEnabled(true);
    threeRecordNoLineEdit->clear();
    threeCustomerNameLineEdit->clear();
    threeEngineerLineEdit->clear();
    threeGrossWeightLineEdit->clear();
    threeGrossWeightTimeLineEdit->clear();
    threeTareWeightLineEdit->clear();
    threeTareWeightTimeLineEdit->clear();
    threeNetWeightLineEdit->clear();
    threeUnitWeightLineEdit->clear();
    threeVolumeLineEdit->clear();
    threeStrengthGradeLineEdit->clear();
    threeWeightPersonLineEdit->setText(userName);
    threeRemarksLineEdit->clear();
    threeDriverLineEdit->clear();
    threeLicensePlateCombox->setCurrentIndex(0);
}

void guobangrukuDlg::on_newAction3_plus()
{
    printAction3->setEnabled(false);
    deleteAction3->setEnabled(false);
    threeGrossWeightBtn->setEnabled(true);
    threeSaveGrossWeightBtn->setEnabled(true);
    threeTareWeightBtn->setEnabled(false);
    threeSaveTareWeightBtn->setEnabled(false);
    threeLicensePlateCombox->setEnabled(true);
    threeRecordNoLineEdit->setText(pub.newfahuoNo());//新增一个发货单号
    threeCustomerNameLineEdit->clear();
    threeEngineerLineEdit->clear();
    threeGrossWeightLineEdit->clear();
    threeGrossWeightTimeLineEdit->clear();
    threeTareWeightLineEdit->clear();
    threeTareWeightTimeLineEdit->clear();
    threeNetWeightLineEdit->clear();
    threeUnitWeightLineEdit->clear();
    threeVolumeLineEdit->clear();
    threeStrengthGradeLineEdit->clear();
    threeWeightPersonLineEdit->setText(userName);
    threeRemarksLineEdit->clear();
    threeDriverLineEdit->clear();
    threeLicensePlateCombox->setCurrentIndex(0);
}

void guobangrukuDlg::on_slAction3()
{
    printAction3->setEnabled(false);
    deleteAction3->setEnabled(false);
    threeGrossWeightBtn->setEnabled(true);
    threeSaveGrossWeightBtn->setEnabled(true);
    threeTareWeightBtn->setEnabled(false);
    threeSaveTareWeightBtn->setEnabled(false);
    threeLicensePlateCombox->setEnabled(true);
    threeRecordNoLineEdit->setText(pub.newshengliaoNo());//新增一个剩料单号
    threeCustomerNameLineEdit->clear();
    threeEngineerLineEdit->clear();
    threeGrossWeightLineEdit->clear();
    threeGrossWeightTimeLineEdit->clear();
    threeTareWeightLineEdit->clear();
    threeTareWeightTimeLineEdit->clear();
    threeNetWeightLineEdit->clear();
    threeUnitWeightLineEdit->clear();
    threeVolumeLineEdit->clear();
    threeStrengthGradeLineEdit->clear();
    threeWeightPersonLineEdit->setText(userName);
    threeRemarksLineEdit->clear();
    threeDriverLineEdit->clear();
    threeLicensePlateCombox->setCurrentIndex(0);
}

void guobangrukuDlg::on_updateAction3()
{
    QString updateSQL = QString("update TankWeighing set GrossWeight='%1',NetWeight='%2',Volume='%3' where RecordNumber='%4';")
            .arg(threeGrossWeightLineEdit->text(),threeNetWeightLineEdit->text(),threeVolumeLineEdit->text(),threeRecordNoLineEdit->text());
    int res = db.sql_exec(updateSQL);
    if(res == 0){
        db.showview(SQL3,threeview,&threemodel);

        QString deleteSQL = QString("delete from inHouseVehicle where CheNo='%1'").arg(threeLicensePlateCombox->currentText());
        db.sql_exec(deleteSQL);

        on_newAction3();
        threeRecordNoLineEdit->clear();
        QMessageBox::information(this,tr("提示信息"),tr("修改成功"),0,0,0);
    }
}

void guobangrukuDlg::on_deleteAction3()
{
    QString deleteSQL = QString("delete from TankWeighing where RecordNumber ='%1';").arg(threeRecordNoLineEdit->text());
    int res = db.sql_exec(deleteSQL);
    if(res == 0){
        db.showview(SQL4,fourview,&fourmodel);
        on_newAction3();
        threeRecordNoLineEdit->clear();
        QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
    }
}

void guobangrukuDlg::on_printAction3()
{
    if(threeRecordNoLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择要打印的过磅记录"),0,0,0);
        return;
    }

    QString printSQL = QString("SELECT * FROM TankWeighing WHERE RecordNumber='%1';").arg(threeRecordNoLineEdit->text());
    if(library->load()){
        typedef void  (*pFunc)(const char *,const char *);
        pFunc function=(pFunc)library->resolve("printReport");
        if(function){
            if(threeRecordNoLineEdit->text().contains("fh")){
                function("report/report16.fr3",printSQL.toLocal8Bit().data());
            }
            else if(threeRecordNoLineEdit->text().contains("sl")){
                function("report/report17.fr3",printSQL.toLocal8Bit().data());
            }

        }
    }
    else{
        QMessageBox::information(this,tr("错误"),library->errorString());
    }
}

void guobangrukuDlg::on_cancelAction3()
{
    QString searchStateSQL = QString("select whetherCancel,DanHao from TankWeighing where RecordNumber='%1';").arg(threeRecordNoLineEdit->text());
    if(db.sql_fetchrow_plus(searchStateSQL,0) == "是"){
        QMessageBox::information(this,tr("提示信息"),tr("该剩料已经作废，不必重复操作"),0,0,0);
        return;
    }
    QString ReturnRecordNo = db.sql_fetchrow_plus(searchStateSQL,1);

    int res = QMessageBox::question(this,tr("提示信息"),tr("是否作废剩料？"),QMessageBox::Yes|QMessageBox::No);
    if(res == QMessageBox::Yes)
    {
        //更新车辆队列表
        QString searchSQL = QString("select CheTime from inHouseVehicle where CheNo='%1'").arg(threeLicensePlateCombox->currentText());
        QString CheTime = db.sql_fetchrow_plus(searchSQL,0);
        QDateTime datetime = QDateTime::fromString(CheTime,"yyyy-MM-dd hh:mm:ss").addDays(10);
        QString updateinHouseVehicle = QString("update inHouseVehicle set CheState='普通',CheTime='%1' where CheNo='%2';").arg(datetime.toString("yyyy-MM-dd hh:mm:ss"),threeLicensePlateCombox->currentText());
        db.sql_exec(updateinHouseVehicle);

        //更新罐车过磅表
        QString updateTankWeighing = QString("update TankWeighing set whetherCancel='是' where RecordNumber='%1';").arg(threeRecordNoLineEdit->text());
        db.sql_exec(updateTankWeighing);

        //更新剩转料记录表
        QString updateTransferMaterialRecord = QString("update TransferMaterialRecord set ReturnZuoFeiVolume=ReturnVolume where ReturnRecordNo='%1'").arg(ReturnRecordNo);
        db.sql_exec(updateTransferMaterialRecord);

        sockClient->send_Msg3();
        QMessageBox::information(this,tr("提示信息"),tr("剩料作废成功"),0,0,0);
        return;
    }
    else {
        return;
    }
}

void guobangrukuDlg::on_chengmaozhong()
{
//    if(LCDnumber->value() == 0){
//        QMessageBox::information(this,tr("错误"),"地磅示数为0");
//        return;
//    }

    disconnect(oneGrossWeightLineEdit,SIGNAL(textChanged(QString)),this,SLOT(NetWeightDisplay()));
    oneGrossWeightLineEdit->setText(QString::number(LCDnumber->value()));
    //oneGrossWeightLineEdit->setText(QString::number(56213));
    oneGrossWeightTimeLineEdit->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm"));
    connect(oneGrossWeightLineEdit,SIGNAL(textChanged(QString)),this,SLOT(NetWeightDisplay()));
    on_baocunmaozhong();
}

void guobangrukuDlg::on_chengpizhong()
{
//    if(LCDnumber->value() == 0){
//        QMessageBox::information(this,tr("错误"),"地磅示数为0");
//        return;
//    }

    connect(oneBuckleLineEdit,SIGNAL(textChanged(QString)),this,SLOT(StorageQuantityDispaly()));
    connect(oneTareWeightLineEdit,SIGNAL(textChanged(QString)),this,SLOT(NetWeightDisplay()));
    oneTareWeightLineEdit->setText(QString::number(LCDnumber->value()));
    //oneTareWeightLineEdit->setText(QString::number(35267));
    oneNetWeightTimeLineEdit->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm"));
    on_baocunpizhong();
    //双击
    on_printAction1();
}

void guobangrukuDlg::on_baocunmaozhong()
{
    if(oneRecordNoLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请新增一个入库单号"),0,0,0);
        return;
    }
    else if(onePlantNameComBox->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择入库厂地"),0,0,0);
        return;
    }
    else if(oneMatNameComBox->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择原料名称"),0,0,0);
        return;
    }
    else if(oneSupplierComBox->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择供应商"),0,0,0);
        return;
    }else if(onePositionNameComBox->currentText().isEmpty() && oneMatNameComBox->currentText().contains("水泥")){
        QMessageBox::information(this,tr("提示信息"),tr("请选择仓位"),0,0,0);
        return;
    }

    else if(onePositionNameComBox->currentText().isEmpty() && oneMatNameComBox->currentText().contains("粉煤灰")){
        QMessageBox::information(this,tr("提示信息"),tr("请选择仓位"),0,0,0);
        return;
    }
    else if(oneGrossWeightLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请称毛重"),0,0,0);
        return;
    }
    else if(oneLicensePlateLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入车牌号"),0,0,0);
        return;
    }

    QString maozhongSQL = QString("insert into PurchaseReceipt (StorageList,Storagefactory,Material,Supplier,Position,\
                                  SpecificationModel,GrossWeight,GrossWeightTime,NetWeight,Buckle,StorageKG,StorageCube,\
                                  DeliveryNote,LicensePlateNumber,DeliveryMan,Telephone,Remarks,WhetherCheck,Time,GBMAN\
                                  ) values ('%1','%2','%3','%4','%5','%6','%7','%8','%9','%10',\
                                  '%11','%12','%13','%14','%15','%16','%17','否','%18','%19');")
    .arg(oneRecordNoLineEdit->text(),onePlantNameComBox->currentText(),oneMatNameComBox->currentText(),oneSupplierComBox->currentText(),onePositionNameComBox->currentText(),
         oneSpecificationComBox->currentText(),oneGrossWeightLineEdit->text(),oneGrossWeightTimeLineEdit->text(),oneTareWeightLineEdit->text())
    .arg(oneBuckleLineEdit->text(),oneStorageKGLineEdit->text(),oneStorageCubeLineEdit->text(),oneDeliveryNoLineEdit->text(),oneLicensePlateLineEdit->text(),oneDeliveryManLineEdit->text(),\
         oneTelephoneLineEdit->text(),oneRemarksLineEdit->text(),QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm"))
    .arg(userName);
    qDebug()<<maozhongSQL;

    int res = db.sql_exec(maozhongSQL);
    if(res == 0){
        db.showview(SQL1,view,&model);//显示表格
        setModelStyle(model);

        QString deleteSQL = QString("delete from cardRecord where cardNo='%1';").arg(oneDeliveryNoLineEdit->text());
        db.sql_exec(deleteSQL);

        on_newAction1();
        oneRecordNoLineEdit->clear();
        oneGrossWeightBtn->setEnabled(false);
        oneSaveGrossWeightBtn->setEnabled(false);
//        QMessageBox::information(this,tr("提示信息"),tr("保存毛重成功"),0,0,0);

        QString filename1 = QString("D:\\CaptureBmpPic\\%1毛重车头.bmp").arg(oneRecordNoLineEdit->text());
        QString filename2 = QString("D:\\CaptureBmpPic\\%1毛重货物.bmp").arg(oneRecordNoLineEdit->text());
        QString filename3 = QString("D:\\CaptureBmpPic\\%1毛重车尾.bmp").arg(oneRecordNoLineEdit->text());
        video->CaptureBmpPic(filename1,filename2,filename3);
    }
}

void guobangrukuDlg::on_baocunpizhong()
{
    if(oneNetWeightTimeLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请称皮重"),0,0,0);
        return;
    }
    else if(oneBuckleLineEdit->text().isEmpty()){
        oneBuckleLineEdit->setText("0");
//        QMessageBox::information(this,tr("提示信息"),tr("请输入扣重"),0,0,0);
//        return;
    }



    if(oneTareWeightLineEdit->text().toDouble() > oneGrossWeightLineEdit->text().toDouble())
    {
        QString tem = oneTareWeightLineEdit->text();
        oneTareWeightLineEdit->setText(oneGrossWeightLineEdit->text());
        oneGrossWeightLineEdit->setText(tem);
        double tem2 = oneGrossWeightLineEdit->text().toDouble() - oneTareWeightLineEdit->text().toDouble();
        oneStorageKGLineEdit->setText(QString::number(tem2,'f',2));
    }


    QString selectCube = QString("select StorageCube from PurchaseReceipt where StorageList='%1'").arg(oneRecordNoLineEdit->text());
    oneStorageCubeLineEdit->setText(db.sql_fetchrow_plus(selectCube,0));

    QString pizhongSQL = QString("update PurchaseReceipt set Tare='%1', TareTime='%2',NetWeight='%3',Buckle='%4',\
                                 StorageKG='%5',StorageCube='%6',DeliveryNote='%7',DeliveryMan='%8',Telephone='%9',\
                                 Remarks='%10',GrossWeight='%11' where StorageList='%12';")
            .arg(oneTareWeightLineEdit->text(),oneNetWeightTimeLineEdit->text(),oneNetWeightLineEdit->text(),oneBuckleLineEdit->text(),oneStorageKGLineEdit->text(),
                 oneStorageCubeLineEdit->text(),oneDeliveryNoLineEdit->text(),oneDeliveryManLineEdit->text(),oneTelephoneLineEdit->text())
            .arg(oneRemarksLineEdit->text(),oneGrossWeightLineEdit->text(),oneRecordNoLineEdit->text());

    int res = db.sql_exec(pizhongSQL);
    if(res == 0){
        db.showview(SQL1,view,&model);//显示表格
        setModelStyle(model);
        QString deleteSQL = QString("delete from cardRecord where cardNo='%1';").arg(oneDeliveryNoLineEdit->text());
        db.sql_exec(deleteSQL);
//        on_newAction1();
//        oneRecordNoLineEdit->clear();
//        QMessageBox::information(this,tr("提示信息"),tr("保存皮重成功"),0,0,0);

        QString filename1 = QString("D:\\CaptureBmpPic\\%1皮重车头").arg(oneRecordNoLineEdit->text());
        QString filename2 = QString("D:\\CaptureBmpPic\\%1皮重货物").arg(oneRecordNoLineEdit->text());
        QString filename3 = QString("D:\\CaptureBmpPic\\%1皮重车尾").arg(oneRecordNoLineEdit->text());
        video->CaptureBmpPic(filename1,filename2,filename3);
    }
}

void guobangrukuDlg::ShowSupplyclick1()
{
    //disconnect(oneMatNameComBox,SIGNAL(currentTextChanged(QString)),this,SLOT(combo2Correspond()));
    oneMatNameComBox->setEnabled(true);
    oneSupplierComBox->setEnabled(true);
    onePositionNameComBox->setEnabled(true);
    oneSpecificationComBox->setEnabled(true);
    oneRecordNoLineEdit->setEnabled(false);
    updateAction1->setEnabled(true);
    deleteAction1->setEnabled(true);
    printAction1->setEnabled(true);
    int row = view->currentIndex().row();

    oneGrossWeightLineEdit->setEnabled(false);
    oneTareWeightLineEdit->setEnabled(false);

    oneRecordNoLineEdit->setText(model->item(row,0)->text());
    oneGrossWeightLineEdit->setText(model->item(row,6)->text());
    oneGrossWeightTimeLineEdit->setText(model->item(row,7)->text());

    oneTareWeightLineEdit->setText(model->item(row,8)->text());
    oneNetWeightTimeLineEdit->setText(model->item(row,9)->text());
    if(oneNetWeightTimeLineEdit->text().isEmpty()){
        checkAction1->setEnabled(false);
    }else{
        checkAction1->setEnabled(true);
    }
    oneNetWeightLineEdit->setText(model->item(row,10)->text());
    oneBuckleLineEdit->setText(model->item(row,11)->text());
    oneStorageKGLineEdit->setText(model->item(row,12)->text());
    oneStorageCubeLineEdit->setText(model->item(row,13)->text());
    //oneDeliveryNoLineEdit->setText(model->item(row,14)->text());
    cardNo = model->item(row,14)->text();
    oneDeliveryManLineEdit->setText(model->item(row,15)->text());
    oneTelephoneLineEdit->setText(model->item(row,16)->text());
    oneRemarksLineEdit->setText(model->item(row,17)->text());
    onePlantNameComBox->setCurrentText(model->item(row,18)->text());
    oneMatNameComBox->setCurrentText(model->item(row,1)->text());
    oneSupplierComBox->setCurrentText(model->item(row,4)->text());
    onePositionNameComBox->setCurrentText(model->item(row,3)->text());
    oneSpecificationComBox->setCurrentText(model->item(row,2)->text());
    WarehousingDate.clear();
    WarehousingDate = model->item(row,21)->text();
    oneLicensePlateLineEdit->setText(model->item(row,5)->text());
    if(oneNetWeightTimeLineEdit->text().isEmpty())
    {
        oneTareWeightBtn->setEnabled(true);
        oneSaveNetWeightBtn->setEnabled(true);
        oneGrossWeightBtn->setEnabled(false);
        oneSaveGrossWeightBtn->setEnabled(false);
    }
    else{
        oneTareWeightBtn->setEnabled(false);
        oneSaveNetWeightBtn->setEnabled(false);
        oneGrossWeightBtn->setEnabled(false);
        oneSaveGrossWeightBtn->setEnabled(false);
    }
}

void guobangrukuDlg::ShowSupplyclick2()
{
    disconnect(oneBuckleLineEdit,SIGNAL(textChanged(QString)),this,SLOT(StorageQuantityDispaly()));
    disconnect(oneTareWeightLineEdit,SIGNAL(textChanged(QString)),this,SLOT(StorageQuantityDispaly()));
    disconnect(oneTareWeightLineEdit,SIGNAL(textChanged(QString)),this,SLOT(NetWeightDisplay()));
    disconnect(oneGrossWeightLineEdit,SIGNAL(textChanged(QString)),this,SLOT(NetWeightDisplay()));
    disconnect(oneMatNameComBox,SIGNAL(currentTextChanged(QString)),this,SLOT(combo2Correspond()));

    oneRecordNoLineEdit->setEnabled(false);
    updateAction1->setEnabled(false);
    checkAction1->setEnabled(false);
    deleteAction1->setEnabled(false);
    printAction1->setEnabled(true);

    int row = twoview->currentIndex().row();
    oneRecordNoLineEdit->setText(twomodel->item(row,0)->text());
    oneGrossWeightLineEdit->setText(twomodel->item(row,6)->text());
    oneGrossWeightTimeLineEdit->setText(twomodel->item(row,7)->text());
    oneTareWeightLineEdit->setText(twomodel->item(row,8)->text());
    oneNetWeightTimeLineEdit->setText(twomodel->item(row,9)->text());
//    oneTareWeightLineEdit->setText(twomodel->item(row,10)->text());
    oneNetWeightLineEdit->setText(twomodel->item(row,10)->text());
    oneBuckleLineEdit->setText(twomodel->item(row,11)->text());
    oneStorageKGLineEdit->setText(twomodel->item(row,12)->text());
    oneStorageCubeLineEdit->setText(twomodel->item(row,13)->text());
    oneDeliveryNoLineEdit->setText(twomodel->item(row,14)->text());
    oneLicensePlateLineEdit->setText(twomodel->item(row,5)->text());
    oneDeliveryManLineEdit->setText(twomodel->item(row,15)->text());
    oneTelephoneLineEdit->setText(twomodel->item(row,16)->text());
    oneRemarksLineEdit->setText(twomodel->item(row,17)->text());
    onePlantNameComBox->setEditable(true);
    oneMatNameComBox->setEditable(true);
    oneSupplierComBox->setEditable(true);
    onePositionNameComBox->setEditable(true);
    oneSpecificationComBox->setEditable(true);
    onePlantNameComBox->setEnabled(false);
    oneMatNameComBox->setEnabled(false);
    oneSupplierComBox->setEnabled(false);
    onePositionNameComBox->setEnabled(false);
    oneSpecificationComBox->setEnabled(false);
    onePlantNameComBox->setCurrentText(twomodel->item(row,18)->text());
    oneMatNameComBox->setCurrentText(twomodel->item(row,1)->text());
    oneSupplierComBox->setCurrentText(twomodel->item(row,4)->text());
    onePositionNameComBox->setCurrentText(twomodel->item(row,3)->text());
    oneSpecificationComBox->setCurrentText(twomodel->item(row,2)->text());

    oneGrossWeightBtn->setEnabled(false);
    oneTareWeightBtn->setEnabled(false);
    oneSaveGrossWeightBtn->setEnabled(false);
    oneSaveNetWeightBtn->setEnabled(false);
    connect(oneBuckleLineEdit,SIGNAL(textChanged(QString)),this,SLOT(StorageQuantityDispaly()));
    connect(oneTareWeightLineEdit,SIGNAL(textChanged(QString)),this,SLOT(StorageQuantityDispaly()));
    connect(oneTareWeightLineEdit,SIGNAL(textChanged(QString)),this,SLOT(NetWeightDisplay()));
    connect(oneGrossWeightLineEdit,SIGNAL(textChanged(QString)),this,SLOT(NetWeightDisplay()));
    connect(oneMatNameComBox,SIGNAL(currentTextChanged(QString)),this,SLOT(combo2Correspond()));

    tabWidget->setCurrentIndex(0);
}

void guobangrukuDlg::ShowSupplyclick3()
{
    threeGrossWeightBtn->setEnabled(true);
    threeSaveGrossWeightBtn->setEnabled(false);
    threeTareWeightBtn->setEnabled(true);
    threeSaveTareWeightBtn->setEnabled(true);
    printAction3->setEnabled(true);
    cancelAction3->setEnabled(false);
    int row = threeview->currentIndex().row();
    threeLicensePlateCombox->setCurrentText(threemodel->item(row,1)->text());
    threeRecordNoLineEdit->setText(threemodel->item(row,0)->text());
    threeCustomerNameLineEdit->setText(threemodel->item(row,11)->text());
    threeEngineerLineEdit->setText(threemodel->item(row,12)->text());
    threeGrossWeightLineEdit->setText(threemodel->item(row,7)->text());
    threeGrossWeightTimeLineEdit->setText(threemodel->item(row,8)->text());
    threeTareWeightLineEdit->setText(threemodel->item(row,9)->text());
    threeTareWeightTimeLineEdit->setText(threemodel->item(row,10)->text());
    threeNetWeightLineEdit->setText(threemodel->item(row,5)->text());
    threeUnitWeightLineEdit->setText(threemodel->item(row,6)->text());
    threeVolumeLineEdit->setText(threemodel->item(row,3)->text());
    threeStrengthGradeLineEdit->setText(threemodel->item(row,4)->text());
    threeWeightPersonLineEdit->setText(threemodel->item(row,14)->text());
    threeRemarksLineEdit->setText(threemodel->item(row,15)->text());
    threeDriverLineEdit->setText(threemodel->item(row,2)->text());

    if(threeRecordNoLineEdit->text().contains("sl")){
        cancelAction3->setEnabled(true);
    }
}

void guobangrukuDlg::ShowSupplyclick4()
{
    printAction3->setEnabled(true);
    threeGrossWeightBtn->setEnabled(false);
    threeSaveGrossWeightBtn->setEnabled(false);
    threeTareWeightBtn->setEnabled(false);
    threeSaveTareWeightBtn->setEnabled(false);
    int row = fourview->currentIndex().row();
    threeLicensePlateCombox->setCurrentText(fourmodel->item(row,1)->text());
    threeRecordNoLineEdit->setText(fourmodel->item(row,0)->text());
    threeCustomerNameLineEdit->setText(fourmodel->item(row,11)->text());
    threeEngineerLineEdit->setText(fourmodel->item(row,12)->text());
    threeGrossWeightLineEdit->setText(fourmodel->item(row,7)->text());
    threeGrossWeightTimeLineEdit->setText(fourmodel->item(row,8)->text());
    threeTareWeightLineEdit->setText(fourmodel->item(row,9)->text());
    threeTareWeightTimeLineEdit->setText(fourmodel->item(row,10)->text());
    threeNetWeightLineEdit->setText(fourmodel->item(row,5)->text());
    threeUnitWeightLineEdit->setText(fourmodel->item(row,6)->text());
    threeVolumeLineEdit->setText(fourmodel->item(row,3)->text());
    threeStrengthGradeLineEdit->setText(fourmodel->item(row,4)->text());
    threeWeightPersonLineEdit->setText(fourmodel->item(row,14)->text());
    threeRemarksLineEdit->setText(fourmodel->item(row,15)->text());
    threeDriverLineEdit->setText(fourmodel->item(row,2)->text());
    tabWidget->setCurrentIndex(2);
}

void guobangrukuDlg::combo2Correspond()
{
    oneSupplierComBox->clear();
    onePositionNameComBox->clear();
    oneSpecificationComBox->clear();
    QString fillSQL3 = QString("select Supplier from PurchaseMaterialList where MaterialName='%1' group by Supplier;").arg(oneMatNameComBox->currentText());
    db.sql_fillComboBoxItem(fillSQL3,oneSupplierComBox);
    oneSupplierComBox->setCurrentText(db.sql_fetchrow_plus(fillSQL3,0));


//    QString chapaiSQL = QString("select LicensePlateNumber from PurchaseReceipt where Material='%1' group by Supplier;").arg(oneMatNameComBox->currentText());
//    oneLicensePlateLineEdit->setText(db.sql_fetchrow_plus(chapaiSQL,0));


//    if(oneMatNameComBox->currentText().contains("石")){
//        QString searchType = QString("select Type from MaterialSetting where Material='%1';").arg(oneMatNameComBox->currentText());
//        qDebug()<<searchType;
//        QString Type = db.sql_fetchrow_plus(searchType,0);

//        QString fillSQL4 = QString("select PositionName from PositionSetting where Material='%1';").arg(Type);
//        db.sql_fillComboBoxItem(fillSQL4,onePositionNameComBox);
//    }else{
        QString fillSQL4 = QString("select PositionName from PositionSetting where Material='%1';").arg(oneMatNameComBox->currentText());
        db.sql_fillComboBoxItem(fillSQL4,onePositionNameComBox);
//    }



    QString fillSQL5 = QString("select Specifications from PurchaseMaterialList where MaterialName='%1' group by Specifications;").arg(oneMatNameComBox->currentText());
    db.sql_fillComboBoxItem(fillSQL5,oneSpecificationComBox);
    oneSpecificationComBox->setCurrentText(db.sql_fetchrow_plus(fillSQL5,0));
}

void guobangrukuDlg::NetWeightDisplay()
{
    double num = oneGrossWeightLineEdit->text().toDouble() - oneTareWeightLineEdit->text().toDouble();
    oneNetWeightLineEdit->setText(QString::number(num,'g',10));
}

void guobangrukuDlg::StorageQuantityDispaly()
{
    QString SQL = QString("select FoldOver from MaterialSetting where Material='%1' and SpecificationModel='%2';")
            .arg(oneMatNameComBox->currentText(),oneSpecificationComBox->currentText());
    QString foldOver = db.sql_fetchrow_plus(SQL,0);
    if(foldOver.isEmpty()){
        foldOver = "0";
    }

    int num1 = 0;
    double num2 = 0;
    str11 = oneNetWeightLineEdit->text();
    str12 = oneBuckleLineEdit->text();

    num1 = str11.toInt() - str12.toInt();
    num2 = ((double)num1) / foldOver.toDouble();

    char strnum2[20] = {0};
    sprintf(strnum2,"%.2lf",num2);
    oneStorageKGLineEdit->setText(QString::number(num1));
    if(strcmp(strnum2,"nan") == 0||strcmp(strnum2,"inf") == 0||strcmp(strnum2,"-inf") == 0){
        oneStorageCubeLineEdit->clear();
    }else{
        oneStorageCubeLineEdit->setText(QString::number(num2,'f',2));
    }
}

void guobangrukuDlg::on_twoFindBtn()
{
    QString ruku,yuanliao,gongyingshang,timeRange;

    if(!(twoPlantNameCombox->currentText().isEmpty())){
        ruku = QString(" and Storagefactory='%1'").arg(twoPlantNameCombox->currentText());
    }
    if(twoMaterialNameCheckBox->checkState() == 2){
        yuanliao = QString(" and Material='%1'").arg(twoMaterialCombox->currentText());
    }
    if(twoSupplierCheckBox->checkState() == 2){
        gongyingshang = QString(" and Supplier='%1'").arg(twoSupplierCombox->currentText());
    }
    QString searchSQLCount = QString(" select COUNT(StorageList) from PurchaseReceipt where WhetherCheck='是' \
                                     and GrossWeightTime between '%1' and '%2'%3%4%5;")
                 .arg(twodt1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),twodt2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),ruku,yuanliao,gongyingshang);
    qDebug()<<searchSQLCount;
   QStringList num =db.find_CheNo(searchSQLCount);
   totalTrainLabelNum->setText(num.at(0));
   QString searchSQL = QString("select StorageList 入库单,Material 原料,SpecificationModel 规格,Position 仓位,\
                               Supplier 供应商,LicensePlateNumber 车牌号,GrossWeight 毛重,GrossWeightTime 称毛重时间,\
                               Tare 皮重,TareTime 称皮重时间,StorageKG 净重,Buckle 扣重,StorageKG 入库（KG）,\
                               StorageCube 入库（方）,DeliveryNote 送货单,DeliveryMan 送货人,Telephone 电话,\
                               Remarks 备注,Storagefactory 入库厂地,PlaceOfOrigin 产地,ContractNumber 合同编号,GBMAN 过磅人 \
                               from PurchaseReceipt where WhetherCheck='是' \
                               and TareTime between '%1' and '%2'%3%4%5;")
           .arg(twodt1->date().toString("yyyy-MM-dd"),twodt2->date().addDays(1).toString("yyyy-MM-dd"),ruku,yuanliao,gongyingshang);
    db.showview(searchSQL,twoview,&twomodel);
}

void guobangrukuDlg::on_fourchaxun()
{
    QString chepaihao;
    if(fourcheckBox->checkState() == 2){
        chepaihao = QString(" and LicensePlateNumber='%1'").arg(fourcombo->currentText());
    }

    QString searchSQL = QString("select RecordNumber  记录编号,LicensePlateNumber 车牌号,Driver 司机,Volume 方量,strengthGrade 强度等级,\
                                NetWeight 净重,BulkDensity 容重,GrossWeight 毛重,\
                                GrossWeightTime 称毛重时间,Tare 皮重,TareTime 称皮重时间,Customer 客户,engineering 工程,\
                                Unit 生产机组,WeighPeople 过磅人,Remarks 备注 from TankWeighing where GrossWeightTime between '%1' and '%2'%3;")
            .arg(fourdate1->date().toString("yyyy-MM-dd"),fourdate2->date().addDays(1).toString("yyyy-MM-dd"),chepaihao);
    db.showview(searchSQL,fourview,&fourmodel);
}

void guobangrukuDlg::on_chengmaozhong3()
{
    if(threeManualInPutCheckBox->checkState() == 0){
        if(threeLCDnumber->value() == 0){
            QMessageBox::information(this,tr("错误"),"地磅示数为0，请正确选择地磅");
            return;
        }

        threeGrossWeightLineEdit->setText(QString::number(threeLCDnumber->value()));
    }

    threeGrossWeightTimeLineEdit->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm"));
    on_chengpizhong3();
}


void guobangrukuDlg::on_baocunmaozhong3()
{
    if(threeRecordNoLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请新增一个单号"),0,0,0);
        return;
    }
    else if(threeLicensePlateCombox->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择过磅车辆"),0,0,0);
        return;
    }
    else if(threeGrossWeightLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请称毛重"),0,0,0);
        return;
    }
    else if(threeTareWeightLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("无皮重信息，无法过磅"),0,0,0);
        return;
    }
    else if(threeUnitWeightLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("无容重信息，可能车牌号输入错误！！！"),0,0,0);
        return;
    }

    QString insertSQL = QString("replace into TankWeighing (RecordNumber,LicensePlateNumber,Customer,engineering,GrossWeight,GrossWeightTime,\
                                BulkDensity,strengthGrade,WeighPeople,Remarks,Driver,Unit,Tare,TareTime,NetWeight,Volume,DanHao) values ('%1','%2',\
                                '%3','%4','%5','%6','%7','%8','%9','%10','%11','%12','%13','%14','%15','%16','%17');")
            .arg(threeRecordNoLineEdit->text(),threeLicensePlateCombox->currentText(),threeCustomerNameLineEdit->text(),threeEngineerLineEdit->text(),threeGrossWeightLineEdit->text(),
                 threeGrossWeightTimeLineEdit->text(),threeUnitWeightLineEdit->text(),threeStrengthGradeLineEdit->text(),threeWeightPersonLineEdit->text())
            .arg(threeRemarksLineEdit->text(),threeDriverLineEdit->text(),threeUnit,threeTareWeightLineEdit->text(),threeTareWeightTimeLineEdit->text(),threeNetWeightLineEdit->text(),
                 threeVolumeLineEdit->text(),threeRecordNum);
    int res = db.sql_exec(insertSQL);
    if(res == 0){
        if(threeRecordNoLineEdit->text().contains("sl")){
            QString insertSQL = QString("replace into inHouseVehicle (CheNo,CheTime,ID,CheState) select '%1','%2',B.CardNumber,'剩料' from ConcreteVehicleInformation B where B.LicensePlate='%1'")
                    .arg(threeLicensePlateCombox->currentText(),QDateTime::currentDateTime().addDays(-10).toString("yyyy-MM-dd hh:mm:ss"));
            db.sql_exec(insertSQL);

            QString updateinHouseVehicle = QString("update inHouseVehicle set CheState = '%1', CheTime = '%2' where CheNo = '%3' ")
                    .arg("剩料",QDateTime::currentDateTime().addDays(-10).toString("yyyy-MM-dd hh:mm:ss"),threeLicensePlateCombox->currentText());
            db.sql_exec(updateinHouseVehicle);

            //加入剩退转中标记为剩料
            QString insertSTZ = QString("insert into TransferMaterialRecord (OperatingTime,ReturnRecordNo,ReturnEngineer,ReturnStrengthGrade,ReturnShippingVolume,ReturnReceiptVolume,ReturnProductVolume,\
                                        ReturnVolume,Operator,Type,ReturnVehicle) values ('%1','%2','%3','%4','%5','%6','%7','%8','%9','剩料','%10');")
                                .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"),threeRecordNum,threeEngineerLineEdit->text(),threeStrengthGradeLineEdit->text(),
                                     threeShippingVolume,threeReceiptVolume,threeActualProductionVolume,threeVolumeLineEdit->text(),userName).arg(threeLicensePlateCombox->currentText());
            db.sql_exec(insertSTZ);
        }
        else if(threeRecordNoLineEdit->text().contains("fh")){
            QString deleteSQL = QString("delete from inHouseVehicle where CheNo='%1'").arg(threeLicensePlateCombox->currentText());
            db.sql_exec(deleteSQL);

            //补方量代码************************************************************/
            double bufang = threeReceiptVolume.toDouble() - threeVolumeLineEdit->text().toDouble();
            if(bufang >= 0.4){
                QString insertSQL = QString("replace into bufangNotice (select * from ProductionNotice where RecordNumber=%1)").arg(threeRecordNum);
                db.sql_exec(insertSQL);
                QString updateSQL = QString("update bufangNotice set ShippingVolume='%1',ReceiptVolume='%1',ActualProductionVolume='%1' where RecordNumber=%2").arg(QString::number(bufang),threeRecordNum);
                db.sql_exec(updateSQL);
            }
            /*********************************************************************************/
        }

        on_newAction3();
        db.showview(SQL3,threeview,&threemodel);
        setModelStyle3(threemodel);
        sockClient->send_Msg3();
        QMessageBox::information(this,tr("提示信息"),tr("保存毛重成功"),0,0,0);
        return;
    }
}

void guobangrukuDlg::on_chengpizhong3()
{
    int netWeight = threeGrossWeightLineEdit->text().toInt() - threeTareWeightLineEdit->text().toInt();
    double volum = (double)netWeight/threeUnitWeightLineEdit->text().toDouble();
    threeNetWeightLineEdit->setText(QString::number(netWeight));
    threeVolumeLineEdit->setText(QString::number(volum,'f',1));
}

void guobangrukuDlg::on_baocunpizhong3()
{
    if(threeTareWeightLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请称皮重"),0,0,0);
        return;
    }

    QString updateSQL = QString("update TankWeighing set ,Remarks='%5' where RecordNumber='%6'")
            .arg(threeTareWeightLineEdit->text(),threeTareWeightTimeLineEdit->text(),threeNetWeightLineEdit->text(),threeVolumeLineEdit->text(),threeRemarksLineEdit->text(),threeRecordNoLineEdit->text());
    int res = db.sql_exec(updateSQL);
    if(res == 0){
        on_newAction3();
        db.showview(SQL3,threeview,&threemodel);
        setModelStyle3(threemodel);
        QMessageBox::information(this,tr("提示信息"),tr("保存皮重成功"),0,0,0);
        return;
    }
}

void guobangrukuDlg::on_dakaichuankou()
{
    serial->setPortName(fivecombo1->currentText());  //设置串口名
    if(serial->open(QIODevice::ReadOnly))//打开串口
    {
        //QMessageBox::information(this,tr("提示信息"),tr("串口打开成功"),0,0,0);
        fivecombo1->setEnabled(false);
        fivecombo2->setEnabled(false);
        fivecombo3->setEnabled(false);
        fivecombo4->setEnabled(false);
        fivecombo5->setEnabled(false);
        fivelineEdit6->setEnabled(false);
        fivelineEdit7->setEnabled(false);

        pub.save_SerialNumber(fivecombo1->currentIndex());
        pub.save_BaudRate(fivecombo2->currentIndex());
        pub.save_DataBits(fivecombo3->currentIndex());
        pub.save_StopBit(fivecombo4->currentIndex());
        pub.save_ParityCorrection(fivecombo5->currentIndex());
        pub.save_StartBit(fivelineEdit6->text().toInt());
        pub.save_InterceptDigit(fivelineEdit7->text().toInt());

        dakaichuankou->setHidden(true);
        guanbichuankou->setHidden(false);

        serial->setBaudRate(fivecombo2->currentText().toInt());  //设置波特率

        //设置数据位数
        if(fivecombo3->currentText().toInt() == 5){
            serial->setDataBits(QSerialPort::Data5);
        }
        else if(fivecombo3->currentText().toInt() == 6){
            serial->setDataBits(QSerialPort::Data6);
        }
        else if(fivecombo3->currentText().toInt() == 7){
            serial->setDataBits(QSerialPort::Data7);
        }
        else if(fivecombo3->currentText().toInt() == 8){
            serial->setDataBits(QSerialPort::Data8);
        }

        //设置停止位
        if(fivecombo4->currentText() == "One"){
            serial->setStopBits(QSerialPort::OneStop);
        }
        else if(fivecombo4->currentText() == "Two"){
            serial->setStopBits(QSerialPort::TwoStop);
        }
        else if(fivecombo4->currentText() == "OnePointFive"){
            serial->setStopBits(QSerialPort::OneAndHalfStop);
        }

        //设置奇偶校验
        if(fivecombo5->currentText() == "None"){
            serial->setParity(QSerialPort::NoParity);
        }
        else if(fivecombo5->currentText() == "Odd"){
            serial->setParity(QSerialPort::OddParity);
        }
        else if(fivecombo5->currentText() == "Even"){
            serial->setParity(QSerialPort::EvenParity);
        }
        else if(fivecombo5->currentText() == "Mark"){
            serial->setParity(QSerialPort::MarkParity);
        }
        else if(fivecombo5->currentText() == "Space"){
            serial->setParity(QSerialPort::SpaceParity);
        }

        serial->setFlowControl(QSerialPort::HardwareControl);//设置流控制
        connect(serial,SIGNAL(readyRead()),this,SLOT(appendBuffer()));
    }
}

void guobangrukuDlg::on_guanbichuankou()
{
    disconnect(serial,SIGNAL(readyRead()),this,SLOT(appendBuffer()));
    serial->close();
    fivecombo1->setEnabled(true);
    fivecombo2->setEnabled(true);
    fivecombo3->setEnabled(true);
    fivecombo4->setEnabled(true);
    fivecombo5->setEnabled(true);
    fivelineEdit6->setEnabled(true);
    fivelineEdit7->setEnabled(true);
    guanbichuankou->setHidden(true);
    dakaichuankou->setHidden(false);
}

void guobangrukuDlg::on_threeLicensePlateCombox()
{
    QString searchSQL = QString("select FaHuoCustomer,Engineering,StrengthGrade,Driver,Capacity,Unit,RecordNumber,ReceiptVolume,ActualProductionVolume,ShippingVolume from \
                                ProductionNotice WHERE DeliveryVehicle='%1' ORDER BY RecordNumber DESC LIMIT 0,1;").arg(threeLicensePlateCombox->currentText());
    QStringList resultStrList = db.CreatStrList(searchSQL);
    if(resultStrList.count() < 10){
        return;
    }

    threeCustomerNameLineEdit->setText(resultStrList.at(0));
    threeEngineerLineEdit->setText(resultStrList.at(1));
    threeEngineerLineEdit->setToolTip(threeEngineerLineEdit->text());
    threeStrengthGradeLineEdit->setText(resultStrList.at(2));
    threeDriverLineEdit->setText(resultStrList.at(3));
    threeUnitWeightLineEdit->setText(resultStrList.at(4));
    threeUnit = resultStrList.at(5);
    threeRecordNum = resultStrList.at(6);
    threeReceiptVolume = resultStrList.at(7);
    threeActualProductionVolume = resultStrList.at(8);
    threeShippingVolume = resultStrList.at(9);

    QString searchTare = QString("select SetTheTare from ConcreteVehicleInformation where Vehiclenumber='%1';").arg(threeLicensePlateCombox->currentText());
    threeTareWeightLineEdit->setText(db.sql_fetchrow_plus(searchTare,0));
    threeTareWeightTimeLineEdit->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm"));

    on_chengpizhong3();
}

void guobangrukuDlg::appendBuffer()
{
    if(buffer.count()>30){
        read_data();
        buffer.clear();
    }
    buffer.append(serial->readAll());
}

int guobangrukuDlg::read_data()
{
    QString numbuffer = buffer.section("+",1,1);
    int start = fivelineEdit6->text().toInt();
    int numcount = fivelineEdit7->text().toInt();
    QString num1 = numbuffer.mid(start,numcount);
    int num = num1.toInt();

    LCDnumber->display(num);
    threeLCDnumber->display(num);

    return num;
}

void guobangrukuDlg::on_fiveUpdateBtn()
{
    pub.save_DVR_IP(DVRIPLineEdit->text());
    pub.save_IPC1(IPC1LineEdit->text().toInt());
    pub.save_IPC2(IPC2LineEdit->text().toInt());
    pub.save_IPC3(IPC3LineEdit->text().toInt());
}
