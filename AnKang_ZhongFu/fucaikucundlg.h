#ifndef FUCAIKUCUNDLG_H
#define FUCAIKUCUNDLG_H

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

class fucaikucunDlg : public QDialog
{
    Q_OBJECT
public:
    explicit fucaikucunDlg(QWidget *parent = 0);
    void refresh();

private:
    const char          *SQL;
    QCheckBox           *checkBox1;
    QCheckBox           *checkBox2;
    QComboBox           *comBox1;
    QComboBox           *comBox2;
    QPushButton         *chaxun;
    QTableView          *view;
    QStandardItemModel  *model = NULL;

private:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_chaxun();
};

#endif // FUCAIKUCUNDLG_H
