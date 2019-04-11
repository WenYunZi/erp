#ifndef BUMENSHEZHIDLG_H
#define BUMENSHEZHIDLG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QStandardItemModel>
#include <QTableView>
#include <QComboBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QListView>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QKeyEvent>
#include <QToolBar>
#include <QAction>
#include <QMessageBox>
#include <QString>
#include "mymysql.h"
#include "mytcpsocket.h"

class bumenshezhiDlg : public QDialog
{
    Q_OBJECT
public:
    explicit bumenshezhiDlg(QWidget *parent = 0);
    ~bumenshezhiDlg();
    void refresh();

public slots:

private:
    const char          *SQL1;
    const char          *SQL2;
    QTabWidget          *tabWidget;
    QWidget             *bumenshezhi;
    QWidget             *jizushezhi;

private:
    QLineEdit           *onelineEdit1;
    QLineEdit           *onelineEdit2;
    QLineEdit           *onelineEdit3;
    QLineEdit           *onelineEdit4;
    QTableView          *oneview;
    QComboBox           *onecombo;
    QCheckBox           *onecheckBox;
    QAction             *newAction;
    QAction             *saveAction;
    QAction             *updateAction;
    QAction             *deleteAction;
    QToolBar            *toolBar;
    QStandardItemModel  *onemodel = NULL;
    QString              str1,str2,str3,str4,str5,str6;

private:
    QLineEdit           *twolineEdit1;
    QTableView          *twoview;
    QComboBox           *twocombo;
    QComboBox           *twocombo1;
    QAction             *newAction2;
    QAction             *saveAction2;
    QAction             *updateAction2;
    QAction             *deleteAction2;
    QToolBar            *toolBar2;
    QStandardItemModel  *twomodel = NULL;
    QString              twostr1,twostr2,twostr3;

private:
    void keyPressEvent(QKeyEvent *event);
    void creatTabPage1();
    void creatTabPage2();

private slots:
    void on_newAction();
    void on_saveAction();
    void on_updateAction();
    void on_deleteAction();
    void ShowSupplyclick();
    void on_newAction2();
    void on_saveAction2();
    void on_updateAction2();
    void on_deleteAction2();
    void ShowSupplyclick2();

private:
    void createAction();
    void createTool();

private:
    void createAction2();
    void createTool2();
};

#endif // BUMENSHEZHIDLG_H
