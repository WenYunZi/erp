#include "fucairukudlg.h"

extern QString userName;

extern mymysql db;
extern pubfunc pub;
extern QString userName;
extern myTCPsocket *sockClient;

fucairukuDlg::fucairukuDlg(QWidget *parent) :
    QDialog(parent)
{
    tabWidget = new QTabWidget(this);
    fucairuku = new QWidget(this);
    fucaichuku  = new QWidget(this);
    fucaikucun  = new QWidget(this);
//    fucaijilu  = new QWidget(this);//记录辅材操作


    creatTabPage1();
    creatTabPage2();
    creatTabPage3();
//    creatTabPage4();//记录辅材操作

    view2Excel = new myExcel(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tabWidget);
}

void fucairukuDlg::refresh()
{
}

void fucairukuDlg::keyPressEvent(QKeyEvent *event)
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

void fucairukuDlg::creatTabPage1()
{
    createAction();
    createTool();


    LuRuSQL = "select FucaiNO 入库单号, FucaiName 辅材名称, SuoShuXiaoLei 所属小类, SuoShuDaLei 所属大类, GuiGe 规格,DanWei 单位, DanJia 单价, ShuLiang 数量,ZongJinE 总金额,SongHuoRenYuan 供应商,\
            LianXiFangShi 供应商联系方式,CaiGouRen 采购人,CaiGouRenLianXiFangShi 采购人联系方式,LuRuRenYuan 录入人员, LuRuRiQi 录入日期,BeiZhu 备注 from fucaitongjibiao";

    QLabel *rukudanhaoLabel = new QLabel(tr("入库单号"),this);
    rukudanhaoLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *fucainameLabel = new QLabel(tr("辅材名称"),this);
    fucainameLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *fucaixiaoleiLabel = new QLabel(tr("所属小类"),this);
    fucaixiaoleiLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *fucaidaleiLabel = new QLabel(tr("所属大类"),this);
    fucaidaleiLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *fucaidanjiaLabel = new QLabel(tr("单价"),this);
    fucaidanjiaLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *fucaishuliangLabel = new QLabel(tr("数量"),this);
    fucaishuliangLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *rukuzongjineLabel = new QLabel(tr("总金额"),this);
    rukuzongjineLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *fucaiguigeLabel = new QLabel(tr("规格"),this);
    fucaiguigeLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *fucaidanweiLabel = new QLabel(tr("单位"),this);
    fucaidanweiLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *songhuorenyuanLabel = new QLabel(tr("供应商"),this);
    songhuorenyuanLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *lianxifangshiLabel = new QLabel(tr("供应商联系方式"),this);
    lianxifangshiLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    QLabel *caigourenyuanLabel = new QLabel(tr("采购人"),this);
    caigourenyuanLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *caigourenlianxifangshiLabel = new QLabel(tr("采购人联系方式"),this);
    caigourenlianxifangshiLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    QLabel *lururenyuanLabel = new QLabel(tr("录入人员"),this);
    lururenyuanLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *lururiqiLabel = new QLabel(tr("录入日期"),this);
    lururiqiLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *lukubeizhuLabel = new QLabel(tr("备注"),this);
    lukubeizhuLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    rukudanhaoLineEdit = new QLineEdit(this);
    rukudanhaoLineEdit->setEnabled(false);
    fucainameComboBox = new QComboBox(this);
    fucainameComboBox->setEnabled(false);

    connect(fucainameComboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(on_fucaidalei()));

    fucaidaleiComboBox = new QComboBox(this);
    fucaidaleiComboBox->setEnabled(false);

    connect(fucaidaleiComboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(on_fucaixiaolei()));

    fucaixiaoleiComboBox = new QComboBox(this);
    fucaixiaoleiComboBox->setEnabled(false);
    fucaidanjiaLineEdit = new QLineEdit(this);
    connect(fucaidanjiaLineEdit,SIGNAL(textChanged(QString)),this,SLOT(on_fucaidanjia()));
    fucaishuliangLineEdit = new QLineEdit(this);
    connect(fucaishuliangLineEdit,SIGNAL(textChanged(QString)),this,SLOT(on_fucaishuliang()));
    rukuzongjineLineEdit = new QLineEdit(this);
    rukuzongjineLineEdit->setEnabled(false);
    fucaiguigeLineEdit = new QLineEdit(this);
    fucaidanweiLineEdit = new QLineEdit(this);
    songhuorenyuanLineEdit = new QLineEdit(this);
    lianxifangshiLineEdit = new QLineEdit(this);
    caigourenyuanLineEdit = new QLineEdit(this);
    caigoulianxifangshiLineEdit = new QLineEdit(this);
    lururenyuanLineEdit = new QLineEdit(this);
    lururenyuanLineEdit->setEnabled(false);
    lururiqiDateEdit = new QDateEdit(QDate::currentDate(),this);
    lururiqiDateEdit->setCalendarPopup(true);
    lukubeizhuLineEdit = new QLineEdit(this);

    QLabel *RuKuRiQi = new QLabel(tr("入库日期"),this);
    RuKuRiQi->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *FenGeFu = new QLabel(tr("--"),this);
    FenGeFu->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    onedateEdit1 = new QDateEdit(QDate::currentDate(),this);
    onedateEdit1->setCalendarPopup(true);
    onedateEdit2 = new QDateEdit(QDate::currentDate(),this);
    onedateEdit2->setCalendarPopup(true);
    onechaxun = new QPushButton(tr("查询"),this);
    connect(onechaxun,SIGNAL(clicked()),this,SLOT(on_onechaxun()));

    daochuBtn1 = new QPushButton(tr("导出"),this);
    daochuBtn1->setFixedWidth(120);
    connect(daochuBtn1,SIGNAL(clicked()),this,SLOT(on_toExcell1()));

    onefucaidaleiCheckBox = new QCheckBox(tr("辅材大类"),this);
    onefudaleiCombox = new QComboBox(this);
    onefudaleiCombox->setFixedWidth(90);
    onefudaleiCombox->setEditable(true);
    db.sql_fillComboBoxItem("select SuoShuDaLei from fucaitongjibiao group by SuoShuDaLei",onefudaleiCombox);
    onefucaixiaoleiCheckBox = new QCheckBox(tr("辅材小类"),this);
    onefucaixiaoleiCombox = new QComboBox(this);
    onefucaixiaoleiCombox->setFixedWidth(90);
    onefucaixiaoleiCombox->setEditable(true);
    db.sql_fillComboBoxItem("select SuoShuXiaoLei from fucaitongjibiao group by SuoShuXiaoLei",onefucaixiaoleiCombox);

    onefucaimingchengCheckBox = new QCheckBox(tr("辅材名称"),this);
    onefucaimingchengCombox = new QComboBox(this);
    onefucaimingchengCombox->setFixedWidth(90);
    onefucaimingchengCombox->setEditable(true);
    db.sql_fillComboBoxItem("select FucaiName from fucaitongjibiao group by FucaiName",onefucaimingchengCombox);

    onesonghuorenyuanCheckBox = new QCheckBox(tr("供应商"),this);
    onesonghuorenyuanCombox = new QComboBox(this);
    onesonghuorenyuanCombox->setFixedWidth(90);
    onesonghuorenyuanCombox->setEditable(true);
    db.sql_fillComboBoxItem("select SongHuoRenYuan from fucaitongjibiao group by SongHuoRenYuan",onesonghuorenyuanCombox);

    fahuoView = new QTableView(this);
    db.showview(LuRuSQL,fahuoView,&fahuoModel);
    connect(fahuoView,SIGNAL(clicked(QModelIndex)),this,SLOT(Show_fahuoSupplyclick()));


    QGridLayout *layout = new QGridLayout;
    layout->addWidget(rukudanhaoLabel,0,0);
    layout->addWidget(rukudanhaoLineEdit,0,1);
    layout->addWidget(fucainameLabel,0,2);
    layout->addWidget(fucainameComboBox,0,3);

    layout->addWidget(fucaidaleiLabel,0,4);
    layout->addWidget(fucaidaleiComboBox,0,5);
    layout->addWidget(fucaixiaoleiLabel,0,6);
    layout->addWidget(fucaixiaoleiComboBox,0,7);

    layout->addWidget(fucaiguigeLabel,0,8);
    layout->addWidget(fucaiguigeLineEdit,0,9);
    layout->addWidget(fucaidanweiLabel,0,10);
    layout->addWidget(fucaidanweiLineEdit,0,11);
    layout->addWidget(fucaidanjiaLabel,1,0);
    layout->addWidget(fucaidanjiaLineEdit,1,1);
    layout->addWidget(fucaishuliangLabel,1,2);
    layout->addWidget(fucaishuliangLineEdit,1,3);
    layout->addWidget(rukuzongjineLabel,1,4);
    layout->addWidget(rukuzongjineLineEdit,1,5);
    layout->addWidget(songhuorenyuanLabel,1,6);
    layout->addWidget(songhuorenyuanLineEdit,1,7);
    layout->addWidget(lianxifangshiLabel,1,8);
    layout->addWidget(lianxifangshiLineEdit,1,9);

    layout->addWidget(caigourenyuanLabel,1,10);
    layout->addWidget(caigourenyuanLineEdit,1,11);
    layout->addWidget(caigourenlianxifangshiLabel,2,0);
    layout->addWidget(caigoulianxifangshiLineEdit,2,1);

    layout->addWidget(lururenyuanLabel,2,2);
    layout->addWidget(lururenyuanLineEdit,2,3);
    layout->addWidget(lururiqiLabel,2,4);
    layout->addWidget(lururiqiDateEdit,2,5,1,2);
    layout->addWidget(lukubeizhuLabel,3,0);
    layout->addWidget(lukubeizhuLineEdit,3,1,1,11);
    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(RuKuRiQi);
    hlayout->addWidget(onedateEdit1);
    hlayout->addWidget(FenGeFu,Qt::AlignVCenter|Qt::AlignLeft);
    hlayout->addWidget(onedateEdit2);
    hlayout->addWidget(onefucaidaleiCheckBox);
    hlayout->addWidget(onefudaleiCombox);
    hlayout->addWidget(onefucaixiaoleiCheckBox);
    hlayout->addWidget(onefucaixiaoleiCombox);
    hlayout->addWidget(onefucaimingchengCheckBox);
    hlayout->addWidget(onefucaimingchengCombox);
    hlayout->addWidget(onesonghuorenyuanCheckBox);
    hlayout->addWidget(onesonghuorenyuanCombox);
    hlayout->addWidget(onechaxun);
    hlayout->addWidget(daochuBtn1);
    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(toolBar);
    vlayout->addLayout(layout);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(fahuoView);
    fucairuku->setLayout(vlayout);
    tabWidget->addTab(fucairuku,tr("辅材入库"));
}

