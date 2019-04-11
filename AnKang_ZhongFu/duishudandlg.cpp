#include "duishudandlg.h"

extern mymysql db;

duishudanDlg::duishudanDlg(QWidget *parent) :
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

    checkBox1 = new QCheckBox(tr("产品类型"),this);
    checkBox2 = new QCheckBox(tr("客户名称"),this);
    checkBox3 = new QCheckBox(tr("工程名称"),this);

    comBox1 = new QComboBox(this);
    comBox1->setEditable(true);
    comBox1->setView(new QListView(this));
    comBox1->addItem(tr(""));
    comBox1->addItem(tr("混凝土"));
    comBox1->addItem(tr("砂浆"));
    comBox2 = new QComboBox(this);
    comBox2->setEditable(true);
    comBox3 = new QComboBox(this);
    comBox3->setEditable(true);

    btn1 = new QPushButton(tr("查询"),this);
    connect(btn1,SIGNAL(clicked()),this,SLOT(on_xiaoshoumingxi()));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label1,0,0);
    layout->addWidget(dateEdit1,0,1);
    layout->addWidget(label2,0,2);
    layout->addWidget(dateEdit2,0,3);
    layout->addWidget(checkBox1,0,4);
    layout->addWidget(comBox1,0,5);
    layout->addWidget(btn1,0,8,2,1,Qt::AlignVCenter);
    layout->addWidget(checkBox2,1,0);
    layout->addWidget(comBox2,1,1,1,3);
    layout->addWidget(checkBox3,1,4);
    layout->addWidget(comBox3,1,5,1,3);
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

    const char *fillcomBox2SQL = "select CustomerName from CustomerFiles;";
    db.sql_fillComboBoxItem(fillcomBox2SQL,comBox2);

    const char *fillcomBox3SQL = "select ProjectName from ProjectName;";
    db.sql_fillComboBoxItem(fillcomBox3SQL,comBox3);
}

void duishudanDlg::refresh()
{

}

void duishudanDlg::on_xiaoshoumingxi()
{
    if(library->load()){
        typedef void (*pFunc)(const char *,const char *);
        pFunc function=(pFunc)library->resolve("loadmyreport");
        if(function){
            //function("report/ConsumptionOfCustomerGroups.fr3",baobiaoSQL.toLocal8Bit().data());
            m_report->dynamicCall("LoadReportFromFile(QString)", "report/ConsumptionOfCustomerGroups.fr3");
            m_report->dynamicCall("ShowReport()");
        }
    }else{
        QMessageBox::information(this,tr("错误"),library->errorString(),0,0,0);
    }
}

void duishudanDlg::on_fahuohuizong()
{
    if(library->load()){
        typedef void (*pFunc)(const char *,const char *);
        pFunc function=(pFunc)library->resolve("loadmyreport");
        if(function){
            //function("report/ConsumptionOfCustomerGroups.fr3",baobiaoSQL.toLocal8Bit().data());
            m_report->dynamicCall("LoadReportFromFile(QString)", "report/ConsumptionOfCustomerGroups.fr3");
            m_report->dynamicCall("ShowReport()");
        }
    }else{
        QMessageBox::information(this,tr("错误"),library->errorString(),0,0,0);
    }
}


