#include "fahuoshujutiaozhengdlg.h"

extern QString userName;
extern mymysql db;
extern myTCPsocket *sockClient;

fahuoshujutiaozhengDlg::fahuoshujutiaozhengDlg(QWidget *parent) :
    QDialog(parent)
{
    tabWidget = new QTabWidget(this);
    qianshoutiaozheng = new QWidget(this);
    qianshoutiaozhengjilu  = new QWidget(this);
    yunjutiaozheng = new QWidget(this);
    yunjutiaozhengjilu  = new QWidget(this);
    //zhuanchangyunju = new QWidget(this);

    creatTabPage1();
    creatTabPage2();
    creatTabPage3();
    creatTabPage4();
    //creatTabPage5();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tabWidget);
}

void fahuoshujutiaozhengDlg::refresh()
{
    //on_chaxunBtn();
    //on_twochaxunBtn();
    //db.showview(SQL3,threeview,&threemodel);
    //db.showview(SQL4,fourview,&fourmodel);
    //db.showview(SQL5,fiveview,&fivemodel);
}

void fahuoshujutiaozhengDlg::createAction()
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

void fahuoshujutiaozhengDlg::createTool()
{
    toolBar = new QToolBar(this);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar->addAction(newAction);
    toolBar->addAction(saveAction);
    toolBar->addAction(updateAction);
    toolBar->addAction(deleteAction);
}

void fahuoshujutiaozhengDlg::keyPressEvent(QKeyEvent *event)
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

void fahuoshujutiaozhengDlg::creatTabPage1()
{
    SQL1 = "select Customer 客户名称,Engineering 工程名称,RecordNumber 记录编号,DeliveryVehicle 送货车辆,Driver 司机,StrengthGrade 强度等级,ShippingVolume 发货方量,ReceiptVolume 签收方量,\
            OutboundTime 发货时间,Flag 结算标志,TaskList 任务单 from ProductionNotice where Flag='2' limit 0;";

    QLabel *label1 = new QLabel(tr("发货日期"),this);
    label1->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label2 = new QLabel(tr("--"),this);
    label2->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label5 = new QLabel(tr("生产记录单"),this);
    label5->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label6 = new QLabel(tr("签收方量"),this);
    label6->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label7 = new QLabel(tr("备注"),this);
    label7->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    checkBox1 = new QCheckBox(tr("实际客户"),this);
    checkBox2 = new QCheckBox(tr("工程名称"),this);

    lineEdit1 = new QLineEdit(this);
    lineEdit1->setEnabled(false);
    lineEdit1->setStyleSheet("color:black");
    lineEdit2 = new QLineEdit(this);
    lineEdit3 = new QLineEdit(this);

    comBox1 = new myComboBox(this);
    db.sql_fillComboBoxItem("SELECT CustomerName FROM CustomerFiles",comBox1);
    connect(comBox1,SIGNAL(editTextChanged(QString)),this,SLOT(on_comBox1Correspond()));

    comBox2 = new QComboBox(this);

    datetimeEdit1 = new QDateTimeEdit(this);
    datetimeEdit1->setDate(QDate::currentDate());
    datetimeEdit1->setCalendarPopup(true);

    datetimeEdit2 = new QDateTimeEdit(this);
    datetimeEdit2->setDate(QDate::currentDate().addDays(1));
    datetimeEdit2->setCalendarPopup(true);

    chaxunBtn = new QPushButton(tr("查询"),this);
    chaxunBtn->setFixedWidth(120);
    connect(chaxunBtn,SIGNAL(clicked()),this,SLOT(on_chaxunBtn()));

    qianshoutiaozhengBtn = new QPushButton(tr("签收调整"),this);
    qianshoutiaozhengBtn->setFixedWidth(120);
    connect(qianshoutiaozhengBtn,SIGNAL(clicked()),this,SLOT(on_qianshoutiaozhengBtn()));

    view = new QTableView(this);
    db.showview_num(SQL1,view,&model,2);
    connect(view,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick()));
    view->setColumnWidth(0,300);
    view->setColumnWidth(1,300);
    view->setColumnWidth(8,120);
    view->setColumnWidth(10,120);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label1,0,0);
    layout->addWidget(datetimeEdit1,0,1);
    layout->addWidget(label2,0,2);
    layout->addWidget(datetimeEdit2,0,3);
    layout->addWidget(chaxunBtn,0,6,2,1,Qt::AlignVCenter);
    layout->addWidget(checkBox1,1,0);
    layout->addWidget(comBox1,1,1,1,3);
    layout->addWidget(checkBox2,1,4);
    layout->addWidget(comBox2,1,5);
    layout->setColumnStretch(0,0);
    layout->setColumnStretch(1,1);
    layout->setColumnStretch(2,0);
    layout->setColumnStretch(3,1);
    layout->setColumnStretch(4,0);
    layout->setColumnStretch(5,1);
    layout->setColumnStretch(6,1);
    layout->setColumnStretch(7,1);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(label5,0);
    hlayout->addWidget(lineEdit1,1);
    hlayout->addWidget(label6,0);
    hlayout->addWidget(lineEdit2,1);
    hlayout->addWidget(label7,0);
    hlayout->addWidget(lineEdit3,2);
    hlayout->addWidget(qianshoutiaozhengBtn,1);
    hlayout->addStretch(6);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(layout);
    vlayout->addSpacing(15);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(view);

    qianshoutiaozheng->setLayout(vlayout);
    tabWidget->addTab(qianshoutiaozheng,tr("签收调整"));
}

