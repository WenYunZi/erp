#include "peihebimubandlg.h"

extern mymysql db;
extern pubfunc pub;
extern QString whetherCheckSend;
extern myTCPsocket *sockClient;
extern QString userName;

peihebimubanDlg::peihebimubanDlg(QWidget *parent) :
    QDialog(parent)
{
    tabWidget                    = new QTabWidget(this);
    peihebimubanxinxi1           = new QWidget(this);
    peihebimubanxinxi2           = new QWidget(this);
    peihebimubanxinxi3           = new QWidget(this);
    peihebimubanxinxi4           = new QWidget(this);
    PhbUpdateRecordWidget        = new QWidget(this);

    QRegExp rx("^[0-9]*$");
    pReg_zhengshu = new QRegExpValidator(rx, this);

    creatTabPage1();
    creatTabPage2();
    creatTabPage3();
    creatTabPage4();
    creatTabPageChange();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tabWidget);
    layout->setSpacing(0);
}

peihebimubanDlg::~peihebimubanDlg()
{

}

void peihebimubanDlg::refresh()
{

}

void peihebimubanDlg::keyPressEvent(QKeyEvent *event)
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

void peihebimubanDlg::creatTabPage1()
{
    createAction();
    createTool();

    QString searchMat = QString("SELECT ERPMaterial,CorrespondingField from UnitMaterialCorrespondsToERPMaterial where ProductionUnit = '1#机组'");
    QList<QStringList> MatList = db.sql_result(searchMat);
    int count = MatList.count();
    QString subStr;
    for(int i = 0; i<count; i++){
        if(MatList.at(i).count() == 2){
            subStr.append(QString("Mat%1 %2,").arg(MatList[i][1],MatList[i][0]));
        }
    }
    subStr = subStr.left(subStr.length()-1);

    SQL1 = QString("select IDENT 配比编号,PhbNumber 模板名称,NAME 强度等级,jbTime 搅拌时间,WuShui 污水比例,%1 from PEIFANG1 ORDER BY PhbNumber").arg(subStr);

    QLabel *PhbNumLabel = new QLabel(tr("模板编号"),this);
    PhbNumLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *PhbNameLabel = new QLabel(tr("模板名称"),this);
    PhbNameLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *StrenghtGradeLabel = new QLabel(tr("强度等级"),this);
    StrenghtGradeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *PhbListLabel = new QLabel(tr("配比列表"),this);
    PhbListLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    QLabel *StirTimeLabel = new QLabel(tr("搅拌时间"),this);
    StirTimeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *WuShuiLabel = new QLabel(tr("污水比例"),this);
    WuShuiLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

    onePhbNumLineEdit = new QLineEdit(this);
    onePhbNumLineEdit->setReadOnly(true);
    onePhbNumLineEdit->setValidator(pReg_zhengshu);
    onePhbNameLineEdit = new QLineEdit(this);
    onePhbNameLineEdit->setReadOnly(true);
    oneStrenghtGradeLineEdit = new QLineEdit(this);
    oneStirTimeLineEdit = new QLineEdit(this);
    oneStirTimeLineEdit->setValidator(pReg_zhengshu);
    oneWuShuiLineEdit = new QLineEdit(this);
    oneWuShuiLineEdit->setValidator(pReg_zhengshu);

    onePhbListView = new QTableView(this);
    db.showview_num(SQL1,onePhbListView,&onePhbListModel,0);
    connect(onePhbListView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick()));
    for(int i = 0;i<17;i++)
    {
       onePhbListView->setColumnWidth(i,76);
    }

    //1#配合比
    QString phbSQL1 = QString("SELECT UnitMaterial,ERPmaterial,CorrespondingField from UnitMaterialCorrespondsToERPMaterial where ProductionUnit = '1#机组'");
    db.newWidget(phbSQL1,list1,strList1,matList1,pflistEdit1,this);

    for(int i = 0; i < strList1.count(); i++){
        connect(pflistEdit1.at(i),SIGNAL(textChanged(QString)),this,SLOT(on_CalcRongZhong1()));
    }

    QHBoxLayout *hlayout1 = new QHBoxLayout;
    hlayout1->addWidget(PhbNumLabel,0);
    hlayout1->addWidget(onePhbNumLineEdit,1);
    hlayout1->addWidget(PhbNameLabel,0);
    hlayout1->addWidget(onePhbNameLineEdit,1);
    hlayout1->addWidget(StrenghtGradeLabel,0);
    hlayout1->addWidget(oneStrenghtGradeLineEdit,1);
    hlayout1->addWidget(StirTimeLabel,0);
    hlayout1->addWidget(oneStirTimeLineEdit,1);
    hlayout1->addWidget(WuShuiLabel,0);
    hlayout1->addWidget(oneWuShuiLineEdit,1);
    hlayout1->addStretch(3);

    QHBoxLayout *hlayout2 = new QHBoxLayout;
    hlayout2->setSpacing(0);
    hlayout2->setMargin(0);
    for(int i = 0; i < list1.size(); i++){
        hlayout2->addWidget(list1.at(i));
    }

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(toolBar);
    vlayout->addLayout(hlayout1);
    vlayout->addSpacing(8);
    vlayout->addLayout(hlayout2,0);
    vlayout->addSpacing(8);
    vlayout->addWidget(PhbListLabel,0);
    vlayout->addWidget(onePhbListView,1);

    peihebimubanxinxi1->setLayout(vlayout);
    tabWidget->addTab(peihebimubanxinxi1,tr("1#配合比信息"));
}

