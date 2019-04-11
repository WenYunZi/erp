#ifndef BANGZHUMENU_H
#define BANGZHUMENU_H

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

class bangzhuMenu : public QDialog
{
    Q_OBJECT
public:
    explicit bangzhuMenu(MainWindow *main_w, QWidget *parent = 0);

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

#endif // BANGZHUMENU_H
