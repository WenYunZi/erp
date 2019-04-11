#include "jiesuandandlg.h"

extern mymysql db;
extern QString userName;

jiesuandanDlg::jiesuandanDlg(QWidget *parent) :
    QDialog(parent)
{
    library = new QLibrary("MyReportDll",this);

    tabWidget = new QTabWidget(this);
    baobiao = new QWidget(this);
    kehuzhangmu = new QWidget(this);

    tableview2Excel = new myExcel(this);

    creatTabPage1();
    creatTabPage2();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tabWidget);
    layout->setSpacing(0);
}

void jiesuandanDlg::refresh()
{

}

QString jiesuandanDlg::ConvertToChinese(double x)
{
    return QString::number(x,'f',2);
}

void jiesuandanDlg::creatTabPage1()
{
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
    dateEdit1->setTime(QTime::fromString("04:00:00","hh:mm:ss"));
    dateEdit1->setCalendarPopup(true);
    connect(dateEdit1,SIGNAL(dateTimeChanged(QDateTime)),this,SLOT(on_dateChanged()));

    dateEdit2 = new QDateTimeEdit(this);
    dateEdit2->setCalendarPopup(true);
    dateEdit2->setDate(QDate::currentDate());
    dateEdit2->setTime(QTime::fromString("04:00:00","hh:mm:ss"));
    connect(dateEdit2,SIGNAL(dateTimeChanged(QDateTime)),this,SLOT(on_dateChanged()));

    checkBox1 = new QCheckBox(tr("客户名称"),this);
    checkBox2 = new QCheckBox(tr("工程名称"),this);

    comBox1 = new myComboBox(this);
    comBox1->setEditable(true);
    comBox2 = new myComboBox(this);
    comBox2->setEditable(true);

    btn1 = new QPushButton(tr("销售利润表"),this);
    connect(btn1,SIGNAL(clicked()),this,SLOT(on_rijiesuandan()));
    btn2 = new QPushButton(tr("利润汇总表"),this);
    connect(btn2,SIGNAL(clicked()),this,SLOT(on_yuejiesuandan()));
    btn3 = new QPushButton(tr("转账凭证"),this);
    connect(btn3,SIGNAL(clicked()),this,SLOT(on_zhuanzhangpingzheng()));
    btn4 = new QPushButton(tr("按钮"),this);
    btn4->setHidden(true);
    connect(btn4,SIGNAL(clicked()),this,SLOT(on_anniu()));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label1,0,0);
    layout->addWidget(dateEdit1,0,1);
    layout->addWidget(label2,0,2);
    layout->addWidget(dateEdit2,0,3);
    layout->addWidget(btn1,0,4,3,1,Qt::AlignVCenter);
    layout->addWidget(btn2,0,5,3,1,Qt::AlignVCenter);
    layout->addWidget(btn3,0,6,3,1,Qt::AlignVCenter);
    layout->addWidget(checkBox1,1,0);
    layout->addWidget(comBox1,1,1,1,3);
    layout->addWidget(checkBox2,2,0);
    layout->addWidget(comBox2,2,1,1,3);
    layout->setColumnStretch(0,0);
    layout->setColumnStretch(1,1);
    layout->setColumnStretch(2,0);
    layout->setColumnStretch(3,1);
    layout->setColumnStretch(4,1);
    layout->setColumnStretch(5,1);
    layout->setColumnStretch(6,1);
    layout->setColumnStretch(7,1);
    layout->setColumnStretch(8,1);
    layout->setColumnStretch(9,1);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(layout);
    vlayout->addWidget(reportView);

    QString fillcomBox1SQL = QString("select Customer from ProductionNotice where OutboundTime between '%1' and '%2' group by Customer;")
            .arg(dateEdit1->dateTime().addDays(-1).toString("yyyy-MM-dd hh:mm::ss"),dateEdit2->dateTime().toString("yyyy-MM-dd hh:mm::ss"));
    db.sql_fillComboBoxItem(fillcomBox1SQL.toStdString().data(),comBox1);
    connect(comBox1,SIGNAL(currentIndexChanged(int)),this,SLOT(on_comBox1React()));

    baobiao->setLayout(vlayout);
    tabWidget->addTab(baobiao,tr("报表查询"));
}

