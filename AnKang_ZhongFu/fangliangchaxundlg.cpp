#include "fangliangchaxundlg.h"

extern mymysql db;

fangliangchaxunDlg::fangliangchaxunDlg(QWidget *parent) :
    QDialog(parent)
{
    library = new QLibrary("MyReportDll",this);

    QLabel *label1 = new QLabel(tr("生产时间"),this);
    label1->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label2 = new QLabel(tr("--"),this);
    label2->setAlignment(Qt::AlignCenter);

    reportView = new QAxWidget(this);//报表显示窗口
    reportView->setControl("{9207E7EB-4CE3-40E1-8A5A-77C43DA9F503}");
    m_report = new QAxObject(this);//报表主体对象
    m_report->setControl("{4764040E-4222-4DEC-9F2E-82D46E212B3A}");
    reportView->dynamicCall("SetReport(IfrxReport*)", m_report->asVariant());//关联报表窗口和报表主体对象

    dateEdit1 = new QDateEdit(QDate::currentDate(),this);
    dateEdit1->setCalendarPopup(true);
    dateEdit2 = new QDateEdit(QDate::currentDate(),this);
    dateEdit2->setCalendarPopup(true);

    checkBox1 = new QCheckBox(tr("车牌号"),this);
    checkBox2 = new QCheckBox(tr("司机姓名"),this);
    checkBox3 = new QCheckBox(tr("客户名称"),this);
    checkBox4 = new QCheckBox(tr("生产机组"),this);
    checkBox5 = new QCheckBox(tr("工程名称"),this);
    checkBox6 = new QCheckBox(tr("厂地名称"),this);

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
    const char *fillSQL6 = "select PlantName from FactorySetting;";
    db.sql_fillComboBoxItem(fillSQL6,comBox6);

    btn1 = new QPushButton(tr("明细查询"),this);
    connect(btn1,SIGNAL(clicked()),this,SLOT(on_fangliangmingxi()));
    btn2 = new QPushButton(tr("工程汇总"),this);
    connect(btn2,SIGNAL(clicked()),this,SLOT(on_gongchenghuizong()));

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(btn1);
    hlayout->addWidget(btn2);
    hlayout->setMargin(0);
    QWidget *widget = new QWidget(this);
    widget->setLayout(hlayout);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label1,0,0);
    layout->addWidget(dateEdit1,0,1);
    layout->addWidget(label2,0,2);
    layout->addWidget(dateEdit2,0,3);
    layout->addWidget(checkBox1,0,4);
    layout->addWidget(comBox1,0,5);
    layout->addWidget(checkBox2,0,6);
    layout->addWidget(comBox2,0,7);
    layout->addWidget(checkBox3,1,0);
    layout->addWidget(comBox3,1,1,1,3);
    layout->addWidget(checkBox4,1,4);
    layout->addWidget(comBox4,1,5);
    layout->addWidget(widget,1,6,2,2,Qt::AlignVCenter);
    layout->addWidget(checkBox5,2,0);
    layout->addWidget(comBox5,2,1,1,3);
    layout->addWidget(checkBox6,2,4);
    layout->addWidget(comBox6,2,5);
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

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(layout);
    vlayout->addWidget(reportView);

    const char *fillcomBox1SQL = "select LicensePlate from ConcreteVehicleInformation;";
    db.sql_fillComboBoxItem(fillcomBox1SQL,comBox1);

    const char *fillcomBox2SQL = "select DriverName from ConcreteTruckDriver;";
    db.sql_fillComboBoxItem(fillcomBox2SQL,comBox2);

    const char *fillcomBox3SQL = "select CustomerName from CustomerFiles;";
    db.sql_fillComboBoxItem(fillcomBox3SQL,comBox3);
    connect(comBox3,SIGNAL(currentIndexChanged(int)),this,SLOT(on_comBox3Correspond()));

    const char *fillcomBox4SQL = "select UnitName from UnitSetting;";
    db.sql_fillComboBoxItem(fillcomBox4SQL,comBox4);
}

void fangliangchaxunDlg::refresh()
{

}

