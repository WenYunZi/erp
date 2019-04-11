#include "caigouhetongguanlidlg.h"

extern mymysql db;
extern pubfunc pub;
extern QString userName;
extern myTCPsocket *sockClient;

caigouhetongguanliDlg::caigouhetongguanliDlg(QWidget *parent) :
    QDialog(parent)
{
    tabWidget = new QTabWidget(this);
    SupplierWidget = new QWidget(this);
    ContractWidget = new QWidget(this);
    PurchasePriceCorrectWidget = new QWidget(this);

    creatTabPage_Supplier();
    creatTabPage_Contract();
    creatTabPage_PurchasePriceCorrect();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tabWidget);
}

void caigouhetongguanliDlg::refresh()
{

}

void caigouhetongguanliDlg::keyPressEvent(QKeyEvent *event)
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

void caigouhetongguanliDlg::creatTabPage_Supplier()
{
    createAction();
    createTool();

    SQL1 = "select ID 供应商编号,Name 供应商名称,Contacts 联系人,Telephone 联系电话,Address 地址,BusinessLicense 营业执照,OrganizationCode 组织机构代码,Bank 开户行,Account 账号,Payee 收款人,Fax 传真 from SupplierFile";

    QLabel *SupplierNumberLabel = new QLabel(tr("供应商编号"),this);
    SupplierNumberLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *SupplierNameLabel = new QLabel(tr("供应商名称"),this);
    SupplierNameLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *ContactLabel = new QLabel(tr("联系人"),this);
    ContactLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *BusinessLicenseLabel = new QLabel(tr("营业执照"),this);
    BusinessLicenseLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *OrganizationCodeLabel = new QLabel(tr("组织机构代码"),this);
    OrganizationCodeLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *BankLabel = new QLabel(tr("开户行"),this);
    BankLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *AccountNumberLabel = new QLabel(tr("账号"),this);
    AccountNumberLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *PayeeLabel = new QLabel(tr("收款人"),this);
    PayeeLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *AddressLabel = new QLabel(tr("地址"),this);
    AddressLabel->setAlignment(Qt::AlignRight);
    QLabel *TelephoneLabel = new QLabel(tr("联系电话"),this);
    TelephoneLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *FaxLabel = new QLabel(tr("传真"),this);
    FaxLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    SupplierNumberLineEdit = new QLineEdit(this);
    SupplierNumberLineEdit->setStyleSheet("color:black");
    SupplierNameLineEdit = new QLineEdit(this);
    ContactLineEdit = new QLineEdit(this);
    TelephoneLineEdit = new QLineEdit(this);
    BusinessLicenseLineEdit = new QLineEdit(this);
    OrganizationCodeLineEdit = new QLineEdit(this);
    BankLineEdit = new QLineEdit(this);
    AccountNumberLineEdit = new QLineEdit(this);
    PayeeLineEdit = new QLineEdit(this);
    FaxLineEdit = new QLineEdit(this);
    AddressLineEdit = new QLineEdit(this);

    SupplierView = new QTableView(this);
    connect(SupplierView,SIGNAL(clicked(QModelIndex)),this,SLOT(ShowSupplyclick()));
    connect(SupplierView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyDoubleClick()));
    db.showview(SQL1,SupplierView,&SupplierModel);
    SupplierView->setColumnWidth(1,230);

    QGridLayout *layout1 = new QGridLayout;
    layout1->addWidget(SupplierNumberLabel,0,0);
    layout1->addWidget(SupplierNumberLineEdit,0,1);
    layout1->addWidget(SupplierNameLabel,0,2);
    layout1->addWidget(SupplierNameLineEdit,0,3);
    layout1->addWidget(ContactLabel,0,4);
    layout1->addWidget(ContactLineEdit,0,5);
    layout1->addWidget(TelephoneLabel,0,6);
    layout1->addWidget(TelephoneLineEdit,0,7);
    layout1->addWidget(BusinessLicenseLabel,1,0);
    layout1->addWidget(BusinessLicenseLineEdit,1,1);
    layout1->addWidget(OrganizationCodeLabel,1,2);
    layout1->addWidget(OrganizationCodeLineEdit,1,3);
    layout1->addWidget(BankLabel,1,4);
    layout1->addWidget(BankLineEdit,1,5);
    layout1->addWidget(AccountNumberLabel,1,6);
    layout1->addWidget(AccountNumberLineEdit,1,7);
    layout1->addWidget(PayeeLabel,2,0);
    layout1->addWidget(PayeeLineEdit,2,1);
    layout1->addWidget(FaxLabel,2,2);
    layout1->addWidget(FaxLineEdit,2,3);
    layout1->addWidget(AddressLabel,2,4);
    layout1->addWidget(AddressLineEdit,2,5,1,3);
    layout1->setColumnStretch(0,0);
    layout1->setColumnStretch(1,1);
    layout1->setColumnStretch(2,0);
    layout1->setColumnStretch(3,1);
    layout1->setColumnStretch(4,0);
    layout1->setColumnStretch(5,1);
    layout1->setColumnStretch(6,0);
    layout1->setColumnStretch(7,1);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(toolBar);
    vlayout->addLayout(layout1);
    vlayout->addWidget(SupplierView);

    SupplierWidget->setLayout(vlayout);
    tabWidget->addTab(SupplierWidget,tr("供应商管理"));
}

