#include "xiaoshouzongzhangdlg.h"

extern mymysql db;
extern myTCPsocket *sockClient;
extern QString userName;

xiaoshouzongzhangDlg::xiaoshouzongzhangDlg(QWidget *parent) :
    QDialog(parent)
{
    tabWidget = new QTabWidget(this);
    xiaoshouzongzhang = new QWidget(this);
    kehuqichushezhi = new QWidget(this);
    fukuanshezhi = new QWidget(this);
    chonghongshezhi = new QWidget(this);
    zhangkuanjiecun = new QWidget(this);

    creatTabPage1();
    creatTabPage2();
    creatTabPage3();
    creatTabPage4();
    creatTabPage5();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tabWidget);
}

void xiaoshouzongzhangDlg::refresh()
{

}

void xiaoshouzongzhangDlg::keyPressEvent(QKeyEvent *event)
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

void xiaoshouzongzhangDlg::creatTabPage1()
{
    SQL1 = "SELECT M.CustomerName 客户名称,\
                    M.ProjectName 工程名称,\
                    M.InitialBalance 上期材料款,\
                    IF(N.benqiTotal IS NULL,0,N.benqiTotal)+M.chonghongAmount 本期材料款,\
                    IF(N.benqiWeiTotal IS NULL,0,N.benqiWeiTotal) 本期未核对材料款,\
                    IF(N.benqiYiTotal IS NULL,0,N.benqiYiTotal)+M.chonghongAmount 本期已核对材料款,\
                    IF(N.dibengTotal IS NULL,0,N.dibengTotal) 地泵费,\
                    IF(N.chebengTotal IS NULL,0,N.chebengTotal) 车泵费,\
                    M.InitialBalance+IF(N.benqiTotal IS NULL,0,N.benqiTotal)+M.chonghongAmount 累计材料款,\
                    M.paymentAmount 客户付款金额,\
                    M.paymentAmount-M.InitialBalance-IF(N.benqiTotal IS NULL,0,N.benqiTotal)-M.chonghongAmount-IF(N.dibengTotal IS NULL,0,N.dibengTotal)-IF(N.chebengTotal IS NULL,0,N.chebengTotal) 客户余额,\
                    M.BalanceDateTime 本期起始日期 FROM SalesContractCustomerEngineeringForm M LEFT JOIN\
          (SELECT SUM(ReceiptVolume*Price) benqiTotal,\
                  SUM(CASE WHEN Flag='2' THEN ReceiptVolume * Price ELSE 0 END) benqiWeiTotal,\
                  SUM(CASE WHEN Flag='0' THEN ReceiptVolume * Price ELSE 0 END) benqiYiTotal,A.Customer,A.Engineering,\
                  SUM(CASE WHEN PouringMethod='地泵' THEN ReceiptVolume * B.PumpFee ELSE 0 END) dibengTotal,\
                  SUM(CASE WHEN PouringMethod='车泵' THEN ReceiptVolume * B.CarPumpFee ELSE 0 END) chebengTotal\
           FROM ProductionNotice A LEFT JOIN (SELECT * FROM SalesContractCustomerEngineeringForm GROUP BY CustomerName,ProjectName) B \
          ON (A.Customer=B.CustomerName AND A.Engineering=B.ProjectName) WHERE A.OutboundTime>B.BalanceDateTime GROUP BY A.Customer,A.Engineering) N \
          ON (M.CustomerName=N.Customer AND M.ProjectName=N.Engineering) GROUP BY M.CustomerName,M.ProjectName";

    QLabel *CustomerNameLabel = new QLabel(tr("客户名称"));
    CustomerNameLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *EngineerNameLabel = new QLabel(tr("工程名称"));
    EngineerNameLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *RemainingSumLabel = new QLabel(tr("客户余额"));
    RemainingSumLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *BalanceDateLabel = new QLabel(tr("结存日期"));
    BalanceDateLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    CustomerLineEdit = new QLineEdit(this);
    CustomerLineEdit->setReadOnly(true);
    EngineerLineEdit = new QLineEdit(this);
    EngineerLineEdit->setReadOnly(true);
    RemainingSumLineEdit = new QLineEdit(this);

    BalanceDateEdit = new QDateTimeEdit(this);
    BalanceDateEdit->setDate(QDate::currentDate());
    BalanceDateEdit->setCalendarPopup(true);
    connect(BalanceDateEdit,SIGNAL(dateTimeChanged(QDateTime)),this,SLOT(on_BalanceDateEdit()));

    BalanceBtn = new QPushButton(tr("结存"),this);
    BalanceBtn->setFixedWidth(120);
    connect(BalanceBtn,SIGNAL(clicked()),this,SLOT(on_BalanceBtn()));


    CustomerCheckBox = new QCheckBox(tr("客户名称"),this);

    CustomerNameCombox = new myComboBox(this);
    db.sql_fillComboBoxItem("SELECT CustomerName FROM CustomerFiles",CustomerNameCombox);

    FindBtn = new QPushButton(tr("查找"),this);
    FindBtn->setFixedWidth(120);
    connect(FindBtn,SIGNAL(clicked()),this,SLOT(on_FindBtn()));

    oneView = new QTableView(this);
    db.showview(SQL1,oneView,&oneModel);
    connect(oneView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(on_oneView()));
    oneView->setColumnWidth(0,210);
    oneView->setColumnWidth(1,230);
    oneView->setColumnWidth(4,120);
    oneView->setColumnWidth(5,120);
    oneView->setColumnWidth(9,130);

    QHBoxLayout *balanceLayout = new QHBoxLayout;
    balanceLayout->addWidget(CustomerNameLabel,0);
    balanceLayout->addWidget(CustomerLineEdit,2);
    balanceLayout->addWidget(EngineerNameLabel,0);
    balanceLayout->addWidget(EngineerLineEdit,2);
    balanceLayout->addWidget(RemainingSumLabel,0);
    balanceLayout->addWidget(RemainingSumLineEdit,1);
    balanceLayout->addWidget(BalanceDateLabel,0);
    balanceLayout->addWidget(BalanceDateEdit,1);
    balanceLayout->addWidget(BalanceBtn,1);
    balanceLayout->addStretch(2);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(CustomerCheckBox,0);
    hlayout->addWidget(CustomerNameCombox,2);
    hlayout->addWidget(FindBtn);
    hlayout->addStretch(3);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(balanceLayout);
    vlayout->addSpacing(10);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(oneView);

    xiaoshouzongzhang->setLayout(vlayout);
    tabWidget->addTab(xiaoshouzongzhang,tr("客户总账"));
}

