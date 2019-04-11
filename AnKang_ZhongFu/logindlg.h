#ifndef LOGINDLG_H
#define LOGINDLG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QKeyEvent>
#include <QCloseEvent>
#include <QTcpSocket>
#include <QGridLayout>
#include <QFont>
#include <QPalette>
#include <QMessageBox>
#include <QHostAddress>
#include "mymysql.h"
#include "pubfunc.h"

class MainWindow;

class loginDlg : public QDialog
{
    Q_OBJECT
public:
    explicit loginDlg(MainWindow *main_w, QWidget *parent = 0);

private:
    void keyPressEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *closeEvent);

public:
    QLabel          *label1;
    QLabel          *label2;
    QLabel          *label3;
    QString          passwd;
    QString          userid;
    QString          hostip;
    bool             islogin;
    bool             isconnecting;

private:
    MainWindow      *w;
    QLabel          *label;
    QLineEdit       *lineEditUserID, *lineEditPasswd, *lineEditHostIP;
    QPushButton     *loginBtn, *logoutBtn;

private slots:
    void loginBtnOnclick();
    void logoutBtnOnclick();
};

#endif // LOGINDLG_H
