#include "thread_sync.h"

extern QString PRODUCTUNITNO;
extern pubfunc pub;
extern QString UNITTYPE;

thread_sync::thread_sync(QObject *parent) :
    QThread(parent)
{
    if(UNITTYPE == "XinXing"){
        XinXingDB = QSqlDatabase::addDatabase("QODBC","UPLOADPF_connect");
        XinXingDB.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=D://HKW8//tpdata//histdatanew_tbl.mdb;UID='';PWD=cdz110119");

        RunStateDB = QSqlDatabase::addDatabase("QODBC","RunStateDB");
        RunStateDB.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=D://HKW8//tpdata//xrunpart_tbl.mdb;UID='';PWD=cdz110119");

        //打开机组数据库
        if(!XinXingDB.open()){
            emit erroMessage(XinXingDB.lastError().text()+QString("XinXingDB"));
        }

        if(!RunStateDB.open()){
            emit erroMessage(RunStateDB.lastError().text()+QString("RunStateDB"));
        }

        XinXingQuery = new QSqlQuery(XinXingDB);
        RunStatequery = new QSqlQuery(RunStateDB);
    }
    else if(UNITTYPE == "FeiMi"){//胶州宏煦用的费米的
        FeiMiBigTaskDB = QSqlDatabase::addDatabase("QODBC","FeiMiBigTaskDB");
        FeiMiBigTaskDB.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=D://CAN_V6//FeiMi//Context//CV6BigTask.mdb;UID='';PWD=");

        FeiMiRecipeDB = QSqlDatabase::addDatabase("QODBC","FeiMiRecipeDB");
        FeiMiRecipeDB.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=D://CAN_V6//FeiMi//Context//CV6Recipe.mdb;UID='admin';PWD=20121120");

        FeiMiSmallTaskDB = QSqlDatabase::addDatabase("QODBC","FeiMiSmallTaskDB");
        FeiMiSmallTaskDB.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=D://CAN_V6//FeiMi//Context//CV6SmallTask.mdb;UID='';PWD=");

        //打开机组数据库
        if(!FeiMiBigTaskDB.open()){
            emit erroMessage(FeiMiBigTaskDB.lastError().text()+QString("FeiMiBigTaskDB"));
        }
        if(!FeiMiRecipeDB.open()){
            emit erroMessage(FeiMiRecipeDB.lastError().text()+QString("FeiMiRecipeDB"));
        }
        if(!FeiMiSmallTaskDB.open()){
            emit erroMessage(FeiMiSmallTaskDB.lastError().text()+QString("FeiMiSmallTaskDB"));
        }

        FMBigTaskQuery = new QSqlQuery(FeiMiBigTaskDB);
        FMRecipeQuery = new QSqlQuery(FeiMiRecipeDB);
        FMSmallTaskQuery = new QSqlQuery(FeiMiSmallTaskDB);
    }
    else if(UNITTYPE == "SANY"){
        SANYDB = QSqlDatabase::addDatabase("QODBC","UPLOADPF_connect");
        SANYDB.setDatabaseName("DRIVER={SQL SERVER};SERVER=localhost;DATABASE=jxc;UID=sa;PWD=sanyjbz");

        //打开机组数据库
        if(!SANYDB.open()){
            emit erroMessage(SANYDB.lastError().text()+QString("SQL SERVER"));
        }

        SANYQuery = new QSqlQuery(SANYDB);
    }
    else if(UNITTYPE == "ZOOMLION"){
        ZOOMLIONDB = QSqlDatabase::addDatabase("QODBC","UPLOADPF_connect");
        ZOOMLIONDB.setDatabaseName("DRIVER={SQL SERVER};SERVER=localhost;DATABASE=ZL_NCMS;UID=pan;PWD=ZOOMLION");

        //打开机组数据库
        if(!ZOOMLIONDB.open()){
            emit erroMessage(ZOOMLIONDB.lastError().text()+QString("SQL SERVER"));
        }

        ZOOMLIONQuery = new QSqlQuery(ZOOMLIONDB);

    }
    else if(UNITTYPE == "BS"){
        BSDB = QSqlDatabase::addDatabase("QODBC","UPLOADPF_connect");
        BSDB.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=D://BS23//BS23DB.mdb;UID='';PWD=");

        //打开机组数据库
        if(!BSDB.open()){
            emit erroMessage(BSDB.lastError().text()+QString("SQL SERVER"));
        }

        BSQuery = new QSqlQuery(BSDB);

    }

     else if(UNITTYPE == "YS"){
        YSDB = QSqlDatabase::addDatabase("QODBC","UPLOADPF_connect");
        YSDB.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS Access};DBQ=D://YS2012DB//YSDB.2.mdb;UID='';PWD=BCS7.2_SDBS");

        //打开机组数据库
        if(!YSDB.open()){
            emit erroMessage(YSDB.lastError().text()+QString("SQL SERVER"));
        }

        YSQuery = new QSqlQuery(YSDB);

    }




    //连接MySQL数据库
    int res = db.sql_connect(pub.read_hostip().toStdString().data(),"dbuser1","dbuser1","akzf_db");
    if(res == -1){
        emit erroMessage(db.geterror()+QString("mysql"));
    }

    ID = 0;
}

thread_sync::~thread_sync()
{
    this->wait();
    db.sql_disconnet();
    if(UNITTYPE == "XinXing"){
        XinXingDB.close();
        RunStateDB.close();
        delete XinXingQuery;
        delete RunStatequery;
    }
    else if(UNITTYPE == "FeiMi"){
        FeiMiBigTaskDB.close();
        FeiMiRecipeDB.close();
        FeiMiSmallTaskDB.close();
        delete FMBigTaskQuery;
        delete FMRecipeQuery;
        delete FMSmallTaskQuery;
    }
    else if(UNITTYPE == "SANY"){
        SANYDB.close();
        delete SANYQuery;
    }
    else if(UNITTYPE == "ZOOMLION"){
        ZOOMLIONDB.close();
        delete ZOOMLIONQuery;
    }
    else if(UNITTYPE == "BS"){
        BSDB.close();
        delete BSQuery;
    }
}

void thread_sync::run()
{
    while(threadIsRun){
        for(int i = 0; i<100; i++){
            if(threadIsRun){
                Sleep(50);
            }else{
                return;
            }
        }
        if(UNITTYPE == "XinXing"){
            //配比同步
            syncPhb(PRODUCTUNITNO);
            //配方库任务同步
            //syncPeiFangKuTask();
            //任务库任务同步
            syncRenWuKuTask();
            //同步单车任务
            syncDcRw();
            //删除单车任务
            deleteDcRw();
            //补方任务
            syncBuFangDcRw();
            //上传生产状态
            uploadRunState();
            //追加生产
            syncZhuiJiaDcRw();
        }
        else if(UNITTYPE == "FeiMi"){
            FMsyncPhb(PRODUCTUNITNO);
            FMsyncPeiFangKuTask();
            FMsyncDcRw();
            FMsyncBuFangDcRw();
        }
        else if(UNITTYPE == "SANY"){
            SANYsyncPhb(PRODUCTUNITNO);
            SANYsyncPeiFangKuTask();
            SANYsyncDcRw();
            SANYdeleteDcRw();
            SANYsyncBuFangDcRw();
            SANYRunState();
        }
        else if(UNITTYPE == "ZOOMLION"){
            ZLsyncStdPhb(PRODUCTUNITNO);
            ZLsyncRenWuKuTask();
            ZLsyncDcRw();
            ZLdeleteDcRw();
            ZLsyncBuFangDcRw();
            ZLRunState();
        }
        else if(UNITTYPE == "BS"){
            BSsyncPhb();
            BSsyncRenWuKuTask();
            BSsyncDcRw();
            BSdeleteDcRw();
        }
    }
}

void thread_sync::syncPhb(QString unitNo)
{
    QString searchPhbReact = QString("select RecipeID,RecipeName,Mat1,Mat2,Mat3,Mat4,Mat5,Mat6,Mat7,Mat8,Mat9,Mat10,Mat11,Mat12,Mat13,Mat14,Mat15,Mat16,Mat17,Mat18,\
                                      intensityLevel,state,jbTime,wushui from PhbReact where unit='%1'").arg(unitNo);
    QList<QStringList> list = db.sql_result(searchPhbReact.toStdString().data());
    for(int i = 0;i<list.size();i++){
        QString RecipeID = list.at(i).at(0);
        QString RecipeName = list.at(i).at(1);
        QString Mat1 = list.at(i).at(2);
        QString Mat2 = list.at(i).at(3);
        QString Mat3 = list.at(i).at(4);
        QString Mat4 = list.at(i).at(5);
        QString Mat5 = list.at(i).at(6);
        QString Mat6 = list.at(i).at(7);
        QString Mat7 = list.at(i).at(8);
        QString Mat8 = list.at(i).at(9);
        QString Mat9 = list.at(i).at(10);
        QString Mat10 = list.at(i).at(11);
        QString Mat11 = list.at(i).at(12);
        QString Mat12 = list.at(i).at(13);
        QString Mat13 = list.at(i).at(14);
        QString Mat14 = list.at(i).at(15);
        QString Mat15 = list.at(i).at(16);
        QString Mat16 = list.at(i).at(17);
        QString Mat17 = list.at(i).at(18);
        QString Mat18 = list.at(i).at(19);
        QString intensityLevel = list.at(i).at(20);
        QString state = list.at(i).at(21);
        QString jbTime = list.at(i).at(22);
        QString wushui = list.at(i).at(23);
        QStringList matList;
        matList<<Mat1<<Mat2<<Mat3<<Mat4<<Mat5<<Mat6<<Mat7<<Mat8<<Mat9<<Mat10<<Mat11<<Mat12<<Mat13<<Mat14<<Mat15<<Mat16<<Mat17<<Mat18;
        if(state == "insert"){
            QString insertSQL = QString("insert into PEIFANG (IDENT,NAME,Mat1,Mat2,Mat3,Mat4,Mat5,Mat6,Mat7,Mat8,Mat9,Mat10,Mat11,Mat12,\
                                        Mat13,Mat14,Mat15,Mat16,Mat17,Mat18,PhbNumber,countps,fdata1) VALUES (%1,'%2',%3,%4,%5,%6,%7,%8,%9,%10,\
                                        %11,%12,%13,%14,%15,%16,%17,%18,%19,%20,'%21',%22,%23)")
                    .arg(RecipeID,intensityLevel).arg(Mat1,Mat2,Mat3,Mat4,Mat5,Mat6,Mat7,Mat8,Mat9)
                    .arg(Mat10,Mat11,Mat12,Mat13,Mat14,Mat15,Mat16,Mat17,Mat18).arg(RecipeName,jbTime,wushui);
            XinXingQuery->exec(insertSQL);
        }
        else if(state == "update"){
            QString updateSQL = QString("update PEIFANG set Mat1=%1,Mat2=%2,Mat3=%3,Mat4=%4,Mat5=%5,Mat6=%6,Mat7=%7,\
                                        Mat8=%8,Mat9=%9,Mat10=%10,Mat11=%11,Mat12=%12,Mat13=%13,Mat14=%14,Mat15=%15,Mat16=%16,Mat17=%17,\
                                        Mat18=%18,countps=%19,IDENT=%21,fdata1=%22 where PhbNumber='%20'")
                    .arg(Mat1,Mat2,Mat3,Mat4,Mat5,Mat6,Mat7,Mat8,Mat9).arg(Mat10,Mat11,Mat12,Mat13,Mat14,Mat15,Mat16,Mat17,Mat18)
                    .arg(jbTime,RecipeName,RecipeID,wushui);
            XinXingQuery->exec(updateSQL);
        }
        else if(state == "delete"){
            QString deleteSQL = QString("delete from PEIFANG where PhbNumber='%1'").arg(RecipeName);
            XinXingQuery->exec(deleteSQL);
        }

        //校验
        if(state == "delete"){
            QString searchSQL = QString("select IDENT from PEIFANG where PhbNumber='%1'").arg(RecipeName);
            XinXingQuery->exec(searchSQL);
            bool res = XinXingQuery->next();
            if(res == false){
                QString deleteSQL = QString("delete from PhbReact where unit='%2' and RecipeName='%1'").arg(RecipeName).arg(unitNo);
                db.sql_exec(deleteSQL);
            }
        }
        else{
            QString searchSQL = QString("select Mat1,Mat2,Mat3,Mat4,Mat5,Mat6,Mat7,Mat8,Mat9,Mat10,Mat11,Mat12,Mat13,Mat14,Mat15,Mat16,Mat17,Mat18 from PEIFANG where PhbNumber='%1'").arg(RecipeName);
            XinXingQuery->exec(searchSQL);
            if(!XinXingQuery->next()){
                QString updateSQL = QString("update PhbReact set state='insert' where unit='%2' and RecipeName='%1'").arg(RecipeName).arg(unitNo);
                db.sql_exec(updateSQL);
                return;
            }
            bool res = false;
            for(int i = 0;i<18;i++){
                res = (XinXingQuery->value(i) == matList.at(i));
                if(res == false){
                    QString updateSQL = QString("update PhbReact set state='update' where unit='%2' and RecipeName='%1'").arg(RecipeName).arg(unitNo);
                    db.sql_exec(updateSQL);
                    return;
                }
            }
            QString deleteSQL = QString("delete from PhbReact where unit='%2' and RecipeName='%1'").arg(RecipeName).arg(unitNo);
            db.sql_exec(deleteSQL);
        }
    }
}

void thread_sync::syncPeiFangKuTask()
{
    //获取需要传输的总任务列表
    QString searchID = QString("select taskID from taskListReact where unitID='%1' order by taskID").arg(PRODUCTUNITNO);
    QStringList taskListIDList = db.find_CheNo(searchID);
    QString taskListID;
    for(int i = 0; i < taskListIDList.count(); i++){
        taskListID.append(QString("'%1',").arg(taskListIDList.at(i)));
    }
    taskListID = taskListID.left(taskListID.length()-1);
    if(taskListID.isEmpty()){
        taskListID = "0";
    }

    QString searchSQL = QString("select TaskNumber,Template,PlannedQuantity,ContractCompletion,Slump,PouringPosition,Engineering,\
                                FaHuoCustomer,PouringMethod,CumulativeNumber,StrengthGrade,SupplyTime from ProductionTaskList \
                                where TaskNumber in (%1);").arg(taskListID);
    QList<QStringList> list = db.sql_result(searchSQL.toStdString().data());
    for(int i = 0;i<list.size();i++){
        //任务编号
        QString rwID = list.at(i).at(0);
        //任务名称
        QString PFname = list.at(i).at(1);
        //设定总方量
        QString GZsetCount = list.at(i).at(2);
        //累计方量
        QString GZfinishCount = list.at(i).at(3);
        //塌落度
        QString GZtaladu = list.at(i).at(4);
        //浇筑部位
        QString GZjzbw = list.at(i).at(5);
        //工程名称
        QString GZgcmc = list.at(i).at(6);
        //用户名称
        QString GZusername = list.at(i).at(7);
        //配比编号
        QString pfid = list.at(i).at(1);
        //泵送情况
        QString GZbsqk = list.at(i).at(8);
        //砼类别、水泥品种
        QString GZspec = "/";
        //完成情况
        QString bak2 = "新任务";
        //含水率修正2
        QString GZsetmjlfs = QString("0");
        //累计车次
        QString GZleijicheci = list.at(i).at(9);
        //配比名称
        QString name = list.at(i).at(1);
        //强度等级
        QString tdj = list.at(i).at(10);
        tdj.replace(" "+list.at(i).at(8),"").replace(" ","");
        //任务生产时间
        QString dateTime = list.at(i).at(11);

        QString insertSQL = QString("insert into rwTab (rwID,PFname,GZsetCount,GZfinishCount,GZtaladu,GZjzbw,GZgcmc,GZusername,pfid,GZbsqk,GZspec,bak2,GZsetmjlfs,\
                                    GZleijicheci,name,tdj,[dateTime]) values ('%1','%2',%3,%4,'%5','%6','%7','%8','%9','%10','%11','%12',%13,%14,'%15','%16',#%17#);")
                             .arg(rwID,PFname,GZsetCount,GZfinishCount,GZtaladu,GZjzbw,GZgcmc,GZusername,pfid)
                             .arg(GZbsqk,GZspec,bak2,GZsetmjlfs,GZleijicheci,name,tdj,dateTime);
        XinXingQuery->exec(insertSQL);
        XinXingQuery->clear();

        //校验
        QString searchSQL = QString("select rwID from rwTab where rwID='%1'").arg(rwID);
        XinXingQuery->exec(searchSQL);
        if(XinXingQuery->next()){//如果找到了记录
            //删除taskReact表中的数据
            QString deleteSQL = QString("delete from taskListReact where taskID='%1' and unitID='%2';").arg(taskListID,PRODUCTUNITNO);
            db.sql_exec(deleteSQL.toStdString().data());
        }else{
            emit erroMessage(PRODUCTUNITNO+"#线任务传输失败");
            break;
        }
    }
}

