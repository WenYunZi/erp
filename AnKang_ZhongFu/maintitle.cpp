#include "maintitle.h"

mainTitle::mainTitle(QWidget *parent) :
    QWidget(parent)
{

    QFont font;
    font.setPixelSize(20);
    font.setFamily(QString("simsun"));

    title = new QLabel;
    title->setText(tr("首页"));
    title->setAlignment(Qt::AlignCenter);
    title->setFont(font);

    QLabel *caidanLabel = new QLabel;
    caidanLabel->setHidden(true);
    caidanLabel->setFixedSize(24,24);
    caidanLabel->setPixmap(QPixmap(QString(":/menupic/caidan.png")));



    menuSwitch = new QToolButton;
    menuSwitch->setHidden(true);
    menuSwitch->setFixedSize(56,22);
    menuSwitch->setToolTip(QString("菜单开关"));
    menuSwitch->setObjectName(QString("menuSwitch"));
    menuSwitch->setStyleSheet("QToolButton[objectName=\"menuSwitch\"]{border:0px;background-image:url(:/menupic/on.png)}");

    gongjukaiguanBtn = new QToolButton;
    gongjukaiguanBtn->setFixedSize(24,24);
    gongjukaiguanBtn->setToolTip(QString("锁定程序"));
    gongjukaiguanBtn->setObjectName(QString("gongjukaiguanBtn"));
    gongjukaiguanBtn->setStyleSheet("QToolButton[objectName=\"gongjukaiguanBtn\"]{border:0px;background-image:url(:/menupic/suoding.png)}"
                                    "QToolButton[objectName=\"gongjukaiguanBtn\"]:hover{border:1px solid rgb(7,4,127);background-image:url(:/menupic/suoding.png)}"
                                    "QToolButton[objectName=\"gongjukaiguanBtn\"]:pressed{border:1px solid rgb(7,4,127);background-image:url(:/menupic/suoding.png);background-color:rgb(118,115,251)}");

    dakaichuangkouBtn = new QToolButton;
    dakaichuangkouBtn->setFixedSize(24,24);
    dakaichuangkouBtn->setToolTip(QString("已打开的窗口"));
   // dakaichuangkouBtn->setShortcut(QKeySequence(QString("Alt+W")));
    dakaichuangkouBtn->setObjectName(QString("dakaichuangkouBtn"));
    dakaichuangkouBtn->setStyleSheet("QToolButton[objectName=\"dakaichuangkouBtn\"]{border:0px;background-image:url(:/menupic/yidakaichuangkou.png)}"
                                     "QToolButton[objectName=\"dakaichuangkouBtn\"]:hover{border:1px solid rgb(7,4,127);background-image:url(:/menupic/yidakaichuangkou.png)}"
                                     "QToolButton[objectName=\"dakaichuangkouBtn\"]:pressed{border:1px solid rgb(7,4,127);background-image:url(:/menupic/yidakaichuangkou.png);background-color:rgb(118,115,251)}");

    closeBtn = new QToolButton;
    closeBtn->setFixedSize(24,24);
    closeBtn->setToolTip(QString("关闭当前窗口"));
    closeBtn->setObjectName(QString("closeBtn"));
    closeBtn->setStyleSheet("QToolButton[objectName=\"closeBtn\"]{border:0px;background-image:url(:/menupic/close.png)}"
                            "QToolButton[objectName=\"closeBtn\"]:hover{border:1px solid rgb(7,4,127);background-image:url(:/menupic/close.png)}"
                            "QToolButton[objectName=\"closeBtn\"]:pressed{border:1px solid rgb(7,4,127);background-image:url(:/menupic/close.png);background-color:rgb(118,115,251)}");

    shouyeBtn = new QToolButton;
    shouyeBtn->setFixedSize(24,24);
    shouyeBtn->setToolTip(QString("首页"));
    shouyeBtn->setObjectName(QString("shouyeBtn"));
    shouyeBtn->setStyleSheet("QToolButton[objectName=\"shouyeBtn\"]{border:0px;background-image:url(:/menupic/shouye.png)}"
                             "QToolButton[objectName=\"shouyeBtn\"]:hover{border:1px solid rgb(7,4,127);background-image:url(:/menupic/shouye.png)}"
                             "QToolButton[objectName=\"shouyeBtn\"]:pressed{border:1px solid rgb(7,4,127);background-image:url(:/menupic/shouye.png);background-color:rgb(118,115,251)}");


    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addSpacing(8);
    layout->addWidget(caidanLabel,0);
    layout->addWidget(menuSwitch,0);
    layout->addStretch(1);
    layout->addSpacing(96);
    layout->addWidget(title,0,Qt::AlignCenter);
    layout->addStretch(1);
    layout->addWidget(shouyeBtn,0,Qt::AlignRight);
    layout->addWidget(gongjukaiguanBtn,0,Qt::AlignRight);
    layout->addWidget(dakaichuangkouBtn,0,Qt::AlignRight);
    layout->addWidget(closeBtn,0,Qt::AlignRight);
    layout->addSpacing(8);
    layout->setMargin(0);

//    this->setObjectName(QString("title"));
//    this->setStyleSheet("QWidget[objectName=\"title\"]{background-color:red}");
}
