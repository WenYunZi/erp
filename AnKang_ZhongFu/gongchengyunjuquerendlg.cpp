#include "gongchengyunjuquerendlg.h"

extern mymysql db;
extern myTCPsocket *sockClient;

gongchengyunjuquerenDlg::gongchengyunjuquerenDlg(QWidget *parent) :
    QDialog(parent)
{
    SQL = "select ContractNumber 合同编号,CustomerName 客户名称,ProjectName 工程名称,Distance 运距 from SalesContractCustomerEngineeringForm;";

    QLabel *label1 = new QLabel(tr("合同编号"),this);
    label1->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label2 = new QLabel(tr("客户名称"),this);
    label2->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label3 = new QLabel(tr("工程名称"),this);
    label3->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label4 = new QLabel(tr("发货日期"),this);
    label4->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
    QLabel *label5 = new QLabel(tr("--"),this);
    label5->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
    QLabel *yunjuLabel = new QLabel(tr("运距"),this);
    yunjuLabel->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
    QLabel *yunfeiLabel = new QLabel(tr("运费"),this);
    yunfeiLabel->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
    QLabel *label6 = new QLabel(tr("注意：是往返距离"),this);
    label6->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
    label6->setStyleSheet("color:red");

    dateEdit1 = new QDateTimeEdit(this);
    dateEdit1->setDate(QDate::currentDate());
    dateEdit1->setTime(QTime::fromString("04:00:00","hh:mm:ss"));
    dateEdit1->setCalendarPopup(true);
    dateEdit2 = new QDateTimeEdit(this);
    dateEdit2->setDate(QDate::currentDate());
    dateEdit2->setTime(QTime::fromString("04:00:00","hh:mm:ss"));
    dateEdit2->setCalendarPopup(true);

    lineEdit1 = new QLineEdit(this);
    lineEdit1->setReadOnly(true);
    lineEdit2 = new QLineEdit(this);
    lineEdit2->setReadOnly(true);
    lineEdit3 = new QLineEdit(this);
    lineEdit3->setReadOnly(true);
    YunJuLineEdit = new QLineEdit(this);
    connect(YunJuLineEdit,SIGNAL(textChanged(QString)),this,SLOT(on_YunJuLineEdit()));
    YunFeiLineEdit = new QLineEdit(this);
    YunFeiLineEdit->setReadOnly(true);

    Btn = new QPushButton(tr("运距确认"),this);
    Btn->setFixedWidth(130);
    connect(Btn,SIGNAL(clicked()),this,SLOT(on_yunjuquerenBtn()));

    chaxunBtn = new QPushButton(tr("查询"),this);
    chaxunBtn->setFixedWidth(130);
    connect(chaxunBtn,SIGNAL(clicked()),this,SLOT(on_chaxunBtn()));

    checkBox = new QCheckBox(tr("修改之前的发货信息"),this);

    checkBox1 = new QCheckBox(tr("工程名称"),this);

    comBox = new myComboBox(this);
    const char *fillSQL = "select ProjectName from SalesContractCustomerEngineeringForm group by ProjectName;";
    db.sql_fillComboBoxItem(fillSQL,comBox);

    view1 = new QTableView(this);
    db.showview(SQL,view1,&model1);
    connect(view1,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick()));
    view1->setColumnWidth(1,300);
    view1->setColumnWidth(2,300);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label1,0,0);
    layout->addWidget(lineEdit1,0,1,1,3);
    layout->addWidget(label2,1,0);
    layout->addWidget(lineEdit2,1,1,1,3);
    layout->addWidget(label3,2,0);
    layout->addWidget(lineEdit3,2,1,1,3);
    layout->addWidget(yunjuLabel,3,0);
    layout->addWidget(YunJuLineEdit,3,1,1,3);
    layout->addWidget(yunfeiLabel,4,0);
    layout->addWidget(YunFeiLineEdit,4,1,1,3);
    layout->setColumnStretch(0,0);
    layout->setColumnStretch(1,1);
    layout->setColumnStretch(2,0);
    layout->setColumnStretch(3,1);
    layout->setColumnStretch(4,1);
    layout->setColumnStretch(5,1);
    layout->setColumnStretch(6,1);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(checkBox,0);
    hlayout->addWidget(label4,0);
    hlayout->addWidget(dateEdit1,1);
    hlayout->addWidget(label5,0);
    hlayout->addWidget(dateEdit2,1);
    hlayout->addWidget(Btn,1,Qt::AlignLeft);
    hlayout->addWidget(label6,0,Qt::AlignLeft);
    hlayout->addStretch(4);

    QHBoxLayout *hlayout1 = new QHBoxLayout;
    hlayout1->addWidget(checkBox1,0);
    hlayout1->addWidget(comBox,1);
    hlayout1->addWidget(chaxunBtn,1);
    hlayout1->addStretch(3);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(layout);
    vlayout->addLayout(hlayout);
    vlayout->addSpacing(8);
    vlayout->addLayout(hlayout1);
    vlayout->addWidget(view1);
}

