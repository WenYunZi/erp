#include "mypushbutton.h"

mypushbutton::mypushbutton(QWidget *parent) :
    QToolButton(parent)
{

}

mypushbutton::mypushbutton(QString textStr, QWidget *parent = 0):QToolButton(parent)
{
    this->setObjectName(tr("toolButton"));
    this->setStyleSheet("QToolButton[objectName=\"toolButton\"]{border:0px;}");
    QPixmap pixmap(":/image/search1.png");
    this->setIcon(QIcon(pixmap));
    this->setIconSize(pixmap.size());
    this->setText(textStr);
    this->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->resize(pixmap.size());
    this->setBkPalette(0);//设置背景完全透明
    this->setAutoRaise(false);
    this->setAutoFillBackground(true);
}

void mypushbutton::setBkPalette(int transparency)//设置背景透明度
{
    QPalette palette;
    palette.setBrush(QPalette::Button,QBrush(QColor(255,255,255,transparency)));
    setPalette(palette);
}

void mypushbutton::enterEvent(QEvent *)
{
    setCursor(Qt::PointingHandCursor);
}

void mypushbutton::leaveEvent(QEvent *)
{
    setCursor(Qt::CustomCursor);
}

void mypushbutton::mousePressEvent(QMouseEvent *e)
{
    e->accept();
}

void mypushbutton::mouseReleaseEvent(QMouseEvent *e)
{
    emit clicked();
    e->accept();
}