void fahuoshujutiaozhengDlg::creatTabPage2()
{
    SQL2 = "select ProductionRecordSheet 生产记录单,CustomerName 客户名称,ProjectName 工程名称,Product 产品,\
            CheNo 送货车辆,OriginalFormula 原方量,NewFormula 新方量,DeliveryTime 发货时间,Regulator 调整人员,\
            AdjustmentTime 调整时间,mark 备注 from SignAdjustmentRecord where ProductionRecordSheet is null;";

    QLabel *label1 = new QLabel(tr("调整时间"),this);
    label1->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label2 = new QLabel(tr("--"),this);
    label2->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    twocomBox1 = new myComboBox(this);
    twocomBox1->setEditable(true);
    const char *fillSQL1 = "SELECT CustomerName FROM CustomerFiles;";
    db.sql_fillComboBoxItem(fillSQL1,twocomBox1);
    connect(twocomBox1,SIGNAL(currentIndexChanged(int)),this,SLOT(on_twocomBox1Correspond()));
    twocomBox2 = new QComboBox(this);
    twocomBox3 = new QComboBox(this);
    const char *fillSQL3 = "SELECT CheNo from SignAdjustmentRecord group by CheNo order by CheNo+0;";
    db.sql_fillComboBoxItem(fillSQL3,twocomBox3);

    twodateEdit1 = new QDateTimeEdit(this);
    twodateEdit1->setDate(QDate::currentDate());
    twodateEdit1->setTime(QTime::fromString("00:00:00","hh:mm:ss"));
    twodateEdit1->setCalendarPopup(true);
    twodateEdit2 = new QDateTimeEdit(this);
    twodateEdit2->setDate(QDate::currentDate().addDays(1));
    twodateEdit2->setTime(QTime::fromString("00:00:00","hh:mm:ss"));
    twodateEdit2->setCalendarPopup(true);

    twocheckBox1 = new QCheckBox(tr("客户名称"),this);
    twocheckBox2 = new QCheckBox(tr("工程名称"),this);
    twocheckBox3 = new QCheckBox(tr("送货车辆"),this);

    twochaxunBtn = new QPushButton(tr("查询"),this);
    twochaxunBtn->setFixedWidth(120);
    connect(twochaxunBtn,SIGNAL(clicked()),this,SLOT(on_twochaxunBtn()));

    twoview = new QTableView(this);
    db.showview(SQL2,twoview,&twomodel);
    twoview->setColumnWidth(1,300);
    twoview->setColumnWidth(2,300);
    twoview->setColumnWidth(7,120);
    twoview->setColumnWidth(9,130);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label1,0,0);
    layout->addWidget(twodateEdit1,0,1);
    layout->addWidget(label2,0,2);
    layout->addWidget(twodateEdit2,0,3);
    layout->addWidget(twocheckBox3,0,4);
    layout->addWidget(twocomBox3,0,5);
    layout->addWidget(twochaxunBtn,0,6,2,1,Qt::AlignVCenter);
    layout->addWidget(twocheckBox1,1,0);
    layout->addWidget(twocomBox1,1,1,1,3);
    layout->addWidget(twocheckBox2,1,4);
    layout->addWidget(twocomBox2,1,5);
    layout->setColumnStretch(0,0);
    layout->setColumnStretch(1,1);
    layout->setColumnStretch(2,0);
    layout->setColumnStretch(3,1);
    layout->setColumnStretch(4,0);
    layout->setColumnStretch(5,1);
    layout->setColumnStretch(6,1);
    layout->setColumnStretch(7,1);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(layout);
    vlayout->addWidget(twoview);

    qianshoutiaozhengjilu->setLayout(vlayout);
    tabWidget->addTab(qianshoutiaozhengjilu,tr("签收调整记录"));
}

