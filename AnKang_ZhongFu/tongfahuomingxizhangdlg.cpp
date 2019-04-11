#include "tongfahuomingxizhangdlg.h"

extern mymysql db;
extern QString userName;

tongfahuomingxizhangDlg::tongfahuomingxizhangDlg(QWidget *parent) :
    QDialog(parent)
{
    tabWidget = new QTabWidget(this);
    tongfahuomingxi = new QWidget(this);
    duizhang = new QWidget(this);
    duizhangjilu = new QWidget(this);

    CreateTongfahuomingxi();
    CreateDuizhang();
    CreateDuizhangJiLu();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tabWidget);
    layout->setSpacing(0);
}

//tongfahuomingxizhangDlg::~tongfahuomingxizhangDlg()
//{
//    delete DetailModel;
//}

void tongfahuomingxizhangDlg::CreateTongfahuomingxi()
{
    DetailSQL = QString("select RecordNumber 发货单号,Customer 客户名称,Engineering 工程名称,StrengthGrade 砼等级,PouringMethod 浇筑方法,PouringPosition 浇筑部位,ReceiptVolume 签收方量,ROUND(B.ProductVolume,1) 机组生产方量,\
                        Price 砼单价,ReceiptVolume*Price 本车价格,OutboundTime 发货时间,DeliveryVehicle 送货车辆,Driver 司机,CumulativeNumber 累计车次,CumulativeVolume 累计方量,A.Unit 生产机组,Flag 核对标志 from \
                        ProductionNotice A LEFT JOIN (SELECT *,sum(SUMPS) ProductVolume FROM HISTDATA group by bsqk) B ON (A.RecordNumber=B.bsqk) limit 0");

    ViewToExcel = new myExcel(this);

    QLabel *TimeLabel = new QLabel(tr("发货时间"),this);
    TimeLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *FuHaoLabel = new QLabel(tr("--"),this);
    FuHaoLabel->setAlignment(Qt::AlignCenter);

    DateTimeEdit1 = new QDateTimeEdit(this);
    DateTimeEdit1->setDate(QDate::currentDate().addDays(-1));
    DateTimeEdit1->setCalendarPopup(true);
    DateTimeEdit2 = new QDateTimeEdit(this);
    DateTimeEdit2->setDate(QDate::currentDate());
    DateTimeEdit2->setCalendarPopup(true);

    CustomerCheck = new QCheckBox(tr("客户名称"),this);
    EngineerCheck = new QCheckBox(tr("工程名称"),this);

    CustomerCombox = new myComboBox(this);
    db.sql_fillComboBoxItem("select Customer from ProductionNotice group by Customer",CustomerCombox);
    EngineerCombox = new myComboBox(this);
    db.sql_fillComboBoxItem("select Engineering from ProductionNotice group by Engineering",EngineerCombox);

    FindBtn = new QPushButton(tr("查找"),this);
    FindBtn->setFixedWidth(120);
    connect(FindBtn,SIGNAL(clicked()),this,SLOT(on_FindBtn()));

    ExportBtn = new QPushButton(tr("导出"),this);
    ExportBtn->setFixedWidth(120);
    connect(ExportBtn,SIGNAL(clicked()),this,SLOT(on_ExportBtn()));


    DetailView = new QTableView(this);
    db.showview(DetailSQL.toStdString().data(),DetailView,&DetailModel);
    connect(DetailView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(on_doubleClickDetailView(QModelIndex)));
    DetailView->setColumnWidth(8,150);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(TimeLabel,0);
    hlayout->addWidget(DateTimeEdit1,0);
    hlayout->addWidget(FuHaoLabel,0);
    hlayout->addWidget(DateTimeEdit2,0);
    hlayout->addWidget(CustomerCheck,0);
    hlayout->addWidget(CustomerCombox,1);
    hlayout->addWidget(EngineerCheck,0);
    hlayout->addWidget(EngineerCombox,1);
    hlayout->addWidget(FindBtn,1);
    hlayout->addWidget(ExportBtn,1);
    hlayout->addStretch(2);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addLayout(hlayout);
    layout->addWidget(DetailView);

    tongfahuomingxi->setLayout(layout);
    tabWidget->addTab(tongfahuomingxi,tr("砼发货明细"));
}

