#ifndef ACCESSCONTROL_H
#define ACCESSCONTROL_H

#include <QWidget>
#include <QLibrary>
#include <QLabel>
#include <windows.h>
#include <QDebug>
#include <QMessageBox>
#include <QHBoxLayout>
#include <C:/HIKvisionSDK/include/HCNetSDK.h>
#include "pubfunc.h"

extern pubfunc pub;

//定义函数指针
typedef bool __stdcall (*pfNET_DVR_Init)();
typedef bool __stdcall (*pfNET_DVR_SetConnectTime)(DWORD dwWaitTime,DWORD dwTryTimes);
typedef bool __stdcall (*pfNET_DVR_SetReconnect)(DWORD dwInterval,BOOL bEnableRecon);
typedef long __stdcall (*pfNET_DVR_Login_V40)(LPNET_DVR_USER_LOGIN_INFO pLoginInfo,LPNET_DVR_DEVICEINFO_V40 lpDeviceInfo);
typedef long __stdcall (*pfNET_DVR_RealPlay_V40)(LONG lUserID,LPNET_DVR_PREVIEWINFO lpPreviewInfo,REALDATACALLBACK fRealDataCallBack_V30,void *pUser);
typedef bool __stdcall (*pfNET_DVR_StopRealPlay)(LONG lRealHandle);
typedef bool __stdcall (*pfNET_DVR_Logout)(LONG lUserID);
typedef bool __stdcall (*pfNET_DVR_Cleanup)();
typedef bool __stdcall (*pfNET_DVR_SetCapturePictureMode)(DWORD dwCaptureMode);
typedef bool __stdcall (*pfNET_DVR_CapturePicture)(LONG lRealHandle,char *sPicFileName);

typedef bool __stdcall (*pfNET_DVR_SetDVRMessageCallBack_V31)(MSGCallBack_V31 fMessageCallBack,void *pUser);
typedef bool __stdcall (*pfNET_DVR_SetupAlarmChan_V41)(LONG lUserID,LPNET_DVR_SETUPALARM_PARAM lpSetupParam);
typedef DWORD __stdcall (*pfNET_DVR_GetLastError)();
typedef bool __stdcall (*pfNET_DVR_ContinuousShoot)(LONG lUserID,LPNET_DVR_SNAPCFG lpInter);

typedef bool __stdcall (*pfNET_DVR_CloseAlarmChan_V30)(LONG lAlarmHandle);

int CALLBACK MSesGCallback(LONG lCommand, NET_DVR_ALARMER *pAlarmer, char *pAlarmInfo, DWORD dwBufLen, void* pUser);

class accessControl : public QWidget
{
    Q_OBJECT
public:
    explicit accessControl(QWidget *parent = 0);
    ~accessControl();


private:
    QLibrary *library;

    bool loadSuccess;

    long _lUserID;
    LONG lHandle;

private:
    //初始化SDK函数
    pfNET_DVR_Init NET_DVR_Init;
    //设置网络连接超时时间和连接尝试次数
    pfNET_DVR_SetConnectTime NET_DVR_SetConnectTime;
    //设置重连功能
    pfNET_DVR_SetReconnect NET_DVR_SetReconnect;
    //登录NVS函数
    pfNET_DVR_Login_V40 NET_DVR_Login_V40;
    //视频接收函数
    pfNET_DVR_RealPlay_V40 NET_DVR_RealPlay_V40;
    //停止接收一路视频
    pfNET_DVR_StopRealPlay NET_DVR_StopRealPlay;
    //用户注销登录
    pfNET_DVR_Logout NET_DVR_Logout;
    //释放SDK
    pfNET_DVR_Cleanup NET_DVR_Cleanup;
    //抓图模式
    pfNET_DVR_SetCapturePictureMode NET_DVR_SetCapturePictureMode;
    //抓图
    pfNET_DVR_CapturePicture NET_DVR_CapturePicture;
    //设置报警回调函数
    pfNET_DVR_SetDVRMessageCallBack_V31 NET_DVR_SetDVRMessageCallBack_V31;
    //启用布防
    pfNET_DVR_SetupAlarmChan_V41 NET_DVR_SetupAlarmChan_V41;
    //错误信息
    pfNET_DVR_GetLastError NET_DVR_GetLastError;
    //连拍触发
    pfNET_DVR_ContinuousShoot NET_DVR_ContinuousShoot;
    //撤防
    pfNET_DVR_CloseAlarmChan_V30 NET_DVR_CloseAlarmChan_V30;

private:
    long NVR_Login(char *NVRIP,char *User,char *Secret);
    void NVR_alarm(LONG lUserID);
    void NVR_shoot(LONG lUserID);
};

#endif // ACCESSCONTROL_H
