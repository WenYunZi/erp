#include "caigouzongzhangdlg.h"

extern mymysql db;
extern myTCPsocket *sockClient;
extern QString userName;

caigouzongzhangDlg::caigouzongzhangDlg(QWidget *parent) :
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

void caigouzongzhangDlg::refresh()
{

}

void caigouzongzhangDlg::keyPressEvent(QKeyEvent *event)
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

void caigouzongzhangDlg::creatTabPage1()
{
    SQL1 = "SELECT 	M.Supplier 供应商,\
                    M.MaterialName 原材料,\
                    M.Specifications 规格,\
                    M.InitialBalance 上期材料款,\
                    IF(N.benqiTotal IS NULL,0,N.benqiTotal)+M.chonghongAmount 本期材料款,\
                    IF(N.benqiWeiTotal IS NULL,0,N.benqiWeiTotal) 本期未核对材料款,\
                    IF(N.benqiYiTotal IS NULL,0,N.benqiYiTotal)+M.chonghongAmount 本期已核对材料款,\
                    M.InitialBalance+IF(N.benqiTotal IS NULL,0,N.benqiTotal)+M.chonghongAmount 累计材料款,\
                    M.paymentAmount 客户收款金额,\
                    M.InitialBalance+IF(N.benqiTotal IS NULL,0,N.benqiTotal)+M.chonghongAmount-M.paymentAmount 未付金额,\
                    M.BalanceDateTime 本期起始日期\
            FROM PurchaseMaterialList M LEFT JOIN (\
            SELECT\
                A.Supplier SUP,\
                Material MAT,\
                SpecificationModel SPEC,\
                SUM(StorageKG * UnitPrice / 1000) benqiTotal,\
                SUM(CASE WHEN Flag = '2' THEN StorageKG * UnitPrice / 1000 ELSE 0 END) benqiWeiTotal,\
                SUM(CASE WHEN Flag = '0' THEN StorageKG * UnitPrice / 1000 ELSE 0 END) benqiYiTotal\
            FROM\
                PurchaseReceipt A\
            LEFT JOIN (SELECT * FROM PurchaseMaterialList GROUP BY Supplier,MaterialName,Specifications) B \
            ON (A.Supplier = B.Supplier AND A.Material = B.MaterialName AND A.SpecificationModel = B.Specifications)\
            WHERE\
                A.GrossWeightTime >= B.BalanceDateTime\
            GROUP BY\
                A.Supplier,\
                Material,\
                SpecificationModel\
            ORDER BY\
                A.Supplier,Material,SpecificationModel ) N ON (M.Supplier=N.SUP AND M.MaterialName=N.MAT AND M.Specifications=N.SPEC) \
            GROUP BY M.Supplier,M.MaterialName,M.Specifications";

    QLabel *SupplierNameLabel = new QLabel(tr("供应商名称"));
    SupplierNameLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *MaterialNameLabel = new QLabel(tr("原材料名称"));
    MaterialNameLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *SpecificationsLabel = new QLabel(tr("规格"));
    SpecificationsLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *RemainingSumLabel = new QLabel(tr("客户余额"));
    RemainingSumLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *BalanceDateLabel = new QLabel(tr("结存日期"));
    BalanceDateLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    SupplierLineEdit = new QLineEdit(this);
    SupplierLineEdit->setReadOnly(true);
    MaterialLineEdit = new QLineEdit(this);
    MaterialLineEdit->setReadOnly(true);
    SpecialLineEdit = new QLineEdit(this);
    SpecialLineEdit->setReadOnly(true);
    RemainingSumLineEdit = new QLineEdit(this);

    BalanceDateEdit = new QDateTimeEdit(this);
    BalanceDateEdit->setDate(QDate::currentDate());
    BalanceDateEdit->setCalendarPopup(true);
    connect(BalanceDateEdit,SIGNAL(dateTimeChanged(QDateTime)),this,SLOT(on_BalanceDateEdit()));

    BalanceBtn = new QPushButton(tr("结存"),this);
    BalanceBtn->setFixedWidth(120);
    connect(BalanceBtn,SIGNAL(clicked()),this,SLOT(on_BalanceBtn()));

    SupplierCheckBox = new QCheckBox(tr("供应商名称"),this);

    SupplierCombox = new myComboBox(this);
    db.sql_fillComboBoxItem("SELECT Name FROM SupplierFile",SupplierCombox);

    FindBtn = new QPushButton(tr("查找"),this);
    FindBtn->setFixedWidth(120);
    connect(FindBtn,SIGNAL(clicked()),this,SLOT(on_FindBtn()));

    oneView = new QTableView(this);
    db.showview(SQL1,oneView,&oneModel);
    connect(oneView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(on_oneView()));
    oneView->setColumnWidth(0,200);
    oneView->setColumnWidth(5,120);
    oneView->setColumnWidth(6,120);
    oneView->setColumnWidth(10,130);

    QHBoxLayout *balanceLayout = new QHBoxLayout;
    balanceLayout->addWidget(SupplierNameLabel,0);
    balanceLayout->addWidget(SupplierLineEdit,2);
    balanceLayout->addWidget(MaterialNameLabel,0);
    balanceLayout->addWidget(MaterialLineEdit,2);
    balanceLayout->addWidget(SpecificationsLabel,0);
    balanceLayout->addWidget(SpecialLineEdit,2);
    balanceLayout->addWidget(RemainingSumLabel,0);
    balanceLayout->addWidget(RemainingSumLineEdit,1);
    balanceLayout->addWidget(BalanceDateLabel,0);
    balanceLayout->addWidget(BalanceDateEdit,1);
    balanceLayout->addWidget(BalanceBtn,1);
    balanceLayout->addStretch(2);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(SupplierCheckBox,0);
    hlayout->addWidget(SupplierCombox,2);
    hlayout->addWidget(FindBtn);
    hlayout->addStretch(3);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(balanceLayout);
    vlayout->addSpacing(10);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(oneView);

    xiaoshouzongzhang->setLayout(vlayout);
    tabWidget->addTab(xiaoshouzongzhang,tr("供应商总账"));
}