void tongfahuomingxizhangDlg::CreateDuizhang()
{
    QLabel *RecordNoLabel = new QLabel(tr("出车单号"),this);
    RecordNoLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    QLabel *TaskListLabel = new QLabel(tr("任务单号"),this);
    TaskListLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    QLabel *RealCustomerLabel = new QLabel(tr("实际客户"),this);
    RealCustomerLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    QLabel *DeliverCustomerLabel = new QLabel(tr("发货客户"),this);
    DeliverCustomerLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    QLabel *EngineerNameLabel = new QLabel(tr("工程地点"),this);
    EngineerNameLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    QLabel *PlannedQuantityLabel = new QLabel(tr("计划方量"),this);
    PlannedQuantityLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    QLabel *OutboundTimeLabel = new QLabel(tr("出站时间"),this);
    OutboundTimeLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    QLabel *ContractNumberLabel = new QLabel(tr("合同编号"),this);
    ContractNumberLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    QLabel *ShippingVolumeLabel = new QLabel(tr("发货方量"),this);
    ShippingVolumeLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    ShippingVolumeLabel->setStyleSheet("color:red");

    QLabel *ReceiptVolumeLabel = new QLabel(tr("签收方量"),this);
    ReceiptVolumeLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    ReceiptVolumeLabel->setStyleSheet("color:red");

    QLabel *ProductVolumeLabel = new QLabel(tr("生产方量"),this);
    ProductVolumeLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    QLabel *CumulativeNumberLabel = new QLabel(tr("累计车次"),this);
    CumulativeNumberLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    CumulativeNumberLabel->setStyleSheet("color:red");

    QLabel *CumulativeVolumeLabel = new QLabel(tr("累计方量"),this);
    CumulativeVolumeLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    CumulativeVolumeLabel->setStyleSheet("color:red");

    QLabel *RemainingMaterialLabel = new QLabel(tr("剩料方量"),this);
    RemainingMaterialLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    QLabel *PriceLabel = new QLabel(tr("混凝土单价"),this);
    PriceLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    PriceLabel->setStyleSheet("color:red");

    QLabel *StrengthGradeLabel = new QLabel(tr("强度等级"),this);
    StrengthGradeLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    QLabel *PouringMethodLabel = new QLabel(tr("浇筑方式"),this);
    PouringMethodLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    PouringMethodLabel->setStyleSheet("color:red");

    QLabel *UnitNoLabel = new QLabel(tr("机组编号"),this);
    UnitNoLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    QLabel *VehicleLabel = new QLabel(tr("车牌号"),this);
    VehicleLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    VehicleLabel->setStyleSheet("color:red");

    QLabel *DriverLabel = new QLabel(tr("司机"),this);
    DriverLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    DriverLabel->setStyleSheet("color:red");

    QLabel *DistanceLabel = new QLabel(tr("运距"),this);
    DistanceLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    DistanceLabel->setStyleSheet("color:red");

    QLabel *FreightPriceLabel = new QLabel(tr("运费价格"),this);
    FreightPriceLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    FreightPriceLabel->setStyleSheet("color:red");

    QLabel *PhbUnitWeightLabel = new QLabel(tr("配比容重"),this);
    PhbUnitWeightLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    QLabel *RealUnitWeightLabel = new QLabel(tr("实际容重"),this);
    RealUnitWeightLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    QLabel *chedanmingxishuomingLabel = new QLabel(tr("(双击车单明细，在出车单和消耗明细中查看当前车单的详细信息)"),this);
    chedanmingxishuomingLabel->setStyleSheet("color:red");
    chedanmingxishuomingLabel->setAlignment(Qt::AlignLeft);

    TaskListLineEdit = new QLineEdit(this);
    TaskListLineEdit->setReadOnly(true);
    RecordNoLineEdit = new QLineEdit(this);
    RecordNoLineEdit->setReadOnly(true);
    RealCustomerLineEdit = new QLineEdit(this);
    RealCustomerLineEdit->setReadOnly(true);
    DeliverCustomerLineEdit = new QLineEdit(this);
    DeliverCustomerLineEdit->setReadOnly(true);
    EngineerNameLineEdit = new QLineEdit(this);
    EngineerNameLineEdit->setReadOnly(true);
    PlannedQuantityLineEdit = new QLineEdit(this);
    PlannedQuantityLineEdit->setReadOnly(true);
    OutboundTimeLineEdit = new QLineEdit(this);
    OutboundTimeLineEdit->setReadOnly(true);
    ContractNumberLineEdit = new QLineEdit(this);
    ContractNumberLineEdit->setReadOnly(true);
    ShippingVolumeLineEdit = new QLineEdit(this);

    ReceiptVolumeLineEdit = new QLineEdit(this);

    ProductVolumeLineEdit = new QLineEdit(this);
    ProductVolumeLineEdit->setReadOnly(true);
    CumulativeNumberLineEdit = new QLineEdit(this);

    CumulativeVolumeLineEdit = new QLineEdit(this);

    RemainingMaterialLineEdit = new QLineEdit(this);
    RemainingMaterialLineEdit->setReadOnly(true);
    PriceLineEdit = new QLineEdit(this);

    StrengthGradeLineEdit = new QLineEdit(this);
    StrengthGradeLineEdit->setReadOnly(true);


    UnitNoLineEdit = new QLineEdit(this);
    UnitNoLineEdit->setReadOnly(true);

    VehicleLineEdit = new QLineEdit(this);
    DriverLineEdit = new QLineEdit(this);

    DistanceLineEdit = new QLineEdit(this);

    FreightPriceLineEdit = new QLineEdit(this);

    PhbUnitWeightLineEdit = new QLineEdit(this);
    PhbUnitWeightLineEdit->setReadOnly(true);
    RealUnitWeightLineEdit = new QLineEdit(this);
    RealUnitWeightLineEdit->setReadOnly(true);

    PouringMethodCombox = new QComboBox(this);
    db.sql_fillComboBoxItem("select PouringMethod from PouringMethod",PouringMethodCombox);

    AllConfirmBtn = new QPushButton(tr("批量核对"),this);
    AllConfirmBtn->setFixedWidth(120);
    connect(AllConfirmBtn,SIGNAL(clicked()),this,SLOT(on_AllConfirmBtn()));

    ConfirmBtn = new QPushButton(tr("单车核对"),this);
    ConfirmBtn->setFixedWidth(120);
    connect(ConfirmBtn,SIGNAL(clicked()),this,SLOT(on_ConfirmBtn()));

    CancelBtn = new QPushButton(tr("取消核对"),this);
    CancelBtn->setFixedWidth(120);
    connect(CancelBtn,SIGNAL(clicked()),this,SLOT(on_CancelBtn()));

    twoAllSelectedBtn = new QPushButton(tr("全选"),this);
    twoAllSelectedBtn->setFixedWidth(120);
    connect(twoAllSelectedBtn,SIGNAL(clicked()),this,SLOT(on_twoAllSelectedBtn()));

    twoAllCancelBtn = new QPushButton(tr("取消"),this);
    twoAllCancelBtn->setFixedWidth(120);
    connect(twoAllCancelBtn,SIGNAL(clicked()),this,SLOT(on_twoAllCancelBtn()));

    QHBoxLayout *BtnLayout = new QHBoxLayout;
    BtnLayout->addWidget(ConfirmBtn,1);
    BtnLayout->addWidget(CancelBtn,1);

    QHBoxLayout *BtnLayout2 = new QHBoxLayout;
    BtnLayout2->addStretch(1);
    BtnLayout2->addWidget(AllConfirmBtn,1);
    BtnLayout2->addWidget(twoAllSelectedBtn,1);
    BtnLayout2->addWidget(twoAllCancelBtn,1);

    ConsumeView = new QTableView(this);

    ProductNoticeView = new QTableView(this);
    ProductNoticeView->setItemDelegate(new myCheckBoxDelegate(5,this));
    ProductNoticeView->sortByColumn(0,Qt::AscendingOrder);
    connect(ProductNoticeView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(on_doubleClickProductNoticeView(QModelIndex)));

    QGridLayout *DetailInfoLayout = new QGridLayout;
    DetailInfoLayout->addWidget(RecordNoLabel,0,0);
    DetailInfoLayout->addWidget(RecordNoLineEdit,0,1);
    DetailInfoLayout->addWidget(TaskListLabel,1,0);
    DetailInfoLayout->addWidget(TaskListLineEdit,1,1);
    DetailInfoLayout->addWidget(ContractNumberLabel,2,0);
    DetailInfoLayout->addWidget(ContractNumberLineEdit,2,1);
    DetailInfoLayout->addWidget(RealCustomerLabel,3,0);
    DetailInfoLayout->addWidget(RealCustomerLineEdit,3,1);
    DetailInfoLayout->addWidget(DeliverCustomerLabel,4,0);
    DetailInfoLayout->addWidget(DeliverCustomerLineEdit,4,1);
    DetailInfoLayout->addWidget(EngineerNameLabel,5,0);
    DetailInfoLayout->addWidget(EngineerNameLineEdit,5,1);
    DetailInfoLayout->addWidget(PlannedQuantityLabel,6,0);
    DetailInfoLayout->addWidget(PlannedQuantityLineEdit,6,1);
    DetailInfoLayout->addWidget(OutboundTimeLabel,7,0);
    DetailInfoLayout->addWidget(OutboundTimeLineEdit,7,1);
    DetailInfoLayout->addWidget(ShippingVolumeLabel,8,0);
    DetailInfoLayout->addWidget(ShippingVolumeLineEdit,8,1);
    DetailInfoLayout->addWidget(ReceiptVolumeLabel,9,0);
    DetailInfoLayout->addWidget(ReceiptVolumeLineEdit,9,1);
    DetailInfoLayout->addWidget(ProductVolumeLabel,10,0);
    DetailInfoLayout->addWidget(ProductVolumeLineEdit,10,1);
    DetailInfoLayout->addWidget(RemainingMaterialLabel,11,0);
    DetailInfoLayout->addWidget(RemainingMaterialLineEdit,11,1);
    DetailInfoLayout->addWidget(CumulativeNumberLabel,12,0);
    DetailInfoLayout->addWidget(CumulativeNumberLineEdit,12,1);
    DetailInfoLayout->addWidget(CumulativeVolumeLabel,13,0);
    DetailInfoLayout->addWidget(CumulativeVolumeLineEdit,13,1);
    DetailInfoLayout->addWidget(PriceLabel,14,0);
    DetailInfoLayout->addWidget(PriceLineEdit,14,1);
    DetailInfoLayout->addWidget(StrengthGradeLabel,16,0);
    DetailInfoLayout->addWidget(StrengthGradeLineEdit,16,1);
    DetailInfoLayout->addWidget(PouringMethodLabel,17,0);
    DetailInfoLayout->addWidget(PouringMethodCombox,17,1);
    DetailInfoLayout->addWidget(UnitNoLabel,18,0);
    DetailInfoLayout->addWidget(UnitNoLineEdit,18,1);
    DetailInfoLayout->addWidget(VehicleLabel,19,0);
    DetailInfoLayout->addWidget(VehicleLineEdit,19,1);
    DetailInfoLayout->addWidget(DriverLabel,20,0);
    DetailInfoLayout->addWidget(DriverLineEdit,20,1);
    DetailInfoLayout->addWidget(DistanceLabel,21,0);
    DetailInfoLayout->addWidget(DistanceLineEdit,21,1);
    DetailInfoLayout->addWidget(FreightPriceLabel,22,0);
    DetailInfoLayout->addWidget(FreightPriceLineEdit,22,1);
    DetailInfoLayout->addWidget(PhbUnitWeightLabel,23,0);
    DetailInfoLayout->addWidget(PhbUnitWeightLineEdit,23,1);
    DetailInfoLayout->addWidget(RealUnitWeightLabel,24,0);
    DetailInfoLayout->addWidget(RealUnitWeightLineEdit,24,1);
    DetailInfoLayout->addLayout(BtnLayout,25,1,Qt::AlignBottom|Qt::AlignRight);
    DetailInfoLayout->setColumnStretch(0,0);
    DetailInfoLayout->setColumnStretch(1,1);

    QVBoxLayout *ConsumeLayout = new QVBoxLayout;
    ConsumeLayout->addWidget(ConsumeView);

    QVBoxLayout *ProductNoticeLayout = new QVBoxLayout;
    ProductNoticeLayout->addWidget(chedanmingxishuomingLabel);
    ProductNoticeLayout->addWidget(ProductNoticeView);
    ProductNoticeLayout->addLayout(BtnLayout2);

    QGroupBox *DetailInfoGroupbox = new QGroupBox(this);
    DetailInfoGroupbox->setTitle("出车单");
    DetailInfoGroupbox->setLayout(DetailInfoLayout);

    QGroupBox *ConsumeGroupbox = new QGroupBox(this);
    ConsumeGroupbox->setTitle("消耗明细");
    ConsumeGroupbox->setFixedWidth(250);
    ConsumeGroupbox->setLayout(ConsumeLayout);

    QGroupBox *ProductNoticeListGroupbox = new QGroupBox(this);
    ProductNoticeListGroupbox->setTitle("车单明细");
    ProductNoticeListGroupbox->setFixedWidth(540);
    ProductNoticeListGroupbox->setLayout(ProductNoticeLayout);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(DetailInfoGroupbox);
    layout->addWidget(ConsumeGroupbox);
    layout->addWidget(ProductNoticeListGroupbox);

    duizhang->setLayout(layout);
    tabWidget->addTab(duizhang,tr("砼发货核对"));
}

