#include "xiabanjilu.h"

extern mymysql db;

xiabanjilu::xiabanjilu(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowTitle(tr("下班记录查询"));
    this->setFixedSize(700,500);

    SQL = "SELECT cheNo 车牌号,cheTime 打卡时间,xiabanTime 下班时间,mark 备注 from cheliangxiabanRecord order by xiabanTime DESC limit 100;";

    QLabel *label2 = new QLabel(tr("下班时间"));
    label2->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label3 = new QLabel(tr("-"));
    label3->setAlignment(Qt::AlignVCenter|Qt::AlignCenter);

    checkBox = new QCheckBox(tr("车牌号"),this);

    dateTimeEdit1 = new QDateTimeEdit(QDateTime::currentDateTime(),this);
    dateTimeEdit1->setCalendarPopup(true);
    dateTimeEdit1->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
    dateTimeEdit2 = new QDateTimeEdit(QDateTime::currentDateTime(),this);
    dateTimeEdit2->setCalendarPopup(true);
    dateTimeEdit2->setDisplayFormat("yyyy-MM-dd hh:mm:ss");

    cheNoCombox = new QComboBox(this);
    cheNoCombox->setEditable(true);
    const char *fillSQL = "select LicensePlate from ConcreteVehicleInformation;";
    db.sql_fillComboBoxItem(fillSQL,cheNoCombox);

    chaxunBtn = new QPushButton(tr("查询"),this);
    connect(chaxunBtn,SIGNAL(clicked()),this,SLOT(on_chaxunBtn()));

    view = new QTableView(this);
    db.showview(SQL,view,&model);
    view->setColumnWidth(1,140);
    view->setColumnWidth(2,140);
    view->setColumnWidth(3,250);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(checkBox,0);
    hlayout->addWidget(cheNoCombox,1);
    hlayout->addWidget(label2,0);
    hlayout->addWidget(dateTimeEdit1,1);
    hlayout->addWidget(label3,0);
    hlayout->addWidget(dateTimeEdit2,1);
    hlayout->addWidget(chaxunBtn,1);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(view);


}

void xiabanjilu::on_chaxunBtn()
{
    QString cheNo;
    if(checkBox->checkState() == 2){
        cheNo = QString(" and cheNo='%1'").arg(cheNoCombox->currentText());
    }

    QString searchSQL = QString("SELECT cheNo 车牌号,cheTime 打卡时间,xiabanTime 下班时间,mark 备注 from cheliangxiabanRecord where xiabanTime \
                                between '%1' and '%2' %3;")
            .arg(dateTimeEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),dateTimeEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),cheNo);
    db.showview(searchSQL.toStdString().data(),view,&model);
}
