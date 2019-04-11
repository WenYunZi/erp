#ifndef YONGHUGUANLIDLG_H
#define YONGHUGUANLIDLG_H

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
#include <QRadioButton>
#include <QToolBar>
#include <QAction>
#include <QMessageBox>
#include <QString>
#include <QButtonGroup>
#include "mymysql.h"
#include "mimaxiugaidlg.h"
#include "mytcpsocket.h"

class yonghuguanliDlg : public QDialog
{
    Q_OBJECT
public:
    explicit yonghuguanliDlg(QWidget *parent = 0);
    ~yonghuguanliDlg();
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
    QStandardItemModel  *model = NULL;
    QLineEdit           *lineEdit1;
    QLineEdit           *lineEdit2;
    QLineEdit           *lineEdit3;
    QLineEdit           *lineEdit4;
    QLineEdit           *lineEdit5;
    QComboBox           *combo1;
    QButtonGroup        *Btngroup;
    QRadioButton        *radioBtn1;
    QRadioButton        *radioBtn2;
    QCheckBox           *checkBox1;
    QCheckBox           *checkBox2;
    QTableView          *view;
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

#endif // YONGHUGUANLIDLG_H
