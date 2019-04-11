#include "shengchanrenwudandlg.h"

extern mymysql db;
extern pubfunc pub;
extern QString userName;
extern QString whetherCheckSend;
extern myTCPsocket *sockClient;
extern mainTitle   *titleBar;

shengchanrenwudanDlg::shengchanrenwudanDlg(QWidget *parent) :
    QDialog(parent)
{
    tabWidget = new QTabWidget(this);
    shengchanrenwudanxinxi = new QWidget(this);
    shenheweixiafadeshengchanrenwudan = new QWidget(this);
    shengchanrenwudanchaxun = new QWidget(this);
    dlg = new shuxingtoolbarDlg(this);

    creatTabPage1();
    creatTabPage3();
    creatTabPage4();

    createAction();
    createTool();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(toolBar);
    layout->addWidget(tabWidget);
    layout->setSpacing(0);
}

shengchanrenwudanDlg::~shengchanrenwudanDlg()
{
    delete model;
    delete threemodel;
    delete fourmodel;
    delete dlg;
}

void shengchanrenwudanDlg::refresh()
{
    db.showview(SQL1.toStdString().data(),TaskListView,&model);
    setModelStyle(model);
    db.showview(SQL3,threeview,&threemodel);
    on_fourFindBtn();
}

void shengchanrenwudanDlg::keyPressEvent(QKeyEvent *event)
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

