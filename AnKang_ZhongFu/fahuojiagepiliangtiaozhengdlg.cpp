#include "fahuojiagepiliangtiaozhengdlg.h"

extern mymysql db;
extern QString userName;
extern myTCPsocket *sockClient;

fahuojiagepiliangtiaozhengDlg::fahuojiagepiliangtiaozhengDlg(QWidget *parent) :
    QDialog(parent)
{
    tabWidget = new QTabWidget(this);
    jiagetiaozheng = new QWidget(this);
    shijianduanjiagetiaozhengjilu = new QWidget(this);

    creatTabPage1();
    creatTabPage2();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tabWidget);
}

void fahuojiagepiliangtiaozhengDlg::refresh()
{
//    on_oneFindBtn();
//    on_twoFindBtn();
}

void fahuojiagepiliangtiaozhengDlg::keyPressEvent(QKeyEvent *event)
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

void fahuojiagepiliangtiaozhengDlg::creatTabPage1()
{
    SQL1 = "select TaskList 任务单,StrengthGrade 强度等级,Customer 客户,Engineering 工程,Unit 机组,ReceiptVolume 发货方量,\
            OutboundTime 出站时间,DeliveryVehicle 送货车辆,RecordNumber 记录编号,Price 价格,ReceiptVolume*Price 总金额 \
            from ProductionNotice limit 0;";

    QLabel *ProductTimeLabel = new QLabel(tr("生产时间"),this);
    ProductTimeLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *FuHaoLabel = new QLabel(tr("--"),this);
    FuHaoLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *StrengthGradeLabel = new QLabel(tr("强度等级"),this);
    StrengthGradeLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *NewPriceLabel = new QLabel(tr("最新价格"),this);
    NewPriceLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *CustomerNameLabel = new QLabel(tr("客户名称"),this);
    CustomerNameLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *OperatorLabel = new QLabel(tr("调整人"),this);
    OperatorLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    oneEngineerCheckBox = new QCheckBox(tr("工程名称"),this);

    dateEdit1 = new QDateTimeEdit(this);
    dateEdit1->setDate(QDate::currentDate());
    dateEdit1->setCalendarPopup(true);
    connect(dateEdit1,SIGNAL(dateTimeChanged(QDateTime)),this,SLOT(on_dateChange()));

    dateEdit2 = new QDateTimeEdit(this);
    dateEdit2->setDate(QDate::currentDate().addDays(1));
    dateEdit2->setCalendarPopup(true);
    connect(dateEdit2,SIGNAL(dateTimeChanged(QDateTime)),this,SLOT(on_dateChange()));


    oneStrengthGradeCombox = new QComboBox(this);

    oneCustomerNameCombox = new myComboBox(this);
    db.sql_fillComboBoxItem(QString("SELECT Customer FROM ProductionNotice where OutboundTime between '%1' and '%2' group by Customer")
                            .arg(dateEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),dateEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss")),oneCustomerNameCombox);
    connect(oneCustomerNameCombox,SIGNAL(editTextChanged(QString)),this,SLOT(on_oneCustomerNameCombox()));

    oneEngineerCombox = new myComboBox(this);

    oneNewPriceLineEdit = new QLineEdit(this);

    OperatorLineEdit = new QLineEdit(userName,this);
    OperatorLineEdit->setReadOnly(true);

    oneConfirmBtn = new QPushButton(tr("新价格确认"),this);
    oneConfirmBtn->setFixedWidth(150);
    connect(oneConfirmBtn,SIGNAL(clicked()),this,SLOT(on_oneConfirmBtn()));

    oneFindBtn = new QPushButton(tr("生产记录查询"),this);
    oneFindBtn->setFixedWidth(150);
    connect(oneFindBtn,SIGNAL(clicked()),this,SLOT(on_oneFindBtn()));

    view = new QTableView(this);
    db.showview(SQL1,view,&model);
    view->setColumnWidth(0,120);
    view->setColumnWidth(2,120);
    view->setColumnWidth(3,120);
    view->setColumnWidth(6,120);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(ProductTimeLabel,0,0);
    layout->addWidget(dateEdit1,0,1);
    layout->addWidget(FuHaoLabel,0,2);
    layout->addWidget(dateEdit2,0,3);
    layout->addWidget(StrengthGradeLabel,0,4);
    layout->addWidget(oneStrengthGradeCombox,0,5);
    layout->addWidget(NewPriceLabel,0,6);
    layout->addWidget(oneNewPriceLineEdit,0,7);
    layout->addWidget(CustomerNameLabel,1,0);
    layout->addWidget(oneCustomerNameCombox,1,1,1,3);
    layout->addWidget(OperatorLabel,1,6);
    layout->addWidget(OperatorLineEdit,1,7);
    layout->addWidget(oneEngineerCheckBox,2,0);
    layout->addWidget(oneEngineerCombox,2,1,1,3);
    layout->setColumnStretch(0,0);
    layout->setColumnStretch(1,1);
    layout->setColumnStretch(2,0);
    layout->setColumnStretch(3,1);
    layout->setColumnStretch(4,0);
    layout->setColumnStretch(5,1);
    layout->setColumnStretch(6,0);
    layout->setColumnStretch(7,1);

    QHBoxLayout *hlayout1 = new QHBoxLayout;
    hlayout1->addWidget(oneConfirmBtn);

    QHBoxLayout *hlayout2 = new QHBoxLayout;
    hlayout2->addWidget(oneFindBtn,1);
    hlayout2->addStretch(12);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(layout);
    vlayout->addLayout(hlayout1);
    vlayout->addSpacing(20);
    vlayout->addLayout(hlayout2);
    vlayout->addWidget(view);

    jiagetiaozheng->setLayout(vlayout);
    tabWidget->addTab(jiagetiaozheng,tr("价格调整"));
}

void fahuojiagepiliangtiaozhengDlg::creatTabPage2()
{
    SQL2 = "select CustomerName 客户名称,ProjectName 工程名称,product 产品,DateOfShipment1 发货日期起,DateOfShipment2 发货日期止,\
            NewPrice 新价格,OriginalPrice 原价格,AdjustmentMan 调整人,AdjustmentTime 调整时间 from TimePeriodPriceAdjustmentRecord;";

    QLabel *UpdateTimeLabel = new QLabel(tr("调整日期"),this);
    UpdateTimeLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *FuHaoLabel = new QLabel(tr("--"),this);
    FuHaoLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    twodateEdit1 = new QDateTimeEdit(this);
    twodateEdit1->setDate(QDate::currentDate());
    twodateEdit1->setCalendarPopup(true);

    twodateEdit2 = new QDateTimeEdit(this);
    twodateEdit2->setDate(QDate::currentDate().addDays(1));
    twodateEdit2->setCalendarPopup(true);

    twoCustomerComBox = new myComboBox(this);
    db.sql_fillComboBoxItem("SELECT CustomerName FROM CustomerFiles",twoCustomerComBox);
    connect(twoCustomerComBox,SIGNAL(currentIndexChanged(int)),this,SLOT(on_twoCustomerComBox()));

    twoEngineerComBox = new QComboBox(this);

    twoCustomerCheckBox = new QCheckBox(tr("客户名称"),this);
    twoEngineerCheckBox = new QCheckBox(tr("工程名称"),this);

    twoFindBtn = new QPushButton(tr("查询"),this);
    connect(twoFindBtn,SIGNAL(clicked()),this,SLOT(on_twoFindBtn()));

    twoview = new QTableView(this);
    db.showview(SQL2,twoview,&twomodel);
    twoview->setColumnWidth(0,300);
    twoview->setColumnWidth(1,300);
    twoview->setColumnWidth(8,130);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(UpdateTimeLabel,0);
    hlayout->addWidget(twodateEdit1,1);
    hlayout->addWidget(FuHaoLabel,0);
    hlayout->addWidget(twodateEdit2,1);
    hlayout->addWidget(twoCustomerCheckBox,0);
    hlayout->addWidget(twoCustomerComBox,2);
    hlayout->addWidget(twoEngineerCheckBox,0);
    hlayout->addWidget(twoEngineerComBox,2);
    hlayout->addWidget(twoFindBtn,1);
    hlayout->addStretch(2);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(twoview);

    shijianduanjiagetiaozhengjilu->setLayout(vlayout);
    tabWidget->addTab(shijianduanjiagetiaozhengjilu,tr("价格调整记录"));
}

void fahuojiagepiliangtiaozhengDlg::on_oneConfirmBtn()
{
    if(oneNewPriceLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入最新价格"),0,0);
        return;
    }
    int rowcount = model->rowCount();
    if(rowcount == 0){
        QMessageBox::information(this,tr("提示信息"),tr("请筛选出要调整的记录"),0,0);
        return;
    }

    db.sql_exec("begin");
    //插入更新记录
    QString insertSQL = QString("insert into TimePeriodPriceAdjustmentRecord (CustomerName,ProjectName,product,DateOfShipment1,DateOfShipment2,\
                                NewPrice,OriginalPrice,AdjustmentMan,AdjustmentTime) values ('%1','%2','%3','%4','%5','%6','%7','%8','%9');")
                .arg(oneCustomerNameCombox->currentText(),oneEngineerCombox->currentText(),oneStrengthGradeCombox->currentText(),dateEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),
                     dateEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),oneNewPriceLineEdit->text(),model->item(0,9)->text(),OperatorLineEdit->text(),
                     QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    if(db.sql_exec(insertSQL) == -1){
        db.sql_exec("rollback");
        return;
    }
    //更改生产通知单上的价格
    QString updateSQL = QString("update ProductionNotice set Price='%1' %2").arg(oneNewPriceLineEdit->text(),tiaojian);
    if(db.sql_exec(updateSQL) == -1){
        db.sql_exec("rollback");
        return;
    }
    db.sql_exec("commit");

    oneNewPriceLineEdit->clear();
    on_oneFindBtn();
    QMessageBox::information(this,tr("提示信息"),tr("价格调整成功"),0,0);
}