void gongchengyunjuquerenDlg::refresh()
{
    //db.showview(SQL,view1,&model1);
}

void gongchengyunjuquerenDlg::keyPressEvent(QKeyEvent *event)
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

void gongchengyunjuquerenDlg::ShowSupplyclick()
{
    int row = view1->currentIndex().row();
    lineEdit1->setText(model1->item(row,0)->text());
    lineEdit2->setText(model1->item(row,1)->text());
    lineEdit3->setText(model1->item(row,2)->text());
    YunJuLineEdit->setText(model1->item(row,3)->text());
    QString searchFreightPrice = QString("select Freight from ConcreteCarFreightSet where cast(MinimumMileage as SIGNED INTEGER)<='%1' and cast(MaximumMileage as SIGNED INTEGER)>='%1';").arg(YunJuLineEdit->text());
    YunFeiLineEdit->setText(db.sql_fetchrow_plus(searchFreightPrice.toStdString().data(),0));
}

void gongchengyunjuquerenDlg::on_YunJuLineEdit()
{
    QString searchFreightPrice = QString("select Freight from ConcreteCarFreightSet where cast(MinimumMileage as SIGNED INTEGER)<='%1' and cast(MaximumMileage as SIGNED INTEGER)>='%1';").arg(YunJuLineEdit->text());
    YunFeiLineEdit->setText(db.sql_fetchrow_plus(searchFreightPrice.toStdString().data(),0));
}

void gongchengyunjuquerenDlg::on_yunjuquerenBtn()
{
    if(lineEdit1->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择要修改的工程运距"),0,0,0);
        return;
    }
    db.sql_exec("begin");//事务开始

    //1.改工程档案表中的运距
    QString updateYunJu = QString("update SalesContractCustomerEngineeringForm set Distance='%1' where CustomerName like '%%2%' and ProjectName='%3';")
                    .arg(YunJuLineEdit->text(),lineEdit2->text().section("顶",0,0),lineEdit3->text());
    int res = db.sql_exec(updateYunJu.toStdString().data());
    if(res == -1){
        db.sql_exec("rollback");
        return;
    }
    //2.改生产任务单中的运距
    QString updateTask = QString("update ProductionTaskList set Distance='%1' where Customer like'%%2%' and Engineering='%3';").arg(YunJuLineEdit->text(),lineEdit2->text().section("顶",0,0),lineEdit3->text());
    res = db.sql_exec(updateTask.toStdString().data());
    if(res == -1){
        db.sql_exec("rollback");
        return;
    }
    if(checkBox->checkState() == 2){//修改之前的发货信息
        //3.改单车任务中的运距和运费
        QString searchFreightPrice = QString("select Freight from ConcreteCarFreightSet where cast(MinimumMileage as SIGNED INTEGER)<='%1' and cast(MaximumMileage as SIGNED INTEGER)>='%1';").arg(YunJuLineEdit->text());
        QString FreightPrice = db.sql_fetchrow_plus(searchFreightPrice.toStdString().data(),0);
        QString updateSQL = QString("update ProductionNotice set Mileage='%1',FreightPrice='%2' where Customer like '%%3%' and Engineering='%4' and OutboundTime between '%5' and '%6';")
                .arg(YunJuLineEdit->text(),FreightPrice,lineEdit2->text().section("顶",0,0),lineEdit3->text(),dateEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),dateEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
        res = db.sql_exec(updateSQL.toStdString().data());
        if(res == -1){
            db.sql_exec("rollback");
            return;
        }
    }
    db.sql_exec("commit");

    on_chaxunBtn();
    lineEdit1->clear();
    lineEdit2->clear();
    lineEdit3->clear();
    YunJuLineEdit->clear();
    YunFeiLineEdit->clear();
    QMessageBox::information(this,tr("提示信息"),tr("运距确认成功"),0,0,0);
}

void gongchengyunjuquerenDlg::on_chaxunBtn()
{
    QString gongcheng;
    if(checkBox1->checkState() == 2){
        gongcheng = QString(" where ProjectName='%1';").arg(comBox->currentText());
    }

    QString searchSQL = QString("select ContractNumber 合同编号,CustomerName 客户名称,ProjectName 工程名称,Distance 运距 from \
                                SalesContractCustomerEngineeringForm %1;").arg(gongcheng);
    db.showview(searchSQL.toStdString().data(),view1,&model1);
}
