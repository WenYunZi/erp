#include "yuanliaorukushujutiaozhengdlg.h"

extern mymysql db;
extern QString userName;
extern myTCPsocket *sockClient;

yuanliaorukushujutiaozhengDlg::yuanliaorukushujutiaozhengDlg(QWidget *parent) :
    QDialog(parent)
{
    tabWidget = new QTabWidget(this);
    yuanliaojiagetiaozheng = new QWidget(this);
    jiagetiaozhengjiluchaxun = new QWidget(this);

    creatTabPage1();
    creatTabPage2();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tabWidget);
}

void yuanliaorukushujutiaozhengDlg::refresh()
{
//    on_oneFindBtn();
//    on_twoFindBtn();
}

void yuanliaorukushujutiaozhengDlg::keyPressEvent(QKeyEvent *event)
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

void yuanliaorukushujutiaozhengDlg::creatTabPage1()
{
    SQL1 = "select StorageList 入库单,Material 原料,SpecificationModel 规格,Supplier 供应商,StorageKG 入库数量KG,UnitPrice 单价,round(StorageKG*UnitPrice/1000,2) 金额,LicensePlateNumber 车牌号,\
            Time 入库时间,Remarks 备注 from PurchaseReceipt limit 0";

    QLabel *MaterialLabel = new QLabel(tr("原料名称"),this);
    MaterialLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *NewPriceLabel = new QLabel(tr("新价格"),this);
    NewPriceLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *SupplierLabel = new QLabel(tr("供应商"),this);
    SupplierLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *StorageTimeLabel = new QLabel(tr("入库时间"),this);
    StorageTimeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *FuHaoLabel = new QLabel(tr("--"),this);
    FuHaoLabel->setAlignment(Qt::AlignCenter|Qt::AlignVCenter);
    QLabel *OperatorLabel = new QLabel(tr("调整人"),this);
    OperatorLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *UnitLabel = new QLabel(tr("元/吨"),this);
    UnitLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *WarningLabel = new QLabel(tr("注：单价为吨/元"),this);
    WarningLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    WarningLabel->setStyleSheet("color:red");

    MaterialCombox =  new myComboBox(this);
    db.sql_fillComboBoxItem("select MaterialName from PurchaseLedger group by MaterialName",MaterialCombox);
    connect(MaterialCombox,SIGNAL(editTextChanged(QString)),this,SLOT(on_MaterialCombox()));

    SupplierCombox = new QComboBox(this);

    datetimeEdit1 = new QDateTimeEdit(this);
    datetimeEdit1->setDate(QDate::currentDate());
    datetimeEdit1->setCalendarPopup(true);

    datetimeEdit2 = new QDateTimeEdit(this);
    datetimeEdit2->setDate(QDate::currentDate().addDays(1));
    datetimeEdit2->setCalendarPopup(true);

    NewPriceLineEdit = new QLineEdit(this);

    OperatorLineEdit = new QLineEdit(userName,this);
    OperatorLineEdit->setStyleSheet("color:black");
    OperatorLineEdit->setEnabled(false);

    oneFindBtn = new QPushButton(tr("入库记录查询"),this);
    oneFindBtn->setFixedWidth(120);
    connect(oneFindBtn,SIGNAL(clicked()),this,SLOT(on_oneFindBtn()));

    PriceUpdateBtn = new QPushButton(tr("价格调整"),this);
    PriceUpdateBtn->setFixedWidth(120);
    connect(PriceUpdateBtn,SIGNAL(clicked()),this,SLOT(on_PriceUpdateBtn()));

    view = new QTableView(this);
    db.showview(SQL1,view,&model);
    view->setColumnWidth(8,130);

    QGridLayout *layout = new QGridLayout;


    layout->addWidget(StorageTimeLabel,0,0);
    layout->addWidget(datetimeEdit1,0,1);
    layout->addWidget(FuHaoLabel,0,2);
    layout->addWidget(datetimeEdit2,0,3);
    layout->addWidget(OperatorLabel,0,4);
    layout->addWidget(OperatorLineEdit,0,5);



    layout->addWidget(MaterialLabel,1,0);
    layout->addWidget(MaterialCombox,1,1);
    layout->addWidget(SupplierLabel,1,2);
    layout->addWidget(SupplierCombox,1,3);
    layout->addWidget(NewPriceLabel,1,4);
    layout->addWidget(NewPriceLineEdit,1,5);
    layout->addWidget(UnitLabel,1,6);


    layout->addWidget(PriceUpdateBtn,0,7,2,1,Qt::AlignVCenter);

    layout->setColumnStretch(0,0);
    layout->setColumnStretch(1,1);
    layout->setColumnStretch(2,0);
    layout->setColumnStretch(3,1);
    layout->setColumnStretch(4,0);
    layout->setColumnStretch(5,1);
    layout->setColumnStretch(6,0);
    layout->setColumnStretch(7,1);
    layout->setColumnStretch(8,0);
    layout->setColumnStretch(9,1);
    layout->setColumnStretch(10,1);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(oneFindBtn,1);
    hlayout->addWidget(WarningLabel,0);
    hlayout->addStretch(4);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(layout);
    vlayout->addSpacing(10);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(view);

    yuanliaojiagetiaozheng->setLayout(vlayout);
    tabWidget->addTab(yuanliaojiagetiaozheng,tr("原料价格调整"));
}