void fahuoshujutiaozhengDlg::creatTabPage3()
{
    SQL3 = "select Customer 客户名称,Engineering 工程名称,RecordNumber 记录编号,DeliveryVehicle 送货车辆,\
            Driver 司机,StrengthGrade 强度等级,Mileage 运距,OutboundTime 发货时间,Flag 结算标志,TaskList 任务单 from ProductionNotice where Flag='2' limit 0;";

    QLabel *label1 = new QLabel(tr("调整时间"),this);
    label1->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label2 = new QLabel(tr("--"),this);
    label2->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label3 = new QLabel(tr("生产记录单"),this);
    label3->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label4 = new QLabel(tr("运距调整"),this);
    label4->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label7 = new QLabel(tr("注:结算过的记录不能调整运距"),this);
    label7->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    label7->setStyleSheet("color:red");

    threecomBox1 = new myComboBox(this);
    threecomBox1->setEditable(true);
    const char *fillSQL1 = "SELECT Customer FROM ProductionNotice group by Customer;";
    db.sql_fillComboBoxItem(fillSQL1,threecomBox1);
    threecomBox2 = new QComboBox(this);
    const char *fillSQL2 = "SELECT Engineering FROM ProductionNotice group by Engineering;";
    db.sql_fillComboBoxItem(fillSQL2,threecomBox2);
    threecomBox3 = new QComboBox(this);
    const char *fillSQL3 = "SELECT DeliveryVehicle FROM ProductionNotice group by DeliveryVehicle order by DeliveryVehicle+0;";
    db.sql_fillComboBoxItem(fillSQL3,threecomBox3);

    threedatetimeEdit1 = new QDateTimeEdit(this);
    threedatetimeEdit1->setDate(QDate::currentDate());
    threedatetimeEdit1->setTime(QTime::fromString("00:00:00","hh:mm:ss"));
    threedatetimeEdit1->setCalendarPopup(true);
    threedatetimeEdit2 = new QDateTimeEdit(this);
    threedatetimeEdit2->setDate(QDate::currentDate().addDays(1));
    threedatetimeEdit2->setTime(QTime::fromString("00:00:00","hh:mm:ss"));
    threedatetimeEdit2->setCalendarPopup(true);

    threechaxunBtn = new QPushButton(tr("查询"),this);
    threechaxunBtn->setFixedWidth(120);
    connect(threechaxunBtn,SIGNAL(clicked()),this,SLOT(on_threeChaXunBtn()));

    threebuyunfeiBtn = new QPushButton(tr("确认"),this);
    threebuyunfeiBtn->setFixedWidth(120);
    connect(threebuyunfeiBtn,SIGNAL(clicked()),this,SLOT(on_threeQuerenBtn()));

    threecheckBox1 = new QCheckBox(tr("客户名称"),this);
    threecheckBox2 = new QCheckBox(tr("工程名称"),this);
    threecheckBox3 = new QCheckBox(tr("送货车辆"),this);

    threelineEdit1 = new QLineEdit(this);
    threelineEdit2 = new QLineEdit(this);

    threeview = new QTableView(this);
    db.showview_num(SQL3,threeview,&threemodel,2);
    connect(threeview,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick3()));
    threeview->setColumnWidth(0,300);
    threeview->setColumnWidth(1,300);
    threeview->setColumnWidth(7,120);
    threeview->setColumnWidth(9,120);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label1,0,0);
    layout->addWidget(threedatetimeEdit1,0,1);
    layout->addWidget(label2,0,2);
    layout->addWidget(threedatetimeEdit2,0,3);
    layout->addWidget(threecheckBox3,0,4);
    layout->addWidget(threecomBox3,0,5);
    layout->addWidget(threechaxunBtn,0,6,2,1,Qt::AlignVCenter);
    layout->addWidget(threecheckBox1,1,0);
    layout->addWidget(threecomBox1,1,1,1,3);
    layout->addWidget(threecheckBox2,1,4);
    layout->addWidget(threecomBox2,1,5);
    layout->setColumnStretch(0,0);
    layout->setColumnStretch(1,1);
    layout->setColumnStretch(2,0);
    layout->setColumnStretch(3,1);
    layout->setColumnStretch(4,0);
    layout->setColumnStretch(5,1);
    layout->setColumnStretch(6,1);
    layout->setColumnStretch(7,1);

    QHBoxLayout *layout1 = new QHBoxLayout;
    layout1->addWidget(label3);
    layout1->addWidget(threelineEdit1);
    layout1->addWidget(label4);
    layout1->addWidget(threelineEdit2);
    layout1->addWidget(threebuyunfeiBtn);
    layout1->addWidget(label7);
    layout1->addStretch(3);


    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(layout);
    vlayout->addSpacing(15);
    vlayout->addLayout(layout1);
    vlayout->addWidget(threeview);

    yunjutiaozheng->setLayout(vlayout);
    tabWidget->addTab(yunjutiaozheng,tr("运距调整"));
}

