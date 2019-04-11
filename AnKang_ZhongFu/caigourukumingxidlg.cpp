#include "caigourukumingxidlg.h"

extern mymysql db;
extern QString userName;

caigourukumingxiDlg::caigourukumingxiDlg(QWidget *parent) :
    QDialog(parent)
{
    tabWidget = new QTabWidget(this);
    tongfahuomingxi = new QWidget(this);
    duizhangjilu = new QWidget(this);

    ViewToExcel = new myExcel(this);

    CreateCaigourukuMingxi();
    CreateDuizhangJiLu();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tabWidget);
    layout->setSpacing(0);
}

caigourukumingxiDlg::~caigourukumingxiDlg()
{
    delete DetailModel;
}

void caigourukumingxiDlg::CreateCaigourukuMingxi()
{
    searchPurchaseReceiptSQL = QString("select 0 选中标志,StorageList 入库单号,Supplier 供应商,Material 原材料,SpecificationModel 规格,Position 仓位,LicensePlateNumber 车牌号,GrossWeight 毛重,\
                        GrossWeightTime 毛重时间,Tare 皮重,TareTime 皮重时间,NetWeight 净重,Buckle 扣重,StorageKG 入库重量,StorageCube 入库方量,UnitPrice 单价,\
                        ROUND(StorageKG*UnitPrice/1000,2) 本车价格,Storagefactory 入库厂地,GBMAN 过磅人,Flag 核对标志 from PurchaseReceipt limit 0");

    QLabel *TimeLabel = new QLabel(tr("入库时间"),this);
    TimeLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *FuHaoLabel = new QLabel(tr("--"),this);
    FuHaoLabel->setAlignment(Qt::AlignCenter);
    QLabel *StorageListLabel = new QLabel(tr("入库单号"),this);
    StorageListLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *SupplierLabel = new QLabel(tr("供应商名称"),this);
    SupplierLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    SupplierLabel->setStyleSheet("color:red");
    QLabel *MaterialNameLabel = new QLabel(tr("原材料名称"),this);
    MaterialNameLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    MaterialNameLabel->setStyleSheet("color:red");
    QLabel *SpecificationModelLabel = new QLabel(tr("规格"),this);
    SpecificationModelLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    SpecificationModelLabel->setStyleSheet("color:red");
    QLabel *PositionLabel = new QLabel(tr("仓位"),this);
    PositionLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *LicensePlateNumberLabel = new QLabel(tr("车牌号"),this);
    LicensePlateNumberLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    LicensePlateNumberLabel->setStyleSheet("color:red");
    QLabel *GrossWeightLabel = new QLabel(tr("毛重"),this);
    GrossWeightLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    GrossWeightLabel->setStyleSheet("color:red");
    QLabel *GrossWeightTimeLabel = new QLabel(tr("毛重时间"),this);
    GrossWeightTimeLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    GrossWeightTimeLabel->setStyleSheet("color:red");
    QLabel *TareLabel = new QLabel(tr("皮重"),this);
    TareLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    TareLabel->setStyleSheet("color:red");
    QLabel *TareTimeLabel = new QLabel(tr("皮重时间"),this);
    TareTimeLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    TareTimeLabel->setStyleSheet("color:red");
    QLabel *NetWeightLabel = new QLabel(tr("净重"),this);
    NetWeightLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    NetWeightLabel->setStyleSheet("color:red");
    QLabel *BuckleLabel = new QLabel(tr("扣重"),this);
    BuckleLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    BuckleLabel->setStyleSheet("color:red");
    QLabel *StorageKGLabel = new QLabel(tr("入库重量"),this);
    StorageKGLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    StorageKGLabel->setStyleSheet("color:red");
    QLabel *StorageCubeLabel = new QLabel(tr("入库方量"),this);
    StorageCubeLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    StorageCubeLabel->setStyleSheet("color:red");
    QLabel *UnitPriceLabel = new QLabel(tr("单价"),this);
    UnitPriceLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    UnitPriceLabel->setStyleSheet("color:red");
    QLabel *StoragefactoryLabel = new QLabel(tr("入库厂地"),this);
    StoragefactoryLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    DateTimeEdit1 = new QDateTimeEdit(this);
    DateTimeEdit1->setDate(QDate::currentDate().addDays(-1));
    DateTimeEdit1->setCalendarPopup(true);
    DateTimeEdit2 = new QDateTimeEdit(this);
    DateTimeEdit2->setDate(QDate::currentDate());
    DateTimeEdit2->setCalendarPopup(true);

    StorageListLineEdit = new QLineEdit(this);
    StorageListLineEdit->setReadOnly(true);
    SupplierLineEdit = new QLineEdit(this);
    MaterialNameLineEdit = new QLineEdit(this);
    SpecificationModelLineEdit = new QLineEdit(this);
    PositionLineEdit = new QLineEdit(this);
    PositionLineEdit->setReadOnly(true);
    LicensePlateNumberLineEdit = new QLineEdit(this);
    GrossWeightLineEdit = new QLineEdit(this);
    GrossWeightTimeLineEdit = new QLineEdit(this);
    TareLineEdit = new QLineEdit(this);
    TareWeightTimeLineEdit = new QLineEdit(this);
    NetWeightLineEdit = new QLineEdit(this);
    BuckleLineEdit = new QLineEdit(this);
    StorageKGLineEdit = new QLineEdit(this);
    StorageCubeLineEdit = new QLineEdit(this);
    StoragefactoryLineEdit = new QLineEdit(this);
    StoragefactoryLineEdit->setReadOnly(true);
    UnitPriceLineEdit = new QLineEdit(this);

    AllSelectedBtn = new QPushButton(tr("全选"),this);
    AllSelectedBtn->setFixedWidth(120);
    connect(AllSelectedBtn,SIGNAL(clicked()),this,SLOT(on_AllSelectedBtn()));

    AllCancelBtn = new QPushButton(tr("取消"),this);
    AllCancelBtn->setFixedWidth(120);
    connect(AllCancelBtn,SIGNAL(clicked()),this,SLOT(on_AllCancelBtn()));

    AllConfirmBtn = new QPushButton(tr("批量核对"),this);
    AllConfirmBtn->setFixedWidth(120);
    connect(AllConfirmBtn,SIGNAL(clicked()),this,SLOT(on_AllConfirmBtn()));

    ConfirmBtn = new QPushButton(tr("单车核对"),this);
    ConfirmBtn->setFixedWidth(120);
    connect(ConfirmBtn,SIGNAL(clicked()),this,SLOT(on_ConfirmBtn()));

    SupplierCheck = new QCheckBox(tr("供应商名称"),this);
    MaterialCheck = new QCheckBox(tr("原材料名称"),this);

    SupplierCombox = new myComboBox(this);
    db.sql_fillComboBoxItem("select Supplier from PurchaseReceipt group by Supplier",SupplierCombox);
    MaterialCombox = new myComboBox(this);
    db.sql_fillComboBoxItem("select Material from PurchaseReceipt group by Material",MaterialCombox);

    FindBtn = new QPushButton(tr("查找"),this);
    FindBtn->setFixedWidth(120);
    connect(FindBtn,SIGNAL(clicked()),this,SLOT(on_FindBtn()));

    ExportBtn = new QPushButton(tr("导出"),this);
    ExportBtn->setFixedWidth(120);
    connect(ExportBtn,SIGNAL(clicked()),this,SLOT(on_ExportBtn()));


    DetailView = new QTableView(this);
    DetailView->setItemDelegate(new myCheckBoxDelegate(0,this));
    db.showview(searchPurchaseReceiptSQL,DetailView,&DetailModel);
    connect(DetailView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(on_doubleClickDetailView(QModelIndex)));
    DetailView->setColumnWidth(0,65);
    DetailView->setColumnWidth(6,70);
    DetailView->setColumnWidth(7,70);
    DetailView->setColumnWidth(8,150);
    DetailView->setColumnWidth(9,70);
    DetailView->setColumnWidth(10,150);
    DetailView->setColumnWidth(11,65);
    DetailView->setColumnWidth(12,65);
    DetailView->setColumnWidth(13,65);
    DetailView->setColumnWidth(14,65);
    DetailView->setColumnWidth(15,65);
    DetailView->setColumnWidth(16,80);
    DetailView->setColumnWidth(17,70);
    DetailView->setColumnWidth(18,70);
    DetailView->setColumnHidden(19,true);

    QHBoxLayout *BtnLayout = new QHBoxLayout;
    BtnLayout->addWidget(AllSelectedBtn,1);
    BtnLayout->addWidget(AllCancelBtn,1);
    BtnLayout->addWidget(AllConfirmBtn,1);
    BtnLayout->addWidget(ConfirmBtn,1);

    QGridLayout *DetailInfoLayout = new QGridLayout;
    DetailInfoLayout->addWidget(StorageListLabel,0,0);
    DetailInfoLayout->addWidget(StorageListLineEdit,0,1);
    DetailInfoLayout->addWidget(SupplierLabel,0,2);
    DetailInfoLayout->addWidget(SupplierLineEdit,0,3);
    DetailInfoLayout->addWidget(MaterialNameLabel,0,4);
    DetailInfoLayout->addWidget(MaterialNameLineEdit,0,5);
    DetailInfoLayout->addWidget(SpecificationModelLabel,0,6);
    DetailInfoLayout->addWidget(SpecificationModelLineEdit,0,7);
    DetailInfoLayout->addWidget(PositionLabel,0,8);
    DetailInfoLayout->addWidget(PositionLineEdit,0,9);
    DetailInfoLayout->addWidget(LicensePlateNumberLabel,0,10);
    DetailInfoLayout->addWidget(LicensePlateNumberLineEdit,0,11);
    DetailInfoLayout->addWidget(UnitPriceLabel,0,12);
    DetailInfoLayout->addWidget(UnitPriceLineEdit,0,13);
    DetailInfoLayout->addWidget(StoragefactoryLabel,0,14);
    DetailInfoLayout->addWidget(StoragefactoryLineEdit,0,15);

    DetailInfoLayout->addWidget(GrossWeightLabel,1,0);
    DetailInfoLayout->addWidget(GrossWeightLineEdit,1,1);
    DetailInfoLayout->addWidget(GrossWeightTimeLabel,1,2);
    DetailInfoLayout->addWidget(GrossWeightTimeLineEdit,1,3);
    DetailInfoLayout->addWidget(TareLabel,1,4);
    DetailInfoLayout->addWidget(TareLineEdit,1,5);
    DetailInfoLayout->addWidget(TareTimeLabel,1,6);
    DetailInfoLayout->addWidget(TareWeightTimeLineEdit,1,7);
    DetailInfoLayout->addWidget(NetWeightLabel,1,8);
    DetailInfoLayout->addWidget(NetWeightLineEdit,1,9);
    DetailInfoLayout->addWidget(BuckleLabel,1,10);
    DetailInfoLayout->addWidget(BuckleLineEdit,1,11);
    DetailInfoLayout->addWidget(StorageKGLabel,1,12);
    DetailInfoLayout->addWidget(StorageKGLineEdit,1,13);
    DetailInfoLayout->addWidget(StorageCubeLabel,1,14);
    DetailInfoLayout->addWidget(StorageCubeLineEdit,1,15);
    DetailInfoLayout->addLayout(BtnLayout,2,10,1,6,Qt::AlignBottom|Qt::AlignRight);

    DetailInfoLayout->setColumnStretch(0,0);
    DetailInfoLayout->setColumnStretch(1,1);
    DetailInfoLayout->setColumnStretch(2,0);
    DetailInfoLayout->setColumnStretch(3,1);
    DetailInfoLayout->setColumnStretch(4,0);
    DetailInfoLayout->setColumnStretch(5,1);
    DetailInfoLayout->setColumnStretch(6,0);
    DetailInfoLayout->setColumnStretch(7,1);
    DetailInfoLayout->setColumnStretch(8,0);
    DetailInfoLayout->setColumnStretch(9,1);
    DetailInfoLayout->setColumnStretch(10,0);
    DetailInfoLayout->setColumnStretch(11,1);
    DetailInfoLayout->setColumnStretch(12,0);
    DetailInfoLayout->setColumnStretch(13,1);
    DetailInfoLayout->setColumnStretch(14,0);
    DetailInfoLayout->setColumnStretch(15,1);

    QGroupBox *DetailInfoGroupbox = new QGroupBox(this);
    DetailInfoGroupbox->setTitle("采购入库单");
    DetailInfoGroupbox->setLayout(DetailInfoLayout);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(TimeLabel,0);
    hlayout->addWidget(DateTimeEdit1,0);
    hlayout->addWidget(FuHaoLabel,0);
    hlayout->addWidget(DateTimeEdit2,0);
    hlayout->addWidget(SupplierCheck,0);
    hlayout->addWidget(SupplierCombox,1);
    hlayout->addWidget(MaterialCheck,0);
    hlayout->addWidget(MaterialCombox,1);
    hlayout->addWidget(FindBtn,1);
    hlayout->addWidget(ExportBtn,1);
    hlayout->addStretch(2);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(DetailInfoGroupbox);
    layout->addLayout(hlayout);
    layout->addWidget(DetailView);

    tongfahuomingxi->setLayout(layout);
    tabWidget->addTab(tongfahuomingxi,tr("采购入库明细"));
}

