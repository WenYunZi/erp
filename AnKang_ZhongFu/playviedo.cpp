#include "playviedo.h"

PlayViedo::PlayViedo(QWidget *parent) :
    QWidget(parent)
{
    library = new QLibrary("HCNetSDK.dll",this);

    VideoStatus = 0;

    char DVRIP[30] = {0};//刻录机ip
    strcpy(DVRIP,pub.read_DVR_IP().toStdString().data());

    PassID1 = pub.read_IPC1().toInt();
    PassID2 = pub.read_IPC2().toInt();
    PassID3 = pub.read_IPC3().toInt();

    Video1 = new myLabel(1,this);
    Video1->setStyleSheet("background-color:black");
    connect(Video1,SIGNAL(isDoubleClick(int)),this,SLOT(ChangeVideoStatus(int)));
    Video2 = new myLabel(2,this);
    Video2->setStyleSheet("background-color:black");
    connect(Video2,SIGNAL(isDoubleClick(int)),this,SLOT(ChangeVideoStatus(int)));
    Video3 = new myLabel(3,this);
    Video3->setStyleSheet("background-color:black");
    connect(Video3,SIGNAL(isDoubleClick(int)),this,SLOT(ChangeVideoStatus(int)));
    Video4 = new myLabel(4,this);
    Video4->setStyleSheet("background-color:black");
    connect(Video4,SIGNAL(isDoubleClick(int)),this,SLOT(ChangeVideoStatus(int)));

    layout = new QGridLayout(this);
    layout->addWidget(Video1,0,0);
    layout->addWidget(Video2,0,1);
    layout->addWidget(Video3,1,0);
    layout->addWidget(Video4,1,1);
    layout->setMargin(0);
    layout->setSpacing(2);

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
        //错误信息
        NET_DVR_GetLastError = (pfNET_DVR_GetLastError)library->resolve("NET_DVR_GetLastError");

        // 初始化
        NET_DVR_Init();
        //设置连接时间与重连时间
        NET_DVR_SetConnectTime(2000, 1);
        NET_DVR_SetReconnect(10000, true);

        //设置抓图模式为bmp
        NET_DVR_SetCapturePictureMode(0);

        _lUserID1 = NVR_Login(DVRIP,"admin","a12345678");
        if(_lUserID1 >= 0){
            qDebug()<<"ddddd";
            _lRealHandle1 = PlayVideo(Video1,_lUserID1,PassID1);
            _lRealHandle2 = PlayVideo(Video2,_lUserID1,PassID2);
            _lRealHandle3 = PlayVideo(Video3,_lUserID1,PassID3);
        }
    }
    else{
        QMessageBox::information(this,tr("错误"),library->errorString(),0,0,0);
    }
}


PlayViedo::~PlayViedo()
{
    if(loadSuccess){
        NET_DVR_StopRealPlay(_lRealHandle1);
        NET_DVR_Logout(_lUserID1);
        NET_DVR_Cleanup();
    }
}

long PlayViedo::NVR_Login(char *NVRIP, char *User, char *Secret)
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

    return lUserID;
}

long PlayViedo::PlayVideo(myLabel *video, long _lUserID, int passID)
{
    //启动预览并设置回调数据流
    LONG _lRealHandle;
    HWND hWnd = (HWND)video->winId();//获取窗口句柄
    NET_DVR_PREVIEWINFO struPlayInfo;
    memset(&struPlayInfo,0,sizeof(NET_DVR_PREVIEWINFO));
    struPlayInfo.hPlayWnd = hWnd;         //需要SDK解码时句柄设为有效值，仅取流不解码时可设为空
    struPlayInfo.lChannel = passID;       //预览通道号
    struPlayInfo.dwStreamType = 0;       //0-主码流，1-子码流，2-码流3，3-码流4，以此类推
    struPlayInfo.dwLinkMode   = 0;       //0- TCP方式，1- UDP方式，2- 多播方式，3- RTP方式，4-RTP/RTSP，5-RSTP/HTTP
    struPlayInfo.bBlocked     = 1;       //0- 非阻塞取流，1- 阻塞取流

    _lRealHandle = NET_DVR_RealPlay_V40(_lUserID, &struPlayInfo, NULL, NULL);
    if (_lRealHandle < 0)
    {
        printf("NET_DVR_RealPlay_V40 error\n");
//        NET_DVR_Logout(_lUserID);
//        NET_DVR_Cleanup();
        return -1;
    }

    return _lRealHandle;
}


void PlayViedo::CaptureBmpPic(QString filename1, QString filename2, QString filename3)
{
    if(loadSuccess){
        NET_DVR_CapturePicture(_lRealHandle1,filename1.toLocal8Bit().data());
        NET_DVR_CapturePicture(_lRealHandle2,filename2.toLocal8Bit().data());
        NET_DVR_CapturePicture(_lRealHandle3,filename3.toLocal8Bit().data());
    }
}

void PlayViedo::ChangeVideoStatus(int ID)
{
    if(VideoStatus == 0){
        switch (ID) {
        case 1:
            layout->addWidget(Video1,0,0,2,2);
            Video1->setHidden(false);
            Video2->setHidden(true);
            Video3->setHidden(true);
            Video4->setHidden(true);
            VideoStatus = 1;
            break;
        case 2:
            layout->addWidget(Video2,0,0,2,2);
            Video1->setHidden(true);
            Video2->setHidden(false);
            Video3->setHidden(true);
            Video4->setHidden(true);
            VideoStatus = 2;
            break;
        case 3:
            layout->addWidget(Video3,0,0,2,2);
            Video1->setHidden(true);
            Video2->setHidden(true);
            Video3->setHidden(false);
            Video4->setHidden(true);
            VideoStatus = 3;
            break;
        case 4:
            layout->addWidget(Video4,0,0,2,2);
            Video1->setHidden(true);
            Video2->setHidden(true);
            Video3->setHidden(true);
            Video4->setHidden(false);
            VideoStatus = 4;
            break;
        default:
            break;
        }
    }else{
        switch (ID) {
        case 1:
            layout->addWidget(Video1,0,0);
            Video1->setHidden(false);
            Video2->setHidden(false);
            Video3->setHidden(false);
            Video4->setHidden(false);
            VideoStatus = 0;
            break;
        case 2:
            layout->addWidget(Video2,0,1);
            Video1->setHidden(false);
            Video2->setHidden(false);
            Video3->setHidden(false);
            Video4->setHidden(false);
            VideoStatus = 0;
            break;
        case 3:
            layout->addWidget(Video3,1,0);
            Video1->setHidden(false);
            Video2->setHidden(false);
            Video3->setHidden(false);
            Video4->setHidden(false);
            VideoStatus = 0;
            break;
        case 4:
            layout->addWidget(Video4,1,1);
            Video1->setHidden(false);
            Video2->setHidden(false);
            Video3->setHidden(false);
            Video4->setHidden(false);
            VideoStatus = 0;
            break;
        default:
            break;
        }
    }
    qDebug()<<ID;
}
