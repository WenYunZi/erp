#ifndef CHANGDISHEZHIDLG_H
#define CHANGDISHEZHIDLG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QStandardItemModel>
#include <QTableView>
#include <QComboBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QToolBar>
#include <QAction>
#include <QMessageBox>
#include <QString>
#include "mymysql.h"
#include "mytcpsocket.h"

class changdishezhiDlg : public QDialog
{
    Q_OBJECT
public:
    explicit changdishezhiDlg(QWidget *parent = 0);
    ~changdishezhiDlg();
    void refresh();

private:
    void keyPressEvent(QKeyEvent *event);

private:
    const char          *SQL;
    QLineEdit           *lineEdit1;
    QLineEdit           *lineEdit2;
    QTableView          *view;
    QAction             *newAction;
    QAction             *saveAction;
    QAction             *updateAction;
    QAction             *deleteAction;
    QToolBar            *toolBar;
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

#endif // CHANGDISHEZHIDLG_H
