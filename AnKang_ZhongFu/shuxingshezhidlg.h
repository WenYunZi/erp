#ifndef SHUXINGSHEZHIDLG_H
#define SHUXINGSHEZHIDLG_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QStandardItemModel>
#include <QTableView>
#include <QComboBox>
#include <QTabWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextBrowser>
#include <QKeyEvent>
#include <QCheckBox>
#include <QLCDNumber>
#include <QPushButton>
#include <QDateTimeEdit>
#include <QDateEdit>
#include <QToolButton>
#include <QToolBar>
#include <QAction>
#include <QMessageBox>
#include <QString>
#include "mymysql.h"
#include "mytcpsocket.h"

class shuxingshezhiDlg : public QDialog
{
    Q_OBJECT
public:
    explicit shuxingshezhiDlg(QWidget *parent = 0);
    ~shuxingshezhiDlg();
    void refresh();

private:
    void keyPressEvent(QKeyEvent *event);

public:
    QTabWidget          *tabWidget;

private:
    QWidget             *chanpinshuxing;
    QWidget             *jiaozhubuwei;
    QWidget             *jiaozhufangfa;

private:
    const char          *SQL1;
    const char          *SQL2;
    const char          *SQL3;
    QAction             *newAction;
    QAction             *saveAction;
    QAction             *updateAction;
    QAction             *deleteAction;
    QToolBar            *toolBar;
    QAction             *newAction2;
    QAction             *saveAction2;
    QAction             *updateAction2;
    QAction             *deleteAction2;
    QToolBar            *toolBar2;
    QAction             *newAction3;
    QAction             *saveAction3;
    QAction             *updateAction3;
    QAction             *deleteAction3;
    QToolBar            *toolBar3;
    QLineEdit           *onelineEdit1;
    QLineEdit           *onelineEdit2;
    QLineEdit           *onelineEdit3;
    QString              onestr1,onestr2,onestr3;
    QTableView          *oneview;
    QStandardItemModel  *onemodel = NULL;
    QLineEdit           *twolineEdit1;
    QTableView          *twoview;
    QStandardItemModel  *twomodel = NULL;
    QString              twostr1,twostr2;
    QLineEdit           *threelineEdit1;
    QTableView          *threeview;
    QStandardItemModel  *threemodel = NULL;
    QString              threestr1,threestr2;

private:
    void creatTabPage1();
    void creatTabPage2();
    void creatTabPage3();

private slots:
    void on_newAction();
    void on_saveAction();
    void on_updateAction();
    void on_deleteAction();
    void on_newAction2();
    void on_saveAction2();
    void on_updateAction2();
    void on_deleteAction2();
    void on_newAction3();
    void on_saveAction3();
    void on_updateAction3();
    void on_deleteAction3();
    void ShowSupplyclick();
    void ShowSupplyclick2();
    void ShowSupplyclick3();

private:
    void createAction();
    void createTool();
    void createAction2();
    void createTool2();
    void createAction3();
    void createTool3();
};

#endif // SHUXINGSHEZHIDLG_H
