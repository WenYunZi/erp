#include "xiaoshouhetongguanlidlg.h"

extern mymysql db;
extern pubfunc pub;
extern QString userName;
extern myTCPsocket *sockClient;

xiaoshouhetongguanliDlg::xiaoshouhetongguanliDlg(QWidget *parent) :
    QDialog(parent)
{
    tabWidget = new QTabWidget(this);
    hetongkehuguanli = new QWidget(this);
    hetonggongchengguanli = new QWidget(this);
    ProductNoticePriceCorrectWidget = new QWidget(this);

    creatTabPage1();
    creatTabPage2();
    creatTabPage3();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tabWidget);
    layout->setSpacing(0);
}

void xiaoshouhetongguanliDlg::refresh()
{
    oneCustomerCombox->clear();
    const char *fillSQL1 = "select A.CustomerName from CustomerFiles A LEFT JOIN (SELECT CustomerName FROM SalesContractManagement) B ON (A.CustomerName=B.CustomerName) WHERE B.CustomerName IS NULL;";
    db.sql_fillComboBoxItem(fillSQL1,oneCustomerCombox);
}

void xiaoshouhetongguanliDlg::init_attributeWidget()
{
    twoAttributeWidget = new QWidget(this);
    attribute_count = 0;

    QString SQL = "select AttributeName,Price from ProductAttributes;";
    db.newCheckBoxAndLineEdit(SQL,twoAttributeCheckBoxList,twoAttributeLineEditList,&attribute_count,this);

    QGridLayout *twoAttributeLayout = new QGridLayout(this);
    twoAttributeLayout->setColumnStretch(0,0);
    twoAttributeLayout->setColumnStretch(1,1);
    twoAttributeLayout->setColumnStretch(2,0);
    twoAttributeLayout->setColumnStretch(3,1);
    twoAttributeLayout->setColumnStretch(4,0);
    twoAttributeLayout->setColumnStretch(5,1);
    twoAttributeLayout->setColumnStretch(6,0);
    twoAttributeLayout->setColumnStretch(7,1);
    twoAttributeLayout->setColumnStretch(8,0);
    twoAttributeLayout->setColumnStretch(9,1);

    twoAttributeLayout->setRowStretch(0,1);
    twoAttributeLayout->setRowStretch(1,1);
    twoAttributeLayout->setRowStretch(2,1);
    twoAttributeLayout->setRowStretch(3,1);
    twoAttributeLayout->setRowStretch(4,1);
    twoAttributeLayout->setRowStretch(5,1);
    twoAttributeLayout->setRowStretch(6,1);
    twoAttributeLayout->setRowStretch(7,1);
    twoAttributeLayout->setRowStretch(8,1);
    twoAttributeLayout->setRowStretch(9,1);
    twoAttributeLayout->setRowStretch(10,1);
    twoAttributeLayout->setRowStretch(11,1);

    int j = 0;
    for(int i = 0; i < attribute_count; i++){
        twoAttributeLayout->addWidget(twoAttributeCheckBoxList[i],j / 10,j % 10);
        twoAttributeLayout->addWidget(twoAttributeLineEditList[i],j / 10,j % 10 + 1,Qt::AlignLeft);
        j+=2;
    }
    twoAttributeWidget->setLayout(twoAttributeLayout);
}

void xiaoshouhetongguanliDlg::init_productWidget()
{
    twoProductWidget = new QWidget(this);
    product_count = 0;

    const char *chanpinSQL = "select ProductName,Price from ProductSetting;";
    db.newCheckBoxAndLineEdit(chanpinSQL,twoProductCheckBoxList,twoProductLineEditList,&product_count,this);

    QGridLayout *twoProductLayout = new QGridLayout(this);
    twoProductLayout->setColumnStretch(0,0);
    twoProductLayout->setColumnStretch(1,1);
    twoProductLayout->setColumnStretch(2,0);
    twoProductLayout->setColumnStretch(3,1);
    twoProductLayout->setColumnStretch(4,0);
    twoProductLayout->setColumnStretch(5,1);
    twoProductLayout->setColumnStretch(6,0);
    twoProductLayout->setColumnStretch(7,1);
    twoProductLayout->setColumnStretch(8,0);
    twoProductLayout->setColumnStretch(9,1);

    twoProductLayout->setRowStretch(0,1);
    twoProductLayout->setRowStretch(1,1);
    twoProductLayout->setRowStretch(2,1);
    twoProductLayout->setRowStretch(3,1);
    twoProductLayout->setRowStretch(4,1);
    twoProductLayout->setRowStretch(5,1);
    twoProductLayout->setRowStretch(6,1);
    twoProductLayout->setRowStretch(7,1);
    twoProductLayout->setRowStretch(8,1);
    twoProductLayout->setRowStretch(9,1);
    twoProductLayout->setRowStretch(10,1);
    twoProductLayout->setRowStretch(11,1);
    int j = 0;
    for(int i = 0; i < product_count; i++){
        twoProductLayout->addWidget(twoProductCheckBoxList[i],j / 10,j % 10);
        twoProductLayout->addWidget(twoProductLineEditList[i],j / 10,j % 10 + 1,Qt::AlignLeft);
        j+=2;
    }
    twoProductWidget->setLayout(twoProductLayout);
}

void xiaoshouhetongguanliDlg::keyPressEvent(QKeyEvent *event)
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

void xiaoshouhetongguanliDlg::creatTabPage1()
{
    createAction();
    createTool();

    SQL1 = "select ContractNumber 合同编号,CustomerName 客户名称,SettlementAmount 结算方量,DateSigned 签订日期,typeOfContract 合同类型,Remarks 备注,SettlementMethod 结算方式,WhetherAudit 是否审核,WhetherEffective 是否有效,InputMan 录入人 from SalesContractManagement;";

    QLabel *label1 = new QLabel(tr("--"));
    label1->setAlignment(Qt::AlignCenter);
    QLabel *oneContractNoLabel = new QLabel(tr("合同编号"),this);
    oneContractNoLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *oneCustomerLabel = new QLabel(tr("客户名称"),this);
    oneCustomerLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *oneSettlementAmountLabel = new QLabel(tr("结算方量"),this);
    oneSettlementAmountLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *oneDateSignedLabel = new QLabel(tr("签订日期"),this);
    oneDateSignedLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *oneRemarksLabel = new QLabel(tr("备注"),this);
    oneRemarksLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *oneContractTypeLabel = new QLabel(tr("合同类型"),this);
    oneContractTypeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *oneSettlementTypeLabel = new QLabel(tr("结算方式"),this);
    oneSettlementTypeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

    oneContractNoLineEdit = new QLineEdit(this);
    oneContractNoLineEdit->setReadOnly(true);
    oneSettlementAmountLineEdit = new QLineEdit(this);
    oneRemarksLineEdit = new QLineEdit(this);
    oneSettlementTypeTextEdit = new QTextEdit(this);
    oneSettlementTypeTextEdit->setFixedHeight(40);

    oneCustomerCombox = new QComboBox(this);
    const char *fillSQL1 = "select A.CustomerName from CustomerFiles A LEFT JOIN (SELECT CustomerName FROM SalesContractManagement) B ON (A.CustomerName=B.CustomerName) WHERE B.CustomerName IS NULL;";
    db.sql_fillComboBoxItem(fillSQL1,oneCustomerCombox);
    oneCustomerCombox->setStyleSheet("color:black");

    oneContractTypeCombox = new QComboBox(this);
    oneContractTypeCombox->setView(new QListView());
    oneContractTypeCombox->addItem(tr("混凝土合同"));
    oneContractTypeCombox->addItem(tr("砂浆合同"));
    oneDateSignedDateEdit = new QDateEdit(QDate::currentDate());
    oneDateSignedDateEdit->setCalendarPopup(true);

    oneFindCustomerCheckBox = new QCheckBox(tr("客户名称"),this);
    oneFindDateSignedCheckBox = new QCheckBox(tr("签订时间"),this);

    oneFindCustomerCombox = new myComboBox(this);
    const char *fillSQL2 = "select CustomerName from CustomerFiles;";
    db.sql_fillComboBoxItem(fillSQL2,oneFindCustomerCombox);

    oneFindContractStatusCombox = new QComboBox(this);
    oneFindContractStatusCombox->setView(new QListView());
    oneFindContractStatusCombox->addItem(tr("有效"));
    oneFindContractStatusCombox->addItem(tr("未审核"));
    oneFindContractStatusCombox->addItem(tr("已审核无效"));

    oneFindDateEdit1 = new QDateEdit(QDate::currentDate(),this);
    oneFindDateEdit1->setCalendarPopup(true);
    oneFindDateEdit2 = new QDateEdit(QDate::currentDate(),this);
    oneFindDateEdit2->setCalendarPopup(true);

    oneChaxunBtn = new QPushButton(tr("查询"),this);
    connect(oneChaxunBtn,SIGNAL(clicked()),this,SLOT(on_oneChaxunBtn()));

    oneView = new QTableView(this);
    db.showview(SQL1,oneView,&oneModel);
    connect(oneView,SIGNAL(clicked(QModelIndex)),this,SLOT(ShowSupplyclick()));
    connect(oneView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyDoubleClick()));
    oneView->setColumnWidth(1,230);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(oneContractNoLabel,0,0);
    layout->addWidget(oneContractNoLineEdit,0,1);
    layout->addWidget(oneCustomerLabel,0,2);
    layout->addWidget(oneCustomerCombox,0,3);
    layout->addWidget(oneSettlementAmountLabel,0,4);
    layout->addWidget(oneSettlementAmountLineEdit,0,5);
    layout->addWidget(oneDateSignedLabel,1,0);
    layout->addWidget(oneDateSignedDateEdit,1,1);
    layout->addWidget(oneRemarksLabel,1,2);
    layout->addWidget(oneRemarksLineEdit,1,3);
    layout->addWidget(oneContractTypeLabel,1,4);
    layout->addWidget(oneContractTypeCombox,1,5);
    layout->addWidget(oneSettlementTypeLabel,2,0);
    layout->addWidget(oneSettlementTypeTextEdit,2,1,1,5);
    layout->setColumnStretch(0,0);
    layout->setColumnStretch(1,1);
    layout->setColumnStretch(2,0);
    layout->setColumnStretch(3,2);
    layout->setColumnStretch(4,0);
    layout->setColumnStretch(5,1);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(oneFindCustomerCheckBox,0);
    hlayout->addWidget(oneFindCustomerCombox,2);
    hlayout->addWidget(oneFindDateSignedCheckBox,0);
    hlayout->addWidget(oneFindDateEdit1,0);
    hlayout->addWidget(label1,0);
    hlayout->addWidget(oneFindDateEdit2,0);
    hlayout->addWidget(oneFindContractStatusCombox,0);
    hlayout->addWidget(oneChaxunBtn,1);
    hlayout->addStretch(5);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(toolBar);
    vlayout->addLayout(layout);
    vlayout->addSpacing(10);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(oneView);

    hetongkehuguanli->setLayout(vlayout);
    tabWidget->addTab(hetongkehuguanli,tr("合同客户管理"));
}

