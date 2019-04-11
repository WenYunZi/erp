#include "shengchanxiaohaobiaodlg.h"

extern mymysql db;

shengchanxiaohaobiaoDlg::shengchanxiaohaobiaoDlg(QWidget *parent) :
    QDialog(parent)
{
    library = new QLibrary("MyReportDll.dll");

    QLabel *label1 = new QLabel(tr("发货时间"));
    label1->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label2 = new QLabel(tr("--"));
    label2->setAlignment(Qt::AlignCenter);

    reportView = new QAxWidget;//报表显示窗口
    reportView->setControl("{9207E7EB-4CE3-40E1-8A5A-77C43DA9F503}");
    m_report = new QAxObject;//报表主体对象
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

    checkBox1 = new QCheckBox(tr("厂地名称"));
    checkBox2 = new QCheckBox(tr("生产机组"));
    checkBox3 = new QCheckBox(tr("原料名称"));
    checkBox4 = new QCheckBox(tr("客户名称"));
    checkBox5 = new QCheckBox(tr("工程名称"));

    comBox1 = new QComboBox;
    comBox1->setEditable(true);
    comBox2 = new QComboBox;
    comBox2->setEditable(true);
    comBox3 = new QComboBox;
    comBox3->setEditable(true);
    comBox4 = new QComboBox;
    comBox4->setEditable(true);
    comBox5 = new QComboBox;
    comBox5->setEditable(true);

    btn1 = new QPushButton(tr("生产明细"));
    connect(btn1,SIGNAL(clicked()),this,SLOT(on_shengchanmingxi()));
    btn2 = new QPushButton(tr("客户汇总"));
    connect(btn2,SIGNAL(clicked()),this,SLOT(on_kehuhuizong()));
    btn3 = new QPushButton(tr("消耗汇总"));
    connect(btn3,SIGNAL(clicked()),this,SLOT(on_haocaihuizong()));
    btn4 = new QPushButton(tr("原料每车消耗"));
    connect(btn4,SIGNAL(clicked()),this,SLOT(on_yuanliaomeichexiaohao()));
    btn5 = new QPushButton(tr("原料每盘消耗"));
    connect(btn5,SIGNAL(clicked()),this,SLOT(on_yuanliaomeipanxiaohao()));
    btn6 = new QPushButton(tr("消耗按客户分组"));
    connect(btn6,SIGNAL(clicked()),this,SLOT(on_xiaohaokehufenzu()));
    btn7 = new QPushButton(tr("消耗按产品分组"));
    connect(btn7,SIGNAL(clicked()),this,SLOT(on_xiaohaochanpinfenzu()));
    btn8 = new QPushButton(tr("仓位耗材汇总"));
    connect(btn8,SIGNAL(clicked()),this,SLOT(on_cangweihaocaihuizong()));
    btn9 = new QPushButton(tr("干粉消耗"));
    connect(btn9,SIGNAL(clicked()),this,SLOT(on_biaohaohuizong()));
    btn9->setHidden(true);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label1,0,0);
    layout->addWidget(dateEdit1,0,1);
    layout->addWidget(label2,0,2);
    layout->addWidget(dateEdit2,0,3);
    layout->addWidget(checkBox1,0,4);
    layout->addWidget(comBox1,0,5);
    layout->addWidget(checkBox2,0,6);
    layout->addWidget(comBox2,0,7);
    layout->addWidget(checkBox3,0,8);
    layout->addWidget(comBox3,0,9);
    layout->addWidget(checkBox4,1,0);
    layout->addWidget(comBox4,1,1,1,3);
    layout->addWidget(checkBox5,1,4);
    layout->addWidget(comBox5,1,5,1,3);
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

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(btn1);
    hlayout->addWidget(btn2);
    hlayout->addWidget(btn3);
    hlayout->addWidget(btn4);
    hlayout->addWidget(btn5);
    hlayout->addWidget(btn6);
    hlayout->addWidget(btn7);
    hlayout->addWidget(btn8);
