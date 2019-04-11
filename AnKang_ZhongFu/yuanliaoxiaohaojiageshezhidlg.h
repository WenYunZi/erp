#ifndef YUANLIAOXIAOHAOJIAGESHEZHIDLG_H
#define YUANLIAOXIAOHAOJIAGESHEZHIDLG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QTableView>
#include <QComboBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QDateEdit>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QString>
#include <QToolBar>
#include <QAction>
#include "mymysql.h"
#include "pubfunc.h"
#include "mytcpsocket.h"

class yuanliaoxiaohaojiageshezhiDlg : public QDialog
{
    Q_OBJECT
public:
    explicit yuanliaoxiaohaojiageshezhiDlg(QWidget *parent = 0);

private:
    void keyPressEvent(QKeyEvent *event);

private:
    const char          *SQL;
    QLineEdit           *lineEdit1;
    QLineEdit           *lineEdit2;
    QDateEdit           *dateEdit1;
    QComboBox           *comBox;

    QAction             *newAction;
    QAction             *saveAction;
    QAction             *deleteAction;
    QToolBar            *toolBar;
    QTableView          *view1;
    QStandardItemModel  *model = NULL;

private slots:
    void on_newAction();
    void on_saveAction();
    void on_deleteAction();
    void ShowSupplyclick();
    void comBoxReply();

private:
    void createAction();
    void createTool();

};

#endif // YUANLIAOXIAOHAOJIAGESHEZHIDLG_H