void caigouhetongguanliDlg::creatTabPage_Contract()
{
    //SQL1 = "select ProjectName 工程名称 from SalesContractCustomerEngineeringForm limit 0";

    QLabel *twoSupplierLabel = new QLabel(tr("供应商名称"),this);
    twoSupplierLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    QLabel *twoPriceUseTimeLabel = new QLabel(tr("价格启用时间"),this);
    twoPriceUseTimeLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);

    twoSupplierLineEdit = new QLineEdit(this);
    twoSupplierLineEdit->setReadOnly(true);

    twoStartUseTimeEdit = new QDateTimeEdit(this);
    twoStartUseTimeEdit->setCalendarPopup(true);
    twoStartUseTimeEdit->setDate(QDate::currentDate());

    twoMaterialQuxiaoBtn = new QPushButton(tr("取消"),this);
    twoMaterialQuxiaoBtn->setFixedWidth(70);
    connect(twoMaterialQuxiaoBtn,SIGNAL(clicked()),this,SLOT(on_twoMaterialQuxiaoBtn()));
    twoMaterialQuanxuanBtn = new QPushButton(tr("全选"),this);
    twoMaterialQuanxuanBtn->setFixedWidth(70);
    connect(twoMaterialQuanxuanBtn,SIGNAL(clicked()),this,SLOT(on_twoMaterialQuanxuanBtn()));

    twoMaterialSaveBtn = new QPushButton(tr("保存"),this);
    twoMaterialSaveBtn->setFixedWidth(100);
    connect(twoMaterialSaveBtn,SIGNAL(clicked()),this,SLOT(on_twoMaterialSaveBtn()));

    twoMaterialDeleteBtn = new QPushButton(tr("删除"),this);
    twoMaterialDeleteBtn->setFixedWidth(100);
    connect(twoMaterialDeleteBtn,SIGNAL(clicked()),this,SLOT(on_twoMaterialDeleteBtn()));


    twoNewMaterialBtn = new QPushButton(tr("新增"),this);
    twoNewMaterialBtn->setFixedWidth(100);
    connect(twoNewMaterialBtn,SIGNAL(clicked()),this,SLOT(on_twoNewMaterialBtn()));

    QGroupBox *twoMaterialSaveGroupbox = new QGroupBox(this);
    twoMaterialSaveGroupbox->setTitle(tr("原材料添加及改价"));

    twoMaterialTreeView = new QTreeView;
    connect(twoMaterialTreeView,SIGNAL(clicked(QModelIndex)),this,SLOT(twoMaterialTreeViewClick(const QModelIndex)));


    init_MaterialWidget();

    //产品布局
    QHBoxLayout *MaterialboxHlayout = new QHBoxLayout;
    MaterialboxHlayout->addWidget(twoMaterialQuxiaoBtn);
    MaterialboxHlayout->addWidget(twoMaterialQuanxuanBtn);
    MaterialboxHlayout->addStretch(1);

    QVBoxLayout *MaterialboxVlayout = new QVBoxLayout;
    MaterialboxVlayout->addLayout(MaterialboxHlayout);
    MaterialboxVlayout->addWidget(twoMaterialWidget);

    twoMaterialGroupBox = new QGroupBox;
    twoMaterialGroupBox->setTitle(tr("请选择该供应商所供应的原材料，并在选择后输入价格信息"));
    twoMaterialGroupBox->setLayout(MaterialboxVlayout);

    //工程添加布局
    QHBoxLayout *MaterialSaveLayout = new QHBoxLayout;
    MaterialSaveLayout->addWidget(twoSupplierLabel,0);
    MaterialSaveLayout->addWidget(twoSupplierLineEdit,1);
    MaterialSaveLayout->addWidget(twoPriceUseTimeLabel,0);
    MaterialSaveLayout->addWidget(twoStartUseTimeEdit,0);
    MaterialSaveLayout->addWidget(twoMaterialSaveBtn,1);
    MaterialSaveLayout->addWidget(twoMaterialDeleteBtn,1);
    MaterialSaveLayout->addWidget(twoNewMaterialBtn,1);
    MaterialSaveLayout->addStretch(2);
    twoMaterialSaveGroupbox->setLayout(MaterialSaveLayout);

    //原材料groupbox
    QVBoxLayout *MaterialAndPicLayout = new QVBoxLayout;
    MaterialAndPicLayout->addWidget(twoMaterialGroupBox,1);
    MaterialAndPicLayout->addStretch(1);

    //原材料列表layout
    QHBoxLayout *MaterialListLayout = new QHBoxLayout;
    MaterialListLayout->addWidget(twoMaterialTreeView);

    MaterialListBox = new QGroupBox;
    MaterialListBox->setTitle(tr("原材料列表"));
    MaterialListBox->setLayout(MaterialListLayout);

    //页面下方整体布局
    QHBoxLayout *viewLayout = new QHBoxLayout;
    viewLayout->addWidget(MaterialListBox,1);
    viewLayout->addLayout(MaterialAndPicLayout,3);


    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(twoMaterialSaveGroupbox);//添加头部布局
    vlayout->addLayout(viewLayout);

    ContractWidget->setLayout(vlayout);
    tabWidget->addTab(ContractWidget,tr("采购合同查询"));
}

