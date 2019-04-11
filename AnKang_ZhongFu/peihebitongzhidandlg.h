#ifndef PEIHEBITONGZHIDANDLG_H
#define PEIHEBITONGZHIDANDLG_H

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
#include <QScrollArea>
#include <QCheckBox>
#include <QLCDNumber>
#include <QPushButton>
#include <QGroupBox>
#include <QScrollBar>
#include <QDateTimeEdit>
#include <QDateEdit>
#include <QList>
#include <QToolBar>
#include <QAction>
#include <QMessageBox>
#include <QScrollArea>
#include <QPaintEvent>
#include <QString>
#include "mymysql.h"
#include "mydelegate.h"
#include "pubfunc.h"
#include "mytcpsocket.h"

#include <QCamera>

class peihebitongzhidanDlg : public QDialog
{
    Q_OBJECT
public:
    explicit peihebitongzhidanDlg(QWidget *parent = 0);
    ~peihebitongzhidanDlg();
    void refresh();

private:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);

public:
    QTabWidget         *tabWidget;
    QWidget            *PhbWidget;

private:
    const char         *SQL1;
    const char         *SQL2;
    const char         *SQL3;
    const char         *SQL4;
    const char         *SQL5;
    const char         *SQL6;
    QWidget            *peihebitongzhidanxinxi;
    QWidget            *weishenhedetongzhidan;
    QWidget            *shenheweixiafatongzhidan;
    QWidget            *yishiyongtongzhidan;
    QWidget            *shiyongxianyoutongzhidan;
    QWidget            *peibixiugaijilv;

private:
    QAction            *newAction;
    QAction            *saveAction;
    QAction            *updateAction;
    QAction            *deleteAction;
    QAction            *checkAction;
    QAction            *sendAction;
    QToolBar           *toolBar;

private:
   QString               GZsetCount;
   QString               GZfinishCount;
   QString               product;
   QLineEdit            *onetzdNumberLineEdit;
   QLineEdit            *CustomerLineEdit;
   QLineEdit            *StrengthGradeLineEdit;
   QLineEdit            *TaskListLineEdit;
   QLineEdit            *EngineerLineEdit;
   QLineEdit            *PourPositionLineEdit;
   QLineEdit            *PourMethodLineEdit;
   QLineEdit            *TaskRemarksLineEdit;
   QLineEdit            *ConstructSiteLineEdit;
   QLineEdit            *SlumpLineEdit;
   QLineEdit            *ContactLineEdit;
   QLineEdit            *TelephoneLineEdit;
   QLineEdit            *SupplyTimeLineEdit;
   QLineEdit            *WuShui1LineEdit;
   QLineEdit            *WuShui2LineEdit;
   QLineEdit            *WuShui3LineEdit;
   QLineEdit            *WuShui4LineEdit;
   QLineEdit            *StirTime1LineEdit;
   QLineEdit            *StirTime2LineEdit;
   QLineEdit            *StirTime3LineEdit;
   QLineEdit            *StirTime4LineEdit;

   QRegExpValidator     *pReg_zhengshu;

   QTableWidget         *tableWidget1;
   QTableWidget         *tableWidget2;

   QComboBox            *PhbTemplateCombox;
   QTableView           *view1;
   QStandardItemModel   *model1 = NULL;

   QScrollArea          *PhbScrollArea;

   QString               QDUDJ;

   QList<QWidget *>      list1;
   QList<QLineEdit *>    pflistEdit1;
   QStringList           strList1;
   QStringList           matList1;

   QList<QWidget *>      list2;
   QList<QLineEdit *>    pflistEdit2;
   QStringList           strList2;
   QStringList           matList2;

   QList<QWidget *>      list3;
   QList<QLineEdit *>    pflistEdit3;
   QStringList           strList3;
   QStringList           matList3;

   QList<QWidget *>      list4;
   QList<QLineEdit *>    pflistEdit4;
   QStringList           strList4;
   QStringList           matList4;

private:
   QTableView           *twoview;
   QStandardItemModel   *twomodel = NULL;

private:
   QTableView           *threeview;
   QStandardItemModel   *threemodel = NULL;

private:
   QDateTimeEdit        *fourdatetime1;
   QDateTimeEdit        *fourdatetime2;
   QCheckBox            *fourcheckBox;
   QPushButton          *fourBtn;
   QTableView           *fourview;
   QStandardItemModel   *fourmodel = NULL;

private:

   QDateTimeEdit        *fivedatetime1;
   QDateTimeEdit        *fivedatetime2;

   QCheckBox            *fiveGongChengCheckBox;
   QCheckBox            *fiveRenWuDanCheckBox;
   QCheckBox            *fiveUnitCheckBox;

   QComboBox            *fiveGongChengCombox;
   QComboBox            *fiveRenWuDanCombox;
   QComboBox            *fiveUnitCombox;

   QPushButton          *fiveFindBtn;
   QTableView           *fiveview;
   QStandardItemModel   *fivemodel = NULL;

private:
    void creatTabPage1();
    void creatTabPage2();
    void creatTabPage3();
    void creatTabPage4();
    void creatTabPage5();

private slots:
    void PhbTemplateComboxRespones();
    void on_newAction();
    void on_newAction_plus();
    void on_saveAction();
    void on_updateAction();
    void on_deleteAction();
    void on_checkAction();
    void on_sendAction();

    void on_CalcRongZhong1();
    void on_CalcRongZhong2();
    void on_CalcRongZhong3();
    void on_CalcRongZhong4();

    void on_fourBtn();

private slots:
    void on_fiveFindBtn();
    void on_fiveDateChange();

    void ShowSupplyclick();
    void ShowSupplyclick2();
    void ShowSupplyclick3();
    void ShowSupplyclick4();

private:
    void createAction();
    void createTool();

};

#endif // PEIHEBITONGZHIDANDLG_H
