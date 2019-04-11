#ifndef SHENGCHANYUJINGDLG_H
#define SHENGCHANYUJINGDLG_H

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
#include <QKeyEvent>
#include <QListView>
#include <QTextEdit>
#include <QMessageBox>
#include <QString>
#include "mymysql.h"
#include "mytcpsocket.h"

class shengchanyujingDlg : public QDialog
{
    Q_OBJECT
public:
    explicit shengchanyujingDlg(QWidget *parent = 0);
    void refresh();

private:
    QString              ContractNumber;
    const char          *SQL;
    QComboBox           *comBox1;
    QComboBox           *comBox2;
    QComboBox           *comBox3;
    QPushButton         *Btn1;
    QTableView          *view;
    QStandardItemModel  *model = NULL;

private:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void comBox1Correspond();
    void on_querenBtn();
    void ShowSupplyclick();

};

#endif // SHENGCHANYUJINGDLG_H