void fucairukuDlg::creatTabPage2()
{
    twocreateAction();
    twocreateTool();


    twoLuRuSQL = "select FucaiNO 出库单号, FucaiName 辅材名称, SuoShuXiaoLei 所属小类, SuoShuDaLei 所属大类, GuiGe 规格,DanWei 单位, DanJia 单价, ShuLiang 数量,ZongJinE 总金额,LingLiaoDanWei 领料单位,SongHuoRenYuan 领料人,\
            ShiYongBuWei 使用部位,LianXiFangShi 联系方式,LuRuRenYuan 录入人员, LuRuRiQi 录入日期,BeiZhu 备注 from fucaitongjibiaotwo";

    QLabel *tworukudanhaoLabel = new QLabel(tr("出库单号"),this);
    tworukudanhaoLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *twofucainameLabel = new QLabel(tr("辅材名称"),this);
    twofucainameLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *twofucaixiaoleiLabel = new QLabel(tr("所属小类"),this);
    twofucaixiaoleiLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *twofucaidaleiLabel = new QLabel(tr("所属大类"),this);
    twofucaidaleiLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *twofucaidanjiaLabel = new QLabel(tr("单价"),this);
    twofucaidanjiaLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *twofucaishuliangLabel = new QLabel(tr("数量"),this);
    twofucaishuliangLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *tworukuzongjineLabel = new QLabel(tr("总金额"),this);
    tworukuzongjineLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *twofucaiguigeLabel = new QLabel(tr("规格"),this);
    twofucaiguigeLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *twofucaidanweiLabel = new QLabel(tr("单位"),this);
    twofucaidanweiLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *twolingliaodanweiLabel = new QLabel(tr("领料单位"),this);
    twolingliaodanweiLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *twosonghuorenyuanLabel = new QLabel(tr("领料人"),this);
    twosonghuorenyuanLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *twoshiyongbuweiLabel = new QLabel(tr("使用部位"),this);
    twoshiyongbuweiLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *twolianxifangshiLabel = new QLabel(tr("联系方式"),this);
    twolianxifangshiLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *twolururenyuanLabel = new QLabel(tr("录入人员"),this);
    twolururenyuanLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *twolururiqiLabel = new QLabel(tr("录入日期"),this);
    twolururiqiLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *twolukubeizhuLabel = new QLabel(tr("备注"),this);
    twolukubeizhuLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    tworukudanhaoLineEdit = new QLineEdit(this);
    tworukudanhaoLineEdit->setEnabled(false);
    twofucainameComboBox = new QComboBox(this);
    twofucainameComboBox->setEnabled(false);

    connect(twofucainameComboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(twoon_fucaidalei()));

    twofucaidaleiComboBox = new QComboBox(this);
    twofucaidaleiComboBox->setEnabled(false);

    connect(twofucaidaleiComboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(twoon_fucaixiaolei()));

    twofucaixiaoleiComboBox = new QComboBox(this);
    twofucaixiaoleiComboBox->setEnabled(false);
    twofucaidanjiaLineEdit = new QLineEdit(this);
    connect(twofucaidanjiaLineEdit,SIGNAL(textChanged(QString)),this,SLOT(twoon_fucaidanjia()));
    twofucaishuliangLineEdit = new QLineEdit(this);
    connect(twofucaishuliangLineEdit,SIGNAL(textChanged(QString)),this,SLOT(twoon_fucaishuliang()));
    tworukuzongjineLineEdit = new QLineEdit(this);
    tworukuzongjineLineEdit->setEnabled(false);
    twofucaiguigeLineEdit = new QLineEdit(this);
    twofucaidanweiLineEdit = new QLineEdit(this);
    twolingliaodanweiLineEdit = new QLineEdit(this);
    twosonghuorenyuanLineEdit = new QLineEdit(this);
    twoshiyongbuweiLineEdit = new QLineEdit(this);
    twolianxifangshiLineEdit = new QLineEdit(this);
    twolururenyuanLineEdit = new QLineEdit(this);
    twolururenyuanLineEdit->setEnabled(false);
    twolururiqiDateEdit = new QDateEdit(QDate::currentDate(),this);
    twolururiqiDateEdit->setCalendarPopup(true);
    twolukubeizhuLineEdit = new QLineEdit(this);

    QLabel *twoRuKuRiQi = new QLabel(tr("出库日期"),this);
    twoRuKuRiQi->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *twoFenGeFu = new QLabel(tr("--"),this);
    twoFenGeFu->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    twodateEdit1 = new QDateEdit(QDate::currentDate(),this);
    twodateEdit1->setCalendarPopup(true);
    twodateEdit2 = new QDateEdit(QDate::currentDate(),this);
    twodateEdit2->setCalendarPopup(true);
    twochaxun = new QPushButton(tr("查询"),this);
    connect(twochaxun,SIGNAL(clicked()),this,SLOT(twoon_onechaxun()));


    daochuBtn2 = new QPushButton(tr("导出"),this);
    daochuBtn2->setFixedWidth(120);
    connect(daochuBtn2,SIGNAL(clicked()),this,SLOT(on_toExcell2()));

    twofucaidaleiCheckBox = new QCheckBox(tr("辅材大类"),this);
    twofudaleiCombox = new QComboBox(this);
    twofudaleiCombox->setFixedWidth(90);
    twofudaleiCombox->setEditable(true);
    db.sql_fillComboBoxItem("select SuoShuDaLei from fucaitongjibiao group by SuoShuDaLei",twofudaleiCombox);
    twofucaixiaoleiCheckBox = new QCheckBox(tr("辅材小类"),this);
    twofucaixiaoleiCombox = new QComboBox(this);
    twofucaixiaoleiCombox->setFixedWidth(90);
    twofucaixiaoleiCombox->setEditable(true);
    db.sql_fillComboBoxItem("select SuoShuXiaoLei from fucaitongjibiao group by SuoShuXiaoLei",twofucaixiaoleiCombox);

    twofucaimingchengCheckBox = new QCheckBox(tr("辅材名称"),this);
    twofucaimingchengCombox = new QComboBox(this);
    twofucaimingchengCombox->setFixedWidth(90);
    twofucaimingchengCombox->setEditable(true);
    db.sql_fillComboBoxItem("select FucaiName from fucaitongjibiao group by FucaiName",twofucaimingchengCombox);

    twosonghuorenyuanCheckBox = new QCheckBox(tr("领料人"),this);
    twosonghuorenyuanCombox = new QComboBox(this);
    twosonghuorenyuanCombox->setFixedWidth(90);
    twosonghuorenyuanCombox->setEditable(true);
    db.sql_fillComboBoxItem("select SongHuoRenYuan from fucaitongjibiao group by SongHuoRenYuan",twosonghuorenyuanCombox);

    twofahuoView = new QTableView(this);
    db.showview(twoLuRuSQL,twofahuoView,&twofahuoModel);
    connect(twofahuoView,SIGNAL(clicked(QModelIndex)),this,SLOT(twoShow_fahuoSupplyclick()));


    QGridLayout *layout = new QGridLayout;
    layout->addWidget(tworukudanhaoLabel,0,0);
    layout->addWidget(tworukudanhaoLineEdit,0,1);
    layout->addWidget(twofucainameLabel,0,2);
    layout->addWidget(twofucainameComboBox,0,3);

    layout->addWidget(twofucaidaleiLabel,0,4);
    layout->addWidget(twofucaidaleiComboBox,0,5);
    layout->addWidget(twofucaixiaoleiLabel,0,6);
    layout->addWidget(twofucaixiaoleiComboBox,0,7);

    layout->addWidget(twofucaiguigeLabel,0,8);
    layout->addWidget(twofucaiguigeLineEdit,0,9);
    layout->addWidget(twofucaidanweiLabel,0,10);
    layout->addWidget(twofucaidanweiLineEdit,0,11);
    layout->addWidget(twofucaidanjiaLabel,1,0);
    layout->addWidget(twofucaidanjiaLineEdit,1,1);
    layout->addWidget(twofucaishuliangLabel,1,2);
    layout->addWidget(twofucaishuliangLineEdit,1,3);
    layout->addWidget(tworukuzongjineLabel,1,4);
    layout->addWidget(tworukuzongjineLineEdit,1,5);
    layout->addWidget(twolingliaodanweiLabel,1,6);
    layout->addWidget(twolingliaodanweiLineEdit,1,7);
    layout->addWidget(twosonghuorenyuanLabel,1,8);
    layout->addWidget(twosonghuorenyuanLineEdit,1,9);
    layout->addWidget(twoshiyongbuweiLabel,1,10);
    layout->addWidget(twoshiyongbuweiLineEdit,1,11);
    layout->addWidget(twolianxifangshiLabel,2,0);
    layout->addWidget(twolianxifangshiLineEdit,2,1);
    layout->addWidget(twolururenyuanLabel,2,2);
    layout->addWidget(twolururenyuanLineEdit,2,3);
    layout->addWidget(twolururiqiLabel,2,4);
    layout->addWidget(twolururiqiDateEdit,2,5,1,2);
    layout->addWidget(twolukubeizhuLabel,3,0);
    layout->addWidget(twolukubeizhuLineEdit,3,1,1,11);
    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(twoRuKuRiQi);
    hlayout->addWidget(twodateEdit1);
    hlayout->addWidget(twoFenGeFu,Qt::AlignVCenter|Qt::AlignLeft);
    hlayout->addWidget(twodateEdit2);
    hlayout->addWidget(twofucaidaleiCheckBox);
    hlayout->addWidget(twofudaleiCombox);
    hlayout->addWidget(twofucaixiaoleiCheckBox);
    hlayout->addWidget(twofucaixiaoleiCombox);
    hlayout->addWidget(twofucaimingchengCheckBox);
    hlayout->addWidget(twofucaimingchengCombox);
    hlayout->addWidget(twosonghuorenyuanCheckBox);
    hlayout->addWidget(twosonghuorenyuanCombox);
    hlayout->addWidget(twochaxun);
    hlayout->addWidget(daochuBtn2);
    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(twotoolBar);
    vlayout->addLayout(layout);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(twofahuoView);
    fucaichuku->setLayout(vlayout);
    tabWidget->addTab(fucaichuku,tr("辅材出库"));
}

