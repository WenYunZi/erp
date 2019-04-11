#ifndef YUANLIAOSHEZHIDLG_H
#define YUANLIAOSHEZHIDLG_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QKeyEvent>
#include <QStandardItemModel>
#include <QTableView>
#include <QComboBox>
#include <QTabWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextBrowser>
#include <QCheckBox>
#include <QPushButton>
#include <QDateTimeEdit>
#include <QDateEdit>
#include <QToolButton>
#include <QToolBar>
#include <QAction>
#include <QString>
#include <QListView>
#include <QMessageBox>
#include "mymysql.h"
#include "mytcpsocket.h"

class yuanliaoshezhiDlg : public QDialog
{
    Q_OBJECT
public:
    explicit yuanliaoshezhiDlg(QWidget *parent = 0);
    ~yuanliaoshezhiDlg();
    void refresh();

private:
    void keyPressEvent(QKeyEvent *event);

private:
    QTabWidget          *tabWidget;
    QWidget             *yuanliaoshezhi;
    QWidget             *jizuyuanliaoduiyingERPyuanliao;
    QWidget             *jizuyuanliaoshezhi;

private:
    const char          *SQL1;
    const char          *SQL2;
    const char          *SQL3;
    QAction             *newAction;
    QAction             *saveAction;
    QAction             *updateAction;
    QAction             *deleteAction;
    QToolBar            *toolBar;
    QAction             *newAction2;
    QAction             *saveAction2;
    QAction             *updateAction2;
    QAction             *deleteAction2;
    QToolBar            *toolBar2;
    QAction             *newAction3;
    QAction             *saveAction3;
    QAction             *updateAction3;
    QAction             *deleteAction3;
    QToolBar            *toolBar3;
    QLineEdit           *MaterialNoLineEdit;
    QLineEdit           *MaterialNameLineEdit;
    QLineEdit           *SpecificationLineEdit;
    QLineEdit           *FoldOverLineEdit;
    QLineEdit           *RemarksLineEdit;
    QComboBox           *UnitCombox;
    QComboBox           *MaterialTyepCombox;
    QTableView          *MaterialView;
    QStandardItemModel  *MaterialModel = NULL;
    QComboBox           *twocombo1;
    QComboBox           *twocombo2;
    QComboBox           *twocombo3;
    QComboBox           *twocombo4;
    QTableView          *twoview;
    QStandardItemModel  *twomodel = NULL;
    QString              twostr1;
    QString              twostr2;
    QString              twostr3;
    QString              twostr4,twostr5;
    QComboBox           *threecombo1;
    QLineEdit           *threelineEdit1;
    QLineEdit           *threelineEdit2;
    QLineEdit           *threelineEdit3;
    QTableView          *threeview;
    QStandardItemModel  *threemodel = NULL;
    QString              threestr1,threestr2,threestr3,threestr4;
    QString              CorrespondingField;
    QString              id;

private:
    void creatTabPage1();
    void creatTabPage2();
    void creatTabPage3();

private slots:
    void on_newAction();
    void on_saveAction();
    void on_updateAction();
    void on_deleteAction();
    void on_newAction2();
    void on_saveAction2();
    void on_updateAction2();
    void on_deleteAction2();
    void on_newAction3();
    void on_saveAction3();
    void on_updateAction3();
    void on_deleteAction3();
    void ShowSupplyclick();
    void ShowSupplyclick2();
    void ShowSupplyclick3();
    void twocombo3Change();
    void twocombo4Change();

private:
    void createAction();
    void createTool();
    void createAction2();
    void createTool2();
    void createAction3();
    void createTool3();
};

#endif // YUANLIAOSHEZHIDLG_H
