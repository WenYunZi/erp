#include "xitongshezhimenu.h"
#include "mainwindow.h"

extern QString quanxian;
extern mainTitle   *titleBar;

xitongshezhiMenu::xitongshezhiMenu(MainWindow *main_w,QWidget *parent) :
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
    label->setPixmap(QPixmap(QString(":/menupic/xitongshezhilabel.png")));
    label->setGeometry(60,10,160,40);

    Btn1 = new QPushButton(this);
    Btn1->setObjectName(QString("Btn1"));
    Btn1->setHidden(true);
    if(quanxian.contains("厂地设置")){
        Btn1->setHidden(false);
        BtnList.append(Btn1);
    }

    Btn2 = new QPushButton(this);
    Btn2->setObjectName(QString("Btn2"));
    Btn2->setHidden(true);
    if(quanxian.contains("部门设置")){
        Btn2->setHidden(false);
        BtnList.append(Btn2);
    }


    Btn3 = new QPushButton(this);
    Btn3->setObjectName(QString("Btn3"));
    Btn3->setHidden(true);
    if(quanxian.contains("原料设置")){
        Btn3->setHidden(false);
        BtnList.append(Btn3);
    }


    Btn4 = new QPushButton(this);
    Btn4->setObjectName(QString("Btn4"));
    Btn4->setHidden(true);
    if(quanxian.contains("仓位设置")){
        Btn4->setHidden(false);
        BtnList.append(Btn4);
    }


    Btn5 = new QPushButton(this);
    Btn5->setObjectName(QString("Btn5"));
    Btn5->setHidden(true);
    if(quanxian.contains("产品设置")){
        Btn5->setHidden(false);
        BtnList.append(Btn5);
    }


    Btn6 = new QPushButton(this);
    Btn6->setObjectName(QString("Btn6"));
    Btn6->setHidden(true);
    if(quanxian.contains("属性设置")){
        Btn6->setHidden(false);
        BtnList.append(Btn6);
    }


    Btn7 = new QPushButton(this);
    Btn7->setObjectName(QString("Btn7"));
    Btn7->setHidden(true);
    if(quanxian.contains("用户管理")){
        Btn7->setHidden(false);
        BtnList.append(Btn7);
    }


    Btn8 = new QPushButton(this);
    Btn8->setObjectName(QString("Btn8"));
    Btn8->setHidden(true);
    if(quanxian.contains("权限管理")){
        Btn8->setHidden(false);
        BtnList.append(Btn8);
    }


    Btn9 = new QPushButton(this);
    Btn9->setObjectName(QString("Btn9"));
    Btn9->setHidden(true);
    if(quanxian.contains("密码修改")){
        Btn9->setHidden(false);
        BtnList.append(Btn9);
    }

    //add liwenxiu 2017-10-27
    Btn12 = new QPushButton(this);
    Btn12->setObjectName(QString("Btn12"));
    Btn12->setHidden(true);
//    if(quanxian.contains("基本参数设置")){
        Btn12->setHidden(false);
        BtnList.append(Btn12);
