#ifndef FUCAIRUKUDLG_H
#define FUCAIRUKUDLG_H

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
#include <QDebug>
#include <QTextEdit>
#include <QToolBar>
#include <QAction>
#include <QMessageBox>
#include <QGroupBox>
#include <QButtonGroup>
#include <QPushButton>
#include <QRadioButton>
#include <QString>
#include "mymysql.h"
#include "pubfunc.h"
#include "fucaideletegate.h"
#include "mytcpsocket.h"
#include "mycombobox.h"
#include "myexcel.h"

class fucairukuDlg : public QDialog
{
    Q_OBJECT
public:
    explicit fucairukuDlg(QWidget *parent = 0);
    void refresh();

private:
    QTabWidget          *tabWidget;
    QWidget             *fucairuku;
    QWidget             *fucaichuku;
    QWidget             *fucaikucun;
//    QWidget             *fucaijilu;

    myExcel             *view2Excel;

private:
    void keyPressEvent(QKeyEvent *event);
    void creatTabPage1();
    void creatTabPage2();
    void creatTabPage3();
//    void creatTabPage4();
/**********************入库************************/
private:
    QAction             *newAction;
    QAction             *saveAction;
    QAction             *updateAction;
    QAction             *deleteAction;
    QAction             *checkAction;
    QToolBar            *toolBar;

private:

    QString onerukudanhao;
    QString onefucainame;
    QString onefucaidalei;
    QString onefucaixiaolei;
    QString onefucaidanjia;
    QString onefucaishuliang;
    QString onerukuzongjine;
    QString onefucaiguige;
    QString onefucaidanwei;
    QString onesonghuorenyuan;
    QString onelianxifangshi;
    QString onelururenyuan;
    QDate onelururiqi;
    QString onelukubeizhu;

    const char          *LuRuSQL;
    QLineEdit *rukudanhaoLineEdit;
    QComboBox *fucainameComboBox;
    QComboBox *fucaixiaoleiComboBox;
    QComboBox *fucaidaleiComboBox;
    QLineEdit *fucaidanjiaLineEdit;
    QLineEdit *fucaishuliangLineEdit;
    QLineEdit *rukuzongjineLineEdit;
    QLineEdit *fucaiguigeLineEdit;
    QLineEdit *fucaidanweiLineEdit;
    QLineEdit *songhuorenyuanLineEdit;
    QLineEdit *lianxifangshiLineEdit;
    QLineEdit *caigourenyuanLineEdit;
    QLineEdit *caigoulianxifangshiLineEdit;
    QLineEdit *lururenyuanLineEdit;
    QDateEdit *lururiqiDateEdit;
    QLineEdit *lukubeizhuLineEdit;

    QDateEdit *onedateEdit1;
    QDateEdit *onedateEdit2;

    QPushButton *onechaxun;
    QPushButton *daochuBtn1;

    QCheckBox *onefucaidaleiCheckBox;
    QComboBox *onefudaleiCombox;
    QCheckBox *onefucaixiaoleiCheckBox;
    QComboBox *onefucaixiaoleiCombox;
    QCheckBox *onefucaimingchengCheckBox;
    QComboBox *onefucaimingchengCombox;
    QCheckBox *onesonghuorenyuanCheckBox;
    QComboBox *onesonghuorenyuanCombox;

    QTableView          *fahuoView;
    QStandardItemModel  *fahuoModel = NULL;

private slots:
    void on_onechaxun();
    void on_toExcell1();
    void Show_fahuoSupplyclick();
    void on_fucaidalei();
    void on_fucaixiaolei();
    void on_fucaidanjia();
    void on_fucaishuliang();

private:
    void createAction();
    void createTool();

private slots:
    void on_newAction();
    void on_newAction_plus();
    void on_saveAction();
    void on_updateAction();
    void on_deleteAction();
     /************入库结束********************/

/**********************出库************************/
private:
    QAction             *twonewAction;
    QAction             *twosaveAction;
    QAction             *twoupdateAction;
    QAction             *twodeleteAction;
    QAction             *twocheckAction;
    QToolBar            *twotoolBar;
private:
    QString tworukudanhao;
    QString twofucainame;
    QString twofucaidalei;
    QString twofucaixiaolei;
    QString twofucaidanjia;
    QString twofucaishuliang;
    QString tworukuzongjine;
    QString twofucaiguige;
    QString twofucaidanwei;
    QString twosonghuorenyuan;
    QString twolianxifangshi;
    QString twolururenyuan;
    QDate twolururiqi;
    QString twolukubeizhu;

private:
    const char          *twoLuRuSQL;
    QLineEdit *tworukudanhaoLineEdit;
    QComboBox *twofucainameComboBox;
    QComboBox *twofucaixiaoleiComboBox;
    QComboBox *twofucaidaleiComboBox;
    QLineEdit *twofucaidanjiaLineEdit;
    QLineEdit *twofucaishuliangLineEdit;
    QLineEdit *tworukuzongjineLineEdit;
    QLineEdit *twofucaiguigeLineEdit;
    QLineEdit *twofucaidanweiLineEdit;
    QLineEdit *twolingliaodanweiLineEdit;
    QLineEdit *twosonghuorenyuanLineEdit;
    QLineEdit *twoshiyongbuweiLineEdit;
    QLineEdit *twolianxifangshiLineEdit;
    QLineEdit *twolururenyuanLineEdit;
    QDateEdit *twolururiqiDateEdit;
    QLineEdit *twolukubeizhuLineEdit;

    QDateEdit *twodateEdit1;
    QDateEdit *twodateEdit2;

    QPushButton *twochaxun;
    QPushButton *daochuBtn2;

    QCheckBox *twofucaidaleiCheckBox;
    QComboBox *twofudaleiCombox;
    QCheckBox *twofucaixiaoleiCheckBox;
    QComboBox *twofucaixiaoleiCombox;
    QCheckBox *twofucaimingchengCheckBox;
    QComboBox *twofucaimingchengCombox;
    QCheckBox *twosonghuorenyuanCheckBox;
    QComboBox *twosonghuorenyuanCombox;

    QTableView          *twofahuoView;
    QStandardItemModel  *twofahuoModel = NULL;

private slots:
    void twoon_onechaxun();
    void on_toExcell2();
    void twoShow_fahuoSupplyclick();
    void twoon_fucaidalei();
    void twoon_fucaixiaolei();
    void twoon_fucaidanjia();
    void twoon_fucaishuliang();

private:
    void twocreateAction();
    void twocreateTool();

private slots:
    void twoon_newAction();
    void twoon_newAction_plus();
    void twoon_saveAction();
    void twoon_updateAction();
    void twoon_deleteAction();
     /************出库结束********************/


    /********************库存**********************/
private:
    QPushButton *threechaxun;
    QPushButton *daochuBtn3;

    QCheckBox *threefucaidaleiCheckBox;
    QComboBox *threefudaleiCombox;
    QCheckBox *threefucaixiaoleiCheckBox;
    QComboBox *threefucaixiaoleiCombox;
    QCheckBox *threefucaimingchengCheckBox;
    QComboBox *threefucaimingchengCombox;
    const char          *threeLuRuSQL;
    QTableView          *threefahuoView;
    QStandardItemModel  *threefahuoModel = NULL;
private slots:
    void threeon_onechaxun();
    void on_toExcell3();
    /********************库存结束**********************/
};

#endif // FUCAIRUKUDLG_H