void caigouzongzhangDlg::creatTabPage2()
{
    SQL2 = "SELECT Supplier 供应商名称,MaterialName 原材料名称,Specifications 规格,InitialBalance 上期供货额,BalanceDateTime 上期供货额截止日期 FROM PurchaseMaterialList \
            GROUP BY Supplier,MaterialName,Specifications";

    QLabel *SupplierNameLabel = new QLabel(tr("供应商名称"));
    SupplierNameLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *MaterialNameLabel = new QLabel(tr("原材料名称"));
    MaterialNameLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *SpecificationsLabel = new QLabel(tr("规格"));
    SpecificationsLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *InitialBalanceLabel = new QLabel(tr("上期供货额"));
    InitialBalanceLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *BalanceDateTimeLabel = new QLabel(tr("上期供货额截止日期"));
    BalanceDateTimeLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    twoSupplierLineEdit = new QLineEdit(this);
    twoSupplierLineEdit->setReadOnly(true);
    twoMaterialLineEdit = new QLineEdit(this);
    twoMaterialLineEdit->setReadOnly(true);
    twoSpecialLineEdit = new QLineEdit(this);
    twoSpecialLineEdit->setReadOnly(true);

    twoInitialBalanceLineEdit = new QLineEdit(this);

    twoBalanceDateTime = new QDateTimeEdit(this);
    twoBalanceDateTime->setDate(QDate::currentDate());
    twoBalanceDateTime->setCalendarPopup(true);

    twoUpdateBtn = new QPushButton(tr("修改期初"));
    twoUpdateBtn->setFixedWidth(120);
    connect(twoUpdateBtn,SIGNAL(clicked()),this,SLOT(on_twoUpdateBtn()));

    twoSupplierCheckBox = new QCheckBox(tr("供应商名称"),this);

    twoSupplierCombox = new myComboBox(this);
    db.sql_fillComboBoxItem("SELECT Name FROM SupplierFile",twoSupplierCombox);

    twoFindBtn = new QPushButton(tr("查找"),this);
    twoFindBtn->setFixedWidth(120);
    connect(twoFindBtn,SIGNAL(clicked()),this,SLOT(on_twoFindBtn()));


    twoView = new QTableView(this);
    db.showview(SQL2,twoView,&twoModel);
    connect(twoView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(on_doubleClickTwoView()));
    twoView->setColumnWidth(0,200);
    twoView->setColumnWidth(4,150);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(SupplierNameLabel,0);
    hlayout->addWidget(twoSupplierLineEdit,1);
    hlayout->addWidget(MaterialNameLabel,0);
    hlayout->addWidget(twoMaterialLineEdit,1);
    hlayout->addWidget(SpecificationsLabel,0);
    hlayout->addWidget(twoSpecialLineEdit,1);
    hlayout->addWidget(InitialBalanceLabel,0);
    hlayout->addWidget(twoInitialBalanceLineEdit,1);
    hlayout->addWidget(BalanceDateTimeLabel,0);
    hlayout->addWidget(twoBalanceDateTime,0);
    hlayout->addWidget(twoUpdateBtn,1);
    hlayout->addStretch(2);

    QHBoxLayout *hlayout1 = new QHBoxLayout;
    hlayout1->addWidget(twoSupplierCheckBox,0);
    hlayout1->addWidget(twoSupplierCombox,2);
    hlayout1->addWidget(twoFindBtn,1);
    hlayout1->addStretch(3);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(hlayout);
    vlayout->addSpacing(10);
    vlayout->addLayout(hlayout1);
    vlayout->addWidget(twoView);

    kehuqichushezhi->setLayout(vlayout);
    tabWidget->addTab(kehuqichushezhi,tr("供应商期初数据设置"));
}

