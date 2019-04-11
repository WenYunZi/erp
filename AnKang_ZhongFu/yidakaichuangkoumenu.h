#ifndef YIDAKAICHUANGKOUMENU_H
#define YIDAKAICHUANGKOUMENU_H

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
#include <QSignalMapper>
#include <QDesktopWidget>
#include "maintitle.h"

class MainWindow;

class yiDaKaiChuangKouMenu : public QWidget
{
    Q_OBJECT
public:
    explicit yiDaKaiChuangKouMenu(MainWindow *main_w, mainTitle *main_title, QWidget *parent = 0);

public:
    int count_except_menu;

private:
    MainWindow *main_w;
    mainTitle  *main_title;
    QSignalMapper *signalMapper;
    bool isMouseOnWindow;

private:
    void leaveEvent(QEvent *);
    void keyPressEvent(QKeyEvent *event);
    QString replace(QString name);

private slots:
    void openWindow(QString windowTitle);
};

#endif // YIDAKAICHUANGKOUMENU_H