void caigourukumingxiDlg::CreateDuizhangJiLu()
{
    SQL3 = "SELECT RecordNo 出车单号,updateContent 修改内容,Operator 核对人,OperatorTime 核对时间 FROM PurchaseReconciliationRecord limit 0";

    QLabel *updateTimeLabel = new QLabel(tr("修改时间"),this);
    updateTimeLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *FuHaoLabel = new QLabel(tr("--"),this);
    FuHaoLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    updateTime1 = new QDateTimeEdit(this);
    updateTime1->setDate(QDate::currentDate());
    updateTime1->setCalendarPopup(true);

    updateTime2 = new QDateTimeEdit(this);
    updateTime2->setDate(QDate::currentDate().addDays(1));
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

void caigourukumingxiDlg::on_FindBtn()
{
    QString Supplier,Material;
    if(SupplierCheck->checkState() == 2){
        Supplier = QString(" and Supplier='%1'").arg(SupplierCombox->currentText());
    }
    if(MaterialCheck->checkState() == 2){
        Material = QString(" and Material='%1'").arg(MaterialCombox->currentText());
    }

    searchPurchaseReceiptSQL = QString("select 0 选中标志,StorageList 入库单号,Supplier 供应商,Material 原材料,SpecificationModel 规格,Position 仓位,LicensePlateNumber 车牌号,GrossWeight 毛重,\
                                GrossWeightTime 毛重时间,Tare 皮重,TareTime 皮重时间,StorageKG 净重,Buckle 扣重,StorageKG 入库重量,StorageCube 入库方量,UnitPrice 单价,\
                                ROUND(StorageKG*UnitPrice/1000,2) 本车价格,Storagefactory 入库厂地,GBMAN 过磅人,Flag 核对标志 from PurchaseReceipt where \
                                GrossWeightTime between '%1' and '%2' %3 %4 order by Supplier,Material,SpecificationModel,Position,GrossWeightTime")
                    .arg(DateTimeEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),DateTimeEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),Supplier,Material);
    db.showview(searchPurchaseReceiptSQL,DetailView,&DetailModel);
    setModelStyle(DetailModel,19);
}

