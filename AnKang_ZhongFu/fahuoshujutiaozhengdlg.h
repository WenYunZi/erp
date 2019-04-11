#ifndef FAHUOSHUJUTIAOZHENGDLG_H
#define FAHUOSHUJUTIAOZHENGDLG_H

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
#include <QToolBar>
#include <QAction>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QKeyEvent>
#include <QTextEdit>
#include <QMessageBox>
#include <QGroupBox>
#include <QButtonGroup>
#include <QPushButton>
#include <QRadioButton>
#include <QString>
#include "mymysql.h"
#include "mytcpsocket.h"
#include "mycombobox.h"


class fahuoshujutiaozhengDlg : public QDialog
{
    Q_OBJECT
public:
    explicit fahuoshujutiaozhengDlg(QWidget *parent = 0);
    void refresh();

private:
    QTabWidget          *tabWidget;
    QWidget             *qianshoutiaozheng;
    QWidget             *qianshoutiaozhengjilu;
    QWidget             *yunjutiaozheng;
    QWidget             *yunjutiaozhengjilu;
    QWidget             *zhuanchangyunju;

private:
    const char          *SQL1;
    QLineEdit           *lineEdit1;
    QLineEdit           *lineEdit2;
    QLineEdit           *lineEdit3;
    myComboBox          *comBox1;
    QComboBox           *comBox2;
    QDateTimeEdit       *datetimeEdit1;
    QDateTimeEdit       *datetimeEdit2;
    QPushButton         *chaxunBtn;
    QPushButton         *qianshoutiaozhengBtn;
    QTableView          *view;
    QStandardItemModel  *model = NULL;
    QCheckBox           *checkBox1;
    QCheckBox           *checkBox2;

    QString              CustomerName;
    QString              Product;
    QString              OriginalFormula;
    QString              DeliveryTime;
    QString              ProjectName;
    QString              CheNo;



private:
    const char          *SQL2;
    myComboBox          *twocomBox1;
    QComboBox           *twocomBox2;
    QComboBox           *twocomBox3;
    QDateTimeEdit       *twodateEdit1;
    QDateTimeEdit       *twodateEdit2;
    QPushButton         *twochaxunBtn;
    QCheckBox           *twocheckBox1;
    QCheckBox           *twocheckBox2;
    QCheckBox           *twocheckBox3;
    QTableView          *twoview;
    QStandardItemModel  *twomodel = NULL;

private:
    const char          *SQL3;
    myComboBox          *threecomBox1;
    QComboBox           *threecomBox2;
    QComboBox           *threecomBox3;
    QDateTimeEdit       *threedatetimeEdit1;
    QDateTimeEdit       *threedatetimeEdit2;
    QPushButton         *threechaxunBtn;
    QPushButton         *threebuyunfeiBtn;
    QCheckBox           *threecheckBox1;
    QCheckBox           *threecheckBox2;
    QCheckBox           *threecheckBox3;
    QTableView          *threeview;
    QStandardItemModel  *threemodel = NULL;
    QLineEdit           *threelineEdit1;
    QLineEdit           *threelineEdit2;

private:
    const char          *SQL4;
    QComboBox           *fourcomBox1;
    QComboBox           *fourcomBox2;
    QComboBox           *fourcomBox3;
    QDateEdit           *fourdateEdit1;
    QDateEdit           *fourdateEdit2;
    QPushButton         *fourchaxunBtn;
    QCheckBox           *fourcheckBox1;
    QCheckBox           *fourcheckBox2;
    QCheckBox           *fourcheckBox3;
    QTableView          *fourview;
    QStandardItemModel  *fourmodel = NULL;

private:
    QAction             *newAction;
    QAction             *saveAction;
    QAction             *updateAction;
    QAction             *deleteAction;
    QToolBar            *toolBar;
    const char          *SQL5;
    QComboBox           *fiveCombox1;
    QComboBox           *fiveCombox2;
    QDateEdit           *fiveDateEdit;
    QLineEdit           *fiveLineEdit;
    QTableView          *fiveview;
    QStandardItemModel  *fivemodel = NULL;
    QString              fiveID;

private:
    void createAction();
    void createTool();

private:
    void keyPressEvent(QKeyEvent *event);
    void creatTabPage1();
    void creatTabPage2();
    void creatTabPage3();
    void creatTabPage4();
    void creatTabPage5();

private slots:
    void on_newAction();
    void on_saveAction();
    void on_updateAction();
    void on_deleteAction();

private slots:
    void ShowSupplyclick();
    void ShowSupplyclick3();
    void ShowSupplyclick5();
    void on_chaxunBtn();
    void on_qianshoutiaozhengBtn();
    void on_twochaxunBtn();
    void on_comBox1Correspond();
    void on_twocomBox1Correspond();
    void on_threeQuerenBtn();
    void on_threeChaXunBtn();
    void on_fourChaXunBtn();
    void on_fiveCombox1Response();
};

#endif // FAHUOSHUJUTIAOZHENGDLG_H
