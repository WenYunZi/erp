#include "hetongzhixingqingkuangdlg.h"

extern mymysql db;

hetongzhixingqingkuangDlg::hetongzhixingqingkuangDlg(QWidget *parent) :
    QDialog(parent)
{
    SQL = "SELECT A.ContractNumber 合同编号,Customer 客户名称,Engineering 工程名称,WhetherEffective 合同状态,sum(ReceiptVolume) 发货方量 FROM ProductionNotice A LEFT JOIN \
            SalesContractManagement B ON (A.ContractNumber=B.ContractNumber) WHERE Flag='0' GROUP BY A.ContractNumber,Engineering";

    QLabel *label1 = new QLabel(tr("客户名称"),this);
    label1->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    EngineerNameCheckBox = new QCheckBox(tr("工程名称"),this);

    comBox1 = new myComboBox(this);
    db.sql_fillComboBoxItem("SELECT CustomerName FROM CustomerFiles",comBox1);
    connect(comBox1,SIGNAL(editTextChanged(QString)),this,SLOT(comBox1Correspond()));

    comBox2 = new QComboBox(this);

    Btn1 = new QPushButton(tr("筛选"),this);
    Btn1->setFixedWidth(120);
    connect(Btn1,SIGNAL(clicked()),this,SLOT(on_shaixuanBtn()));
    Btn2 = new QPushButton(tr("全部"),this);
    Btn2->setFixedWidth(120);
    connect(Btn2,SIGNAL(clicked()),this,SLOT(on_quanbuBtn()));

    view = new QTableView(this);
    db.showview(SQL,view,&model);
    view->setColumnWidth(1,300);
    view->setColumnWidth(2,320);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(label1,0);
    hlayout->addWidget(comBox1,2);
    hlayout->addWidget(EngineerNameCheckBox,0);
    hlayout->addWidget(comBox2,3);
    hlayout->addWidget(Btn1,1);
    hlayout->addWidget(Btn2,1);
    hlayout->addStretch(5);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(view);
}

void hetongzhixingqingkuangDlg::refresh()
{

}

void hetongzhixingqingkuangDlg::keyPressEvent(QKeyEvent *event)
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

void hetongzhixingqingkuangDlg::on_shaixuanBtn()
{
    QString Engineering;
    if(EngineerNameCheckBox->checkState() == 2){
        Engineering = QString(" AND A.Engineering='%1'").arg(comBox2->currentText());
    }
    QString searchSQL = QString("SELECT A.ContractNumber 合同编号,Customer 客户名称,Engineering 工程名称,WhetherEffective 合同状态,sum(ReceiptVolume) 发货方量 FROM ProductionNotice A LEFT JOIN \
                                SalesContractManagement B ON (A.ContractNumber=B.ContractNumber) WHERE Flag='0' and A.Customer='%1' %2 GROUP BY A.ContractNumber,Engineering")
                        .arg(comBox1->currentText(),Engineering);
    db.showview(searchSQL.toStdString().data(),view,&model);
}

void hetongzhixingqingkuangDlg::on_quanbuBtn()
{
    db.showview(SQL,view,&model);
}

void hetongzhixingqingkuangDlg::comBox1Correspond()
{
    comBox2->clear();
    QString fillSQL2 = QString("select Engineering from ProductionNotice where Customer='%1' group by Engineering").arg(comBox1->currentText());
    db.sql_fillComboBoxItem(fillSQL2,comBox2);
}