void fahuoshujutiaozhengDlg::creatTabPage4()
{
    SQL4 = "select ProductionRecordSheet 生产记录单,CustomerName 客户名称,ProjectName 工程名称,Product 产品,CheNo 送货车辆,\
            OriginalDistance 原运距,NewDistance 新运距,DeliveryTime 发货时间,Regulator 调整人员,AdjustmentTime 调整时间 \
            from DistanceAdjustmentRecord;";

    QLabel *label1 = new QLabel(tr("调整时间"),this);
    label1->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label2 = new QLabel(tr("--"),this);
    label2->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    fourdateEdit1 = new QDateEdit(QDate::currentDate(),this);
    fourdateEdit1->setCalendarPopup(true);
    fourdateEdit2 = new QDateEdit(QDate::currentDate(),this);
    fourdateEdit2->setCalendarPopup(true);

    fourcheckBox1 = new QCheckBox(tr("客户名称"),this);
    fourcheckBox2 = new QCheckBox(tr("工程名称"),this);
    fourcheckBox3 = new QCheckBox(tr("送货车辆"),this);

    fourcomBox1 = new QComboBox(this);
    const char *fillSQL1 = "SELECT CustomerName FROM DistanceAdjustmentRecord GROUP BY CustomerName;";
    db.sql_fillComboBoxItem(fillSQL1,fourcomBox1);
    fourcomBox2 = new QComboBox(this);
    const char *fillSQL2 = "SELECT ProjectName FROM DistanceAdjustmentRecord GROUP BY ProjectName;";
    db.sql_fillComboBoxItem(fillSQL2,fourcomBox2);
    fourcomBox3 = new QComboBox(this);
    const char *fillSQL3 = "SELECT CheNo FROM DistanceAdjustmentRecord GROUP BY CheNo;";
    db.sql_fillComboBoxItem(fillSQL3,fourcomBox3);

    fourchaxunBtn = new QPushButton(tr("查询"),this);
    fourchaxunBtn->setFixedWidth(120);
    connect(fourchaxunBtn,SIGNAL(clicked()),this,SLOT(on_fourChaXunBtn()));

    fourview = new QTableView(this);
    db.showview(SQL4,fourview,&fourmodel);
    fourview->setColumnWidth(1,300);
    fourview->setColumnWidth(2,300);
    fourview->setColumnWidth(7,120);
    fourview->setColumnWidth(9,130);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label1,0,0);
    layout->addWidget(fourdateEdit1,0,1);
    layout->addWidget(label2,0,2);
    layout->addWidget(fourdateEdit2,0,3);
    layout->addWidget(fourcheckBox3,0,4);
    layout->addWidget(fourcomBox3,0,5);
    layout->addWidget(fourchaxunBtn,0,6,2,1,Qt::AlignVCenter);
    layout->addWidget(fourcheckBox1,1,0);
    layout->addWidget(fourcomBox1,1,1,1,3);
    layout->addWidget(fourcheckBox2,1,4);
    layout->addWidget(fourcomBox2,1,5);
    layout->setColumnStretch(0,0);
    layout->setColumnStretch(1,1);
    layout->setColumnStretch(2,0);
    layout->setColumnStretch(3,1);
    layout->setColumnStretch(4,0);
    layout->setColumnStretch(5,1);
    layout->setColumnStretch(6,1);
    layout->setColumnStretch(7,1);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(layout);
    vlayout->addWidget(fourview);

    yunjutiaozhengjilu->setLayout(vlayout);
    tabWidget->addTab(yunjutiaozhengjilu,tr("运距调整记录"));
}

