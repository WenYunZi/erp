#include "thread_jizujiekou.h"

extern pubfunc pub;
extern QString PRODUCTUNITNO;
extern QString UNITTYPE;

thread_jizujiekou::thread_jizujiekou(QObject *parent) :
    QThread(parent)
{
    PlantName = pub.readPlantName();
    jizuNo = QString("%1#机组").arg(PRODUCTUNITNO);

    if(UNITTYPE == "XinXing"){
        XinXingDB = QSqlDatabase::addDatabase("QODBC","XinXingDB");
        XinXingDB.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=D://HKW8//tpdata//histdatanew_tbl.mdb;UID='';PWD=cdz110119");

        //打开机组数据库
        if(!XinXingDB.open()){
            QString erro = XinXingDB.lastError().text()+QString("UNIT DATABASE date:")+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
            emit erroMessage(erro);
        }

        XinXingQuery = new QSqlQuery(XinXingDB);
    }
    else if(UNITTYPE == "FeiMi"){
        FeiMiDB = QSqlDatabase::addDatabase("QODBC","FeiMiDB");
        FeiMiDB.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=D://CAN_V6//FeiMi//Context//Crude//CV6Crude.mdb;UID='';PWD=20121120");

        //打开机组数据库
        if(!FeiMiDB.open()){
            QString erro = FeiMiDB.lastError().text()+QString("UNIT DATABASE date:")+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
            emit erroMessage(erro);
        }

        FeiMiQuery = new QSqlQuery(FeiMiDB);
    }
    else if(UNITTYPE == "SANY"){
        SANYDB = QSqlDatabase::addDatabase("QODBC","SANYDB");
        SANYDB.setDatabaseName("DRIVER={SQL SERVER};SERVER=localhost;DATABASE=jxc;UID=sa;PWD=sanyjbz");

        //打开机组数据库
        if(!SANYDB.open()){
            QString erro = SANYDB.lastError().text()+QString("UNIT DATABASE date:")+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
            emit erroMessage(erro);
        }

        SANYQuery = new QSqlQuery(SANYDB);
    }
    else if(UNITTYPE == "ZOOMLION"){
        ZOOMLIONDB = QSqlDatabase::addDatabase("QODBC","ZOOMLIONDB");
        ZOOMLIONDB.setDatabaseName("DRIVER={SQL SERVER};SERVER=localhost;DATABASE=ZL_NCMS;UID=pan;PWD=ZOOMLION");

        //打开机组数据库
        if(!ZOOMLIONDB.open()){
            QString erro = ZOOMLIONDB.lastError().text()+QString("UNIT DATABASE date:")+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
            emit erroMessage(erro);
        }

        ZOOMLIONQuery = new QSqlQuery(ZOOMLIONDB);
        ZOOMLIONItemQuery = new QSqlQuery(ZOOMLIONDB);
        ZOOMLIONCountQuery = new QSqlQuery(ZOOMLIONDB);
    }
    else if(UNITTYPE == "BS"){
        BSDB = QSqlDatabase::addDatabase("QODBC","BSDBconsume");
        BSDB.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=D://BS23//BS23DB.mdb;UID='';PWD=");

        //打开机组数据库
        if(!BSDB.open()){
            QString erro = BSDB.lastError().text()+QString("UNIT DATABASE date:")+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
            emit erroMessage(erro);
        }

        BSQuery = new QSqlQuery(BSDB);
        BSItemQuery = new QSqlQuery(BSDB);
    }

    //连接MySQL数据库
    int res = db.sql_connect(pub.read_hostip().toStdString().data(),"dbuser1","dbuser1","akzf_db");
    if(res == -1){
        QString erro = db.geterror()+QString("mysql date:")+QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        writeErroLog(erro);
        emit erroMessage(erro);
    }
}

thread_jizujiekou::~thread_jizujiekou()
{
    this->wait();
    db.sql_disconnet();

    if(UNITTYPE == "XinXing"){
        XinXingDB.close();
        delete XinXingQuery;
    }
    else if(UNITTYPE == "FeiMi"){
        FeiMiDB.close();
        delete FeiMiQuery;
    }
    else if(UNITTYPE == "SANY"){
        SANYDB.close();
        delete SANYQuery;
    }
    else if(UNITTYPE == "ZOOMLION"){
        ZOOMLIONDB.close();
        delete ZOOMLIONQuery;
        delete ZOOMLIONItemQuery;
        delete ZOOMLIONCountQuery;
    }
    else if(UNITTYPE == "BS"){
        BSDB.close();
        delete BSQuery;
    }
}

void thread_jizujiekou::run()
{
    while(threadIsRun){
        //消耗

        if(UNITTYPE == "XinXing"){
            XinXingsyncXiaohao();
        }
        else if(UNITTYPE == "FeiMi"){
            FeiMisyncXiaohao();
        }
        else if(UNITTYPE == "SANY"){
            SANYsyncXiaohao();
        }
        else if(UNITTYPE == "ZOOMLION"){
            ZOOMLIONsyncXiaohao();
        }
        else if(UNITTYPE == "BS"){
            BSsyncXiaohao();
        }

        for(int i = 0; i<1000; i++){
            if(threadIsRun){
                Sleep(30);
            }else{
                return;
            }
        }
    }
}