void thread_sync::syncRenWuKuTask()
{
    //获取需要传输的总任务列表
    QString searchID = QString("select taskID from taskListReact where unitID='%1' order by taskID").arg(PRODUCTUNITNO);
    QStringList taskListIDList = db.find_CheNo(searchID);
    QString taskListID;
    for(int i = 0; i < taskListIDList.count(); i++){
        taskListID.append(QString("'%1',").arg(taskListIDList.at(i)));
    }
    taskListID = taskListID.left(taskListID.length()-1);
    if(taskListID.isEmpty()){
        taskListID = "0";
    }

    QString searchSQL = QString("SELECT TaskNumber,Template,PlannedQuantity,ContractCompletion,Slump,PouringPosition,Engineering,FaHuoCustomer,\
                                PouringMethod,CumulativeNumber,StrengthGrade,SupplyTime, MAT1,MAT2,MAT3,MAT4,MAT5,MAT6,MAT7,MAT8,MAT9,MAT10,\
                                MAT11,MAT12,MAT13,MAT14,MAT15,MAT16,MAT17,MAT18,MAT19,MAT20,WuShui FROM ProductionTaskList A LEFT JOIN (SELECT * FROM rwPEIFANG) B \
                                ON (A.TaskNumber=B.TaskList) WHERE B.StateNo='%1' AND TaskNumber IN (%2)").arg(PRODUCTUNITNO,taskListID);
    QList<QStringList> list = db.sql_result(searchSQL.toStdString().data());
    for(int i = 0;i<list.size();i++){
        //任务编号
        QString rwID = list.at(i).at(0);
        //任务名称
        QString PFname = list.at(i).at(1);
        //设定总方量
        QString GZsetCount = list.at(i).at(2);
        //累计方量
        QString GZfinishCount = list.at(i).at(3);
        //塌落度
        QString GZtaladu = list.at(i).at(4);
        //浇筑部位
        QString GZjzbw = list.at(i).at(5);
        //工程名称
        QString GZgcmc = list.at(i).at(6);
        //用户名称
        QString GZusername = list.at(i).at(7);
        //配比编号
        QString pfid = list.at(i).at(1);
        //泵送情况
        QString GZbsqk = list.at(i).at(8);
        //砼类别、水泥品种
        QString GZspec = "/";
        //完成情况
        QString bak2 = "新任务";
        //含水率修正2
        QString GZsetmjlfs = QString("0");
        //累计车次
        QString GZleijicheci = list.at(i).at(9);
        //配比名称
        QString name = list.at(i).at(1);
        //强度等级
        QString tdj = list.at(i).at(10);
        tdj.replace(" "+list.at(i).at(8),"").replace(" ","");
        //任务生产时间
        QString dateTime = list.at(i).at(11);
        QString MAT1 = list.at(i).at(12);
        QString MAT2 = list.at(i).at(13);
        QString MAT3 = list.at(i).at(14);
        QString MAT4 = list.at(i).at(15);
        QString MAT5 = list.at(i).at(16);
        QString MAT6 = list.at(i).at(17);
        QString MAT7 = list.at(i).at(18);
        QString MAT8 = list.at(i).at(19);
        QString MAT9 = list.at(i).at(20);
        QString MAT10 = list.at(i).at(21);
        QString MAT11 = list.at(i).at(22);
        QString MAT12 = list.at(i).at(23);
        QString MAT13 = list.at(i).at(24);
        QString MAT14 = list.at(i).at(25);
        QString MAT15 = list.at(i).at(26);
        QString MAT16 = list.at(i).at(27);
        QString MAT17 = list.at(i).at(28);
        QString MAT18 = list.at(i).at(29);
        QString MAT19 = list.at(i).at(30);
        QString MAT20 = list.at(i).at(31);
        QString WuShui = list.at(i).at(32);
        if(MAT1.isEmpty()){
            MAT1 = "0";
        }
        if(MAT2.isEmpty()){
            MAT2 = "0";
        }
        if(MAT3.isEmpty()){
            MAT3 = "0";
        }
        if(MAT4.isEmpty()){
            MAT4 = "0";
        }
        if(MAT5.isEmpty()){
            MAT5 = "0";
        }
        if(MAT6.isEmpty()){
            MAT6 = "0";
        }
        if(MAT7.isEmpty()){
            MAT7 = "0";
        }
        if(MAT8.isEmpty()){
            MAT8 = "0";
        }
        if(MAT9.isEmpty()){
            MAT9 = "0";
        }
        if(MAT10.isEmpty()){
            MAT10 = "0";
        }
        if(MAT11.isEmpty()){
            MAT11 = "0";
        }
        if(MAT12.isEmpty()){
            MAT12 = "0";
        }
        if(MAT13.isEmpty()){
            MAT13 = "0";
        }
        if(MAT14.isEmpty()){
            MAT14 = "0";
        }
        if(MAT15.isEmpty()){
            MAT15 = "0";
        }
        if(MAT16.isEmpty()){
            MAT16 = "0";
        }
        if(MAT17.isEmpty()){
            MAT17 = "0";
        }
        if(MAT18.isEmpty()){
            MAT18 = "0";
        }
        if(MAT19.isEmpty()){
            MAT19 = "0";
        }
        if(MAT20.isEmpty()){
            MAT20 = "0";
        }
        if(WuShui.isEmpty()){
            WuShui = "0";
        }

        QString insertSQL = QString("insert into rwTab (rwID,PFname,GZsetCount,GZfinishCount,GZtaladu,GZjzbw,GZgcmc,GZusername,pfid,GZbsqk,GZspec,bak2,GZsetmjlfs,\
                                    GZleijicheci,name,tdj,[dateTime],mat1,mat2,mat3,mat4,mat5,mat6,mat7,mat8,mat9,mat10,mat11,mat12,mat13,mat14,mat15,mat16,mat17,\
                                    mat18,mat19,mat20,wushui) values ('%1','%2',%3,%4,'%5','%6','%7','%8','%9','%10','%11','%12',%13,%14,'%15','%16',#%17#,\
                                     %18,%19,%20,%21,%22,%23,%24,%25,%26,%27,%28,%29,%30,%31,%32,%33,%34,%35,%36,%37,%38);")
                             .arg(rwID,PFname,GZsetCount,GZfinishCount,GZtaladu,GZjzbw,GZgcmc,GZusername,pfid)
                             .arg(GZbsqk,GZspec,bak2,GZsetmjlfs,GZleijicheci,name,tdj,dateTime)
                             .arg(MAT1,MAT2,MAT3,MAT4,MAT5,MAT6,MAT7,MAT8,MAT9)
                             .arg(MAT10,MAT11,MAT12,MAT13,MAT14,MAT15,MAT16,MAT17,MAT18).arg(MAT19,MAT20,WuShui);
        XinXingQuery->exec(insertSQL);
        if(!XinXingQuery->lastError().text().isEmpty()){
            QString updateSQL = QString("update rwTab set mat1=%1,mat2=%2,mat3=%3,mat4=%4,mat5=%5,mat6=%6,mat7=%7,mat8=%8,mat9=%9,mat10=%10,mat11=%11,\
                                         mat12=%12,mat13=%13,mat14=%14,mat15=%15,mat16=%16,mat17=%17,mat18=%18,mat19=%19,mat20=%20,WuShui=%21 where rwID='%22'")
                    .arg(MAT1,MAT2,MAT3,MAT4,MAT5,MAT6,MAT7,MAT8,MAT9).arg(MAT10,MAT11,MAT12,MAT13,MAT14,MAT15,MAT16,MAT17,MAT18).arg(MAT19,MAT20,WuShui,rwID);
            XinXingQuery->exec(updateSQL);
        }

        //校验
        QString searchSQL = QString("select rwID from rwTab where rwID='%1'").arg(rwID);
        XinXingQuery->exec(searchSQL);
        if(XinXingQuery->next()){//如果找到了记录
            //删除taskReact表中的数据
            QString deleteSQL = QString("delete from taskListReact where taskID='%1' and unitID='%2';").arg(rwID,PRODUCTUNITNO);
            db.sql_exec(deleteSQL.toStdString().data());
        }else{
            emit erroMessage(PRODUCTUNITNO+"#线任务传输失败");
            break;
        }
    }
}

void thread_sync::syncDcRw()
{
    QString searchSQL = QString("select RecordNum from SendProductNotice where Unit='%1' order by RecordNum+0 limit 1").arg(PRODUCTUNITNO);
    QString SendNum = db.sql_fetchrow_plus(searchSQL.toStdString().data(),0);
    if(SendNum.isEmpty()){
        SendNum = "0";
    }

    QString searchDcRw = QString("select RecordNumber,TaskList,DeliveryVehicle,Driver,ActualProductionVolume,ProductionTime,Engineering,StrengthGrade,TemplateName, \
                                 PouringMethod,VolumeMortar from ProductionNotice where RecordNumber=%1 and Unit='%2#机组'").arg(SendNum,PRODUCTUNITNO);
    QList<QStringList> listNotice = db.sql_result(searchDcRw.toStdString().data());
    for(int i = 0;i<listNotice.size();i++){
        QString DJBH = listNotice.at(i).at(0);
        QString khrwdh = listNotice.at(i).at(1);
        QString CH = listNotice.at(i).at(2);
        QString SJname = listNotice.at(i).at(3);
        QString BCFS = listNotice.at(i).at(4);
        QString scdate = listNotice.at(i).at(5);
        QString GCMC = listNotice.at(i).at(6);
        QString bh = listNotice.at(i).at(7);
        bh.replace(" "+listNotice.at(i).at(9),"").replace(" ","");
        QString PHB = listNotice.at(i).at(8);

        QString searchJBTime = QString("select JBTIME from rwPEIFANG where TaskList='%1' and StateNo='%2'").arg(khrwdh,PRODUCTUNITNO);
        QString JBSJ = db.sql_fetchrow_plus(searchJBTime,0);
        if(JBSJ.isEmpty()){
            JBSJ = "0";
        }
        //砂浆
        QString shajiang = listNotice.at(i).at(10);

        //如果本车方量为0，则跳过
        if(BCFS.toDouble() == 0){
            return;
        }
        QString insertDcRwTabMy;
        if(shajiang.toDouble() == 0){
            insertDcRwTabMy = QString("insert into DcRwTab (khrwdh,CH,SJname,BCFS,SFWC,SFYX,SFZF,scdate,GCMC,bh,JBSJ,SCSTST,PHB,DJBHOrder,bsqk,DJBH) values \
            ('%1','%2','%3',%4,0,0,0,'%5','%6','%7',%10,-1,'%8',%9,'%9','%9');").arg(khrwdh,CH,SJname,BCFS,scdate,GCMC,bh,PHB,DJBH).arg(JBSJ);
            XinXingQuery->exec(insertDcRwTabMy);
            XinXingQuery->clear();
        }
        if(shajiang.toDouble() > 0){
            insertDcRwTabMy = QString("insert into DcRwTab (khrwdh,CH,SJname,BCFS,SFWC,SFYX,SFZF,scdate,GCMC,bh,JBSJ,SCSTST,PHB,DJBHOrder,bsqk,DJBH,SJPBH,SJFS) values \
            ('%1','%2','%3',%4,0,0,0,'%5','%6','%7',%11,-1,'%8',%9,'%9','%9','砂浆',%10);").arg(khrwdh,CH,SJname,BCFS,scdate,GCMC,bh,PHB,DJBH).arg(shajiang,JBSJ);
            XinXingQuery->exec(insertDcRwTabMy);
            XinXingQuery->clear();
        }

        //校验
        QString searchSQL = QString("select scdate from DcRwTab where DJBH='%1'").arg(DJBH);
        XinXingQuery->exec(searchSQL);
        if(XinXingQuery->next()){//如果找到了记录
            QString deleteSQL = QString("delete from SendProductNotice where RecordNum='%1'").arg(DJBH);
            db.sql_exec(deleteSQL);
        }else{
            emit erroMessage(QString("单车任务传输失败:\n")+insertDcRwTabMy);
            return;
        }
    }
}

void thread_sync::deleteDcRw()
{
    QString searchSQL = QString("select cheNo,cheTime,Unit,recordNo from productNoticeReact where Unit='%1#机组' order by recordNo+0 desc limit 1").arg(PRODUCTUNITNO);
    QString cheNo = db.sql_fetchrow_plus(searchSQL.toStdString().data(),0);
    QString cheTime = db.sql_fetchrow_plus(searchSQL.toStdString().data(),1);
    QString unit = db.sql_fetchrow_plus(searchSQL.toStdString().data(),2);
    unit = unit.left(1);
    QString recordNo = db.sql_fetchrow_plus(searchSQL.toStdString().data(),3);
    if(PRODUCTUNITNO == unit){
        QString deleteSQL = QString("delete from DcRwTab where bsqk='%1' and SFYX=0").arg(recordNo);
        XinXingQuery->exec(deleteSQL);
        qDebug()<<tr("删除任务")<<deleteSQL<<XinXingQuery->lastError().text();
        XinXingQuery->clear();

        QString deleteSQL1 = QString("delete from productNoticeReact where cheNo='%1' and cheTime='%2';").arg(cheNo,cheTime);
        db.sql_exec(deleteSQL1.toStdString().data());
    }
}

void thread_sync::syncBuFangDcRw()
{
    QString search = QString("select number from bufangReact where unit='%1' limit 1").arg(PRODUCTUNITNO);
    QString bufangNo = db.sql_fetchrow_plus(search.toStdString().data(),0);
    if(bufangNo.isEmpty()){
        bufangNo = "0";
    }

    QString searchDcRw = QString("select RecordNumber,TaskList,DeliveryVehicle,Driver,ActualProductionVolume,ProductionTime,Engineering,StrengthGrade,TemplateName, \
                                 PouringMethod,VolumeMortar from bufangNotice where RecordNumber=%1 and Unit='%2#机组' and WhetherDocument='是';").arg(bufangNo,PRODUCTUNITNO);
    QList<QStringList> listNotice = db.sql_result(searchDcRw.toStdString().data());
    for(int i = 0;i<listNotice.size();i++){
        QString DJBH = listNotice.at(i).at(0);
        QString khrwdh = listNotice.at(i).at(1);
        QString CH = listNotice.at(i).at(2);
        QString SJname = listNotice.at(i).at(3);
        QString BCFS = listNotice.at(i).at(4);
        QString scdate = listNotice.at(i).at(5);
        QString GCMC = listNotice.at(i).at(6);
        QString bh = listNotice.at(i).at(7);
        bh.replace(" "+listNotice.at(i).at(9),"").replace(" ","");
        QString PHB = listNotice.at(i).at(8);

        QString searchJBTime = QString("select JBTIME from rwPEIFANG where TaskList='%1' and StateNo='%2'").arg(khrwdh,PRODUCTUNITNO);
        QString JBSJ = db.sql_fetchrow_plus(searchJBTime,0);
        if(JBSJ.isEmpty()){
            JBSJ = "0";
        }
        //砂浆
        QString shajiang = listNotice.at(i).at(10);
        //混凝土方量
        BCFS = QString::number(BCFS.toDouble()-shajiang.toDouble(),'f',1);


        //混凝土任务开始
        if(BCFS.toDouble() >= 0.4){
            QString insertSQL = QString("insert into DcRwTab (khrwdh,CH,SJname,BCFS,SFWC,SFYX,SFZF,scdate,GCMC,bh,JBSJ,SCSTST,PHB,DJBHOrder,bsqk,DJBH) values \
                                        ('%1','%2','%3',%4,0,0,0,'%5','%6','%7',%10,-1,'%8',%9,'%9','%11');").arg(khrwdh,CH,SJname,BCFS,scdate,GCMC,bh,PHB,DJBH).arg(JBSJ,QString("Z")+DJBH);
            XinXingQuery->exec(insertSQL);
            XinXingQuery->clear();

            //校验
            QString searchSQL = QString("select scdate from DcRwTab where DJBH='%1'").arg(QString("Z")+DJBH);
            XinXingQuery->exec(searchSQL);
            qDebug()<<searchSQL<<XinXingQuery->lastError().text();
            if(XinXingQuery->next()){//如果找到了记录
                QString deleteSQL = QString("delete from bufangReact where number='%1';").arg(bufangNo);
                db.sql_exec(deleteSQL.toStdString().data());
            }else{
                emit erroMessage("补方任务传输失败");
                return;
            }
        }
        /*混凝土任务结束*/

        //如果含有砂浆
        if(shajiang.toDouble() > 0){
            QString insertSQL = QString("insert into DcRwTab (khrwdh,CH,SJname,BCFS,SFWC,SFYX,SFZF,scdate,GCMC,bh,JBSJ,SCSTST,PHB,DJBHOrder,bsqk,DJBH) values \
                                        ('%1','%2','%3',%4,0,0,0,'%5','%6','%7',%11,-1,'%8',%10,'%9','%10')")
                    .arg("砂浆",CH,SJname,shajiang,scdate,GCMC,bh,"砂浆",DJBH).arg(QString::number(DJBH.toDouble()+1000),JBSJ);
            XinXingQuery->exec(insertSQL);
            XinXingQuery->clear();


            //校验
            QString searchSQL1 = QString("select scdate from DcRwTab where DJBH='%1'").arg(QString::number(DJBH.toDouble()+1000));
            XinXingQuery->exec(searchSQL1);
            qDebug()<<searchSQL1<<XinXingQuery->lastError().text();
            if(XinXingQuery->next()){//如果找到了记录

            }else{
                emit erroMessage("补方任务传输失败");
                return;
            }
        }
        //砂浆任务结束
    }
}