void fahuoshujutiaozhengDlg::creatTabPage5()
{
    SQL5 = "select TransferTime 转厂时间,TransferVehicle 转厂车辆,DriverName 司机姓名,\
            TransferDistance 转厂运距,NoteTaker 记录人,RecordingTime 记录时间,ID from TransferDistanceRecord;";

    createAction();
    createTool();

    QLabel *label1 = new QLabel(tr("转厂时间"),this);
    label1->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label2 = new QLabel(tr("转厂运距"),this);
    label2->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label3 = new QLabel(tr("车牌号"),this);
    label3->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label4 = new QLabel(tr("司机姓名"),this);
    label4->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    fiveCombox1 = new QComboBox(this);
    const char *fillSQL1 = "SELECT LicensePlate FROM ConcreteVehicleInformation ORDER BY LicensePlate;";
    db.sql_fillComboBoxItem(fillSQL1,fiveCombox1);
    connect(fiveCombox1,SIGNAL(currentIndexChanged(QString)),this,SLOT(on_fiveCombox1Response()));

    fiveCombox2 = new QComboBox(this);
    const char *fillSQL2 = "SELECT DriverName FROM ConcreteTruckDriver ORDER BY DriverName;";
    db.sql_fillComboBoxItem(fillSQL2,fiveCombox2);

    fiveDateEdit = new QDateEdit(QDate::currentDate(),this);
    fiveDateEdit->setCalendarPopup(true);
    fiveLineEdit = new QLineEdit(this);

    fiveview = new QTableView(this);
    db.showview(SQL5,fiveview,&fivemodel);
    connect(fiveview,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick5()));
    fiveview->setColumnWidth(5,120);
    fiveview->setColumnHidden(6,true);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label3,0,0);
    layout->addWidget(fiveCombox1,0,1);
    layout->addWidget(label4,0,2);
    layout->addWidget(fiveCombox2,0,3);
    layout->addWidget(label1,1,0);
    layout->addWidget(fiveDateEdit,1,1);
    layout->addWidget(label2,1,2);
    layout->addWidget(fiveLineEdit,1,3);
    layout->setColumnStretch(0,0);
    layout->setColumnStretch(1,1);
    layout->setColumnStretch(2,0);
    layout->setColumnStretch(3,1);
    layout->setColumnStretch(4,3);


    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(toolBar);
    vlayout->addLayout(layout);
    vlayout->addWidget(fiveview);

    zhuanchangyunju->setLayout(vlayout);
    tabWidget->addTab(zhuanchangyunju,tr("转厂运距"));
}

void fahuoshujutiaozhengDlg::on_newAction()
{
    saveAction->setEnabled(true);
    updateAction->setEnabled(false);
    deleteAction->setEnabled(false);

    disconnect(fiveCombox1,SIGNAL(currentIndexChanged(QString)),this,SLOT(on_fiveCombox1Response()));
    fiveCombox1->setCurrentIndex(0);
    fiveCombox2->setCurrentIndex(0);
    fiveLineEdit->clear();
    fiveDateEdit->setDate(QDate::currentDate());
    connect(fiveCombox1,SIGNAL(currentIndexChanged(QString)),this,SLOT(on_fiveCombox1Response()));
}

