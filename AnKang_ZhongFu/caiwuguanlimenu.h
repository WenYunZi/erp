#ifndef CAIWUGUANLIMENU_H
#define CAIWUGUANLIMENU_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolButton>
#include <QScrollArea>
#include <QPaintEvent>
#include <QCloseEvent>
#include <QList>
#include <QKeyEvent>
#include "maintitle.h"

class MainWindow;

class caiwuguanliMenu : public QWidget
{
    Q_OBJECT
public:
    explicit caiwuguanliMenu(MainWindow *main_w, QWidget *parent = 0);

public:
    MainWindow  *main_w;
    QToolButton *toolBtn;
    QLabel      *label;
    QPushButton *Btn1;
    QPushButton *Btn2;
    QPushButton *Btn3;
    QPushButton *Btn4;
//    QPushButton *Btn5;
//    QPushButton *Btn6;
//    QPushButton *Btn7;
//    QPushButton *Btn8;
//    QPushButton *Btn9;
//    QPushButton *Btn10;
//    QPushButton *Btn11;
    QPushButton *Btn12;
    QPushButton *Btn13;
//    QPushButton *Btn14;
    QPushButton *Btn15;
    QPushButton *Btn16;
    QScrollArea *scrollArea;
    QList<QPushButton *> BtnList;

private:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_close();

};

#endif // CAIWUGUANLIMENU_H
