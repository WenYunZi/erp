#ifndef BENGCHESIJIDLG_H
#define BENGCHESIJIDLG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QStandardItemModel>
#include <QTableView>
#include <QKeyEvent>
#include <QComboBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QToolBar>
#include <QAction>
#include <QMessageBox>
#include <QString>
#include "mymysql.h"
#include "mytcpsocket.h"

class bengchesijiDlg : public QDialog
{
    Q_OBJECT
public:
    explicit bengchesijiDlg(QWidget *parent = 0);
    void refresh();

private:
    QAction             *newAction;
    QAction             *saveAction;
    QAction             *updateAction;
    QAction             *deleteAction;

private:
    const char          *SQL;
    QToolBar            *toolBar;
    QTableView          *view;
    QLineEdit           *lineEdit1;
    QLineEdit           *lineEdit2;
    QLineEdit           *lineEdit3;
    QStandardItemModel  *model = NULL;

private:
    void keyPressEvent(QKeyEvent *event);

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

#endif // BENGCHESIJIDLG_H
