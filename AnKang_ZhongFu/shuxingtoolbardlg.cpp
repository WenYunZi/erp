#include "shuxingtoolbardlg.h"

extern mymysql db;

shuxingtoolbarDlg::shuxingtoolbarDlg(QWidget *parent) :
    QDialog(parent)
{
    //this->setFixedSize(550,350);
    this->setWindowTitle(tr("属性选择"));
    this->shuxing.clear();

    layout = new QGridLayout(this);
    layout->setColumnStretch(0,1);
    layout->setColumnStretch(1,1);
    layout->setColumnStretch(2,1);
    layout->setColumnStretch(3,1);
    layout->setColumnStretch(4,1);
    layout->setRowStretch(0,1);
    layout->setRowStretch(1,1);
    layout->setRowStretch(2,1);
    layout->setRowStretch(3,1);
    layout->setRowStretch(4,1);
    layout->setRowStretch(5,1);
    layout->setRowStretch(6,1);
}

shuxingtoolbarDlg::~shuxingtoolbarDlg()
{

}

void shuxingtoolbarDlg::init_shuxingToolBar(QString ContractNumber,QString EngineerName,QString StartTime)
{
    int num = 0;
    shuxing.clear();
    QString SQL = QString("select attribute,\
                          CASE WHEN LOCATE('细石',attribute)>0 THEN 1 \
                                   WHEN LOCATE('P',attribute)>0 THEN 2 \
                                   WHEN LOCATE('W',attribute)>0 THEN 3 \
                                   WHEN LOCATE('F',attribute)>0 THEN 4 \
                                   WHEN LOCATE('SY-K',attribute)>0 THEN 5 \
                                   WHEN LOCATE('GB-A',attribute)>0 THEN 6 \
                                   WHEN LOCATE('膨胀',attribute)>0 THEN 7\
                                   WHEN LOCATE('补偿',attribute)>0 THEN 8 \
                                   WHEN LOCATE('收缩',attribute)>0 THEN 9 \
                                   WHEN LOCATE('早强',attribute)>0 THEN 10 \
                                   WHEN LOCATE('防冻',attribute)>0 THEN 11\
                                   ELSE 0\
                          END SHUNXU \
                          from SalesAttributeList where ContractNumber='%1' and EngineerName='%2' and StartTime=\
                          (select MAX(StartTime) from SalesAttributeList where  ContractNumber='%1' and EngineerName='%2' and StartTime<='%3') ORDER BY SHUNXU").arg(ContractNumber,EngineerName,StartTime);
    db.newCheckBox(SQL,list,&num,this);

    for(int i = 0; i < num; i++){
        connect(list[i],SIGNAL(stateChanged(int)),this,SLOT(chanpinshuxing()));
        layout->addWidget(list[i],i / 5,i % 5);
    }
}

void shuxingtoolbarDlg::chanpinshuxing()
{
    int count = list.count();
    shuxing.clear();
    for(int i = 0; i < count; i++){
        QCheckBox *checkBox = qobject_cast<QCheckBox*>(list[i]);
        if(checkBox->checkState() == 2){
            shuxing.append(list[i]->text());
            shuxing.append(" ");
        }
    }
}