void xiaoshouzongzhangDlg::creatTabPage2()
{
    SQL2 = "SELECT CustomerName 客户名称,ProjectName 工程名称,InitialBalance 上期材料款,BalanceDateTime 上期材料款截止日期 FROM SalesContractCustomerEngineeringForm GROUP BY CustomerName,ProjectName";

    QLabel *CustomerNameLabel = new QLabel(tr("客户名称"));
    CustomerNameLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *EngineerNameLabel = new QLabel(tr("工程名称"));
    EngineerNameLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *InitialBalanceLabel = new QLabel(tr("上期材料款"));
    InitialBalanceLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *BalanceDateTimeLabel = new QLabel(tr("上期材料款截止日期"));
    BalanceDateTimeLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    twoCustomerLineEdit = new QLineEdit(this);
    twoCustomerLineEdit->setReadOnly(true);

    twoEngineerLineEdit = new QLineEdit(this);
    twoEngineerLineEdit->setReadOnly(true);

    twoInitialBalanceLineEdit = new QLineEdit(this);

    twoBalanceDateTime = new QDateTimeEdit(this);
    twoBalanceDateTime->setDate(QDate::currentDate());
    twoBalanceDateTime->setCalendarPopup(true);

    twoUpdateBtn = new QPushButton(tr("修改期初"));
    twoUpdateBtn->setFixedWidth(120);
    connect(twoUpdateBtn,SIGNAL(clicked()),this,SLOT(on_twoUpdateBtn()));

    twoCustomerCheckBox = new QCheckBox(tr("客户名称"),this);

    twoCustomerCombox = new myComboBox(this);
    db.sql_fillComboBoxItem("SELECT CustomerName FROM CustomerFiles",twoCustomerCombox);

    twoFindBtn = new QPushButton(tr("查找"),this);
    twoFindBtn->setFixedWidth(120);
    connect(twoFindBtn,SIGNAL(clicked()),this,SLOT(on_twoFindBtn()));


    twoView = new QTableView(this);
    db.showview(SQL2,twoView,&twoModel);
    connect(twoView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(on_doubleClickTwoView()));
    twoView->setColumnWidth(0,210);
    twoView->setColumnWidth(1,250);
    twoView->setColumnWidth(3,150);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(CustomerNameLabel,0);
    hlayout->addWidget(twoCustomerLineEdit,1);
    hlayout->addWidget(EngineerNameLabel,0);
    hlayout->addWidget(twoEngineerLineEdit,1);
    hlayout->addWidget(InitialBalanceLabel,0);
    hlayout->addWidget(twoInitialBalanceLineEdit,1);
    hlayout->addWidget(BalanceDateTimeLabel,0);
    hlayout->addWidget(twoBalanceDateTime,0);
    hlayout->addWidget(twoUpdateBtn,1);
    hlayout->addStretch(2);

    QHBoxLayout *hlayout1 = new QHBoxLayout;
    hlayout1->addWidget(twoCustomerCheckBox,0);
    hlayout1->addWidget(twoCustomerCombox,2);
    hlayout1->addWidget(twoFindBtn,1);
    hlayout1->addStretch(3);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(hlayout);
    vlayout->addSpacing(10);
    vlayout->addLayout(hlayout1);
    vlayout->addWidget(twoView);

    kehuqichushezhi->setLayout(vlayout);
    tabWidget->addTab(kehuqichushezhi,tr("客户期初数据设置"));
}