void xiaoshouhetongguanliDlg::creatTabPage2()
{
    SQL1 = "select ProjectName 工程名称 from SalesContractCustomerEngineeringForm limit 0";

    QLabel *twoCustomerLabel = new QLabel(tr("客户名称"),this);
    twoCustomerLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    QLabel *twoEngineerLabel = new QLabel(tr("工程名称"),this);
    twoEngineerLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    QLabel *twoDistanceLabel = new QLabel(tr("工程运距"),this);
    twoDistanceLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    QLabel *twoPumpFeeLabel = new QLabel(tr("泵费"),this);
    twoPumpFeeLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    QLabel *twoPriceUseTimeLabel = new QLabel(tr("价格启用时间"),this);
    twoPriceUseTimeLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);

    twoCustomerLineEdit = new QLineEdit(this);
    twoCustomerLineEdit->setReadOnly(true);

    twoEngineerLineEdit = new QLineEdit(this);

    twoDistanceLineEdit = new QLineEdit(this);
    twoDistanceLineEdit->setFixedWidth(40);

    twoPumpFeeLineEdit = new QLineEdit(this);
    twoPumpFeeLineEdit->setFixedWidth(40);

    twoStartUseTimeEdit = new QDateTimeEdit(this);
    twoStartUseTimeEdit->setCalendarPopup(true);
    twoStartUseTimeEdit->setDate(QDate::currentDate());

    twoAttributeQuxiaoBtn = new QPushButton(tr("取消"),this);
    twoAttributeQuxiaoBtn->setFixedWidth(70);
    connect(twoAttributeQuxiaoBtn,SIGNAL(clicked()),this,SLOT(on_quxiaoBtn()));
    twoAttributeQuanxuanBtn = new QPushButton(tr("全选"),this);
    twoAttributeQuanxuanBtn->setFixedWidth(70);
    connect(twoAttributeQuanxuanBtn,SIGNAL(clicked()),this,SLOT(on_quanxuanBtn()));

    twoProductQuxiaoBtn = new QPushButton(tr("取消"),this);
    twoProductQuxiaoBtn->setFixedWidth(70);
    connect(twoProductQuxiaoBtn,SIGNAL(clicked()),this,SLOT(on_chanpinquxiaoBtn()));
    twoProductQuanxuanBtn = new QPushButton(tr("全选"),this);
    twoProductQuanxuanBtn->setFixedWidth(70);
    connect(twoProductQuanxuanBtn,SIGNAL(clicked()),this,SLOT(on_chanpinquanxuanBtn()));

    twoEngineerSaveBtn = new QPushButton(tr("保存"),this);
    twoEngineerSaveBtn->setFixedWidth(80);
    connect(twoEngineerSaveBtn,SIGNAL(clicked()),this,SLOT(on_twoEngineerSaveBtn()));

    twoAllEngineerSaveBtn = new QPushButton(tr("批量保存"),this);
    twoAllEngineerSaveBtn->setHidden(true);
    twoAllEngineerSaveBtn->setFixedWidth(80);
    connect(twoAllEngineerSaveBtn,SIGNAL(clicked()),this,SLOT(on_twoAllEngineerSaveBtn()));

    twoEngineerDeleteBtn = new QPushButton(tr("删除"),this);
    twoEngineerDeleteBtn->setFixedWidth(80);
    connect(twoEngineerDeleteBtn,SIGNAL(clicked()),this,SLOT(on_twoEngineerDeleteBtn()));

    twoAllEngineerDeleteBtn = new QPushButton(tr("批量删除"),this);
    twoAllEngineerDeleteBtn->setHidden(true);
    twoAllEngineerDeleteBtn->setFixedWidth(80);
    connect(twoAllEngineerDeleteBtn,SIGNAL(clicked()),this,SLOT(on_twoAllEngineerDeleteBtn()));

    twoNewEngineerBtn = new QPushButton(tr("新增"),this);
    twoNewEngineerBtn->setFixedWidth(80);
    connect(twoNewEngineerBtn,SIGNAL(clicked()),this,SLOT(on_twoNewEngineerBtn()));

    QGroupBox *twoEngineerSaveGroupbox = new QGroupBox(this);
    twoEngineerSaveGroupbox->setTitle(tr("工程添加及改价"));

    twoEngineerView = new QTreeView;
    connect(twoEngineerView,SIGNAL(clicked(QModelIndex)),this,SLOT(twoEngineerViewClick(const QModelIndex)));

    /*****************************************************************************************/
    customPlot = new QCustomPlot(this);
    customPlot->addGraph();// 添加数据曲线（一个图像可以有多个数据曲线）
    customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(QColor(41,138,220), 2), QBrush(QColor(5,189,251)), 10));

    customPlot->xAxis->setTicks(false);//x轴不显示刻度
    customPlot->yAxis->setTicks(false);//y轴不显示刻度

    customPlot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);//箭头
    customPlot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);

    connect(customPlot,SIGNAL(mouseMove(QMouseEvent*)),this,SLOT(my_mouseMove(QMouseEvent*)));
    /*******************************************************************************************/

    twoProductRadBtn = new QRadioButton(tr("产品"),this);
    twoProductRadBtn->setChecked(true);
    connect(twoProductRadBtn,SIGNAL(clicked()),this,SLOT(ON_PrintXY()));

    twoAttributeRadBtn = new QRadioButton(tr("属性"),this);
    connect(twoAttributeRadBtn,SIGNAL(clicked()),this,SLOT(ON_PrintXY()));

    twoBtnGroup = new QButtonGroup(this);
    twoBtnGroup->addButton(twoProductRadBtn,1);
    twoBtnGroup->addButton(twoAttributeRadBtn,2);

    twoProductCombox = new QComboBox(this);
    db.sql_fillComboBoxItem("select ProductName from ProductSetting",twoProductCombox);
    connect(twoProductCombox,SIGNAL(currentTextChanged(QString)),this,SLOT(ON_PrintXY()));

    twoAttributeCombox = new QComboBox(this);
    db.sql_fillComboBoxItem("select AttributeName from ProductAttributes",twoAttributeCombox);
    connect(twoAttributeCombox,SIGNAL(currentTextChanged(QString)),this,SLOT(ON_PrintXY()));

    init_productWidget();
    init_attributeWidget();

    //radiobtn布局
    QHBoxLayout *hRadioLayout = new QHBoxLayout;
    hRadioLayout->addWidget(twoProductRadBtn,0);
    hRadioLayout->addWidget(twoProductCombox,1);
    hRadioLayout->addWidget(twoAttributeRadBtn,0);
    hRadioLayout->addWidget(twoAttributeCombox,1);
    hRadioLayout->addStretch(3);

    //产品布局
    QHBoxLayout *h_chanpinvlayout = new QHBoxLayout;
    h_chanpinvlayout->addWidget(twoProductQuxiaoBtn);
    h_chanpinvlayout->addWidget(twoProductQuanxuanBtn);
    h_chanpinvlayout->addStretch(1);
    QVBoxLayout *chanpinVLayout = new QVBoxLayout;
    chanpinVLayout->addLayout(h_chanpinvlayout);
    chanpinVLayout->addWidget(twoProductWidget);

    //属性布局
    QHBoxLayout *h_vlayout2 = new QHBoxLayout;
    h_vlayout2->addWidget(twoAttributeQuxiaoBtn);
    h_vlayout2->addWidget(twoAttributeQuanxuanBtn);
    h_vlayout2->addStretch(1);
    QVBoxLayout *shuxingVLayout = new QVBoxLayout;
    shuxingVLayout->addLayout(h_vlayout2);
    shuxingVLayout->addWidget(twoAttributeWidget);

    twoProductGroupBox = new QGroupBox;
    twoProductGroupBox->setTitle(tr("请选择该工程所销售的产品，并在选择后输入每方价格信息"));
    twoProductGroupBox->setLayout(chanpinVLayout);
    twoAttributeGroupBox = new QGroupBox;
    twoAttributeGroupBox->setTitle(tr("请选择该工程所需的属性，并在选择后输入每方加价信息"));
    twoAttributeGroupBox->setLayout(shuxingVLayout);

    //工程添加布局
    QHBoxLayout *EngineerSaveLayout = new QHBoxLayout;
    EngineerSaveLayout->addWidget(twoCustomerLabel,0);
    EngineerSaveLayout->addWidget(twoCustomerLineEdit,1);
    EngineerSaveLayout->addWidget(twoEngineerLabel,0);
    EngineerSaveLayout->addWidget(twoEngineerLineEdit,1);
    EngineerSaveLayout->addWidget(twoDistanceLabel,0);
    EngineerSaveLayout->addWidget(twoDistanceLineEdit,1);
    EngineerSaveLayout->addWidget(twoPumpFeeLabel,0);
    EngineerSaveLayout->addWidget(twoPumpFeeLineEdit,1);
    EngineerSaveLayout->addWidget(twoPriceUseTimeLabel,0);
    EngineerSaveLayout->addWidget(twoStartUseTimeEdit,0);

    QHBoxLayout *EngineerBtnLayout = new QHBoxLayout;
    EngineerBtnLayout->addStretch(20);
    EngineerBtnLayout->addWidget(twoEngineerSaveBtn,1);
    EngineerBtnLayout->addWidget(twoAllEngineerSaveBtn,1);
    EngineerBtnLayout->addWidget(twoEngineerDeleteBtn,1);
    EngineerBtnLayout->addWidget(twoAllEngineerDeleteBtn,1);
    EngineerBtnLayout->addWidget(twoNewEngineerBtn,1);

    QVBoxLayout *EngineerLayout = new QVBoxLayout;
    EngineerLayout->addLayout(EngineerSaveLayout);
    EngineerLayout->addLayout(EngineerBtnLayout);

    twoEngineerSaveGroupbox->setLayout(EngineerLayout);

    //产品属性box
    QVBoxLayout *ProductAttributeLayout = new QVBoxLayout;
    ProductAttributeLayout->addWidget(twoProductGroupBox,1);
    ProductAttributeLayout->addWidget(twoAttributeGroupBox,1);
    ProductAttributeLayout->addLayout(hRadioLayout,0);
    ProductAttributeLayout->addWidget(customPlot,1);

    //工程列表layout
    QHBoxLayout *gongchengListLayout = new QHBoxLayout;
    gongchengListLayout->addWidget(twoEngineerView);

    gongchengListBox = new QGroupBox;
    gongchengListBox->setTitle(tr("工程列表"));
    gongchengListBox->setLayout(gongchengListLayout);

    //页面下方整体布局
    QHBoxLayout *viewLayout = new QHBoxLayout;
    viewLayout->addWidget(gongchengListBox,1);
    viewLayout->addLayout(ProductAttributeLayout,3);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(twoEngineerSaveGroupbox);//添加头部布局
    vlayout->addLayout(viewLayout);

    hetonggongchengguanli->setLayout(vlayout);
    tabWidget->addTab(hetonggongchengguanli,tr("合同工程管理"));
}

