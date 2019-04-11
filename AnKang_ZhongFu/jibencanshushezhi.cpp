#include "jibencanshushezhi.h"
#include <QGroupBox>
#include <QMessageBox>

extern pubfunc pub;
extern mymysql db;
extern QString userName;
extern QString PRODUCTUNITNO;

jibencanshushezhi::jibencanshushezhi(QWidget *parent) :
    QDialog(parent)
{
    QLabel *UnitNumlabel = new QLabel(tr("机组编号"),this);
    QLabel *PlantNamelabel = new QLabel(tr("厂地名称"),this);
    QLabel *UnitTypelabel = new QLabel(tr("机组型号"),this);

    QLabel *MenJin1Label = new QLabel(tr("门禁IP"),this);

    QLabel *zhuYiLabel = new QLabel(tr("注意：机组参数改动前请确保机组接口关闭"),this);
    zhuYiLabel->setStyleSheet("color:red");
    zhuYiLabel->setAlignment(Qt::AlignLeft);

    MenJin1lineEdit = new QLineEdit(pub.read_accessControl_ip1(),this);

    WhetherConnectMenjin = new QCheckBox("是否连接到门禁控制卡",this);
    if(pub.read_connect_menjin() == "true"){
        WhetherConnectMenjin->setCheckState(Qt::Checked);
    }
    else if(pub.read_connect_menjin() == "false"){
        WhetherConnectMenjin->setCheckState(Qt::Unchecked);
    }

    qishiID1LineEdit = new QLineEdit(this);
    qishiID2LineEdit = new QLineEdit(this);
    qishiID3LineEdit = new QLineEdit(this);
    qishiID4LineEdit = new QLineEdit(this);

    UnitNumcomBox = new QComboBox(this);
    UnitNumcomBox->setView(new QListView());
    UnitNumcomBox->addItem("");
    UnitNumcomBox->addItem("1");
    UnitNumcomBox->addItem("2");
    UnitNumcomBox->addItem("3");
    UnitNumcomBox->addItem("4");
    UnitNumcomBox->setCurrentText(PRODUCTUNITNO);

    PlantNamecomBox = new QComboBox(this);
    const char *fillSQL = "select PlantName from FactorySetting;";
    db.sql_fillComboBoxItem(fillSQL,PlantNamecomBox);
    PlantNamecomBox->setCurrentText(pub.readPlantName());

    UnitTypecomBox = new QComboBox(this);
    UnitTypecomBox->setView(new QListView());
    UnitTypecomBox->addItem("");
    UnitTypecomBox->addItem("XinXing");
    UnitTypecomBox->addItem("SANY");
    UnitTypecomBox->addItem("FeiMi");
    UnitTypecomBox->addItem("SANY");
    UnitTypecomBox->addItem("ZOOMLION");
    UnitTypecomBox->addItem("BS");
    UnitTypecomBox->setCurrentText(pub.read_unitType());

    genggaiBtn = new QPushButton(tr("更改"),this);
    genggaiBtn->setFixedWidth(100);
    connect(genggaiBtn,SIGNAL(clicked()),this,SLOT(on_updatejibencanshu()));

    chazhao1Btn = new QPushButton(tr("1#机组ID"),this);
    chazhao1Btn->setFixedWidth(120);
    connect(chazhao1Btn,SIGNAL(clicked()),this,SLOT(on_chazhao1Btn()));
    chazhao2Btn = new QPushButton(tr("2#机组ID"),this);
    chazhao2Btn->setFixedWidth(120);
    connect(chazhao2Btn,SIGNAL(clicked()),this,SLOT(on_chazhao2Btn()));
    chazhao3Btn = new QPushButton(tr("3#机组ID"),this);
    chazhao3Btn->setFixedWidth(120);
    connect(chazhao3Btn,SIGNAL(clicked()),this,SLOT(on_chazhao3Btn()));
    chazhao4Btn = new QPushButton(tr("4#机组ID"),this);
    chazhao4Btn->setFixedWidth(120);
    connect(chazhao4Btn,SIGNAL(clicked()),this,SLOT(on_chazhao4Btn()));

    shezhi1Btn = new QPushButton(tr("设置1"),this);
    shezhi1Btn->setFixedWidth(80);
    connect(shezhi1Btn,SIGNAL(clicked()),this,SLOT(on_shezhi1Btn()));
    shezhi2Btn = new QPushButton(tr("设置2"),this);
    shezhi2Btn->setFixedWidth(80);
    connect(shezhi2Btn,SIGNAL(clicked()),this,SLOT(on_shezhi2Btn()));
    shezhi3Btn = new QPushButton(tr("设置3"),this);
    shezhi3Btn->setFixedWidth(80);
    connect(shezhi3Btn,SIGNAL(clicked()),this,SLOT(on_shezhi3Btn()));
    shezhi4Btn = new QPushButton(tr("设置4"),this);
    shezhi4Btn->setFixedWidth(80);
    connect(shezhi4Btn,SIGNAL(clicked()),this,SLOT(on_shezhi4Btn()));

    QGridLayout *layout1 = new QGridLayout;
    layout1->addWidget(UnitNumlabel,0,0);
    layout1->addWidget(UnitNumcomBox,0,1);
    layout1->addWidget(PlantNamelabel,1,0);
    layout1->addWidget(PlantNamecomBox,1,1);
    layout1->addWidget(UnitTypelabel,2,0);
    layout1->addWidget(UnitTypecomBox,2,1);
    layout1->setColumnStretch(0,0);
    layout1->setColumnStretch(1,1);

    QGridLayout *layout2 = new QGridLayout;
    layout2->addWidget(MenJin1Label,0,0);
    layout2->addWidget(MenJin1lineEdit,0,1);
    layout2->addWidget(WhetherConnectMenjin,1,0,1,2,Qt::AlignHCenter);
    layout2->setColumnStretch(0,0);
    layout2->setColumnStretch(1,1);

    QGridLayout *layout3 = new QGridLayout;
    layout3->addWidget(chazhao1Btn,0,0,1,1);
    layout3->addWidget(qishiID1LineEdit,0,1,1,1);
    layout3->addWidget(shezhi1Btn,0,2,1,1);
    layout3->addWidget(chazhao2Btn,1,0,1,1);
    layout3->addWidget(qishiID2LineEdit,1,1,1,1);
    layout3->addWidget(shezhi2Btn,1,2,1,1);
    layout3->addWidget(chazhao3Btn,2,0,1,1);
    layout3->addWidget(qishiID3LineEdit,2,1,1,1);
    layout3->addWidget(shezhi3Btn,2,2,1,1);
    layout3->addWidget(chazhao4Btn,3,0,1,1);
    layout3->addWidget(qishiID4LineEdit,3,1,1,1);
    layout3->addWidget(shezhi4Btn,3,2,1,1);

    layout3->setColumnStretch(0,0);
    layout3->setColumnStretch(1,1);
    layout3->setColumnStretch(2,0);

    QGroupBox *UnitSetgroupBox = new QGroupBox(this);
    UnitSetgroupBox->setFixedSize(240,200);
    UnitSetgroupBox->setTitle(tr("机组参数设置"));
    UnitSetgroupBox->setLayout(layout1);

    QGroupBox *MenjinSetgroupBox = new QGroupBox(this);
    MenjinSetgroupBox->setFixedSize(240,200);
    MenjinSetgroupBox->setTitle(tr("门禁参数设置"));
    MenjinSetgroupBox->setLayout(layout2);

    QGroupBox *UnitIDSetgroupBox = new QGroupBox(this);
    UnitIDSetgroupBox->setFixedSize(340,200);
    UnitIDSetgroupBox->setTitle(tr("机组数据传输起始ID"));
    UnitIDSetgroupBox->setLayout(layout3);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(UnitSetgroupBox,1);
    hlayout->addWidget(UnitIDSetgroupBox,1);
    hlayout->addWidget(MenjinSetgroupBox,1);
    hlayout->addStretch(2);

    QHBoxLayout *hlayout1 = new QHBoxLayout;
    hlayout1->addStretch(20);
    hlayout1->addWidget(genggaiBtn,1);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(hlayout,1);
    vlayout->addWidget(zhuYiLabel);
    vlayout->addStretch(10);
    vlayout->addLayout(hlayout1,1);
}