void jiesuandanDlg::creatTabPage2()
{
    SQL2 = "SELECT CustomerName 客户名称,\
        IF(SUM(B.Z) IS NULL,0,ROUND(SUM(B.Z),2)) 原材料货款,\
        IF(C.YF IS NULL,0,ROUND(C.YF,2)) 罐车运费,\
        IF(yunfei IS NULL, 0, yunfei) 路桥运费,\
        IF(rengong IS NULL, 0, rengong) 人工费,\
        IF(xianjin IS NULL, 0, xianjin) 现金交款,\
        IF(D.HNTGHE IS NULL,0,ROUND(D.HNTGHE,2)) 混凝土供货额,\
        ROUND(IF(SUM(B.Z) IS NULL,0,ROUND(SUM(B.Z),2))+IF(C.YF IS NULL,0,ROUND(C.YF,2))+IF(yunfei IS NULL, 0, yunfei)+\
        IF(rengong IS NULL, 0, rengong)+IF(xianjin IS NULL, 0, xianjin)-IF(D.HNTGHE IS NULL,0,ROUND(D.HNTGHE,2)),2) 合计\
        FROM\
            CustomerFiles A\
        LEFT JOIN (\
            SELECT\
                Supplier,\
                Material,\
                UnitPrice,\
                StorageKG,\
                StorageCube,\
                IF(SUM(UnitPrice*StorageKG/1000) IS NULL,0,ROUND(SUM(UnitPrice*StorageKG/1000),2)) Z\
            FROM\
                PurchaseReceipt\
            GROUP BY\
                Supplier,\
                Material\
        ) B ON (\
            SUBSTRING_INDEX(A.CustomerName, '顶', 1) = B.Supplier\
            AND LOCATE(SUBSTRING_INDEX(A.CustomerName, '顶', - 1),B.Material)!=0)\
        LEFT JOIN (\
            SELECT\
                FreightPrice,\
                ReceiptVolume,\
                Customer,\
                Driver,\
                SUM(ReceiptVolume*FreightPrice) YF\
            FROM\
                ProductionNotice group by Driver\
        ) C ON (\
            SUBSTRING_INDEX(A.CustomerName, '顶', 1) = C.Driver\
            AND LOCATE(\
                SUBSTRING_INDEX(A.CustomerName, '顶' ,- 1),\
                '罐车运费'\
            ) != 0\
        )\
        LEFT JOIN (\
            SELECT\
                Price,\
                ReceiptVolume,\
                Customer,\
                SUM(ReceiptVolume*Price) HNTGHE\
            FROM\
                ProductionNotice group by Customer\
        ) D ON (A.CustomerName = D.Customer)\
        GROUP BY\
            CustomerName";

    twoCheckBox = new QCheckBox(tr("客户名称"),this);

    twocomBox = new myComboBox(this);
    twocomBox->setEditable(true);
    const char *fillSQL = "select CustomerName from CustomerFiles;";
    db.sql_fillComboBoxItem3(fillSQL,twocomBox);

    twoview = new QTableView(this);
    db.showview(SQL2,twoview,&twomodel);

    twoshuaxinBtn = new QPushButton(tr("刷新/查询"),this);
    connect(twoshuaxinBtn,SIGNAL(clicked()),this,SLOT(on_twoshuaxin()));
    twodaochuBtn = new QPushButton(tr("导出"),this);
    connect(twodaochuBtn,SIGNAL(clicked()),this,SLOT(on_twodaochu()));

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(twoCheckBox,0);
    hlayout->addWidget(twocomBox,1);
    hlayout->addWidget(twoshuaxinBtn,1);
    hlayout->addWidget(twodaochuBtn,1);
    hlayout->addStretch(6);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(twoview);

    kehuzhangmu->setLayout(vlayout);
    tabWidget->addTab(kehuzhangmu,tr("账款查询"));
}