void caigourukumingxiDlg::on_ExportBtn()
{
    ViewToExcel->Table2ExcelByHtml(DetailView,QString("发货明细账"));
}

void caigourukumingxiDlg::on_doubleClickDetailView(QModelIndex index)
{
    StorageListLineEdit->setText(index.model()->index(index.row(),1).data().toString());
    SupplierLineEdit->setText(index.model()->index(index.row(),2).data().toString());
    MaterialNameLineEdit->setText(index.model()->index(index.row(),3).data().toString());
    SpecificationModelLineEdit->setText(index.model()->index(index.row(),4).data().toString());
    PositionLineEdit->setText(index.model()->index(index.row(),5).data().toString());
    LicensePlateNumberLineEdit->setText(index.model()->index(index.row(),6).data().toString());
    GrossWeightLineEdit->setText(index.model()->index(index.row(),7).data().toString());
    GrossWeightTimeLineEdit->setText(index.model()->index(index.row(),8).data().toString());
    TareLineEdit->setText(index.model()->index(index.row(),9).data().toString());
    TareWeightTimeLineEdit->setText(index.model()->index(index.row(),10).data().toString());
    NetWeightLineEdit->setText(index.model()->index(index.row(),13).data().toString());
    BuckleLineEdit->setText(index.model()->index(index.row(),12).data().toString());
    StorageKGLineEdit->setText(index.model()->index(index.row(),13).data().toString());
    StorageCubeLineEdit->setText(index.model()->index(index.row(),14).data().toString());
    UnitPriceLineEdit->setText(index.model()->index(index.row(),15).data().toString());
    StoragefactoryLineEdit->setText(index.model()->index(index.row(),17).data().toString());
}

