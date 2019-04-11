#include "peihebitongzhidandlg.h"
#include "mainwindow.h"

#define RONGZHONGWUCHA 2

extern mymysql db;
extern pubfunc pub;
extern QString whetherCheckSend;
extern QString userName;
extern myTCPsocket *sockClient;

peihebitongzhidanDlg::peihebitongzhidanDlg(QWidget *parent) :
    QDialog(parent)
{
    PhbWidget = new QWidget(this);

    tabWidget = new QTabWidget(this);
    peihebitongzhidanxinxi = new QWidget(this);
    //weishenhedetongzhidan = new QWidget(this);
    shenheweixiafatongzhidan = new QWidget(this);
    yishiyongtongzhidan = new QWidget(this);
    peibixiugaijilv = new QWidget(this);

    QRegExp rx("^[0-9]*$");
    pReg_zhengshu = new QRegExpValidator(rx, this);

    creatTabPage1();
    //creatTabPage2();
    creatTabPage3();
    creatTabPage4();
    creatTabPage5();

    createAction();
    createTool();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(toolBar);
    layout->addWidget(tabWidget);
}

peihebitongzhidanDlg::~peihebitongzhidanDlg()
{
    delete model1;
    //delete twomodel;
    delete threemodel;
    delete fourmodel;
}

void peihebitongzhidanDlg::refresh()
{
    db.showview(SQL1,view1,&model1);
    db.showview(SQL3,threeview,&threemodel);
    on_fourBtn();
    on_fiveFindBtn();
}

void peihebitongzhidanDlg::paintEvent(QPaintEvent *event)
{
    PhbWidget->setFixedWidth(PhbScrollArea->width());
    event->accept();
}

void peihebitongzhidanDlg::keyPressEvent(QKeyEvent *event)
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