void jibencanshushezhi::on_updatejibencanshu()
{
    if(userName != "admin"){
        QMessageBox::information(this,tr("提示信息"),tr("admin用户具有该权限，请使用admin用户名进行登录修改"),0,0,0);
        return;
    }

    pub.save_JizuBianhao(UnitNumcomBox->currentText());
    pub.save_PlantName(PlantNamecomBox->currentText());
    pub.save_accessControl_ip1(MenJin1lineEdit->text());
    if(WhetherConnectMenjin->checkState() == 2){
        pub.write_connect_menjin("true");
    }
    else if(WhetherConnectMenjin->checkState() == 0){
        pub.write_connect_menjin("false");
    }
    pub.write_unitType(UnitTypecomBox->currentText());

    QMessageBox::information(this,tr("提示信息"),tr("更改成功,重新运行软件使新参数生效"),0,0,0);
}

void jibencanshushezhi::on_chazhao1Btn()
{
    QString searchSQL = QString("select CURDATE from HISTDATA where unit='1#机组' order by CURDATE desc limit 1");
    qishiID1LineEdit->setText(db.sql_fetchrow_plus(searchSQL.toStdString().data(),0));
}

void jibencanshushezhi::on_chazhao2Btn()
{
    QString searchSQL = QString("select CURDATE from HISTDATA where unit='2#机组' order by CURDATE desc limit 1");
    qishiID2LineEdit->setText(db.sql_fetchrow_plus(searchSQL.toStdString().data(),0));
}

