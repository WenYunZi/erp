#ifndef MIMAXIUGAIDLG_H
#define MIMAXIUGAIDLG_H

#include <QDialog>
#include <QMessageBox>
#include <QMdiSubWindow>
#include <QLabel>
#include <QLineEdit>
#include <QKeyEvent>
#include <QTextEdit>
#include <QStandardItemModel>
#include <QTableView>
#include <QComboBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QString>
#include "mymysql.h"

class mimaxiugaiDlg : public QDialog
{
    Q_OBJECT
public:
    explicit mimaxiugaiDlg(QWidget *parent = 0);

private:
    void keyPressEvent(QKeyEvent *event);

private:
    QLineEdit   *lineEdit1;
    QLineEdit   *lineEdit2;
    QLineEdit   *lineEdit3;
    QPushButton *Btn;
    QComboBox   *combo1;
    QString      str1,str2,str3,str4;

private slots:
    void on_updateAction();
};

#endif // MIMAXIUGAIDLG_H
