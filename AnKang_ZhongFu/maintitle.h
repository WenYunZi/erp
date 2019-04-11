#ifndef MAINTITLE_H
#define MAINTITLE_H

#include <QWidget>
#include <QLabel>
#include <QToolButton>
#include <QHBoxLayout>
#include <QPainter>
#include <QLinearGradient>
#include <QIcon>
#include <QMovie>

class mainTitle : public QWidget
{
    Q_OBJECT
public:
    explicit mainTitle(QWidget *parent = 0);

public:
    QLabel *title;
    QToolButton *gongjukaiguanBtn;
    QToolButton *dakaichuangkouBtn;
    QToolButton *closeBtn;
    QToolButton *shouyeBtn;
    QToolButton *menuSwitch;
};

#endif // MAINTITLE_H