void fahuojiagepiliangtiaozhengDlg::on_oneFindBtn()
{
    QString gongcheng;
    if(oneEngineerCheckBox->checkState() == 2){
        gongcheng = QString(" and Engineering='%1'").arg(oneEngineerCombox->currentText());
    }
    QString searchSQL = QString("select TaskList 任务单,StrengthGrade 强度等级,Customer 客户,Engineering 工程,Unit 机组,ReceiptVolume 发货方量,\
                                OutboundTime 出站时间,DeliveryVehicle 送货车辆,RecordNumber 记录编号,Price 价格,Price*ReceiptVolume 总金额 \
                                from ProductionNotice where OutboundTime between '%1' and '%2' and Customer='%3' %4 and StrengthGrade='%5';")
            .arg(dateEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),dateEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),
                 oneCustomerNameCombox->currentText(),gongcheng,oneStrengthGradeCombox->currentText());
    db.showview(searchSQL.toStdString().data(),view,&model);

    tiaojian = searchSQL.mid(searchSQL.indexOf("where"));
}


void fahuojiagepiliangtiaozhengDlg::on_oneCustomerNameCombox()
{
    oneEngineerCombox->clear();
    oneStrengthGradeCombox->clear();
    QString filloneEngineerCombox = QString("SELECT Engineering FROM ProductionNotice where OutboundTime between '%1' and '%2' and Customer='%3' group by Engineering")
            .arg(dateEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),dateEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),oneCustomerNameCombox->currentText());
    db.sql_fillComboBoxItem(filloneEngineerCombox,oneEngineerCombox);

    QString filloneStrengthGradeCombox = QString("select StrengthGrade from ProductionNotice where OutboundTime between '%1' and '%2' and Customer='%3' group by StrengthGrade")
            .arg(dateEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),dateEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),oneCustomerNameCombox->currentText());
    db.sql_fillComboBoxItem(filloneStrengthGradeCombox,oneStrengthGradeCombox);
}

