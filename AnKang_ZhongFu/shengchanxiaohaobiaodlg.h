#ifndef SHENGCHANXIAOHAOBIAODLG_H
#define SHENGCHANXIAOHAOBIAODLG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QStandardItemModel>
#include <QTableView>
#include <QComboBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QThread>
#include <QDate>
#include <QVBoxLayout>
#include <QDateEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QToolButton>
#include <QIcon>
#include <QToolBar>
#include <QLibrary>
#include <QThread>
#include <QByteArray>
#include <QFileInfo>
#include <QLibrary>
#include <QAction>
#include <QString>
#include <QMessageBox>
#include <QAxWidget>
#include <QAxObject>
#include "mymysql.h"

class shengchanxiaohaobiaoDlg : public QDialog
{
    Q_OBJECT
public:
    explicit shengchanxiaohaobiaoDlg(QWidget *parent = 0);
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
    QPushButton *btn9;

    QAxWidget   *reportView;
    QAxObject   *m_report;


private slots:
    void on_shengchanmingxi();
    void on_kehuhuizong();
    void on_haocaihuizong();
    void on_yuanliaomeichexiaohao();
    void on_yuanliaomeipanxiaohao();
    void on_xiaohaokehufenzu();
    void on_xiaohaochanpinfenzu();
    void on_cangweihaocaihuizong();
    void on_biaohaohuizong();
};

#endif // SHENGCHANXIAOHAOBIAODLG_H