void fahuoshujutiaozhengDlg::on_saveAction()
{
    if(fiveCombox1->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择车辆"),0,0,0);
        return;
    }
    if(fiveCombox2->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择司机"),0,0,0);
        return;
    }
    if(fiveLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入转厂运距"),0,0,0);
        return;
    }
    QString insertSQL = QString("insert into TransferDistanceRecord (TransferTime,TransferVehicle,DriverName,\
                                TransferDistance,NoteTaker,RecordingTime) values ('%1','%2','%3','%4','%5','%6');")
            .arg(fiveDateEdit->date().toString("yyyy-MM-dd"),fiveCombox1->currentText(),fiveCombox2->currentText(),
                 fiveLineEdit->text(),userName,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm"));
    int res = db.sql_exec(insertSQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();
        on_newAction();
        QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
    }
}

void fahuoshujutiaozhengDlg::on_updateAction()
{
    if(fiveCombox1->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择车辆"),0,0,0);
        return;
    }
    if(fiveCombox2->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择司机"),0,0,0);
        return;
    }
    if(fiveLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入转厂运距"),0,0,0);
        return;
    }
    QString updateSQL = QString("update TransferDistanceRecord set TransferTime='%1',TransferVehicle='%2',\
                                DriverName='%3',TransferDistance='%4',NoteTaker='%5',RecordingTime='%6' \
                                where ID='%7';")
            .arg(fiveDateEdit->date().toString("yyyy-MM-dd"),fiveCombox1->currentText(),fiveCombox2->currentText(),
                 fiveLineEdit->text(),userName,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm"),fiveID);
    int res = db.sql_exec(updateSQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();
        on_newAction();
        QMessageBox::information(this,tr("提示信息"),tr("修改成功"),0,0,0);
    }
}

void fahuoshujutiaozhengDlg::on_deleteAction()
{
    QString deleteSQL = QString("delete from TransferDistanceRecord where ID='%1';").arg(fiveID);
    int res = db.sql_exec(deleteSQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();
        on_newAction();
        QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
    }
}

void fahuoshujutiaozhengDlg::ShowSupplyclick()
{
    int row = view->currentIndex().row();
    lineEdit1->setText(model->item(row,2)->text());
    CustomerName = model->item(row,0)->text();
    ProjectName = model->item(row,1)->text();
    Product = model->item(row,5)->text();
    OriginalFormula = model->item(row,6)->text();
    DeliveryTime = model->item(row,8)->text();
    CheNo = model->item(row,3)->text();
}

void fahuoshujutiaozhengDlg::ShowSupplyclick3()
{
    int row = threeview->currentIndex().row();
    threelineEdit1->setText(threemodel->item(row,2)->text());
}

void fahuoshujutiaozhengDlg::ShowSupplyclick5()
{
    saveAction->setEnabled(false);
    updateAction->setEnabled(true);
    deleteAction->setEnabled(true);
    int row = fiveview->currentIndex().row();
    fiveID = fivemodel->item(row,6)->text();
    fiveCombox1->setCurrentText(fivemodel->item(row,1)->text());
    fiveCombox2->setCurrentText(fivemodel->item(row,2)->text());
    fiveDateEdit->setDate(QDate::fromString(fivemodel->item(row,0)->text(),"yyyy-MM-dd"));
    fiveLineEdit->setText(fivemodel->item(row,3)->text());
}

void fahuoshujutiaozhengDlg::on_chaxunBtn()
{
    QString kehu,gongcheng;
    if(checkBox1->checkState() == 2){
        kehu = QString(" and Customer='%1' ").arg(comBox1->currentText());
    }
    if(checkBox2->checkState() == 2){
        kehu = QString(" and Engineering='%1' ").arg(comBox2->currentText());
    }
    QString SearchSQL = QString("select Customer 客户名称,Engineering 工程名称,RecordNumber 记录编号,DeliveryVehicle 送货车辆,Driver 司机,StrengthGrade 强度等级,\
                                ShippingVolume 发货方量,ReceiptVolume 签收方量,OutboundTime 发货时间,Flag 结算标志,TaskList 任务单 from ProductionNotice where OutboundTime \
                                between '%1' and '%2' %3 %4;")
            .arg(datetimeEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),datetimeEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),kehu,gongcheng);
    db.showview_num(SearchSQL.toStdString().data(),view,&model,2);
    view->sortByColumn(2,Qt::DescendingOrder);
}

