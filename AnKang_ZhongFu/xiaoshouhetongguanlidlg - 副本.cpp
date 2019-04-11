#include "xiaoshouhetongguanlidlg.h"

extern mymysql db;
extern pubfunc pub;
extern QString userName;
extern myTCPsocket *sockClient;

xiaoshouhetongguanliDlg::xiaoshouhetongguanliDlg(QWidget *parent) :
    QDialog(parent)
{
    tabWidget = new QTabWidget(this);
    xiaoshouhetongguanli = new QWidget(this);
    xiaoshouhetongchaxun = new QWidget(this);

    creatTabPage1();
    creatTabPage2();
    createAction();
    createTool();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(toolBar);
    layout->addWidget(tabWidget);
    layout->setSpacing(0);
}

void xiaoshouhetongguanliDlg::refresh()
{
    on_twochaxunBtn();
}

void xiaoshouhetongguanliDlg::init_shuxingWidget()
{
    shuxingWidget = new QWidget(this);
    shuxing_count = 0;

    const char *SQL = "select AttributeName,Price from ProductAttributes;";
    db.newCheckBoxAndLineEdit(SQL,checkBoxlist,lineEditlist,&shuxing_count,this);

    onelayout = new QGridLayout(this);
    onelayout->setColumnStretch(0,0);
    onelayout->setColumnStretch(1,1);
    onelayout->setColumnStretch(2,0);
    onelayout->setColumnStretch(3,1);
    onelayout->setColumnStretch(4,0);
    onelayout->setColumnStretch(5,1);
    onelayout->setColumnStretch(6,0);
    onelayout->setColumnStretch(7,1);
    onelayout->setColumnStretch(8,0);
    onelayout->setColumnStretch(9,1);
    onelayout->setRowStretch(0,1);
    onelayout->setRowStretch(1,1);
    onelayout->setRowStretch(2,1);
    onelayout->setRowStretch(3,1);
    onelayout->setRowStretch(4,1);
    onelayout->setRowStretch(5,1);
    onelayout->setRowStretch(6,1);
    onelayout->setRowStretch(7,1);
    onelayout->setRowStretch(8,1);
    onelayout->setRowStretch(9,1);
    onelayout->setRowStretch(10,1);
    onelayout->setRowStretch(11,1);

    int j = 0;
    for(int i = 0; i < shuxing_count; i++){
        onelayout->addWidget(checkBoxlist[i],j / 10,j % 10);
        onelayout->addWidget(lineEditlist[i],j / 10,j % 10 + 1,Qt::AlignLeft);
        j+=2;
    }
    shuxingWidget->setLayout(onelayout);
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
    QLabel *label1 = new QLabel(tr("合同编号"),this);
    label1->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label2 = new QLabel(tr("客户名称"),this);
    label2->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label3 = new QLabel(tr("结算方量"),this);
    label3->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label4 = new QLabel(tr("签订日期"),this);
    label4->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label5 = new QLabel(tr("备注"),this);
    label5->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label6 = new QLabel(tr("合同类型"),this);
    label6->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label7 = new QLabel(tr("结算方式"),this);
    label7->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label9 = new QLabel(tr("销售合同产品信息列表"),this);
    label9->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    QLabel *label10 = new QLabel(tr("请选择销售产品所需要的属性，并在选择符合后输入每方加价信息"),this);
    label10->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);

    lineEdit1 = new QLineEdit(this);
    lineEdit1->setReadOnly(true);
    lineEdit2 = new QLineEdit(this);
    lineEdit3 = new QLineEdit(this);
    textEdit = new QTextEdit(this);
    textEdit->setFixedHeight(40);
    comBox1 = new QComboBox;
    const char *fillSQL1 = "select CustomerName from CustomerFiles;";
    db.sql_fillComboBoxItem(fillSQL1,comBox1);
    comBox2 = new QComboBox;
    comBox2->setView(new QListView());
    comBox2->addItem(tr("混凝土合同"));
    comBox2->addItem(tr("砂浆合同"));
    dateEdit = new QDateEdit(QDate::currentDate());
    dateEdit->setCalendarPopup(true);

    //设置表头1
    QStringList header1;
    header1.append(QObject::tr("产品名称"));
    header1.append(QObject::tr("产品单价（元）"));
    view1 = new QTableWidget;
    view1->setItemDelegate(new xiaoshouhetongDelegate1(0));
    view1->setFixedWidth(300);
    view1->setColumnCount(2);
    view1->setRowCount(0);
    view1->setHorizontalHeaderLabels(header1);
    //设置view1的右键菜单
    zengjiaAction1 = new QAction(tr("增加"),this);
    zengjiaAction1->setIcon(QIcon(":/image/zengjia.png"));
    shanchuAction1 = new QAction(tr("删除"),this);
    shanchuAction1->setIcon(QIcon(":/image/shanchu.png"));
    connect(zengjiaAction1,SIGNAL(triggered()),this,SLOT(Increasing1()));
    connect(shanchuAction1,SIGNAL(triggered()),this,SLOT(Decreasing1()));
    view1->addAction(zengjiaAction1);
    view1->addAction(shanchuAction1);
    view1->setContextMenuPolicy(Qt::ActionsContextMenu);

    quxiaoBtn = new QPushButton(tr("取消"));
    quxiaoBtn->setFixedWidth(70);
    connect(quxiaoBtn,SIGNAL(clicked()),this,SLOT(on_quxiaoBtn()));
    quanxuanBtn = new QPushButton(tr("全选"));
    quanxuanBtn->setFixedWidth(70);
    connect(quanxuanBtn,SIGNAL(clicked()),this,SLOT(on_quanxuanBtn()));

    init_shuxingWidget();

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label1,0,0);
    layout->addWidget(lineEdit1,0,1);
    layout->addWidget(label2,0,2);
    layout->addWidget(comBox1,0,3);
    layout->addWidget(label3,0,4);
    layout->addWidget(lineEdit2,0,5);
    layout->addWidget(label4,1,0);
    layout->addWidget(dateEdit,1,1);
    layout->addWidget(label5,1,2);
    layout->addWidget(lineEdit3,1,3);
    layout->addWidget(label6,1,4);
    layout->addWidget(comBox2,1,5);
    layout->addWidget(label7,2,0);
    layout->addWidget(textEdit,2,1,1,5);
    layout->setColumnStretch(0,0);
    layout->setColumnStretch(1,1);
    layout->setColumnStretch(2,0);
    layout->setColumnStretch(3,2);
    layout->setColumnStretch(4,0);
    layout->setColumnStretch(5,1);

    QVBoxLayout *vlayout1 = new QVBoxLayout;
    vlayout1->addWidget(label9,0);
    vlayout1->addWidget(view1,2);

    QVBoxLayout *vlayout2 = new QVBoxLayout;
    QHBoxLayout *h_vlayout2 = new QHBoxLayout;
    h_vlayout2->addWidget(label10);
    h_vlayout2->addWidget(quxiaoBtn);
    h_vlayout2->addWidget(quanxuanBtn);
    h_vlayout2->addStretch(1);
    vlayout2->addLayout(h_vlayout2);
    vlayout2->addWidget(shuxingWidget);

    QHBoxLayout *hlayout1 = new QHBoxLayout;
    hlayout1->addLayout(vlayout1);
    hlayout1->addLayout(vlayout2);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addLayout(layout);
    vlayout->addLayout(hlayout1,1);

    xiaoshouhetongguanli->setLayout(vlayout);
    tabWidget->addTab(xiaoshouhetongguanli,tr("销售合同管理"));
}

