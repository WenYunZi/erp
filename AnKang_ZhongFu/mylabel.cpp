#include "mylabel.h"

myLabel::myLabel(int ID, QWidget *parent) :
    QLabel(parent)
{
    this->ID = ID;
}

void myLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit isDoubleClick(this->ID);
    event->accept();
}