void caigouhetongguanliDlg::creatTabPage_PurchasePriceCorrect()
{
    SQL3 = "select Name 供应商名称, 0 是否修改 from SupplierFile";

    QLabel *purchaseReceiptTime1Labe = new QLabel(tr("入库单时间"),this);
    purchaseReceiptTime1Labe->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
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

    threeSupplierListView = new QTableView(this);
    threeSupplierListView->setItemDelegate(new myCheckBoxDelegate(1,this));
    db.showview(SQL3,threeSupplierListView,&threeSupplierListModel);
    threeSupplierListView->setColumnWidth(0,300);


    threeUpdateDetailInfoView = new QTableView(this);
    db.showview("select updateSupplier 修改的供应商,receiptTime 修改的入库单日期,Operator 修改人,OperatingTime 修改时间 from PurchaseReceiptPriceCorrectRecord limit 0",threeUpdateDetailInfoView,&threeUpdateDetailInfoModel);
    threeUpdateDetailInfoView->setColumnWidth(0,300);
    threeUpdateDetailInfoView->setColumnWidth(1,300);
    threeUpdateDetailInfoView->setColumnWidth(3,130);

    QHBoxLayout *BtnLayout = new QHBoxLayout;
    BtnLayout->addStretch(10);
    BtnLayout->addWidget(threeQuanXuanBtn,1);
    BtnLayout->addWidget(threeQuXiaoBtn,1);

    QVBoxLayout *SupplierListBoxLayout = new QVBoxLayout;
    SupplierListBoxLayout->addWidget(threeSupplierListView);
    SupplierListBoxLayout->addLayout(BtnLayout);

    QGroupBox *SupplierListBox = new QGroupBox(this);
    SupplierListBox->setTitle(tr("供应商列表"));
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
    hlayout1->addWidget(purchaseReceiptTime1Labe,0);
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

    PurchasePriceCorrectWidget->setLayout(vlayout);
    tabWidget->addTab(PurchasePriceCorrectWidget,tr("采购入库单价格修正"));
}

