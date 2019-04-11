#include "cheliangzhuangtai.h"

extern mymysql db;
extern myTCPsocket *sockClient;

cheliangzhuangtai::cheliangzhuangtai(QWidget *parent) :
    QDialog(parent)
{
    this->setWindowTitle(tr("车辆下班"));
    this->setFixedSize(800,500);

    comBox11 = new QComboBox(this);
    comBox11->setFixedWidth(100);
    comBox11->setView(new QListView(this));
    comBox11->addItem(tr("主班"));
    comBox11->addItem(tr("副班"));
    comBox11->addItem(tr("休班"));
    comBox11->addItem(tr("无班"));
    const char *sql1 = "select VehicleStat from ConcreteVehicleInformation where Driver2='一组' group by VehicleStat;";
    comBox11->setCurrentText(db.sql_fetchrow_plus(sql1,0));

    comBox12 = new QComboBox(this);
    comBox12->setFixedWidth(100);
    comBox12->setView(new QListView(this));
    comBox12->addItem(tr("主班"));
    comBox12->addItem(tr("副班"));
    comBox12->addItem(tr("休班"));
    comBox12->addItem(tr("无班"));
    const char *sql2 = "select VehicleStat from ConcreteVehicleInformation where Driver2='二组' group by VehicleStat;";
    comBox12->setCurrentText(db.sql_fetchrow_plus(sql2,0));

    comBox13 = new QComboBox(this);
    comBox13->setFixedWidth(100);
    comBox13->setView(new QListView(this));
    comBox13->addItem(tr("主班"));
    comBox13->addItem(tr("副班"));
    comBox13->addItem(tr("休班"));
    comBox13->addItem(tr("无班"));
    const char *sql3 = "select VehicleStat from ConcreteVehicleInformation where Driver2='三组' group by VehicleStat;";
    comBox13->setCurrentText(db.sql_fetchrow_plus(sql3,0));

    comBox14 = new QComboBox(this);
    comBox14->setFixedWidth(100);
    comBox14->setView(new QListView(this));
    comBox14->addItem(tr("主班"));
    comBox14->addItem(tr("副班"));
    comBox14->addItem(tr("休班"));
    comBox14->addItem(tr("无班"));
    const char *sql4 = "select VehicleStat from ConcreteVehicleInformation where Driver2='四组' group by VehicleStat;";
    comBox14->setCurrentText(db.sql_fetchrow_plus(sql4,0));

    querenBtn2 = new QPushButton(tr("确认下班"),this);
    connect(querenBtn2,SIGNAL(clicked()),this,SLOT(on_querenxiabanBtn()));
    banciBtn = new QPushButton(tr("班次调整"),this);
    connect(banciBtn,SIGNAL(clicked()),this,SLOT(on_bancitiaozhengBtn()));

    QGridLayout *glayout1 = new QGridLayout;
    glayout1->setColumnStretch(0,1);
    glayout1->setColumnStretch(1,1);
    glayout1->setColumnStretch(2,1);
    glayout1->setColumnStretch(3,1);
    glayout1->setColumnStretch(4,1);
    glayout1->setColumnStretch(5,1);
    glayout1->setRowStretch(0,1);
    glayout1->setRowStretch(1,1);
    int num1 = 0;
    const char *SQL1 = "SELECT CheNo from inHouseVehicle A LEFT JOIN (SELECT LicensePlate,Driver2 FROM ConcreteVehicleInformation) B ON (A.CheNo = B.LicensePlate) WHERE B.Driver2='一组';";
    db.newCheckBox(SQL1,list1,&num1,this);
    for(int i = 0; i < num1; i++){
        glayout1->addWidget(list1[i],i / 6,i % 6);
    }

    QGridLayout *glayout2 = new QGridLayout;
    glayout2->setColumnStretch(0,1);
    glayout2->setColumnStretch(1,1);
    glayout2->setColumnStretch(2,1);
    glayout2->setColumnStretch(3,1);
    glayout2->setColumnStretch(4,1);
    glayout2->setColumnStretch(5,1);
    glayout2->setRowStretch(0,1);
    glayout2->setRowStretch(1,1);
    int num2 = 0;
    const char *SQL2 = "SELECT CheNo from inHouseVehicle A LEFT JOIN (SELECT LicensePlate,Driver2 FROM ConcreteVehicleInformation) B ON (A.CheNo = B.LicensePlate) WHERE B.Driver2='二组';";
    db.newCheckBox(SQL2,list2,&num2,this);
    for(int i = 0; i < num2; i++){
        glayout2->addWidget(list2[i],i / 6,i % 6);
    }

    QGridLayout *glayout3 = new QGridLayout;
    glayout3->setColumnStretch(0,1);
    glayout3->setColumnStretch(1,1);
    glayout3->setColumnStretch(2,1);
    glayout3->setColumnStretch(3,1);
    glayout3->setColumnStretch(4,1);
    glayout3->setColumnStretch(5,1);
    glayout3->setRowStretch(0,1);
    glayout3->setRowStretch(1,1);
    int num3 = 0;
    const char *SQL3 = "SELECT CheNo from inHouseVehicle A LEFT JOIN (SELECT LicensePlate,Driver2 FROM ConcreteVehicleInformation) B ON (A.CheNo = B.LicensePlate) WHERE B.Driver2='三组';";
    db.newCheckBox(SQL3,list3,&num3,this);
    for(int i = 0; i < num3; i++){
        glayout3->addWidget(list3[i],i / 6,i % 6);
    }

    QGridLayout *glayout4 = new QGridLayout;
    glayout4->setColumnStretch(0,1);
    glayout4->setColumnStretch(1,1);
    glayout4->setColumnStretch(2,1);
    glayout4->setColumnStretch(3,1);
    glayout4->setColumnStretch(4,1);
    glayout4->setColumnStretch(5,1);
    glayout4->setRowStretch(0,1);
    glayout4->setRowStretch(1,1);
    int num4 = 0;
    const char *SQL4 = "SELECT CheNo from inHouseVehicle A LEFT JOIN (SELECT LicensePlate,Driver2 FROM ConcreteVehicleInformation) B ON (A.CheNo = B.LicensePlate) WHERE B.Driver2='四组';";
    db.newCheckBox(SQL4,list4,&num4,this);
    for(int i = 0; i < num4; i++){
        glayout4->addWidget(list4[i],i / 6,i % 6);
    }


    QHBoxLayout *layout1 = new QHBoxLayout;
    layout1->addWidget(comBox11,1);
    layout1->addLayout(glayout1,2);

    QHBoxLayout *layout2 = new QHBoxLayout;
    layout2->addWidget(comBox12);
    layout2->addLayout(glayout2,2);

    QHBoxLayout *layout3 = new QHBoxLayout;
    layout3->addWidget(comBox13);
    layout3->addLayout(glayout3,2);

    QHBoxLayout *layout4 = new QHBoxLayout;
    layout4->addWidget(comBox14);
    layout4->addLayout(glayout4,2);

    groupBox1 = new QGroupBox(this);
    groupBox1->setTitle(tr("一组"));
    groupBox1->setLayout(layout1);
    groupBox2 = new QGroupBox(this);
    groupBox2->setTitle(tr("二组"));
    groupBox2->setLayout(layout2);
    groupBox3 = new QGroupBox(this);
    groupBox3->setTitle(tr("三组"));
    groupBox3->setLayout(layout3);
    groupBox4 = new QGroupBox(this);
    groupBox4->setTitle(tr("四组"));
    groupBox4->setLayout(layout4);

    QHBoxLayout *hlayout1 = new QHBoxLayout;
    hlayout1->addStretch(5);
    hlayout1->addWidget(banciBtn,1);
    hlayout1->addWidget(querenBtn2,1);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(groupBox1,1);
    vlayout->addWidget(groupBox2,1);
    vlayout->addWidget(groupBox3,1);
    vlayout->addWidget(groupBox4,1);
    vlayout->addLayout(hlayout1,1);
}

