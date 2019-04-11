#ifndef CHELIANGWEIXIUGUANLI_H
#define CHELIANGWEIXIUGUANLI_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QTableView>
#include <QComboBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QString>
#include <QToolBar>
#include <QAction>
#include "mymysql.h"
#include "pubfunc.h"
#include "cheliangweixiudelegate.h"
#include "mytcpsocket.h"
#include <QComboBox>
#include <QWidget>
#include <QTabWidget>
#include <QDateEdit>
#include <QDebug>
#include <QGroupBox>
#include "mycombobox.h"
#include "myexcel.h"

class cheliangweixiuguanli : public QDialog
{
    Q_OBJECT
public:
    explicit cheliangweixiuguanli(QWidget *parent = 0);
    ~cheliangweixiuguanli();
    void refresh();

private:
    void keyPressEvent(QKeyEvent *event);
    void creatTabPage1();
    void creatTabPage2();
    void creatTabPage22();
    void creatTabPage3();
    void creatTabPage4();
    void creatTabPage5();
    void creatTabPage6();

private:
    QTabWidget          *tabWidget;
    QWidget             *waichuweixiuduizhangdan;
    QWidget             *weixiujilu;
    QWidget             *cheliangweixiuribaobiao;
    QWidget             *jiayoumingxiliangbiao;
    QWidget             *xingchejilubiao;
    QWidget             *kaohezongbiao;
    QWidget             *peizhiyemian;
    myExcel             *view2Excel;

/***********************Start creatTabPage1*****************************/
private:
    const char          *SQL;
    QLineEdit           *weixiushijianlineEdit;
    QLineEdit           *gongshifeiLineEdit;
    QLineEdit           *gonghuofangLineEdit;
    QLineEdit           *lurushijianlineEdit;

    QComboBox           *chehaoBombox;
    QComboBox           *weiXiuStateComBox;
    QComboBox           *chepaihaocomBox;
    QComboBox           *gonghuofangcomBox;
    QComboBox           *chepaihaocomBox1;
    QComboBox           *changdiComBox;

    QComboBox           *sijiBox;

    QTableWidget        *view1;

    QAction             *zengjiaAction;
    QAction             *shanchuAction;

private:
    const char          *SQL2;
    QCheckBox           *checkBox1;
    QCheckBox           *checkBox2;
    QComboBox           *twocomBox;
    QDateEdit           *twodateEdit1;
    QDateEdit           *twodateEdit2;
    QPushButton         *twoBtn;
    QTableView          *twoview;
    QStandardItemModel  *twomodel = NULL;

private:
    const char          *SQL3;
    QCheckBox           *shijianCheckBox;
    QCheckBox           *chepaiCheckBox;
    QCheckBox           *gonghuofangCheckBox ;
    QCheckBox           *weixiuCheckBox;
    QCheckBox           *peijianCheckBox;
    QCheckBox           *threecheckBox5;
    QComboBox           *threechepaihaocomBox;
    QComboBox           *threeweixiuxiangmucomBox;
    QComboBox           *threepeijiancomBox;
    QComboBox           *threechangdicomBox;
    QDateTimeEdit       *shijianDateEdit1;
    QDateTimeEdit       *shijianDateEdit2;
    QPushButton         *cheliangweixiumingxiBtn;
    QPushButton         *daochuBtn;
    QPushButton         *chaxunBtn;
    QLineEdit           *zongjilineEdit;
    QLabel              *zongjiLabel2;
    QTableView          *threeview;
    QStandardItemModel  *threemodel = NULL;

private:
    QAction             *newAction;
    QAction             *saveAction;
    QAction             *updateAction;
    QAction             *deleteAction;
    QToolBar            *toolBar;

private slots:
    void on_newAction();
    void on_saveAction();
    void on_updateAction();
    void on_deleteAction();
    void ShowSupplyclick();
    void ON_Sum1();
private slots:
    void on_mingxichaxun();
    void on_toExcell();
    void chepai2ON_xingming1();
    void ON_xingming2chepai1();
    void on_chaxunBtn();


private:

    void createAction();
    void createTool();
/***********************End creatTabPage1*******************************/
/***********************Start creatTabPage2*****************************/
private:
    const char          *TabPageSQL2;
    QLineEdit           *weixiushijianlineEdit2;

    QCheckBox           *chehaoCheckBox21;
    QComboBox           *chehaoComBox21;

    QComboBox           *chepaihaocomBox2;
    QComboBox           *weiXiuStateComBox2;
    QComboBox           *shiyongrenComBox2;
    QComboBox           *danweiComBox2;