void xiaoshouhetongguanliDlg::creatTabPage3()
{
    SQL3 = "select CustomerName 客户名称,ProjectName 工程名称,0 是否修改 from SalesContractCustomerEngineeringForm group by CustomerName,ProjectName order by CustomerName,ProjectName";

    QLabel *ProductNoticeTime1Labe = new QLabel(tr("出车单时间"),this);
    ProductNoticeTime1Labe->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    QLabel *fuHaoLabel = new QLabel(tr("--"),this);
    fuHaoLabel->setAlignment(Qt::AlignCenter|Qt::AlignVCenter);

    QLabel *updateTime1Labe = new QLabel(tr("修改时间"),this);
    updateTime1Labe->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    QLabel *fuHaoLabel1 = new QLabel(tr("--"),this);
    fuHaoLabel1->setAlignment(Qt::AlignCenter|Qt::AlignVCenter);

    threeDateTimeEdit1 = new QDateTimeEdit(this);
    threeDateTimeEdit1->setCalendarPopup(true);
    threeDateTimeEdit1->setDate(QDate::currentDate());

    threeDateTimeEdit2 = new QDateTimeEdit(this);
    threeDateTimeEdit2->setCalendarPopup(true);
    threeDateTimeEdit2->setDate(QDate::currentDate());

    threeUpdateDateTimeEdit1 = new QDateTimeEdit(this);
    threeUpdateDateTimeEdit1->setCalendarPopup(true);
    threeUpdateDateTimeEdit1->setDate(QDate::currentDate());

    threeUpdateDateTimeEdit2 = new QDateTimeEdit(this);
    threeUpdateDateTimeEdit2->setCalendarPopup(true);
    threeUpdateDateTimeEdit2->setDate(QDate::currentDate().addDays(1));

    threeCustomerCheckBox = new QCheckBox(tr("客户名称"),this);

    threeCustomerComBox = new myComboBox(this);
    db.sql_fillComboBoxItem("select CustomerName from SalesContractCustomerEngineeringForm group by CustomerName order by CustomerName",threeCustomerComBox);

    threeUpdateBtn = new QPushButton(tr("确认修改"),this);
    threeUpdateBtn->setFixedWidth(120);
    connect(threeUpdateBtn,SIGNAL(clicked()),this,SLOT(on_threeUpdateBtn()));

    threeQuanXuanBtn = new QPushButton(tr("全选"),this);
    threeQuanXuanBtn->setFixedWidth(120);
    connect(threeQuanXuanBtn,SIGNAL(clicked()),this,SLOT(on_threeQuanXuanBtn()));

    threeQuXiaoBtn = new QPushButton(tr("取消"),this);
    threeQuXiaoBtn->setFixedWidth(120);
    connect(threeQuXiaoBtn,SIGNAL(clicked()),this,SLOT(on_threeQuXiaoBtn()));

    threeFindBtn = new QPushButton(tr("查询"),this);
    threeFindBtn->setFixedWidth(120);
    connect(threeFindBtn,SIGNAL(clicked()),this,SLOT(on_threeFindBtn()));

    threeCustomerFindBtn = new QPushButton(tr("查询"),this);
    threeCustomerFindBtn->setFixedWidth(100);
    connect(threeCustomerFindBtn,SIGNAL(clicked()),this,SLOT(on_threeCustomerFindBtn()));

    threeEngineerListView = new QTableView(this);
    threeEngineerListView->setItemDelegate(new myCheckBoxDelegate(2,this));
    db.showview(SQL3,threeEngineerListView,&threeEngineerListModel);
    threeEngineerListView->setColumnWidth(1,260);

    threeUpdateDetailInfoView = new QTableView(this);
    db.showview("select updateEngineer 修改的工程,OutBoundTime 修改的出车单日期,Operator 修改人,OperatingTime 修改时间 from ProductionNoticePriceCorrectRecord limit 0",threeUpdateDetailInfoView,&threeUpdateDetailInfoModel);
    threeUpdateDetailInfoView->setColumnWidth(0,300);
    threeUpdateDetailInfoView->setColumnWidth(1,300);
    threeUpdateDetailInfoView->setColumnWidth(3,130);

    QHBoxLayout *BtnLayout = new QHBoxLayout;
    BtnLayout->addStretch(10);
    BtnLayout->addWidget(threeQuanXuanBtn,1);
    BtnLayout->addWidget(threeQuXiaoBtn,1);

    QHBoxLayout *SupplierListBoxHLayout = new QHBoxLayout;
    SupplierListBoxHLayout->addWidget(threeCustomerCheckBox,0);
    SupplierListBoxHLayout->addWidget(threeCustomerComBox,1);
    SupplierListBoxHLayout->addWidget(threeCustomerFindBtn,1);

    QVBoxLayout *SupplierListBoxVLayout = new QVBoxLayout;
    SupplierListBoxVLayout->addWidget(threeEngineerListView);
    SupplierListBoxVLayout->addLayout(BtnLayout);

    QVBoxLayout *SupplierListBoxLayout = new QVBoxLayout;
    SupplierListBoxLayout->addLayout(SupplierListBoxHLayout);
    SupplierListBoxLayout->addLayout(SupplierListBoxVLayout);

    QGroupBox *SupplierListBox = new QGroupBox(this);
    SupplierListBox->setTitle(tr("工程列表"));
    SupplierListBox->setLayout(SupplierListBoxLayout);

    QHBoxLayout *UpdateDetailInfoBoxHeadLayout = new QHBoxLayout;
    UpdateDetailInfoBoxHeadLayout->addWidget(updateTime1Labe,0);
    UpdateDetailInfoBoxHeadLayout->addWidget(threeUpdateDateTimeEdit1,0);
    UpdateDetailInfoBoxHeadLayout->addWidget(fuHaoLabel1,0);
    UpdateDetailInfoBoxHeadLayout->addWidget(threeUpdateDateTimeEdit2,0);
    UpdateDetailInfoBoxHeadLayout->addWidget(threeFindBtn,1);
    UpdateDetailInfoBoxHeadLayout->addStretch(4);

    QVBoxLayout *UpdateDetailInfoBoxLayout = new QVBoxLayout;
    UpdateDetailInfoBoxLayout->addLayout(UpdateDetailInfoBoxHeadLayout);
    UpdateDetailInfoBoxLayout->addWidget(threeUpdateDetailInfoView);

    QGroupBox *UpdateDetailInfoBox = new QGroupBox(this);
    UpdateDetailInfoBox->setTitle(tr("修改记录"));
    UpdateDetailInfoBox->setLayout(UpdateDetailInfoBoxLayout);

    QHBoxLayout *hlayout1 = new QHBoxLayout;
    hlayout1->addWidget(ProductNoticeTime1Labe,0);
    hlayout1->addWidget(threeDateTimeEdit1,1);
    hlayout1->addWidget(fuHaoLabel,0);
    hlayout1->addWidget(threeDateTimeEdit2,1);
    hlayout1->addWidget(threeUpdateBtn,1);
    hlayout1->addStretch(5);

    QHBoxLayout *hlayout2 = new QHBoxLayout;
    hlayout2->addWidget(SupplierListBox,2);
    hlayout2->addWidget(UpdateDetailInfoBox,3);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(hlayout1);
    vlayout->addLayout(hlayout2);

    ProductNoticePriceCorrectWidget->setLayout(vlayout);
    tabWidget->addTab(ProductNoticePriceCorrectWidget,tr("出车单价格修正"));
}

