#include "yuanliaoguanlimenu.h"
#include "mainwindow.h"

extern QString quanxian;
extern mainTitle   *titleBar;

yuanliaoguanliMenu::yuanliaoguanliMenu(MainWindow *main_w,QWidget *parent) :
    QDialog(parent)
{
    this->main_w = main_w;
    toolBtn = new QToolButton(this);
    connect(toolBtn,SIGNAL(clicked()),this,SLOT(on_close()));
    toolBtn->setObjectName(QString("toolBtn"));
    toolBtn->setFixedSize(40,40);
    toolBtn->setGeometry(10,10,50,50);

    label = new QLabel(this);
    label->setFixedSize(160,40);
    label->setPixmap(QPixmap(QString(":/menupic/yuanliaoguanlilabel.png")));
    label->setGeometry(60,10,160,40);

    Btn1 = new QPushButton(this);
    Btn1->setObjectName(QString("Btn1"));
    if(!quanxian.contains("库存查询")){
        Btn1->setHidden(true);
    }

    Btn2 = new QPushButton(this);
    Btn2->setObjectName(QString("Btn2"));
    if(!quanxian.contains("库存调整")){
        Btn2->setHidden(true);
    }

    Btn1->setFixedSize(120,120);
    Btn2->setFixedSize(120,120);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(Btn1);
    vlayout->addWidget(Btn2);

    vlayout->setMargin(0);

    QWidget *widget = new QWidget(this);
    widget->setObjectName(QString("scrollwidget"));
    widget->setLayout(vlayout);

    scrollArea = new QScrollArea(this);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setWidget(widget);

    this->setStyleSheet("QScrollArea{border: 0px}"
                        "QToolButton[objectName=\"toolBtn\"]{border:0px;background-image:url(:/menupic/fanhuijiantou1.png);}"
                        "QToolButton[objectName=\"toolBtn\"]:hover{background-image:url(:/menupic/hoverfanhuijiantou1.png);}"
                        "QToolButton[objectName=\"toolBtn\"]:pressed{background-image:url(:/menupic/pressedfanhuijiantou1.png);}"

                        "QPushButton[objectName=\"Btn1\"]{border:0px;background-image:url(:/menupic/cangweikucunbtn.png)}"
                        "QPushButton[objectName=\"Btn1\"]:hover{border:1px solid white;background-image:url(:/menupic/cangweikucunbtn.png)}"
                        "QPushButton[objectName=\"Btn1\"]:pressed{border:2px solid white;background-image:url(:/menupic/cangweikucunbtn.png)}"

                        "QPushButton[objectName=\"Btn2\"]{border:0px;background-image:url(:/menupic/kucuntiaozhengbtn.png)}"
                        "QPushButton[objectName=\"Btn2\"]:hover{border:1px solid white;background-image:url(:/menupic/kucuntiaozhengbtn.png)}"
                        "QPushButton[objectName=\"Btn2\"]:pressed{border:2px solid white;background-image:url(:/menupic/kucuntiaozhengbtn.png)}");
}

void yuanliaoguanliMenu::paintEvent(QPaintEvent *event)
{
    scrollArea->setGeometry(140,60,122,this->height()-70);
    event->accept();
}

void yuanliaoguanliMenu::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Escape:
           event->ignore();
           break;
        default:
           QWidget::keyPressEvent(event);
    }
}

void yuanliaoguanliMenu::on_close()
{
    this->main_w->mdiArea->closeActiveSubWindow();
    if(this->main_w->mdiArea->subWindowList().size() != 0){
        QString name = this->main_w->mdiArea->activeSubWindow()->windowTitle();
        titleBar->title->setText(name);
    }
}

