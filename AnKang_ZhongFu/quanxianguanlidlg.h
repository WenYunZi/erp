#ifndef QUANXIANGUANLIDLG_H
#define QUANXIANGUANLIDLG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QStandardItemModel>
#include <QTableView>
#include <QComboBox>
#include <QKeyEvent>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QList>
#include <QToolBar>
#include <QAction>
#include <QMessageBox>
#include <QTreeView>
#include <QPushButton>
#include <QTreeWidget>
#include <QStringList>
#include <QTreeWidgetItem>
#include <QString>
#include "mymysql.h"

class quanxianguanliDlg : public QDialog
{
    Q_OBJECT
public:
    explicit quanxianguanliDlg(QWidget *parent = 0);
    ~quanxianguanliDlg();
    void refresh();

private:
    void keyPressEvent(QKeyEvent *event);

private:
    const char          *SQL;
    QCheckBox           *checkBox;

    QList<QTreeWidgetItem *> itemList;

    QTreeWidgetItem     *root1;
    QTreeWidgetItem     *root2;
    QTreeWidgetItem     *root3;
    QTreeWidgetItem     *root4;
    QTreeWidgetItem     *root5;
    QTreeWidgetItem     *root6;
    QTreeWidgetItem     *root7;
    QTreeWidgetItem     *root8;
    QTreeWidgetItem     *root9;
    QTreeWidgetItem     *root10;
    QTreeWidgetItem     *root11;
    QTreeWidgetItem     *root12;
    QTreeWidgetItem     *root13;
    QTreeWidgetItem     *root14;
    QTreeWidgetItem     *root15;
    QTreeWidgetItem     *root16;

    QTreeWidgetItem     *leaf11;
    QTreeWidgetItem     *leaf12;
    QTreeWidgetItem     *leaf13;
    QTreeWidgetItem     *leaf14;
    QTreeWidgetItem     *leaf15;
    QTreeWidgetItem     *leaf16;

    QTreeWidgetItem     *leaf21;
    QTreeWidgetItem     *leaf22;

    QTreeWidgetItem     *leaf31;
    QTreeWidgetItem     *leaf32;
    QTreeWidgetItem     *leaf33;
    QTreeWidgetItem     *leaf34;
    QTreeWidgetItem     *leaf35;

    QTreeWidgetItem     *leaf41;

    QTreeWidgetItem     *leaf51;
    QTreeWidgetItem     *leaf52;
    QTreeWidgetItem     *leaf53;
    QTreeWidgetItem     *leaf54;
    QTreeWidgetItem     *leaf55;
    QTreeWidgetItem     *leaf56;
    QTreeWidgetItem     *leaf57;
    QTreeWidgetItem     *leaf58;
    QTreeWidgetItem     *leaf59;
    QTreeWidgetItem     *leaf510;

    QTreeWidgetItem     *leaf61;
    QTreeWidgetItem     *leaf62;
    QTreeWidgetItem     *leaf63;
    QTreeWidgetItem     *leaf64;

    QTreeWidgetItem     *leaf71;
    QTreeWidgetItem     *leaf72;
    QTreeWidgetItem     *leaf73;
    QTreeWidgetItem     *leaf74;
    QTreeWidgetItem     *leaf75;
    QTreeWidgetItem     *leaf76;

    QTreeWidgetItem     *leaf81;
    QTreeWidgetItem     *leaf82;
    QTreeWidgetItem     *leaf83;

    QTreeWidgetItem     *leaf91;
    QTreeWidgetItem     *leaf92;
    QTreeWidgetItem     *leaf93;
    QTreeWidgetItem     *leaf94;
//    QTreeWidgetItem     *leaf95;
//    QTreeWidgetItem     *leaf96;
//    QTreeWidgetItem     *leaf97;
//    QTreeWidgetItem     *leaf98;
//    QTreeWidgetItem     *leaf99;
    QTreeWidgetItem     *leaf910;
    QTreeWidgetItem     *leaf911;
//    QTreeWidgetItem     *leaf912;
    QTreeWidgetItem     *leaf913;
    QTreeWidgetItem     *leaf914;

    QTreeWidgetItem     *leaf101;
    QTreeWidgetItem     *leaf102;
    QTreeWidgetItem     *leaf103;
    QTreeWidgetItem     *leaf104;
    QTreeWidgetItem     *leaf105;
    QTreeWidgetItem     *leaf106;
    QTreeWidgetItem     *leaf107;
    QTreeWidgetItem     *leaf108;
    QTreeWidgetItem     *leaf109;
    QTreeWidgetItem     *leaf1010;

    QTreeWidgetItem     *leaf111;
    QTreeWidgetItem     *leaf112;
    QTreeWidgetItem     *leaf113;
    QTreeWidgetItem     *leaf114;
    QTreeWidgetItem     *leaf115;
    QTreeWidgetItem     *leaf116;
    QTreeWidgetItem     *leaf117;
    //add liwenxiu 2017-11-2
    QTreeWidgetItem     *leaf118;
    QTreeWidgetItem     *leaf119;
    //end liwenxiu 2017-11-2

    QTreeWidgetItem     *leaf121;
    QTreeWidgetItem     *leaf122;
    QTreeWidgetItem     *leaf123;
    QTreeWidgetItem     *leaf124;
    QTreeWidgetItem     *leaf125;

    QTreeWidgetItem     *leaf131;

    QTreeWidgetItem     *leaf141;

    QTreeWidgetItem     *leaf151;
    QTreeWidgetItem     *leaf152;
    QTreeWidgetItem     *leaf153;
    QTreeWidgetItem     *leaf154;
    QTreeWidgetItem     *leaf155;
    QTreeWidgetItem     *leaf156;

    QTreeWidgetItem     *leaf161;
    QTreeWidgetItem     *leaf162;
    QTreeWidgetItem     *leaf163;
    QTreeWidgetItem     *leaf164;
    QTreeWidgetItem     *leaf165;
    QTreeWidgetItem     *leaf166;
    QTreeWidgetItem     *leaf167;
    QTreeWidgetItem     *leaf168;
    QTreeWidgetItem     *leaf169;
    QTreeWidgetItem     *leaf1610;
    QTreeWidgetItem     *leaf1611;
    //add liwenxiu 2017-11-1
    QTreeWidgetItem     *leaf1612;
    //end liwenxiu 2017-11-1

    QTableView          *view;
    QTreeWidget         *treeWidget;
    QStandardItemModel  *model = NULL;
    QLineEdit           *lineEdit;
    QPushButton         *Btn;
    QPushButton         *Btn1;

public slots:

private slots:
    void on_stateChanged();
    void on_leafstateChanged();
    void ShowSupplyclick();
    void on_updateAction();
    void on_refresh();
};

#endif // QUANXIANGUANLIDLG_H