//    }
    //end liwenxiu 2017-10-27

    Btn1->setFixedSize(120,120);
    Btn2->setFixedSize(120,120);
    Btn3->setFixedSize(120,120);
    Btn4->setFixedSize(120,120);
    Btn5->setFixedSize(120,120);
    Btn6->setFixedSize(120,120);
    Btn7->setFixedSize(120,120);
    Btn8->setFixedSize(120,120);
    Btn9->setFixedSize(120,120);

    //add liwenxiu 2017-10-27
    Btn12->setFixedSize(120,120);
    //end liwenxiu 2017-10-27

    QGridLayout *layout = new QGridLayout(this);
    for(int i = 0; i<BtnList.count(); i++){
        layout->addWidget(BtnList[i],i%6,i/6);
    }

    layout->setMargin(0);

    QWidget *widget = new QWidget(this);
    widget->setObjectName(QString("scrollwidget"));
    widget->setLayout(layout);

    scrollArea = new QScrollArea(this);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setWidget(widget);

    this->setStyleSheet("QScrollArea{border: 0px}"
                        "QToolButton[objectName=\"toolBtn\"]{border:0px;background-image:url(:/menupic/fanhuijiantou15.png);}"
                        "QToolButton[objectName=\"toolBtn\"]:hover{background-image:url(:/menupic/hoverfanhuijiantou15.png);}"
                        "QToolButton[objectName=\"toolBtn\"]:pressed{background-image:url(:/menupic/pressedfanhuijiantou15.png);}"

                        "QPushButton[objectName=\"Btn1\"]{border:0px;background-image:url(:/menupic/changdishezhibtn.png)}"
                        "QPushButton[objectName=\"Btn1\"]:hover{border:1px solid white;background-image:url(:/menupic/changdishezhibtn.png)}"
                        "QPushButton[objectName=\"Btn1\"]:pressed{border:2px solid white;background-image:url(:/menupic/changdishezhibtn.png)}"

                        "QPushButton[objectName=\"Btn2\"]{border:0px;background-image:url(:/menupic/bumenshezhibtn.png)}"
                        "QPushButton[objectName=\"Btn2\"]:hover{border:1px solid white;background-image:url(:/menupic/bumenshezhibtn.png)}"
                        "QPushButton[objectName=\"Btn2\"]:pressed{border:2px solid white;background-image:url(:/menupic/bumenshezhibtn.png)}"

                        "QPushButton[objectName=\"Btn3\"]{border:0px;background-image:url(:/menupic/yuanliaoshezhibtn.png)}"
                        "QPushButton[objectName=\"Btn3\"]:hover{border:1px solid white;background-image:url(:/menupic/yuanliaoshezhibtn.png)}"
                        "QPushButton[objectName=\"Btn3\"]:pressed{border:2px solid white;background-image:url(:/menupic/yuanliaoshezhibtn.png)}"

                        "QPushButton[objectName=\"Btn4\"]{border:0px;background-image:url(:/menupic/cangweishezhibtn.png)}"
                        "QPushButton[objectName=\"Btn4\"]:hover{border:1px solid white;background-image:url(:/menupic/cangweishezhibtn.png)}"
                        "QPushButton[objectName=\"Btn4\"]:pressed{border:2px solid white;background-image:url(:/menupic/cangweishezhibtn.png)}"

                        "QPushButton[objectName=\"Btn5\"]{border:0px;background-image:url(:/menupic/chanpinshezhibtn.png)}"
                        "QPushButton[objectName=\"Btn5\"]:hover{border:1px solid white;background-image:url(:/menupic/chanpinshezhibtn.png)}"
                        "QPushButton[objectName=\"Btn5\"]:pressed{border:2px solid white;background-image:url(:/menupic/chanpinshezhibtn.png)}"

                        "QPushButton[objectName=\"Btn6\"]{border:0px;background-image:url(:/menupic/shuxingshezhibtn.png)}"
                        "QPushButton[objectName=\"Btn6\"]:hover{border:1px solid white;background-image:url(:/menupic/shuxingshezhibtn.png)}"
                        "QPushButton[objectName=\"Btn6\"]:pressed{border:2px solid white;background-image:url(:/menupic/shuxingshezhibtn.png)}"

                        "QPushButton[objectName=\"Btn7\"]{border:0px;background-image:url(:/menupic/yonghuguanlibtn.png)}"
                        "QPushButton[objectName=\"Btn7\"]:hover{border:1px solid white;background-image:url(:/menupic/yonghuguanlibtn.png)}"
                        "QPushButton[objectName=\"Btn7\"]:pressed{border:2px solid white;background-image:url(:/menupic/yonghuguanlibtn.png)}"

                        "QPushButton[objectName=\"Btn8\"]{border:0px;background-image:url(:/menupic/quanxianguanlibtn.png)}"
                        "QPushButton[objectName=\"Btn8\"]:hover{border:1px solid white;background-image:url(:/menupic/quanxianguanlibtn.png)}"
                        "QPushButton[objectName=\"Btn8\"]:pressed{border:2px solid white;background-image:url(:/menupic/quanxianguanlibtn.png)}"

                        "QPushButton[objectName=\"Btn9\"]{border:0px;background-image:url(:/menupic/mimaxiugaibtn.png)}"
                        "QPushButton[objectName=\"Btn9\"]:hover{border:1px solid white;background-image:url(:/menupic/mimaxiugaibtn.png)}"
                        "QPushButton[objectName=\"Btn9\"]:pressed{border:2px solid white;background-image:url(:/menupic/mimaxiugaibtn.png)}"

                        "QPushButton[objectName=\"Btn12\"]{border:0px;background-image:url(:/menupic/jibencanshushezhi.png)}"
                        "QPushButton[objectName=\"Btn12\"]:hover{border:1px solid white;background-image:url(:/menupic/jibencanshushezhi.png)}"
                        "QPushButton[objectName=\"Btn12\"]:pressed{border:2px solid white;background-image:url(:/menupic/jibencanshushezhi.png)}");

}

void xitongshezhiMenu::paintEvent(QPaintEvent *event)
{
    scrollArea->setGeometry(140,60,252,this->height()-70);
    event->accept();
}

void xitongshezhiMenu::keyPressEvent(QKeyEvent *event)
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

void xitongshezhiMenu::on_close()
{
    this->main_w->mdiArea->closeActiveSubWindow();
    if(this->main_w->mdiArea->subWindowList().size() != 0){
        QString name = this->main_w->mdiArea->activeSubWindow()->windowTitle();
        titleBar->title->setText(name);
    }
}