void xiaoshouzongzhangDlg::creatTabPage3()
{
    SQL3 = "select CustomerName 客户名称,EngineerName 工程名称,TransferAccount 付款金额,TransferType 付款方式,TransferDate 付款日期,OperatingTime 录入日期,Operator 录入人 from TransferRecord limit 0";

    QLabel *CustomerNameLabel = new QLabel(tr("客户名称"));
    CustomerNameLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *EngineerLabel = new QLabel(tr("工程名称"));
    EngineerLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *payAccountLabel = new QLabel(tr("付款金额"));
    payAccountLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *payTypeLabel = new QLabel(tr("付款方式"));
    payTypeLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *payDateLabel = new QLabel(tr("付款日期"));
    payDateLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *OperatingDateLabel = new QLabel(tr("操作时间"));
    OperatingDateLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *FuHaoLabel = new QLabel(tr("--"));
    FuHaoLabel->setAlignment(Qt::AlignVCenter|Qt::AlignCenter);

    threeCustomerCombox = new myComboBox(this);
    db.sql_fillComboBoxItem("SELECT CustomerName FROM CustomerFiles",threeCustomerCombox);
    connect(threeCustomerCombox,SIGNAL(editTextChanged(QString)),this,SLOT(on_threeCustomerCombox()));

    threeEngineerCombox = new myComboBox(this);

    threeTransferTypeCombox = new QComboBox(this);
    threeTransferTypeCombox->setEditable(true);
    threeTransferTypeCombox->setView(new QListView(this));
    threeTransferTypeCombox->addItem("现金");
    threeTransferTypeCombox->addItem("转账");
    threeTransferTypeCombox->addItem("承兑");

    threeTransferAccountLineEdit = new QLineEdit(this);

    threeTransferDate = new QDateTimeEdit(this);
    threeTransferDate->setDate(QDate::currentDate());
    threeTransferDate->setCalendarPopup(true);

    threeConfirmBtn = new QPushButton(tr("确认"),this);
    threeConfirmBtn->setFixedWidth(120);
    connect(threeConfirmBtn,SIGNAL(clicked()),this,SLOT(on_threeConfirmBtn()));

    threeFindCustomerCheckBox = new QCheckBox(tr("客户名称"),this);

    threeFindCustomerCombox = new myComboBox(this);
    db.sql_fillComboBoxItem("SELECT CustomerName FROM CustomerFiles",threeFindCustomerCombox);

    threeOperatingDate1 = new QDateTimeEdit(this);
    threeOperatingDate1->setDate(QDate::currentDate());
    threeOperatingDate1->setCalendarPopup(true);
    threeOperatingDate2 = new QDateTimeEdit(this);
    threeOperatingDate2->setDate(QDate::currentDate().addDays(1));
    threeOperatingDate2->setCalendarPopup(true);

    threeFindBtn = new QPushButton(tr("查询"),this);
    threeFindBtn->setFixedWidth(120);
    connect(threeFindBtn,SIGNAL(clicked()),this,SLOT(on_threeFindBtn()));

    threeView = new QTableView(this);
    db.showview(SQL3,threeView,&threeModel);
    threeView->setColumnWidth(0,210);
    threeView->setColumnWidth(1,250);
    threeView->setColumnWidth(4,130);
    threeView->setColumnWidth(5,130);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(CustomerNameLabel,0);
    hlayout->addWidget(threeCustomerCombox,2);
    hlayout->addWidget(EngineerLabel,0);
    hlayout->addWidget(threeEngineerCombox,2);
    hlayout->addWidget(payAccountLabel,0);
    hlayout->addWidget(threeTransferAccountLineEdit,1);
    hlayout->addWidget(payTypeLabel,0);
    hlayout->addWidget(threeTransferTypeCombox,1);
    hlayout->addWidget(payDateLabel,0);
    hlayout->addWidget(threeTransferDate,1);
    hlayout->addWidget(threeConfirmBtn,1);

    QHBoxLayout *hlayout1 = new QHBoxLayout;
    hlayout1->addWidget(OperatingDateLabel,0);
    hlayout1->addWidget(threeOperatingDate1,0);
    hlayout1->addWidget(FuHaoLabel,0);
    hlayout1->addWidget(threeOperatingDate2,0);
    hlayout1->addWidget(threeFindCustomerCheckBox,0);
    hlayout1->addWidget(threeFindCustomerCombox,2);
    hlayout1->addWidget(threeFindBtn,1);
    hlayout1->addStretch(2);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(hlayout);
    vlayout->addSpacing(10);
    vlayout->addLayout(hlayout1);
    vlayout->addWidget(threeView);

    fukuanshezhi->setLayout(vlayout);
    tabWidget->addTab(fukuanshezhi,tr("收付款操作"));
}

