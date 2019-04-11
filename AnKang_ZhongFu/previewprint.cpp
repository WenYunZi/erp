#include "previewprint.h"

extern pubfunc pub;
extern QString userName;
extern QString whetherCheckSend;

PreviewPrint::PreviewPrint(QWidget *parent) :
    QDialog(parent)
{
    this->setFixedSize(683,370);
    this->setWindowTitle(tr("打印预览"));
    //this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint|Qt::Tool);

    m_report = new QAxObject(this);//报表主体对象
    m_report->setControl("{4764040E-4222-4DEC-9F2E-82D46E212B3A}");

    this->setAutoFillBackground(true);
    QPalette palette;
    QPixmap pixmap(":image/PreviewPrint.png");
    palette.setBrush(QPalette::Window, QBrush(pixmap));
    this->setPalette(palette);

    isPrint = false;

    int res = db.sql_connect(pub.read_hostip(),"dbuser1","dbuser1","akzf_db");
    if(res == -1){
        this->close();
        return;
    }

    //任务单号
    RenwudanNoLineEdit = new QLineEdit(this);
    StationNumLineEdit->setReadOnly(true);
    //计划方量
    JihuafangliangLineEdit = new QLineEdit(this);
    JihuafangliangLineEdit->setReadOnly(true);

    //运距
    YunjuLineEdit = new QLineEdit(this);
    YunjuLineEdit->setReadOnly(true);

    //搅拌站
    StationNumLineEdit = new QLineEdit(this);
    StationNumLineEdit->setGeometry(121,205,96,21);
    StationNumLineEdit->setReadOnly(true);
    //生产日期
    ProductTimeLineEdit = new QLineEdit(this);
    ProductTimeLineEdit->setGeometry(505,73,139,21);
    ProductTimeLineEdit->setReadOnly(false);
    //工程名称
    EngineerLineEdit = new QLineEdit(this);
    EngineerLineEdit->setGeometry(121,73,298,21);
    EngineerLineEdit->setReadOnly(true);
    //施工部位
    PourPostionLineEdit = new QLineEdit(this);
    PourPostionLineEdit->setGeometry(121,153,298,21);
    PourPostionLineEdit->setReadOnly(true);
    //委托单位
    CustomerLineEdit = new QLineEdit(this);
    CustomerLineEdit->setGeometry(121,100,298,21);
    CustomerLineEdit->setReadOnly(true);
    //强度等级
    StrengthGradeLineEdit = new QLineEdit(this);
    StrengthGradeLineEdit->setGeometry(121,179,96,21);
    StrengthGradeLineEdit->setReadOnly(true);
    //输送方式
    PourMethodCombox = new QComboBox(this);
    PourMethodCombox->setGeometry(305,205,114,21);
    db.sql_fillComboBoxItem("select PouringMethod from PouringMethod",PourMethodCombox);
    //本车方量
    ShippingVolumeLineEdit = new QLineEdit(this);
    ShippingVolumeLineEdit->setGeometry(427,232,71,21);
    //累计方量
    CumulativeVolumeLineEdit = new QLineEdit(this);
    CumulativeVolumeLineEdit->setGeometry(585,232,59,21);
    //车次
    CumulativeNumberLineEdit = new QLineEdit(this);
    CumulativeNumberLineEdit->setGeometry(305,232,36,21);
    //塌落度
    SlumpLineEdit = new QLineEdit(this);
    SlumpLineEdit->setGeometry(305,179,114,21);
    SlumpLineEdit->setReadOnly(true);
    //出站时间
    OutboundTimeLineEdit = new QLineEdit(this);
    OutboundTimeLineEdit->setGeometry(505,100,139,21);
    OutboundTimeLineEdit->setReadOnly(false);
    //配比编号
    PhbNumLineEdit = new QLineEdit(this);
    PhbNumLineEdit->setGeometry(505,179,139,21);
    PhbNumLineEdit->setReadOnly(true);
    //发货员
    DeliveryLineEdit = new QLineEdit(this);
    DeliveryLineEdit->setGeometry(307,258,111,21);
    DeliveryLineEdit->setReadOnly(true);
    DeliveryLineEdit->setText(userName);

    if(whetherCheckSend == "有"){
        RenwudanNoLineEdit->setReadOnly(false);
        JihuafangliangLineEdit->setReadOnly(false);
        YunjuLineEdit->setReadOnly(false);
        StationNumLineEdit->setReadOnly(false);
        ProductTimeLineEdit->setReadOnly(false);
        EngineerLineEdit->setReadOnly(false);
        PourPostionLineEdit->setReadOnly(false);
        CustomerLineEdit->setReadOnly(false);
        StrengthGradeLineEdit->setReadOnly(false);
        ShippingVolumeLineEdit->setReadOnly(false);
        CumulativeVolumeLineEdit->setReadOnly(false);
        CumulativeNumberLineEdit->setReadOnly(false);
        SlumpLineEdit->setReadOnly(false);
        OutboundTimeLineEdit->setReadOnly(false);
        PhbNumLineEdit->setReadOnly(false);
        DeliveryLineEdit->setReadOnly(false);
    }

    printBtn = new QPushButton(tr("打印"),this);
    printBtn->setGeometry(465,322,80,26);
    connect(printBtn,SIGNAL(clicked()),this,SLOT(on_printBtn()));\

    cancelBtn = new QPushButton(tr("取消"),this);
    cancelBtn->setGeometry(564,322,80,26);
    connect(cancelBtn,SIGNAL(clicked()),this,SLOT(on_cancelBtn()));

    //车号
    VehicleCombox = new QComboBox(this);
    VehicleCombox->setGeometry(121,232,96,21);
    VehicleCombox->setEditable(true);
    db.sql_fillComboBoxItem("select LicensePlate from ConcreteVehicleInformation order by LicensePlate+0",VehicleCombox);
    connect(VehicleCombox,SIGNAL(editTextChanged(QString)),this,SLOT(on_VehicleCombox()));

    //司机
    DriverCombox = new QComboBox(this);
    DriverCombox->setGeometry(121,258,96,21);
    DriverCombox->setEditable(true);
    db.sql_fillComboBoxItem("select Driver2 from ConcreteVehicleInformation group by Driver2",DriverCombox);
}

