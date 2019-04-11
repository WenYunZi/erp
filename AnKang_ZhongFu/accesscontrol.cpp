#include "accesscontrol.h"

extern pubfunc pub;

accessControl::accessControl(QWidget *parent) :
    QWidget(parent)
{
    library = new QLibrary("HCNetSDK.dll",this);

    char DVRIP[30] = {0};//刻录机ip
    strcpy(DVRIP,pub.read_connect_menjin().toStdString().data());

    loadSuccess = library->load();


    if(loadSuccess){
        //解析动态库中的函数
        //初始化SDK函数
        NET_DVR_Init = (pfNET_DVR_Init)library->resolve("NET_DVR_Init");
        //设置网络连接超时时间和连接尝试次数
        NET_DVR_SetConnectTime = (pfNET_DVR_SetConnectTime)library->resolve("NET_DVR_SetConnectTime") ;
        //设置重连功能
        NET_DVR_SetReconnect = (pfNET_DVR_SetReconnect)library->resolve("NET_DVR_SetReconnect") ;
        //登录NVS函数
        NET_DVR_Login_V40 = (pfNET_DVR_Login_V40)library->resolve("NET_DVR_Login_V40");
        //视频接收函数
        NET_DVR_RealPlay_V40 = (pfNET_DVR_RealPlay_V40)library->resolve("NET_DVR_RealPlay_V40");
        //停止接收一路视频函数
        NET_DVR_StopRealPlay = (pfNET_DVR_StopRealPlay)library->resolve("NET_DVR_StopRealPlay");
        //用户注销登录
        NET_DVR_Logout = (pfNET_DVR_Logout)library->resolve("NET_DVR_Logout");
        //释放SDK
        NET_DVR_Cleanup = (pfNET_DVR_Cleanup)library->resolve("NET_DVR_Cleanup");
        //抓图模式
        NET_DVR_SetCapturePictureMode = (pfNET_DVR_SetCapturePictureMode)library->resolve("NET_DVR_SetCapturePictureMode");
        //抓图
        NET_DVR_CapturePicture = (pfNET_DVR_CapturePicture)library->resolve("NET_DVR_CapturePicture");
        //设置报警回调函数
        NET_DVR_SetDVRMessageCallBack_V31 = (pfNET_DVR_SetDVRMessageCallBack_V31)library->resolve("NET_DVR_SetDVRMessageCallBack_V31");
        //启用布防
        NET_DVR_SetupAlarmChan_V41 = (pfNET_DVR_SetupAlarmChan_V41)library->resolve("NET_DVR_SetupAlarmChan_V41");
        //错误信息
        NET_DVR_GetLastError = (pfNET_DVR_GetLastError)library->resolve("NET_DVR_GetLastError");
        //连拍触发
        NET_DVR_ContinuousShoot = (pfNET_DVR_ContinuousShoot)library->resolve("NET_DVR_ContinuousShoot");
        //撤防
        NET_DVR_CloseAlarmChan_V30 = (pfNET_DVR_CloseAlarmChan_V30)library->resolve("NET_DVR_CloseAlarmChan_V30");

        // 初始化
        NET_DVR_Init();
        //设置连接时间与重连时间
        NET_DVR_SetConnectTime(2000, 1);
        NET_DVR_SetReconnect(10000, true);

        //设置抓图模式为bmp
        NET_DVR_SetCapturePictureMode(0);

        //登录设备
        _lUserID = NVR_Login("192.168.12.13","admin","a12345678");

        //报警布防
        NVR_alarm(_lUserID);

        //网络连拍触发
        NVR_shoot(_lUserID);

    }
    else{
        QMessageBox::information(this,tr("错误"),library->errorString(),0,0,0);
    }
}

accessControl::~accessControl()
{
    //撤销布防上传通道
    if (!NET_DVR_CloseAlarmChan_V30(lHandle))
    {
        printf("NET_DVR_CloseAlarmChan_V30 failed, error code: %d\n", NET_DVR_GetLastError());
        NET_DVR_Logout(_lUserID);
        NET_DVR_Cleanup();
        return;
    }

    //注销用户
    NET_DVR_Logout(_lUserID);

    //释放SDK资源
    NET_DVR_Cleanup();


}

