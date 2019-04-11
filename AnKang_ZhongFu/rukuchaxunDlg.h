#ifndef RUKUCHAXUN_H
#define RUKUCHAXUN_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QStandardItemModel>
#include <QTableView>
#include <QComboBox>
#include <QKeyEvent>
#include <QDate>
#include <QFont>
#include <QColor>
#include <QSizePolicy>
#include <QTabWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QTextBrowser>
#include <QCheckBox>
#include <QLCDNumber>
#include <QPushButton>
#include <QDateTimeEdit>
#include <QDateEdit>
#include <QList>
#include <QString>
#include <QDesktopWidget>
#include "warehousewidget.h"
#include "kucunxinxidlg.h"
#include "mymysql.h"
#include "pubfunc.h"

class rukuchaxunDlg : public QDialog
{
    Q_OBJECT
public:
    explicit rukuchaxunDlg(QWidget *parent = 0);
    ~rukuchaxunDlg();
    void refresh();

private:
    void keyPressEvent(QKeyEvent *event);

private:
    const char          *SQL1;
    const char          *SQL2;
    const char          *SQL3;
    const char          *SQL4;
    QDate                date;
    QTabWidget          *tabWidget;
    QWidget             *lilunkucun;
    QWidget             *kucunchaxun;
    QWidget             *jiecundianchaxun;
    QWidget             *lishikucunchaxun;

private:
    QList<WarehouseWidget *>   wareHouseList;
    QDateTimeEdit       *datetime;
    QPushButton         *chaxun;
    QTableView          *view;
    QStandardItemModel  *model = NULL;

private:
    QGridLayout         *twolayout;
    QPushButton         *twoshuaxin;
    QPushButton         *twobaocun;
    QPushButton         *twoqitaxinxi;
    QTableView          *twoview;
    QStandardItemModel  *twomodel = NULL;
    QComboBox           *twoCombox;

private:
    QCheckBox           *threecheckBox1;
    QDateEdit           *threedate1;
    QDateEdit           *threedate2;
    QComboBox           *threecombo1;
    QPushButton         *threechaxun;
    QTableView          *threeview;
    QStandardItemModel  *threemodel = NULL;

private:
    QDateTimeEdit       *fourdatetime;
    QPushButton         *fourchaxun;
    QTableView          *fourview;
    QStandardItemModel  *fourmodel = NULL;

private:
    void creatTabPage1();
    void creatTabPage2();
    void creatTabPage3();
    void creatTabPage4();

private slots:
    void on_chaxun();
    void on_twoshuaxin();
    void on_twobaocun();
    void on_twoqitaxinxi();
    void on_threechaxun();
    void on_fourchaxun();
};

#endif // RUKUCHAXUN_H
