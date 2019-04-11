#ifndef SHENGCHANRENWUDANDLG_H
#define SHENGCHANRENWUDANDLG_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QStandardItemModel>
#include <QTableView>
#include <QComboBox>
#include <QKeyEvent>
#include <QTabWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextBrowser>
#include <QCheckBox>
#include <QLCDNumber>
#include <QPushButton>
#include <QDateTimeEdit>
#include <QDateEdit>
#include <QBrush>
#include <QDebug>
#include <QToolButton>
#include <QToolBar>
#include <QMessageBox>
#include <QAction>
#include <QString>
#include <QValidator>
#include "mymysql.h"
#include "pubfunc.h"
#include "shuxingtoolbardlg.h"
#include "mytcpsocket.h"
#include "maintitle.h"
#include "cheliangzhuangtai.h"
#include "mycombobox.h"


class shengchanrenwudanDlg : public QDialog
{
    Q_OBJECT
public:
    explicit shengchanrenwudanDlg(QWidget *parent = 0);
    ~shengchanrenwudanDlg();
    void refresh();

private:
    void keyPressEvent(QKeyEvent *event);

public:
    QTabWidget          *tabWidget;

private:
    QString              warningState;
    QString              SQL1;
    const char          *SQL2;
    const char          *SQL3;
    const char          *SQL4;
    QWidget             *shengchanrenwudanxinxi;
    QWidget             *weishenhedeshengchanrenwudan;
    QWidget             *shenheweixiafadeshengchanrenwudan;
    QWidget             *shengchanrenwudanchaxun;
    QAction             *newAction;
    QAction             *saveAction;
    QAction             *updateAction;
    QAction             *deleteAction;
    QAction             *checkAction;
    QAction             *sendAction;
    QAction             *invalidAction;
    QAction             *cheliangStatusAction;
    QAction             *jiaozhufangshiAction;
    QToolBar            *toolBar;
    shuxingtoolbarDlg   *dlg;

private:
    QLineEdit           *oneTaskNoLineEdit;
    QLineEdit           *oneStrengthGradeLineEdit;
    QLineEdit           *PlannedQuantityLineEdit;
    QLineEdit           *TelephoneLineEdit;
    QLineEdit           *HasBeenUnderTaskLineEdit;
    QComboBox           *SlumpCombox;
    QLineEdit           *ContractCompletionLineEdit;
    QLineEdit           *ConstructionSiteLineEdit;
    QLineEdit           *RemarksLineEdit;
    QLineEdit           *SettlementAmountLineEdit;
    myComboBox          *RealCustomerCombox;
    myComboBox          *FaHuoCustomerCombox;
    QComboBox           *PourPositionCombox;
    myComboBox          *EngineerCombox;
    QComboBox           *PourMethodCombox;
    QComboBox           *ProductCombox;
    QComboBox           *oneContactsComBox;
    QLineEdit           *ContractNoLineEdit;
    QDateEdit           *InfoDateEdit;
    QDateTimeEdit       *SupplyDatetimeEdit;
    QToolButton         *AttributeToolBtn;
    QTableView          *TaskListView;
    QStandardItemModel  *model = NULL;

private:
    QTableView          *threeview;
    QStandardItemModel  *threemodel = NULL;
    QCheckBox           *fourEngineerCheckBox;
    myComboBox          *fourEngineerCombox;
    QDateEdit           *fourdate1;
    QDateEdit           *fourdate2;
    QPushButton         *fourFindBtn;
    QTableView          *fourview;
    QStandardItemModel  *fourmodel = NULL;
    QString chaxunSQL;

private:
    void creatTabPage1();
    void creatTabPage3();
    void creatTabPage4();
    void setModelStyle(QStandardItemModel *model);

private slots:
    void on_newAction();
    void on_newAction_plus();
    void on_saveAction();
    void on_updateAction();
    void on_deleteAction();
    void on_checkAction();
    void on_sendAction();
    void on_invalidAction();
    void on_cheliangStatusAction();
    void on_jiaozhufangshiAction();
    void ShowSupplyclick();
    void ShowSupplyclick3();
    void ShowSupplyclick4();
    void on_AttributeToolBtn();
    void on_fillStrengthGrade();
    void on_fourFindBtn();
    void on_RealCustomerCombox();
    void on_EngineerCombox();
    void on_oneContactsComBox();

private:
    void createAction();
    void createTool();
};

#endif // SHENGCHANRENWUDANDLG_H