void xiaoshouzongzhangDlg::creatTabPage4()
{
    SQL4 = "select CustomerName 客户名称,EngineerName 工程名称,ChongHongAccount 冲红金额,Remarks 备注,OperatorTime 录入日期,Operator 录入人 from ChongHongRecord_Customer limit 0";

    QLabel *CustomerNameLabel = new QLabel(tr("客户名称"));
    CustomerNameLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *EngineerLabel = new QLabel(tr("工程名称"));
    EngineerLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *ChongHongAccountLabel = new QLabel(tr("冲红金额"));
    ChongHongAccountLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *RemarksLabel = new QLabel(tr("备注"));
    RemarksLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    QLabel *OperatingDateLabel = new QLabel(tr("操作时间"));
    OperatingDateLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *FuHaoLabel = new QLabel(tr("--"));
    FuHaoLabel->setAlignment(Qt::AlignVCenter|Qt::AlignCenter);

    fourCustomerCombox = new myComboBox(this);
    db.sql_fillComboBoxItem("SELECT CustomerName FROM CustomerFiles",fourCustomerCombox);
    connect(fourCustomerCombox,SIGNAL(editTextChanged(QString)),this,SLOT(on_fourCustomerCombox()));

    fourEngineerCombox = new myComboBox(this);

    fourRemarksLineEdit = new QLineEdit(this);

    fourChongHongAccountLineEdit = new QLineEdit(this);

    fourConfirmBtn = new QPushButton(tr("确认"),this);
    fourConfirmBtn->setFixedWidth(120);
    connect(fourConfirmBtn,SIGNAL(clicked()),this,SLOT(on_fourConfirmBtn()));

    fourFindCustomerCheckBox = new QCheckBox(tr("客户名称"),this);

    fourFindCustomerCombox = new myComboBox(this);
    db.sql_fillComboBoxItem("SELECT CustomerName FROM CustomerFiles",fourFindCustomerCombox);

    fourOperatingDate1 = new QDateTimeEdit(this);
    fourOperatingDate1->setDate(QDate::currentDate());
    fourOperatingDate1->setCalendarPopup(true);
    fourOperatingDate2 = new QDateTimeEdit(this);
    fourOperatingDate2->setDate(QDate::currentDate().addDays(1));
    fourOperatingDate2->setCalendarPopup(true);

    fourFindBtn = new QPushButton(tr("查询"),this);
    fourFindBtn->setFixedWidth(120);
    connect(fourFindBtn,SIGNAL(clicked()),this,SLOT(on_fourFindBtn()));

    fourView = new QTableView(this);
    db.showview(SQL4,fourView,&fourModel);
    fourView->setColumnWidth(0,210);
    fourView->setColumnWidth(1,250);
    fourView->setColumnWidth(4,130);
    fourView->setColumnWidth(5,130);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(CustomerNameLabel,0);
    hlayout->addWidget(fourCustomerCombox,2);
    hlayout->addWidget(EngineerLabel,0);
    hlayout->addWidget(fourEngineerCombox,2);
    hlayout->addWidget(ChongHongAccountLabel,0);
    hlayout->addWidget(fourChongHongAccountLineEdit,1);
    hlayout->addWidget(RemarksLabel,0);
    hlayout->addWidget(fourRemarksLineEdit,2);
    hlayout->addWidget(fourConfirmBtn,1);

    QHBoxLayout *hlayout1 = new QHBoxLayout;
    hlayout1->addWidget(OperatingDateLabel,0);
    hlayout1->addWidget(fourOperatingDate1,0);
    hlayout1->addWidget(FuHaoLabel,0);
    hlayout1->addWidget(fourOperatingDate2,0);
    hlayout1->addWidget(fourFindCustomerCheckBox,0);
    hlayout1->addWidget(fourFindCustomerCombox,2);
    hlayout1->addWidget(fourFindBtn,1);
    hlayout1->addStretch(2);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(hlayout);
    vlayout->addSpacing(10);
    vlayout->addLayout(hlayout1);
    vlayout->addWidget(fourView);

    chonghongshezhi->setLayout(vlayout);
    tabWidget->addTab(chonghongshezhi,tr("冲红操作"));
}