void thread_sync::uploadRunState()
{
    QString unitNo = PRODUCTUNITNO;
    QString searchDcRwTabSQL = QString("select bsqk from DcRwTab where SFWC=0 AND SFYX=-1");
    XinXingQuery->exec(searchDcRwTabSQL);
    while (XinXingQuery->next()) {
        QString DJBH = XinXingQuery->value(0).toString();
        QString searchHISTDATAsql = QString("select count(1)+1,SUM(SUMPS) from HISTDATA WHERE bsqk='%1'").arg(DJBH);
        RunStatequery->exec(searchHISTDATAsql);
        RunStatequery->next();
        QString panshu = RunStatequery->value(0).toString();
        QString volume = RunStatequery->value(1).toString();
        QString updateMySQL = QString("update ProductionNotice set Confirmor='是' where RecordNumber=%1").arg(DJBH);
        db.sql_exec(updateMySQL.toStdString().data());
        QString insertMySQL = QString("replace into RunStateTab (recordNo,panshu,volume,unitNo) values ('%1','%2','%3','%4');").arg(DJBH,panshu,volume,unitNo);
        db.sql_exec(insertMySQL.toStdString().data());
    }

    QString searchMySQLRunState = QString("select recordNo from RunStateTab where unitNo='%1'").arg(unitNo);
    QStringList recordList = db.find_CheNo(searchMySQLRunState);
    for(int i = 0; i<recordList.count(); i++){
        QString searchSQL = QString("select DJBH from DcRwTab where SFWC=0 AND SFYX=-1 and bsqk='%1'").arg(recordList.at(i));
        XinXingQuery->exec(searchSQL.toStdString().data());
        if(!XinXingQuery->next()){
            //删除相关生产状态表中的记录
            QString deleteSQL = QString("delete from RunStateTab where recordNo='%1'").arg(recordList.at(i));
            db.sql_exec(deleteSQL.toStdString().data());
            //删除车辆队列
            QString deleteVehicle = QString("delete from inHouseVehicle where CheNo=(select DeliveryVehicle from ProductionNotice where RecordNumber=%1)").arg(recordList.at(i));
            db.sql_exec(deleteVehicle);
        }
    }
}

void thread_sync::syncZhuiJiaDcRw()
{
    QString search = QString("select RecordNo,ZhuiJiaVolume,ZhuiJiaStatus,ZhuiJiaTime from ZhuiJiaRecord where WhetherSync='否' limit 1");
    QString recordNo = db.sql_fetchrow_plus(search.toStdString().data(),0);
    QString BCFS = db.sql_fetchrow_plus(search.toStdString().data(),1);
    QString whetherCancel = db.sql_fetchrow_plus(search.toStdString().data(),2);
    QString ZhuiJiaTime = db.sql_fetchrow_plus(search.toStdString().data(),3);
    QString FLAG = db.sql_fetchrow_plus(search.toStdString().data(),3);
    FLAG = FLAG.right(8);

    if(whetherCancel == "否"){
        QString searchDcRw = QString("select RecordNumber,TaskList,DeliveryVehicle,Driver,ShippingVolume,ProductionTime,Engineering,StrengthGrade,TemplateName, \
                                     PouringMethod,VolumeMortar,Unit from ProductionNotice where RecordNumber=%1").arg(recordNo);
        QStringList listNotice = db.CreatStrList(searchDcRw);
        if(listNotice.isEmpty()){
            return;
        }
        QString unit = listNotice.at(11);
        if(unit.left(1) != PRODUCTUNITNO){
            return;
        }

        QString DJBH = listNotice.at(0);
        QString khrwdh = listNotice.at(1);
        QString CH = listNotice.at(2);
        QString SJname = listNotice.at(3);
        QString scdate = listNotice.at(5);
        QString GCMC = listNotice.at(6);
        QString bh = listNotice.at(7);
        bh.replace(" "+listNotice.at(9),"").replace(" ","");
        QString PHB = listNotice.at(8);

        QString searchJBTime = QString("select JBTIME from rwPEIFANG where TaskList='%1' and StateNo='%2'").arg(khrwdh,PRODUCTUNITNO);
        QString JBSJ = db.sql_fetchrow_plus(searchJBTime,0);
        if(JBSJ.isEmpty()){
            JBSJ = "0";
        }

        //混凝土任务开始
        if(BCFS.toDouble() > 0){
            QString insertSQL = QString("insert into DcRwTab (khrwdh,CH,SJname,BCFS,SFWC,SFYX,SFZF,scdate,GCMC,bh,JBSJ,SCSTST,PHB,DJBHOrder,bsqk,DJBH) \
                                        values ('%1','%2','%3',%4,0,0,0,'%5','%6','%7',%10,-1,'%8',%9,'%9','%11');")
                    .arg(khrwdh,CH,SJname,BCFS,scdate,GCMC,bh,PHB,DJBH).arg(JBSJ,FLAG);
            XinXingQuery->exec(insertSQL);
            qDebug()<<XinXingQuery->lastError().text()<<insertSQL;
            XinXingQuery->clear();

            //校验
            QString searchSQL = QString("select scdate from DcRwTab where DJBH='%1'").arg(FLAG);
            XinXingQuery->exec(searchSQL);
            if(XinXingQuery->next()){//如果找到了记录
                QString updateSQL = QString("update ZhuiJiaRecord set WhetherSync='是' where RecordNo='%1' and ZhuiJiaTime='%2';").arg(recordNo,ZhuiJiaTime);
                db.sql_exec(updateSQL.toStdString().data());
            }else{
                emit erroMessage("追加任务传输失败");
                return;
            }
        }
        /*混凝土任务结束*/
    }
    else if(whetherCancel == "是"){
        QString deleteSQL = QString("delete from DcRwTab where DJBH='%1';").arg(FLAG);
        XinXingQuery->exec(deleteSQL);
        XinXingQuery->clear();

        //校验
        QString searchSQL = QString("select scdate from DcRwTab where DJBH='%1'").arg(FLAG);
        XinXingQuery->exec(searchSQL);
        if(!XinXingQuery->next()){//如果没有找到记录
            QString updateSQL = QString("update ZhuiJiaRecord set WhetherSync='是' where RecordNo='%1' and ZhuiJiaTime='%2';").arg(recordNo,ZhuiJiaTime);
            db.sql_exec(updateSQL.toStdString().data());
        }else{
            emit erroMessage("追加任务传输失败");
            return;
        }
    }
}

void thread_sync::FMsyncPhb(QString unitNo)
{
    QString searchPhbReact = QString("select RecipeID,RecipeName,Mat1,Mat2,Mat3,Mat4,Mat5,Mat6,Mat7,Mat8,Mat9,Mat10,Mat11,Mat12,Mat13,Mat14,Mat15,Mat16,Mat17,Mat18,\
                                      intensityLevel,state,jbTime from PhbReact where unit='%1'").arg(unitNo);
    QList<QStringList> list = db.sql_result(searchPhbReact.toStdString().data());
    for(int i = 0;i<list.size();i++){
        QString RecipeID = list.at(i).at(0);
        QString RecipeName = list.at(i).at(1);
        QString Mat1 = list.at(i).at(2);
        QString Mat2 = list.at(i).at(3);
        QString Mat3 = list.at(i).at(4);
        QString Mat4 = list.at(i).at(5);
        QString Mat5 = list.at(i).at(6);
        QString Mat6 = list.at(i).at(7);
        QString Mat7 = list.at(i).at(8);
        QString Mat8 = list.at(i).at(9);
        QString Mat9 = list.at(i).at(10);
        QString Mat10 = list.at(i).at(11);
        QString Mat11 = list.at(i).at(12);
        QString Mat12 = list.at(i).at(13);
        QString Mat13 = list.at(i).at(14);
        QString Mat14 = list.at(i).at(15);
        QString Mat15 = list.at(i).at(16);
        QString Mat16 = list.at(i).at(17);
        QString Mat17 = list.at(i).at(18);
        QString Mat18 = list.at(i).at(19);
        QString intensityLevel = list.at(i).at(20);
        QString state = list.at(i).at(21);
        QString jbTime = list.at(i).at(22);
        QStringList matList;
        matList<<Mat1<<Mat2<<Mat3<<Mat4<<Mat5<<Mat6<<Mat7<<Mat8<<Mat9<<Mat10<<Mat11<<Mat12<<Mat13<<Mat14<<Mat15<<Mat16<<Mat17<<Mat18;
        if(state == "insert"){
            QString insertSQL = QString("insert into FormulaTable (c_Code,c_Strength,d_Item0,d_Item1,d_Item2,d_Item3,d_Item4,d_Item5,d_Item6,d_Item7,d_Item8,d_Item9,d_Item10,\
                                        d_Item11,d_Item12,d_Item13,d_Item14,d_Item15,d_Item16,d_Item17,c_UniqueMark,d_MixingTime) VALUES ('%1','%2',%3,%4,%5,%6,%7,%8,%9,%10,\
                                        %11,%12,%13,%14,%15,%16,%17,%18,%19,%20,'%21',%22)")
                    .arg(RecipeID,intensityLevel).arg(Mat1,Mat2,Mat3,Mat4,Mat5,Mat6,Mat7,Mat8,Mat9)
                    .arg(Mat10,Mat11,Mat12,Mat13,Mat14,Mat15,Mat16,Mat17,Mat18).arg(RecipeName,jbTime);
            FMRecipeQuery->exec(insertSQL);
        }
        else if(state == "update"){
            QString updateSQL = QString("update FormulaTable set d_Item0=%1,d_Item1=%2,d_Item2=%3,d_Item3=%4,d_Item4=%5,d_Item5=%6,d_Item6=%7,\
                                        d_Item7=%8,d_Item8=%9,d_Item9=%10,d_Item10=%11,d_Item11=%12,d_Item12=%13,d_Item13=%14,d_Item14=%15,d_Item15=%16,d_Item16=%17,\
                                        d_Item17=%18,d_MixingTime=%19,c_Code='%20' where c_UniqueMark='%21'")
                    .arg(Mat1,Mat2,Mat3,Mat4,Mat5,Mat6,Mat7,Mat8,Mat9).arg(Mat10,Mat11,Mat12,Mat13,Mat14,Mat15,Mat16,Mat17,Mat18)
                    .arg(jbTime,RecipeID,RecipeName);
            FMRecipeQuery->exec(updateSQL);
        }
        else if(state == "delete"){
            QString deleteSQL = QString("delete from FormulaTable where c_UniqueMark='%1'").arg(RecipeName);
            FMRecipeQuery->exec(deleteSQL);
        }



        //校验
        if(state == "delete"){
            QString searchSQL = QString("select c_UniqueMark from FormulaTable where c_UniqueMark='%1'").arg(RecipeName);
            FMRecipeQuery->exec(searchSQL);
            bool res = FMRecipeQuery->next();
            if(res == false){
                QString deleteSQL = QString("delete from PhbReact where unit='%2' and RecipeName='%1'").arg(RecipeName).arg(unitNo);
                db.sql_exec(deleteSQL);
            }
        }
        else{
            QString searchSQL = QString("select d_Item0,d_Item1,d_Item2,d_Item3,d_Item4,d_Item5,d_Item6,d_Item7,d_Item8,d_Item9,d_Item10,\
                                        d_Item11,d_Item12,d_Item13,d_Item14,d_Item15,d_Item16,d_Item17 from FormulaTable where c_UniqueMark='%1'").arg(RecipeName);
            FMRecipeQuery->exec(searchSQL);
            if(!FMRecipeQuery->next()){
                QString updateSQL = QString("update PhbReact set state='insert' where unit='%2' and RecipeName='%1'").arg(RecipeName).arg(unitNo);
                db.sql_exec(updateSQL);
                return;
            }
            bool res = false;
            for(int i = 0;i<18;i++){
                res = (FMRecipeQuery->value(i) == matList.at(i));
                if(res == false){
                    QString updateSQL = QString("update PhbReact set state='update' where unit='%2' and RecipeName='%1'").arg(RecipeName).arg(unitNo);
                    db.sql_exec(updateSQL);
                    return;
                }
            }
            QString deleteSQL = QString("delete from PhbReact where unit='%2' and RecipeName='%1'").arg(RecipeName).arg(unitNo);
            db.sql_exec(deleteSQL);
        }
    }
}

void thread_sync::FMsyncPeiFangKuTask()
{
    //获取需要传输的总任务列表
    QString searchID = QString("select taskID from taskListReact where unitID='%1' order by taskID").arg(PRODUCTUNITNO);
    QStringList taskListIDList = db.find_CheNo(searchID);
    QString taskListID;
    for(int i = 0; i < taskListIDList.count(); i++){
        taskListID.append(QString("'%1',").arg(taskListIDList.at(i)));
    }
    taskListID = taskListID.left(taskListID.length()-1);
    if(taskListID.isEmpty()){
        taskListID = "0";
    }

    QString searchSQL = QString("select TaskNumber,Template,PlannedQuantity,ContractCompletion,Slump,PouringPosition,Engineering,\
                                FaHuoCustomer,PouringMethod,CumulativeNumber,StrengthGrade,SupplyTime from ProductionTaskList \
                                where TaskNumber in (%1);").arg(taskListID);
    QList<QStringList> list = db.sql_result(searchSQL.toStdString().data());
    for(int i = 0;i<list.size();i++){
        //任务编号
        QString rwID = list.at(i).at(0);
        //配方名称
        QString PFname = list.at(i).at(1);
        //设定总方量
        QString GZsetCount = list.at(i).at(2);
        //累计方量
        QString GZfinishCount = list.at(i).at(3);
        //塌落度
        QString GZtaladu = list.at(i).at(4);
        //浇筑部位
        QString GZjzbw = list.at(i).at(5);
        //工程名称
        QString GZgcmc = list.at(i).at(6);
        //用户名称
        QString GZusername = list.at(i).at(7);
        //泵送情况
        QString GZbsqk = list.at(i).at(8);
        //累计车次
        QString GZleijicheci = list.at(i).at(9);
        //强度等级
        QString tdj = list.at(i).at(10);
        tdj.replace(" "+list.at(i).at(8),"").replace(" ","");

        QString insertSQL = QString("insert into BigTaskTable (c_UniqueMark,c_FMark,d_PlanCubics,d_acc_cubics,c_Slump,c_ProjectPart,c_ProjectName,c_ClientName,c_PouringType,\
                                    i_acc_trucks,c_Strength) values ('%1','%2',%3,%4,'%5','%6','%7','%8','%9',%10,'%11');")
                             .arg(rwID,PFname,GZsetCount,GZfinishCount,GZtaladu,GZjzbw,GZgcmc,GZusername).arg(GZbsqk,GZleijicheci,tdj);
        FMBigTaskQuery->exec(insertSQL);
        FMBigTaskQuery->clear();

        //校验
        QString searchSQL = QString("select c_UniqueMark from BigTaskTable where c_UniqueMark='%1'").arg(rwID);
        FMBigTaskQuery->exec(searchSQL);
        if(FMBigTaskQuery->next()){//如果找到了记录
            //删除taskReact表中的数据
            QString deleteSQL = QString("delete from taskListReact where taskID='%1' and unitID='%2'").arg(rwID,PRODUCTUNITNO);
            db.sql_exec(deleteSQL.toStdString().data());
        }else{
            emit erroMessage(PRODUCTUNITNO+"#线任务传输失败");
            break;
        }
    }
}

void thread_sync::FMsyncDcRw()
{
    QString searchSQL = QString("select RecordNum from SendProductNotice where Unit='%1' order by RecordNum+0 limit 1").arg(PRODUCTUNITNO);
    QString SendNum = db.sql_fetchrow_plus(searchSQL.toStdString().data(),0);
    if(SendNum.isEmpty()){
        SendNum = "0";
    }

    QString searchDcRw = QString("select RecordNumber,TaskList,DeliveryVehicle,Driver,ActualProductionVolume,ProductionTime,Engineering,StrengthGrade,TemplateName, \
                                 PouringMethod,VolumeMortar,FaHuoCustomer,PouringPosition,Slump,CumulativeNumber,CumulativeVolume from ProductionNotice where RecordNumber=%1 and Unit='%2#机组'").arg(SendNum,PRODUCTUNITNO);
    QList<QStringList> listNotice = db.sql_result(searchDcRw.toStdString().data());
    for(int i = 0;i<listNotice.size();i++){
        QString RecordNumber = listNotice.at(i).at(0);
        QString TaskList = listNotice.at(i).at(1);
        QString DeliveryVehicle = listNotice.at(i).at(2);
        QString Driver = listNotice.at(i).at(3);
        QString ActualProductionVolume = listNotice.at(i).at(4);
        QString Engineering = listNotice.at(i).at(6);
        QString StrengthGrade = listNotice.at(i).at(7);
        StrengthGrade.replace(" "+listNotice.at(i).at(9),"").replace(" ","");
        QString TemplateName = listNotice.at(i).at(8);

        QString searchJBTime = QString("select JBTIME from rwPEIFANG where TaskList='%1' and StateNo='%2'").arg(TaskList,PRODUCTUNITNO);
        QString JBSJ = db.sql_fetchrow_plus(searchJBTime,0);
        if(JBSJ.isEmpty()){
            JBSJ = "0";
        }
        QString PouringMethod = listNotice.at(i).at(9);

        //砂浆
        QString shajiang = listNotice.at(i).at(10);
        QString FaHuoCustomer = listNotice.at(i).at(11);
        QString PouringPosition = listNotice.at(i).at(12);
        QString Slump = listNotice.at(i).at(13);
        QString CumulativeNumber = listNotice.at(i).at(14);
        QString CumulativeVolume = listNotice.at(i).at(15);


        //混凝土方量
        ActualProductionVolume = QString::number(ActualProductionVolume.toDouble()-shajiang.toDouble(),'f',1);

        //如果本车方量为0，则跳过
        if(ActualProductionVolume.toDouble() <= 0){
            return;
        }

        QString insertDcRwTabMy = QString("insert into SmallTaskTable (c_UniqueMark,c_FormulaUniqueMark,d_CurrentCubics,c_VehicleUniqueMark,\
                                  c_BigTaskUniqueMark,c_ProjectName,c_ClientName,c_ProjectPart,c_ProjectSlump,c_PouringType,\
                                  c_Remark,c_BTI0,c_BTI1,c_BTI2,c_BTI3,c_BTI4,c_DriverUniqueMark,c_STI0,c_STI1,c_STI2,c_STI3,c_STI4,c_ContractCode,\
                                  d_AccumulatedCubics,i_AccumulatedTrucks,i_WorkingState,c_ProjectStrength) values \
        ('%1','%2',%3,'%4','%5','%6','%7','%8','%9','%10','','','','','','','%11','','','','','','',%12,%13,0,'%14')")
                .arg(RecordNumber,TemplateName,ActualProductionVolume,DeliveryVehicle,TaskList,Engineering,FaHuoCustomer,PouringPosition)
                .arg(Slump,PouringMethod,Driver,CumulativeVolume,CumulativeNumber,StrengthGrade);
        FMSmallTaskQuery->exec(insertDcRwTabMy);
        if(FMSmallTaskQuery->lastError().isValid()){
            emit erroMessage(QString("单车任务传输失败:\n")+insertDcRwTabMy+FMSmallTaskQuery->lastError().text());
            FMSmallTaskQuery->clear();
            return;
        }

        if(shajiang.toDouble() > 0){
            QString insertDcRwTabMy = QString("insert into SmallTaskTable (c_UniqueMark,c_FormulaUniqueMark,d_CurrentCubics,c_VehicleUniqueMark,\
                                      c_BigTaskUniqueMark,c_ProjectName,c_ClientName,c_ProjectPart,c_ProjectSlump,c_PouringType,\
                                      c_Remark,c_BTI0,c_BTI1,c_BTI2,c_BTI3,c_BTI4,c_DriverUniqueMark,c_STI0,c_STI1,c_STI2,c_STI3,c_STI4,c_ContractCode,\
                                      d_AccumulatedCubics,i_AccumulatedTrucks,i_WorkingState,c_ProjectStrength) values \
            ('%1','%2',%3,'%4','%5','%6','%7','%8','%9','%10','','','','','','','%11','','','','','','',%12,%13,0,'%14')")
                    .arg(RecordNumber,"砂浆",shajiang,DeliveryVehicle,TaskList,Engineering,FaHuoCustomer,PouringPosition)
                    .arg(Slump,PouringMethod,Driver,CumulativeVolume,CumulativeNumber,StrengthGrade);
            FMSmallTaskQuery->exec(insertDcRwTabMy);
            if(FMSmallTaskQuery->lastError().isValid()){
                emit erroMessage(QString("单车任务传输失败:\n")+insertDcRwTabMy+FMSmallTaskQuery->lastError().text());
                FMSmallTaskQuery->clear();
                return;
            }
        }

        QString deleteSQL = QString("delete from SendProductNotice where RecordNum='%1'").arg(RecordNumber);
        db.sql_exec(deleteSQL);
    }
}

