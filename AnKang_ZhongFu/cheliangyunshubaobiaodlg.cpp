#include "cheliangyunshubaobiaodlg.h"

extern mymysql db;

cheliangyunshubaobiaoDlg::cheliangyunshubaobiaoDlg(QWidget *parent) :
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

    checkBox1 = new QCheckBox(tr("车牌号"),this);
    checkBox2 = new QCheckBox(tr("司机姓名"),this);
    checkBox3 = new QCheckBox(tr("客户名称"),this);
    checkBox4 = new QCheckBox(tr("车辆类型"),this);
    checkBox5 = new QCheckBox(tr("工程名称"),this);
    checkBox6 = new QCheckBox(tr("浇筑部位"),this);

    comBox1 = new QComboBox(this);
    comBox1->setEditable(true);
    comBox2 = new QComboBox(this);
    comBox2->setEditable(true);
    comBox3 = new QComboBox(this);
    comBox3->setEditable(true);
    comBox4 = new QComboBox(this);
    comBox4->setView(new QListView(this));
    comBox4->addItem(tr(""));
    comBox4->addItem(tr("自有车辆"));
    comBox4->addItem(tr("租用车辆"));
    comBox4->addItem(tr("临时车辆"));
    comBox4->setEditable(true);
    comBox5 = new QComboBox(this);
    comBox5->setEditable(true);
    comBox6 = new QComboBox(this);
    comBox6->setEditable(true);

    btn1 = new QPushButton(tr("发货明细"),this);
    connect(btn1,SIGNAL(clicked()),this,SLOT(on_fahuomingxi()));
    btn2 = new QPushButton(tr("车辆运距"),this);
//    btn2->setHidden(true);
    connect(btn2,SIGNAL(clicked()),this,SLOT(on_cheliangyunju()));
    btn3 = new QPushButton(tr("车辆油耗"),this);
    btn3->setHidden(true);
    connect(btn3,SIGNAL(clicked()),this,SLOT(on_cheliangyouhao()));

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(btn1);
    hlayout->addWidget(btn2);
    hlayout->addWidget(btn3);
    hlayout->setMargin(0);
    QWidget *widget = new QWidget;
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
    //connect(comBox3,SIGNAL(currentIndexChanged(int)),this,SLOT(on_comBox3Correspond()));

    const char *fillcomBox6SQL = "select PouringPosition from PouringPosition;";
    db.sql_fillComboBoxItem(fillcomBox6SQL,comBox6);

    const char *fillcomBox5SQL = "select Engineering from ProductionNotice group by Engineering;";
    db.sql_fillComboBoxItem(fillcomBox5SQL,comBox5);
}

void cheliangyunshubaobiaoDlg::refresh()
{

}

void cheliangyunshubaobiaoDlg::on_fahuomingxi()
{
    QString chepaihao,sijiName,kehumingcheng,cheliangleixing,gongchengmingcheng,jiaozhubuwei;
    if(checkBox1->checkState() == 2){
        chepaihao = QString(" and A.DeliveryVehicle='%1'").arg(comBox1->currentText());
    }
    if(checkBox2->checkState() == 2){
        sijiName = QString("and A.Driver='%1'").arg(comBox2->currentText());
    }
    if(checkBox3->checkState() == 2){
        kehumingcheng = QString("and A.Customer='%1'").arg(comBox3->currentText());
    }
    if(checkBox4->checkState() == 2){
        cheliangleixing = QString("and B.VehicleType='%1'").arg(comBox4->currentText());
    }
    if(checkBox5->checkState() == 2){
        gongchengmingcheng = QString("and A.Engineering='%1'").arg(comBox5->currentText());
    }
    if(checkBox6->checkState() == 2){
        jiaozhubuwei = QString("and A.PouringPosition='%1'").arg(comBox6->currentText());
    }

    QString baobiaoSQL = QString("SELECT * FROM ProductionNotice A LEFT JOIN (SELECT LicensePlate,VehicleType \
                                 FROM ConcreteVehicleInformation ) B ON (A.DeliveryVehicle=B.LicensePlate) WHERE \
                                 A.OutboundTime between '%1' and '%2'%3%4%5%6%7%8 ORDER BY DeliveryVehicle")
                    .arg(dateEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),dateEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),
                         chepaihao,sijiName,kehumingcheng,cheliangleixing,gongchengmingcheng,jiaozhubuwei);
    qDebug()<<baobiaoSQL;
    if(library->load()){
        typedef void (*pFunc)(const char *,const char *);
        pFunc function=(pFunc)library->resolve("loadmyreport");
        if(function){
            function("./report/VehicleTransportTable.fr3",baobiaoSQL.toLocal8Bit().data());
            m_report->dynamicCall("LoadReportFromFile(QString)", "report/VehicleTransportTable.fr3");
            m_report->dynamicCall("ShowReport()");
        }
    }else{
        QMessageBox::information(this,tr("错误"),library->errorString(),0,0,0);
    }
}

