#ifndef CAIGOUHETONGGUANLIDLG_H
#define CAIGOUHETONGGUANLIDLG_H

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
#include <QDebug>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QKeyEvent>
#include <QGroupBox>
#include <QToolBar>
#include <QAction>
#include <QMessageBox>
#include <QString>
#include "mymysql.h"
#include "pubfunc.h"
#include "mytcpsocket.h"
#include "mycheckboxdelegate.h"

class caigouhetongguanliDlg : public QDialog
{
    Q_OBJECT
public:
    explicit caigouhetongguanliDlg(QWidget *parent = 0);
    void refresh();

private:
    QTabWidget          *tabWidget;
    QWidget             *SupplierWidget;
    QWidget             *ContractWidget;
    QWidget             *PurchasePriceCorrectWidget;

private:
    QAction             *newAction;
    QAction             *saveAction;
    QAction             *updateAction;
    QAction             *deleteAction;
    QToolBar            *toolBar;

public:
    QComboBox           *combox;

private:
    const char          *SQL1;
    QTableView          *SupplierView;
    QStandardItemModel  *SupplierModel = NULL;
    QLineEdit           *SupplierNumberLineEdit;
    QLineEdit           *SupplierNameLineEdit;
    QLineEdit           *ContactLineEdit;
    QLineEdit           *TelephoneLineEdit;
    QLineEdit           *BusinessLicenseLineEdit;
    QLineEdit           *OrganizationCodeLineEdit;
    QLineEdit           *BankLineEdit;
    QLineEdit           *AccountNumberLineEdit;
    QLineEdit           *PayeeLineEdit;
    QLineEdit           *FaxLineEdit;
    QLineEdit           *AddressLineEdit;

private:
    const char          *SQL2;
    int                  material_count;
    QGroupBox           *MaterialListBox;
    QString              twoMaterialAndSpecifications;
    QString              SupplierContractNumber;
    QLineEdit           *twoSupplierLineEdit;
    QDateTimeEdit       *twoStartUseTimeEdit;
    QGroupBox           *twoMaterialGroupBox;
    QPushButton         *twoMaterialQuxiaoBtn;
    QPushButton         *twoMaterialQuanxuanBtn;
    QPushButton         *twoMaterialSaveBtn;
    QPushButton         *twoMaterialDeleteBtn;
    QPushButton         *twoNewMaterialBtn;
    QWidget             *twoMaterialWidget;
    QList<QCheckBox *>   twoMaterialCheckBoxList;
    QList<QLineEdit *>   twoMaterialLineEditList;
    QTreeView           *twoMaterialTreeView;
    QStandardItemModel  *twoMaterialTreeModel = NULL;

    QAction             *twoDeleteEngineerAction;

private:
    const char          *SQL3;

    QDateTimeEdit       *threeDateTimeEdit1;
    QDateTimeEdit       *threeDateTimeEdit2;

    QDateTimeEdit       *threeUpdateDateTimeEdit1;
    QDateTimeEdit       *threeUpdateDateTimeEdit2;

    QPushButton         *threeUpdateBtn;
    QPushButton         *threeQuanXuanBtn;
    QPushButton         *threeQuXiaoBtn;
    QPushButton         *threeFindBtn;

    QTableView          *threeSupplierListView;
    QStandardItemModel  *threeSupplierListModel = NULL;

    QTableView          *threeUpdateDetailInfoView;
    QStandardItemModel  *threeUpdateDetailInfoModel = NULL;



private:
    void keyPressEvent(QKeyEvent *event);
    void creatTabPage_Supplier();
    void creatTabPage_Contract();
    void creatTabPage_PurchasePriceCorrect();

private:
    void createAction();
    void createTool();

private slots:
    void on_newAction();
    void on_newAction_plus();
    void on_saveAction();
    void on_updateAction();
    void on_deleteAction();
    void ShowSupplyclick();
    void ShowSupplyDoubleClick();

private slots:
    void on_twoMaterialQuxiaoBtn();
    void on_twoMaterialQuanxuanBtn();
    void on_twoMaterialSaveBtn();
    void on_twoMaterialDeleteBtn();
    void on_twoNewMaterialBtn();
    void twoMaterialTreeViewClick(const QModelIndex index);

private slots:
    void on_threeQuanXuanBtn();
    void on_threeQuXiaoBtn();
    void on_threeUpdateBtn();
    void on_threeFindBtn();

private:
    void init_MaterialWidget();
};

#endif // CAIGOUHETONGGUANLIDLG_H
