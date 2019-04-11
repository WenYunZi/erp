#ifndef ODBCOPERATOR_H
#define ODBCOPERATOR_H

#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QSqlError>
#include <QTableView>
#include <QStandardItemModel>

class ODBCoperator
{
public:
    ODBCoperator();

public:
    int showview(QSqlQuery *query, QTableView *view, QStandardItemModel **model, int rowcount);

};

#endif // ODBCOPERATOR_H
