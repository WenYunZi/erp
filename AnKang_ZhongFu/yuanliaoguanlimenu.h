#ifndef YUANLIAOGUANLIMENU_H
#define YUANLIAOGUANLIMENU_H

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

class yuanliaoguanliMenu : public QDialog
{
    Q_OBJECT
public:
    explicit yuanliaoguanliMenu(MainWindow *main_w, QWidget *parent = 0);

private:
    MainWindow *main_w;

public:
    QToolButton *toolBtn;
    QLabel      *label;
    QPushButton *Btn1;
    QPushButton *Btn2;
    QScrollArea *scrollArea;

private:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_close();

};

#endif // YUANLIAOGUANLIMENU_H