//    hlayout->addWidget(btn9);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(layout);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(reportView);

    const char *fillcomBox1SQL = "select PlantName from FactorySetting;";
    db.sql_fillComboBoxItem(fillcomBox1SQL,comBox1);

    const char *fillcomBox2SQL = "select UnitName from UnitSetting;";
    db.sql_fillComboBoxItem(fillcomBox2SQL,comBox2);

    const char *fillcomBox3SQL = "select Material from MaterialSetting;";
    db.sql_fillComboBoxItem(fillcomBox3SQL,comBox3);

    const char *fillcomBox4SQL = "select CustomerName from CustomerFiles;";
    db.sql_fillComboBoxItem(fillcomBox4SQL,comBox4);

    const char *fillcomBox5SQL = "select Engineering from ProductionNotice group by Engineering;";
    db.sql_fillComboBoxItem(fillcomBox5SQL,comBox5);
}

void shengchanxiaohaobiaoDlg::refresh()
{

}

void shengchanxiaohaobiaoDlg::on_shengchanmingxi()
{
    QString changdimingcheng,shengchanjizu,kehumingcheng,gongchengmingcheng;
    if(checkBox1->checkState() == 2){
        changdimingcheng = QString(" and PlantName='%1'").arg(comBox1->currentText());
    }
    if(checkBox2->checkState() == 2){
        shengchanjizu = QString(" and unit='%1'").arg(comBox2->currentText());
    }
    if(checkBox4->checkState() == 2){
        kehumingcheng = QString(" and USERNAME='%1'").arg(comBox4->currentText());
    }
    if(checkBox5->checkState() == 2){
        gongchengmingcheng = QString(" and GCNAME='%1'").arg(comBox5->currentText());
    }
    QString baobiaoSQL = QString("select USERNAME,GCNAME,QDUDJ,SUM(SUMPS),JIAOZHUBW,unit,CURDATE,PFNAME,id,CheNumber from HISTDATA WHERE \
                                 CURDATE between '%1' and '%2'%3%4%5%6 GROUP BY CheTime order by USERNAME,GCNAME")
            .arg(dateEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),dateEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),
                 changdimingcheng,shengchanjizu,kehumingcheng,gongchengmingcheng);
    if(library->load()){
        typedef void (*pFunc)(const char *,const char *);
        pFunc function=(pFunc)library->resolve("loadmyreport");
        if(function){
            function("report/ProductionDetails.fr3",baobiaoSQL.toLocal8Bit().data());
            m_report->dynamicCall("LoadReportFromFile(QString)", "report/ProductionDetails.fr3");
            m_report->dynamicCall("ShowReport()");
        }
    }else{
        QMessageBox::information(this,tr("错误"),library->errorString());
    }
}

void shengchanxiaohaobiaoDlg::on_kehuhuizong()
{
    QString changdimingcheng,shengchanjizu,kehumingcheng,gongchengmingcheng;
    if(checkBox1->checkState() == 2){
        changdimingcheng = QString(" and PlantName='%1'").arg(comBox1->currentText());
    }
    if(checkBox2->checkState() == 2){
        shengchanjizu = QString(" and unit='%1'").arg(comBox2->currentText());
    }
    if(checkBox4->checkState() == 2){
        kehumingcheng = QString(" and USERNAME='%1'").arg(comBox4->currentText());
    }
    if(checkBox5->checkState() == 2){
        gongchengmingcheng = QString(" and GCNAME='%1'").arg(comBox5->currentText());
    }
    QString baobiaoSQL = QString("SELECT QDUDJ,GCNAME,unit,USERNAME,round(SUM(SUMPS),1) \
                                 FROM HISTDATA where CURDATE between '%1' and '%2'%3 %4 %5 %6 \
                                 GROUP BY QDUDJ,GCNAME ORDER BY USERNAME,GCNAME,unit;")
            .arg(dateEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),dateEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),
                 changdimingcheng,shengchanjizu,kehumingcheng,gongchengmingcheng);
    if(library->load()){
        typedef void (*pFunc)(const char *,const char *);
        pFunc function=(pFunc)library->resolve("loadmyreport");
        if(function){
            function("report/CustomerSummary.fr3",baobiaoSQL.toLocal8Bit().data());
            m_report->dynamicCall("LoadReportFromFile(QString)", "report/CustomerSummary.fr3");
            m_report->dynamicCall("ShowReport()");
        }
    }else{
        QMessageBox::information(this,tr("错误"),library->errorString());
    }
}