long accessControl::NVR_Login(char *NVRIP, char *User, char *Secret)
{
    //登录参数，包括设备地址、登录用户、密码等
    LONG lUserID;

    NET_DVR_USER_LOGIN_INFO struLoginInfo;
    memset(&struLoginInfo,0,sizeof(NET_DVR_USER_LOGIN_INFO));

    struLoginInfo.bUseAsynLogin = 0; //同步登录方式
    strcpy(struLoginInfo.sDeviceAddress, NVRIP); //设备IP地址
    struLoginInfo.wPort = 8000; //设备服务端口
    strcpy(struLoginInfo.sUserName, User); //设备登录用户名
    strcpy(struLoginInfo.sPassword, Secret); //设备登录密码

    //设备信息, 输出参数
    NET_DVR_DEVICEINFO_V40 struDeviceInfoV40;
    memset(&struDeviceInfoV40,0,sizeof(NET_DVR_DEVICEINFO_V40));

    lUserID = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);
    if (lUserID < 0)
    {
      NET_DVR_Cleanup();
      return -1;
    }

    qDebug()<<lUserID;

    return lUserID;
}

void accessControl::NVR_alarm(LONG lUserID)
{
    //设置报警回调函数

    qDebug()<<"1";

    NET_DVR_SetDVRMessageCallBack_V31(MSesGCallback, NULL);

    qDebug()<<"2";

    NET_DVR_SETUPALARM_PARAM struSetupParam;

    qDebug()<<"3";

    memset(&struSetupParam, 0, sizeof(NET_DVR_SETUPALARM_PARAM));

    qDebug()<<"4";

    struSetupParam.dwSize=sizeof(NET_DVR_SETUPALARM_PARAM);


    qDebug()<<"5";

    struSetupParam.byLevel = 1; //布防优先级：0- 一等级（高），1- 二等级（中）

    qDebug()<<"6";

    struSetupParam.byAlarmInfoType = 1; //上传报警信息类型: 0- 老报警信息(NET_DVR_PLATE_RESULT), 1- 新报警信息(NET_ITS_PLATE_RESULT)

    qDebug()<<"7";

    lHandle = NET_DVR_SetupAlarmChan_V41(lUserID,&struSetupParam);

    qDebug()<<"8"<<lHandle;

    if (lHandle < 0)
    {


        qDebug()<<"9";

        printf("NET_DVR_SetupAlarmChan_V41 failed, error code: %d\n", NET_DVR_GetLastError());


        qDebug()<<"10";

        NET_DVR_Logout(lUserID);

        qDebug()<<"11";

        NET_DVR_Cleanup();


        qDebug()<<"12";

        return;
    }

    qDebug()<<"13";
    qDebug()<<"布防成功!\n";

    //printf();
}

void accessControl::NVR_shoot(LONG lUserID)
{
    NET_DVR_SNAPCFG struSnapCfg;
    memset(&struSnapCfg, 0, sizeof(NET_DVR_SNAPCFG));

    //结构体大小
    struSnapCfg.dwSize = sizeof(NET_DVR_SNAPCFG);

    //线圈抓拍次数，0-不抓拍，非0-连拍次数，目前最大5次
    struSnapCfg.bySnapTimes  = 2;

    //抓拍等待时间，单位ms，取值范围[0,60000]
    struSnapCfg.wSnapWaitTime   = 1000;

    //连拍间隔时间，单位ms，取值范围[67,60000]
    struSnapCfg.wIntervalTime[0]  = 1000;
    struSnapCfg.wIntervalTime[1]  = 1000;

    //触发IO关联的车道号，取值范围[0,9]
    struSnapCfg.byRelatedDriveWay = 0;

    //网络触发连拍
    if (!NET_DVR_ContinuousShoot(lUserID, &struSnapCfg))
    {
        printf("NET_DVR_ContinuousShoot failed, error code: %d\n", NET_DVR_GetLastError());
        return;
    }
   // printf("网络触发连拍!\n");
}

