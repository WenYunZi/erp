#include "shengchanfenbudlg.h"

extern mymysql db;

shengchanfenbuDlg::shengchanfenbuDlg(QWidget *parent) :
    QDialog(parent)
{
    SQL = "SELECT B.CheNumber 车辆号码,B.USERCHE 驾驶员,B.GCNAME 工程名称,B.JIAOZHUBW 浇筑部位,B.phbNumber 任务名称,\
            D.StrengthGrade 砼等级,B.CheTime 时间,\
            B.Z 每车方量,\
              SUM(CASE Material WHEN '砂' THEN SJMAT ELSE 0 END) 砂,\
              SUM(CASE Material WHEN '水洗砂' THEN SJMAT ELSE 0 END) 水洗砂,\
              SUM(CASE Material WHEN '石子' THEN SJMAT ELSE 0 END) 石子,\
              SUM(CASE Material WHEN '细石' THEN SJMAT ELSE 0 END) 细石,\
              SUM(CASE Material WHEN '水泥1' THEN SJMAT ELSE 0 END) 水泥1,\
              SUM(CASE Material WHEN '水泥2' THEN SJMAT ELSE 0 END) 水泥2,\
              SUM(CASE Material WHEN '矿粉' THEN SJMAT ELSE 0 END) 矿粉,\
              SUM(CASE Material WHEN '粉煤灰' THEN SJMAT ELSE 0 END) 粉煤灰,\
              SUM(CASE Material WHEN '膨胀剂' THEN SJMAT ELSE 0 END) 膨胀剂,\
              SUM(CASE Material WHEN '外加剂1' THEN SJMAT ELSE 0 END) 外加剂1,\
              IF(SUM(CASE Material WHEN '外加剂1' THEN IF((LOCATE('防冻',MATNAME)>0),1,0) ELSE 0 END)>0,'是','否') 外加剂1防冻,\
              SUM(CASE Material WHEN '外加剂2' THEN SJMAT ELSE 0 END) 外加剂2,\
              IF(SUM(CASE Material WHEN '外加剂2' THEN IF((LOCATE('防冻',MATNAME)>0),1,0) ELSE 0 END)>0,'是','否') 外加剂2防冻,\
              SUM(CASE Material WHEN '外加剂3' THEN SJMAT ELSE 0 END) 增效剂,\
              SUM(CASE Material WHEN '清水' THEN SJMAT ELSE 0 END) 清水,\
              recordNo 记录号,unit 生产机组\
           FROM HISTDATA2 A LEFT JOIN (SELECT *,ROUND(SUM(SUMPS),1) Z FROM HISTDATA GROUP BY bsqk) B ON (A.CHETIME=B.CheTime and A.JIZUNO=B.unit) \
           LEFT JOIN (SELECT * FROM UnitMaterialSetting) C ON (C.CorrespondingField=A.FILED AND C.SubordinateUnit=A.JIZUNO) \
           LEFT JOIN (SELECT * FROM ProductionTaskList) D ON (D.TaskNumber=B.phbNumber)\
           WHERE A.CHETIME BETWEEN '%1' AND '%2' GROUP BY A.JIZUNO,A.CHETIME ORDER BY recordNo limit 0";

    QLabel *label1 = new QLabel(tr("日期"),this);
    label1->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    QLabel *label2 = new QLabel(tr("-"),this);
    label2->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);

    ProductedVolumeLabel = new QLabel(this);
    ProductedVolumeLabel->setStyleSheet("color:red");

    UnitNoCheck = new QCheckBox(tr("机组"),this);

    UnitNoCombox = new QComboBox(this);
    db.sql_fillComboBoxItem("select UnitName from UnitSetting",UnitNoCombox);

    dateEdit1 = new QDateTimeEdit(this);
    dateEdit1->setDate(QDate::currentDate().addDays(-1));
    dateEdit1->setTime(QTime::fromString("00:00:00","hh:mm:ss"));
    dateEdit1->setCalendarPopup(true);
    dateEdit2 = new QDateTimeEdit(this);
    dateEdit2->setDate(QDate::currentDate());
    dateEdit2->setTime(QTime::fromString("00:00:00","hh:mm:ss"));
    dateEdit2->setCalendarPopup(true);

    chaxunBtn = new QPushButton(tr("查询"),this);
    chaxunBtn->setFixedWidth(130);
    connect(chaxunBtn,SIGNAL(clicked()),this,SLOT(on_chaxunBtn()));
    daochuBtn = new QPushButton(tr("导出"),this);
    daochuBtn->setFixedWidth(130);
    connect(daochuBtn,SIGNAL(clicked()),this,SLOT(on_daochuBtn()));

    view = new QTableView(this);
    db.showview(SQL,view,&model);

    view2Excel = new myExcel(this);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(label1,0);
    hlayout->addWidget(dateEdit1,1);
    hlayout->addWidget(label2,0);
    hlayout->addWidget(dateEdit2,1);
    hlayout->addWidget(UnitNoCheck,0);
    hlayout->addWidget(UnitNoCombox,1);
    hlayout->addWidget(chaxunBtn,1);
    hlayout->addWidget(daochuBtn,1);
    hlayout->addWidget(ProductedVolumeLabel,1);
    hlayout->addStretch(6);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(view);
}

