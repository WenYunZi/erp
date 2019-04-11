#ifndef JIESUANDANDLG_H
#define JIESUANDANDLG_H

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
#include <QRegExp>
#include <QByteArray>
#include <QLibrary>
#include <QAction>
#include <QString>
#include <QMessageBox>
#include <QAxWidget>
#include <QAxObject>
#include "mymysql.h"
#include "mycombobox.h"
#include "myexcel.h"

class jiesuandanDlg : public QDialog
{
    Q_OBJECT
public:
    explicit jiesuandanDlg(QWidget *parent = 0);
    void refresh();

public:
    QTabWidget      *tabWidget;
    QWidget         *baobiao;
    QWidget         *kehuzhangmu;

    myExcel         *tableview2Excel;

private:
    QLibrary        *library;
    QDateTimeEdit   *dateEdit1;
    QDateTimeEdit   *dateEdit2;
    QCheckBox       *checkBox1;
    QCheckBox       *checkBox2;
    myComboBox      *comBox1;
    myComboBox      *comBox2;
    QPushButton     *btn1;
    QPushButton     *btn2;
    QPushButton     *btn3;
    QPushButton     *btn4;

    QAxWidget       *reportView;
    QAxObject       *m_report;

private:
    const char          *SQL2;
    QTableView          *twoview;
    QStandardItemModel  *twomodel = NULL;
    QPushButton         *twodaochuBtn;
    QPushButton         *twoshuaxinBtn;
    myComboBox          *twocomBox;
    QCheckBox           *twoCheckBox;


private:
    QString ConvertToChinese(double x);

private:
    void creatTabPage1();
    void creatTabPage2();
    void setModelStyle(QStandardItemModel *model);

private slots:
    void on_rijiesuandan();
    void on_yuejiesuandan();
    void on_zhuanzhangpingzheng();
    void on_dateChanged();
    void on_comBox1React();
    void on_anniu();
    void on_twodaochu();
    void on_twoshuaxin();

};

#endif // JIESUANDANDLG_H