void tongfahuomingxizhangDlg::CreateDuizhangJiLu()
{
    SQL3 = "SELECT RecordNo 出车单号,updateContent 修改内容,Operator 核对人,OperatorTime 核对时间 FROM ReconciliationRecord limit 0";

    QLabel *updateTimeLabel = new QLabel(tr("修改时间"),this);
    updateTimeLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *FuHaoLabel = new QLabel(tr("--"),this);
    FuHaoLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    updateTime1 = new QDateTimeEdit(this);
    updateTime1->setDate(QDate::currentDate());
    updateTime1->setCalendarPopup(true);

    updateTime2 = new QDateTimeEdit(this);
    updateTime2->setDate(QDate::currentDate().addDays(+1));
    updateTime2->setCalendarPopup(true);

    threeFindBtn = new QPushButton(tr("查询"),this);
    threeFindBtn->setFixedWidth(120);
    connect(threeFindBtn,SIGNAL(clicked()),this,SLOT(on_threeFindBtn()));

    ReconciliationView = new QTableView(this);
    db.showview(SQL3,ReconciliationView,&ReconciliationModel);
    ReconciliationView->setColumnWidth(1,300);
    ReconciliationView->setColumnWidth(3,130);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(updateTimeLabel,0);
    hlayout->addWidget(updateTime1,1);
    hlayout->addWidget(FuHaoLabel,0);
    hlayout->addWidget(updateTime2,1);
    hlayout->addWidget(threeFindBtn,1);
    hlayout->addStretch(3);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addLayout(hlayout);
    layout->addWidget(ReconciliationView);

    duizhangjilu->setLayout(layout);
    tabWidget->addTab(duizhangjilu,tr("核对记录查询"));
}