void caigouhetongguanliDlg::on_newAction()
{
    saveAction->setEnabled(true);
    updateAction->setEnabled(false);
    deleteAction->setEnabled(false);

    SupplierNumberLineEdit->clear();
    SupplierNameLineEdit->clear();
    ContactLineEdit->clear();
    TelephoneLineEdit->clear();
    BusinessLicenseLineEdit->clear();
    OrganizationCodeLineEdit->clear();
    BankLineEdit->clear();
    AccountNumberLineEdit->clear();
    PayeeLineEdit->clear();
    FaxLineEdit->clear();
    AddressLineEdit->clear();
}

void caigouhetongguanliDlg::on_newAction_plus()
{
    saveAction->setEnabled(true);
    updateAction->setEnabled(false);
    deleteAction->setEnabled(false);

    SupplierNumberLineEdit->setText(pub.newPurchaseContracNo());
    SupplierNameLineEdit->clear();
    ContactLineEdit->clear();
    TelephoneLineEdit->clear();
    BusinessLicenseLineEdit->clear();
    OrganizationCodeLineEdit->clear();
    BankLineEdit->clear();
    AccountNumberLineEdit->clear();
    PayeeLineEdit->clear();
    FaxLineEdit->clear();
    AddressLineEdit->clear();
}

void caigouhetongguanliDlg::on_saveAction()
{
    if(SupplierNumberLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入供应商编号"),0,0,0);
        return;
    }
    if(SupplierNameLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入供应商名称"),0,0,0);
        return;
    }

    QString saveSQL = QString("insert into SupplierFile (ID,Name,Contacts,Telephone,Address,BusinessLicense,OrganizationCode,\
                              Bank,Account,Payee,Fax) values ('%1','%2','%3','%4','%5','%6','%7','%8','%9','%10','%11');")
                .arg(SupplierNumberLineEdit->text(),SupplierNameLineEdit->text(),ContactLineEdit->text(),TelephoneLineEdit->text(),AddressLineEdit->text(),
                     BusinessLicenseLineEdit->text(),OrganizationCodeLineEdit->text())
                .arg(BankLineEdit->text(),AccountNumberLineEdit->text(),PayeeLineEdit->text(),FaxLineEdit->text());
    int res = db.sql_exec(saveSQL);
    if(res == -1){
        QMessageBox::information(this,tr("错误"),tr("请检查供应商编号是否重复"),0,0,0);
        return;
    }

    db.showview(SQL1,SupplierView,&SupplierModel);
    on_newAction();
    QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
}

void caigouhetongguanliDlg::on_updateAction()
{
    if(SupplierNumberLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入供应商编号"),0,0,0);
        return;
    }
    if(SupplierNameLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入供应商名称"),0,0,0);
        return;
    }

    QString updateSQL = QString("replace into SupplierFile (ID,Name,Contacts,Telephone,Address,BusinessLicense,OrganizationCode,\
                              Bank,Account,Payee,Fax) values ('%1','%2','%3','%4','%5','%6','%7','%8','%9','%10','%11');")
                .arg(SupplierNumberLineEdit->text(),SupplierNameLineEdit->text(),ContactLineEdit->text(),TelephoneLineEdit->text(),AddressLineEdit->text(),
                     BusinessLicenseLineEdit->text(),OrganizationCodeLineEdit->text())
                .arg(BankLineEdit->text(),AccountNumberLineEdit->text(),PayeeLineEdit->text(),FaxLineEdit->text());
    int res = db.sql_exec(updateSQL);
    if(res == -1){
        QMessageBox::information(this,tr("错误"),tr("请检查供应商编号是否重复"),0,0,0);
        return;
    }

    db.showview(SQL1,SupplierView,&SupplierModel);
    on_newAction();
    QMessageBox::information(this,tr("提示信息"),tr("修改成功"),0,0,0);
}

