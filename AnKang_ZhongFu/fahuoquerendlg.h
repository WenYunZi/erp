#ifndef FAHUOQUERENDLG_H
#define FAHUOQUERENDLG_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QStandardItemModel>
#include <QTableView>
#include <QComboBox>
#include <QTabWidget>
#include <QGridLayout>
#include <QKeyEvent>
#include <QHBoxLayout>
#include <QLibrary>
#include <QVBoxLayout>
#include <QTextBrowser>
#include <QDebug>
#include <QCheckBox>
#include <QLCDNumber>
#include <QPushButton>
#include <QDateTimeEdit>
#include <QMessageBox>
#include <QDateEdit>
#include <QTimer>
#include <QToolButton>
#include "mymysql.h"
#include "pubfunc.h"
#include "mytcpsocket.h"
#include "odbcoperator.h"
#include "previewprint.h"

class fahuoquerenDlg : public QDialog
{
    Q_OBJECT
public:
    explicit fahuoquerenDlg(QWidget *parent = 0);
    ~fahuoquerenDlg();
    void refresh();

private:
    void keyPressEvent(QKeyEvent *event);

private:
    QTabWidget          *tabWidget;
    QWidget             *fahuoqueren;
    QWidget             *fahuochaxun;
    QWidget             *cheliangduilie;

private:
    QAxObject           *m_report;
    QString              Mileage;
    QString              FreightPerPrice;
    QString              RecordNumber;
    QString              ContractNumber;
    QString              Price;
    QLibrary            *library;
    QString              UnitNo;
    QString              SQL1;
    const char          *SQL2;
    QDateTimeEdit       *OutBoundTime;
    QDateTimeEdit       *ShengchanriqiTime;
    QLineEdit           *CustomerLineEdit;
    QLineEdit           *StrengthGradeLineEdit;
    QLineEdit           *EngineerNameLineEdit;
    QLineEdit           *PourPositionLineEdit;
    QLineEdit           *ContactLineEdit;
    QLineEdit           *TaskListLineEdit;
    QLineEdit           *SlumpLineEdit;
    QLineEdit           *TelephoneLineEdit;
    QLineEdit           *ShippingVolumeLineEdit;
    QLineEdit           *OperatorLineEdit;
    QLineEdit           *TemplateLineEdit;
    QLineEdit           *UnitNoLineEdit;
    QLineEdit           *RemainMatLineEdit;
    QLineEdit           *UnitWeightLineEdit;
    QLineEdit           *CumulationNumberLineEdit;

    QLineEdit           *CompleteVolumeLineEdit;
    QLineEdit           *BeizhuLineEdit;
    QLineEdit           *ConstructionSiteLineEdit;
    QString              ProductionTime;
    QPushButton         *PrintBtn;
    QPushButton         *shuaxinBtn;
    QTableView          *view;
    QStandardItemModel  *model = NULL;

    QComboBox           *VehicleCombox;
    QComboBox           *DriverCombox;
    QLineEdit           *PourMethodCombox;

private:
    QCheckBox           *twoEngineerCheckBox;
    QCheckBox           *twoProductTimeCheckBox;
    QCheckBox           *twoVehicleCheckBox;
    QCheckBox           *twoUnitCheckBox;
    QComboBox           *twoEngineerCombox;
    QComboBox           *twoVehicleCombox;
    QComboBox           *twoUnitCombox;
    QTableView          *twoview;
    QStandardItemModel  *twomodel = NULL;
    QDateTimeEdit       *twoProductTime1;
    QDateTimeEdit       *twoProductTime2;
    QPushButton         *twoFindBtn;

private:
    void creatTabPage1();
    void creatTabPage2();

private slots:
    void ShowSupplyclick();
    void ShowSupplyclick2();

    void on_VehicleCombox();
    void on_print();
    void on_fahuochaxun();
    void on_shuaxinBtn();
};

#endif // FAHUOQUERENDLG_H