void tongfahuomingxizhangDlg::on_FindBtn()
{
    QString Customer,Engineer;
    if(CustomerCheck->checkState() == 2){
        Customer = QString(" and Customer='%1'").arg(CustomerCombox->currentText());
    }
    if(EngineerCheck->checkState() == 2){
        Engineer = QString(" and Engineering='%1'").arg(EngineerCombox->currentText());
    }

    QString searchSQL = QString("select RecordNumber 发货单号,Customer 客户名称,Engineering 工程名称,StrengthGrade 砼等级,PouringMethod 浇筑方法,PouringPosition 浇筑部位,ReceiptVolume 签收方量,ROUND(B.ProductVolume,1) 机组生产方量,\
                                Price 砼单价,ReceiptVolume*Price 本车价格,OutboundTime 发货时间,DeliveryVehicle 送货车辆,Driver 司机,CumulativeNumber 累计车次,\
                                CumulativeVolume 累计方量,A.Unit 生产机组,Flag 核对标志 from ProductionNotice A LEFT JOIN (SELECT *,sum(SUMPS) ProductVolume FROM HISTDATA group by bsqk) B ON (A.RecordNumber=B.bsqk) where OutboundTime between '%1' and '%2' %3 %4 \
                                order by Customer,Engineering,StrengthGrade,PouringMethod,PouringPosition,OutboundTime")
                    .arg(DateTimeEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),DateTimeEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),Customer,Engineer);
    db.showview(searchSQL.toStdString().data(),DetailView,&DetailModel);
    setModelStyle(DetailModel,16);
}

