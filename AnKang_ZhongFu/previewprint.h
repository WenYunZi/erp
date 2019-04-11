#ifndef PREVIEWPRINT_H
#define PREVIEWPRINT_H

#include <QDialog>
#include <QLineEdit>
#include <QPalette>
#include <QPushButton>
#include <QPixmap>
#include <QComboBox>
#include <QAxObject>
#include <QVariantList>
#include <windows.h>
#include <QMessageBox>
#include "mymysql.h"
#include "pubfunc.h"

class PreviewPrint : public QDialog
{
    Q_OBJECT
public:
    explicit PreviewPrint(QWidget *parent = 0);

private:
    QAxObject   *m_report;
    mymysql db;
    QString rwID;
    QString cheName;
    QString cheNumber;
    QString shengchanfangliang;

public:
    QLineEdit *RenwudanNoLineEdit;
    QLineEdit *JihuafangliangLineEdit;
    QLineEdit *YunjuLineEdit;
    QLineEdit *StationNumLineEdit;
    QLineEdit *lineEdit2;
    QLineEdit *ProductTimeLineEdit;
    QLineEdit *EngineerLineEdit;
    QLineEdit *PourPostionLineEdit;
    QLineEdit *CustomerLineEdit;
    QLineEdit *StrengthGradeLineEdit;
    QLineEdit *ShippingVolumeLineEdit;
    QLineEdit *CumulativeVolumeLineEdit;
    QLineEdit *CumulativeNumberLineEdit;
    QLineEdit *SlumpLineEdit;
    QLineEdit *OutboundTimeLineEdit;
    QLineEdit *PhbNumLineEdit;
    QLineEdit *DeliveryLineEdit;
    QComboBox *PourMethodCombox;
    QComboBox *VehicleCombox;
    QComboBox *DriverCombox;
    QPushButton *printBtn;
    QPushButton *cancelBtn;
    bool isPrint;

private:
    QString TaskNumber;
    QString StrengthGrade;
    QString Contacts;
    QString Customer;
    QString PouringPosition;
    QString ContactNumber;
    QString Engineering;
    QString PouringMethod;
    QString ContractCompletion;
    QString ConstructionSite;
    QString Slump;
    QString SupplyTime;
    QString Template;
    QString rongzhong;
    QString Unit;
    QString PricePerParty;
    QString ContractNumber;
    QString Distance;
    QString fahuocheci;
    QString cheTime;
    QString FreightPrice;
    QString RecordNumber;

public:
    void init(QString cheNumber, QString cheName, QString recordNum);

signals:

private slots:
    void on_VehicleCombox();
    void on_printBtn();
    void on_cancelBtn();

};

#endif // PREVIEWPRINT_H
