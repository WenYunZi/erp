#ifndef FAHUOJIAGEPILIANGTIAOZHENGDLG_H
#define FAHUOJIAGEPILIANGTIAOZHENGDLG_H

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
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
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
#include "mycombobox.h"
#include "mytcpsocket.h"

class fahuojiagepiliangtiaozhengDlg : public QDialog
{
    Q_OBJECT
public:
    explicit fahuojiagepiliangtiaozhengDlg(QWidget *parent = 0);
    void refresh();

private:
    QTabWidget          *tabWidget;
    QWidget             *jiagetiaozheng;
    QWidget             *shijianduanjiagetiaozhengjilu;

private:
    QString              tiaojian;
    const char          *SQL1;
    QDateTimeEdit       *dateEdit1;
    QDateTimeEdit       *dateEdit2;
    QCheckBox           *oneEngineerCheckBox;
    QComboBox           *oneStrengthGradeCombox;
    QComboBox           *oneCustomerNameCombox;
    QComboBox           *oneEngineerCombox;
    QLineEdit           *oneNewPriceLineEdit;
    QLineEdit           *OperatorLineEdit;
    QPushButton         *oneConfirmBtn;
    QPushButton         *oneFindBtn;
    QTableView          *view;
    QStandardItemModel  *model = NULL;

private:
    const char          *SQL2;
    QDateTimeEdit       *twodateEdit1;
    QDateTimeEdit       *twodateEdit2;
    QComboBox           *twoCustomerComBox;
    QComboBox           *twoEngineerComBox;
    QCheckBox           *twoCustomerCheckBox;
    QCheckBox           *twoEngineerCheckBox;
    QPushButton         *twoFindBtn;
    QTableView          *twoview;
    QStandardItemModel  *twomodel = NULL;

private:
    const char          *SQL3;
    QDateEdit           *threedateEdit1;
    QDateEdit           *threedateEdit2;
    QPushButton         *threechaxun;
    QTableView          *threeview;
    QStandardItemModel  *threemodel = NULL;

private:
    void keyPressEvent(QKeyEvent *event);
    void creatTabPage1();
    void creatTabPage2();

private slots:
    void on_oneConfirmBtn();
    void on_oneFindBtn();
    void on_oneCustomerNameCombox();
    void on_dateChange();

private slots:
    void on_twoFindBtn();
    void on_twoCustomerComBox();
};

#endif // FAHUOJIAGEPILIANGTIAOZHENGDLG_H
