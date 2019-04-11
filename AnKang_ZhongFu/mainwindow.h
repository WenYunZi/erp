#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QWidget>
#include <QAction>
#include <QCloseEvent>
#include <QMdiArea>
#include <QStatusBar>
#include <QLabel>
#include <QDateTimeEdit>
#include <QResizeEvent>
#include <QDateTime>
#include <QTimer>
#include <QMdiSubWindow>
#include <QMessageBox>
#include <QPoint>
#include <QStringList>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPalette>
#include <QIcon>
#include <QRect>
#include <QToolBar>
#include <QSound>
#include "caigouhetongguanlidlg.h"
#include "caigoujiesuandlg.h"
#include "yuanliaorukushujutiaozhengdlg.h"
#include "fucaigongyingshangdangandlg.h"
#include "guobangrukudlg.h"
#include "rukuchaxunDlg.h"
#include "kucunqichushedingdlg.h"
#include "kehudangandlg.h"
#include "xiaoshouhetongguanlidlg.h"
#include "shengchanrenwudandlg.h"
#include "peihebimubandlg.h"
#include "peihebitongzhidandlg.h"
#include "shengchanrenwuanpaidlg.h"
#include "fahuoquerendlg.h"
#include "jizujiekoudlg.h"
#include "tongchesijidlg.h"
#include "tongchexinxidlg.h"
#include "yunfeishezhidlg.h"
#include "gongchengyunjuquerendlg.h"
#include "bengchesijidlg.h"
#include "bengchexinxidlg.h"
#include "changdishezhidlg.h"
#include "bumenshezhidlg.h"
#include "yuanliaoshezhidlg.h"
#include "cangweishezhidlg.h"
#include "chanpinshezhidlg.h"
#include "shuxingshezhidlg.h"
#include "xiaoshoumingxibiaodlg.h"
#include "shengchanmingxibiaodlg.h"
#include "yonghuguanlidlg.h"
#include "mimaxiugaidlg.h"
#include "caigoumingxibiaodlg.h"
#include "xitongsuodingdlg.h"
#include "quanxianguanlidlg.h"
#include "logindlg.h"
#include "pubfunc.h"
#include "widget.h"
#include "guanyudlg.h"
#include "shouyedlg.h"
#include "metromenu.h"
#include "caigouguanlimenu.h"
#include "yuanliaoguanlimenu.h"
#include "fucaiguanlimenu.h"
#include "bangfangguanlimenu.h"
#include "xiaoshouguanlimenu.h"
#include "diaoduguanlimenu.h"
#include "shiyanshiguanlimenu.h"
#include "shengchanguanlimenu.h"
#include "caiwuguanlimenu.h"
#include "baobiaochaxunmenu.h"
#include "tongcheguanlimenu.h"
#include "bengcheguanlimenu.h"
#include "xitongshezhimenu.h"
#include "gongjumenu.h"
#include "bangzhumenu.h"
#include "yidakaichuangkoumenu.h"
#include "fucaishezhidlg.h"
#include "fucairukudlg.h"
#include "fucaichukudlg.h"
#include "fucaikucundlg.h"
#include "fucaihaoyongtongjidlg.h"
#include "fahuoshujutiaozhengdlg.h"
#include "tongfahuomingxizhangdlg.h"
#include "caigourukumingxidlg.h"
#include "caigouzongzhangdlg.h"
#include "xiaoshouzongzhangdlg.h"
#include "zhanghaoshezhidlg.h"
#include "yuanliaoxiaohaojiagetiaozhengdlg.h"
#include "maintitle.h"
#include "fahuojiagepiliangtiaozhengdlg.h"
#include "hetongzhixingqingkuangdlg.h"
#include "xiaoshoushoukuantiaojiandlg.h"
#include "shengchanyujingdlg.h"
#include "shengchanxiaohaobiaodlg.h"
#include "cheliangyunshubaobiaodlg.h"
#include "fangliangchaxundlg.h"
#include "shengchanfenbudlg.h"
#include "duishudandlg.h"
#include "jiesuandandlg.h"
#include "mytcpsocket.h"
#include "accesscontrol.h"
#include "previewprint.h"
#include "yuanliaoxiaohaojiageshezhidlg.h"
#include "jibencanshushezhi.h"
#include "shengchanfangliangshengliaodlg.h"
#include "cheliangweixiuguanli.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void createMetroMenu();
    void createStatus();

    void closeEvent(QCloseEvent *event);
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

public:
    QMdiArea                 *mdiArea;


private:
    int pressX;
    int releaseX;
    bool isLeftPressed;
    int curPos;
    QPoint pLast;

