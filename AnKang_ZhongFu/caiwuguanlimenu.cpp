#include "caiwuguanlimenu.h"
#include "mainwindow.h"

extern QString quanxian;
extern mainTitle   *titleBar;

caiwuguanliMenu::caiwuguanliMenu(MainWindow *main_w,QWidget *parent) :
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
    label->setPixmap(QPixmap(QString(":/menupic/caiwuguanlilabel.png")));
    label->setGeometry(60,10,160,40);

    Btn1 = new QPushButton(this);
    Btn1->setObjectName(QString("Btn1"));
    Btn1->setHidden(true);
    if(quanxian.contains("砼发货明细")){
        Btn1->setHidden(false);
        BtnList.append(Btn1);
    }


    Btn2 = new QPushButton(this);
    Btn2->setObjectName(QString("Btn2"));
    Btn2->setHidden(true);
    if(quanxian.contains("采购入库明细")){
        Btn2->setHidden(false);
        BtnList.append(Btn2);
    }

    Btn3 = new QPushButton(this);
    Btn3->setObjectName(QString("Btn3"));
    Btn3->setHidden(true);
    if(quanxian.contains("销售总账")){
        Btn3->setHidden(false);
        BtnList.append(Btn3);
    }

    Btn4 = new QPushButton(this);
    Btn4->setObjectName(QString("Btn4"));
    Btn4->setHidden(true);
    if(quanxian.contains("采购总账")){
        Btn4->setHidden(false);
        BtnList.append(Btn4);
    }


//    Btn5 = new QPushButton(this);
//    Btn5->setObjectName(QString("Btn5"));
//    Btn5->setHidden(true);
//    if(quanxian.contains("车辆费用付款")){
//        Btn5->setHidden(false);
//        BtnList.append(Btn5);
//    }


//    Btn6 = new QPushButton(this);
//    Btn6->setObjectName(QString("Btn6"));
//    Btn6->setHidden(true);
//    if(quanxian.contains("其他费用设置")){
//        Btn6->setHidden(false);
//        BtnList.append(Btn6);
//    }


//    Btn7 = new QPushButton(this);
//    Btn7->setObjectName(QString("Btn7"));
//    Btn7->setHidden(true);
//    if(quanxian.contains("其他费用付款")){
//        Btn7->setHidden(false);
//        BtnList.append(Btn7);
//    }


//    Btn8 = new QPushButton(this);
//    Btn8->setObjectName(QString("Btn8"));
//    Btn8->setHidden(true);
//    if(quanxian.contains("辅材付款")){
//        Btn8->setHidden(false);
//        BtnList.append(Btn8);
//    }


//    Btn9 = new QPushButton(this);
//    Btn9->setObjectName(QString("Btn9"));
//    Btn9->setHidden(true);
//    if(quanxian.contains("账号设置")){
//        Btn9->setHidden(false);
//        BtnList.append(Btn9);
//    }


//    Btn10 = new QPushButton(this);
//    Btn10->setObjectName(QString("Btn10"));
//    Btn10->setHidden(true);
//    if(quanxian.contains("原料消耗价格调整")){
//        Btn10->setHidden(false);
//        BtnList.append(Btn10);
//    }


//    Btn11 = new QPushButton(this);
//    Btn11->setObjectName(QString("Btn11"));
//    Btn11->setHidden(true);
//    if(quanxian.contains("账期管理")){
//        Btn11->setHidden(false);
//        BtnList.append(Btn11);
//    }

    Btn12 = new QPushButton(this);
    Btn12->setObjectName(QString("Btn12"));
    Btn12->setHidden(true);
    if(quanxian.contains("发货价格批量调整")){
        Btn12->setHidden(false);
        BtnList.append(Btn12);
    }

    Btn13 = new QPushButton(this);
    Btn13->setObjectName(QString("Btn13"));
    Btn13->setHidden(true);
    if(quanxian.contains("发货数据调整")){
        Btn13->setHidden(false);
        BtnList.append(Btn13);
    }

//    Btn14 = new QPushButton(this);
//    Btn14->setObjectName(QString("Btn14"));
//    Btn14->setHidden(true);
//    if(quanxian.contains("销售结算")){
//        Btn14->setHidden(false);
//        BtnList.append(Btn14);
//    }

    Btn15 = new QPushButton(this);
    Btn15->setObjectName(QString("Btn15"));
    Btn15->setHidden(true);
    if(quanxian.contains("原料入库数据调整")){
        Btn15->setHidden(false);
        BtnList.append(Btn15);
    }

    Btn16 = new QPushButton(this);
    Btn16->setObjectName(QString("Btn16"));
    Btn16->setHidden(true);
    if(quanxian.contains("供货对账单")){
        Btn16->setHidden(true);
        BtnList.append(Btn16);
    }

    Btn1->setFixedSize(120,120);
    Btn2->setFixedSize(120,120);
    Btn3->setFixedSize(120,120);
    Btn4->setFixedSize(120,120);
