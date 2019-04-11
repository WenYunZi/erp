#-------------------------------------------------
#
# Project created by panjinlei 2016-09-23 15:22:25
#
#-------------------------------------------------

QT       += core gui xml sql
QT       += serialport
QT       += network
QT       += axcontainer
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


LIBS += -LC:\mysql\lib -llibmysql

RC_FILE = QSLOGO.rc


TARGET = QSERP
TEMPLATE = app



SOURCES += main.cpp\
        mainwindow.cpp \
    guobangrukudlg.cpp \
    kucunqichushedingdlg.cpp \
    kehudangandlg.cpp \
    shengchanrenwudandlg.cpp \
    peihebimubandlg.cpp \
    peihebitongzhidandlg.cpp \
    shengchanrenwuanpaidlg.cpp \
    fahuoquerendlg.cpp \
    jizujiekoudlg.cpp \
    tongchesijidlg.cpp \
    tongchexinxidlg.cpp \
    changdishezhidlg.cpp \
    bumenshezhidlg.cpp \
    yuanliaoshezhidlg.cpp \
    cangweishezhidlg.cpp \
    chanpinshezhidlg.cpp \
    shuxingshezhidlg.cpp \
    yonghuguanlidlg.cpp \
    mimaxiugaidlg.cpp \
    rukuchaxunDlg.cpp \
    mymysql.cpp \
    logindlg.cpp \
    quanxianguanlidlg.cpp \
    pubfunc.cpp \
    mydelegate.cpp \
    shuxingtoolbardlg.cpp \
    gongchengmingchengdlg.cpp \
    caigoumingxibiaodlg.cpp \
    xiaoshoumingxibiaodlg.cpp \
    shengchanmingxibiaodlg.cpp \
    xitongsuodingdlg.cpp \
    widget.cpp \
    titlewidget.cpp \
    mypushbutton.cpp \
    guanyudlg.cpp \
    mycompleterlineedit.cpp \
    metromenu.cpp \
    caigouguanlimenu.cpp \
    yuanliaoguanlimenu.cpp \
    fucaiguanlimenu.cpp \
    bangfangguanlimenu.cpp \
    xiaoshouguanlimenu.cpp \
    diaoduguanlimenu.cpp \
    shiyanshiguanlimenu.cpp \
    shengchanguanlimenu.cpp \
    caiwuguanlimenu.cpp \
    baobiaochaxunmenu.cpp \
    tongcheguanlimenu.cpp \
    bengcheguanlimenu.cpp \
    xitongshezhimenu.cpp \
    gongjumenu.cpp \
    bangzhumenu.cpp \
    yidakaichuangkoumenu.cpp \
    shouyedlg.cpp \
    caigouhetongguanlidlg.cpp \
    caigoujiesuandlg.cpp \
    yuanliaorukushujutiaozhengdlg.cpp \
    fucaigongyingshangdangandlg.cpp \
    fucaishezhidlg.cpp \
    fucairukudlg.cpp \
    fucaichukudlg.cpp \
    fucaikucundlg.cpp \
    fucaihaoyongtongjidlg.cpp \
    fahuoshujutiaozhengdlg.cpp \
    xiaoshouzongzhangdlg.cpp \
    zhanghaoshezhidlg.cpp \
    yuanliaoxiaohaojiagetiaozhengdlg.cpp \
    maintitle.cpp \
    fahuojiagepiliangtiaozhengdlg.cpp \
    hetongzhixingqingkuangdlg.cpp \
    xiaoshoushoukuantiaojiandlg.cpp \
    shengchanyujingdlg.cpp \
    yunfeishezhidlg.cpp \
    gongchengyunjuquerendlg.cpp \
    bengchesijidlg.cpp \
    bengchexinxidlg.cpp \
    xiaoshouhetongguanlidlg.cpp \
    fucaideletegate.cpp \
    shengchanxiaohaobiaodlg.cpp \
    cheliangyunshubaobiaodlg.cpp \
    fangliangchaxundlg.cpp \
    shengchanfenbudlg.cpp \
    duishudandlg.cpp \
    jiesuandandlg.cpp \
    mytcpsocket.cpp \
    thread_jizujiekou.cpp \
    fucaichukudelegate.cpp \
    warehousewidget.cpp \
    kucunxinxidlg.cpp \
    accesscontrol.cpp \
    cheliangzhuangtai.cpp \
    mycombobox.cpp \
    previewprint.cpp \
    thread_sync.cpp \
    ccrashstack.cpp \
    yuanliaoxiaohaojiageshezhidlg.cpp \
    odbcoperator.cpp \
    xiabanjilu.cpp \
    jibencanshushezhi.cpp \
    tongfahuomingxizhangdlg.cpp \
    caigourukumingxidlg.cpp \
    contractdeletedlg.cpp \
    mycheckboxdelegate.cpp \
    caigouzongzhangdlg.cpp \
    myexcel.cpp \
    shengchanfangliangshengliaodlg.cpp \
    qcustomplot.cpp \
    playviedo.cpp \
    mylabel.cpp \
    shengchanxinxidlg.cpp \
    cheliangweixiuguanli.cpp \
    cheliangweixiudelegate.cpp