void xiaoshouhetongguanliDlg::createAction()
{
    newAction = new QAction(tr("新增"),this);
    newAction->setIcon(QIcon(":/image/new.png"));
    connect(newAction,SIGNAL(triggered()),this,SLOT(on_newAction_plus()));
    saveAction = new QAction(tr("保存"),this);
    saveAction->setIcon(QIcon(":/image/save.png"));
    connect(saveAction,SIGNAL(triggered()),this,SLOT(on_saveAction()));
    updateAction = new QAction(tr("修改"),this);
    updateAction->setEnabled(false);
    updateAction->setIcon(QIcon(":/image/update.png"));
    connect(updateAction,SIGNAL(triggered()),this,SLOT(on_updateAction()));
    deleteAction = new QAction(tr("删除"),this);
    deleteAction->setEnabled(false);
    deleteAction->setIcon(QIcon(":/image/delete.png"));
    connect(deleteAction,SIGNAL(triggered()),this,SLOT(on_deleteAction()));
    checkAction = new QAction(tr("审核"),this);
    checkAction->setEnabled(false);
    checkAction->setIcon(QIcon(":/image/check.png"));
    connect(checkAction,SIGNAL(triggered()),this,SLOT(on_checkAction()));
}

void xiaoshouhetongguanliDlg::createTool()
{
    toolBar = new QToolBar;
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar->addAction(newAction);
    toolBar->addAction(saveAction);
    toolBar->addAction(updateAction);
    toolBar->addAction(deleteAction);
    toolBar->addAction(checkAction);
}

void xiaoshouhetongguanliDlg::on_newAction()
{
    saveAction->setEnabled(true);
    updateAction->setEnabled(false);
    deleteAction->setEnabled(false);
    checkAction->setEnabled(false);
    oneContractNoLineEdit->clear();
    oneSettlementAmountLineEdit->clear();
    oneRemarksLineEdit->clear();
    oneCustomerCombox->setCurrentIndex(0);
    oneCustomerCombox->setEnabled(true);
    oneCustomerCombox->setEditable(false);
    oneContractTypeCombox->setCurrentIndex(0);
    oneDateSignedDateEdit->setDate(QDate::currentDate());
    oneSettlementTypeTextEdit->clear();
}

void xiaoshouhetongguanliDlg::on_newAction_plus()
{
    saveAction->setEnabled(true);
    updateAction->setEnabled(false);
    deleteAction->setEnabled(false);
    checkAction->setEnabled(false);
    oneContractNoLineEdit->setText(pub.newSalesContractNo());
    oneSettlementAmountLineEdit->clear();
    oneRemarksLineEdit->clear();
    oneCustomerCombox->setCurrentIndex(0);
    oneCustomerCombox->setEnabled(true);
    oneCustomerCombox->setEditable(false);
    oneContractTypeCombox->setCurrentIndex(0);
    oneDateSignedDateEdit->setDate(QDate::currentDate());
    oneSettlementTypeTextEdit->clear();
}

void xiaoshouhetongguanliDlg::on_saveAction()
{
    if(oneContractNoLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请新增一个合同编号"),0,0,0);
        return;
    }
    if(oneCustomerCombox->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择一个客户名称"),0,0,0);
        return;
    }

    QString searchKehu = QString("select CustomerName from SalesContractManagement where CustomerName='%1' and WhetherEffective='有效'").arg(oneCustomerCombox->currentText());
    if(db.row_count(searchKehu) != 0){
        QMessageBox::information(this,tr("提示信息"),tr("该客户已存在合同"),0,0,0);
        return;
    }

    //插入合同
    QString saveSalesContractManagementSQL = QString("insert into SalesContractManagement (ContractNumber,CustomerName,SettlementAmount,DateSigned,typeOfContract,\
                              Remarks,SettlementMethod,WhetherAudit,WhetherEffective,InputMan) values ('%1','%2','%3','%4','%5','%6','%7','%8','%9','%10')")
                    .arg(oneContractNoLineEdit->text(),oneCustomerCombox->currentText(),oneSettlementAmountLineEdit->text(),oneDateSignedDateEdit->date().toString("yyyy-MM-dd"),
                         oneContractTypeCombox->currentText(),oneRemarksLineEdit->text(),oneSettlementTypeTextEdit->toPlainText()).arg("否","无效",userName);

    int res = db.sql_exec(saveSalesContractManagementSQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();
        on_newAction();
        oneFindContractStatusCombox->setCurrentIndex(1);
        on_oneChaxunBtn();
        QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
    }
}

void xiaoshouhetongguanliDlg::on_updateAction()
{
    if(oneContractNoLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请新增一个合同编号"),0,0,0);
        return;
    }
    if(oneCustomerCombox->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择一个客户名称"),0,0,0);
        return;
    }

    //更新合同
    QString updateSQL = QString("update SalesContractManagement set SettlementAmount='%1',DateSigned='%2',Remarks='%3',SettlementMethod='%4',InputMan='%5' where ContractNumber='%6'")
               .arg(oneSettlementAmountLineEdit->text(),oneDateSignedDateEdit->date().toString("yyyy-MM-dd"),oneRemarksLineEdit->text(),
                    oneSettlementTypeTextEdit->toPlainText(),userName,oneContractNoLineEdit->text());

    int res = db.sql_exec(updateSQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();
        on_newAction();
        on_oneChaxunBtn();
        QMessageBox::information(this,tr("提示信息"),tr("修改成功"),0,0,0);
    }
}

void xiaoshouhetongguanliDlg::on_deleteAction()
{
    QString searchSQL = QString("select ContractNumber from SalesContractManagement where ContractNumber='%1' and WhetherEffective='有效'").arg(oneContractNoLineEdit->text());
    if(db.row_count(searchSQL) != 0){
        ContractDeleteDlg *dlg = new ContractDeleteDlg(this);
        dlg->exec();
        if(dlg->isOnOkBtn == false){
            return;
        }
    }

    QString deleteSalesAttributeListSQL = QString("delete from SalesAttributeList where ContractNumber='%1';").arg(oneContractNoLineEdit->text());
    QString deleteSalesProductListSQL = QString("delete from SalesProductList where ContractNumber='%1';").arg(oneContractNoLineEdit->text());
    QString deleteSalesContractManagementSQL = QString("delete from SalesContractManagement where ContractNumber='%1';").arg(oneContractNoLineEdit->text());

    int res = 0;
    db.sql_exec("begin");
    res = db.sql_exec(deleteSalesAttributeListSQL.toStdString().data());
    if(res == -1){
        db.sql_exec("rollback");
        return;
    }
    res = db.sql_exec(deleteSalesProductListSQL.toStdString().data());
    if(res == -1){
        db.sql_exec("rollback");
        return;
    }
    res = db.sql_exec(deleteSalesContractManagementSQL.toStdString().data());
    if(res == -1){
        db.sql_exec("rollback");
        return;
    }
    db.sql_exec("commit");

    if(res == 0){
        sockClient->send_Msg3();
        on_newAction();
        on_oneChaxunBtn();
        QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
    }
}

