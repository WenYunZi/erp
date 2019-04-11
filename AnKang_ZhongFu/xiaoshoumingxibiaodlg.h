#ifndef XIAOSHOUMINGXIBIAODLG_H
#define XIAOSHOUMINGXIBIAODLG_H

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
#include <QPushButton>
#include <QToolButton>
#include <QIcon>
#include <QToolBar>
#include <QLibrary>
#include <QByteArray>
#include <QLibrary>
#include <QAction>
#include <QString>
#include <QMessageBox>
#include <QAxWidget>
#include <QAxObject>
#include "mymysql.h"

class xiaoshoumingxibiaoDlg : public QDialog
{
    Q_OBJECT
public:
    explicit xiaoshoumingxibiaoDlg(QWidget *parent = 0);
    void refresh();

private:
    QLibrary    *library;
    QDateTimeEdit   *dateEdit1;
    QDateTimeEdit   *dateEdit2;
    QCheckBox   *checkBox1;
    QCheckBox   *checkBox2;
    QCheckBox   *checkBox3;
    QCheckBox   *checkBox4;
    QCheckBox   *checkBox5;
    QCheckBox   *checkBox6;
    QCheckBox   *checkBox7;
    QCheckBox   *checkBox8;
    QCheckBox   *checkBox9;
    QComboBox   *comBox1;
    QComboBox   *comBox2;
    QComboBox   *comBox3;
    QComboBox   *comBox4;
    QComboBox   *comBox5;
    QComboBox   *comBox6;
    QComboBox   *comBox7;
    QComboBox   *comBox9;


    QPushButton *btn1;
    QPushButton *shengchanzongfangliangBtn;
    QPushButton *btn2;
    QPushButton *btn3;

    QAxWidget   *reportView;
    QAxObject   *m_report;

private slots:
    void on_xiaoshoumingxi();
    void on_shengchanzongfang();
    void on_fahuohuizong();
    void on_ganfenfahuo();
};

#endif // XIAOSHOUMINGXIBIAODLG_H
