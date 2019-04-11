#ifndef JIZUJIEKOUDLG_H
#define JIZUJIEKOUDLG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QFont>
#include <QVBoxLayout>
#include <QPaintEvent>
#include <QCloseEvent>
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>
#include <QWidget>
#include <QProgressBar>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QString>
#include <QHBoxLayout>
#include "mymysql.h"
#include "pubfunc.h"
#include "thread_jizujiekou.h"
#include "mytcpsocket.h"
#include "thread_sync.h"

class jizujiekouDlg : public QDialog
{
    Q_OBJECT
public:
    explicit jizujiekouDlg(QWidget *parent = 0);
public:
    bool isOpen;
    QProgressBar *pProgressBar;

private:
    void keyPressEvent(QKeyEvent *event);

private:

    QPushButton               *Btn1;
    QPushButton               *Btn2;
    QWidget                   *widget;
    QLabel                    *label1;
    QLabel                    *label2;
    QLabel                    *label3;
    QLabel                    *label4;
    QTimer                    *timer;

public:
    thread_jizujiekou         *thread;
    thread_sync               *threadSync;

private:
    void closeEvent(QCloseEvent *event);
    void paintEvent(QPaintEvent *paintEvent);

public slots:
    void on_shujuchuanshu();
    void on_tingzhichuanshu();

private slots:
    void updateProcess(int value);
    void RecErroMessage(QString erro);
};

#endif // JIZUJIEKOUDLG_H