void xiaoshouhetongguanliDlg::creatTabPage2()
{
    SQL2 = "select ContractNumber 合同编号,CustomerName 客户名称,SettlementAmount 结算方量,DateSigned 签订日期,\
            typeOfContract 合同类型,Remarks 备注,SettlementMethod 结算方式,ProductName 产品名称,ProductPrice 产品单价,\
            AttributeName 属性名称,AttributePrice 属性单价,\
            WhetherAudit 是否审核,WhetherEffective 是否有效,InputMan 录入人 from SalesContractManagement;";

    QLabel *label1 = new QLabel(tr("--"));
    label1->setAlignment(Qt::AlignCenter);

    twocheckBox1 = new QCheckBox(tr("客户名称"));
    twocheckBox2 = new QCheckBox(tr("签订时间"));
    twocomBox1 = new QComboBox;
    const char *fillSQL1 = "select CustomerName from CustomerFiles;";
    db.sql_fillComboBoxItem(fillSQL1,twocomBox1);
    twocomBox2 = new QComboBox;
    twocomBox2->setView(new QListView());
    twocomBox2->addItem(tr("有效"));
    twocomBox2->addItem(tr("未审核"));
    twocomBox2->addItem(tr("已审核无效"));
    twocomBox2->setCurrentIndex(1);
    twodateEdit1 = new QDateEdit(QDate::currentDate());
    twodateEdit1->setCalendarPopup(true);
    twodateEdit2 = new QDateEdit(QDate::currentDate());
    twodateEdit2->setCalendarPopup(true);
    twochaxunBtn = new QPushButton(tr("查询"));
    connect(twochaxunBtn,SIGNAL(clicked()),this,SLOT(on_twochaxunBtn()));
    twoview = new QTableView;
    db.showview(SQL2,twoview,&twomodel);
    connect(twoview,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick2()));
    twoview->setColumnWidth(1,300);
    twoview->setColumnWidth(6,200);
    twoview->setColumnHidden(7,true);
    twoview->setColumnHidden(8,true);
    twoview->setColumnHidden(9,true);
    twoview->setColumnHidden(10,true);
    twoview->setColumnHidden(11,true);
    twoview->setColumnHidden(12,true);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(twocheckBox1);
    hlayout->addWidget(twocomBox1,2);
    hlayout->addWidget(twocheckBox2);
    hlayout->addWidget(twodateEdit1,1);
    hlayout->addWidget(label1);
    hlayout->addWidget(twodateEdit2,1);
    hlayout->addWidget(twocomBox2,1);
    hlayout->addWidget(twochaxunBtn,1);
    hlayout->addStretch(1);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addLayout(hlayout);
    vlayout->addWidget(twoview);

    xiaoshouhetongchaxun->setLayout(vlayout);
    tabWidget->addTab(xiaoshouhetongchaxun,tr("销售合同查询"));
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
}

