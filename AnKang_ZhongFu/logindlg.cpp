#include "logindlg.h"
#include "mainwindow.h"

extern mymysql db;
extern pubfunc pub;
extern QString quanxian;
extern QString whetherCheckSend;
extern QString userName;
extern myTCPsocket *sockClient;
extern QString PRODUCTUNITNO;
extern QString connectMenJin;
extern QString UNITTYPE;

loginDlg::loginDlg(MainWindow *main_w, QWidget *parent) :
    QDialog(parent)
{
    this->w = main_w;
    pub.write_whether_update();//设置软件开始时自动更新
    islogin         = false;//意味着islogin在对话框初始化的时候值为false;
    isconnecting    = false;

    label = new QLabel(tr("用户登录"));
    label->setAlignment(Qt::AlignHCenter|Qt::AlignBottom);
    label->setStyleSheet("color:white");
    QFont ft;
    ft.setPixelSize(20);
    label->setFont(ft);
    label->setGeometry(310,80,220,50);
    label->setParent(this);

    label1 = new QLabel(tr("数据库连接失败"));
    label1->setAlignment(Qt::AlignCenter);
    label1->setStyleSheet("color:white");
    label1->setGeometry(310,135,220,15);
    label1->setParent(this);
    label1->setHidden(true);

    label2 = new QLabel(tr("用户不存在或密码错误"));
    label2->setAlignment(Qt::AlignCenter);
    label2->setStyleSheet("color:white");
    label2->setGeometry(310,135,220,15);
    label2->setParent(this);
    label2->setHidden(true);

    label3 = new QLabel(tr("服务端连接失败或服务端未运行"));
    label3->setAlignment(Qt::AlignCenter);
    label3->setStyleSheet("color:white");
    label3->setGeometry(310,135,220,15);
    label3->setParent(this);
    label3->setHidden(true);

    lineEditHostIP = new QLineEdit;
    lineEditHostIP->setPlaceholderText(tr("服务器IP"));
    lineEditHostIP->setGeometry(310,155,220,20);
    lineEditHostIP->setParent(this);
    lineEditHostIP->setText(pub.read_hostip());

    lineEditUserID = new QLineEdit;
    lineEditUserID->setText(pub.read_username());
    lineEditUserID->setPlaceholderText(tr("用户名"));
    lineEditUserID->setGeometry(310,185,220,20);
    lineEditUserID->setParent(this);

    lineEditPasswd = new QLineEdit;
    lineEditPasswd->setPlaceholderText(tr("密码"));
    lineEditPasswd->setEchoMode(QLineEdit::Password);//设置为密码框
    lineEditPasswd->setGeometry(310,215,220,20);
    lineEditPasswd->setParent(this);


    loginBtn = new QPushButton;
    loginBtn->setText("登录");
    loginBtn->setGeometry(310,255,100,25);
    loginBtn->setParent(this);
    logoutBtn = new QPushButton;
    logoutBtn->setText("取消");
    logoutBtn->setGeometry(430,255,100,25);
    logoutBtn->setParent(this);

    this->setWindowTitle("登录");
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setFixedSize(550,300);
    //设置背景图片
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/image/login.png")));
    setPalette(palette);

    connect(loginBtn, SIGNAL(clicked()), this, SLOT(loginBtnOnclick()));
    connect(logoutBtn, SIGNAL(clicked()), this, SLOT(logoutBtnOnclick()));
}

void loginDlg::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Escape:
           exit(0);
           break;
        default:
           QDialog::keyPressEvent(event);
    }
}

void loginDlg::closeEvent(QCloseEvent *closeEvent)
{
    if(islogin == true){
        closeEvent->accept();
    }
    if(islogin == false){
        closeEvent->ignore();
        exit(0);
    }
}

void loginDlg::loginBtnOnclick()
{
    islogin = true;
    if(isconnecting == false){
        hostip = lineEditHostIP->text();
        userid = lineEditUserID->text();
        passwd = lineEditPasswd->text();
        label1->setHidden(true);
        label2->setHidden(true);

        isconnecting = true;
        int res = db.sql_connect(hostip,"dbuser1","dbuser1","akzf_db");

        if (res == -1){
            label1->setHidden(false);
            isconnecting = false;
            return;
        }
        else if(res == 0){
            QString SQL1 = QString("select Jurisdiction,WeighingPermissions,RealName from UserManagement where UserName='%1' and Password1='%2';").arg(userid,passwd);
            int ret= db.sql_whetherExisting(SQL1);
            if(ret == -3){
                label2->setHidden(false);
                db.sql_disconnet();
                isconnecting = false;
                return;
            }
            else{//登录成功后连接服务器端
                pub.write_hostip(hostip);
                pub.write_username(userid);
                sockClient->myTCPsocket_connected(hostip);//连接服务端
                quanxian = db.sql_fetchrow_plus(SQL1,0);
                whetherCheckSend = db.sql_fetchrow_plus(SQL1,1);
                userName = db.sql_fetchrow_plus(SQL1,2);
                PRODUCTUNITNO = pub.readJizuBianhao();
                connectMenJin = pub.read_connect_menjin();
                UNITTYPE = pub.read_unitType();
                close();
            }
        }
    }
}

void loginDlg::logoutBtnOnclick()
{
    exit(0);
}