void fucairukuDlg::creatTabPage3()
{
    threeLuRuSQL = "select FucaiNO 库存单号, FucaiName 辅材名称, SuoShuXiaoLei 所属小类, SuoShuDaLei 所属大类, GuiGe 规格,DanWei 单位, DanJia 单价, ShuLiang 数量,ZongJinE 总金额,SongHuoRenYuan 领料人,\
            LianXiFangShi 联系方式,LuRuRenYuan 录入人员, LuRuRiQi 录入日期,BeiZhu 备注 from fucaitongjibiaothree";

    threechaxun = new QPushButton(tr("查询"),this);
    connect(threechaxun,SIGNAL(clicked()),this,SLOT(threeon_onechaxun()));

    daochuBtn3 = new QPushButton(tr("导出"),this);
    daochuBtn3->setFixedWidth(120);
    connect(daochuBtn3,SIGNAL(clicked()),this,SLOT(on_toExcell3()));

    threefucaidaleiCheckBox = new QCheckBox(tr("辅材大类"),this);
    threefudaleiCombox = new QComboBox(this);
    threefudaleiCombox->setFixedWidth(90);
    threefudaleiCombox->setEditable(true);
    db.sql_fillComboBoxItem("select SuoShuDaLei from fucaitongjibiaothree group by SuoShuDaLei",threefudaleiCombox);
    threefucaixiaoleiCheckBox = new QCheckBox(tr("辅材小类"),this);
    threefucaixiaoleiCombox = new QComboBox(this);
    threefucaixiaoleiCombox->setFixedWidth(90);
    threefucaixiaoleiCombox->setEditable(true);
    db.sql_fillComboBoxItem("select SuoShuXiaoLei from fucaitongjibiaothree group by SuoShuXiaoLei",threefucaixiaoleiCombox);

    threefucaimingchengCheckBox = new QCheckBox(tr("辅材名称"),this);
    threefucaimingchengCombox = new QComboBox(this);
    threefucaimingchengCombox->setFixedWidth(90);
    threefucaimingchengCombox->setEditable(true);
    db.sql_fillComboBoxItem("select FucaiName from fucaitongjibiaothree group by FucaiName",threefucaimingchengCombox);

    threefahuoView = new QTableView(this);
    db.showview(threeLuRuSQL,threefahuoView,&threefahuoModel);
    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(threefucaidaleiCheckBox);
    hlayout->addWidget(threefudaleiCombox);
    hlayout->addWidget(threefucaixiaoleiCheckBox);
    hlayout->addWidget(threefucaixiaoleiCombox);
    hlayout->addWidget(threefucaimingchengCheckBox);
    hlayout->addWidget(threefucaimingchengCombox);
    hlayout->addWidget(threechaxun);
    hlayout->addWidget(daochuBtn3);
    hlayout->addStretch(6);
    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(threefahuoView);
    fucaikucun->setLayout(vlayout);
    tabWidget->addTab(fucaikucun,tr("辅材库存"));
}

//void fucairukuDlg::creatTabPage4()
//{
//    //    fucaijilu->setLayout();
//    tabWidget->addTab(fucaijilu,tr("辅材操作记录"));
//}

/*************************************入库开始*********************************************/

void fucairukuDlg::on_onechaxun()
{
    QString Time,fucaimingzi,fucaidalei,fucaixiaolei,songhuorenyuan;
    Time = QString(" and LuRuRiQi between '%1' and '%2'").arg(onedateEdit1->date().toString("yyyy-MM-dd"),onedateEdit2->date().addDays(1).toString("yyyy-MM-dd"));
    if(onefucaidaleiCheckBox->checkState() == 2){
        fucaidalei =  QString(" and SuoShuDaLei = '%1'").arg(onefudaleiCombox->currentText());
    }
    if(onefucaixiaoleiCheckBox->checkState() == 2){
        fucaixiaolei =  QString(" and SuoShuXiaoLei = '%1'").arg(onefucaixiaoleiCombox->currentText());
    }
    if(onefucaimingchengCheckBox->checkState() == 2){
        fucaimingzi =  QString(" and FucaiName = '%1'").arg(onefucaimingchengCombox->currentText());
    }
    if(onesonghuorenyuanCheckBox->checkState() == 2){
        songhuorenyuan =  QString(" and SongHuoRenYuan = '%1'").arg(onesonghuorenyuanCombox->currentText());
    }

    QString chaxunSQL = QString("select FucaiNO 入库单号, FucaiName 辅材名称, SuoShuXiaoLei 所属小类, SuoShuDaLei 所属大类, GuiGe 规格,DanWei 单位, DanJia 单价, ShuLiang 数量,ZongJinE 总金额,SongHuoRenYuan 供应商,\
               LianXiFangShi 供应商联系方式,CaiGouRen 采购人,CaiGouRenLianXiFangShi 采购人联系方式,LuRuRenYuan 录入人员, LuRuRiQi 录入日期,BeiZhu 备注 from fucaitongjibiao where FucaiNO is not null %1 %2 %3 %4 %5")
               .arg(Time,fucaidalei,fucaixiaolei,fucaimingzi,songhuorenyuan);
    db.showview_num(chaxunSQL,fahuoView,&fahuoModel,0);

}

void fucairukuDlg::on_toExcell1()
{
    view2Excel->Table2ExcelByHtml(fahuoView,"辅材入库表");
}

void fucairukuDlg::Show_fahuoSupplyclick()
{

    updateAction->setEnabled(true);
    deleteAction->setEnabled(true);
    saveAction->setEnabled(false);

    int row = fahuoView->currentIndex().row();
    rukudanhaoLineEdit->setText(fahuoModel->item(row,0)->text());
    onerukudanhao = fahuoModel->item(row,0)->text();


    fucainameComboBox->clear();
    fucainameComboBox->setEnabled(true);
    fucainameComboBox->setEditable(true);
    fucainameComboBox->setCurrentText(fahuoModel->item(row,1)->text());
    onefucainame = fahuoModel->item(row,1)->text();

    disconnect(fucaidaleiComboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(on_fucaixiaolei()));
    fucaidaleiComboBox->clear();
    fucaidaleiComboBox->setEnabled(true);
    const char * selectClass = "select Class from AuxiliaryCategory";
    db.sql_fillComboBoxItem(selectClass,fucaidaleiComboBox);
    connect(fucaidaleiComboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(on_fucaixiaolei()));


    fucaidaleiComboBox->setCurrentText(fahuoModel->item(row,3)->text());
    onefucaidalei = fahuoModel->item(row,3)->text();
    fucaixiaoleiComboBox->setCurrentText(fahuoModel->item(row,2)->text());
    onefucaixiaolei = fahuoModel->item(row,2)->text();
    fucaixiaoleiComboBox->setEnabled(true);
    fucaidanjiaLineEdit->setText(fahuoModel->item(row,6)->text());
    onefucaidanjia = fahuoModel->item(row,6)->text();
    fucaishuliangLineEdit->setText(fahuoModel->item(row,7)->text());
    onefucaishuliang = fahuoModel->item(row,7)->text();
    rukuzongjineLineEdit->setText(fahuoModel->item(row,8)->text());
    onerukuzongjine = fahuoModel->item(row,8)->text();
    fucaiguigeLineEdit->setText(fahuoModel->item(row,4)->text());
    onefucaiguige = fahuoModel->item(row,4)->text();
    fucaidanweiLineEdit->setText(fahuoModel->item(row,5)->text());
    onefucaidanwei = fahuoModel->item(row,5)->text();
    songhuorenyuanLineEdit->setText(fahuoModel->item(row,9)->text());
    onesonghuorenyuan = fahuoModel->item(row,9)->text();
    lianxifangshiLineEdit->setText(fahuoModel->item(row,10)->text());
    onelianxifangshi = fahuoModel->item(row,10)->text();
    caigourenyuanLineEdit->setText(fahuoModel->item(row,11)->text());
    caigoulianxifangshiLineEdit->setText(fahuoModel->item(row,12)->text());
    lururenyuanLineEdit->setText(fahuoModel->item(row,13)->text());
    onelururenyuan = fahuoModel->item(row,13)->text();
    lururiqiDateEdit->setDate(QDate::fromString(fahuoModel->item(row,14)->text(),"yyyy-MM-dd"));
    onelururiqi = QDate::fromString(fahuoModel->item(row,14)->text(),"yyyy-MM-dd");
    lukubeizhuLineEdit->setText(fahuoModel->item(row,15)->text());
    onelukubeizhu = fahuoModel->item(row,15)->text();

}

