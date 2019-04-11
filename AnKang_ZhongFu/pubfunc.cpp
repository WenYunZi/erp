#include "pubfunc.h"
#include <QTextCodec>

extern mymysql db;

pubfunc::pubfunc()
{
    configIniRead = new QSettings("config.ini",QSettings::IniFormat);
    configIniWrite = new QSettings("config.ini",QSettings::IniFormat);
}

QString pubfunc::newListNo()
{
    const char *searchSQL = "select value,data from setting where `key`='PurchaseReceiptNo';";
    QString data = db.sql_fetchrow_plus(searchSQL,1);
    if(data != QDate::currentDate().toString("yyyy-MM-dd")){
        QString updateSQL = QString("update setting set value='1',data='%1' where `key`='PurchaseReceiptNo';")
                .arg(QDate::currentDate().toString("yyyy-MM-dd"));
        db.sql_exec(updateSQL.toStdString().data());
    }

    int num = db.sql_fetchrow_plus(searchSQL,0).toInt();
    QString str = QString("rk")+QDate::currentDate().toString("yyyyMMdd")+QString("").sprintf("%03d",num);
    db.sql_exec("update setting set value=value+'1' where `key`='PurchaseReceiptNo';");
    return str;
}

QString pubfunc::newshengliaoNo()
{
    const char *searchSQL = "select value,data from setting where `key`='shengliaoNo';";
    QString data = db.sql_fetchrow_plus(searchSQL,1);
    if(data != QDate::currentDate().toString("yyyy-MM-dd")){
        QString updateSQL = QString("update setting set value='1',data='%1' where `key`='shengliaoNo';")
                .arg(QDate::currentDate().toString("yyyy-MM-dd"));
        db.sql_exec(updateSQL);
    }

    int num = db.sql_fetchrow_plus(searchSQL,0).toInt();
    QString str = QString("sl")+QDate::currentDate().toString("yyyyMMdd")+QString("").sprintf("%03d",num);
    db.sql_exec("update setting set value=value+'1' where `key`='shengliaoNo';");
    return str;
}

QString pubfunc::newfahuoNo()
{
    const char *searchSQL = "select value,data from setting where `key`='fahuoNo';";
    QString data = db.sql_fetchrow_plus(searchSQL,1);
    if(data != QDate::currentDate().toString("yyyy-MM-dd")){
        QString updateSQL = QString("update setting set value='1',data='%1' where `key`='fahuoNo';")
                .arg(QDate::currentDate().toString("yyyy-MM-dd"));
        db.sql_exec(updateSQL);
    }

    int num = db.sql_fetchrow_plus(searchSQL,0).toInt();
    QString str = QString("fh")+QDate::currentDate().toString("yyyyMMdd")+QString("").sprintf("%03d",num);
    db.sql_exec("update setting set value=value+'1' where `key`='fahuoNo';");
    return str;
}

QString pubfunc::newRenwudanNo()
{
    const char *searchSQL = "select value,data from setting where `key`='renwudanNo';";
    QString data = db.sql_fetchrow_plus(searchSQL,1);
    if(data != QDate::currentDate().toString("yyyy-MM-dd")){
        QString updateSQL = QString("update setting set value='1',data='%1' where `key`='renwudanNo';")
                .arg(QDate::currentDate().toString("yyyy-MM-dd"));
        db.sql_exec(updateSQL);
    }

    int num = db.sql_fetchrow_plus(searchSQL,0).toInt();
    QString str = QDate::currentDate().toString("yyyyMMdd")+QString("").sprintf("%03d",num);
    db.sql_exec("update setting set value=value+'1' where `key`='renwudanNo';");
    return str;
}

QString pubfunc::newTongzhidanNo()
{
    const char *searchSQL = "select value,data from setting where `key`='tongzhidanNo';";
    QString data = db.sql_fetchrow_plus(searchSQL,1);
    if(data != QDate::currentDate().toString("yyyy-MM-dd")){
        QString updateSQL = QString("update setting set value='1',data='%1' where `key`='tongzhidanNo';")
                .arg(QDate::currentDate().toString("yyyy-MM-dd"));
        db.sql_exec(updateSQL);
    }

    int num = db.sql_fetchrow_plus(searchSQL,0).toInt();
    QString str = QString("tzd")+QDate::currentDate().toString("yyyyMMdd")+QString("").sprintf("%03d",num);
    db.sql_exec("update setting set value=value+'1' where `key`='tongzhidanNo';");
    return str;
}


QString pubfunc::readJizuBianhao()
{
    return configIniRead->value("JizuNo/Num").toString();
}

