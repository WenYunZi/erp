#ifndef BENGCHEGUANLIMENU_H
#define BENGCHEGUANLIMENU_H

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

class bengcheguanliMenu : public QWidget
{
    Q_OBJECT
public:
    explicit bengcheguanliMenu(MainWindow *main_w, QWidget *parent = 0);

public:
    MainWindow  *main_w;
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

#endif // BENGCHEGUANLIMENU_H