void xiaoshouhetongguanliDlg::createTool()
{
    toolBar = new QToolBar;
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar->addAction(newAction);
    toolBar->addAction(saveAction);
    toolBar->addAction(updateAction);
    toolBar->addAction(deleteAction);
}

void xiaoshouhetongguanliDlg::on_newAction()
{
    saveAction->setEnabled(true);
    updateAction->setEnabled(false);
    deleteAction->setEnabled(false);
    lineEdit1->clear();
    lineEdit2->clear();
    lineEdit3->clear();
    comBox1->setCurrentIndex(0);
    comBox2->setCurrentIndex(0);
    dateEdit->setDate(QDate::currentDate());
    textEdit->clear();
    view1->setRowCount(0);

    //刷新属性
    const char *SQL = "select AttributeName,Price from ProductAttributes;";
    db.newCheckBoxAndLineEdit(SQL,checkBoxlist,lineEditlist,&shuxing_count,this);
    int j = 0;
    for(int i = 0; i < shuxing_count; i++){
        onelayout->addWidget(checkBoxlist[i],j / 10,j % 10);
        onelayout->addWidget(lineEditlist[i],j / 10,j % 10 + 1,Qt::AlignLeft);
        j+=2;
    }
}

void xiaoshouhetongguanliDlg::on_newAction_plus()
{
    saveAction->setEnabled(true);
    updateAction->setEnabled(false);
    deleteAction->setEnabled(false);
    lineEdit1->setText(pub.newSalesContractNo());
    lineEdit2->clear();
    lineEdit3->clear();
    comBox1->setCurrentIndex(0);
    comBox2->setCurrentIndex(0);
    dateEdit->setDate(QDate::currentDate());
    view1->setRowCount(0);
    textEdit->clear();

    //刷新属性
    const char *SQL = "select AttributeName,Price from ProductAttributes;";
    db.newCheckBoxAndLineEdit(SQL,checkBoxlist,lineEditlist,&shuxing_count,this);
    int j = 0;
    for(int i = 0; i < shuxing_count; i++){
        onelayout->addWidget(checkBoxlist[i],j / 10,j % 10);
        onelayout->addWidget(lineEditlist[i],j / 10,j % 10 + 1,Qt::AlignLeft);
        j+=2;
    }
}

