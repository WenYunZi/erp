 #include "caigoumingxibiaodlg.h"
#include <QDebug>
extern mymysql db;
extern QString strCurrentDir;

caigoumingxibiaoDlg::caigoumingxibiaoDlg(QWidget *parent) :
    QDialog(parent)
{
    library = new QLibrary("MyReportDll.dll",this);
    QLabel *label1 = new QLabel(tr("入库日期"),this);
    label1->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label2 = new QLabel(tr("--"),this);
    label2->setAlignment(Qt::AlignCenter);

    dateEdit1 = new QDateTimeEdit(this);
    dateEdit1->setDate(QDate::currentDate().addDays(-1));
    dateEdit1->setTime(QTime::fromString("00:00:00","hh:mm:ss"));
    dateEdit1->setCalendarPopup(true);
    dateEdit2 = new QDateTimeEdit(this);
    dateEdit2->setDate(QDate::currentDate());
    dateEdit2->setTime(QTime::fromString("00:00:00","hh:mm:ss"));
    dateEdit2->setCalendarPopup(true);

    checkBox1 = new QCheckBox(tr("供应商"),this);
    checkBox2 = new QCheckBox(tr("厂地"),this);
    checkBox3 = new QCheckBox(tr("原料"),this);
    checkBox4 = new QCheckBox(tr("车牌号"),this);
    comBox1 = new QComboBox(this);
    comBox1->setEditable(true);
    comBox2 = new QComboBox(this);
    comBox2->setEditable(true);
    comBox3 = new QComboBox(this);
    comBox3->setEditable(true);
    comBox4 = new QComboBox(this);
    comBox4->setEditable(true);
    btn1 = new QPushButton(tr("供应商分组"),this);
    connect(btn1,SIGNAL(clicked()),this,SLOT(on_gongyingshangfenzu()));
    btn2 = new QPushButton(tr("原料分组"),this);
    connect(btn2,SIGNAL(clicked()),this,SLOT(on_yuanliaofenzu()));
    btn3 = new QPushButton(tr("供应商汇总"),this);
    connect(btn3,SIGNAL(clicked()),this,SLOT(on_gongyingshanghuizong()));
    btn4 = new QPushButton(tr("原料汇总"),this);
    connect(btn4,SIGNAL(clicked()),this,SLOT(on_yuanliaohuizong()));

    reportView = new QAxWidget(this);//报表显示窗口
    reportView->setControl("{9207E7EB-4CE3-40E1-8A5A-77C43DA9F503}");
    m_report = new QAxObject(this);//报表主体对象
    m_report->setControl("{4764040E-4222-4DEC-9F2E-82D46E212B3A}");
    reportView->dynamicCall("SetReport(IfrxReport*)", m_report->asVariant());//关联报表窗口和报表主体对象

    const char *comBox1SQL = "select Name from SupplierFile;";
    db.sql_fillComboBoxItem(comBox1SQL,comBox1);

    const char *comBox2SQL = "select PlantName from FactorySetting;";
    db.sql_fillComboBoxItem(comBox2SQL,comBox2);

    const char *comBox3SQL = "select Material from MaterialSetting;";
    db.sql_fillComboBoxItem(comBox3SQL,comBox3);

    const char *comBox4SQL = "select LicensePlateNumber from PurchaseReceipt group by LicensePlateNumber";
    db.sql_fillComboBoxItem(comBox4SQL,comBox4);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label1,0,0);
    layout->addWidget(dateEdit1,0,1);
    layout->addWidget(label2,0,2);
    layout->addWidget(dateEdit2,0,3);
    layout->addWidget(checkBox3,0,4);
    layout->addWidget(comBox3,0,5);
    layout->addWidget(checkBox2,0,6);
    layout->addWidget(comBox2,0,7);
    layout->addWidget(btn1,0,8);
    layout->addWidget(btn2,0,9);
    layout->addWidget(checkBox1,1,0);
    layout->addWidget(comBox1,1,1,1,3);
    layout->addWidget(checkBox4,1,4);
    layout->addWidget(comBox4,1,5);
    layout->addWidget(btn3,1,8);
    layout->addWidget(btn4,1,9);
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
}

caigoumingxibiaoDlg::~caigoumingxibiaoDlg()
{

}

void caigoumingxibiaoDlg::refresh()
{

}


void caigoumingxibiaoDlg::on_gongyingshangfenzu()
{
    QString gongyingshang,changdi,yuanliao,chepaihao;
    if(checkBox1->checkState() == 2){
        gongyingshang = QString("and Supplier='%1'").arg(comBox1->currentText());
    }
    if(checkBox2->checkState() == 2){
        changdi = QString("and Storagefactory='%1'").arg(comBox2->currentText());
    }
    if(checkBox3->checkState() == 2){
        yuanliao = QString("and Material='%1'").arg(comBox3->currentText());
    }
    if(checkBox4->checkState() == 2){
        chepaihao = QString("and LicensePlateNumber='%1'").arg(comBox4->currentText());
    }
    QString baobiaoSQL = QString("select * from PurchaseReceipt where WhetherCheck='%1' and TareTime between '%2' and '%3' \
                                 %4 %5 %6 %7 order by Supplier,Material,Time;")
            .arg(QString("是"),dateEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),dateEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),
                 gongyingshang,changdi,yuanliao,chepaihao);
    if(library->load()){
        typedef void  (*pFunc)(const char *,const char *);
        pFunc function=(pFunc)library->resolve("loadmyreport");
        if(function){
            function("report/SupplierGrouping.fr3",baobiaoSQL.toLocal8Bit().data());
            m_report->dynamicCall("LoadReportFromFile(QString)", "report/SupplierGrouping.fr3");
            m_report->dynamicCall("ShowReport()");
        }else{
            QMessageBox::information(this,tr("错误"),library->errorString(),0,0,0);
        }
    }else{
        QMessageBox::information(this,tr("错误"),library->errorString(),0,0,0);
    }
}

