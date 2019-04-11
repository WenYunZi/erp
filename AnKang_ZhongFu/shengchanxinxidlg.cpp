#include "shengchanxinxidlg.h"
extern mymysql db;

shengchanxinxiDlg::shengchanxinxiDlg(QString tasklist,QWidget *parent) :
    QDialog(parent)
{
    this->setWindowTitle("派车信息");
    this->resize(950,400);
//    QDesktopWidget *desktop = QApplication::desktop();
//    this->setObjectName(tr("shengchanxinxiDlg"));
//    this->setStyleSheet("QDialog[objectName=\"shengchanxinxiDlg\"]{border: 3px solid rgb(6,17,153);}");
//    this->setWindowFlags(Qt::Popup);
//    this->setFixedSize(500,300);
//    this->move(desktop->width()/2 - this->width()/2,desktop->height()/2 - this->height()/2);

    SQL = QString("select RecordNumber 发货序号,DeliveryVehicle 送货车辆,Unit 机组,ReceiptVolume 发货方量,CumulativeNumber 累计车次,CumulativeVolume 累计方量,OutboundTime 出站时间,SettlementTime 回厂时间 from ProductionNotice where OutboundTime > '%1' and TaskList = '%2'")
            .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd 00:00:00"),tasklist);
    qDebug()<<SQL;

    view = new QTableView(this);
    db.showview(SQL,view,&model);
    view->setColumnWidth(6,130);
    view->setColumnWidth(7,130);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(view);
}

