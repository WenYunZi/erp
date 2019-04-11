#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QToolButton>
#include <QPalette>
#include <QPixmap>
#include <QMouseEvent>
#include <QCursor>

class mypushbutton : public QToolButton
{
    Q_OBJECT
public:
    explicit mypushbutton(QWidget *parent = 0);
    mypushbutton(QString textStr, QWidget *parent);

signals:

public slots:

public:
    void setBkPalette(int transparency);//设置背景透明度
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
};

#endif // MYPUSHBUTTON_H