void shengchanrenwudanDlg::creatTabPage1()
{
    SQL1 = QString("select TaskNumber 任务单号,Customer 实际客户,FaHuoCustomer 发货客户,Engineering 工程名称,StrengthGrade 强度等级,PouringPosition 浇筑部位,PouringMethod 浇筑方法,HasBeenUnderTask 已下任务量,\
                   PlannedQuantity 计划方量,ContractCompletion 完成方量,Product 产品名称,Slump 坍落度,Contacts 联系人,ContactNumber 联系电话,SupplyTime 供货时间,Remarks 备注,\
                   ContractNumber 合同编号,WhetherInvalid 是否作废,ConstructionSite 工程地址 from ProductionTaskList where TaskNumber between '%1' and '%2' and WhetherCheck='是' and WhetherSend='是'")
            .arg(QDate::currentDate().addDays(-1).toString("yyyyMMdd000"),QDate::currentDate().toString("yyyyMMdd999"));

    QLabel *TaskNoLabel = new QLabel(tr("任务单"),this);
    TaskNoLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *StrengthGradeLabel = new QLabel(tr("强度等级"),this);
    StrengthGradeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *ContactsLabel = new QLabel(tr("联系人"),this);
    ContactsLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *PlannedQuantityLabel = new QLabel(tr("计划方量"),this);
    PlannedQuantityLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *RealCustomerLabel = new QLabel(tr("实际客户"),this);
    RealCustomerLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *FaHuoCustomerLabel = new QLabel(tr("发货客户"),this);
    FaHuoCustomerLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *PourPositionLabel = new QLabel(tr("浇筑部位"),this);
    PourPositionLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *TelephoneLabel = new QLabel(tr("联系电话"),this);
    TelephoneLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *EngineerLabel = new QLabel(tr("工程名称"),this);
    EngineerLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *PourMethodLabel = new QLabel(tr("浇筑方法"),this);
    PourMethodLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *HasBeenUnderTaskLabel = new QLabel(tr("合同以下方量"),this);
    HasBeenUnderTaskLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *SlumpLabel = new QLabel(tr("坍落度"),this);
    SlumpLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *ContractCompletionLabel = new QLabel(tr("合同完成方量"),this);
    ContractCompletionLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *ProductLabel = new QLabel(tr("产品"),this);
    ProductLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *InfoDateTimeLabel = new QLabel(tr("通知日期"),this);
    InfoDateTimeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *SupplyGoodDateLabel = new QLabel(tr("供货时间"),this);
    SupplyGoodDateLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *WarningLabel = new QLabel(tr("强度等级中含有产品属性，请正确选择。"),this);
    WarningLabel->setStyleSheet("color:red");
    QLabel *RemarksLabel = new QLabel(tr("备注"),this);
    RemarksLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *TodayTaskListLabel = new QLabel(tr("今天已下任务单信息"),this);
    TodayTaskListLabel->setAlignment(Qt::AlignLeft|Qt::AlignBottom);
    QLabel *ContractNoLabel = new QLabel(tr("合同编号"),this);
    ContractNoLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *SettlementAmountLabel = new QLabel(tr("结算方量"),this);
    SettlementAmountLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *ConstructionSiteLabel = new QLabel(tr("工程地址"),this);
    ConstructionSiteLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

    oneTaskNoLineEdit = new QLineEdit(this);
    oneTaskNoLineEdit->setEnabled(false);
    oneTaskNoLineEdit->setStyleSheet("color:red");

    oneStrengthGradeLineEdit = new QLineEdit(this);
    oneStrengthGradeLineEdit->setEnabled(false);
    oneStrengthGradeLineEdit->setStyleSheet("color:black");

    PlannedQuantityLineEdit = new QLineEdit(this);
    QRegExp regx("^[-+]?\\d+(\\.\\d+)?$");
    QValidator *validator = new QRegExpValidator(regx, PlannedQuantityLineEdit );
    PlannedQuantityLineEdit->setValidator( validator );

    TelephoneLineEdit = new QLineEdit(this);

    ConstructionSiteLineEdit = new QLineEdit(this);

    HasBeenUnderTaskLineEdit = new QLineEdit(this);
    HasBeenUnderTaskLineEdit->setEnabled(false);
    HasBeenUnderTaskLineEdit->setStyleSheet("color:black");

    ContractCompletionLineEdit = new QLineEdit(this);
    ContractCompletionLineEdit->setEnabled(false);
    ContractCompletionLineEdit->setStyleSheet("color:black");

    RemarksLineEdit = new QLineEdit(this);

    SettlementAmountLineEdit = new QLineEdit(this);

    SlumpCombox = new QComboBox(this);
    SlumpCombox->setEditable(true);
    db.sql_fillComboBoxItem("select Slump from ProductionTaskList where Slump like '%±%' group by Slump",SlumpCombox);
    SlumpCombox->setCurrentText("150±30");

    RealCustomerCombox = new myComboBox(this);
    db.sql_fillComboBoxItem("select CustomerName from SalesContractManagement where WhetherEffective='有效' group by CustomerName",RealCustomerCombox);
    connect(RealCustomerCombox,SIGNAL(editTextChanged(QString)),this,SLOT(on_RealCustomerCombox()));

    FaHuoCustomerCombox = new myComboBox(this);

    PourPositionCombox = new myComboBox(this);

    EngineerCombox = new myComboBox(this);
    EngineerCombox->setEditable(true);

    PourMethodCombox = new QComboBox(this);
    db.sql_fillComboBoxItem("select PouringMethod from PouringMethod",PourMethodCombox);

    ProductCombox = new QComboBox(this);

    oneContactsComBox = new QComboBox(this);
    oneContactsComBox->setEditable(true);

    ContractNoLineEdit = new QLineEdit(this);
    ContractNoLineEdit->setReadOnly(true);

    InfoDateEdit = new QDateEdit(QDate::currentDate(),this);
    InfoDateEdit->setCalendarPopup(true);
    SupplyDatetimeEdit = new QDateTimeEdit(QDateTime::currentDateTime(),this);
    SupplyDatetimeEdit->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
    SupplyDatetimeEdit->setCalendarPopup(true);

    AttributeToolBtn = new QToolButton(this);
    AttributeToolBtn->setText(tr("属性"));
    connect(AttributeToolBtn,SIGNAL(clicked()),this,SLOT(on_AttributeToolBtn()));

    TaskListView = new QTableView(this);
    connect(TaskListView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick()));
    db.showview(SQL1.toStdString().data(),TaskListView,&model);
    setModelStyle(model);
    TaskListView->setColumnWidth(1,150);
    TaskListView->setColumnWidth(2,150);
    TaskListView->setColumnWidth(3,150);
    TaskListView->setColumnWidth(4,150);

    QGridLayout *layout1 = new QGridLayout;
    layout1->addWidget(TaskNoLabel,0,0);
    layout1->addWidget(oneTaskNoLineEdit,0,1);
    layout1->addWidget(StrengthGradeLabel,0,2);
    layout1->addWidget(oneStrengthGradeLineEdit,0,3,1,2);
    layout1->addWidget(ContactsLabel,0,5);
    layout1->addWidget(oneContactsComBox,0,6);
    layout1->addWidget(PlannedQuantityLabel,0,7);
    layout1->addWidget(PlannedQuantityLineEdit,0,8);
    layout1->addWidget(RealCustomerLabel,1,0);
    layout1->addWidget(RealCustomerCombox,1,1);
    layout1->addWidget(PourPositionLabel,1,2);
    layout1->addWidget(PourPositionCombox,1,3,1,2);
    layout1->addWidget(TelephoneLabel,1,5);
    layout1->addWidget(TelephoneLineEdit,1,6);
    layout1->addWidget(SettlementAmountLabel,1,7);
    layout1->addWidget(SettlementAmountLineEdit,1,8);
    layout1->addWidget(FaHuoCustomerLabel,2,0);
    layout1->addWidget(FaHuoCustomerCombox,2,1);
    layout1->addWidget(PourMethodLabel,2,2);
    layout1->addWidget(PourMethodCombox,2,3,1,2);
    layout1->addWidget(HasBeenUnderTaskLabel,2,5);
    layout1->addWidget(HasBeenUnderTaskLineEdit,2,6);
    layout1->addWidget(ContractNoLabel,2,7);
    layout1->addWidget(ContractNoLineEdit,2,8);
    layout1->addWidget(EngineerLabel,3,0);
    layout1->addWidget(EngineerCombox,3,1);
    layout1->addWidget(SlumpLabel,3,2);
    layout1->addWidget(SlumpCombox,3,3,1,2);
    layout1->addWidget(ContractCompletionLabel,3,5);
    layout1->addWidget(ContractCompletionLineEdit,3,6);
    layout1->addWidget(SupplyGoodDateLabel,3,7);
    layout1->addWidget(SupplyDatetimeEdit,3,8);
    layout1->addWidget(ConstructionSiteLabel,4,0);
    layout1->addWidget(ConstructionSiteLineEdit,4,1);
    layout1->addWidget(ProductLabel,4,2);
    layout1->addWidget(ProductCombox,4,3);
    layout1->addWidget(AttributeToolBtn,4,4);
    layout1->addWidget(InfoDateTimeLabel,4,5);
    layout1->addWidget(InfoDateEdit,4,6);
    layout1->addWidget(WarningLabel,5,1);
    layout1->addWidget(RemarksLabel,6,0);
    layout1->addWidget(RemarksLineEdit,6,1,1,7);
    layout1->addWidget(TodayTaskListLabel,7,0,1,2);
    layout1->setColumnStretch(0,0);
    layout1->setColumnStretch(1,1);
    layout1->setColumnStretch(2,0);
    layout1->setColumnStretch(3,1);
    layout1->setColumnStretch(4,0);
    layout1->setColumnStretch(5,0);
    layout1->setColumnStretch(6,1);
    layout1->setColumnStretch(7,0);
    layout1->setColumnStretch(8,1);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(layout1);
    vlayout->addWidget(TaskListView);

    shengchanrenwudanxinxi->setLayout(vlayout);
    tabWidget->addTab(shengchanrenwudanxinxi,tr("生产任务单信息"));
}