void shengchanxiaohaobiaoDlg::on_haocaihuizong()
{
    QString changdimingcheng,shengchanjizu,yuanliaomingcheng,kehumingcheng,gongchengmingcheng;
    if(checkBox1->checkState() == 2){
        changdimingcheng = QString(" and B.PlantName='%1'").arg(comBox1->currentText());
    }
    if(checkBox2->checkState() == 2){
        shengchanjizu = QString(" and unit='%1'").arg(comBox2->currentText());
    }
    if(checkBox3->checkState() == 2){
        yuanliaomingcheng = QString(" and MATNAME='%1'").arg(comBox3->currentText());
    }
    if(checkBox4->checkState() == 2){
        kehumingcheng = QString(" and USERNAME='%1'").arg(comBox4->currentText());
    }
    if(checkBox5->checkState() == 2){
        gongchengmingcheng = QString(" and GCNAME='%1'").arg(comBox5->currentText());
    }
    QString baobiaoSQL = QString("SELECT MATNAME,MATPRICE,ROUND(SUM(SJMAT),1),ROUND(SUM(YQMAT),1) FROM HISTDATA2 A \
                                 left join (select id,USERNAME,GCNAME,PlantName,unit,CURDATE from HISTDATA) B ON (A.CURDATA=B.CURDATE AND A.JIZUNO=B.unit) \
                                 where A.CURDATA between '%1' and '%2' %3%4%5%6%7 GROUP BY A.MATNAME ORDER BY A.FILED;")
            .arg(dateEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),dateEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),
                 changdimingcheng,shengchanjizu,yuanliaomingcheng,kehumingcheng,gongchengmingcheng);
    if(library->load()){
        typedef void (*pFunc)(const char *,const char *);
        pFunc function=(pFunc)library->resolve("loadmyreport");
        if(function){
            function("report/ConsumptionSummary.fr3",baobiaoSQL.toLocal8Bit().data());
            m_report->dynamicCall("LoadReportFromFile(QString)", "report/ConsumptionSummary.fr3");
            m_report->dynamicCall("ShowReport()");
        }
    }else{
        QMessageBox::information(this,tr("错误"),library->errorString());
    }
}

void shengchanxiaohaobiaoDlg::on_yuanliaomeichexiaohao()
{
    QString changdimingcheng,shengchanjizu,kehumingcheng,gongchengmingcheng;
        if(checkBox1->checkState() == 2){
            changdimingcheng = QString(" and PlantName='%1'").arg(comBox1->currentText());
        }
        if(checkBox2->checkState() == 2){
            shengchanjizu = QString(" and unit='%1'").arg(comBox2->currentText());
        }
        if(checkBox4->checkState() == 2){
            kehumingcheng = QString(" and USERNAME like '%%1%'").arg(comBox4->currentText());
        }
        if(checkBox5->checkState() == 2){
            gongchengmingcheng = QString(" and GCNAME='%1'").arg(comBox5->currentText());
        }
        QString baobiaoSQL = QString("select USERNAME,GCNAME,CheNumber,CheTime,unit,QDUDJ,PFNAME,PhbNumber,round(SUM(SUMPS),1) from \
                                     HISTDATA where CheTime between '%1' and '%2' %3 %4 %5 %6  GROUP BY unit,CheTime ORDER BY USERNAME,unit,id;")
                        .arg(dateEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),dateEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),
                             changdimingcheng,shengchanjizu,kehumingcheng,gongchengmingcheng);
        if(library->load()){
            typedef int (*pFunc)(const char *,const char *);
            pFunc function=(pFunc)library->resolve("loadmyreport");
            if(function){
                function("report/ConsumptionPerVehicle.fr3",baobiaoSQL.toLocal8Bit().data());
                m_report->dynamicCall("LoadReportFromFile(QString)", "report/ConsumptionPerVehicle.fr3");
                m_report->dynamicCall("ShowReport()");
            }
        }else{
            QMessageBox::information(this,tr("错误"),library->errorString());
        }
}

