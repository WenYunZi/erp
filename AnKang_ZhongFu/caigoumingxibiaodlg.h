#ifndef CAIGOUMINGXIBIAODLG_H
#define CAIGOUMINGXIBIAODLG_H

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
#include <QDateTimeEdit>
#include <QPaintEvent>
#include <QCheckBox>
#include <QPushButton>
#include <QToolButton>
#include <QIcon>
#include <QToolBar>
#include <QByteArray>
#include <QLibrary>
#include <QAction>
#include <QString>
#include <QMessageBox>
#include <QAxWidget>
#include <QAxObject>
#include "mymysql.h"

class caigoumingxibiaoDlg : public QDialog
{
    Q_OBJECT
public:
    explicit caigoumingxibiaoDlg(QWidget *parent = 0);
    ~caigoumingxibiaoDlg();
    void refresh();

public slots:

private:
    QLibrary        *library;
    QDateTimeEdit   *dateEdit1;
    QDateTimeEdit   *dateEdit2;
    QCheckBox       *checkBox1;
    QCheckBox       *checkBox2;
    QCheckBox       *checkBox3;
    QCheckBox       *checkBox4;
    QComboBox       *comBox1;
    QComboBox       *comBox2;
    QComboBox       *comBox3;
    QComboBox       *comBox4;
    QPushButton     *btn1;
    QPushButton     *btn2;
    QPushButton     *btn3;
    QPushButton     *btn4;
    QAxWidget       *reportView;
    QAxObject       *m_report;

private slots:
    void on_gongyingshangfenzu();
    void on_yuanliaofenzu();
    void on_gongyingshanghuizong();
    void on_yuanliaohuizong();
};

#endif // CAIGOUMINGXIBIAODLG_H