void shengchanrenwudanDlg::creatTabPage3()
{
    SQL3 = "select TaskNumber 任务单号,Customer 实际客户,FaHuoCustomer 发货客户,Engineering 工程名称,StrengthGrade 强度等级,PouringPosition 浇筑部位,PouringMethod 浇筑方法,\
            HasBeenUnderTask 已下任务量,PlannedQuantity 计划方量,ContractCompletion 完成方量,Product 产品名称,Slump 坍落度,Contacts 联系人,ContactNumber 联系电话,\
            SupplyTime 供货时间,Remarks 备注,ContractNumber 合同编号,WhetherInvalid 是否作废,ConstructionSite 工程地址 from ProductionTaskList where WhetherCheck='是' and WhetherSend='否'";

    threeview = new QTableView(this);
    connect(threeview,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick3()));
    db.showview(SQL3,threeview,&threemodel);
    threeview->setColumnWidth(1,150);
    threeview->setColumnWidth(2,150);
    threeview->setColumnWidth(3,150);
    threeview->setColumnWidth(4,150);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(threeview);
    shenheweixiafadeshengchanrenwudan->setLayout(vlayout);
    tabWidget->addTab(shenheweixiafadeshengchanrenwudan,tr("未下发的生产任务单"));
}

void shengchanrenwudanDlg::creatTabPage4()
{
    SQL4 = "select TaskNumber 任务单号,Customer 实际客户,FaHuoCustomer 发货客户,Engineering 工程名称,StrengthGrade 强度等级,PouringPosition 浇筑部位,PouringMethod 浇筑方法,HasBeenUnderTask 已下任务量,\
            PlannedQuantity 计划方量,ContractCompletion 完成方量,Product 产品名称,Slump 坍落度,Contacts 联系人,ContactNumber 联系电话,SupplyTime 供货时间,Remarks 备注,\
            ContractNumber 合同编号,WhetherInvalid 是否作废,ConstructionSite 工程地址 from ProductionTaskList where WhetherCheck='是' and WhetherSend='是' limit 0;";

    fourEngineerCheckBox = new QCheckBox(tr("工程"),this);

    fourEngineerCombox = new myComboBox(this);
    db.sql_fillComboBoxItem("select Engineering from ProductionTaskList group by Engineering",fourEngineerCombox);

    fourdate1 = new QDateEdit(QDate::currentDate().addDays(-1),this);
    fourdate1->setCalendarPopup(true);
    fourdate2 = new QDateEdit(QDate::currentDate(),this);
    fourdate2->setCalendarPopup(true);

    fourFindBtn = new QPushButton(tr("查询"),this);
    fourFindBtn->setFixedWidth(120);
    connect(fourFindBtn,SIGNAL(clicked()),this,SLOT(on_fourFindBtn()));

    QLabel *SupplyTimeLabel = new QLabel(tr("供货时间"),this);
    SupplyTimeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *FuHaoLabel = new QLabel(tr("--"),this);
    FuHaoLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *WarningLabel = new QLabel(tr("红色：未生产，蓝色：未完成，黄色：已完成，白色：已作废"),this);
    WarningLabel->setStyleSheet("color:red");
    WarningLabel->setAlignment(Qt::AlignLeft|Qt::AlignBottom);

    fourview = new QTableView(this);
    db.showview(SQL4,fourview,&fourmodel);
    connect(fourview,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick4()));

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(fourEngineerCheckBox,0);
    hlayout->addWidget(fourEngineerCombox,1);
    hlayout->addWidget(SupplyTimeLabel,0);
    hlayout->addWidget(fourdate1,0);
    hlayout->addWidget(FuHaoLabel,0);
    hlayout->addWidget(fourdate2,0);
    hlayout->addWidget(fourFindBtn,1);
    hlayout->addStretch(3);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(hlayout);
    vlayout->addSpacing(10);
    vlayout->addWidget(WarningLabel);
    vlayout->addWidget(fourview);

    shengchanrenwudanchaxun->setLayout(vlayout);
    tabWidget->addTab(shengchanrenwudanchaxun,tr("生产任务单查询"));
}

