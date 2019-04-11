#ifndef KEHUDANGANDLG_H
#define KEHUDANGANDLG_H

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
#include <QVBoxLayout>
#include <QCheckBox>
#include <QToolBar>
#include <QAction>
#include <QMessageBox>
#include <QString>
#include "mymysql.h"
#include "mytcpsocket.h"

class kehudanganDlg : public QDialog
{
    Q_OBJECT
public:
    explicit kehudanganDlg(QWidget *parent = 0);
    ~kehudanganDlg();
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
    QLineEdit           *lineEdit5;
    QLineEdit           *lineEdit6;
    QLineEdit           *lineEdit8;
    QLineEdit           *lineEdit9;
    QComboBox           *combo;
    QCheckBox           *checkBox;
    QTableView          *view;
    QStandardItemModel  *model = NULL;
    QString              str1,str2,str3,str4,str5,str6,str7,str8,str9;

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

#endif // KEHUDANGANDLG_H
