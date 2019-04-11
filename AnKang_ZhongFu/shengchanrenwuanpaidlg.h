#ifndef SHENGCHANRENWUANPAIDLG_H
#define SHENGCHANRENWUANPAIDLG_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QKeyEvent>
#include <QStandardItemModel>
#include <QTableView>
#include <QComboBox>
#include <QBrush>
#include <QTabWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QAction>
#include <QMessageBox>
#include <QTextBrowser>
#include <QCheckBox>
#include <QGroupBox>
#include <QLCDNumber>
#include <QPushButton>
#include <QTimer>
#include <QDateTimeEdit>
#include <QDateEdit>
#include <QToolButton>
#include "mymysql.h"
#include "mytcpsocket.h"
#include "pubfunc.h"
#include "mycombobox.h"

class shengchanrenwuanpaiDlg : public QDialog
{
    Q_OBJECT
public:
    explicit shengchanrenwuanpaiDlg(QWidget *parent = 0);
    ~shengchanrenwuanpaiDlg();
    void refresh();

private:
    void keyPressEvent(QKeyEvent *event);

public:
    QTabWidget          *tabWidget;

private:
    QWidget             *shengchanrenwuanpai;
    QWidget             *shengchantongzhichaxun;
    QWidget             *yianpaiweishengchan;
    QWidget             *fahuobufang;
    QWidget             *bufangjilu;
    QWidget             *zhuanliaochuli;
    QWidget             *zhuanliaojilu;
    QWidget             *gongdicheliangfenbu;
    QWidget             *zuofeijilu;

private:
    const char          *SQL1;
    QString              PricePerParty;
    QString              ContractNumber;
    QString              GZfinishCount;
    QString              GZleijicheci;
    QString              Distance;
    QString              Price;
    QString              FreightPrice;

    QLineEdit           *oneAddCheliangLineEdit;
    QLineEdit           *oneDelCheliangLineEdit;

    QLineEdit           *oneTaskListLineEdit;
    QLineEdit           *oneStrengthGradeLineEdit;
    QLineEdit           *oneContactLineEdit;
    QLineEdit           *oneRealCustomerLineEdit;
    QLineEdit           *onePouringPositionLineEdit;
    QLineEdit           *oneTelephoneLineEdit;
    QLineEdit           *oneEngineerLineEdit;
    QLineEdit           *onePouringMethodLineEdit;
    QLineEdit           *oneLeiJiFLLineEdit;
    QLineEdit           *oneFaHuoCustomerLineEdit;
    QLineEdit           *oneSlumpLineEdit;
    QLineEdit           *oneSupplyTimeLineEdit;
    QLineEdit           *oneShippingVolumeLineEdit;
    QLineEdit           *oneMotarVolumeLineEdit;
    QLineEdit           *ActualProductionVolumeLineEdit;
    QLineEdit           *oneRemainingMaterialLineEdit;
    QLineEdit           *oneLeijiCheCiLineEdit;
    QLineEdit           *oneAnPaiFlLineEdit;
    QLineEdit           *oneAnPaiCheCiLineEdit;
    QLineEdit           *oneXuKaiVolumeLineEdit;
    QLineEdit           *oneConstructionSiteLineEdit;

    QComboBox           *oneProductPartCombox;
    QComboBox           *oneUnitCombox;
    QComboBox           *oneVehicleCombox;
    QComboBox           *oneDriverCombox;
    myComboBox          *oneProjectCombox;
    myComboBox          *onePouringPositionCombox;

    QDateTimeEdit       *oneProductDatetimeEdit;
    QDateEdit           *oneSendtime1DateEdit;
    QDateEdit           *oneSendtime2DateEdit;
    QTableView          *view;
    QStandardItemModel  *model = NULL;
    QCheckBox           *oneGongChengCheckBox;
    QCheckBox           *onePouringPositionCheckBox;
    QCheckBox           *oneXiaFaTimecheckBox;
//    QCheckBox           *oneHideCompletecheckBox;
//    QCheckBox           *oneHideProductingCheckBox;
    QCheckBox           *oneHideCheck;