void thread_sync::FMsyncBuFangDcRw()
{
    QString search = QString("select number from bufangReact where unit='%1' limit 1").arg(PRODUCTUNITNO);
    QString bufangNo = db.sql_fetchrow_plus(search,0);
    if(bufangNo.isEmpty()){
        bufangNo = "0";
    }

    QString searchDcRw = QString("select RecordNumber,TaskList,DeliveryVehicle,Driver,ActualProductionVolume,ProductionTime,Engineering,StrengthGrade,TemplateName, \
                                 PouringMethod,VolumeMortar,FaHuoCustomer,PouringPosition,Slump,CumulativeNumber,CumulativeVolume from bufangNotice where RecordNumber=%1 and Unit='%2#机组' and WhetherDocument='是';").arg(bufangNo,PRODUCTUNITNO);
    QList<QStringList> listNotice = db.sql_result(searchDcRw.toStdString().data());
    for(int i = 0;i<listNotice.size();i++){
        QString RecordNumber = listNotice.at(i).at(0);
        QString TaskList = listNotice.at(i).at(1);
        QString DeliveryVehicle = listNotice.at(i).at(2);
        QString Driver = listNotice.at(i).at(3);
        QString ActualProductionVolume = listNotice.at(i).at(4);
        QString Engineering = listNotice.at(i).at(6);
        QString StrengthGrade = listNotice.at(i).at(7);
        StrengthGrade.replace(" "+listNotice.at(i).at(9),"").replace(" ","");
        QString TemplateName = listNotice.at(i).at(8);

        QString searchJBTime = QString("select JBTIME from rwPEIFANG where TaskList='%1' and StateNo='%2'").arg(TaskList,PRODUCTUNITNO);
        QString JBSJ = db.sql_fetchrow_plus(searchJBTime,0);
        if(JBSJ.isEmpty()){
            JBSJ = "0";
        }

        QString PouringMethod = listNotice.at(i).at(9);
        //砂浆
        QString shajiang = listNotice.at(i).at(10);
        QString FaHuoCustomer = listNotice.at(i).at(11);
        QString PouringPosition = listNotice.at(i).at(12);
        QString Slump = listNotice.at(i).at(13);
        QString CumulativeNumber = listNotice.at(i).at(14);
        QString CumulativeVolume = listNotice.at(i).at(15);
        //混凝土方量
        ActualProductionVolume = QString::number(ActualProductionVolume.toDouble()-shajiang.toDouble(),'f',1);

        //混凝土任务开始
        if(ActualProductionVolume.toDouble() >= 0.4){
            QString insertSQL = QString("insert into SmallTaskTable (c_UniqueMark,c_FormulaUniqueMark,d_CurrentCubics,c_VehicleUniqueMark,\
                                        c_BigTaskUniqueMark,c_ProjectName,c_ClientName,c_ProjectPart,c_ProjectSlump,c_PouringType,\
                                        c_Remark,c_BTI0,c_BTI1,c_BTI2,c_BTI3,c_BTI4,c_DriverUniqueMark,c_STI0,c_STI1,c_STI2,c_STI3,c_STI4,c_ContractCode,\
                                        d_AccumulatedCubics,i_AccumulatedTrucks,i_WorkingState,c_ProjectStrength) values \
              ('%1','%2',%3,'%4','%5','%6','%7','%8','%9','%10','','','','','','','%11','','','','','','',%12,%13,0,'%14')")
                      .arg(RecordNumber,TemplateName,ActualProductionVolume,DeliveryVehicle,TaskList,Engineering,FaHuoCustomer,PouringPosition)
                      .arg(Slump,PouringMethod,Driver,CumulativeVolume,CumulativeNumber,StrengthGrade);
            FMSmallTaskQuery->exec(insertSQL);
            if(FMSmallTaskQuery->lastError().isValid()){
                emit erroMessage(QString("补方任务传输失败（混凝土）\n")+insertSQL+"  "+FMSmallTaskQuery->lastError().text());
                FMSmallTaskQuery->clear();
                return;
            }else{
                QString deleteSQL = QString("delete from bufangReact where number='%1';").arg(bufangNo);
                db.sql_exec(deleteSQL);
                FMSmallTaskQuery->clear();
            }
        }
        /*混凝土任务结束*/

        //如果含有砂浆
        if(shajiang.toDouble() > 0){
            QString insertSQL = insertSQL = QString("insert into SmallTaskTable (c_UniqueMark,c_FormulaUniqueMark,d_CurrentCubics,c_VehicleUniqueMark,\
                                                    c_BigTaskUniqueMark,c_ProjectName,c_ClientName,c_ProjectPart,c_ProjectSlump,c_PouringType,\
                                                    c_Remark,c_BTI0,c_BTI1,c_BTI2,c_BTI3,c_BTI4,c_DriverUniqueMark,c_STI0,c_STI1,c_STI2,c_STI3,c_STI4,c_ContractCode,\
                                                    d_AccumulatedCubics,i_AccumulatedTrucks,i_WorkingState,c_ProjectStrength) values \
                          ('%1','%2',%3,'%4','%5','%6','%7','%8','%9','%10','','','','','','','%11','','','','','','',%12,%13,0,'%14')")
                                  .arg(RecordNumber,"砂浆",shajiang,DeliveryVehicle,TaskList,Engineering,FaHuoCustomer,PouringPosition)
                                  .arg(Slump,PouringMethod,Driver,CumulativeVolume,CumulativeNumber,StrengthGrade);
            FMSmallTaskQuery->exec(insertSQL);
            if(FMSmallTaskQuery->lastError().isValid()){
                emit erroMessage(QString("补方任务传输失败（砂浆）\n")+insertSQL+"  "+FMSmallTaskQuery->lastError().text());
                FMSmallTaskQuery->clear();
                return;
            }else{
                QString deleteSQL = QString("delete from bufangReact where number='%1'").arg(bufangNo);
                db.sql_exec(deleteSQL);
                FMSmallTaskQuery->clear();
            }
        }
        //砂浆任务结束
    }
}

void thread_sync::SANYsyncPhb(QString unitNo)
{
    QString searchPhbReact = QString("select RecipeID,RecipeName,Mat1,Mat2,Mat3,Mat4,Mat5,Mat6,Mat7,Mat8,Mat9,Mat10,Mat11,Mat12,Mat13,Mat14,Mat15,Mat16,Mat17,Mat18,\
                                      intensityLevel,state,jbTime,wushui from PhbReact where unit='%1'").arg(unitNo);
    QList<QStringList> list = db.sql_result(searchPhbReact.toStdString().data());
    for(int i = 0;i<list.size();i++){
        QString RecipeID = list.at(i).at(0);
        QString RecipeName = list.at(i).at(1);
        QString Mat1 = list.at(i).at(2);
        QString Mat2 = list.at(i).at(3);
        QString Mat3 = list.at(i).at(4);
        QString Mat4 = list.at(i).at(5);
        QString Mat5 = list.at(i).at(6);
        QString Mat6 = list.at(i).at(7);
        QString Mat7 = list.at(i).at(8);
        QString Mat8 = list.at(i).at(9);
        QString Mat9 = list.at(i).at(10);
        QString Mat10 = list.at(i).at(11);
        QString Mat11 = list.at(i).at(12);
        QString Mat12 = list.at(i).at(13);
        QString Mat13 = list.at(i).at(14);
        QString Mat14 = list.at(i).at(15);
        QString Mat15 = list.at(i).at(16);
        QString Mat16 = list.at(i).at(17);
        QString Mat17 = list.at(i).at(18);
        QString Mat18 = list.at(i).at(19);
        QString intensityLevel = list.at(i).at(20);
        QString state = list.at(i).at(21);
        QString jbTime = list.at(i).at(22);
        QString wushui = list.at(i).at(23);
        QStringList matList;
        matList<<Mat1<<Mat2<<Mat3<<Mat4<<Mat5<<Mat6<<Mat7<<Mat8<<Mat9<<Mat10<<Mat11<<Mat12<<Mat13<<Mat14<<Mat15<<Mat16<<Mat17<<Mat18;
        if(state == "insert" || state == "update"){
            QString deleteSQL = QString("delete from recipe where RecipeName='%1'").arg(RecipeName);
            SANYQuery->exec(deleteSQL);
            if(SANYQuery->lastError().isValid()){
                emit erroMessage(deleteSQL+SANYQuery->lastError().text());
                return;
            }

            QString insertSQL = QString("insert into recipe (RecipeID,intensityLevel,RecipeSN1,RecipeSN2,RecipeSN3,RecipeFMH,RecipeFJJ,RecipeKF,RecipeWJJ1,RecipeWJJ2,RecipeDSL,\
                                        RecipeZSL,RecipeXSL,RecipeSZ,RecipeSZ1,RecipeSHUI,RecipeOth1,RecipeOth2,RecipeSN4,RecipeSZ2,RecipeName) VALUES (%1,'%2',%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,\
                                        %13,%14,%15,%16,%17,%18,%19,%20,'%21')")
                    .arg(RecipeID,intensityLevel).arg(Mat1,Mat2,Mat3,Mat4,Mat5,Mat6,Mat7,Mat8,Mat9).arg(Mat10,Mat11,Mat12,Mat13,Mat14,jbTime,Mat16,Mat17,Mat18).arg(RecipeName);
            SANYQuery->exec(insertSQL);
            if(SANYQuery->lastError().isValid()){
                emit erroMessage(insertSQL+SANYQuery->lastError().text());
                return;
            }
        }

        else{
            QString deleteSQL = QString("delete from recipe where RecipeName='%1'").arg(RecipeName);
            SANYQuery->exec(deleteSQL);
            if(SANYQuery->lastError().isValid()){
                emit erroMessage(deleteSQL+SANYQuery->lastError().text());
                return;
            }
        }


        QString deleteSQL = QString("delete from PhbReact where unit='%1' and RecipeName='%2'").arg(unitNo,RecipeName);
        db.sql_exec(deleteSQL);
    }
}

void thread_sync::SANYsyncPeiFangKuTask()
{
    //获取需要传输的总任务列表
    QString searchID = QString("select taskID from taskListReact where unitID='%1' order by taskID").arg(PRODUCTUNITNO);
    QStringList taskListIDList = db.find_CheNo(searchID);
    QString taskListID;
    for(int i = 0; i < taskListIDList.count(); i++){
        taskListID.append(QString("'%1',").arg(taskListIDList.at(i)));
    }
    taskListID = taskListID.left(taskListID.length()-1);
    if(taskListID.isEmpty()){
        taskListID = "0";
    }

    QString searchSQL = QString("select TaskNumber,Template,PlannedQuantity,ContractCompletion,Slump,PouringPosition,Engineering,\
                                FaHuoCustomer,PouringMethod,CumulativeNumber,StrengthGrade,SupplyTime from ProductionTaskList \
                                where TaskNumber in (%1);").arg(taskListID);
    QList<QStringList> list = db.sql_result(searchSQL.toStdString().data());
    for(int i = 0;i<list.size();i++){
        //任务编号
        QString rwID = list.at(i).at(0);
        //配方名称
        QString PFname = list.at(i).at(1);
        //设定总方量
        QString GZsetCount = list.at(i).at(2);
        //累计方量
        QString GZfinishCount = list.at(i).at(3);
        //塌落度
        QString GZtaladu = list.at(i).at(4);
        //浇筑部位
        QString GZjzbw = list.at(i).at(5);
        //工程名称
        QString GZgcmc = list.at(i).at(6);
        //用户名称
        QString GZusername = list.at(i).at(7);
        //泵送情况
        QString GZbsqk = list.at(i).at(8);
        //累计车次
        QString GZleijicheci = list.at(i).at(9);
        //强度等级
        QString tdj = list.at(i).at(10);
        tdj.replace(" "+list.at(i).at(8),"").replace(" ","");
        //时间
        QString dateTime = list.at(i).at(11);

        //先删除任务
        QString deleterwSQL = QString("delete from Task where TaskName='%1'").arg(rwID);
        SANYQuery->exec(deleterwSQL);
        if(SANYQuery->lastError().isValid()){
            emit erroMessage(deleterwSQL+" "+SANYQuery->lastError().text());
            return;
        }

        //后插入任务
        QString searchID = QString("select top 1 TaskID from Task order by TaskID DESC");
        SANYQuery->exec(searchID);
        if(SANYQuery->lastError().isValid()){
            emit erroMessage(searchID+" "+SANYQuery->lastError().text()+"查找机组任务号失败");
            return;
        }
        SANYQuery->next();
        QString TaskID = QString::number(SANYQuery->value(0).toString().toInt()+1);
        QString insertSQL = QString("insert into Task (TaskID,TaskName,planDate,ProjectName,ProjectCmpy,RecipeNo,ProjectPart,WorkMethod,\
                                    ShipVia,Ustate) values (%1,'%2','%3','%4','%5','%6','%7','%8',0,1);")
                             .arg(TaskID,rwID,dateTime,GZgcmc,GZusername,PFname,GZjzbw,GZbsqk);
        SANYQuery->exec(insertSQL);
        if(SANYQuery->lastError().isValid()){
            emit erroMessage(insertSQL+" "+SANYQuery->lastError().text()+"总任务传输失败");
            return;
        }

        //删除taskReact表中的数据
        QString deleteSQL = QString("delete from taskListReact where taskID='%1' and unitID='%2'").arg(rwID,PRODUCTUNITNO);
        db.sql_exec(deleteSQL);
    }
}