//    Btn5->setFixedSize(120,120);
//    Btn6->setFixedSize(120,120);
//    Btn7->setFixedSize(120,120);
//    Btn8->setFixedSize(120,120);
//    Btn9->setFixedSize(120,120);
//    Btn10->setFixedSize(120,120);
//    Btn11->setFixedSize(120,120);
    Btn12->setFixedSize(120,120);
    Btn13->setFixedSize(120,120);
//    Btn14->setFixedSize(120,120);
    Btn15->setFixedSize(120,120);
    Btn16->setFixedSize(120,120);

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
                        "QToolButton[objectName=\"toolBtn\"]{border:0px;background-image:url(:/menupic/fanhuijiantou8.png);}"
                        "QToolButton[objectName=\"toolBtn\"]:hover{background-image:url(:/menupic/hoverfanhuijiantou8.png);}"
                        "QToolButton[objectName=\"toolBtn\"]:pressed{background-image:url(:/menupic/pressedfanhuijiantou8.png);}"

                        "QPushButton[objectName=\"Btn1\"]{border:0px;background-image:url(:/menupic/tongfahuomingxihedui.png)}"
                        "QPushButton[objectName=\"Btn1\"]:hover{border:1px solid white;background-image:url(:/menupic/tongfahuomingxihedui.png)}"
                        "QPushButton[objectName=\"Btn1\"]:pressed{border:2px solid white;background-image:url(:/menupic/tongfahuomingxihedui.png)}"

                        "QPushButton[objectName=\"Btn2\"]{border:0px;background-image:url(:/menupic/caigourukumingxihedui.png)}"
                        "QPushButton[objectName=\"Btn2\"]:hover{border:1px solid white;background-image:url(:/menupic/caigourukumingxihedui.png)}"
                        "QPushButton[objectName=\"Btn2\"]:pressed{border:2px solid white;background-image:url(:/menupic/caigourukumingxihedui.png)}"

                        "QPushButton[objectName=\"Btn3\"]{border:0px;background-image:url(:/menupic/xiaoshouzongzhangbtn.png)}"
                        "QPushButton[objectName=\"Btn3\"]:hover{border:1px solid white;background-image:url(:/menupic/xiaoshouzongzhangbtn.png)}"
                        "QPushButton[objectName=\"Btn3\"]:pressed{border:2px solid white;background-image:url(:/menupic/xiaoshouzongzhangbtn.png)}"


                        "QPushButton[objectName=\"Btn4\"]{border:0px;background-image:url(:/menupic/caigouzongzhangbtn.png)}"
                        "QPushButton[objectName=\"Btn4\"]:hover{border:1px solid white;background-image:url(:/menupic/caigouzongzhangbtn.png)}"
                        "QPushButton[objectName=\"Btn4\"]:pressed{border:2px solid white;background-image:url(:/menupic/caigouzongzhangbtn.png)}"


                        "QPushButton[objectName=\"Btn12\"]{border:0px;background-image:url(:/menupic/fahuojiagepiliangtiaozhengbtn.png)}"
                        "QPushButton[objectName=\"Btn12\"]:hover{border:1px solid white;background-image:url(:/menupic/fahuojiagepiliangtiaozhengbtn.png)}"
                        "QPushButton[objectName=\"Btn12\"]:pressed{border:2px solid white;background-image:url(:/menupic/fahuojiagepiliangtiaozhengbtn.png)}"

                        "QPushButton[objectName=\"Btn13\"]{border:0px;background-image:url(:/menupic/fahuoshujutiaozheng.png)}"
                        "QPushButton[objectName=\"Btn13\"]:hover{border:1px solid white;background-image:url(:/menupic/fahuoshujutiaozheng.png)}"
                        "QPushButton[objectName=\"Btn13\"]:pressed{border:2px solid white;background-image:url(:/menupic/fahuoshujutiaozheng.png)}"

                        "QPushButton[objectName=\"Btn15\"]{border:0px;background-image:url(:/menupic/shujutiaozhengbtn.png)}"
                        "QPushButton[objectName=\"Btn15\"]:hover{border:1px solid white;background-image:url(:/menupic/shujutiaozhengbtn.png)}"
                        "QPushButton[objectName=\"Btn15\"]:pressed{border:2px solid white;background-image:url(:/menupic/shujutiaozhengbtn.png)}"

                        "QPushButton[objectName=\"Btn16\"]{border:0px;background-image:url(:/menupic/caigoujiesuan.png)}"
                        "QPushButton[objectName=\"Btn16\"]:hover{border:1px solid white;background-image:url(:/menupic/caigoujiesuan.png)}"
                        "QPushButton[objectName=\"Btn16\"]:pressed{border:2px solid white;background-image:url(:/menupic/caigoujiesuan.png)}"
                      );

}

void caiwuguanliMenu::paintEvent(QPaintEvent *event)
{
    scrollArea->setGeometry(140,60,600,this->height()-70);
    event->accept();
}

void caiwuguanliMenu::keyPressEvent(QKeyEvent *event)
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

void caiwuguanliMenu::on_close()
{
    this->main_w->mdiArea->closeActiveSubWindow();
    if(this->main_w->mdiArea->subWindowList().size() != 0){
        QString name = this->main_w->mdiArea->activeSubWindow()->windowTitle();
        titleBar->title->setText(name);
    }
}
