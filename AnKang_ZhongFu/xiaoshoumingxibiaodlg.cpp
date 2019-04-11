#include "xiaoshoumingxibiaodlg.h"
#include "widget.h"

extern mymysql db;

xiaoshoumingxibiaoDlg::xiaoshoumingxibiaoDlg(QWidget *parent) :
    QDialog(parent)
{
    library = new QLibrary("MyReportDll",this);

    QLabel *label1 = new QLabel(tr("发货时间"),this);
    label1->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label2 = new QLabel(tr("--"),this);
    label2->setAlignment(Qt::AlignCenter);

    reportView = new QAxWidget(this);//报表显示窗口
    reportView->setControl("{9207E7EB-4CE3-40E1-8A5A-77C43DA9F503}");
    m_report = new QAxObject(this);//报表主体对象
    m_report->setControl("{4764040E-4222-4DEC-9F2E-82D46E212B3A}");
    reportView->dynamicCall("SetReport(IfrxReport*)", m_report->asVariant());//关联报表窗口和报表主体对象

    dateEdit1 = new QDateTimeEdit(this);
    dateEdit1->setDate(QDate::currentDate().addDays(-1));
    dateEdit1->setTime(QTime::fromString("00:00:00","hh:mm:ss"));
    dateEdit1->setCalendarPopup(true);
    dateEdit2 = new QDateTimeEdit(this);
    dateEdit2->setDate(QDate::currentDate());
    dateEdit2->setTime(QTime::fromString("00:00:00","hh:mm:ss"));
    dateEdit2->setCalendarPopup(true);

    checkBox1 = new QCheckBox(tr("厂地名称"),this);
    checkBox2 = new QCheckBox(tr("生产机组"),this);
    checkBox3 = new QCheckBox(tr("客户名称"),this);
    checkBox4 = new QCheckBox(tr("砼车"),this);
    checkBox5 = new QCheckBox(tr("砼车司机"),this);
    checkBox6 = new QCheckBox(tr("工程名称"),this);
    checkBox7 = new QCheckBox(tr("浇筑方式"),this);
    checkBox8 = new QCheckBox(tr("包含作废任务单"),this);
    checkBox9 = new QCheckBox(tr("砼标号"),this);

    comBox1 = new QComboBox(this);
    comBox1->setEditable(true);
    comBox2 = new QComboBox(this);
    comBox2->setEditable(true);
    comBox3 = new QComboBox(this);
    comBox3->setEditable(true);
    comBox4 = new QComboBox(this);
    comBox4->setEditable(true);
    comBox5 = new QComboBox(this);
    comBox5->setEditable(true);
    comBox6 = new QComboBox(this);
    comBox6->setEditable(true);
    comBox7 = new QComboBox(this);
    comBox7->setEditable(true);
    comBox9 = new QComboBox(this);
    comBox9->setEditable(true);



    btn1 = new QPushButton(tr("销售明细表"),this);
    connect(btn1,SIGNAL(clicked()),this,SLOT(on_xiaoshoumingxi()));
    shengchanzongfangliangBtn = new QPushButton(tr("生产总方量表"),this);
    connect(shengchanzongfangliangBtn,SIGNAL(clicked()),this,SLOT(on_shengchanzongfang()));
    shengchanzongfangliangBtn->setHidden(true);
    btn2 = new QPushButton(tr("发货汇总"),this);
    connect(btn2,SIGNAL(clicked()),this,SLOT(on_fahuohuizong()));
    btn3 = new QPushButton(tr("干粉发货"),this);
    connect(btn3,SIGNAL(clicked()),this,SLOT(on_ganfenfahuo()));
    btn3->setHidden(true);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label1,0,0);
    layout->addWidget(dateEdit1,0,1);
    layout->addWidget(label2,0,2);
    layout->addWidget(dateEdit2,0,3);
    layout->addWidget(checkBox1,0,4);
    layout->addWidget(comBox1,0,5);
    layout->addWidget(checkBox2,0,6);
    layout->addWidget(comBox2,0,7);
    layout->addWidget(btn1,0,8,2,1,Qt::AlignVCenter);
//    layout->addWidget(shengchanzongfangliangBtn,0,9,2,1,Qt::AlignVCenter);
    layout->addWidget(btn2,0,9,2,1,Qt::AlignVCenter);