void fahuoshujutiaozhengDlg::on_qianshoutiaozhengBtn()
{
    if(lineEdit1->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择要调整的生产记录单"),0,0,0);
        return;
    }
    if(lineEdit1->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入签收方量"),0,0,0);
        return;
    }
    db.sql_exec("begin");
    QString updateSQL = QString("update ProductionNotice set ReceiptVolume='%1' where RecordNumber='%2';")
            .arg(lineEdit2->text(),lineEdit1->text());
    int res = db.sql_exec(updateSQL.toStdString().data());
    if(res == -1){
        db.sql_exec("rollback");
        return;
    }
    if(!view->currentIndex().isValid()){
        db.sql_exec("rollback");
        return;
    }
    QString inserSQL = QString("insert into SignAdjustmentRecord (ProductionRecordSheet,CustomerName,\
                               ProjectName,Product,OriginalFormula,NewFormula,DeliveryTime,Regulator,\
                               AdjustmentTime,CheNo,mark) values ('%1','%2','%3','%4','%5','%6','%7','%8','%9','%10','%11');")
    .arg(lineEdit1->text(),CustomerName,ProjectName,Product,OriginalFormula,lineEdit2->text(),DeliveryTime,userName,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
    .arg(CheNo,lineEdit3->text());

    res = db.sql_exec(inserSQL.toStdString().data());
    if(res == -1){
        db.sql_exec("rollback");
        return;
    }
    db.sql_exec("commit");
    on_chaxunBtn();
    lineEdit1->clear();
    lineEdit2->clear();
    QMessageBox::information(this,tr("提示消息"),tr("签收调整成功"),0,0,0);

}

void fahuoshujutiaozhengDlg::on_twochaxunBtn()
{
    QString kehumingcheng,gongchengmingcheng,songhuocheliang;
    if(twocheckBox1->checkState() == 2){
        kehumingcheng = QString(" and CustomerName='%1'").arg(twocomBox1->currentText());
    }
    if(twocheckBox2->checkState() == 2){
        gongchengmingcheng = QString(" and ProjectName='%1'").arg(twocomBox2->currentText());
    }
    if(twocheckBox3->checkState() == 2){
        songhuocheliang = QString(" and CheNo='%1'").arg(twocomBox2->currentText());
    }
    QString searchSQL = QString("select ProductionRecordSheet 生产记录单,CustomerName 客户名称,ProjectName 工程名称,Product 产品,\
                                CheNo 送货车辆,OriginalFormula 原方量,NewFormula 新方量,DeliveryTime 发货时间,Regulator 调整人员,\
                                AdjustmentTime 调整时间,mark 备注 from SignAdjustmentRecord where AdjustmentTime between '%1' and '%2'%3%4%5")
            .arg(twodateEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),twodateEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),kehumingcheng,gongchengmingcheng,songhuocheliang);
    db.showview(searchSQL.toStdString().data(),twoview,&twomodel);

}

void fahuoshujutiaozhengDlg::on_comBox1Correspond()
{
    comBox2->clear();
    QString fillSQL2 = QString("select Engineering from ProductionNotice where Customer='%1' group by Engineering;").arg(comBox1->currentText());
    db.sql_fillComboBoxItem(fillSQL2.toStdString().data(),comBox2);
}

void fahuoshujutiaozhengDlg::on_twocomBox1Correspond()
{
    twocomBox2->clear();
    QString fillSQL2 = QString("select Engineering from ProductionNotice where Customer='%1' group by Engineering;").arg(twocomBox1->currentText());
    db.sql_fillComboBoxItem(fillSQL2.toStdString().data(),twocomBox2);
}