void xiaoshouhetongguanliDlg::on_checkAction()
{
    QString checkSQL = QString("update SalesContractManagement set WhetherAudit='是',WhetherEffective='有效' where ContractNumber='%1'").arg(oneContractNoLineEdit->text());
    int res = db.sql_exec(checkSQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();
        on_newAction();
        on_oneChaxunBtn();
        QMessageBox::information(this,tr("提示信息"),tr("审核成功"),0,0,0);
    }
}

void xiaoshouhetongguanliDlg::ShowSupplyclick()
{
    saveAction->setEnabled(false);
    updateAction->setEnabled(true);
    deleteAction->setEnabled(true);
    checkAction->setEnabled(true);
    oneCustomerCombox->setEnabled(false);
    oneCustomerCombox->setEditable(true);

    int row = oneView->currentIndex().row();

    oneContractNoLineEdit->setText(oneModel->item(row,0)->text());
    oneCustomerCombox->setCurrentText(oneModel->item(row,1)->text());
    oneSettlementAmountLineEdit->setText(oneModel->item(row,2)->text());
    oneDateSignedDateEdit->setDate(QDate::fromString(oneModel->item(row,3)->text(),"yyyy-MM-dd"));
    oneContractTypeCombox->setCurrentText(oneModel->item(row,4)->text());
    oneRemarksLineEdit->setText(oneModel->item(row,5)->text());
    oneSettlementTypeTextEdit->setText(oneModel->item(row,6)->text());
}

void xiaoshouhetongguanliDlg::ShowSupplyDoubleClick()
{
    int row = oneView->currentIndex().row();
    if(oneModel->item(row,8)->text() != "有效"){
        return;
    }

    twoCustomerNoStr = oneModel->item(row,0)->text();
    twoCustomerLineEdit->setText(oneModel->item(row,1)->text());
    twoEngineerLineEdit->clear();
    twoDistanceLineEdit->clear();
    twoPumpFeeLineEdit->clear();
    twoStartUseTimeEdit->setDate(QDate::currentDate());

    QString gongchengSQL = QString("select ProjectName,DateTime from SalesContractCustomerEngineeringForm where CustomerName='%1' order by ProjectName,DateTime").arg(twoCustomerLineEdit->text());
    db.show_treeview2(gongchengSQL.toStdString().data(),twoEngineerView,&twoEngineerModel);

    tabWidget->setCurrentIndex(1);
}

void xiaoshouhetongguanliDlg::on_quxiaoBtn()
{
    for(int i = 0; i<attribute_count; i++){
        twoAttributeCheckBoxList[i]->setCheckState(Qt::Unchecked);
    }
}

void xiaoshouhetongguanliDlg::on_quanxuanBtn()
{
    for(int i = 0; i<attribute_count; i++){
        twoAttributeCheckBoxList[i]->setCheckState(Qt::Checked);
    }
}

void xiaoshouhetongguanliDlg::on_chanpinquxiaoBtn()
{
    for(int i = 0; i<product_count; i++){
        twoProductCheckBoxList[i]->setCheckState(Qt::Unchecked);
    }
}

void xiaoshouhetongguanliDlg::on_chanpinquanxuanBtn()
{
    for(int i = 0; i<product_count; i++){
        twoProductCheckBoxList[i]->setCheckState(Qt::Checked);
    }
}