private:
    bool            isMetroMenuHide;
    QLabel          *background;
    QWidget         *widget;
    QLabel          *label;
    QLabel          *sysTime;
    QLabel          *yonghu;
    QLabel          *yonghuming;
    QLabel          *sysDateTimeLabel;
    QTimer          *timer;
    QRect            mdiAreaRect;
    QWidget         *central;
    QVBoxLayout     *vlayout;
    QHBoxLayout     *hlayout;

    MetroMenu       *metroMenu;
    QDateTime        sysdatetime;

    yiDaKaiChuangKouMenu *isOpenWindow;

public:
    caigouguanliMenu                *caigouguanlimenu    = NULL;
    yuanliaoguanliMenu              *yuanliaoguanlimenu  = NULL;
    fucaiguanliMenu                 *fucaiguanlimenu     = NULL;
    bangfangguanliMenu              *bangfangguanlimenu  = NULL;
    xiaoshouguanliMenu              *xiaoshouguanlimenu  = NULL;
    diaoduguanliMenu                *diaoduguanlimenu    = NULL;
    shiyanshiguanliMenu             *shiyanshiguanlimenu = NULL;
    shengchanguanliMenu             *shengchanguanlimenu = NULL;
    caiwuguanliMenu                 *caiwuguanlimenu     = NULL;
    baobiaochaxunMenu               *baobiaochaxunmenu   = NULL;
    tongcheguanliMenu               *tongcheguanlimenu   = NULL;
    bengcheguanliMenu               *bengcheguanlimenu   = NULL;
    xitongshezhiMenu                *xitongshezhimenu    = NULL;
    gongjuMenu                      *gongjumenu          = NULL;
    bangzhuMenu                     *bangzhumenu         = NULL;

public:
    caigouhetongguanliDlg           *cghtglDlg      = NULL;
    yuanliaoxiaohaojiageshezhiDlg   *ylxhjgszDlg    = NULL;
    caigoujiesuanDlg                *cgjsDlg        = NULL;
    yuanliaorukushujutiaozhengDlg   *ylrksjtzDlg    = NULL;
    fucaigongyingshangdanganDlg     *fcgysdaDlg     = NULL;
    guobangrukuDlg                  *gbrkDlg        = NULL;
    rukuchaxunDlg                   *rkcxDlg        = NULL;
    kucunqichushedingDlg            *kcqcsdDlg      = NULL;
    fucaishezhiDlg                  *fcszDlg        = NULL;
    fucairukuDlg                    *fcrkDlg        = NULL;
    fucaichukuDlg                   *fcckDlg        = NULL;
    fucaikucunDlg                   *fckcDlg        = NULL;
    fucaihaoyongtongjiDlg           *fchytjDlg      = NULL;
    kehudanganDlg                   *khdaDlg        = NULL;
    xiaoshouhetongguanliDlg         *xshtglDlg      = NULL;
    fahuojiagepiliangtiaozhengDlg   *fhjgpltzDlg    = NULL;
    hetongzhixingqingkuangDlg       *htzxqkDlg      = NULL;
    xiaoshoushoukuantiaojianDlg     *xssktjDlg      = NULL;
    shengchanyujingDlg              *scyjDlg        = NULL;
    shengchanrenwudanDlg            *scrwdDlg       = NULL;
    peihebimubanDlg                 *phbmbDlg       = NULL;
    peihebitongzhidanDlg            *phbtzdDlg      = NULL;
    shengchanrenwuanpaiDlg          *scrwapDlg      = NULL;
    fahuoquerenDlg                  *fhqrDlg        = NULL;
    fahuoshujutiaozhengDlg          *fhsjtzDlg      = NULL;
    jizujiekouDlg                   *jiekouDlg      = NULL;
    tongfahuomingxizhangDlg         *tfhmxzDlg      = NULL;
    caigourukumingxiDlg             *cgrkmxDlg      = NULL;
    caigouzongzhangDlg              *cgzzDlg        = NULL;
    xiaoshouzongzhangDlg            *xszzDlg        = NULL;
    zhanghaoshezhiDlg               *zhszDlg        = NULL;
    yuanliaoxiaohaojiagetiaozhengDlg *ylxhjgtzDlg   = NULL;
    caigoumingxibiaoDlg             *cgmxbDlg       = NULL;
    xiaoshoumingxibiaoDlg           *xsmxbDlg       = NULL;
    shengchanxiaohaobiaoDlg         *scxhbDlg       = NULL;
    cheliangyunshubaobiaoDlg        *clysbDlg       = NULL;
    fangliangchaxunDlg              *flcxDlg        = NULL;
    shengchanfenbuDlg               *scfbDlg        = NULL;
    shengchanfangliangshengliaoDlg  *scflslDlg      = NULL;
    duishudanDlg                    *dsdDlg         = NULL;
    jiesuandanDlg                   *jsdDlg         = NULL;
    tongchesijiDlg                  *tcsjDlg        = NULL;
    tongchexinxiDlg                 *tcxxDlg        = NULL;
    yunfeishezhiDlg                 *yfszDlg        = NULL;
    gongchengyunjuquerenDlg         *gcyjqrDlg      = NULL;
    //add liwenxiu 2017-11-2
    cheliangweixiuguanli            *clwxgl         = NULL;
