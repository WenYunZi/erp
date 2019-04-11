#ifndef BENGCHEXINXIDLG_H
#define BENGCHEXINXIDLG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QStandardItemModel>
#include <QTableView>
#include <QKeyEvent>
#include <QDateEdit>
#include <QComboBox>
#include <QListView>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QToolBar>
#include <QAction>
#include <QMessageBox>
#include <QString>
#include "mymysql.h"
#include "mytcpsocket.h"

class bengchexinxiDlg : public QDialog
{
    Q_OBJECT
public:
    explicit bengchexinxiDlg(QWidget *parent = 0);
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
    QLineEdit           *lineEdit5;
    QLineEdit           *lineEdit6;
    QLineEdit           *lineEdit7;
    QComboBox           *comBox1;
    QComboBox           *comBox2;
    QComboBox           *comBox3;
    QComboBox           *comBox4;
    QComboBox           *comBox5;
    QComboBox           *comBox6;
    QDateEdit           *dateEdit1;
    QDateEdit           *dateEdit2;
    QTableView          *view;
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

#endif // BENGCHEXINXIDLG_H