void thread_jizujiekou::XinXingsyncXiaohao()
{
    whetherTransfer = false;//是否转移

    //获取当前起始记录号
    QString StartTime = pub.read_HISTDATA_ID(jizuNo);
    if(StartTime.isEmpty()){
        emit erroMessage(QString("获取起始记录号错误"));
        return;
    }

    //获取记录条数
    QString sizeSQL = QString("SELECT COUNT(*) FROM HISTDATA WHERE CURDATE>#%1#").arg(StartTime);
    XinXingQuery->exec(sizeSQL);
    XinXingQuery->next();
    double total = XinXingQuery->value(0).toInt();//总记录条数
    if(total>=100){
        total = 100;
    }
    double count = 0;//当前记录条数
    XinXingQuery->clear();
    //获取记录合集
    QString selectSQL = QString("SELECT top 100 * FROM HISTDATA WHERE CURDATE>#%1# ORDER BY CURDATE").arg(StartTime);
    XinXingQuery->exec(selectSQL);
    //查询出错则退出
    if(XinXingQuery->lastError().isValid()){
        QString erro = selectSQL+"\n"+XinXingQuery->lastError().text()+"\n"+QString("获取记录集合错误");
        emit erroMessage(erro);
        return;
    }

    /********************************************插入操作*********************************************************/

    while (XinXingQuery->next() && threadIsRun) {
        whetherTransfer = true;
        //插入HSITDATA表
        insertHISTDATA.clear();
        insertHISTDATA = QString("REPLACE INTO HISTDATA (CURDATE,PFNAME,SUMWGT,JBSJ,SUMPS,SERVER,USERNAME,USERCHE,JIAOZHUBW,\
                                 TALADU,GCNAME,QDUDJ,PhbNumber,CheTime,CheNumber,bsqk,gcdz,id,unit,PlantName) values ('%1',\
                                 '%2','%3','%4','%5','%6','%7','%8','%9','%10','%11','%12','%13','%14','%15','%16','%17',\
                                 %18,'%19','%20');")
                .arg(XinXingQuery->value("CURDATE").toString().replace(QString("T"),QString(" ")),XinXingQuery->value("PFNAME").toString(),XinXingQuery->value("SUMWGT").toString(),XinXingQuery->value("JBSJ").toString(),
                     XinXingQuery->value("SUMPS").toString(),XinXingQuery->value("SERVER").toString(),XinXingQuery->value("USERNAME").toString(),XinXingQuery->value("USERCHE").toString(),XinXingQuery->value("JIAOZUBW").toString())
                .arg(XinXingQuery->value("TALADU").toString(),XinXingQuery->value("GCNAME").toString(),XinXingQuery->value("QDUDJ").toString(),XinXingQuery->value("PhbNumber").toString(),XinXingQuery->value("CheTime").toString().replace(QString("T"),QString(" ")),
                       XinXingQuery->value("CheNumber").toString(),XinXingQuery->value("bsqk").toString(),XinXingQuery->value("gcdz").toString(),XinXingQuery->value("id").toString())
                .arg(jizuNo,PlantName);
        int res = db.sql_exec(insertHISTDATA.toStdString().data());
        if(res == -1){//如果出错，则发出错误信号并且提交事务，退出线程
            QString erro = insertHISTDATA+"\n"+db.geterror()+QString("\n错误ID：%1 ").arg(XinXingQuery->value("id").toString().toInt())+"\n"+QString("上传HISTDATA表错误");
            writeErroLog(erro);
            emit erroMessage(erro);
            return;
        }

        //校验插入到HISTDATA表中的内容是否正确
        //获取mysql中的记录内容
        QString searchErroHISTDATASQL = QString("select CURDATE,PFNAME,SUMWGT,JBSJ,SUMPS,SERVER,USERNAME,USERCHE,JIAOZHUBW,TALADU,GCNAME,QDUDJ,phbNumber,CheTime,CheNumber,bsqk,gcdz,\
                        id,unit,PlantName,autoID from HISTDATA WHERE CURDATE='%1' and unit='%2'").arg(XinXingQuery->value("CURDATE").toString().replace(QString("T"),QString(" ")),jizuNo);
        QStringList resList = db.CreatStrList(searchErroHISTDATASQL);
        //如果没有获取记录
        if(resList.isEmpty()){
            QString deleteSQL = QString("delete from HISTDATA where unit=''");
            db.sql_exec(deleteSQL.toStdString().data());
            return;
        }
        //mysql记录
        QString mysqlStr;
        for(int i = 0; i<resList.count()-1; i++){
            mysqlStr = mysqlStr.append(resList.at(i));
        }
        //access记录
        QString accessStr;
        accessStr = accessStr.append(XinXingQuery->value("CURDATE").toString().replace(QString("T"),QString(" "))).append(XinXingQuery->value("PFNAME").toString()).append(XinXingQuery->value("SUMWGT").toString()).append(XinXingQuery->value("JBSJ").toString())
                             .append(XinXingQuery->value("SUMPS").toString()).append(XinXingQuery->value("SERVER").toString()).append(XinXingQuery->value("USERNAME").toString()).append(XinXingQuery->value("USERCHE").toString())
                             .append(XinXingQuery->value("JIAOZUBW").toString()).append(XinXingQuery->value("TALADU").toString()).append(XinXingQuery->value("GCNAME").toString()).append(XinXingQuery->value("QDUDJ").toString())
                             .append(XinXingQuery->value("PhbNumber").toString()).append(XinXingQuery->value("CheTime").toString().replace(QString("T"),QString(" "))).append(XinXingQuery->value("CheNumber").toString()).append(XinXingQuery->value("bsqk").toString())
                             .append(XinXingQuery->value("gcdz").toString()).append(XinXingQuery->value("id").toString()).append(jizuNo).append(PlantName);
        //判断获取到的mysql记录是否与access中的数据一致
        if(mysqlStr != accessStr){
            QString deleteSQL = QString("delete from HISTDATA where autoID=%1").arg(resList.at(20));
            db.sql_exec(deleteSQL.toStdString().data());
            return;
        }

        //插入HSITDATA表2
        int field = 0;//对应字段
        insertHISTDATA2.clear();
        insertHISTDATA2 = QString("REPLACE INTO HISTDATA2 (ID,YQMAT,SJMAT,MATNAME,CHETIME,CURDATA,JIZUNO,PLANTNAME,FILED,recordNo) ");
        for(int i = 26; i < 44; i++){
            field++;
            if(XinXingQuery->value(i).toString().toDouble() != 0){
                QString subStr = QString("(SELECT %1,'%2','%3',ERPmaterial,'%4','%5','%6','%7','%8','%9' FROM UnitMaterialCorrespondsToERPMaterial \
                                         WHERE ProductionUnit = '%6' AND CorrespondingField = '%8') UNION ")
                        .arg(XinXingQuery->value("id").toString(),XinXingQuery->value(i).toString(),XinXingQuery->value(i+18).toString(),
                             XinXingQuery->value("CheTime").toString().replace(QString("T"),QString(" ")),
                             XinXingQuery->value("CURDATE").toString().replace(QString("T"),QString(" ")),
                             jizuNo,PlantName).arg(field).arg(XinXingQuery->value("bsqk").toString());
                insertHISTDATA2 = insertHISTDATA2.append(subStr);
            }
        }
        insertHISTDATA2 = insertHISTDATA2.left(insertHISTDATA2.length()-7);
        res = db.sql_exec(insertHISTDATA2.toStdString().data());
        if(res == -1){//如果出错，则发出错误信号并且提交事务，退出线程
            QString erro = insertHISTDATA2+"\n"+db.geterror()+QString("\n错误ID：%1 ").arg(XinXingQuery->value("id").toString().toInt())+"\n"+QString("上传HISTDATA2表错误");
            writeErroLog(erro);
            emit erroMessage(erro);
            return;
        }

        //校验插入到HISTDATA2表中的内容是否正确
        //获取mysql中HISTDATA2表的记录内容
        QString searchErroHISTDATA2SQL = QString("select ID,YQMAT,SJMAT,FILED,CHETIME,CURDATA,JIZUNO,PLANTNAME,recordNo,autoID from HISTDATA2 WHERE ID='%1' and JIZUNO='%2'").arg(XinXingQuery->value("id").toString(),jizuNo);
        QList<QStringList> strList = db.sql_result(searchErroHISTDATA2SQL);
        //获取access中记录条数
        int MatCount = 0;
        for(int i = 26; i < 44; i++){
            if(XinXingQuery->value(i).toString().toDouble() != 0){
                MatCount++;
            }
        }

        //判断获取到的记录条数是否一致
        if(strList.count() != MatCount){
            QString deleteSQL = QString("delete from HISTDATA2 where JIZUNO=''");
            db.sql_exec(deleteSQL);
            return;
        }
        else{
            for(int i = 0; i<strList.count(); i++){
                //mysql记录
                QString mysqlStr;
                for(int j = 0; j<strList.at(i).count()-1; j++){
                    mysqlStr = mysqlStr.append(strList.at(i).at(j));
                }
                //access记录
                QString accessStr;
                accessStr = accessStr.append(XinXingQuery->value("id").toString()).append(XinXingQuery->value(strList.at(i).at(3).toInt()+25).toString())
                                     .append(XinXingQuery->value(strList.at(i).at(3).toInt()+43).toString()).append(strList.at(i).at(3)).append(XinXingQuery->value("CheTime").toString().replace(QString("T"),QString(" ")))
                                     .append(XinXingQuery->value("CURDATE").toString().replace(QString("T"),QString(" "))).append(jizuNo).append(PlantName).append(XinXingQuery->value("bsqk").toString());
                if(mysqlStr != accessStr){
                    return;
                }
            }
        }

        count++;
        emit updateProcess((int)count/total*100);
        ID = XinXingQuery->value("CURDATE").toString().replace(QString("T"),QString(" "));
    }

    /********************************************插入操作END*********************************************************/

    //发送刷新信号、保存ID号
    if(whetherTransfer == true){
        pub.save_HISTDATA_ID(jizuNo,ID);
        whetherTransfer = false;
        emit updateProcess(0);
    }
}

