#ifndef CONTRACTDELETEDLG_H
#define CONTRACTDELETEDLG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
#include <QString>
#include "mymysql.h"

class ContractDeleteDlg : public QDialog
{
    Q_OBJECT
public:
    explicit ContractDeleteDlg(QWidget *parent = 0);

public:
    bool isOnOkBtn;

private:
    QPushButton *OkBtn;
    QPushButton *CancelBtn;
    QLineEdit   *PassWordLineEdit;

private slots:
    void on_OkBtn();
    void on_CancelBtn();
};

#endif // CONTRACTDELETEDLG_H