void fucairukuDlg::on_fucaidalei()
{
    disconnect(fucaidaleiComboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(on_fucaixiaolei()));
    fucaidaleiComboBox->clear();
    fucaidaleiComboBox->setEnabled(true);
    const char * selectClass = "select Class from AuxiliaryCategory";
    db.sql_fillComboBoxItem(selectClass,fucaidaleiComboBox);
    connect(fucaidaleiComboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(on_fucaixiaolei()));
    fucaixiaoleiComboBox->setEnabled(true);

    QString chaxunSQL = QString("select SuoShuXiaoLei, SuoShuDaLei,GuiGe,DanWei,DanJia,SongHuoRenYuan,\
                                LianXiFangShi from fucaitongjibiao where FucaiName = '%1' group by FucaiName")
               .arg(fucainameComboBox->currentText());

    fucaidaleiComboBox->setCurrentText(db.sql_fetchrow_plus(chaxunSQL,1));
    fucaixiaoleiComboBox->setCurrentText(db.sql_fetchrow_plus(chaxunSQL,0));
    fucaiguigeLineEdit->setText(db.sql_fetchrow_plus(chaxunSQL,2));
    fucaidanweiLineEdit->setText(db.sql_fetchrow_plus(chaxunSQL,3));
    fucaidanjiaLineEdit->setText(db.sql_fetchrow_plus(chaxunSQL,4));
    songhuorenyuanLineEdit->setText(db.sql_fetchrow_plus(chaxunSQL,5));
    lianxifangshiLineEdit->setText(db.sql_fetchrow_plus(chaxunSQL,6));
}

void fucairukuDlg::on_fucaixiaolei()
{
    fucaixiaoleiComboBox->clear();
    for(int i = 1;i<29;i++)
    {
       QString fillSQL2 = QString("select Class%1 from AuxiliaryCategory where Class = '%2';").arg(i).arg(fucaidaleiComboBox->currentText());
       QString fileclass1 = db.sql_fetchrow_plus(fillSQL2,0);
       if(fileclass1 == "")
       {
           break;
       }
       QString fileSQL3 = QString("replace into fucaileibie set Class = '%1',Class1 = '%2';").arg(fucaidaleiComboBox->currentText(),fileclass1);
       db.sql_exec(fileSQL3);
    }
    QString fillSQL4 = QString("select Class1 from fucaileibie where Class = '%1';").arg(fucaidaleiComboBox->currentText());
    db.sql_fillComboBoxItem(fillSQL4,fucaixiaoleiComboBox);
}

void fucairukuDlg::on_fucaidanjia()
{
    rukuzongjineLineEdit->setText(QString::number(fucaidanjiaLineEdit->text().toDouble() * fucaishuliangLineEdit->text().toDouble(), 'f', 2));
}

void fucairukuDlg::on_fucaishuliang()
{
    rukuzongjineLineEdit->setText(QString::number(fucaidanjiaLineEdit->text().toDouble() * fucaishuliangLineEdit->text().toDouble(), 'f', 2));
}

void fucairukuDlg::createAction()
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

void fucairukuDlg::createTool()
{
    toolBar = new QToolBar(this);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar->addAction(newAction);
    toolBar->addAction(saveAction);
    toolBar->addAction(updateAction);
    toolBar->addAction(deleteAction);
}

void fucairukuDlg::on_newAction()
{
    saveAction->setEnabled(true);
    updateAction->setEnabled(false);
    deleteAction->setEnabled(false);
}

void fucairukuDlg::on_newAction_plus()
{
    saveAction->setEnabled(true);
    updateAction->setEnabled(false);
    deleteAction->setEnabled(false);

    QString searchSQL = QString("select FucaiNO from fucaitongjibiao order by FucaiNO+0 desc limit 1");
    rukudanhaoLineEdit->setText(QString::number(db.sql_fetchrow_plus(searchSQL.toStdString().data(),0).toDouble()+1));

    fucainameComboBox->clear();
    fucainameComboBox->setEnabled(true);
    fucainameComboBox->setEditable(true);
    db.sql_fillComboBoxItem("select FucaiName from fucaitongjibiao group by FucaiName",fucainameComboBox);

    fucaixiaoleiComboBox->clear();

    disconnect(fucaidaleiComboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(on_fucaixiaolei()));
    fucaidaleiComboBox->clear();
    fucaidaleiComboBox->setEnabled(true);
    const char * selectClass = "select Class from AuxiliaryCategory";
    db.sql_fillComboBoxItem(selectClass,fucaidaleiComboBox);
    connect(fucaidaleiComboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(on_fucaixiaolei()));

    fucaixiaoleiComboBox->setEnabled(true);
    fucaidanjiaLineEdit->clear();
    fucaishuliangLineEdit->clear();
    rukuzongjineLineEdit->clear();
    fucaiguigeLineEdit->clear();
    fucaidanweiLineEdit->clear();
    songhuorenyuanLineEdit->clear();
    lianxifangshiLineEdit->clear();
    lururenyuanLineEdit->setText(userName);
    lukubeizhuLineEdit->clear();
}

void fucairukuDlg::on_saveAction()
{
    if(fucainameComboBox->currentText().isEmpty()){
        QMessageBox::information(this,tr("错误"),tr("请输入辅材名称"),0,0,0);
        return;
    }
    if(fucaidanjiaLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("错误"),tr("请输入辅材单价"),0,0,0);
        return;
    }
    if(fucaishuliangLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("错误"),tr("请输入辅材数量"),0,0,0);
        return;
    }

    QString saveSQL = QString("insert into fucaitongjibiao (FucaiNO , FucaiName , SuoShuXiaoLei , SuoShuDaLei , GuiGe ,DanWei , DanJia , ShuLiang ,ZongJinE ,SongHuoRenYuan ,\
                              LianXiFangShi,CaiGouRen,CaiGouRenLianXiFangShi,LuRuRenYuan , LuRuRiQi ,BeiZhu) values ('%1','%2','%3','%4','%5','%6',\
                            '%7','%8','%9','%10','%11','%12','%13','%14','%15','%16');")
                        .arg(rukudanhaoLineEdit->text(),fucainameComboBox->currentText(),fucaixiaoleiComboBox->currentText(),fucaidaleiComboBox->currentText(),fucaiguigeLineEdit->text())
                        .arg(fucaidanweiLineEdit->text(),fucaidanjiaLineEdit->text(),fucaishuliangLineEdit->text(),rukuzongjineLineEdit->text(),songhuorenyuanLineEdit->text())
                        .arg(lianxifangshiLineEdit->text(),caigourenyuanLineEdit->text(),caigoulianxifangshiLineEdit->text(),lururenyuanLineEdit->text(),lururiqiDateEdit->date().toString("yyyy-MM-dd"),lukubeizhuLineEdit->text());
    int res = db.sql_exec(saveSQL.toStdString().data());
    if(res == -1){
        QMessageBox::information(this,tr("提示信息"),tr("保存失败"),0,0,0);
        return;

    }else{
        QString selectName = QString("select FucaiName,GuiGe from fucaitongjibiaothree where FucaiName = '%1' and GuiGe = '%2'").arg(fucainameComboBox->currentText(),fucaiguigeLineEdit->text());
        QString ret31 = db.sql_fetchrow_plus(selectName,0);

        /**************
         * if(相同规格的辅材不存在){
         *插入
         * }
        *******************/
        if(ret31 == ""){
            QString saveSQL3 = QString("insert into fucaitongjibiaothree (FucaiNO , FucaiName , SuoShuXiaoLei , SuoShuDaLei , GuiGe ,DanWei , DanJia , ShuLiang ,ZongJinE ,SongHuoRenYuan ,\
                                      LianXiFangShi ,LuRuRenYuan , LuRuRiQi ,BeiZhu) values ('%1','%2','%3','%4','%5','%6',\
                                    '%7','%8','%9','%10','%11','%12','%13','%14');")
                                .arg(rukudanhaoLineEdit->text(),fucainameComboBox->currentText(),fucaixiaoleiComboBox->currentText(),fucaidaleiComboBox->currentText(),fucaiguigeLineEdit->text())
                                .arg(fucaidanweiLineEdit->text(),fucaidanjiaLineEdit->text(),fucaishuliangLineEdit->text(),rukuzongjineLineEdit->text(),songhuorenyuanLineEdit->text())
                                .arg(lianxifangshiLineEdit->text(),lururenyuanLineEdit->text(),lururiqiDateEdit->date().toString("yyyy-MM-dd"),lukubeizhuLineEdit->text());
            db.sql_exec(saveSQL3.toStdString().data());
        }else{
            QString selectshuliang = QString("select ShuLiang from fucaitongjibiaothree where FucaiName = '%1' and GuiGe = '%2'").arg(fucainameComboBox->currentText(),fucaiguigeLineEdit->text());
            QString shuliang = db.sql_fetchrow_plus(selectshuliang,0);
            QString kucun = QString::number(shuliang.toInt() + fucaishuliangLineEdit->text().toInt(), 10);
            QString zongjine = QString::number(kucun.toDouble() * fucaidanjiaLineEdit->text().toDouble(),'f',2);
            QString updatethree = QString("update fucaitongjibiaothree set ShuLiang = '%1',ZongJinE = '%2' where FucaiName = '%3' and  GuiGe = '%4'").arg(kucun,zongjine,fucainameComboBox->currentText(),fucaiguigeLineEdit->text());
            qDebug()<<"updatethree"<<updatethree;
            db.sql_exec(updatethree);
        }

        QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
        rukudanhaoLineEdit->clear();
        fucainameComboBox->clear();
        fucaixiaoleiComboBox->clear();
        fucaidaleiComboBox->clear();
        fucaidanjiaLineEdit->clear();
        fucaishuliangLineEdit->clear();
        rukuzongjineLineEdit->clear();
        fucaiguigeLineEdit->clear();
        fucaidanweiLineEdit->clear();
        songhuorenyuanLineEdit->clear();
        lianxifangshiLineEdit->clear();
        lururenyuanLineEdit->clear();
        lukubeizhuLineEdit->clear();
        onefucaimingchengCombox->clear();
        db.sql_fillComboBoxItem("select FucaiName from fucaitongjibiao group by FucaiName",onefucaimingchengCombox);
        on_onechaxun();
        threeon_onechaxun();
    }
}

