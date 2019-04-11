#ifndef CHELIANGZHUANGTAI_H
#define CHELIANGZHUANGTAI_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QStandardItemModel>
#include <QTableView>
#include <QComboBox>
#include <QKeyEvent>
#include <QDate>
#include <QFont>
#include <QColor>
#include <QSizePolicy>
#include <QTabWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QTextBrowser>
#include <QCheckBox>
#include <QPushButton>
#include <QDateTimeEdit>
#include <QDateEdit>
#include <QList>
#include <QDesktopWidget>
#include <QApplication>
#include <QString>
#include <QList>
#include <QGroupBox>
#include <QListView>
#include "mymysql.h"
#include "pubfunc.h"
#include "mytcpsocket.h"

class cheliangzhuangtai : public QDialog
{
    Q_OBJECT
public:
    explicit cheliangzhuangtai(QWidget *parent = 0);

private:
    QGroupBox *groupBox1;
    QGroupBox *groupBox2;
    QGroupBox *groupBox3;
    QGroupBox *groupBox4;
    QComboBox *comBox11;
    QComboBox *comBox12;
    QComboBox *comBox13;
    QComboBox *comBox14;

    QPushButton *querenBtn2;
    QPushButton *banciBtn;


    QList<QCheckBox *>      list1;
    QList<QCheckBox *>      list2;
    QList<QCheckBox *>      list3;
    QList<QCheckBox *>      list4;


public slots:
    void on_bancitiaozhengBtn();
    void on_querenxiabanBtn();

};

#endif // CHELIANGZHUANGTAI_H
