#include "baobiaochaxunmenu.h"
#include "mainwindow.h"

extern QString quanxian;
extern mainTitle   *titleBar;

baobiaochaxunMenu::baobiaochaxunMenu(MainWindow *main_w,QWidget *parent) :
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
    label->setPixmap(QPixmap(QString(":/menupic/baobiaochaxunlabel.png")));
    label->setGeometry(60,10,160,40);

    Btn1 = new QPushButton(this);
    Btn1->setObjectName(QString("Btn1"));
    Btn1->setHidden(true);
    if(quanxian.contains("采购明细表")){
        Btn1->setHidden(false);
        BtnList.append(Btn1);
    }


    Btn2 = new QPushButton(this);
    Btn2->setObjectName(QString("Btn2"));
    Btn2->setHidden(true);
    if(quanxian.contains("销售明细表")){
        Btn2->setHidden(false);
        BtnList.append(Btn2);
    }

    Btn4 = new QPushButton(this);
    Btn4->setObjectName(QString("Btn4"));
    Btn4->setHidden(true);
    if(quanxian.contains("生产消耗表")){
        Btn4->setHidden(false);
        BtnList.append(Btn4);
    }

    Btn5 = new QPushButton(this);
    Btn5->setObjectName(QString("Btn5"));
    Btn5->setHidden(true);
    if(quanxian.contains("车辆运输报表")){
        Btn5->setHidden(false);
        BtnList.append(Btn5);
    }


    Btn7 = new QPushButton(this);
    Btn7->setObjectName(QString("Btn7"));
    Btn7->setHidden(true);
    if(quanxian.contains("生产分布")){
        Btn7->setHidden(false);
        BtnList.append(Btn7);
    }

    Btnshengchanfangliangshengliao = new QPushButton(this);
    Btnshengchanfangliangshengliao->setObjectName(QString("Btnshengchanfangliangshengliao"));
    Btnshengchanfangliangshengliao->setHidden(true);
    if(quanxian.contains("生产方量省料")){
        Btnshengchanfangliangshengliao->setHidden(false);
        BtnList.append(Btnshengchanfangliangshengliao);
    }

    Btn1->setFixedSize(120,120);
    Btn2->setFixedSize(120,120);
    Btn4->setFixedSize(120,120);
    Btn5->setFixedSize(120,120);
    Btn7->setFixedSize(120,120);
    Btnshengchanfangliangshengliao->setFixedSize(120,120);

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
                        "QToolButton[objectName=\"toolBtn\"]{border:0px;background-image:url(:/menupic/fanhuijiantou9.png);}"
                        "QToolButton[objectName=\"toolBtn\"]:hover{background-image:url(:/menupic/hoverfanhuijiantou9.png);}"
                        "QToolButton[objectName=\"toolBtn\"]:pressed{background-image:url(:/menupic/pressedfanhuijiantou9.png);}"

                        "QPushButton[objectName=\"Btn1\"]{border:0px;background-image:url(:/menupic/caigoumingxibiaobtn.png)}"
                        "QPushButton[objectName=\"Btn1\"]:hover{border:1px solid white;background-image:url(:/menupic/caigoumingxibiaobtn.png)}"
                        "QPushButton[objectName=\"Btn1\"]:pressed{border:2px solid white;background-image:url(:/menupic/caigoumingxibiaobtn.png)}"

                        "QPushButton[objectName=\"Btn2\"]{border:0px;background-image:url(:/menupic/xiaoshoumingxibiaobtn.png)}"
                        "QPushButton[objectName=\"Btn2\"]:hover{border:1px solid white;background-image:url(:/menupic/xiaoshoumingxibiaobtn.png)}"
                        "QPushButton[objectName=\"Btn2\"]:pressed{border:2px solid white;background-image:url(:/menupic/xiaoshoumingxibiaobtn.png)}"

                        "QPushButton[objectName=\"Btn3\"]{border:0px;background-image:url(:/menupic/lilunxiaohaobiaobtn.png)}"
                        "QPushButton[objectName=\"Btn3\"]:hover{border:1px solid white;background-image:url(:/menupic/lilunxiaohaobiaobtn.png)}"
                        "QPushButton[objectName=\"Btn3\"]:pressed{border:2px solid white;background-image:url(:/menupic/lilunxiaohaobiaobtn.png)}"

                        "QPushButton[objectName=\"Btn4\"]{border:0px;background-image:url(:/menupic/shengchanxiaohaobiaobtn.png)}"
                        "QPushButton[objectName=\"Btn4\"]:hover{border:1px solid white;background-image:url(:/menupic/shengchanxiaohaobiaobtn.png)}"
                        "QPushButton[objectName=\"Btn4\"]:pressed{border:2px solid white;background-image:url(:/menupic/shengchanxiaohaobiaobtn.png)}"

                        "QPushButton[objectName=\"Btn5\"]{border:0px;background-image:url(:/menupic/cheliangyunshubaobiaobtn.png)}"
                        "QPushButton[objectName=\"Btn5\"]:hover{border:1px solid white;background-image:url(:/menupic/cheliangyunshubaobiaobtn.png)}"
                        "QPushButton[objectName=\"Btn5\"]:pressed{border:2px solid white;background-image:url(:/menupic/cheliangyunshubaobiaobtn.png)}"

                        "QPushButton[objectName=\"Btn6\"]{border:0px;background-image:url(:/menupic/fangliangchaxunbtn.png)}"
                        "QPushButton[objectName=\"Btn6\"]:hover{border:1px solid white;background-image:url(:/menupic/fangliangchaxunbtn.png)}"
                        "QPushButton[objectName=\"Btn6\"]:pressed{border:2px solid white;background-image:url(:/menupic/fangliangchaxunbtn.png)}"

                        "QPushButton[objectName=\"Btn7\"]{border:0px;background-image:url(:/menupic/shengchanfenbubtn.png)}"
                        "QPushButton[objectName=\"Btn7\"]:hover{border:1px solid white;background-image:url(:/menupic/shengchanfenbubtn.png)}"
                        "QPushButton[objectName=\"Btn7\"]:pressed{border:2px solid white;background-image:url(:/menupic/shengchanfenbubtn.png)}"

                        "QPushButton[objectName=\"Btnshengchanfangliangshengliao\"]{border:0px;background-image:url(:/menupic/shengchanfangliangshengliaoBtn.png)}"
                        "QPushButton[objectName=\"Btnshengchanfangliangshengliao\"]:hover{border:1px solid white;background-image:url(:/menupic/shengchanfangliangshengliaoBtn.png)}"
                        "QPushButton[objectName=\"Btnshengchanfangliangshengliao\"]:pressed{border:2px solid white;background-image:url(:/menupic/shengchanfangliangshengliaoBtn.png)}"

                        "QPushButton[objectName=\"Btn9\"]{border:0px;background-image:url(:/menupic/jiesuandanbtn.png)}"
                        "QPushButton[objectName=\"Btn9\"]:hover{border:1px solid white;background-image:url(:/menupic/jiesuandanbtn.png)}"
                        "QPushButton[objectName=\"Btn9\"]:pressed{border:2px solid white;background-image:url(:/menupic/jiesuandanbtn.png)}"

                        "QPushButton[objectName=\"Btn10\"]{border:0px;background-image:url(:/menupic/meipanxiaohaotongjibtn.png)}"
                        "QPushButton[objectName=\"Btn10\"]:hover{border:1px solid white;background-image:url(:/menupic/meipanxiaohaotongjibtn.png)}"
                        "QPushButton[objectName=\"Btn10\"]:pressed{border:2px solid white;background-image:url(:/menupic/meipanxiaohaotongjibtn.png)}");

}

void baobiaochaxunMenu::paintEvent(QPaintEvent *event)
{
    scrollArea->setGeometry(140,60,252,this->height()-70);
    event->accept();
}

void baobiaochaxunMenu::keyPressEvent(QKeyEvent *event)
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

void baobiaochaxunMenu::on_close()
{
    this->main_w->mdiArea->closeActiveSubWindow();
    if(this->main_w->mdiArea->subWindowList().size() != 0){
        QString name = this->main_w->mdiArea->activeSubWindow()->windowTitle();
        titleBar->title->setText(name);
    }
}