void xiaoshouhetongguanliDlg::on_saveAction()
{
    QString ProductName,ProductPrice;
    QString AttributeName,AttributePrice;

    QString searchKehu = QString("select CustomerName from SalesContractManagement where CustomerName='%1' and WhetherEffective='有效' union \
                                 select CustomerName from CashContractManagement where CustomerName='%1' and WhetherEffective='有效'")
            .arg(comBox1->currentText());
    if(db.row_count(searchKehu) != 0){
        QMessageBox::information(this,tr("提示信息"),tr("该客户已存在合同"),0,0,0);
        return;
    }

    int rowcount1 = view1->rowCount();
    if(rowcount1 == 0){
        QMessageBox::information(this,tr("提示信息"),tr("请添加销售产品"),0,0,0);
        return;
    }
    for(int i = 0; i < rowcount1; i++){
        /*产品名称****************************************************************************************/
        if(!view1->item(i,0) || view1->item(i,0)->text().isEmpty()){
            QMessageBox::information(this,tr("提示信息"),tr("请检查产品名称是否有空行"),0,0,0);
            return;
        }else{
            ProductName.append(view1->item(i,0)->text() + " ");
        }
        /*产品单价****************************************************************************************/
        if(!view1->item(i,1) || view1->item(i,1)->text().isEmpty()){
            QMessageBox::information(this,tr("提示信息"),tr("请检查产品单价是否有空行"),0,0,0);
            return;
        }else{
            ProductPrice.append(view1->item(i,1)->text() + " ");
        }
    }

    //属性名称价格
    for(int i = 0; i<shuxing_count; i++){
        if(checkBoxlist[i]->checkState() == 2){
            AttributeName.append(checkBoxlist[i]->text() + " ");
            AttributePrice.append(lineEditlist[i]->text() + " ");
        }
    }

    QString saveSQL = QString("insert into SalesContractManagement (ContractNumber,CustomerName,SettlementAmount,\
                              DateSigned,typeOfContract,Remarks,SettlementMethod,ProductName,ProductPrice,\
                              AttributeName,AttributePrice,WhetherAudit,WhetherEffective,InputMan) values ('%1',\
                              '%2','%3','%4','%5','%6','%7','%8','%9','%10','%11','%12','%13','%14');")
    .arg(lineEdit1->text(),comBox1->currentText(),lineEdit2->text(),dateEdit->date().toString("yyyy-MM-dd"),
         comBox2->currentText(),lineEdit3->text(),textEdit->toPlainText(),ProductName)
    .arg(ProductPrice,AttributeName,AttributePrice,"否","无效",userName);
    int res = db.sql_exec(saveSQL.toStdString().data());
    if(res == -1){
        if(strstr(db.geterror(),"PRIMARY") != NULL){
            QMessageBox::information(this, tr("失败"),tr("请检查合同编号是否重复"),0,0,0);
        }
        return;
    }else if(res == 0){
        sockClient->send_Msg3();
        on_newAction();
        lineEdit1->clear();
        QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
    }
}

