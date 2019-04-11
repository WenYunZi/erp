#ifndef FUCAICHUKUDLG_H
#define FUCAICHUKUDLG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QTextEdit>
#include <QStandardItemModel>
#include <QTableView>
#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QListView>
#include <QVBoxLayout>
#include <QDebug>
#include <QCheckBox>
#include <QKeyEvent>
#include <QTextEdit>
#include <QToolBar>
#include <QAction>
#include <QMessageBox>
#include <QGroupBox>
#include <QButtonGroup>
#include <QPushButton>
#include <QRadioButton>
#include <QString>
#include "mymysql.h"
#include "pubfunc.h"
#include "fucaichukudelegate.h"
#include "mytcpsocket.h"

class fucaichukuDlg : public QDialog
{
    Q_OBJECT
public:
    explicit fucaichukuDlg(QWidget *parent = 0);
    void refresh();

private:
    QTabWidget          *tabWidget;
    QWidget             *fucaichuku;
    QWidget             *chukuchaxun;

private:
    QAction             *newAction;
    QAction             *saveAction;
    QAction             *updateAction;
    QAction             *deleteAction;
    QAction             *checkAction;
    QToolBar            *toolBar;

private:
    QLineEdit           *lineEdit1;
    QLineEdit           *lineEdit2;
    QLineEdit           *lineEdit3;
    QLineEdit           *lineEdit4;
    QDateTimeEdit       *datetimeEdit;
    QComboBox           *comBox1;
    QComboBox           *comBox2;
    QComboBox           *comBox3;
    QComboBox           *comBox4;
    QAction             *zengjiaAction;
    QAction             *shanchuAction;
    QTableWidget        *view;
    int                  row;

private:
    const char          *SQL2;
    QDateEdit           *twodateEdit1;
    QDateEdit           *twodateEdit2;
    QComboBox           *twocomBox1;
    QComboBox           *twocomBox2;
    QCheckBox           *twocheckBox1;
    QCheckBox           *twocheckBox2;
    QPushButton         *twochaxun;
    QTableView          *twoview;
    QStandardItemModel  *twomodel = NULL;

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
    void on_checkAction();
    void ShowSupplyclick();
    void Increasing();
    void Decreasing();
    void on_twochaxunBtn();
    void on_CalculateTotalAmount();
};

#endif // FUCAICHUKUDLG_H
