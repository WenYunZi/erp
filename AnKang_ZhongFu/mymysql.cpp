#include "mymysql.h"

extern pubfunc pub;

//所有有关mysql API函数调用，都是在mymysql这个类里面实现的

mymysql::mymysql(QObject *parent) :
    QObject(parent)
{
    mysql_init(&mysql);
    connection = NULL;
    memset(buf, 0, sizeof(buf));
    //默认为本地服务器登录
    whetherRemoteServer = false;
}

int mymysql::sql_connect(QString Hostname, const char *User, const char *Password, const char *DBName)
{
    int timeout = 30;
    mysql_options(&mysql,MYSQL_OPT_CONNECT_TIMEOUT,(const char *)&timeout);
    mysql_options(&mysql,MYSQL_OPT_READ_TIMEOUT,(const char *)&timeout);
    mysql_options(&mysql,MYSQL_OPT_WRITE_TIMEOUT,(const char *)&timeout);
    connection = mysql_real_connect(&mysql, Hostname.toStdString().data(), User, Password, DBName, 0, 0,0);
    if (connection == NULL){
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"sql_connect"<<geterror();
        return -1;
    }else{
        mysql_query(connection, "set names utf8");
        return 0;
    }
}

int mymysql::sql_reconnect()
{
    sql_disconnet();
    int res = 0;

    for(int i = 0; i<5; i++){
        mymysql();
        res = sql_connect(pub.read_hostip().toStdString().data(),"dbuser1","dbuser1","akzf_db");
        if(res == 0){
            break;
        }
    }
    if(res != 0){
        emit errorMsg(geterror());
        return res;
    }
    return res;
}



const char *mymysql::geterror()
{
    return buf;
}

void mymysql::sql_disconnet()
{
    if (connection){
        mysql_close(connection);
        connection = NULL;
    }
}

int mymysql::sql_affect_rows()
{
    if(!connection){
        return -1;
    }
    return mysql_affected_rows(connection);
}



int mymysql::sql_exec(QString SQL)
{
    if(!connection){
        return -1;
    }
    if (mysql_query(connection, SQL.toStdString().data()) != 0){
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"sql_exec"<<geterror()<<SQL<<endl;

        int ret = mysql_ping(&mysql);
        if(ret != 0){
            if(sql_reconnect() != 0){
                return -1;
            }
            mysql_query(connection, SQL.toStdString().data());
        }else{
            return -1;
        }

    }
    return 0;
}