void xiaoshouhetongguanliDlg::on_updateAction()
{
    QString searchSQL = QString("select * from SalesContractCheckInfo where ContractNo='%1'").arg(lineEdit1->text());
    if(db.row_count(searchSQL) != 0){
        QMessageBox::information(this,tr("提示信息"),tr("已审核的合同不能修改，请到合同变更中进行合同变更"),0,0,0);
        return;
    }

    QString ProductName,ProductPrice,Contacts,ContactNumber,ConstructionSite,product,Factory,Distance;
    QString AttributeName,AttributePrice;
    int rowcount1 = view1->rowCount();
    if(rowcount1 == 0){
        QMessageBox::information(this,tr("提示信息"),tr("请添加销售产品"),0,0,0);
        return;
    }
    for(int i = 0; i < rowcount1; i++){
        /*产品名称****************************************************************************************/
        if(!view1->item(i,0) || view1->item(i,0)->text().isEmpty()){
            QMessageBox::information(this,tr("提示信息"),tr("请检查产品名称是否有空行"),0,0,0);
            return;
        }else{
            ProductName.append(view1->item(i,0)->text() + " ");
        }
        /*产品单价****************************************************************************************/
        if(!view1->item(i,1) || view1->item(i,1)->text().isEmpty()){
            QMessageBox::information(this,tr("提示信息"),tr("请检查产品单价是否有空行"),0,0,0);
            return;
        }else{
            ProductPrice.append(view1->item(i,1)->text() + " ");
        }
    }

    //属性名称价格
    for(int i = 0; i<shuxing_count; i++){
        if(checkBoxlist[i]->checkState() == 2){
            AttributeName.append(checkBoxlist[i]->text() + " ");
            AttributePrice.append(lineEditlist[i]->text() + " ");
        }
    }
    QString updateSQL = QString("update SalesContractManagement set SettlementAmount='%1',DateSigned='%2',\
                                Remarks='%3',SettlementMethod='%4',ProductName='%5',ProductPrice='%6',\
                                AttributeName='%7',AttributePrice='%8',WhetherAudit='%9',\
                                WhetherEffective='%10',InputMan='%11',CustomerName='%12' where ContractNumber='%13';")
               .arg(lineEdit2->text(),dateEdit->date().toString("yyyy-MM-dd"),lineEdit3->text(),
                    textEdit->toPlainText(),ProductName,ProductPrice,AttributeName,AttributePrice)
               .arg("否","无效",userName,comBox1->currentText(),lineEdit1->text());
    int res = db.sql_exec(updateSQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();
        on_newAction();
        lineEdit1->clear();
        QMessageBox::information(this,tr("提示信息"),tr("修改成功"),0,0,0);
    }
}

void xiaoshouhetongguanliDlg::on_deleteAction()
{
    QString searchSQL = QString("select * from SalesContractCheckInfo where ContractNo='%1'").arg(lineEdit1->text());
    if(db.row_count(searchSQL) != 0){
        QMessageBox::information(this,tr("提示信息"),tr("已审核的合同不能删除"),0,0,0);
        return;
    }

    QString deleteSQL = QString("delete from SalesContractManagement where ContractNumber='%1';").arg(lineEdit1->text());
    int res = db.sql_exec(deleteSQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();
        on_newAction();
        lineEdit1->clear();
        QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
    }
}