//    layout->addWidget(btn3,0,11,2,1,Qt::AlignVCenter);
    layout->addWidget(checkBox3,1,0);
    layout->addWidget(comBox3,1,1,1,3);
    layout->addWidget(checkBox4,1,4);
    layout->addWidget(comBox4,1,5);
    layout->addWidget(checkBox5,1,6);
    layout->addWidget(comBox5,1,7);
    layout->addWidget(checkBox6,2,0);
    layout->addWidget(comBox6,2,1,1,3);
    layout->addWidget(checkBox7,2,4);
    layout->addWidget(comBox7,2,5);
    layout->addWidget(checkBox9,2,6);
    layout->addWidget(comBox9,2,7);

    layout->addWidget(checkBox8,2,8);
    layout->setColumnStretch(0,0);
    layout->setColumnStretch(1,1);
    layout->setColumnStretch(2,0);
    layout->setColumnStretch(3,1);
    layout->setColumnStretch(4,0);
    layout->setColumnStretch(5,1);
    layout->setColumnStretch(6,0);
    layout->setColumnStretch(7,1);
    layout->setColumnStretch(8,1);
    layout->setColumnStretch(9,1);
    layout->setColumnStretch(10,1);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(layout);
    vlayout->addWidget(reportView);

    const char *fillcomBox1SQL = "select PlantName from FactorySetting;";
    db.sql_fillComboBoxItem(fillcomBox1SQL,comBox1);

    const char *fillcomBox2SQL = "select UnitName from UnitSetting;";
    db.sql_fillComboBoxItem(fillcomBox2SQL,comBox2);

    const char *fillcomBox3SQL = "select CustomerName from CustomerFiles;";
    db.sql_fillComboBoxItem(fillcomBox3SQL,comBox3);

    const char *fillcomBox4SQL = "select Vehiclenumber from ConcreteVehicleInformation;";
    db.sql_fillComboBoxItem(fillcomBox4SQL,comBox4);

    const char *fillcomBox5SQL = "select DriverName from ConcreteTruckDriver;";
    db.sql_fillComboBoxItem(fillcomBox5SQL,comBox5);

    const char *fillcomBox6SQL = "select Engineering from ProductionNotice group by Engineering;";
    db.sql_fillComboBoxItem(fillcomBox6SQL,comBox6);

    const char *fillcomBox7SQL = "select PouringMethod from ProductionNotice group by PouringMethod;";
    db.sql_fillComboBoxItem(fillcomBox7SQL,comBox7);

    const char *fillcomBox9SQL = "select TemplateName from ProductionNotice group by TemplateName;";
    db.sql_fillComboBoxItem(fillcomBox9SQL,comBox9);

}

void xiaoshoumingxibiaoDlg::refresh()
{

}

void xiaoshoumingxibiaoDlg::on_xiaoshoumingxi()
{
    QString changdimingcheng,shengchanjizu,kehumingcheng,tongche,tongchesiji,gongchengmingcheng,xianjinrenwudan,jiaozhufangshi,tongbiaohao;
    if(checkBox1->checkState() == 2){
        changdimingcheng = QString(" and PlantName='%1'").arg(comBox1->currentText());
    }
    if(checkBox2->checkState() == 2){
        shengchanjizu = QString(" and Unit='%1'").arg(comBox2->currentText());
    }
    if(checkBox3->checkState() == 2){
        kehumingcheng = QString(" and Customer='%1'").arg(comBox3->currentText());
    }
    if(checkBox4->checkState() == 2){
        tongche = QString(" and DeliveryVehicle='%1'").arg(comBox4->currentText());
    }
    if(checkBox5->checkState() == 2){
        tongchesiji = QString(" and Driver='%1'").arg(comBox5->currentText());
    }
    if(checkBox6->checkState() == 2){
        gongchengmingcheng = QString(" and Engineering='%1'").arg(comBox6->currentText());
    }
    if(checkBox7->checkState() == 2){
        jiaozhufangshi = QString(" and PouringMethod ='%1'").arg(comBox7->currentText());
    }

    if(checkBox8->checkState() == 0){
        xianjinrenwudan = " and MortarTotal='否'";
    }

    if(checkBox9->checkState() == 2){
        tongbiaohao = QString(" and TemplateName ='%1'").arg(comBox9->currentText());
    }

    QString baobiaoSQL = QString("select *,MID(OutboundTime,1,10) from ProductionNotice where Flag = '0' and OutboundTime between '%1' and '%2'\
                                 %3 %4 %5 %6 %7 %8 %9 %10 %11 order by Customer,Engineering,RecordNumber,PouringPosition,StrengthGrade;")
            .arg(dateEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),dateEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),
                 changdimingcheng,shengchanjizu,kehumingcheng,tongche,tongchesiji,gongchengmingcheng).arg(xianjinrenwudan,jiaozhufangshi,tongbiaohao);
    qDebug()<<baobiaoSQL;
    if(library->load()){
        typedef void (*pFunc)(const char *,const char *);
        pFunc function=(pFunc)library->resolve("loadmyreport");
        if(function){
            function("report/report3.fr3",baobiaoSQL.toLocal8Bit().data());
            m_report->dynamicCall("LoadReportFromFile(QString)", "report/report3.fr3");
            m_report->dynamicCall("ShowReport()");
        }else{
            QMessageBox::information(this,tr("错误"),library->errorString(),0,0,0);
        }
    }
    else{
        QMessageBox::information(this,tr("错误"),library->errorString(),0,0,0);
    }
}