void peihebimubanDlg::creatTabPage2()
{
    createAction2();
    createTool2();

    QString searchMat = QString("SELECT ERPMaterial,CorrespondingField from UnitMaterialCorrespondsToERPMaterial where ProductionUnit = '2#机组'");
    QList<QStringList> MatList = db.sql_result(searchMat);
    int count = MatList.count();
    QString subStr;
    for(int i = 0; i<count; i++){
        if(MatList.at(i).count() == 2){
            subStr.append(QString("Mat%1 %2,").arg(MatList[i][1],MatList[i][0]));
        }
    }
    subStr = subStr.left(subStr.length()-1);

    SQL2 = QString("select IDENT 配比编号,PhbNumber 模板名称,NAME 强度等级,jbTime 搅拌时间,WuShui 污水比例,%1 FROM PEIFANG2 ORDER BY PhbNumber").arg(subStr);

    QLabel *PhbNumLabel = new QLabel(tr("模板编号"),this);
    PhbNumLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *PhbNameLabel = new QLabel(tr("模板名称"),this);
    PhbNameLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *StrenghtGradeLabel = new QLabel(tr("强度等级"),this);
    StrenghtGradeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *PhbListLabel = new QLabel(tr("配比列表"),this);
    PhbListLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    QLabel *StirTimeLabel = new QLabel(tr("搅拌时间"),this);
    StirTimeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *WuShuiLabel = new QLabel(tr("污水比例"),this);
    WuShuiLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

    twoPhbNumLineEdit = new QLineEdit(this);
    twoPhbNumLineEdit->setReadOnly(true);
    twoPhbNumLineEdit->setValidator(pReg_zhengshu);
    twoPhbNameLineEdit = new QLineEdit(this);
    twoStrenghtGradeLineEdit = new QLineEdit(this);
    twoStirTimeLineEdit = new QLineEdit(this);
    twoStirTimeLineEdit->setValidator(pReg_zhengshu);
    twoWuShuiLineEdit = new QLineEdit(this);
    twoWuShuiLineEdit->setValidator(pReg_zhengshu);

    twoPhbListView = new QTableView(this);
    db.showview_num(SQL2,twoPhbListView,&twoPhbListModel,0);
    connect(twoPhbListView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick2()));
    for(int i = 0;i<18;i++)
    {
       twoPhbListView->setColumnWidth(i,72);
    }

    //2#配合比
    QString phbSQL2 = QString("SELECT UnitMaterial,ERPmaterial,CorrespondingField from UnitMaterialCorrespondsToERPMaterial where ProductionUnit = '2#机组'");
    db.newWidget(phbSQL2,list2,strList2,matList2,pflistEdit2,this);

    for(int i = 0; i < strList2.count(); i++){
        connect(pflistEdit2.at(i),SIGNAL(textChanged(QString)),this,SLOT(on_CalcRongZhong2()));
    }

    QHBoxLayout *hlayout1 = new QHBoxLayout;
    hlayout1->addWidget(PhbNumLabel,0);
    hlayout1->addWidget(twoPhbNumLineEdit,1);
    hlayout1->addWidget(PhbNameLabel,0);
    hlayout1->addWidget(twoPhbNameLineEdit,1);
    hlayout1->addWidget(StrenghtGradeLabel,0);
    hlayout1->addWidget(twoStrenghtGradeLineEdit,1);
    hlayout1->addWidget(StirTimeLabel,0);
    hlayout1->addWidget(twoStirTimeLineEdit,1);
    hlayout1->addWidget(WuShuiLabel,0);
    hlayout1->addWidget(twoWuShuiLineEdit,1);
    hlayout1->addStretch(3);

    QHBoxLayout *hlayout2 = new QHBoxLayout;
    hlayout2->setSpacing(0);
    hlayout2->setMargin(0);
    for(int i = 0; i < list2.size(); i++){
        hlayout2->addWidget(list2.at(i));
    }

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(toolBar2);
    vlayout->addLayout(hlayout1);
    vlayout->addSpacing(8);
    vlayout->addLayout(hlayout2,0);
    vlayout->addSpacing(8);
    vlayout->addWidget(PhbListLabel,0);
    vlayout->addWidget(twoPhbListView,1);

    peihebimubanxinxi2->setLayout(vlayout);
    tabWidget->addTab(peihebimubanxinxi2,tr("2#配合比信息"));
}

void peihebimubanDlg::creatTabPage3()
{
    createAction3();
    createTool3();

    QString searchMat = QString("SELECT ERPMaterial,CorrespondingField from UnitMaterialCorrespondsToERPMaterial where ProductionUnit = '3#机组'");
    QList<QStringList> MatList = db.sql_result(searchMat);
    int count = MatList.count();
    QString subStr;
    for(int i = 0; i<count; i++){
        if(MatList.at(i).count() == 2){
            subStr.append(QString("Mat%1 %2,").arg(MatList[i][1],MatList[i][0]));
        }
    }
    subStr = subStr.left(subStr.length()-1);

    SQL3 = QString("select IDENT 配比编号,PhbNumber 模板名称,NAME 强度等级,jbTime 搅拌时间,WuShui 污水比例,%1 FROM PEIFANG3 ORDER BY PhbNumber").arg(subStr);

    QLabel *PhbNumLabel = new QLabel(tr("模板编号"),this);
    PhbNumLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *PhbNameLabel = new QLabel(tr("模板名称"),this);
    PhbNameLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *StrenghtGradeLabel = new QLabel(tr("强度等级"),this);
    StrenghtGradeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *PhbListLabel = new QLabel(tr("配比列表"),this);
    PhbListLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    QLabel *StirTimeLabel = new QLabel(tr("搅拌时间"),this);
    StirTimeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *WuShuiLabel = new QLabel(tr("污水比例"),this);
    WuShuiLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

    threePhbNumLineEdit = new QLineEdit(this);
    threePhbNumLineEdit->setReadOnly(true);
    threePhbNumLineEdit->setValidator(pReg_zhengshu);
    threePhbNameLineEdit = new QLineEdit(this);
    threeStrenghtGradeLineEdit = new QLineEdit(this);
    threeStirTimeLineEdit = new QLineEdit(this);
    threeStirTimeLineEdit->setValidator(pReg_zhengshu);
    threeWuShuiLineEdit = new QLineEdit(this);
    threeWuShuiLineEdit->setValidator(pReg_zhengshu);

    threePhbListView = new QTableView(this);
    db.showview_num(SQL3,threePhbListView,&threePhbListModel,0);
    connect(threePhbListView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick3()));
    for(int i = 0;i<18;i++)
    {
       threePhbListView->setColumnWidth(i,72);
    }

    //3#配合比
    QString phbSQL3 = QString("SELECT UnitMaterial,ERPmaterial,CorrespondingField from UnitMaterialCorrespondsToERPMaterial where ProductionUnit = '3#机组'");
    db.newWidget(phbSQL3,list3,strList3,matList3,pflistEdit3,this);

    for(int i = 0; i < strList3.count(); i++){
        connect(pflistEdit3.at(i),SIGNAL(textChanged(QString)),this,SLOT(on_CalcRongZhong3()));
    }

    QHBoxLayout *hlayout1 = new QHBoxLayout;
    hlayout1->addWidget(PhbNumLabel,0);
    hlayout1->addWidget(threePhbNumLineEdit,1);
    hlayout1->addWidget(PhbNameLabel,0);
    hlayout1->addWidget(threePhbNameLineEdit,1);
    hlayout1->addWidget(StrenghtGradeLabel,0);
    hlayout1->addWidget(threeStrenghtGradeLineEdit,1);
    hlayout1->addWidget(StirTimeLabel,0);
    hlayout1->addWidget(threeStirTimeLineEdit,1);
    hlayout1->addWidget(WuShuiLabel,0);
    hlayout1->addWidget(threeWuShuiLineEdit,1);
    hlayout1->addStretch(2);

    QHBoxLayout *hlayout2 = new QHBoxLayout;
    hlayout2->setSpacing(0);
    hlayout2->setMargin(0);
    for(int i = 0; i < list3.size(); i++){
        hlayout2->addWidget(list3.at(i));
    }

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(toolBar3);
    vlayout->addLayout(hlayout1);
    vlayout->addSpacing(8);
    vlayout->addLayout(hlayout2,0);
    vlayout->addSpacing(8);
    vlayout->addWidget(PhbListLabel,0);
    vlayout->addWidget(threePhbListView,1);

    peihebimubanxinxi3->setLayout(vlayout);
    tabWidget->addTab(peihebimubanxinxi3,tr("3#配合比信息"));
}

