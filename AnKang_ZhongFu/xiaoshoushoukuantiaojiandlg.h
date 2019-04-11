#ifndef XIAOSHOUSHOUKUANTIAOJIANDLG_H
#define XIAOSHOUSHOUKUANTIAOJIANDLG_H

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
#include <QListView>
#include <QCheckBox>
#include <QKeyEvent>
#include <QTextEdit>
#include <QMessageBox>
#include <QString>
#include "mymysql.h"
#include "mytcpsocket.h"

class xiaoshoushoukuantiaojianDlg : public QDialog
{
    Q_OBJECT
public:
    explicit xiaoshoushoukuantiaojianDlg(QWidget *parent = 0);
    void refresh();

private:
    QString              ContractNumber;
    const char          *SQL;
    QComboBox           *comBox1;
    QComboBox           *comBox2;
    QComboBox           *comBox3;
    QTextEdit           *textEdit;
    QPushButton         *Btn1;
    QTableView          *view;
    QStandardItemModel  *model = NULL;

private:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void comBox1Correspond();
    void ShowSupplyclick();
    void on_querenBtn();

};

#endif // XIAOSHOUSHOUKUANTIAOJIANDLG_H