    QPushButton         *oneAddCheliangBtn;
    QPushButton         *oneDelCheliangBtn;
    QPushButton         *oneBuDaShuiPiaoBtn;
    QPushButton         *qitaxinxiBtn;

    QPushButton         *tongzhishengchanBtn;
    QPushButton         *chexiaoshengchanBtn;
    QPushButton         *chaxunBtn;
    QPushButton         *zuofeiBtn;
    QPushButton         *zhuanliaoBtn;
    QString              peihebimubanmingcheng;
    QString              rongzhong;
    QString              shengliaodanhao;
    QString              PlannedQuantity;
    int                  IndexOfCombox3;

    QLabel              *lastVehicleInfoLabel;
    QLabel              *TodayPlanVolumeLabel;

    QString              VehicleVolume;
    QString              anpaifangliang;
    QString              anpaicheci;
    QString              jiaozhufangfa;

    QAction             *yincangAct;
    QAction             *chexiaoyincangAct;

private:
    const char          *SQL2;
    QTableView          *twoview;
    QStandardItemModel  *twomodel = NULL;

    const char          *SQL22;
    QTableView          *twoProductingView;
    QStandardItemModel  *twoProductingModel = NULL;

    QTimer              *twoRefreshRunStateTimer;

    QLineEdit           *twoProductingRecordNoLineEdit;

    QPushButton         *twoSetProductedBtn;

    QString              twoUnitNo;

private:
    const char          *SQL3;
    QCheckBox           *threeEngineerCheckBox;
    QCheckBox           *threeProductTimeCheckBox;
    QCheckBox           *threeVehicleCheckBox;
    QCheckBox           *threeProductUnitCheckBox;
    QCheckBox           *threeInfoManCheckBox;
    QComboBox           *threeEngineerCombox;
    QComboBox           *threeVehicleCombox;
    QComboBox           *threeProductUnitCombox;
    QComboBox           *threeInfoManCombox;
    QTableView          *threeview;
    QStandardItemModel  *threemodel = NULL;
    QTableView          *threeProductNoticeView;
    QStandardItemModel  *threeProductNoticeModel = NULL;
    QDateTimeEdit       *threeProductTime1;
    QDateTimeEdit       *threeProductTime2;
    QPushButton         *threeFindBtn;
    QString              yianpairenwuliang;
    QString              yianpaicheci;
    QString              fahuojiluhao;

private:
    const char          *SQL4;
    QTableView          *fourview;
    QStandardItemModel  *fourmodel = NULL;
    QPushButton         *bufangBtn;
    QPushButton         *hulueBtn;
    QLineEdit           *fourRecordNoLineEdit;
    QLineEdit           *fourRealCustomerLineEdit;
    QLineEdit           *fourFaHuoCustomerLineEdit;
    QLineEdit           *fourEngineerLineEdit;
    QLineEdit           *fourTongVolumeLineEdit;
    QLineEdit           *fourMotarLineEdit;
    QComboBox           *fourUnitNoComBox;
    QString              cheHao;

private:
    const char          *SQL5;
    QTableView          *fiveview;
    QStandardItemModel  *fivemodel = NULL;
    QPushButton         *fiveBtn;
    QDateTimeEdit       *fivedateTimeEdit1;
    QDateTimeEdit       *fivedateTimeEdit2;
    QCheckBox           *fiveCheckBox1;
    QCheckBox           *fiveCheckBox2;
    QComboBox           *fiveCombox1;
    QComboBox           *fiveCombox2;

private:
    const char          *SQL6;
    const char          *SQL62;
    QString              sixTaskNumber;
    QString              sixBiaoHao;
    QString              sixShengChanLiang;
    QTableView          *sixOriginalView;
    QStandardItemModel  *sixOriginalModel = NULL;
    QTableView          *sixTargetView;
    QStandardItemModel  *sixTargetModel = NULL;
    QPushButton         *sixFindBtn;
    QPushButton         *sixConfirmTransferBtn;
    QLineEdit           *sixRecordNumLineEdit;
    QLineEdit           *sixOriginalNoLineEdit;
    QLineEdit           *sixCustomerLineEdit;
    QLineEdit           *sixEngineerLineEdit;
    QLineEdit           *sixVehicleLineEdit;
    QLineEdit           *sixShippingVolumeLineEdit;
    QLineEdit           *sixReceiptVolumeLineEdit;