HEADERS  += mainwindow.h \
    guobangrukudlg.h \
    kucunqichushedingdlg.h \
    kehudangandlg.h \
    shengchanrenwudandlg.h \
    peihebimubandlg.h \
    peihebitongzhidandlg.h \
    shengchanrenwuanpaidlg.h \
    fahuoquerendlg.h \
    jizujiekoudlg.h \
    tongchesijidlg.h \
    tongchexinxidlg.h \
    changdishezhidlg.h \
    bumenshezhidlg.h \
    yuanliaoshezhidlg.h \
    cangweishezhidlg.h \
    chanpinshezhidlg.h \
    shuxingshezhidlg.h \
    yonghuguanlidlg.h \
    mimaxiugaidlg.h \
    rukuchaxunDlg.h \
    mymysql.h \
    logindlg.h \
    quanxianguanlidlg.h \
    pubfunc.h \
    mydelegate.h \
    shuxingtoolbardlg.h \
    gongchengmingchengdlg.h \
    caigoumingxibiaodlg.h \
    xiaoshoumingxibiaodlg.h \
    shengchanmingxibiaodlg.h \
    xitongsuodingdlg.h \
    widget.h \
    titlewidget.h \
    mypushbutton.h \
    mytcpsocket.h \
    guanyudlg.h \
    shouyedlg.h \
    mycompleterlineedit.h \
    metromenu.h \
    caigouguanlimenu.h \
    yuanliaoguanlimenu.h \
    fucaiguanlimenu.h \
    bangfangguanlimenu.h \
    xiaoshouguanlimenu.h \
    diaoduguanlimenu.h \
    shiyanshiguanlimenu.h \
    shengchanguanlimenu.h \
    caiwuguanlimenu.h \
    baobiaochaxunmenu.h \
    tongcheguanlimenu.h \
    bengcheguanlimenu.h \
    xitongshezhimenu.h \
    gongjumenu.h \
    bangzhumenu.h \
    yidakaichuangkoumenu.h \
    caigouhetongguanlidlg.h \
    caigoujiesuandlg.h \
    yuanliaorukushujutiaozhengdlg.h \
    fucaigongyingshangdangandlg.h \
    fucaishezhidlg.h \
    fucairukudlg.h \
    fucaichukudlg.h \
    fucaikucundlg.h \
    fucaihaoyongtongjidlg.h \
    fahuoshujutiaozhengdlg.h \
    xiaoshouzongzhangdlg.h \
    zhanghaoshezhidlg.h \
    yuanliaoxiaohaojiagetiaozhengdlg.h \
    maintitle.h \
    fahuojiagepiliangtiaozhengdlg.h \
    hetongzhixingqingkuangdlg.h \
    xiaoshoushoukuantiaojiandlg.h \
    shengchanyujingdlg.h \
    yunfeishezhidlg.h \
    gongchengyunjuquerendlg.h \
    bengchesijidlg.h \
    bengchexinxidlg.h \
    xiaoshouhetongguanlidlg.h \
    fucaideletegate.h \
    shengchanxiaohaobiaodlg.h \
    cheliangyunshubaobiaodlg.h \
    fangliangchaxundlg.h \
    shengchanfenbudlg.h \
    duishudandlg.h \
    jiesuandandlg.h \
    thread_jizujiekou.h \
    fucaichukudelegate.h \
    warehousewidget.h \
    kucunxinxidlg.h \
    accesscontrol.h \
    cheliangzhuangtai.h \
    mycombobox.h \
    previewprint.h \
    thread_sync.h \
    ccrashstack.h \
    yuanliaoxiaohaojiageshezhidlg.h \
    odbcoperator.h \
    xiabanjilu.h \
    jibencanshushezhi.h \
    tongfahuomingxizhangdlg.h \
    caigourukumingxidlg.h \
    contractdeletedlg.h \
    mycheckboxdelegate.h \
    caigouzongzhangdlg.h \
    myexcel.h \
    shengchanfangliangshengliaodlg.h \
    qcustomplot.h \
    playviedo.h \
    mylabel.h \
    shengchanxinxidlg.h \
    cheliangweixiuguanli.h \
    cheliangweixiudelegate.h

#INCLUDEPATH += $$PWD/../build-primaryBSTERP-Desktop_Qt_5_2_0_MinGW_32bit-Debug
#DEPENDPATH += $$PWD/../build-primaryBSTERP-Desktop_Qt_5_2_0_MinGW_32bit-Debug

RESOURCES += \
    image.qrc \
    menupic.qrc
