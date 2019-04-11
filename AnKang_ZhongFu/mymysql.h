#ifndef MYMYSQL_H
#define MYMYSQL_H

//windows下使用mysql.h的方法
//路径中使用/符号
#include <windows.h>
#include <C:/mysql/include/mysql.h>
#include <QRegExp>

//linux下使用mysql.h的方法
//#include <mysql/mysql.h>

/*
int listen_st;//linux下的定义socket描述符的写法
SOCKET listen_st;//windows下的定义socket描述符的写法
*/

#include <QWidget>
#include <QObject>
#include <QStandardItemModel>
#include <QComboBox>
#include <QString>
#include <QTableWidget>
#include <QDate>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlDatabase>
#include <QCheckBox>
#include <QLineEdit>
#include <QTableWidgetItem>
#include <QTableView>
#include <QTreeView>
#include <QList>
#include <QSignalMapper>
#include <QPointer>
#include <QStringList>
#include <QVBoxLayout>
#include <QVariant>
#include <QStringList>
#include <QDebug>
#include <QListView>
#include <string.h>
#include "pubfunc.h"
#include "warehousewidget.h"

class mymysql : public QObject
{
    Q_OBJECT
public:
    explicit mymysql(QObject *parent = 0);
    const char *geterror();
    //第一个参数代表server IP地址，第二个参数代表用户名，第三个密码，第四个使用数据库名
    int sql_connect(QString Hostname, const char *User, const char *Password, const char *DBName);
    int sql_reconnect();
    void sql_disconnet();
    int sql_affect_rows();
    int sql_exec(QString SQL);
    QString sql_fetchrow_plus(QString SQL, int filednum);
    int sql_fillComboBoxItem(QString SQL, QComboBox *comboBox);
    int sql_fillComboBoxItem2(QString SQL, QComboBox *comboBox);
    int sql_fillComboBoxItem3(QString SQL, QComboBox *comboBox);
    int sql_fillQStringList(QString SQL, QStringList *stringList);
    int sql_fillTableWidgetItem(QString SQL, QTableWidget *view);
    int sql_whetherExisting(QString SQL);
    int sql_whetherRepeat(QString SQL, QString str);
    int sql_fillTableWidget(QString SQL, QTableWidget *view, int startColum);
    int sql_fillTableWidget2(QString SQL, QTableWidget *view, int column);
    QList<QStringList> sql_result(QString SQL);
    int showview(QString SQL,QTableView *view,QStandardItemModel **model);
    int showview_num(QString SQL, QTableView *view, QStandardItemModel **model, int column);
    int show_treeview(QString SQL,QTreeView *view,QStandardItemModel **model);
    int show_treeview2(QString SQL, QTreeView *view, QStandardItemModel **model);
    int showview_caigoujiesuan(QString SQL,QTableView *view,QStandardItemModel **model);
    int showview_xiaoshoujiesuan(QString SQL,QTableView *view,QStandardItemModel **model);
    int showview_yunfeijiesuan(QString SQL,QTableView *view,QStandardItemModel **model);
    int showview_yunfeitongji(QString SQL,QTableView *view,QStandardItemModel **model);
    int showview_yuanliaorukushujutiaozheng(QString SQL,QTableView *view,QStandardItemModel **model);
    QStringList find_factory_from_tasklist(QString SQL);
    int newCheckBox(QString SQL,QList<QCheckBox *> &checkBoxList,int *num, QWidget *parent);
    int newWareHouseWidget(QString SQL,QList<WarehouseWidget *> &wareHoseWidgetList,int *num, QWidget *parent);
    int newCheckBoxAndLineEdit(QString SQL,QList<QCheckBox *> &checkBoxList,QList<QLineEdit *> &lineEdiList,int *num, QWidget *parent);
    int newWidget(QString SQL, QList<QWidget *> &WidgetList, QStringList &strList, QStringList &matList, QList<QLineEdit *> &pfLineEditList, QWidget *parent);
    int whether_caigoushenhequanxian(QString userName);
    int whether_xiaoshoushenhequanxian(QString userName);
    QString caigouhetongshenheren();
    QString xiaoshouhetongshenheren();
    int row_count(QString SQL);
    QStringList find_CheNo(QString SQL1);
    QStringList CreatStrList(QString SQL);


signals:
    void errorMsg(const char *);
    void reconnectSuccess();

private:
    MYSQL *connection;
    MYSQL mysql;
    char buf[1024];
    bool whetherRemoteServer;

public:
    void setWhetherRemoteServer(bool trueOrFalse);

};

#endif // MYMYSQL_H