void fucairukuDlg::on_updateAction()
{
    if(fucainameComboBox->currentText().isEmpty()){
        QMessageBox::information(this,tr("错误"),tr("请输入辅材名称"),0,0,0);
        return;
    }
    if(fucaidanjiaLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("错误"),tr("请输入辅材单价"),0,0,0);
        return;
    }
    if(fucaishuliangLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("错误"),tr("请输入辅材数量"),0,0,0);
        return;
    }

    QString updateSQL = QString("update fucaitongjibiao set FucaiName = '%1', SuoShuXiaoLei ='%2', SuoShuDaLei  ='%3', GuiGe  ='%4',DanWei  ='%5', DanJia  ='%6', ShuLiang='%7' ,ZongJinE='%8' ,SongHuoRenYuan='%9' ,\
                              LianXiFangShi ='%10',CaiGouRen = '%11',CaiGouRenLianXiFangShi = '%12',LuRuRenYuan ='%13', LuRuRiQi ='%14',BeiZhu='%15' where FucaiNO = '%16'")
                        .arg(fucainameComboBox->currentText(),fucaixiaoleiComboBox->currentText(),fucaidaleiComboBox->currentText(),fucaiguigeLineEdit->text())
                        .arg(fucaidanweiLineEdit->text(),fucaidanjiaLineEdit->text(),fucaishuliangLineEdit->text(),rukuzongjineLineEdit->text(),songhuorenyuanLineEdit->text())
                        .arg(lianxifangshiLineEdit->text(),caigourenyuanLineEdit->text(),caigoulianxifangshiLineEdit->text(),lururenyuanLineEdit->text(),lururiqiDateEdit->date().toString("yyyy-MM-dd"),lukubeizhuLineEdit->text(),rukudanhaoLineEdit->text());
    int res = db.sql_exec(updateSQL.toStdString().data());
    if(res == -1){
        QMessageBox::information(this,tr("提示信息"),tr("保存失败"),0,0,0);
        return;

    }else{
        if(onefucainame == fucainameComboBox->currentText() && onefucaiguige == fucaiguigeLineEdit->text()){//辅材名字不变,其他信息改变的情况
            QString selectshuliang = QString("select ShuLiang from fucaitongjibiaothree where FucaiName = '%1' and GuiGe = '%2'").arg(fucainameComboBox->currentText(),fucaiguigeLineEdit->text());
            QString shuliang = db.sql_fetchrow_plus(selectshuliang,0);
            QString kucun = QString::number(shuliang.toInt() - onefucaishuliang.toInt() + fucaishuliangLineEdit->text().toInt(),10);
            QString zongjine = QString::number(kucun.toDouble() * fucaidanjiaLineEdit->text().toDouble(),'f',2);
            QString updatethree = QString("update fucaitongjibiaothree set ShuLiang = '%1',ZongJinE = '%2',SuoShuXiaoLei = '%3',SuoShuDaLei = '%4',DanWei = '%5',DanJia = '%6',SongHuoRenYuan = '%7',LianXiFangShi = '%8',LuRuRenYuan = '%9',LuRuRiQi = '%10',BeiZhu = '%11' where FucaiName = '%12' and GuiGe = '%13'")
                                            .arg(kucun,zongjine,fucaixiaoleiComboBox->currentText(),fucaidaleiComboBox->currentText(),fucaidanweiLineEdit->text())
                                            .arg(fucaidanjiaLineEdit->text(),songhuorenyuanLineEdit->text(),lianxifangshiLineEdit->text(),lururenyuanLineEdit->text())
                                            .arg(lururiqiDateEdit->date().toString("yyyy-MM-dd"),lukubeizhuLineEdit->text(),fucainameComboBox->currentText(),fucaiguigeLineEdit->text());
            db.sql_exec(updatethree);
        }else{//上面是名字规格都一致

            QString selectshuliang2 = QString("select ShuLiang from fucaitongjibiaothree where FucaiName = '%1' and GuiGe = '%2'").arg(onefucainame,onefucaiguige);
            QString shuliang2 = db.sql_fetchrow_plus(selectshuliang2,0);
            if(shuliang2 == "0" || shuliang2 == fucaishuliangLineEdit->text()){//这里判断了减没了的情况，没考虑原材料不存在的情况
                QString selectshuliang3 = QString("delete from fucaitongjibiaothree where FucaiName = '%1' and GuiGe = '%2'").arg(onefucainame,onefucaiguige);
                db.sql_exec(selectshuliang3);
            }

            QString sel = QString("select FucaiName,GuiGe,ShuLiang,FucaiNO from fucaitongjibiaothree where FucaiName='%1' and GuiGe= '%2'").arg(fucainameComboBox->currentText(),fucaiguigeLineEdit->text());
            if(db.sql_result(sel).isEmpty()){//本身没有
                QString saveSQL3 = QString("insert into fucaitongjibiaothree (FucaiNO , FucaiName , SuoShuXiaoLei , SuoShuDaLei , GuiGe ,DanWei , DanJia , ShuLiang ,ZongJinE ,SongHuoRenYuan ,\
                                          LianXiFangShi ,LuRuRenYuan , LuRuRiQi ,BeiZhu) values ('%1','%2','%3','%4','%5','%6',\
                                        '%7','%8','%9','%10','%11','%12','%13','%14');")
                                    .arg(rukudanhaoLineEdit->text(),fucainameComboBox->currentText(),fucaixiaoleiComboBox->currentText(),fucaidaleiComboBox->currentText(),fucaiguigeLineEdit->text())
                                    .arg(fucaidanweiLineEdit->text(),fucaidanjiaLineEdit->text(),fucaishuliangLineEdit->text(),rukuzongjineLineEdit->text(),songhuorenyuanLineEdit->text())
                                    .arg(lianxifangshiLineEdit->text(),lururenyuanLineEdit->text(),lururiqiDateEdit->date().toString("yyyy-MM-dd"),lukubeizhuLineEdit->text());
                db.sql_exec(saveSQL3.toStdString().data());
            }else {
                QString shuliang = db.sql_fetchrow_plus(sel,2);
                QString no =db.sql_fetchrow_plus(sel,3);
                qDebug()<<"shuliang:"<<shuliang<<"no"<<no;
                QString kucun = QString::number(shuliang.toInt() + fucaishuliangLineEdit->text().toInt(), 10);
                QString zongjine = QString::number(kucun.toDouble() * fucaidanjiaLineEdit->text().toDouble(),'f',2);
                QString updatethree = QString("replace into fucaitongjibiaothree(FucaiNO,FucaiName,SuoShuXiaoLei,SuoShuDaLei,GuiGe,DanWei,DanJia,ShuLiang,ZongJinE,SongHuoRenYuan ,\
                                              LianXiFangShi,LuRuRenYuan , LuRuRiQi,BeiZhu) value('%1','%2','%3','%4','%5','%6','%7','%8','%9','%10','%11','%12','%13','%14')")\
                                            .arg(no,fucainameComboBox->currentText(),fucaixiaoleiComboBox->currentText(),fucaidaleiComboBox->currentText(),fucaiguigeLineEdit->text(),fucaidanweiLineEdit->text(),fucaidanjiaLineEdit->text())
                                            .arg(kucun,zongjine,songhuorenyuanLineEdit->text(),lianxifangshiLineEdit->text())
                                            .arg(lururenyuanLineEdit->text(),lururiqiDateEdit->date().toString("yyyy-MM-dd"),lukubeizhuLineEdit->text());
                qDebug()<<"updatethree"<<updatethree;
                db.sql_exec(updatethree);
            }
        }

        QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
        rukudanhaoLineEdit->clear();
        fucainameComboBox->clear();
        fucaixiaoleiComboBox->clear();
        fucaidaleiComboBox->clear();
        fucaidanjiaLineEdit->clear();
        fucaishuliangLineEdit->clear();
        rukuzongjineLineEdit->clear();
        fucaiguigeLineEdit->clear();
        fucaidanweiLineEdit->clear();
        songhuorenyuanLineEdit->clear();
        lianxifangshiLineEdit->clear();
        lururenyuanLineEdit->clear();
        lukubeizhuLineEdit->clear();
        onefucaimingchengCombox->clear();
        db.sql_fillComboBoxItem("select FucaiName from fucaitongjibiao group by FucaiName",onefucaimingchengCombox);
        on_onechaxun();
        threeon_onechaxun();
    }
}

