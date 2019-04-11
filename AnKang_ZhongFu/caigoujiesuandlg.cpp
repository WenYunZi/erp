#include "caigoujiesuandlg.h"

extern mymysql db;
extern QString userName;
extern myTCPsocket *sockClient;

caigoujiesuanDlg::caigoujiesuanDlg(QWidget *parent) :
    QDialog(parent)
{
    library = new QLibrary("MyReportDll",this);

    QLabel *gonghuoriqiLabel = new QLabel(tr("发货时间"),this);
    gonghuoriqiLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *xiahuaxianLabel = new QLabel(tr("--"),this);
    xiahuaxianLabel->setAlignment(Qt::AlignVCenter|Qt::AlignCenter);
    QLabel *gouhuofangLabel = new QLabel(tr("购货方"),this);
    gouhuofangLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *gongchengmingchengLabel = new QLabel(tr("工程名称"),this);
    gongchengmingchengLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    reportView = new QAxWidget(this);//报表显示窗口
    reportView->setControl("{9207E7EB-4CE3-40E1-8A5A-77C43DA9F503}");
    m_report = new QAxObject(this);//报表主体对象
    m_report->setControl("{4764040E-4222-4DEC-9F2E-82D46E212B3A}");
    reportView->dynamicCall("SetReport(IfrxReport*)", m_report->asVariant());//关联报表窗口和报表主体对象

    dateEdit1 = new QDateTimeEdit(this);
    dateEdit1->setDate(QDate::currentDate().addDays(-1));
    dateEdit1->setCalendarPopup(true);
//    dateEdit1->setEnabled(false);
    dateEdit1->setStyleSheet("color:black");
    dateEdit2 = new QDateTimeEdit(this);
    dateEdit2->setDate(QDate::currentDate());
    dateEdit2->setCalendarPopup(true);

    gouhuofangComBox = new myComboBox(this);
    db.sql_fillComboBoxItem("select Customer from ProductionNotice group by Customer",gouhuofangComBox);
    connect(gouhuofangComBox,SIGNAL(editTextChanged(QString)),this,SLOT(touch_gouhuofangComBox()));

    gongchengmingchengComBox = new QComboBox(this);
    gongchengmingchengComBox->setEditable(true);

    btn1 = new QPushButton(tr("供货明细"),this);
    btn1->setFixedWidth(120);
    connect(btn1,SIGNAL(clicked()),this,SLOT(on_gonghuomingxi()));


    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(gonghuoriqiLabel);
    hlayout->addWidget(dateEdit1);
    hlayout->addWidget(xiahuaxianLabel);
    hlayout->addWidget(dateEdit2);
    hlayout->addWidget(gouhuofangLabel);
    hlayout->addWidget(gouhuofangComBox,2);
    hlayout->addWidget(gongchengmingchengLabel);
    hlayout->addWidget(gongchengmingchengComBox,2);
    hlayout->addWidget(btn1);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(reportView);
}

void caigoujiesuanDlg::refresh()
{

}

void caigoujiesuanDlg::keyPressEvent(QKeyEvent *event)
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

