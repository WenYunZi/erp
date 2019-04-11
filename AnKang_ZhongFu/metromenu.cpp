#include "metromenu.h"

extern QString quanxian;

MetroMenu::MetroMenu(QWidget *parent) :
    QWidget(parent)
{
    this->setObjectName(QString("widget"));

    Btn1 = new QPushButton(this);
    Btn1->setObjectName(QString("Btn1"));
    if(!quanxian.contains("采购管理菜单")){
        Btn1->setHidden(true);
    }

    Btn2 = new QPushButton(this);
    Btn2->setObjectName(QString("Btn2"));
    if(!quanxian.contains("原料管理菜单")){
        Btn2->setHidden(true);
    }

    Btn3 = new QPushButton(this);
    Btn3->setObjectName(QString("Btn3"));
    if(!quanxian.contains("辅材管理菜单")){
        Btn3->setHidden(true);
    }

    Btn4 = new QPushButton(this);
    Btn4->setObjectName(QString("Btn4"));
    if(!quanxian.contains("磅房管理菜单")){
        Btn4->setHidden(true);
    }

    Btn5 = new QPushButton(this);
    Btn5->setObjectName(QString("Btn5"));
    if(!quanxian.contains("销售管理菜单")){
        Btn5->setHidden(true);
    }

    Btn6 = new QPushButton(this);
    Btn6->setObjectName(QString("Btn6"));
    if(!quanxian.contains("调度管理菜单")){
        Btn6->setHidden(true);
    }

    Btn7 = new QPushButton(this);
    Btn7->setObjectName(QString("Btn7"));
    if(!quanxian.contains("实验室管理菜单")){
        Btn7->setHidden(true);
    }

    Btn8 = new QPushButton(this);
    Btn8->setObjectName(QString("Btn8"));
    if(!quanxian.contains("生产管理菜单")){
        Btn8->setHidden(true);
    }

    Btn9 = new QPushButton(this);
    Btn9->setObjectName(QString("Btn9"));
    if(!quanxian.contains("财务管理菜单")){
        Btn9->setHidden(true);
    }

    Btn10 = new QPushButton(this);
    Btn10->setObjectName(QString("Btn10"));
    if(!quanxian.contains("报表查询菜单")){
        Btn10->setHidden(true);
    }

    Btn11 = new QPushButton(this);
    Btn11->setObjectName(QString("Btn11"));
    if(!quanxian.contains("砼车管理菜单")){
        Btn11->setHidden(true);
    }

    Btn12 = new QPushButton(this);
    Btn12->setObjectName(QString("Btn12"));
    if(!quanxian.contains("泵车管理菜单")){
        Btn12->setHidden(true);
    }

    Btn16 = new QPushButton(this);
    Btn16->setObjectName(QString("Btn16"));
    if(!quanxian.contains("系统设置菜单")){
        Btn16->setHidden(true);
    }

    Btn17 = new QPushButton(this);
    Btn17->setObjectName(QString("Btn17"));

    Btn18 = new QPushButton(this);
    Btn18->setObjectName(QString("Btn18"));

    Btn1->setFixedSize(230,130);
    Btn2->setFixedSize(230,130);
    Btn3->setFixedSize(230,130);
    Btn4->setFixedSize(230,130);
    Btn5->setFixedSize(230,130);
    Btn6->setFixedSize(230,130);
    Btn7->setFixedSize(230,130);
    Btn8->setFixedSize(230,130);
    Btn9->setFixedSize(230,130);
    Btn10->setFixedSize(230,130);
    Btn11->setFixedSize(230,130);
    Btn12->setFixedSize(230,130);
    Btn16->setFixedSize(230,130);
    Btn17->setFixedSize(230,130);
    Btn18->setFixedSize(230,130);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(Btn1);
    vlayout->addWidget(Btn2);
    vlayout->addWidget(Btn3);
    vlayout->addWidget(Btn4);
    vlayout->addWidget(Btn5);
    vlayout->addWidget(Btn6);
    vlayout->addWidget(Btn7);
    vlayout->addWidget(Btn8);
    vlayout->addWidget(Btn9);
    vlayout->addWidget(Btn10);
    vlayout->addWidget(Btn11);
    vlayout->addWidget(Btn12);
    vlayout->addWidget(Btn16);
    vlayout->addWidget(Btn17);
    vlayout->addWidget(Btn18);
    vlayout->setMargin(0);
    vlayout->setSpacing(2);

    QWidget *widget = new QWidget;
    widget->setObjectName(QString("scrollwidget"));
    widget->setLayout(vlayout);

    scrollArea = new QScrollArea;
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setWidget(widget);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(scrollArea,Qt::AlignTop);
    layout->setMargin(0);
    this->setLayout(layout);

    this->setStyleSheet("QScrollArea{border: 0px;background-color:rgb(7,4,127);}"
                        "QWidget[objectName=\"scrollwidget\"]{background-color:rgb(7,4,127);}"
                        "QDialog[objectName=\"widget\"]{background-color:rgb(7,4,127);}"
                        "QPushButton[objectName=\"Btn1\"]{border:0px;background-image:url(:/menupic/caigouguanli.png);}"
                        "QPushButton[objectName=\"Btn1\"]:hover{background-image:url(:/menupic/caigouguanli.png);border: 1px solid rgb(7,4,127);}"
                        "QPushButton[objectName=\"Btn1\"]:pressed{background-image:url(:/menupic/caigouguanli.png);border: 2px solid rgb(7,4,127);}"

                        "QPushButton[objectName=\"Btn2\"]{border:0px;background-image:url(:/menupic/yuanliaoguanli.png);}"
                        "QPushButton[objectName=\"Btn2\"]:hover{background-image:url(:/menupic/yuanliaoguanli.png);border: 1px solid rgb(7,4,127);}"
                        "QPushButton[objectName=\"Btn2\"]:pressed{background-image:url(:/menupic/yuanliaoguanli.png);border: 2px solid rgb(7,4,127);}"

                        "QPushButton[objectName=\"Btn3\"]{border:0px;background-image:url(:/menupic/fucaiguanli.png);}"
                        "QPushButton[objectName=\"Btn3\"]:hover{background-image:url(:/menupic/fucaiguanli.png);border: 1px solid rgb(7,4,127);}"
                        "QPushButton[objectName=\"Btn3\"]:pressed{background-image:url(:/menupic/fucaiguanli.png);border: 2px solid rgb(7,4,127);}"

                        "QPushButton[objectName=\"Btn4\"]{border:0px;background-image:url(:/menupic/bangfangguanli.png);}"
                        "QPushButton[objectName=\"Btn4\"]:hover{background-image:url(:/menupic/bangfangguanli.png);border: 1px solid rgb(7,4,127);}"
                        "QPushButton[objectName=\"Btn4\"]:pressed{background-image:url(:/menupic/bangfangguanli.png);border: 2px solid rgb(7,4,127);}"

                        "QPushButton[objectName=\"Btn5\"]{border:0px;background-image:url(:/menupic/xiaoshouguanli.png);}"
                        "QPushButton[objectName=\"Btn5\"]:hover{background-image:url(:/menupic/xiaoshouguanli.png);border: 1px solid rgb(7,4,127);}"
                        "QPushButton[objectName=\"Btn5\"]:pressed{background-image:url(:/menupic/xiaoshouguanli.png);border: 2px solid rgb(7,4,127);}"

                        "QPushButton[objectName=\"Btn6\"]{border:0px;background-image:url(:/menupic/diaoduguanli.png);}"
                        "QPushButton[objectName=\"Btn6\"]:hover{background-image:url(:/menupic/diaoduguanli.png);border: 1px solid rgb(7,4,127);}"
                        "QPushButton[objectName=\"Btn6\"]:pressed{background-image:url(:/menupic/diaoduguanli.png);border: 2px solid rgb(7,4,127);}"

                        "QPushButton[objectName=\"Btn7\"]{border:0px;background-image:url(:/menupic/shiyanshiguanli.png);}"
                        "QPushButton[objectName=\"Btn7\"]:hover{background-image:url(:/menupic/shiyanshiguanli.png);border: 1px solid rgb(7,4,127);}"
                        "QPushButton[objectName=\"Btn7\"]:pressed{background-image:url(:/menupic/shiyanshiguanli.png);border: 2px solid rgb(7,4,127);}"

                        "QPushButton[objectName=\"Btn8\"]{border:0px;background-image:url(:/menupic/shengchanguanli.png);}"
                        "QPushButton[objectName=\"Btn8\"]:hover{background-image:url(:/menupic/shengchanguanli.png);border: 1px solid rgb(7,4,127);}"
                        "QPushButton[objectName=\"Btn8\"]:pressed{background-image:url(:/menupic/shengchanguanli.png);border: 2px solid rgb(7,4,127);}"

                        "QPushButton[objectName=\"Btn9\"]{border:0px;background-image:url(:/menupic/caiwuguanli.png);}"
                        "QPushButton[objectName=\"Btn9\"]:hover{background-image:url(:/menupic/caiwuguanli.png);border: 1px solid rgb(7,4,127);}"
                        "QPushButton[objectName=\"Btn9\"]:pressed{background-image:url(:/menupic/caiwuguanli.png);border: 2px solid rgb(7,4,127);}"

                        "QPushButton[objectName=\"Btn10\"]{border:0px;background-image:url(:/menupic/baobiaochaxun.png);}"
                        "QPushButton[objectName=\"Btn10\"]:hover{background-image:url(:/menupic/baobiaochaxun.png);border: 1px solid rgb(7,4,127);}"
                        "QPushButton[objectName=\"Btn10\"]:pressed{background-image:url(:/menupic/baobiaochaxun.png);border: 2px solid rgb(7,4,127);}"

                        "QPushButton[objectName=\"Btn11\"]{border:0px;background-image:url(:/menupic/tongcheguanli.png);}"
                        "QPushButton[objectName=\"Btn11\"]:hover{background-image:url(:/menupic/tongcheguanli.png);border: 1px solid rgb(7,4,127);}"
                        "QPushButton[objectName=\"Btn11\"]:pressed{background-image:url(:/menupic/tongcheguanli.png);border: 2px solid rgb(7,4,127);}"

                        "QPushButton[objectName=\"Btn12\"]{border:0px;background-image:url(:/menupic/bengcheguanli.png);}"
                        "QPushButton[objectName=\"Btn12\"]:hover{background-image:url(:/menupic/bengcheguanli.png);border: 1px solid rgb(7,4,127);}"
                        "QPushButton[objectName=\"Btn12\"]:pressed{background-image:url(:/menupic/bengcheguanli.png);border: 2px solid rgb(7,4,127);}"

                        "QPushButton[objectName=\"Btn16\"]{border:0px;background-image:url(:/menupic/xitongshezhi.png);}"
                        "QPushButton[objectName=\"Btn16\"]:hover{background-image:url(:/menupic/xitongshezhi.png);border: 1px solid rgb(7,4,127);}"
                        "QPushButton[objectName=\"Btn16\"]:pressed{background-image:url(:/menupic/xitongshezhi.png);border: 2px solid rgb(7,4,127);}"

                        "QPushButton[objectName=\"Btn17\"]{border:0px;background-image:url(:/menupic/gongju.png);}"
                        "QPushButton[objectName=\"Btn17\"]:hover{background-image:url(:/menupic/gongju.png);border: 1px solid rgb(7,4,127);}"
                        "QPushButton[objectName=\"Btn17\"]:pressed{background-image:url(:/menupic/gongju.png);border: 2px solid rgb(7,4,127);}"

                        "QPushButton[objectName=\"Btn18\"]{border:0px;background-image:url(:/menupic/bangzhu.png);}"
                        "QPushButton[objectName=\"Btn18\"]:hover{background-image:url(:/menupic/bangzhu.png);border: 1px solid rgb(7,4,127);}"
                        "QPushButton[objectName=\"Btn18\"]:pressed{background-image:url(:/menupic/bangzhu.png);border: 2px solid rgb(7,4,127);}");
}