void shengchanxiaohaobiaoDlg::on_yuanliaomeipanxiaohao()
{
    QString changdimingcheng,shengchanjizu,kehumingcheng,gongchengmingcheng;
        if(checkBox1->checkState() == 2){
            changdimingcheng = QString(" and PlantName='%1'").arg(comBox1->currentText());
        }
        if(checkBox2->checkState() == 2){
            shengchanjizu = QString(" and unit='%1'").arg(comBox2->currentText());
        }
        if(checkBox4->checkState() == 2){
            kehumingcheng = QString(" and USERNAME='%1'").arg(comBox4->currentText());
        }
        if(checkBox5->checkState() == 2){
            gongchengmingcheng = QString(" and GCNAME='%1'").arg(comBox5->currentText());
        }
        QString baobiaoSQL = QString("select USERNAME,SUMPS,GCNAME,CheNumber,CheTime,unit,QDUDJ,PFNAME,PhbNumber,CURDATE from HISTDATA where CheTime \
                                     between '%1' and '%2' %3 %4 %5 %6 ORDER BY USERNAME,CheTime,CURDATE;")
                        .arg(dateEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),dateEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),
                             changdimingcheng,shengchanjizu,kehumingcheng,gongchengmingcheng);
        qDebug()<<baobiaoSQL;
        if(library->load()){
            typedef void (*pFunc)(const char *,const char *);
            pFunc function=(pFunc)library->resolve("loadmyreport");
            if(function){
                function("report/ConsumptionPerPlate.fr3",baobiaoSQL.toLocal8Bit().data());
                m_report->dynamicCall("LoadReportFromFile(QString)", "report/ConsumptionPerPlate.fr3");
                m_report->dynamicCall("ShowReport()");
            }
        }else{
            QMessageBox::information(this,tr("错误"),library->errorString());
        }
}

void shengchanxiaohaobiaoDlg::on_xiaohaokehufenzu()
{
    QString changdimingcheng,shengchanjizu,yuanliaomingcheng,kehumingcheng,gongchengmingcheng;

    if(checkBox1->checkState() == 2){
        changdimingcheng = QString(" and B.PlantName='%1'").arg(comBox1->currentText());
    }
    if(checkBox2->checkState() == 2){
        shengchanjizu = QString(" and unit='%1'").arg(comBox2->currentText());
    }
    if(checkBox3->checkState() == 2){
        yuanliaomingcheng = QString(" and MATNAME='%1'").arg(comBox3->currentText());
    }
    if(checkBox4->checkState() == 2){
        kehumingcheng = QString(" and USERNAME='%1'").arg(comBox4->currentText());
    }
    if(checkBox5->checkState() == 2){
        gongchengmingcheng = QString(" and GCNAME='%1'").arg(comBox5->currentText());
    }

    QString baobiaoSQL = QString("select MATNAME,MATPRICE,USERNAME,ROUND(SUM(A.SJMAT),1),ROUND(SUM(A.YQMAT),1),CURDATE from HISTDATA2 A left join \
                                 (select id,GCNAME,PlantName,unit,USERNAME,CURDATE from HISTDATA) B on (A.CURDATA=B.CURDATE AND A.JIZUNO=B.unit) where \
                                 A.CURDATA between '%1' and '%2' %3%4%5%6%7 group by B.USERNAME,A.MATNAME ORDER BY \
                                 B.USERNAME,A.FILED;")
                    .arg(dateEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),dateEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),
                         changdimingcheng,shengchanjizu,yuanliaomingcheng,kehumingcheng,gongchengmingcheng);
    if(library->load()){
        typedef void (*pFunc)(const char *,const char *);
        pFunc function=(pFunc)library->resolve("loadmyreport");
        if(function){
            function("report/ConsumptionOfCustomerGroups.fr3",baobiaoSQL.toLocal8Bit().data());
            m_report->dynamicCall("LoadReportFromFile(QString)", "report/ConsumptionOfCustomerGroups.fr3");
            m_report->dynamicCall("ShowReport()");
        }
    }
    else{
        QMessageBox::information(this,tr("错误"),library->errorString());
    }
}