void fucairukuDlg::on_deleteAction()
{
    QString deleteSQL = QString("delete from fucaitongjibiao where FucaiNO ='%1' and GuiGe = '%2';").arg(rukudanhaoLineEdit->text(),fucaiguigeLineEdit->text());
    int res = db.sql_exec(deleteSQL.toStdString().data());
    if(res == 0){       
        QString selectshuliang = QString("select ShuLiang from fucaitongjibiaothree where FucaiName = '%1' and GuiGe = '%2'").arg(fucainameComboBox->currentText(),fucaiguigeLineEdit->text());
        QString shuliang = db.sql_fetchrow_plus(selectshuliang,0);
        QString kucun = QString::number(shuliang.toInt() - fucaishuliangLineEdit->text().toInt(), 10);
        QString zongjine = QString::number(kucun.toDouble() * fucaidanjiaLineEdit->text().toDouble(),'f',2);
        QString updatethree = QString("update fucaitongjibiaothree set ShuLiang = '%1',ZongJinE = '%2' where FucaiName = '%3' and GuiGe = '%4'").arg(kucun,zongjine,fucainameComboBox->currentText(),fucaiguigeLineEdit->text());
        db.sql_exec(updatethree);
        QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
        rukudanhaoLineEdit->clear();
        fucainameComboBox->clear();
        fucaixiaoleiComboBox->clear();
        fucaidaleiComboBox->clear();
        fucaidanjiaLineEdit->clear();
        fucaishuliangLineEdit->clear();
        rukuzongjineLineEdit->clear();
        fucaiguigeLineEdit->clear();
        fucaidanweiLineEdit->clear();
        songhuorenyuanLineEdit->clear();
        lianxifangshiLineEdit->clear();
        lururenyuanLineEdit->clear();
        lukubeizhuLineEdit->clear();
        onefucaimingchengCombox->clear();
        on_onechaxun();
        threeon_onechaxun();
    }
}
/*************************************入库结束*********************************************/


/*************************************出库开始*********************************************/
void fucairukuDlg::twoon_onechaxun()
{
    QString Time,fucaimingzi,fucaidalei,fucaixiaolei,songhuorenyuan;
    Time = QString(" and LuRuRiQi between '%1' and '%2'").arg(twodateEdit1->date().toString("yyyy-MM-dd"),twodateEdit2->date().addDays(1).toString("yyyy-MM-dd"));
    if(twofucaidaleiCheckBox->checkState() == 2){
        fucaidalei =  QString(" and SuoShuDaLei = '%1'").arg(twofudaleiCombox->currentText());
    }
    if(twofucaixiaoleiCheckBox->checkState() == 2){
        fucaixiaolei =  QString(" and SuoShuXiaoLei = '%1'").arg(twofucaixiaoleiCombox->currentText());
    }
    if(twofucaimingchengCheckBox->checkState() == 2){
        fucaimingzi =  QString(" and FucaiName = '%1'").arg(twofucaimingchengCombox->currentText());
    }
    if(twosonghuorenyuanCheckBox->checkState() == 2){
        songhuorenyuan =  QString(" and SongHuoRenYuan = '%1'").arg(twosonghuorenyuanCombox->currentText());
    }

    QString chaxunSQL = QString("select FucaiNO 出库单号, FucaiName 辅材名称, SuoShuXiaoLei 所属小类, SuoShuDaLei 所属大类, GuiGe 规格,DanWei 单位, DanJia 单价, ShuLiang 数量,ZongJinE 总金额,LingLiaoDanWei 领料单位,SongHuoRenYuan 领料人,\
                                ShiYongBuWei 使用部位,LianXiFangShi 联系方式,LuRuRenYuan 录入人员, LuRuRiQi 录入日期,BeiZhu 备注 from fucaitongjibiaotwo where FucaiNO is not null %1 %2 %3 %4 %5")
               .arg(Time,fucaidalei,fucaixiaolei,fucaimingzi,songhuorenyuan);
    db.showview_num(chaxunSQL,twofahuoView,&twofahuoModel,0);

}

void fucairukuDlg::on_toExcell2()
{
    view2Excel->Table2ExcelByHtml(twofahuoView,"辅材出库表");
}

void fucairukuDlg::twoShow_fahuoSupplyclick()
{

    twoupdateAction->setEnabled(true);
    twodeleteAction->setEnabled(true);
    twosaveAction->setEnabled(false);

    int row = twofahuoView->currentIndex().row();
    tworukudanhaoLineEdit->setText(twofahuoModel->item(row,0)->text());
    tworukudanhao = twofahuoModel->item(row,0)->text();

    twofucainameComboBox->clear();
    twofucainameComboBox->setEnabled(true);
    twofucainameComboBox->setEditable(true);
    twofucainameComboBox->setCurrentText(twofahuoModel->item(row,1)->text());
    twofucainame = twofahuoModel->item(row,1)->text();

    disconnect(twofucaidaleiComboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(twoon_fucaixiaolei()));
    twofucaidaleiComboBox->clear();
    twofucaidaleiComboBox->setEnabled(true);
    const char * selectClass = "select Class from AuxiliaryCategory";
    db.sql_fillComboBoxItem(selectClass,twofucaidaleiComboBox);
    connect(twofucaidaleiComboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(twoon_fucaixiaolei()));

    twofucaidaleiComboBox->setCurrentText(twofahuoModel->item(row,3)->text());
    twofucaidalei = twofahuoModel->item(row,3)->text();
    twofucaixiaoleiComboBox->setCurrentText(twofahuoModel->item(row,2)->text());
    twofucaixiaolei = twofahuoModel->item(row,2)->text();
    twofucaixiaoleiComboBox->setEnabled(true);
    twofucaidanjiaLineEdit->setText(twofahuoModel->item(row,6)->text());
    twofucaidanjia = twofahuoModel->item(row,6)->text();
    twofucaishuliangLineEdit->setText(twofahuoModel->item(row,7)->text());
    twofucaishuliang = twofahuoModel->item(row,7)->text();
    tworukuzongjineLineEdit->setText(twofahuoModel->item(row,8)->text());
    tworukuzongjine = twofahuoModel->item(row,8)->text();
    twofucaiguigeLineEdit->setText(twofahuoModel->item(row,4)->text());
    twofucaiguige = twofahuoModel->item(row,4)->text();
    twofucaidanweiLineEdit->setText(twofahuoModel->item(row,5)->text());
    twofucaidanwei = twofahuoModel->item(row,5)->text();
    twolingliaodanweiLineEdit->setText(twofahuoModel->item(row,9)->text());
    twosonghuorenyuanLineEdit->setText(twofahuoModel->item(row,10)->text());
    twosonghuorenyuan = twofahuoModel->item(row,10)->text();
    twoshiyongbuweiLineEdit->setText(twofahuoModel->item(row,11)->text());
    twolianxifangshiLineEdit->setText(twofahuoModel->item(row,12)->text());
    twolianxifangshi = twofahuoModel->item(row,12)->text();
    twolururenyuanLineEdit->setText(twofahuoModel->item(row,13)->text());
    twolururenyuan = twofahuoModel->item(row,13)->text();
    twolururiqiDateEdit->setDate(QDate::fromString(twofahuoModel->item(row,14)->text(),"yyyy-MM-dd"));
    twolururiqi = QDate::fromString(twofahuoModel->item(row,14)->text(),"yyyy-MM-dd");
    twolukubeizhuLineEdit->setText(twofahuoModel->item(row,15)->text());
    twolukubeizhu = twofahuoModel->item(row,15)->text();

}

void fucairukuDlg::twoon_fucaidalei()
{
    disconnect(twofucaidaleiComboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(twoon_fucaixiaolei()));
    twofucaidaleiComboBox->clear();
    twofucaidaleiComboBox->setEnabled(true);
    const char * selectClass = "select Class from AuxiliaryCategory";
    db.sql_fillComboBoxItem(selectClass,twofucaidaleiComboBox);
    connect(twofucaidaleiComboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(twoon_fucaixiaolei()));
    twofucaixiaoleiComboBox->setEnabled(true);

    QString chaxunSQL = QString("select SuoShuXiaoLei, SuoShuDaLei,GuiGe,DanWei,DanJia,SongHuoRenYuan,\
                                LianXiFangShi,ShuLiang from fucaitongjibiaothree where FucaiName = '%1' group by FucaiName")
               .arg(twofucainameComboBox->currentText());

    twofucaidaleiComboBox->setCurrentText(db.sql_fetchrow_plus(chaxunSQL,1));
    twofucaixiaoleiComboBox->setCurrentText(db.sql_fetchrow_plus(chaxunSQL,0));
    twofucaiguigeLineEdit->setText(db.sql_fetchrow_plus(chaxunSQL,2));
    twofucaidanweiLineEdit->setText(db.sql_fetchrow_plus(chaxunSQL,3));
    twofucaidanjiaLineEdit->setText(db.sql_fetchrow_plus(chaxunSQL,4));
//    twosonghuorenyuanLineEdit->setText(db.sql_fetchrow_plus(chaxunSQL,5));
//    twolianxifangshiLineEdit->setText(db.sql_fetchrow_plus(chaxunSQL,6));
    QMessageBox::information(this,tr("库存"),tr("库存总数：")+db.sql_fetchrow_plus(chaxunSQL,7),0,0,0);
//    twofucaishuliangLineEdit->setText(db.sql_fetchrow_plus(chaxunSQL,7));
}

void fucairukuDlg::twoon_fucaixiaolei()
{
    twofucaixiaoleiComboBox->clear();
    for(int i = 1;i<29;i++)
    {
       QString fillSQL2 = QString("select Class%1 from AuxiliaryCategory where Class = '%2';").arg(i).arg(twofucaidaleiComboBox->currentText());
       QString fileclass1 = db.sql_fetchrow_plus(fillSQL2,0);
       if(fileclass1 == "")
       {
           break;
       }
       QString fileSQL3 = QString("replace into fucaileibie set Class = '%1',Class1 = '%2';").arg(twofucaidaleiComboBox->currentText(),fileclass1);
       db.sql_exec(fileSQL3);
    }
    QString fillSQL4 = QString("select Class1 from fucaileibie where Class = '%1';").arg(twofucaidaleiComboBox->currentText());
    db.sql_fillComboBoxItem(fillSQL4,twofucaixiaoleiComboBox);
}

