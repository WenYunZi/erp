#ifndef TONGCHESIJIDLG_H
#define TONGCHESIJIDLG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QStandardItemModel>
#include <QTableView>
#include <QKeyEvent>
#include <QComboBox>
#include <QGridLayout>
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QToolBar>
#include <QAction>
#include <QMessageBox>
#include <QString>
#include "mymysql.h"
#include "mytcpsocket.h"

class tongchesijiDlg : public QDialog
{
    Q_OBJECT
public:
    explicit tongchesijiDlg(QWidget *parent = 0);
    ~tongchesijiDlg();
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
    QLineEdit           *lineEdit1;
    QLineEdit           *lineEdit2;
    QLineEdit           *lineEdit3;
    QLineEdit           *lineEdit4;
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

#endif // TONGCHESIJIDLG_H
