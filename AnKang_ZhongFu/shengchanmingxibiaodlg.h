#ifndef SHENGCHANMINGXIBIAODLG_H
#define SHENGCHANMINGXIBIAODLG_H

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
#include "mymysql.h"

class shengchanmingxibiaoDlg : public QDialog
{
    Q_OBJECT
public:
    explicit shengchanmingxibiaoDlg(QWidget *parent = 0);
    ~shengchanmingxibiaoDlg();

signals:

public slots:

private:
    QLibrary    *library;
    QDateEdit   *dateEdit1;
    QDateEdit   *dateEdit2;
    QCheckBox   *checkBox1;
    QCheckBox   *checkBox2;
    QCheckBox   *checkBox3;
    QCheckBox   *checkBox4;
    QCheckBox   *checkBox5;
    QCheckBox   *checkBox6;
    QComboBox   *comBox1;
    QComboBox   *comBox2;
    QComboBox   *comBox3;
    QComboBox   *comBox4;
    QComboBox   *comBox5;
    QPushButton *btn1;
    QPushButton *btn2;
    QPushButton *btn3;
    QPushButton *btn4;
    QPushButton *btn5;
    QPushButton *btn6;
    QPushButton *btn7;
    QPushButton *btn8;
    QToolButton *toolBtn;

private slots:
    void on_kehuhuizong();
    void on_meichexiaohao();
    void on_meipanxiaohao();
    void on_xiaohaohuizong();
    void on_cangweixiaohao();
    void on_chanpinxiaohao();
    void on_kehuxiaohao();
    void on_biaohaohuizong();
    void on_close();
};


#endif // SHENGCHANMINGXIBIAODLG_H
