#ifndef KUCUNXINXIDLG_H
#define KUCUNXINXIDLG_H

#include <QDialog>
#include <QWidget>
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
#include "mymysql.h"
#include "pubfunc.h"

class kucunxinxiDlg : public QDialog
{
    Q_OBJECT
public:
    explicit kucunxinxiDlg(QWidget *parent = 0);

private:
    QString SQL;
    QTableView *view;
    QStandardItemModel *model = NULL;
    QPushButton *shuaxinBtn;
    QPushButton *saveKuCunBtn;

private slots:
    void on_shuaxinBtn();
    void on_saveKuCunBtn();

};

#endif // KUCUNXINXIDLG_H