void jiesuandanDlg::on_rijiesuandan()
{
    QString customer,gongcheng,subcustomer,subgongcheng;
    if(checkBox1->checkState() == 2){
        customer = QString(" and A.Customer='%1'").arg(comBox1->currentText());
        subcustomer = QString(" and Customer='%1'").arg(comBox1->currentText());
    }
    if(checkBox2->checkState() == 2){
        gongcheng = QString(" and A.Engineering='%1'").arg(comBox2->currentText());
        subgongcheng = QString(" and Engineering='%1'").arg(comBox2->currentText());
    }

    QString baobiaoSQL = QString("SELECT\
                                 *,REPLACE (A.StrengthGrade, ' ', '') QDUDJ,\
                                 F.ZFL sumfangliang,\
                                 F.BSL sumbengsong,\
                                 IFNULL(IF(A.PouringMethod = '公司泵' OR A.PouringMethod = '外租泵',E.Price,'0'),0) DANJIA,\
                                 SUM(A.ReceiptVolume * A.FreightPrice) YUNFEI,\
                                 B.MAT,SUM(B.SJYL),B.XHJG,SUM(B.XIAOHAO)\
                             FROM\
                                 ProductionNotice A\
                             LEFT JOIN (\
                                 SELECT recordNo,C.MATNAME MAT,ROUND(SUM(SJMAT),1) SJYL,D.Price XHJG,SUM(Price * SJMAT / 1000) XIAOHAO FROM HISTDATA2 C\
                                 LEFT JOIN (SELECT * FROM MatXiaohaoPriceSetting) D ON (C.MATNAME = D.MatName AND D.startDate = (\
                                 SELECT MAX(startDate) FROM MatXiaohaoPriceSetting WHERE C.CHETIME > startDate AND MatName = C.MATNAME)\
                                 ) WHERE CHETIME BETWEEN '%1' AND '%2'	GROUP BY C.MATNAME,C.recordNo) B ON (B.recordNo = A.RecordNumber) \
                             LEFT JOIN (SELECT * FROM bengfeiSetting) E ON (A.Customer = E.CustomerName AND E.datetime = (\
                                     SELECT MAX(datetime) FROM bengfeiSetting WHERE A.OutboundTime > datetime AND A.Customer = CustomerName))\
                             LEFT JOIN (SELECT OutboundTime,Customer,Engineering,StrengthGrade,RecordNumber,Price,SUM(ReceiptVolume) ZFL,\
                                        IFNULL(SUM(CASE WHEN (PouringMethod = '公司泵' OR PouringMethod = '外租泵') THEN ReceiptVolume END),0) BSL FROM \
                                        ProductionNotice WHERE OutboundTime BETWEEN '%1' AND '%2' %5 %6 GROUP BY Customer,Engineering,StrengthGrade,\
                             Price) F ON (F.Customer=A.Customer AND F.Engineering=A.Engineering AND F.StrengthGrade=A.StrengthGrade AND F.Price=A.Price)\
                             WHERE\
                                 A.OutboundTime BETWEEN '%1' AND '%2' %3 %4\
                             GROUP BY\
                                 A.Customer,A.Engineering,A.StrengthGrade,A.Price,B.MAT\
                             ORDER BY\
                                 A.Customer,A.Engineering,A.StrengthGrade,A.Price,B.MAT")
                    .arg(dateEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),dateEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss")
                         ,customer,gongcheng,subcustomer,subgongcheng);
            qDebug()<<baobiaoSQL;
    if(library->load()){
        typedef void (*pFunc)(const char *,const char *);
        pFunc function=(pFunc)library->resolve("loadmyreport");
        if(function){
            function("report/SettlementSheet.fr3",baobiaoSQL.toLocal8Bit().data());
            QVariantList params1,params2;
            params1<<"data1"<<QString("\"")+dateEdit1->dateTime().toString("yyyy年MM月dd日h时")+QString("\"");
            params2<<"data2"<<QString("\"")+dateEdit2->dateTime().toString("yyyy年MM月dd日h时")+QString("\"");
            m_report->dynamicCall("LoadReportFromFile(QString)", "report/SettlementSheet.fr3");
            m_report->dynamicCall("SetVariable(QString, QVariant)", params1);
            m_report->dynamicCall("SetVariable(QString, QVariant)", params2);
            m_report->dynamicCall("ShowReport()");
        }else{
            QMessageBox::information(this,tr("错误"),library->errorString(),0,0,0);
        }
    }else{
        QMessageBox::information(this,tr("错误"),library->errorString(),0,0,0);
    }
}

