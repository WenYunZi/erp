#ifndef FUCAISHEZHIDLG_H
#define FUCAISHEZHIDLG_H

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
#include <QDebug>
#include <QToolBar>
#include <QStringList>
#include <QAction>
#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QMessageBox>
#include <QGroupBox>
#include <QButtonGroup>
#include <QPushButton>
#include <QRadioButton>
#include <QString>
#include "mymysql.h"
#include "mytcpsocket.h"

class fucaishezhiDlg : public QDialog
{
    Q_OBJECT
public:
    explicit fucaishezhiDlg(QWidget *parent = 0);
    void refresh();

private:
    QTabWidget          *tabWidget;
    QWidget             *tianjiafucai;
    QWidget             *fucaileibieshezhi;

private:
    QAction             *newAction;
    QAction             *saveAction;
    QAction             *updateAction;
    QAction             *deleteAction;
    QToolBar            *toolBar;
    QAction             *saveAction2;
    QAction             *deleteAction2;
    QToolBar            *toolBar2;

private:
    const char          *SQL1;
    QLineEdit           *lineEdit1;
    QLineEdit           *lineEdit2;
    QLineEdit           *lineEdit3;
    QLineEdit           *lineEdit4;
    QLineEdit           *lineEdit5;
    QLineEdit           *lineEdit6;
    QLineEdit           *lineEdit7;
    QLineEdit           *lineEdit8;
    QCheckBox           *checkBox1;
    QCheckBox           *checkBox2;
    QCheckBox           *checkBox3;
    QComboBox           *combox1;
    QComboBox           *combox2;
    QComboBox           *combox3;
    QTableView          *view;
    QStandardItemModel  *model = NULL;
    QPushButton         *chaxun;

private:
    const char          *SQL2;
    QStandardItemModel  *twomodel = NULL;
    QLabel              *label2;
    QButtonGroup        *twoBtnGroup;
    QLineEdit           *twolineEdit1;
    QComboBox           *twocombox1;
    QRadioButton        *tworadioBtn1;
    QRadioButton        *tworadioBtn2;
    QTreeView           *twoview;
    QGridLayout         *layout;

private:
    void keyPressEvent(QKeyEvent *event);
    void creatTabPage1();
    void creatTabPage2();

private slots:
    void on_newAction();
    void on_saveAction();
    void on_updateAction();
    void on_deleteAction();
    void ShowSupplyclick();
    void on_saveAction2();
    void on_deleteAction2();

private:
    void createAction();
    void createTool();
    void createAction2();
    void createTool2();

private slots:
    void on_layout_change();
    void fillComBox2();
    void on_chaxun();
};

#endif // FUCAISHEZHIDLG_H
