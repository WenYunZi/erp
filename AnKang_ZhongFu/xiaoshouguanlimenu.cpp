#include "xiaoshouguanlimenu.h"
#include "mainwindow.h"

extern QString quanxian;
extern mainTitle   *titleBar;

xiaoshouguanliMenu::xiaoshouguanliMenu(MainWindow *main_w,QWidget *parent) :
    QWidget(parent)
{
    this->main_w = main_w;
    toolBtn = new QToolButton(this);
    connect(toolBtn,SIGNAL(clicked()),this,SLOT(on_close()));
    toolBtn->setObjectName(QString("toolBtn"));
    toolBtn->setFixedSize(40,40);
    toolBtn->setGeometry(10,10,50,50);

    label = new QLabel(this);
    label->setFixedSize(160,40);
    label->setPixmap(QPixmap(QString(":/menupic/xiaoshouguanlilabel.png")));
    label->setGeometry(60,10,160,40);

    Btn1 = new QPushButton(this);
    Btn1->setObjectName(QString("Btn1"));
    Btn1->setHidden(true);
    if(quanxian.contains("客户信息维护")){
        Btn1->setHidden(false);
        BtnList.append(Btn1);
    }

    Btn2 = new QPushButton(this);
    Btn2->setObjectName(QString("Btn2"));
    Btn2->setHidden(true);
    if(quanxian.contains("销售合同管理")){
        Btn2->setHidden(false);
        BtnList.append(Btn2);
    }

    Btn3 = new QPushButton(this);
    Btn3->setObjectName(QString("Btn3"));
    Btn3->setHidden(true);
    if(quanxian.contains("合同执行情况")){
        Btn3->setHidden(false);
        BtnList.append(Btn3);
    }

    Btn4 = new QPushButton(this);
    Btn4->setObjectName(QString("Btn4"));
    Btn4->setHidden(true);
    if(quanxian.contains("销售收款条件")){
        Btn4->setHidden(false);
        BtnList.append(Btn4);
    }

    Btn5 = new QPushButton(this);
    Btn5->setObjectName(QString("Btn5"));
    Btn5->setHidden(true);
    if(quanxian.contains("生产预警")){
        Btn5->setHidden(false);
        BtnList.append(Btn5);
    }

    Btn1->setFixedSize(120,120);
    Btn2->setFixedSize(120,120);
    Btn3->setFixedSize(120,120);
    Btn4->setFixedSize(120,120);
    Btn5->setFixedSize(120,120);

    QGridLayout *layout = new QGridLayout(this);
    for(int i = 0; i<BtnList.count(); i++){
        layout->addWidget(BtnList[i],i%6,i/6);
    }
    layout->setMargin(0);

    QWidget *widget = new QWidget;
    widget->setObjectName(QString("scrollwidget"));
    widget->setLayout(layout);

    scrollArea = new QScrollArea(this);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setWidget(widget);

    this->setStyleSheet("QScrollArea{border: 0px}"
                        "QToolButton[objectName=\"toolBtn\"]{border:0px;background-image:url(:/menupic/fanhuijiantou4.png);}"
                        "QToolButton[objectName=\"toolBtn\"]:hover{background-image:url(:/menupic/hoverfanhuijiantou4.png);}"
                        "QToolButton[objectName=\"toolBtn\"]:pressed{background-image:url(:/menupic/pressedfanhuijiantou4.png);}"

                        "QPushButton[objectName=\"Btn1\"]{border:0px;background-image:url(:/menupic/kehudanganbtn.png)}"
                        "QPushButton[objectName=\"Btn1\"]:hover{border:1px solid white;background-image:url(:/menupic/kehudanganbtn.png)}"
                        "QPushButton[objectName=\"Btn1\"]:pressed{border:2px solid white;background-image:url(:/menupic/kehudanganbtn.png)}"

                        "QPushButton[objectName=\"Btn2\"]{border:0px;background-image:url(:/menupic/xiaoshouhetongguanlibtn.png)}"
                        "QPushButton[objectName=\"Btn2\"]:hover{border:1px solid white;background-image:url(:/menupic/xiaoshouhetongguanlibtn.png)}"
                        "QPushButton[objectName=\"Btn2\"]:pressed{border:2px solid white;background-image:url(:/menupic/xiaoshouhetongguanlibtn.png)}"

                        "QPushButton[objectName=\"Btn3\"]{border:0px;background-image:url(:/menupic/hetongzhixingqingkuangbtn.png)}"
                        "QPushButton[objectName=\"Btn3\"]:hover{border:1px solid white;background-image:url(:/menupic/hetongzhixingqingkuangbtn.png)}"
                        "QPushButton[objectName=\"Btn3\"]:pressed{border:2px solid white;background-image:url(:/menupic/hetongzhixingqingkuangbtn.png)}"

                        "QPushButton[objectName=\"Btn4\"]{border:0px;background-image:url(:/menupic/xiaoshoushoukuantiaojianbtn.png)}"
                        "QPushButton[objectName=\"Btn4\"]:hover{border:1px solid white;background-image:url(:/menupic/xiaoshoushoukuantiaojianbtn.png)}"
                        "QPushButton[objectName=\"Btn4\"]:pressed{border:2px solid white;background-image:url(:/menupic/xiaoshoushoukuantiaojianbtn.png)}"

                        "QPushButton[objectName=\"Btn5\"]{border:0px;background-image:url(:/menupic/shengchanyujingbtn.png)}"
                        "QPushButton[objectName=\"Btn5\"]:hover{border:1px solid white;background-image:url(:/menupic/shengchanyujingbtn.png)}"
                        "QPushButton[objectName=\"Btn5\"]:pressed{border:2px solid white;background-image:url(:/menupic/shengchanyujingbtn.png)}");

}

void xiaoshouguanliMenu::paintEvent(QPaintEvent *event)
{
    scrollArea->setGeometry(140,60,252,this->height()-70);
    event->accept();
}

void xiaoshouguanliMenu::keyPressEvent(QKeyEvent *event)
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

void xiaoshouguanliMenu::on_close()
{
    this->main_w->mdiArea->closeActiveSubWindow();
    if(this->main_w->mdiArea->subWindowList().size() != 0){
        QString name = this->main_w->mdiArea->activeSubWindow()->windowTitle();
        titleBar->title->setText(name);
    }
}