void peihebimubanDlg::creatTabPage4()
{
    createAction4();
    createTool4();

    QString searchMat = QString("SELECT ERPMaterial,CorrespondingField from UnitMaterialCorrespondsToERPMaterial where ProductionUnit = '4#机组'");
    QList<QStringList> MatList = db.sql_result(searchMat);
    int count = MatList.count();
    QString subStr;
    for(int i = 0; i<count; i++){
        if(MatList.at(i).count() == 2){
            subStr.append(QString("Mat%1 %2,").arg(MatList[i][1],MatList[i][0]));
        }
    }
    subStr = subStr.left(subStr.length()-1);

    SQL4 = QString("select IDENT 配比编号,PhbNumber 模板名称,NAME 强度等级,jbTime 搅拌时间,WuShui 污水比例,%1 FROM PEIFANG4 ORDER BY PhbNumber").arg(subStr);

    QLabel *PhbNumLabel = new QLabel(tr("模板编号"),this);
    PhbNumLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *PhbNameLabel = new QLabel(tr("模板名称"),this);
    PhbNameLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *StrenghtGradeLabel = new QLabel(tr("强度等级"),this);
    StrenghtGradeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *PhbListLabel = new QLabel(tr("配比列表"),this);
    PhbListLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    QLabel *StirTimeLabel = new QLabel(tr("搅拌时间"),this);
    StirTimeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *WuShuiLabel = new QLabel(tr("污水比例"),this);
    WuShuiLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

    three2PhbNumLineEdit = new QLineEdit(this);
    three2PhbNumLineEdit->setReadOnly(true);
    three2PhbNumLineEdit->setValidator(pReg_zhengshu);
    three2PhbNameLineEdit = new QLineEdit(this);
    three2StrenghtGradeLineEdit = new QLineEdit(this);
    three2StirTimeLineEdit = new QLineEdit(this);
    three2StirTimeLineEdit->setValidator(pReg_zhengshu);
    three2WuShuiLineEdit = new QLineEdit(this);
    three2WuShuiLineEdit->setValidator(pReg_zhengshu);

    three2PhbListView = new QTableView(this);
    db.showview_num(SQL4,three2PhbListView,&three2PhbListModel,0);
    connect(three2PhbListView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick4()));
    for(int i = 0;i<18;i++)
    {
       three2PhbListView->setColumnWidth(i,72);
    }

    //4#配合比
    QString phbSQL4 = QString("SELECT UnitMaterial,ERPmaterial,CorrespondingField from UnitMaterialCorrespondsToERPMaterial where ProductionUnit = '4#机组'");
    db.newWidget(phbSQL4,list4,strList4,matList4,pflistEdit4,this);

    for(int i = 0; i < strList4.count(); i++){
        connect(pflistEdit4.at(i),SIGNAL(textChanged(QString)),this,SLOT(on_CalcRongZhong4()));
    }

    QHBoxLayout *hlayout1 = new QHBoxLayout;
    hlayout1->addWidget(PhbNumLabel,0);
    hlayout1->addWidget(three2PhbNumLineEdit,1);
    hlayout1->addWidget(PhbNameLabel,0);
    hlayout1->addWidget(three2PhbNameLineEdit,1);
    hlayout1->addWidget(StrenghtGradeLabel,0);
    hlayout1->addWidget(three2StrenghtGradeLineEdit,1);
    hlayout1->addWidget(StirTimeLabel,0);
    hlayout1->addWidget(three2StirTimeLineEdit,1);
    hlayout1->addWidget(WuShuiLabel,0);
    hlayout1->addWidget(three2WuShuiLineEdit,1);
    hlayout1->addStretch(2);

    QHBoxLayout *hlayout2 = new QHBoxLayout;
    hlayout2->setSpacing(0);
    hlayout2->setMargin(0);
    for(int i = 0; i < list4.size(); i++){
        hlayout2->addWidget(list4.at(i));
    }

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(toolBar4);
    vlayout->addLayout(hlayout1);
    vlayout->addSpacing(8);
    vlayout->addLayout(hlayout2,0);
    vlayout->addSpacing(8);
    vlayout->addWidget(PhbListLabel,0);
    vlayout->addWidget(three2PhbListView,1);

    peihebimubanxinxi4->setLayout(vlayout);
    tabWidget->addTab(peihebimubanxinxi4,tr("4#配合比信息"));
}

void peihebimubanDlg::creatTabPageChange()
{
    QLabel *DateTimeLabel = new QLabel(tr("修改时间"),this);
    DateTimeLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *FuHaoLabel = new QLabel(tr("--"),this);
    FuHaoLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *UnitLabel = new QLabel(tr("机组号"),this);
    UnitLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

    fourDateTimeEdit1 = new QDateTimeEdit(this);
    fourDateTimeEdit1->setDate(QDate::currentDate());
    fourDateTimeEdit1->setCalendarPopup(true);

    fourDateTimeEdit2 = new QDateTimeEdit(this);
    fourDateTimeEdit2->setDate(QDate::currentDate().addDays(1));
    fourDateTimeEdit2->setCalendarPopup(true);

    fourPhbNameCheckBox = new QCheckBox(tr("配合比模板名称"),this);

    fourPhbNameCombox = new myComboBox(this);
    db.sql_fillComboBoxItem("select PhbNumber from PEIFANG1",fourPhbNameCombox);

    fourUnitNoCombox = new QComboBox(this);
    db.sql_fillComboBoxItem("select UnitName from UnitSetting",fourUnitNoCombox);
    fourUnitNoCombox->setCurrentIndex(1);

    fourFindBtn = new QPushButton(tr("查找"),this);
    fourFindBtn->setFixedWidth(120);
    connect(fourFindBtn,SIGNAL(clicked()),this,SLOT(on_fourFindBtn()));

    fourUpdateView = new QTableView(this);
    db.showview("select phbName 配合比模板名称,updateMan 修改人,neirong 内容,time 修改时间 from PEIFANG_xiugai1 limit 0",fourUpdateView,&fourUpdateModel);
    fourUpdateView->setColumnWidth(0,150);
    fourUpdateView->setColumnWidth(2,150);
    fourUpdateView->setColumnWidth(3,150);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(DateTimeLabel,0);
    hlayout->addWidget(fourDateTimeEdit1,0);
    hlayout->addWidget(FuHaoLabel,0);
    hlayout->addWidget(fourDateTimeEdit2,0);
    hlayout->addWidget(fourPhbNameCheckBox,0);
    hlayout->addWidget(fourPhbNameCombox,2);
    hlayout->addWidget(UnitLabel,0);
    hlayout->addWidget(fourUnitNoCombox,1);
    hlayout->addWidget(fourFindBtn,0);
    hlayout->addStretch(4);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(fourUpdateView);

    PhbUpdateRecordWidget->setLayout(vlayout);
    tabWidget->addTab(PhbUpdateRecordWidget,tr("配合比修改记录"));
}