void pubfunc::save_JizuBianhao(QString num)
{
    configIniWrite->setValue("JizuNo/num",num);
}


void pubfunc::save_PlantName(QString PlantName)
{
    configIniWrite->setValue("PlantName/Name",PlantName);
}

QString pubfunc::read_HISTDATA_ID(QString unitNo)
{
    QString searchSQL = QString("select value from config where tablename='HISTDATA' and `key`='%1'").arg(unitNo);
    return db.sql_fetchrow_plus(searchSQL,0);
}

void pubfunc::save_HISTDATA_ID(QString unitNo,QString ID)
{
    QString updateSQL = QString("update config set value='%1' where tablename='HISTDATA' and `key`='%2'").arg(ID,unitNo);
    db.sql_exec(updateSQL);
    return;
}

void pubfunc::save_accessControl_ip1(QString accessControl_ip1)
{
    configIniWrite->setValue("ACCESSCONTROL1/IP",accessControl_ip1);
}

QString pubfunc::readPlantName()
{
    return configIniRead->value("PlantName/Name").toString();
}

QString pubfunc::read_SerialNumber()
{
    return configIniRead->value("SerialNumber/num").toString();
}

void pubfunc::save_SerialNumber(int num)
{
    configIniWrite->setValue("SerialNumber/num",num);
}

QString pubfunc::read_BaudRate()
{
    return configIniRead->value("BaudRate/num").toString();
}

void pubfunc::save_BaudRate(int num)
{
    configIniWrite->setValue("BaudRate/num",num);
}

QString pubfunc::read_DataBits()
{
    return configIniRead->value("DataBits/num").toString();
}

void pubfunc::save_DataBits(int num)
{
    configIniWrite->setValue("DataBits/num",num);
}

QString pubfunc::read_StopBit()
{
    return configIniRead->value("StopBit/num").toString();
}

void pubfunc::save_StopBit(int num)
{
    configIniWrite->setValue("StopBit/num",num);
}

QString pubfunc::read_ParityCorrection()
{
    return configIniRead->value("ParityCorrection/num").toString();
}

void pubfunc::save_ParityCorrection(int num)
{
    configIniWrite->setValue("ParityCorrection/num",num);
}

QString pubfunc::read_StartBit()
{
    return configIniRead->value("StartBit/num").toString();
}

void pubfunc::save_StartBit(int num)
{
    configIniWrite->setValue("StartBit/num",num);
}

QString pubfunc::read_InterceptDigit()
{
    return configIniRead->value("InterceptDigit/num").toString();
}

void pubfunc::save_InterceptDigit(int num)
{
    configIniWrite->setValue("InterceptDigit/num",num);
}

QString pubfunc::read_hostip()
{
    return configIniRead->value("HOSTIP/VALUES").toString();
}

void pubfunc::write_hostip(QString hostip)
{
    configIniWrite->setValue("HOSTIP/VALUES",hostip);
}

QString pubfunc::read_username()
{
    return configIniRead->value("USERNAME/NAME").toString();
}

void pubfunc::write_username(QString username)
{
    configIniWrite->setValue("USERNAME/NAME",username);
}

QString pubfunc::read_whether_update()
{
    return configIniRead->value("WHETHER_UPDATE/VALUE").toString();
}

void pubfunc::write_whether_update()
{
    configIniWrite->setValue("WHETHER_UPDATE/VALUE",QString("true"));
}

QString pubfunc::newPurchaseContracNo()
{
    const char *searchSQL = "select value,data from setting where `key`='PurchaseContracNo';";
    QString data = db.sql_fetchrow_plus(searchSQL,1);
    if(data != QDate::currentDate().toString("yyyy-MM-dd")){
        QString updateSQL = QString("update setting set value='1',data='%1' where `key`='PurchaseContracNo';")
                .arg(QDate::currentDate().toString("yyyy-MM-dd"));
        db.sql_exec(updateSQL);
    }

    int num = db.sql_fetchrow_plus(searchSQL,0).toInt();
    QString str = QString("cg")+QDate::currentDate().toString("yyyyMMdd")+QString("").sprintf("%03d",num);
    db.sql_exec("update setting set value=value+'1' where `key`='PurchaseContracNo';");
    return str;
}