void thread_sync::SANYsyncDcRw()
{
    QString searchSQL = QString("select RecordNum from SendProductNotice where Unit='%1' order by RecordNum+0 limit 1").arg(PRODUCTUNITNO);
    QString SendNum = db.sql_fetchrow_plus(searchSQL.toStdString().data(),0);
    if(SendNum.isEmpty()){
        SendNum = "0";
    }

    QString searchDcRw = QString("select RecordNumber,TaskList,DeliveryVehicle,Driver,ActualProductionVolume,ProductionTime,Engineering,StrengthGrade,TemplateName, \
                                 PouringMethod,VolumeMortar,FaHuoCustomer,PouringPosition,Slump,CumulativeNumber,CumulativeVolume from ProductionNotice where RecordNumber=%1 and Unit='%2#机组'").arg(SendNum,PRODUCTUNITNO);
    QList<QStringList> listNotice = db.sql_result(searchDcRw.toStdString().data());
    for(int i = 0;i<listNotice.size();i++){
        QString RecordNumber = listNotice.at(i).at(0);
        QString TaskList = listNotice.at(i).at(1);
        QString DeliveryVehicle = listNotice.at(i).at(2);
        QString Driver = listNotice.at(i).at(3);
        QString ActualProductionVolume = listNotice.at(i).at(4);
        QString scdate = listNotice.at(i).at(5);
        QString Engineering = listNotice.at(i).at(6);
        QString StrengthGrade = listNotice.at(i).at(7);
        StrengthGrade.replace(" "+listNotice.at(i).at(9),"").replace(" ","");
        QString TemplateName = listNotice.at(i).at(8);

        QString searchJBTime = QString("select JBTIME from rwPEIFANG where TaskList='%1' and StateNo='%2'").arg(TaskList,PRODUCTUNITNO);
        QString JBSJ = db.sql_fetchrow_plus(searchJBTime,0);
        if(JBSJ.isEmpty()){
            JBSJ = "0";
        }
        QString PouringMethod = listNotice.at(i).at(9);

        //砂浆
        QString shajiang = listNotice.at(i).at(10);
        QString FaHuoCustomer = listNotice.at(i).at(11);
        QString PouringPosition = listNotice.at(i).at(12);
        QString Slump = listNotice.at(i).at(13);
        QString CumulativeNumber = listNotice.at(i).at(14);
        QString CumulativeVolume = listNotice.at(i).at(15);


        //混凝土方量
        ActualProductionVolume = QString::number(ActualProductionVolume.toDouble()-shajiang.toDouble(),'f',1);

        //如果本车混凝土方量为0且砂浆方量为0，则跳过
        if(ActualProductionVolume.toDouble() <= 0 && shajiang.toDouble()<=0){
            QString deleteSQL = QString("delete from SendProductNotice where RecordNum='%1'").arg(RecordNumber);
            db.sql_exec(deleteSQL);
            return;
        }


        //混凝土
        if(ActualProductionVolume.toDouble() > 0){
            double plateCount = ActualProductionVolume.toDouble()/2;
            int count = ceil(plateCount);
            QString panshu = QString::number(count);
            QString StationName = QString("%1#搅拌站").arg(PRODUCTUNITNO);

            //查询DeliveryID
            QString searchOutMaster = QString("select top 1 DeliveryID from OutMaster order by DeliveryID DESC");
            SANYQuery->exec(searchOutMaster);
            if(SANYQuery->lastError().isValid()){
                emit erroMessage(searchOutMaster+" "+SANYQuery->lastError().text()+"查询DeliveryID失败");
                return;
            }
            SANYQuery->next();
            QString DeliveryID = QString::number(SANYQuery->value(0).toString().toInt()+1);
            //查询TaskID,RecipeNo
            QString searchTask = QString("select TaskID,RecipeNo from Task where TaskName='%1'").arg(TaskList);
            SANYQuery->exec(searchTask);
            if(SANYQuery->lastError().isValid()){
                emit erroMessage(searchTask+" "+SANYQuery->lastError().text()+"查询TaskID,RecipeNo失败");
                return;
            }
            SANYQuery->next();
            QString TaskID = SANYQuery->value(0).toString();
            QString RecipeNo = SANYQuery->value(1).toString();
            //查询recipeID
            QString searchRecipe = QString("select RecipeID from recipe where RecipeName='%1'").arg(RecipeNo);
            SANYQuery->exec(searchRecipe);
            if(SANYQuery->lastError().isValid()){
                emit erroMessage(searchRecipe+" "+SANYQuery->lastError().text()+"查询recipeID失败");
                return;
            }
            SANYQuery->next();
            QString RecipeID = SANYQuery->value(0).toString();

            QString insertOutMaster = QString("insert into OutMaster (DeliveryID,DeliveryName,DeliveryDate,TaskID,RecipeNo,Quantity,TruckID,\
                                              EmployeeID,ProjectCmpy,ProjectPart,StationName,EndCount,ProjectName,OutCount,reserve2,intensityLevel,\
                                              tld,WorkMethod,TaskName,ItemNo) values (%1,'%2','%3',%4,'%5',%6,'%7',2,'%8','%9','%10',%11,'%12',%13,'%14',\
                                              '%15','%16','%17','%18',%19)")
                                    .arg(DeliveryID).arg(TaskList,scdate).arg(TaskID).arg(RecipeNo).arg(ActualProductionVolume).arg(DeliveryVehicle).arg(FaHuoCustomer,PouringPosition,StationName)
                                    .arg(CumulativeVolume).arg(Engineering).arg(CumulativeNumber).arg(Driver,StrengthGrade,Slump,RecordNumber,TaskList,panshu);
            SANYQuery->exec(insertOutMaster);
            if(SANYQuery->lastError().isValid()){
                emit erroMessage(insertOutMaster+" "+SANYQuery->lastError().text()+"插入OutMaster失败");
                return;
            }

            QString insertCurOut = QString("insert into CurOut (OverID,StationID,EmployeeID,DeliveryID,RecipeID,Quantity,ItemNo,RecipeName,mDateTime) values \
                                           (1,1,1,%1,%2,%3,%4,'%5','%6')")
                                    .arg(DeliveryID,RecipeID,ActualProductionVolume,panshu).arg(RecipeNo,scdate);
            SANYQuery->exec(insertCurOut);
            if(SANYQuery->lastError().isValid()){
                emit erroMessage(insertCurOut+" "+SANYQuery->lastError().text()+"插入CurOut失败");
                return;
            }
        }


        if(shajiang.toDouble() > 0){
            double plateCount = shajiang.toDouble()/2;
            int count = ceil(plateCount);
            QString panshu = QString::number(count);
            QString StationName = QString("%1#搅拌站").arg(PRODUCTUNITNO);

            //查询DeliveryID
            QString searchOutMaster = QString("select top 1 DeliveryID from OutMaster order by DeliveryID DESC");
            SANYQuery->exec(searchOutMaster);
            if(SANYQuery->lastError().isValid()){
                emit erroMessage(searchOutMaster+" "+SANYQuery->lastError().text()+"查询DeliveryID失败（砂浆）");
                return;
            }
            SANYQuery->next();
            QString DeliveryID = QString::number(SANYQuery->value(0).toString().toInt()+1);
            //查询TaskID,RecipeNo
            QString searchTask = QString("select TaskID,RecipeNo from Task where TaskName='砂浆'");
            //QString searchTask = QString("select TaskID,RecipeNo from Task where TaskName='%1'").arg(TaskList);
            SANYQuery->exec(searchTask);
            if(SANYQuery->lastError().isValid()){
                emit erroMessage(searchTask+" "+SANYQuery->lastError().text()+"查询TaskID,RecipeNo失败（砂浆）");
                return;
            }
            SANYQuery->next();
            QString TaskID = SANYQuery->value(0).toString();
            QString RecipeNo = SANYQuery->value(1).toString();
            //查询recipeID
            QString searchRecipe = QString("select RecipeID from recipe where RecipeName='%1'").arg(RecipeNo);
            SANYQuery->exec(searchRecipe);
            if(SANYQuery->lastError().isValid()){
                emit erroMessage(searchRecipe+" "+SANYQuery->lastError().text()+"查询recipeID失败（砂浆）");
                return;
            }
            SANYQuery->next();
            QString RecipeID = SANYQuery->value(0).toString();

            QString insertOutMaster = QString("insert into OutMaster (DeliveryID,DeliveryName,DeliveryDate,TaskID,RecipeNo,Quantity,TruckID,\
                                              EmployeeID,ProjectCmpy,ProjectPart,StationName,EndCount,ProjectName,OutCount,reserve2,intensityLevel,\
                                              tld,WorkMethod,TaskName,ItemNo) values (%1,'%2','%3',%4,'%5',%6,'%7',2,'%8','%9','%10',%11,'%12',%13,'%14',\
                                              '%15','%16','%17','%18',%19);")
                            .arg(DeliveryID).arg("砂浆",scdate).arg(TaskID).arg(RecipeNo).arg(ActualProductionVolume).arg(DeliveryVehicle).arg(FaHuoCustomer,PouringPosition,StationName)
                            .arg(CumulativeVolume).arg(Engineering).arg(CumulativeNumber).arg(Driver,StrengthGrade,Slump,RecordNumber,"砂浆",panshu);

            SANYQuery->exec(insertOutMaster);
            if(SANYQuery->lastError().isValid()){
                emit erroMessage(insertOutMaster+" "+SANYQuery->lastError().text()+"插入insertOutMaster失败（砂浆）");
                return;
            }

//            QString insertCurOut = QString("insert into CurOut (OverID,StationID,EmployeeID,DeliveryID,RecipeID,Quantity,ItemNo,RecipeName,mDateTime,SZ2) values \
//                                           (1,1,1,%1,%2,%3,%4,'砂浆','%6',0)")
//                                    .arg(DeliveryID,RecipeID,shajiang,panshu).arg(scdate);
            QString insertCurOut = QString("insert into CurOut (OverID,StationID,EmployeeID,DeliveryID,RecipeID,Quantity,ItemNo,RecipeName,mDateTime) values \
                                           (1,1,1,%1,%2,%3,%4,'%5','%6')")
                                    .arg(DeliveryID,RecipeID,shajiang,panshu).arg(RecipeNo,scdate);
            SANYQuery->exec(insertCurOut);
            if(SANYQuery->lastError().isValid()){
                emit erroMessage(insertCurOut+" "+SANYQuery->lastError().text()+"插入insertCurOut失败（砂浆）");
                return;
            }
        }
        //砂浆任务结束


        QString deleteSQL = QString("delete from SendProductNotice where RecordNum='%1'").arg(RecordNumber);
        db.sql_exec(deleteSQL);
    }
}

void thread_sync::SANYdeleteDcRw()
{
    QString searchSQL = QString("select cheNo,cheTime,Unit,recordNo from productNoticeReact where Unit='%1#机组' order by recordNo+0 desc limit 1").arg(PRODUCTUNITNO);
    QStringList resList = db.CreatStrList(searchSQL);
    QString cheNo,cheTime,unit,recordNo;
    if(resList.count() == 4){
        cheNo = resList.at(0);
        cheTime = resList.at(1);
        unit = resList.at(2);
        unit = unit.left(1);
        recordNo = resList.at(3);
    }
    if(PRODUCTUNITNO == unit){
        QString deleteSQL = QString("delete CurOut from CurOut a,OutMaster b where a.DeliveryID = b.DeliveryID AND b.DeliveryDate = '%1' AND b.TruckID = '%2'").arg(cheTime,cheNo);
        SANYQuery->exec(deleteSQL);
        SANYQuery->clear();

        QString deleteSQL1 = QString("delete from productNoticeReact where cheNo='%1' and cheTime='%2'").arg(cheNo,cheTime);
        db.sql_exec(deleteSQL1.toStdString().data());
    }
}

void thread_sync::SANYsyncBuFangDcRw()
{
    QString search = QString("select number from bufangReact where unit='%1' limit 1").arg(PRODUCTUNITNO);
    QString bufangNo = db.sql_fetchrow_plus(search.toStdString().data(),0);
    if(bufangNo.isEmpty()){
        bufangNo = "0";
    }

    QString searchDcRw = QString("select select RecordNumber,TaskList,DeliveryVehicle,Driver,ActualProductionVolume,ProductionTime,Engineering,StrengthGrade,TemplateName, \
                                 PouringMethod,VolumeMortar,FaHuoCustomer,PouringPosition,Slump,CumulativeNumber,CumulativeVolume from bufangNotice where RecordNumber=%1 and \
                                 Unit='%2#机组' and WhetherDocument='是'").arg(bufangNo,PRODUCTUNITNO);
    QList<QStringList> listNotice = db.sql_result(searchDcRw.toStdString().data());
    for(int i = 0;i<listNotice.size();i++){
        QString RecordNumber = listNotice.at(i).at(0);
        QString TaskList = listNotice.at(i).at(1);
        QString DeliveryVehicle = listNotice.at(i).at(2);
        QString Driver = listNotice.at(i).at(3);
        QString ActualProductionVolume = listNotice.at(i).at(4);
        QString scdate = listNotice.at(i).at(5);
        QString Engineering = listNotice.at(i).at(6);
        QString StrengthGrade = listNotice.at(i).at(7);
        StrengthGrade.replace(" "+listNotice.at(i).at(9),"").replace(" ","");
        QString TemplateName = listNotice.at(i).at(8);

        QString searchJBTime = QString("select JBTIME from rwPEIFANG where TaskList='%1' and StateNo='%2'").arg(TaskList,PRODUCTUNITNO);
        QString JBSJ = db.sql_fetchrow_plus(searchJBTime,0);
        if(JBSJ.isEmpty()){
            JBSJ = "0";
        }
        QString PouringMethod = listNotice.at(i).at(9);

        //砂浆
        QString shajiang = listNotice.at(i).at(10);
        QString FaHuoCustomer = listNotice.at(i).at(11);
        QString PouringPosition = listNotice.at(i).at(12);
        QString Slump = listNotice.at(i).at(13);
        QString CumulativeNumber = listNotice.at(i).at(14);
        QString CumulativeVolume = listNotice.at(i).at(15);

        //混凝土方量
        ActualProductionVolume = QString::number(ActualProductionVolume.toDouble()-shajiang.toDouble(),'f',1);

        double plateCount = ActualProductionVolume.toDouble()/2;
        int count = ceil(plateCount);
        QString panshu = QString::number(count);
        QString StationName = QString("%1#搅拌站").arg(PRODUCTUNITNO);

        //混凝土任务开始
        if(ActualProductionVolume.toDouble() >= 0.4){
            //查询DeliveryID
            QString searchOutMaster = QString("select top 1 DeliveryID from OutMaster order by DeliveryID DESC");
            SANYQuery->exec(searchOutMaster);
            if(SANYQuery->lastError().isValid()){
                emit erroMessage(searchOutMaster+" "+SANYQuery->lastError().text()+"补方查询DeliveryID失败");
                return;
            }
            SANYQuery->next();
            QString DeliveryID = QString::number(SANYQuery->value(0).toString().toInt()+1);
            //查询TaskID,RecipeNo
            QString searchTask = QString("select TaskID,RecipeNo from Task where TaskName='%1'").arg(TaskList);
            SANYQuery->exec(searchTask);
            if(SANYQuery->lastError().isValid()){
                emit erroMessage(searchTask+" "+SANYQuery->lastError().text()+"补方查询TaskID,RecipeNo失败");
                return;
            }
            SANYQuery->next();
            QString TaskID = SANYQuery->value(0).toString();
            QString RecipeNo = SANYQuery->value(1).toString();
            //查询recipeID
            QString searchRecipe = QString("select RecipeID from recipe where RecipeName='%1'").arg(RecipeNo);
            SANYQuery->exec(searchRecipe);
            if(SANYQuery->lastError().isValid()){
                emit erroMessage(searchRecipe+" "+SANYQuery->lastError().text()+"补方查询recipeID失败");
                return;
            }
            SANYQuery->next();
            QString RecipeID = SANYQuery->value(0).toString();


            QString insertOutMaster = QString("insert into OutMaster (DeliveryID,DeliveryName,DeliveryDate,TaskID,RecipeNo,Quantity,TruckID,\
                                              EmployeeID,ProjectCmpy,ProjectPart,StationName,EndCount,ProjectName,OutCount,reserve2,intensityLevel,\
                                              tld,WorkMethod,TaskName,ItemNo) values (%1,'%2','%3',%4,'%5',%6,'%7',2,'%8','%9','%10',%11,'%12',%13,'%14',\
                                              '%15','%16','%17','%18',%19);")
                        .arg(DeliveryID).arg(TaskList,scdate).arg(TaskID).arg(RecipeNo).arg(ActualProductionVolume).arg(DeliveryVehicle).arg(FaHuoCustomer,PouringPosition,StationName)
                        .arg(CumulativeVolume).arg(Engineering).arg(CumulativeNumber).arg(Driver,StrengthGrade,Slump,RecordNumber,TaskList,panshu);
            SANYQuery->exec(insertOutMaster);
            if(SANYQuery->lastError().isValid()){
                emit erroMessage(insertOutMaster+" "+SANYQuery->lastError().text()+"补方混凝土任务传输失败");
                return;
            }

            QString insertCurOut = QString("insert into CurOut (StationID,EmployeeID,DeliveryID,RecipeID,Quantity,ItemNo,RecipeName,mDateTime) values \
                                           (%1,%2,%3,%4,%5,%6,'%7','%8')")
                                    .arg(1).arg(1).arg(DeliveryID,RecipeID,ActualProductionVolume,panshu).arg(RecipeNo,scdate);
            SANYQuery->exec(insertCurOut);
            if(SANYQuery->lastError().isValid()){
                emit erroMessage(insertCurOut+" "+SANYQuery->lastError().text()+"补方混凝土任务传输失败");
                return;
            }

            //删除补方中间表记录
            QString deleteSQL = QString("delete from bufangReact where number='%1';").arg(bufangNo);
            db.sql_exec(deleteSQL);
        }
        /*混凝土任务结束*/


        //如果该单车任务含有砂浆
        if(shajiang.toDouble() > 0){
            double plateCount = shajiang.toDouble()/3;
            int count = ceil(plateCount);
            QString panshu = QString::number(count);

            //查询DeliveryID
            QString searchOutMaster = QString("select top 1 DeliveryID from OutMaster order by DeliveryID DESC");
            SANYQuery->exec(searchOutMaster);
            if(SANYQuery->lastError().isValid()){
                emit erroMessage(searchOutMaster+" "+SANYQuery->lastError().text()+"补方查询DeliveryID失败（砂浆）");
                return;
            }
            SANYQuery->next();
            QString DeliveryID = QString::number(SANYQuery->value(0).toString().toInt()+1);
            //查询TaskID,RecipeNo
            QString searchTask = QString("select TaskID,RecipeNo from Task where TaskName='砂浆'");
            SANYQuery->exec(searchTask);
            if(SANYQuery->lastError().isValid()){
                emit erroMessage(searchTask+" "+SANYQuery->lastError().text()+"补方查询TaskID,RecipeNo失败（砂浆）");
                return;
            }
            SANYQuery->next();
            QString TaskID = SANYQuery->value(0).toString();
            QString RecipeNo = SANYQuery->value(1).toString();
            //查询recipeID
            QString searchRecipe = QString("select RecipeID from recipe where RecipeName='%1'").arg(RecipeNo);
            SANYQuery->exec(searchRecipe);
            if(SANYQuery->lastError().isValid()){
                emit erroMessage(searchRecipe+" "+SANYQuery->lastError().text()+"补方查询recipeID失败（砂浆）");
                return;
            }
            SANYQuery->next();
            QString RecipeID = SANYQuery->value(0).toString();

            QString insertOutMaster = QString("insert into OutMaster (DeliveryID,DeliveryName,DeliveryDate,TaskID,RecipeNo,Quantity,TruckID,\
                                              EmployeeID,ProjectCmpy,ProjectPart,StationName,EndCount,ProjectName,OutCount,reserve2,intensityLevel,\
                                              tld,WorkMethod,TaskName,ItemNo) values (%1,'%2','%3',%4,'%5',%6,'%7',2,'%8','%9','%10',%11,'%12',%13,'%14',\
                                              '%15','%16','%17','%18',%19)")
                    .arg(DeliveryID).arg("砂浆",scdate).arg(TaskID).arg(RecipeNo).arg(ActualProductionVolume).arg(DeliveryVehicle).arg(FaHuoCustomer,PouringPosition,StationName)
                    .arg(CumulativeVolume).arg(Engineering).arg(CumulativeNumber).arg(Driver,StrengthGrade,Slump,RecordNumber,"砂浆",panshu);
            SANYQuery->exec(insertOutMaster);
            if(SANYQuery->lastError().isValid()){
                emit erroMessage(insertOutMaster+" "+SANYQuery->lastError().text()+"补方砂浆任务传输失败");
                return;
            }

            QString insertCurOut = QString("insert into CurOut (StationID,EmployeeID,DeliveryID,RecipeID,Quantity,ItemNo,RecipeName,mDateTime) values \
                                           (%1,%2,%3,%4,%5,%6,'%7','%8')")
                                    .arg(1).arg(1).arg(DeliveryID,RecipeID,shajiang,panshu).arg(RecipeNo,scdate);
            SANYQuery->exec(insertCurOut);
            if(SANYQuery->lastError().isValid()){
                emit erroMessage(insertCurOut+" "+SANYQuery->lastError().text()+"补方砂浆任务传输失败");
                return;
            }

            //删除补方中间表记录
            QString deleteSQL = QString("delete from bufangReact where number='%1';").arg(bufangNo);
            db.sql_exec(deleteSQL);
        }
        //砂浆任务结束
    }
}

