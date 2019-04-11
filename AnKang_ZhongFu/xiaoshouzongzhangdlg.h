#ifndef XIAOSHOUZONGZHANGDLG_H
#define XIAOSHOUZONGZHANGDLG_H

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
#include <QMessageBox>
#include <QGroupBox>
#include <QButtonGroup>
#include <QPushButton>
#include <QRadioButton>
#include <QString>
#include "mymysql.h"
#include "mytcpsocket.h"
#include "mycombobox.h"

class xiaoshouzongzhangDlg : public QDialog
{
    Q_OBJECT
public:
    explicit xiaoshouzongzhangDlg(QWidget *parent = 0);
    void refresh();

private:
    QTabWidget          *tabWidget;
    QWidget             *xiaoshouzongzhang;
    QWidget             *kehuqichushezhi;
    QWidget             *fukuanshezhi;
    QWidget             *chonghongshezhi;
    QWidget             *zhangkuanjiecun;


private:
    void keyPressEvent(QKeyEvent *event);
    void creatTabPage1();
    void creatTabPage2();
    void creatTabPage3();
    void creatTabPage4();
    void creatTabPage5();


private:
    const char          *SQL1;

    QLineEdit           *CustomerLineEdit;
    QLineEdit           *EngineerLineEdit;
    QLineEdit           *RemainingSumLineEdit;

    QDateTimeEdit       *BalanceDateEdit;

    QPushButton         *BalanceBtn;

    QCheckBox           *CustomerCheckBox;
    QComboBox           *CustomerNameCombox;
    QPushButton         *FindBtn;

    QTableView          *oneView;
    QStandardItemModel  *oneModel = NULL;

private:
    const char          *SQL2;

    QLineEdit           *twoCustomerLineEdit;
    QLineEdit           *twoEngineerLineEdit;
    QLineEdit           *twoInitialBalanceLineEdit;
    QDateTimeEdit       *twoBalanceDateTime;
    QPushButton         *twoUpdateBtn;

    QCheckBox           *twoCustomerCheckBox;
    QComboBox           *twoCustomerCombox;
    QPushButton         *twoFindBtn;

    QTableView          *twoView;
    QStandardItemModel  *twoModel = NULL;

private:
    const char          *SQL3;

    QComboBox           *threeCustomerCombox;
    QComboBox           *threeEngineerCombox;
    QLineEdit           *threeTransferAccountLineEdit;
    QComboBox           *threeTransferTypeCombox;
    QDateTimeEdit       *threeTransferDate;
    QPushButton         *threeConfirmBtn;

    QCheckBox           *threeFindCustomerCheckBox;
    QComboBox           *threeFindCustomerCombox;
    QDateTimeEdit       *threeOperatingDate1;
    QDateTimeEdit       *threeOperatingDate2;
    QPushButton         *threeFindBtn;


    QTableView          *threeView;
    QStandardItemModel  *threeModel = NULL;

private:
    const char          *SQL4;

    QComboBox           *fourCustomerCombox;
    QComboBox           *fourEngineerCombox;
    QLineEdit           *fourChongHongAccountLineEdit;
    QLineEdit           *fourRemarksLineEdit;
    QPushButton         *fourConfirmBtn;

    QCheckBox           *fourFindCustomerCheckBox;
    QComboBox           *fourFindCustomerCombox;
    QDateTimeEdit       *fourOperatingDate1;
    QDateTimeEdit       *fourOperatingDate2;
    QPushButton         *fourFindBtn;


    QTableView          *fourView;
    QStandardItemModel  *fourModel = NULL;

private:
    const char          *SQL5;

    QDateTimeEdit       *fiveBalanceDate1;
    QDateTimeEdit       *fiveBalanceDate2;

    QCheckBox           *fiveCustomerCheck;
    QCheckBox           *fiveEngineerCheck;
    QComboBox           *fiveCustomerCombox;
    QComboBox           *fiveEngineerCombox;

    QPushButton         *fiveFindBtn;

    QTableView          *fiveBalanceView;
    QStandardItemModel  *fiveBalanceModel = NULL;



private slots:
    void on_BalanceBtn();
    void on_FindBtn();
    void on_oneView();
    void on_BalanceDateEdit();

private slots:
    void on_doubleClickTwoView();
    void on_twoUpdateBtn();
    void on_twoFindBtn();

private slots:
    void on_threeConfirmBtn();
    void on_threeFindBtn();
    void on_threeCustomerCombox();

private slots:
    void on_fourConfirmBtn();
    void on_fourFindBtn();
    void on_fourCustomerCombox();

private slots:
    void on_fiveBtn();

};

#endif // XIAOSHOUZONGZHANGDLG_H