QString pubfunc::newAuxiliaryStorageNo()
{
    const char *searchSQL = "select value,data from setting where `key`='AuxiliaryStorageNo';";
    QString data = db.sql_fetchrow_plus(searchSQL,1);
    if(data != QDate::currentDate().toString("yyyy-MM-dd")){
        QString updateSQL = QString("update setting set value='1',data='%1' where `key`='AuxiliaryStorageNo';")
                .arg(QDate::currentDate().toString("yyyy-MM-dd"));
        db.sql_exec(updateSQL);
    }

    int num = db.sql_fetchrow_plus(searchSQL,0).toInt();
    QString str = QString("rk")+QDate::currentDate().toString("yyyyMMdd")+QString("").sprintf("%03d",num);
    db.sql_exec("update setting set value=value+'1' where `key`='AuxiliaryStorageNo';");
    return str;
}


QString pubfunc::newAuxiliaryOutputNo()
{
    const char *searchSQL = "select value,data from setting where `key`='AuxiliaryOutputNo';";
    QString data = db.sql_fetchrow_plus(searchSQL,1);
    if(data != QDate::currentDate().toString("yyyy-MM-dd")){
        QString updateSQL = QString("update setting set value='1',data='%1' where `key`='AuxiliaryOutputNo';")
                .arg(QDate::currentDate().toString("yyyy-MM-dd"));
        db.sql_exec(updateSQL);
    }

    int num = db.sql_fetchrow_plus(searchSQL,0).toInt();
    QString str = QString("ck")+QDate::currentDate().toString("yyyyMMdd")+QString("").sprintf("%03d",num);
    db.sql_exec("update setting set value=value+'1' where `key`='AuxiliaryOutputNo';");
    return str;
}

QString pubfunc::newSalesContractNo()
{
    const char *searchSQL = "select value,data from setting where `key`='SalesContractNo';";
    QString data = db.sql_fetchrow_plus(searchSQL,1);
    if(data != QDate::currentDate().toString("yyyy-MM-dd")){
        QString updateSQL = QString("update setting set value='1',data='%1' where `key`='SalesContractNo';")
                .arg(QDate::currentDate().toString("yyyy-MM-dd"));
        db.sql_exec(updateSQL);
    }

    int num = db.sql_fetchrow_plus(searchSQL,0).toInt();
    QString str = QString("xs")+QDate::currentDate().toString("yyyyMMdd")+QString("").sprintf("%03d",num);
    db.sql_exec("update setting set value=value+'1' where `key`='SalesContractNo';");
    return str;
}

QString pubfunc::read_accessControl_ip1()
{
    return configIniRead->value("ACCESSCONTROL1/IP").toString();
}

QString pubfunc::read_connect_menjin()
{
    return configIniRead->value("CONNECT_MENJIN/VALUE").toString();
}

void pubfunc::write_connect_menjin(QString str)
{
    configIniWrite->setValue("CONNECT_MENJIN/VALUE",str);
}

QString pubfunc::read_unitType()
{
    return configIniRead->value("UNITTYPE/VALUE").toString();
}

void pubfunc::write_unitType(QString unitType)
{
    configIniWrite->setValue("UNITTYPE/VALUE",unitType);
}

//add by panjinlei 2018-03-16

QString pubfunc::read_DVR_IP()
{
    QSettings *configIniRead = new QSettings("config.ini",QSettings::IniFormat);
    return configIniRead->value("DVRIP/VALUES").toString();
}

void pubfunc::save_DVR_IP(QString ip)
{
    QSettings *configIniWrite = new QSettings("config.ini",QSettings::IniFormat);
    configIniWrite->setValue("DVRIP/VALUES",ip);
    delete configIniWrite;
}

QString pubfunc::read_IPC1()
{
    QSettings *configIniRead = new QSettings("config.ini",QSettings::IniFormat);
    return configIniRead->value("IPC1/VALUES").toString();
}

void pubfunc::save_IPC1(int num)
{
    QSettings *configIniWrite = new QSettings("config.ini",QSettings::IniFormat);
    configIniWrite->setValue("IPC1/VALUES",num);
    delete configIniWrite;
}

QString pubfunc::read_IPC2()
{
    QSettings *configIniRead = new QSettings("config.ini",QSettings::IniFormat);
    return configIniRead->value("IPC2/VALUES").toString();
}

void pubfunc::save_IPC2(int num)
{
    QSettings *configIniWrite = new QSettings("config.ini",QSettings::IniFormat);
    configIniWrite->setValue("IPC2/VALUES",num);
    delete configIniWrite;
}

QString pubfunc::read_IPC3()
{
    QSettings *configIniRead = new QSettings("config.ini",QSettings::IniFormat);
    return configIniRead->value("IPC3/VALUES").toString();
}

void pubfunc::save_IPC3(int num)
{
    QSettings *configIniWrite = new QSettings("config.ini",QSettings::IniFormat);
    configIniWrite->setValue("IPC3/VALUES",num);
    delete configIniWrite;
}

//end