void peihebitongzhidanDlg::creatTabPage1()
{
    SQL1 = "select TaskNumber 任务单号,Customer 客户名称,Engineering 工程名称,StrengthGrade 强度等级,Template 配合比模板,PouringPosition 浇筑部位,\
            PouringMethod 浇筑方法,PlannedQuantity 计划方量,Slump 坍落度,Contacts 联系人,ContactNumber 联系电话,Remarks 备注,SupplyTime 供货时间,NoticeNo 通知单号 from ProductionTaskList \
            where WhetherCheck='是' and WhetherSend='是' and WhetherReceive='是' and NoticeNo='' and WhetherInvalid=''";

    QLabel *tzdNumberLabel  = new QLabel(tr("通知单号"),this);
    tzdNumberLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *CustomerLabel  = new QLabel(tr("客户名称"),this);
    CustomerLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *StrengthGradeLabel  = new QLabel(tr("强度等级"),this);
    StrengthGradeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *TaskListLabel  = new QLabel(tr("任务单号"),this);
    TaskListLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *EngineerLabel  = new QLabel(tr("工程名称"),this);
    EngineerLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *PourPositionLabel  = new QLabel(tr("浇筑部位"),this);
    PourPositionLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *PourMethodLabel  = new QLabel(tr("浇筑方法"),this);
    PourMethodLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *TaskRemarksLabel  = new QLabel(tr("任务单备注"),this);
    TaskRemarksLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *ConstructSiteLabel  = new QLabel(tr("施工地点"),this);
    ConstructSiteLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *SlumpLabel = new QLabel(tr("坍落度"),this);
    SlumpLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *ContactLabel = new QLabel(tr("联系人"),this);
    ContactLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *TelephoneLabel = new QLabel(tr("联系电话"),this);
    TelephoneLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *SupplyTimeLabel = new QLabel(tr("供货时间"),this);
    SupplyTimeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *PhbTemplateLabel = new QLabel(tr("配比模板"),this);
    PhbTemplateLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *NoPhbTaskListLabel = new QLabel(tr("未关联配比的任务单"),this);
    NoPhbTaskListLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    QLabel *WuShui1Label = new QLabel(tr("1#线污水比例"),this);
    WuShui1Label->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    QLabel *WuShui2Label = new QLabel(tr("2#线污水比例"),this);
    WuShui2Label->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    QLabel *WuShui3Label = new QLabel(tr("3#线污水比例"),this);
    WuShui3Label->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    QLabel *WuShui4Label = new QLabel(tr("4#线污水比例"),this);
    WuShui4Label->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    QLabel *StirTime1Label = new QLabel(tr("1#线搅拌时间"),this);
    StirTime1Label->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    QLabel *StirTime2Label = new QLabel(tr("2#线搅拌时间"),this);
    StirTime2Label->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    QLabel *StirTime3Label = new QLabel(tr("3#线搅拌时间"),this);
    StirTime3Label->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    QLabel *StirTime4Label = new QLabel(tr("4#线搅拌时间"),this);
    StirTime4Label->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);

    onetzdNumberLineEdit = new QLineEdit(this);
    onetzdNumberLineEdit->setReadOnly(true);
    CustomerLineEdit = new QLineEdit(this);
    CustomerLineEdit->setReadOnly(true);
    StrengthGradeLineEdit = new QLineEdit(this);
    StrengthGradeLineEdit->setReadOnly(true);
    TaskListLineEdit = new QLineEdit(this);
    TaskListLineEdit->setReadOnly(true);
    EngineerLineEdit = new QLineEdit(this);
    EngineerLineEdit->setReadOnly(true);
    PourPositionLineEdit = new QLineEdit(this);
    PourPositionLineEdit->setReadOnly(true);
    PourMethodLineEdit = new QLineEdit(this);
    PourMethodLineEdit->setReadOnly(true);
    TaskRemarksLineEdit = new QLineEdit(this);
    TaskRemarksLineEdit->setReadOnly(true);
    ConstructSiteLineEdit = new QLineEdit(this);
    ConstructSiteLineEdit->setReadOnly(true);
    SlumpLineEdit = new QLineEdit(this);
    SlumpLineEdit->setReadOnly(true);
    ContactLineEdit = new QLineEdit(this);
    ContactLineEdit->setReadOnly(true);
    TelephoneLineEdit = new QLineEdit(this);
    TelephoneLineEdit->setReadOnly(true);
    SupplyTimeLineEdit = new QLineEdit(this);
    SupplyTimeLineEdit->setReadOnly(true);
    WuShui1LineEdit = new QLineEdit(this);
    WuShui1LineEdit->setFixedWidth(60);
    WuShui1LineEdit->setValidator(pReg_zhengshu);
    WuShui2LineEdit = new QLineEdit(this);
    WuShui2LineEdit->setFixedWidth(60);
    WuShui2LineEdit->setValidator(pReg_zhengshu);
    WuShui3LineEdit = new QLineEdit(this);
    WuShui3LineEdit->setFixedWidth(60);
    WuShui3LineEdit->setValidator(pReg_zhengshu);
    WuShui4LineEdit = new QLineEdit(this);
    WuShui4LineEdit->setFixedWidth(60);
    WuShui4LineEdit->setValidator(pReg_zhengshu);
    StirTime1LineEdit = new QLineEdit(this);
    StirTime1LineEdit->setFixedWidth(60);
    StirTime1LineEdit->setValidator(pReg_zhengshu);
    StirTime2LineEdit = new QLineEdit(this);
    StirTime2LineEdit->setFixedWidth(60);
    StirTime2LineEdit->setValidator(pReg_zhengshu);
    StirTime3LineEdit = new QLineEdit(this);
    StirTime3LineEdit->setFixedWidth(60);
    StirTime3LineEdit->setValidator(pReg_zhengshu);
    StirTime4LineEdit = new QLineEdit(this);
    StirTime4LineEdit->setFixedWidth(60);
    StirTime4LineEdit->setValidator(pReg_zhengshu);

    //1#配合比
    QString phbSQL1 = QString("SELECT UnitMaterial,ERPmaterial,CorrespondingField from UnitMaterialCorrespondsToERPMaterial where ProductionUnit = '1#机组'");
    db.newWidget(phbSQL1,list1,strList1,matList1,pflistEdit1,this);

    //2#配合比
    QString phbSQL2 = QString("SELECT UnitMaterial,ERPmaterial,CorrespondingField from UnitMaterialCorrespondsToERPMaterial where ProductionUnit = '2#机组'");
    db.newWidget(phbSQL2,list2,strList2,matList2,pflistEdit2,this);

    //3#配合比
    QString phbSQL3 = QString("SELECT UnitMaterial,ERPmaterial,CorrespondingField from UnitMaterialCorrespondsToERPMaterial where ProductionUnit = '3#机组'");
    db.newWidget(phbSQL3,list3,strList3,matList3,pflistEdit3,this);

    //4#配合比
    QString phbSQL4 = QString("SELECT UnitMaterial,ERPmaterial,CorrespondingField from UnitMaterialCorrespondsToERPMaterial where ProductionUnit = '4#机组'");
    db.newWidget(phbSQL4,list4,strList4,matList4,pflistEdit4,this);

    PhbTemplateCombox = new QComboBox(this);
    PhbTemplateCombox->setEnabled(false);
    PhbTemplateCombox->setStyleSheet("color:black");
    const char *fillComBox = "select PhbNumber from PEIFANG1";
    db.sql_fillComboBoxItem(fillComBox,PhbTemplateCombox);
    connect(PhbTemplateCombox,SIGNAL(currentTextChanged(QString)),this,SLOT(PhbTemplateComboxRespones()));

    view1 = new QTableView(this);
    connect(view1,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick()));
    db.showview(SQL1,view1,&model1);

    QGridLayout *layout1 = new QGridLayout;
    layout1->addWidget(tzdNumberLabel,0,0);
    layout1->addWidget(onetzdNumberLineEdit,0,1);
    layout1->addWidget(CustomerLabel,0,2);
    layout1->addWidget(CustomerLineEdit,0,3);
    layout1->addWidget(StrengthGradeLabel,0,4);
    layout1->addWidget(StrengthGradeLineEdit,0,5);
    layout1->addWidget(TaskListLabel,1,0);
    layout1->addWidget(TaskListLineEdit,1,1);
    layout1->addWidget(EngineerLabel,1,2);
    layout1->addWidget(EngineerLineEdit,1,3);
    layout1->addWidget(PourPositionLabel,1,4);
    layout1->addWidget(PourPositionLineEdit,1,5);
    layout1->addWidget(PourMethodLabel,1,6);
    layout1->addWidget(PourMethodLineEdit,1,7);
    layout1->addWidget(TaskRemarksLabel,2,0);
    layout1->addWidget(TaskRemarksLineEdit,2,1,1,3);
    layout1->addWidget(ConstructSiteLabel,2,4);
    layout1->addWidget(ConstructSiteLineEdit,2,5);
    layout1->addWidget(SlumpLabel,2,6);
    layout1->addWidget(SlumpLineEdit,2,7);
    layout1->addWidget(PhbTemplateLabel,3,0);
    layout1->addWidget(PhbTemplateCombox,3,1);
    layout1->addWidget(ContactLabel,3,2);
    layout1->addWidget(ContactLineEdit,3,3);
    layout1->addWidget(TelephoneLabel,3,4);
    layout1->addWidget(TelephoneLineEdit,3,5);
    layout1->addWidget(SupplyTimeLabel,3,6);
    layout1->addWidget(SupplyTimeLineEdit,3,7);
    layout1->setSpacing(10);

    QHBoxLayout *hlayout1 = new QHBoxLayout;
    hlayout1->setSpacing(0);
    hlayout1->setMargin(0);
    for(int i = 0; i < list1.size(); i++){
        hlayout1->addWidget(list1.at(i));
    }

    QHBoxLayout *hlayout2 = new QHBoxLayout;
    hlayout2->setSpacing(0);
    hlayout2->setMargin(0);
    for(int i = 0; i < list2.size(); i++){
        hlayout2->addWidget(list2.at(i));
    }

    QHBoxLayout *hlayout3 = new QHBoxLayout;
    hlayout3->setSpacing(0);
    hlayout3->setMargin(0);
    for(int i = 0; i < list3.size(); i++){
        hlayout3->addWidget(list3.at(i));
    }

    QHBoxLayout *hlayout4 = new QHBoxLayout;
    hlayout4->setSpacing(0);
    hlayout4->setMargin(0);
    for(int i = 0; i < list4.size(); i++){
        hlayout4->addWidget(list4.at(i));
    }

    QGroupBox *groupBox1 = new QGroupBox(this);
    groupBox1->setTitle(tr("1#配合比"));
    groupBox1->setLayout(hlayout1);

    QGroupBox *groupBox2 = new QGroupBox(this);
    groupBox2->setTitle(tr("2#配合比"));
    groupBox2->setLayout(hlayout2);

    QGroupBox *groupBox3 = new QGroupBox(this);
    groupBox3->setTitle(tr("3#配合比"));
    groupBox3->setLayout(hlayout3);

    QGroupBox *groupBox4 = new QGroupBox(this);
    groupBox4->setTitle(tr("4#配合比"));
    groupBox4->setLayout(hlayout4);

    QVBoxLayout *PhbLayout = new QVBoxLayout;
    PhbLayout->addWidget(groupBox1,0);
    PhbLayout->addWidget(groupBox2,0);
    PhbLayout->addWidget(groupBox3,0);
    PhbLayout->addWidget(groupBox4,0);
    PhbLayout->setMargin(0);

    PhbWidget->setLayout(PhbLayout);

    PhbScrollArea = new QScrollArea(this);
    PhbScrollArea->setObjectName(QString("PhbScrollArea"));
    PhbScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    PhbScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    PhbScrollArea->setWidget(PhbWidget);
    PhbScrollArea->setStyleSheet("QScrollArea[objectName=\"PhbScrollArea\"]{border:0px;}");

    QHBoxLayout *WuShuiLayout = new QHBoxLayout;
    WuShuiLayout->addStretch(30);
    WuShuiLayout->addWidget(StirTime1Label,0,Qt::AlignRight);
    WuShuiLayout->addWidget(StirTime1LineEdit,1,Qt::AlignRight);
    WuShuiLayout->addWidget(WuShui1Label,0,Qt::AlignRight);
    WuShuiLayout->addWidget(WuShui1LineEdit,1,Qt::AlignRight);

    WuShuiLayout->addWidget(StirTime2Label,0,Qt::AlignRight);
    WuShuiLayout->addWidget(StirTime2LineEdit,1,Qt::AlignRight);
    WuShuiLayout->addWidget(WuShui2Label,0,Qt::AlignRight);
    WuShuiLayout->addWidget(WuShui2LineEdit,1,Qt::AlignRight);

    WuShuiLayout->addWidget(StirTime3Label,0,Qt::AlignRight);
    WuShuiLayout->addWidget(StirTime3LineEdit,1,Qt::AlignRight);
    WuShuiLayout->addWidget(WuShui3Label,0,Qt::AlignRight);
    WuShuiLayout->addWidget(WuShui3LineEdit,1,Qt::AlignRight);

    WuShuiLayout->addWidget(StirTime4Label,0,Qt::AlignRight);
    WuShuiLayout->addWidget(StirTime4LineEdit,1,Qt::AlignRight);
    WuShuiLayout->addWidget(WuShui4Label,0,Qt::AlignRight);
    WuShuiLayout->addWidget(WuShui4LineEdit,1,Qt::AlignRight);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addLayout(layout1,1);
    vlayout->addSpacing(5);
    vlayout->addWidget(PhbScrollArea,1);
    vlayout->addSpacing(5);
    vlayout->addLayout(WuShuiLayout,0);
    vlayout->addSpacing(5);
    vlayout->addWidget(NoPhbTaskListLabel,0);
    vlayout->addWidget(view1,1);

    peihebitongzhidanxinxi->setLayout(vlayout);
    tabWidget->addTab(peihebitongzhidanxinxi,tr("配合比通知单信息"));
}

void peihebitongzhidanDlg::creatTabPage2()
{
    SQL2 = "select TaskNumber 任务单号,Customer 客户名称,Engineering 工程名称,StrengthGrade 强度等级,Template 配合比模板,PouringPosition 浇筑部位,\
            PouringMethod 浇筑方法,PlannedQuantity 计划方量,Slump 坍落度,Contacts 联系人,ContactNumber 联系电话,Remarks 备注,SupplyTime 供货时间,NoticeNo 通知单号 from ProductionTaskList \
            where WhetherCheck='是' and WhetherSend='是' and WhetherReceive='是' and TzdCheck='否' and TzdSend='否' and WhetherInvalid=''";

    twoview = new QTableView(this);
    connect(twoview,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick2()));
    db.showview(SQL2,twoview,&twomodel);



    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(twoview);


    weishenhedetongzhidan->setLayout(vlayout);

    tabWidget->addTab(weishenhedetongzhidan,tr("未审核的通知单"));
}