void thread_jizujiekou::FeiMisyncXiaohao()
{
    whetherTransfer = false;//是否转移

    //获取当前起始记录号
    QString StartTime = pub.read_HISTDATA_ID(jizuNo);
    if(StartTime.isEmpty()){
        emit erroMessage(QString("获取起始记录号错误"));
        return;
    }

    //获取记录条数
    QString sizeSQL = QString("SELECT COUNT(*) FROM CrudeTable WHERE t_DateTime>=#%1# and i_State=101").arg(StartTime);
    FeiMiQuery->exec(sizeSQL);
    FeiMiQuery->next();
    double total = FeiMiQuery->value(0).toInt();//总记录条数
    if(total>=100){
        total = 100;
    }
    double count = 0;//当前记录条数
    FeiMiQuery->clear();
    //获取记录合集
    QString selectSQL = QString("SELECT top 100 * FROM CrudeTable WHERE t_DateTime>=#%1# and i_State=101 ORDER BY t_DateTime").arg(StartTime);
    FeiMiQuery->exec(selectSQL);
    //查询出错则退出
    if(FeiMiQuery->lastError().isValid()){
        QString erro = selectSQL+"\n"+FeiMiQuery->lastError().text()+"\n"+QString("获取记录集合错误");
        emit erroMessage(erro);
        return;
    }

    /********************************************插入操作*********************************************************/

    while (FeiMiQuery->next() && threadIsRun) {
        whetherTransfer = true;
        //插入HSITDATA表
        insertHISTDATA.clear();
        insertHISTDATA = QString("REPLACE INTO HISTDATA (CURDATE,PFNAME,SUMWGT,JBSJ,SUMPS,SERVER,USERNAME,USERCHE,JIAOZHUBW,\
                                 TALADU,GCNAME,QDUDJ,PhbNumber,CheTime,CheNumber,bsqk,gcdz,id,unit,PlantName) values ('%1',\
                                 '%2','%3','%4','%5','%6','%7','%8','%9','%10','%11','%12','%13','%14','%15','%16','%17',\
                                 '%18','%19','%20');")
                .arg(FeiMiQuery->value("t_DateTime").toString().replace(QString("T"),QString(" ")),FeiMiQuery->value("c_FormulaUniqueMark").toString(),"0",FeiMiQuery->value("d_MixingTime").toString(),
                     FeiMiQuery->value("d_ThisCubics").toString(),"0",FeiMiQuery->value("c_ClientName").toString(),FeiMiQuery->value("c_VehicleUniqueMark").toString(),FeiMiQuery->value("c_ProjectPart").toString())
                .arg(FeiMiQuery->value("c_Slump").toString(),FeiMiQuery->value("c_ProjectName").toString(),FeiMiQuery->value("c_Strength").toString(),FeiMiQuery->value("c_BigTaskUniqueMark").toString(),"0",
                     FeiMiQuery->value("c_VehicleUniqueMark").toString(),FeiMiQuery->value("c_SmallTaskUniqueMark").toString(),"",FeiMiQuery->value("ID").toString())
                .arg(jizuNo,PlantName);
        int res = db.sql_exec(insertHISTDATA);
        if(res == -1){//如果出错，则发出错误信号并且提交事务，退出线程
            QString erro = insertHISTDATA+"\n"+db.geterror()+QString("\n错误ID：%1 ").arg(FeiMiQuery->value("ID").toString())+"\n"+QString("上传HISTDATA表错误");
            emit erroMessage(erro);
            return;
        }

        //校验插入到HISTDATA表中的内容是否正确
        //获取mysql中的记录内容
        QString searchErroHISTDATASQL = QString("select CURDATE,PFNAME,SUMWGT,JBSJ,SUMPS,SERVER,USERNAME,USERCHE,JIAOZHUBW,TALADU,GCNAME,QDUDJ,phbNumber,CheTime,\
                                                CheNumber,bsqk,gcdz,id,unit,PlantName,autoID from HISTDATA WHERE id='%1' and unit='%2'").arg(FeiMiQuery->value("ID").toString(),jizuNo);
        QStringList resList = db.CreatStrList(searchErroHISTDATASQL);
        //如果没有获取记录
        if(resList.isEmpty()){
            QString deleteSQL = QString("delete from HISTDATA where unit=''");
            db.sql_exec(deleteSQL);
            return;
        }
        //mysql记录
        QString mysqlStr;
        for(int i = 0; i<resList.count()-1; i++){
            mysqlStr = mysqlStr.append(resList.at(i));
        }
        //access记录
        QString accessStr;
        accessStr = accessStr.append(FeiMiQuery->value("t_DateTime").toString().replace(QString("T"),QString(" "))).append(FeiMiQuery->value("c_FormulaUniqueMark").toString()).append("0").append(FeiMiQuery->value("d_MixingTime").toString())
                             .append(FeiMiQuery->value("d_ThisCubics").toString()).append("0").append(FeiMiQuery->value("c_ClientName").toString()).append(FeiMiQuery->value("c_VehicleUniqueMark").toString())
                             .append(FeiMiQuery->value("c_ProjectPart").toString()).append(FeiMiQuery->value("c_Slump").toString()).append(FeiMiQuery->value("c_ProjectName").toString()).append(FeiMiQuery->value("c_Strength").toString())
                             .append(FeiMiQuery->value("c_BigTaskUniqueMark").toString()).append("0").append(FeiMiQuery->value("c_VehicleUniqueMark").toString()).append(FeiMiQuery->value("c_SmallTaskUniqueMark").toString())
                             .append("").append(FeiMiQuery->value("ID").toString()).append(jizuNo).append(PlantName);
        //判断获取到的mysql记录是否与access中的数据一致
        if(mysqlStr != accessStr){
            QString deleteSQL = QString("delete from HISTDATA where autoID=%1").arg(resList.at(20));
            db.sql_exec(deleteSQL);
            return;
        }

        //插入HSITDATA表2
        int field = 0;//对应字段
        insertHISTDATA2.clear();
        insertHISTDATA2 = QString("REPLACE INTO HISTDATA2 (ID,YQMAT,SJMAT,MATNAME,CHETIME,CURDATA,JIZUNO,PLANTNAME,FILED,recordNo) ");
        for(int i = 24; i < 48; i++){
            field++;
            if(FeiMiQuery->value(i).toString().toDouble() != 0){
                QString subStr = QString("(SELECT '%1','%2','%3',ERPmaterial,'%4','%5','%6','%7','%8','%9' FROM UnitMaterialCorrespondsToERPMaterial \
                                         WHERE ProductionUnit = '%6' AND CorrespondingField = '%8') UNION ")
                        .arg(FeiMiQuery->value("ID").toString(),FeiMiQuery->value(i).toString(),FeiMiQuery->value(i+24).toString(),"0",
                             FeiMiQuery->value("t_DateTime").toString().replace(QString("T"),QString(" ")),
                             jizuNo,PlantName).arg(field).arg(FeiMiQuery->value("c_SmallTaskUniqueMark").toString());
                insertHISTDATA2 = insertHISTDATA2.append(subStr);
            }
        }
        insertHISTDATA2 = insertHISTDATA2.left(insertHISTDATA2.length()-7);
        res = db.sql_exec(insertHISTDATA2.toStdString().data());
        if(res == -1){//如果出错，则发出错误信号并且提交事务，退出线程
            QString erro = insertHISTDATA2+"\n"+db.geterror()+QString("\n错误ID：%1 ").arg(FeiMiQuery->value("ID").toString())+"\n"+QString("上传HISTDATA2表错误");
            writeErroLog(erro);
            emit erroMessage(erro);
            return;
        }

        //校验插入到HISTDATA2表中的内容是否正确
        //获取mysql中HISTDATA2表的记录内容
        QString searchErroHISTDATA2SQL = QString("select ID,YQMAT,SJMAT,FILED,CHETIME,CURDATA,JIZUNO,PLANTNAME,recordNo,autoID from HISTDATA2 WHERE ID='%1' and JIZUNO='%2'").arg(FeiMiQuery->value("ID").toString(),jizuNo);
        QList<QStringList> strList = db.sql_result(searchErroHISTDATA2SQL);
        //获取access中记录条数
        int MatCount = 0;
        for(int i = 24; i < 48; i++){
            if(FeiMiQuery->value(i).toString().toDouble() != 0){
                MatCount++;
            }
        }

        //判断获取到的记录条数是否一致
        if(strList.count() != MatCount){
            QString deleteSQL = QString("delete from HISTDATA2 where JIZUNO=''");
            db.sql_exec(deleteSQL.toStdString().data());
            return;
        }
        else{
            for(int i = 0; i<strList.count(); i++){
                //mysql记录
                QString mysqlStr;
                for(int j = 0; j<strList.at(i).count()-1; j++){
                    mysqlStr = mysqlStr.append(strList.at(i).at(j));
                }
                //access记录
                QString accessStr;
                accessStr = accessStr.append(FeiMiQuery->value("ID").toString()).append(FeiMiQuery->value(strList.at(i).at(3).toInt()+23).toString())
                                     .append(FeiMiQuery->value(strList.at(i).at(3).toInt()+47).toString()).append(strList.at(i).at(3)).append("0")
                                     .append(FeiMiQuery->value("t_DateTime").toString().replace(QString("T"),QString(" "))).append(jizuNo).append(PlantName).append(FeiMiQuery->value("c_SmallTaskUniqueMark").toString());
                if(mysqlStr != accessStr){
                    return;
                }
            }
        }

        count++;
        emit updateProcess((int)count/total*100);
        ID = FeiMiQuery->value("t_DateTime").toString().replace(QString("T"),QString(" "));
    }

    /********************************************插入操作END*********************************************************/

    //发送刷新信号、保存ID号
    if(whetherTransfer == true){
        pub.save_HISTDATA_ID(jizuNo,ID);
        whetherTransfer = false;
        emit updateProcess(0);
    }
}