void jiesuandanDlg::on_yuejiesuandan()
{
    QString customer,gongcheng;
    if(checkBox1->checkState() == 2){
        customer = QString(" and Customer='%1'").arg(comBox1->currentText());
    }
    if(checkBox2->checkState() == 2){
        gongcheng = QString(" and Engineering='%1'").arg(comBox2->currentText());
    }

    QString baobiaoSQL = QString("SELECT *,REPLACE (StrengthGrade, ' ', '') QDUDJ, SUM(ReceiptVolume) sumfangliang,SUM(ReceiptVolume*A.Price) shouru, IFNULL(SUM(\
                                 CASE WHEN (PouringMethod = '公司泵' OR PouringMethod = '外租泵') THEN ReceiptVolume END),0) sumbengsong,\
                                 IFNULL(IF(A.PouringMethod = '公司泵' OR A.PouringMethod = '外租泵',E.Price,'0'),0) DANJIA,\
                                 SUM(ReceiptVolume * FreightPrice) YUNFEI,SUM(B.XIAOHAO) XIAOHAOJIAGE FROM ProductionNotice A \
                            LEFT JOIN (SELECT recordNo,SUM(Price * SJMAT / 1000) XIAOHAO FROM HISTDATA2 C \
                            LEFT JOIN (SELECT * FROM MatXiaohaoPriceSetting) D ON (C.MATNAME = D.MatName AND D.startDate = (SELECT MAX(startDate) \
                                 FROM MatXiaohaoPriceSetting WHERE C.CHETIME > startDate AND MatName = C.MATNAME)) where CHETIME BETWEEN '%1' AND '%2' GROUP BY recordNo) B ON (A.RecordNumber = B.recordNo) \
                            LEFT JOIN (SELECT * FROM bengfeiSetting) E ON (A.Customer = E.CustomerName AND E.datetime = (SELECT MAX(datetime) FROM bengfeiSetting\
                                 WHERE A.OutboundTime > datetime AND A.Customer = CustomerName))\
                            WHERE OutboundTime BETWEEN '%1' AND '%2' GROUP BY Customer ORDER BY Customer")
                    .arg(dateEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),dateEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),customer,gongcheng);
    if(library->load()){
        typedef void (*pFunc)(const char *,const char *);
        pFunc function=(pFunc)library->resolve("loadmyreport");
        if(function){
            function("report/lirunhuizongbiao.fr3",baobiaoSQL.toLocal8Bit().data());
            QVariantList params1,params2;
            params1<<"data1"<<QString("\"")+dateEdit1->dateTime().toString("yyyy年MM月dd日h时")+QString("\"");
            params2<<"data2"<<QString("\"")+dateEdit2->dateTime().toString("yyyy年MM月dd日h时")+QString("\"");
            m_report->dynamicCall("LoadReportFromFile(QString)", "report/lirunhuizongbiao.fr3");
            m_report->dynamicCall("SetVariable(QString, QVariant)", params1);
            m_report->dynamicCall("SetVariable(QString, QVariant)", params2);
            m_report->dynamicCall("ShowReport()");
        }else{
                 QMessageBox::information(this,tr("错误"),library->errorString(),0,0,0);
        }
    }else{
        QMessageBox::information(this,tr("错误"),library->errorString(),0,0,0);
    }
}

