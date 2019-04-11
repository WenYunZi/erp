#include "odbcoperator.h"

ODBCoperator::ODBCoperator()
{

}

int ODBCoperator::showview(QSqlQuery *query, QTableView *view, QStandardItemModel **model,int rowcount)
{
    if((*model) != NULL){
        delete (*model);
        (*model) = NULL;
    }
    if(query->lastError().isValid()){
        return -1;
    }

    int fieldcount = query->record().count();//返回SQL语句执行后有多少列
    (*model) = new QStandardItemModel(rowcount, fieldcount);//根据SQL语句返回的行列总数，动态的建一个model出来.
    //设置列名
    QSqlRecord record = query->record();
    for(int i = 0;i<fieldcount;i++){
        (*model)->setHeaderData(i, Qt::Horizontal, record.fieldName(i));
    }

    int i = 0;
    while (query->next()) {
        for(int j = 0;j<fieldcount;j++){//循环遍历一行当中所有的列
            (*model)->setData((*model)->index(i, j, QModelIndex()), query->value(j));
        }
        i++;
    }

    view->setModel((*model));
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置表格不可编辑
    view->setSortingEnabled(true);
    view->sortByColumn(10,Qt::AscendingOrder);

    query->clear();//释放内存空间
    return 0;
}