void PreviewPrint::init(QString cheNumber,QString cheName, QString recordNum)
{
    this->cheNumber = cheNumber;
    this->cheName = cheName;

    QString searchTask = QString("select TaskList,ShippingVolume,StrengthGrade,Contacts,FaHuoCustomer,PouringPosition,ContactNumber,Engineering,PouringMethod,\
                                 CumulativeVolume,ConstructionSite,Slump,OutboundTime,TemplateName,Price,ContractNumber,Mileage,CumulativeNumber,FreightPrice,\
                                 RecordNumber from ProductionNotice where RecordNumber=%1").arg(recordNum);

    QStringList resList = db.CreatStrList(searchTask);

    if(resList.count() == 20){
        TaskNumber = resList.at(0);
        shengchanfangliang = resList.at(1);
        StrengthGrade = resList.at(2);
        Contacts = resList.at(3);
        Customer = resList.at(4);
        PouringPosition = resList.at(5);
        ContactNumber = resList.at(6);
        Engineering = resList.at(7);
        PouringMethod = resList.at(8);
        ContractCompletion = resList.at(9);
        ConstructionSite = resList.at(10);
        Slump = resList.at(11);
        SupplyTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        Template = resList.at(13);
        PricePerParty = resList.at(14);
        ContractNumber = resList.at(15);
        Distance = resList.at(16);
        fahuocheci = resList.at(17);
        FreightPrice  = resList.at(18);
        RecordNumber = resList.at(19);
    }

    Unit = QString("%1#机组").arg(pub.readJizuBianhao());

    StationNumLineEdit->setText(Unit);
    ProductTimeLineEdit->setText(SupplyTime.left(10)+" "+recordNum);
    EngineerLineEdit->setText(Engineering);
    PourPostionLineEdit->setText(PouringPosition);
    CustomerLineEdit->setText(Customer);
    StrengthGradeLineEdit->setText(StrengthGrade);
    PourMethodCombox->setCurrentText(PouringMethod);
    ShippingVolumeLineEdit->setText(shengchanfangliang);
    CumulativeVolumeLineEdit->setText(ContractCompletion);
    CumulativeNumberLineEdit->setText(fahuocheci);
    SlumpLineEdit->setText(Slump);
    OutboundTimeLineEdit->setText(SupplyTime.right(8));
    PhbNumLineEdit->setText(Template);
    DriverCombox->setCurrentText(cheName);
    VehicleCombox->setCurrentText(cheNumber);

    RenwudanNoLineEdit->setText(TaskNumber);
    QString JiHuaFangLiang = QString("select PlannedQuantity from productiontasklist where TaskNumber=%1").arg(RenwudanNoLineEdit->text());
    QStringList JiHuaFangLiangList = db.CreatStrList(JiHuaFangLiang);
    JihuafangliangLineEdit->setText(JiHuaFangLiangList.at(0));
    QString YunJu = QString("select Distance from salescontractcustomerengineeringform where CustomerName = '%1' and ProjectName = '%2'").arg(CustomerLineEdit->text(),EngineerLineEdit->text());
    QStringList YunJuList = db.CreatStrList(YunJu);
    YunjuLineEdit->setText(YunJuList.at(0));
}

void PreviewPrint::on_VehicleCombox()
{
    QString searchSQL = QString("select Driver2 from ConcreteVehicleInformation where LicensePlate='%1';").arg(VehicleCombox->currentText());
    DriverCombox->setCurrentText(db.sql_fetchrow_plus(searchSQL,0));
}