void jiesuandanDlg::on_zhuanzhangpingzheng()
{
    QString customer,gongcheng,subcustomer,subgongcheng;
    if(checkBox1->checkState() == 2){
        customer = QString(" and A.Customer='%1'").arg(comBox1->currentText());
        subcustomer = QString(" and Customer='%1'").arg(comBox1->currentText());
    }
    if(checkBox2->checkState() == 2){
        gongcheng = QString(" and A.Engineering='%1'").arg(comBox2->currentText());
        subgongcheng = QString(" and Engineering='%1'").arg(comBox2->currentText());
    }

    QString baobiaoSQL = QString("SELECT\
                                 *,REPLACE (A.StrengthGrade, ' ', '') QDUDJ,\
                                 F.ZFL sumfangliang,\
                                 F.BSL sumbengsong,\
                                 IFNULL(IF(A.PouringMethod = '公司泵' OR A.PouringMethod = '外租泵',E.Price,'0'),0) DANJIA,\
                                 SUM(A.ReceiptVolume * A.FreightPrice) YUNFEI,\
                                 B.MAT,SUM(B.SJYL),B.XHJG,SUM(B.XIAOHAO)\
                             FROM\
                                 ProductionNotice A\
                             LEFT JOIN (\
                                 SELECT recordNo,C.MATNAME MAT,ROUND(SUM(SJMAT),1) SJYL,D.Price XHJG,SUM(Price * SJMAT / 1000) XIAOHAO FROM HISTDATA2 C\
                                 LEFT JOIN (SELECT * FROM MatXiaohaoPriceSetting) D ON (C.MATNAME = D.MatName AND D.startDate = (\
                                 SELECT MAX(startDate) FROM MatXiaohaoPriceSetting WHERE C.CHETIME > startDate AND MatName = C.MATNAME)\
                                 ) WHERE CHETIME BETWEEN '%1' AND '%2'	GROUP BY C.MATNAME,C.recordNo) B ON (B.recordNo = A.RecordNumber) \
                             LEFT JOIN (SELECT * FROM bengfeiSetting) E ON (A.Customer = E.CustomerName AND E.datetime = (\
                                     SELECT MAX(datetime) FROM bengfeiSetting WHERE A.OutboundTime > datetime AND A.Customer = CustomerName))\
                             LEFT JOIN (SELECT OutboundTime,Customer,Engineering,StrengthGrade,RecordNumber,Price,SUM(ReceiptVolume) ZFL,\
                                        IFNULL(SUM(CASE WHEN (PouringMethod = '公司泵' OR PouringMethod = '外租泵') THEN ReceiptVolume END),0) BSL FROM \
                                        ProductionNotice WHERE OutboundTime BETWEEN '%1' AND '%2' %5 %6 GROUP BY Customer,Engineering,StrengthGrade,\
                             Price) F ON (F.Customer=A.Customer AND F.Engineering=A.Engineering AND F.StrengthGrade=A.StrengthGrade AND F.Price=A.Price)\
                             WHERE\
                                 A.OutboundTime BETWEEN '%1' AND '%2' %3 %4\
                             GROUP BY\
                                 A.Customer,A.Engineering,A.StrengthGrade,A.Price,B.MAT\
                             ORDER BY\
                                 A.Customer,A.Engineering,A.StrengthGrade,A.Price,B.MAT")
                    .arg(dateEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),dateEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss")
                         ,customer,gongcheng,subcustomer,subgongcheng);
            qDebug()<<baobiaoSQL;
    QString baobiaoSQL1 = QString("SELECT\
                                 *,SUM(B.XIAOHAO)\
                             FROM\
                                 ProductionNotice A\
                             LEFT JOIN (\
                                 SELECT recordNo,C.MATNAME MAT,ROUND(SUM(SJMAT),1) SJYL,D.Price XHJG,SUM(Price * SJMAT / 1000) XIAOHAO FROM HISTDATA2 C\
                                 LEFT JOIN (SELECT * FROM MatXiaohaoPriceSetting) D ON (C.MATNAME = D.MatName AND D.startDate = (\
                                 SELECT MAX(startDate) FROM MatXiaohaoPriceSetting WHERE C.CHETIME > startDate AND MatName = C.MATNAME)\
                                 ) WHERE CHETIME BETWEEN '%1' AND '%2'	GROUP BY C.MATNAME,C.recordNo) B ON (B.recordNo = A.RecordNumber) \
                             WHERE\
                                 A.OutboundTime BETWEEN '%1' AND '%2' AND A.Customer=:Customer AND A.Engineering=:Engineering AND \
                                 A.StrengthGrade=:StrengthGrade AND A.Price=:Price\
                             GROUP BY\
                                 A.Customer,A.Engineering,A.StrengthGrade,A.Price\
                             ORDER BY\
                                 A.Customer,A.Engineering,A.StrengthGrade,A.Price")
                    .arg(dateEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),dateEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss")
                         ,customer,gongcheng);
    if(library->load()){
        typedef void (*pFunc)(const char *,const char *,const char *);
        pFunc function=(pFunc)library->resolve("loadmyreport2");
        if(function){
            function("report/zhuanzhangpingzheng.fr3",baobiaoSQL.toLocal8Bit().data(),baobiaoSQL1.toLocal8Bit().data());
            QVariantList params1,params2,params3;
            params1<<"data1"<<QString("\"")+dateEdit1->dateTime().toString("yyyy年MM月dd日h时")+QString("\"");
            params2<<"data2"<<QString("\"")+dateEdit2->dateTime().toString("yyyy年MM月dd日h时")+QString("\"");
            params3<<"ZDR"<<QString("\"")+userName+QString("\"");
            m_report->dynamicCall("LoadReportFromFile(QString)", "report/zhuanzhangpingzheng.fr3");
            m_report->dynamicCall("SetVariable(QString, QVariant)", params1);
            m_report->dynamicCall("SetVariable(QString, QVariant)", params2);
            m_report->dynamicCall("SetVariable(QString, QVariant)", params3);
            m_report->dynamicCall("ShowReport()");
        }else{
                 QMessageBox::information(this,tr("错误"),library->errorString(),0,0,0);
        }
    }else{
        QMessageBox::information(this,tr("错误"),library->errorString(),0,0,0);
    }
}