void shengchanfenbuDlg::refresh()
{

}

void shengchanfenbuDlg::on_chaxunBtn()
{
    QString UnitNo;
    if(UnitNoCheck->checkState() == 2){
        UnitNo = QString(" and unit='%1'").arg(UnitNoCombox->currentText());
    }

    QString searchSQL = QString("SELECT D.DeliveryVehicle 车辆号码,D.Driver 驾驶员,D.Engineering 工程名称,D.PouringPosition 浇筑部位,B.phbNumber 任务名称,\
                                D.StrengthGrade 砼等级,B.CheTime 时间,\
                                B.PRODUCTVOLUME 每车方量,\
                                    SUM(CASE Material WHEN '砂' THEN SJMAT ELSE 0 END) 砂,\
                                    SUM(CASE Material WHEN '水洗砂' THEN SJMAT ELSE 0 END) 水洗砂,\
                                    SUM(CASE Material WHEN '石子' THEN SJMAT ELSE 0 END) 石子,\
                                    SUM(CASE Material WHEN '细石' THEN SJMAT ELSE 0 END) 细石,\
                                    SUM(CASE Material WHEN '水泥1' THEN SJMAT ELSE 0 END) 水泥1,\
                                    SUM(CASE Material WHEN '水泥2' THEN SJMAT ELSE 0 END) 水泥2,\
                                    SUM(CASE Material WHEN '矿粉' THEN SJMAT ELSE 0 END) 矿粉,\
                                    SUM(CASE Material WHEN '粉煤灰' THEN SJMAT ELSE 0 END) 粉煤灰,\
                                    SUM(CASE Material WHEN '膨胀剂' THEN SJMAT ELSE 0 END) 膨胀剂,\
                                    SUM(CASE Material WHEN '外加剂1' THEN IF((LOCATE('防冻',MATNAME)>0),0,SJMAT) ELSE 0 END) 外加剂1,\
                                    SUM(CASE Material WHEN '外加剂1' THEN IF((LOCATE('防冻',MATNAME)>0),SJMAT,0) ELSE 0 END) 防冻剂1,\
                                    SUM(CASE Material WHEN '外加剂2' THEN IF((LOCATE('防冻',MATNAME)>0),0,SJMAT) ELSE 0 END) 外加剂2,\
                                    SUM(CASE Material WHEN '外加剂2' THEN IF((LOCATE('防冻',MATNAME)>0),SJMAT,0) ELSE 0 END) 防冻剂2,\
                                    SUM(CASE Material WHEN '外加剂3' THEN SJMAT ELSE 0 END) 增效剂,\
                                    SUM(CASE Material WHEN '清水' THEN SJMAT ELSE 0 END) 清水,\
                                    recordNo 记录号,JIZUNO 生产机组\
                                FROM HISTDATA2 A LEFT JOIN (SELECT phbNumber,bsqk,unit,CheTime,ROUND(SUM(SUMPS),1) PRODUCTVOLUME FROM HISTDATA GROUP BY bsqk,unit) B ON (A.recordNo=B.bsqk and A.JIZUNO=B.unit)\
                                LEFT JOIN (SELECT CorrespondingField,SubordinateUnit,Material FROM UnitMaterialSetting) C ON (C.CorrespondingField=A.FILED AND C.SubordinateUnit=A.JIZUNO) \
                                LEFT JOIN (SELECT DeliveryVehicle,Driver,Engineering,PouringPosition,StrengthGrade,RecordNumber FROM ProductionNotice) D ON (D.RecordNumber=A.recordNo)\
                                WHERE A.CHETIME BETWEEN '%1' AND '%2' %3 GROUP BY A.JIZUNO,A.recordNo ORDER BY recordNo")
                                .arg(dateEdit1->dateTime().toString("yyyy-MM-dd hh:mm:ss"),dateEdit2->dateTime().toString("yyyy-MM-dd hh:mm:ss"),UnitNo);
    db.showview(searchSQL.toStdString().data(),view,&model);

    double total = 0;
    int    rowCount = model->rowCount();
    for(int i=0; i<rowCount; i++){
        total += model->item(i,7)->text().toDouble();
    }
    ProductedVolumeLabel->setText(QString("合计： 生产方量%1方").arg(total));
}

void shengchanfenbuDlg::on_daochuBtn()
{
    view2Excel->Table2ExcelByHtml(view,QString("生产消耗分布表"));
}
