#ifndef SHUXINGTOOLBARDLG_H
#define SHUXINGTOOLBARDLG_H

#include <QDialog>
#include <QCheckBox>
#include <QList>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QSignalMapper>
#include <QMessageBox>
#include "mymysql.h"

class shuxingtoolbarDlg : public QDialog
{
    Q_OBJECT
public:
    explicit shuxingtoolbarDlg(QWidget *parent = 0);
    ~shuxingtoolbarDlg();
    void setContractNumber(QString ContractNumber);
    void init_shuxingToolBar(QString ContractNumber,QString EngineerName,QString StartTime);

public:
    QString shuxing;

public:
    QGridLayout         *   layout;
    QCheckBox           **  checkBox;
    QList<QCheckBox *>      list;
    QSignalMapper       *   signalmapper;

private slots:
    void chanpinshuxing();
};

#endif // SHUXINGTOOLBARDLG_H