void PreviewPrint::on_printBtn()
{
    QVariantList params1,params2,params3,params4,params5,params6,params7,params8,params9,params10,params11,params12,params13,params14,params15,params16,params17,params18,params19;
    params1<<"GCMC"<<QString("\"")+EngineerLineEdit->text()+QString("\"");
    params2<<"SGDW"<<QString("\"")+CustomerLineEdit->text()+QString("\"");
    params3<<"SGBW"<<QString("\"")+PourPostionLineEdit->text()+QString("\"");
    params4<<"QDUDJ"<<QString("\"")+StrengthGradeLineEdit->text()+QString("\"");
    params5<<"JBZ"<<QString("\"")+StationNumLineEdit->text()+QString("\"");
    params6<<"CHENO"<<QString("\"")+VehicleCombox->currentText()+QString("\"");
    params7<<"SJNAME"<<QString("\"")+DriverCombox->currentText()+QString("\"");
    params8<<"TLD"<<QString("\"")+SlumpLineEdit->text()+QString("\"");
    params9<<"JZFS"<<QString("\"")+PourMethodCombox->currentText()+QString("\"");
    params10<<"CHECI"<<QString("\"")+CumulativeNumberLineEdit->text()+QString("\"");
    params11<<"SCRQ"<<QString("\"")+ProductTimeLineEdit->text()+QString("\"");
    params12<<"CZSJ"<<QString("\"")+OutboundTimeLineEdit->text()+QString("\"");
    params13<<"PHBNO"<<QString("\"")+PhbNumLineEdit->text()+QString("\"");
    params14<<"BCFL"<<QString("\"")+ShippingVolumeLineEdit->text()+QString("\"");
    params15<<"LJFL"<<QString("\"")+CumulativeVolumeLineEdit->text()+QString("\"");
    params16<<"FHR"<<QString("\"")+DeliveryLineEdit->text()+QString("\"");

    params17<<"RWDH"<<QString("\"")+RenwudanNoLineEdit->text()+QString("\"");
    params18<<"JHFL"<<QString("\"")+JihuafangliangLineEdit->text()+QString("\"");
    params19<<"YJ"<<QString("\"")+YunjuLineEdit->text()+QString("\"");



    //打印发货单
    m_report->dynamicCall("LoadReportFromFile(QString)", "report/CurOut.fr3");
    m_report->dynamicCall("SetVariable(QString, QVariant)", params1);
    m_report->dynamicCall("SetVariable(QString, QVariant)", params2);
    m_report->dynamicCall("SetVariable(QString, QVariant)", params3);
    m_report->dynamicCall("SetVariable(QString, QVariant)", params4);
    m_report->dynamicCall("SetVariable(QString, QVariant)", params5);
    m_report->dynamicCall("SetVariable(QString, QVariant)", params6);
    m_report->dynamicCall("SetVariable(QString, QVariant)", params7);
    m_report->dynamicCall("SetVariable(QString, QVariant)", params8);
    m_report->dynamicCall("SetVariable(QString, QVariant)", params9);
    m_report->dynamicCall("SetVariable(QString, QVariant)", params10);
    m_report->dynamicCall("SetVariable(QString, QVariant)", params11);
    m_report->dynamicCall("SetVariable(QString, QVariant)", params12);
    m_report->dynamicCall("SetVariable(QString, QVariant)", params13);
    m_report->dynamicCall("SetVariable(QString, QVariant)", params14);
    m_report->dynamicCall("SetVariable(QString, QVariant)", params15);
    m_report->dynamicCall("SetVariable(QString, QVariant)", params16);
    m_report->dynamicCall("SetVariable(QString, QVariant)", params17);
    m_report->dynamicCall("SetVariable(QString, QVariant)", params18);
    m_report->dynamicCall("SetVariable(QString, QVariant)", params19);
    m_report->dynamicCall("PrepareReport(bool)", "true");

    keybd_event(VK_RETURN,0,0,0);
    keybd_event(VK_RETURN,0,KEYEVENTF_KEYUP,0);

    m_report->dynamicCall("PrintReport()");

    //更新生产通知单和运费
    QString panduanSQL = QString("select ConsignmentNumber from SalesLedger where ConsignmentNumber=%1;").arg(RecordNumber);
    int ret = db.row_count(panduanSQL);
    if(ret == 0){
        //事务开始
        db.sql_exec("begin");
        //更新发货单
        QString updateSQL = QString("update ProductionNotice set WhetherDelivery='是',OutboundTime='%1',caozuoyuan='%3' where RecordNumber=%2;").arg(SupplyTime,RecordNumber,userName);
        int res = db.sql_exec(updateSQL);
        if(res == -1){
            db.sql_exec("rollback");
            return;
        }
        //更新总任务单中的已完成任务量，发货车次
        QString updateTaskListSQL = QString("update ProductionTaskList set fahuocheci='%1',ContractCompletion='%2' where TaskNumber='%3';")
                .arg(CumulativeNumberLineEdit->text(),CumulativeVolumeLineEdit->text(),TaskNumber);
        res = db.sql_exec(updateTaskListSQL);
        if(res == -1){
            db.sql_exec("rollback");
            return;
        }
        //事务结束
        db.sql_exec("commit");
    }

    db.sql_disconnet();
    this->close();
}

void PreviewPrint::on_cancelBtn()
{
    db.sql_disconnet();
    this->close();
}
