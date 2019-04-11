#ifndef SHENGCHANFENBUDLG_H
#define SHENGCHANFENBUDLG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QStandardItemModel>
#include <QTableView>
#include <QComboBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QDate>
#include <QVBoxLayout>
#include <QDateEdit>
#include <QCheckBox>
#include <QListView>
#include <QPushButton>
#include <QToolButton>
#include <QIcon>
#include <QToolBar>
#include <QTableView>
#include <QStandardItemModel>
#include <QListView>
#include <QLibrary>
#include <QByteArray>
#include <QLibrary>
#include <QAction>
#include <QString>
#include <QMessageBox>
#include <QAxWidget>
#include <QAxObject>
#include "mymysql.h"
#include "myexcel.h"

class shengchanfenbuDlg : public QDialog
{
    Q_OBJECT
public:
    explicit shengchanfenbuDlg(QWidget *parent = 0);
    void refresh();

private:
    QString SQL;
    QDateTimeEdit *dateEdit1;
    QDateTimeEdit *dateEdit2;
    QCheckBox     *UnitNoCheck;
    QComboBox     *UnitNoCombox;

    QLabel        *ProductedVolumeLabel;

    QPushButton *chaxunBtn;
    QPushButton *daochuBtn;
    QTableView *view;
    QStandardItemModel *model = NULL;
    myExcel *view2Excel;

private slots:
    void on_chaxunBtn();
    void on_daochuBtn();


};

#endif // SHENGCHANFENBUDLG_H