void fahuoshujutiaozhengDlg::on_threeQuerenBtn()
{
    if(threelineEdit1->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择要调整的生产记录单"),0,0,0);
        return;
    }
    if(threelineEdit2->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入调整运距"),0,0,0);
        return;
    }


    //事务开始
    db.sql_exec("begin;");

    //查找运费
    QString searchFreightPrice = QString("select Freight from ConcreteCarFreightSet where cast(MinimumMileage as SIGNED INTEGER)<='%1' and cast(MaximumMileage as SIGNED INTEGER)>='%1';").arg(threelineEdit2->text());
    QString FreightPrice = db.sql_fetchrow_plus(searchFreightPrice.toStdString().data(),0);

    QString updateSQL = QString("update ProductionNotice set Mileage='%1',FreightPrice='%2' where RecordNumber='%3';").arg(threelineEdit2->text(),FreightPrice,threelineEdit1->text());
    int res = db.sql_exec(updateSQL.toStdString().data());
    if(res == -1){
        db.sql_exec("rollback");
        return;
    }
    if(!threeview->currentIndex().isValid()){
        db.sql_exec("rollback");
        return;
    }
    int row = threeview->currentIndex().row();
    QString inserSQL = QString("insert into DistanceAdjustmentRecord (ProductionRecordSheet,CustomerName,\
                               ProjectName,Product,OriginalDistance,NewDistance,DeliveryTime,Regulator,\
                               AdjustmentTime,CheNo) values ('%1','%2','%3','%4','%5','%6','%7','%8','%9','%10');")
    .arg(threelineEdit1->text(),threemodel->item(row,0)->text(),threemodel->item(row,1)->text(),threemodel->item(row,5)->text(),
         threemodel->item(row,6)->text(),threelineEdit2->text(),threemodel->item(row,7)->text(),userName,
         QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
    .arg(threemodel->item(row,3)->text());
    res = db.sql_exec(inserSQL.toStdString().data());
    if(res == -1){
        db.sql_exec("rollback");
        return;
    }
    db.sql_exec("commit");
    on_threeChaXunBtn();
    threelineEdit1->clear();
    threelineEdit2->clear();
    QMessageBox::information(this,tr("提示消息"),tr("运距调整成功"),0,0,0);
}

void fahuoshujutiaozhengDlg::on_threeChaXunBtn()
{
    QString kehumingcheng,gongchengmingcheng,songhuocheliang;
    if(threecheckBox1->checkState() == 2){
        kehumingcheng = QString(" and Customer='%1'").arg(threecomBox1->currentText());
    }
    if(threecheckBox2->checkState() == 2){
        gongchengmingcheng = QString(" and Engineering='%1'").arg(threecomBox2->currentText());
    }
    if(threecheckBox3->checkState() == 2){
        songhuocheliang = QString(" and DeliveryVehicle='%1'").arg(threecomBox3->currentText());
    }
    QString searchSQL = QString("select Customer 客户名称,Engineering 工程名称,RecordNumber 记录编号,DeliveryVehicle 送货车辆,\
                                Driver 司机,StrengthGrade 强度等级,Mileage 运距,OutboundTime 发货时间,Flag 结算标志,TaskList 任务单 \
                                from ProductionNotice where Flag='2' and OutboundTime between '%1' and '%2' %3 %4 %5;")
            .arg(threedatetimeEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),threedatetimeEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),
                 kehumingcheng,gongchengmingcheng,songhuocheliang);
    db.showview_num(searchSQL.toStdString().data(),threeview,&threemodel,2);
    threeview->sortByColumn(2,Qt::DescendingOrder);
}

void fahuoshujutiaozhengDlg::on_fourChaXunBtn()
{
    QString kehumingcheng,gongchengmingcheng,songhuocheliang;
    if(fourcheckBox1->checkState() == 2){
        kehumingcheng = QString(" and CustomerName='%1'").arg(fourcomBox1->currentText());
    }
    if(fourcheckBox2->checkState() == 2){
        gongchengmingcheng = QString(" and ProjectName='%1'").arg(fourcomBox2->currentText());
    }
    if(fourcheckBox3->checkState() == 2){
        songhuocheliang = QString(" and CheNo='%1'").arg(fourcomBox3->currentText());
    }
    QString searchSQL = QString("select ProductionRecordSheet 生产记录单,CustomerName 客户名称,ProjectName 工程名称,Product 产品,CheNo 送货车辆,\
                                OriginalDistance 原运距,NewDistance 新运距,DeliveryTime 发货时间,Regulator 调整人员,AdjustmentTime 调整时间 \
                                from DistanceAdjustmentRecord where AdjustmentTime between '%1' and '%2' %3%4%5;")
            .arg(fourdateEdit1->date().toString("yyyy-MM-dd"),fourdateEdit2->date().addDays(1).toString("yyyy-MM-dd"),
                 kehumingcheng,gongchengmingcheng,songhuocheliang);
    db.showview(searchSQL.toStdString().data(),fourview,&fourmodel);
}

void fahuoshujutiaozhengDlg::on_fiveCombox1Response()
{
    QString searchSQL = QString("select Driver1 from ConcreteVehicleInformation where LicensePlate='%1';").arg(fiveCombox1->currentText());
    fiveCombox2->setCurrentText(db.sql_fetchrow_plus(searchSQL.toStdString().data(),0));
}