void peihebimubanDlg::createAction()
{
    newAction = new QAction(tr("新增"),this);
    newAction->setIcon(QIcon(":/image/new.png"));
    connect(newAction,SIGNAL(triggered()),this,SLOT(on_newAction()));
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
}

void peihebimubanDlg::createTool()
{
    toolBar = new QToolBar(this);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar->addAction(newAction);
    toolBar->addAction(saveAction);
    toolBar->addAction(updateAction);
    toolBar->addAction(deleteAction);
}

void peihebimubanDlg::createAction2()
{
    newAction2 = new QAction(tr("新增"),this);
    newAction2->setIcon(QIcon(":/image/new.png"));
    connect(newAction2,SIGNAL(triggered()),this,SLOT(on_newAction2()));
    saveAction2 = new QAction(tr("保存"),this);
    saveAction2->setEnabled(false);
    saveAction2->setIcon(QIcon(":/image/save.png"));
    connect(saveAction2,SIGNAL(triggered()),this,SLOT(on_saveAction2()));
    updateAction2 = new QAction(tr("修改"),this);
    updateAction2->setEnabled(false);
    updateAction2->setIcon(QIcon(":/image/update.png"));
    connect(updateAction2,SIGNAL(triggered()),this,SLOT(on_updateAction2()));
    deleteAction2 = new QAction(tr("删除"),this);
    deleteAction2->setEnabled(false);
    deleteAction2->setIcon(QIcon(":/image/delete.png"));
    connect(deleteAction2,SIGNAL(triggered()),this,SLOT(on_deleteAction2()));
}

void peihebimubanDlg::createTool2()
{
    toolBar2 = new QToolBar(this);
    toolBar2->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar2->addAction(newAction2);
    toolBar2->addAction(saveAction2);
    toolBar2->addAction(updateAction2);
    toolBar2->addAction(deleteAction2);
}

void peihebimubanDlg::createAction3()
{
    newAction3 = new QAction(tr("新增"),this);
    newAction3->setIcon(QIcon(":/image/new.png"));
    connect(newAction3,SIGNAL(triggered()),this,SLOT(on_newAction3()));
    saveAction3 = new QAction(tr("保存"),this);
    saveAction3->setEnabled(false);
    saveAction3->setIcon(QIcon(":/image/save.png"));
    connect(saveAction3,SIGNAL(triggered()),this,SLOT(on_saveAction3()));
    updateAction3 = new QAction(tr("修改"),this);
    updateAction3->setEnabled(false);
    updateAction3->setIcon(QIcon(":/image/update.png"));
    connect(updateAction3,SIGNAL(triggered()),this,SLOT(on_updateAction3()));
    deleteAction3 = new QAction(tr("删除"),this);
    deleteAction3->setEnabled(false);
    deleteAction3->setIcon(QIcon(":/image/delete.png"));
    connect(deleteAction3,SIGNAL(triggered()),this,SLOT(on_deleteAction3()));
}

void peihebimubanDlg::createTool3()
{
    toolBar3 = new QToolBar(this);
    toolBar3->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar3->addAction(newAction3);
    toolBar3->addAction(saveAction3);
    toolBar3->addAction(updateAction3);
    toolBar3->addAction(deleteAction3);
}

void peihebimubanDlg::createAction4()
{
    newAction4 = new QAction(tr("新增"),this);
    newAction4->setIcon(QIcon(":/image/new.png"));
    connect(newAction4,SIGNAL(triggered()),this,SLOT(on_newAction4()));
    saveAction4 = new QAction(tr("保存"),this);
    saveAction4->setEnabled(false);
    saveAction4->setIcon(QIcon(":/image/save.png"));
    connect(saveAction4,SIGNAL(triggered()),this,SLOT(on_saveAction4()));
    updateAction4 = new QAction(tr("修改"),this);
    updateAction4->setEnabled(false);
    updateAction4->setIcon(QIcon(":/image/update.png"));
    connect(updateAction4,SIGNAL(triggered()),this,SLOT(on_updateAction4()));
    deleteAction4 = new QAction(tr("删除"),this);
    deleteAction4->setEnabled(false);
    deleteAction4->setIcon(QIcon(":/image/delete.png"));
    connect(deleteAction4,SIGNAL(triggered()),this,SLOT(on_deleteAction4()));
}

void peihebimubanDlg::createTool4()
{
    toolBar4 = new QToolBar(this);
    toolBar4->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar4->addAction(newAction4);
    toolBar4->addAction(saveAction4);
    toolBar4->addAction(updateAction4);
    toolBar4->addAction(deleteAction4);
}


void peihebimubanDlg::on_newAction()
{
    saveAction->setEnabled(true);
    updateAction->setEnabled(false);
    deleteAction->setEnabled(false);
    onePhbNumLineEdit->setReadOnly(false);
    onePhbNameLineEdit->setReadOnly(false);
    oneWuShuiLineEdit->setText("0");

    onePhbNumLineEdit->clear();
    onePhbNameLineEdit->clear();
    oneStrenghtGradeLineEdit->clear();
    oneStirTimeLineEdit->clear();

    for(int i = 0; i < strList1.count(); i++){
        pflistEdit1.at(i)->clear();
    }
}