void fangliangchaxunDlg::on_fangliangmingxi()
{
    QString chepaihao,sijiName,kehumingcheng,shengchanjizu,gongchengmingcheng,changdimingcheng;
    if(checkBox1->checkState() == 2){
        chepaihao = QString(" and CheNumber='%1'").arg(comBox1->currentText());
    }
    if(checkBox2->checkState() == 2){
        sijiName = QString(" and USERCHE='%1'").arg(comBox2->currentText());
    }
    if(checkBox3->checkState() == 2){
        kehumingcheng = QString(" and USERNAME='%1'").arg(comBox3->currentText());
    }
    if(checkBox4->checkState() == 2){
        shengchanjizu = QString(" and unit='%1'").arg(comBox4->currentText());
    }
    if(checkBox5->checkState() == 2){
        gongchengmingcheng = QString(" and GCNAME='%1'").arg(comBox5->currentText());
    }
    if(checkBox6->checkState() == 2){
        changdimingcheng = QString(" and PlantName='%1'").arg(comBox6->currentText());
    }
    QString baobiaoSQL = QString("select *,round(SUM(SUMPS),1) from HISTDATA where CURDATE between '%1' and '%2'%3%4%5%6%7%8 \
                                 group by CheTime ORDER BY USERNAME,GCNAME")
                    .arg(dateEdit1->date().toString("yyyy-MM-dd"),dateEdit2->date().addDays(1).toString("yyyy-MM-dd"),
                         chepaihao,sijiName,kehumingcheng,shengchanjizu,gongchengmingcheng,changdimingcheng);
    if(library->load()){
        typedef void (*pFunc)(const char *,const char *);
        pFunc function=(pFunc)library->resolve("loadmyreport");
        if(function){
            function("./report/SquareDetail.fr3",baobiaoSQL.toLocal8Bit().data());
            m_report->dynamicCall("LoadReportFromFile(QString)", "report/SquareDetail.fr3");
            m_report->dynamicCall("ShowReport()");
        }else{
            QMessageBox::information(this,tr("错误"),library->errorString(),0,0,0);
        }
    }else{
        QMessageBox::information(this,tr("错误"),library->errorString(),0,0,0);
    }
}

void fangliangchaxunDlg::on_gongchenghuizong()
{
    QString chepaihao,sijiName,kehumingcheng,shengchanjizu,gongchengmingcheng,changdimingcheng;
    if(checkBox1->checkState() == 2){
        chepaihao = QString(" and CheNumber='%1'").arg(comBox1->currentText());
    }
    if(checkBox2->checkState() == 2){
        sijiName = QString(" and USERCHE='%1'").arg(comBox2->currentText());
    }
    if(checkBox3->checkState() == 2){
        kehumingcheng = QString(" and USERNAME='%1'").arg(comBox3->currentText());
    }
    if(checkBox4->checkState() == 2){
        shengchanjizu = QString(" and unit='%1'").arg(comBox4->currentText());
    }
    if(checkBox5->checkState() == 2){
        gongchengmingcheng = QString(" and GCNAME='%1'").arg(comBox5->currentText());
    }
    if(checkBox6->checkState() == 2){
        changdimingcheng = QString(" and PlantName='%1'").arg(comBox6->currentText());
    }
    QString baobiaoSQL = QString("SELECT QDUDJ,GCNAME,unit,USERNAME,round(SUM(SUMPS),1) FROM HISTDATA WHERE CURDATE BETWEEN \
                                 '%1' AND '%2'%3%4%5%6%7%8 GROUP BY unit,QDUDJ,GCNAME ORDER BY USERNAME,GCNAME,unit;")
                    .arg(dateEdit1->date().toString("yyyy-MM-dd"),dateEdit2->date().addDays(1).toString("yyyy-MM-dd"),
                         chepaihao,sijiName,kehumingcheng,shengchanjizu,gongchengmingcheng,changdimingcheng);

    if(library->load()){
        typedef void (*pFunc)(const char *,const char *);
        pFunc function=(pFunc)library->resolve("loadmyreport");
        if(function){
            function("./report/ProjectSummary.fr3",baobiaoSQL.toLocal8Bit().data());
            m_report->dynamicCall("LoadReportFromFile(QString)", "report/ProjectSummary.fr3");
            m_report->dynamicCall("ShowReport()");
        }else{
            QMessageBox::information(this,tr("错误"),library->errorString(),0,0,0);
        }
    }else{
        QMessageBox::information(this,tr("错误"),library->errorString(),0,0,0);
    }
}

void fangliangchaxunDlg::on_comBox3Correspond()
{
    comBox5->clear();
    QString fillcomBox5SQL = QString("select ProjectName from SalesContractCustomerEngineeringForm where CustomerName='%1';").arg(comBox3->currentText());
    db.sql_fillComboBoxItem(fillcomBox5SQL.toStdString().data(),comBox5);
}