void fahuojiagepiliangtiaozhengDlg::on_dateChange()
{
    disconnect(oneCustomerNameCombox,SIGNAL(editTextChanged(QString)),this,SLOT(on_oneCustomerNameCombox()));
    oneCustomerNameCombox->clear();
    db.sql_fillComboBoxItem(QString("SELECT Customer FROM ProductionNotice where OutboundTime between '%1' and '%2' group by Customer")
                            .arg(dateEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),dateEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss")),oneCustomerNameCombox);
    connect(oneCustomerNameCombox,SIGNAL(editTextChanged(QString)),this,SLOT(on_oneCustomerNameCombox()));
}


void fahuojiagepiliangtiaozhengDlg::on_twoFindBtn()
{
    QString kehumingcheng,gongchengmingcheng;

    if(twoCustomerCheckBox->checkState() == 2){
        kehumingcheng = QString(" and CustomerName='%1'").arg(twoCustomerComBox->currentText());
    }

    if(twoEngineerCheckBox->checkState() == 2){
        gongchengmingcheng = QString(" and ProjectName='%1'").arg(twoEngineerComBox->currentText());
    }

    QString searchSQL = QString("select CustomerName 客户名称,ProjectName 工程名称,product 产品,DateOfShipment1 发货日期起,\
                                DateOfShipment2 发货日期止,NewPrice 新价格,OriginalPrice 原价格,AdjustmentMan 调整人,\
                                AdjustmentTime 调整时间 from TimePeriodPriceAdjustmentRecord where AdjustmentTime \
                                between '%1' and '%2'%3%4;")
            .arg(twodateEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),twodateEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),
                 kehumingcheng,gongchengmingcheng);
    db.showview(searchSQL.toStdString().data(),twoview,&twomodel);
}

void fahuojiagepiliangtiaozhengDlg::on_twoCustomerComBox()
{
    twoEngineerComBox->clear();
    QString fillSQL2 = QString("select ProjectName from SalesContractCustomerEngineeringForm where CustomerName like '%%1%' group by ProjectName;").arg(twoCustomerComBox->currentText().section("顶",0,0));
    db.sql_fillComboBoxItem(fillSQL2.toStdString().data(),twoEngineerComBox);
}