void peihebimubanDlg::on_saveAction()
{
    if(oneStirTimeLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("错误"),tr("搅拌时间不能为空"),0,0,0);
        return;
    }
    if(oneWuShuiLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("错误"),tr("污水比例不能为空"),0,0,0);
        return;
    }

    QString matName,matAcount;
    int count = strList1.count();
    for(int i = 0;i<count;i++){
        if(pflistEdit1.at(i)->text().isEmpty()){
            QMessageBox::information(this,tr("错误"),tr("配方值有空值！！！"),0,0,0);
            return;
        }
        matName.append(QString("Mat%1,").arg(strList1[i]));
        matAcount.append(QString("'%1',").arg(pflistEdit1.at(i)->text()));
    }

    QString saveSQL = QString("insert into PEIFANG1 (%1 IDENT,PhbNumber,NAME,jbTime,WuShui) values (%2 '%3','%4','%5','%6','%7');")
            .arg(matName,matAcount,onePhbNumLineEdit->text(),onePhbNameLineEdit->text(),oneStrenghtGradeLineEdit->text(),oneStirTimeLineEdit->text(),oneWuShuiLineEdit->text());
    int res = db.sql_exec(saveSQL);
    if(res == 0){
        db.showview_num(SQL1,onePhbListView,&onePhbListModel,0);
        QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
        return;
    }
}

void peihebimubanDlg::on_updateAction()
{
    if(oneStirTimeLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("错误"),tr("搅拌时间不能为空"),0,0,0);
        return;
    }
    if(oneWuShuiLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("错误"),tr("污水比例不能为空"),0,0,0);
        return;
    }

    int count = strList1.count();
    QString updateSQL = QString("update PEIFANG1 set ");
    for(int i = 0;i<count;i++){
        if(pflistEdit1.at(i)->text().isEmpty()){
            QMessageBox::information(this,tr("错误"),tr("配方值有空值！！！"),0,0,0);
            return;
        }
        QString str = QString("Mat%1='%2',").arg(strList1[i],pflistEdit1.at(i)->text());
        updateSQL.append(str);
    }
    updateSQL = updateSQL.append(QString("jbTime='%1',WuShui='%2',NAME='%3' where PhbNumber='%4'").arg(oneStirTimeLineEdit->text(),oneWuShuiLineEdit->text(),oneStrenghtGradeLineEdit->text(),onePhbNameLineEdit->text()));

    db.sql_exec("begin;");
    int res = db.sql_exec(updateSQL);
    if(res == -1){
        db.sql_exec("rollback;");
        return;
    }

    for(int i = 0;i<count;i++){
        if(pfList.at(i) != pflistEdit1.at(i)->text()){
            QString xiugaineirong = matList1[i]+QString(":")+pfList.at(i)+QString("→")+pflistEdit1.at(i)->text();
            QString insertSQL = QString("insert into PEIFANG_xiugai1 (phbName,updateMan,neirong,time) values ('%1','%2','%3','%4')")
                    .arg(onePhbNameLineEdit->text(),userName,xiugaineirong,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            db.sql_exec(insertSQL);
            if(res == -1){
                db.sql_exec("rollback;");
                return;
            }
        }
    }
    db.sql_exec("commit;");
    db.showview_num(SQL1,onePhbListView,&onePhbListModel,0);
    QMessageBox::information(this,tr("提示信息"),tr("修改成功"),0,0,0);
    return;
}

void peihebimubanDlg::on_deleteAction()
{
    QString deleteSQL = QString("delete from PEIFANG1 where PhbNumber='%1'").arg(onePhbNameLineEdit->text());
    int res = db.sql_exec(deleteSQL.toStdString().data());
    if(res == 0){
        db.showview_num(SQL1,onePhbListView,&onePhbListModel,0);
        QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
        return;
    }
}

void peihebimubanDlg::on_newAction2()
{
    saveAction2->setEnabled(true);
    updateAction2->setEnabled(false);
    deleteAction2->setEnabled(false);
    twoPhbNumLineEdit->setReadOnly(false);
    twoPhbNameLineEdit->setReadOnly(false);
    twoWuShuiLineEdit->setText("0");

    twoPhbNumLineEdit->clear();
    twoPhbNameLineEdit->clear();
    twoStrenghtGradeLineEdit->clear();
    twoStirTimeLineEdit->clear();

    for(int i = 0; i < strList2.count(); i++){
        pflistEdit2.at(i)->clear();
    }
}

void peihebimubanDlg::on_saveAction2()
{
    if(twoStirTimeLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("错误"),tr("搅拌时间不能为空"),0,0,0);
        return;
    }
    if(twoWuShuiLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("错误"),tr("污水比例不能为空"),0,0,0);
        return;
    }

    QString matName,matAcount;
    int count = strList2.count();
    for(int i = 0;i<count;i++){
        if(pflistEdit2.at(i)->text().isEmpty()){
            QMessageBox::information(this,tr("错误"),tr("配方值有空值！！！"),0,0,0);
            return;
        }
        matName.append(QString("Mat%1,").arg(strList2[i]));
        matAcount.append(QString("'%1',").arg(pflistEdit2.at(i)->text()));
    }

    QString saveSQL = QString("INSERT INTO PEIFANG2 (%1 IDENT,PhbNumber,NAME,jbTime,WuShui) VALUES (%2 '%3','%4','%5','%6','%7');")
            .arg(matName,matAcount,twoPhbNumLineEdit->text(),twoPhbNameLineEdit->text(),twoStrenghtGradeLineEdit->text(),twoStirTimeLineEdit->text(),twoWuShuiLineEdit->text());
    int res = db.sql_exec(saveSQL);
    if(res == 0){
        db.showview_num(SQL2,twoPhbListView,&twoPhbListModel,0);
        QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
        return;
    }
}

void peihebimubanDlg::on_updateAction2()
{
    if(twoStirTimeLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("错误"),tr("搅拌时间不能为空"),0,0,0);
        return;
    }
    if(twoWuShuiLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("错误"),tr("污水比例不能为空"),0,0,0);
        return;
    }

    int count = strList2.count();
    QString updateSQL = QString("UPDATE PEIFANG2 SET ");
    for(int i = 0;i<count;i++){
        if(pflistEdit2.at(i)->text().isEmpty()){
            QMessageBox::information(this,tr("错误"),tr("配方值有空值！！！"),0,0,0);
            return;
        }
        QString str = QString("Mat%1='%2',").arg(strList2[i],pflistEdit2.at(i)->text());
        updateSQL.append(str);
    }
    updateSQL = updateSQL.append(QString("jbTime='%1',WuShui='%2',NAME='%3' where PhbNumber='%4'").arg(twoStirTimeLineEdit->text(),twoWuShuiLineEdit->text(),twoStrenghtGradeLineEdit->text(),twoPhbNameLineEdit->text()));

    db.sql_exec("begin;");
    int res = db.sql_exec(updateSQL.toStdString().data());
    if(res == -1){
        db.sql_exec("rollback");
        return;
    }

    for(int i = 0;i<count;i++){
        if(pfList.at(i) != pflistEdit2.at(i)->text()){
            QString xiugaineirong = matList2[i]+QString(":")+pfList.at(i)+QString("→")+pflistEdit2.at(i)->text();
            QString insertSQL = QString("insert into peifang_xiugai2 (phbName,updateMan,neirong,time) values ('%1','%2','%3','%4')")
                    .arg(twoPhbNameLineEdit->text(),userName,xiugaineirong,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            db.sql_exec(insertSQL);
            if(res == -1){
                db.sql_exec("rollback");
                return;
            }
        }
    }
    db.sql_exec("commit");
    db.showview_num(SQL2,twoPhbListView,&twoPhbListModel,0);
    QMessageBox::information(this,tr("提示信息"),tr("修改成功"),0,0,0);
    return;
}