void thread_sync::SANYRunState()
{
    QString unitNo = PRODUCTUNITNO;
    QString searchDcRwTabSQL = QString("SELECT a.DeliveryID,b.WorkMethod,a.Quantity,a.ItemNo FROM CurOut a LEFT OUTER JOIN (SELECT DeliveryID, WorkMethod FROM OutMaster) b ON a.DeliveryID = b.DeliveryID");
    SANYQuery->exec(searchDcRwTabSQL);

    qDebug()<<"run_1620";

    while (SANYQuery->next()) {

    qDebug()<<"run_1624";


        QString DJBH = SANYQuery->value(1).toString();//bsqk
        QString TotalVolume = SANYQuery->value(2).toString();//8方
        QString TotalPanshu = SANYQuery->value(3).toString();//盘数

        QString searchHISTDATAsql = QString("SELECT count(1),SUM(SUMPS) FROM HISTDATA WHERE bsqk='%1'").arg(DJBH);
        QString panshu = db.sql_fetchrow_plus(searchHISTDATAsql,0);//1
        QString volume = db.sql_fetchrow_plus(searchHISTDATAsql,1);//2
        qDebug()<<"panshu"<<panshu;

        if(panshu.toInt()!=0)
        {
            QString updateMySQL = QString("update ProductionNotice set Confirmor='是' where RecordNumber=%1").arg(DJBH);
            db.sql_exec(updateMySQL.toStdString().data());

            QString insertMySQL = QString("replace into RunStateTab (recordNo,panshu,volume,unitNo) values ('%1','%2','%3','%4');").arg(DJBH,panshu,volume,unitNo);
            db.sql_exec(insertMySQL.toStdString().data());
        }
    }



    QString searchMySQLRunState = QString("select recordNo from RunStateTab where unitNo='%1'").arg(unitNo);
    QStringList recordList = db.find_CheNo(searchMySQLRunState);
    for(int i = 0; i<recordList.count(); i++){
        QString searchSQL = QString("SELECT a.DeliveryID, b.WorkMethod,a.Quantity FROM CurOut a LEFT OUTER JOIN (SELECT DeliveryID, WorkMethod FROM OutMaster) b ON a.DeliveryID = b.DeliveryID where b.WorkMethod='%1' ").arg(recordList.at(i));
        SANYQuery->exec(searchSQL.toStdString().data());
        if(!SANYQuery->next()){
            //删除相关生产状态表中的记录
            QString deleteSQL = QString("delete from RunStateTab where recordNo='%1'").arg(recordList.at(i));
            db.sql_exec(deleteSQL.toStdString().data());
            //删除车辆队列
            QString deleteVehicle = QString("delete from inHouseVehicle where CheNo=(select DeliveryVehicle from ProductionNotice where RecordNumber=%1)").arg(recordList.at(i));
            db.sql_exec(deleteVehicle);
        }
    }

}

void thread_sync::ZLsyncStdPhb(QString unitNo)
{
    QString searchPhbReact = QString("select RecipeID,RecipeName,Mat1,Mat2,Mat3,Mat4,Mat5,Mat6,Mat7,Mat8,Mat9,Mat10,Mat11,Mat12,Mat13,Mat14,Mat15,Mat16,Mat17,Mat18,\
                                      Mat19,Mat20,Mat21,Mat22,Mat23,Mat24,intensityLevel,state,jbTime,wushui from PhbReact where unit='%1'").arg(unitNo);
    QList<QStringList> list = db.sql_result(searchPhbReact);
    for(int i = 0;i<list.size();i++){
        QString RecipeID = list.at(i).at(0);
        QString RecipeName = list.at(i).at(1);
        QString Mat1 = list.at(i).at(2);
        QString Mat2 = list.at(i).at(3);
        QString Mat3 = list.at(i).at(4);
        QString Mat4 = list.at(i).at(5);
        QString Mat5 = list.at(i).at(6);
        QString Mat6 = list.at(i).at(7);
        QString Mat7 = list.at(i).at(8);
        QString Mat8 = list.at(i).at(9);
        QString Mat9 = list.at(i).at(10);
        QString Mat10 = list.at(i).at(11);
        QString Mat11 = list.at(i).at(12);
        QString Mat12 = list.at(i).at(13);
        QString Mat13 = list.at(i).at(14);
        QString Mat14 = list.at(i).at(15);
        QString Mat15 = list.at(i).at(16);
        QString Mat16 = list.at(i).at(17);
        QString Mat17 = list.at(i).at(18);
        QString Mat18 = list.at(i).at(19);
        QString Mat19 = list.at(i).at(20);
        QString Mat20 = list.at(i).at(21);
        QString Mat21 = list.at(i).at(22);
        QString Mat22 = list.at(i).at(23);
        QString Mat23 = list.at(i).at(24);
        QString Mat24 = list.at(i).at(25);
        QString intensityLevel = list.at(i).at(26);
        QString state = list.at(i).at(27);
        QString jbTime = list.at(i).at(28);
        QString wushui = list.at(i).at(29);
        QStringList matList;
        matList<<Mat1<<Mat2<<Mat3<<Mat4<<Mat5<<Mat6<<Mat7<<Mat8<<Mat9<<Mat10<<Mat11<<Mat12<<Mat13<<Mat14<<Mat15<<Mat16<<Mat17<<Mat18<<Mat19<<Mat20<<Mat21<<Mat22<<Mat23<<Mat24;
        double Volume = 0;
        for(int i = 0; i < matList.count(); i++){
            Volume += matList.at(i).toDouble();
        }

        if(state == "insert" || state == "update"){
            //先删除
            QString deleteFormulaSQL = QString("delete from FormulaStandard where ID='%1'").arg(RecipeID);
            ZOOMLIONQuery->exec(deleteFormulaSQL);
            if(ZOOMLIONQuery->lastError().isValid()){
                emit erroMessage(deleteFormulaSQL+ZOOMLIONQuery->lastError().text());
                return;
            }
            QString deleteFormulaItemSQL = QString("delete from FormulaStandardItems where FormulaStandardID='%1'").arg(RecipeID);
            ZOOMLIONQuery->exec(deleteFormulaItemSQL);
            if(ZOOMLIONQuery->lastError().isValid()){
                emit erroMessage(deleteFormulaItemSQL+ZOOMLIONQuery->lastError().text());
                return;
            }

            //后插入
            QString insertFormulaStandardSQL = QString("insert into FormulaStandard (ID,ConcreteStrength,FormulaMsgNo,MixingTime,ProductLineID,Volume,XZBool,XZRecord,Version,Status) VALUES (%1,'%2','%3',%4,'00000001',%5,0,'',1,0)")
                    .arg(RecipeID,intensityLevel,RecipeName,jbTime,QString::number(Volume));
            ZOOMLIONQuery->exec(insertFormulaStandardSQL);
            if(ZOOMLIONQuery->lastError().isValid()){
                emit erroMessage(insertFormulaStandardSQL+ZOOMLIONQuery->lastError().text());
                return;
            }

            QString searchFiledSQL = QString("select CorrespondingField from UnitMaterialSetting where SubordinateUnit='%1#机组' order by CorrespondingField+0").arg(unitNo);
            QStringList FieldList = db.find_CheNo(searchFiledSQL);

            for(int i = 0; i < FieldList.count(); i++){
                QString SiloID = QString("").sprintf("%08d",FieldList.at(i).toInt()+1000000);
                QString StuffID = QString("").sprintf("%08d",FieldList.at(i).toInt());
                QString insertFormulaStandardItemsSQL = QString("insert into FormulaStandardItems (FormulaStandardID,SiloID,StuffID,TypeAmount,Version,Status,MinAmount,MaxAmount) VALUES ('%1','%2','%3',%4,1,0,%4,%4)")
                        .arg(RecipeID,SiloID,StuffID,matList.at(FieldList.at(i).toInt()-1));
                ZOOMLIONQuery->exec(insertFormulaStandardItemsSQL);
                if(ZOOMLIONQuery->lastError().isValid()){
                    emit erroMessage(insertFormulaStandardItemsSQL+ZOOMLIONQuery->lastError().text());
                    return;
                }
            }

            if(RecipeID == "999"){
                //先删除
                QString deleteFormulaSQL = QString("delete from FormulaReference where ID='%1'").arg(RecipeID);
                ZOOMLIONQuery->exec(deleteFormulaSQL);
                if(ZOOMLIONQuery->lastError().isValid()){
                    emit erroMessage(deleteFormulaSQL+ZOOMLIONQuery->lastError().text());
                    return;
                }
                QString deleteFormulaItemSQL = QString("delete from FormulaReferenceItems where FormulaReferenceID='%1'").arg(RecipeID);
                ZOOMLIONQuery->exec(deleteFormulaItemSQL);
                if(ZOOMLIONQuery->lastError().isValid()){
                    emit erroMessage(deleteFormulaItemSQL+ZOOMLIONQuery->lastError().text());
                    return;
                }

                //后插入
                QString insertFormulaStandardSQL = QString("insert into FormulaReference (ID,ConcreteStrength,FormulaMsgNo,MixingTime,ProductLineID,Volume,XZBool,XZRecord,Version,Status) VALUES (%1,'%2','%3',%4,'00000001',%5,0,'',1,0)")
                        .arg(RecipeID,intensityLevel,RecipeName,jbTime,QString::number(Volume));
                ZOOMLIONQuery->exec(insertFormulaStandardSQL);
                if(ZOOMLIONQuery->lastError().isValid()){
                    emit erroMessage(insertFormulaStandardSQL+ZOOMLIONQuery->lastError().text());
                    return;
                }

                QString searchFiledSQL = QString("select CorrespondingField from UnitMaterialSetting where SubordinateUnit='%1#机组' order by CorrespondingField+0").arg(unitNo);
                QStringList FieldList = db.find_CheNo(searchFiledSQL);

                for(int i = 0; i < FieldList.count(); i++){
                    QString SiloID = QString("").sprintf("%08d",FieldList.at(i).toInt()+1000000);
                    QString StuffID = QString("").sprintf("%08d",FieldList.at(i).toInt());
                    QString insertFormulaStandardItemsSQL = QString("insert into FormulaReferenceItems (FormulaReferenceID,SiloID,StuffID,TypeAmount,Version,Status) VALUES ('%1','%2','%3',%4,1,0)")
                            .arg(RecipeID,SiloID,StuffID,matList.at(FieldList.at(i).toInt()-1));
                    ZOOMLIONQuery->exec(insertFormulaStandardItemsSQL);
                    if(ZOOMLIONQuery->lastError().isValid()){
                        emit erroMessage(insertFormulaStandardItemsSQL+ZOOMLIONQuery->lastError().text());
                        return;
                    }
                }
            }
        }
        else{
            //删除
            QString deleteFormulaSQL = QString("delete from FormulaStandard where ID='%1'").arg(RecipeID);
            ZOOMLIONQuery->exec(deleteFormulaSQL);
            if(ZOOMLIONQuery->lastError().isValid()){
                emit erroMessage(deleteFormulaSQL+ZOOMLIONQuery->lastError().text());
                return;
            }

            QString deleteFormulaItemSQL = QString("delete from FormulaStandardItems where FormulaStandardID='%1'").arg(RecipeID);
            ZOOMLIONQuery->exec(deleteFormulaItemSQL);
            if(ZOOMLIONQuery->lastError().isValid()){
                emit erroMessage(deleteFormulaItemSQL+ZOOMLIONQuery->lastError().text());
                return;
            }

            if(RecipeID == "999"){
                //先删除
                QString deleteFormulaSQL = QString("delete from FormulaReference where ID='%1'").arg(RecipeID);
                ZOOMLIONQuery->exec(deleteFormulaSQL);
                if(ZOOMLIONQuery->lastError().isValid()){
                    emit erroMessage(deleteFormulaSQL+ZOOMLIONQuery->lastError().text());
                    return;
                }
                QString deleteFormulaItemSQL = QString("delete from FormulaReferenceItems where FormulaReferenceID='%1'").arg(RecipeID);
                ZOOMLIONQuery->exec(deleteFormulaItemSQL);
                if(ZOOMLIONQuery->lastError().isValid()){
                    emit erroMessage(deleteFormulaItemSQL+ZOOMLIONQuery->lastError().text());
                    return;
                }
            }
        }

        QString deleteSQL = QString("delete from PhbReact where unit='%1' and RecipeName='%2'").arg(unitNo,RecipeName);
        db.sql_exec(deleteSQL);
    }
}

