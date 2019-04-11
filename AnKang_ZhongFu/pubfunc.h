#ifndef PUBFUNC_H
#define PUBFUNC_H

#include <QString>
#include <QDate>
#include <QSettings>
#include <QTableView>
#include <QStandardItemModel>
#include <QStandardItem>
#include "mymysql.h"

class pubfunc
{
public:
    pubfunc();

private:
    QString str;
    QDate date;
    QSettings *configIniRead;
    QSettings *configIniWrite;
    int num;

public:
    QString newListNo();
    QString newshengliaoNo();
    QString newfahuoNo();
    QString newRenwudanNo();
    QString newTongzhidanNo();
    QString readJizuBianhao();
    QString readPlantName();
    QString read_HISTDATA_ID(QString unitNo);

    void save_HISTDATA_ID(QString unitNo, QString ID);
    void save_JizuBianhao(QString num);
    void save_PlantName(QString PlantName);
    void save_TaskNotice_ID(QString TaskNotice_ID);
    void save_accessControl_ip1(QString accessControl_ip1);

    QString read_SerialNumber();
    void save_SerialNumber(int num);

    QString read_BaudRate();
    void save_BaudRate(int num);

    QString read_DataBits();
    void save_DataBits(int num);

    QString read_StopBit();
    void save_StopBit(int num);

    QString read_ParityCorrection();
    void save_ParityCorrection(int num);

    QString read_StartBit();
    void save_StartBit(int num);

    QString read_InterceptDigit();
    void save_InterceptDigit(int num);

    QString read_hostip();
    void write_hostip(QString hostip);

    QString read_username();
    void write_username(QString username);

    QString read_whether_update();
    void write_whether_update();

    QString newPurchaseContracNo();
    QString newAuxiliaryStorageNo();
    QString newAuxiliaryOutputNo();
    QString newSalesContractNo();
    QString read_accessControl_ip1();

    QString read_connect_menjin();
    void write_connect_menjin(QString str);

    QString read_unitType();
    void write_unitType(QString unitType);

    //add by panjinlei 2018-03-16
    QString read_DVR_IP();
    void save_DVR_IP(QString ip);

    QString read_IPC1();
    void save_IPC1(int num);

    QString read_IPC2();
    void save_IPC2(int num);

    QString read_IPC3();
    void save_IPC3(int num);


    //end
};

#endif // PUBFUNC_H