void fucairukuDlg::twoon_fucaidanjia()
{
    tworukuzongjineLineEdit->setText(QString::number(twofucaidanjiaLineEdit->text().toDouble() * twofucaishuliangLineEdit->text().toDouble(), 'f', 2));
}

void fucairukuDlg::twoon_fucaishuliang()
{
    tworukuzongjineLineEdit->setText(QString::number(twofucaidanjiaLineEdit->text().toDouble() * twofucaishuliangLineEdit->text().toDouble(), 'f', 2));
}

void fucairukuDlg::twocreateAction()
{
    twonewAction = new QAction(tr("新增"),this);
    twonewAction->setIcon(QIcon(":/image/new.png"));
    connect(twonewAction,SIGNAL(triggered()),this,SLOT(twoon_newAction_plus()));
    twosaveAction = new QAction(tr("保存"),this);
    twosaveAction->setIcon(QIcon(":/image/save.png"));
    connect(twosaveAction,SIGNAL(triggered()),this,SLOT(twoon_saveAction()));
    twoupdateAction = new QAction(tr("修改"),this);
    twoupdateAction->setEnabled(false);
    twoupdateAction->setIcon(QIcon(":/image/update.png"));
    connect(twoupdateAction,SIGNAL(triggered()),this,SLOT(twoon_updateAction()));
    twodeleteAction = new QAction(tr("删除"),this);
    twodeleteAction->setEnabled(false);
    twodeleteAction->setIcon(QIcon(":/image/delete.png"));
    connect(twodeleteAction,SIGNAL(triggered()),this,SLOT(twoon_deleteAction()));
}

void fucairukuDlg::twocreateTool()
{
    twotoolBar = new QToolBar(this);
    twotoolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    twotoolBar->addAction(twonewAction);
    twotoolBar->addAction(twosaveAction);
    twotoolBar->addAction(twoupdateAction);
    twotoolBar->addAction(twodeleteAction);
}

void fucairukuDlg::twoon_newAction()
{
    twosaveAction->setEnabled(true);
    twoupdateAction->setEnabled(false);
    twodeleteAction->setEnabled(false);
}

void fucairukuDlg::twoon_newAction_plus()
{
    twosaveAction->setEnabled(true);
    twoupdateAction->setEnabled(false);
    twodeleteAction->setEnabled(false);

    QString searchSQL = QString("select FucaiNO from fucaitongjibiaotwo order by FucaiNO+0 desc limit 1");
    tworukudanhaoLineEdit->setText(QString::number(db.sql_fetchrow_plus(searchSQL.toStdString().data(),0).toDouble()+1));

    twofucainameComboBox->clear();
    twofucainameComboBox->setEnabled(true);
    twofucainameComboBox->setEditable(true);
    db.sql_fillComboBoxItem("select FucaiName from fucaitongjibiao group by FucaiName",twofucainameComboBox);

    twofucaixiaoleiComboBox->clear();

    disconnect(twofucaidaleiComboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(twoon_fucaixiaolei()));
    twofucaidaleiComboBox->clear();
    twofucaidaleiComboBox->setEnabled(true);
    const char * selectClass = "select Class from AuxiliaryCategory";
    db.sql_fillComboBoxItem(selectClass,twofucaidaleiComboBox);
    connect(twofucaidaleiComboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(twoon_fucaixiaolei()));

    twofucaixiaoleiComboBox->setEnabled(true);
    twofucaidanjiaLineEdit->clear();
    twofucaishuliangLineEdit->clear();
    tworukuzongjineLineEdit->clear();
    twofucaiguigeLineEdit->clear();
    twofucaidanweiLineEdit->clear();
    twosonghuorenyuanLineEdit->clear();
    twolianxifangshiLineEdit->clear();
    twolururenyuanLineEdit->setText(userName);
    twolukubeizhuLineEdit->clear();
}

void fucairukuDlg::twoon_saveAction()
{
    //判断 辅材 存不存在，存在继续判断出库的 数量 是否《= 库存数量
    QString selecttwo = QString("select FucaiName,ShuLiang from fucaitongjibiaothree where FucaiName = '%1' and GuiGe = '%2'").arg(twofucainameComboBox->currentText(),twofucaiguigeLineEdit->text());
    if(db.sql_result(selecttwo).isEmpty()){//本身没有
        QMessageBox::information(this,tr("错误"),tr("辅材不存在"),0,0,0);
        return;
    }
    if(db.sql_fetchrow_plus(selecttwo,1).toDouble()<=0){
        QString deletethree = QString("delete from fucaitongjibiaothree where FucaiName = '%1' and GuiGe = '%2'").arg(twofucainameComboBox->currentText(),twofucaiguigeLineEdit->text());
        db.sql_exec(deletethree);

    }
    if(db.sql_fetchrow_plus(selecttwo,1).toDouble() < twofucaishuliangLineEdit->text().toDouble())
    {
        QMessageBox::information(this,tr("错误"),tr("出库数量大于库存数量"),0,0,0);
        return;
    }

    if(twofucainameComboBox->currentText().isEmpty()){
        QMessageBox::information(this,tr("错误"),tr("请输入辅材名称"),0,0,0);
        return;
    }
    if(twofucaidanjiaLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("错误"),tr("请输入辅材单价"),0,0,0);
        return;
    }
    if(twofucaishuliangLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("错误"),tr("请输入辅材数量"),0,0,0);
        return;
    }

    QString saveSQL = QString("insert into fucaitongjibiaotwo (FucaiNO , FucaiName , SuoShuXiaoLei , SuoShuDaLei , GuiGe ,DanWei , DanJia , ShuLiang ,ZongJinE ,LingLiaoDanWei,SongHuoRenYuan ,\
                             ShiYongBuWei,LianXiFangShi ,LuRuRenYuan , LuRuRiQi ,BeiZhu) values ('%1','%2','%3','%4','%5','%6',\
                            '%7','%8','%9','%10','%11','%12','%13','%14','%15','%16');")
                        .arg(tworukudanhaoLineEdit->text(),twofucainameComboBox->currentText(),twofucaixiaoleiComboBox->currentText(),twofucaidaleiComboBox->currentText(),twofucaiguigeLineEdit->text())
                        .arg(twofucaidanweiLineEdit->text(),twofucaidanjiaLineEdit->text(),twofucaishuliangLineEdit->text(),tworukuzongjineLineEdit->text(),twolingliaodanweiLineEdit->text(),twosonghuorenyuanLineEdit->text())
                        .arg(twoshiyongbuweiLineEdit->text(),twolianxifangshiLineEdit->text(),twolururenyuanLineEdit->text(),twolururiqiDateEdit->date().toString("yyyy-MM-dd"),twolukubeizhuLineEdit->text());
    int res = db.sql_exec(saveSQL.toStdString().data());
    if(res == -1){
        QMessageBox::information(this,tr("提示信息"),tr("保存失败"),0,0,0);
        return;

    }else{
        QString selectshuliang = QString("select ShuLiang from fucaitongjibiaothree where FucaiName = '%1' and GuiGe = '%2'").arg(twofucainameComboBox->currentText(),twofucaiguigeLineEdit->text());
        QString shuliang = db.sql_fetchrow_plus(selectshuliang,0);
        QString kucun = QString::number(shuliang.toInt() - twofucaishuliangLineEdit->text().toInt(), 10);
        QString zongjine = QString::number(kucun.toDouble() * twofucaidanjiaLineEdit->text().toDouble(),'f',2);
        QString updatethree = QString("update fucaitongjibiaothree set ShuLiang = '%1',ZongJinE = '%2' where FucaiName = '%3' and GuiGe = '%4'").arg(kucun,zongjine,twofucainameComboBox->currentText(),twofucaiguigeLineEdit->text());
        db.sql_exec(updatethree);
        QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
        tworukudanhaoLineEdit->clear();
        twofucainameComboBox->clear();
        twofucaixiaoleiComboBox->clear();
        twofucaidaleiComboBox->clear();
        twofucaidanjiaLineEdit->clear();
        twofucaishuliangLineEdit->clear();
        tworukuzongjineLineEdit->clear();
        twofucaiguigeLineEdit->clear();
        twofucaidanweiLineEdit->clear();
        twosonghuorenyuanLineEdit->clear();
        twolianxifangshiLineEdit->clear();
        twolururenyuanLineEdit->clear();
        twolukubeizhuLineEdit->clear();
        twofucaimingchengCombox->clear();
        db.sql_fillComboBoxItem("select FucaiName from fucaitongjibiao group by FucaiName",twofucaimingchengCombox);
        twoon_onechaxun();
        threeon_onechaxun();
    }
}

