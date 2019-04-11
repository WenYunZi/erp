#ifndef YUANLIAOXIAOHAOJIAGETIAOZHENGDLG_H
#define YUANLIAOXIAOHAOJIAGETIAOZHENGDLG_H

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
#include <QTextEdit>
#include <QToolBar>
#include <QAction>
#include <QMessageBox>
#include <QGroupBox>
#include <QButtonGroup>
#include <QPushButton>
#include <QRadioButton>
#include <QString>
#include "mymysql.h"

class yuanliaoxiaohaojiagetiaozhengDlg : public QDialog
{
    Q_OBJECT
public:
    explicit yuanliaoxiaohaojiagetiaozhengDlg(QWidget *parent = 0);
    void refresh();

private:
    QTabWidget          *tabWidget;
    QWidget             *yuanliaoxiaohaojiagetiaozheng;
    QWidget             *tiaozhengjiluchaxun;
    QWidget             *yuanliaomingchengtiaozheng;
    QWidget             *mingchengtiaozhengjilu;

private:
    QLineEdit           *lineEdit1;
    QLineEdit           *lineEdit2;
    QComboBox           *comBox1;
    QComboBox           *comBox2;
    QComboBox           *comBox3;
    QCheckBox           *checkBox1;
    QCheckBox           *checkBox2;
    QDateTimeEdit       *datetimeEdit1;
    QDateTimeEdit       *datetimeEdit2;
    QPushButton         *Btn1;
    QPushButton         *Btn2;
    QPushButton         *Btn3;
    QTableView          *view;

private:
    QComboBox           *twocomBox;
    QPushButton         *twoBtn1;
    QPushButton         *twoBtn2;
    QPushButton         *twoBtn3;
    QTableView          *twoview;

private:
    QDateTimeEdit       *threedatetimeEdit1;
    QDateTimeEdit       *threedatetimeEdit2;
    QCheckBox           *threecheckBox1;
    QCheckBox           *threecheckBox2;
    QCheckBox           *threecheckBox3;
    QCheckBox           *threecheckBox4;
    QComboBox           *threecomBox1;
    QComboBox           *threecomBox2;
    QComboBox           *threecomBox3;
    QComboBox           *threecomBox4;
    QComboBox           *threecomBox5;
    QComboBox           *threecomBox6;
    QLineEdit           *threelineEdit1;
    QLineEdit           *threelineEdit2;
    QPushButton         *threeBtn1;
    QPushButton         *threeBtn2;
    QPushButton         *threeBtn3;
    QTableView          *threeview;

private:
    QComboBox           *fourcomBox;
    QPushButton         *fourBtn1;
    QPushButton         *fourBtn2;
    QPushButton         *fourBtn3;
    QTableView          *fourview;


private:
    void keyPressEvent(QKeyEvent *event);
    void creatTabPage1();
    void creatTabPage2();
    void creatTabPage3();
    void creatTabPage4();

};

#endif // YUANLIAOXIAOHAOJIAGETIAOZHENGDLG_H
