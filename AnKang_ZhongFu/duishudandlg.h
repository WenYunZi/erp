#ifndef DUISHUDANDLG_H
#define DUISHUDANDLG_H

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
#include <QListView>
#include <QPushButton>
#include <QToolButton>
#include <QIcon>
#include <QToolBar>
#include <QListView>
#include <QLibrary>
#include <QByteArray>
#include <QLibrary>
#include <QAction>
#include <QString>
#include <QMessageBox>
#include <QAxWidget>
#include <QAxObject>
#include "mymysql.h"

class duishudanDlg : public QDialog
{
    Q_OBJECT
public:
    explicit duishudanDlg(QWidget *parent = 0);
    void refresh();

private:
    QLibrary    *library;
    QDateEdit   *dateEdit1;
    QDateEdit   *dateEdit2;
    QCheckBox   *checkBox1;
    QCheckBox   *checkBox2;
    QCheckBox   *checkBox3;
    QComboBox   *comBox1;
    QComboBox   *comBox2;
    QComboBox   *comBox3;
    QPushButton *btn1;

    QAxWidget   *reportView;
    QAxObject   *m_report;

private slots:
    void on_xiaoshoumingxi();
    void on_fahuohuizong();

};

#endif // DUISHUDANDLG_H
