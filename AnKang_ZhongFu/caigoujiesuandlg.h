#ifndef CAIGOUJIESUANDLG_H
#define CAIGOUJIESUANDLG_H

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
#include <QModelIndex>
#include <QTextEdit>
#include <QToolBar>
#include <QAction>
#include <QDebug>
#include <QMessageBox>
#include <QGroupBox>
#include <QButtonGroup>
#include <QPushButton>
#include <QRadioButton>
#include <QString>
#include <QAxObject>
#include <QAxWidget>
#include <QLibrary>
#include "mymysql.h"
#include "mytcpsocket.h"
#include "mycombobox.h"

class caigoujiesuanDlg : public QDialog
{
    Q_OBJECT
public:
    explicit caigoujiesuanDlg(QWidget *parent = 0);
    void refresh();

private:
    void keyPressEvent(QKeyEvent *event);

private:
    QLibrary                *library;
    QDateTimeEdit           *dateEdit1;
    QDateTimeEdit           *dateEdit2;

    QComboBox               *gouhuofangComBox;
    QComboBox               *gongchengmingchengComBox;
    QPushButton             *btn1;


    QAxWidget   *reportView;
    QAxObject   *m_report;

private slots:
    void on_gonghuomingxi();
    void touch_gouhuofangComBox();
    void touch_gongchengmingchengComBox();

};

#endif // CAIGOUJIESUANDLG_H