void xiaoshoumingxibiaoDlg::on_shengchanzongfang()
{
    checkBox1 = new QCheckBox(tr("厂地名称"),this);
    checkBox2 = new QCheckBox(tr("生产机组"),this);
    checkBox3 = new QCheckBox(tr("客户名称"),this);
    checkBox6 = new QCheckBox(tr("工程名称"),this);
    checkBox7 = new QCheckBox(tr("浇筑方式"),this);

    QString changdimingcheng,shengchanjizu,kehumingcheng,gongchengmingcheng,xianjinrenwudan,jiaozhufangshi,tongbiaohao;
    if(checkBox1->checkState() == 2){
        changdimingcheng = QString(" and PlantName='%1'").arg(comBox1->currentText());
    }
    if(checkBox2->checkState() == 2){
        shengchanjizu = QString(" and Unit='%1'").arg(comBox2->currentText());
    }
    if(checkBox3->checkState() == 2){
        kehumingcheng = QString(" and Customer='%1'").arg(comBox3->currentText());
    }
    if(checkBox6->checkState() == 2){
        gongchengmingcheng = QString(" and Engineering='%1'").arg(comBox6->currentText());
    }
    if(checkBox7->checkState() == 2){
        jiaozhufangshi = QString(" and PouringMethod ='%1'").arg(comBox7->currentText());
    }
    if(checkBox8->checkState() == 0){
        xianjinrenwudan = " and MortarTotal='否'";
    }
    if(checkBox9->checkState() == 2){
        tongbiaohao = QString(" and TemplateName ='%1'").arg(comBox9->currentText());
    }
    QString baobiaoSQL = QString("select *,SUM(ReceiptVolume),SUM(RemainingMaterial),MID(OutboundTime,1,10),\
                                    SUM(CASE WHEN Unit = '4#机组' OR Unit = '5#机组' THEN ReceiptVolume ELSE 0 END) dong ,\
                                    SUM(CASE WHEN Unit = '1#机组' OR Unit = '2#机组' THEN ReceiptVolume ELSE 0 END) xi ,\
                                    SUM(CASE WHEN Unit = '3#机组' THEN ReceiptVolume ELSE 0 END) xiC ,\
                                    SUM(CASE WHEN Unit = '4#机组' OR Unit = '5#机组' THEN RemainingMaterial ELSE 0 END) dongsheng ,\
                                    SUM(CASE WHEN Unit = '1#机组' OR Unit = '2#机组' THEN RemainingMaterial ELSE 0 END) xisheng ,\
                                    SUM(CASE Unit WHEN '3#机组' THEN RemainingMaterial ELSE 0 END) xiCsheng \
                                    from ProductionNotice where Flag = '0' and OutboundTime between '%1' and '%2' \
                                    %3 %4 %5 %6 %7 %8 %9 group by MID(OutboundTime,1,10),Engineering,Customer,StrengthGrade\
                                    ORDER BY MID(OutboundTime,1,10),Engineering,Customer,StrengthGrade;")
               .arg(dateEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),dateEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),
                    changdimingcheng,shengchanjizu,kehumingcheng).arg(gongchengmingcheng,xianjinrenwudan,jiaozhufangshi,tongbiaohao);

    if(library->load()){
        typedef void (*pFunc)(const char *,const char *);
        pFunc function=(pFunc)library->resolve("loadmyreport");
        if(function){
            function("report/GeneralProductionScale.fr3",baobiaoSQL.toLocal8Bit().data());
            m_report->dynamicCall("LoadReportFromFile(QString)", "report/GeneralProductionScale.fr3");
            m_report->dynamicCall("ShowReport()");
        }else{
            QMessageBox::information(this,tr("错误"),library->errorString(),0,0,0);
        }
    }
    else{
        QMessageBox::information(this,tr("错误"),library->errorString(),0,0,0);
    }
}