void peihebimubanDlg::on_deleteAction2()
{
    QString deleteSQL = QString("delete from PEIFANG2 where PhbNumber='%1'").arg(twoPhbNameLineEdit->text());
    int res = db.sql_exec(deleteSQL.toStdString().data());
    if(res == 0){
        db.showview_num(SQL2,twoPhbListView,&twoPhbListModel,0);
        QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
        return;
    }
}

void peihebimubanDlg::on_newAction3()
{
    saveAction3->setEnabled(true);
    updateAction3->setEnabled(false);
    deleteAction3->setEnabled(false);
    threePhbNumLineEdit->setReadOnly(false);
    threePhbNameLineEdit->setReadOnly(false);
    threeWuShuiLineEdit->setText("0");

    threePhbNumLineEdit->clear();
    threePhbNameLineEdit->clear();
    threeStrenghtGradeLineEdit->clear();
    threeStirTimeLineEdit->clear();

    for(int i = 0; i < strList3.count(); i++){
        pflistEdit3.at(i)->clear();
    }
}

void peihebimubanDlg::on_saveAction3()
{
    if(threeStirTimeLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("错误"),tr("搅拌时间不能为空"),0,0,0);
        return;
    }
    if(threeWuShuiLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("错误"),tr("污水比例不能为空"),0,0,0);
        return;
    }

    QString matName,matAcount;
    int count = strList3.count();
    for(int i = 0;i<count;i++){
        if(pflistEdit3.at(i)->text().isEmpty()){
            QMessageBox::information(this,tr("错误"),tr("配方值有空值！！！"),0,0,0);
            return;
        }
        matName.append(QString("Mat%1,").arg(strList3[i]));
        matAcount.append(QString("'%1',").arg(pflistEdit3.at(i)->text()));
    }

    QString saveSQL = QString("INSERT INTO PEIFANG3 (%1 IDENT,PhbNumber,NAME,jbTime,WuShui) VALUES (%2 '%3','%4','%5','%6','%7');")
            .arg(matName,matAcount,threePhbNumLineEdit->text(),threePhbNameLineEdit->text(),threeStrenghtGradeLineEdit->text(),threeStirTimeLineEdit->text(),threeWuShuiLineEdit->text());
    int res = db.sql_exec(saveSQL);
    if(res == 0){
        db.showview_num(SQL3,threePhbListView,&threePhbListModel,0);
        QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
        return;
    }
}

void peihebimubanDlg::on_updateAction3()
{
    if(threeStirTimeLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("错误"),tr("搅拌时间不能为空"),0,0,0);
        return;
    }
    if(threeWuShuiLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("错误"),tr("污水比例不能为空"),0,0,0);
        return;
    }

    int count = strList3.count();
    QString updateSQL = QString("UPDATE PEIFANG3 SET ");
    for(int i = 0;i<count;i++){
        if(pflistEdit3.at(i)->text().isEmpty()){
            QMessageBox::information(this,tr("错误"),tr("配方值有空值！！！"),0,0,0);
            return;
        }
        QString str = QString("Mat%1='%2',").arg(strList3[i],pflistEdit3.at(i)->text());
        updateSQL.append(str);
    }
    updateSQL = updateSQL.append(QString("jbTime='%1',WuShui='%2',NAME='%3' where PhbNumber='%4'").arg(threeStirTimeLineEdit->text(),threeWuShuiLineEdit->text(),threeStrenghtGradeLineEdit->text(),threePhbNameLineEdit->text()));

    db.sql_exec("begin;");
    int res = db.sql_exec(updateSQL.toStdString().data());
    if(res == -1){
        db.sql_exec("rollback");
        return;
    }

    for(int i = 0;i<count;i++){
        if(pfList.at(i) != pflistEdit3.at(i)->text()){
            QString xiugaineirong = matList3[i]+QString(":")+pfList.at(i)+QString("→")+pflistEdit3.at(i)->text();
            QString insertSQL = QString("insert into peifang_xiugai3 (phbName,updateMan,neirong,time) values ('%1','%2','%3','%4')")
                    .arg(threePhbNameLineEdit->text(),userName,xiugaineirong,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            db.sql_exec(insertSQL);
            if(res == -1){
                db.sql_exec("rollback");
                return;
            }
        }
    }
    db.sql_exec("commit");
    db.showview_num(SQL3,threePhbListView,&threePhbListModel,0);
    QMessageBox::information(this,tr("提示信息"),tr("修改成功"),0,0,0);
    return;
}

void peihebimubanDlg::on_deleteAction3()
{
    QString deleteSQL = QString("delete from PEIFANG3 where PhbNumber='%1'").arg(threePhbNameLineEdit->text());
    int res = db.sql_exec(deleteSQL);
    if(res == 0){
        db.showview_num(SQL3,threePhbListView,&threePhbListModel,0);
        QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
        return;
    }
}

void peihebimubanDlg::on_newAction4()
{
    saveAction4->setEnabled(true);
    updateAction4->setEnabled(false);
    deleteAction4->setEnabled(false);
    three2PhbNumLineEdit->setReadOnly(false);
    three2PhbNameLineEdit->setReadOnly(false);
    three2WuShuiLineEdit->setText("0");

    three2PhbNumLineEdit->clear();
    three2PhbNameLineEdit->clear();
    three2StrenghtGradeLineEdit->clear();
    three2StirTimeLineEdit->clear();

    for(int i = 0; i < strList4.count(); i++){
        pflistEdit4.at(i)->clear();
    }
}

