#include "shiyanshiguanlimenu.h"
#include "mainwindow.h"

extern QString quanxian;
extern mainTitle   *titleBar;

shiyanshiguanliMenu::shiyanshiguanliMenu(MainWindow *main_w,QWidget *parent) :
    QWidget(parent)
{
    this->main_w = main_w;
    toolBtn = new QToolButton(this);
    connect(toolBtn,SIGNAL(clicked()),this,SLOT(on_close()));
    toolBtn->setObjectName(QString("toolBtn"));
    toolBtn->setFixedSize(40,40);
    toolBtn->setGeometry(10,10,50,50);

    label = new QLabel(this);
    label->setFixedSize(200,40);
    label->setPixmap(QPixmap(QString(":/menupic/shiyanshiguanlilabel.png")));
    label->setGeometry(60,10,200,40);

    Btn1 = new QPushButton(this);
    Btn1->setObjectName(QString("Btn1"));
    if(!quanxian.contains("配合比模板维护")){
        Btn1->setHidden(true);
    }

    Btn3 = new QPushButton(this);
    Btn3->setObjectName(QString("Btn3"));
    if(!quanxian.contains("配合比通知单")){
        Btn3->setHidden(true);
    }

    Btn1->setFixedSize(120,120);
    Btn3->setFixedSize(120,120);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(Btn1);
    vlayout->addWidget(Btn3);

    vlayout->setMargin(0);

    QWidget *widget = new QWidget;
    widget->setObjectName(QString("scrollwidget"));
    widget->setLayout(vlayout);

    scrollArea = new QScrollArea(this);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setWidget(widget);

    this->setStyleSheet("QScrollArea{border: 0px}"
                        "QToolButton[objectName=\"toolBtn\"]{border:0px;background-image:url(:/menupic/fanhuijiantou6.png);}"
                        "QToolButton[objectName=\"toolBtn\"]:hover{background-image:url(:/menupic/hoverfanhuijiantou6.png);}"
                        "QToolButton[objectName=\"toolBtn\"]:pressed{background-image:url(:/menupic/pressedfanhuijiantou6.png);}"

                        "QPushButton[objectName=\"Btn1\"]{border:0px;background-image:url(:/menupic/peihebimubanweihubtn.png)}"
                        "QPushButton[objectName=\"Btn1\"]:hover{border:1px solid white;background-image:url(:/menupic/peihebimubanweihubtn.png)}"
                        "QPushButton[objectName=\"Btn1\"]:pressed{border:2px solid white;background-image:url(:/menupic/peihebimubanweihubtn.png)}"

                        "QPushButton[objectName=\"Btn3\"]{border:0px;background-image:url(:/menupic/peihebitongzhidanbtn.png)}"
                        "QPushButton[objectName=\"Btn3\"]:hover{border:1px solid white;background-image:url(:/menupic/peihebitongzhidanbtn.png)}"
                        "QPushButton[objectName=\"Btn3\"]:pressed{border:2px solid white;background-image:url(:/menupic/peihebitongzhidanbtn.png)}");

}

void shiyanshiguanliMenu::paintEvent(QPaintEvent *event)
{
    scrollArea->setGeometry(140,60,122,this->height()-70);
    event->accept();
}

void shiyanshiguanliMenu::keyPressEvent(QKeyEvent *event)
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

void shiyanshiguanliMenu::on_close()
{
    this->main_w->mdiArea->closeActiveSubWindow();
    if(this->main_w->mdiArea->subWindowList().size() != 0){
        QString name = this->main_w->mdiArea->activeSubWindow()->windowTitle();
        titleBar->title->setText(name);
    }
}

