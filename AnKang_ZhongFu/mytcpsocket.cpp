#include "mytcpsocket.h"
#include "mainwindow.h"

extern QString userName;
extern QString quanxian;
extern QString whetherCheckSend;
extern QString PRODUCTUNITNO;
extern mainTitle   *titleBar;
extern pubfunc pub;

myTCPsocket::myTCPsocket(MainWindow *main_w, QWidget *parent) :
    QWidget(parent)
{
    this->main_w = main_w;
    sockClient = new QTcpSocket(this);
    connect(sockClient,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(sock_Error()));//设置socket出错时的槽函数
    connect(sockClient,SIGNAL(readyRead()),this,SLOT(read_Msg()));//设置socket读消息的槽函数
    connect(sockClient,SIGNAL(connected()),this,SLOT(socket_connected()));//设置socket完成连接消息的槽函数
}

void myTCPsocket::myTCPsocket_connected(QString hostip)
{
    QHostAddress hostAddr(hostip);
    sockClient->connectToHost(hostAddr,8000);//银泰
}

void myTCPsocket::myTCPsocket_disconnected()
{
    sockClient->close();
}

void myTCPsocket::sock_Error()
{
    QMessageBox msgBox;
    msgBox.setText(QString("检测到与服务器的连接已经断开(%1)").arg(sockClient->errorString()));
    msgBox.setInformativeText("是否要进行重新连接？");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();
    switch (ret) {
      case QMessageBox::Yes:
          sockClient->close();
          sockClient = new QTcpSocket(this);
          connect(sockClient,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(sock_Error()));//设置socket出错时的槽函数
          connect(sockClient,SIGNAL(readyRead()),this,SLOT(read_Msg()));//设置socket读消息的槽函数
          connect(sockClient,SIGNAL(connected()),this,SLOT(socket_connected()));//设置socket完成连接消息的槽函数
          myTCPsocket_connected(pub.read_hostip());
          break;
      case QMessageBox::No:
          exit(0);
          break;
      default:
          exit(0);
          break;
    }
}

void myTCPsocket::read_Msg()
{
    qDebug()<<tr("收到的字节")<<sockClient->bytesAvailable();
    struct msg_t msg;
    memset(&msg, 0, sizeof(msg));
    QByteArray recv = sockClient->readAll();
    while (recv.size() != 0) {
        int size = (unsigned int)recv.size()<sizeof(msg)?recv.size():sizeof(msg);
        memcpy(&msg,recv.data(),size);
        //处理消息
        switch (msg.head[0])
        {
        case 0://来自server的send消息
            recv_send_Msg(&msg);
            break;
        case 1://来自server的sys1系统消息
            system_Msg(&msg);
            break;
        default:
            //未知消息 --忽略
            break;
        }
        int length = sizeof(msg.head)+sizeof(msg.src)+sizeof(msg.win_info)+strlen(msg.body);
        qDebug()<<tr("收到消息:")<<sizeof(msg)<<length<<endl<<msg.head[0]<<msg.head[1]<<msg.head[2]<<msg.head[3]<<msg.src<<msg.win_info<<msg.body;
        recv = recv.mid(length);
    }
}

void myTCPsocket::socket_connected()
{
    login_Msg();//向server端发送登录消息
}

void myTCPsocket::login_Msg()
{
    QDate date;
    QString currentDate = date.currentDate().toString("yyyy-MM-dd");
    if(sockClient->isOpen())
    {
        if (sockClient->state() == QAbstractSocket::ConnectedState)
        {
            struct msg_t msg;
            memset(&msg, 0, sizeof(msg));
            msg.head[0] = 1;//设置消息为登录消息
            strncpy(msg.src,userName.toStdString().data(),strlen(userName.toStdString().data()));//设置登录用户
            strncpy(msg.body,currentDate.toStdString().data(),strlen(currentDate.toStdString().data()));//设置登录消息时间
            sockClient->write((const char *)&msg, sizeof(msg.head)+sizeof(msg.src)+sizeof(msg.win_info)+strlen(msg.body));
        }
    }
}