void xiaoshouhetongguanliDlg::on_twoEngineerSaveBtn()
{
//    QString searchPeoPle = QString("select * from salescontractauditor where CheckPerson='%1'").arg(userName);
//    if(db.row_count(searchPeoPle) == 0){
//        QMessageBox::information(this,tr("提示信息"),tr("当前用户不具备修改合同权限"),0,0,0);
//        return;
//    }

    if(twoEngineerLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("工程名称不能为空"),0,0,0);
        return;
    }
    if(twoDistanceLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("工程运距不能为空"),0,0,0);
        return;
    }
    if(twoPumpFeeLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("泵费不能为空"),0,0,0);
        return;
    }

    //插入工程表
    QString updateEngineeringSQL = QString("replace into SalesContractCustomerEngineeringForm (ContractNumber,CustomerName,ProjectName,Distance,PumpFee,DateTime) values ('%1','%2','%3','%4','%5','%6')")
            .arg(twoCustomerNoStr,twoCustomerLineEdit->text(),twoEngineerLineEdit->text(),twoDistanceLineEdit->text(),twoPumpFeeLineEdit->text(),twoStartUseTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"));

    //删除之前的产品
    QString deleteSalesProductListSQL = QString("delete from SalesProductList where ContractNumber='%1' and EngineerName='%2' and StartTime='%3'")
            .arg(twoCustomerNoStr,twoEngineerLineEdit->text(),twoStartUseTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"));

    //产品名称价格
    QString saveSalesProductListSQL = QString("replace into SalesProductList (ContractNumber,CustomerName,EngineerName,product,ProductPrice,StartTime) values ");
    for(int i = 0; i<product_count; i++){
        if(twoProductCheckBoxList[i]->checkState() == 2){
            saveSalesProductListSQL = saveSalesProductListSQL.append(QString("('%1','%2','%3','%4','%5','%6'),")
                                      .arg(twoCustomerNoStr,twoCustomerLineEdit->text(),twoEngineerLineEdit->text(),
                                           twoProductCheckBoxList[i]->text(),twoProductLineEditList[i]->text(),twoStartUseTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss")));
        }
    }
    saveSalesProductListSQL = saveSalesProductListSQL.left(saveSalesProductListSQL.length()-1);

    //删除之前的属性
    QString deleteSalesAttributeListSQL = QString("delete from SalesAttributeList where ContractNumber='%1' and EngineerName='%2' and StartTime='%3'")
            .arg(twoCustomerNoStr,twoEngineerLineEdit->text(),twoStartUseTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"));

    //属性名称价格
    QString saveSalesAttributeListSQL = QString("replace into SalesAttributeList (ContractNumber,CustomerName,EngineerName,attribute,AttributePrice,StartTime) values ");
    for(int i = 0; i<attribute_count; i++){
        if(twoAttributeCheckBoxList[i]->checkState() == 2){
            saveSalesAttributeListSQL = saveSalesAttributeListSQL.append(QString("('%1','%2','%3','%4','%5','%6'),")
                                     .arg(twoCustomerNoStr,twoCustomerLineEdit->text(),twoEngineerLineEdit->text(),
                                          twoAttributeCheckBoxList[i]->text(),twoAttributeLineEditList[i]->text(),twoStartUseTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss")));
        }
    }
    saveSalesAttributeListSQL = saveSalesAttributeListSQL.left(saveSalesAttributeListSQL.length()-1);

    int res = 0;
    db.sql_exec("begin");
    res = db.sql_exec(updateEngineeringSQL.toStdString().data());
    if(res == -1){
        db.sql_exec("rollback");
        return;
    }
    res = db.sql_exec(deleteSalesProductListSQL.toStdString().data());
    if(res == -1){
        db.sql_exec("rollback");
        return;
    }
    res = db.sql_exec(saveSalesProductListSQL.toStdString().data());
    if(res == -1){
        db.sql_exec("rollback");
        QMessageBox::information(this,tr("提示信息"),tr("请至少选择一种产品"),0,0,0);
        return;
    }
    res = db.sql_exec(deleteSalesAttributeListSQL.toStdString().data());
    if(res == -1){
        db.sql_exec("rollback");
        return;
    }
    res = db.sql_exec(saveSalesAttributeListSQL.toStdString().data());
    if(res == -1){
        db.sql_exec("rollback");
        QMessageBox::information(this,tr("提示信息"),tr("请至少选择一种属性"),0,0,0);
        return;
    }
    db.sql_exec("commit");

    QString gongchengSQL = QString("select ProjectName,DateTime from SalesContractCustomerEngineeringForm where CustomerName='%1' order by ProjectName,DateTime").arg(twoCustomerLineEdit->text());
    db.show_treeview2(gongchengSQL.toStdString().data(),twoEngineerView,&twoEngineerModel);

    QMessageBox::information(this,tr("提示信息"),tr("操作成功"),0,0,0);
}

void xiaoshouhetongguanliDlg::on_twoAllEngineerSaveBtn()
{
    QString searchPeoPle = QString("select * from salescontractauditor where CheckPerson='%1'").arg(userName);
    if(db.row_count(searchPeoPle) == 0){
        QMessageBox::information(this,tr("提示信息"),tr("当前用户不具备修改合同权限"),0,0,0);
        return;
    }

    if(twoEngineerLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("工程名称不能为空"),0,0,0);
        return;
    }
    if(twoDistanceLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("工程运距不能为空"),0,0,0);
        return;
    }
    if(twoPumpFeeLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("泵费不能为空"),0,0,0);
        return;
    }

    /******************************************************************************************************/
    int rowCount = twoEngineerModel->rowCount();
    qDebug()<<rowCount;
    for(int k = 0; k<rowCount; k++){
        QString EngineerName = twoEngineerModel->item(k,0)->text();

        //插入工程表
        QString updateEngineeringSQL = QString("replace into SalesContractCustomerEngineeringForm (ContractNumber,CustomerName,ProjectName,Distance,PumpFee,DateTime) values ('%1','%2','%3','%4','%5','%6')")
                .arg(twoCustomerNoStr,twoCustomerLineEdit->text(),EngineerName,twoDistanceLineEdit->text(),twoPumpFeeLineEdit->text(),twoStartUseTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"));

        //删除之前的产品
        QString deleteSalesProductListSQL = QString("delete from SalesProductList where ContractNumber='%1' and EngineerName='%2' and StartTime='%3'")
                .arg(twoCustomerNoStr,EngineerName,twoStartUseTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"));

        //产品名称价格
        QString saveSalesProductListSQL = QString("replace into SalesProductList (ContractNumber,CustomerName,EngineerName,product,ProductPrice,StartTime) values ");
        for(int i = 0; i<product_count; i++){
            if(twoProductCheckBoxList[i]->checkState() == 2){
                saveSalesProductListSQL = saveSalesProductListSQL.append(QString("('%1','%2','%3','%4','%5','%6'),")
                                          .arg(twoCustomerNoStr,twoCustomerLineEdit->text(),EngineerName,
                                               twoProductCheckBoxList[i]->text(),twoProductLineEditList[i]->text(),twoStartUseTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss")));
            }
        }
        saveSalesProductListSQL = saveSalesProductListSQL.left(saveSalesProductListSQL.length()-1);

        //删除之前的属性
        QString deleteSalesAttributeListSQL = QString("delete from SalesAttributeList where ContractNumber='%1' and EngineerName='%2' and StartTime='%3'")
                .arg(twoCustomerNoStr,EngineerName,twoStartUseTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"));

        //属性名称价格
        QString saveSalesAttributeListSQL = QString("replace into SalesAttributeList (ContractNumber,CustomerName,EngineerName,attribute,AttributePrice,StartTime) values ");
        for(int i = 0; i<attribute_count; i++){
            if(twoAttributeCheckBoxList[i]->checkState() == 2){
                saveSalesAttributeListSQL = saveSalesAttributeListSQL.append(QString("('%1','%2','%3','%4','%5','%6'),")
                                         .arg(twoCustomerNoStr,twoCustomerLineEdit->text(),EngineerName,
                                              twoAttributeCheckBoxList[i]->text(),twoAttributeLineEditList[i]->text(),twoStartUseTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss")));
            }
        }
        saveSalesAttributeListSQL = saveSalesAttributeListSQL.left(saveSalesAttributeListSQL.length()-1);

        int res = 0;
        db.sql_exec("begin");
        res = db.sql_exec(updateEngineeringSQL);
        if(res == -1){
            db.sql_exec("rollback");
            return;
        }
        res = db.sql_exec(deleteSalesProductListSQL);
        if(res == -1){
            db.sql_exec("rollback");
            return;
        }
        res = db.sql_exec(saveSalesProductListSQL);
        if(res == -1){
            db.sql_exec("rollback");
            QMessageBox::information(this,tr("提示信息"),tr("请至少选择一种产品"),0,0,0);
            return;
        }
        res = db.sql_exec(deleteSalesAttributeListSQL);
        if(res == -1){
            db.sql_exec("rollback");
            return;
        }
        res = db.sql_exec(saveSalesAttributeListSQL);
        if(res == -1){
            db.sql_exec("rollback");
            QMessageBox::information(this,tr("提示信息"),tr("请至少选择一种属性"),0,0,0);
            return;
        }
        db.sql_exec("commit");
    }
    /******************************************************************************************************/

    QString gongchengSQL = QString("select ProjectName,DateTime from SalesContractCustomerEngineeringForm where CustomerName='%1' order by ProjectName,DateTime").arg(twoCustomerLineEdit->text());
    db.show_treeview2(gongchengSQL,twoEngineerView,&twoEngineerModel);

    QMessageBox::information(this,tr("提示信息"),tr("操作成功"),0,0,0);
}

void xiaoshouhetongguanliDlg::on_twoEngineerDeleteBtn()
{
    QString searchPeoPle = QString("select * from salescontractauditor where CheckPerson='%1'").arg(userName);
    if(db.row_count(searchPeoPle) == 0){
        QMessageBox::information(this,tr("提示信息"),tr("当前用户不具备修改合同权限"),0,0,0);
        return;
    }

    if(twoEngineerLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("工程名称不能为空"),0,0,0);
        return;
    }

    QString deleteSQL = QString("delete from SalesContractCustomerEngineeringForm where CustomerName='%1' and ProjectName='%2' and DateTime='%3'")
            .arg(twoCustomerLineEdit->text(),twoEngineerLineEdit->text(),twoStartUseTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"));

    QString deleteAttribute = QString("delete from SalesAttributeList where CustomerName='%1' and EngineerName='%2' and StartTime='%3'")
            .arg(twoCustomerLineEdit->text(),twoEngineerLineEdit->text(),twoStartUseTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"));

    QString deleteProduct = QString("delete from SalesProductList where CustomerName='%1' and EngineerName='%2' and StartTime='%3'")
            .arg(twoCustomerLineEdit->text(),twoEngineerLineEdit->text(),twoStartUseTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"));

    int res = 0;
    db.sql_exec("begin");
    res = db.sql_exec(deleteSQL.toStdString().data());
    if(res == -1){
        db.sql_exec("rollback");
        return;
    }
    res = db.sql_exec(deleteAttribute.toStdString().data());
    if(res == -1){
        db.sql_exec("rollback");
        return;
    }
    res = db.sql_exec(deleteProduct.toStdString().data());
    if(res == -1){
        db.sql_exec("rollback");
        return;
    }
    db.sql_exec("commit");

    QString gongchengSQL = QString("select ProjectName,DateTime from SalesContractCustomerEngineeringForm where CustomerName='%1' order by ProjectName,DateTime").arg(twoCustomerLineEdit->text());
    db.show_treeview2(gongchengSQL.toStdString().data(),twoEngineerView,&twoEngineerModel);

    on_twoNewEngineerBtn();
    QMessageBox::information(this,tr("提示信息"),tr("工程删除成功"),0,0,0);
}

void xiaoshouhetongguanliDlg::on_twoAllEngineerDeleteBtn()
{
    QString searchPeoPle = QString("select * from salescontractauditor where CheckPerson='%1'").arg(userName);
    if(db.row_count(searchPeoPle) == 0){
        QMessageBox::information(this,tr("提示信息"),tr("当前用户不具备修改合同权限"),0,0,0);
        return;
    }

    if(twoEngineerLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("工程名称不能为空"),0,0,0);
        return;
    }

    int rowCount = twoEngineerModel->rowCount();
    for(int k = 0; k<rowCount; k++){
        QString EngineerName = twoEngineerModel->item(k,0)->text();

        QString deleteSQL = QString("delete from SalesContractCustomerEngineeringForm where CustomerName='%1' and ProjectName='%2' and DateTime='%3'")
                .arg(twoCustomerLineEdit->text(),EngineerName,twoStartUseTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"));

        QString deleteAttribute = QString("delete from SalesAttributeList where CustomerName='%1' and EngineerName='%2' and StartTime='%3'")
                .arg(twoCustomerLineEdit->text(),EngineerName,twoStartUseTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"));

        QString deleteProduct = QString("delete from SalesProductList where CustomerName='%1' and EngineerName='%2' and StartTime='%3'")
                .arg(twoCustomerLineEdit->text(),EngineerName,twoStartUseTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"));

        int res = 0;
        db.sql_exec("begin");
        res = db.sql_exec(deleteSQL.toStdString().data());
        if(res == -1){
            db.sql_exec("rollback");
            return;
        }
        res = db.sql_exec(deleteAttribute.toStdString().data());
        if(res == -1){
            db.sql_exec("rollback");
            return;
        }
        res = db.sql_exec(deleteProduct.toStdString().data());
        if(res == -1){
            db.sql_exec("rollback");
            return;
        }
        db.sql_exec("commit");
    }

    QString gongchengSQL = QString("select ProjectName,DateTime from SalesContractCustomerEngineeringForm where CustomerName='%1' order by ProjectName,DateTime").arg(twoCustomerLineEdit->text());
    db.show_treeview2(gongchengSQL.toStdString().data(),twoEngineerView,&twoEngineerModel);

    on_twoNewEngineerBtn();
    QMessageBox::information(this,tr("提示信息"),tr("工程删除成功"),0,0,0);
}

void xiaoshouhetongguanliDlg::on_twoNewEngineerBtn()
{
    twoEngineerLineEdit->clear();
    twoDistanceLineEdit->clear();
    twoPumpFeeLineEdit->clear();
    twoStartUseTimeEdit->setDate(QDate::currentDate());
}

void xiaoshouhetongguanliDlg::on_oneChaxunBtn()
{
    QString ContractStatus,kehumingcheng,qiandingshijian;

    switch(oneFindContractStatusCombox->currentIndex()){
    case 0:
        ContractStatus = QString(" where WhetherEffective='有效'");
        break;
    case 1:
        ContractStatus = QString(" where WhetherAudit='否'");
        break;
    case 2:
        ContractStatus = QString(" where WhetherAudit='是' and WhetherEffective='无效'");
        break;
    }

    if(oneFindCustomerCheckBox->checkState() == 2){
        kehumingcheng = QString(" and CustomerName='%1'").arg(oneFindCustomerCombox->currentText());
    }
    if(oneFindDateSignedCheckBox->checkState() == 2){
        qiandingshijian = QString(" and DateSigned between '%1' and '%2'").arg(oneFindDateEdit1->date().toString("yyyy-MM-dd"),oneFindDateEdit2->date().toString("yyyy-MM-dd"));
    }

    QString searchSQL = QString("select ContractNumber 合同编号,CustomerName 客户名称,SettlementAmount 结算方量,DateSigned 签订日期,typeOfContract 合同类型,Remarks 备注,\
                                SettlementMethod 结算方式,WhetherAudit 是否审核,WhetherEffective 是否有效,InputMan 录入人 from SalesContractManagement %1 %2 %3;")
            .arg(ContractStatus,kehumingcheng,qiandingshijian);
    db.showview(searchSQL.toStdString().data(),oneView,&oneModel);
}

void xiaoshouhetongguanliDlg::twoEngineerViewClick(const QModelIndex &index)
{
    QString dateTime = index.data().toString();
    QString EngineerName = index.parent().data().toString();

    twoEngineerLineEdit->setText(EngineerName);
    twoStartUseTimeEdit->setDateTime(QDateTime::fromString(dateTime,"yyyy-MM-dd hh:mm:ss"));

    QString searchDistance = QString("select Distance,PumpFee from SalesContractCustomerEngineeringForm where CustomerName='%1' and ProjectName='%2' and DateTime='%3'")
            .arg(twoCustomerLineEdit->text(),twoEngineerLineEdit->text(),twoStartUseTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
    QStringList strList = db.CreatStrList(searchDistance);
    if(strList.count() == 2){
        twoDistanceLineEdit->setText(strList.at(0));
        twoPumpFeeLineEdit->setText(strList.at(1));
    }


    //属性
    QString searchAttributeListSQL = QString("select attribute,AttributePrice from SalesAttributeList where ContractNumber='%1' and EngineerName='%2' and StartTime='%3'")
            .arg(twoCustomerNoStr,EngineerName,dateTime);
    QList<QStringList> AttributeList = db.sql_result(searchAttributeListSQL.toStdString().data());
    int count1 = AttributeList.count();
    if(count1 != 0){
        for(int i = 0; i<attribute_count; i++){
            for(int j = 0; j<count1; j++){
                if(twoAttributeCheckBoxList[i]->text() == AttributeList.at(j).at(0)){
                    twoAttributeCheckBoxList[i]->setCheckState(Qt::Checked);
                    twoAttributeLineEditList[i]->setText(AttributeList.at(j).at(1));
                    break;
                }
                else{
                    twoAttributeCheckBoxList[i]->setCheckState(Qt::Unchecked);
                }
            }
        }
    }
    else{
        for(int i = 0; i<attribute_count; i++){
            twoAttributeCheckBoxList[i]->setCheckState(Qt::Unchecked);
        }
    }

    //产品
    QString searchProductListSQL = QString("select product,ProductPrice from SalesProductList where ContractNumber='%1' and EngineerName='%2' and StartTime='%3'")
            .arg(twoCustomerNoStr,EngineerName,dateTime);
    QList<QStringList> ProductList = db.sql_result(searchProductListSQL.toStdString().data());
    int count2 = ProductList.count();
    if(count2 != 0){
        for(int i = 0; i<product_count; i++){
            for(int j = 0; j<count2; j++){
                if(twoProductCheckBoxList[i]->text() == ProductList.at(j).at(0)){
                    twoProductCheckBoxList[i]->setCheckState(Qt::Checked);
                    twoProductLineEditList[i]->setText(ProductList.at(j).at(1));
                    break;
                }
                else{
                    twoProductCheckBoxList[i]->setCheckState(Qt::Unchecked);
                }
            }
        }
    }
    else{
        for(int i = 0; i<product_count; i++){
            twoProductCheckBoxList[i]->setCheckState(Qt::Unchecked);
        }
    }


    ON_PrintXY();
}

void xiaoshouhetongguanliDlg::on_threeQuanXuanBtn()
{
    SQL3 = SQL3.replace("0 是否修改","2 是否修改");
    db.showview(SQL3,threeEngineerListView,&threeEngineerListModel);

    int rowCount = threeEngineerListModel->rowCount();
    for(int i = 0; i<rowCount; i++){
       threeEngineerListModel->item(i,2)->setCheckState(Qt::Checked);
    }
}

void xiaoshouhetongguanliDlg::on_threeQuXiaoBtn()
{
    SQL3 = SQL3.replace("2 是否修改","0 是否修改");
    db.showview(SQL3,threeEngineerListView,&threeEngineerListModel);

    int rowCount = threeEngineerListModel->rowCount();
    for(int i = 0; i<rowCount; i++){
       threeEngineerListModel->item(i,2)->setCheckState(Qt::Checked);
    }
}

void xiaoshouhetongguanliDlg::on_threeUpdateBtn()
{
    int rowCount = threeEngineerListModel->rowCount();
    int Flag = 0;
    for(int i = 0; i<rowCount; i++){
       if(threeEngineerListModel->item(i,2)->checkState() == 2){
           Flag++;
       }
    }
    if(Flag == 0){
        QMessageBox::information(this,tr("提示信息"),tr("请至少选择一个要更改的工程"),0,0,0);
        return;
    }

    progressDialog = new QProgressDialog(this);
    progressDialog->setFixedSize(500,100);
    progressDialog->setWindowModality(Qt::WindowModal);//采用模拟的方式进行显示，即显示进度的同时，其他窗口将不响应输入信号
    progressDialog->setWindowTitle(tr("请等待"));//设置标题的显示时间
    progressDialog->setLabelText(tr("正在修改出车单价格和运距"));
    progressDialog->setCancelButtonText(tr("取消"));//退出按钮名字

    int recordCount = 0;
    for(int i = 0; i<rowCount; i++){
       if(threeEngineerListModel->item(i,2)->checkState() == 2){
           QString CustomerName = threeEngineerListModel->item(i,0)->text();
           QString Engineering = threeEngineerListModel->item(i,1)->text();
           QString searchNoticeCount = QString("SELECT count(1) from ProductionNotice where Customer='%1' and Engineering='%2' and OutboundTime between '%3' and '%4'")
                   .arg(CustomerName,Engineering,threeDateTimeEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),threeDateTimeEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
           recordCount += db.sql_fetchrow_plus(searchNoticeCount,0).toInt();
       }
    }
    progressDialog->setRange(0,recordCount);//设置显示的范围

    QString EngineerStrList;
    int progressValue = 0;
    for(int i = 0; i<rowCount; i++){
       if(threeEngineerListModel->item(i,2)->checkState() == 2){
           QString CustomerName = threeEngineerListModel->item(i,0)->text();
           QString Engineering = threeEngineerListModel->item(i,1)->text();
           EngineerStrList = EngineerStrList.append(QString("'%1',").arg(Engineering));
           QString searchNotice = QString("SELECT StrengthGrade,OutboundTime,RecordNumber from ProductionNotice where Customer='%1' and Engineering='%2' and OutboundTime between '%3' and '%4'")
                   .arg(CustomerName,Engineering,threeDateTimeEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),threeDateTimeEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
           QList<QStringList> NoticeResult = db.sql_result(searchNotice);
           for(int j = 0; j<NoticeResult.count(); j++){
               if(NoticeResult.at(j).count()<3){
                   return;
               }
               QString StrengthGrade = NoticeResult.at(j).at(0);
               QString OutboundTime = NoticeResult.at(j).at(1);
               QString RecordNumber = NoticeResult.at(j).at(2);

               //计算每方单价
               double total = 0;
               QString searchPriceSQL = QString("select ProductPrice from SalesProductList where CustomerName='%1' and product='%2' and EngineerName='%3' and StartTime<='%4' order by StartTime desc limit 1")
                                               .arg(CustomerName,StrengthGrade.section(" ",0,0),Engineering,OutboundTime);
               total += db.sql_fetchrow_plus(searchPriceSQL,0).toDouble();
               int count = StrengthGrade.count(" ");//求出强度等级中包含的产品及属性个数
               for(int k = 1; k < count; k++){
                   QString searchSQL = QString("select AttributePrice from SalesAttributeList where CustomerName='%1' and attribute='%2' and EngineerName='%3' and StartTime<='%4' order by StartTime desc limit 1")
                                               .arg(CustomerName,StrengthGrade.section(" ",k,k),Engineering,OutboundTime);
                   total += db.sql_fetchrow_plus(searchSQL,0).toDouble();
               }
               QString PricePerParty = QString::number(total);

               //获取工程运距
               QString searchYunJuSQL = QString("select Distance from SalesContractCustomerEngineeringForm where CustomerName='%1' and ProjectName='%2' and DateTime<='%3' order by DateTime desc limit 1")
                                                .arg(CustomerName,Engineering,OutboundTime);
               QString Distance = db.sql_fetchrow_plus(searchYunJuSQL,0);

               //获取运费
               //查找运费
               QString searchFreightPrice = QString("select Freight from ConcreteCarFreightSet where MinimumMileage+0<='%1' and MaximumMileage+0>='%1'").arg(Distance);
               QString FreightPrice = db.sql_fetchrow_plus(searchFreightPrice,0);

               //更新出车单价格及运距
               QString updateNoticeSQL = QString("update ProductionNotice set Price='%1',Mileage='%2',FreightPrice='%3' where RecordNumber=%4").arg(PricePerParty,Distance,FreightPrice,RecordNumber);
               db.sql_exec(updateNoticeSQL);

               //设置当前的标题进度
               progressDialog->setValue(++progressValue);
               //如果检测到按钮取消被激活，就跳出去
               if(progressDialog->wasCanceled()){
                 return;
               }
           }
       }
    }

    EngineerStrList = EngineerStrList.left(EngineerStrList.length()-1);
    QString searchSQL = QString("select CONCAT(Customer,' ',Engineering,' ',StrengthGrade,' ',MID(MIN(OutboundTime),1,10),'--',MID(MAX(OutboundTime),1,10)) from \
                                ProductionNotice where Engineering IN (%1) and (Price IS NULL OR Price='') and OutboundTime BETWEEN '%2' AND '%3' GROUP BY Customer,Engineering,StrengthGrade")
                    .arg(EngineerStrList,threeDateTimeEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),threeDateTimeEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
    if(db.row_count(searchSQL)>0){
        QStringList DetailInfoList = db.find_CheNo(searchSQL);

        QString DetailInfo;
        for(int i = 0; i<DetailInfoList.count(); i++){
            DetailInfo = DetailInfo.append(DetailInfoList.at(i)).append("\n");
        }
    }

    QString insertSQL = QString("insert into ProductionNoticePriceCorrectRecord (updateEngineer,OutBoundTime,Operator,OperatingTime) values ('%1','%2','%3','%4')")
            .arg(EngineerStrList.replace("'",""),QString("%1--%2").arg(threeDateTimeEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),threeDateTimeEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss")),
                 userName,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    db.sql_exec(insertSQL);
}

void xiaoshouhetongguanliDlg::on_threeFindBtn()
{
    QString searchSQL = QString("select updateEngineer 修改的工程,OutBoundTime 修改的出车单日期,Operator 修改人,OperatingTime 修改时间 from ProductionNoticePriceCorrectRecord where OperatingTime \
                                between '%1' and '%2'").arg(threeUpdateDateTimeEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),threeUpdateDateTimeEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
    db.showview(searchSQL,threeUpdateDetailInfoView,&threeUpdateDetailInfoModel);
}

void xiaoshouhetongguanliDlg::on_threeCustomerFindBtn()
{
    SQL3 = QString("select CustomerName 客户名称,ProjectName 工程名称,0 是否修改 from SalesContractCustomerEngineeringForm where CustomerName = '%1' group by \
                    CustomerName,ProjectName order by CustomerName,ProjectName").arg(threeCustomerComBox->currentText());
    db.showview(SQL3,threeEngineerListView,&threeEngineerListModel);
}

void xiaoshouhetongguanliDlg::ON_PrintXY()
{
    customPlot->xAxis->setTicks(true);//x轴显示刻度
    customPlot->yAxis->setTicks(true);//y轴显示刻度

    customPlot->yAxis->setLabel("单价");
    if(twoBtnGroup->checkedId() == 1){
        customPlot->xAxis->setLabel(twoProductCombox->currentText()+"日期");
    }
    else if(twoBtnGroup->checkedId() == 2){
        customPlot->xAxis->setLabel(twoAttributeCombox->currentText()+"日期");
    }

    QVector<double> Price;
    QString searchPriceSQL;
    if(twoBtnGroup->checkedId() == 1){
        searchPriceSQL = QString("select ProductPrice from SalesProductList where CustomerName='%1' and product='%2' and EngineerName='%3' order by StartTime")
                .arg(twoCustomerLineEdit->text(),twoProductCombox->currentText(),twoEngineerLineEdit->text());
    }
    else if(twoBtnGroup->checkedId() == 2){
        searchPriceSQL = QString("select AttributePrice from SalesAttributeList where CustomerName='%1' and attribute='%2' and EngineerName='%3' order by StartTime")
                .arg(twoCustomerLineEdit->text(),twoAttributeCombox->currentText(),twoEngineerLineEdit->text());
    }
    QStringList PriceList = db.find_CheNo(searchPriceSQL);
    for(int i = 0; i < PriceList.count();i++){
      Price.append(PriceList[i].toDouble());
    }

    QVector<double> Day;
    QString searchDaySQL;
    if(twoBtnGroup->checkedId() == 1){
        searchDaySQL = QString("select StartTime from SalesProductList where CustomerName='%1' and product='%2' and EngineerName='%3' order by StartTime")
                .arg(twoCustomerLineEdit->text(),twoProductCombox->currentText(),twoEngineerLineEdit->text());
    }
    else if(twoBtnGroup->checkedId() == 2){
        searchDaySQL = QString("select StartTime from SalesAttributeList where CustomerName='%1' and attribute='%2' and EngineerName='%3' order by StartTime")
                .arg(twoCustomerLineEdit->text(),twoAttributeCombox->currentText(),twoEngineerLineEdit->text());
    }
    QStringList DayList = db.find_CheNo(searchDaySQL);
    for(int i = 0; i < DayList.count();i++){
        QDateTime time = QDateTime::fromString(DayList[i],"yyyy-MM-dd hh:mm:ss");
        double xianshiTime = time.toTime_t();
        Day.append(xianshiTime);
    }

    if(Day.isEmpty()||Price.isEmpty()){
        return;
    }

    customPlot->graph(0)->setData(Day,Price);// 更新数据

    //设定x,y轴显示范围
    QString searchSQL;
    if(twoBtnGroup->checkedId() == 1){
        searchSQL = QString("select MAX(ProductPrice+0),MIN(ProductPrice+0) from SalesProductList where CustomerName='%1' and product='%2' and EngineerName='%3'")
                .arg(twoCustomerLineEdit->text(),twoProductCombox->currentText(),twoEngineerLineEdit->text());
    }
    else if(twoBtnGroup->checkedId() == 2){
        searchSQL = QString("select MAX(AttributePrice+0),MIN(AttributePrice+0) from SalesAttributeList where CustomerName='%1' and attribute='%2' and EngineerName='%3'")
                .arg(twoCustomerLineEdit->text(),twoAttributeCombox->currentText(),twoEngineerLineEdit->text());
    }
    QStringList resList = db.CreatStrList(searchSQL);
    if(resList.count() == 2){
        customPlot->yAxis->setRange(resList[1].toDouble()-20,resList[0].toDouble()+20); //自定义y轴值的显示范围
    }
    customPlot->xAxis->setRange(Day.first()-24*3600,Day.last()+24*3600);//自定义x轴值的显示范围

    // configure bottom axis to show date and time instead of number:
    customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    customPlot->xAxis->setDateTimeFormat("yy年MM月dd日");

    // 重绘
    customPlot->replot();
}

void xiaoshouhetongguanliDlg::my_mouseMove(QMouseEvent *event)
{
    //获取鼠标坐标点
    int x_pos = event->pos().x();
    // 把鼠标坐标点 转换为 QCustomPlot 内部坐标值 （pixelToCoord 函数）
    // coordToPixel 函数与之相反 是把内部坐标值 转换为外部坐标点
    double x_val = customPlot->xAxis->pixelToCoord(x_pos);
    QDateTime time;
    QString tshow = time.fromTime_t(x_val).toString("yyyy-MM-dd");
    QString t = time.fromTime_t(x_val).toString("yyyy-MM-dd 04:00:00");
    QString Price;
    if(twoBtnGroup->checkedId() == 1){
        Price = QString("select ProductPrice from SalesProductList where CustomerName='%1' and product='%2' and EngineerName='%3' and StartTime='%4'")
                .arg(twoCustomerLineEdit->text(),twoProductCombox->currentText(),twoEngineerLineEdit->text(),t);
    }
    else if(twoBtnGroup->checkedId() == 2){
        Price = QString("select AttributePrice from SalesAttributeList where CustomerName='%1' and attribute='%2' and EngineerName='%3' and StartTime='%4'")
                .arg(twoCustomerLineEdit->text(),twoAttributeCombox->currentText(),twoEngineerLineEdit->text(),t);
    }
    QString DayList = db.sql_fetchrow_plus(Price,0);
    // 然后打印在界面上
    if(DayList != NULL)
    {
        customPlot->setToolTip(tr("(%1,%2)").arg(tshow).arg(DayList));
    }else{
        customPlot->setToolTip("");
    }
}
