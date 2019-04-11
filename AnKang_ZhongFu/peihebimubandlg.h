#ifndef PEIHEBIMUBANDLG_H
#define PEIHEBIMUBANDLG_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QStandardItemModel>
#include <QTableView>
#include <QKeyEvent>
#include <QComboBox>
#include <QTabWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QSignalMapper>
#include <QVBoxLayout>
#include <QVariant>
#include <QButtonGroup>
#include <QTextBrowser>
#include <QCheckBox>
#include <QLCDNumber>
#include <QPushButton>
#include <QTableWidgetItem>
#include <QDateTimeEdit>
#include <QDateEdit>
#include <QGroupBox>
#include <QRadioButton>
#include <QToolButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QToolBar>
#include <QAction>
#include <QString>
#include <QAbstractItemDelegate>
#include <QString>
#include "mymysql.h"
#include "pubfunc.h"
#include "mytcpsocket.h"
#include "mycombobox.h"

class peihebimubanDlg : public QDialog
{
    Q_OBJECT
public:
    explicit peihebimubanDlg(QWidget *parent = 0);
    ~peihebimubanDlg();
    void refresh();

private:
    void keyPressEvent(QKeyEvent *event);

private:
    QAction             *newAction;
    QAction             *saveAction;
    QAction             *updateAction;
    QAction             *deleteAction;

    QAction             *newAction2;
    QAction             *saveAction2;
    QAction             *updateAction2;
    QAction             *deleteAction2;

    QAction             *newAction3;
    QAction             *saveAction3;
    QAction             *updateAction3;
    QAction             *deleteAction3;

    QAction             *newAction4;
    QAction             *saveAction4;
    QAction             *updateAction4;
    QAction             *deleteAction4;

    QToolBar            *toolBar;
    QToolBar            *toolBar2;
    QToolBar            *toolBar3;
    QToolBar            *toolBar4;
    QTabWidget          *tabWidget;
    QWidget             *peihebimubanxinxi1;
    QWidget             *peihebimubanxinxi2;
    QWidget             *peihebimubanxinxi3;
    QWidget             *peihebimubanxinxi4;
    QWidget             *PhbUpdateRecordWidget;

    QRegExpValidator    *pReg_zhengshu;

    QStringList          pfList;

private:
    QString              SQL1;
    QLineEdit           *onePhbNumLineEdit;
    QLineEdit           *onePhbNameLineEdit;
    QLineEdit           *oneStrenghtGradeLineEdit;
    QLineEdit           *oneStirTimeLineEdit;
    QLineEdit           *oneWuShuiLineEdit;
    QTableView          *onePhbListView;
    QStandardItemModel  *onePhbListModel = NULL;

    QList<QWidget *>      list1;
    QList<QLineEdit *>    pflistEdit1;
    QStringList           strList1;
    QStringList           matList1;


private:
    QString              SQL2;
    QLineEdit           *twoPhbNumLineEdit;
    QLineEdit           *twoPhbNameLineEdit;
    QLineEdit           *twoStrenghtGradeLineEdit;
    QLineEdit           *twoStirTimeLineEdit;
    QLineEdit           *twoWuShuiLineEdit;
    QTableView          *twoPhbListView;
    QStandardItemModel  *twoPhbListModel = NULL;

    QList<QWidget *>      list2;
    QList<QLineEdit *>    pflistEdit2;
    QStringList           strList2;
    QStringList           matList2;

private:
    QString              SQL3;
    QLineEdit           *threePhbNumLineEdit;
    QLineEdit           *threePhbNameLineEdit;
    QLineEdit           *threeStrenghtGradeLineEdit;
    QLineEdit           *threeStirTimeLineEdit;
    QLineEdit           *threeWuShuiLineEdit;
    QTableView          *threePhbListView;
    QStandardItemModel  *threePhbListModel = NULL;

    QList<QWidget *>      list3;
    QList<QLineEdit *>    pflistEdit3;
    QStringList           strList3;
    QStringList           matList3;

private:
    QString              SQL4;
    QLineEdit           *three2PhbNumLineEdit;
    QLineEdit           *three2PhbNameLineEdit;
    QLineEdit           *three2StrenghtGradeLineEdit;
    QLineEdit           *three2StirTimeLineEdit;
    QLineEdit           *three2WuShuiLineEdit;
    QTableView          *three2PhbListView;
    QStandardItemModel  *three2PhbListModel = NULL;

    QList<QWidget *>      list4;
    QList<QLineEdit *>    pflistEdit4;
    QStringList           strList4;
    QStringList           matList4;

private:
    QDateTimeEdit        *fourDateTimeEdit1;
    QDateTimeEdit        *fourDateTimeEdit2;

    QComboBox            *fourUnitNoCombox;

    QCheckBox            *fourPhbNameCheckBox;
    QComboBox            *fourPhbNameCombox;

    QPushButton          *fourFindBtn;

    QTableView          *fourUpdateView;
    QStandardItemModel  *fourUpdateModel = NULL;

private:
    void creatTabPage1();
    void creatTabPage2();
    void creatTabPage3();
    void creatTabPage4();
    void creatTabPageChange();

    void createAction();
    void createTool();

    void createAction2();
    void createTool2();

    void createAction3();
    void createTool3();

    void createAction4();
    void createTool4();

private slots:
    void on_newAction();
    void on_saveAction();
    void on_updateAction();
    void on_deleteAction();

    void on_newAction2();
    void on_saveAction2();
    void on_updateAction2();
    void on_deleteAction2();

    void on_newAction3();
    void on_saveAction3();
    void on_updateAction3();
    void on_deleteAction3();

    void on_newAction4();
    void on_saveAction4();
    void on_updateAction4();
    void on_deleteAction4();

    void ShowSupplyclick();
    void ShowSupplyclick2();
    void ShowSupplyclick3();
    void ShowSupplyclick4();

    void on_CalcRongZhong1();
    void on_CalcRongZhong2();
    void on_CalcRongZhong3();
    void on_CalcRongZhong4();

    void on_fourFindBtn();
};

#endif // PEIHEBIMUBANDLG_H
