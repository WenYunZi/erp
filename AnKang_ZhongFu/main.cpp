#include "mainwindow.h"
#include "ccrashstack.h"
#include <QApplication>
#include <QTranslator>
#include <QProcess>
#include <QDir>

mymysql         db;
pubfunc         pub;
QString         quanxian;
QString         whetherCheckSend;
QString         userName;
QString         PRODUCTUNITNO;
QString         strCurrentDir;
QString         connectMenJin;
QString         UNITTYPE;
myTCPsocket     *sockClient;
mainTitle       *titleBar;

accessControl   *MenJinControl;

long __stdcall   callback(_EXCEPTION_POINTERS*   excp)
{
    CCrashStack crashStack(excp);
    QString sCrashInfo = crashStack.GetExceptionInfo();
    QString sFileName = "testcrash.log";

    QFile file(sFileName);
    if (file.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        file.write(sCrashInfo.toUtf8());
        file.close();
    }

    qDebug()<<"Error:\n"<<sCrashInfo;
    //MessageBox(0,L"Error",L"error",MB_OK);
    QMessageBox msgBox;
    msgBox.setText(QString::fromUtf8("亲，我死了，重新启动下吧！"));
    msgBox.exec();

    return EXCEPTION_EXECUTE_HANDLER;
}

int main(int argc, char *argv[])
{
    SetUnhandledExceptionFilter(callback);

    QApplication a(argc, argv);
    QTranslator translator;
    translator.load("./qt_zh_CN.qm");
    a.installTranslator(&translator);
    a.setWindowIcon(QIcon("QSLOGO.ico"));
    a.setStyleSheet("QTableView{ gridline-color : rgb(150,150,150)}"
                    "QLineEdit {border: 1px solid rgb(150,150,150);}"
                    "QComboBox{border: 1px solid rgb(150,150,150);}"
                    "QComboBox::drop-down {subcontrol-position: top right;"
                        "width: 20px;"
                        "border-left-width: 1px;"
                        "border-left-color: rgb(150,150,150);"
                        "border-left-style: solid;}"
                    "QComboBox QAbstractItemView::item{height: 20px;}"
                    "QLineEdit QAbstractItemView::item{height: 20px;"
                        "selection-background-color:qconicalgradient(cx:0.5,cy:0.522909,angle:179.9,stop:0.494318 rgba(134,198,233,255),stop:0.5 rgba(206,234,248,255));}"
                    "QComboBox::down-arrow {image: url(:/image/jiantou.png);}"
                    "QDateTimeEdit{border: 1px solid rgb(150,150,150);}"
                    "QDateTimeEdit::drop-down {subcontrol-position: top right;"
                        "width: 20px;"
                        "border-left-width: 1px;"
                        "border-left-color: rgb(150,150,150);"
                        "border-left-style: solid;}"
                    "QDateTimeEdit::down-arrow {image: url(:/image/jiantou.png);}"
                    "QDateEdit{border: 1px solid rgb(150,150,150);}"
                    "QDateEdit::drop-down {subcontrol-position: top right;"
                        "width: 20px;"
                        "border-left-width: 1px;"
                        "border-left-color: rgb(150,150,150);"
                        "border-left-style: solid;}"
                    "QDateEdit::down-arrow {image: url(:/image/jiantou.png);}"
                    "QTabWidget::pane {border-top: 2px solid rgb(7,4,127);"
                        "background-color: rgb(240,240,240)}"
                    "QTabWidget::tab-bar {left: 5px;}"
                    "QMenuBar {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 lightgray, stop:1 darkgray); }"
                    "QMenuBar::item {spacing: 20px;padding: 5px 8px;"
                        "background: transparent;border-radius: 4px;"
                        "font:50pt;}"
                    "QMenuBar::item:selected {background: #a8a8a8;}"
                    "QMenuBar::item:pressed {background: #888888;}"
                    "QPushButton{border: 1px solid rgb(150,150,150);background-color:rgb(240,240,240);"
                        "padding: 2px 12px 2px 12px;"
                        "outline: none;}"
                    "QPushButton:hover{background-color:rgb(240,240,240);border: 1px solid rgb(7,4,127)}"
                    "QPushButton:pressed{background-color:rgb(220,220,220);border: 1px solid rgb(7,4,127)}"
                    "QStatusBar {background: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 darkgray, stop:1 lightgray);}"
                    );


    MainWindow w;
    w.setMinimumSize(900,625);
    w.show();

    return a.exec();
}
