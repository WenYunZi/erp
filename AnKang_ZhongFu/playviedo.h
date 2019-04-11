#ifndef PLAYVIEDO_H
#define PLAYVIEDO_H

#include <QWidget>
#include <QLibrary>
#include <QLabel>
#include <windows.h>
#include <QDebug>
#include <QMessageBox>
#include <QHBoxLayout>
#include <C:/HIKvisionSDK/include/HCNetSDK.h>
#include "pubfunc.h"
#include "mylabel.h"

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
typedef DWORD __stdcall (*pfNET_DVR_GetLastError)();

class PlayViedo : public QWidget
{
    Q_OBJECT
public:
    explicit PlayViedo(QWidget *parent = 0);
    ~PlayViedo();

private:
    QLibrary *library;

    bool loadSuccess;

    myLabel *Video1;
    myLabel *Video2;
    myLabel *Video3;
    myLabel *Video4;

    int VideoStatus;

    QGridLayout *layout;

    int PassID1;//摄像头1通道号
    int PassID2;//摄像头2通道号
    int PassID3;//摄像头3通道号

    long _lUserID1;
    long _lUserID2;
    long _lUserID3;

    long _lRealHandle1;
    long _lRealHandle2;
    long _lRealHandle3;

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
    //错误信息
    pfNET_DVR_GetLastError NET_DVR_GetLastError;


private:
    long NVR_Login(char *NVRIP,char *User,char *Secret);
    long PlayVideo(myLabel *video,long _lUserID,int passID);

public:
    void CaptureBmpPic(QString filename1,QString filename2,QString filename3);

private slots:
    void ChangeVideoStatus(int ID);

};

#endif // PLAYVIEDO_H
