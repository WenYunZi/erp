#include "mytablewidget.h"

extern mymysql db;

myTableWidget::myTableWidget()
{
}

myTableWidget::myTableWidget(const char *str1, const char *str2, const char *str3)
{

    this->setColumnCount(3);
    this->setRowCount(1);
    //设置每列宽
    this->setColumnWidth(0,250);
    this->setColumnWidth(1,200);
    this->setColumnWidth(2,200);
    //设置表头
    QStringList header;
    header.append(QObject::tr(str1));
    header.append(QObject::tr(str2));
    header.append(QObject::tr(str3));
    this->setHorizontalHeaderLabels(header);

    comBox = new QComboBox;
    comBox->addItem(tr(""));
    const char *fillSQL = "select Material from MaterialSetting;";
    db.sql_fillComboBoxItem(fillSQL,comBox);
    comBox->setVisible(false);
    this->setCellWidget(0,0,comBox);

    //信号和槽函数
    connect(this,SIGNAL(cellClicked(int,int)),this,SLOT(appearComBox()));
}

void myTableWidget::appearComBox()
{
    int row = this->currentRow();
    this->cellWidget(row,0)->setVisible(true);
}

void myTableWidget::increaseRow()
{

}

void myTableWidget::deleteRow()
{

}

void myTableWidget::fillTableItem()
{

}
