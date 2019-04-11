#include "mainwindow.h"
#include <QDebug>
#include <QPalette>
#include <QProcess>
#include <QStackedLayout>

extern mymysql db;
extern pubfunc pub;
extern QString quanxian;
extern QString whetherCheckSend;
extern QString userName;
extern QString PRODUCTUNITNO;
extern QString connectMenJin;
extern QString UNITTYPE;
extern myTCPsocket *sockClient;
extern mainTitle   *titleBar;

extern accessControl *MenJinControl;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //启动更新程序
    QString whether_update = pub.read_whether_update();
    if(whether_update == "true"){
        qDebug()<<"需要更新";

        QProcess prg(this);
        if(prg.startDetached(QString("softupdate.exe"))){
            qDebug()<<"更新程序启动成功";
            //db.sql_disconnet();
            exit(0);//更新程序成功启动后主程序退出
        }
        qDebug()<<"更新程序启动失败"<<prg.error();
    }
///qDebug()<<"222222222222222";
    this->setObjectName(QString("mainWindow"));
    this->setStyleSheet("QMainWindow[objectName=\"mainWindow\"]{background:rgb(7,4,127)}");
    this->setMouseTracking(true);

    sockClient = new myTCPsocket(this);
    isMetroMenuHide = false;
    loginDlg dlg(this);
    dlg.exec();

    this->setWindowTitle(tr("青盛ERP"));//设置主窗口标题
    this->setWindowState(Qt::WindowMaximized);//设置主窗口默认最大化开启
    createMetroMenu();

    titleBar = new mainTitle(this);//创建窗口标题栏
    titleBar->setFixedHeight(30);

    mdiArea = new QMdiArea(this);
    mdiArea->setActivationOrder(QMdiArea::ActivationHistoryOrder);//子窗口按照活动顺序排列
    mdiArea->setBackground(QBrush(QColor(255,255,255)));

    //当子窗口的范围查过父窗口的显示范围时，父窗口自动添加横向滚动条。
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    //当子窗口的范围查过父窗口的显示范围时，父窗口自动添加纵向滚动条。
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    central = new QWidget(this);
    this->setCentralWidget(central);

    hlayout = new QHBoxLayout;
    hlayout->addWidget(metroMenu);
    hlayout->addWidget(mdiArea);
    hlayout->setSpacing(2);

    vlayout = new QVBoxLayout;
    vlayout->addWidget(titleBar);
    vlayout->addLayout(hlayout);
    vlayout->setMargin(0);
    vlayout->setSpacing(2);
    central->setLayout(vlayout);
    central->setMouseTracking(true);

    connect(titleBar->menuSwitch,SIGNAL(clicked()),this,SLOT(move_metromenu()));
    connect(titleBar->gongjukaiguanBtn,SIGNAL(clicked()),this,SLOT(on_suoding()));
    connect(titleBar->dakaichuangkouBtn,SIGNAL(clicked()),this,SLOT(on_openWindow()));
    connect(titleBar->closeBtn,SIGNAL(clicked()),this,SLOT(close_active_window()));
    connect(titleBar->shouyeBtn,SIGNAL(clicked()),this,SLOT(showShouYe()));

    connect(&db,SIGNAL(errorMsg(const char*)),this,SLOT(dbConnectError(const char*)));
    connect(&db,SIGNAL(reconnectSuccess()),this,SLOT(reconnectSocket()));

    createStatus();

    if(connectMenJin == "true"){
        MenJinControl = new accessControl(this);
        //MenJinControl->accessControl_connect();
    }

    if(!PRODUCTUNITNO.isEmpty()){
        jiekouDlg = new jizujiekouDlg(this);
        jiekouDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(jiekouDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("机组接口"));
        subWindow->setWindowIcon(QIcon(":/image/jiekou.png"));
        jiekouDlg->on_shujuchuanshu();
    }

    showShouYe();
}

MainWindow::~MainWindow()
{
    delete mdiArea;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    int res = QMessageBox::question(this,tr("提示信息"),tr("是否退出？"),QMessageBox::Yes|QMessageBox::No);
    if(res == QMessageBox::Yes)
    {
        db.sql_disconnet();
        sockClient->myTCPsocket_disconnected();
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("机组接口") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                jiekouDlg->thread->setThreadIsRun(false);
                jiekouDlg->thread->wait();
                jiekouDlg->threadSync->setThreadIsRun(false);
                jiekouDlg->threadSync->wait();
            }
        }
        event->accept();
    }
    else {
        event->ignore();
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setBrush(QBrush(QColor(240,240,240)));
    painter.setPen(Qt::NoPen);
    painter.drawRect(0,0,this->width(),30);
    event->accept();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_F1)
    {
        QDesktopWidget *desktop = QApplication::desktop();
        isOpenWindow = new yiDaKaiChuangKouMenu(this,titleBar);

        if(isOpenWindow->count_except_menu == 0){
            return;//如果子窗口个数为零则直接返回
        }

        isOpenWindow->show();
        isOpenWindow->move((desktop->width() - isOpenWindow->width())/2,(desktop->height() - isOpenWindow->height())/2 - 60);
    }
    if(event->key() == Qt::Key_Alt)
    {
        move_metromenu();
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    pressX = event->x();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    releaseX = event->x();
    if(releaseX - pressX >= 30){
        if(isMetroMenuHide == true){
            isMetroMenuHide = false;
            metroMenu->setVisible(true);
            hlayout->insertWidget(0,metroMenu);
            titleBar->menuSwitch->setStyleSheet("QToolButton[objectName=\"menuSwitch\"]{border:0px;background-image:url(:/menupic/on.png)}");
        }
    }
    if(releaseX - pressX <= -30){
        if(isMetroMenuHide == false){
            isMetroMenuHide = true;
            metroMenu->setVisible(false);
            hlayout->removeWidget(metroMenu);
            titleBar->menuSwitch->setStyleSheet("QToolButton[objectName=\"menuSwitch\"]{border:0px;background-image:url(:/menupic/off.png)}");
        }
    }
}

void MainWindow::createMetroMenu()
{
    metroMenu = new MetroMenu;
    metroMenu->setFixedWidth(230);
    connect(metroMenu->Btn1,SIGNAL(clicked()),this,SLOT(on_caigouguanlimenu()));
    connect(metroMenu->Btn2,SIGNAL(clicked()),this,SLOT(on_yuanliaoguanlimenu()));
    connect(metroMenu->Btn3,SIGNAL(clicked()),this,SLOT(on_fucaiguanlimenu()));
    connect(metroMenu->Btn4,SIGNAL(clicked()),this,SLOT(on_bangfangguanlimenu()));
    connect(metroMenu->Btn5,SIGNAL(clicked()),this,SLOT(on_xiaoshouguanlimenu()));
    connect(metroMenu->Btn6,SIGNAL(clicked()),this,SLOT(on_diaoduguanlimenu()));
    connect(metroMenu->Btn7,SIGNAL(clicked()),this,SLOT(on_shiyanshiguanlimenu()));
    connect(metroMenu->Btn8,SIGNAL(clicked()),this,SLOT(on_shengchanguanlimenu()));
    connect(metroMenu->Btn9,SIGNAL(clicked()),this,SLOT(on_caiwuguanlimenu()));
    connect(metroMenu->Btn10,SIGNAL(clicked()),this,SLOT(on_baobiaochaxunmenu()));
    connect(metroMenu->Btn11,SIGNAL(clicked()),this,SLOT(on_tongcheguanlimenu()));
    connect(metroMenu->Btn12,SIGNAL(clicked()),this,SLOT(on_bengcheguanlimenu()));
    connect(metroMenu->Btn16,SIGNAL(clicked()),this,SLOT(on_xitongshezhimenu()));
    connect(metroMenu->Btn17,SIGNAL(clicked()),this,SLOT(on_gongjumenu()));
    connect(metroMenu->Btn18,SIGNAL(clicked()),this,SLOT(on_bangzhumenu()));
}

