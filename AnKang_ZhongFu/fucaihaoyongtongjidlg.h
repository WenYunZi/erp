#ifndef FUCAIHAOYONGTONGJIDLG_H
#define FUCAIHAOYONGTONGJIDLG_H

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
#include <QDebug>
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

class fucaihaoyongtongjiDlg : public QDialog
{
    Q_OBJECT
public:
    explicit fucaihaoyongtongjiDlg(QWidget *parent = 0);
    void refresh();

private:
    const char          *SQL;
    QCheckBox           *checkBox1;
    QCheckBox           *checkBox2;
    QCheckBox           *checkBox3;
    QCheckBox           *checkBox4;
    QCheckBox           *checkBox5;
    QComboBox           *comBox1;
    QComboBox           *comBox2;
    QComboBox           *comBox3;
    QComboBox           *comBox4;
    QComboBox           *comBox5;
    QDateEdit           *dateEidt1;
    QDateEdit           *dateEidt2;
    QPushButton         *chaxun;
    QTableView          *view;
    QStandardItemModel  *model = NULL;

private:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_chaxunBtn();

};

#endif // FUCAIHAOYONGTONGJIDLG_H