void tongfahuomingxizhangDlg::on_ExportBtn()
{
    ViewToExcel->Table2ExcelByHtml(DetailView,QString("发货明细账"));
}

void tongfahuomingxizhangDlg::on_doubleClickDetailView(QModelIndex index)
{
    QString chuchedanhao = QString("Select Customer,FaHuoCustomer,Engineering,ShippingVolume,RemainingMaterial,StrengthGrade,PouringMethod,Unit,Driver\
                                   ,Mileage,FreightPrice,OutboundTime,ContractNumber,Price,TaskList,CumulativeNumber,CumulativeVolume,ReceiptVolume,Capacity,DeliveryVehicle from ProductionNotice \
                                   where RecordNumber = %1").arg(index.model()->index(index.row(),0).data().toString());
qDebug()<<chuchedanhao;
    QStringList resultStrList = db.CreatStrList(chuchedanhao);
    if(resultStrList.count()<19){
        return;
    }

    RecordNoLineEdit->setText(index.model()->index(index.row(),0).data().toString());
    RealCustomerLineEdit->setText(resultStrList.at(0));
    DeliverCustomerLineEdit->setText(resultStrList.at(1));
    EngineerNameLineEdit->setText(resultStrList.at(2));
    ShippingVolumeLineEdit->setText(resultStrList.at(3));
    RemainingMaterialLineEdit->setText(resultStrList.at(4));
    StrengthGradeLineEdit->setText(resultStrList.at(5));
    PouringMethodCombox->setCurrentText(resultStrList.at(6));
    UnitNoLineEdit->setText(resultStrList.at(7));
    DriverLineEdit->setText(resultStrList.at(8));
    DistanceLineEdit->setText(resultStrList.at(9));
    FreightPriceLineEdit->setText(resultStrList.at(10));
    OutboundTimeLineEdit->setText(resultStrList.at(11));
    ContractNumberLineEdit->setText(resultStrList.at(12));
    PriceLineEdit->setText(resultStrList.at(13));
    TaskListLineEdit->setText(resultStrList.at(14));
    CumulativeNumberLineEdit->setText(resultStrList.at(15));
    CumulativeVolumeLineEdit->setText(resultStrList.at(16));
    ReceiptVolumeLineEdit->setText(resultStrList.at(17));
    PhbUnitWeightLineEdit->setText(resultStrList.at(18));
    VehicleLineEdit->setText(resultStrList.at(19));
    ProductVolumeLineEdit->setText(index.model()->index(index.row(),7).data().toString());

    QString searchPlannedQuantity = QString("Select PlannedQuantity from ProductionTaskList where TaskNumber = %1").arg(resultStrList.at(14));
    PlannedQuantityLineEdit->setText(db.sql_fetchrow_plus(searchPlannedQuantity.toStdString().data(),0));

    //消耗表
    QString fillConsumeViewSQL = QString("Select MATNAME 原料名称,ROUND(SUM(SJMAT),2) 原料消耗 from HISTDATA2 where recordNo = '%1' GROUP BY MATNAME").arg(index.model()->index(index.row(),0).data().toString());
    db.showview(fillConsumeViewSQL.toStdString().data(),ConsumeView,&ConsumeModel);

    //车单明细
    QString fillProductNoticeViewSQL = QString("select RecordNumber 出车单号,ReceiptVolume 本车方量,CumulativeNumber 累计车次,CumulativeVolume 累计方量,OutboundTime 出站时间,0 选中标志,Flag 核对标志 from ProductionNotice where TaskList='%1' and OutboundTime >= '%2' and OutboundTime <='%3' order by RecordNumber+0").arg(resultStrList.at(14)).arg(DateTimeEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(DateTimeEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
    db.showview_num(fillProductNoticeViewSQL.toStdString().data(),ProductNoticeView,&ProductNoticeModel,0);
    setProductNoticeViewModelStyle(ProductNoticeModel);
    ProductNoticeView->setColumnWidth(0,65);
    ProductNoticeView->setColumnWidth(1,65);
    ProductNoticeView->setColumnWidth(2,65);
    ProductNoticeView->setColumnWidth(3,65);
    ProductNoticeView->setColumnWidth(4,130);
    ProductNoticeView->setColumnWidth(5,65);
    ProductNoticeView->setColumnWidth(6,65);
    ProductNoticeView->setColumnHidden(6,true);

    double UnitWeight = 0;
    for(int i = 0; i<ConsumeModel->rowCount(); i++){
        UnitWeight += ConsumeModel->item(i,1)->text().toDouble();
    }
    UnitWeight = UnitWeight/ProductVolumeLineEdit->text().toDouble();
    RealUnitWeightLineEdit->setText(QString::number(UnitWeight,'f',2));

    tabWidget->setCurrentIndex(1);
}

void tongfahuomingxizhangDlg::on_doubleClickProductNoticeView(QModelIndex index)
{
    QString chuchedanhao = QString("Select Customer,FaHuoCustomer,Engineering,ShippingVolume,RemainingMaterial,StrengthGrade,PouringMethod,Unit,Driver\
                                   ,Mileage,FreightPrice,OutboundTime,ContractNumber,Price,TaskList,CumulativeNumber,CumulativeVolume,ReceiptVolume,Capacity,DeliveryVehicle from ProductionNotice \
                                   where RecordNumber = %1").arg(index.model()->index(index.row(),0).data().toString());
    QStringList resultStrList = db.CreatStrList(chuchedanhao);
    if(resultStrList.count()<19){
        return;
    }

    RecordNoLineEdit->setText(index.model()->index(index.row(),0).data().toString());
    RealCustomerLineEdit->setText(resultStrList.at(0));
    DeliverCustomerLineEdit->setText(resultStrList.at(1));
    EngineerNameLineEdit->setText(resultStrList.at(2));
    ShippingVolumeLineEdit->setText(resultStrList.at(3));
    RemainingMaterialLineEdit->setText(resultStrList.at(4));
    StrengthGradeLineEdit->setText(resultStrList.at(5));
    PouringMethodCombox->setCurrentText(resultStrList.at(6));
    UnitNoLineEdit->setText(resultStrList.at(7));
    DriverLineEdit->setText(resultStrList.at(8));
    DistanceLineEdit->setText(resultStrList.at(9));
    FreightPriceLineEdit->setText(resultStrList.at(10));
    OutboundTimeLineEdit->setText(resultStrList.at(11));
    ContractNumberLineEdit->setText(resultStrList.at(12));
    PriceLineEdit->setText(resultStrList.at(13));
    TaskListLineEdit->setText(resultStrList.at(14));
    CumulativeNumberLineEdit->setText(resultStrList.at(15));
    CumulativeVolumeLineEdit->setText(resultStrList.at(16));
    ReceiptVolumeLineEdit->setText(resultStrList.at(17));
    PhbUnitWeightLineEdit->setText(resultStrList.at(18));
    VehicleLineEdit->setText(resultStrList.at(19));

    QString searchPlannedQuantity = QString("Select PlannedQuantity from ProductionTaskList where TaskNumber = %1").arg(resultStrList.at(14));
    PlannedQuantityLineEdit->setText(db.sql_fetchrow_plus(searchPlannedQuantity.toStdString().data(),0));

    //消耗表
    QString fillConsumeViewSQL = QString("Select MATNAME 原料名称,ROUND(SUM(SJMAT),2) 原料消耗 from HISTDATA2 where recordNo = '%1' GROUP BY MATNAME").arg(index.model()->index(index.row(),0).data().toString());
    db.showview(fillConsumeViewSQL.toStdString().data(),ConsumeView,&ConsumeModel);

    setProductNoticeViewModelStyle(ProductNoticeModel);

    QString searchProductVolume = QString("select round(SUM(SUMPS),1) from HISTDATA where bsqk='%1' GROUP BY bsqk").arg(index.model()->index(index.row(),0).data().toString());
    ProductVolumeLineEdit->setText(db.sql_fetchrow_plus(searchProductVolume.toStdString().data(),0));

    double UnitWeight = 0;
    for(int i = 0; i<ConsumeModel->rowCount(); i++){
        UnitWeight += ConsumeModel->item(i,1)->text().toDouble();
    }
    UnitWeight = UnitWeight/ProductVolumeLineEdit->text().toDouble();
    RealUnitWeightLineEdit->setText(QString::number(UnitWeight,'f',2));
}

void tongfahuomingxizhangDlg::on_AllConfirmBtn()
{
    QString RecordNoList;
    int rowCount = ProductNoticeModel->rowCount();
    for(int i=0; i<rowCount; i++){
        if(ProductNoticeModel->item(i,5)->checkState() == 2){
            RecordNoList.append(QString("%1,").arg(ProductNoticeModel->item(i,0)->text()));
        }
    }
    RecordNoList = RecordNoList.left(RecordNoList.length()-1);

    QString updateSQL = QString("update ProductionNotice set Flag='0' where RecordNumber in (%1)").arg(RecordNoList);
    int res = db.sql_exec(updateSQL);
    if(res == 0){
        on_FindBtn();
        tabWidget->setCurrentIndex(0);
    }

    QString insertReconciliationRecord = QString("insert into ReconciliationRecord (RecordNo,updateContent,Operator,OperatorTime) values ('%1','%2','%3','%4')")
            .arg(RecordNoLineEdit->text(),RecordNoList,userName,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    db.sql_exec(insertReconciliationRecord.toStdString().data());
}

void tongfahuomingxizhangDlg::on_ConfirmBtn()
{
    QString searchDetailInfoSQL = QString("Select ShippingVolume,ReceiptVolume,CumulativeNumber,CumulativeVolume,Price,PouringMethod,DeliveryVehicle,Driver,Mileage,\
                                          FreightPrice from ProductionNotice where RecordNumber = %1").arg(RecordNoLineEdit->text());
    QStringList resultStrList = db.CreatStrList(searchDetailInfoSQL);
    if(resultStrList.count()<10){
        return;
    }

    QString updateSQL = QString("update ProductionNotice set Flag='0',ShippingVolume='%1',ReceiptVolume='%2',CumulativeNumber='%3',CumulativeVolume='%4',Price='%5',\
                                PouringMethod='%6',DeliveryVehicle='%7',Driver='%8',Mileage='%9',FreightPrice='%10' where RecordNumber=%11")
            .arg(ShippingVolumeLineEdit->text(),ReceiptVolumeLineEdit->text(),CumulativeNumberLineEdit->text(),CumulativeVolumeLineEdit->text(),PriceLineEdit->text(),
                 PouringMethodCombox->currentText(),VehicleLineEdit->text(),DriverLineEdit->text(),DistanceLineEdit->text()).arg(FreightPriceLineEdit->text(),RecordNoLineEdit->text());
    db.sql_exec(updateSQL.toStdString().data());

    QString updateContent;
    if(resultStrList.at(0)!=ShippingVolumeLineEdit->text()){
        updateContent.append(" 发货方量：").append(resultStrList.at(0)).append("→").append(ShippingVolumeLineEdit->text());
    }
    if(resultStrList.at(1)!=ReceiptVolumeLineEdit->text()){
        updateContent.append(" 签收方量：").append(resultStrList.at(1)).append("→").append(ReceiptVolumeLineEdit->text());
    }
    if(resultStrList.at(2)!=CumulativeNumberLineEdit->text()){
        updateContent.append(" 累计车次：").append(resultStrList.at(2)).append("→").append(CumulativeNumberLineEdit->text());
    }
    if(resultStrList.at(3)!=CumulativeVolumeLineEdit->text()){
        updateContent.append(" 累计方量：").append(resultStrList.at(3)).append("→").append(CumulativeVolumeLineEdit->text());
    }
    if(resultStrList.at(4)!=PriceLineEdit->text()){
        updateContent.append(" 砼价格：").append(resultStrList.at(4)).append("→").append(PriceLineEdit->text());
    }
    if(resultStrList.at(5)!=PouringMethodCombox->currentText()){
        updateContent.append(" 浇筑方式：").append(resultStrList.at(5)).append("→").append(PouringMethodCombox->currentText());
    }
    if(resultStrList.at(6)!=VehicleLineEdit->text()){
        updateContent.append(" 车牌号：").append(resultStrList.at(6)).append("→").append(VehicleLineEdit->text());
    }
    if(resultStrList.at(7)!=DriverLineEdit->text()){
        updateContent.append(" 司机：").append(resultStrList.at(7)).append("→").append(DriverLineEdit->text());
    }
    if(resultStrList.at(8)!=DistanceLineEdit->text()){
        updateContent.append(" 运距：").append(resultStrList.at(8)).append("→").append(DistanceLineEdit->text());
    }
    if(resultStrList.at(9)!=FreightPriceLineEdit->text()){
        updateContent.append(" 运费：").append(resultStrList.at(9)).append("→").append(FreightPriceLineEdit->text());
    }

    QString insertReconciliationRecord = QString("insert into ReconciliationRecord (RecordNo,updateContent,Operator,OperatorTime) values ('%1','%2','%3','%4')")
            .arg(RecordNoLineEdit->text(),updateContent,userName,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    db.sql_exec(insertReconciliationRecord.toStdString().data());


    on_FindBtn();
    tabWidget->setCurrentIndex(0);
}

void tongfahuomingxizhangDlg::on_CancelBtn()
{
    QString updateSQL = QString("update ProductionNotice set Flag='2' where RecordNumber=%1").arg(RecordNoLineEdit->text());
    db.sql_exec(updateSQL.toStdString().data());

    on_FindBtn();
    tabWidget->setCurrentIndex(0);
}

void tongfahuomingxizhangDlg::on_twoAllSelectedBtn()
{
    QString searchSQL = QString("select RecordNumber 出车单号,ReceiptVolume 本车方量,CumulativeNumber 累计车次,CumulativeVolume 累计方量,OutboundTime 出站时间,\
                                2 选中标志,Flag 核对标志 from ProductionNotice where TaskList='%1' and OutboundTime >= '%2' and OutboundTime <='%3' order by RecordNumber+0").arg(TaskListLineEdit->text()).arg(DateTimeEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(DateTimeEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
    db.showview_num(searchSQL,ProductNoticeView,&ProductNoticeModel,0);
    setProductNoticeViewModelStyle(ProductNoticeModel);

    int rowCount = ProductNoticeModel->rowCount();
    for(int i = 0; i<rowCount; i++){
       ProductNoticeModel->item(i,5)->setCheckState(Qt::Checked);
    }
}

void tongfahuomingxizhangDlg::on_twoAllCancelBtn()
{
    QString searchSQL = QString("select RecordNumber 出车单号,ReceiptVolume 本车方量,CumulativeNumber 累计车次,CumulativeVolume 累计方量,OutboundTime 出站时间,\
                                0 选中标志,Flag 核对标志 from ProductionNotice where TaskList='%1' order by RecordNumber+0").arg(TaskListLineEdit->text());
    db.showview_num(searchSQL,ProductNoticeView,&ProductNoticeModel,0);
    setProductNoticeViewModelStyle(ProductNoticeModel);

    int rowCount = ProductNoticeModel->rowCount();
    for(int i = 0; i<rowCount; i++){
       ProductNoticeModel->item(i,5)->setCheckState(Qt::Unchecked);
    }
}

void tongfahuomingxizhangDlg::on_threeFindBtn()
{
    QString searchSQL = QString("SELECT RecordNo 出车单号,updateContent 修改内容,Operator 核对人,OperatorTime 核对时间 FROM ReconciliationRecord where OperatorTime between '%1' and '%2'")
            .arg(updateTime1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),updateTime2->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
    db.showview(searchSQL.toStdString().data(),ReconciliationView,&ReconciliationModel);
}

void tongfahuomingxizhangDlg::setModelStyle(QStandardItemModel *model,int column)
{
    int columnCount = model->columnCount();
    int rowCount    = model->rowCount();
    for(int i = 0; i < rowCount; i++){
        for(int j = 0; j < columnCount; j++){
            if(model->item(i,column)->text().toInt() == 2){
                model->item(i,j)->setBackground(QBrush(QColor(200,100,100)));//红
            }
            else if(model->item(i,column)->text().toInt() == 0){
                model->item(i,j)->setBackground(QBrush(QColor(255,255,255)));//白
            }
        }
    }
}

void tongfahuomingxizhangDlg::setProductNoticeViewModelStyle(QStandardItemModel *model)
{
    int columnCount = model->columnCount();
    int rowCount    = model->rowCount();
    for(int i = 0; i < rowCount; i++){
        for(int j = 0; j < columnCount; j++){
            if(model->item(i,0)->text() == RecordNoLineEdit->text()){
                model->item(i,j)->setBackground(QBrush(QColor(114,184,254)));//蓝
            }else if(model->item(i,6)->text().toInt() == 2){
                model->item(i,j)->setBackground(QBrush(QColor(200,100,100)));//红
            }else if(model->item(i,6)->text().toInt() == 0){
                model->item(i,j)->setBackground(QBrush(QColor(255,255,255)));//白
            }
        }
    }
}