void yuanliaorukushujutiaozhengDlg::creatTabPage2()
{
    SQL2 = "select StorageList  入库单,MaterialName 原料名称,Supplier 供应商,OriginalPrice 原价格,NewPrice 新价格,AdjustmentTime 调整时间,AdjustmentMan 调整人 from PriceAdjustmentRecord limit 0";

    QLabel *UpdateTimeLabel = new QLabel(tr("调整时间"),this);
    UpdateTimeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *FuHaoLabel = new QLabel(tr("--"),this);
    FuHaoLabel->setAlignment(Qt::AlignCenter|Qt::AlignVCenter);

    twodatetimeEdit1 = new QDateTimeEdit(this);
    twodatetimeEdit1->setDate(QDate::currentDate());
    twodatetimeEdit1->setCalendarPopup(true);

    twodatetimeEdit2 = new QDateTimeEdit(this);
    twodatetimeEdit2->setDate(QDate::currentDate().addDays(1));
    twodatetimeEdit2->setCalendarPopup(true);


    twoMaterialCheckBox = new QCheckBox(tr("原料名称"),this);
    twoSupplierNameCheckBox = new QCheckBox(tr("供应商"),this);

    twoMaterialCombox = new QComboBox(this);
    QString fillSQL1 = QString("select MaterialName from PurchaseMaterialList group by MaterialName;");
    db.sql_fillComboBoxItem(fillSQL1.toStdString().data(),twoMaterialCombox);
    connect(twoMaterialCombox,SIGNAL(currentIndexChanged(int)),this,SLOT(on_twoMaterialCombox()));

    twoSupplierNameCombox = new QComboBox(this);

    twoFindBtn = new QPushButton(tr("查询"),this);
    twoFindBtn->setFixedWidth(120);
    connect(twoFindBtn,SIGNAL(clicked()),this,SLOT(on_twoFindBtn()));

    twoview = new QTableView(this);
    db.showview(SQL2,twoview,&twomodel);
    twoview->setColumnWidth(7,120);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(UpdateTimeLabel,0);
    hlayout->addWidget(twodatetimeEdit1,0);
    hlayout->addWidget(FuHaoLabel,0);
    hlayout->addWidget(twodatetimeEdit2,0);
    hlayout->addWidget(twoMaterialCheckBox,0);
    hlayout->addWidget(twoMaterialCombox,1);
    hlayout->addWidget(twoSupplierNameCheckBox,0);
    hlayout->addWidget(twoSupplierNameCombox,1);
    hlayout->addWidget(twoFindBtn,1);
    hlayout->addStretch(4);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(twoview);

    jiagetiaozhengjiluchaxun->setLayout(vlayout);
    tabWidget->addTab(jiagetiaozhengjiluchaxun,tr("价格调整记录查询"));
}

