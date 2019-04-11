#ifndef XIAOSHOUGUANLIMENU_H
#define XIAOSHOUGUANLIMENU_H

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

class xiaoshouguanliMenu : public QWidget
{
    Q_OBJECT
public:
    explicit xiaoshouguanliMenu(MainWindow *main_w, QWidget *parent = 0);

public:
    MainWindow  *main_w;
    QToolButton *toolBtn;
    QLabel      *label;
    QPushButton *Btn1;
    QPushButton *Btn2;
    QPushButton *Btn3;
    QPushButton *Btn4;
    QPushButton *Btn5;
    QScrollArea *scrollArea;
    QList<QPushButton *> BtnList;

private:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_close();

};

#endif // XIAOSHOUGUANLIMENU_H
