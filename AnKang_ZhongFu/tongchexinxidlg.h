#ifndef TONGCHEXINXIDLG_H
#define TONGCHEXINXIDLG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QKeyEvent>
#include <QTextEdit>
#include <QStandardItemModel>
#include <QTableView>
#include <QComboBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListView>
#include <QDateTimeEdit>
#include <QToolBar>
#include <QAction>
#include <QMessageBox>
#include <QString>
#include "mymysql.h"
#include "mytcpsocket.h"

class tongchexinxiDlg : public QDialog
{
    Q_OBJECT
public:
    explicit tongchexinxiDlg(QWidget *parent = 0);
    ~tongchexinxiDlg();
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
    QTableView          *view;
    QStandardItemModel  *model = NULL;
    QComboBox           *combo1;
    QComboBox           *combo2;
    QComboBox           *combo3;
    QComboBox           *combo4;
    QComboBox           *combo5;
    QComboBox           *combo6;
    QLineEdit           *lineEdit1;
    QLineEdit           *lineEdit2;
    QLineEdit           *lineEdit4;
    QLineEdit           *lineEdit5;
    QLineEdit           *lineEdit6;
    QLineEdit           *lineEdit7;
    QLineEdit           *lineEdit8;
    QDateEdit           *dateEidt1;
    QDateEdit           *dateEidt2;
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

#endif // TONGCHEXINXIDLG_H