void thread_sync::ZLsyncRwPhb(QString TaskList)
{
    QString searchPhbReact = QString("select TaskList,JBTIME,Mat1,Mat2,Mat3,Mat4,Mat5,Mat6,Mat7,Mat8,Mat9,Mat10,Mat11,Mat12,Mat13,Mat14,Mat15,Mat16,Mat17,Mat18,\
                                      Mat19,Mat20,Mat21,Mat22,Mat23,Mat24 from rwPEIFANG where StateNo='%1' and TaskList='%2'").arg(PRODUCTUNITNO,TaskList);
    QList<QStringList> list = db.sql_result(searchPhbReact);
    for(int i = 0;i<list.size();i++){
        QString RecipeID = list.at(i).at(0);
        QString jbTime = list.at(i).at(1);
        QString Mat1 = list.at(i).at(2);
        QString Mat2 = list.at(i).at(3);
        QString Mat3 = list.at(i).at(4);
        QString Mat4 = list.at(i).at(5);
        QString Mat5 = list.at(i).at(6);
        QString Mat6 = list.at(i).at(7);
        QString Mat7 = list.at(i).at(8);
        QString Mat8 = list.at(i).at(9);
        QString Mat9 = list.at(i).at(10);
        QString Mat10 = list.at(i).at(11);
        QString Mat11 = list.at(i).at(12);
        QString Mat12 = list.at(i).at(13);
        QString Mat13 = list.at(i).at(14);
        QString Mat14 = list.at(i).at(15);
        QString Mat15 = list.at(i).at(16);
        QString Mat16 = list.at(i).at(17);
        QString Mat17 = list.at(i).at(18);
        QString Mat18 = list.at(i).at(19);
        QString Mat19 = list.at(i).at(20);
        QString Mat20 = list.at(i).at(21);
        QString Mat21 = list.at(i).at(22);
        QString Mat22 = list.at(i).at(23);
        QString Mat23 = list.at(i).at(24);
        QString Mat24 = list.at(i).at(25);

        QString searchTaskInfo = QString("select Template,StrengthGrade from ProductionTaskList where TaskNumber='%1'").arg(RecipeID);
        QStringList resList = db.CreatStrList(searchTaskInfo);
        if(resList.count() != 2){
            return;
        }
        QString RecipeName = resList.at(0);
        QString intensityLevel = resList.at(1);


        QStringList matList;
        matList<<Mat1<<Mat2<<Mat3<<Mat4<<Mat5<<Mat6<<Mat7<<Mat8<<Mat9<<Mat10<<Mat11<<Mat12<<Mat13<<Mat14<<Mat15<<Mat16<<Mat17<<Mat18<<Mat19<<Mat20<<Mat21<<Mat22<<Mat23<<Mat24;
        double Volume = 0;
        for(int i = 0; i < matList.count(); i++){
            Volume += matList.at(i).toDouble();
        }

        //先删除
//        QString deleteFormulaSQL = QString("delete from FormulaReference where ID='%1'").arg(RecipeID);
//        ZOOMLIONQuery->exec(deleteFormulaSQL);
//        if(ZOOMLIONQuery->lastError().isValid()){
//            emit erroMessage(deleteFormulaSQL+ZOOMLIONQuery->lastError().text());
//            return;
//        }
        QString deleteFormulaItemSQL = QString("delete from FormulaReferenceItems where FormulaReferenceID='%1'").arg(RecipeID);
        ZOOMLIONQuery->exec(deleteFormulaItemSQL);
        if(ZOOMLIONQuery->lastError().isValid()){
            emit erroMessage(deleteFormulaItemSQL+ZOOMLIONQuery->lastError().text());
            return;
        }

        //后插入
        QString insertFormulaStandardSQL = QString("insert into FormulaReference (ID,ConcreteStrength,FormulaMsgNo,MixingTime,ProductLineID,Volume,XZBool,XZRecord,Version,Status) VALUES (%1,'%2','%3',%4,'00000001',%5,0,'',1,0)")
                .arg(RecipeID,intensityLevel,RecipeName,jbTime,QString::number(Volume));
        ZOOMLIONQuery->exec(insertFormulaStandardSQL);
        if(ZOOMLIONQuery->lastError().isValid()){
            if(ZOOMLIONQuery->lastError().text().contains("插入重复键")){
                QString insertFormulaStandardSQL = QString("update FormulaReference set ConcreteStrength='%1',FormulaMsgNo='%2',MixingTime=%3,Volume=%4 where ID='%5'")
                        .arg(intensityLevel,RecipeName,jbTime,QString::number(Volume),RecipeID);
                ZOOMLIONQuery->exec(insertFormulaStandardSQL);
                if(ZOOMLIONQuery->lastError().isValid()){
                    emit erroMessage(insertFormulaStandardSQL+ZOOMLIONQuery->lastError().text());
                    return;
                }
            }else{
                emit erroMessage(insertFormulaStandardSQL+ZOOMLIONQuery->lastError().text());
                return;
            }
        }

        QString searchFiledSQL = QString("select CorrespondingField from UnitMaterialSetting where SubordinateUnit='%1#机组' order by CorrespondingField+0").arg(PRODUCTUNITNO);
        QStringList FieldList = db.find_CheNo(searchFiledSQL);

        for(int i = 0; i < FieldList.count(); i++){
            QString SiloID = QString("").sprintf("%08d",FieldList.at(i).toInt()+1000000);
            QString StuffID = QString("").sprintf("%08d",FieldList.at(i).toInt());
            QString insertFormulaStandardItemsSQL = QString("insert into FormulaReferenceItems (FormulaReferenceID,SiloID,StuffID,TypeAmount,Version,Status) VALUES ('%1','%2','%3',%4,1,0)")
                    .arg(RecipeID,SiloID,StuffID,matList.at(FieldList.at(i).toInt()-1));
            ZOOMLIONQuery->exec(insertFormulaStandardItemsSQL);
            if(ZOOMLIONQuery->lastError().isValid()){
                emit erroMessage(insertFormulaStandardItemsSQL+ZOOMLIONQuery->lastError().text());
                return;
            }
        }
    }
}

void thread_sync::ZLsyncRenWuKuTask()
{
    //获取需要传输的总任务列表
    QString searchID = QString("select taskID from taskListReact where unitID='%1' order by taskID").arg(PRODUCTUNITNO);
    QStringList taskListIDList = db.find_CheNo(searchID);
    QString taskListID;
    for(int i = 0; i < taskListIDList.count(); i++){
        taskListID.append(QString("'%1',").arg(taskListIDList.at(i)));
    }
    taskListID = taskListID.left(taskListID.length()-1);
    if(taskListID.isEmpty()){
        taskListID = "0";
    }

    QString searchSQL = QString("select TaskNumber,Template,PlannedQuantity,ContractCompletion,Slump,PouringPosition,Engineering,\
                                FaHuoCustomer,PouringMethod,CumulativeNumber,StrengthGrade,SupplyTime from ProductionTaskList \
                                where TaskNumber in (%1);").arg(taskListID);
    QList<QStringList> list = db.sql_result(searchSQL.toStdString().data());
    for(int i = 0;i<list.size();i++){
        //任务编号
        QString rwID = list.at(i).at(0);
        //配方名称
        QString PFname = list.at(i).at(1);
        //配方编号
        QString searchPfID = QString("select IDENT from PEIFANG%1 where PhbNumber='%2'").arg(PRODUCTUNITNO,PFname);
        QString PFID = db.sql_fetchrow_plus(searchPfID,0);
        //设定总方量
        QString GZsetCount = list.at(i).at(2);
        //累计方量
        QString GZfinishCount = list.at(i).at(3);
        //塌落度
        QString GZtaladu = list.at(i).at(4);
        //浇筑部位
        QString GZjzbw = list.at(i).at(5);
        //工程名称
        QString ProjectName = list.at(i).at(6);
        //客户名称
        QString CustomerName = list.at(i).at(7);
        //泵送情况
        QString GZbsqk = list.at(i).at(8);
        //累计车次
        QString GZleijicheci = list.at(i).at(9);
        //强度等级
        QString StrengthGrade = list.at(i).at(10);
        StrengthGrade.replace(" "+list.at(i).at(8),"").replace(" ","");
        //时间
        QString SupplyTime = list.at(i).at(11);

        //客户ID
        QString searchCustomerID = QString("select TOP 1 ID from Customers ORDER BY ID DESC");
        ZOOMLIONQuery->exec(searchCustomerID);
        ZOOMLIONQuery->next();
        QString CustomerNumber = ZOOMLIONQuery->value(0).toString();
        qDebug()<<"CustomerNumber"<<CustomerNumber;
        CustomerNumber = QString("").sprintf("%08d",CustomerNumber.toInt()+1);
        qDebug()<<"CustomerNumber"<<CustomerNumber;

        //插入客户表
        QString insertCustomerSQL = QString("insert into Customers (ID,CustomerName,Version,CreateTime,Status) values ('%1','%2',%3,'%4',%5)")
                .arg(CustomerNumber,CustomerName,"1",SupplyTime,"0");
        ZOOMLIONQuery->exec(insertCustomerSQL);
        if(ZOOMLIONQuery->lastError().isValid()){
            emit erroMessage(insertCustomerSQL+ZOOMLIONQuery->lastError().text());
            return;
        }

        //工程ID
        QString searchProjectSQL = QString("select TOP 1 ID from Project ORDER BY ID DESC");
        ZOOMLIONQuery->exec(searchProjectSQL);
        ZOOMLIONQuery->next();
        QString ProjectNumber = ZOOMLIONQuery->value(0).toString();
        ProjectNumber = QString("").sprintf("%08d",ProjectNumber.toInt()+1);

        //插入工程
        QString insertProjectSQL = QString("insert into Project (ID,CustomersID,ProjectName,Status,Version) values ('%1','%2','%3',0,1)").arg(ProjectNumber,CustomerNumber,ProjectName);
        ZOOMLIONQuery->exec(insertProjectSQL);
        if(ZOOMLIONQuery->lastError().isValid()){
            emit erroMessage(insertProjectSQL+ZOOMLIONQuery->lastError().text());
            return;
        }

//        QString deleteSQL = QString("delete from PTaskList where ID='%1'").arg(rwID);
//        ZOOMLIONQuery->exec(deleteSQL);
//        if(ZOOMLIONQuery->lastError().isValid()){
//            emit erroMessage(deleteSQL+ZOOMLIONQuery->lastError().text());
//            return;
//        }

        QString insertSQL = QString("insert into PTaskList (ID,PTaskListNo,ProjectID,ConstructTime,ConstructPlace,RequiredNum,ProvidedNum,SumCarNum,PouringMode,\
                                    ConcreteStrength,Sink,status,Version,CreateTime) values ('%1','%2','%3','%4','%5',%6,%7,%8,'%9','%10','%11',%12,%13,'%14')")
                .arg(rwID,rwID,ProjectNumber,SupplyTime.left(10),GZjzbw,GZsetCount,GZfinishCount,GZleijicheci,GZbsqk)
                .arg(StrengthGrade,GZtaladu,"0","1",SupplyTime);
        ZOOMLIONQuery->exec(insertSQL);
        if(ZOOMLIONQuery->lastError().isValid()){
            if(ZOOMLIONQuery->lastError().text().contains("插入重复键")){
                QString updateSQL = QString("update PTaskList set PTaskListNo='%1',ProjectID='%2',ConstructTime='%3',ConstructPlace='%4',RequiredNum=%5,ProvidedNum=%6,SumCarNum=%7,PouringMode='%8',\
                                            ConcreteStrength='%9',Sink='%10',status=%11,Version=%12,CreateTime='%13' where ID='%14'")
                        .arg(rwID,ProjectNumber,SupplyTime.left(10),GZjzbw,GZsetCount,GZfinishCount,GZleijicheci,GZbsqk)
                        .arg(StrengthGrade,GZtaladu,"0","1",SupplyTime,rwID);
                ZOOMLIONQuery->exec(updateSQL);
                if(ZOOMLIONQuery->lastError().isValid()){
                    emit erroMessage(updateSQL+ZOOMLIONQuery->lastError().text());
                    return;
                }
            }else{
                emit erroMessage(insertSQL+ZOOMLIONQuery->lastError().text());
                return;
            }

        }

        QString deleteTaskFormulaSQL = QString("delete from PTaskFormula where PTaskListID='%1'").arg(rwID);
        ZOOMLIONQuery->exec(deleteTaskFormulaSQL);
        if(ZOOMLIONQuery->lastError().isValid()){
            emit erroMessage(deleteTaskFormulaSQL+ZOOMLIONQuery->lastError().text());
            return;
        }

        QString insertTaskFormulaSQL = QString("insert into PTaskFormula (PTaskListID,ProductLineID,FormulaStdConID,FormulaStdMorID,Version,CreateTime,Status,FormulaConID,FormulaMorID) values ('%1','%2','%3','%4',%5,'%6',%7,%8,%9)")
                .arg(rwID,"00000001",PFID,"999","0",SupplyTime,"0",rwID,"999");
        ZOOMLIONQuery->exec(insertTaskFormulaSQL);
        if(ZOOMLIONQuery->lastError().isValid()){
            emit erroMessage(insertTaskFormulaSQL+ZOOMLIONQuery->lastError().text());
            return;
        }

        ZLsyncRwPhb(rwID);

        //删除taskReact表中的数据
        QString deleteReactSQL = QString("delete from taskListReact where taskID='%1' and unitID='%2';").arg(rwID,PRODUCTUNITNO);
        db.sql_exec(deleteReactSQL);
    }
}

void thread_sync::ZLsyncDcRw()
{
    QString searchSQL = QString("select RecordNum from SendProductNotice where Unit='%1' order by RecordNum+0 limit 1").arg(PRODUCTUNITNO);
    QString SendNum = db.sql_fetchrow_plus(searchSQL.toStdString().data(),0);
    if(SendNum.isEmpty()){
        SendNum = "0";
    }

    QString searchDcRw = QString("select RecordNumber,TaskList,DeliveryVehicle,Driver,ActualProductionVolume,ProductionTime,Engineering,StrengthGrade,TemplateName, \
                                 PouringMethod,VolumeMortar,FaHuoCustomer,PouringPosition,Slump,CumulativeNumber,CumulativeVolume from ProductionNotice where RecordNumber=%1 and Unit='%2#机组'").arg(SendNum,PRODUCTUNITNO);
    QList<QStringList> listNotice = db.sql_result(searchDcRw.toStdString().data());
            //emit erroMessage(QString("单车任务传输失败:\n")+searchDcRw);
    for(int i = 0;i<listNotice.size();i++){
        QString RecordNumber = listNotice.at(i).at(0);
        QString TaskList = listNotice.at(i).at(1);
        QString DeliveryVehicle = listNotice.at(i).at(2);
        QString Driver = listNotice.at(i).at(3);
        QString TicketNum = listNotice.at(i).at(4);
        QString ActualProductionVolume = listNotice.at(i).at(4);
        QString ProductionTime = listNotice.at(i).at(5);
        QString Engineering = listNotice.at(i).at(6);
        QString StrengthGrade = listNotice.at(i).at(7);
        StrengthGrade.replace(" "+listNotice.at(i).at(9),"").replace(" ","");
        QString TemplateName = listNotice.at(i).at(8);

        QString searchJBTime = QString("select JBTIME from rwPEIFANG where TaskList='%1' and StateNo='%2'").arg(TaskList,PRODUCTUNITNO);
        QString JBSJ = db.sql_fetchrow_plus(searchJBTime,0);
        if(JBSJ.isEmpty()){
            JBSJ = "0";
        }
        QString PouringMethod = listNotice.at(i).at(9);

        //砂浆
        QString shajiang = listNotice.at(i).at(10);
        if(shajiang.isEmpty()){
            shajiang = "0";
        }
        QString FaHuoCustomer = listNotice.at(i).at(11);
        QString PouringPosition = listNotice.at(i).at(12);
        QString Slump = listNotice.at(i).at(13);
        QString CumulativeNumber = listNotice.at(i).at(14);
        QString CumulativeVolume = listNotice.at(i).at(15);


        //混凝土方量
        ActualProductionVolume = QString::number(ActualProductionVolume.toDouble()-shajiang.toDouble(),'f',1);

        //如果本车方量为0且砂浆也为0，则跳过
        if(ActualProductionVolume.toDouble() <= 0 && shajiang.toDouble() <= 0){
            QString deleteSQL = QString("delete from SendProductNotice where RecordNum='%1'").arg(RecordNumber);
            db.sql_exec(deleteSQL);
            return;
        }

        //查找任务配方号
        QString searchTaskFormulaID = QString("select ID from PTaskFormula where PTaskListID='%1'").arg(TaskList);
        ZOOMLIONQuery->exec(searchTaskFormulaID);
        ZOOMLIONQuery->next();
        QString TaskFormulaID = ZOOMLIONQuery->value(0).toString();

        QString insertDcRwTabMy = QString("insert into ProductRegist (PRegOrder,TaskFormulaID,CarID,Driver,ConcreteSumNum,MortarNum,StartTime,PrintStatus,TicketNum,CreateTime,XZBool,XZRecord,Status,TrayRate,ProductRegNo) values \
                                          (%1,'%2','%3','%4',%5,%6,'%7',%8,%9,'%10',0,'',0,3,'%11')")
                        .arg(RecordNumber,TaskFormulaID,DeliveryVehicle,Driver,ActualProductionVolume,shajiang,ProductionTime,"0",TicketNum)
                        .arg(ProductionTime,RecordNumber);
        ZOOMLIONQuery->exec(insertDcRwTabMy);
        if(ZOOMLIONQuery->lastError().isValid()){
            emit erroMessage(QString("单车任务传输失败:\n")+insertDcRwTabMy+ZOOMLIONQuery->lastError().text());
            ZOOMLIONQuery->clear();
            return;
        }

        QString deleteSQL = QString("delete from SendProductNotice where RecordNum='%1'").arg(RecordNumber);
        db.sql_exec(deleteSQL);
    }
}

void thread_sync::ZLdeleteDcRw()
{
    QString searchSQL = QString("select cheNo,cheTime,Unit,recordNo from productNoticeReact where Unit='%1#机组' order by recordNo+0 desc limit 1").arg(PRODUCTUNITNO);
    QStringList resList = db.CreatStrList(searchSQL);
    QString cheNo,cheTime,unit,recordNo;
    if(resList.count() == 4){
        cheNo = resList.at(0);
        cheTime = resList.at(1);
        unit = resList.at(2);
        unit = unit.left(1);
        recordNo = resList.at(3);
    }

    if(PRODUCTUNITNO == unit){
        QString deleteSQL = QString("delete from ProductRegist where PRegOrder=%1").arg(recordNo);
        ZOOMLIONQuery->exec(deleteSQL);
        if(ZOOMLIONQuery->lastError().isValid()){
            emit erroMessage(QString("单车任务撤销失败:\n")+deleteSQL+ZOOMLIONQuery->lastError().text());
            ZOOMLIONQuery->clear();
            return;
        }

        QString deleteSQL1 = QString("delete from productNoticeReact where cheNo='%1' and cheTime='%2'").arg(cheNo,cheTime);
        db.sql_exec(deleteSQL1);
    }
}