void caigouhetongguanliDlg::on_deleteAction()
{
    QString deletePurchaseMaterialListSQL = QString("delete from PurchaseMaterialList where Supplier='%1';").arg(SupplierNumberLineEdit->text());
    db.sql_exec(deletePurchaseMaterialListSQL);

    QString deleteSQL = QString("delete from SupplierFile where ID='%1';").arg(SupplierNumberLineEdit->text());
    int res = db.sql_exec(deleteSQL);
    if(res == 0){
        db.showview(SQL1,SupplierView,&SupplierModel);
        on_newAction();
        QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
    }
}

void caigouhetongguanliDlg::ShowSupplyclick()
{
    updateAction->setEnabled(true);
    deleteAction->setEnabled(true);
    saveAction->setEnabled(false);
    SupplierNumberLineEdit->setReadOnly(true);

    int row = SupplierView->currentIndex().row();
    SupplierNumberLineEdit->setText(SupplierModel->item(row,0)->text());
    SupplierNameLineEdit->setText(SupplierModel->item(row,1)->text());
    ContactLineEdit->setText(SupplierModel->item(row,2)->text());
    TelephoneLineEdit->setText(SupplierModel->item(row,3)->text());
    AddressLineEdit->setText(SupplierModel->item(row,4)->text());
    BusinessLicenseLineEdit->setText(SupplierModel->item(row,5)->text());
    OrganizationCodeLineEdit->setText(SupplierModel->item(row,6)->text());
    BankLineEdit->setText(SupplierModel->item(row,7)->text());
    AccountNumberLineEdit->setText(SupplierModel->item(row,8)->text());
    PayeeLineEdit->setText(SupplierModel->item(row,9)->text());
    FaxLineEdit->setText(SupplierModel->item(row,10)->text());
}

void caigouhetongguanliDlg::ShowSupplyDoubleClick()
{
    int row = SupplierView->currentIndex().row();
    SupplierContractNumber = SupplierModel->item(row,0)->text();
    twoSupplierLineEdit->setText(SupplierModel->item(row,1)->text());
    twoStartUseTimeEdit->setDate(QDate::currentDate());

    QString SearchMaterialSQL = QString("select CONCAT(MaterialName,' ',Specifications),DateTime from PurchaseMaterialList where Supplier='%1' order by CONCAT(MaterialName,' ',Specifications),DateTime").arg(twoSupplierLineEdit->text());
    db.show_treeview2(SearchMaterialSQL.toStdString().data(),twoMaterialTreeView,&twoMaterialTreeModel);


    tabWidget->setCurrentIndex(1);
}

void caigouhetongguanliDlg::on_twoMaterialQuxiaoBtn()
{
    for(int i = 0; i<material_count; i++){
        twoMaterialCheckBoxList[i]->setCheckState(Qt::Unchecked);
    }
}

void caigouhetongguanliDlg::on_twoMaterialQuanxuanBtn()
{
    for(int i = 0; i<material_count; i++){
        twoMaterialCheckBoxList[i]->setCheckState(Qt::Checked);
    }
}

