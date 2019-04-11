#ifndef YUANLIAORUKUSHUJUTIAOZHENGDLG_H
#define YUANLIAORUKUSHUJUTIAOZHENGDLG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QTextEdit>
#include <QStandardItemModel>
#include <QTableView>
#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QDebug>
#include <QKeyEvent>
#include <QTextEdit>
#include <QToolBar>
#include <QAction>
#include <QMessageBox>
#include <QGroupBox>
#include <QButtonGroup>
#include <QPushButton>
#include <QRadioButton>
#include <QString>
#include "mymysql.h"
#include "mytcpsocket.h"
#include "mycombobox.h"

class yuanliaorukushujutiaozhengDlg : public QDialog
{
    Q_OBJECT
public:
    explicit yuanliaorukushujutiaozhengDlg(QWidget *parent = 0);
    void refresh();

private:
    QTabWidget          *tabWidget;
    QWidget             *yuanliaojiagetiaozheng;
    QWidget             *jiagetiaozhengjiluchaxun;

private:
    QString              tiaojian;
    QString              searchSQL1;
    const char          *SQL1;
    QComboBox           *MaterialCombox;
    QComboBox           *SupplierCombox;
    QDateTimeEdit       *datetimeEdit1;
    QDateTimeEdit       *datetimeEdit2;
    QLineEdit           *NewPriceLineEdit;
    QLineEdit           *OperatorLineEdit;
    QPushButton         *oneFindBtn;
    QPushButton         *PriceUpdateBtn;
    QTableView          *view;
    QStandardItemModel  *model = NULL;

private:
    const char          *SQL2;
    QDateTimeEdit       *twodatetimeEdit1;
    QDateTimeEdit       *twodatetimeEdit2;

    QCheckBox           *twoMaterialCheckBox;
    QCheckBox           *twoSupplierNameCheckBox;

    QComboBox           *twoMaterialCombox;
    QComboBox           *twoSupplierNameCombox;
    QPushButton         *twoFindBtn;
    QTableView          *twoview;
    QStandardItemModel  *twomodel = NULL;

private:
    int row;
    const char          *SQL3;
    QCheckBox           *threecheckBox;
    QLineEdit           *threelineEdit1;
    QLineEdit           *threelineEdit2;
    QDateTimeEdit       *threedatetimeEdit1;
    QDateTimeEdit       *threedatetimeEdit2;
    QDateTimeEdit       *threedatetimeEdit3;
    QComboBox           *threecombox1;
    QPushButton         *threerukujiluchaxun;
    QPushButton         *threeshijiantiaozheng;
    QTableView          *threeview;
    QStandardItemModel  *threemodel = NULL;

private:
    const char          *SQL4;
    QDateEdit           *fourdateEdit1;
    QDateEdit           *fourdateEdit2;
    QPushButton         *fourchaxun;
    QTableView          *fourview;
    QStandardItemModel  *fourmodel = NULL;

private:
    void keyPressEvent(QKeyEvent *event);
    void creatTabPage1();
    void creatTabPage2();

private slots:
    void on_MaterialCombox();
    void on_oneFindBtn();
    void on_PriceUpdateBtn();
    void on_twoMaterialCombox();
    void on_twoFindBtn();
};

#endif // YUANLIAORUKUSHUJUTIAOZHENGDLG_H