void caigoumingxibiaoDlg::on_yuanliaofenzu()
{
    QString gongyingshang,changdi,yuanliao,chepaihao;
    if(checkBox1->checkState() == 2){
        gongyingshang = QString("and Supplier='%1'").arg(comBox1->currentText());
    }
    if(checkBox2->checkState() == 2){
        changdi = QString("and Storagefactory='%1'").arg(comBox2->currentText());
    }
    if(checkBox3->checkState() == 2){
        yuanliao = QString("and Material='%1'").arg(comBox3->currentText());
    }
    if(checkBox4->checkState() == 2){
        chepaihao = QString("and LicensePlateNumber='%1'").arg(comBox4->currentText());
    }

    QString baobiaoSQL = QString("select * from PurchaseReceipt where WhetherCheck='%1' and TareTime between '%2' and '%3' \
                                 %4 %5 %6 %7 order by Material,Supplier,Time;")
            .arg(QString("是"),dateEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),dateEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),
                 gongyingshang,changdi,yuanliao,chepaihao);
    qDebug()<<baobiaoSQL;
    if(library->load()){
        typedef void (*pFunc)(const char *,const char *);
        pFunc function=(pFunc)library->resolve("loadmyreport");
        if(function){
            function("report/MaterialGrouping.fr3",baobiaoSQL.toLocal8Bit().data());
            m_report->dynamicCall("LoadReportFromFile(QString)", "report/MaterialGrouping.fr3");
            m_report->dynamicCall("ShowReport()");
        }else{
            QMessageBox::information(this,tr("错误"),library->errorString(),0,0,0);
        }
    }
    else{
        QMessageBox::information(this,tr("错误"),library->errorString());
    }
}

void caigoumingxibiaoDlg::on_gongyingshanghuizong()
{
    QString gongyingshang,changdi,yuanliao,chepaihao;

    if(checkBox1->checkState() == 2){
        gongyingshang = QString("and Supplier='%1'").arg(comBox1->currentText());
    }
    if(checkBox2->checkState() == 2){
        changdi = QString("and Storagefactory='%1'").arg(comBox2->currentText());
    }
    if(checkBox3->checkState() == 2){
        yuanliao = QString("and Material='%1'").arg(comBox3->currentText());
    }
    if(checkBox4->checkState() == 2){
        chepaihao = QString("and LicensePlateNumber='%1'").arg(comBox4->currentText());
    }

    QString baobiaoSQL = QString("select *,SUM(StorageKG) from PurchaseReceipt where WhetherCheck='%1' and TareTime between '%2' and '%3' \
                                 %4 %5 %6 %7 GROUP BY Supplier,Material,SpecificationModel order by Supplier,Material,SpecificationModel,Time;")
            .arg(QString("是"),dateEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),dateEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),
                 gongyingshang,changdi,yuanliao,chepaihao);

    if(library->load()){
        typedef void  (*pFunc)(const char *,const char *);
        pFunc function=(pFunc)library->resolve("loadmyreport");
        if(function){
            function("report/SupplierSummary.fr3",baobiaoSQL.toLocal8Bit().data());
            m_report->dynamicCall("LoadReportFromFile(QString)", "report/SupplierSummary.fr3");
            m_report->dynamicCall("ShowReport()");
        }else{
            QMessageBox::information(this,tr("错误"),library->errorString(),0,0,0);
        }
    }
    else{
        QMessageBox::information(this,tr("错误"),library->errorString(),0,0,0);
    }
}

void caigoumingxibiaoDlg::on_yuanliaohuizong()
{
    QString gongyingshang,changdi,yuanliao,chepaihao;

    if(checkBox1->checkState() == 2){
        gongyingshang = QString("and Supplier='%1'").arg(comBox1->currentText());
    }
    if(checkBox2->checkState() == 2){
        changdi = QString("and Storagefactory='%1'").arg(comBox2->currentText());
    }
    if(checkBox3->checkState() == 2){
        yuanliao = QString("and Material='%1'").arg(comBox3->currentText());
    }
    if(checkBox4->checkState() == 2){
        chepaihao = QString("and LicensePlateNumber='%1'").arg(comBox4->currentText());
    }

    QString baobiaoSQL = QString("select *,SUM(StorageKG) from PurchaseReceipt where WhetherCheck='%1' and TareTime between '%2' and '%3' \
                                 %4 %5 %6 %7 GROUP BY Supplier,Material,SpecificationModel order by Material,SpecificationModel,Supplier,Time;")
            .arg(QString("是"),dateEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),dateEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),
                 gongyingshang,changdi,yuanliao,chepaihao);

    if(library->load()){
        typedef void  (*pFunc)(const char *,const char *);
        pFunc function=(pFunc)library->resolve("loadmyreport");
        if(function){
            function("report/MaterialSummary.fr3",baobiaoSQL.toLocal8Bit().data());
            m_report->dynamicCall("LoadReportFromFile(QString)", "report/MaterialSummary.fr3");
            m_report->dynamicCall("ShowReport()");
        }else{
            QMessageBox::information(this,tr("错误"),library->errorString(),0,0,0);
        }
    }
    else{
        QMessageBox::information(this,tr("错误"),library->errorString(),0,0,0);
    }
}

