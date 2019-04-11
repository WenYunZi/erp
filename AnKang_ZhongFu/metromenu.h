#ifndef METROMENU_H
#define METROMENU_H

#include <QDialog>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QToolBox>
#include <QRect>
#include <QScrollArea>
#include <QPaintEvent>
#include <QButtonGroup>
#include <QLabel>
#include <QDebug>

class MetroMenu : public QWidget
{
    Q_OBJECT

public:
    MetroMenu(QWidget *parent = 0);

public:
    QPushButton *Btn1;
    QPushButton *Btn2;
    QPushButton *Btn3;
    QPushButton *Btn4;
    QPushButton *Btn5;
    QPushButton *Btn6;
    QPushButton *Btn7;
    QPushButton *Btn8;
    QPushButton *Btn9;
    QPushButton *Btn10;
    QPushButton *Btn11;
    QPushButton *Btn12;



    QPushButton *Btn16;
    QPushButton *Btn17;
    QPushButton *Btn18;
    QButtonGroup *BtnGroup;
    QLabel *beijingLabel;

public:
    QScrollArea *scrollArea;
};

#endif // METROMENU_H