void shengchanrenwudanDlg::setModelStyle(QStandardItemModel *model)
{
    int columnCount = model->columnCount();
    int rowCount    = model->rowCount();
    for(int i = 0; i < rowCount; i++){
        for(int j = 0; j < columnCount; j++){
            if(!model->item(i,17)->text().isEmpty()){
                continue;
            }
            if(model->item(i,9)->text().toInt() == 0){
                model->item(i,j)->setBackground(QBrush(QColor(200,100,100)));//红
            }else{
                if(model->item(i,9)->text().toDouble() < model->item(i,8)->text().toDouble()){
                    model->item(i,j)->setBackground(QBrush(QColor(100,200,200)));//蓝
                }
                if(model->item(i,9)->text().toDouble() >= model->item(i,8)->text().toDouble()){
                    model->item(i,j)->setBackground(QBrush(QColor(255,255,0)));//黄
                }
            }
        }
    }
}

void shengchanrenwudanDlg::on_newAction()
{
    saveAction->setEnabled(true);
    updateAction->setEnabled(false);
    deleteAction->setEnabled(false);
    checkAction->setEnabled(false);
    sendAction->setEnabled(false);
    invalidAction->setEnabled(false);
    oneTaskNoLineEdit->clear();
    oneStrengthGradeLineEdit->clear();
    PlannedQuantityLineEdit->clear();
    TelephoneLineEdit->clear();
    HasBeenUnderTaskLineEdit->clear();
    ContractCompletionLineEdit->clear();
    RemarksLineEdit->clear();
    SettlementAmountLineEdit->clear();
    ContractNoLineEdit->clear();
    ConstructionSiteLineEdit->clear();
    SlumpCombox->setCurrentText("150±30");
    RealCustomerCombox->setCurrentIndex(0);
    PourPositionCombox->setCurrentIndex(0);
    EngineerCombox->setCurrentIndex(0);
    PourMethodCombox->setCurrentIndex(0);
    ProductCombox->setCurrentIndex(0);
    oneContactsComBox->setCurrentIndex(0);
    SupplyDatetimeEdit->setDateTime(QDateTime::currentDateTime());

    tabWidget->setCurrentIndex(0);
}

void shengchanrenwudanDlg::on_newAction_plus()
{
    saveAction->setEnabled(true);
    updateAction->setEnabled(false);
    deleteAction->setEnabled(false);
    checkAction->setEnabled(false);
    sendAction->setEnabled(false);
    invalidAction->setEnabled(false);

    oneTaskNoLineEdit->setText(pub.newRenwudanNo());
    oneStrengthGradeLineEdit->clear();
    PlannedQuantityLineEdit->clear();
    TelephoneLineEdit->clear();
    HasBeenUnderTaskLineEdit->clear();
    SlumpCombox->setCurrentText("200±20");
    ContractCompletionLineEdit->clear();
    RemarksLineEdit->clear();
    ConstructionSiteLineEdit->clear();
    SettlementAmountLineEdit->clear();
    RealCustomerCombox->setCurrentIndex(0);
    PourPositionCombox->setCurrentIndex(0);
    EngineerCombox->setCurrentIndex(0);
    PourMethodCombox->setCurrentIndex(0);
    ProductCombox->setCurrentIndex(0);
    oneContactsComBox->setCurrentIndex(0);
    ContractNoLineEdit->clear();
    SupplyDatetimeEdit->setDateTime(QDateTime::currentDateTime());

    tabWidget->setCurrentIndex(0);
}

void shengchanrenwudanDlg::on_saveAction()
{
    if(oneTaskNoLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请新增一个任务单"),0,0,0);
        return;
    }
    if(RealCustomerCombox->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择实际客户"),0,0,0);
        return;
    }
    if(oneStrengthGradeLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("强度等级不能为空"),0,0,0);
        return;
    }
    if(PourPositionCombox->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择浇筑部位"),0,0,0);
        return;
    }
    if(PourMethodCombox->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择浇筑方法"),0,0,0);
        return;
    }
    if(SlumpCombox->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入坍落度"),0,0,0);
        return;
    }
    if(PlannedQuantityLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入计划方量"),0,0,0);
        return;
    }

    QString searchSQL = QString("select * from SalesContractCustomerEngineeringForm where CustomerName='%1' and ProjectName='%2';")
            .arg(RealCustomerCombox->currentText(),EngineerCombox->currentText());
    int rowcount = db.row_count(searchSQL);
    if(rowcount == 0){
        QMessageBox::information(this,tr("提示信息"),tr("当前客户不存在该工程，请到工程档案中添加该工程"),0,0,0);
        return;
    }

    QString saveSQL = QString("insert into ProductionTaskList (TaskNumber,SendTime,Product,StrengthGrade,Slump,PlannedQuantity,\
                              HasBeenUnderTask,ContractCompletion,PouringPosition,PouringMethod,Engineering,Customer,Contacts,\
                              ContactNumber,DateOfNotification,SupplyTime,Remarks,CumulativeNumber,ContractNumber,SettlementAmount,\
                              WhetherCheck,FaHuoCustomer,ConstructionSite) values ('%1','%3','%4','%5','%6','%7','%8','%9','%10','%11','%12','%13','%14',\
                              '%15','%16','%17','%18','%19','%20','%21','%22','%23','%24')")
                        .arg(oneTaskNoLineEdit->text(),QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm"),
                             ProductCombox->currentText(),oneStrengthGradeLineEdit->text(),SlumpCombox->currentText(),PlannedQuantityLineEdit->text(),"0","0",PourPositionCombox->currentText())
                        .arg(PourMethodCombox->currentText(),EngineerCombox->currentText(),RealCustomerCombox->currentText(),oneContactsComBox->currentText(),TelephoneLineEdit->text(),
                             InfoDateEdit->date().toString("yyyy-MM-dd"),SupplyDatetimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"),RemarksLineEdit->text())
                        .arg("0",ContractNoLineEdit->text(),SettlementAmountLineEdit->text(),"是",FaHuoCustomerCombox->currentText(),ConstructionSiteLineEdit->text());

    int res = db.sql_exec(saveSQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();//发送刷新消息
        on_newAction();
        oneTaskNoLineEdit->clear();
        saveAction->setEnabled(false);
        QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
        sockClient->send_Msg1("生产任务单","有新的任务单需要审核。。。");
    }
}

