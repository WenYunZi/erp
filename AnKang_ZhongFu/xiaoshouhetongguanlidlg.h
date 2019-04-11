#ifndef XIAOSHOUHETONGGUANLIDLG_H
#define XIAOSHOUHETONGGUANLIDLG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QTextEdit>
#include <QStandardItemModel>
#include <QTableView>
#include <QListView>
#include <QStringList>
#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QKeyEvent>
#include <QTextEdit>
#include <QToolBar>
#include <QDebug>
#include <QAction>
#include <QMessageBox>
#include <QGroupBox>
#include <QButtonGroup>
#include <QPushButton>
#include <QRadioButton>
#include <QList>
#include <QTreeView>
#include <QStandardItemModel>
#include <QProgressDialog>
#include <QString>
#include <QMouseEvent>
#include <QButtonGroup>
#include <QPoint>
#include "mymysql.h"
#include "pubfunc.h"
#include "mytcpsocket.h"
#include "mycombobox.h"
#include "contractdeletedlg.h"
#include "mycheckboxdelegate.h"
#include "qcustomplot.h"

class xiaoshouhetongguanliDlg : public QDialog
{
    Q_OBJECT
public:
    explicit xiaoshouhetongguanliDlg(QWidget *parent = 0);
    void refresh();

private:
    QTabWidget          *tabWidget;
    QWidget             *hetongkehuguanli;
    QWidget             *hetonggongchengguanli;
    QWidget             *ProductNoticePriceCorrectWidget;

private:
    QAction             *newAction;
    QAction             *saveAction;
    QAction             *updateAction;
    QAction             *deleteAction;
    QAction             *checkAction;
    QToolBar            *toolBar;

private:
    const char          *SQL1;
    int                  attribute_count;
    int                  product_count;
    QLineEdit           *oneContractNoLineEdit;
    QLineEdit           *oneSettlementAmountLineEdit;
    QLineEdit           *oneRemarksLineEdit;
    QComboBox           *oneCustomerCombox;
    QComboBox           *oneContractTypeCombox;
    QDateEdit           *oneDateSignedDateEdit;
    QTextEdit           *oneSettlementTypeTextEdit;
    QCheckBox           *oneFindCustomerCheckBox;
    QCheckBox           *oneFindDateSignedCheckBox;
    QComboBox           *oneFindCustomerCombox;
    QComboBox           *oneFindContractStatusCombox;
    QDateEdit           *oneFindDateEdit1;
    QDateEdit           *oneFindDateEdit2;
    QPushButton         *oneChaxunBtn;
    QTableView          *oneView;
    QStandardItemModel  *oneModel = NULL;


private:
    const char          *SQL2;
    QGroupBox           *gongchengListBox;
    QString              twoCustomerNoStr;
    QLineEdit           *twoCustomerLineEdit;
    QLineEdit           *twoEngineerLineEdit;
    QLineEdit           *twoDistanceLineEdit;
    QLineEdit           *twoPumpFeeLineEdit;
    QDateTimeEdit       *twoStartUseTimeEdit;
    QGroupBox           *twoProductGroupBox;
    QGroupBox           *twoAttributeGroupBox;
    QPushButton         *twoAttributeQuxiaoBtn;
    QPushButton         *twoAttributeQuanxuanBtn;
    QPushButton         *twoProductQuxiaoBtn;
    QPushButton         *twoProductQuanxuanBtn;
    QPushButton         *twoEngineerSaveBtn;
    QPushButton         *twoAllEngineerSaveBtn;
    QPushButton         *twoEngineerDeleteBtn;
    QPushButton         *twoAllEngineerDeleteBtn;
    QPushButton         *twoNewEngineerBtn;
    QWidget             *twoAttributeWidget;
    QWidget             *twoProductWidget;
    QList<QCheckBox *>   twoAttributeCheckBoxList;
    QList<QLineEdit *>   twoAttributeLineEditList;
    QList<QCheckBox *>   twoProductCheckBoxList;
    QList<QLineEdit *>   twoProductLineEditList;
    QTreeView           *twoEngineerView;
    QStandardItemModel  *twoEngineerModel = NULL;

    QRadioButton        *twoProductRadBtn;
    QRadioButton        *twoAttributeRadBtn;
    QComboBox           *twoProductCombox;
    QComboBox           *twoAttributeCombox;

    QButtonGroup        *twoBtnGroup;

    QCustomPlot         *customPlot;

    QAction             *twoDeleteEngineerAction;

private:
    QString              SQL3;

    QProgressDialog     *progressDialog;
    QTimer              *timer;
    int                  currentValue;

    QDateTimeEdit       *threeDateTimeEdit1;
    QDateTimeEdit       *threeDateTimeEdit2;

    QDateTimeEdit       *threeUpdateDateTimeEdit1;
    QDateTimeEdit       *threeUpdateDateTimeEdit2;

    QCheckBox           *threeCustomerCheckBox;
    QComboBox           *threeCustomerComBox;

    QPushButton         *threeUpdateBtn;
    QPushButton         *threeQuanXuanBtn;
    QPushButton         *threeQuXiaoBtn;
    QPushButton         *threeFindBtn;
    QPushButton         *threeCustomerFindBtn;

    QTableView          *threeEngineerListView;
    QStandardItemModel  *threeEngineerListModel = NULL;

    QTableView          *threeUpdateDetailInfoView;
    QStandardItemModel  *threeUpdateDetailInfoModel = NULL;

private:
    void init_attributeWidget();
    void init_productWidget();

private:
    void keyPressEvent(QKeyEvent *event);
    void creatTabPage1();
    void creatTabPage2();
    void creatTabPage3();

private:
    void createAction();
    void createTool();

private slots:
    void on_newAction();
    void on_newAction_plus();
    void on_saveAction();
    void on_updateAction();
    void on_deleteAction();
    void on_checkAction();
    void ShowSupplyclick();
    void ShowSupplyDoubleClick();

    void on_quxiaoBtn();
    void on_quanxuanBtn();
    void on_chanpinquxiaoBtn();
    void on_chanpinquanxuanBtn();
    void on_twoEngineerSaveBtn();
    void on_twoAllEngineerSaveBtn();
    void on_twoEngineerDeleteBtn();
    void on_twoAllEngineerDeleteBtn();
    void on_twoNewEngineerBtn();

private slots:
    void on_oneChaxunBtn();
    void twoEngineerViewClick(const QModelIndex &index);

private slots:
    void on_threeQuanXuanBtn();
    void on_threeQuXiaoBtn();
    void on_threeUpdateBtn();
    void on_threeFindBtn();
    void on_threeCustomerFindBtn();

private slots:
    void ON_PrintXY();
    void my_mouseMove(QMouseEvent* event);
};

#endif // XIAOSHOUHETONGGUANLIDLG_H
