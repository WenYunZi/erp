#ifndef GONGCHENGYUNJUQUERENDLG_H
#define GONGCHENGYUNJUQUERENDLG_H

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
#include "mytcpsocket.h"
#include "mycombobox.h"

class gongchengyunjuquerenDlg : public QDialog
{
    Q_OBJECT
public:
    explicit gongchengyunjuquerenDlg(QWidget *parent = 0);
    void refresh();

private:
    const char          *SQL;
    QDateTimeEdit       *dateEdit1;
    QDateTimeEdit       *dateEdit2;
    QLineEdit           *lineEdit1;
    QLineEdit           *lineEdit2;
    QLineEdit           *lineEdit3;
    QLineEdit           *YunJuLineEdit;
    QLineEdit           *YunFeiLineEdit;
    QPushButton         *Btn;
    QCheckBox           *checkBox;
    QCheckBox           *checkBox1;
    QTableView          *view1;
    QStandardItemModel  *model1 = NULL;
    QComboBox           *comBox;
    QPushButton         *chaxunBtn;

private:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void ShowSupplyclick();
    void on_YunJuLineEdit();
    void on_yunjuquerenBtn();
    void on_chaxunBtn();

};

#endif // GONGCHENGYUNJUQUERENDLG_H