void shengchanxiaohaobiaoDlg::on_xiaohaochanpinfenzu()
{
    QString changdimingcheng,shengchanjizu,yuanliaomingcheng,kehumingcheng,gongchengmingcheng;

    if(checkBox1->checkState() == 2){
        changdimingcheng = QString(" and B.PlantName='%1'").arg(comBox1->currentText());
    }
    if(checkBox2->checkState() == 2){
        shengchanjizu = QString(" and unit='%1'").arg(comBox2->currentText());
    }
    if(checkBox3->checkState() == 2){
        yuanliaomingcheng = QString(" and MATNAME='%1'").arg(comBox3->currentText());
    }
    if(checkBox4->checkState() == 2){
        kehumingcheng = QString(" and USERNAME='%1'").arg(comBox4->currentText());
    }
    if(checkBox5->checkState() == 2){
        gongchengmingcheng = QString(" and GCNAME='%1'").arg(comBox5->currentText());
    }
    QString baobiaoSQL = QString("select MATNAME,MATPRICE,QDUDJ,ROUND(SUM(A.SJMAT),1),ROUND(SUM(A.YQMAT),1),CURDATE from HISTDATA2 A  \
                                 left join (select id,GCNAME,USERNAME,unit,PlantName,QDUDJ,CURDATE from HISTDATA) B on (A.CURDATA=B.CURDATE AND A.JIZUNO=B.unit)\
                                 where A.CURDATA between '%1' and '%2'\
                                 %3%4%5%6%7 group by B.QDUDJ,A.MATNAME ORDER BY B.QDUDJ,A.FILED;")
            .arg(dateEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),dateEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),
                 changdimingcheng,shengchanjizu,yuanliaomingcheng,kehumingcheng,gongchengmingcheng);
    if(library->load()){
        typedef void (*pFunc)(const char *,const char *);
        pFunc function=(pFunc)library->resolve("loadmyreport");
        if(function){
            function("report/ConsumptionOfProductsGroup.fr3",baobiaoSQL.toLocal8Bit().data());
            m_report->dynamicCall("LoadReportFromFile(QString)", "report/ConsumptionOfProductsGroup.fr3");
            m_report->dynamicCall("ShowReport()");
        }
    }else{
        QMessageBox::information(this,tr("错误"),library->errorString());
    }
}

void shengchanxiaohaobiaoDlg::on_cangweihaocaihuizong()
{
    QString baobiaoSQL = QString("SELECT MATNAME,ROUND(SUM(YQMAT),1),ROUND(SUM(SJMAT),1),B.Position FROM HISTDATA2 A LEFT JOIN \
                                 (SELECT * FROM UnitMaterialCorrespondsToERPMaterial) B ON (A.FILED=B.CorrespondingField and A.JIZUNO=B.ProductionUnit) WHERE CHETIME \
                                 BETWEEN '%1' AND '%2' GROUP BY B.Position;")
                    .arg(dateEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),dateEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
    if(library->load()){
        typedef void (*pFunc)(const char *,const char *);
        pFunc function=(pFunc)library->resolve("loadmyreport");
        if(function){
            function("report/PositionConsumptionSummary.fr3",baobiaoSQL.toLocal8Bit().data());
            m_report->dynamicCall("LoadReportFromFile(QString)", "report/PositionConsumptionSummary.fr3");
            m_report->dynamicCall("ShowReport()");
        }
    }else{
        QMessageBox::information(this,tr("错误"),library->errorString());
    }
}

void shengchanxiaohaobiaoDlg::on_biaohaohuizong()
{
    QString changdimingcheng,shengchanjizu,kehumingcheng,gongchengmingcheng;
    if(checkBox1->checkState() == 2){
        changdimingcheng = QString(" and PlantName='%1'").arg(comBox1->currentText());
    }
    if(checkBox2->checkState() == 2){
        shengchanjizu = QString(" and unit='%1'").arg(comBox2->currentText());
    }
    if(checkBox4->checkState() == 2){
        kehumingcheng = QString(" and USERNAME='%1'").arg(comBox4->currentText());
    }
    if(checkBox5->checkState() == 2){
        gongchengmingcheng = QString(" and GCNAME='%1'").arg(comBox5->currentText());
    }
    QString baobiaoSQL = QString("select * from ganfenXiaoHao WHERE \
                                 dateTime between '%1' and '%2'")
            .arg(dateEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss").replace("-0","- "),dateEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss").replace("-0","- "));
            qDebug()<<baobiaoSQL;
    if(library->load()){
        typedef void (*pFunc)(const char *,const char *);
        pFunc function=(pFunc)library->resolve("loadmyreport");
        if(function){
            function("report/ganfenxiaohao.fr3",baobiaoSQL.toLocal8Bit().data());
            m_report->dynamicCall("LoadReportFromFile(QString)", "report/ganfenxiaohao.fr3");
            m_report->dynamicCall("ShowReport()");
        }
    }else{
        QMessageBox::information(this,tr("错误"),library->errorString());
    }
}