    QLineEdit           *shuliangLineEdit2;
    QLineEdit           *beizhulineEdit2;
    QLineEdit           *lurushijianlineEdit2;

    QPushButton         *daochuBtn2;
    QLabel              *zongjiLabe22;
    QPushButton         *peijianchaxunBtn2;
    QPushButton         *weixiujiluBtn2;
    QDateTimeEdit       *shijianDateEdit21;
    QDateTimeEdit       *shijianDateEdit22;

    QTableView          *Tableview2;
    QStandardItemModel  *TableviewModel2 = NULL;

private:
    void createAction2();
    void createTool2();

private slots:
     void on_toExcell2();
     void on_peijianBtn2();
     void on_newAction2();
     void on_saveAction2();
     void on_updateAction2();
     void on_deleteAction2();
     void ON_chepai2xingming2();
     void ON_xingming2chepai2();

     void on_chaxunBtn2();
     void ShowSupplyclick2();
     void ON_Sum2();


private:
    QAction             *newAction2;
    QAction             *saveAction2;
    QAction             *updateAction2;
    QAction             *deleteAction2;
    QToolBar            *toolBar2;
/***********************End creatTabPage2******************************************/


/***********************Start creatTabPage22****************************************/
private:
    const char          *TabPageSQL22;

    QPushButton         *chaxunBtn22;

    QLineEdit           *LicenseNumberLineEdit22;
    QLineEdit           *MaintenanceDateEdit22;
    QLineEdit           *MaintenanceLineEdit22;
    QLineEdit           *KilometreNumberLineEdit22;
    QLineEdit           *RepairPersonnelLineEdit22;
    QLineEdit           *DriverSignatureLineEdit22;
    QLineEdit           *EntryTimeLineEdit22;
    QTableView          *Tableview22;
    QStandardItemModel  *TableviewModel22 = NULL;
private:
    QAction             *newAction22;
    QAction             *saveAction22;
    QAction             *updateAction22;
    QAction             *deleteAction22;
    QToolBar            *toolBar22;

private:
    void createAction22();
    void createTool22();
private slots:
//     void on_toExcell22();
     void on_newAction22();
     void on_saveAction22();
     void on_updateAction22();
     void on_deleteAction22();

     void ShowSupplyclick22();
     void on_chaxunBtn22();


/***********************End creatTabPage22******************************************/


/***********************Start creatTabPage3****************************************/
private:
    const char          *TabPageSQL3;

    QComboBox           *zhandianComBox3;
    QComboBox           *jiayoufangshiComBox3;
    QCheckBox           *xuanzezhandianCheckBox;
    QComboBox           *zhandianComBox32;
    QCheckBox           *jiayoufangshiCheckBox;
    QCheckBox           *chehaoCheckBox32;
    QComboBox           *jiayoufangshiComBox32;
    QComboBox           *chehaoComBox32;
    QComboBox           *chepaihaoComBox3;
    QComboBox           *xingmingComBox3;
    QComboBox           *jiayourenComBox3;

    QLineEdit           *riqiLineEdit3;
    QLineEdit           *jiayoushijianLineEdit3;
    QLineEdit           *jiayouliangLineEdit3;
    QLineEdit           *gonglishuLineEdit3;
    QLineEdit           *beizhuLineEdit3;
    QLineEdit           *lurushijianLineEdit3;
    QLineEdit           *lururenLineEdit3;

    QPushButton         *daochuBtn3;
    QLabel              *zongjiLabe32;
    QPushButton         *chaxunBtn3;
    QPushButton         *huizongBtn3;
    QPushButton         *peijianchaxunBtn3;
    QPushButton         *weixiujiluBtn3;
    QDateTimeEdit       *shijianDateEdit31;
    QDateTimeEdit       *shijianDateEdit32;

    QTableView          *Tableview3;
    QStandardItemModel  *TableviewModel3 = NULL;

private:
    void createAction3();
    void createTool3();

private slots:
     void on_toExcell3();
     void on_newAction3();
     void on_saveAction3();
     void on_updateAction3();
     void on_deleteAction3();
     void on_chaxunBtn3();
     void on_huizongBtn3();
     void ShowSupplyclick3();
     void ON_chepai2xingming3();
     void ON_xingming2chepai3();
     void ON_Sum3();

private:
    QAction             *newAction3;
    QAction             *saveAction3;
    QAction             *updateAction3;
    QAction             *deleteAction3;
    QToolBar            *toolBar3;
/***********************End creatTabPage3*****************************************/
/***********************Start creatTabPage4***************************************/
private:
    const char          *TabPageSQL41;
    const char          *TabPageSQL42;