void caigourukumingxiDlg::on_AllSelectedBtn()
{
    searchPurchaseReceiptSQL.replace("0 选中标志","2 选中标志");
    db.showview(searchPurchaseReceiptSQL,DetailView,&DetailModel);
    setModelStyle(DetailModel,19);

    int rowCount = DetailModel->rowCount();
    for(int i = 0; i<rowCount; i++){
       DetailModel->item(i,0)->setCheckState(Qt::Checked);
    }
}

void caigourukumingxiDlg::on_AllCancelBtn()
{
    searchPurchaseReceiptSQL.replace("2 选中标志","0 选中标志");
    db.showview(searchPurchaseReceiptSQL,DetailView,&DetailModel);
    setModelStyle(DetailModel,19);

    int rowCount = DetailModel->rowCount();
    for(int i = 0; i<rowCount; i++){
       DetailModel->item(i,0)->setCheckState(Qt::Unchecked);
    }
}

void caigourukumingxiDlg::on_AllConfirmBtn()
{
    QString RecordNoList;
    int rowCount = DetailModel->rowCount();
    for(int i=0; i<rowCount; i++){
        if(DetailModel->item(i,0)->checkState() == 2){
            RecordNoList.append(QString("'%1',").arg(DetailModel->item(i,1)->text()));
        }
    }
    RecordNoList = RecordNoList.left(RecordNoList.length()-1);

    QString updateSQL = QString("update PurchaseReceipt set Flag='0' where StorageList in (%1)").arg(RecordNoList);
    int res = db.sql_exec(updateSQL);
    if(res == 0){
        on_FindBtn();
    }
}