//    cheliangweixiushezhi            *clwxsz         = NULL;
    //end liwenxiu 2017-11-2
    bengchesijiDlg                  *bcsjDlg        = NULL;
    bengchexinxiDlg                 *bcxxDlg        = NULL;
    changdishezhiDlg                *cdszDlg        = NULL;
    bumenshezhiDlg                  *bmszDlg        = NULL;
    yuanliaoshezhiDlg               *ylszDlg        = NULL;
    cangweishezhiDlg                *cwszDlg        = NULL;
    chanpinshezhiDlg                *cpszDlg        = NULL;
    shuxingshezhiDlg                *sxszDlg        = NULL;
    yonghuguanliDlg                 *yhglDlg        = NULL;
    quanxianguanliDlg               *qxglDlg        = NULL;
    guanyuDlg                       *gyDlg          = NULL;
    jibencanshushezhi               *jbcssz         = NULL;   


public slots:
    void on_caigouguanlimenu();
    void on_yuanliaoguanlimenu();
    void on_fucaiguanlimenu();
    void on_bangfangguanlimenu();
    void on_xiaoshouguanlimenu();
    void on_diaoduguanlimenu();
    void on_shiyanshiguanlimenu();
    void on_shengchanguanlimenu();
    void on_caiwuguanlimenu();
    void on_baobiaochaxunmenu();
    void on_tongcheguanlimenu();
    void on_bengcheguanlimenu();
    void on_xitongshezhimenu();
    void on_gongjumenu();
    void on_bangzhumenu();



public slots:
    void move_metromenu();
    void close_active_window();

    void on_caigouhetongguanli();
    void on_yuanliaoxiaohaojiageshezhi();
    void on_caigoujiesuan();
    void on_yuanliaorukushujutiaozheng();
    void on_fucaigongyingshangdangan();

    void on_guobangruku();
    void on_kucunchaxun();
    void on_kucunqichusheding();

    void on_fucaishezhi();
    void on_fucairuku();
    void on_fucaichuku();
    void on_fucaikucun();
    void on_fucaihaoyongtongji();

    void on_kehudangan();
    void on_xiaoshouhetongguanli();
    void on_fahuojiagepiliangtiaozheng();

    void on_hetongzhixingqingkuang();
    void on_xiaoshoushoukuantiaojian();
    void on_shengchanyujing();

    void on_shengchanrenwudan();
    void on_shengchanrenwuanpai();
    void on_fahuoshujutiaozheng();

    void on_peihebimubanweihu();
    void on_peihebitongzhidan();

    void on_fahuoqueren();
    void on_jizujiekou();

    void on_tongfahuomingxizhang();
    void on_caigourukumingxi();
    void on_xiaoshouzongzhang();
    void on_caigouzongzhang();
    void on_zhanghaoshezhi();
    void on_yuanliaoxiaohaojiagetiaozheng();

    void on_caigoumingxibiao();
    void on_xiaoshouxiaohaobaobiao();
    void on_shengchanxiaohaobiao();
    void on_cheliangyunshubiao();
    void on_fangliangchaxun();
    void on_shengchanfenbu();
    void on_shengchanfangliangshengliaobiao();
    void on_duishudan();
    void on_jiesuandan();

    void on_tongchesiji();
    void on_tongchexinxi();
    void on_yunfeishezhi();
    void on_gongchengyunjuqueren();
    void on_cheliangweixiu();
    void on_bengchesiji();
    void on_bengchexinxi();

    void on_changdishezhi();
    void on_bumenshezhi();
    void on_yuanliaoshezhi();
    void on_cangweishezhi();
    void on_chanpingshezhi();
    void on_shuxingshezhi();
    void on_yonghuguanli();
    void on_quanxianguanli();
    void on_mimaxiugai();
    void on_jibenpeizhishezhi();

    void showShouYe();

    void on_closeAllWindow();
    void on_suoding();

    void on_openHelpFile();
    void on_guanyu();

    void on_openWindow();

    void disPlaySysTime();

private:
    void caigou_connect();
    void yuanliao_connect();
    void fucai_connect();
    void bangfang_connect();
    void xiaoshou_connect();
    void diaodu_connect();
    void shiyanshi_connect();
    void shengchan_connect();
    void caiwu_connect();
    void baobiao_connect();
    void tongche_connect();
    void bengche_connect();
    void xitong_connect();
    void gongju_connect();
    void bangzhu_connect();

private slots:
    void dbConnectError(const char* msg);
    void reconnectSocket();
};

#endif // MAINWINDOW_H