void xiaoshouhetongguanliDlg::ShowSupplyclick2()
{
    saveAction->setEnabled(false);
    updateAction->setEnabled(true);
    deleteAction->setEnabled(true);
    int row = twoview->currentIndex().row();

    lineEdit1->setText(twomodel->item(row,0)->text());
    lineEdit2->setText(twomodel->item(row,2)->text());
    lineEdit3->setText(twomodel->item(row,5)->text());
    comBox1->setCurrentText(twomodel->item(row,1)->text());
    comBox2->setCurrentText(twomodel->item(row,4)->text());
    dateEdit->setDate(QDate::fromString(twomodel->item(row,3)->text(),"yyyy-MM-dd"));
    textEdit->setText(twomodel->item(row,6)->text());

    int count1 = twomodel->item(row,7)->text().count(" ");//产品名称
    view1->setRowCount(count1);
    for(int i = 0; i < count1; i++){
        view1->setItem(i,0,new QTableWidgetItem(twomodel->item(row,7)->text().section(" ",i,i)));
        view1->setItem(i,1,new QTableWidgetItem(twomodel->item(row,8)->text().section(" ",i,i)));
    }

    int count2 = twomodel->item(row,9)->text().count(" ");//属性
    if(count2 != 0){
        for(int i = 0; i<shuxing_count; i++){
            for(int j = 0; j<count2; j++){
                if(checkBoxlist[i]->text() == twomodel->item(row,9)->text().section(" ",j,j)){
                    checkBoxlist[i]->setCheckState(Qt::Checked);
                    lineEditlist[i]->setText(twomodel->item(row,10)->text().section(" ",j,j));
                    break;
                }
                else{
                    checkBoxlist[i]->setCheckState(Qt::Unchecked);
                    lineEditlist[i]->clear();
                }
            }
        }
    }
    else{
        for(int i = 0; i<shuxing_count; i++){
            checkBoxlist[i]->setCheckState(Qt::Unchecked);
            lineEditlist[i]->clear();
        }
    }

    tabWidget->setCurrentIndex(0);
}

void xiaoshouhetongguanliDlg::Increasing1()
{
    int row = view1->rowCount(); //获取表格行数
    view1->setRowCount(++row);//表格加一行
}

void xiaoshouhetongguanliDlg::Decreasing1()
{
    int row = view1->rowCount();
    if(row == 0){
        return;
    }
    row = view1->currentRow();
    this->view1->removeRow(row);
}

void xiaoshouhetongguanliDlg::on_quxiaoBtn()
{
    for(int i = 0; i<shuxing_count; i++){
        checkBoxlist[i]->setCheckState(Qt::Unchecked);
    }
}

void xiaoshouhetongguanliDlg::on_quanxuanBtn()
{
    for(int i = 0; i<shuxing_count; i++){
        checkBoxlist[i]->setCheckState(Qt::Checked);
    }
}

void xiaoshouhetongguanliDlg::on_twochaxunBtn()
{
    QString ContractStatus,kehumingcheng,qiandingshijian;

    switch(twocomBox2->currentIndex()){
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

    if(twocheckBox1->checkState() == 2){
        kehumingcheng = QString(" and CustomerName='%1'").arg(twocomBox1->currentText());
    }
    if(twocheckBox2->checkState() == 2){
        qiandingshijian = QString(" and DateSigned between '%1' and '%2'").arg(twodateEdit1->date().toString("yyyy-MM-dd"),twodateEdit2->date().toString("yyyy-MM-dd"));
    }

    QString searchSQL = QString("select ContractNumber 合同编号,CustomerName 客户名称,SettlementAmount 结算方量,DateSigned 签订日期,\
                                typeOfContract 合同类型,Remarks 备注,SettlementMethod 结算方式,ProductName 产品名称,ProductPrice 产品单价,\
                                AttributeName 属性名称,AttributePrice 属性单价,\
                                WhetherAudit 是否审核,WhetherEffective 是否有效,InputMan 录入人 from SalesContractManagement %1%2%3;")
            .arg(ContractStatus,kehumingcheng,qiandingshijian);
    db.showview(searchSQL.toStdString().data(),twoview,&twomodel);
}