    QLineEdit           *shijianLineEdit4;
    QLineEdit           *chehaoLineEdit4;
    QLineEdit           *xingmingLineEdit4;
    QLineEdit           *daodagongdiLineEdit4;
    QLineEdit           *checiLineEdit4;
    QLineEdit           *diaoLineEdit4;
    QLineEdit           *shengliaobujineshuLineEdit4;
    QLineEdit           *raoxiubugonglishuLineEdit4;
    QLineEdit           *beizhuLineEdit4;
    QLineEdit           *lichengLineEdit4;
    QLineEdit           *zonglichengLineEdit4;
    QLineEdit           *xiugaishijianLineEdit4;
    QLineEdit           *lururenLineEdit4;

    QPushButton         *daochuBtn4;
    QLabel              *zongjiLabe42;
    QLabel              *zongjineLabe42;
    QPushButton         *chaxunBtn4;
    QPushButton         *yunjuchaxunBtn4;
    QPushButton         *peijianchaxunBtn4;
    QPushButton         *weixiujiluBtn4;
    QDateTimeEdit       *shijianDateEdit41;
    QDateTimeEdit       *shijianDateEdit42;

    QCheckBox           *jiashiyuanCheckBox4;
    QComboBox           *jiashiyuanComBox4;
    QCheckBox           *jiashiyuanSiJiCheckBox4;
    QComboBox           *jiashiyuanSiJiComBox4;

    QTableView          *Tableview4;
    QStandardItemModel  *TableviewModel4 = NULL;

private:
    void createAction4();
    void createTool4();

private slots:
     void on_toExcell4();
     void on_updateAction4();
     void on_chaxunBtn4();
     void on_yunjuchaxunBtn4();
     void ShowSupplyclick4();
     void on_zonglicheng4();
     void ON_Sum4();

private:
    QAction             *newAction4;
    QAction             *saveAction4;
    QAction             *updateAction4;
    QAction             *deleteAction4;
    QToolBar            *toolBar4;
/***********************End creatTabPage4******************************************/
/***********************Start creatTabPage5****************************************/
private:
    const char          *TabPageSQL5;

    QLineEdit           *chehaoLineEdit5;
    QLineEdit           *jiashiyuanLineEdit5;
    QLineEdit           *yunshucishuLineEdit5;
    QLineEdit           *diaoguancishuLineEdit5;
    QLineEdit           * buzhujineLineEdit5;
    QLineEdit           *hejijineshuLineEdit5;
    QLineEdit           *kaohelichengLineEdit5;
    QLineEdit           *tiaozhenglichengLineEdit5;
    QLineEdit           *shijihaoyouLineEdit5;
    QLineEdit           *baigonglihaoyouLineEdit5;
    QLineEdit           *jieyoushuLineEdit5;
    QLineEdit           *jiangliLineEdit5;
    QLineEdit           *chaoejiangliLineEdit5;
    QLineEdit           *gongziLineEdit5;

    QLineEdit           *dayunfeiLineEdit5;
    QLineEdit           *xiaoyunfeiLineEdit5;
    QLineEdit           *dayouhaoLineEdit5;
    QLineEdit           *xiaoyouhaoLineEdit5;
    QLineEdit           *diaoguanjiageLineEdit5;


    QPushButton         *daochuBtn5;
    QLabel              *zongjiLabe52;
    QPushButton         *chaxunBtn5;
    QDateTimeEdit       *shijianDateEdit51;
    QDateTimeEdit       *shijianDateEdit52;

    QCheckBox           *jiashiyuanCheckBox5;
    QComboBox           *jiashiyuanComBox5;
    QCheckBox           *jiashiyuanSiJiCheckBox5;
    QComboBox           *jiashiyuanSiJiComBox5;

    QTableView          *Tableview5;
    QStandardItemModel  *TableviewModel5 = NULL;

private:
    void createAction5();
    void createTool5();

private slots:
     void on_toExcell5();
     void on_updateAction5();
     void on_chaxunBtn5();
     void ShowSupplyclick5();
     void ON_Sum5();

private:
    QAction             *newAction5;
    QAction             *saveAction5;
    QAction             *updateAction5;
    QAction             *deleteAction5;
    QToolBar            *toolBar5;
/*************************End creatTabPage5****************************************/

};

#endif // CHELIANGWEIXIUGUANLI_H
