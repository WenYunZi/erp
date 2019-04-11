#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QBitmap>
#include <QDesktopWidget>
#include <QSound>
#include <QApplication>
#include <QTimer>
#include <QDesktopServices>
#include "titlewidget.h"
#include "mypushbutton.h"

class MainWindow;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(MainWindow *main_w, QWidget *parent = 0);
    ~Widget();

private:
    MainWindow      *main_w;
    int              beginY;
    int              timeCount;
    double           tran;
    bool             isEnter;
    QString          winTitle;
    titleWidget     *titleW;
    QLabel          *content;
    mypushbutton    *btnLook;
    QTimer          *timerStay;
    QTimer          *timerClose;
    QTimer          *timerShow;
    QRect            deskRect;
    QPoint           normalPoint;


public:
    void setMsg(QString title, QString content);
    void setWinTitle(QString winTitle);
    void paintEvent(QPaintEvent *);
    void showAsQQ();

    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

private slots:
    void myMove();
    void myStay();
    void myClose();
    void seeInfo();
    void widgetCount1();

};

#endif // WIDGET_H