void peihebitongzhidanDlg::creatTabPage3()
{
    SQL3 = "select TaskNumber 任务单号,Customer 客户名称,Engineering 工程名称,StrengthGrade 强度等级,Template 配合比模板,PouringPosition 浇筑部位,\
            PouringMethod 浇筑方法,PlannedQuantity 计划方量,Slump 坍落度,Contacts 联系人,ContactNumber 联系电话,Remarks 备注,SupplyTime 供货时间,NoticeNo 通知单号 from ProductionTaskList \
            where WhetherCheck='是' and WhetherSend='是' and WhetherReceive='是' and TzdCheck='否' and TzdSend='否' and WhetherInvalid=''";

    threeview = new QTableView(this);
    connect(threeview,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick3()));
    db.showview(SQL3,threeview,&threemodel);


    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(threeview);

    shenheweixiafatongzhidan->setLayout(vlayout);
    tabWidget->addTab(shenheweixiafatongzhidan,tr("未下发的通知单"));
}

void peihebitongzhidanDlg::creatTabPage4()
{
    SQL4 = "select TaskNumber 任务单号,Customer 客户名称,Engineering 工程名称,StrengthGrade 强度等级,Template 配合比模板,PouringPosition 浇筑部位,\
            PouringMethod 浇筑方法,PlannedQuantity 计划方量,Slump 坍落度,Contacts 联系人,ContactNumber 联系电话,Remarks 备注,SupplyTime 供货时间,NoticeNo 通知单号 from ProductionTaskList \
            where WhetherCheck='是' and WhetherSend='是' and WhetherReceive='是' and TzdCheck='是' and TzdSend='是' and WhetherInvalid='' order by TaskNumber desc limit 100;";

    fourdatetime1 = new QDateTimeEdit(this);
    fourdatetime1->setDate(QDate::currentDate());
    fourdatetime1->setCalendarPopup(true);
    fourdatetime2 = new QDateTimeEdit(this);
    fourdatetime2->setDate(QDate::currentDate());
    fourdatetime2->setCalendarPopup(true);

    fourcheckBox = new QCheckBox(this);
    fourcheckBox->setText(tr("配合比通知单下发时间"));
    fourcheckBox->setCheckState(Qt::Checked);

    QLabel *label = new QLabel(tr("--"),this);

    fourBtn = new QPushButton(tr("查询"),this);
    fourBtn->setFixedWidth(120);
    connect(fourBtn,SIGNAL(clicked()),this,SLOT(on_fourBtn()));

    fourview = new QTableView(this);
    connect(fourview,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick4()));
    db.showview(SQL4,fourview,&fourmodel);

    on_fourBtn();

    QGridLayout *layout1 = new QGridLayout;
    layout1->addWidget(fourcheckBox,0,0);
    layout1->addWidget(fourdatetime1,0,1);
    layout1->addWidget(label,0,2);
    layout1->addWidget(fourdatetime2,0,3);
    layout1->addWidget(fourBtn,0,4);
    layout1->setColumnStretch(0,0);
    layout1->setColumnStretch(1,1);
    layout1->setColumnStretch(2,0);
    layout1->setColumnStretch(3,1);
    layout1->setColumnStretch(4,1);
    layout1->setColumnStretch(5,3);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addLayout(layout1);
    vlayout->addWidget(fourview);

    yishiyongtongzhidan->setLayout(vlayout);

    tabWidget->addTab(yishiyongtongzhidan,tr("已使用的通知单"));
}

void peihebitongzhidanDlg::creatTabPage5()
{
    SQL5 = "select rwID 任务编号,Engineering 工程名称,matChang 修改内容,StateNo 搅拌站号,user 修改人,changTime 修改时间 from rwPeiFangChangeRecord limit 0";

    QLabel *TimeLabel  = new QLabel(tr("修改时间"),this);
    TimeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label = new QLabel(tr("--"),this);
    label->setAlignment(Qt::AlignCenter);

    fivedatetime1 = new QDateTimeEdit(this);
    fivedatetime1->setCalendarPopup(true);
    fivedatetime1->setDate(QDate::currentDate());
    fivedatetime2 = new QDateTimeEdit(this);
    fivedatetime2->setCalendarPopup(true);
    fivedatetime2->setDate(QDate::currentDate().addDays(1));
    connect(fivedatetime1,SIGNAL(dateTimeChanged(QDateTime)),this,SLOT(on_fiveDateChange()));
    connect(fivedatetime2,SIGNAL(dateTimeChanged(QDateTime)),this,SLOT(on_fiveDateChange()));

    fiveGongChengCheckBox = new QCheckBox(tr("工程名称"),this);
    fiveRenWuDanCheckBox = new QCheckBox(tr("任务单号"),this);
    fiveUnitCheckBox = new QCheckBox(tr("生产机组"),this);

    fiveGongChengCombox = new QComboBox(this);
    fiveRenWuDanCombox = new QComboBox(this);

    on_fiveDateChange();

    fiveUnitCombox = new QComboBox(this);
    const char * fillUnitSQL = "select UnitName from UnitSetting";
    db.sql_fillComboBoxItem(fillUnitSQL,fiveUnitCombox);

    fiveFindBtn = new QPushButton(this);
    fiveFindBtn->setFixedWidth(120);
    connect(fiveFindBtn,SIGNAL(clicked()),this,SLOT(on_fiveFindBtn()));
    fiveFindBtn->setText(tr("查询"));

    fiveview = new QTableView(this);
    db.showview(SQL5,fiveview,&fivemodel);
    fiveview->setColumnWidth(1,220);
    fiveview->setColumnWidth(2,150);
    fiveview->setColumnWidth(5,150);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(TimeLabel,0);
    hlayout->addWidget(fivedatetime1,1);
    hlayout->addWidget(label,0);
    hlayout->addWidget(fivedatetime2,1);
    hlayout->addWidget(fiveGongChengCheckBox,0);
    hlayout->addWidget(fiveGongChengCombox,2);
    hlayout->addWidget(fiveRenWuDanCheckBox,0);
    hlayout->addWidget(fiveRenWuDanCombox,1);
    hlayout->addWidget(fiveUnitCheckBox,0);
    hlayout->addWidget(fiveUnitCombox,1);
    hlayout->addWidget(fiveFindBtn,1);
    hlayout->addStretch(3);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addLayout(hlayout);
    vlayout->addWidget(fiveview);

    peibixiugaijilv->setLayout(vlayout);

    tabWidget->addTab(peibixiugaijilv,tr("任务单配比修改记录"));
}

void peihebitongzhidanDlg::PhbTemplateComboxRespones()
{
    //1#配比
    QString fillTableWidget1 = QString("SELECT ");
    for(int i = 0;i<strList1.count();i++){
        QString str = QString("Mat%1,").arg(strList1.at(i));
        fillTableWidget1.append(str);
    }
    fillTableWidget1 = fillTableWidget1.append(QString(" jbTime,WuShui from PEIFANG1 where PhbNumber='%1'").arg(PhbTemplateCombox->currentText()));
    QStringList resStrList1 = db.CreatStrList(fillTableWidget1);
    if(resStrList1.count()<strList1.count()+2){
        return;
    }
    for(int i = 0; i < strList1.count(); i++){
        connect(pflistEdit1.at(i),SIGNAL(textChanged(QString)),this,SLOT(on_CalcRongZhong1()));
        pflistEdit1.at(i)->setText(resStrList1.at(i));
    }
    StirTime1LineEdit->setText(resStrList1.at(strList1.count()));
    WuShui1LineEdit->setText(resStrList1.at(strList1.count()+1));



    //2#配比
    QString fillTableWidget2 = QString("SELECT ");
    for(int i = 0;i<strList2.count();i++){
        QString str = QString("Mat%1,").arg(strList2.at(i));
        fillTableWidget2.append(str);
    }
    fillTableWidget2 = fillTableWidget2.append(QString(" jbTime,WuShui from PEIFANG2 where PhbNumber='%1'").arg(PhbTemplateCombox->currentText()));
    QStringList resStrList2 = db.CreatStrList(fillTableWidget2);
    if(resStrList2.count()<strList2.count()+2){
        return;
    }
    for(int i = 0; i < strList2.count(); i++){
        connect(pflistEdit2.at(i),SIGNAL(textChanged(QString)),this,SLOT(on_CalcRongZhong2()));
        pflistEdit2.at(i)->setText(resStrList2.at(i));
    }
    StirTime2LineEdit->setText(resStrList2.at(strList2.count()));
    WuShui2LineEdit->setText(resStrList2.at(strList2.count()+1));



    //3#配比
    QString fillTableWidget3 = QString("SELECT ");
    for(int i = 0;i<strList3.count();i++){
        QString str = QString("Mat%1,").arg(strList3.at(i));
        fillTableWidget3.append(str);
    }
    fillTableWidget3 = fillTableWidget3.append(QString(" jbTime,WuShui from PEIFANG3 where PhbNumber='%1'").arg(PhbTemplateCombox->currentText()));
    QStringList resStrList3 = db.CreatStrList(fillTableWidget3);
    if(resStrList3.count()<strList3.count()+2){
        return;
    }
    for(int i = 0; i < strList3.count(); i++){
        connect(pflistEdit3.at(i),SIGNAL(textChanged(QString)),this,SLOT(on_CalcRongZhong3()));
        pflistEdit3.at(i)->setText(resStrList3.at(i));
    }
    StirTime3LineEdit->setText(resStrList3.at(strList3.count()));
    WuShui3LineEdit->setText(resStrList3.at(strList3.count()+1));

    //4#配比
    QString fillTableWidget4 = QString("SELECT ");
    for(int i = 0;i<strList4.count();i++){
        QString str = QString("Mat%1,").arg(strList4.at(i));
        fillTableWidget4.append(str);
    }
    fillTableWidget4 = fillTableWidget4.append(QString(" jbTime,WuShui from PEIFANG4 where PhbNumber='%1'").arg(PhbTemplateCombox->currentText()));
    QStringList resStrList4 = db.CreatStrList(fillTableWidget4);
    if(resStrList4.count()<strList4.count()+2){
        return;
    }
    for(int i = 0; i < strList4.count(); i++){
        connect(pflistEdit4.at(i),SIGNAL(textChanged(QString)),this,SLOT(on_CalcRongZhong4()));
        pflistEdit4.at(i)->setText(resStrList4.at(i));
    }
    StirTime4LineEdit->setText(resStrList4.at(strList4.count()));
    WuShui4LineEdit->setText(resStrList4.at(strList4.count()+1));
}

