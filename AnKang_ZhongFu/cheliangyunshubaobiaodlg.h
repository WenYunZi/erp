#ifndef CHELIANGYUNSHUBAOBIAODLG_H
#define CHELIANGYUNSHUBAOBIAODLG_H

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
#include <QDebug>
#include <QCheckBox>
#include <QPushButton>
#include <QToolButton>
#include <QIcon>
#include <QListView>
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

class cheliangyunshubaobiaoDlg : public QDialog
{
    Q_OBJECT
public:
    explicit cheliangyunshubaobiaoDlg(QWidget *parent = 0);
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
    QComboBox   *comBox1;
    QComboBox   *comBox2;
    QComboBox   *comBox3;
    QComboBox   *comBox4;
    QComboBox   *comBox5;
    QComboBox   *comBox6;
    QPushButton *btn1;
    QPushButton *btn2;
    QPushButton *btn3;

    QAxWidget   *reportView;
    QAxObject   *m_report;

private slots:
    void on_fahuomingxi();
    void on_cheliangyunju();
    void on_cheliangyouhao();
    void on_comBox3Correspond();

};

#endif // CHELIANGYUNSHUBAOBIAODLG_H