void thread_jizujiekou::SANYsyncXiaohao()
{
    whetherTransfer = false;

    //获取当前起始记录号
    QString StartTime = pub.read_HISTDATA_ID(jizuNo);
    if(StartTime.isEmpty()){
        emit erroMessage(QString("获取起始记录号错误"));
        return;
    }

    //获取记录条数
    QString sizeSQL = QString("SELECT COUNT(*) FROM manufacture WHERE mDateTime>'%1'").arg(StartTime);
    SANYQuery->exec(sizeSQL);
    //查询出错则退出
    if(SANYQuery->lastError().isValid()){
        QString erro = sizeSQL+"\n"+SANYQuery->lastError().text()+"\n"+QString("获取记录条数错误");
        emit erroMessage(erro);
        return;
    }
    SANYQuery->next();
    double total = SANYQuery->value(0).toInt();//总记录条数
    if(total>=100){
        total = 100;
    }
    double count = 0;//当前记录条数
    SANYQuery->clear();

    //获取记录合集
    QString selectSQL = QString("SELECT TOP 100 * FROM manufacture a LEFT OUTER JOIN (SELECT * FROM OutMaster) b ON a.DeliveryID = b.DeliveryID WHERE (a.mDateTime>'%1') ORDER BY a.mDateTime").arg(StartTime);
    SANYQuery->exec(selectSQL);
    //查询出错则退出
    if(SANYQuery->lastError().isValid()){
        QString erro = selectSQL+"\n"+SANYQuery->lastError().text()+"\n"+QString("获取记录集合错误");
        emit erroMessage(erro);
        return;
    }

    /********************************************插入操作*********************************************************/

    while (SANYQuery->next() && threadIsRun) {
        //计算每盘重量
        double SUMWGT = 0;
        for(int i = 7; i < 43; i+=2){
            SUMWGT += SANYQuery->value(i).toDouble();
        }

        whetherTransfer = true;
        //插入HSITDATA表
        insertHISTDATA.clear();
        insertHISTDATA = QString("REPLACE INTO HISTDATA (CURDATE,PFNAME,JBSJ,SUMPS,SERVER,USERNAME,USERCHE,JIAOZHUBW,TALADU,GCNAME,QDUDJ,PhbNumber,CheTime,CheNumber,bsqk,id,unit,\
                                 PlantName,SUMWGT) values ('%1','%2',0,'%5','%6','%7','%8','%9','%10','%11','%12','%13','%14','%15','%16',0,'%19','%20','%21');")
                .arg(SANYQuery->value("mDateTime").toString().replace(QString("T"),QString(" ")),SANYQuery->value("RecipeNo").toString(),SANYQuery->value("ItemNO").toString(),
                     SANYQuery->value("FName").toString(),SANYQuery->value("ProjectCmpy").toString(),SANYQuery->value("reserve2").toString(),SANYQuery->value("ProjectPart").toString(),SANYQuery->value("tld").toString())
                .arg(SANYQuery->value("ProjectName").toString(),SANYQuery->value("intensityLevel").toString(),SANYQuery->value("RecipeNo").toString(),SANYQuery->value("DeliveryDate").toString().replace(QString("T"),QString(" ")),SANYQuery->value("TruckID").toString(),
                     SANYQuery->value("WorkMethod").toString(),jizuNo,PlantName)
                .arg(QString::number(SUMWGT));
        int res = db.sql_exec(insertHISTDATA);
        if(res == -1){//如果出错，则发出错误信号并且提交事务，退出线程
            QString erro = insertHISTDATA+"\n"+db.geterror()+QString("\n错误ID：%1 ").arg(SANYQuery->value(0).toString())+"\n"+QString("上传HISTDATA表错误");
            emit erroMessage(erro);
            return;
        }

        //插入HSITDATA表2
        int field = 0;//对应字段
        insertHISTDATA2.clear();
        insertHISTDATA2 = QString("REPLACE INTO HISTDATA2 (ID,YQMAT,SJMAT,MATNAME,CHETIME,CURDATA,JIZUNO,PLANTNAME,FILED,recordNo) ");
        for(int i = 7; i < 43; i+=2){
            field++;
            if(SANYQuery->value(i).toString().toDouble() != 0){
                QString subStr = QString("(SELECT %1,'%2','%3',ERPmaterial,'%4','%5','%6','%7','%8','%9' FROM UnitMaterialCorrespondsToERPMaterial \
                                         WHERE ProductionUnit = '%6' AND CorrespondingField = '%8') UNION ")
                        .arg("0",SANYQuery->value(i).toString(),SANYQuery->value(i+1).toString(),SANYQuery->value("DeliveryDate").toString().replace(QString("T"),QString(" ")),
                             SANYQuery->value("mDateTime").toString().replace(QString("T"),QString(" ")),jizuNo,PlantName).arg(field).arg(SANYQuery->value("WorkMethod").toString());
                insertHISTDATA2 = insertHISTDATA2.append(subStr);
            }
        }
        insertHISTDATA2 = insertHISTDATA2.left(insertHISTDATA2.length()-7);
        res = db.sql_exec(insertHISTDATA2);
        if(res == -1){//如果出错，则发出错误信号并且提交事务，退出线程
            QString erro = insertHISTDATA2+"\n"+db.geterror()+QString("\n错误ID：%1 ").arg(SANYQuery->value(0).toString())+"\n"+QString("上传HISTDATA2表错误");
            emit erroMessage(erro);
            return;
        }

//        //校验插入到HISTDATA2表中的内容是否正确
//        //获取mysql中HISTDATA2表记录条数
//        QString searchErroHISTDATA2SQL = QString("select 1 from HISTDATA2 WHERE CURDATA='%1' and JIZUNO='%2'").arg(SANYQuery->value(0).toString(),jizuNo);
//        int HISTDATA2_count = db.row_count(searchErroHISTDATA2SQL);

//        //获取access中记录条数
//        int MatCount = 0;
//        for(int i = 7; i < 43; i+=2){
//            if(SANYQuery->value(i).toString().toDouble() != 0){
//                MatCount++;
//            }
//        }

//        //判断获取到的记录条数是否一致
//        if(HISTDATA2_count != MatCount){
//            QString deleteSQL = QString("delete from HISTDATA2 where JIZUNO=''");
//            db.sql_exec(deleteSQL);
//            QString erro = QString("\n错误ID：%1 ").arg(SANYQuery->value(0).toString())+"mysql:"+QString::number(HISTDATA2_count)+" "+"unit:"+QString::number(MatCount)+"\n"+QString("上传HISTDATA2表记录数量错误");
//            emit erroMessage(erro);
//            return;
//        }

        count++;
        emit updateProcess((int)count/total*100);
        ID = SANYQuery->value("mDateTime").toString().replace(QString("T"),QString(" "));
    }

    /********************************************插入操作END*********************************************************/


    //发送刷新信号、保存ID号
    if(whetherTransfer == true){
        pub.save_HISTDATA_ID(jizuNo,ID);
        whetherTransfer = false;
        emit updateProcess(0);
    }
}

