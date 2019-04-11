#ifndef SHENGCHANFANGLIANGSHENGLIAODLG_H
#define SHENGCHANFANGLIANGSHENGLIAODLG_H

#include <QDialog>
#include "myexcel.h"
#include <QDateTimeEdit>
#include <QPushButton>
#include <QTableView>
#include <QStandardItemModel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <mymysql.h>

class shengchanfangliangshengliaoDlg : public QDialog
{
    Q_OBJECT
public:
    explicit shengchanfangliangshengliaoDlg(QWidget *parent = 0);
private:
    QString                      shengchanfangliangSQL;
    QString                      shengliaofangliangSQL;
    QString                      shengchanzongfangliangSQL;
    myExcel                      *ViewToExcel;

    QTableView                  *shengchanfangliangView;
    QStandardItemModel          *shengchanfangliangModel = NULL;

    QPushButton                 *shengchanfangliangBtn;
    QPushButton                 *shengliaofangliangBtn;
    QPushButton                 *shengchanzongfangliangBtn;
    QPushButton                 *ExportBtn;

    QDateTimeEdit               *DateTimeEdit1;
    QDateTimeEdit               *DateTimeEdit2;
signals:

public slots:
    void on_shengchanfangliangBtn();
    void on_shengliaofangliangBtn();
    void on_shengchanzongfangliangBtn();

    void on_ExportBtn();

};

#endif // SHENGCHANFANGLIANGSHENGLIAODLG_H