void caigourukumingxiDlg::on_ConfirmBtn()
{
    QString searchPurchaseDetail = QString("select Supplier,Material,SpecificationModel,LicensePlateNumber,UnitPrice,GrossWeight,\
                                           GrossWeightTime,Tare,TareTime,NetWeight,Buckle,StorageKG,StorageCube from PurchaseReceipt where StorageList='%1'").arg(StorageListLineEdit->text());
    QStringList resultStrList = db.CreatStrList(searchPurchaseDetail);
    if(resultStrList.count()<13){
        return;
    }

    QString updateSQL = QString("update PurchaseReceipt set Flag='0',Supplier='%1',Material='%2',SpecificationModel='%3',LicensePlateNumber='%4',UnitPrice='%5',GrossWeight='%6',\
                                GrossWeightTime='%7',Tare='%8',TareTime='%9',NetWeight='%10',Buckle='%11',StorageKG='%12',StorageCube='%13' where StorageList='%14'")
            .arg(SupplierLineEdit->text(),MaterialNameLineEdit->text(),SpecificationModelLineEdit->text(),LicensePlateNumberLineEdit->text(),UnitPriceLineEdit->text(),GrossWeightLineEdit->text(),
                 GrossWeightTimeLineEdit->text(),TareLineEdit->text(),TareWeightTimeLineEdit->text())
            .arg(NetWeightLineEdit->text(),BuckleLineEdit->text(),StorageKGLineEdit->text(),StorageCubeLineEdit->text(),StorageListLineEdit->text());
    db.sql_exec(updateSQL.toStdString().data());

    QString updateContent;
    if(resultStrList.at(0)!=SupplierLineEdit->text()){
        updateContent.append(" 供应商：").append(resultStrList.at(0)).append("→").append(SupplierLineEdit->text());
    }
    if(resultStrList.at(1)!=MaterialNameLineEdit->text()){
        updateContent.append(" 原材料：").append(resultStrList.at(1)).append("→").append(MaterialNameLineEdit->text());
    }
    if(resultStrList.at(2)!=SpecificationModelLineEdit->text()){
        updateContent.append(" 规格：").append(resultStrList.at(2)).append("→").append(SpecificationModelLineEdit->text());
    }
    if(resultStrList.at(3)!=LicensePlateNumberLineEdit->text()){
        updateContent.append(" 车牌号：").append(resultStrList.at(3)).append("→").append(LicensePlateNumberLineEdit->text());
    }
    if(resultStrList.at(4)!=UnitPriceLineEdit->text()){
        updateContent.append(" 单价：").append(resultStrList.at(4)).append("→").append(UnitPriceLineEdit->text());
    }
    if(resultStrList.at(5)!=GrossWeightLineEdit->text()){
        updateContent.append(" 毛重：").append(resultStrList.at(5)).append("→").append(GrossWeightLineEdit->text());
    }
    if(resultStrList.at(6)!=GrossWeightTimeLineEdit->text()){
        updateContent.append(" 毛重时间：").append(resultStrList.at(6)).append("→").append(GrossWeightTimeLineEdit->text());
    }
    if(resultStrList.at(7)!=TareLineEdit->text()){
        updateContent.append(" 皮重：").append(resultStrList.at(7)).append("→").append(TareLineEdit->text());
    }
    if(resultStrList.at(8)!=TareWeightTimeLineEdit->text()){
        updateContent.append(" 皮重时间：").append(resultStrList.at(8)).append("→").append(TareWeightTimeLineEdit->text());
    }
    if(resultStrList.at(9)!=NetWeightLineEdit->text()){
        updateContent.append(" 净重：").append(resultStrList.at(9)).append("→").append(NetWeightLineEdit->text());
    }
    if(resultStrList.at(10)!=BuckleLineEdit->text()){
        updateContent.append(" 扣重：").append(resultStrList.at(10)).append("→").append(BuckleLineEdit->text());
    }
    if(resultStrList.at(11)!=StorageKGLineEdit->text()){
        updateContent.append(" 入库重量：").append(resultStrList.at(11)).append("→").append(StorageKGLineEdit->text());
    }
    if(resultStrList.at(12)!=StorageCubeLineEdit->text()){
        updateContent.append(" 入库方量：").append(resultStrList.at(12)).append("→").append(StorageCubeLineEdit->text());
    }


    QString insertSQL = QString("insert into PurchaseReconciliationRecord (RecordNo,updateContent,Operator,OperatorTime) values ('%1','%2','%3','%4')")
            .arg(StorageListLineEdit->text(),updateContent,userName,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    db.sql_exec(insertSQL.toStdString().data());

    on_FindBtn();
}

void caigourukumingxiDlg::on_threeFindBtn()
{
    QString searchSQL = QString("SELECT RecordNo 出车单号,updateContent 修改内容,Operator 核对人,OperatorTime 核对时间 FROM PurchaseReconciliationRecord where OperatorTime between '%1' and '%2'")
            .arg(updateTime1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),updateTime2->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
    db.showview(searchSQL.toStdString().data(),ReconciliationView,&ReconciliationModel);
}

void caigourukumingxiDlg::setModelStyle(QStandardItemModel *model,int column)
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