void xiaoshoumingxibiaoDlg::on_fahuohuizong()
{
    QString changdimingcheng,shengchanjizu,kehumingcheng,tongche,tongchesiji,gongchengmingcheng,xianjinrenwudan,jiaozhufangshi,tongbiaohao;
    if(checkBox1->checkState() == 2){
        changdimingcheng = QString(" and PlantName='%1'").arg(comBox1->currentText());
    }
    if(checkBox2->checkState() == 2){
        shengchanjizu = QString(" and Unit='%1'").arg(comBox2->currentText());
    }
    if(checkBox3->checkState() == 2){
        kehumingcheng = QString(" and Customer='%1'").arg(comBox3->currentText());
    }
    if(checkBox4->checkState() == 2){
        tongche = QString(" and DeliveryVehicle='%1'").arg(comBox4->currentText());
    }
    if(checkBox5->checkState() == 2){
        tongchesiji = QString(" and Driver='%1'").arg(comBox5->currentText());
    }
    if(checkBox6->checkState() == 2){
        gongchengmingcheng = QString(" and Engineering='%1'").arg(comBox6->currentText());
    }
    if(checkBox7->checkState() == 2){
        jiaozhufangshi = QString(" and PouringMethod ='%1'").arg(comBox7->currentText());
    }
    if(checkBox8->checkState() == 0){
        xianjinrenwudan = " and MortarTotal='否'";
    }
    if(checkBox9->checkState() == 2){
        tongbiaohao = QString(" and TemplateName ='%1'").arg(comBox9->currentText());
    }
    QString baobiaoSQL = QString("select Customer,Engineering,StrengthGrade,SUM(ReceiptVolume),MID(OutboundTime,1,10),PouringMethod \
                                 from ProductionNotice where Flag = '0' and OutboundTime between '%1' and '%2' \
                                 %3 %4 %5 %6 %7 %8 %9 %10 group by Customer,Engineering,StrengthGrade,PouringMethod,MID(OutboundTime,1,10) \
                                 ORDER BY MID(OutboundTime,1,10),Customer,Engineering,StrengthGrade,PouringMethod;")
            .arg(dateEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),dateEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),
                 changdimingcheng,shengchanjizu,kehumingcheng,tongche,tongchesiji,gongchengmingcheng).arg(xianjinrenwudan,jiaozhufangshi,tongbiaohao);
    if(library->load()){
        typedef void (*pFunc)(const char *,const char *);
        pFunc function=(pFunc)library->resolve("loadmyreport");
        if(function){
            function("report/report4.fr3",baobiaoSQL.toLocal8Bit().data());
            m_report->dynamicCall("LoadReportFromFile(QString)", "report/report4.fr3");
            m_report->dynamicCall("ShowReport()");
        }else{
            QMessageBox::information(this,tr("错误"),library->errorString(),0,0,0);
        }
    }
    else{
        QMessageBox::information(this,tr("错误"),library->errorString(),0,0,0);
    }
}

void xiaoshoumingxibiaoDlg::on_ganfenfahuo()
{
    QString changdimingcheng,shengchanjizu,kehumingcheng,tongche,tongchesiji,gongchengmingcheng,jiaozhufangshi;
    if(checkBox3->checkState() == 2){
        kehumingcheng = QString(" and kehu='%1'").arg(comBox3->currentText());
    }
    if(checkBox4->checkState() == 2){
        tongche = QString(" and chepaihao='%1'").arg(comBox4->currentText());
    }
    if(checkBox5->checkState() == 2){
        tongchesiji = QString(" and siji='%1'").arg(comBox5->currentText());
    }
    if(checkBox6->checkState() == 2){
        gongchengmingcheng = QString(" and gongcheng='%1'").arg(comBox6->currentText());
    }
    if(checkBox7->checkState() == 2){
        jiaozhufangshi = QString(" PouringMethod and ='%1'").arg(comBox7->currentText());
    }
    QString baobiaoSQL = QString("select * from fahuoguobang where pizhongsj between '%1' and '%2'\
                                 %3 %4 %5 %6 %7 %8 %9 order by kehu,No;")
            .arg(dateEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),dateEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),
                 changdimingcheng,shengchanjizu,kehumingcheng,tongche,tongchesiji,gongchengmingcheng,jiaozhufangshi);
    if(library->load()){
        typedef void (*pFunc)(const char *,const char *);
        pFunc function=(pFunc)library->resolve("loadmyreport");
        if(function){
            function("report/ganfenfahuo.fr3",baobiaoSQL.toLocal8Bit().data());
            m_report->dynamicCall("LoadReportFromFile(QString)", "report/ganfenfahuo.fr3");
            m_report->dynamicCall("ShowReport()");
        }else{
            QMessageBox::information(this,tr("错误"),library->errorString(),0,0,0);
        }
    }
    else{
        QMessageBox::information(this,tr("错误"),library->errorString(),0,0,0);
    }
}
