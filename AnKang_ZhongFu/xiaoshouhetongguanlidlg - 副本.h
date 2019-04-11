#ifndef XIAOSHOUHETONGGUANLIDLG_H
#define XIAOSHOUHETONGGUANLIDLG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QTextEdit>
#include <QStandardItemModel>
#include <QTableView>
#include <QListView>
#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QKeyEvent>
#include <QTextEdit>
#include <QToolBar>
#include <QDebug>
#include <QAction>
#include <QMessageBox>
#include <QGroupBox>
#include <QButtonGroup>
#include <QPushButton>
#include <QRadioButton>
#include <QList>
#include <QString>
#include "mymysql.h"
#include "pubfunc.h"
#include "mytcpsocket.h"
#include "xiaoshouhetongdelegate1.h"
#include "xiaoshouhetongdelegate3.h"
#include "xiaoshouhetongdelegate4.h"

class xiaoshouhetongguanliDlg : public QDialog
{
    Q_OBJECT
public:
    explicit xiaoshouhetongguanliDlg(QWidget *parent = 0);
    void refresh();

private:
    QTabWidget          *tabWidget;
    QWidget             *xiaoshouhetongguanli;
    QWidget             *xiaoshouhetongchaxun;

private:
    QAction             *newAction;
    QAction             *saveAction;
    QAction             *updateAction;
    QAction             *deleteAction;
    QToolBar            *toolBar;

private:
    QGridLayout         *onelayout;
    int                  shuxing_count;
    QLineEdit           *lineEdit1;
    QLineEdit           *lineEdit2;
    QLineEdit           *lineEdit3;
    QComboBox           *comBox1;
    QComboBox           *comBox2;
    QDateEdit           *dateEdit;
    QTableWidget        *view1;
    QTextEdit           *textEdit;
    QPushButton         *quxiaoBtn;
    QPushButton         *quanxuanBtn;
    QWidget             *shuxingWidget;
    QList<QCheckBox *>   checkBoxlist;
    QList<QLineEdit *>   lineEditlist;

private:
    const char          *SQL2;
    QCheckBox           *twocheckBox1;
    QCheckBox           *twocheckBox2;
    QComboBox           *twocomBox1;
    QComboBox           *twocomBox2;
    QDateEdit           *twodateEdit1;
    QDateEdit           *twodateEdit2;
    QPushButton         *twochaxunBtn;
    QTableView          *twoview;
    QStandardItemModel  *twomodel = NULL;

private:
    QAction *zengjiaAction1;
    QAction *shanchuAction1;

private:
    void init_shuxingWidget();

private:
    void keyPressEvent(QKeyEvent *event);
    void creatTabPage1();
    void creatTabPage2();

private:
    void createAction();
    void createTool();

private slots:
    void on_newAction();
    void on_newAction_plus();
    void on_saveAction();
    void on_updateAction();
    void on_deleteAction();
    void ShowSupplyclick2();
    void Increasing1();
    void Decreasing1();
    void on_quxiaoBtn();
    void on_quanxuanBtn();
    void on_twochaxunBtn();
};

#endif // XIAOSHOUHETONGGUANLIDLG_H
