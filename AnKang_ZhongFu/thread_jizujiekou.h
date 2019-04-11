 #ifndef THREAD_JIZUJIEKOU_H
#define THREAD_JIZUJIEKOU_H

#include <QThread>
#include <QWidget>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include "pubfunc.h"
#include "mymysql.h"
#include "mytcpsocket.h"

class thread_jizujiekou : public QThread
{
    Q_OBJECT
public:
    explicit thread_jizujiekou(QObject *parent = 0);
    ~thread_jizujiekou();
    void run();

private:
    mymysql db;

    QSqlDatabase XinXingDB;
    QSqlQuery *XinXingQuery;

    QSqlDatabase FeiMiDB;
    QSqlQuery *FeiMiQuery;

    QSqlDatabase SANYDB;
    QSqlQuery *SANYQuery;

    QSqlDatabase ZOOMLIONDB;
    QSqlQuery *ZOOMLIONQuery;
    QSqlQuery *ZOOMLIONItemQuery;
    QSqlQuery *ZOOMLIONCountQuery;

    QSqlDatabase BSDB;
    QSqlQuery *BSQuery;
    QSqlQuery *BSItemQuery;

private:
    QString insertHISTDATA;
    QString insertHISTDATA2;
    bool whetherTransfer;//是否上传了数据
    QString ID;

    QString PlantName;
    QString jizuNo;

signals:
    void updateProcess(int count);
    void erroMessage(QString erro);
    void refreshMsg();

public:
    QString erro;
    bool threadIsRun;

private:
    void XinXingsyncXiaohao();
    void FeiMisyncXiaohao();
    void SANYsyncXiaohao();
    void ZOOMLIONsyncXiaohao();
    void BSsyncXiaohao();
    void writeErroLog(QString erro);

public:
    void setThreadIsRun(bool whetherRun);
};

#endif // THREAD_JIZUJIEKOU_H