void thread_jizujiekou::ZOOMLIONsyncXiaohao()
{
    whetherTransfer = false;

    //获取当前起始记录号
    QString StartTime = pub.read_HISTDATA_ID(jizuNo);
    if(StartTime.isEmpty()){
        emit erroMessage(QString("获取起始记录号错误"));
        return;
    }

    //获取记录条数
    QString sizeSQL = QString("SELECT * FROM HistoryTray a LEFT OUTER JOIN (SELECT ID FROM History) b ON (a.HID = b.ID) WHERE a.CreateTime>'%1' order by a.CreateTime").arg(StartTime);
    ZOOMLIONQuery->exec(sizeSQL);
    //查询出错则退出
    if(ZOOMLIONQuery->lastError().isValid()){
        QString erro = sizeSQL+"\n"+ZOOMLIONQuery->lastError().text()+"\n"+QString("获取记录条数错误");
        emit erroMessage(erro);
        return;
    }

    double total = 0;//总记录条数
    while(ZOOMLIONQuery->next()){
        total++;
        if(total == 100){
            break;
        }
    }
    double count = 0;//当前记录条数
    ZOOMLIONQuery->clear();

    //获取记录合集
    QString selectSQL = QString("SELECT TOP 100 * FROM HistoryTray a LEFT OUTER JOIN (SELECT * FROM History) b ON a.HID = b.ID LEFT OUTER JOIN \
                                (SELECT CreateTime AS CheTime, HID, TrayNum FROM HistoryTray) C ON C.HID = a.HID AND C.TrayNum = 1 WHERE (a.CreateTime > '%1') \
                                ORDER BY a.CreateTime").arg(StartTime);
    ZOOMLIONQuery->exec(selectSQL);
    //查询出错则退出
    if(ZOOMLIONQuery->lastError().isValid()){
        QString erro = selectSQL+"\n"+ZOOMLIONQuery->lastError().text()+"\n"+QString("获取记录集合错误");
        emit erroMessage(erro);
        return;
    }

    /********************************************插入操作*********************************************************/

    while (ZOOMLIONQuery->next() && threadIsRun) {

        whetherTransfer = true;
        //插入HSITDATA表
        insertHISTDATA.clear();
        insertHISTDATA = QString("REPLACE INTO HISTDATA (CURDATE,PFNAME,JBSJ,SUMPS,SERVER,USERNAME,USERCHE,JIAOZHUBW,TALADU,GCNAME,QDUDJ,PhbNumber,CheTime,CheNumber,bsqk,id,unit,\
                                 PlantName,SUMWGT) values ('%1','%2','%4','%5','%6','%7','%8','%9','%10','%11','%12','%13','%14','%15','%16','%18','%19','%20','%21')")
                .arg(ZOOMLIONQuery->value("CreateTime").toString().replace(QString("T"),QString(" ")),ZOOMLIONQuery->value("ConFormulaName").toString(),ZOOMLIONQuery->value("MixingTime").toString(),ZOOMLIONQuery->value("Volume").toString(),
                     ZOOMLIONQuery->value("SysOperator").toString(),ZOOMLIONQuery->value("CustomerName").toString(),ZOOMLIONQuery->value("Driver").toString(),ZOOMLIONQuery->value("ConstructPlace").toString(),ZOOMLIONQuery->value("Sink").toString())
                .arg(ZOOMLIONQuery->value("ProjectName").toString(),ZOOMLIONQuery->value("ConcreteStrength").toString(),ZOOMLIONQuery->value("ConFormulaName").toString(),ZOOMLIONQuery->value("CheTime").toString().replace(QString("T"),QString(" ")),ZOOMLIONQuery->value("CarID").toString(),
                     ZOOMLIONQuery->value("ProductRegNo").toString(),ZOOMLIONQuery->value("HID").toString(),jizuNo,PlantName)
                .arg(QString::number(0));
        int res = db.sql_exec(insertHISTDATA);
        if(res == -1){//如果出错，则发出错误信号并且提交事务，退出线程
            QString erro = insertHISTDATA+"\n"+db.geterror()+QString("\n错误ID：%1 ").arg(ZOOMLIONQuery->value("HID").toString())+"\n"+QString("上传HISTDATA表错误");
            emit erroMessage(erro);
            return;
        }

        //插入HSITDATA表2
        QString searchItemConsume = QString("SELECT * FROM HistoryItems WHERE (HTID = '%1')").arg(ZOOMLIONQuery->value("ID").toString());
        ZOOMLIONItemQuery->exec(searchItemConsume);
        //qDebug()<<searchItemConsume;
        //查询出错则退出
        if(ZOOMLIONItemQuery->lastError().isValid()){
            QString erro = selectSQL+"\n"+ZOOMLIONItemQuery->lastError().text()+"\n"+QString("获取记录Item集合错误");
            emit erroMessage(erro);
            return;
        }


        insertHISTDATA2.clear();
        insertHISTDATA2 = QString("REPLACE INTO HISTDATA2 (ID,YQMAT,SJMAT,MATNAME,CHETIME,CURDATA,JIZUNO,PLANTNAME,FILED,recordNo) ");
        while(ZOOMLIONItemQuery->next()){
            QString subStr = QString("(SELECT '%1','%2','%3',ERPmaterial,'%4','%5','%6','%7','%8','%9' FROM UnitMaterialCorrespondsToERPMaterial \
                                     WHERE ProductionUnit = '%6' AND CorrespondingField = '%8') UNION ")
                    .arg(ZOOMLIONQuery->value("HID").toString(),ZOOMLIONItemQuery->value("TargetNum").toString(),ZOOMLIONItemQuery->value("StuffUsedNum").toString(),ZOOMLIONQuery->value("CheTime").toString().replace(QString("T"),QString(" ")),
                         ZOOMLIONQuery->value("CreateTime").toString().replace(QString("T"),QString(" ")),jizuNo,PlantName).arg(ZOOMLIONItemQuery->value("StuffID").toString().toInt()).arg(ZOOMLIONQuery->value("ProductRegNo").toString());
            insertHISTDATA2 = insertHISTDATA2.append(subStr);
        }
        insertHISTDATA2 = insertHISTDATA2.left(insertHISTDATA2.length()-7);
        res = db.sql_exec(insertHISTDATA2);
        if(res == -1){//如果出错，则发出错误信号并且提交事务，退出线程
            QString erro = insertHISTDATA2+"\n"+db.geterror()+QString("\n错误ID：%1 ").arg(ZOOMLIONQuery->value("CreateTime").toString().replace(QString("T"),QString(" ")))+"\n"+QString("上传HISTDATA2表错误");
            emit erroMessage(erro);
            return;
        }

        count++;

        qDebug()<<"total"<<total<<"count"<<count;
        emit updateProcess((int)count/total*100);
        ID = ZOOMLIONQuery->value("CreateTime").toString().replace(QString("T"),QString(" "));
    }

    /********************************************插入操作END*********************************************************/


    //发送刷新信号、保存ID号
    if(whetherTransfer == true){
        pub.save_HISTDATA_ID(jizuNo,ID);
        whetherTransfer = false;
        emit updateProcess(0);
    }
}