void peihebimubanDlg::on_saveAction4()
{
    if(three2StirTimeLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("错误"),tr("搅拌时间不能为空"),0,0,0);
        return;
    }
    if(three2WuShuiLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("错误"),tr("污水比例不能为空"),0,0,0);
        return;
    }

    QString matName,matAcount;
    int count = strList4.count();
    for(int i = 0;i<count;i++){
        if(pflistEdit4.at(i)->text().isEmpty()){
            QMessageBox::information(this,tr("错误"),tr("配方值有空值！！！"),0,0,0);
            return;
        }
        matName.append(QString("Mat%1,").arg(strList4[i]));
        matAcount.append(QString("'%1',").arg(pflistEdit4.at(i)->text()));
    }

    QString saveSQL = QString("INSERT INTO PEIFANG4 (%1 IDENT,PhbNumber,NAME,jbTime,WuShui) VALUES (%2 '%3','%4','%5','%6','%7');")
            .arg(matName,matAcount,three2PhbNumLineEdit->text(),three2PhbNameLineEdit->text(),three2StrenghtGradeLineEdit->text(),three2StirTimeLineEdit->text(),three2WuShuiLineEdit->text());
    int res = db.sql_exec(saveSQL);
    if(res == 0){
        db.showview_num(SQL4,three2PhbListView,&three2PhbListModel,0);
        QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
        return;
    }
}

void peihebimubanDlg::on_updateAction4()
{
    if(three2StirTimeLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("错误"),tr("搅拌时间不能为空"),0,0,0);
        return;
    }
    if(three2WuShuiLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("错误"),tr("污水比例不能为空"),0,0,0);
        return;
    }

    int count = strList4.count();
    QString updateSQL = QString("UPDATE PEIFANG4 SET ");
    for(int i = 0;i<count;i++){
        if(pflistEdit4.at(i)->text().isEmpty()){
            QMessageBox::information(this,tr("错误"),tr("配方值有空值！！！"),0,0,0);
            return;
        }
        QString str = QString("Mat%1='%2',").arg(strList4[i],pflistEdit4.at(i)->text());
        updateSQL.append(str);
    }
    updateSQL = updateSQL.append(QString("jbTime='%1',WuShui='%2',NAME='%3' where PhbNumber='%4'").arg(three2StirTimeLineEdit->text(),three2WuShuiLineEdit->text(),three2StrenghtGradeLineEdit->text(),three2PhbNameLineEdit->text()));

    db.sql_exec("begin;");
    int res = db.sql_exec(updateSQL.toStdString().data());
    if(res == -1){
        db.sql_exec("rollback");
        return;
    }

    for(int i = 0;i<count;i++){
        if(pfList.at(i) != pflistEdit4.at(i)->text()){
            QString xiugaineirong = matList4[i]+QString(":")+pfList.at(i)+QString("→")+pflistEdit4.at(i)->text();
            QString insertSQL = QString("insert into peifang_xiugai4 (phbName,updateMan,neirong,time) values ('%1','%2','%3','%4')")
                    .arg(three2PhbNameLineEdit->text(),userName,xiugaineirong,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            db.sql_exec(insertSQL);
            if(res == -1){
                db.sql_exec("rollback");
                return;
            }
        }
    }
    db.sql_exec("commit");
    db.showview_num(SQL4,three2PhbListView,&three2PhbListModel,0);
    QMessageBox::information(this,tr("提示信息"),tr("修改成功"),0,0,0);
    return;
}

void peihebimubanDlg::on_deleteAction4()
{
    QString deleteSQL = QString("delete from PEIFANG4 where PhbNumber='%1'").arg(three2PhbNameLineEdit->text());
    int res = db.sql_exec(deleteSQL);
    if(res == 0){
        db.showview_num(SQL4,three2PhbListView,&three2PhbListModel,0);
        QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
        return;
    }
}

void peihebimubanDlg::ShowSupplyclick()
{
    saveAction->setEnabled(false);
    updateAction->setEnabled(true);
    deleteAction->setEnabled(true);
    pfList.clear();
    onePhbNameLineEdit->setReadOnly(true);
    onePhbNumLineEdit->setReadOnly(true);

    int row = onePhbListView->currentIndex().row();
    onePhbNumLineEdit->setText(onePhbListModel->item(row,0)->text());
    onePhbNameLineEdit->setText(onePhbListModel->item(row,1)->text());
    oneStrenghtGradeLineEdit->setText(onePhbListModel->item(row,2)->text());
    oneStirTimeLineEdit->setText(onePhbListModel->item(row,3)->text());
    oneWuShuiLineEdit->setText(onePhbListModel->item(row,4)->text());

    //1#配比
    QString fillTableWidget1 = QString("SELECT ");
    for(int i = 0;i<strList1.count();i++){
        QString str = QString("Mat%1,").arg(strList1.at(i));
        fillTableWidget1.append(str);
    }
    fillTableWidget1 = fillTableWidget1.left(fillTableWidget1.length()-1);
    fillTableWidget1 = fillTableWidget1.append(QString(" FROM PEIFANG1 WHERE PhbNumber='%1'").arg(onePhbListModel->item(row,1)->text()));
    QStringList resStrList1 = db.CreatStrList(fillTableWidget1);
    if(resStrList1.count()<strList1.count()){
        return;
    }
    for(int i = 0; i < strList1.count(); i++){
        disconnect(pflistEdit1.at(i),SIGNAL(textChanged(QString)),this,SLOT(on_CalcRongZhong1()));
        pflistEdit1.at(i)->setText(resStrList1.at(i));
        connect(pflistEdit1.at(i),SIGNAL(textChanged(QString)),this,SLOT(on_CalcRongZhong1()));
        pfList.append(pflistEdit1.at(i)->text());
    }
    on_CalcRongZhong1();
}


void peihebimubanDlg::ShowSupplyclick2()
{
    saveAction2->setEnabled(false);
    updateAction2->setEnabled(true);
    deleteAction2->setEnabled(true);
    pfList.clear();
    twoPhbNameLineEdit->setReadOnly(true);
    twoPhbNumLineEdit->setReadOnly(true);

    int row = twoPhbListView->currentIndex().row();
    twoPhbNumLineEdit->setText(twoPhbListModel->item(row,0)->text());
    twoPhbNameLineEdit->setText(twoPhbListModel->item(row,1)->text());
    twoStrenghtGradeLineEdit->setText(twoPhbListModel->item(row,2)->text());
    twoStirTimeLineEdit->setText(twoPhbListModel->item(row,3)->text());
    twoWuShuiLineEdit->setText(twoPhbListModel->item(row,4)->text());

    //2#配比
    QString fillPhbDataSQL = QString("SELECT ");
    for(int i = 0;i<strList2.count();i++){
        QString str = QString("Mat%1,").arg(strList2.at(i));
        fillPhbDataSQL.append(str);
    }
    fillPhbDataSQL = fillPhbDataSQL.left(fillPhbDataSQL.length()-1);
    fillPhbDataSQL = fillPhbDataSQL.append(QString(" FROM PEIFANG2 where PhbNumber='%1'").arg(twoPhbListModel->item(row,1)->text()));
    QStringList resStrList1 = db.CreatStrList(fillPhbDataSQL);
    if(resStrList1.count()<strList2.count()){
        return;
    }
    for(int i = 0; i < strList2.count(); i++){
        disconnect(pflistEdit2.at(i),SIGNAL(textChanged(QString)),this,SLOT(on_CalcRongZhong2()));
        pflistEdit2.at(i)->setText(resStrList1.at(i));
        connect(pflistEdit2.at(i),SIGNAL(textChanged(QString)),this,SLOT(on_CalcRongZhong2()));
        pfList.append(pflistEdit2.at(i)->text());
    }
    on_CalcRongZhong2();
}

