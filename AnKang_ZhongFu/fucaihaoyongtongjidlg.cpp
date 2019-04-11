#include "fucaihaoyongtongjidlg.h"

extern mymysql db;

fucaihaoyongtongjiDlg::fucaihaoyongtongjiDlg(QWidget *parent) :
    QDialog(parent)
{
    SQL = "select RecordNumber 记录号,AuxiliaryNumber 辅材编号,MaterialName 辅材名称,\
            Specifications 规格,QuantitiesConsumed 耗用数量,Company 单位,UnitPrice 单价,\
            amountOfConsumption 耗用金额,Outdate 出库日期,DeviceType  设备类型,\
            LicensePlateOrDeviceName 车牌设备名称,CollarMan 领用人,Reviewer 审核人, \
            GenericClass 所属大类,SubordinateClass 所属小类 from MaterialConsumptionStatistics;";

    QLabel *label1 = new QLabel(tr("领用日期"),this);
    label1->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label2 = new QLabel(tr("--"),this);
    label2->setAlignment(Qt::AlignCenter);

    checkBox1 = new QCheckBox(tr("设备类型"),this);
    checkBox2 = new QCheckBox(tr("车牌/设备"),this);
    checkBox3 = new QCheckBox(tr("辅材类别"),this);
    checkBox4 = new QCheckBox(tr("辅材名称"),this);
    checkBox5 = new QCheckBox(tr("小类"),this);
    comBox1 = new QComboBox(this);
    const char *fillSQL1 = "SELECT DeviceType FROM MaterialConsumptionStatistics group by DeviceType;";
    db.sql_fillComboBoxItem(fillSQL1,comBox1);
    comBox2 = new QComboBox(this);
    const char *fillSQL2 = "SELECT LicensePlateOrDeviceName FROM MaterialConsumptionStatistics group by LicensePlateOrDeviceName;";
    db.sql_fillComboBoxItem(fillSQL2,comBox2);
    comBox3 = new QComboBox(this);
    const char *fillSQL3 = "SELECT GenericClass FROM MaterialConsumptionStatistics group by GenericClass;";
    db.sql_fillComboBoxItem(fillSQL3,comBox3);
    comBox4 = new QComboBox(this);
    const char *fillSQL4 = "SELECT MaterialName FROM MaterialConsumptionStatistics group by MaterialName;";
    db.sql_fillComboBoxItem(fillSQL4,comBox4);
    comBox5 = new QComboBox(this);
    const char *fillSQL5 = "SELECT SubordinateClass FROM MaterialConsumptionStatistics group by SubordinateClass;";
    db.sql_fillComboBoxItem(fillSQL5,comBox5);
    dateEidt1 = new QDateEdit(QDate::currentDate(),this);
    dateEidt1->setCalendarPopup(true);
    dateEidt2 = new QDateEdit(QDate::currentDate(),this);
    dateEidt2->setCalendarPopup(true);
    chaxun = new QPushButton(tr("查询"),this);
    connect(chaxun,SIGNAL(clicked()),this,SLOT(on_chaxunBtn()));

    view = new QTableView(this);
    db.showview(SQL,view,&model);
    view->setColumnWidth(8,120);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label1,0,0);
    layout->addWidget(dateEidt1,0,1);
    layout->addWidget(label2,0,2);
    layout->addWidget(dateEidt2,0,3);
    layout->addWidget(checkBox1,0,4);
    layout->addWidget(comBox1,0,5);
    layout->addWidget(checkBox2,0,6);
    layout->addWidget(comBox2,0,7);
    layout->addWidget(chaxun,0,8,2,1,Qt::AlignVCenter);
    layout->addWidget(checkBox3,1,0);
    layout->addWidget(comBox3,1,1);
    layout->addWidget(checkBox4,1,4);
    layout->addWidget(comBox4,1,5);
    layout->addWidget(checkBox5,1,6);
    layout->addWidget(comBox5,1,7);
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
    vlayout->addWidget(view);
}

void fucaihaoyongtongjiDlg::refresh()
{
    on_chaxunBtn();
}

void fucaihaoyongtongjiDlg::keyPressEvent(QKeyEvent *event)
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

void fucaihaoyongtongjiDlg::on_chaxunBtn()
{
    QString str1,str2,str3,str4,str5;
    if(checkBox1->checkState() == 2){
        str1 = QString(" and DeviceType='%1'").arg(comBox1->currentText());
    }
    if(checkBox2->checkState() == 2){
        str2 = QString(" and LicensePlateOrDeviceName='%1'").arg(comBox2->currentText());
    }
    if(checkBox3->checkState() == 2){
        str3 = QString(" and GenericClass='%1'").arg(comBox3->currentText());
    }
    if(checkBox4->checkState() == 2){
        str4 = QString(" and MaterialName='%1'").arg(comBox4->currentText());
    }
    if(checkBox5->checkState() == 2){
        str5 = QString(" and SubordinateClass='%1'").arg(comBox5->currentText());
    }

    QString searchSQL = QString("select RecordNumber 记录号,AuxiliaryNumber 辅材编号,MaterialName 辅材名称,\
                                Specifications 规格,QuantitiesConsumed 耗用数量,Company 单位,UnitPrice 单价,\
                                amountOfConsumption 耗用金额,Outdate 出库日期,DeviceType  设备类型,\
                                LicensePlateOrDeviceName 车牌设备名称,CollarMan 领用人,Reviewer 审核人, \
                                GenericClass 所属大类,SubordinateClass 所属小类 from MaterialConsumptionStatistics \
                                where Outdate between '%1' and '%2'%3%4%5%6%7;")
            .arg(dateEidt1->date().toString("yyyy-MM-dd"),dateEidt2->date().addDays(1).toString("yyyy-MM-dd"),
                 str1,str2,str3,str4,str5);
    db.showview(searchSQL.toStdString().data(),view,&model);
    qDebug()<<db.geterror();
}
