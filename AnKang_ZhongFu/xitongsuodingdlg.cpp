#include "xitongsuodingdlg.h"

extern QString userName;

extern mymysql db;
extern pubfunc pub;

xitongsuodingDlg::xitongsuodingDlg(QWidget *parent) :
    QDialog(parent)
{
    flag = false;
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->resize(400,247);

    //设置背景图片
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/image/baobiao.jpg")));
    setPalette(palette);

    label = new QLabel(tr("系统已锁定，请输入密码解锁"),this);
    label->setStyleSheet("color:red");
    label->setAlignment(Qt::AlignCenter);
    QFont ft;
    ft.setPixelSize(20);
    label->setFont(ft);
    label->setGeometry(50,40,300,30);

    label1 = new QLabel(tr("密码输入错误"),this);
    label1->setHidden(true);
    label1->setStyleSheet("color:red");
    label1->setGeometry(165,80,150,20);

    lineEdit = new QLineEdit(this);
    lineEdit->setEchoMode(QLineEdit::Password);
    lineEdit->setGeometry(50,110,300,30);

    ok = new QPushButton(tr("确认"),this);
    connect(ok,SIGNAL(clicked()),this,SLOT(on_ok()));
    ok->setGeometry(140,170,120,30);
}

void xitongsuodingDlg::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()){
        case Qt::Key_Escape:
            event->ignore();
            break;
        default:
            QDialog::keyPressEvent(event);
    }
}

void xitongsuodingDlg::closeEvent(QCloseEvent *closeEvent)
{
    if(flag == true){
        closeEvent->accept();
    }
    if(flag == false) {
        closeEvent->ignore();
    }
}

void xitongsuodingDlg::on_ok()
{
    QString mimaSQL = QString("select * from UserManagement where RealName='%1' and Password1='%2';").arg(userName,lineEdit->text());
    int ret= db.row_count(mimaSQL);
    qDebug()<<mimaSQL<<db.geterror();
    if(ret == 0){
        label1->setHidden(false);
        return;
    }else{
        flag = true;
        close();
    }
}
