#ifndef CAIGOURUKUMINGXIDLG_H
#define CAIGOURUKUMINGXIDLG_H

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

class caigourukumingxiDlg : public QDialog
{
    Q_OBJECT
public:
    explicit caigourukumingxiDlg(QWidget *parent = 0);
    ~caigourukumingxiDlg();

signals:

private:
    QTabWidget          *tabWidget;
    QWidget             *tongfahuomingxi;
    QWidget             *duizhangjilu;

private:
    QString                      DetailSQL;
    QTableView                  *DetailView;
    QStandardItemModel          *DetailModel = NULL;

    QString                     searchPurchaseReceiptSQL;

    QDateTimeEdit               *DateTimeEdit1;
    QDateTimeEdit               *DateTimeEdit2;

    QCheckBox                   *SupplierCheck;
    QCheckBox                   *MaterialCheck;

    QComboBox                   *SupplierCombox;
    QComboBox                   *MaterialCombox;

    QPushButton                 *FindBtn;
    QPushButton                 *ExportBtn;

    myExcel                     *ViewToExcel;

private:
    QLineEdit   *StorageListLineEdit;
    QLineEdit   *SupplierLineEdit;
    QLineEdit   *MaterialNameLineEdit;
    QLineEdit   *SpecificationModelLineEdit;
    QLineEdit   *GrossWeightLineEdit;
    QLineEdit   *GrossWeightTimeLineEdit;
    QLineEdit   *TareLineEdit;
    QLineEdit   *TareWeightTimeLineEdit;
    QLineEdit   *BuckleLineEdit;
    QLineEdit   *StorageCubeLineEdit;
    QLineEdit   *StoragefactoryLineEdit;
    QLineEdit   *PositionLineEdit;
    QLineEdit   *LicensePlateNumberLineEdit;
    QLineEdit   *StorageKGLineEdit;
    QLineEdit   *NetWeightLineEdit;
    QLineEdit   *UnitPriceLineEdit;

    QPushButton *AllSelectedBtn;
    QPushButton *AllCancelBtn;
    QPushButton *AllConfirmBtn;
    QPushButton *ConfirmBtn;

private:
    const char          *SQL3;

    QTableView          *ReconciliationView;
    QStandardItemModel  *ReconciliationModel = NULL;

    QDateTimeEdit       *updateTime1;
    QDateTimeEdit       *updateTime2;

    QPushButton         *threeFindBtn;

private:
    void CreateCaigourukuMingxi();
    void CreateDuizhang();
    void CreateDuizhangJiLu();


private slots:
    void on_FindBtn();
    void on_ExportBtn();
    void on_doubleClickDetailView(QModelIndex index);
    void on_AllSelectedBtn();
    void on_AllCancelBtn();
    void on_AllConfirmBtn();
    void on_ConfirmBtn();
    void on_threeFindBtn();

private:
    void setModelStyle(QStandardItemModel *model, int column);

};

#endif // CAIGOURUKUMINGXIDLG_H
