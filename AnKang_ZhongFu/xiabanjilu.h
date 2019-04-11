#ifndef XIABANJILU_H
#define XIABANJILU_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QStandardItemModel>
#include <QTableView>
#include <QComboBox>
#include <QKeyEvent>
#include <QTabWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextBrowser>
#include <QCheckBox>
#include <QLCDNumber>
#include <QPushButton>
#include <QDateTimeEdit>
#include <QDateEdit>
#include <QBrush>
#include <QDebug>
#include <QToolButton>
#include <QToolBar>
#include <QMessageBox>
#include <QAction>
#include <QString>
#include "mymysql.h"
#include "pubfunc.h"

class xiabanjilu : public QWidget
{
    Q_OBJECT
public:
    explicit xiabanjilu(QWidget *parent = 0);

private:
    const char          *SQL;
    QCheckBox           *checkBox;
    QDateTimeEdit       *dateTimeEdit1;
    QDateTimeEdit       *dateTimeEdit2;
    QComboBox           *cheNoCombox;
    QPushButton         *chaxunBtn;
    QTableView          *view;
    QStandardItemModel  *model = NULL;

signals:

private slots:
    void on_chaxunBtn();

};

#endif // XIABANJILU_H