void MainWindow::move_metromenu()
{
    if(isMetroMenuHide == false){
        isMetroMenuHide = true;
        metroMenu->setVisible(false);
        hlayout->removeWidget(metroMenu);
        titleBar->menuSwitch->setStyleSheet("QToolButton[objectName=\"menuSwitch\"]{border:0px;background-image:url(:/menupic/off.png)}");
    }
    else{
        isMetroMenuHide = false;
        metroMenu->setVisible(true);
        hlayout->insertWidget(0,metroMenu);
        titleBar->menuSwitch->setStyleSheet("QToolButton[objectName=\"menuSwitch\"]{border:0px;background-image:url(:/menupic/on.png)}");
    }
}

void MainWindow::close_active_window()
{
    if(this->mdiArea->subWindowList().size() == 0){
        titleBar->title->setText(tr(" "));
        return;//如果子窗口个数为零直接返回
    }
    this->mdiArea->activeSubWindow()->close();
    if(this->mdiArea->subWindowList().size() == 0){
        titleBar->title->setText(tr(" "));
        return;//如果子窗口个数为零直接返回
    }
    QString name = this->mdiArea->activeSubWindow()->windowTitle();
    titleBar->title->setText(name);
}

void MainWindow::on_caigouguanlimenu()
{
    titleBar->title->setText(tr("采购管理菜单"));
    if(mdiArea->subWindowList().isEmpty())
    {
        caigouguanlimenu = new caigouguanliMenu(this,this);
        caigouguanlimenu->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(caigouguanlimenu,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("采购管理菜单"));
        subWindow->showMaximized();
        caigou_connect();
    }
    else
    {
        for(int i = 0;i < mdiArea->subWindowList().size();i++)
        {
            bool iscontains = mdiArea->subWindowList().at(i)->windowTitle().contains(QString("菜单"));
            if(iscontains)
            {
                mdiArea->subWindowList().at(i)->close();
                i = 0;
            }
        }

        caigouguanlimenu = new caigouguanliMenu(this,this);
        caigouguanlimenu->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(caigouguanlimenu,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("采购管理菜单"));
        subWindow->showMaximized();
        caigou_connect();
    }
}

void MainWindow::on_yuanliaoguanlimenu()
{
    titleBar->title->setText(tr("原料管理菜单"));
    if(mdiArea->subWindowList().isEmpty())
    {
        yuanliaoguanlimenu = new yuanliaoguanliMenu(this,this);
        yuanliaoguanlimenu->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(yuanliaoguanlimenu,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("原料管理菜单"));
        subWindow->showMaximized();
        yuanliao_connect();
    }
    else
    {
        for(int i = 0;i < mdiArea->subWindowList().size();i++)
        {
            bool iscontains = mdiArea->subWindowList().at(i)->windowTitle().contains(QString("菜单"));
            if(iscontains)
            {
                mdiArea->subWindowList().at(i)->close();
                i = 0;
            }
        }

        yuanliaoguanlimenu = new yuanliaoguanliMenu(this,this);
        yuanliaoguanlimenu->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(yuanliaoguanlimenu,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("原料管理菜单"));
        subWindow->showMaximized();
        yuanliao_connect();
    }
}

void MainWindow::on_fucaiguanlimenu()
{
    titleBar->title->setText(tr("辅材管理菜单"));
    if(mdiArea->subWindowList().isEmpty())
    {
        fucaiguanlimenu = new fucaiguanliMenu(this,this);
        fucaiguanlimenu->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(fucaiguanlimenu,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("辅材管理菜单"));
        subWindow->showMaximized();
        fucai_connect();
    }
    else
    {
        for(int i = 0;i < mdiArea->subWindowList().size();i++)
        {
            bool iscontains = mdiArea->subWindowList().at(i)->windowTitle().contains(QString("菜单"));
            if(iscontains)
            {
                mdiArea->subWindowList().at(i)->close();
                i = 0;
            }
        }

        fucaiguanlimenu = new fucaiguanliMenu(this,this);
        fucaiguanlimenu->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(fucaiguanlimenu,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("辅材管理菜单"));
        subWindow->showMaximized();
        fucai_connect();
    }
}

void MainWindow::on_bangfangguanlimenu()
{
    titleBar->title->setText(tr("磅房管理菜单"));
    if(mdiArea->subWindowList().isEmpty())
    {
        bangfangguanlimenu = new bangfangguanliMenu(this,this);
        bangfangguanlimenu->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(bangfangguanlimenu,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("磅房管理菜单"));
        subWindow->showMaximized();
        bangfang_connect();
    }
    else
    {
        for(int i = 0;i < mdiArea->subWindowList().size();i++)
        {
            bool iscontains = mdiArea->subWindowList().at(i)->windowTitle().contains(QString("菜单"));
            if(iscontains)
            {
                mdiArea->subWindowList().at(i)->close();
                i = 0;
            }
        }

        bangfangguanlimenu = new bangfangguanliMenu(this,this);
        bangfangguanlimenu->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(bangfangguanlimenu,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("磅房管理菜单"));
        subWindow->showMaximized();
        bangfang_connect();
    }
}

void MainWindow::on_xiaoshouguanlimenu()
{
    titleBar->title->setText(tr("销售管理菜单"));
    if(mdiArea->subWindowList().isEmpty())
    {
        xiaoshouguanlimenu = new xiaoshouguanliMenu(this,this);
        xiaoshouguanlimenu->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(xiaoshouguanlimenu,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("销售管理菜单"));
        subWindow->showMaximized();
        xiaoshou_connect();
    }
    else
    {
        for(int i = 0;i < mdiArea->subWindowList().size();i++)
        {
            bool iscontains = mdiArea->subWindowList().at(i)->windowTitle().contains(QString("菜单"));
            if(iscontains)
            {
                mdiArea->subWindowList().at(i)->close();
                i = 0;
            }
        }

        xiaoshouguanlimenu = new xiaoshouguanliMenu(this,this);
        xiaoshouguanlimenu->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(xiaoshouguanlimenu,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("销售管理菜单"));
        subWindow->showMaximized();
        xiaoshou_connect();
    }
}

void MainWindow::on_diaoduguanlimenu()
{
    titleBar->title->setText(tr("调度管理菜单"));
    if(mdiArea->subWindowList().isEmpty())
    {
        diaoduguanlimenu = new diaoduguanliMenu(this,this);
        diaoduguanlimenu->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(diaoduguanlimenu,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("调度管理菜单"));
        subWindow->showMaximized();
        diaodu_connect();
    }
    else
    {
        for(int i = 0;i < mdiArea->subWindowList().size();i++)
        {
            bool iscontains = mdiArea->subWindowList().at(i)->windowTitle().contains(QString("菜单"));
            if(iscontains)
            {
                mdiArea->subWindowList().at(i)->close();
                i = 0;
            }
        }

        diaoduguanlimenu = new diaoduguanliMenu(this,this);
        diaoduguanlimenu->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(diaoduguanlimenu,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("调度管理菜单"));
        subWindow->showMaximized();
        diaodu_connect();
    }
}

