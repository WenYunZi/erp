#ifndef HETONGZHIXINGQINGKUANGDLG_H
#define HETONGZHIXINGQINGKUANGDLG_H

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
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QKeyEvent>
#include <QTextEdit>
#include <QMessageBox>
#include <QString>
#include "mymysql.h"
#include "mycombobox.h"

class hetongzhixingqingkuangDlg : public QDialog
{
    Q_OBJECT
public:
    explicit hetongzhixingqingkuangDlg(QWidget *parent = 0);
    void refresh();

private:
    const char          *SQL;
    QComboBox           *comBox1;
    QComboBox           *comBox2;
    QCheckBox           *EngineerNameCheckBox;
    QPushButton         *Btn1;
    QPushButton         *Btn2;
    QTableView          *view;
    QStandardItemModel  *model = NULL;

private:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_shaixuanBtn();
    void on_quanbuBtn();
    void comBox1Correspond();
};

#endif // HETONGZHIXINGQINGKUANGDLG_H