void peihebitongzhidanDlg::on_newAction()
{
    PhbTemplateCombox->setEnabled(true);
    saveAction->setEnabled(true);
    updateAction->setEnabled(false);
    deleteAction->setEnabled(false);
    checkAction->setEnabled(false);
    sendAction->setEnabled(false);
    onetzdNumberLineEdit->clear();
    CustomerLineEdit->clear();
    StrengthGradeLineEdit->clear();
    TaskListLineEdit->clear();
    EngineerLineEdit->clear();
    PourPositionLineEdit->clear();
    PourMethodLineEdit->clear();
    TaskRemarksLineEdit->clear();
    ConstructSiteLineEdit->clear();
    SlumpLineEdit->clear();
    ContactLineEdit->clear();
    TelephoneLineEdit->clear();
    SupplyTimeLineEdit->clear();
    PhbTemplateCombox->setCurrentIndex(0);

    tabWidget->setCurrentIndex(0);
}

void peihebitongzhidanDlg::on_newAction_plus()
{
    PhbTemplateCombox->setEnabled(true);
    saveAction->setEnabled(true);
    updateAction->setEnabled(false);
    deleteAction->setEnabled(false);
    checkAction->setEnabled(false);
    sendAction->setEnabled(false);
    onetzdNumberLineEdit->setText(pub.newTongzhidanNo());
    CustomerLineEdit->clear();
    StrengthGradeLineEdit->clear();
    TaskListLineEdit->clear();
    EngineerLineEdit->clear();
    PourPositionLineEdit->clear();
    PourMethodLineEdit->clear();
    TaskRemarksLineEdit->clear();
    ConstructSiteLineEdit->clear();
    SlumpLineEdit->clear();
    ContactLineEdit->clear();
    TelephoneLineEdit->clear();
    SupplyTimeLineEdit->clear();
    PhbTemplateCombox->setCurrentIndex(0);


    tabWidget->setCurrentIndex(0);
}