void yuanliaorukushujutiaozhengDlg::on_MaterialCombox()
{
    SupplierCombox->clear();
    QString fillSQL2 = QString("select Supplier from PurchaseReceipt where Material='%1' group by Supplier;").arg(MaterialCombox->currentText());
    db.sql_fillComboBoxItem(fillSQL2,SupplierCombox);
}

void yuanliaorukushujutiaozhengDlg::on_oneFindBtn()
{
    searchSQL1 = QString("select StorageList 入库单,Material 原料,SpecificationModel 规格,Supplier 供应商,StorageKG 入库数量KG,UnitPrice 单价,round(StorageKG*UnitPrice/1000,2) 金额,LicensePlateNumber 车牌号,\
                            GrossWeightTime 入库时间,Remarks 备注 from PurchaseReceipt where Material='%1' and Supplier='%2' and GrossWeightTime between '%3' and '%4'")
                .arg(MaterialCombox->currentText(),SupplierCombox->currentText(),datetimeEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),datetimeEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
    db.showview(searchSQL1,view,&model);

    tiaojian = searchSQL1.mid(searchSQL1.indexOf("where"));
}

void yuanliaorukushujutiaozhengDlg::on_PriceUpdateBtn()
{
    int rowcount = model->rowCount();
    if(rowcount == 0){
        QMessageBox::information(this,tr("提示信息"),tr("请筛选出要调整的入库单"),0,0,0);
        return;
    }
    if(NewPriceLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入新价格"),0,0,0);
        return;
    }
    //事务开始
    db.sql_exec("begin");
    for(int i = 0; i<rowcount; i++){
        //调整记录计入价格调整记录表中
        QString replaceSQL = QString("replace into PriceAdjustmentRecord (StorageList,MaterialName,Supplier,OriginalPrice,NewPrice,AdjustmentTime,AdjustmentMan) values ('%1','%2','%3','%4','%5','%6','%7')")
                        .arg(model->item(i,0)->text(),model->item(i,1)->text(),model->item(i,3)->text(),model->item(i,5)->text(),NewPriceLineEdit->text(),QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm"),OperatorLineEdit->text());
        if(db.sql_exec(replaceSQL.toStdString().data()) == -1){
            db.sql_exec("rollback");
            return;
        }
    }
    //更新入库单中的价格
    QString updateSQL = QString("update PurchaseReceipt set UnitPrice='%1' %2").arg(NewPriceLineEdit->text(),tiaojian);
    if(db.sql_exec(updateSQL.toStdString().data()) == -1){
        db.sql_exec("rollback");
        return;
    }
    db.sql_exec("commit");

    on_oneFindBtn();
    NewPriceLineEdit->clear();
    QMessageBox::information(this,tr("提示信息"),tr("价格调整成功"),0,0,0);
}

void yuanliaorukushujutiaozhengDlg::on_twoMaterialCombox()
{
    twoSupplierNameCombox->clear();
    QString fillSQL2 = QString("select Supplier from PurchaseMaterialList where MaterialName='%1'").arg(twoMaterialCombox->currentText());
    db.sql_fillComboBoxItem(fillSQL2,twoSupplierNameCombox);
}

void yuanliaorukushujutiaozhengDlg::on_twoFindBtn()
{
    QString MaterialName,Supplier;
    if(twoMaterialCheckBox->checkState() == 2){
        MaterialName = QString(" and MaterialName='%1'").arg(twoMaterialCombox->currentText());
    }
    if(twoSupplierNameCheckBox->checkState() == 2){
        Supplier = QString(" and Supplier='%1'").arg(twoSupplierNameCombox->currentText());
    }

    QString searchSQL = QString("select StorageList  入库单,MaterialName 原料名称,Supplier 供应商,OriginalPrice 原价格,NewPrice 新价格,AdjustmentTime 调整时间,\
                                AdjustmentMan 调整人 from PriceAdjustmentRecord where AdjustmentTime between '%1' and '%2' %3 %4")
            .arg(twodatetimeEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),twodatetimeEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),MaterialName,Supplier);
    db.showview(searchSQL,twoview,&twomodel);
}
