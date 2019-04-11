#ifndef THREAD_SYNC_H
#define THREAD_SYNC_H

#include <QThread>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QStringList>
#include <math.h>
#include "pubfunc.h"
#include "mymysql.h"
#include "mytcpsocket.h"

class thread_sync : public QThread
{
    Q_OBJECT
public:
    explicit thread_sync(QObject *parent = 0);
    ~thread_sync();

public:
    void run();

signals:
    void updateProcess(int count);
    void erroMessage(QString erro);
    void refreshMsg();

public:
    bool threadIsRun;

private:
    //新型
    QSqlDatabase XinXingDB;
    QSqlDatabase RunStateDB;

    QSqlQuery *XinXingQuery;
    QSqlQuery *RunStatequery;

    //飞米
    QSqlDatabase FeiMiBigTaskDB;
    QSqlDatabase FeiMiRecipeDB;
    QSqlDatabase FeiMiSmallTaskDB;

    QSqlQuery *FMBigTaskQuery;
    QSqlQuery *FMRecipeQuery;
    QSqlQuery *FMSmallTaskQuery;

    //三一
    QSqlDatabase SANYDB;

    QSqlQuery *SANYQuery;

    //中联
    QSqlDatabase ZOOMLIONDB;

    QSqlQuery *ZOOMLIONQuery;

    //博硕
    QSqlDatabase BSDB;

    QSqlQuery *BSQuery;

    //岳首
    QSqlDatabase YSDB;

    QSqlQuery *YSQuery;

    mymysql db;

private:
    QString insertHISTDATA;
    QString insertHISTDATA2;
    bool whetherTransfer;//是否上传了数据
    int ID;

private://新型站
    void syncPhb(QString unitNo);
    void syncPeiFangKuTask();
    void syncRenWuKuTask();
    void syncDcRw();
    void deleteDcRw();
    void syncBuFangDcRw();
    void uploadRunState();
    void syncZhuiJiaDcRw();

private://飞米站
    void FMsyncPhb(QString unitNo);
    void FMsyncPeiFangKuTask();
    void FMsyncDcRw();
    void FMsyncBuFangDcRw();

private://三一站
    void SANYsyncPhb(QString unitNo);
    void SANYsyncPeiFangKuTask();
    void SANYsyncDcRw();
    void SANYdeleteDcRw();
    void SANYsyncBuFangDcRw();
    void SANYRunState();

private://中联站
    void ZLsyncStdPhb(QString unitNo);
    void ZLsyncRwPhb(QString TaskList);
    void ZLsyncRenWuKuTask();
    void ZLsyncDcRw();
    void ZLdeleteDcRw();
    void ZLsyncBuFangDcRw();
    void ZLRunState();

private://博硕站
    void BSsyncPhb();
    void BSsyncRenWuKuTask();
    void BSsyncDcRw();
    void BSdeleteDcRw();

public:

public:
    void setThreadIsRun(bool whetherRun);

public slots:

};

#endif // THREAD_SYNC_H