void MainWindow::on_shiyanshiguanlimenu()
{
    titleBar->title->setText(tr("实验室管理菜单"));
    if(mdiArea->subWindowList().isEmpty())
    {
        shiyanshiguanlimenu = new shiyanshiguanliMenu(this,this);
        shiyanshiguanlimenu->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(shiyanshiguanlimenu,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("实验室管理菜单"));
        subWindow->showMaximized();
        shiyanshi_connect();
    }
    else
    {
        for(int i = 0;i < mdiArea->subWindowList().size();i++)
        {
            bool iscontains = mdiArea->subWindowList().at(i)->windowTitle().contains(QString("菜单"));
            if(iscontains)
            {
                mdiArea->subWindowList().at(i)->close();
                i = 0;
            }
        }

        shiyanshiguanlimenu = new shiyanshiguanliMenu(this,this);
        shiyanshiguanlimenu->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(shiyanshiguanlimenu,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("实验室管理菜单"));
        subWindow->showMaximized();
        shiyanshi_connect();
    }
}

void MainWindow::on_shengchanguanlimenu()
{
    titleBar->title->setText(tr("生产管理菜单"));
    if(mdiArea->subWindowList().isEmpty())
    {
        shengchanguanlimenu = new shengchanguanliMenu(this,this);
        shengchanguanlimenu->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(shengchanguanlimenu,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("生产管理菜单"));
        subWindow->showMaximized();
        shengchan_connect();
    }
    else
    {
        for(int i = 0;i < mdiArea->subWindowList().size();i++)
        {
            bool iscontains = mdiArea->subWindowList().at(i)->windowTitle().contains(QString("菜单"));
            if(iscontains)
            {
                mdiArea->subWindowList().at(i)->close();
                i = 0;
            }
        }

        shengchanguanlimenu = new shengchanguanliMenu(this,this);
        shengchanguanlimenu->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(shengchanguanlimenu,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("生产管理菜单"));
        subWindow->showMaximized();
        shengchan_connect();
    }
}

void MainWindow::on_caiwuguanlimenu()
{
    titleBar->title->setText(tr("财务管理菜单"));
    if(mdiArea->subWindowList().isEmpty())
    {
        caiwuguanlimenu = new caiwuguanliMenu(this,this);
        caiwuguanlimenu->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(caiwuguanlimenu,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("财务管理菜单"));
        subWindow->showMaximized();
        caiwu_connect();
    }
    else
    {
        for(int i = 0;i < mdiArea->subWindowList().size();i++)
        {
            bool iscontains = mdiArea->subWindowList().at(i)->windowTitle().contains(QString("菜单"));
            if(iscontains)
            {
                mdiArea->subWindowList().at(i)->close();
                i = 0;
            }
        }

        caiwuguanlimenu = new caiwuguanliMenu(this,this);
        caiwuguanlimenu->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(caiwuguanlimenu,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("财务管理菜单"));
        subWindow->showMaximized();
        caiwu_connect();
    }
}

void MainWindow::on_baobiaochaxunmenu()
{
    titleBar->title->setText(tr("报表查询菜单"));
    if(mdiArea->subWindowList().isEmpty())
    {
        baobiaochaxunmenu = new baobiaochaxunMenu(this,this);
        baobiaochaxunmenu->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(baobiaochaxunmenu,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("报表查询菜单"));
        subWindow->showMaximized();
        baobiao_connect();
    }
    else
    {
        for(int i = 0;i < mdiArea->subWindowList().size();i++)
        {
            bool iscontains = mdiArea->subWindowList().at(i)->windowTitle().contains(QString("菜单"));
            if(iscontains)
            {
                mdiArea->subWindowList().at(i)->close();
                i = 0;
            }
        }

        baobiaochaxunmenu = new baobiaochaxunMenu(this,this);
        baobiaochaxunmenu->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(baobiaochaxunmenu,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("报表查询菜单"));
        subWindow->showMaximized();
        baobiao_connect();
    }
}

void MainWindow::on_tongcheguanlimenu()
{
    titleBar->title->setText(tr("砼车管理菜单"));
    if(mdiArea->subWindowList().isEmpty())
    {
        tongcheguanlimenu = new tongcheguanliMenu(this,this);
        tongcheguanlimenu->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(tongcheguanlimenu,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("砼车管理菜单"));
        subWindow->showMaximized();
        tongche_connect();
    }
    else
    {
        for(int i = 0;i < mdiArea->subWindowList().size();i++)
        {
            bool iscontains = mdiArea->subWindowList().at(i)->windowTitle().contains(QString("菜单"));
            if(iscontains)
            {
                mdiArea->subWindowList().at(i)->close();
                i = 0;
            }
        }

        tongcheguanlimenu = new tongcheguanliMenu(this,this);
        tongcheguanlimenu->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(tongcheguanlimenu,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("砼车管理菜单"));
        subWindow->showMaximized();
        tongche_connect();
    }
}

void MainWindow::on_bengcheguanlimenu()
{
    titleBar->title->setText(tr("泵车管理菜单"));
    if(mdiArea->subWindowList().isEmpty())
    {
        bengcheguanlimenu = new bengcheguanliMenu(this,this);
        bengcheguanlimenu->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(bengcheguanlimenu,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("泵车管理菜单"));
        subWindow->showMaximized();
        bengche_connect();
    }
    else
    {
        for(int i = 0;i < mdiArea->subWindowList().size();i++)
        {
            bool iscontains = mdiArea->subWindowList().at(i)->windowTitle().contains(QString("菜单"));
            if(iscontains)
            {
                mdiArea->subWindowList().at(i)->close();
                i = 0;
            }
        }

        bengcheguanlimenu = new bengcheguanliMenu(this,this);
        bengcheguanlimenu->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(bengcheguanlimenu,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("泵车管理菜单"));
        subWindow->showMaximized();
        bengche_connect();
    }
}

void MainWindow::on_xitongshezhimenu()
{
    titleBar->title->setText(tr("系统设置菜单"));
    if(mdiArea->subWindowList().isEmpty())
    {
        xitongshezhimenu = new xitongshezhiMenu(this,this);
        xitongshezhimenu->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(xitongshezhimenu,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("系统设置菜单"));
        subWindow->showMaximized();
        xitong_connect();
    }
    else
    {
        for(int i = 0;i < mdiArea->subWindowList().size();i++)
        {
            bool iscontains = mdiArea->subWindowList().at(i)->windowTitle().contains(QString("菜单"));
            if(iscontains)
            {
                mdiArea->subWindowList().at(i)->close();
                i = 0;
            }
        }

        xitongshezhimenu = new xitongshezhiMenu(this,this);
        xitongshezhimenu->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(xitongshezhimenu,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("系统设置菜单"));
        subWindow->showMaximized();
        xitong_connect();
    }
}

void MainWindow::on_gongjumenu()
{
    titleBar->title->setText(tr("工具菜单"));
    if(mdiArea->subWindowList().isEmpty())
    {
        gongjumenu = new gongjuMenu(this,this);
        gongjumenu->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(gongjumenu,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("工具菜单"));
        subWindow->showMaximized();
        gongju_connect();
    }
    else
    {
        for(int i = 0;i < mdiArea->subWindowList().size();i++)
        {
            bool iscontains = mdiArea->subWindowList().at(i)->windowTitle().contains(QString("菜单"));
            if(iscontains)
            {
                mdiArea->subWindowList().at(i)->close();
                i = 0;
            }
        }

        gongjumenu = new gongjuMenu(this,this);
        gongjumenu->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(gongjumenu,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("工具菜单"));
        subWindow->showMaximized();
        gongju_connect();
    }
}