void jiesuandanDlg::on_dateChanged()
{
    disconnect(comBox1,SIGNAL(currentIndexChanged(int)),this,SLOT(on_comBox1React()));
    comBox1->clear();
    QString fillcomBox1SQL = QString("select Customer from ProductionNotice where OutboundTime between '%1' and '%2' group by Customer;")
            .arg(dateEdit1->dateTime().toString("yyyy-MM-dd hh:mm::ss"),dateEdit2->dateTime().toString("yyyy-MM-dd hh:mm::ss"));
    db.sql_fillComboBoxItem(fillcomBox1SQL.toStdString().data(),comBox1);
    connect(comBox1,SIGNAL(currentIndexChanged(int)),this,SLOT(on_comBox1React()));
}

void jiesuandanDlg::on_comBox1React()
{
    comBox2->clear();
    QString fillcomBox1SQL = QString("select Engineering from ProductionNotice where OutboundTime between '%1' and '%2' and Customer='%3' group by Engineering;")
            .arg(dateEdit1->dateTime().toString("yyyy-MM-dd hh:mm::ss"),dateEdit2->dateTime().toString("yyyy-MM-dd hh:mm::ss"),comBox1->currentText());
    db.sql_fillComboBoxItem(fillcomBox1SQL.toStdString().data(),comBox2);
}

void jiesuandanDlg::on_anniu()
{

}

void jiesuandanDlg::on_twodaochu()
{
    tableview2Excel->Table2ExcelByHtml(twoview,"客户账目");
}

void jiesuandanDlg::on_twoshuaxin()
{
    QString kehu;
    if(twoCheckBox->checkState() == 2){
        kehu = QString(" where CustomerName like '%%1%' ").arg(twocomBox->currentText());
    }

    QString searchSQL = QString("SELECT CustomerName 客户名称,\
                                IF(SUM(B.Z) IS NULL,0,ROUND(SUM(B.Z),2)) 原材料货款,\
                                IF(C.YF IS NULL,0,ROUND(C.YF,2)) 罐车运费,\
                                IF(yunfei IS NULL, 0, yunfei) 路桥运费,\
                                IF(rengong IS NULL, 0, rengong) 人工费,\
                                IF(xianjin IS NULL, 0, xianjin) 现金交款,\
                                IF(D.HNTGHE IS NULL,0,ROUND(D.HNTGHE,2)) 混凝土供货额,\
                                ROUND(IF(SUM(B.Z) IS NULL,0,ROUND(SUM(B.Z),2))+IF(C.YF IS NULL,0,ROUND(C.YF,2))+IF(yunfei IS NULL, 0, yunfei)+\
                                IF(rengong IS NULL, 0, rengong)+IF(xianjin IS NULL, 0, xianjin)-IF(D.HNTGHE IS NULL,0,ROUND(D.HNTGHE,2)),2) 合计\
                                FROM\
                                    CustomerFiles A\
                                LEFT JOIN (\
                                    SELECT\
                                        Supplier,\
                                        Material,\
                                        UnitPrice,\
                                        StorageKG,\
                                        StorageCube,\
                                        IF(SUM(UnitPrice*StorageKG/1000) IS NULL,0,ROUND(SUM(UnitPrice*StorageKG/1000),2)) Z\
                                    FROM\
                                        PurchaseReceipt\
                                    GROUP BY\
                                        Supplier,\
                                        Material\
                                ) B ON (\
                                    SUBSTRING_INDEX(A.CustomerName, '顶', 1) = B.Supplier\
                                    AND LOCATE(SUBSTRING_INDEX(A.CustomerName, '顶', - 1),B.Material)!=0)\
                                LEFT JOIN (\
                                    SELECT\
                                        FreightPrice,\
                                        ReceiptVolume,\
                                        Customer,\
                                        Driver,\
                                        SUM(ReceiptVolume*FreightPrice) YF\
                                    FROM\
                                        ProductionNotice group by Driver\
                                ) C ON (\
                                    SUBSTRING_INDEX(A.CustomerName, '顶', 1) = C.Driver\
                                    AND LOCATE(\
                                        SUBSTRING_INDEX(A.CustomerName, '顶' ,- 1),\
                                        '罐车运费'\
                                    ) != 0\
                                )\
                                LEFT JOIN (\
                                    SELECT\
                                        Price,\
                                        ReceiptVolume,\
                                        Customer,\
                                        SUM(ReceiptVolume*Price) HNTGHE\
                                    FROM\
                                        ProductionNotice group by Customer\
                                ) D ON (A.CustomerName = D.Customer) %1\
                                GROUP BY\
                                    CustomerName").arg(kehu);

    db.showview(searchSQL.toStdString().data(),twoview,&twomodel);
}