void xiaoshouzongzhangDlg::creatTabPage5()
{
    SQL5 = "select Customer 客户名称,Engineer 工程名称,Account 结存余额,balanceDate 结存时间,Operator 操作人,OperatingTime 操作时间 from BalanceRecord_Customer limit 0";

    QLabel *TimeLabel = new QLabel(tr("结存时间"));
    TimeLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *FuHaoLabel = new QLabel(tr("--"));
    FuHaoLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    fiveBalanceDate1 = new QDateTimeEdit(this);
    fiveBalanceDate1->setDate(QDate::currentDate());
    fiveBalanceDate1->setCalendarPopup(true);
    fiveBalanceDate2 = new QDateTimeEdit(this);
    fiveBalanceDate2->setDate(QDate::currentDate().addDays(1));
    fiveBalanceDate2->setCalendarPopup(true);

    fiveCustomerCheck = new QCheckBox(tr("客户名称"),this);
    fiveEngineerCheck = new QCheckBox(tr("工程名称"),this);

    fiveCustomerCombox = new myComboBox(this);
    db.sql_fillComboBoxItem("SELECT CustomerName FROM CustomerFiles",fiveCustomerCombox);

    fiveEngineerCombox = new myComboBox(this);
    db.sql_fillComboBoxItem("select ProjectName from SalesContractCustomerEngineeringForm group by ProjectName",fiveEngineerCombox);

    fiveBalanceView = new QTableView(this);
    db.showview(SQL5,fiveBalanceView,&fiveBalanceModel);

    fiveFindBtn = new QPushButton(tr("查找"),this);
    fiveFindBtn->setFixedWidth(120);
    connect(fiveFindBtn,SIGNAL(clicked()),this,SLOT(on_fiveBtn()));

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(TimeLabel,0);
    hlayout->addWidget(fiveBalanceDate1,1);
    hlayout->addWidget(FuHaoLabel,0);
    hlayout->addWidget(fiveBalanceDate2,1);
    hlayout->addWidget(fiveCustomerCheck,0);
    hlayout->addWidget(fiveCustomerCombox,1);
    hlayout->addWidget(fiveEngineerCheck,0);
    hlayout->addWidget(fiveEngineerCombox,1);
    hlayout->addWidget(fiveFindBtn,1);
    hlayout->addStretch(2);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(fiveBalanceView);


    zhangkuanjiecun->setLayout(vlayout);
    tabWidget->addTab(zhangkuanjiecun,tr("账款结存记录"));
}

