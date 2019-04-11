#ifndef GUOBANGRUKUDLG_H
#define GUOBANGRUKUDLG_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QStandardItemModel>
#include <QTableView>
#include <QComboBox>
#include <QTabWidget>
#include <QTime>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QTextBrowser>
#include <QCheckBox>
#include <QLCDNumber>
#include <QBrush>
#include <QPushButton>
#include <QDateTimeEdit>
#include <QDateEdit>
#include <QLibrary>
#include <QGroupBox>
#include <QTableWidget>
#include <QToolButton>
#include <QCompleter>
#include <QAction>
#include <QToolBar>
#include <QString>
#include <QDate>
#include <QListView>
#include <QDateTime>
#include <QFont>
#include <QColor>
#include <QSizePolicy>
#include <QAbstractItemModel>
#include <QMessageBox>
#include <QDebug>
#include <QPalette>
#include <QByteArray>
#include <QtSerialPort/QSerialPort>//提供访问串口的功能
#include <QtSerialPort/QSerialPortInfo>//提供系统中存在的串口的信息
#include "mymysql.h"
#include "pubfunc.h"
#include "mycompleterlineedit.h"
#include "mycombobox.h"
#include "playviedo.h"
#include "mytcpsocket.h"

class guobangrukuDlg : public QDialog
{
    Q_OBJECT
public:
    explicit guobangrukuDlg(QWidget *parent = 0);
    ~guobangrukuDlg();
    void refresh();

private:
    void keyPressEvent(QKeyEvent *event);

private:
    void creatTabPage1();
    void creatTabPage2();
    void creatTabPage3();
    void creatTabPage4();
    void creatTabPage5();
    void createAction1();
    void createTool1();
    void createAction3();
    void createTool3();
    void setModelStyle(QStandardItemModel *model);
    void setModelStyle3(QStandardItemModel *model);

private slots:
    void on_newAction1();
    void on_newAction1_plus();
    void on_updateAction1();
    void on_deleteAction1();
    void on_checkAction1();
    void on_printAction1();
    void on_newAction3();
    void on_newAction3_plus();
    void on_slAction3();
    void on_updateAction3();
    void on_deleteAction3();
    void on_printAction3();
    void on_cancelAction3();
    void ShowSupplyclick1();
    void ShowSupplyclick2();
    void ShowSupplyclick3();
    void ShowSupplyclick4();
    void combo2Correspond();
    void on_chengmaozhong();
    void on_chengpizhong();
    void on_baocunmaozhong();
    void on_baocunpizhong();
    void NetWeightDisplay();
    void StorageQuantityDispaly();
    void on_twoFindBtn();
    void on_fourchaxun();
    void on_chengmaozhong3();
    void on_baocunmaozhong3();
    void on_chengpizhong3();
    void on_baocunpizhong3();
    void on_dakaichuankou();
    void on_guanbichuankou();

    void on_threeLicensePlateCombox();
    void appendBuffer();
    int  read_data();

    void on_fiveUpdateBtn();



private:
    const char  *SQL1;
    const char  *SQL2;
    QString      SQL3;
    const char  *SQL4;


    QToolBar    *toolBar1;
    QToolBar    *toolBar3;
    QTabWidget  *tabWidget;
    QWidget     *caigourukudan;
    QWidget     *rukudanchaxun;
    QWidget     *guancheguobang;
    QWidget     *guancheguobangjilv;
    QWidget     *dibangcanshushezhi;

private:
    QLibrary            *library;
    QAction             *newAction1;
    QAction             *updateAction1;
    QAction             *deleteAction1;
    QAction             *checkAction1;
    QAction             *printAction1;