void caigouhetongguanliDlg::on_twoMaterialSaveBtn()
{
    //删除之前的原材料
    QString deleteMaterialListSQL = QString("delete from PurchaseMaterialList where Supplier='%1' and DateTime='%2'")
                                .arg(twoSupplierLineEdit->text(),twoStartUseTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"));

    //添加新价格
    QString saveMaterialListSQL = QString("replace into PurchaseMaterialList (ContractNumber,Supplier,MaterialName,Specifications,Price,DateTime) values ");
    for(int i = 0; i<material_count; i++){
        if(twoMaterialCheckBoxList[i]->checkState() == 2){
            saveMaterialListSQL = saveMaterialListSQL.append(QString("('%1','%2','%3','%4','%5','%6'),")
                                      .arg(SupplierContractNumber,twoSupplierLineEdit->text(),twoMaterialCheckBoxList[i]->text().section(" ",0,0),
                                           twoMaterialCheckBoxList[i]->text().section(" ",1,1),twoMaterialLineEditList[i]->text(),
                                           twoStartUseTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss")));
        }
    }
    saveMaterialListSQL = saveMaterialListSQL.left(saveMaterialListSQL.length()-1);



    int res = 0;
    db.sql_exec("begin");
    res = db.sql_exec(deleteMaterialListSQL);
    if(res == -1){
        db.sql_exec("rollback");
        return;
    }
    res = db.sql_exec(saveMaterialListSQL);
    if(res == -1){
        db.sql_exec("rollback");
        QMessageBox::information(this,tr("提示信息"),tr("请至少选择一种原材料"),0,0,0);
        return;
    }
    db.sql_exec("commit");

    QString SearchMaterialSQL = QString("select CONCAT(MaterialName,' ',Specifications),DateTime from PurchaseMaterialList where Supplier='%1' order by CONCAT(MaterialName,' ',Specifications),DateTime").arg(twoSupplierLineEdit->text());
    db.show_treeview2(SearchMaterialSQL.toStdString().data(),twoMaterialTreeView,&twoMaterialTreeModel);

    QMessageBox::information(this,tr("提示信息"),tr("操作成功"),0,0,0);
}

void caigouhetongguanliDlg::on_twoMaterialDeleteBtn()
{
    if(!twoMaterialTreeView->currentIndex().isValid()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择要删除的项目"),0,0,0);
        return;
    }

    QString deleteProduct = QString("delete from PurchaseMaterialList where Supplier='%1' and CONCAT(MaterialName,' ',Specifications)='%2' and DateTime='%3'")
            .arg(twoSupplierLineEdit->text(),twoMaterialAndSpecifications,twoStartUseTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"));

    int res = db.sql_exec(deleteProduct.toStdString().data());
    if(res == 0){
        QString SearchMaterialSQL = QString("select CONCAT(MaterialName,' ',Specifications),DateTime from PurchaseMaterialList where Supplier='%1' order by CONCAT(MaterialName,' ',Specifications),DateTime").arg(twoSupplierLineEdit->text());
        db.show_treeview2(SearchMaterialSQL.toStdString().data(),twoMaterialTreeView,&twoMaterialTreeModel);
        twoMaterialAndSpecifications.clear();

        on_twoNewMaterialBtn();
        QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
    }
}

void caigouhetongguanliDlg::on_twoNewMaterialBtn()
{
    twoStartUseTimeEdit->setDate(QDate::currentDate());
}

void caigouhetongguanliDlg::twoMaterialTreeViewClick(const QModelIndex index)
{
    QString dateTime = index.data().toString();
    twoMaterialAndSpecifications = index.parent().data().toString();
    twoStartUseTimeEdit->setDateTime(QDateTime::fromString(dateTime,"yyyy-MM-dd hh:mm:ss"));

    //原材料
    QString searchMaterialListSQL = QString("select CONCAT(MaterialName,' ',Specifications),Price from PurchaseMaterialList where Supplier='%1' and DateTime='%2'")
            .arg(twoSupplierLineEdit->text(),twoStartUseTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
    QList<QStringList> MaterialList = db.sql_result(searchMaterialListSQL);
    int count2 = MaterialList.count();
    if(count2 != 0){
        for(int i = 0; i<material_count; i++){
            for(int j = 0; j<count2; j++){
                if(twoMaterialCheckBoxList[i]->text() == MaterialList.at(j).at(0)){
                    twoMaterialCheckBoxList[i]->setCheckState(Qt::Checked);
                    twoMaterialLineEditList[i]->setText(MaterialList.at(j).at(1));
                    break;
                }
                else{
                    twoMaterialCheckBoxList[i]->setCheckState(Qt::Unchecked);
                }
            }
        }
    }
    else{
        for(int i = 0; i<material_count; i++){
            twoMaterialCheckBoxList[i]->setCheckState(Qt::Unchecked);
        }
    }
}

void caigouhetongguanliDlg::on_threeQuanXuanBtn()
{
    QString searchSQL = "select Name 供应商名称, 2 是否修改 from SupplierFile";
    db.showview(searchSQL,threeSupplierListView,&threeSupplierListModel);

    int rowCount = threeSupplierListModel->rowCount();
    for(int i = 0; i<rowCount; i++){
       threeSupplierListModel->item(i,1)->setCheckState(Qt::Checked);
    }
}

void caigouhetongguanliDlg::on_threeQuXiaoBtn()
{
    QString searchSQL = "select Name 供应商名称, 0 是否修改 from SupplierFile";
    db.showview(searchSQL,threeSupplierListView,&threeSupplierListModel);

    int rowCount = threeSupplierListModel->rowCount();
    for(int i = 0; i<rowCount; i++){
       threeSupplierListModel->item(i,1)->setCheckState(Qt::Unchecked);
    }
}

void caigouhetongguanliDlg::on_threeUpdateBtn()
{
    QString SupplierStrList;
    int rowCount = threeSupplierListModel->rowCount();
    for(int i = 0; i<rowCount; i++){
       if(threeSupplierListModel->item(i,1)->checkState() == 2){
           SupplierStrList = SupplierStrList.append(QString("'%1',").arg(threeSupplierListModel->item(i,0)->text()));
       }
    }
    SupplierStrList = SupplierStrList.left(SupplierStrList.length()-1);

    QString updateSQL = QString("UPDATE PurchaseReceipt A LEFT JOIN PurchaseMaterialList B ON ( A.Supplier = B.Supplier AND A.Material = B.MaterialName\
                                 AND A.SpecificationModel = B.Specifications AND B.DateTime = (SELECT MAX(DateTime) FROM PurchaseMaterialList WHERE\
                                 Supplier = A.Supplier AND MaterialName = A.Material AND Specifications = A.SpecificationModel AND DateTime < A.GrossWeightTime)) \
                                 SET A.UnitPrice = B.Price WHERE A.Supplier IN (%1) AND GrossWeightTime BETWEEN '%2' AND '%3'")
                        .arg(SupplierStrList,threeDateTimeEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),threeDateTimeEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
    int res = db.sql_exec(updateSQL);
    if(res == 0){
        QString searchSQL = QString("select CONCAT(Supplier,' ',Material,' ',SpecificationModel,' ',MID(MIN(GrossWeightTime),1,10),'--',MID(MAX(GrossWeightTime),1,10)) from \
                                    PurchaseReceipt where Supplier IN (%1) and (UnitPrice IS NULL OR UnitPrice='') and GrossWeightTime BETWEEN '%2' AND '%3' GROUP BY \
                                    Supplier,Material,SpecificationModel")
                        .arg(SupplierStrList,threeDateTimeEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),threeDateTimeEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"));

        QStringList DetailInfoList = db.find_CheNo(searchSQL);
        qDebug()<<DetailInfoList;

        QString DetailInfo;
        for(int i = 0; i<DetailInfoList.count(); i++){
            if(!DetailInfoList.at(i).isEmpty()){
                DetailInfo = DetailInfo.append(DetailInfoList.at(i)).append("\n");
            }
        }
        if(!DetailInfo.isEmpty()){
            QMessageBox msgBox;
            msgBox.setText(QString("检测到有空的价格区间"));
            msgBox.setInformativeText(DetailInfo);
            msgBox.setStandardButtons(QMessageBox::Yes);
            msgBox.setDefaultButton(QMessageBox::Yes);
            int ret = msgBox.exec();
            switch (ret) {
              case QMessageBox::Yes:
                  break;
              default:
                  break;
            }
        }else{
            QMessageBox::information(this,tr("提示信息"),tr("修改成功"),0,0,0);
        }

        QString insertSQL = QString("insert into PurchaseReceiptPriceCorrectRecord (updateSupplier,receiptTime,Operator,OperatingTime) values ('%1','%2','%3','%4')")
                .arg(SupplierStrList.replace("'",""),QString("%1--%2").arg(threeDateTimeEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),threeDateTimeEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss")),
                     userName,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        db.sql_exec(insertSQL);
        on_threeFindBtn();
    }else{
        QMessageBox::information(this,tr("提示信息"),tr("请至少选择一个供应商"),0,0,0);
    }
}

void caigouhetongguanliDlg::on_threeFindBtn()
{
    QString searchSQL = QString("select updateSupplier 修改的供应商,receiptTime 修改的入库单日期,Operator 修改人,OperatingTime 修改时间 from PurchaseReceiptPriceCorrectRecord where OperatingTime \
                                between '%1' and '%2'")
                                .arg(threeUpdateDateTimeEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),threeUpdateDateTimeEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
    db.showview(searchSQL,threeUpdateDetailInfoView,&threeUpdateDetailInfoModel);
}

void caigouhetongguanliDlg::init_MaterialWidget()
{
    twoMaterialWidget = new QWidget(this);
    material_count = 0;

    const char *fillMaterialSQL = "select CONCAT(Material,' ',SpecificationModel),0 from MaterialSetting order by Type;";
    db.newCheckBoxAndLineEdit(fillMaterialSQL,twoMaterialCheckBoxList,twoMaterialLineEditList,&material_count,this);

    QGridLayout *twoMaterialLayout = new QGridLayout(this);
    twoMaterialLayout->setColumnStretch(0,0);
    twoMaterialLayout->setColumnStretch(1,1);
    twoMaterialLayout->setColumnStretch(2,0);
    twoMaterialLayout->setColumnStretch(3,1);
    twoMaterialLayout->setColumnStretch(4,0);
    twoMaterialLayout->setColumnStretch(5,1);
    twoMaterialLayout->setColumnStretch(6,0);
    twoMaterialLayout->setColumnStretch(7,1);

    twoMaterialLayout->setRowStretch(0,1);
    twoMaterialLayout->setRowStretch(1,1);
    twoMaterialLayout->setRowStretch(2,1);
    twoMaterialLayout->setRowStretch(3,1);
    twoMaterialLayout->setRowStretch(4,1);
    twoMaterialLayout->setRowStretch(5,1);
    twoMaterialLayout->setRowStretch(6,1);
    twoMaterialLayout->setRowStretch(7,1);
    twoMaterialLayout->setRowStretch(8,1);
    twoMaterialLayout->setRowStretch(9,1);
    twoMaterialLayout->setRowStretch(10,1);
    twoMaterialLayout->setRowStretch(11,1);
    int j = 0;
    for(int i = 0; i < material_count; i++){
        twoMaterialLayout->addWidget(twoMaterialCheckBoxList[i],j / 8,j % 8);
        twoMaterialLayout->addWidget(twoMaterialLineEditList[i],j / 8,j % 8 + 1,Qt::AlignLeft);
        j+=2;
    }
    twoMaterialWidget->setLayout(twoMaterialLayout);
}


void caigouhetongguanliDlg::createAction()
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
}

void caigouhetongguanliDlg::createTool()
{
    toolBar = new QToolBar(this);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar->addAction(newAction);
    toolBar->addAction(saveAction);
    toolBar->addAction(updateAction);
    toolBar->addAction(deleteAction);
}
