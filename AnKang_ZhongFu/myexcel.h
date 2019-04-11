#ifndef MYEXCEL_H
#define MYEXCEL_H

#include <QDialog>
#include <QTableWidget>
#include <QTableView>
#include <QFileDialog>
#include <QDesktopServices>
#include <QMessageBox>
#include <QAxObject>
#include <QDebug>
#include <QProgressDialog>

class myExcel : public QDialog
{
    Q_OBJECT
public:
    explicit myExcel(QWidget *parent = 0);

public:
    void Table2ExcelByHtml(QTableView *table,QString title);

public slots:

};

#endif // MYEXCEL_H