QString mymysql::sql_fetchrow_plus(QString SQL,int filednum)
{
    if(!connection){
        return "erro";
    }
    if (mysql_query(connection, SQL.toStdString().data()) != 0){
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"sql_fetchrow_plus"<<geterror();

        int ret = mysql_ping(&mysql);
        if(ret != 0){
            if(sql_reconnect() != 0){
                return "erro1";
            }
            mysql_query(connection, SQL.toStdString().data());
        }else{
            return "erro1";
        }
    }
    MYSQL_RES *result = mysql_store_result(connection);
    if (result == NULL){//没有查询结果
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"sql_fetchrow_plus"<<geterror();
        return "erro2";
    }
    int rowcount = mysql_affected_rows(connection);//返回SQL语句执行后有多少行
    if(rowcount == 0){
        return "";
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    QString values = row[filednum];
    mysql_free_result(result);//释放通过mysql_store_result函数分配的内存空间
    return values;
}

int mymysql::sql_fillComboBoxItem(QString SQL, QComboBox *comboBox)
{
    if(!connection){
        return -1;
    }
    if (mysql_query(connection, SQL.toStdString().data()) != 0){
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"sql_fillComboBoxItem"<<geterror();
        int ret = mysql_ping(&mysql);
        if(ret != 0){
            if(sql_reconnect() != 0){
                return -1;
            }
            mysql_query(connection, SQL.toStdString().data());
        }else{
            return -1;
        }
    }
    MYSQL_RES *result = mysql_store_result(connection);
    if (result == NULL){//没有查询结果
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"sql_fillComboBoxItem"<<geterror();
        return -1;
    }
    comboBox->setView(new QListView());
    comboBox->addItem("");
    int rowcount = mysql_affected_rows(connection);//返回SQL语句执行后有多少行
    if(rowcount == 0){
        return -3;
    }
    for(int i = 0;i < rowcount;i++){
        MYSQL_ROW row = mysql_fetch_row(result);
        comboBox->addItem(row[0]);
        qDebug()<<row[0];
    }
    mysql_free_result(result);//释放通过mysql_store_result函数分配的内存空间
    return 0;
}

int mymysql::sql_fillComboBoxItem2(QString SQL, QComboBox *comboBox)
{
    if(!connection){
        return -1;
    }
    if (mysql_query(connection, SQL.toStdString().data()) != 0){
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"sql_fillComboBoxItem2"<<geterror();
        int ret = mysql_ping(&mysql);
        if(ret != 0){
            if(sql_reconnect() != 0){
                return -1;
            }
            mysql_query(connection, SQL.toStdString().data());
        }else{
            return -1;
        }
    }
    MYSQL_RES *result = mysql_store_result(connection);
    if (result == NULL){//没有查询结果
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"sql_fillComboBoxItem2"<<geterror();
        return -1;
    }
    comboBox->setView(new QListView());
    comboBox->addItem("");
    int fieldcount = mysql_field_count(connection);//返回SQL语句执行后有多少列
    MYSQL_ROW row = mysql_fetch_row(result);
    if(row == 0){
        return -3;
    }
    for(int i = 1; i < fieldcount; i++){
        if(!QString(row[i]).isEmpty()){
            comboBox->addItem(row[i]);
        }
    }
    mysql_free_result(result);//释放通过mysql_store_result函数分配的内存空间
    return 0;
}

int mymysql::sql_fillComboBoxItem3(QString SQL, QComboBox *comboBox)
{
    if(!connection){
        return -1;
    }
    if (mysql_query(connection, SQL.toStdString().data()) != 0){
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"sql_fillComboBoxItem3"<<geterror();
        int ret = mysql_ping(&mysql);
        if(ret != 0){
            if(sql_reconnect() != 0){
                return -1;
            }
            mysql_query(connection, SQL.toStdString().data());
        }else{
            return -1;
        }
    }
    MYSQL_RES *result = mysql_store_result(connection);
    if (result == NULL){//没有查询结果
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"sql_fillComboBoxItem3"<<geterror();
        return -1;
    }
    comboBox->setView(new QListView());
    comboBox->addItem("");
    int rowcount = mysql_affected_rows(connection);//返回SQL语句执行后有多少行
    if(rowcount == 0){
        return -3;
    }
    for(int i = 0;i < rowcount;i++){
        MYSQL_ROW row = mysql_fetch_row(result);
        QString str = row[0];
        str = str.section("顶",0,0);
        if(comboBox->findText(str) == -1){
            comboBox->addItem(str);
        }
    }
    mysql_free_result(result);//释放通过mysql_store_result函数分配的内存空间
    return 0;
}

int mymysql::sql_fillQStringList(QString SQL, QStringList *stringList)
{
    if(!connection){
        return -1;
    }
    if (mysql_query(connection, SQL.toStdString().data()) != 0){
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"sql_fillQStringList"<<geterror();
        int ret = mysql_ping(&mysql);
        if(ret != 0){
            if(sql_reconnect() != 0){
                return -1;
            }
            mysql_query(connection, SQL.toStdString().data());
        }else{
            return -1;
        }
    }
    MYSQL_RES *result = mysql_store_result(connection);
    if (result == NULL){//没有查询结果
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"sql_fillQStringList"<<geterror();
        return -1;
    }
    int rowcount = mysql_affected_rows(connection);//返回SQL语句执行后有多少行
    for(int i = 0; i < rowcount; i++){//循环遍历每一行
        MYSQL_ROW row = mysql_fetch_row(result);
        (*stringList) << QString(row[0]);
    }
    mysql_free_result(result);//释放通过mysql_store_result函数分配的内存空间
    return 0;
}

int mymysql::sql_fillTableWidgetItem(QString SQL, QTableWidget *view)
{
    if(!connection){
        return -1;
    }
    if (mysql_query(connection, SQL.toStdString().data()) != 0){
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"sql_fillTableWidgetItem"<<geterror();
        int ret = mysql_ping(&mysql);
        if(ret != 0){
            if(sql_reconnect() != 0){
                return -1;
            }
            mysql_query(connection, SQL.toStdString().data());
        }else{
            return -1;
        }
    }
    MYSQL_RES *result = mysql_store_result(connection);
    if (result == NULL){//没有查询结果
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"sql_fillTableWidgetItem"<<geterror();
        return -1;
    }
    int rowcount = mysql_affected_rows(connection);//返回SQL语句执行后有多少行
    int fieldcount = mysql_field_count(connection);//返回SQL语句执行后有多少列
    view->setRowCount(rowcount);
    for(int i = 0;i<rowcount;i++){//循环遍历每一行
        MYSQL_ROW row = mysql_fetch_row(result);
        for(int j = 0;j<fieldcount;j++){//循环遍历一行当中所有的列
            if(j == 2){
                QString searchSQL = QString("select Freight from ConcreteCarFreightSet where cast(MinimumMileage as SIGNED INTEGER)<='%1' and cast(MaximumMileage as SIGNED INTEGER)>='%1';").arg(QString(row[1]));
                view->setItem(i,2,new QTableWidgetItem(sql_fetchrow_plus(searchSQL.toStdString().data(),0)));
                continue;
            }
            view->setItem(i,j,new QTableWidgetItem(row[j]));
        }
    }
    mysql_free_result(result);//释放通过mysql_store_result函数分配的内存空间
    return 0;
}



int mymysql::sql_whetherExisting(QString SQL)//查询是否有对应的数据
{
    if(!connection){
        return -1;
    }
    if (mysql_query(connection, SQL.toStdString().data()) != 0){
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"sql_whetherExisting"<<geterror();
        int ret = mysql_ping(&mysql);
        if(ret != 0){
            if(sql_reconnect() != 0){
                return -1;
            }
            mysql_query(connection, SQL.toStdString().data());
        }else{
            return -1;
        }
    }
    MYSQL_RES *result = mysql_store_result(connection);
    if (result == NULL){//没有查询结果
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"sql_whetherExisting"<<geterror();
        return -2;
    }
    int rowcount = mysql_affected_rows(connection);//返回SQL语句执行后有多少行
    if(rowcount != 0){
        return 1;
    }
    if(rowcount == 0){
        return -3;
    }
    mysql_free_result(result);//释放通过mysql_store_result函数分配的内存空间
    return 0;
}

int mymysql::sql_whetherRepeat(QString SQL, QString str)//如果有重复返回-3，无重复返回0；
{
    if(!connection){
        return -1;
    }
    int res = 0;
    if (mysql_query(connection, SQL.toStdString().data()) != 0){
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"sql_whetherRepeat"<<geterror();
        int ret = mysql_ping(&mysql);
        if(ret != 0){
            if(sql_reconnect() != 0){
                return -1;
            }
            mysql_query(connection, SQL.toStdString().data());
        }else{
            return -1;
        }
    }
    MYSQL_RES *result = mysql_store_result(connection);
    if (result == NULL){//没有查询结果
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"sql_whetherRepeat"<<geterror();
        return -2;
    }
    int rowcount = mysql_affected_rows(connection);//返回SQL语句执行后有多少行
    for(int i = 0;i < rowcount;i++){
        MYSQL_ROW row = mysql_fetch_row(result);
        QString strfrom(row[0]);
        if(str == strfrom){
            res = -3;
            return res;
        }
    }
    mysql_free_result(result);//释放通过mysql_store_result函数分配的内存空间
    return res;
}

int mymysql::sql_fillTableWidget(QString SQL, QTableWidget *view, int startColum)
{
    if(!connection){
        return -1;
    }
    if (mysql_query(connection, SQL.toStdString().data()) != 0){
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"sql_fillTableWidget"<<endl<<SQL<<endl<<geterror();
        int ret = mysql_ping(&mysql);
        if(ret != 0){
            if(sql_reconnect() != 0){
                return -1;
            }
            mysql_query(connection, SQL.toStdString().data());
        }else{
            return -1;
        }
    }

    MYSQL_RES *result = mysql_store_result(connection);
    if (result == NULL){//没有查询结果
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"sql_fillTableWidget"<<geterror();
        return -1;
    }
    int rowcount = mysql_affected_rows(connection);//返回SQL语句执行后有多少行
    int fieldcount = mysql_field_count(connection);//返回SQL语句执行后有多少列
    //设置行数
    view->setRowCount(rowcount);
    for(int i = 0;i<rowcount;i++){//循环遍历每一行
        MYSQL_ROW row = mysql_fetch_row(result);
        for(int j = 0;j<fieldcount;j++){//循环遍历一行当中所有的列
            view->setItem(i,j+startColum,new QTableWidgetItem(row[j]));
        }
    }
    mysql_free_result(result);//释放通过mysql_store_result函数分配的内存空间
    return 0;
}

int mymysql::sql_fillTableWidget2(QString SQL, QTableWidget *view,int column)
{
    if(!connection){
        return -1;
    }
    if (mysql_query(connection, SQL.toStdString().data()) != 0){
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"sql_fillTableWidget2"<<endl<<SQL<<endl<<geterror();
        int ret = mysql_ping(&mysql);
        if(ret != 0){
            if(sql_reconnect() != 0){
                return -1;
            }
            mysql_query(connection, SQL.toStdString().data());
        }else{
            return -1;
        }
    }

    MYSQL_RES *result = mysql_store_result(connection);
    if (result == NULL){//没有查询结果
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"sql_fillTableWidget2"<<geterror();
        return -1;
    }

    int fieldcount = mysql_field_count(connection);//返回SQL语句执行后有多少列
    int rowcount = mysql_affected_rows(connection);//返回SQL语句执行后有多少行
    if(rowcount == 0){
        return -1;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    for(int i = 0;i<fieldcount;i++){//循环遍历一行当中所有的列
        view->setItem(i,column,new QTableWidgetItem(row[i]));
    }

    mysql_free_result(result);//释放通过mysql_store_result函数分配的内存空间
    return 0;
}

QList<QStringList> mymysql::sql_result(QString SQL)
{
    QStringList strList;
    QList<QStringList> list;
    if(!connection){
        return list;
    }

    if (mysql_query(connection, SQL.toStdString().data()) != 0){
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"sql_result"<<endl<<SQL<<endl<<geterror();
        int ret = mysql_ping(&mysql);
        if(ret != 0){
            if(sql_reconnect() != 0){
                return list;
            }
            mysql_query(connection, SQL.toStdString().data());
        }else{
            return list;
        }
    }

    MYSQL_RES *result = mysql_store_result(connection);
    if (result == NULL){//没有查询结果
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"sql_result"<<geterror();
        return list;
    }
    int rowcount = mysql_affected_rows(connection);//返回SQL语句执行后有多少行
    int fieldcount = mysql_field_count(connection);//返回SQL语句执行后有多少列

    for(int i = 0;i<rowcount;i++){//循环遍历每一行
        MYSQL_ROW row = mysql_fetch_row(result);
        strList.clear();
        for(int j = 0;j<fieldcount;j++){//循环遍历一行当中所有的列
            strList.append(row[j]);
        }
        list.append(strList);
    }
    mysql_free_result(result);//释放通过mysql_store_result函数分配的内存空间
    return list;
}



int mymysql::showview(QString SQL, QTableView *view,QStandardItemModel **model)
{
    if(!connection){
        return -1;
    }
    if((*model) != NULL){
        delete (*model);
        (*model) = NULL;
    }
    if (mysql_query(connection, SQL.toStdString().data()) != 0){
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"showview"<<endl<<SQL<<endl<<geterror();
        int ret = mysql_ping(&mysql);
        if(ret != 0){
            if(sql_reconnect() != 0){
                return -1;
            }
            mysql_query(connection, SQL.toStdString().data());
        }else{
            return -1;
        }
    }

    MYSQL_RES *result = mysql_store_result(connection);
    if (result == NULL){//没有查询结果
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"showview"<<geterror();
        return -1;
    }
    int rowcount = mysql_affected_rows(connection);//返回SQL语句执行后有多少行
    int fieldcount = mysql_field_count(connection);//返回SQL语句执行后有多少列
    (*model) = new QStandardItemModel(rowcount, fieldcount);//根据SQL语句返回的行列总数，动态的建一个model出来.
    MYSQL_FIELD *field;

    for(int i = 0;i<fieldcount;i++){
        field = mysql_fetch_field(result);
        (*model)->setHeaderData(i, Qt::Horizontal, field->name);
    }
    for(int i = 0;i<rowcount;i++){//循环遍历每一行
        MYSQL_ROW row = mysql_fetch_row(result);
        for(int j = 0;j<fieldcount;j++){//循环遍历一行当中所有的列
            (*model)->setData((*model)->index(i, j, QModelIndex()), row[j]);
        }
    }
    view->setModel((*model));
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置表格不可编辑
    view->setSortingEnabled(true);
    view->sortByColumn(0,Qt::AscendingOrder);

    mysql_free_result(result);//释放通过mysql_store_result函数分配的内存空间
    return 0;

}

int mymysql::showview_num(QString SQL, QTableView *view,QStandardItemModel **model,int column)
{
    if(!connection){
        return -1;
    }
    if((*model) != NULL){
        delete (*model);
        (*model) = NULL;
    }
    if (mysql_query(connection, SQL.toStdString().data()) != 0){
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"showview_num"<<SQL<<geterror();
        int ret = mysql_ping(&mysql);
        if(ret != 0){
            if(sql_reconnect() != 0){
                return -1;
            }
            mysql_query(connection, SQL.toStdString().data());
        }else{
            return -1;
        }
    }

    MYSQL_RES *result = mysql_store_result(connection);
    if (result == NULL){//没有查询结果
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"showview_num"<<SQL<<geterror();
        return -1;
    }
    int rowcount = mysql_affected_rows(connection);//返回SQL语句执行后有多少行
    int fieldcount = mysql_field_count(connection);//返回SQL语句执行后有多少列
    (*model) = new QStandardItemModel(rowcount, fieldcount);//根据SQL语句返回的行列总数，动态的建一个model出来.
    MYSQL_FIELD *field;
    for(int i = 0;i<fieldcount;i++){
        field = mysql_fetch_field(result);
        (*model)->setHeaderData(i, Qt::Horizontal, field->name);
    }
    int j = 0;
    for(int i = 0;i<rowcount;i++){//循环遍历每一行
        MYSQL_ROW row = mysql_fetch_row(result);
        for(j = 0;j<fieldcount;j++){//循环遍历一行当中所有的列
            if(j == column){
                (*model)->setData((*model)->index(i, j, QModelIndex()),QVariant(atoi(row[j])));
            }else{
                (*model)->setData((*model)->index(i, j, QModelIndex()), row[j]);
            }
        }
    }
    view->setModel((*model));
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置表格不可编辑
    view->setSortingEnabled(true);
    mysql_free_result(result);//释放通过mysql_store_result函数分配的内存空间
    return 0;
}

int mymysql::show_treeview(QString SQL, QTreeView *view, QStandardItemModel **model)
{
    if(!connection){
        return -1;
    }
    if((*model) != NULL){
        delete (*model);
        (*model) = NULL;
    }
    if (mysql_query(connection, SQL.toStdString().data()) != 0){
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"show_treeview"<<geterror();
        int ret = mysql_ping(&mysql);
        if(ret != 0){
            if(sql_reconnect() != 0){
                return -1;
            }
            mysql_query(connection, SQL.toStdString().data());
        }else{
            return -1;
        }
    }

    MYSQL_RES *result = mysql_store_result(connection);
    if (result == NULL){//没有查询结果
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"show_treeview"<<geterror();
        return -1;
    }
    int rowcount = mysql_affected_rows(connection);//返回SQL语句执行后有多少行
    int fieldcount = mysql_field_count(connection);//返回SQL语句执行后有多少列
    (*model) = new QStandardItemModel;//根据SQL语句返回的行列总数，动态的建一个model出来.
    for(int i = 0;i < rowcount;i++){//循环遍历每一行
        MYSQL_ROW row = mysql_fetch_row(result);
        QStandardItem *root_item = new QStandardItem(QIcon(":/image/dalei.png"),QString(row[0]));
        (*model)->appendRow(root_item);
        for(int j = 1;j<fieldcount;j++){//循环遍历一行当中所有的列
            if(!QString(row[j]).isEmpty()){
                QStandardItem *leaf_item = new QStandardItem(QIcon(":/image/yuandian.png"),QString(row[j]));
                root_item->appendRow(leaf_item);
            }
        }
    }
    view->setModel((*model));
    view->setHeaderHidden(true);
    view->expandAll();
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置表格不可编辑
    mysql_free_result(result);//释放通过mysql_store_result函数分配的内存空间
    return 0;
}

int mymysql::show_treeview2(QString SQL, QTreeView *view, QStandardItemModel **model)
{
    if(!connection){
        return -1;
    }
    if((*model) != NULL){
        delete (*model);
        (*model) = NULL;
    }
    if (mysql_query(connection, SQL.toStdString().data()) != 0){
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"show_treeview2"<<geterror();
        int ret = mysql_ping(&mysql);
        if(ret != 0){
            if(sql_reconnect() != 0){
                return -1;
            }
            mysql_query(connection, SQL.toStdString().data());
        }else{
            return -1;
        }
    }

    MYSQL_RES *result = mysql_store_result(connection);
    if (result == NULL){//没有查询结果
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"show_treeview2"<<geterror();
        return -1;
    }
    int rowcount = mysql_affected_rows(connection);//返回SQL语句执行后有多少行

    QMultiMap<QString,QStandardItem *> multiMap;
    QStringList mainStr;

    for(int i = 0;i < rowcount;i++){//循环遍历每一行
        MYSQL_ROW row = mysql_fetch_row(result);
        multiMap.insert(QString(row[0]),new QStandardItem(QIcon(":/image/yuandian.png"),QString(row[1])));
        if(!mainStr.contains(row[0])){
            mainStr.append(row[0]);
        }
    }

    (*model) = new QStandardItemModel;//根据SQL语句返回的行列总数，动态的建一个model出来.
    for(int i = 0; i<mainStr.count(); i++){
        QStandardItem *root_item = new QStandardItem(QIcon(":/image/dalei.png"),mainStr[i]);
        (*model)->appendRow(root_item);

        QList<QStandardItem*> ItemList = multiMap.values(mainStr[i]);
        for(int j = 0; j<ItemList.count(); j++){
            root_item->appendRow(ItemList[j]);
        }
    }
    view->setModel((*model));
    view->setHeaderHidden(true);
    view->expandAll();
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置表格不可编辑
    mysql_free_result(result);//释放通过mysql_store_result函数分配的内存空间
    return 0;
}

int mymysql::showview_caigoujiesuan(QString SQL, QTableView *view, QStandardItemModel **model)
{
    if(!connection){
        return -1;
    }
    if((*model) != NULL){
        delete (*model);
        (*model) = NULL;
    }
    if (mysql_query(connection, SQL.toStdString().data()) != 0){
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"showview_caigoujiesuan"<<geterror();
        int ret = mysql_ping(&mysql);
        if(ret != 0){
            if(sql_reconnect() != 0){
                return -1;
            }
            mysql_query(connection, SQL.toStdString().data());
        }else{
            return -1;
        }
    }
    MYSQL_RES *result = mysql_store_result(connection);
    if (result == NULL){//没有查询结果
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"showview_caigoujiesuan"<<geterror();
        return -1;
    }
    int rowcount = mysql_affected_rows(connection);//返回SQL语句执行后有多少行
    int fieldcount = mysql_field_count(connection);//返回SQL语句执行后有多少列
    (*model) = new QStandardItemModel(rowcount, fieldcount);//根据SQL语句返回的行列总数，动态的建一个model出来.
    MYSQL_FIELD *field;
    for(int i = 0;i<fieldcount;i++){
        field = mysql_fetch_field(result);
        (*model)->setHeaderData(i, Qt::Horizontal, field->name);
    }
    for(int i = 0;i<rowcount;i++){//循环遍历每一行
        MYSQL_ROW row = mysql_fetch_row(result);
        for(int j = 0;j<fieldcount;j++){//循环遍历一行当中所有的列
            if(j == 8){
                double total = 0;
                if(QString(row[7]) == "吨"){
                    total = QString(row[5]).toDouble()*QString(row[6]).toDouble()/1000;
                }else if(QString(row[7]) == "公斤"){
                    total = QString(row[5]).toDouble()*QString(row[6]).toDouble();
                }
                (*model)->setData((*model)->index(i, 8, QModelIndex()), QString::number(total,'f',2));
                continue;
            }
            (*model)->setData((*model)->index(i, j, QModelIndex()), row[j]);
        }
    }
    view->setModel((*model));
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置表格不可编辑
    view->setSortingEnabled(true);
    mysql_free_result(result);//释放通过mysql_store_result函数分配的内存空间
    return 0;
}

int mymysql::showview_xiaoshoujiesuan(QString SQL, QTableView *view, QStandardItemModel **model)
{
    if(!connection){
        return -1;
    }
    if((*model) != NULL){
        delete (*model);
        (*model) = NULL;
    }
    if (mysql_query(connection, SQL.toStdString().data()) != 0){
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"showview_xiaoshoujiesuan"<<geterror();
        int ret = mysql_ping(&mysql);
        if(ret != 0){
            if(sql_reconnect() != 0){
                return -1;
            }
            mysql_query(connection, SQL.toStdString().data());
        }else{
            return -1;
        }
    }
    MYSQL_RES *result = mysql_store_result(connection);
    if (result == NULL){//没有查询结果
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"showview_xiaoshoujiesuan"<<geterror();
        return -1;
    }
    int rowcount = mysql_affected_rows(connection);//返回SQL语句执行后有多少行
    int fieldcount = mysql_field_count(connection);//返回SQL语句执行后有多少列
    (*model) = new QStandardItemModel(rowcount, fieldcount);//根据SQL语句返回的行列总数，动态的建一个model出来.
    MYSQL_FIELD *field;
    for(int i = 0;i<fieldcount;i++){
        field = mysql_fetch_field(result);
        (*model)->setHeaderData(i, Qt::Horizontal, field->name);
    }
    for(int i = 0;i<rowcount;i++){//循环遍历每一行
        MYSQL_ROW row = mysql_fetch_row(result);
        for(int j = 0;j<fieldcount;j++){//循环遍历一行当中所有的列
            if(j == 5){
                double total = QString(row[3]).toDouble()*QString(row[4]).toDouble();
                (*model)->setData((*model)->index(i, 5, QModelIndex()), QString::number(total,'f',2));
                continue;
            }
            if(j == 9){
                double total = QString(row[7]).toDouble()*QString(row[8]).toDouble();
                (*model)->setData((*model)->index(i, 9, QModelIndex()), QString::number(total,'f',2));
                continue;
            }
            (*model)->setData((*model)->index(i, j, QModelIndex()), row[j]);
        }
    }
    view->setModel((*model));
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置表格不可编辑
    view->setSortingEnabled(true);
    mysql_free_result(result);//释放通过mysql_store_result函数分配的内存空间
    return 0;
}

int mymysql::showview_yunfeijiesuan(QString SQL, QTableView *view, QStandardItemModel **model)
{
    if(!connection){
        return -1;
    }
    if((*model) != NULL){
        delete (*model);
        (*model) = NULL;
    }
    if (mysql_query(connection, SQL.toStdString().data()) != 0){
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"showview_yunfeijiesuan"<<geterror();
        int ret = mysql_ping(&mysql);
        if(ret != 0){
            if(sql_reconnect() != 0){
                return -1;
            }
            mysql_query(connection, SQL.toStdString().data());
        }else{
            return -1;
        }
    }
    MYSQL_RES *result = mysql_store_result(connection);
    if (result == NULL){//没有查询结果
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"showview_yunfeijiesuan"<<geterror();
        return -1;
    }
    int rowcount = mysql_affected_rows(connection);//返回SQL语句执行后有多少行
    int fieldcount = mysql_field_count(connection);//返回SQL语句执行后有多少列
    (*model) = new QStandardItemModel(rowcount, fieldcount);//根据SQL语句返回的行列总数，动态的建一个model出来.
    MYSQL_FIELD *field;
    for(int i = 0;i<fieldcount;i++){
        field = mysql_fetch_field(result);
        (*model)->setHeaderData(i, Qt::Horizontal, field->name);
    }
    for(int i = 0;i<rowcount;i++){//循环遍历每一行
        MYSQL_ROW row = mysql_fetch_row(result);
        for(int j = 0;j<fieldcount;j++){//循环遍历一行当中所有的列
            if(j == 8){
                double total = QString(row[4]).toDouble()*QString(row[7]).toDouble();
                (*model)->setData((*model)->index(i, 8, QModelIndex()), QString::number(total,'f',2));
                continue;
            }
            (*model)->setData((*model)->index(i, j, QModelIndex()), row[j]);
        }
    }
    view->setModel((*model));
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置表格不可编辑
    view->setSortingEnabled(true);
    mysql_free_result(result);//释放通过mysql_store_result函数分配的内存空间
    return 0;
}

int mymysql::showview_yunfeitongji(QString SQL, QTableView *view, QStandardItemModel **model)
{
    if(!connection){
        return -1;
    }
    if((*model) != NULL){
        delete (*model);
        (*model) = NULL;
    }
    if (mysql_query(connection, SQL.toStdString().data()) != 0){
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"showview_yunfeitongji"<<geterror();
        int ret = mysql_ping(&mysql);
        if(ret != 0){
            if(sql_reconnect() != 0){
                return -1;
            }
            mysql_query(connection, SQL.toStdString().data());
        }else{
            return -1;
        }
    }
    MYSQL_RES *result = mysql_store_result(connection);
    if (result == NULL){//没有查询结果
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"showview_yunfeitongji"<<geterror();
        return -1;
    }
    int rowcount = mysql_affected_rows(connection);//返回SQL语句执行后有多少行
    int fieldcount = mysql_field_count(connection);//返回SQL语句执行后有多少列
    (*model) = new QStandardItemModel(rowcount, fieldcount);//根据SQL语句返回的行列总数，动态的建一个model出来.
    MYSQL_FIELD *field;
    for(int i = 0;i<fieldcount;i++){
        field = mysql_fetch_field(result);
        (*model)->setHeaderData(i, Qt::Horizontal, field->name);
    }
    for(int i = 0;i<rowcount;i++){//循环遍历每一行
        MYSQL_ROW row = mysql_fetch_row(result);
        for(int j = 0;j<fieldcount;j++){//循环遍历一行当中所有的列
            if(j == 6){
                double total = QString(row[2]).toDouble()*QString(row[3]).toDouble();
                (*model)->setData((*model)->index(i, 6, QModelIndex()), QString::number(total,'f',2));
                continue;
            }
            (*model)->setData((*model)->index(i, j, QModelIndex()), row[j]);
        }
    }
    view->setModel((*model));
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置表格不可编辑
    view->setSortingEnabled(true);
    mysql_free_result(result);//释放通过mysql_store_result函数分配的内存空间
    return 0;
}

int mymysql::showview_yuanliaorukushujutiaozheng(QString SQL, QTableView *view, QStandardItemModel **model)
{
    if(!connection){
        return -1;
    }
    if((*model) != NULL){
        delete (*model);
        (*model) = NULL;
    }
    if (mysql_query(connection, SQL.toStdString().data()) != 0){
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"showview_yuanliaorukushujutiaozheng"<<geterror();
        int ret = mysql_ping(&mysql);
        if(ret != 0){
            if(sql_reconnect() != 0){
                return -1;
            }
            mysql_query(connection, SQL.toStdString().data());
        }else{
            return -1;
        }
    }
    MYSQL_RES *result = mysql_store_result(connection);
    if (result == NULL){//没有查询结果
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"showview_yuanliaorukushujutiaozheng"<<geterror();
        return -1;
    }
    int rowcount = mysql_affected_rows(connection);//返回SQL语句执行后有多少行
    int fieldcount = mysql_field_count(connection);//返回SQL语句执行后有多少列
    (*model) = new QStandardItemModel(rowcount, fieldcount);//根据SQL语句返回的行列总数，动态的建一个model出来.
    MYSQL_FIELD *field;
    for(int i = 0;i<fieldcount;i++){
        field = mysql_fetch_field(result);
        (*model)->setHeaderData(i, Qt::Horizontal, field->name);
    }
    for(int i = 0;i<rowcount;i++){//循环遍历每一行
        MYSQL_ROW row = mysql_fetch_row(result);
        for(int j = 0;j<fieldcount;j++){//循环遍历一行当中所有的列
            if(j == 9){
                double total = QString(row[5]).toDouble()*QString(row[6]).toDouble()/1000;
                (*model)->setData((*model)->index(i, 9, QModelIndex()), QString::number(total,'f',2));
                continue;
            }
            (*model)->setData((*model)->index(i, j, QModelIndex()), row[j]);
        }
    }
    view->setModel((*model));
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置表格不可编辑
    view->setSortingEnabled(true);
    mysql_free_result(result);//释放通过mysql_store_result函数分配的内存空间
    return 0;
}

QStringList mymysql::find_factory_from_tasklist(QString SQL)
{
    QStringList list;
    if(!connection){
        return list;
    }
    if (mysql_query(connection, SQL.toStdString().data()) != 0){
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"find_factory_from_tasklist"<<geterror();
        int ret = mysql_ping(&mysql);
        if(ret != 0){
            if(sql_reconnect() != 0){
                return list;
            }
            mysql_query(connection, SQL.toStdString().data());
        }else{
            return list;
        }
    }
    MYSQL_RES *result = mysql_store_result(connection);
    if (result == NULL){//没有查询结果
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"find_factory_from_tasklist"<<geterror();
        return list;
    }
    int rowcount = mysql_affected_rows(connection);//返回SQL语句执行后有多少行
    for(int i = 0;i<rowcount;i++){//循环遍历每一行
        MYSQL_ROW row = mysql_fetch_row(result);
        list.append(row[0]);
    }
    mysql_free_result(result);//释放通过mysql_store_result函数分配的内存空间
    return list;
}

int mymysql::newCheckBox(QString SQL, QList<QCheckBox *> &checkBoxList, int *num, QWidget *parent)
{
    if(!connection){
        return -1;
    }
    if(!checkBoxList.isEmpty()){
        int num = checkBoxList.size();
        for(int i = 0; i<num; i++){
            delete checkBoxList[i];
        }
        checkBoxList.clear();
    }

    if (mysql_query(connection, SQL.toStdString().data()) != 0){
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"newCheckBox"<<geterror();
        int ret = mysql_ping(&mysql);
        if(ret != 0){
            if(sql_reconnect() != 0){
                return -1;
            }
            mysql_query(connection, SQL.toStdString().data());
        }else{
            return -1;
        }
    }

    MYSQL_RES *result = mysql_store_result(connection);
    if (result == NULL){//没有查询结果
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"newCheckBox"<<geterror();
        return -1;
    }
    int rowcount = mysql_affected_rows(connection);//返回SQL语句执行后有多少行
    *num = rowcount;
    QCheckBox *checkBox[rowcount - 1];
    for(int i = 0;i < rowcount;i++){
        checkBox[i] = new QCheckBox(parent);
        MYSQL_ROW row = mysql_fetch_row(result);
        checkBox[i]->setText(row[0]);
        checkBoxList<<checkBox[i];
    }
    mysql_free_result(result);//释放通过mysql_store_result函数分配的内存空间
    return 0;
}

int mymysql::newWareHouseWidget(QString SQL, QList<WarehouseWidget *> &wareHoseWidgetList, int *num,QWidget *parent)
{
    if(!connection){
        return -1;
    }
    if(!wareHoseWidgetList.isEmpty()){
        int num = wareHoseWidgetList.size();
        for(int i = 0; i<num; i++){
            delete wareHoseWidgetList[i];
        }
        wareHoseWidgetList.clear();
    }
    if (mysql_query(connection, SQL.toStdString().data()) != 0){
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"newWareHouseWidget"<<geterror();
        int ret = mysql_ping(&mysql);
        if(ret != 0){
            if(sql_reconnect() != 0){
                return -1;
            }
            mysql_query(connection, SQL.toStdString().data());
        }else{
            return -1;
        }
    }
    MYSQL_RES *result = mysql_store_result(connection);
    if (result == NULL){//没有查询结果
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"newWareHouseWidget"<<geterror();
        return -1;
    }
    int rowcount = mysql_affected_rows(connection);//返回SQL语句执行后有多少行
    *num = rowcount;
    WarehouseWidget *wareHouseWidget[rowcount - 1];
    for(int i = 0; i < rowcount; i++){
        wareHouseWidget[i] = new WarehouseWidget(parent);
        MYSQL_ROW row = mysql_fetch_row(result);
        wareHouseWidget[i]->setWarehouseProgre(QString(row[2]).toDouble()/QString(row[3]).toDouble()/10);
        wareHouseWidget[i]->setText(row[0],row[1],row[4]);
        wareHouseWidget[i]->setUnit(row[6]);
        wareHoseWidgetList<<wareHouseWidget[i];
    }
    mysql_free_result(result);//释放通过mysql_store_result函数分配的内存空间
    return 0;
}

int mymysql::newCheckBoxAndLineEdit(QString SQL, QList<QCheckBox *> &checkBoxList, QList<QLineEdit *> &lineEdiList, int *num, QWidget *parent)
{
    if(!connection){
        return -1;
    }
    if(!checkBoxList.isEmpty()){
        int num = checkBoxList.size();
        for(int i = 0; i<num; i++){
            delete checkBoxList[i];
        }
        checkBoxList.clear();
    }
    if(!lineEdiList.isEmpty()){
        int num = lineEdiList.size();
        for(int i = 0; i<num; i++){
            delete lineEdiList[i];
        }
        lineEdiList.clear();
    }
    if (mysql_query(connection, SQL.toStdString().data()) != 0){
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"newCheckBoxAndLineEdit"<<geterror();
        int ret = mysql_ping(&mysql);
        if(ret != 0){
            if(sql_reconnect() != 0){
                return -1;
            }
            mysql_query(connection, SQL.toStdString().data());
        }else{
            return -1;
        }
    }

    MYSQL_RES *result = mysql_store_result(connection);
    if (result == NULL){//没有查询结果
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"newCheckBoxAndLineEdit"<<geterror();
        return -1;
    }
    int rowcount = mysql_affected_rows(connection);//返回SQL语句执行后有多少行
    *num = rowcount;
    QCheckBox *checkBox[rowcount - 1];
    QLineEdit *lineEdit[rowcount - 1];
    for(int i = 0;i < rowcount;i++){
        checkBox[i] = new QCheckBox(parent);
        lineEdit[i] = new QLineEdit(parent);
        lineEdit[i]->setFixedWidth(35);
        MYSQL_ROW row = mysql_fetch_row(result);
        checkBox[i]->setText(row[0]);
        lineEdit[i]->setText(row[1]);
        checkBoxList<<checkBox[i];
        lineEdiList<<lineEdit[i];
    }
    mysql_free_result(result);//释放通过mysql_store_result函数分配的内存空间
    return 0;
}

int mymysql::newWidget(QString SQL, QList<QWidget *> &WidgetList, QStringList &strList,QStringList &matList, QList<QLineEdit *> &pfLineEditList, QWidget *parent)
{
    if(!connection){
        return -1;
    }
    if(!WidgetList.isEmpty()){
        int num = WidgetList.size();
        for(int i = 0; i<num; i++){
            delete WidgetList[i];
        }
        WidgetList.clear();
    }

    if(!pfLineEditList.isEmpty()){
        int num = pfLineEditList.size();
        for(int i = 0; i<num; i++){
            delete pfLineEditList[i];
        }
        pfLineEditList.clear();
    }

    if(!strList.isEmpty()){
        strList.clear();
    }

    if(!matList.isEmpty()){
        matList.clear();
    }

    if (mysql_query(connection, SQL.toStdString().data()) != 0){
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"newWidget"<<geterror();
        int ret = mysql_ping(&mysql);
        if(ret != 0){
            if(sql_reconnect() != 0){
                return -1;
            }
            mysql_query(connection, SQL.toStdString().data());
        }else{
            return -1;
        }
    }

    MYSQL_RES *result = mysql_store_result(connection);
    if (result == NULL){//没有查询结果
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"newWidget"<<geterror();
        return -1;
    }

    QRegExp rx("^[-+]?\\d+(\\.\\d+)?$");
    QRegExpValidator *pReg = new QRegExpValidator(rx, this);

    int rowcount = mysql_affected_rows(connection);//返回SQL语句执行后有多少行

    //添加控件头**********************************************/
    QLabel *PositionNameLabel  = new QLabel(tr("仓位名称"),parent);
    PositionNameLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *MatNameLabel  = new QLabel(tr("原料名称"),parent);
    MatNameLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *PhbDataLabel  = new QLabel(tr("配方值"),parent);
    PhbDataLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(PositionNameLabel,0);
    vlayout->addWidget(MatNameLabel,0);
    vlayout->addWidget(PhbDataLabel,1);

    QWidget *widgetHead = new QWidget(parent);
    widgetHead->setLayout(vlayout);
    WidgetList<<widgetHead;
    /*************************************************************/


    QWidget *widget[rowcount - 1];
    for(int i = 0;i < rowcount;i++){
        widget[i] = new QWidget(parent);
        MYSQL_ROW row = mysql_fetch_row(result);

        QLabel *PositionNameLabel  = new QLabel(row[0],parent);
        PositionNameLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        QLabel *MatNameLabel  = new QLabel(row[1],parent);
        MatNameLabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        QLineEdit *peifangzhilineEdit = new QLineEdit(parent);
        peifangzhilineEdit->setValidator(pReg);

        //Widget列表
        QVBoxLayout *vlayout = new QVBoxLayout;
        vlayout->addWidget(PositionNameLabel,0);
        vlayout->addWidget(MatNameLabel,0);
        vlayout->addWidget(peifangzhilineEdit,1);
        widget[i]->setLayout(vlayout);
        WidgetList<<widget[i];
        //pfLineEditList列表
        pfLineEditList<<peifangzhilineEdit;
        //QStringList列表
        strList<<row[2];
        matList<<row[0];
    }

    //添加控件尾**********************************************/
    QLabel *footerlabel1  = new QLabel(tr("容重"),parent);
    footerlabel1->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    QLineEdit *peifangRongZhonglineEdit = new QLineEdit(parent);
    peifangRongZhonglineEdit->setReadOnly(true);

    QVBoxLayout *vfooterlayout = new QVBoxLayout;
    vfooterlayout->addWidget(footerlabel1,0);
    vfooterlayout->addWidget(peifangRongZhonglineEdit,0);

    QWidget *widgetFooter = new QWidget(parent);
    widgetFooter->setLayout(vfooterlayout);
    WidgetList<<widgetFooter;
    //pfLineEditList列表
    pfLineEditList<<peifangRongZhonglineEdit;

    //砂率
    /****************************************************************/
    QLabel *footerlabel2  = new QLabel(tr("砂率"),parent);
    footerlabel2->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    QLineEdit *peifangShalvlineEdit = new QLineEdit(parent);
    peifangShalvlineEdit->setReadOnly(true);

    QVBoxLayout *vfooterlayout2 = new QVBoxLayout;
    vfooterlayout2->addWidget(footerlabel2,0);
    vfooterlayout2->addWidget(peifangShalvlineEdit,0);

    QWidget *widgetFooter2 = new QWidget(parent);
    widgetFooter2->setLayout(vfooterlayout2);
    WidgetList<<widgetFooter2;
    //pfLineEditList列表
    pfLineEditList<<peifangShalvlineEdit;
    /*************************************************************/

    //外加剂掺量
    /****************************************************************/
    QLabel *footerlabel3  = new QLabel(tr("外加剂掺量"),parent);
    footerlabel3->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    QLineEdit *waijiajichanlianglineEdit = new QLineEdit(parent);
    waijiajichanlianglineEdit->setReadOnly(true);

    QVBoxLayout *vfooterlayout3 = new QVBoxLayout;
    vfooterlayout3->addWidget(footerlabel3,0);
    vfooterlayout3->addWidget(waijiajichanlianglineEdit,0);

    QWidget *widgetFooter3 = new QWidget(parent);
    widgetFooter3->setLayout(vfooterlayout3);
    WidgetList<<widgetFooter3;
    //pfLineEditList列表
    pfLineEditList<<waijiajichanlianglineEdit;
    /*************************************************************/

    mysql_free_result(result);//释放通过mysql_store_result函数分配的内存空间
    return 0;
}


int mymysql::whether_caigoushenhequanxian(QString userName)
{
    if(!connection){
        return -1;
    }
    QString SQL = "SELECT CheckPerson from PurchaseContractCheckPerson;";
    if (mysql_query(connection, SQL.toStdString().data()) != 0){
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"whether_caigoushenhequanxian"<<geterror();
        int ret = mysql_ping(&mysql);
        if(ret != 0){
            if(sql_reconnect() != 0){
                return -1;
            }
            mysql_query(connection, SQL.toStdString().data());
        }else{
            return -1;
        }
    }

    MYSQL_RES *result = mysql_store_result(connection);
    if (result == NULL){//没有查询结果
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"whether_caigoushenhequanxian"<<geterror();
        return -1;
    }
    int rowcount = mysql_affected_rows(connection);//返回SQL语句执行后有多少行
    if(rowcount == 0){
        return -3;
    }
    for(int i = 0;i < rowcount;i++){
        MYSQL_ROW row = mysql_fetch_row(result);
        if(!strcmp(userName.toStdString().data(),row[0])){
            return 1;
        }
    }
    mysql_free_result(result);//释放通过mysql_store_result函数分配的内存空间
    return 0;
}

int mymysql::whether_xiaoshoushenhequanxian(QString userName)
{
    if(!connection){
        return -1;
    }
    QString SQL = "SELECT CheckPerson from SalesContractAuditor;";
    if (mysql_query(connection, SQL.toStdString().data()) != 0){
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"whether_xiaoshoushenhequanxian"<<geterror();
        int ret = mysql_ping(&mysql);
        if(ret != 0){
            if(sql_reconnect() != 0){
                return -1;
            }
            mysql_query(connection, SQL.toStdString().data());
        }else{
            return -1;
        }
    }

    MYSQL_RES *result = mysql_store_result(connection);
    if (result == NULL){//没有查询结果
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"whether_xiaoshoushenhequanxian"<<geterror();
        return -1;
    }
    int rowcount = mysql_affected_rows(connection);//返回SQL语句执行后有多少行
    if(rowcount == 0){
        return -3;
    }
    for(int i = 0;i < rowcount;i++)
    {
        MYSQL_ROW row = mysql_fetch_row(result);
        if(!strcmp(userName.toStdString().data(),row[0])){
            return 1;
        }
    }
    mysql_free_result(result);//释放通过mysql_store_result函数分配的内存空间
    return 0;
}

QString mymysql::caigouhetongshenheren()
{
    QString SQL = "SELECT CheckPerson from PurchaseContractCheckPerson;";
    QString person = " ";
    if(!connection){
        return person;
    }
    if (mysql_query(connection, SQL.toStdString().data()) != 0){
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"caigouhetongshenheren"<<geterror();
        int ret = mysql_ping(&mysql);
        if(ret != 0){
            if(sql_reconnect() != 0){
                return "";
            }
            mysql_query(connection, SQL.toStdString().data());
        }else{
            return "";
        }
    }
    MYSQL_RES *result = mysql_store_result(connection);
    if (result == NULL){//没有查询结果
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"caigouhetongshenheren"<<geterror();
        return "";
    }
    int rowcount = mysql_affected_rows(connection);//返回SQL语句执行后有多少行
    if(rowcount == 0){
        return "";
    }
    for(int i = 0;i < rowcount;i++){
        MYSQL_ROW row = mysql_fetch_row(result);
        person += row[0];
        person += " ";
    }
    mysql_free_result(result);//释放通过mysql_store_result函数分配的内存空间
    return person;
}

QString mymysql::xiaoshouhetongshenheren()
{
    QString SQL = "SELECT CheckPerson from SalesContractAuditor;";
    QString person = " ";

    if(!connection){
        return person;
    }
    if (mysql_query(connection, SQL.toStdString().data()) != 0){
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"xiaoshouhetongshenheren"<<geterror();
        int ret = mysql_ping(&mysql);
        if(ret != 0){
            if(sql_reconnect() != 0){
                return "";
            }
            mysql_query(connection, SQL.toStdString().data());
        }else{
            return "";
        }
    }
    MYSQL_RES *result = mysql_store_result(connection);
    if (result == NULL){//没有查询结果
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"xiaoshouhetongshenheren"<<geterror();
        return "";
    }
    int rowcount = mysql_affected_rows(connection);//返回SQL语句执行后有多少行
    if(rowcount == 0){
        return "";
    }
    for(int i = 0;i < rowcount;i++){
        MYSQL_ROW row = mysql_fetch_row(result);
        person += row[0];
        person += " ";
    }
    mysql_free_result(result);//释放通过mysql_store_result函数分配的内存空间
    return person;
}

int mymysql::row_count(QString SQL)
{
    if(!connection){
        return -1;
    }
    if (mysql_query(connection, SQL.toStdString().data()) != 0){
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"row_count"<<geterror();
        int ret = mysql_ping(&mysql);
        if(ret != 0){
            if(sql_reconnect() != 0){
                return -1;
            }
            mysql_query(connection, SQL.toStdString().data());
        }else{
            return -1;
        }
    }
    MYSQL_RES *result = mysql_store_result(connection);
    if (result == NULL){//没有查询结果
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"row_count"<<geterror();
        return -2;
    }
    int rowcount = mysql_affected_rows(connection);//返回SQL语句执行后有多少行
    mysql_free_result(result);//释放通过mysql_store_result函数分配的内存空间
    return rowcount;
}

QStringList mymysql::find_CheNo(QString SQL)
{
    QStringList strList;
    if(!connection){
        return strList;
    }
    if (mysql_query(connection, SQL.toStdString().data()) != 0){
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"find_CheNo"<<geterror();
        int ret = mysql_ping(&mysql);
        if(ret != 0){
            if(sql_reconnect() != 0){
                return strList;
            }
            mysql_query(connection, SQL.toStdString().data());
        }else{
            return strList;
        }
    }
    MYSQL_RES *result = mysql_store_result(connection);
    if (result == NULL){//没有查询结果
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"find_CheNo"<<geterror();
        return strList;
    }
    int rowcount = mysql_affected_rows(connection);//返回SQL语句执行后有多少行
    if(rowcount == 0){
        return strList;
    }
    int fieldcount = mysql_field_count(connection);//返回SQL语句执行后有多少列
    if(fieldcount == 0){
        return strList;
    }
    for(int i = 0;i < rowcount;i++){
        MYSQL_ROW row = mysql_fetch_row(result);
        strList.append(row[0]);
    }
    mysql_free_result(result);//释放通过mysql_store_result函数分配的内存空间
    return strList;
}

QStringList mymysql::CreatStrList(QString SQL)
{
    QStringList strList;
    if(!connection){
        return strList;
    }
    if (mysql_query(connection, SQL.toStdString().data()) != 0){
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"CreatStrList"<<geterror();
        int ret = mysql_ping(&mysql);
        if(ret != 0){
            if(sql_reconnect() != 0){
                return strList;
            }
            mysql_query(connection, SQL.toStdString().data());
        }else{
            return strList;
        }
    }
    MYSQL_RES *result = mysql_store_result(connection);
    if (result == NULL){//没有查询结果
        memset(buf, 0, sizeof(buf));
        strcpy(buf, mysql_error(&mysql));
        qDebug()<<"CreatStrList"<<geterror();
        return strList;
    }
    int fieldcount = mysql_field_count(connection);//返回SQL语句执行后有多少列
    if(fieldcount == 0){
        return strList;
    }
    int rowcount = mysql_affected_rows(connection);//返回SQL语句执行后有多少行
    if(rowcount == 0){
        return strList;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    for(int i = 0;i < fieldcount;i++){
        strList.append(row[i]);
    }
    mysql_free_result(result);//释放通过mysql_store_result函数分配的内存空间
    return strList;
}

void mymysql::setWhetherRemoteServer(bool trueOrFalse)
{
    this->whetherRemoteServer = trueOrFalse;
}