void caigouzongzhangDlg::creatTabPage3()
{
    SQL3 = "select SupplierName 供应商名称,Material 原材料名称,Special 规格,TransferAccount 付款金额,TransferType 付款方式,TransferDate 付款日期,OperatingTime 录入日期,Operator 录入人 from TransferRecord_Supplier limit 0";

    QLabel *SupplierNameLabel = new QLabel(tr("供应商名称"));
    SupplierNameLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *MaterialLabel = new QLabel(tr("原材料名称"));
    MaterialLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *SpecialLabel = new QLabel(tr("规格"));
    SpecialLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
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

    threeSupplierCombox = new myComboBox(this);
    db.sql_fillComboBoxItem("SELECT Name FROM SupplierFile",threeSupplierCombox);
    connect(threeSupplierCombox,SIGNAL(editTextChanged(QString)),this,SLOT(on_threeSupplierCombox()));

    threeMaterialCombox = new QComboBox(this);

    threeSpecialCombox = new QComboBox(this);

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

    threeFindSupplierCheckBox = new QCheckBox(tr("供应商"),this);

    threeFindSupplierCombox = new myComboBox(this);
    db.sql_fillComboBoxItem("SELECT Name FROM SupplierFile",threeFindSupplierCombox);

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
    threeView->setColumnWidth(0,300);
    threeView->setColumnWidth(3,130);
    threeView->setColumnWidth(4,130);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(SupplierNameLabel,0);
    hlayout->addWidget(threeSupplierCombox,1);
    hlayout->addWidget(MaterialLabel,0);
    hlayout->addWidget(threeMaterialCombox,1);
    hlayout->addWidget(SpecialLabel,0);
    hlayout->addWidget(threeSpecialCombox,1);
    hlayout->addWidget(payAccountLabel,0);
    hlayout->addWidget(threeTransferAccountLineEdit,1);
    hlayout->addWidget(payTypeLabel,0);
    hlayout->addWidget(threeTransferTypeCombox,1);
    hlayout->addWidget(payDateLabel,0);
    hlayout->addWidget(threeTransferDate,1);
    hlayout->addWidget(threeConfirmBtn,1);
    hlayout->addStretch(2);

    QHBoxLayout *hlayout1 = new QHBoxLayout;
    hlayout1->addWidget(OperatingDateLabel,0);
    hlayout1->addWidget(threeOperatingDate1,0);
    hlayout1->addWidget(FuHaoLabel,0);
    hlayout1->addWidget(threeOperatingDate2,0);
    hlayout1->addWidget(threeFindSupplierCheckBox,0);
    hlayout1->addWidget(threeFindSupplierCombox,2);
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

void caigouzongzhangDlg::creatTabPage4()
{
    SQL4 = "select Supplier 供应商,MaterialName 原材料,Specifications 规格,ChongHongAccount 冲红金额,Remarks 备注,OperatorTime 录入日期,Operator 录入人 from ChongHongRecord_Supplier limit 0";

    QLabel *SupplierLabel = new QLabel(tr("供应商"));
    SupplierLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *MaterialLabel = new QLabel(tr("原材料"));
    MaterialLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *SpecialLabel = new QLabel(tr("规格"));
    SpecialLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *ChongHongAccountLabel = new QLabel(tr("冲红金额"));
    ChongHongAccountLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *RemarksLabel = new QLabel(tr("备注"));
    RemarksLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    QLabel *OperatingDateLabel = new QLabel(tr("操作时间"));
    OperatingDateLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *FuHaoLabel = new QLabel(tr("--"));
    FuHaoLabel->setAlignment(Qt::AlignVCenter|Qt::AlignCenter);

    fourSupplierCombox = new myComboBox(this);
    db.sql_fillComboBoxItem("SELECT Name FROM SupplierFile",fourSupplierCombox);
    connect(fourSupplierCombox,SIGNAL(editTextChanged(QString)),this,SLOT(on_fourSupplierCombox()));

    fourMaterialCombox = new myComboBox(this);

    fourSpecialCombox = new myComboBox(this);

    fourRemarksLineEdit = new QLineEdit(this);

    fourChongHongAccountLineEdit = new QLineEdit(this);

    fourConfirmBtn = new QPushButton(tr("确认"),this);
    fourConfirmBtn->setFixedWidth(120);
    connect(fourConfirmBtn,SIGNAL(clicked()),this,SLOT(on_fourConfirmBtn()));

    fourFindCustomerCheckBox = new QCheckBox(tr("供应商"),this);

    fourFindCustomerCombox = new myComboBox(this);
    db.sql_fillComboBoxItem("SELECT Name FROM SupplierFile",fourFindCustomerCombox);

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
    hlayout->addWidget(SupplierLabel,0);
    hlayout->addWidget(fourSupplierCombox,2);
    hlayout->addWidget(MaterialLabel,0);
    hlayout->addWidget(fourMaterialCombox,2);
    hlayout->addWidget(SpecialLabel,0);
    hlayout->addWidget(fourSpecialCombox,2);
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

void caigouzongzhangDlg::creatTabPage5()
{
    SQL5 = "select Supplier 供应商,MaterialName 原材料,Specifications 规格,Account 结存余额,balanceDate 结存时间,Operator 操作人,OperatingTime 操作时间 from BalanceRecord_Supplier limit 0";

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

    fiveSupplierCheck = new QCheckBox(tr("供应商"),this);
    fiveMaterialCheck = new QCheckBox(tr("原材料"),this);

    fiveSupplierCombox = new myComboBox(this);
    db.sql_fillComboBoxItem("SELECT Name FROM SupplierFile",fiveSupplierCombox);

    fiveMaterialCombox = new myComboBox(this);
    db.sql_fillComboBoxItem("select MaterialName from PurchaseMaterialList group by MaterialName",fiveMaterialCombox);

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
    hlayout->addWidget(fiveSupplierCheck,0);
    hlayout->addWidget(fiveSupplierCombox,1);
    hlayout->addWidget(fiveMaterialCheck,0);
    hlayout->addWidget(fiveMaterialCombox,1);
    hlayout->addWidget(fiveFindBtn,1);
    hlayout->addStretch(2);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(fiveBalanceView);


    zhangkuanjiecun->setLayout(vlayout);
    tabWidget->addTab(zhangkuanjiecun,tr("账款结存记录"));
}

void caigouzongzhangDlg::on_BalanceBtn()
{
    if(SupplierLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择一个供应商和原材料"),0,0,0);
        return;
    }

    QString updateSQL = QString("update PurchaseMaterialList set InitialBalance='%1',paymentAmount='0',chonghongAmount='0',BalanceDateTime='%2' where Supplier='%3' and MaterialName='%4' and Specifications='%5'")
            .arg(RemainingSumLineEdit->text(),BalanceDateEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"),SupplierLineEdit->text(),MaterialLineEdit->text(),SpecialLineEdit->text());
    db.sql_exec(updateSQL);

    QString insertSQL = QString("insert into BalanceRecord_Supplier (Supplier,MaterialName,Specifications,Account,balanceDate,Operator,OperatingTime) values ('%1','%2','%3','%4','%5','%6','%7')")
            .arg(SupplierLineEdit->text(),MaterialLineEdit->text(),SpecialLineEdit->text(),RemainingSumLineEdit->text(),BalanceDateEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"),userName,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    db.sql_exec(insertSQL);

    on_FindBtn();

    SupplierLineEdit->clear();
    MaterialLineEdit->clear();
    SpecialLineEdit->clear();
    RemainingSumLineEdit->clear();
}

void caigouzongzhangDlg::on_FindBtn()
{
    QString CustomerName;
    if(SupplierCheckBox->checkState() == 2){
        CustomerName = QString(" WHERE M.Supplier='%1'").arg(SupplierCombox->currentText());
    }
    QString searchSQL = QString("SELECT M.Supplier 供应商,\
                                        M.MaterialName 原材料,\
                                        M.Specifications 规格,\
                                        M.InitialBalance 上期材料款,\
                                        IF(N.benqiTotal IS NULL,0,N.benqiTotal)+M.chonghongAmount 本期材料款,\
                                        IF(N.benqiWeiTotal IS NULL,0,N.benqiWeiTotal) 本期未核对材料款,\
                                        IF(N.benqiYiTotal IS NULL,0,N.benqiYiTotal)+M.chonghongAmount 本期已核对材料款,\
                                        M.InitialBalance+IF(N.benqiTotal IS NULL,0,N.benqiTotal)+M.chonghongAmount 累计材料款,\
                                        M.paymentAmount 客户收款金额,\
                                        M.InitialBalance+IF(N.benqiTotal IS NULL,0,N.benqiTotal)+M.chonghongAmount-M.paymentAmount 未付金额,\
                                        M.BalanceDateTime 本期起始日期\
                                FROM PurchaseMaterialList M LEFT JOIN (\
                                SELECT\
                                    A.Supplier SUP,\
                                    Material MAT,\
                                    SpecificationModel SPEC,\
                                    SUM(StorageKG * UnitPrice / 1000) benqiTotal,\
                                    SUM(CASE WHEN Flag = '2' THEN StorageKG * UnitPrice / 1000 ELSE 0 END) benqiWeiTotal,\
                                    SUM(CASE WHEN Flag = '0' THEN StorageKG * UnitPrice / 1000 ELSE 0 END) benqiYiTotal\
                                FROM\
                                    PurchaseReceipt A\
                                LEFT JOIN (SELECT * FROM PurchaseMaterialList GROUP BY Supplier,MaterialName,Specifications) B \
                                ON (A.Supplier = B.Supplier AND A.Material = B.MaterialName AND A.SpecificationModel = B.Specifications)\
                                WHERE\
                                    A.GrossWeightTime >= B.BalanceDateTime\
                                GROUP BY\
                                    A.Supplier,\
                                    Material,\
                                    SpecificationModel\
                                ORDER BY\
                                    A.Supplier,Material,SpecificationModel ) N ON (M.Supplier=N.SUP AND M.MaterialName=N.MAT AND M.Specifications=N.SPEC) %1 \
                                GROUP BY M.Supplier,M.MaterialName,M.Specifications")
                        .arg(CustomerName);
            db.showview(searchSQL,oneView,&oneModel);
}

void caigouzongzhangDlg::on_oneView()
{
    int row = oneView->currentIndex().row();
    SupplierLineEdit->setText(oneModel->item(row,0)->text());
    MaterialLineEdit->setText(oneModel->item(row,1)->text());
    SpecialLineEdit->setText(oneModel->item(row,2)->text());

    QString searchSQL = QString("SELECT M.InitialBalance+IF(N.benqiTotal IS NULL,0,N.benqiTotal)+M.chonghongAmount-M.paymentAmount 未付金额 \
                                FROM PurchaseMaterialList M LEFT JOIN (\
                                SELECT\
                                    A.Supplier SUP,\
                                    Material MAT,\
                                    SpecificationModel SPEC,\
                                    SUM(StorageKG * UnitPrice / 1000) benqiTotal,\
                                    SUM(CASE WHEN Flag = '2' THEN StorageKG * UnitPrice / 1000 ELSE 0 END) benqiWeiTotal,\
                                    SUM(CASE WHEN Flag = '0' THEN StorageKG * UnitPrice / 1000 ELSE 0 END) benqiYiTotal\
                                FROM\
                                    PurchaseReceipt A\
                                LEFT JOIN (SELECT * FROM PurchaseMaterialList GROUP BY Supplier,MaterialName,Specifications) B \
                                ON (A.Supplier = B.Supplier AND A.Material = B.MaterialName AND A.SpecificationModel = B.Specifications)\
                                WHERE\
                                    A.GrossWeightTime >= B.BalanceDateTime AND A.GrossWeightTime<'%1'\
                                GROUP BY\
                                    A.Supplier,\
                                    Material,\
                                    SpecificationModel\
                                ORDER BY\
                                    A.Supplier,Material,SpecificationModel ) N ON (M.Supplier=N.SUP AND M.MaterialName=N.MAT AND M.Specifications=N.SPEC) \
                                WHERE M.Supplier='%2' AND M.MaterialName='%3' AND M.Specifications='%4'\
                                GROUP BY M.Supplier,M.MaterialName,M.Specifications")
                        .arg(BalanceDateEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"),SupplierLineEdit->text(),MaterialLineEdit->text(),SpecialLineEdit->text());
    RemainingSumLineEdit->setText(db.sql_fetchrow_plus(searchSQL,0));
    if(RemainingSumLineEdit->text().isEmpty()){
        RemainingSumLineEdit->setText("0");
    }
}

void caigouzongzhangDlg::on_BalanceDateEdit()
{
    QString searchSQL = QString("SELECT M.InitialBalance+IF(N.benqiTotal IS NULL,0,N.benqiTotal)+M.chonghongAmount-M.paymentAmount 未付金额 \
                                FROM PurchaseMaterialList M LEFT JOIN (\
                                SELECT\
                                    A.Supplier SUP,\
                                    Material MAT,\
                                    SpecificationModel SPEC,\
                                    SUM(StorageKG * UnitPrice / 1000) benqiTotal,\
                                    SUM(CASE WHEN Flag = '2' THEN StorageKG * UnitPrice / 1000 ELSE 0 END) benqiWeiTotal,\
                                    SUM(CASE WHEN Flag = '0' THEN StorageKG * UnitPrice / 1000 ELSE 0 END) benqiYiTotal\
                                FROM\
                                    PurchaseReceipt A\
                                LEFT JOIN (SELECT * FROM PurchaseMaterialList GROUP BY Supplier,MaterialName,Specifications) B \
                                ON (A.Supplier = B.Supplier AND A.Material = B.MaterialName AND A.SpecificationModel = B.Specifications)\
                                WHERE\
                                    A.GrossWeightTime >= B.BalanceDateTime AND A.GrossWeightTime<'%1'\
                                GROUP BY\
                                    A.Supplier,\
                                    Material,\
                                    SpecificationModel\
                                ORDER BY\
                                    A.Supplier,Material,SpecificationModel ) N ON (M.Supplier=N.SUP AND M.MaterialName=N.MAT AND M.Specifications=N.SPEC) \
                                WHERE M.Supplier='%2' AND M.MaterialName='%3' AND M.Specifications='%4'\
                                GROUP BY M.Supplier,M.MaterialName,M.Specifications")
                        .arg(BalanceDateEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"),SupplierLineEdit->text(),MaterialLineEdit->text(),SpecialLineEdit->text());
    RemainingSumLineEdit->setText(db.sql_fetchrow_plus(searchSQL,0));
    if(RemainingSumLineEdit->text().isEmpty()){
        RemainingSumLineEdit->setText("0");
    }
}

void caigouzongzhangDlg::on_doubleClickTwoView()
{
    int row = twoView->currentIndex().row();
    twoSupplierLineEdit->setText(twoModel->item(row,0)->text());
    twoMaterialLineEdit->setText(twoModel->item(row,1)->text());
    twoSpecialLineEdit->setText(twoModel->item(row,2)->text());
    twoInitialBalanceLineEdit->setText(twoModel->item(row,3)->text());
    twoBalanceDateTime->setDateTime(QDateTime::fromString(twoModel->item(row,4)->text(),"yyyy-MM-dd hh:mm:ss"));
}

void caigouzongzhangDlg::on_twoUpdateBtn()
{
    if(twoSupplierLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择供应商"),0,0,0);
        return;
    }
    QString updateSQL = QString("update PurchaseMaterialList set InitialBalance='%1',BalanceDateTime='%2' where Supplier='%3' and MaterialName='%4' and Specifications='%5'")
            .arg(twoInitialBalanceLineEdit->text(),twoBalanceDateTime->dateTime().toString("yyyy-MM-dd hh:mm:ss"),twoSupplierLineEdit->text(),
                 twoMaterialLineEdit->text(),twoSpecialLineEdit->text());
    int res = db.sql_exec(updateSQL);
    if(res == 0){
        twoSupplierLineEdit->clear();
        twoInitialBalanceLineEdit->clear();
        twoMaterialLineEdit->clear();
        twoSpecialLineEdit->clear();
        on_twoFindBtn();
        QMessageBox::information(this,tr("提示信息"),tr("修改成功"),0,0,0);
    }
}

void caigouzongzhangDlg::on_twoFindBtn()
{
    QString customer;
    if(twoSupplierCheckBox->checkState() == 2){
        customer = QString(" where Supplier='%1'").arg(twoSupplierCombox->currentText());
    }
    QString searchSQL = QString("SELECT Supplier 供应商名称,MaterialName 原材料名称,Specifications 规格,InitialBalance 上期供货额,BalanceDateTime 上期供货额截止日期 FROM PurchaseMaterialList %1 \
                                GROUP BY Supplier,MaterialName,Specifications").arg(customer);
    db.showview(searchSQL,twoView,&twoModel);
}

void caigouzongzhangDlg::on_threeConfirmBtn()
{
    QString updateSQL = QString("update PurchaseMaterialList set paymentAmount=paymentAmount+'%1' where Supplier='%2' and MaterialName='%3' and Specifications='%4'")
            .arg(threeTransferAccountLineEdit->text(),threeSupplierCombox->currentText(),threeMaterialCombox->currentText(),threeSpecialCombox->currentText());

    QString insertSQL = QString("insert into TransferRecord_Supplier (SupplierName,Material,Special,TransferAccount,TransferType,TransferDate,OperatingTime,Operator) \
                                values ('%1','%2','%3','%4','%5','%6','%7','%8')")
            .arg(threeSupplierCombox->currentText(),threeMaterialCombox->currentText(),threeSpecialCombox->currentText(),threeTransferAccountLineEdit->text(),threeTransferTypeCombox->currentText(),threeTransferDate->dateTime().toString("yyyy-MM-dd hh:mm:ss"),
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
    QMessageBox::information(this,tr("提示信息"),tr("操作成功"),0,0,0);
}

void caigouzongzhangDlg::on_threeFindBtn()
{
    QString SupplierName;
    if(threeFindSupplierCheckBox->checkState() == 2){
        SupplierName = QString(" and SupplierName='%1'").arg(threeFindSupplierCombox->currentText());
    }
    QString searchSQL = QString("select SupplierName 供应商名称,Material 原材料名称,Special 规格,TransferAccount 付款金额,TransferType 付款方式,TransferDate 付款日期,OperatingTime 录入日期,Operator 录入人 from TransferRecord_Supplier where \
                                OperatingTime between '%1' and '%2' %3")
                                .arg(threeOperatingDate1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),threeOperatingDate2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),SupplierName);
    db.showview(searchSQL,threeView,&threeModel);
}

void caigouzongzhangDlg::on_threeSupplierCombox()
{
    disconnect(threeMaterialCombox,SIGNAL(editTextChanged(QString)),this,SLOT(on_threeMaterialCombox()));
    threeMaterialCombox->clear();
    db.sql_fillComboBoxItem(QString("SELECT MaterialName FROM PurchaseMaterialList where Supplier='%1' GROUP BY MaterialName").arg(threeSupplierCombox->currentText()),threeMaterialCombox);
    connect(threeMaterialCombox,SIGNAL(currentIndexChanged(int)),this,SLOT(on_threeMaterialCombox()));
}

void caigouzongzhangDlg::on_threeMaterialCombox()
{
    threeSpecialCombox->clear();
    db.sql_fillComboBoxItem(QString("SELECT Specifications FROM PurchaseMaterialList where Supplier='%1' and MaterialName='%2' GROUP BY MaterialName")
                            .arg(threeSupplierCombox->currentText(),threeMaterialCombox->currentText()),threeSpecialCombox);
}

void caigouzongzhangDlg::on_fourConfirmBtn()
{
    QString updateSQL = QString("update PurchaseMaterialList set chonghongAmount=chonghongAmount+'%1' where Supplier='%2' and MaterialName='%3' and Specifications='%4'")
            .arg(fourChongHongAccountLineEdit->text(),fourSupplierCombox->currentText(),fourMaterialCombox->currentText(),fourSpecialCombox->currentText());

    QString insertSQL = QString("insert into ChongHongRecord_Supplier (Supplier,MaterialName,Specifications,ChongHongAccount,Remarks,OperatorTime,Operator) values ('%1','%2','%3','%4','%5','%6','%7')")
            .arg(fourSupplierCombox->currentText(),fourMaterialCombox->currentText(),fourSpecialCombox->currentText(),fourChongHongAccountLineEdit->text(),fourRemarksLineEdit->text(),
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
    fourSupplierCombox->setCurrentIndex(0);
    fourMaterialCombox->setCurrentIndex(0);
    fourSpecialCombox->setCurrentIndex(0);
    fourChongHongAccountLineEdit->clear();

    QMessageBox::information(this,tr("提示信息"),tr("操作成功"),0,0,0);
}

void caigouzongzhangDlg::on_fourFindBtn()
{
    QString CustomerName;
    if(fourFindCustomerCheckBox->checkState() == 2){
        CustomerName = QString(" and Supplier='%1'").arg(fourFindCustomerCombox->currentText());
    }
    QString searchSQL = QString("select Supplier 供应商,MaterialName 原材料,Specifications 规格,ChongHongAccount 冲红金额,Remarks 备注,OperatorTime 录入日期,Operator 录入人 from ChongHongRecord_Supplier where \
                                OperatorTime between '%1' and '%2' %3")
                                .arg(fourOperatingDate1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),fourOperatingDate2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),CustomerName);
    db.showview(searchSQL,fourView,&fourModel);
}

void caigouzongzhangDlg::on_fourSupplierCombox()
{
    disconnect(fourMaterialCombox,SIGNAL(editTextChanged(QString)),this,SLOT(on_fourMaterialCombox()));
    fourMaterialCombox->clear();
    db.sql_fillComboBoxItem(QString("select MaterialName from PurchaseMaterialList where Supplier='%1' group by MaterialName").arg(fourSupplierCombox->currentText()),fourMaterialCombox);
    connect(fourMaterialCombox,SIGNAL(editTextChanged(QString)),this,SLOT(on_fourMaterialCombox()));
}

void caigouzongzhangDlg::on_fourMaterialCombox()
{
    fourSpecialCombox->clear();
    db.sql_fillComboBoxItem(QString("select Specifications from PurchaseMaterialList where Supplier='%1' and MaterialName='%2' group by Specifications")
                            .arg(fourSupplierCombox->currentText(),fourMaterialCombox->currentText()),fourSpecialCombox);
}

void caigouzongzhangDlg::on_fiveBtn()
{
    QString Supplier,Material;
    if(fiveSupplierCheck->checkState() == 2){
        Supplier = QString(" and Supplier='%1'").arg(fiveSupplierCombox->currentText());
    }
    if(fiveMaterialCheck->checkState() == 2){
        Material = QString(" and MaterialName='%1'").arg(fiveMaterialCombox->currentText());
    }

    QString searchSQL = QString("select Supplier 供应商,MaterialName 原材料,Specifications 规格,Account 结存余额,balanceDate 结存时间,Operator 操作人,OperatingTime 操作时间 from BalanceRecord_Supplier where OperatingTime \
                                between '%1' and '%2' %3 %4")
                                .arg(fiveBalanceDate1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),fiveBalanceDate2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),Supplier,Material);
    db.showview(searchSQL,fiveBalanceView,&fiveBalanceModel);
}


