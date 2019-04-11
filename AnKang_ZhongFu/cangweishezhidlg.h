#ifndef CANGWEISHEZHIDLG_H
#define CANGWEISHEZHIDLG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QStandardItemModel>
#include <QTableView>
#include <QComboBox>
#include <QKeyEvent>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QDate>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QToolBar>
#include <QAction>
#include <QString>
#include <QMessageBox>
#include "mymysql.h"
#include "mytcpsocket.h"

class cangweishezhiDlg : public QDialog
{
    Q_OBJECT
public:
    explicit cangweishezhiDlg(QWidget *parent = 0);
    ~cangweishezhiDlg();
    void refresh();

private:
    void keyPressEvent(QKeyEvent *event);

private:
    const char          *SQL;
    QAction             *newAction;
    QAction             *saveAction;
    QAction             *updateAction;
    QAction             *deleteAction;
    QToolBar            *toolBar;
    QLineEdit           *lineEdit1;
    QLineEdit           *lineEdit2;
    QLineEdit           *lineEdit3;
    QTableView          *view;
    QComboBox           *combo1;
    QComboBox           *combo2;
    QComboBox           *combo3;
    QComboBox           *combo4;
    QStandardItemModel  *model = NULL;
    QDate                date;
    QString              str1,str2,str3,str4,str5,str6;

private slots:
    void on_newAction();
    void on_saveAction();
    void on_updateAction();
    void on_deleteAction();
    void ShowSupplyclick();

private:
    void createAction();
    void createTool();

};

#endif // CANGWEISHEZHIDLG_H