void cheliangyunshubaobiaoDlg::on_cheliangyunju()
{
    QString chepaihao,sijiName,kehumingcheng,gongchengmingcheng;
    if(checkBox1->checkState() == 2){
        chepaihao = QString(" and DeliveryVehicle='%1'").arg(comBox1->currentText());
    }
    if(checkBox2->checkState() == 2){
        sijiName = QString("and Driver='%1'").arg(comBox2->currentText());
    }
    if(checkBox3->checkState() == 2){
        kehumingcheng = QString("and Customer='%1'").arg(comBox3->currentText());
    }
    if(checkBox5->checkState() == 2){
        gongchengmingcheng = QString("and Engineering='%1'").arg(comBox5->currentText());
    }

    QString chepaihao2,sijiName2;
    if(checkBox1->checkState() == 2){
        chepaihao2 = QString(" and TransferVehicle='%1'").arg(comBox1->currentText());
    }
    if(checkBox2->checkState() == 2){
        sijiName2 = QString("and DriverName='%1'").arg(comBox2->currentText());
    }

    QString baobiaoSQL = QString("select DeliveryVehicle,Driver,Engineering,Mileage,count(Mileage),OutboundTime \
                                 from ProductionNotice where OutboundTime between '%1' and '%2' %3%4%5%6 group by Engineering,Mileage")
            .arg(dateEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),dateEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),chepaihao,sijiName,kehumingcheng,gongchengmingcheng);

    QString baobiaoSQL2 = QString("select * from TransferDistanceRecord where TransferTime between '%1' and '%2' %3%4")
            .arg(dateEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),dateEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),chepaihao2,sijiName2);


    if(library->load()){
        typedef void (*pFunc)(const char *,const char *,const char *);
        pFunc function=(pFunc)library->resolve("loadmyreport2");
        if(function){
            function("./report/VehicleDistanceStatistics.fr3",baobiaoSQL.toLocal8Bit().data(),baobiaoSQL2.toLocal8Bit().data());
            m_report->dynamicCall("LoadReportFromFile(QString)", "report/VehicleDistanceStatistics.fr3");
            m_report->dynamicCall("ShowReport()");
        }
    }else{
        QMessageBox::information(this,tr("错误"),library->errorString(),0,0,0);
    }
}

void cheliangyunshubaobiaoDlg::on_cheliangyouhao()
{
    QString chepaihao,sijiName;
    if(checkBox1->checkState() == 2){
        chepaihao = QString(" and LicensePlateNumber='%1'").arg(comBox1->currentText());
    }
    if(checkBox2->checkState() == 2){
        sijiName = QString("and Driver='%1'").arg(comBox2->currentText());
    }

    QString baobiaoSQL = QString("select * from ConcreteTruckRefuelingInformation where RefuelingTime between '%1' and '%2' %3%4")
                    .arg(dateEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),dateEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),chepaihao,sijiName);

    if(library->load()){
        typedef void (*pFunc)(const char *,const char *);
        pFunc function=(pFunc)library->resolve("loadmyreport");
        if(function){
            function("./report/VehicleFuelConsumptionStatistics.fr3",baobiaoSQL.toLocal8Bit().data());
            m_report->dynamicCall("LoadReportFromFile(QString)", "report/VehicleFuelConsumptionStatistics.fr3");
            m_report->dynamicCall("ShowReport()");
        }
    }else{
        QMessageBox::information(this,tr("错误"),library->errorString(),0,0,0);
    }
}

void cheliangyunshubaobiaoDlg::on_comBox3Correspond()
{
    comBox5->clear();
    QString fillcomBox5SQL = QString("select ProjectName from SalesContractCustomerEngineeringForm where CustomerName='%1';").arg(comBox3->currentText());
    db.sql_fillComboBoxItem(fillcomBox5SQL.toStdString().data(),comBox5);
}
