#include "widget.h"
#include "mainwindow.h"

static int widgetCount = 0;

Widget::Widget(MainWindow *main_w, QWidget *parent)
    : QWidget(parent)
{
    this->main_w = main_w;
    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint|Qt::Tool);
    setAttribute(Qt::WA_DeleteOnClose);
    isEnter = false;
    titleW  = new titleWidget;
    connect(titleW,SIGNAL(myClose()),this,SLOT(close()));
    connect(titleW,SIGNAL(myClose()),this,SLOT(widgetCount1()));
    content = new QLabel;
    content->setWordWrap(true);
    content->setAlignment(Qt::AlignTop);
    content->setFixedSize(300,100);
    btnLook = new mypushbutton(tr("查看"),this);
    connect(btnLook,SIGNAL(clicked()),this,SLOT(seeInfo()));

    QVBoxLayout*mainLayout=new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->addWidget(titleW);
    mainLayout->addWidget(content);
    content->setMargin(5);
    mainLayout->addWidget(btnLook,0,Qt::AlignRight);
    setLayout(mainLayout);

    setFixedSize(sizeHint().width(),sizeHint().height());

    beginY      = QApplication::desktop()->height();
    timeCount   = 0;
    tran        = 1.0;

    timerShow = new QTimer(this);
    connect(timerShow,SIGNAL(timeout()),this,SLOT(myMove()));
    timerStay = new QTimer(this);
    connect(timerStay,SIGNAL(timeout()),this,SLOT(myStay()));
    timerClose = new QTimer(this);
    connect(timerClose,SIGNAL(timeout()),this,SLOT(myClose()));
}

Widget::~Widget()
{

}

void Widget::setMsg(QString title, QString content)
{
    titleW->setTitleText(" " + title);
    this->content->setText("   " + content);
}

void Widget::setWinTitle(QString winTitle)
{
    this->winTitle.clear();
    this->winTitle = winTitle;
}

void Widget::paintEvent(QPaintEvent *)
{
    QBitmap bitmap(this->size());
    bitmap.fill(Qt::white);
    QPainter painter(this);
    painter.setBrush(QBrush(QColor(240,255,255)));
    painter.setPen(QPen(QBrush(QColor(100,200,200)),4));
    painter.drawRoundedRect(bitmap.rect(),5,5);
    setMask(bitmap);
}

void Widget::showAsQQ()
{
    widgetCount++;
    QDesktopWidget *deskTop = QApplication::desktop();
    deskRect = deskTop->availableGeometry();
    normalPoint.setX(deskRect.width() - rect().width() - 1);
    normalPoint.setY(deskRect.height() - (rect().height()));
    move(normalPoint.x(),deskRect.height() + 100);
    show();
    timerShow->start(5);

    QString dir = QCoreApplication::applicationDirPath();
    QSound::play(dir+"/mysounds/bells.wav");
}

//平滑显示出来
void Widget::myMove()
{
    beginY--;
    move(normalPoint.x(),beginY);

    if(beginY<=normalPoint.y() - 30){
         timerShow->stop();
         timerStay->start(1000);
    }
}

//停留显示
void Widget::myStay()
{
    timeCount++;
    if(timeCount>=90){
     timerStay->stop();
     timerClose->start(200);
    }
}

//自动关闭时实现淡出效果
void Widget::myClose()
{
    if(isEnter){
        tran = 1.0;
        setWindowOpacity(tran);
        return;
    }
    tran -= 0.05;
    if(tran<=0.0){
        timerClose->stop();
        emit close();
        widgetCount--;
    }
    else
        setWindowOpacity(tran);
}

void Widget::seeInfo()
{
    this->main_w->showMaximized();
    if(winTitle == "生产任务单"){
        this->main_w->on_shengchanrenwudan();
        this->main_w->scrwdDlg->tabWidget->setCurrentIndex(1);
    }
    else if(winTitle == "生产任务安排"){
        this->main_w->on_shengchanrenwuanpai();
        this->main_w->scrwapDlg->tabWidget->setCurrentIndex(0);
    }
    else if(winTitle == "配合比通知单"){
        this->main_w->on_peihebitongzhidan();
        this->main_w->phbtzdDlg->tabWidget->setCurrentIndex(0);
    }
}

void Widget::widgetCount1()
{
    widgetCount--;
}

void Widget::enterEvent(QEvent *)
{
    isEnter = true;
}

void Widget::leaveEvent(QEvent *)
{
    isEnter = false;
}