void thread_jizujiekou::BSsyncXiaohao()
{
    whetherTransfer = false;

    //获取当前起始记录号
    QString StartTime = pub.read_HISTDATA_ID(jizuNo);
    if(StartTime.isEmpty()){
        emit erroMessage(QString("获取起始记录号错误"));
        return;
    }

    //获取记录条数
    QString sizeSQL = QString("SELECT * FROM Piece WHERE DatTim>#%1# order by DatTim").arg(StartTime);
    BSQuery->exec(sizeSQL);
    //查询出错则退出
    if(BSQuery->lastError().isValid()){
        emit erroMessage(sizeSQL+"\n"+BSQuery->lastError().text()+"\n"+QString("获取记录条数错误"));
        return;
    }
    double total = 0;//总记录条数
    while(BSQuery->next()){
        total++;
        if(total == 100){
            break;
        }
    }
    double count = 0;//当前记录条数
    BSQuery->clear();

    //获取记录合集
    QString selectSQL = QString("SELECT TOP 100 *,a.ID AS AID,B.DatTim AS BDATTIM,A.DatTim AS ADATTIM FROM Piece A LEFT JOIN (SELECT * FROM Product) B ON (A.Product = B.ID) where A.DatTim>#%1#").arg(StartTime);
    BSQuery->exec(selectSQL);
    //查询出错则退出
    if(BSQuery->lastError().isValid()){
        QString erro = selectSQL+"\n"+BSQuery->lastError().text()+"\n"+QString("获取记录集合错误");
        emit erroMessage(erro);
        return;
    }

    /********************************************插入操作*********************************************************/

    while (BSQuery->next() && threadIsRun) {

        whetherTransfer = true;
        //插入HSITDATA表
        insertHISTDATA.clear();
        insertHISTDATA = QString("REPLACE INTO HISTDATA (CURDATE,PFNAME,JBSJ,SUMPS,SERVER,USERNAME,USERCHE,JIAOZHUBW,TALADU,GCNAME,QDUDJ,PhbNumber,CheTime,CheNumber,bsqk,id,unit,\
                                 PlantName,SUMWGT) values ('%1','%2','%4','%5','%6','%7','%8','%9','%10','%11','%12','%13','%14','%15','%16','%18','%19','%20','%21')")
                .arg(BSQuery->value("ADATTIM").toString().replace(QString("T"),QString(" ")),BSQuery->value("Recipe").toString(),"0",BSQuery->value("PieAmnt").toString(),
                     BSQuery->value("Operator").toString(),BSQuery->value("Customer").toString(),BSQuery->value("Driver").toString(),BSQuery->value("ConsPos").toString(),BSQuery->value("Lands").toString())
                .arg(BSQuery->value("ProjName").toString(),BSQuery->value("BetLev").toString(),BSQuery->value("Recipe").toString(),BSQuery->value("BDATTIM").toString().replace(QString("T"),QString(" ")),BSQuery->value("Vehicle").toString(),
                     BSQuery->value("Pour").toString(),BSQuery->value("AID").toString(),jizuNo,PlantName)
                .arg(QString::number(0));
        int res = db.sql_exec(insertHISTDATA);
        if(res == -1){//如果出错，则发出错误信号并且提交事务，退出线程
            QString erro = insertHISTDATA+"\n"+db.geterror()+QString("\n错误ID：%1 ").arg(BSQuery->value("ADATTIM").toString())+"\n"+QString("上传HISTDATA表错误");
            emit erroMessage(erro);
            return;
        }


        //插入HSITDATA表2
        QString searchItemConsume = QString("SELECT * FROM Dosage WHERE (Piece = %1)").arg(BSQuery->value("AID").toString());
        BSItemQuery->exec(searchItemConsume);
        //qDebug()<<searchItemConsume;
        //查询出错则退出
        if(BSItemQuery->lastError().isValid()){
            QString erro = selectSQL+"\n"+BSItemQuery->lastError().text()+"\n"+QString("获取记录Item集合错误");
            emit erroMessage(erro);
            return;
        }


        insertHISTDATA2.clear();
        insertHISTDATA2 = QString("REPLACE INTO HISTDATA2 (ID,YQMAT,SJMAT,MATNAME,CHETIME,CURDATA,JIZUNO,PLANTNAME,FILED,recordNo) VALUES ");
        int filedID = 0;
        while(BSItemQuery->next()){
            filedID++;
            QString subStr = QString("('%1','%2','%3','%4','%5','%6','%7','%8','%9','%10'),")
                    .arg(BSItemQuery->value("Piece").toString(),BSItemQuery->value("PlanAmnt").toString(),BSItemQuery->value("FactAmnt").toString(),BSItemQuery->value("Material").toString(),BSQuery->value("BDATTIM").toString().replace(QString("T"),QString(" ")),
                         BSQuery->value("ADATTIM").toString().replace(QString("T"),QString(" ")),jizuNo,PlantName).arg(filedID).arg(BSQuery->value("ErpID").toString());
            insertHISTDATA2 = insertHISTDATA2.append(subStr);
        }
        insertHISTDATA2 = insertHISTDATA2.left(insertHISTDATA2.length()-1);
        res = db.sql_exec(insertHISTDATA2);
        if(res == -1){//如果出错，则发出错误信号并且提交事务，退出线程
            QString erro = insertHISTDATA2+"\n"+db.geterror()+QString("\n错误ID：%1 ").arg(BSQuery->value("ADATTIM").toString().replace(QString("T"),QString(" ")))+"\n"+QString("上传HISTDATA2表错误");
            emit erroMessage(erro);
            return;
        }

        count++;

        qDebug()<<"total"<<total<<"count"<<count;
        emit updateProcess((int)count/total*100);
        ID = BSQuery->value("ADATTIM").toString().replace(QString("T"),QString(" "));
    }

    /********************************************插入操作END*********************************************************/


    //发送刷新信号、保存ID号
    if(whetherTransfer == true){
        pub.save_HISTDATA_ID(jizuNo,ID);
        whetherTransfer = false;
        emit updateProcess(0);
    }
}

void thread_jizujiekou::writeErroLog(QString erro)
{
    QString sFileName = "UnitAPIErro.log";

    QFile file(sFileName);
    if (file.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        file.write(erro.toUtf8());
        file.close();
    }

    return;
}

void thread_jizujiekou::setThreadIsRun(bool whetherRun)
{
    threadIsRun = whetherRun;
}