void jibencanshushezhi::on_chazhao3Btn()
{
    QString searchSQL = QString("select CURDATE from HISTDATA where unit='3#机组' order by CURDATE desc limit 1");
    qishiID3LineEdit->setText(db.sql_fetchrow_plus(searchSQL.toStdString().data(),0));
}

void jibencanshushezhi::on_chazhao4Btn()
{
    QString searchSQL = QString("select CURDATE from HISTDATA where unit='4#机组' order by CURDATE desc limit 1");
    qishiID4LineEdit->setText(db.sql_fetchrow_plus(searchSQL.toStdString().data(),0));
}

void jibencanshushezhi::on_shezhi1Btn()
{
    if(userName != "admin"){
        QMessageBox::information(this,tr("提示信息"),tr("admin用户具有该权限，请使用admin用户名进行登录修改"),0,0,0);
        return;
    }

    QString updateSQL = QString("update config set value='%1' where tablename='HISTDATA' and `key`='1#机组'").arg(qishiID1LineEdit->text());
    int res = db.sql_exec(updateSQL.toStdString().data());
    if(res == 0){
        QMessageBox::information(this,tr("提示信息"),tr("1#设置成功"),0,0,0);
    }
}

void jibencanshushezhi::on_shezhi2Btn()
{
    if(userName != "admin"){
        QMessageBox::information(this,tr("提示信息"),tr("admin用户具有该权限，请使用admin用户名进行登录修改"),0,0,0);
        return;
    }

    QString updateSQL = QString("update config set value='%1' where tablename='HISTDATA' and `key`='2#机组'").arg(qishiID2LineEdit->text());
    int res = db.sql_exec(updateSQL.toStdString().data());
    if(res == 0){
        QMessageBox::information(this,tr("提示信息"),tr("2#设置成功"),0,0,0);
    }
}

void jibencanshushezhi::on_shezhi3Btn()
{
    if(userName != "admin"){
        QMessageBox::information(this,tr("提示信息"),tr("admin用户具有该权限，请使用admin用户名进行登录修改"),0,0,0);
        return;
    }

    QString updateSQL = QString("update config set value='%1' where tablename='HISTDATA' and `key`='3#机组'").arg(qishiID3LineEdit->text());
    int res = db.sql_exec(updateSQL.toStdString().data());
    if(res == 0){
        QMessageBox::information(this,tr("提示信息"),tr("3#设置成功"),0,0,0);
    }
}

void jibencanshushezhi::on_shezhi4Btn()
{
    if(userName != "admin"){
        QMessageBox::information(this,tr("提示信息"),tr("admin用户具有该权限，请使用admin用户名进行登录修改"),0,0,0);
        return;
    }

    QString updateSQL = QString("update config set value='%1' where tablename='HISTDATA' and `key`='4#机组'").arg(qishiID4LineEdit->text());
    int res = db.sql_exec(updateSQL.toStdString().data());
    if(res == 0){
        QMessageBox::information(this,tr("提示信息"),tr("4#设置成功"),0,0,0);
    }
}