void shengchanrenwudanDlg::on_updateAction()
{
    if(oneTaskNoLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请新增一个任务单"),0,0,0);
        return;
    }
    if(RealCustomerCombox->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择实际客户"),0,0,0);
        return;
    }
    if(oneStrengthGradeLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("强度等级不能为空"),0,0,0);
        return;
    }
    if(PourPositionCombox->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择浇筑部位"),0,0,0);
        return;
    }
    if(PourMethodCombox->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择浇筑方法"),0,0,0);
        return;
    }
    if(SlumpCombox->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入坍落度"),0,0,0);
        return;
    }
    if(PlannedQuantityLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入计划方量"),0,0,0);
        return;
    }

    QString updateSQL = QString("update ProductionTaskList set SendTime='%2',Product='%3',StrengthGrade='%4',Slump='%5',PlannedQuantity='%6',\
                                HasBeenUnderTask='0',ContractCompletion='0',PouringPosition='%7',PouringMethod='%8',Engineering='%10',Customer='%11',\
                                Contacts='%12',ContactNumber='%13',DateOfNotification='%14',SupplyTime='%15',Remarks='%17',CumulativeNumber='%18',\
                                ContractNumber='%19',SettlementAmount='%21',FaHuoCustomer='%22',ConstructionSite='%23' where TaskNumber='%24'")
            .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm"),
                 ProductCombox->currentText(),oneStrengthGradeLineEdit->text(),SlumpCombox->currentText(),PlannedQuantityLineEdit->text(),PourPositionCombox->currentText(),
                 PourMethodCombox->currentText())
            .arg(EngineerCombox->currentText(),RealCustomerCombox->currentText(),oneContactsComBox->currentText(),TelephoneLineEdit->text(),
                 InfoDateEdit->date().toString("yyyy-MM-dd"),SupplyDatetimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"),
                 RemarksLineEdit->text())
            .arg(ContractCompletionLineEdit->text(),ContractNoLineEdit->text(),SettlementAmountLineEdit->text(),FaHuoCustomerCombox->currentText(),ConstructionSiteLineEdit->text(),oneTaskNoLineEdit->text());

    int res = db.sql_exec(updateSQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();//发送刷新消息
        on_newAction();
        oneTaskNoLineEdit->clear();
        saveAction->setEnabled(false);
        QMessageBox::information(this,tr("提示信息"),tr("修改成功"),0,0,0);
    }
}

void shengchanrenwudanDlg::on_deleteAction()
{
    QString deleteSQL = QString("delete from ProductionTaskList where TaskNumber='%1';").arg(oneTaskNoLineEdit->text());
    int res = db.sql_exec(deleteSQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();//发送刷新消息
        on_newAction();
        oneTaskNoLineEdit->clear();
        saveAction->setEnabled(false);
        QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
    }
}

void shengchanrenwudanDlg::on_checkAction()
{

}

