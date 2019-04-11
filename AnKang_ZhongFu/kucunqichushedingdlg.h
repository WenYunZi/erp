#ifndef KUCUNQICHUSHEDINGDLG_H
#define KUCUNQICHUSHEDINGDLG_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QLineEdit>
#include <QTextEdit>
#include <QKeyEvent>
#include <QStandardItemModel>
#include <QTableView>
#include <QComboBox>
#include <QTabWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextBrowser>
#include <QCheckBox>
#include <QLCDNumber>
#include <QPushButton>
#include <QDateTimeEdit>
#include <QDateEdit>
#include <QString>
#include <QMessageBox>
#include "mymysql.h"

class kucunqichushedingDlg : public QDialog
{
    Q_OBJECT
public:
    explicit kucunqichushedingDlg(QWidget *parent = 0);
    ~kucunqichushedingDlg();
    void refresh();

private:
    void keyPressEvent(QKeyEvent *event);

private:
    QTabWidget          *tabWidget;
    QWidget             *lilunkucunqichusheding;
    QWidget             *cangweitiaozheng;
    QWidget             *cangweitiaozhengjilv;

private:
    const char          *SQL1;
    const char          *SQL2;
    const char          *SQL3;
    QLineEdit           *lineEdit1;
    QLineEdit           *lineEdit2;
    QLineEdit           *lineEdit3;
    QPushButton         *tiaozhengqueren;
    QTableView          *view;
    QStandardItemModel  *model = NULL;

private:
    QLineEdit           *twolineEdit1;
    QLineEdit           *twolineEdit2;
    QLineEdit           *twolineEdit3;
    QLineEdit           *twolineEdit4;
    QLineEdit           *twolineEdit6;
    QLineEdit           *twolineEdit7;
    QTimer              *timer;
    QLineEdit           *twodatetime;
    QPushButton         *twocangwei;
    QTableView          *twoview ;
    QStandardItemModel  *twomodel = NULL;
    QString              DepartmentName,SubordinateUnit;
    QDateEdit           *threedate1;
    QDateEdit           *threedate2;
    QPushButton         *threechaxun;
    QTableView          *threeview;
    QStandardItemModel  *threemodel = NULL;

private:
    void creatTabPage1();
    void creatTabPage2();
    void creatTabPage3();

private slots:
    void ShowSupplyclick();
    void on_tiaozhengqueren();
    void on_twocangwei();
    void ShowSupplyclick2();
    void setTimeDate();
    void on_threechaxun();
};

#endif // KUCUNQICHUSHEDINGDLG_H
