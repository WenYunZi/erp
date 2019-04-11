#include "fucaigongyingshangdangandlg.h"

extern mymysql db;
extern myTCPsocket *sockClient;

fucaigongyingshangdanganDlg::fucaigongyingshangdanganDlg(QWidget *parent) :
    QDialog(parent)
{
    SQL = "select Number 编号,SupplierName 供应商名称,ContactPersonnel 联系人员,ContactNumber 联系电话,Fax 传真,Address 地址,\
            Payee 收款人,AccountNumber 账号,BankAccount 开户行,ServiceTelephone 售后服务电话,FactoryPhone 厂家电话,\
            CommodityCategory  商品类别,Remarks 备注,LegalRepresentative 法人代表,BusinessLicense 营业执照,\
            OrganizationCode 组织机构代码 from AuxiliaryMaterialSupplier;";

    createAction();
    createTool();

    QLabel *label1 = new QLabel(tr("供应商编号"),this);
    label1->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label2 = new QLabel(tr("供应商名称"),this);
    label2->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label3 = new QLabel(tr("联系人"),this);
    label3->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label4 = new QLabel(tr("联系电话"),this);
    label4->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label5 = new QLabel(tr("传真"),this);
    label5->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label6 = new QLabel(tr("收款人"),this);
    label6->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label7 = new QLabel(tr("收款账号"),this);
    label7->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label8 = new QLabel(tr("开户行"),this);
    label8->setAlignment(Qt::AlignRight);
    QLabel *label9 = new QLabel(tr("售后服务"),this);
    label9->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label10 = new QLabel(tr("商品类别"),this);
    label10->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label11 = new QLabel(tr("组织机构代码"),this);
    label11->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label12 = new QLabel(tr("备注"),this);
    label12->setAlignment(Qt::AlignRight);
    QLabel *label13 = new QLabel(tr("厂家电话"),this);
    label13->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label14 = new QLabel(tr("法人代表"),this);
    label14->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label15 = new QLabel(tr("营业执照"),this);
    label15->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label16 = new QLabel(tr("地址"),this);
    label16->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    lineEdit1 = new QLineEdit(this);
    lineEdit1->setStyleSheet("color:black");
    lineEdit2 = new QLineEdit(this);
    lineEdit3 = new QLineEdit(this);
    lineEdit4 = new QLineEdit(this);
    lineEdit5 = new QLineEdit(this);
    lineEdit6 = new QLineEdit(this);
    lineEdit7 = new QLineEdit(this);
    lineEdit8 = new QLineEdit(this);
    lineEdit9 = new QLineEdit(this);
    lineEdit10 = new QLineEdit(this);
    lineEdit11 = new QLineEdit(this);
    lineEdit12 = new QLineEdit(this);
    lineEdit13 = new QLineEdit(this);
    lineEdit14 = new QLineEdit(this);
    lineEdit15 = new QLineEdit(this);
    combox = new QComboBox(this);
    combox->setEditable(true);
    const char *fillSQL = "SELECT Class from AuxiliaryCategory;";
    db.sql_fillComboBoxItem(fillSQL,combox);

    view = new QTableView(this);
    connect(view,SIGNAL(clicked(QModelIndex)),this,SLOT(ShowSupplyclick()));
    db.showview(SQL,view,&model);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label1,0,0);
    layout->addWidget(lineEdit1,0,1);
    layout->addWidget(label2,0,2);
    layout->addWidget(lineEdit2,0,3);
    layout->addWidget(label3,0,4);
    layout->addWidget(lineEdit3,0,5);
    layout->addWidget(label4,0,6);
    layout->addWidget(lineEdit4,0,7);
    layout->addWidget(label5,0,8);
    layout->addWidget(lineEdit5,0,9);
    layout->addWidget(label6,1,0);
    layout->addWidget(lineEdit6,1,1);
    layout->addWidget(label7,1,2);
    layout->addWidget(lineEdit7,1,3);
    layout->addWidget(label8,1,4);
    layout->addWidget(lineEdit8,1,5,1,3);
    layout->addWidget(label9,1,8);
    layout->addWidget(lineEdit9,1,9);
    layout->addWidget(label10,2,0);
    layout->addWidget(combox,2,1);
    layout->addWidget(label11,2,2);
    layout->addWidget(lineEdit10,2,3);
    layout->addWidget(label12,2,4);
    layout->addWidget(lineEdit11,2,5,1,3);
    layout->addWidget(label13,2,8);
    layout->addWidget(lineEdit12,2,9);
    layout->addWidget(label14,3,0);
    layout->addWidget(lineEdit13,3,1);
    layout->addWidget(label15,3,2);
    layout->addWidget(lineEdit14,3,3);
    layout->addWidget(label16,3,4);
    layout->addWidget(lineEdit15,3,5,1,3);
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

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(toolBar);
    vlayout->addLayout(layout);
    vlayout->addWidget(view);
}

void fucaigongyingshangdanganDlg::refresh()
{
    db.showview(SQL,view,&model);
}

void fucaigongyingshangdanganDlg::keyPressEvent(QKeyEvent *event)
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

void fucaigongyingshangdanganDlg::on_newAction()
{
    lineEdit1->setEnabled(true);
    saveAction->setEnabled(true);
    updateAction->setEnabled(false);
    deleteAction->setEnabled(false);

    lineEdit1->clear();
    lineEdit2->clear();
    lineEdit3->clear();
    lineEdit4->clear();
    lineEdit5->clear();
    lineEdit6->clear();
    lineEdit7->clear();
    lineEdit8->clear();
    lineEdit9->clear();
    lineEdit10->clear();
    lineEdit11->clear();
    lineEdit12->clear();
    lineEdit13->clear();
    lineEdit14->clear();
    lineEdit15->clear();
    combox->setCurrentIndex(0);
}