void shengchanrenwudanDlg::on_sendAction()
{
    //计算每方单价
    double total = 0;
    QString searchSQL = QString("select ProductPrice from SalesProductList where ContractNumber='%1' and product='%2' and EngineerName='%3' and StartTime<='%4' order by StartTime desc limit 1")
            .arg(ContractNoLineEdit->text(),oneStrengthGradeLineEdit->text().section(" ",0,0),EngineerCombox->currentText(),QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    total += db.sql_fetchrow_plus(searchSQL,0).toDouble();
    int count = oneStrengthGradeLineEdit->text().count(" ");//求出强度等级中包含的产品及属性个数
    for(int i = 1; i < count; i++){
        QString searchSQL = QString("select AttributePrice from SalesAttributeList where ContractNumber='%1' and attribute='%2' and EngineerName='%3' and StartTime<='%4' order by StartTime desc limit 1")
                .arg(ContractNoLineEdit->text(),oneStrengthGradeLineEdit->text().section(" ",i,i),EngineerCombox->currentText(),QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        total += db.sql_fetchrow_plus(searchSQL,0).toDouble();
    }
    QString Price = QString::number(total);

    //获取工程运距
    QString searchYunJuSQL = QString("select PumpFee,Distance from SalesContractCustomerEngineeringForm where ProjectName='%1' and CustomerName = '%2' and DateTime<='%3' order by DateTime desc limit 1")
         .arg(EngineerCombox->currentText(),RealCustomerCombox->currentText(),QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

    QString Distance = db.sql_fetchrow_plus(searchYunJuSQL,1);

    qDebug()<<"price:"<<Price<<"Distance:"<<Distance;


    QString sendSQL = QString("update ProductionTaskList set WhetherSend='是',WhetherReceive='是',ReceivingTime='%1',NoticeNo='',PricePerParty='%2',Distance='%3' where TaskNumber='%4'")
            .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"),Price,Distance,oneTaskNoLineEdit->text());
    int res = db.sql_exec(sendSQL);
    if(res == 0){
        //更新销售合同管理中的已下任务量
        QString updateSQL = QString("update SalesContractManagement set UnderTask=UnderTask+'%1' where ContractNumber='%2';").arg(PlannedQuantityLineEdit->text(),ContractNoLineEdit->text());
        db.sql_exec(updateSQL.toStdString().data());

        sockClient->send_Msg3();//发送刷新消息
        on_newAction();
        oneTaskNoLineEdit->clear();
        saveAction->setEnabled(false);
        QMessageBox::information(this,tr("提示信息"),"下发成功",0,0,0);
        sockClient->send_Msg1("配合比通知单","有新的任务单需要关联配比。。。");
    }
}

void shengchanrenwudanDlg::on_invalidAction()
{
    int res = QMessageBox::question(this,tr("提示信息"),tr("请确认该任务单已完成后再进行作废操作,作废后生产部门将不会再看到此任务单"),QMessageBox::Yes,QMessageBox::No);
    if(res == QMessageBox::Yes){
        QString invalidSQL = QString("update ProductionTaskList set WhetherInvalid='是' where TaskNumber='%1';").arg(oneTaskNoLineEdit->text());
        int res = db.sql_exec(invalidSQL.toStdString().data());
        if(res == 0){
            sockClient->send_Msg3();//发送刷新消息
            on_newAction();
            oneTaskNoLineEdit->clear();
            saveAction->setEnabled(false);
            QMessageBox::information(this,tr("提示信息"),tr("作废成功"),0,0,0);
        }
    }else{
        return;
    }
}

void shengchanrenwudanDlg::on_cheliangStatusAction()
{
    cheliangzhuangtai *cheliangDlg = new cheliangzhuangtai(this);
    cheliangDlg->exec();
    delete cheliangDlg;
}

void shengchanrenwudanDlg::on_jiaozhufangshiAction()
{
    if(oneTaskNoLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择要修改的任务单"),0,0,0);
        return;
    }
    QString updateSQL = QString("update ProductionTaskList set PouringMethod='%1' where TaskNumber='%2';")
            .arg(PourMethodCombox->currentText(),oneTaskNoLineEdit->text());
    int res = db.sql_exec(updateSQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();
        QMessageBox::information(this,tr("提示信息"),tr("浇筑方式修改成功"),0,0,0);
        return;
    }
}

void shengchanrenwudanDlg::ShowSupplyclick()
{
    saveAction->setEnabled(false);
    updateAction->setEnabled(false);
    deleteAction->setEnabled(false);
    sendAction->setEnabled(false);
    invalidAction->setEnabled(true);

    int row = TaskListView->currentIndex().row();
    oneTaskNoLineEdit->setText(model->item(row,0)->text());
    RealCustomerCombox->setCurrentText(model->item(row,1)->text());
    FaHuoCustomerCombox->setCurrentText(model->item(row,2)->text());
    EngineerCombox->setCurrentText(model->item(row,3)->text());

    PourPositionCombox->setCurrentText(model->item(row,5)->text());
    PourMethodCombox->setCurrentText(model->item(row,6)->text());
    HasBeenUnderTaskLineEdit->setText(model->item(row,7)->text());
    PlannedQuantityLineEdit->setText(model->item(row,8)->text());
    ContractCompletionLineEdit->setText(model->item(row,9)->text());
    ProductCombox->setCurrentText(model->item(row,10)->text());
    SlumpCombox->setCurrentText(model->item(row,11)->text());
    oneContactsComBox->setCurrentText(model->item(row,12)->text());
    TelephoneLineEdit->setText(model->item(row,13)->text());
    SupplyDatetimeEdit->setDateTime(QDateTime::fromString(model->item(row,14)->text(),"yyyy-MM-dd hh:mm:ss"));
    RemarksLineEdit->setText(model->item(row,15)->text());
    ContractNoLineEdit->setText(model->item(row,16)->text());
    ConstructionSiteLineEdit->setText(model->item(row,18)->text());
    oneStrengthGradeLineEdit->setText(model->item(row,4)->text());
}

void shengchanrenwudanDlg::ShowSupplyclick3()
{
    saveAction->setEnabled(false);
    updateAction->setEnabled(true);
    deleteAction->setEnabled(false);
    sendAction->setEnabled(true);
    invalidAction->setEnabled(false);

    int row = threeview->currentIndex().row();
    oneTaskNoLineEdit->setText(threemodel->item(row,0)->text());
    RealCustomerCombox->setCurrentText(threemodel->item(row,1)->text());
    FaHuoCustomerCombox->setCurrentText(threemodel->item(row,2)->text());
    EngineerCombox->setCurrentText(threemodel->item(row,3)->text());

    PourPositionCombox->setCurrentText(threemodel->item(row,5)->text());
    PourMethodCombox->setCurrentText(threemodel->item(row,6)->text());
    HasBeenUnderTaskLineEdit->setText(threemodel->item(row,7)->text());
    PlannedQuantityLineEdit->setText(threemodel->item(row,8)->text());
    ContractCompletionLineEdit->setText(threemodel->item(row,9)->text());
    ProductCombox->setCurrentText(threemodel->item(row,10)->text());
    SlumpCombox->setCurrentText(threemodel->item(row,11)->text());
    oneContactsComBox->setCurrentText(threemodel->item(row,12)->text());
    TelephoneLineEdit->setText(threemodel->item(row,13)->text());
    SupplyDatetimeEdit->setDateTime(QDateTime::fromString(threemodel->item(row,14)->text(),"yyyy-MM-dd hh:mm:ss"));
    RemarksLineEdit->setText(threemodel->item(row,15)->text());
    ContractNoLineEdit->setText(threemodel->item(row,16)->text());
    ConstructionSiteLineEdit->setText(threemodel->item(row,18)->text());
    oneStrengthGradeLineEdit->setText(threemodel->item(row,4)->text());

    tabWidget->setCurrentIndex(0);
}

void shengchanrenwudanDlg::ShowSupplyclick4()
{
    saveAction->setEnabled(false);
    updateAction->setEnabled(false);
    deleteAction->setEnabled(false);
    sendAction->setEnabled(false);
    invalidAction->setEnabled(true);

    int row = fourview->currentIndex().row();
    oneTaskNoLineEdit->setText(fourmodel->item(row,0)->text());
    RealCustomerCombox->setCurrentText(fourmodel->item(row,1)->text());
    FaHuoCustomerCombox->setCurrentText(fourmodel->item(row,2)->text());
    EngineerCombox->setCurrentText(fourmodel->item(row,3)->text());
    oneStrengthGradeLineEdit->setText(fourmodel->item(row,4)->text());
    PourPositionCombox->setCurrentText(fourmodel->item(row,5)->text());
    PourMethodCombox->setCurrentText(fourmodel->item(row,6)->text());
    HasBeenUnderTaskLineEdit->setText(fourmodel->item(row,7)->text());
    PlannedQuantityLineEdit->setText(fourmodel->item(row,8)->text());
    ContractCompletionLineEdit->setText(fourmodel->item(row,9)->text());
    ProductCombox->setCurrentText(fourmodel->item(row,10)->text());
    SlumpCombox->setCurrentText(fourmodel->item(row,11)->text());
    oneContactsComBox->setCurrentText(fourmodel->item(row,12)->text());
    TelephoneLineEdit->setText(fourmodel->item(row,13)->text());
    SupplyDatetimeEdit->setDateTime(QDateTime::fromString(fourmodel->item(row,14)->text(),"yyyy-MM-dd hh:mm:ss"));
    RemarksLineEdit->setText(fourmodel->item(row,15)->text());
    ContractNoLineEdit->setText(fourmodel->item(row,16)->text());
    ConstructionSiteLineEdit->setText(fourmodel->item(row,18)->text());

    tabWidget->setCurrentIndex(0);
}

void shengchanrenwudanDlg::on_AttributeToolBtn()
{
    dlg->exec();
    QString qiangdudengji = ProductCombox->currentText() + " " + dlg->shuxing;
    oneStrengthGradeLineEdit->setText(qiangdudengji);
    oneStrengthGradeLineEdit->setToolTip(qiangdudengji);
}

void shengchanrenwudanDlg::on_fillStrengthGrade()
{
    QString chanpin = ProductCombox->currentText() + " ";
    QString shuxing = dlg->shuxing;

    QString qiangdudengji = chanpin + shuxing;
    oneStrengthGradeLineEdit->setText(qiangdudengji);
    oneStrengthGradeLineEdit->setToolTip(qiangdudengji);
}

void shengchanrenwudanDlg::on_fourFindBtn()
{
    QString str;
    if(fourEngineerCheckBox->checkState() == 2){
        str = QString("and Engineering='%1'").arg(fourEngineerCombox->currentText());
    }
    chaxunSQL = QString("select TaskNumber 任务单号,Customer 实际客户,FaHuoCustomer 发货客户,Engineering 工程名称,StrengthGrade 强度等级,PouringPosition 浇筑部位,PouringMethod 浇筑方法,HasBeenUnderTask 已下任务量,\
                        PlannedQuantity 计划方量,ContractCompletion 完成方量,Product 产品名称,Slump 坍落度,Contacts 联系人,ContactNumber 联系电话,SupplyTime 供货时间,Remarks 备注,\
                        ContractNumber 合同编号,WhetherInvalid 是否作废,ConstructionSite 工程地址 from ProductionTaskList where WhetherCheck='是' and WhetherSend='是' and \
                        TaskNumber between '%2' and '%3' %4;").arg(fourdate1->date().toString("yyyyMMdd000"),fourdate2->date().toString("yyyyMMdd999"),str);

    db.showview(chaxunSQL.toStdString().data(),fourview,&fourmodel);
    setModelStyle(fourmodel);
}

void shengchanrenwudanDlg::on_RealCustomerCombox()
{
    FaHuoCustomerCombox->setCurrentText(RealCustomerCombox->currentText());

    disconnect(EngineerCombox,SIGNAL(editTextChanged(QString)),this,SLOT(on_EngineerCombox()));
    EngineerCombox->clear();
    QString fillEngineerComboxSQL = QString("select ProjectName from SalesContractCustomerEngineeringForm where CustomerName='%1' group by ProjectName").arg(RealCustomerCombox->currentText());
    db.sql_fillComboBoxItem(fillEngineerComboxSQL,EngineerCombox);
    connect(EngineerCombox,SIGNAL(editTextChanged(QString)),this,SLOT(on_EngineerCombox()));

    QString searchContractNo = QString("select ContractNumber,SettlementAmount,UnderTask,QuantityOfProduction,WarningState from SalesContractManagement where CustomerName='%1'").arg(RealCustomerCombox->currentText());
    QStringList resStr = db.CreatStrList(searchContractNo);
    if(resStr.count()<5){
        ContractNoLineEdit->clear();
        SettlementAmountLineEdit->clear();
        HasBeenUnderTaskLineEdit->clear();
        ContractCompletionLineEdit->clear();
        warningState.clear();
        return;
    }
    ContractNoLineEdit->setText(resStr.at(0));
    SettlementAmountLineEdit->setText(resStr.at(1));
    HasBeenUnderTaskLineEdit->setText(resStr.at(2));
    ContractCompletionLineEdit->setText(resStr.at(3));
    warningState = resStr.at(4);
}

void shengchanrenwudanDlg::on_EngineerCombox()
{
    disconnect(ProductCombox,SIGNAL(currentTextChanged(QString)),this,SLOT(on_fillStrengthGrade()));

    ProductCombox->clear();

    QString fillProduct = QString("select product from SalesProductList where ContractNumber='%1' and EngineerName='%2' and StartTime=\
                                  (select MAX(StartTime) from SalesProductList where ContractNumber='%1' and EngineerName='%2' and StartTime<='%3')")
                        .arg(ContractNoLineEdit->text(),EngineerCombox->currentText(),SupplyDatetimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
    db.sql_fillComboBoxItem(fillProduct,ProductCombox);
    qDebug()<<fillProduct<<db.geterror();

    dlg->init_shuxingToolBar(ContractNoLineEdit->text(),EngineerCombox->currentText(),SupplyDatetimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"));

    connect(ProductCombox,SIGNAL(currentTextChanged(QString)),this,SLOT(on_fillStrengthGrade()));
}

void shengchanrenwudanDlg::on_oneContactsComBox()
{
    QString searchSQL = QString("select ContactNumber from ProductionTaskList where ContractNumber='%1' and Contacts='%2' limit 1").arg(ContractNoLineEdit->text(),oneContactsComBox->currentText());
    TelephoneLineEdit->setText(db.sql_fetchrow_plus(searchSQL.toStdString().data(),0));
}

void shengchanrenwudanDlg::createAction()
{
    newAction = new QAction(tr("新增"),this);
    newAction->setIcon(QIcon(":/image/new.png"));
    connect(newAction,SIGNAL(triggered()),this,SLOT(on_newAction_plus()));
    saveAction = new QAction(tr("保存"),this);
    saveAction->setEnabled(false);
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
    checkAction->setEnabled(true);
    checkAction->setIcon(QIcon(":/image/check.png"));
    connect(checkAction,SIGNAL(triggered()),this,SLOT(on_checkAction()));
    sendAction = new QAction(tr("下发"),this);
    sendAction->setEnabled(false);
    sendAction->setIcon(QIcon(":/image/send.png"));
    connect(sendAction,SIGNAL(triggered()),this,SLOT(on_sendAction()));
    invalidAction = new QAction(tr("作废"),this);
    invalidAction->setEnabled(false);
    invalidAction->setIcon(QIcon(":/image/invalid.png"));
    connect(invalidAction,SIGNAL(triggered()),this,SLOT(on_invalidAction()));
    cheliangStatusAction = new QAction(tr("车辆状态"),this);
    cheliangStatusAction->setIcon(QIcon(":/image/tongche.png"));
    connect(cheliangStatusAction,SIGNAL(triggered()),this,SLOT(on_cheliangStatusAction()));
    jiaozhufangshiAction = new QAction(tr("修改浇筑方式"),this);
    jiaozhufangshiAction->setIcon(QIcon(":/image/update.png"));
    connect(jiaozhufangshiAction,SIGNAL(triggered()),this,SLOT(on_jiaozhufangshiAction()));
}

void shengchanrenwudanDlg::createTool()
{
    toolBar = new QToolBar;
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar->addAction(newAction);
    toolBar->addAction(saveAction);
    toolBar->addAction(updateAction);
    toolBar->addAction(deleteAction);
    if(whetherCheckSend == "有"){
        toolBar->addAction(sendAction);
    }
    toolBar->addAction(invalidAction);
    toolBar->addAction(cheliangStatusAction);
    toolBar->addAction(jiaozhufangshiAction);
}