void xiaoshouzongzhangDlg::on_BalanceBtn()
{
    if(CustomerLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择一个客户和工程"),0,0,0);
        return;
    }

    QString updateSQL = QString("update SalesContractCustomerEngineeringForm set InitialBalance='%1',paymentAmount='0',chonghongAmount='0',BalanceDateTime='%2' where CustomerName='%3' and ProjectName='%4'")
            .arg(QString::number(-RemainingSumLineEdit->text().toDouble(),'f',2),BalanceDateEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"),CustomerLineEdit->text(),EngineerLineEdit->text());
    db.sql_exec(updateSQL);

    QString insertSQL = QString("insert into BalanceRecord_Customer (Customer,Engineer,Account,balanceDate,Operator,OperatingTime) values ('%1','%2','%3','%4','%5','%6')")
            .arg(CustomerLineEdit->text(),EngineerLineEdit->text(),RemainingSumLineEdit->text(),BalanceDateEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"),userName,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    db.sql_exec(insertSQL);

    on_FindBtn();

    CustomerLineEdit->clear();
    EngineerLineEdit->clear();
    RemainingSumLineEdit->clear();
}

void xiaoshouzongzhangDlg::on_FindBtn()
{
    QString CustomerName;
    if(CustomerCheckBox->checkState() == 2){
        CustomerName = QString(" where M.CustomerName='%1'").arg(CustomerNameCombox->currentText());
    }
    QString searchSQL = QString("SELECT M.CustomerName 客户名称,\
                                M.ProjectName 工程名称,\
                                M.InitialBalance 上期材料款,\
                                IF(N.benqiTotal IS NULL,0,N.benqiTotal)+M.chonghongAmount 本期材料款,\
                                IF(N.benqiWeiTotal IS NULL,0,N.benqiWeiTotal) 本期未核对材料款,\
                                IF(N.benqiYiTotal IS NULL,0,N.benqiYiTotal)+M.chonghongAmount 本期已核对材料款,\
                                IF(N.dibengTotal IS NULL,0,N.dibengTotal) 地泵费,\
                                IF(N.chebengTotal IS NULL,0,N.chebengTotal) 车泵费,\
                                M.InitialBalance+IF(N.benqiTotal IS NULL,0,N.benqiTotal)+M.chonghongAmount 累计材料款,\
                                M.paymentAmount 客户付款金额,\
                                M.paymentAmount-M.InitialBalance-IF(N.benqiTotal IS NULL,0,N.benqiTotal)-M.chonghongAmount-IF(N.dibengTotal IS NULL,0,N.dibengTotal)-IF(N.chebengTotal IS NULL,0,N.chebengTotal) 客户余额,\
                                M.BalanceDateTime 本期起始日期 FROM SalesContractCustomerEngineeringForm M LEFT JOIN\
                      (SELECT SUM(ReceiptVolume*Price) benqiTotal,\
                              SUM(CASE WHEN Flag='2' THEN ReceiptVolume * Price ELSE 0 END) benqiWeiTotal,\
                              SUM(CASE WHEN Flag='0' THEN ReceiptVolume * Price ELSE 0 END) benqiYiTotal,A.Customer,A.Engineering,\
                              SUM(CASE WHEN PouringMethod='地泵' THEN ReceiptVolume * B.PumpFee ELSE 0 END) dibengTotal,\
                              SUM(CASE WHEN PouringMethod='车泵' THEN ReceiptVolume * B.CarPumpFee ELSE 0 END) chebengTotal\
                       FROM ProductionNotice A LEFT JOIN (SELECT * FROM SalesContractCustomerEngineeringForm GROUP BY CustomerName,ProjectName) B \
                      ON (A.Customer=B.CustomerName AND A.Engineering=B.ProjectName) WHERE A.OutboundTime>B.BalanceDateTime GROUP BY A.Customer,A.Engineering) N \
                      ON (M.CustomerName=N.Customer AND M.ProjectName=N.Engineering) %1 GROUP BY M.CustomerName,M.ProjectName").arg(CustomerName);
    db.showview(searchSQL,oneView,&oneModel);
}

void xiaoshouzongzhangDlg::on_oneView()
{
    int row = oneView->currentIndex().row();
    CustomerLineEdit->setText(oneModel->item(row,0)->text());
    EngineerLineEdit->setText(oneModel->item(row,1)->text());

    QString searchSQL = QString("SELECT M.paymentAmount-M.InitialBalance-IF(N.benqiTotal IS NULL,0,N.benqiTotal)-M.chonghongAmount\
                                 FROM SalesContractCustomerEngineeringForm M LEFT JOIN\
                      (SELECT SUM(ReceiptVolume*Price) benqiTotal,\
                              SUM(CASE WHEN Flag='2' THEN ReceiptVolume * Price ELSE 0 END) benqiWeiTotal,\
                              SUM(CASE WHEN Flag='0' THEN ReceiptVolume * Price ELSE 0 END) benqiYiTotal,A.Customer,A.Engineering \
                       FROM ProductionNotice A LEFT JOIN (SELECT * FROM SalesContractCustomerEngineeringForm GROUP BY CustomerName,ProjectName) B \
                      ON (A.Customer=B.CustomerName AND A.Engineering=B.ProjectName) WHERE A.OutboundTime>B.BalanceDateTime and A.OutboundTime<='%1' GROUP BY A.Customer,A.Engineering) N \
                      ON (M.CustomerName=N.Customer AND M.ProjectName=N.Engineering) where M.CustomerName='%2' and M.ProjectName='%3' GROUP BY M.CustomerName,M.ProjectName")
            .arg(BalanceDateEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"),CustomerLineEdit->text(),EngineerLineEdit->text());
    RemainingSumLineEdit->setText(db.sql_fetchrow_plus(searchSQL,0));
    if(RemainingSumLineEdit->text().isEmpty()){
        RemainingSumLineEdit->setText("0");
    }
}

void xiaoshouzongzhangDlg::on_BalanceDateEdit()
{
    QString searchSQL = QString("SELECT M.paymentAmount-M.InitialBalance-IF(N.benqiTotal IS NULL,0,N.benqiTotal)-M.chonghongAmount\
                                FROM SalesContractCustomerEngineeringForm M LEFT JOIN\
                      (SELECT SUM(ReceiptVolume*Price) benqiTotal,\
                              SUM(CASE WHEN Flag='2' THEN ReceiptVolume * Price ELSE 0 END) benqiWeiTotal,\
                              SUM(CASE WHEN Flag='0' THEN ReceiptVolume * Price ELSE 0 END) benqiYiTotal,A.Customer,A.Engineering \
                       FROM ProductionNotice A LEFT JOIN (SELECT * FROM SalesContractCustomerEngineeringForm GROUP BY CustomerName,ProjectName) B \
                      ON (A.Customer=B.CustomerName AND A.Engineering=B.ProjectName) WHERE A.OutboundTime>B.BalanceDateTime and A.OutboundTime<='%1' GROUP BY A.Customer,A.Engineering) N \
                      ON (M.CustomerName=N.Customer AND M.ProjectName=N.Engineering) where M.CustomerName='%2' and M.ProjectName='%3' GROUP BY M.CustomerName,M.ProjectName")
            .arg(BalanceDateEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"),CustomerLineEdit->text(),EngineerLineEdit->text());
    RemainingSumLineEdit->setText(db.sql_fetchrow_plus(searchSQL,0));
    if(RemainingSumLineEdit->text().isEmpty()){
        RemainingSumLineEdit->setText("0");
    }
}

void xiaoshouzongzhangDlg::on_doubleClickTwoView()
{
    int row = twoView->currentIndex().row();
    twoCustomerLineEdit->setText(twoModel->item(row,0)->text());
    twoEngineerLineEdit->setText(twoModel->item(row,1)->text());
    twoInitialBalanceLineEdit->setText(twoModel->item(row,2)->text());
    twoBalanceDateTime->setDateTime(QDateTime::fromString(twoModel->item(row,3)->text(),"yyyy-MM-dd hh:mm:ss"));
}

void xiaoshouzongzhangDlg::on_twoUpdateBtn()
{
    if(twoCustomerLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择一个客户"),0,0,0);
        return;
    }
    QString updateSQL = QString("update SalesContractCustomerEngineeringForm set InitialBalance='%1',BalanceDateTime='%2' where CustomerName='%3' and ProjectName='%4'")
            .arg(twoInitialBalanceLineEdit->text(),twoBalanceDateTime->dateTime().toString("yyyy-MM-dd hh:mm:ss"),twoCustomerLineEdit->text(),twoEngineerLineEdit->text());
    int res = db.sql_exec(updateSQL);
    if(res == 0){
        twoCustomerLineEdit->clear();
        twoEngineerLineEdit->clear();
        twoInitialBalanceLineEdit->clear();
        on_twoFindBtn();
        QMessageBox::information(this,tr("提示信息"),tr("修改成功"),0,0,0);
    }
}

void xiaoshouzongzhangDlg::on_twoFindBtn()
{
    QString customer;
    if(twoCustomerCheckBox->checkState() == 2){
        customer = QString(" where CustomerName='%1'").arg(twoCustomerCombox->currentText());
    }
    QString searchSQL = QString("SELECT CustomerName 客户名称,ProjectName 工程名称,InitialBalance 上期材料款,BalanceDateTime 上期材料款截止日期 FROM SalesContractCustomerEngineeringForm %1 GROUP BY CustomerName,ProjectName").arg(customer);
    db.showview(searchSQL,twoView,&twoModel);
}

void xiaoshouzongzhangDlg::on_threeConfirmBtn()
{
    QString updateSQL = QString("update SalesContractCustomerEngineeringForm set paymentAmount=paymentAmount+'%1' where CustomerName='%2' and ProjectName='%3'")
            .arg(threeTransferAccountLineEdit->text(),threeCustomerCombox->currentText(),threeEngineerCombox->currentText());

    QString insertSQL = QString("insert into TransferRecord (CustomerName,EngineerName,TransferAccount,TransferType,TransferDate,OperatingTime,Operator) values ('%1','%2','%3','%4','%5','%6','%7')")
            .arg(threeCustomerCombox->currentText(),threeEngineerCombox->currentText(),threeTransferAccountLineEdit->text(),threeTransferTypeCombox->currentText(),threeTransferDate->dateTime().toString("yyyy-MM-dd hh:mm:ss"),
                 QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"),userName);

    int res = 0;
    db.sql_exec("begin");
    res = db.sql_exec(updateSQL);
    if(res != 0){
        db.sql_exec("rollback");
        return;
    }
    res = db.sql_exec(insertSQL);
    if(res != 0){
        db.sql_exec("rollback");
        return;
    }
    db.sql_exec("commit");
    on_threeFindBtn();
    threeCustomerCombox->setCurrentIndex(0);
    threeEngineerCombox->setCurrentIndex(0);
    threeTransferAccountLineEdit->clear();
    QMessageBox::information(this,tr("提示信息"),tr("操作成功"),0,0,0);
}

void xiaoshouzongzhangDlg::on_threeFindBtn()
{
    QString CustomerName;
    if(threeFindCustomerCheckBox->checkState() == 2){
        CustomerName = QString(" and CustomerName='%1'").arg(threeFindCustomerCombox->currentText());
    }
    QString searchSQL = QString("select CustomerName 客户名称,EngineerName 工程名称,TransferAccount 付款金额,TransferType 付款方式,TransferDate 付款日期,OperatingTime 录入日期,Operator 录入人 from TransferRecord where \
                                OperatingTime between '%1' and '%2' %3")
                                .arg(threeOperatingDate1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),threeOperatingDate2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),CustomerName);
            db.showview(searchSQL,threeView,&threeModel);
}

void xiaoshouzongzhangDlg::on_threeCustomerCombox()
{
    threeEngineerCombox->clear();
    db.sql_fillComboBoxItem(QString("select ProjectName from SalesContractCustomerEngineeringForm where CustomerName='%1' group by ProjectName").arg(threeCustomerCombox->currentText()),threeEngineerCombox);
}

void xiaoshouzongzhangDlg::on_fourConfirmBtn()
{
    QString updateSQL = QString("update SalesContractCustomerEngineeringForm set chonghongAmount=chonghongAmount+'%1' where CustomerName='%2' and ProjectName='%3'")
            .arg(fourChongHongAccountLineEdit->text(),fourCustomerCombox->currentText(),fourEngineerCombox->currentText());

    QString insertSQL = QString("insert into ChongHongRecord_Customer (CustomerName,EngineerName,ChongHongAccount,Remarks,OperatorTime,Operator) values ('%1','%2','%3','%4','%5','%6')")
            .arg(fourCustomerCombox->currentText(),fourEngineerCombox->currentText(),fourChongHongAccountLineEdit->text(),fourRemarksLineEdit->text(),
                 QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"),userName);

    int res = 0;
    db.sql_exec("begin");
    res = db.sql_exec(updateSQL);
    if(res != 0){
        db.sql_exec("rollback");
        return;
    }
    res = db.sql_exec(insertSQL);
    if(res != 0){
        db.sql_exec("rollback");
        return;
    }
    db.sql_exec("commit");
    on_fourFindBtn();
    fourCustomerCombox->setCurrentIndex(0);
    fourEngineerCombox->setCurrentIndex(0);
    fourChongHongAccountLineEdit->clear();

    QMessageBox::information(this,tr("提示信息"),tr("操作成功"),0,0,0);
}

void xiaoshouzongzhangDlg::on_fourFindBtn()
{
    QString CustomerName;
    if(fourFindCustomerCheckBox->checkState() == 2){
        CustomerName = QString(" and CustomerName='%1'").arg(fourFindCustomerCombox->currentText());
    }
    QString searchSQL = QString("select CustomerName 客户名称,EngineerName 工程名称,ChongHongAccount 冲红金额,Remarks 备注,OperatorTime 录入日期,Operator 录入人 from ChongHongRecord_Customer where \
                                OperatorTime between '%1' and '%2' %3")
                                .arg(fourOperatingDate1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),fourOperatingDate2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),CustomerName);
    db.showview(searchSQL,fourView,&fourModel);
}

void xiaoshouzongzhangDlg::on_fourCustomerCombox()
{
    fourEngineerCombox->clear();
    db.sql_fillComboBoxItem(QString("select ProjectName from SalesContractCustomerEngineeringForm where CustomerName='%1' group by ProjectName").arg(fourCustomerCombox->currentText()),fourEngineerCombox);
}

void xiaoshouzongzhangDlg::on_fiveBtn()
{
    QString Customer,Engineer;
    if(fiveCustomerCheck->checkState() == 2){
        Customer = QString(" and Customer='%1'").arg(fiveCustomerCombox->currentText());
    }
    if(fiveEngineerCheck->checkState() == 2){
        Engineer = QString(" and Engineer='%1'").arg(fiveEngineerCombox->currentText());
    }

    QString searchSQL = QString("select Customer 客户名称,Engineer 工程名称,Account 结存余额,balanceDate 结存时间,Operator 操作人,OperatingTime 操作时间 from BalanceRecord_Customer where OperatingTime \
                                between '%1' and '%2' %3 %4")
                                .arg(fiveBalanceDate1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),fiveBalanceDate2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),Customer,Engineer);
    db.showview(searchSQL,fiveBalanceView,&fiveBalanceModel);
}