void thread_sync::ZLsyncBuFangDcRw()
{
    QString search = QString("select number from bufangReact where unit='%1' limit 1").arg(PRODUCTUNITNO);
    QString bufangNo = db.sql_fetchrow_plus(search.toStdString().data(),0);
    if(bufangNo.isEmpty()){
        bufangNo = "0";
    }

    QString searchDcRw = QString("select RecordNumber,TaskList,DeliveryVehicle,Driver,ActualProductionVolume,ProductionTime,Engineering,StrengthGrade,TemplateName,PouringMethod,VolumeMortar,\
                                 FaHuoCustomer,PouringPosition,Slump,CumulativeNumber,CumulativeVolume from bufangNotice where RecordNumber=%1 and Unit='%2#机组' and WhetherDocument='是';").arg(bufangNo,PRODUCTUNITNO);
    QList<QStringList> listNotice = db.sql_result(searchDcRw.toStdString().data());
    for(int i = 0;i<listNotice.size();i++){
        QString RecordNumber = listNotice.at(i).at(0);
        QString TaskList = listNotice.at(i).at(1);
        QString DeliveryVehicle = listNotice.at(i).at(2);
        QString Driver = listNotice.at(i).at(3);
        QString TicketNum = listNotice.at(i).at(4);
        QString ActualProductionVolume = listNotice.at(i).at(4);
        QString ProductionTime = listNotice.at(i).at(5);
        QString Engineering = listNotice.at(i).at(6);
        QString StrengthGrade = listNotice.at(i).at(7);
        StrengthGrade.replace(" "+listNotice.at(i).at(9),"").replace(" ","");
        QString TemplateName = listNotice.at(i).at(8);

        QString searchJBTime = QString("select JBTIME from rwPEIFANG where TaskList='%1' and StateNo='%2'").arg(TaskList,PRODUCTUNITNO);
        QString JBSJ = db.sql_fetchrow_plus(searchJBTime,0);
        if(JBSJ.isEmpty()){
            JBSJ = "0";
        }
        QString PouringMethod = listNotice.at(i).at(9);

        //砂浆
        QString shajiang = listNotice.at(i).at(10);
        if(shajiang.isEmpty()){
            shajiang = "0";
        }
        QString FaHuoCustomer = listNotice.at(i).at(11);
        QString PouringPosition = listNotice.at(i).at(12);
        QString Slump = listNotice.at(i).at(13);
        QString CumulativeNumber = listNotice.at(i).at(14);
        QString CumulativeVolume = listNotice.at(i).at(15);


        //混凝土方量
        ActualProductionVolume = QString::number(ActualProductionVolume.toDouble()-shajiang.toDouble(),'f',1);

        //如果本车方量为0，则跳过
        if(ActualProductionVolume.toDouble() <= 0){
            return;
        }

        //查找任务配方号
        QString searchTaskFormulaID = QString("select ID from PTaskFormula where PTaskListID='%1'").arg(TaskList);
        ZOOMLIONQuery->exec(searchTaskFormulaID);
        ZOOMLIONQuery->next();
        QString TaskFormulaID = ZOOMLIONQuery->value(0).toString();

        QString insertDcRwTabMy = QString("insert into ProductRegist (PRegOrder,TaskFormulaID,CarID,Driver,ConcreteSumNum,MortarNum,StartTime,PrintStatus,TicketNum,CreateTime,XZBool,XZRecord,Status) values \
                                          (%1,'%2','%3','%4',%5,%6,'%7',%8,%9,'%10',0,'',-2)")
                        .arg(RecordNumber,TaskFormulaID,DeliveryVehicle,Driver,ActualProductionVolume,shajiang,ProductionTime,"0",TicketNum)
                        .arg(ProductionTime);
        ZOOMLIONQuery->exec(insertDcRwTabMy);
        if(ZOOMLIONQuery->lastError().isValid()){
            emit erroMessage(QString("单车任务传输失败:\n")+insertDcRwTabMy+ZOOMLIONQuery->lastError().text());
            ZOOMLIONQuery->clear();
            return;
        }

        QString deleteSQL = QString("delete from bufangReact where number='%1'").arg(bufangNo);
        db.sql_exec(deleteSQL);
    }
}

void thread_sync::ZLRunState()
{
    QString unitNo = PRODUCTUNITNO;
    QString searchDcRwTabSQL = QString("SELECT ProductRegNo,ConcreteSumNum FROM ProductRegist where Status>0");
    ZOOMLIONQuery->exec(searchDcRwTabSQL);
    while (ZOOMLIONQuery->next()) {
        QString DJBH = ZOOMLIONQuery->value(0).toString();
//        QString TotalVolume = ZOOMLIONQuery->value(1).toString();
        QString searchHISTDATAsql = QString("SELECT count(1),SUM(SUMPS) FROM HISTDATA WHERE bsqk='%1'").arg(DJBH);
        QString panshu = db.sql_fetchrow_plus(searchHISTDATAsql,0);
        QString volume = db.sql_fetchrow_plus(searchHISTDATAsql,1);

        QString updateMySQL = QString("update ProductionNotice set Confirmor='是' where RecordNumber=%1").arg(DJBH);
        db.sql_exec(updateMySQL.toStdString().data());

        QString insertMySQL = QString("replace into RunStateTab (recordNo,panshu,volume,unitNo) values ('%1','%2','%3','%4');").arg(DJBH,panshu,volume,unitNo);
        db.sql_exec(insertMySQL.toStdString().data());

    }

    QString searchMySQLRunState = QString("select recordNo from RunStateTab where unitNo='%1'").arg(unitNo);
    QStringList recordList = db.find_CheNo(searchMySQLRunState);
    for(int i = 0; i<recordList.count(); i++){
        QString searchSQL = QString("select ProductRegNo from ProductRegist where Status=-2 and ProductRegNo='%1'").arg(recordList.at(i));
        ZOOMLIONQuery->exec(searchSQL.toStdString().data());
        if(ZOOMLIONQuery->next()){
            //删除相关生产状态表中的记录
            QString deleteSQL = QString("delete from RunStateTab where recordNo='%1'").arg(recordList.at(i));
            db.sql_exec(deleteSQL.toStdString().data());
            //删除车辆队列
            QString deleteVehicle = QString("delete from inHouseVehicle where CheNo=(select DeliveryVehicle from ProductionNotice where RecordNumber=%1)").arg(recordList.at(i));
            db.sql_exec(deleteVehicle);
        }
    }
}

void thread_sync::BSsyncPhb()
{
    QString searchPhbReact = QString("select RecipeID,RecipeName,Mat1,Mat2,Mat3,Mat4,Mat5,Mat6,Mat7,Mat8,Mat9,Mat10,Mat11,Mat12,Mat13,Mat14,Mat15,Mat16,Mat17,Mat18,\
                                      Mat19,Mat20,Mat21,Mat22,Mat23,Mat24,intensityLevel,state,jbTime,wushui from PhbReact where unit='%1'").arg(PRODUCTUNITNO);
    QList<QStringList> list = db.sql_result(searchPhbReact);
    for(int i = 0;i<list.size();i++){
        QString RecipeID = list.at(i).at(0);
        QString RecipeName = list.at(i).at(1);
        QString Mat1 = list.at(i).at(2);
        QString Mat2 = list.at(i).at(3);
        QString Mat3 = list.at(i).at(4);
        QString Mat4 = list.at(i).at(5);
        QString Mat5 = list.at(i).at(6);
        QString Mat6 = list.at(i).at(7);
        QString Mat7 = list.at(i).at(8);
        QString Mat8 = list.at(i).at(9);
        QString Mat9 = list.at(i).at(10);
        QString Mat10 = list.at(i).at(11);
        QString Mat11 = list.at(i).at(12);
        QString Mat12 = list.at(i).at(13);
        QString Mat13 = list.at(i).at(14);
        QString Mat14 = list.at(i).at(15);
        QString Mat15 = list.at(i).at(16);
        QString Mat16 = list.at(i).at(17);
        QString Mat17 = list.at(i).at(18);
        QString Mat18 = list.at(i).at(19);
        QString Mat19 = list.at(i).at(20);
        QString Mat20 = list.at(i).at(21);
        QString Mat21 = list.at(i).at(22);
        QString Mat22 = list.at(i).at(23);
        QString Mat23 = list.at(i).at(24);
        QString Mat24 = list.at(i).at(25);
        QString intensityLevel = list.at(i).at(26);
        QString state = list.at(i).at(27);
        QString jbTime = list.at(i).at(28);
        QString wushui = list.at(i).at(29);
        QStringList matList;
        matList<<Mat1<<Mat2<<Mat3<<Mat4<<Mat5<<Mat6<<Mat7<<Mat8<<Mat9<<Mat10<<Mat11<<Mat12<<Mat13<<Mat14<<Mat15<<Mat16<<Mat17<<Mat18<<Mat19<<Mat20<<Mat21<<Mat22<<Mat23<<Mat24;
        double Volume = 0;
        for(int i = 0; i < matList.count(); i++){
            Volume += matList.at(i).toDouble();
        }

        if(state == "insert" || state == "update"){
            //插入
            QString insertSQL = QString("insert into Recipe (Code,Tag,BetLev,MixLast,Flag,M5,M6,M7,M22,M23,M30,M31,U5,\
                                                       U6,U7,U22,U23,U30,U31) VALUES ('%1','%2','%3',%4,'1','水泥1','粉煤灰2','粉煤灰','细砂仓','粗砂仓',\
                                                       '粉外剂1','粉外剂2',%5,%6,%7,%8,%9,%10,%11)")
                    .arg(RecipeID,RecipeName,intensityLevel,jbTime).arg(Mat1,Mat2,Mat3,Mat4,Mat5,Mat6,Mat7);
            BSQuery->exec(insertSQL);
            if(BSQuery->lastError().isValid()){
                emit erroMessage(insertSQL+BSQuery->lastError().text());
                return;
            }
        }

        QString deleteSQL = QString("delete from PhbReact where unit='%1' and RecipeName='%2'").arg(PRODUCTUNITNO,RecipeName);
        db.sql_exec(deleteSQL);
    }
}

void thread_sync::BSsyncRenWuKuTask()
{
    //获取需要传输的总任务列表
    QString searchID = QString("select taskID from taskListReact where unitID='%1' order by taskID").arg(PRODUCTUNITNO);
    QStringList taskListIDList = db.find_CheNo(searchID);
    QString taskListID;
    for(int i = 0; i < taskListIDList.count(); i++){
        taskListID.append(QString("'%1',").arg(taskListIDList.at(i)));
    }
    taskListID = taskListID.left(taskListID.length()-1);
    if(taskListID.isEmpty()){
        taskListID = "0";
    }

    QString searchSQL = QString("select TaskNumber,Template,PlannedQuantity,ContractCompletion,Slump,PouringPosition,Engineering,\
                                FaHuoCustomer,PouringMethod,CumulativeNumber,StrengthGrade,SupplyTime from ProductionTaskList \
                                where TaskNumber in (%1);").arg(taskListID);
    QList<QStringList> list = db.sql_result(searchSQL.toStdString().data());
    for(int i = 0;i<list.size();i++){
        //任务编号
        QString rwID = list.at(i).at(0);
        //配方名称
        QString PFname = list.at(i).at(1);
        //配方编号
        QString searchPFID = QString("select IDENT,jbTime from PEIFANG%1 WHERE PhbNumber='%2'").arg(PRODUCTUNITNO,PFname);
        QString PFID = db.sql_fetchrow_plus(searchPFID,0);
        QString jbTime = db.sql_fetchrow_plus(searchPFID,1);
        //设定总方量
        QString setCount = list.at(i).at(2);
        //累计方量
        QString finishCount = list.at(i).at(3);
        //塌落度
        QString taladu = list.at(i).at(4);
        //浇筑部位
        QString jzbw = list.at(i).at(5);
        //工程名称
        QString gcmc = list.at(i).at(6);
        //用户名称
        QString username = list.at(i).at(7);
        //泵送情况
        QString bsqk = list.at(i).at(8);
        //累计车次
        QString leijicheci = list.at(i).at(9);
        //强度等级
        QString tdj = list.at(i).at(10);
        tdj.replace(" "+list.at(i).at(8),"").replace(" ","");
        //时间
        QString dateTime = list.at(i).at(11);


        //插入任务
        QString insertSQL = QString("insert into Task (Code,DatTim,Recipe,Customer,ProjName,ConsPos,Pour,BetLev,Lands,MixLast,Mete,Flag) values \
                                    ('%1','%2','%3','%4','%5','%6','%7','%8','%9',%10,%11,'1')")
                             .arg(rwID,dateTime,PFname,username,gcmc,jzbw).arg(bsqk,tdj,taladu,jbTime,setCount);
        BSQuery->exec(insertSQL);
        if(BSQuery->lastError().isValid()){
            emit erroMessage(insertSQL+" "+BSQuery->lastError().text()+"总任务传输失败");
            return;
        }

        //删除taskReact表中的数据
        QString deleteSQL = QString("delete from taskListReact where taskID='%1' and unitID='%2'").arg(rwID,PRODUCTUNITNO);
        db.sql_exec(deleteSQL);
    }
}

void thread_sync::BSsyncDcRw()
{
    QString searchSQL = QString("select RecordNum from SendProductNotice where Unit='%1' order by RecordNum+0 limit 1").arg(PRODUCTUNITNO);
    QString SendNum = db.sql_fetchrow_plus(searchSQL.toStdString().data(),0);
    if(SendNum.isEmpty()){
        SendNum = "0";
    }

    QString searchDcRw = QString("select RecordNumber,TaskList,DeliveryVehicle,Driver,ActualProductionVolume,ProductionTime,Engineering,StrengthGrade,TemplateName, \
                                 PouringMethod,VolumeMortar,FaHuoCustomer,PouringPosition,Slump,CumulativeNumber,CumulativeVolume from ProductionNotice where RecordNumber=%1 and Unit='%2#机组'").arg(SendNum,PRODUCTUNITNO);
    QList<QStringList> listNotice = db.sql_result(searchDcRw.toStdString().data());
    for(int i = 0;i<listNotice.size();i++){
        QString RecordNumber = listNotice.at(i).at(0);
        QString TaskList = listNotice.at(i).at(1);
        QString DeliveryVehicle = listNotice.at(i).at(2);
        QString Driver = listNotice.at(i).at(3);
        QString ActualProductionVolume = listNotice.at(i).at(4);
        QString scdate = listNotice.at(i).at(5);
        QString Engineering = listNotice.at(i).at(6);
        QString StrengthGrade = listNotice.at(i).at(7);
        StrengthGrade.replace(" "+listNotice.at(i).at(9),"").replace(" ","");
        QString TemplateName = listNotice.at(i).at(8);
        //配方编号
        QString searchPFID = QString("select IDENT from PEIFANG%1 WHERE PhbNumber='%2'").arg(PRODUCTUNITNO,TemplateName);
        QString PFID = db.sql_fetchrow_plus(searchPFID,0);

        QString PouringMethod = listNotice.at(i).at(9);

        //砂浆
        QString shajiang = listNotice.at(i).at(10);
        QString FaHuoCustomer = listNotice.at(i).at(11);
        QString PouringPosition = listNotice.at(i).at(12);
        QString Slump = listNotice.at(i).at(13);
        QString CumulativeNumber = listNotice.at(i).at(14);
        QString CumulativeVolume = listNotice.at(i).at(15);

        //如果本车方量为0，则跳过
        if(ActualProductionVolume.toDouble() <= 0){
            QString deleteSQL = QString("delete from SendProductNotice where RecordNum='%1'").arg(RecordNumber);
            db.sql_exec(deleteSQL);
            return;
        }

        QString insertSQL = QString("insert into Produce (ErpID,Code,Recipe,DatTim,Vehicle,Driver,ProdMete,TotVehs,TotMete,Flag) values \
                                    (%1,'%2','%3','%4','%5','%6',%7,%8,%9,'1')")
                                .arg(RecordNumber,TaskList,TemplateName,scdate,DeliveryVehicle,Driver,ActualProductionVolume,CumulativeNumber,CumulativeVolume);
        BSQuery->exec(insertSQL);
        if(BSQuery->lastError().isValid()){
            emit erroMessage(insertSQL+" "+BSQuery->lastError().text()+"单车任务传输失败");
            return;
        }

        QString deleteSQL = QString("delete from SendProductNotice where RecordNum='%1'").arg(RecordNumber);
        db.sql_exec(deleteSQL);
    }
}

void thread_sync::BSdeleteDcRw()
{
    QString searchSQL = QString("select recordNo from productNoticeReact where Unit='%1#机组' order by recordNo+0 desc limit 1").arg(PRODUCTUNITNO);
    QString recordNo = db.sql_fetchrow_plus(searchSQL,0);
    if(recordNo.isEmpty()){
        recordNo = "0";
    }

    QString searchDcRw = QString("select RecordNumber,TaskList,DeliveryVehicle,Driver,ActualProductionVolume,ProductionTime,Engineering,StrengthGrade,TemplateName, \
                                 PouringMethod,VolumeMortar,FaHuoCustomer,PouringPosition,Slump,CumulativeNumber,CumulativeVolume from zuofeinotice where RecordNumber=%1 and Unit='%2#机组'").arg(recordNo,PRODUCTUNITNO);
    QList<QStringList> listNotice = db.sql_result(searchDcRw.toStdString().data());
    for(int i = 0;i<listNotice.size();i++){
        QString RecordNumber = listNotice.at(i).at(0);
        QString TaskList = listNotice.at(i).at(1);
        QString DeliveryVehicle = listNotice.at(i).at(2);
        QString Driver = listNotice.at(i).at(3);
        QString ActualProductionVolume = listNotice.at(i).at(4);
        QString scdate = listNotice.at(i).at(5);
        QString StrengthGrade = listNotice.at(i).at(7);
        StrengthGrade.replace(" "+listNotice.at(i).at(9),"").replace(" ","");
        QString TemplateName = listNotice.at(i).at(8);
        //配方编号
        QString searchPFID = QString("select IDENT from PEIFANG%1 WHERE PhbNumber='%2'").arg(PRODUCTUNITNO,TemplateName);
        QString PFID = db.sql_fetchrow_plus(searchPFID,0);

        QString insertSQL = QString("insert into ProdDel (ErpID,Code,Recipe,DatTim,Vehicle,Driver,ProdMete,Flag) values \
                                    (%1,'%2','%3','%4','%5','%6',%7,'1')")
                                .arg(RecordNumber,TaskList,TemplateName,scdate,DeliveryVehicle,Driver,ActualProductionVolume);
        BSQuery->exec(insertSQL);
        if(BSQuery->lastError().isValid()){
            emit erroMessage(insertSQL+" "+BSQuery->lastError().text()+"单车任务删除失败");
            return;
        }

        QString deleteSQL1 = QString("delete from productNoticeReact where recordNo='%1'").arg(recordNo);
        db.sql_exec(deleteSQL1.toStdString().data());
    }
}

void thread_sync::setThreadIsRun(bool whetherRun)
{
    threadIsRun = whetherRun;
}
