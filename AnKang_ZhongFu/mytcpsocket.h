#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QWidget>
#include <QDebug>
#include <QTimer>
#include <QMessageBox>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDate>
#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include "widget.h"
#include "maintitle.h"
#include "pubfunc.h"

#define CLIENTCOUNT 100
#define BODYBUF 2048

struct msg_t{
        int  head[4];
        char src[30];
        char win_info[50];
        char body[BODYBUF];
};

class MainWindow;

class myTCPsocket : public QWidget
{
    Q_OBJECT
public:
    explicit myTCPsocket(MainWindow *main_w, QWidget *parent = 0);
    void myTCPsocket_connected(QString hostip);
    void myTCPsocket_disconnected();

private:
    QTcpSocket                   *sockClient;
    MainWindow                   *main_w;
    QTimer                       *judge_netWork;

private slots:
    void sock_Error();//socket出错的时候触发的槽函数
    void read_Msg();//socket接收到消息触发的槽函数
    void socket_connected();//socket成功连接到服务端后触发的槽函数

private:
    void login_Msg();
    void recv_send_Msg(struct msg_t *msg);
    void system_Msg(struct msg_t *msg);
    void titleConvert(QString title);

public:
    void send_Msg1(const char *win_title,const char *msg_body);
    void send_Msg2(int UnitNo/*机组编号*/, const char *win_title, const char *msg_body);
    void send_Msg3();//刷新消息
};

#endif // MYTCPSOCKET_H
