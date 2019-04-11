#ifndef GONGCHENGMINGCHENGDLG_H
#define GONGCHENGMINGCHENGDLG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QStandardItemModel>
#include <QTableView>
#include <QComboBox>
#include <QGridLayout>
#include <QKeyEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QToolBar>
#include <QAction>
#include <QMessageBox>
#include <QString>
#include "mymysql.h"

class gongchengmingchengDlg : public QDialog
{
    Q_OBJECT
public:
    explicit gongchengmingchengDlg(QWidget *parent = 0);
    ~gongchengmingchengDlg();

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
    QStandardItemModel  *model = NULL;

private:
    void createAction();
    void createTool();

private slots:
    void on_newAction();
    void on_saveAction();
    void on_updateAction();
    void on_deleteAction();
    void ShowSupplyclick();
};

#endif // GONGCHENGMINGCHENGDLG_H