    QAction             *newAction3;
    QAction             *slAction3;
    QAction             *updateAction3;
    QAction             *deleteAction3;
    QAction             *printAction3;
    QAction             *cancelAction3;

private:
    QString              cardNo;
    QCompleter          *completer;
    QDateTime           *rukudate;
    QLineEdit           *oneRecordNoLineEdit;
    QLineEdit           *oneGrossWeightLineEdit;
    QLineEdit           *oneGrossWeightTimeLineEdit;
    QLineEdit           *oneTareWeightLineEdit;
    QLineEdit           *oneNetWeightTimeLineEdit;
    QLineEdit           *oneNetWeightLineEdit;
    QLineEdit           *oneBuckleLineEdit;
    QLineEdit           *oneStorageKGLineEdit;
    QLineEdit           *oneStorageCubeLineEdit;
    QLineEdit           *oneDeliveryNoLineEdit;
    QLineEdit           *lineEdit16;//车牌号
    MyCompleterLineEdit *oneLicensePlateLineEdit;
    QLineEdit           *oneDeliveryManLineEdit;
    QLineEdit           *oneTelephoneLineEdit;
    QLineEdit           *oneRemarksLineEdit;
    QComboBox           *onePlantNameComBox;
    QComboBox           *oneMatNameComBox;
    QComboBox           *oneSupplierComBox;
    QComboBox           *onePositionNameComBox;
    QComboBox           *oneSpecificationComBox;
    QPushButton         *oneGrossWeightBtn;
    QPushButton         *oneTareWeightBtn;
    QPushButton         *oneSaveGrossWeightBtn;
    QPushButton         *oneSaveNetWeightBtn;
    QTableView          *view;
    QLCDNumber          *LCDnumber;
    QStandardItemModel  *model = NULL;
    QString str7,str8,str9,str10,str11,str12,str13,str14,str15,str16,str17,str18,str19;
    QString str,str1,str2,str3,str4,str5;
    QString WarehousingDate;

    PlayViedo           *video;

private:
    QCheckBox           *twoMaterialNameCheckBox;
    QCheckBox           *twoSupplierCheckBox;
    QLabel              *totalTrainLabelNum;
    QPushButton         *twoFindBtn;
    QDateEdit           *twodt1;
    QDateEdit           *twodt2;
    QComboBox           *twoPlantNameCombox;
    QComboBox           *twoMaterialCombox;
    QComboBox           *twoSupplierCombox;
    QTableView          *twoview;
    QStandardItemModel  *twomodel = NULL;

private:
    QLCDNumber          *threeLCDnumber;
    QPushButton         *threeGrossWeightBtn;
    QPushButton         *threeSaveGrossWeightBtn;
    QPushButton         *threeTareWeightBtn;
    QPushButton         *threeSaveTareWeightBtn;
    QComboBox           *threeLicensePlateCombox;
    QLineEdit           *threeRecordNoLineEdit;
    QLineEdit           *threeCustomerNameLineEdit;
    QLineEdit           *threeEngineerLineEdit;
    QLineEdit           *threeGrossWeightLineEdit;
    QLineEdit           *threeGrossWeightTimeLineEdit;
    QLineEdit           *threeTareWeightLineEdit;
    QLineEdit           *threeTareWeightTimeLineEdit;
    QLineEdit           *threeNetWeightLineEdit;
    QLineEdit           *threeUnitWeightLineEdit;
    QLineEdit           *threeVolumeLineEdit;
    QLineEdit           *threeStrengthGradeLineEdit;
    QLineEdit           *threeWeightPersonLineEdit;
    QLineEdit           *threeRemarksLineEdit;
    QLineEdit           *threeDriverLineEdit;
    QTableView          *threeview;
    QStandardItemModel  *threemodel = NULL;
    QString              threeUnit;
    QString              threeRecordNum;
    QString              threeReceiptVolume;
    QString              threeShippingVolume;
    QString              threeActualProductionVolume;
    QCheckBox           *threeManualInPutCheckBox;

private:
    QCheckBox           *fourcheckBox;
    QPushButton         *fourchaxun;
    QDateEdit           *fourdate1;
    QDateEdit           *fourdate2;
    QComboBox           *fourcombo;
    QTableView          *fourview;
    QStandardItemModel  *fourmodel = NULL;

private:
    QString              buffer;
    QComboBox           *fivecombo1;
    QComboBox           *fivecombo2;
    QComboBox           *fivecombo3;
    QComboBox           *fivecombo4;
    QComboBox           *fivecombo5;
    QLineEdit           *fivelineEdit6;
    QLineEdit           *fivelineEdit7;
    QPushButton         *dakaichuankou;
    QPushButton         *guanbichuankou;
    QSerialPort         *serial;

    QLineEdit           *DVRIPLineEdit;
    QLineEdit           *IPC1LineEdit;
    QLineEdit           *IPC2LineEdit;
    QLineEdit           *IPC3LineEdit;
    QPushButton         *fiveUpdateBtn;


};

#endif // GUOBANGRUKUDLG_H
