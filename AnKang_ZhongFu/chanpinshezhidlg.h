#ifndef CHANPINSHEZHIDLG_H
#define CHANPINSHEZHIDLG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QStandardItemModel>
#include <QTableView>
#include <QComboBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QToolBar>
#include <QAction>
#include <QString>
#include <QMessageBox>
#include "mymysql.h"
#include "mytcpsocket.h"

class chanpinshezhiDlg : public QDialog
{
    Q_OBJECT
public:
    explicit chanpinshezhiDlg(QWidget *parent = 0);
    ~chanpinshezhiDlg();
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
    QLineEdit           *lineEdit4;
    QLineEdit           *lineEdit5;
    QLineEdit           *lineEdit6;
    QTableView          *view;
    QComboBox           *combo1;
    QStandardItemModel  *model = NULL;

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

#endif // CHANPINSHEZHIDLG_H