void peihebitongzhidanDlg::on_saveAction()
{
    if(TaskListLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择一个任务单"),0,0,0);
        return;
    }
    if(PhbTemplateCombox->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择一个配合比"),0,0,0);
        return;
    }

    //1#机组修改记录
    QString searchSQL1 = QString("select * from rwPEIFANG where TaskList='%1' and StateNo='1'").arg(TaskListLineEdit->text());
    if(db.row_count(searchSQL1) != 0){
        for(int i = 0; i<strList1.count(); i++){
            if(pflistEdit1.at(i)->text().toDouble() != db.sql_fetchrow_plus(searchSQL1,strList1.at(i).toInt()).toDouble()){
                QString neirong = matList1.at(i)+": "+db.sql_fetchrow_plus(searchSQL1,strList1.at(i).toInt())+"→"+pflistEdit1.at(i)->text();
                QString insertSQL = QString("insert into rwPeiFangChangeRecord (rwID,Engineering,matChang,StateNo,user,changTime) values ('%1','%2','%3','%4','%5','%6')")
                        .arg(TaskListLineEdit->text(),EngineerLineEdit->text(),neirong,"1#机组",userName,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
                db.sql_exec(insertSQL);
            }
        }
    }

    //2#机组修改记录
    QString searchSQL2 = QString("select * from rwPEIFANG where TaskList='%1' and StateNo='2'").arg(TaskListLineEdit->text());
    if(db.row_count(searchSQL2) != 0){
        for(int i = 0; i<strList2.count(); i++){
            if(pflistEdit2.at(i)->text().toDouble() != db.sql_fetchrow_plus(searchSQL2,strList2.at(i).toInt()).toDouble()){
                QString neirong = matList2.at(i)+": "+db.sql_fetchrow_plus(searchSQL2,strList2.at(i).toInt())+"→"+pflistEdit2.at(i)->text();
                QString insertSQL = QString("insert into rwPeiFangChangeRecord (rwID,Engineering,matChang,StateNo,user,changTime) values ('%1','%2','%3','%4','%5','%6')")
                        .arg(TaskListLineEdit->text(),EngineerLineEdit->text(),neirong,"2#机组",userName,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
                db.sql_exec(insertSQL);
            }
        }
    }

    //3#机组修改记录
    QString searchSQL3 = QString("select * from rwPEIFANG where TaskList='%1' and StateNo='3'").arg(TaskListLineEdit->text());
    if(db.row_count(searchSQL3) != 0){
        for(int i = 0; i<strList3.count(); i++){
            if(pflistEdit3.at(i)->text().toDouble() != db.sql_fetchrow_plus(searchSQL3,strList3.at(i).toInt()).toDouble()){
                QString neirong = matList3.at(i)+": "+db.sql_fetchrow_plus(searchSQL3,strList3.at(i).toInt())+"→"+pflistEdit3.at(i)->text();
                QString insertSQL = QString("insert into rwPeiFangChangeRecord (rwID,Engineering,matChang,StateNo,user,changTime) values ('%1','%2','%3','%4','%5','%6')")
                        .arg(TaskListLineEdit->text(),EngineerLineEdit->text(),neirong,"3#机组",userName,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
                db.sql_exec(insertSQL);
            }
        }
    }

    //4#机组修改记录
    QString searchSQL4 = QString("select * from rwPEIFANG where TaskList='%1' and StateNo='4'").arg(TaskListLineEdit->text());
    if(db.row_count(searchSQL4) != 0){
        for(int i = 0; i<strList4.count(); i++){
            if(pflistEdit4.at(i)->text().toDouble() != db.sql_fetchrow_plus(searchSQL4,strList4.at(i).toInt()).toDouble()){
                QString neirong = matList4.at(i)+": "+db.sql_fetchrow_plus(searchSQL4,strList4.at(i).toInt())+"→"+pflistEdit4.at(i)->text();
                QString insertSQL = QString("insert into rwPeiFangChangeRecord (rwID,Engineering,matChang,StateNo,user,changTime) values ('%1','%2','%3','%4','%5','%6')")
                        .arg(TaskListLineEdit->text(),EngineerLineEdit->text(),neirong,"4#机组",userName,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
                db.sql_exec(insertSQL);
            }
        }
    }

    //事务操作开始
    db.sql_exec("begin");
    int res = 0;
    //插入1#站配比
    QString insertSQL1 = QString("replace into rwPEIFANG SET TaskList='%1'").arg(TaskListLineEdit->text());
    for(int i = 0; i < strList1.count(); i++){
        insertSQL1.append(QString(",MAT%1 = '%2'").arg(strList1.at(i),pflistEdit1.at(i)->text()));
    }
    insertSQL1.append(QString(",WuShui='%1',JBTIME='%2',StateNo='1'").arg(WuShui1LineEdit->text(),StirTime1LineEdit->text()));
    res = db.sql_exec(insertSQL1);
    if(res != 0){
        db.sql_exec("rollback");
        return;
    }

    //插入2#站配比
    QString insertSQL2 = QString("replace into rwPEIFANG SET TaskList='%1'").arg(TaskListLineEdit->text());
    for(int i = 0; i < strList2.count(); i++){
        insertSQL2.append(QString(",MAT%1 = '%2'").arg(strList2.at(i),pflistEdit2.at(i)->text()));
    }
    insertSQL2.append(QString(",WuShui='%1',JBTIME='%2',StateNo='2'").arg(WuShui2LineEdit->text(),StirTime2LineEdit->text()));
    res = db.sql_exec(insertSQL2);
    if(res != 0){
        db.sql_exec("rollback");
        return;
    }

    //插入3#站配比
    QString insertSQL3 = QString("replace into rwPEIFANG SET TaskList='%1'").arg(TaskListLineEdit->text());
    for(int i = 0; i < strList3.count(); i++){
        insertSQL3.append(QString(",MAT%1 = '%2'").arg(strList3.at(i),pflistEdit3.at(i)->text()));
    }
    insertSQL3.append(QString(",WuShui='%1',JBTIME='%2',StateNo='3'").arg(WuShui3LineEdit->text(),StirTime3LineEdit->text()));
    res = db.sql_exec(insertSQL3);
    if(res != 0){
        db.sql_exec("rollback");
        return;
    }

    //插入4#站配比
    QString insertSQL4 = QString("replace into rwPEIFANG SET TaskList='%1'").arg(TaskListLineEdit->text());
    for(int i = 0; i < strList4.count(); i++){
        insertSQL4.append(QString(",MAT%1 = '%2'").arg(strList4.at(i),pflistEdit4.at(i)->text()));
    }
    insertSQL4.append(QString(",WuShui='%1',JBTIME='%2',StateNo='4'").arg(WuShui4LineEdit->text(),StirTime4LineEdit->text()));
    res = db.sql_exec(insertSQL4);
    if(res != 0){
        db.sql_exec("rollback");
        return;
    }

    //更新任务单
    QString saveSQL = QString("update ProductionTaskList set NoticeNo='%1',Template='%2',TzdCheck='否',TzdSend='否' where TaskNumber='%3';")
                            .arg(onetzdNumberLineEdit->text(),PhbTemplateCombox->currentText(),TaskListLineEdit->text());
    res = db.sql_exec(saveSQL);
    if(res != 0){
        db.sql_exec("rollback");
        return;
    }
    //事务操作结束
    db.sql_exec("commit");

    if(res == 0){
        sockClient->send_Msg3();
        on_newAction();
        onetzdNumberLineEdit->clear();
        saveAction->setEnabled(false);
        PhbTemplateCombox->setEnabled(false);
        QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
        sockClient->send_Msg1("配合比通知单","有新的通知单需要下发。。。");
    }
}

void peihebitongzhidanDlg::on_updateAction()
{
    if(TaskListLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择一个任务单"),0,0,0);
        return;
    }
    if(PhbTemplateCombox->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择一个配合比"),0,0,0);
        return;
    }


    //1#机组修改记录
    QString searchSQL1 = QString("select * from rwPEIFANG where TaskList='%1' and StateNo='1'").arg(TaskListLineEdit->text());
    if(db.row_count(searchSQL1) != 0){
        for(int i = 0; i<strList1.count(); i++){
            if(pflistEdit1.at(i)->text().toDouble() != db.sql_fetchrow_plus(searchSQL1,strList1.at(i).toInt()).toDouble()){
                QString neirong = matList1.at(i)+": "+db.sql_fetchrow_plus(searchSQL1,strList1.at(i).toInt())+"→"+pflistEdit1.at(i)->text();
                QString insertSQL = QString("insert into rwPeiFangChangeRecord (rwID,Engineering,matChang,StateNo,user,changTime) values ('%1','%2','%3','%4','%5','%6')")
                        .arg(TaskListLineEdit->text(),EngineerLineEdit->text(),neirong,"1#机组",userName,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
                db.sql_exec(insertSQL);
            }
        }
    }

    //2#机组修改记录
    QString searchSQL2 = QString("select * from rwPEIFANG where TaskList='%1' and StateNo='2'").arg(TaskListLineEdit->text());
    if(db.row_count(searchSQL2) != 0){
        for(int i = 0; i<strList2.count(); i++){
            if(pflistEdit2.at(i)->text().toDouble() != db.sql_fetchrow_plus(searchSQL2,strList2.at(i).toInt()).toDouble()){
                QString neirong = matList2.at(i)+": "+db.sql_fetchrow_plus(searchSQL2,strList2.at(i).toInt())+"→"+pflistEdit2.at(i)->text();
                QString insertSQL = QString("insert into rwPeiFangChangeRecord (rwID,Engineering,matChang,StateNo,user,changTime) values ('%1','%2','%3','%4','%5','%6')")
                        .arg(TaskListLineEdit->text(),EngineerLineEdit->text(),neirong,"2#机组",userName,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
                db.sql_exec(insertSQL);
            }
        }
    }

    //3#机组修改记录
    QString searchSQL3 = QString("select * from rwPEIFANG where TaskList='%1' and StateNo='3'").arg(TaskListLineEdit->text());
    if(db.row_count(searchSQL3) != 0){
        for(int i = 0; i<strList3.count(); i++){
            if(pflistEdit3.at(i)->text().toDouble() != db.sql_fetchrow_plus(searchSQL3,strList3.at(i).toInt()).toDouble()){
                QString neirong = matList3.at(i)+": "+db.sql_fetchrow_plus(searchSQL3,strList3.at(i).toInt())+"→"+pflistEdit3.at(i)->text();
                QString insertSQL = QString("insert into rwPeiFangChangeRecord (rwID,Engineering,matChang,StateNo,user,changTime) values ('%1','%2','%3','%4','%5','%6')")
                        .arg(TaskListLineEdit->text(),EngineerLineEdit->text(),neirong,"3#机组",userName,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
                db.sql_exec(insertSQL);
            }
        }
    }

    //4#机组修改记录
    QString searchSQL4 = QString("select * from rwPEIFANG where TaskList='%1' and StateNo='4'").arg(TaskListLineEdit->text());
    if(db.row_count(searchSQL4) != 0){
        for(int i = 0; i<strList4.count(); i++){
            if(pflistEdit4.at(i)->text().toDouble() != db.sql_fetchrow_plus(searchSQL4,strList4.at(i).toInt()).toDouble()){
                QString neirong = matList4.at(i)+": "+db.sql_fetchrow_plus(searchSQL4,strList4.at(i).toInt())+"→"+pflistEdit4.at(i)->text();
                QString insertSQL = QString("insert into rwPeiFangChangeRecord (rwID,Engineering,matChang,StateNo,user,changTime) values ('%1','%2','%3','%4','%5','%6')")
                        .arg(TaskListLineEdit->text(),EngineerLineEdit->text(),neirong,"4#机组",userName,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
                db.sql_exec(insertSQL);
            }
        }
    }

    //事务操作开始
    db.sql_exec("begin");
    int res = 0;
    //插入1#站配比
    QString insertSQL1 = QString("replace into rwPEIFANG SET TaskList='%1'").arg(TaskListLineEdit->text());
    for(int i = 0; i < strList1.count(); i++){
        insertSQL1.append(QString(",MAT%1 = '%2'").arg(strList1.at(i),pflistEdit1.at(i)->text()));
    }
    insertSQL1.append(QString(",WuShui='%1',JBTIME='%2',StateNo='1'").arg(WuShui1LineEdit->text(),StirTime1LineEdit->text()));
    res = db.sql_exec(insertSQL1);
    if(res != 0){
        db.sql_exec("rollback");
        return;
    }

    //插入2#站配比
    QString insertSQL2 = QString("replace into rwPEIFANG SET TaskList='%1'").arg(TaskListLineEdit->text());
    for(int i = 0; i < strList2.count(); i++){
        insertSQL2.append(QString(",MAT%1 = '%2'").arg(strList2.at(i),pflistEdit2.at(i)->text()));
    }
    insertSQL2.append(QString(",WuShui='%1',JBTIME='%2',StateNo='2'").arg(WuShui2LineEdit->text(),StirTime2LineEdit->text()));
    res = db.sql_exec(insertSQL2);
    if(res != 0){
        db.sql_exec("rollback");
        return;
    }

    //插入3#站配比
    QString insertSQL3 = QString("replace into rwPEIFANG SET TaskList='%1'").arg(TaskListLineEdit->text());
    for(int i = 0; i < strList3.count(); i++){
        insertSQL3.append(QString(",MAT%1 = '%2'").arg(strList3.at(i),pflistEdit3.at(i)->text()));
    }
    insertSQL3.append(QString(",WuShui='%1',JBTIME='%2',StateNo='3'").arg(WuShui3LineEdit->text(),StirTime3LineEdit->text()));
    res = db.sql_exec(insertSQL3);
    if(res != 0){
        db.sql_exec("rollback");
        return;
    }

    //插入4#站配比
    QString insertSQL4 = QString("replace into rwPEIFANG SET TaskList='%1'").arg(TaskListLineEdit->text());
    for(int i = 0; i < strList4.count(); i++){
        insertSQL4.append(QString(",MAT%1 = '%2'").arg(strList4.at(i),pflistEdit4.at(i)->text()));
    }
    insertSQL4.append(QString(",WuShui='%1',JBTIME='%2',StateNo='4'").arg(WuShui4LineEdit->text(),StirTime4LineEdit->text()));
    res = db.sql_exec(insertSQL4);
    if(res != 0){
        db.sql_exec("rollback");
        return;
    }

    //更新任务单
    QString saveSQL = QString("update ProductionTaskList set NoticeNo='%1',Template='%2',TzdCheck='否',TzdSend='否' where TaskNumber='%3';")
                            .arg(onetzdNumberLineEdit->text(),PhbTemplateCombox->currentText(),TaskListLineEdit->text());
    res = db.sql_exec(saveSQL);
    if(res != 0){
        db.sql_exec("rollback");
        return;
    }
    //事务操作结束
    db.sql_exec("commit");

    if(res == 0){
        sockClient->send_Msg3();
        on_newAction();
        onetzdNumberLineEdit->clear();
        saveAction->setEnabled(false);
        PhbTemplateCombox->setEnabled(false);
        QMessageBox::information(this,tr("提示信息"),tr("修改成功"),0,0,0);
        sockClient->send_Msg1("配合比通知单","有新的通知单需要下发。。。");
    }
}

void peihebitongzhidanDlg::on_deleteAction()
{
    //事务操作开始
    db.sql_exec("begin");
    int res = 0;
    QString deleteSQL1 = QString("update ProductionTaskList set  NoticeNo='',Template='',TzdCheck='',TzdSend='' where TaskNumber='%1';").arg(TaskListLineEdit->text());
    res = db.sql_exec(deleteSQL1);
    if(res != 0){
        db.sql_exec("rollback");
        return;
    }
    QString deleteSQL2 = QString("delete from rwPEIFANG where TaskList='%1'").arg(TaskListLineEdit->text());
    res = db.sql_exec(deleteSQL2);
    if(res != 0){
        db.sql_exec("rollback");
        return;
    }
    //事务操作结束
    db.sql_exec("commit");

    if(res == 0){
        sockClient->send_Msg3();
        on_newAction();
        onetzdNumberLineEdit->clear();
        saveAction->setEnabled(false);
        PhbTemplateCombox->setEnabled(false);
        QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
    }
}

void peihebitongzhidanDlg::on_checkAction()
{
    QString checkSQL = QString("update ProductionTaskList set TzdCheck='是',NoticeCheckTime='%1' where TaskNumber='%2';").arg(QDate::currentDate().toString("yyyy-MM-dd"),TaskListLineEdit->text());
    int res = db.sql_exec(checkSQL);
    if(res == 0){
        sockClient->send_Msg3();
        on_newAction();
        onetzdNumberLineEdit->clear();
        saveAction->setEnabled(false);
        QMessageBox::information(this,tr("提示信息"),tr("审核成功"),0,0,0);
    }
}

void peihebitongzhidanDlg::on_sendAction()
{
    //下发
    QString sendSQL = QString("update ProductionTaskList set TzdSend='是',TzdCheck='是',NoticeCheckTime='%1',NoticeSendTime='%1' where TaskNumber='%2';")
                    .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:mm"),TaskListLineEdit->text());
    int res = db.sql_exec(sendSQL);
    if(res == 0){
        QString insertSQL = QString("REPLACE into taskListReact (taskID,unitID) values ('%1','1'),('%1','2'),('%1','3')").arg(TaskListLineEdit->text());
        db.sql_exec(insertSQL);

        sockClient->send_Msg3();//刷新表格
        on_newAction();
        onetzdNumberLineEdit->clear();
        saveAction->setEnabled(false);
        PhbTemplateCombox->setEnabled(false);
        QMessageBox::information(this,tr("提示信息"),tr("下发成功"),0,0,0);
    }

    sockClient->send_Msg1("生产任务安排","有新的生产任务安排。。。");
}

void peihebitongzhidanDlg::on_CalcRongZhong1()
{
    double pfRongZhong1 = 0;
    double pfShaZhong1 = 0;
    double pfGuLiaoZhong1 = 0;
    double pfWaiJiaJizhong1 = 0;
    double pfFenLiaoZhong1 = 0;
    for(int i = 0; i < strList1.count(); i++){
        pfRongZhong1 += pflistEdit1.at(i)->text().toDouble();

        if(matList1.at(i).contains("砂")){
            pfShaZhong1 += pflistEdit1.at(i)->text().toDouble();
        }
        if(matList1.at(i).contains("砂") || matList1.at(i).contains("石")){
            pfGuLiaoZhong1 += pflistEdit1.at(i)->text().toDouble();
        }
        if(matList1.at(i).contains("剂")){
            pfWaiJiaJizhong1 += pflistEdit1.at(i)->text().toDouble();
        }
        if(matList1.at(i).contains("粉") || matList1.at(i).contains("煤") || matList1.at(i).contains("泥")){
            pfFenLiaoZhong1 += pflistEdit1.at(i)->text().toDouble();
        }
    }
    pflistEdit1.at(strList1.count())->setText(QString::number(pfRongZhong1));
    pflistEdit1.at(strList1.count()+1)->setText(QString::number(pfShaZhong1/pfGuLiaoZhong1*100,'f',2));
    pflistEdit1.at(strList1.count()+2)->setText(QString::number(pfWaiJiaJizhong1/pfFenLiaoZhong1*100,'f',2));
}

void peihebitongzhidanDlg::on_CalcRongZhong2()
{
    double pfRongZhong2 = 0;
    double pfShaZhong2 = 0;
    double pfGuLiaoZhong2 = 0;
    double pfWaiJiaJizhong2 = 0;
    double pfFenLiaoZhong2 = 0;
    for(int i = 0; i < strList2.count(); i++){
        pfRongZhong2 += pflistEdit2.at(i)->text().toDouble();

        if(matList2.at(i).contains("砂")){
            pfShaZhong2 += pflistEdit2.at(i)->text().toDouble();
        }
        if(matList2.at(i).contains("砂") || matList2.at(i).contains("石")){
            pfGuLiaoZhong2 += pflistEdit2.at(i)->text().toDouble();
        }
        if(matList2.at(i).contains("剂")){
            pfWaiJiaJizhong2 += pflistEdit2.at(i)->text().toDouble();
        }
        if(matList2.at(i).contains("粉") || matList2.at(i).contains("煤") || matList2.at(i).contains("泥")){
            pfFenLiaoZhong2 += pflistEdit2.at(i)->text().toDouble();
        }
    }
    pflistEdit2.at(strList2.count())->setText(QString::number(pfRongZhong2));
    pflistEdit2.at(strList2.count()+1)->setText(QString::number(pfShaZhong2/pfGuLiaoZhong2*100,'f',2));
    pflistEdit2.at(strList2.count()+2)->setText(QString::number(pfWaiJiaJizhong2/pfFenLiaoZhong2*100,'f',2));
}

void peihebitongzhidanDlg::on_CalcRongZhong3()
{
    double pfRongZhong3 = 0;
    double pfShaZhong3 = 0;
    double pfGuLiaoZhong3 = 0;
    double pfWaiJiaJizhong3 = 0;
    double pfFenLiaoZhong3 = 0;
    for(int i = 0; i < strList3.count(); i++){
        pfRongZhong3 += pflistEdit3.at(i)->text().toDouble();

        if(matList3.at(i).contains("砂")){
            pfShaZhong3 += pflistEdit3.at(i)->text().toDouble();
        }
        if(matList3.at(i).contains("砂") || matList3.at(i).contains("石")){
            pfGuLiaoZhong3 += pflistEdit3.at(i)->text().toDouble();
        }
        if(matList3.at(i).contains("剂")){
            pfWaiJiaJizhong3 += pflistEdit3.at(i)->text().toDouble();
        }
        if(matList3.at(i).contains("粉") || matList3.at(i).contains("煤") || matList3.at(i).contains("泥")){
            pfFenLiaoZhong3 += pflistEdit3.at(i)->text().toDouble();
        }
    }
    pflistEdit3.at(strList3.count())->setText(QString::number(pfRongZhong3));
    pflistEdit3.at(strList3.count()+1)->setText(QString::number(pfShaZhong3/pfGuLiaoZhong3*100,'f',2));
    pflistEdit3.at(strList3.count()+2)->setText(QString::number(pfWaiJiaJizhong3/pfFenLiaoZhong3*100,'f',2));
}

void peihebitongzhidanDlg::on_CalcRongZhong4()
{
    double pfRongZhong4 = 0;
    double pfShaZhong4 = 0;
    double pfGuLiaoZhong4 = 0;
    double pfWaiJiaJizhong4 = 0;
    double pfFenLiaoZhong4 = 0;
    for(int i = 0; i < strList4.count(); i++){
        pfRongZhong4 += pflistEdit4.at(i)->text().toDouble();

        if(matList4.at(i).contains("砂")){
            pfShaZhong4 += pflistEdit4.at(i)->text().toDouble();
        }
        if(matList4.at(i).contains("砂") || matList4.at(i).contains("石")){
            pfGuLiaoZhong4 += pflistEdit4.at(i)->text().toDouble();
        }
        if(matList4.at(i).contains("剂")){
            pfWaiJiaJizhong4 += pflistEdit4.at(i)->text().toDouble();
        }
        if(matList4.at(i).contains("粉") || matList4.at(i).contains("煤") || matList4.at(i).contains("泥")){
            pfFenLiaoZhong4 += pflistEdit4.at(i)->text().toDouble();
        }
    }
    pflistEdit4.at(strList4.count())->setText(QString::number(pfRongZhong4));
    pflistEdit4.at(strList4.count()+1)->setText(QString::number(pfShaZhong4/pfGuLiaoZhong4*100,'f',2));
    pflistEdit4.at(strList4.count()+2)->setText(QString::number(pfWaiJiaJizhong4/pfFenLiaoZhong4*100,'f',2));
}

void peihebitongzhidanDlg::on_fourBtn()
{
    if(fourcheckBox->checkState() == 2){
        QString chaxunSQL = QString("select TaskNumber 任务单号,Customer 客户名称,Engineering 工程名称,StrengthGrade 强度等级,Template 配合比模板,PouringPosition 浇筑部位,\
                                    PouringMethod 浇筑方法,PlannedQuantity 计划方量,Slump 坍落度,Contacts 联系人,ContactNumber 联系电话,Remarks 备注,SupplyTime 供货时间,NoticeNo 通知单号 \
                                    from ProductionTaskList where WhetherCheck='是' and WhetherSend='是' and WhetherInvalid='' and WhetherReceive='是' and TzdCheck='是' \
                                    and TzdSend='是' and TaskNumber between '%1' and '%2';")
                        .arg(fourdatetime1->dateTime().toString("yyyyMMdd000"),fourdatetime2->dateTime().toString("yyyyMMdd999"));
        db.showview(chaxunSQL,fourview,&fourmodel);
    }else{
        db.showview(SQL4,fourview,&fourmodel);
    }
}

void peihebitongzhidanDlg::on_fiveFindBtn()
{
    QString gongcheng,renwudan,jizu;
    if(fiveGongChengCheckBox->checkState() == 2){
        gongcheng = QString(" and Engineering = '%1'").arg(fiveGongChengCombox->currentText());
    }
    if(fiveRenWuDanCheckBox->checkState() == 2){
        renwudan = QString(" and rwID = '%1'").arg(fiveRenWuDanCombox->currentText());
    }
    if(fiveUnitCheckBox->checkState() == 2){
        jizu = QString(" and StateNo = '%1'").arg(fiveUnitCombox->currentText());
    }

    QString searchSQL = QString("select rwID 任务编号,Engineering 工程名称,matChang 修改内容,StateNo 搅拌站号,user 修改人,changTime 修改时间 from rwPeiFangChangeRecord \
                                where changTime between '%1' and '%2' %3 %4 %5 ")
        .arg(fivedatetime1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),fivedatetime2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),gongcheng,renwudan,jizu);
    db.showview(searchSQL,fiveview,&fivemodel);
}

void peihebitongzhidanDlg::on_fiveDateChange()
{
    QString fillGongChengSQL = QString("select Engineering from rwPeiFangChangeRecord where changTime between '%1' and '%2' group by Engineering;")
            .arg(fivedatetime1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),fivedatetime2->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
    QString fillRenWuDanSQL = QString("select rwID from rwPeiFangChangeRecord where changTime between '%1' and '%2' group by rwID;")
            .arg(fivedatetime1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),fivedatetime2->dateTime().toString("yyyy-MM-dd hh:mm:ss"));

    fiveGongChengCombox->clear();
    fiveRenWuDanCombox->clear();

    db.sql_fillComboBoxItem(fillGongChengSQL,fiveGongChengCombox);
    db.sql_fillComboBoxItem(fillRenWuDanSQL,fiveRenWuDanCombox);
}

void peihebitongzhidanDlg::ShowSupplyclick()
{
    if(onetzdNumberLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请新增一个通知单号"),0,0,0);
        return;
    }

    int row = view1->currentIndex().row();
    TaskListLineEdit->setText(model1->item(row,0)->text());
    CustomerLineEdit->setText(model1->item(row,1)->text());
    EngineerLineEdit->setText(model1->item(row,2)->text());
    StrengthGradeLineEdit->setText(model1->item(row,3)->text());
    PourPositionLineEdit->setText(model1->item(row,5)->text());
    PourMethodLineEdit->setText(model1->item(row,6)->text());
    SlumpLineEdit->setText(model1->item(row,8)->text());
    ContactLineEdit->setText(model1->item(row,9)->text());
    TelephoneLineEdit->setText(model1->item(row,10)->text());
    TaskRemarksLineEdit->setText(model1->item(row,11)->text());
    SupplyTimeLineEdit->setText(model1->item(row,12)->text());

    disconnect(PhbTemplateCombox,SIGNAL(currentTextChanged(QString)),this,SLOT(PhbTemplateComboxRespones()));
    QString fillComBox = QString("select PhbNumber from PEIFANG1 where PhbNumber like '%%1%';").arg(model1->item(row,3)->text().section(" ",0,0));
    PhbTemplateCombox->clear();
    db.sql_fillComboBoxItem(fillComBox,PhbTemplateCombox);
    connect(PhbTemplateCombox,SIGNAL(currentTextChanged(QString)),this,SLOT(PhbTemplateComboxRespones()));
}

void peihebitongzhidanDlg::ShowSupplyclick2()
{
    saveAction->setEnabled(false);
    updateAction->setEnabled(true);
    deleteAction->setEnabled(true);
    checkAction->setEnabled(true);
    PhbTemplateCombox->setEnabled(false);

    int row = twoview->currentIndex().row();
    TaskListLineEdit->setText(twomodel->item(row,0)->text());
    CustomerLineEdit->setText(twomodel->item(row,1)->text());
    EngineerLineEdit->setText(twomodel->item(row,2)->text());
    StrengthGradeLineEdit->setText(twomodel->item(row,3)->text());
    PourPositionLineEdit->setText(twomodel->item(row,5)->text());
    PourMethodLineEdit->setText(twomodel->item(row,6)->text());
    SlumpLineEdit->setText(twomodel->item(row,8)->text());
    ContactLineEdit->setText(twomodel->item(row,9)->text());
    TelephoneLineEdit->setText(twomodel->item(row,10)->text());
    TaskRemarksLineEdit->setText(twomodel->item(row,11)->text());
    SupplyTimeLineEdit->setText(twomodel->item(row,12)->text());
    onetzdNumberLineEdit->setText(twomodel->item(row,13)->text());

    disconnect(PhbTemplateCombox,SIGNAL(currentTextChanged(QString)),this,SLOT(PhbTemplateComboxRespones()));
    QString fillComBox = QString("select PhbNumber from PEIFANG1 where PhbNumber like '%%1%';").arg(twomodel->item(row,3)->text().section(" ",0,0));
    PhbTemplateCombox->clear();
    db.sql_fillComboBoxItem(fillComBox,PhbTemplateCombox);
    connect(PhbTemplateCombox,SIGNAL(currentTextChanged(QString)),this,SLOT(PhbTemplateComboxRespones()));

    PhbTemplateCombox->setCurrentText(twomodel->item(row,4)->text());

    QString searchSQL1 = QString("select * from rwPEIFANG where TaskList='%1' and StateNo='1'").arg(TaskListLineEdit->text());
    if(db.row_count(searchSQL1) != 0){
        for(int i = 0; i < strList1.count(); i++){
            pflistEdit1.at(i)->setText(db.sql_fetchrow_plus(searchSQL1,strList1.at(i).toInt()));
        }
    }
    StirTime1LineEdit->setText(db.sql_fetchrow_plus(searchSQL1,21));
    WuShui1LineEdit->setText(db.sql_fetchrow_plus(searchSQL1,23));


    QString searchSQL2 = QString("select * from rwPEIFANG where TaskList='%1' and StateNo='2'").arg(TaskListLineEdit->text());
    if(db.row_count(searchSQL2) != 0){
        for(int i = 0; i < strList2.count(); i++){
            pflistEdit2.at(i)->setText(db.sql_fetchrow_plus(searchSQL2,strList2.at(i).toInt()));
        }
    }
    StirTime2LineEdit->setText(db.sql_fetchrow_plus(searchSQL2,21));
    WuShui2LineEdit->setText(db.sql_fetchrow_plus(searchSQL2,23));

    tabWidget->setCurrentIndex(0);
}

void peihebitongzhidanDlg::ShowSupplyclick3()
{
    saveAction->setEnabled(false);
    updateAction->setEnabled(true);
    deleteAction->setEnabled(false);
    checkAction->setEnabled(false);
    sendAction->setEnabled(true);
    PhbTemplateCombox->setEnabled(true);

    int row = threeview->currentIndex().row();
    TaskListLineEdit->setText(threemodel->item(row,0)->text());
    CustomerLineEdit->setText(threemodel->item(row,1)->text());
    EngineerLineEdit->setText(threemodel->item(row,2)->text());
    StrengthGradeLineEdit->setText(threemodel->item(row,3)->text());
    PourPositionLineEdit->setText(threemodel->item(row,5)->text());
    PourMethodLineEdit->setText(threemodel->item(row,6)->text());
    SlumpLineEdit->setText(threemodel->item(row,8)->text());
    ContactLineEdit->setText(threemodel->item(row,9)->text());
    TelephoneLineEdit->setText(threemodel->item(row,10)->text());
    TaskRemarksLineEdit->setText(threemodel->item(row,11)->text());
    SupplyTimeLineEdit->setText(threemodel->item(row,12)->text());
    onetzdNumberLineEdit->setText(threemodel->item(row,13)->text());

    disconnect(PhbTemplateCombox,SIGNAL(currentTextChanged(QString)),this,SLOT(PhbTemplateComboxRespones()));
    QString fillComBox = QString("select PhbNumber from PEIFANG1 where PhbNumber like '%%1%';").arg(threemodel->item(row,3)->text().section(" ",0,0));
    PhbTemplateCombox->clear();
    db.sql_fillComboBoxItem(fillComBox,PhbTemplateCombox);
    connect(PhbTemplateCombox,SIGNAL(currentTextChanged(QString)),this,SLOT(PhbTemplateComboxRespones()));

    PhbTemplateCombox->setCurrentText(threemodel->item(row,4)->text());

    QString searchSQL1 = QString("select * from rwPEIFANG where TaskList='%1' and StateNo='1'").arg(TaskListLineEdit->text());
    if(db.row_count(searchSQL1) != 0){
        for(int i = 0; i < strList1.count(); i++){
            pflistEdit1.at(i)->setText(db.sql_fetchrow_plus(searchSQL1,strList1.at(i).toInt()));
        }
    }
    StirTime1LineEdit->setText(db.sql_fetchrow_plus(searchSQL1,21));
    WuShui1LineEdit->setText(db.sql_fetchrow_plus(searchSQL1,23));


    QString searchSQL2 = QString("select * from rwPEIFANG where TaskList='%1' and StateNo='2'").arg(TaskListLineEdit->text());
    if(db.row_count(searchSQL2) != 0){
        for(int i = 0; i < strList2.count(); i++){
            pflistEdit2.at(i)->setText(db.sql_fetchrow_plus(searchSQL2,strList2.at(i).toInt()));
        }
    }
    StirTime2LineEdit->setText(db.sql_fetchrow_plus(searchSQL2,21));
    WuShui2LineEdit->setText(db.sql_fetchrow_plus(searchSQL2,23));

    tabWidget->setCurrentIndex(0);
}

void peihebitongzhidanDlg::ShowSupplyclick4()
{
    saveAction->setEnabled(false);
    updateAction->setEnabled(false);
    deleteAction->setEnabled(false);
    checkAction->setEnabled(false);
    sendAction->setEnabled(false);
    PhbTemplateCombox->setEnabled(true);

    int row = fourview->currentIndex().row();
    TaskListLineEdit->setText(fourmodel->item(row,0)->text());
    CustomerLineEdit->setText(fourmodel->item(row,1)->text());
    EngineerLineEdit->setText(fourmodel->item(row,2)->text());
    StrengthGradeLineEdit->setText(fourmodel->item(row,3)->text());
    PourPositionLineEdit->setText(fourmodel->item(row,5)->text());
    PourMethodLineEdit->setText(fourmodel->item(row,6)->text());
    SlumpLineEdit->setText(fourmodel->item(row,8)->text());
    ContactLineEdit->setText(fourmodel->item(row,9)->text());
    TelephoneLineEdit->setText(fourmodel->item(row,10)->text());
    TaskRemarksLineEdit->setText(fourmodel->item(row,11)->text());
    SupplyTimeLineEdit->setText(fourmodel->item(row,12)->text());
    onetzdNumberLineEdit->setText(fourmodel->item(row,13)->text());

    disconnect(PhbTemplateCombox,SIGNAL(currentTextChanged(QString)),this,SLOT(PhbTemplateComboxRespones()));
    QString fillComBox = QString("select PhbNumber from PEIFANG1 where PhbNumber like '%%1%';").arg(fourmodel->item(row,3)->text().section(" ",0,0));
    PhbTemplateCombox->clear();
    db.sql_fillComboBoxItem(fillComBox,PhbTemplateCombox);
    connect(PhbTemplateCombox,SIGNAL(currentTextChanged(QString)),this,SLOT(PhbTemplateComboxRespones()));

    PhbTemplateCombox->setCurrentText(fourmodel->item(row,4)->text());

    QString searchSQL1 = QString("select * from rwPEIFANG where TaskList='%1' and StateNo='1'").arg(TaskListLineEdit->text());
    if(db.row_count(searchSQL1) != 0){
        for(int i = 0; i < strList1.count(); i++){
            pflistEdit1.at(i)->setText(db.sql_fetchrow_plus(searchSQL1,strList1.at(i).toInt()));
        }
    }
    StirTime1LineEdit->setText(db.sql_fetchrow_plus(searchSQL1,21));
    WuShui1LineEdit->setText(db.sql_fetchrow_plus(searchSQL1,23));


    QString searchSQL2 = QString("select * from rwPEIFANG where TaskList='%1' and StateNo='2'").arg(TaskListLineEdit->text());
    if(db.row_count(searchSQL2) != 0){
        for(int i = 0; i < strList2.count(); i++){
            pflistEdit2.at(i)->setText(db.sql_fetchrow_plus(searchSQL2,strList2.at(i).toInt()));
        }
    }
    StirTime2LineEdit->setText(db.sql_fetchrow_plus(searchSQL2,21));
    WuShui2LineEdit->setText(db.sql_fetchrow_plus(searchSQL2,23));

    tabWidget->setCurrentIndex(0);
}

void peihebitongzhidanDlg::createAction()
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
    checkAction->setEnabled(false);
    checkAction->setIcon(QIcon(":/image/check.png"));
    connect(checkAction,SIGNAL(triggered()),this,SLOT(on_checkAction()));
    sendAction = new QAction(tr("下发"),this);
    sendAction->setEnabled(false);
    sendAction->setIcon(QIcon(":/image/send.png"));
    connect(sendAction,SIGNAL(triggered()),this,SLOT(on_sendAction()));
}

void peihebitongzhidanDlg::createTool()
{
    toolBar = new QToolBar;
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar->addAction(newAction);
    toolBar->addAction(saveAction);
    toolBar->addAction(updateAction);
    toolBar->addAction(deleteAction);
    if(whetherCheckSend == "有"){
        //toolBar->addAction(checkAction);
        toolBar->addAction(sendAction);
    }
}
