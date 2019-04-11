#ifndef TONGCHEGUANLIMENU_H
#define TONGCHEGUANLIMENU_H

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
#include <QKeyEvent>
#include "maintitle.h"

class MainWindow;

class tongcheguanliMenu : public QWidget
{
    Q_OBJECT
public:
    explicit tongcheguanliMenu(MainWindow *main_w, QWidget *parent = 0);

public:
    MainWindow  *main_w;
    QToolButton *toolBtn;
    QLabel      *label;
    QPushButton *Btn1;
    QPushButton *Btn2;
    QPushButton *Btn5;
    QPushButton *Btn6;
    QPushButton *Btn7;
    QScrollArea *scrollArea;
    QList<QPushButton *> BtnList;

private:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_close();

};

#endif // TONGCHEGUANLIMENU_H
