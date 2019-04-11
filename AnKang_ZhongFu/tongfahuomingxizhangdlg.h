#ifndef TONGFAHUOMINGXIZHANGDLG_H
#define TONGFAHUOMINGXIZHANGDLG_H

#include <QDialog>
#include <QString>
#include <QTableView>
#include <QStandardItemModel>
#include <QPushButton>
#include <QDateTimeEdit>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QTabWidget>
#include <QGridLayout>
#include "mymysql.h"
#include "myexcel.h"
#include "mycombobox.h"
#include "mycheckboxdelegate.h"


class tongfahuomingxizhangDlg : public QDialog
{
    Q_OBJECT
public:
    explicit tongfahuomingxizhangDlg(QWidget *parent = 0);
    //~tongfahuomingxizhangDlg();

signals:

private:
    QTabWidget          *tabWidget;
    QWidget             *tongfahuomingxi;
    QWidget             *duizhang;
    QWidget             *duizhangjilu;

private:
    QString                      DetailSQL;
    QTableView                  *DetailView;
    QStandardItemModel          *DetailModel = NULL;

    QDateTimeEdit               *DateTimeEdit1;
    QDateTimeEdit               *DateTimeEdit2;

    QCheckBox                   *CustomerCheck;
    QCheckBox                   *EngineerCheck;

    QComboBox                   *CustomerCombox;
    QComboBox                   *EngineerCombox;

    QCheckBox                   *jiashiyuanCheckBox5;
    QComboBox                   *jiashiyuanComBox5;


    QPushButton                 *FindBtn;
    QPushButton                 *ExportBtn;

    myExcel                     *ViewToExcel;

private:
    QLineEdit   *TaskListLineEdit;
    QLineEdit   *RecordNoLineEdit;
    QLineEdit   *RealCustomerLineEdit;
    QLineEdit   *DeliverCustomerLineEdit;
    QLineEdit   *EngineerNameLineEdit;
    QLineEdit   *PlannedQuantityLineEdit;
    QLineEdit   *ShippingVolumeLineEdit;
    QLineEdit   *ReceiptVolumeLineEdit;
    QLineEdit   *ProductVolumeLineEdit;
    QLineEdit   *RemainingMaterialLineEdit;
    QLineEdit   *StrengthGradeLineEdit;
    QLineEdit   *UnitNoLineEdit;
    QLineEdit   *DriverLineEdit;
    QLineEdit   *VehicleLineEdit;
    QLineEdit   *OutboundTimeLineEdit;
    QLineEdit   *ContractNumberLineEdit;
    QLineEdit   *DistanceLineEdit;
    QLineEdit   *FreightPriceLineEdit;
    QLineEdit   *PriceLineEdit;
    QLineEdit   *renwudanhaoEdit;
    QLineEdit   *CumulativeNumberLineEdit;
    QLineEdit   *CumulativeVolumeLineEdit;
    QLineEdit   *PhbUnitWeightLineEdit;
    QLineEdit   *RealUnitWeightLineEdit;

    QPushButton *AllConfirmBtn;
    QPushButton *ConfirmBtn;
    QPushButton *CancelBtn;

    QPushButton *twoAllSelectedBtn;
    QPushButton *twoAllCancelBtn;

    QComboBox   *PouringMethodCombox;

    QTableView          *ConsumeView;
    QStandardItemModel  *ConsumeModel = NULL;
    QTableView          *ProductNoticeView;
    QStandardItemModel  *ProductNoticeModel = NULL;

private:
    const char          *SQL3;

    QTableView          *ReconciliationView;
    QStandardItemModel  *ReconciliationModel = NULL;

    QDateTimeEdit       *updateTime1;
    QDateTimeEdit       *updateTime2;

    QPushButton         *threeFindBtn;

private:
    void CreateTongfahuomingxi();
    void CreateDuizhang();
    void CreateDuizhangJiLu();

private slots:
    void on_FindBtn();
    void on_ExportBtn();
    void on_doubleClickDetailView(QModelIndex index);
    void on_doubleClickProductNoticeView(QModelIndex index);
    void on_AllConfirmBtn();
    void on_ConfirmBtn();
    void on_CancelBtn();
    void on_twoAllSelectedBtn();
    void on_twoAllCancelBtn();

    void on_threeFindBtn();

private:
    void setModelStyle(QStandardItemModel *model, int column);
    void setProductNoticeViewModelStyle(QStandardItemModel *model);

};

#endif // TONGFAHUOMINGXIZHANGDLG_H
