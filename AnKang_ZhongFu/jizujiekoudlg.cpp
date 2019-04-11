#include "jizujiekoudlg.h"

extern mymysql      db;
extern pubfunc      pub;
extern myTCPsocket *sockClient;

jizujiekouDlg::jizujiekouDlg(QWidget *parent) :
    QDialog(parent)
{
    isOpen = false;
    widget = new QWidget(this);
    widget->resize(1200,120);

    Btn1 = new QPushButton(tr("数据传输"),this);
    connect(Btn1,SIGNAL(clicked()),this,SLOT(on_shujuchuanshu()));
    Btn2 = new QPushButton(tr("停止传输"),this);
    connect(Btn2,SIGNAL(clicked()),this,SLOT(on_tingzhichuanshu()));
    Btn2->setHidden(true);

    label1 = new QLabel(tr("数据传输已停止，请点击数据传输！"),this);
    label2 = new QLabel(tr("数据传输进行中......"),this);
    label2->setHidden(true);
    label3 = new QLabel(this);
    label3->setPixmap(QPixmap(":/image/chuanshu.png"));
    label3->setHidden(true);
    label4 = new QLabel(this);
    label4->setPixmap(QPixmap(":/image/tingzhi.png"));
    label3->setScaledContents(true);
    label4->setScaledContents(true);
    label3->setParent(widget);
    label4->setParent(widget);

    QFont ft;
    ft.setPixelSize(30);
    label1->setFont(ft);
    label2->setFont(ft);
    QFont ft1;
    ft1.setPixelSize(20);
    Btn1->setFont(ft1);
    Btn2->setFont(ft1);
    label1->setStyleSheet("color:red");
    label2->setStyleSheet("color:red");

    pProgressBar = new QProgressBar(this);
    pProgressBar->setFixedHeight(10);
    pProgressBar->setOrientation(Qt::Horizontal);// 水平方向
    pProgressBar->setMinimum(0);// 最小值
    pProgressBar->setMaximum(100);// 最大值
    pProgressBar->setValue(0);//设置当前值

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(widget,0,0,1,2);
    layout->addWidget(pProgressBar,1,0,1,2);
    layout->addWidget(Btn1,2,0);
    layout->addWidget(Btn2,2,0);
    layout->addWidget(label1,2,1);
    layout->addWidget(label2,2,1);
    layout->setRowStretch(0,1);
    layout->setRowStretch(1,1);
    layout->setRowStretch(2,1);
    layout->setRowStretch(3,1);
    layout->setRowStretch(4,5);
    layout->setColumnStretch(0,1);
    layout->setColumnStretch(1,10);

    thread = new thread_jizujiekou(this);
    connect(thread,SIGNAL(updateProcess(int)),this,SLOT(updateProcess(int)));
    connect(thread,SIGNAL(erroMessage(QString)),this,SLOT(RecErroMessage(QString)));

    threadSync = new thread_sync(this);
    connect(threadSync,SIGNAL(erroMessage(QString)),this,SLOT(RecErroMessage(QString)));
}

void jizujiekouDlg::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Escape:
           event->ignore();
           break;
        default:
           QDialog::keyPressEvent(event);
    }
}

void jizujiekouDlg::closeEvent(QCloseEvent *event)
{
    if(Btn1->isHidden()){
        int res = QMessageBox::question(this,tr("提示信息"),tr("该窗口关闭时机组接口会一同关闭，确认关闭？"),QMessageBox::Yes,QMessageBox::No);
        if(res == QMessageBox::Yes){
            isOpen = false;
            //关闭上传消耗线程
            thread->setThreadIsRun(false);
            thread->wait();
            //关闭同步线程
            threadSync->setThreadIsRun(false);
            threadSync->wait();
            event->accept();
        }
        if(res == QMessageBox::No){
            event->ignore();
        }
    }else{
        thread->wait();
        event->accept();
    }
}

void jizujiekouDlg::paintEvent(QPaintEvent *paintEvent)
{
    label3->resize(widget->size());
    label4->resize(widget->size());
    paintEvent->accept();
}

void jizujiekouDlg::on_shujuchuanshu()
{
    Btn1->setHidden(true);
    Btn2->setHidden(false);
    label1->setHidden(true);
    label2->setHidden(false);
    label3->setHidden(false);
    label4->setHidden(true);
    //上传消耗线程
    thread->setThreadIsRun(true);
    thread->start();
    //同步任务
    threadSync->setThreadIsRun(true);
    threadSync->start();
}

void jizujiekouDlg::on_tingzhichuanshu()
{
    Btn1->setHidden(false);
    Btn2->setHidden(true);
    label1->setHidden(false);
    label2->setHidden(true);
    label3->setHidden(true);
    label4->setHidden(false);
    //上传消耗线程
    thread->setThreadIsRun(false);
    thread->quit();
    //同步任务线程退出
    threadSync->setThreadIsRun(false);
    threadSync->quit();
}

void jizujiekouDlg::updateProcess(int value)
{
    pProgressBar->setValue(value);
}

void jizujiekouDlg::RecErroMessage(QString erro)
{
    on_tingzhichuanshu();
    QMessageBox msgBox;
    msgBox.setText(QString("检测到机组接口有错误发生"));
    msgBox.setInformativeText(QString("详细错误信息:\n\%1\n\n是否重新打开机组接口？").arg(erro));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();
    switch (ret) {
      case QMessageBox::Yes:
          on_shujuchuanshu();
          break;
      case QMessageBox::No:
          break;
      default:
          break;
    }
}