void peihebimubanDlg::ShowSupplyclick3()
{
    saveAction3->setEnabled(false);
    updateAction3->setEnabled(true);
    deleteAction3->setEnabled(true);
    pfList.clear();
    threePhbNameLineEdit->setReadOnly(true);
    threePhbNumLineEdit->setReadOnly(true);

    int row = threePhbListView->currentIndex().row();
    threePhbNumLineEdit->setText(threePhbListModel->item(row,0)->text());
    threePhbNameLineEdit->setText(threePhbListModel->item(row,1)->text());
    threeStrenghtGradeLineEdit->setText(threePhbListModel->item(row,2)->text());
    threeStirTimeLineEdit->setText(threePhbListModel->item(row,3)->text());
    threeWuShuiLineEdit->setText(threePhbListModel->item(row,4)->text());

    //3#配比
    QString fillPhbDataSQL = QString("SELECT ");
    for(int i = 0;i<strList3.count();i++){
        QString str = QString("Mat%1,").arg(strList3.at(i));
        fillPhbDataSQL.append(str);
    }
    fillPhbDataSQL = fillPhbDataSQL.left(fillPhbDataSQL.length()-1);
    fillPhbDataSQL = fillPhbDataSQL.append(QString(" FROM PEIFANG3 where PhbNumber='%1'").arg(threePhbListModel->item(row,1)->text()));
    QStringList resStrList1 = db.CreatStrList(fillPhbDataSQL);
    if(resStrList1.count()<strList3.count()){
        return;
    }
    for(int i = 0; i < strList3.count(); i++){
        disconnect(pflistEdit3.at(i),SIGNAL(textChanged(QString)),this,SLOT(on_CalcRongZhong3()));
        pflistEdit3.at(i)->setText(resStrList1.at(i));
        connect(pflistEdit3.at(i),SIGNAL(textChanged(QString)),this,SLOT(on_CalcRongZhong3()));
        pfList.append(pflistEdit3.at(i)->text());
    }
    on_CalcRongZhong3();
}

void peihebimubanDlg::ShowSupplyclick4()
{
    saveAction4->setEnabled(false);
    updateAction4->setEnabled(true);
    deleteAction4->setEnabled(true);
    pfList.clear();
    three2PhbNameLineEdit->setReadOnly(true);
    three2PhbNumLineEdit->setReadOnly(true);

    int row = three2PhbListView->currentIndex().row();
    three2PhbNumLineEdit->setText(three2PhbListModel->item(row,0)->text());
    three2PhbNameLineEdit->setText(three2PhbListModel->item(row,1)->text());
    three2StrenghtGradeLineEdit->setText(three2PhbListModel->item(row,2)->text());
    three2StirTimeLineEdit->setText(three2PhbListModel->item(row,3)->text());
    three2WuShuiLineEdit->setText(three2PhbListModel->item(row,4)->text());

    //4#配比
    QString fillPhbDataSQL = QString("SELECT ");
    for(int i = 0;i<strList4.count();i++){
        QString str = QString("Mat%1,").arg(strList4.at(i));
        fillPhbDataSQL.append(str);
    }
    fillPhbDataSQL = fillPhbDataSQL.left(fillPhbDataSQL.length()-1);
    fillPhbDataSQL = fillPhbDataSQL.append(QString(" FROM PEIFANG4 where PhbNumber='%1'").arg(three2PhbListModel->item(row,1)->text()));
    QStringList resStrList1 = db.CreatStrList(fillPhbDataSQL);
    if(resStrList1.count()<strList4.count()){
        return;
    }
    for(int i = 0; i < strList4.count(); i++){
        disconnect(pflistEdit4.at(i),SIGNAL(textChanged(QString)),this,SLOT(on_CalcRongZhong4()));
        pflistEdit4.at(i)->setText(resStrList1.at(i));
        connect(pflistEdit4.at(i),SIGNAL(textChanged(QString)),this,SLOT(on_CalcRongZhong4()));
        pfList.append(pflistEdit4.at(i)->text());
    }
    on_CalcRongZhong4();
}

void peihebimubanDlg::on_CalcRongZhong1()
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

void peihebimubanDlg::on_CalcRongZhong2()
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

void peihebimubanDlg::on_CalcRongZhong3()
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

void peihebimubanDlg::on_CalcRongZhong4()
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


void peihebimubanDlg::on_fourFindBtn()
{
    QString phbName;
    if(fourPhbNameCheckBox->checkState() == 2){
        phbName = QString(" and phbName='%1'").arg(fourPhbNameCombox->currentText());
    }

    QString searchSQL;
    switch (fourUnitNoCombox->currentIndex()){
    case 1:
        searchSQL = QString("select phbName 配合比模板名称,updateMan 修改人,neirong 内容,time 修改时间 from PEIFANG_XIUGAI1 where time between '%1' and '%2' %3")
                .arg(fourDateTimeEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),fourDateTimeEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),phbName);
        break;
    case 2:
        searchSQL = QString("SELECT phbName 配合比模板名称,updateMan 修改人,neirong 内容,time 修改时间 from PEIFANG_XIUGAI2 where time between '%1' and '%2' %3")
                .arg(fourDateTimeEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),fourDateTimeEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),phbName);
        break;
    case 3:
        searchSQL = QString("SELECT phbName 配合比模板名称,updateMan 修改人,neirong 内容,time 修改时间 from PEIFANG_XIUGAI3 where time between '%1' and '%2' %3")
                .arg(fourDateTimeEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),fourDateTimeEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),phbName);
        break;
    default:
        break;
    }

    db.showview(searchSQL,fourUpdateView,&fourUpdateModel);
}