int CALLBACK MSesGCallback(LONG lCommand, NET_DVR_ALARMER *pAlarmer, char *pAlarmInfo, DWORD dwBufLen, void *pUser)
{
    qDebug()<<"huidiaohanshuchufa"<<lCommand;

    mymysql paidui;
    paidui.sql_connect(pub.read_hostip().toStdString().data(),"dbuser1","dbuser1","akzf_db");


    switch (lCommand)
    {
        case COMM_UPLOAD_PLATE_RESULT:
        {
            NET_DVR_PLATE_RESULT struPlateResult={0};
            memcpy(&struPlateResult, pAlarmInfo, sizeof(struPlateResult));
            qDebug()<<"VehicleNumber1:"<< struPlateResult.struPlateInfo.sLicense;

            QString VehicleNum = QString(struPlateResult.struPlateInfo.sLicense).right(6);


            //插入车辆队列
            QString insertDuiLie = QString("insert into inHouseVehicle (CheNo,CheTime,ID) select B.Vehiclenumber,'%1','%2' \
                                        from ConcreteVehicleInformation B where B.LicensePlate like '%%2%'")
                    .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"),VehicleNum);
            paidui.sql_exec(insertDuiLie.toStdString().data());

            QString searchCheNo = QString("select Vehiclenumber from ConcreteVehicleInformation where LicensePlate like '%%1%'").arg(VehicleNum);
            QString cheNo = paidui.sql_fetchrow_plus(searchCheNo,0);

            //更新出车单车辆回厂时间
            QString updateBackTime = QString("update ProductionNotice set SettlementTime='%1' where DeliveryVehicle='%2' order by RecordNumber desc limit 1")
                    .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"),cheNo);
            paidui.sql_exec(updateBackTime.toStdString().data());

            //插入大屏显示的Vehicle表信息
            QString insertSQL = QString("insert into Vehicle (cheNo) select B.Vehiclenumber \
                                        from ConcreteVehicleInformation B where B.LicensePlate like '%%1%'").arg(VehicleNum);
            paidui.sql_exec(insertSQL.toStdString().data());
            Sleep(1000);

            //其他信息处理......
            break;
        }
        case COMM_ITS_PLATE_RESULT:
        {
            NET_ITS_PLATE_RESULT struITSPlateResult={0};
            memcpy(&struITSPlateResult, pAlarmInfo, sizeof(struITSPlateResult));

            for (int i = 0;i < struITSPlateResult.dwPicNum;i++)
            {
                qDebug()<<"VehicleNumber2"<<QString(struITSPlateResult.struPlateInfo.sLicense).right(6);

                QString VehicleNum = QString(struITSPlateResult.struPlateInfo.sLicense).right(6);


                //插入车辆队列
                QString insertDuiLie = QString("insert into inHouseVehicle (CheNo,CheTime,ID) select B.Vehiclenumber,'%1','%2' \
                                            from ConcreteVehicleInformation B where B.LicensePlate like '%%2%'")
                        .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"),VehicleNum);
                paidui.sql_exec(insertDuiLie.toStdString().data());

                QString searchCheNo = QString("select Vehiclenumber from ConcreteVehicleInformation where LicensePlate like '%%1%'").arg(VehicleNum);
                QString cheNo = paidui.sql_fetchrow_plus(searchCheNo,0);

                //更新出车单车辆回厂时间
                QString updateBackTime = QString("update ProductionNotice set SettlementTime='%1' where DeliveryVehicle='%2' order by RecordNumber desc limit 1")
                        .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"),cheNo);
                paidui.sql_exec(updateBackTime.toStdString().data());

                //插入大屏显示的Vehicle表信息
                QString insertSQL = QString("insert into Vehicle (cheNo) select B.Vehiclenumber \
                                            from ConcreteVehicleInformation B where B.LicensePlate like '%%1%'").arg(VehicleNum);
                paidui.sql_exec(insertSQL.toStdString().data());
                Sleep(1000);

            }
            break;
        }
        default:
            break;
    }

    paidui.sql_disconnet();


    return 0;


}
