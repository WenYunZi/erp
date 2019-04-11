#include "guanyudlg.h"

guanyuDlg::guanyuDlg(QWidget *parent) :
    QDialog(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setFixedSize(450,220);
    this->setObjectName(tr("guanyudlg"));
    this->setStyleSheet("QDialog[objectName=\"guanyudlg\"]{background-color:rgb(240,240,240);"
                        "border: 3px solid rgb(6,17,153);}");

    label1 = new QLabel;
    label1->setGeometry(30,30,100,100);
    label1->setParent(this);
    label1->setPixmap(QPixmap(":/image/logo1.png"));

    label2 = new QLabel;
    label2->setGeometry(140,30,280,100);
    label2->setParent(this);
    label2->setAlignment(Qt::AlignBottom);
    label2->setText(tr("青盛ERP 2.6 Build\n\n青岛青盛软件科技有限公司 版权所有\n\nCopyright(c)2017 QShine Inc All Rights Reserved"));

    Btn = new QPushButton;
    Btn->setObjectName(tr("myBtn"));
    connect(Btn,SIGNAL(clicked()),this,SLOT(on_queding()));
    Btn->setGeometry(320,160,100,30);
    Btn->setParent(this);
    Btn->setText(tr("确定"));//[objectName=\"myBtn\"]
    Btn->setStyleSheet("QPushButton{border: 1px solid rgb(150,150,150);background-color:rgb(240,240,240);}"
                       "QPushButton:hover{background-color:rgb(240,240,240);border: 1px solid rgb(7,4,127)}"
                       "QPushButton:pressed{background-color:rgb(240,240,240);border: 2px solid rgb(7,4,127)}");
}

void guanyuDlg::on_queding()
{
    close();
}
