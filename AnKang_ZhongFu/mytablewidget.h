#ifndef MYTABLEWIDGET_H
#define MYTABLEWIDGET_H

#include <QTableWidget>
#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QStandardItemModel>
#include <QTableView>
#include <QComboBox>
#include <QTabWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QSignalMapper>
#include <QVBoxLayout>
#include <QTextBrowser>
#include <QCheckBox>
#include <QLCDNumber>
#include <QPushButton>
#include <QTableWidgetItem>
#include <QDateTimeEdit>
#include <QDateEdit>
#include <QGroupBox>
#include <QRadioButton>
#include <QToolButton>
#include <QTableWidget>
#include <QMessageBox>
#include <QToolBar>
#include <QAction>
#include <QString>
#include "mymysql.h"

class myTableWidget : public QTableWidget
{
public:
    myTableWidget();
    myTableWidget(const char *str1, const char *str2, const char *str3);

private:
    QComboBox *comBox;

private slots:
    void appearComBox();
    void increaseRow();
    void deleteRow();
    void fillTableItem();
};

#endif // MYTABLEWIDGET_H
