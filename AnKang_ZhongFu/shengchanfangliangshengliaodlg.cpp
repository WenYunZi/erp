#include "shengchanfangliangshengliaodlg.h"

extern mymysql db;

shengchanfangliangshengliaoDlg::shengchanfangliangshengliaoDlg(QWidget *parent) :
    QDialog(parent)
{
    //生产方量


    ViewToExcel = new myExcel(this);

    QLabel *TimeLabel = new QLabel(tr("日期:"),this);
    TimeLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *FuHaoLabel = new QLabel(tr("--"),this);
    FuHaoLabel->setAlignment(Qt::AlignCenter);

    DateTimeEdit1 = new QDateTimeEdit(this);
    DateTimeEdit1->setDate(QDate::currentDate().addDays(-1));
    DateTimeEdit1->setCalendarPopup(true);
    DateTimeEdit2 = new QDateTimeEdit(this);
    DateTimeEdit2->setDate(QDate::currentDate());
    DateTimeEdit2->setCalendarPopup(true);

    shengchanfangliangBtn = new QPushButton(tr("生产方量"),this);
    shengchanfangliangBtn->setFixedWidth(120);
    connect(shengchanfangliangBtn,SIGNAL(clicked()),this,SLOT(on_shengchanfangliangBtn()));
    shengliaofangliangBtn = new QPushButton(tr("省料方量"),this);
    shengliaofangliangBtn->setFixedWidth(120);
    connect(shengliaofangliangBtn,SIGNAL(clicked()),this,SLOT(on_shengliaofangliangBtn()));;
    shengchanzongfangliangBtn = new QPushButton(tr("生产总方量"),this);
    shengchanzongfangliangBtn->setFixedWidth(120);
    connect(shengchanzongfangliangBtn,SIGNAL(clicked()),this,SLOT(on_shengchanzongfangliangBtn()));;

    ExportBtn = new QPushButton(tr("导出"),this);
    ExportBtn->setFixedWidth(120);
    connect(ExportBtn,SIGNAL(clicked()),this,SLOT(on_ExportBtn()));

    shengchanfangliangView = new QTableView(this);

    QHBoxLayout *uplayout = new QHBoxLayout;
    uplayout->addWidget(TimeLabel,0);
    uplayout->addWidget(DateTimeEdit1,0);
    uplayout->addWidget(FuHaoLabel,0);
    uplayout->addWidget(DateTimeEdit2,0);
    uplayout->addWidget(shengchanfangliangBtn,0);
    uplayout->addWidget(shengliaofangliangBtn,0);
    uplayout->addWidget(shengchanzongfangliangBtn,0);
    uplayout->addWidget(ExportBtn,0);
    uplayout->addStretch(2);
    QVBoxLayout *updown = new QVBoxLayout(this);
    updown->addLayout(uplayout);
    updown->addWidget(shengchanfangliangView);

}

void shengchanfangliangshengliaoDlg::on_shengchanfangliangBtn()
{
    shengchanfangliangSQL = QString("SELECT StrengthGrade 等级,SUM(ReceiptVolume) 方量 ,SUM(RemainingMaterial) 省料 ,0 备注 FROM ProductionNotice where OutboundTime BETWEEN '%1' and '%2' GROUP BY StrengthGrade")
         .arg(DateTimeEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),DateTimeEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
    db.showview(shengchanfangliangSQL.toStdString().data(),shengchanfangliangView,&shengchanfangliangModel);
    shengchanfangliangView->setColumnWidth(0,250);

}

void shengchanfangliangshengliaoDlg::on_shengliaofangliangBtn()
{
    shengliaofangliangSQL = QString("SELECT StrengthGrade 等级,SUM(RemainingMaterial) 方量 FROM ProductionNotice where OutboundTime BETWEEN '%1' and '%2' GROUP BY StrengthGrade")
    .arg(DateTimeEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),DateTimeEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
    db.showview(shengliaofangliangSQL.toStdString().data(),shengchanfangliangView,&shengchanfangliangModel);
    shengchanfangliangView->setColumnWidth(0,250);


}

void shengchanfangliangshengliaoDlg::on_shengchanzongfangliangBtn()
{
    shengchanzongfangliangSQL = QString("SELECT Engineering 工程名称,Customer 单位,StrengthGrade 等级,\
                                        SUM(CASE WHEN Unit = '4#机组' OR Unit = '5#机组' THEN ReceiptVolume ELSE 0 END) 东站方量 ,\
                                        SUM(CASE WHEN Unit = '1#机组' OR Unit = '2#机组' THEN ReceiptVolume ELSE 0 END) 西站方量 ,\
                                        SUM(CASE WHEN Unit = '3#机组' THEN ReceiptVolume ELSE 0 END) C站方量\
                                        FROM ProductionNotice where OutboundTime BETWEEN '%1' and '%2' GROUP BY StrengthGrade ORDER BY Engineering,Customer")
                                        .arg(DateTimeEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),DateTimeEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"));


    db.showview(shengchanzongfangliangSQL.toStdString().data(),shengchanfangliangView,&shengchanfangliangModel);
    shengchanfangliangView->setColumnWidth(0,250);
    shengchanfangliangView->setColumnWidth(1,250);
    shengchanfangliangView->setColumnWidth(2,250);
}

void shengchanfangliangshengliaoDlg::on_ExportBtn()
{
    ViewToExcel->Table2ExcelByHtml(shengchanfangliangView,QString(""));
}