void caigoujiesuanDlg::on_gonghuomingxi()
{
    QString customStr,gongchengmingchengStr;
    if(gouhuofangComBox->currentText() != ""){
        customStr = QString(" and Customer='%1'").arg(gouhuofangComBox->currentText());
    }else{
        QMessageBox::information(this,tr("提示信息"),tr("请输入供货方"),0,0,0);
        return;
    }


    if(gongchengmingchengComBox->currentText() != ""){
        gongchengmingchengStr = QString(" and Engineering='%1'").arg(gongchengmingchengComBox->currentText());
    }else{
        QMessageBox::information(this,tr("提示信息"),tr("请输入工程名称"),0,0,0);
        return;
    }

    QString baobiaoSQL = QString("select Customer,Engineering,MID(OutboundTime,1,10),REPLACE(StrengthGrade,' ','') StrengthGrade,SUM(ReceiptVolume),ReceiptVolume,Price,SUM(ReceiptVolume*Price),\
                                 SUM(CASE WHEN PouringMethod='车泵' THEN ReceiptVolume ELSE 0 END) chebeng,SUM(CASE WHEN PouringMethod='地泵' THEN ReceiptVolume ELSE 0 END) dibeng,COUNT(CumulativeNumber),B.CarPumpFee,B.PumpFee \
                                 from ProductionNotice A LEFT JOIN (SELECT * FROM SalesContractCustomerEngineeringForm WHERE CustomerName='%3' AND ProjectName='%4' AND BalanceDateTime<='%1' ORDER BY BalanceDateTime DESC LIMIT 1) B \
                                 ON (A.Customer=B.CustomerName AND A.Engineering=B.ProjectName) where Flag = '0' and OutboundTime between '%1' and '%2' and Customer='%3' and Engineering='%4' GROUP BY StrengthGrade,MID(OutboundTime,1,10),\
                                 PouringMethod,Price ORDER BY Customer,Engineering,OutboundTime,StrengthGrade,PouringMethod")
                                 .arg(dateEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),dateEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),gouhuofangComBox->currentText(),gongchengmingchengComBox->currentText());
    qDebug()<<baobiaoSQL;

    QString baobiaoSQL2 = QString("select REPLACE(StrengthGrade,' ','') StrengthGrade,SUM(ReceiptVolume),Price,SUM(ReceiptVolume*Price),SUM(CASE WHEN PouringMethod='车泵' THEN ReceiptVolume ELSE 0 END) chebeng,\
                                  SUM(CASE WHEN PouringMethod='地泵' THEN ReceiptVolume ELSE 0 END) dibeng from ProductionNotice where Flag = '0' and OutboundTime between '%1' and '%2' %3%4\
                                  GROUP BY StrengthGrade,Price ORDER BY StrengthGrade")
            .arg(dateEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),dateEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),customStr,gongchengmingchengStr);
    qDebug()<<baobiaoSQL2;


    if(library->load()){
        typedef void (*pFunc)(const char *,const char *,const char *);
        pFunc function=(pFunc)library->resolve("loadmyreport2");
        if(function){
            QString searchLastMatPrice = QString("select InitialBalance from SalesContractCustomerEngineeringForm where CustomerName='%1' and ProjectName='%2' group by CustomerName,ProjectName")
                    .arg(gouhuofangComBox->currentText(),gongchengmingchengComBox->currentText());
            QVariantList params1,params2,params3,params4,params5;
            params1<<"LastMatPrice"<<QString("\"")+db.sql_fetchrow_plus(searchLastMatPrice,0)+QString("\"");
            params2<<"Operator"<<QString("\"")+userName+QString("\"");
            params3<<"OperatingTime"<<QString("\"")+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")+QString("\"");
            params4<<"date1"<<QString("\"")+dateEdit1->date().toString("yyyy.MM.dd")+QString("\"");
            params5<<"date2"<<QString("\"")+dateEdit2->date().addDays(-1).toString("MM.dd")+QString("\"");
            function("./report/PremixedConcreteSupplyBill.fr3",baobiaoSQL.toLocal8Bit().data(),baobiaoSQL2.toLocal8Bit().data());
            m_report->dynamicCall("LoadReportFromFile(QString)", "report/PremixedConcreteSupplyBill.fr3");
            m_report->dynamicCall("SetVariable(QString, QVariant)", params1);
            m_report->dynamicCall("SetVariable(QString, QVariant)", params2);
            m_report->dynamicCall("SetVariable(QString, QVariant)", params3);
            m_report->dynamicCall("SetVariable(QString, QVariant)", params4);
            m_report->dynamicCall("SetVariable(QString, QVariant)", params5);
            m_report->dynamicCall("ShowReport()");
        }
    }else{
        QMessageBox::information(this,tr("错误"),library->errorString(),0,0,0);
    }
}

void caigoujiesuanDlg::touch_gouhuofangComBox()
{
    disconnect(gongchengmingchengComBox,SIGNAL(editTextChanged(QString)),this,SLOT(touch_gongchengmingchengComBox()));
    gongchengmingchengComBox->clear();
    QString gongchengmingchengComBoxSQL = QString("select Engineering from ProductionNotice where Customer = '%1' group by Engineering;").arg(gouhuofangComBox->currentText());
    db.sql_fillComboBoxItem(gongchengmingchengComBoxSQL.toStdString().data(),gongchengmingchengComBox);
    connect(gongchengmingchengComBox,SIGNAL(editTextChanged(QString)),this,SLOT(touch_gongchengmingchengComBox()));
}

void caigoujiesuanDlg::touch_gongchengmingchengComBox()
{
    QString searchBalanceDateTimeSQL = QString("select BalanceDateTime from SalesContractCustomerEngineeringForm where CustomerName='%1' and ProjectName='%2' group by CustomerName,ProjectName")
            .arg(gouhuofangComBox->currentText(),gongchengmingchengComBox->currentText());
    dateEdit1->setDateTime(QDateTime::fromString(db.sql_fetchrow_plus(searchBalanceDateTimeSQL,0),"yyyy-MM-dd hh:mm:ss"));
}

