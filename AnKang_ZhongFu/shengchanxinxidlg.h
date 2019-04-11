#ifndef SHENGCHANXINXIDLG_H
#define SHENGCHANXINXIDLG_H

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
#include <QPushButton>
#include <QDateTimeEdit>
#include <QDateEdit>
#include <QList>
#include <QDesktopWidget>
#include <QApplication>
#include <QString>
#include "mymysql.h"
#include "pubfunc.h"

class shengchanxinxiDlg : public QDialog
{
    Q_OBJECT
public:
    explicit shengchanxinxiDlg(QString tasklist, QWidget *parent = 0);
private:
    QString SQL;
    QTableView *view;
    QStandardItemModel *model = NULL;



signals:

public slots:

};

#endif // SHENGCHANXINXIDLG_H
