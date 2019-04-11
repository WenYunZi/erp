#ifndef FUCAIGONGYINGSHANGDANGANDLG_H
#define FUCAIGONGYINGSHANGDANGANDLG_H

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
#include <QVBoxLayout>
#include <QCheckBox>
#include <QKeyEvent>
#include <QToolBar>
#include <QAction>
#include <QMessageBox>
#include <QString>
#include "mymysql.h"
#include "mytcpsocket.h"

class fucaigongyingshangdanganDlg : public QDialog
{
    Q_OBJECT
public:
    explicit fucaigongyingshangdanganDlg(QWidget *parent = 0);
    void refresh();

private:
    QAction             *newAction;
    QAction             *saveAction;
    QAction             *updateAction;
    QAction             *deleteAction;
    QToolBar            *toolBar;

private:
    const char          *SQL;
    QLineEdit           *lineEdit1;
    QLineEdit           *lineEdit2;
    QLineEdit           *lineEdit3;
    QLineEdit           *lineEdit4;
    QLineEdit           *lineEdit5;
    QLineEdit           *lineEdit6;
    QLineEdit           *lineEdit7;
    QLineEdit           *lineEdit8;
    QLineEdit           *lineEdit9;
    QLineEdit           *lineEdit10;
    QLineEdit           *lineEdit11;
    QLineEdit           *lineEdit12;
    QLineEdit           *lineEdit13;
    QLineEdit           *lineEdit14;
    QLineEdit           *lineEdit15;
    QComboBox           *combox;
    QTableView          *view;
    QStandardItemModel  *model = NULL;


private:
    void keyPressEvent(QKeyEvent *event);

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

#endif // FUCAIGONGYINGSHANGDANGANDLG_H