void MainWindow::on_bangzhumenu()
{
    titleBar->title->setText(tr("帮助菜单"));
    if(mdiArea->subWindowList().isEmpty())
    {
        bangzhumenu = new bangzhuMenu(this,this);
        bangzhumenu->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(bangzhumenu,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("帮助菜单"));
        subWindow->showMaximized();
        bangzhu_connect();
    }
    else
    {
        for(int i = 0;i < mdiArea->subWindowList().size();i++)
        {
            bool iscontains = mdiArea->subWindowList().at(i)->windowTitle().contains(QString("菜单"));
            if(iscontains)
            {
                mdiArea->subWindowList().at(i)->close();
                i = 0;
            }
        }

        bangzhumenu = new bangzhuMenu(this,this);
        bangzhumenu->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(bangzhumenu,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("帮助菜单"));
        subWindow->showMaximized();
        bangzhu_connect();
    }
}

void MainWindow::on_caigouhetongguanli()
{
    titleBar->title->setText(tr("采购合同管理"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        cghtglDlg = new caigouhetongguanliDlg(this);
        cghtglDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(cghtglDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("采购合同管理"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("采购合同管理") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            cghtglDlg = new caigouhetongguanliDlg(this);
            cghtglDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(cghtglDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("采购合同管理"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_yuanliaoxiaohaojiageshezhi()
{
    titleBar->title->setText(tr("原料消耗价格设置"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        ylxhjgszDlg = new yuanliaoxiaohaojiageshezhiDlg(this);
        ylxhjgszDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(ylxhjgszDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("原料消耗价格设置"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("原料消耗价格设置") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            ylxhjgszDlg = new yuanliaoxiaohaojiageshezhiDlg(this);
            ylxhjgszDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(ylxhjgszDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("原料消耗价格设置"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_caigoujiesuan()
{
    titleBar->title->setText(tr("供货对账单"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        cgjsDlg = new caigoujiesuanDlg(this);
        cgjsDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(cgjsDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("供货对账单"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("供货对账单") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            cgjsDlg = new caigoujiesuanDlg(this);
            cgjsDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(cgjsDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("供货对账单"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_yuanliaorukushujutiaozheng()
{
    titleBar->title->setText(tr("原料入库数据调整"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        ylrksjtzDlg = new yuanliaorukushujutiaozhengDlg(this);
        ylrksjtzDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(ylrksjtzDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("原料入库数据调整"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("原料入库数据调整") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            ylrksjtzDlg = new yuanliaorukushujutiaozhengDlg(this);
            ylrksjtzDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(ylrksjtzDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("原料入库数据调整"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_fucaigongyingshangdangan()
{
    titleBar->title->setText(tr("辅材供应商档案"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        fcgysdaDlg = new fucaigongyingshangdanganDlg(this);
        fcgysdaDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(fcgysdaDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("辅材供应商档案"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("辅材供应商档案") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            fcgysdaDlg = new fucaigongyingshangdanganDlg(this);
            fcgysdaDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(fcgysdaDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("辅材供应商档案"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_guobangruku()
{
    titleBar->title->setText(tr("采购入库"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        gbrkDlg = new guobangrukuDlg(this);
        gbrkDlg->setAttribute(Qt::WA_DeleteOnClose,true);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(gbrkDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("采购入库"));
        subWindow->setWindowIcon(QIcon(":/image/dibang.png"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("采购入库") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            gbrkDlg = new guobangrukuDlg(this);
            gbrkDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(gbrkDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("采购入库"));
            subWindow->setWindowIcon(QIcon(":/image/dibang.png"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_kucunchaxun()
{
    titleBar->title->setText(tr("库存查询"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        rkcxDlg = new rukuchaxunDlg(this);
        rkcxDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(rkcxDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("库存查询"));
        subWindow->setWindowIcon(QIcon(":/image/chaxun.png"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("库存查询") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            rkcxDlg = new rukuchaxunDlg(this);
            rkcxDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(rkcxDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("库存查询"));
            subWindow->setWindowIcon(QIcon(":/image/chaxun.png"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_kucunqichusheding()
{
    titleBar->title->setText(tr("库存调整"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        kcqcsdDlg = new kucunqichushedingDlg(this);
        kcqcsdDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(kcqcsdDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("库存调整"));
        subWindow->setWindowIcon(QIcon(":/image/kucunsheding.png"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("库存调整") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            kcqcsdDlg = new kucunqichushedingDlg(this);
            kcqcsdDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(kcqcsdDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("库存调整"));
            subWindow->setWindowIcon(QIcon(":/image/kucunsheding.png"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_fucaishezhi()
{
    titleBar->title->setText(tr("辅材设置"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        fcszDlg = new fucaishezhiDlg(this);
        fcszDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(fcszDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("辅材设置"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("辅材设置") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            fcszDlg = new fucaishezhiDlg(this);
            fcszDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(fcszDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("辅材设置"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_fucairuku()
{
    titleBar->title->setText(tr("辅材入库"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        fcrkDlg = new fucairukuDlg(this);
        fcrkDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(fcrkDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("辅材入库"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("辅材入库") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            fcrkDlg = new fucairukuDlg(this);
            fcrkDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(fcrkDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("辅材入库"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_fucaichuku()
{
    titleBar->title->setText(tr("辅材出库"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        fcckDlg = new fucaichukuDlg(this);
        fcckDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(fcckDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("辅材出库"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("辅材出库") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            fcckDlg = new fucaichukuDlg(this);
            fcckDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(fcckDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("辅材出库"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_fucaikucun()
{
    titleBar->title->setText(tr("辅材库存"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        fckcDlg = new fucaikucunDlg(this);
        fckcDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(fckcDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("辅材库存"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("辅材库存") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            fckcDlg = new fucaikucunDlg(this);
            fckcDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(fckcDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("辅材库存"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_fucaihaoyongtongji()
{
    titleBar->title->setText(tr("辅材耗用统计"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        fchytjDlg = new fucaihaoyongtongjiDlg(this);
        fchytjDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(fchytjDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("辅材耗用统计"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("辅材耗用统计") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            fchytjDlg = new fucaihaoyongtongjiDlg(this);
            fchytjDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(fchytjDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("辅材耗用统计"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_kehudangan()
{
    titleBar->title->setText(tr("客户信息维护"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        khdaDlg = new kehudanganDlg(this);
        khdaDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(khdaDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("客户信息维护"));
        subWindow->setWindowIcon(QIcon(":/image/file.png"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("客户信息维护") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            khdaDlg = new kehudanganDlg(this);
            khdaDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(khdaDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("客户信息维护"));
            subWindow->setWindowIcon(QIcon(":/image/file.png"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_xiaoshouhetongguanli()
{
    titleBar->title->setText(tr("销售合同管理"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        xshtglDlg = new xiaoshouhetongguanliDlg(this);
        xshtglDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(xshtglDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("销售合同管理"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("销售合同管理") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            xshtglDlg = new xiaoshouhetongguanliDlg(this);
            xshtglDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(xshtglDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("销售合同管理"));
            subWindow->showMaximized();
        }
    }
}



void MainWindow::on_fahuojiagepiliangtiaozheng()
{
    titleBar->title->setText(tr("发货价格批量调整"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        fhjgpltzDlg = new fahuojiagepiliangtiaozhengDlg(this);
        fhjgpltzDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(fhjgpltzDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("发货价格批量调整"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("发货价格批量调整") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            fhjgpltzDlg = new fahuojiagepiliangtiaozhengDlg(this);
            fhjgpltzDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(fhjgpltzDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("发货价格批量调整"));
            subWindow->showMaximized();
        }
    }
}



void MainWindow::on_hetongzhixingqingkuang()
{
    titleBar->title->setText(tr("合同执行情况"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        htzxqkDlg = new hetongzhixingqingkuangDlg(this);
        htzxqkDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(htzxqkDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("合同执行情况"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("合同执行情况") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            htzxqkDlg = new hetongzhixingqingkuangDlg(this);
            htzxqkDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(htzxqkDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("合同执行情况"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_xiaoshoushoukuantiaojian()
{
    titleBar->title->setText(tr("销售收款条件"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        xssktjDlg = new xiaoshoushoukuantiaojianDlg(this);
        xssktjDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(xssktjDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("销售收款条件"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("销售收款条件") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            xssktjDlg = new xiaoshoushoukuantiaojianDlg(this);
            xssktjDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(xssktjDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("销售收款条件"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_shengchanyujing()
{
    titleBar->title->setText(tr("生产预警"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        scyjDlg = new shengchanyujingDlg(this);
        scyjDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(scyjDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("生产预警"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("生产预警") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            scyjDlg = new shengchanyujingDlg(this);
            scyjDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(scyjDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("生产预警"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_shengchanrenwudan()
{
    titleBar->title->setText(tr("生产任务单"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        scrwdDlg = new shengchanrenwudanDlg(this);
        scrwdDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(scrwdDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("生产任务单"));
        subWindow->setWindowIcon(QIcon(":/image/task.png"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("生产任务单") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            scrwdDlg = new shengchanrenwudanDlg(this);
            scrwdDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(scrwdDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("生产任务单"));
            subWindow->setWindowIcon(QIcon(":/image/task.png"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_peihebimubanweihu()
{
    titleBar->title->setText(tr("配合比模板维护"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        phbmbDlg = new peihebimubanDlg(this);
        phbmbDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(phbmbDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("配合比模板维护"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("配合比模板维护") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            phbmbDlg = new peihebimubanDlg(this);
            phbmbDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(phbmbDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("配合比模板维护"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_peihebitongzhidan()
{
    titleBar->title->setText(tr("配合比通知单"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        phbtzdDlg = new peihebitongzhidanDlg(this);
        phbtzdDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(phbtzdDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("配合比通知单"));
        subWindow->setWindowIcon(QIcon(":/image/tongzhi.png"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("配合比通知单") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            phbtzdDlg = new peihebitongzhidanDlg(this);
            phbtzdDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(phbtzdDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("配合比通知单"));
            subWindow->setWindowIcon(QIcon(":/image/tongzhi.png"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_shengchanrenwuanpai()
{
    titleBar->title->setText(tr("生产任务安排"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        scrwapDlg = new shengchanrenwuanpaiDlg(this);
        scrwapDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(scrwapDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("生产任务安排"));
        subWindow->setWindowIcon(QIcon(":/image/anpai.png"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("生产任务安排") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            scrwapDlg = new shengchanrenwuanpaiDlg(this);
            scrwapDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(scrwapDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("生产任务安排"));
            subWindow->setWindowIcon(QIcon(":/image/anpai.png"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_fahuoshujutiaozheng()
{
    titleBar->title->setText(tr("发货数据调整"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        fhsjtzDlg = new fahuoshujutiaozhengDlg(this);
        fhsjtzDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(fhsjtzDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("发货数据调整"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("发货数据调整") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            fhsjtzDlg = new fahuoshujutiaozhengDlg(this);
            fhsjtzDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(fhsjtzDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("发货数据调整"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_fahuoqueren()
{
    titleBar->title->setText(tr("发货确认"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        fhqrDlg = new fahuoquerenDlg(this);
        fhqrDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(fhqrDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("发货确认"));
        subWindow->setWindowIcon(QIcon(":/image/fahuo.png"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("发货确认") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            fhqrDlg = new fahuoquerenDlg(this);
            fhqrDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(fhqrDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("发货确认"));
            subWindow->setWindowIcon(QIcon(":/image/fahuo.png"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_jizujiekou()
{
    titleBar->title->setText(tr("机组接口"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        jiekouDlg = new jizujiekouDlg(this);
        jiekouDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(jiekouDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("机组接口"));
        subWindow->setWindowIcon(QIcon(":/image/jiekou.png"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("机组接口") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            jiekouDlg = new jizujiekouDlg(this);
            jiekouDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(jiekouDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("机组接口"));
            subWindow->setWindowIcon(QIcon(":/image/jiekou.png"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_tongfahuomingxizhang()
{
    titleBar->title->setText(tr("砼发货明细"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        tfhmxzDlg = new tongfahuomingxizhangDlg(this);
        tfhmxzDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(tfhmxzDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("砼发货明细"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("砼发货明细") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            tfhmxzDlg = new tongfahuomingxizhangDlg(this);
            tfhmxzDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(tfhmxzDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("砼发货明细"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_caigourukumingxi()
{
    titleBar->title->setText(tr("采购入库明细"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        cgrkmxDlg = new caigourukumingxiDlg(this);
        cgrkmxDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(cgrkmxDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("采购入库明细"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("采购入库明细") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            cgrkmxDlg = new caigourukumingxiDlg(this);
            cgrkmxDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(cgrkmxDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("采购入库明细"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_xiaoshouzongzhang()
{
    titleBar->title->setText(tr("销售总账"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        xszzDlg = new xiaoshouzongzhangDlg(this);
        xszzDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(xszzDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("销售总账"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("销售总账") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            xszzDlg = new xiaoshouzongzhangDlg(this);
            xszzDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(xszzDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("销售总账"));
            subWindow->showMaximized();
        }
    }
}


void MainWindow::on_caigouzongzhang()
{
    titleBar->title->setText(tr("采购总账"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        cgzzDlg = new caigouzongzhangDlg(this);
        cgzzDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(cgzzDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("采购总账"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("采购总账") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            cgzzDlg = new caigouzongzhangDlg(this);
            cgzzDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(cgzzDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("采购总账"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_zhanghaoshezhi()
{
    titleBar->title->setText(tr("账号设置"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        zhszDlg = new zhanghaoshezhiDlg(this);
        zhszDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(zhszDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("账号设置"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("账号设置") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            zhszDlg = new zhanghaoshezhiDlg(this);
            zhszDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(zhszDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("账号设置"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_yuanliaoxiaohaojiagetiaozheng()
{
    titleBar->title->setText(tr("原料消耗价格调整"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        ylxhjgtzDlg = new yuanliaoxiaohaojiagetiaozhengDlg(this);
        ylxhjgtzDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(ylxhjgtzDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("原料消耗价格调整"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("原料消耗价格调整") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            ylxhjgtzDlg = new yuanliaoxiaohaojiagetiaozhengDlg(this);
            ylxhjgtzDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(ylxhjgtzDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("原料消耗价格调整"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_caigoumingxibiao()
{
    titleBar->title->setText(tr("采购明细表"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        cgmxbDlg = new caigoumingxibiaoDlg;
        cgmxbDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(cgmxbDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("采购明细表"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("采购明细表") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            cgmxbDlg = new caigoumingxibiaoDlg;
            cgmxbDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(cgmxbDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("采购明细表"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_xiaoshouxiaohaobaobiao()
{
    titleBar->title->setText(tr("销售明细表"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        xsmxbDlg = new xiaoshoumingxibiaoDlg;
        xsmxbDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(xsmxbDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("销售明细表"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("销售明细表") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            xsmxbDlg = new xiaoshoumingxibiaoDlg;
            xsmxbDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(xsmxbDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("销售明细表"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_shengchanxiaohaobiao()
{
    titleBar->title->setText(tr("生产消耗表"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        scxhbDlg = new shengchanxiaohaobiaoDlg(this);
        scxhbDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(scxhbDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("生产消耗表"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("生产消耗表") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            scxhbDlg = new shengchanxiaohaobiaoDlg(this);
            scxhbDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(scxhbDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("生产消耗表"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_cheliangyunshubiao()
{
    titleBar->title->setText(tr("车辆运输报表"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        clysbDlg = new cheliangyunshubaobiaoDlg(this);
        clysbDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(clysbDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("车辆运输报表"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("车辆运输报表") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            clysbDlg = new cheliangyunshubaobiaoDlg(this);
            clysbDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(clysbDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("车辆运输报表"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_fangliangchaxun()
{
    titleBar->title->setText(tr("方量查询"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        flcxDlg = new fangliangchaxunDlg(this);
        flcxDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(flcxDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("方量查询"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("方量查询") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            flcxDlg = new fangliangchaxunDlg(this);
            flcxDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(flcxDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("方量查询"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_shengchanfenbu()
{
    titleBar->title->setText(tr("生产分布"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        scfbDlg = new shengchanfenbuDlg(this);
        scfbDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(scfbDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("生产分布"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("生产分布") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            scfbDlg = new shengchanfenbuDlg(this);
            scfbDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(scfbDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("生产分布"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_duishudan()
{
    titleBar->title->setText(tr("对数单"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        dsdDlg = new duishudanDlg(this);
        dsdDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(dsdDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("对数单"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("对数单") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            dsdDlg = new duishudanDlg(this);
            dsdDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(dsdDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("对数单"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_jiesuandan()
{
    titleBar->title->setText(tr("结算单"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        jsdDlg = new jiesuandanDlg(this);
        jsdDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(jsdDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("结算单"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("结算单") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            jsdDlg = new jiesuandanDlg(this);
            jsdDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(jsdDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("结算单"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_shengchanfangliangshengliaobiao()
{
    titleBar->title->setText(tr("生产方量省料"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        scflslDlg = new shengchanfangliangshengliaoDlg(this);
        scflslDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(scflslDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("生产方量省料"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("生产方量省料") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            scflslDlg = new shengchanfangliangshengliaoDlg(this);
            scflslDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(scflslDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("生产方量省料"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_tongchesiji()
{
    titleBar->title->setText(tr("砼车司机"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        tcsjDlg = new tongchesijiDlg(this);
        tcsjDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(tcsjDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("砼车司机"));
        subWindow->setWindowIcon(QIcon(":/image/siji.png"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("砼车司机") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            tcsjDlg = new tongchesijiDlg(this);
            tcsjDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(tcsjDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("砼车司机"));
            subWindow->setWindowIcon(QIcon(":/image/siji.png"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_tongchexinxi()
{
    titleBar->title->setText(tr("砼车信息"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        tcxxDlg = new tongchexinxiDlg(this);
        tcxxDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(tcxxDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("砼车信息"));
        subWindow->setWindowIcon(QIcon(":/image/tongche.png"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("砼车信息") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            tcxxDlg = new tongchexinxiDlg(this);
            tcxxDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(tcxxDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("砼车信息"));
            subWindow->setWindowIcon(QIcon(":/image/tongche.png"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_yunfeishezhi()
{
    titleBar->title->setText(tr("运费设置"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        yfszDlg = new yunfeishezhiDlg(this);
        yfszDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(yfszDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("运费设置"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("运费设置") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            yfszDlg = new yunfeishezhiDlg(this);
            yfszDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(yfszDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("运费设置"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_gongchengyunjuqueren()
{
    titleBar->title->setText(tr("工程运距确认"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        gcyjqrDlg = new gongchengyunjuquerenDlg(this);
        gcyjqrDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(gcyjqrDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("工程运距确认"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("工程运距确认") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            gcyjqrDlg = new gongchengyunjuquerenDlg(this);
            gcyjqrDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(gcyjqrDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("工程运距确认"));
            subWindow->showMaximized();
        }
    }
}

//add liwenxiu 2017-11-2
void MainWindow::on_cheliangweixiu()
{
    titleBar->title->setText(tr("车辆维修费用"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        clwxgl = new cheliangweixiuguanli(this);
        clwxgl->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(clwxgl,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("车辆维修费用"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("车辆维修费用") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            clwxgl = new cheliangweixiuguanli(this);
            clwxgl->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(clwxgl,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("车辆维修费用"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_bengchesiji()
{
    titleBar->title->setText(tr("泵车司机"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        bcsjDlg = new bengchesijiDlg(this);
        bcsjDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(bcsjDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("泵车司机"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("泵车司机") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            bcsjDlg = new bengchesijiDlg(this);
            bcsjDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(bcsjDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("泵车司机"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_bengchexinxi()
{
    titleBar->title->setText(tr("泵车信息"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        bcxxDlg = new bengchexinxiDlg(this);
        bcxxDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(bcxxDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("泵车信息"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("泵车信息") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            bcxxDlg = new bengchexinxiDlg(this);
            bcxxDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(bcxxDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("泵车信息"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_changdishezhi()
{
    titleBar->title->setText(tr("厂地设置"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        cdszDlg = new changdishezhiDlg(this);
        cdszDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(cdszDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("厂地设置"));
        subWindow->setWindowIcon(QIcon(":/image/factory.png"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("厂地设置") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            cdszDlg = new changdishezhiDlg(this);
            cdszDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(cdszDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("厂地设置"));
            subWindow->setWindowIcon(QIcon(":/image/factory.png"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_bumenshezhi()
{
    titleBar->title->setText(tr("部门设置"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        bmszDlg = new bumenshezhiDlg(this);
        bmszDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(bmszDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("部门设置"));
        subWindow->setWindowIcon(QIcon(":/image/bumen.png"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("部门设置") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            bmszDlg = new bumenshezhiDlg(this);
            bmszDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(bmszDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("部门设置"));
            subWindow->setWindowIcon(QIcon(":/image/bumen.png"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_yuanliaoshezhi()
{
    titleBar->title->setText(tr("原料设置"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        ylszDlg = new yuanliaoshezhiDlg(this);
        ylszDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(ylszDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("原料设置"));
        subWindow->setWindowIcon(QIcon(":/image/yuanliao.png"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("原料设置") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            ylszDlg = new yuanliaoshezhiDlg(this);
            ylszDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(ylszDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("原料设置"));
            subWindow->setWindowIcon(QIcon(":/image/yuanliao.png"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_cangweishezhi()
{
    titleBar->title->setText(tr("仓位设置"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        cwszDlg = new cangweishezhiDlg(this);
        cwszDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(cwszDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("仓位设置"));
        subWindow->setWindowIcon(QIcon(":/image/anliao.png"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("仓位设置") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            cwszDlg = new cangweishezhiDlg(this);
            cwszDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(cwszDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("仓位设置"));
            subWindow->setWindowIcon(QIcon(":/image/anliao.png"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_chanpingshezhi()
{
    titleBar->title->setText(tr("产品设置"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        cpszDlg = new chanpinshezhiDlg(this);
        cpszDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(cpszDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("产品设置"));
        subWindow->setWindowIcon(QIcon(":/image/chanpin.png"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("产品设置") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            cpszDlg = new chanpinshezhiDlg(this);
            cpszDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(cpszDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("产品设置"));
            subWindow->setWindowIcon(QIcon(":/image/chanpin.png"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_shuxingshezhi()
{
    titleBar->title->setText(tr("属性设置"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        sxszDlg = new shuxingshezhiDlg(this);
        sxszDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(sxszDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("属性设置"));
        subWindow->setWindowIcon(QIcon(":/image/cpin.png"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("属性设置") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            sxszDlg = new shuxingshezhiDlg(this);
            sxszDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(sxszDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("属性设置"));
            subWindow->setWindowIcon(QIcon(":/image/cpin.png"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_yonghuguanli()
{
    titleBar->title->setText(tr("用户管理"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        yhglDlg = new yonghuguanliDlg(this);
        yhglDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(yhglDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("用户管理"));
        subWindow->setWindowIcon(QIcon(":/image/yonghu.png"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("用户管理") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            yhglDlg = new yonghuguanliDlg(this);
            yhglDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(yhglDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("用户管理"));
            subWindow->setWindowIcon(QIcon(":/image/yonghu.png"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_quanxianguanli()
{
    titleBar->title->setText(tr("权限管理"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        qxglDlg = new quanxianguanliDlg(this);
        qxglDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(qxglDlg,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("权限管理"));
        subWindow->setWindowIcon(QIcon(":/image/you.png"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("权限管理") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            qxglDlg = new quanxianguanliDlg(this);
            qxglDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(qxglDlg,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("权限管理"));
            subWindow->setWindowIcon(QIcon(":/image/yohu.png"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_mimaxiugai()
{
    titleBar->title->setText(tr("密码修改"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        mimaxiugaiDlg *w1 = new mimaxiugaiDlg(this);
        w1->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(w1,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("密码修改"));
        subWindow->setWindowIcon(QIcon(":/image/mima.png"));
        subWindow->showMaximized();

    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("密码修改") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            mimaxiugaiDlg *w1 = new mimaxiugaiDlg(this);
            w1->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(w1,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("密码修改"));
            subWindow->setWindowIcon(QIcon(":/image/mima.png"));
            subWindow->showMaximized();
        }
    }
}

void MainWindow::on_jibenpeizhishezhi()
{
    titleBar->title->setText(tr("基本参数设置"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        jbcssz = new jibencanshushezhi(this);
        jbcssz->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(jbcssz,Qt::FramelessWindowHint);
        subWindow->setWindowTitle(tr("基本参数设置"));
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("基本参数设置") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            jbcssz = new jibencanshushezhi(this);
            jbcssz->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(jbcssz,Qt::FramelessWindowHint);
            subWindow->setWindowTitle(tr("基本参数设置"));
            subWindow->showMaximized();
        }
    }

}

void MainWindow::on_closeAllWindow()
{
    mdiArea->closeAllSubWindows();
}

void MainWindow::on_suoding()
{
    xitongsuodingDlg *w1 = new xitongsuodingDlg;
    w1->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
    w1->exec();
}

void MainWindow::on_openHelpFile()
{
    QDesktopServices ds;
    if(!ds.openUrl(QUrl(QString("QSERP.chm")))){
        QMessageBox::information(this,tr("错误"),tr("帮助文档打开失败"),0,0,0);
    }
}

void MainWindow::on_guanyu()
{
    gyDlg  = new guanyuDlg;
    gyDlg->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
    gyDlg->exec();
}

void MainWindow::on_openWindow()
{
    QDesktopWidget *desktop = QApplication::desktop();
    isOpenWindow = new yiDaKaiChuangKouMenu(this,titleBar);

    if(isOpenWindow->count_except_menu == 0){
        return;//如果子窗口个数为零则直接返回
    }

    isOpenWindow->show();
    isOpenWindow->move((desktop->width() - isOpenWindow->width())/2,(desktop->height() - isOpenWindow->height())/2 - 60);
}


void MainWindow::disPlaySysTime()
{
    sysDateTimeLabel->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
}

void MainWindow::createStatus()
{
    QLabel *banquan = new QLabel(tr("    版权所有：青岛青盛软件科技有限公司                 "));
    sysTime = new QLabel(tr("系统时间："));
    sysTime->setAlignment(Qt::AlignCenter);
    yonghu = new QLabel(tr("  用户名："));
    yonghu->setAlignment(Qt::AlignCenter);
    yonghuming = new QLabel(userName + QString(tr("    ")));
    sysDateTimeLabel = new QLabel;
    sysDateTimeLabel->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

    QLabel *UnitLabel = NULL;
    if(!PRODUCTUNITNO.isEmpty()){
        UnitLabel = new QLabel(QString("  机组：%1#机组  型号：%2").arg(PRODUCTUNITNO,UNITTYPE));
    }

    timer = new QTimer;
    timer->setInterval(1000);
    timer->start();
    connect(timer,SIGNAL(timeout()),this,SLOT(disPlaySysTime()));

    statusBar()->addWidget(yonghu);
    statusBar()->addWidget(yonghuming);
    statusBar()->addWidget(sysTime);
    statusBar()->addWidget(sysDateTimeLabel);
    statusBar()->addWidget(UnitLabel);
    statusBar()->setStyleSheet("QStatusBar::item{border: 2px}");
    statusBar()->addWidget(banquan);
}

void MainWindow::showShouYe()
{
    titleBar->title->setText(tr("首页"));
    bool flags=false;
    if(mdiArea->subWindowList().isEmpty())
    {
        shouyeDlg *w1 = new shouyeDlg(this);
        w1->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
        QMdiSubWindow *subWindow = mdiArea->addSubWindow(w1,0);
        subWindow->setWindowTitle(tr("首页"));
        subWindow->setWindowIcon(QIcon(":/image/shouye.png"));
        subWindow->setWindowFlags(Qt::FramelessWindowHint);
        subWindow->showMaximized();
    }
    else
    {
        for(int i=0;i<mdiArea->subWindowList().size();i++)
        {
            if(tr("首页") == mdiArea->subWindowList().at(i)->windowTitle())
            {
                mdiArea->subWindowList().at(i)->showMaximized();
                flags=true;
            }
        }
        if(flags == false)
        {
            shouyeDlg *w1 = new shouyeDlg(this);
            w1->setAttribute(Qt::WA_DeleteOnClose);//代表关闭这个widget的时候，自动将这个widget delete。
            QMdiSubWindow *subWindow = mdiArea->addSubWindow(w1,0);
            subWindow->setWindowTitle(tr("首页"));
            subWindow->setWindowIcon(QIcon(":/image/shouye.png"));
            subWindow->setWindowFlags(Qt::FramelessWindowHint);
            subWindow->showMaximized();
        }
    }
}

void MainWindow::caigou_connect()
{
    connect(caigouguanlimenu->Btn2,SIGNAL(clicked()),this,SLOT(on_caigouhetongguanli()));
    connect(caigouguanlimenu->Btn4,SIGNAL(clicked()),this,SLOT(on_yuanliaoxiaohaojiageshezhi()));
    connect(caigouguanlimenu->Btn6,SIGNAL(clicked()),this,SLOT(on_fucaigongyingshangdangan()));
}

void MainWindow::yuanliao_connect()
{
    connect(yuanliaoguanlimenu->Btn1,SIGNAL(clicked()),this,SLOT(on_kucunchaxun()));
    connect(yuanliaoguanlimenu->Btn2,SIGNAL(clicked()),this,SLOT(on_kucunqichusheding()));
}

void MainWindow::fucai_connect()
{
    connect(fucaiguanlimenu->Btn1,SIGNAL(clicked()),this,SLOT(on_fucaishezhi()));
    connect(fucaiguanlimenu->Btn2,SIGNAL(clicked()),this,SLOT(on_fucairuku()));
    connect(fucaiguanlimenu->Btn3,SIGNAL(clicked()),this,SLOT(on_fucaichuku()));
    connect(fucaiguanlimenu->Btn4,SIGNAL(clicked()),this,SLOT(on_fucaikucun()));
    connect(fucaiguanlimenu->Btn5,SIGNAL(clicked()),this,SLOT(on_fucaihaoyongtongji()));
}

void MainWindow::bangfang_connect()
{
    connect(bangfangguanlimenu->Btn1,SIGNAL(clicked()),this,SLOT(on_guobangruku()));
}

void MainWindow::xiaoshou_connect()
{
    connect(xiaoshouguanlimenu->Btn1,SIGNAL(clicked()),this,SLOT(on_kehudangan()));
    connect(xiaoshouguanlimenu->Btn2,SIGNAL(clicked()),this,SLOT(on_xiaoshouhetongguanli()));
    connect(xiaoshouguanlimenu->Btn3,SIGNAL(clicked()),this,SLOT(on_hetongzhixingqingkuang()));
    connect(xiaoshouguanlimenu->Btn4,SIGNAL(clicked()),this,SLOT(on_xiaoshoushoukuantiaojian()));
    connect(xiaoshouguanlimenu->Btn5,SIGNAL(clicked()),this,SLOT(on_shengchanyujing()));
}

void MainWindow::diaodu_connect()
{
    connect(diaoduguanlimenu->Btn1,SIGNAL(clicked()),this,SLOT(on_shengchanrenwudan()));
    connect(diaoduguanlimenu->Btn2,SIGNAL(clicked()),this,SLOT(on_shengchanrenwuanpai()));
}

void MainWindow::shiyanshi_connect()
{
    connect(shiyanshiguanlimenu->Btn1,SIGNAL(clicked()),this,SLOT(on_peihebimubanweihu()));
    connect(shiyanshiguanlimenu->Btn3,SIGNAL(clicked()),this,SLOT(on_peihebitongzhidan()));
}

void MainWindow::shengchan_connect()
{
    connect(shengchanguanlimenu->Btn2,SIGNAL(clicked()),this,SLOT(on_fahuoqueren()));
    connect(shengchanguanlimenu->Btn4,SIGNAL(clicked()),this,SLOT(on_jizujiekou()));
}

void MainWindow::caiwu_connect()
{
    connect(caiwuguanlimenu->Btn1,SIGNAL(clicked()),this,SLOT(on_tongfahuomingxizhang()));
    connect(caiwuguanlimenu->Btn2,SIGNAL(clicked()),this,SLOT(on_caigourukumingxi()));
    connect(caiwuguanlimenu->Btn3,SIGNAL(clicked()),this,SLOT(on_xiaoshouzongzhang()));
    connect(caiwuguanlimenu->Btn4,SIGNAL(clicked()),this,SLOT(on_caigouzongzhang()));
    connect(caiwuguanlimenu->Btn12,SIGNAL(clicked()),this,SLOT(on_fahuojiagepiliangtiaozheng()));
    connect(caiwuguanlimenu->Btn13,SIGNAL(clicked()),this,SLOT(on_fahuoshujutiaozheng()));
    connect(caiwuguanlimenu->Btn15,SIGNAL(clicked()),this,SLOT(on_yuanliaorukushujutiaozheng()));
    connect(caiwuguanlimenu->Btn16,SIGNAL(clicked()),this,SLOT(on_caigoujiesuan()));
}

void MainWindow::baobiao_connect()
{
    connect(baobiaochaxunmenu->Btn1,SIGNAL(clicked()),this,SLOT(on_caigoumingxibiao()));
    connect(baobiaochaxunmenu->Btn2,SIGNAL(clicked()),this,SLOT(on_xiaoshouxiaohaobaobiao()));
    connect(baobiaochaxunmenu->Btn4,SIGNAL(clicked()),this,SLOT(on_shengchanxiaohaobiao()));
    connect(baobiaochaxunmenu->Btn5,SIGNAL(clicked()),this,SLOT(on_cheliangyunshubiao()));
    connect(baobiaochaxunmenu->Btn7,SIGNAL(clicked()),this,SLOT(on_shengchanfenbu()));
    connect(baobiaochaxunmenu->Btnshengchanfangliangshengliao,SIGNAL(clicked()),this,SLOT(on_shengchanfangliangshengliaobiao()));
}

void MainWindow::tongche_connect()
{
    connect(tongcheguanlimenu->Btn1,SIGNAL(clicked()),this,SLOT(on_tongchesiji()));
    connect(tongcheguanlimenu->Btn2,SIGNAL(clicked()),this,SLOT(on_tongchexinxi()));
    connect(tongcheguanlimenu->Btn5,SIGNAL(clicked()),this,SLOT(on_yunfeishezhi()));
    connect(tongcheguanlimenu->Btn6,SIGNAL(clicked()),this,SLOT(on_gongchengyunjuqueren()));
    //add liwenxiu 2017-11-2
    connect(tongcheguanlimenu->Btn7,SIGNAL(clicked()),this,SLOT(on_cheliangweixiu()));
    //end liwenxiu 2017-11-2
}

void MainWindow::bengche_connect()
{
    connect(bengcheguanlimenu->Btn1,SIGNAL(clicked()),this,SLOT(on_bengchesiji()));
    connect(bengcheguanlimenu->Btn2,SIGNAL(clicked()),this,SLOT(on_bengchexinxi()));
}

void MainWindow::xitong_connect()
{
    connect(xitongshezhimenu->Btn1,SIGNAL(clicked()),this,SLOT(on_changdishezhi()));
    connect(xitongshezhimenu->Btn2,SIGNAL(clicked()),this,SLOT(on_bumenshezhi()));
    connect(xitongshezhimenu->Btn3,SIGNAL(clicked()),this,SLOT(on_yuanliaoshezhi()));
    connect(xitongshezhimenu->Btn4,SIGNAL(clicked()),this,SLOT(on_cangweishezhi()));
    connect(xitongshezhimenu->Btn5,SIGNAL(clicked()),this,SLOT(on_chanpingshezhi()));
    connect(xitongshezhimenu->Btn6,SIGNAL(clicked()),this,SLOT(on_shuxingshezhi()));
    connect(xitongshezhimenu->Btn7,SIGNAL(clicked()),this,SLOT(on_yonghuguanli()));
    connect(xitongshezhimenu->Btn8,SIGNAL(clicked()),this,SLOT(on_quanxianguanli()));
    connect(xitongshezhimenu->Btn9,SIGNAL(clicked()),this,SLOT(on_mimaxiugai()));
    connect(xitongshezhimenu->Btn12,SIGNAL(clicked()),this,SLOT(on_jibenpeizhishezhi()));
}

void MainWindow::gongju_connect()
{
    connect(gongjumenu->Btn1,SIGNAL(clicked()),this,SLOT(showShouYe()));
    connect(gongjumenu->Btn2,SIGNAL(clicked()),this,SLOT(on_openWindow()));
    connect(gongjumenu->Btn3,SIGNAL(clicked()),this,SLOT(on_closeAllWindow()));
    connect(gongjumenu->Btn4,SIGNAL(clicked()),this,SLOT(on_suoding()));
}

void MainWindow::bangzhu_connect()
{
    connect(bangzhumenu->Btn1,SIGNAL(clicked()),this,SLOT(on_openHelpFile()));
    connect(bangzhumenu->Btn2,SIGNAL(clicked()),this,SLOT(on_guanyu()));
}

void MainWindow::dbConnectError(const char *msg)
{
    QMessageBox::information(this,tr("错误"),tr(msg),0,0,0);
    sockClient->myTCPsocket_disconnected();
    sockClient->myTCPsocket_connected(pub.read_hostip());
}

void MainWindow::reconnectSocket()
{
    sockClient->myTCPsocket_disconnected();
    sockClient->myTCPsocket_connected(pub.read_hostip());
}