    QAction             *shanchuAction;

private:
    const char          *SQL7;
    QString              sevenTaskNumber;
    QTableView          *sevenview;
    QStandardItemModel  *sevenmodel = NULL;
    QTableView          *sevenview2;
    QStandardItemModel  *sevenmodel2 = NULL;
    QPushButton         *sevenBtn;
    QPushButton         *sevenzhuanliaoBtn;
    QDateTimeEdit       *sevendateTimeEdit1;
    QDateTimeEdit       *sevendateTimeEdit2;
    QLineEdit           *sevenLineEdit1;
    QLineEdit           *sevenLineEdit2;
    QLineEdit           *sevenLineEdit3;
    QLineEdit           *sevenLineEdit4;
    QLineEdit           *sevenLineEdit5;
    QLineEdit           *sevenLineEdit6;


private:
    const char          *SQL8;
    QTableView          *eightview;
    QStandardItemModel  *eightmodel = NULL;
    QPushButton         *eightBtn;

private:
    const char          *SQL9;
    QCheckBox           *ninecheckBox1;
    QCheckBox           *ninecheckBox2;
    QCheckBox           *ninecheckBox3;
    QCheckBox           *ninecheckBox4;
    QCheckBox           *ninecheckBox5;
    myComboBox          *ninecombo1;
    QComboBox           *ninecombo2;
    QComboBox           *ninecombo3;
    QComboBox           *ninecombo4;
    QTableView          *nineview;
    QStandardItemModel  *ninemodel = NULL;
    QDateTimeEdit       *ninedate1;
    QDateTimeEdit       *ninedate2;
    QPushButton         *nineBtn;
    QString              nineyianpairenwuliang;
    QString              nineyianpaicheci;
    QString              ninefahuojiluhao;

private:
    void creatTabPage1();
    void creatTabPage2();
    void creatTabPage3();
    void creatTabPage4();
    void creatTabPage5();
    void creatTabPage6();
    void creatTabPage7();
    void creatTabPage8();
    void creatTabPage9();
    void setModelStyle(QStandardItemModel *model);
    void setPage3ModelStyle(QStandardItemModel *model);

private:
    bool page3Open;
    bool page4Open;
    bool page5Open;
    bool page6Open;
    bool page7Open;
    bool page8Open;
    bool page9Open;

private slots:
    void ShowSupplyclick();
    void ShowSupplyclick2();
    void on_doubleClickTwoProductingView(QModelIndex index);
    void ShowSupplyclick3();
    void ShowSupplyclick4();
    void ShowSupplyclick6();

private slots:
    void oneVehicleComboxResponse();
    void ActualProductionVolume();

    void on_oneAddCheliangBtn();
    void on_oneDelCheliangBtn();
    void on_oneBuDaShuiPiaoBtn();
    void on_qitaxinxiBtn();

    void on_tongzhishengchan();
    void on_chexiaoshengchan();
    void on_chaxunrenwudan();
    void on_zuofeiBtn();
    void on_zhuanliaochuliBtn();

    void on_yincangAct();
    void on_chexiaoyincangAct();

private slots:
    void on_twoRefreshRunStateTimer();
    void on_twoSetProductedBtn();

private slots:
    void on_threeFindBtn();

private slots:
    void on_bufangBtn();
    void on_hulueBtn();

private slots:
    void on_fiveChaxunBtn();

private slots:
    void on_sixFindBtn();
    void on_sixConfirmTransferBtn();
    void Decreasing();

private slots:
    void on_sevenChaxunBtn();
    void on_eightShuaXin();
    void on_ninechaxun();

private slots:
    void on_tabWidget(int index);
};

#endif // SHENGCHANRENWUANPAIDLG_H