void fucairukuDlg::twoon_updateAction()
{
    //判断 辅材 存不存在，存在继续判断出库的 数量 是否《= 库存数量
    QString selecttwo = QString("select FucaiName,ShuLiang from fucaitongjibiao where FucaiName = '%1' and GuiGe = '%2'").arg(twofucainameComboBox->currentText(),twofucaiguigeLineEdit->text());
    if(db.sql_result(selecttwo).isEmpty()){//本身没有
        QMessageBox::information(this,tr("错误"),tr("辅材不存在"),0,0,0);
        return;
    }
    if(db.sql_fetchrow_plus(selecttwo,1).toDouble() <= twofucaishuliangLineEdit->text().toDouble())
    {
        QMessageBox::information(this,tr("错误"),tr("出库数量大于库存数量"),0,0,0);
        return;
    }

    if(twofucainameComboBox->currentText().isEmpty()){
        QMessageBox::information(this,tr("错误"),tr("请输入辅材名称"),0,0,0);
        return;
    }
    if(twofucaidanjiaLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("错误"),tr("请输入辅材单价"),0,0,0);
        return;
    }
    if(twofucaishuliangLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("错误"),tr("请输入辅材数量"),0,0,0);
        return;
    }

    QString updateSQL = QString("update fucaitongjibiaotwo set FucaiName = '%1', SuoShuXiaoLei ='%2', SuoShuDaLei  ='%3', GuiGe  ='%4',DanWei  ='%5', DanJia  ='%6', ShuLiang='%7' ,ZongJinE='%8' ,LingLiaoDanWei='%9',SongHuoRenYuan='%10',ShiYongBuWei='%11',\
                              LianXiFangShi ='%12',LuRuRenYuan ='%13', LuRuRiQi ='%14',BeiZhu='%15' where FucaiNO = '%16'")
                        .arg(twofucainameComboBox->currentText(),twofucaixiaoleiComboBox->currentText(),twofucaidaleiComboBox->currentText(),twofucaiguigeLineEdit->text())
                        .arg(twofucaidanweiLineEdit->text(),twofucaidanjiaLineEdit->text(),twofucaishuliangLineEdit->text(),tworukuzongjineLineEdit->text(),twolingliaodanweiLineEdit->text(),twosonghuorenyuanLineEdit->text(),twoshiyongbuweiLineEdit->text())
                        .arg(twolianxifangshiLineEdit->text(),twolururenyuanLineEdit->text(),twolururiqiDateEdit->date().toString("yyyy-MM-dd"),twolukubeizhuLineEdit->text(),tworukudanhaoLineEdit->text());
    int res = db.sql_exec(updateSQL.toStdString().data());
    if(res == -1){
        QMessageBox::information(this,tr("提示信息"),tr("保存失败"),0,0,0);
        return;

    }else{
        /****************更新旧的********************/
        QString selectyuanshuliang = QString("select ShuLiang,DanJia from fucaitongjibiaothree where FucaiName = '%1' and GuiGe = '%2'").arg(twofucainame,twofucaiguige);
        QString yuanshuliang = db.sql_fetchrow_plus(selectyuanshuliang,0);
        QString yuankucun = QString::number(yuanshuliang.toInt() + twofucaishuliang.toInt(),10);
        QString yuanzongjine = QString::number(yuankucun.toDouble() * db.sql_fetchrow_plus(yuanshuliang,1).toDouble(),'f',2);
        QString updateyuanthree = QString("update fucaitongjibiaothree set ShuLiang = '%1',ZongJinE = '%2' where  FucaiName = '%3' and GuiGe = '%4'").arg(yuankucun,yuanzongjine,twofucainame,twofucaiguige);
        db.sql_exec(updateyuanthree);
        /*****************更新新的********************/
        QString selectshuliang = QString("select ShuLiang,DanJia from fucaitongjibiaothree where FucaiName = '%1' and GuiGe = '%2'").arg(twofucainameComboBox->currentText(),twofucaiguigeLineEdit->text());
        QString shuliang = db.sql_fetchrow_plus(selectshuliang,0);
        QString kucun = QString::number(shuliang.toInt() - twofucaishuliangLineEdit->text().toInt(),10);
        QString zongjine = QString::number(kucun.toDouble() * twofucaidanjiaLineEdit->text().toDouble(),'f',2);
        QString updatethree = QString("update fucaitongjibiaothree set ShuLiang = '%1',ZongJinE = '%2',SuoShuXiaoLei = '%3',SuoShuDaLei = '%4',DanWei = '%5',DanJia = '%6',SongHuoRenYuan = '%7',LianXiFangShi = '%8',LuRuRenYuan = '%9',LuRuRiQi = '%10',BeiZhu = '%11' where FucaiName = '%12' and GuiGe = '%13'")
                                        .arg(kucun,zongjine,twofucaixiaoleiComboBox->currentText(),twofucaidaleiComboBox->currentText(),twofucaidanweiLineEdit->text())
                                        .arg(twofucaidanjiaLineEdit->text(),twosonghuorenyuanLineEdit->text(),twolianxifangshiLineEdit->text(),twolururenyuanLineEdit->text())
                                        .arg(twolururiqiDateEdit->date().toString("yyyy-MM-dd"),twolukubeizhuLineEdit->text(),twofucainameComboBox->currentText(),twofucaiguigeLineEdit->text());
        db.sql_exec(updatethree);

        QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
        tworukudanhaoLineEdit->clear();
        twofucainameComboBox->clear();
        twofucaixiaoleiComboBox->clear();
        twofucaidaleiComboBox->clear();
        twofucaidanjiaLineEdit->clear();
        twofucaishuliangLineEdit->clear();
        tworukuzongjineLineEdit->clear();
        twofucaiguigeLineEdit->clear();
        twofucaidanweiLineEdit->clear();
        twosonghuorenyuanLineEdit->clear();
        twolianxifangshiLineEdit->clear();
        twolururenyuanLineEdit->clear();
        twolukubeizhuLineEdit->clear();
        twofucaimingchengCombox->clear();
        db.sql_fillComboBoxItem("select FucaiName from fucaitongjibiao group by FucaiName",twofucaimingchengCombox);
        twoon_onechaxun();
        threeon_onechaxun();
    }
}

void fucairukuDlg::twoon_deleteAction()
{

    QString selectshuliangthree = QString("select ShuLiang from fucaitongjibiaothree where FucaiName = '%1' and GuiGe = '%2'").arg(twofucainameComboBox->currentText(),twofucaiguigeLineEdit->text());
    QString shuliangthree = db.sql_fetchrow_plus(selectshuliangthree,0);
    if(shuliangthree == twofucaishuliangLineEdit->text()){
        QString saveSQL3 = QString("insert into fucaitongjibiaothree (FucaiNO , FucaiName , SuoShuXiaoLei , SuoShuDaLei , GuiGe ,DanWei , DanJia , ShuLiang ,ZongJinE ,SongHuoRenYuan ,\
                                  LianXiFangShi ,LuRuRenYuan , LuRuRiQi ,BeiZhu) values ('%1','%2','%3','%4','%5','%6',\
                                '%7','%8','%9','%10','%11','%12','%13','%14');")
                            .arg(tworukudanhaoLineEdit->text(),twofucainameComboBox->currentText(),twofucaixiaoleiComboBox->currentText(),twofucaidaleiComboBox->currentText(),twofucaiguigeLineEdit->text())
                            .arg(twofucaidanweiLineEdit->text(),twofucaidanjiaLineEdit->text(),twofucaishuliangLineEdit->text(),tworukuzongjineLineEdit->text(),twosonghuorenyuanLineEdit->text())
                            .arg(twolianxifangshiLineEdit->text(),twolururenyuanLineEdit->text(),twolururiqiDateEdit->date().toString("yyyy-MM-dd"),twolukubeizhuLineEdit->text());
        db.sql_exec(saveSQL3.toStdString().data());
    }



    QString deleteSQL = QString("delete from fucaitongjibiaotwo where FucaiNO ='%1' and GuiGe = '%2';").arg(tworukudanhaoLineEdit->text(),twofucaiguigeLineEdit->text());
    qDebug()<<deleteSQL;
    int res = db.sql_exec(deleteSQL.toStdString().data());
    if(res == 0){
        QString selectshuliang = QString("select ShuLiang from fucaitongjibiaothree where FucaiName = '%1' and GuiGe = '%2'").arg(twofucainameComboBox->currentText(),twofucaiguigeLineEdit->text());
        QString shuliang = db.sql_fetchrow_plus(selectshuliang,0);
        QString kucun = QString::number(shuliang.toInt() + twofucaishuliangLineEdit->text().toInt(), 10);
        QString zongjine = QString::number(kucun.toDouble() * twofucaidanjiaLineEdit->text().toDouble(),'f',2);
        QString updatethree = QString("update fucaitongjibiaothree set ShuLiang = '%1',ZongJinE = '%2' where FucaiName = '%3' and GuiGe = '%4'").arg(kucun,zongjine,twofucainameComboBox->currentText(),twofucaiguigeLineEdit->text());
        db.sql_exec(updatethree);
        QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
        twoon_onechaxun();
        threeon_onechaxun();
    }
}

void fucairukuDlg::threeon_onechaxun()
{
    QString fucaimingzi,fucaidalei,fucaixiaolei;

    if(threefucaidaleiCheckBox->checkState() == 2){
        fucaidalei =  QString(" and SuoShuDaLei = '%1'").arg(threefudaleiCombox->currentText());
    }
    if(threefucaixiaoleiCheckBox->checkState() == 2){
        fucaixiaolei =  QString(" and SuoShuXiaoLei = '%1'").arg(threefucaixiaoleiCombox->currentText());
    }
    if(threefucaimingchengCheckBox->checkState() == 2){
        fucaimingzi =  QString(" and FucaiName = '%1'").arg(threefucaimingchengCombox->currentText());
    }

    QString chaxunSQL = QString("select FucaiNO 库存单号, FucaiName 辅材名称, SuoShuXiaoLei 所属小类, SuoShuDaLei 所属大类, GuiGe 规格,DanWei 单位, DanJia 单价, ShuLiang 数量,ZongJinE 总金额,SongHuoRenYuan 供应商,\
               LianXiFangShi 联系方式,LuRuRenYuan 录入人员, LuRuRiQi 录入日期,BeiZhu 备注 from fucaitongjibiaothree where FucaiName is not null %1 %2 %3 ")
                                                                            .arg(fucaimingzi,fucaidalei,fucaixiaolei);
            db.showview_num(chaxunSQL,threefahuoView,&threefahuoModel,0);
}

void fucairukuDlg::on_toExcell3()
{
        view2Excel->Table2ExcelByHtml(threefahuoView,"辅材库存表");
}

/*************************************出库结束*********************************************/
