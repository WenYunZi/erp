#ifndef XITONGSUODINGDLG_H
#define XITONGSUODINGDLG_H

#include <QDialog>
#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QCloseEvent>
#include <QVBoxLayout>
#include <QPushButton>
#include "pubfunc.h"
#include "mymysql.h"

class xitongsuodingDlg : public QDialog
{
    Q_OBJECT
public:
    explicit xitongsuodingDlg(QWidget *parent = 0);

private:
    void keyPressEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *closeEvent);

private:
    bool         flag;
    QLabel      *label;
    QLabel      *label1;
    QLineEdit   *lineEdit;
    QPushButton *ok;

private slots:
    void on_ok();


};

#endif // XITONGSUODINGDLG_H