void myTCPsocket::recv_send_Msg(msg_t *msg)
{
    switch(msg->head[1]){
    case 1:
        //send1消息（弹窗通知消息）
        if(userName != msg->src){
            if(quanxian.contains(msg->win_info)){
                if(QString(msg->win_info) == "生产任务单"||QString(msg->win_info) == "配合比通知单"/*具有审核权限的窗口*/){
                    if(whetherCheckSend == "有"){
                        Widget *popupWidnow = new Widget(main_w);
                        popupWidnow->setWinTitle(msg->win_info);
                        popupWidnow->setMsg(tr("通知消息，来自：")+QString(msg->src),msg->body);
                        popupWidnow->showAsQQ();
                    }
                }
                else if(strcmp(msg->win_info,"发货确认") == 0){
                    QString str = msg->body;
                    if(str.left(1) == PRODUCTUNITNO){
                        Widget *popupWidnow = new Widget(main_w);
                        popupWidnow->setWinTitle(msg->win_info);
                        popupWidnow->setMsg(tr("通知消息，来自：")+QString(msg->src),msg->body);
                        popupWidnow->showAsQQ();
                    }
                }
                else{
                    Widget *popupWidnow = new Widget(main_w);
                    popupWidnow->setWinTitle(msg->win_info);
                    popupWidnow->setMsg(tr("通知消息，来自：")+QString(msg->src),msg->body);
                    popupWidnow->showAsQQ();
                }
            }
        }
        break;
    case 2:
        if(PRODUCTUNITNO.toInt() == msg->head[2]){
            QSqlDatabase DB = QSqlDatabase::addDatabase("QODBC","writeAccessDB");
            DB.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=D://HKW8//tpdata//histdatanew_tbl.mdb;UID='';PWD=cdz110119");
            if(!DB.open()){//打开机组数据库
                return;
            }
            QSqlQuery *query = new QSqlQuery(DB);
            query->exec(msg->body);
            delete query;
            DB.close();
        }
        break;
    case 3://send3消息（刷新消息）
        for(int i = 0; i<main_w->mdiArea->subWindowList().size(); i++){
           QString winTitle = main_w->mdiArea->subWindowList().at(i)->windowTitle();
           titleConvert(winTitle);
        }
        break;
    default:
        break;
    }
}

void myTCPsocket::system_Msg(msg_t *msg)
{
    switch(msg->head[1]){
    case 1:
        QMessageBox::information(this,tr("注册提醒"),tr(msg->body),0,0,0);
        break;
    case 2:
        QMessageBox::information(this,tr("软件注册"),tr("软件到期，请注册！！！"),0,0,0);
        exit(0);
        break;
    case 3:
        QMessageBox::information(this,tr("提醒"),tr("您的账号已在别处登录。"),0,0,0);
        exit(0);
        break;
    case 4:
        QMessageBox::information(this,tr("登录错误"),tr("请检查客户端以及服务器的系统时间。"),0,0,0);
        exit(0);
        break;
    }
}

void myTCPsocket::send_Msg1(const char *win_title/*接收该消息的子窗口名称*/,const char *msg_body/*弹窗内容*/)
{
    if(sockClient->isOpen()){
        if(sockClient->state() == QAbstractSocket::ConnectedState){
            struct msg_t msg;
            memset(&msg,0,sizeof(msg));
            msg.head[0] = 0;
            msg.head[1] = 1;
            strcpy(msg.src,userName.toStdString().data());
            strcpy(msg.win_info,win_title);
            strncpy(msg.body,msg_body,strlen(msg_body));
            sockClient->write((const char *)&msg, sizeof(msg.head)+sizeof(msg.src)+sizeof(msg.win_info)+strlen(msg.body));
            sockClient->waitForBytesWritten(-1);
            sockClient->waitForReadyRead();
        }
    }
}

void myTCPsocket::send_Msg2(int UnitNo,const char *win_title,const char *msg_body)
{
    if(sockClient->isOpen()){
        if(sockClient->state() == QAbstractSocket::ConnectedState){
            struct msg_t msg;
            memset(&msg,0,sizeof(msg));
            msg.head[0] = 0;
            msg.head[1] = 2;
            msg.head[2] = UnitNo;
            strcpy(msg.src,userName.toStdString().data());
            strcpy(msg.win_info,win_title);
            strncpy(msg.body,msg_body,strlen(msg_body));
            sockClient->write((const char *)&msg, sizeof(msg.head)+sizeof(msg.src)+sizeof(msg.win_info)+strlen(msg.body));
            sockClient->waitForBytesWritten(-1);
            sockClient->waitForReadyRead();
        }
    }
}

void myTCPsocket::send_Msg3()
{
    if(sockClient->isOpen()){
        if(sockClient->state() == QAbstractSocket::ConnectedState){
            struct msg_t msg;
            memset(&msg,0,sizeof(msg));
            msg.head[0] = 0;
            msg.head[1] = 3;
            sockClient->write((const char *)&msg, sizeof(msg.head));
            sockClient->waitForBytesWritten(-1);
            sockClient->waitForReadyRead();
        }
    }
}