void cheliangzhuangtai::on_bancitiaozhengBtn()
{
    QString updateSQL1 = QString("update ConcreteVehicleInformation set VehicleStat='%1' where Driver2='一组'").arg(comBox11->currentText());
    QString updateSQL2 = QString("update ConcreteVehicleInformation set VehicleStat='%1' where Driver2='二组'").arg(comBox12->currentText());
    QString updateSQL3 = QString("update ConcreteVehicleInformation set VehicleStat='%1' where Driver2='三组'").arg(comBox13->currentText());
    QString updateSQL4 = QString("update ConcreteVehicleInformation set VehicleStat='%1' where Driver2='四组'").arg(comBox14->currentText());
    db.sql_exec(updateSQL1.toStdString().data());
    db.sql_exec(updateSQL2.toStdString().data());
    db.sql_exec(updateSQL3.toStdString().data());
    db.sql_exec(updateSQL4.toStdString().data());
    sockClient->send_Msg3();
    this->close();
}

void cheliangzhuangtai::on_querenxiabanBtn()
{
    for(int i = 0; i < list1.size(); i++){
        if(list1[i]->checkState() == 2){
            QString deleteSQL = QString("delete from inHouseVehicle where CheNo='%1';").arg(list1[i]->text());
            db.sql_exec(deleteSQL.toStdString().data());
        }
    }

    for(int i = 0; i < list2.size(); i++){
        if(list2[i]->checkState() == 2){
            QString deleteSQL = QString("delete from inHouseVehicle where CheNo='%1';").arg(list2[i]->text());
            db.sql_exec(deleteSQL.toStdString().data());
        }
    }

    for(int i = 0; i < list3.size(); i++){
        if(list3[i]->checkState() == 2){
            QString deleteSQL = QString("delete from inHouseVehicle where CheNo='%1';").arg(list3[i]->text());
            db.sql_exec(deleteSQL.toStdString().data());
        }
    }

    for(int i = 0; i < list4.size(); i++){
        if(list4[i]->checkState() == 2){
            QString deleteSQL = QString("delete from inHouseVehicle where CheNo='%1';").arg(list4[i]->text());
            db.sql_exec(deleteSQL.toStdString().data());
        }
    }

    sockClient->send_Msg3();

    this->close();
}
