#ifndef YUNFEISHEZHIDLG_H
#define YUNFEISHEZHIDLG_H

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
#include <QTextEdit>
#include <QToolBar>
#include <QAction>
#include <QDebug>
#include <QMessageBox>
#include <QGroupBox>
#include <QButtonGroup>
#include <QPushButton>
#include <QListView>
#include <QRadioButton>
#include <QString>
#include "mymysql.h"
#include "mytcpsocket.h"

class yunfeishezhiDlg : public QDialog
{
    Q_OBJECT
public:
    explicit yunfeishezhiDlg(QWidget *parent = 0);
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
    QComboBox           *comBox1;
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

#endif // YUNFEISHEZHIDLG_H
