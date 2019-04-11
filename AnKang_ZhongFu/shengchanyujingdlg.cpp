#include "shengchanyujingdlg.h"

extern mymysql db;
extern myTCPsocket *sockClient;

shengchanyujingDlg::shengchanyujingDlg(QWidget *parent) :
    QDialog(parent)
{
    SQL = "SELECT CustomerName 客户名称,ProjectName 工程名称,WarningState 预警状态,Salesman 业务员,ContractNumber 合同编号 FROM SalesContractManagement \
           union SELECT CustomerName 客户名称,ProjectName 工程名称,WarningState 预警状态,Salesman 业务员,OrderRecordNumber 合同编号 FROM CashContractManagement;";

    QLabel *label1 = new QLabel(tr("客户名称"),this);
    label1->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label2 = new QLabel(tr("预警状态"),this);
    label2->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label3 = new QLabel(tr("工程名称"),this);
    label3->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    comBox1 = new QComboBox(this);
    const char *fillSQL1 = "select CustomerName from CustomerFiles;";
    db.sql_fillComboBoxItem(fillSQL1,comBox1);
    connect(comBox1,SIGNAL(currentIndexChanged(int)),this,SLOT(comBox1Correspond()));

    comBox2 = new QComboBox(this);

    comBox3 = new QComboBox(this);
    comBox3->setView(new QListView(this));
    comBox3->addItem(tr(""));
    comBox3->addItem(tr("停工"));
    comBox3->addItem(tr("预警"));
    comBox3->addItem(tr("正常"));

    Btn1 = new QPushButton(tr("确认"),this);
    connect(Btn1,SIGNAL(clicked()),this,SLOT(on_querenBtn()));

    view = new QTableView(this);
    db.showview(SQL,view,&model);
    connect(view,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick()));
    view->setColumnWidth(0,300);
    view->setColumnWidth(1,300);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label1,0,0);
    layout->addWidget(comBox1,0,1);
    layout->addWidget(label2,0,2);
    layout->addWidget(comBox3,0,3);
    layout->addWidget(Btn1,0,4,2,1,Qt::AlignVCenter);
    layout->addWidget(label3,1,0);
    layout->addWidget(comBox2,1,1);
    layout->setColumnStretch(0,0);
    layout->setColumnStretch(1,2);
    layout->setColumnStretch(2,0);
    layout->setColumnStretch(3,1);
    layout->setColumnStretch(4,1);
    layout->setColumnStretch(5,1);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(layout);
    vlayout->addWidget(view);
}

void shengchanyujingDlg::refresh()
{
    db.showview(SQL,view,&model);
}

void shengchanyujingDlg::keyPressEvent(QKeyEvent *event)
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

void shengchanyujingDlg::comBox1Correspond()
{
    comBox2->clear();
    QString fillSQL2 = QString("select ProjectName from SalesContractManagement where CustomerName='%1' group by ProjectName union select ProjectName from CashContractManagement where CustomerName='%1' group by ProjectName;").arg(comBox1->currentText());
    db.sql_fillComboBoxItem(fillSQL2.toStdString().data(),comBox2);
}

void shengchanyujingDlg::on_querenBtn()
{
    int res = 0;
    if(ContractNumber.contains("xs")){
        QString updateSQL = QString("update SalesContractManagement set WarningState='%1' where ContractNumber='%2';")
                .arg(comBox3->currentText(),ContractNumber);
        res = db.sql_exec(updateSQL.toStdString().data());
    }else if(ContractNumber.contains("xj")){
        QString updateSQL = QString("update CashContractManagement set WarningState='%1' where OrderRecordNumber='%2';")
                .arg(comBox3->currentText(),ContractNumber);
        res = db.sql_exec(updateSQL.toStdString().data());
    }

    if(res == 0){
        comBox1->setCurrentIndex(0);
        comBox2->setCurrentIndex(0);
        comBox3->setCurrentIndex(0);
        sockClient->send_Msg3();
        QMessageBox::information(this,tr("提示信息"),tr("确认成功"),0,0,0);
    }
}

void shengchanyujingDlg::ShowSupplyclick()
{
    int row = view->currentIndex().row();
    ContractNumber.clear();
    ContractNumber = model->item(row,4)->text();
    comBox1->setCurrentText(model->item(row,0)->text());
    comBox2->setCurrentText(model->item(row,1)->text());
    comBox3->setCurrentText(model->item(row,2)->text());
}