void fucaigongyingshangdanganDlg::on_saveAction()
{
    if(lineEdit1->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入供应商编号"),0,0,0);
        return;
    }
    if(lineEdit2->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入供应商名称"),0,0,0);
        return;
    }
    if(lineEdit3->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入联系人"),0,0,0);
        return;
    }
    if(lineEdit4->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入联系电话"),0,0,0);
        return;
    }
    if(combox->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择商品类别"),0,0,0);
        return;
    }
    QString saveSQL = QString("insert into AuxiliaryMaterialSupplier (Number,SupplierName,ContactPersonnel,ContactNumber,Fax,\
                              Address,Payee,AccountNumber,BankAccount,ServiceTelephone,FactoryPhone,CommodityCategory,Remarks,LegalRepresentative,\
                              BusinessLicense,OrganizationCode) values ('%1','%2','%3','%4','%5','%6','%7','%8','%9','%10','%11','%12','%13','%14','%15','%16');")
                    .arg(lineEdit1->text(),lineEdit2->text(),lineEdit3->text(),lineEdit4->text(),lineEdit5->text(),
                         lineEdit15->text(),lineEdit6->text(),lineEdit7->text(),lineEdit8->text())
                    .arg(lineEdit9->text(),lineEdit12->text(),combox->currentText(),lineEdit11->text(),
                         lineEdit13->text(),lineEdit14->text(),lineEdit10->text());
    int res = db.sql_exec(saveSQL.toStdString().data());
    if(res == -1){
        if((strstr(db.geterror(),"PRIMARY")) != NULL){
            QMessageBox::information(this,tr("错误"),tr("请检查供应商编号是否重复"),0,0,0);
            return;
        }
    }
    else if(res == 0){
        sockClient->send_Msg3();
        on_newAction();
        QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
    }
}

void fucaigongyingshangdanganDlg::on_updateAction()
{
    if(lineEdit1->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入供应商编号"),0,0,0);
        return;
    }
    if(lineEdit2->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入供应商名称"),0,0,0);
        return;
    }
    if(lineEdit3->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入联系人"),0,0,0);
        return;
    }
    if(lineEdit4->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入联系电话"),0,0,0);
        return;
    }
    if(combox->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择商品类别"),0,0,0);
        return;
    }
    QString updateSQL = QString("update AuxiliaryMaterialSupplier set SupplierName ='%1',ContactPersonnel ='%2',ContactNumber ='%3',\
                              Fax ='%4',Address ='%5',Payee ='%6',AccountNumber ='%7',BankAccount ='%8',ServiceTelephone ='%9',FactoryPhone ='%10',\
                              CommodityCategory ='%11',Remarks ='%12',LegalRepresentative ='%13',BusinessLicense ='%14',OrganizationCode='%15' where Number ='%16';")
                    .arg(lineEdit2->text(),lineEdit3->text(),lineEdit4->text(),lineEdit5->text(),
                         lineEdit15->text(),lineEdit6->text(),lineEdit7->text(),lineEdit8->text())
                    .arg(lineEdit9->text(),lineEdit12->text(),combox->currentText(),lineEdit11->text(),
                         lineEdit13->text(),lineEdit14->text(),lineEdit10->text(),lineEdit1->text());
    int res = db.sql_exec(updateSQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();
        on_newAction();
        QMessageBox::information(this,tr("提示信息"),tr("修改成功"),0,0,0);
    }
}

void fucaigongyingshangdanganDlg::on_deleteAction()
{
    QString deleteSQL = QString("delete from AuxiliaryMaterialSupplier where Number ='%1';").arg(lineEdit1->text());
    int res = db.sql_exec(deleteSQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();
        on_newAction();
        QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
    }
}

void fucaigongyingshangdanganDlg::ShowSupplyclick()
{
    updateAction->setEnabled(true);
    deleteAction->setEnabled(true);
    saveAction->setEnabled(false);
    lineEdit1->setEnabled(false);

    int row = view->currentIndex().row();
    lineEdit1->setText(model->item(row,0)->text());
    lineEdit2->setText(model->item(row,1)->text());
    lineEdit3->setText(model->item(row,2)->text());
    lineEdit4->setText(model->item(row,3)->text());
    lineEdit5->setText(model->item(row,4)->text());
    lineEdit6->setText(model->item(row,6)->text());
    lineEdit7->setText(model->item(row,7)->text());
    lineEdit8->setText(model->item(row,8)->text());
    lineEdit9->setText(model->item(row,9)->text());
    lineEdit10->setText(model->item(row,15)->text());
    lineEdit11->setText(model->item(row,12)->text());
    lineEdit12->setText(model->item(row,10)->text());
    lineEdit13->setText(model->item(row,13)->text());
    lineEdit14->setText(model->item(row,14)->text());
    lineEdit15->setText(model->item(row,5)->text());
    combox->setCurrentText(model->item(row,11)->text());
}

void fucaigongyingshangdanganDlg::createAction()
{
    newAction = new QAction(tr("新增"),this);
    newAction->setIcon(QIcon(":/image/new.png"));
    connect(newAction,SIGNAL(triggered()),this,SLOT(on_newAction()));
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

void fucaigongyingshangdanganDlg::createTool()
{
    toolBar = new QToolBar(this);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar->addAction(newAction);
    toolBar->addAction(saveAction);
    toolBar->addAction(updateAction);
    toolBar->addAction(deleteAction);
}