void myTCPsocket::titleConvert(QString title)
{
    if(title == "采购合同管理"){
        main_w->cghtglDlg->refresh();
    }
    else if(title == "原料入库数据调整"){
        main_w->ylrksjtzDlg->refresh();
    }
    else if(title == "辅材供应商档案"){
        main_w->fcgysdaDlg->refresh();
    }
    else if(title == "库存查询"){
        main_w->rkcxDlg->refresh();
    }
    else if(title == "库存调整"){
        main_w->kcqcsdDlg->refresh();
    }
    else if(title == "辅材设置"){
        main_w->fcszDlg->refresh();
    }
    else if(title == "辅材出库"){
        main_w->fcckDlg->refresh();
    }
    else if(title == "辅材库存"){
        main_w->fckcDlg->refresh();
    }
    else if(title == "辅材耗用统计"){
        main_w->fchytjDlg->refresh();
    }
    else if(title == "采购入库"){
        main_w->gbrkDlg->refresh();
    }
    else if(title == "客户信息维护"){
        main_w->khdaDlg->refresh();
    }
    else if(title == "销售合同管理"){
        main_w->xshtglDlg->refresh();
    }
    else if(title == "发货价格批量调整"){
        main_w->fhjgpltzDlg->refresh();
    }
    else if(title == "合同执行情况"){
        main_w->htzxqkDlg->refresh();
    }
    else if(title == "销售收款条件"){
        main_w->xssktjDlg->refresh();
    }
    else if(title == "生产预警"){
        main_w->scyjDlg->refresh();
    }
    else if(title == "生产任务单"){
        main_w->scrwdDlg->refresh();
    }
    else if(title == "生产任务安排"){
        main_w->scrwapDlg->refresh();
    }
    else if(title == "发货数据调整"){
        main_w->fhsjtzDlg->refresh();
    }
    else if(title == "配合比模板维护"){
        main_w->phbmbDlg->refresh();
    }
    else if(title == "配合比通知单"){
        main_w->phbtzdDlg->refresh();
    }
    else if(title == "发货确认"){
        main_w->fhqrDlg->refresh();
    }
    else if(title == "销售总账"){
        main_w->xszzDlg->refresh();
    }
    else if(title == "账号设置"){
        main_w->zhszDlg->refresh();
    }
    else if(title == "原料消耗价格调整"){
        main_w->ylxhjgtzDlg->refresh();
    }
    else if(title == "采购明细表"){
        main_w->cgmxbDlg->refresh();
    }
    else if(title == "销售明细表"){
        main_w->xsmxbDlg->refresh();
    }
    else if(title == "生产消耗表"){
        main_w->scxhbDlg->refresh();
    }
    else if(title == "车辆运输报表"){
        main_w->clysbDlg->refresh();
    }
    else if(title == "方量查询"){
        main_w->flcxDlg->refresh();
    }
    else if(title == "生产分布"){
        main_w->scfbDlg->refresh();
    }
    else if(title == "对数单"){
        main_w->dsdDlg->refresh();
    }
    else if(title == "结算单"){
        main_w->jsdDlg->refresh();
    }
    else if(title == "砼车司机"){
        main_w->tcsjDlg->refresh();
    }
    else if(title == "砼车信息"){
        main_w->tcxxDlg->refresh();
    }
    else if(title == "运费设置"){
        main_w->yfszDlg->refresh();
    }
    else if(title == "工程运距确认"){
        main_w->gcyjqrDlg->refresh();
    }
    else if(title == "泵车司机"){
        main_w->bcsjDlg->refresh();
    }
    else if(title == "泵车信息"){
        main_w->bcxxDlg->refresh();
    }
    else if(title == "厂地设置"){
        main_w->cdszDlg->refresh();
    }
    else if(title == "部门设置"){
        main_w->bmszDlg->refresh();
    }
    else if(title == "原料设置"){
        main_w->ylszDlg->refresh();
    }
    else if(title == "仓位设置"){
        main_w->cwszDlg->refresh();
    }
    else if(title == "产品设置"){
        main_w->cpszDlg->refresh();
    }
    else if(title == "属性设置"){
        main_w->sxszDlg->refresh();
    }
    else if(title == "用户管理"){
        main_w->yhglDlg->refresh();
    }
    else if(title == "权限管理"){
        main_w->qxglDlg->refresh();
    }
}
