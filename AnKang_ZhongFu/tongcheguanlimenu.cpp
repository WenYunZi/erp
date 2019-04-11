#include "tongcheguanlimenu.h"
#include "mainwindow.h"

extern QString quanxian;
extern mainTitle   *titleBar;

tongcheguanliMenu::tongcheguanliMenu(MainWindow *main_w,QWidget *parent) :
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
    label->setPixmap(QPixmap(QString(":/menupic/tongcheguanlilabel.png")));
    label->setGeometry(60,10,160,40);

    Btn1 = new QPushButton(this);
    Btn1->setObjectName(QString("Btn1"));
    BtnList.append(Btn1);
    if(!quanxian.contains("砼车司机")){
        Btn1->setHidden(true);

    }

    Btn2 = new QPushButton(this);
    Btn2->setObjectName(QString("Btn2"));
    BtnList.append(Btn2);
    if(!quanxian.contains("砼车信息")){
        Btn2->setHidden(true);

    }

    Btn5 = new QPushButton(this);
    Btn5->setObjectName(QString("Btn5"));
    BtnList.append(Btn5);
    if(!quanxian.contains("运费设置")){
        Btn5->setHidden(true);

    }

    Btn6 = new QPushButton(this);
    Btn6->setObjectName(QString("Btn6"));
    BtnList.append(Btn6);
    if(!quanxian.contains("工程运距确认")){
        Btn6->setHidden(true);

    }

    //add liwenxiu 2017-11-2
    Btn7 = new QPushButton(this);
    Btn7->setObjectName(QString("Btn7"));
    BtnList.append(Btn7);
//    if(!quanxian.contains("车辆维修费用")){
//      Btn7->setHidden(true);

//    }

    Btn1->setFixedSize(120,120);
    Btn2->setFixedSize(120,120);
    Btn5->setFixedSize(120,120);
    Btn6->setFixedSize(120,120);
    //add liwenxiu 2017-11-2
    Btn7->setFixedSize(120,120);
     //end liwenxiu 2017-11-2

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(Btn1);
    layout->addWidget(Btn2);
    layout->addWidget(Btn5);
    layout->addWidget(Btn6);
    layout->addWidget(Btn7);

    layout->setMargin(0);//设置窗体左右边距

    QWidget *widget = new QWidget;
    widget->setObjectName(QString("scrollwidget"));
    widget->setLayout(layout);

    scrollArea = new QScrollArea(this);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setWidget(widget);

    this->setStyleSheet("QScrollArea{border: 0px}"
                        "QToolButton[objectName=\"toolBtn\"]{border:0px;background-image:url(:/menupic/fanhuijiantou10.png);}"
                        "QToolButton[objectName=\"toolBtn\"]:hover{background-image:url(:/menupic/hoverfanhuijiantou10.png);}"
                        "QToolButton[objectName=\"toolBtn\"]:pressed{background-image:url(:/menupic/pressedfanhuijiantou10.png);}"

                        "QPushButton[objectName=\"Btn1\"]{border:0px;background-image:url(:/menupic/tongchesijibtn.png)}"
                        "QPushButton[objectName=\"Btn1\"]:hover{border:1px solid white;background-image:url(:/menupic/tongchesijibtn.png)}"
                        "QPushButton[objectName=\"Btn1\"]:pressed{border:2px solid white;background-image:url(:/menupic/tongchesijibtn.png)}"

                        "QPushButton[objectName=\"Btn2\"]{border:0px;background-image:url(:/menupic/tongchexinxibtn.png)}"
                        "QPushButton[objectName=\"Btn2\"]:hover{border:1px solid white;background-image:url(:/menupic/tongchexinxibtn.png)}"
                        "QPushButton[objectName=\"Btn2\"]:pressed{border:2px solid white;background-image:url(:/menupic/tongchexinxibtn.png)}"

                        "QPushButton[objectName=\"Btn5\"]{border:0px;background-image:url(:/menupic/yunfeishezhibtn.png)}"
                        "QPushButton[objectName=\"Btn5\"]:hover{border:1px solid white;background-image:url(:/menupic/yunfeishezhibtn.png)}"
                        "QPushButton[objectName=\"Btn5\"]:pressed{border:2px solid white;background-image:url(:/menupic/yunfeishezhibtn.png)}"

                        "QPushButton[objectName=\"Btn6\"]{border:0px;background-image:url(:/menupic/gongchengyunjuquerenbtn.png)}"
                        "QPushButton[objectName=\"Btn6\"]:hover{border:1px solid white;background-image:url(:/menupic/gongchengyunjuquerenbtn.png)}"
                        "QPushButton[objectName=\"Btn6\"]:pressed{border:2px solid white;background-image:url(:/menupic/gongchengyunjuquerenbtn.png)}"

                        "QPushButton[objectName=\"Btn7\"]{border:0px;background-image:url(:/menupic/cheliangweixiufeiyong.png)}"
                        "QPushButton[objectName=\"Btn7\"]:hover{border:1px solid white;background-image:url(:/menupic/cheliangweixiufeiyong.png)}"
                        "QPushButton[objectName=\"Btn7\"]:pressed{border:2px solid white;background-image:url(:/menupic/cheliangweixiufeiyong.png)}");

}

void tongcheguanliMenu::paintEvent(QPaintEvent *event)
{
    scrollArea->setGeometry(140,60,252,this->height()-70);
    event->accept();
}

void tongcheguanliMenu::keyPressEvent(QKeyEvent *event)
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

void tongcheguanliMenu::on_close()
{
    this->main_w->mdiArea->closeActiveSubWindow();
    if(this->main_w->mdiArea->subWindowList().size() != 0){
        QString name = this->main_w->mdiArea->activeSubWindow()->windowTitle();
        titleBar->title->setText(name);
    }
}
