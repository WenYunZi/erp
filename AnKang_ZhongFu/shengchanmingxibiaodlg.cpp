#include "shengchanmingxibiaodlg.h"

extern mymysql db;

shengchanmingxibiaoDlg::shengchanmingxibiaoDlg(QWidget *parent) :
    QDialog(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setFixedSize(600,360);

    library = new QLibrary("MyReportDll");

    //设置背景图片
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/image/baobiao.jpg")));
    setPalette(palette);

    QFont ft;
    ft.setPixelSize(15);

    QLabel *label1 = new QLabel(tr("生产日期"),this);
    label1->setGeometry(37,65,100,20);
    label1->setFont(ft);
    QLabel *label2 = new QLabel(tr("——"),this);
    label2->setGeometry(280,65,50,20);
    label2->setAlignment(Qt::AlignCenter);
    label2->setFont(ft);
    QLabel *label3 = new QLabel(tr("生产报表"),this);
    label3->setAlignment(Qt::AlignCenter);
    label3->setGeometry(200,20,200,25);
    ft.setPixelSize(25);
    label3->setFont(ft);

    dateEdit1 = new QDateEdit(QDate::currentDate(),this);
    dateEdit1->setGeometry(110,65,170,20);
    dateEdit1->setCalendarPopup(true);
    dateEdit2 = new QDateEdit(QDate::currentDate(),this);
    dateEdit2->setGeometry(330,65,170,20);
    dateEdit2->setCalendarPopup(true);


    ft.setPixelSize(15);
    checkBox1 = new QCheckBox(this);
    checkBox1->setText(tr("客户名称"));
    checkBox1->setFont(ft);
    checkBox1->setGeometry(20,105,100,20);
    checkBox2 = new QCheckBox(this);
    checkBox2->setText(tr("工程名称"));
    checkBox2->setFont(ft);
    checkBox2->setGeometry(20,145,100,20);
    checkBox3 = new QCheckBox(this);
    checkBox3->setText(tr("厂地名称"));
    checkBox3->setFont(ft);
    checkBox3->setGeometry(20,185,100,20);
    checkBox4 = new QCheckBox(this);
    checkBox4->setText(tr("原料名称"));
    checkBox4->setFont(ft);
    checkBox4->setGeometry(20,225,100,20);
    checkBox6 = new QCheckBox(this);
    checkBox6->setText(tr("生产机组"));
    checkBox6->setFont(ft);
    checkBox6->setGeometry(290,185,100,20);

    comBox1 = new QComboBox(this);
    comBox1->setGeometry(110,105,270,20);
    comBox1->setEditable(true);
    comBox2 = new QComboBox(this);
    comBox2->setGeometry(110,145,270,20);
    comBox2->setEditable(true);
    comBox3 = new QComboBox(this);
    comBox3->setGeometry(110,185,170,20);
    comBox3->setEditable(true);
    comBox4 = new QComboBox(this);
    comBox4->setGeometry(110,225,170,20);
    comBox4->setEditable(true);
    comBox5 = new QComboBox(this);
    comBox5->setGeometry(380,185,170,20);
    comBox5->setEditable(true);

    btn1 = new QPushButton(this);
    connect(btn1,SIGNAL(clicked()),this,SLOT(on_kehuhuizong()));
    btn1->setText(tr("客户汇总"));
    btn1->setGeometry(30,255,120,30);
    btn2 = new QPushButton(this);
    connect(btn2,SIGNAL(clicked()),this,SLOT(on_meichexiaohao()));
    btn2->setText(tr("每车消耗"));
    btn2->setGeometry(170,255,120,30);
    btn3 = new QPushButton(this);
    connect(btn3,SIGNAL(clicked()),this,SLOT(on_meipanxiaohao()));
    btn3->setText(tr("每盘消耗"));
    btn3->setGeometry(310,255,120,30);
    btn4 = new QPushButton(this);
    connect(btn4,SIGNAL(clicked()),this,SLOT(on_xiaohaohuizong()));
    btn4->setText(tr("消耗汇总"));
    btn4->setGeometry(450,255,120,30);
    btn5 = new QPushButton(this);
    connect(btn5,SIGNAL(clicked()),this,SLOT(on_cangweixiaohao()));
    btn5->setText(tr("仓位消耗"));
    btn5->setGeometry(30,295,120,30);
    btn6 = new QPushButton(this);
    connect(btn6,SIGNAL(clicked()),this,SLOT(on_chanpinxiaohao()));
    btn6->setText(tr("产品消耗"));
    btn6->setGeometry(170,295,120,30);
    btn7 = new QPushButton(this);
    connect(btn7,SIGNAL(clicked()),this,SLOT(on_kehuxiaohao()));
    btn7->setText(tr("客户消耗"));
    btn7->setGeometry(310,295,120,30);
    btn8 = new QPushButton(this);
    connect(btn8,SIGNAL(clicked()),this,SLOT(on_biaohaohuizong()));
    btn8->setText(tr("标号汇总"));
    btn8->setGeometry(450,295,120,30);


    toolBtn = new QToolButton(this);
    connect(toolBtn,SIGNAL(clicked()),this,SLOT(on_close()));
    toolBtn->setIcon(QIcon(":/image/close.png"));
    toolBtn->setGeometry(575,0,25,25);

    const char *fillcomBox1SQL = "select CustomerName from CustomerFiles;";
    db.sql_fillComboBoxItem(fillcomBox1SQL,comBox1);

    const char *fillcomBox2SQL = "select ProjectName from ProjectName;";
    db.sql_fillComboBoxItem(fillcomBox2SQL,comBox2);

    const char *fillcomBox3SQL = "select PlantName from FactorySetting;";
    db.sql_fillComboBoxItem(fillcomBox3SQL,comBox3);

    const char *fillcomBox4SQL = "select Material from MaterialSetting;";
    db.sql_fillComboBoxItem(fillcomBox4SQL,comBox4);

    const char *fillcomBox5SQL = "select UnitName from UnitSetting;";
    db.sql_fillComboBoxItem(fillcomBox5SQL,comBox5);
}

shengchanmingxibiaoDlg::~shengchanmingxibiaoDlg()
{

}

void shengchanmingxibiaoDlg::on_kehuhuizong()
{
    char *baobiaoSQL = new char[2000];
    memset(baobiaoSQL,0,2000);

    char kehumingcheng[200]      = {0};
    char gongchengmingcheng[100] = {0};
    char changdimingcheng[100]   = {0};
    char shengchanjizu[100]      = {0};

    //utf8--->gbk
    QByteArray text1 = comBox1->currentText().toLocal8Bit();
    QByteArray text2 = comBox2->currentText().toLocal8Bit();
    QByteArray text3 = comBox3->currentText().toLocal8Bit();
    QByteArray text5 = comBox5->currentText().toLocal8Bit();

    if(checkBox1->checkState() == 2){
        sprintf(kehumingcheng,"and USERNAME='%s'",text1.data());
    }
    if(checkBox2->checkState() == 2){
        sprintf(gongchengmingcheng,"and GCNAME='%s'",text2.data());
    }
    if(checkBox3->checkState() == 2){
        sprintf(changdimingcheng,"and PlantName='%s'",text3.data());
    }
    if(checkBox6->checkState() == 2){
        sprintf(shengchanjizu,"and unit='%s'",text5.data());
    }

    sprintf(baobiaoSQL,"SELECT QDUDJ,GCNAME,unit,USERNAME,round(SUM(SUMPS),1) \
            FROM HISTDATA where CURDATE between '%s' and '%s'\
            %s %s %s %s GROUP BY unit,QDUDJ ORDER BY USERNAME,GCNAME,unit;",\
            dateEdit1->date().toString("yyyy-MM-dd").toStdString().data(),\
            dateEdit2->date().addDays(1).toString("yyyy-MM-dd").toStdString().data(),kehumingcheng,gongchengmingcheng,\
            changdimingcheng,shengchanjizu);
    if(library->load()){
        typedef void (*pFunc)(const char *,const char *);
        pFunc function=(pFunc)library->resolve("loadmyreport");
        if(function){
            function("./report/report5.fr3",baobiaoSQL);
        }
    }
    else{
        QMessageBox::information(this,tr("错误"),library->errorString());
    }
    delete [] baobiaoSQL;
}

void shengchanmingxibiaoDlg::on_meichexiaohao()
{
    char *baobiaoSQL = new char[2000];
    memset(baobiaoSQL,0,2000);

    char kehumingcheng[200]      = {0};
    char gongchengmingcheng[100] = {0};
    char changdimingcheng[100]   = {0};
    char shengchanjizu[100]      = {0};

    //utf8--->gbk
    QByteArray text1 = comBox1->currentText().toLocal8Bit();
    QByteArray text2 = comBox2->currentText().toLocal8Bit();
    QByteArray text3 = comBox3->currentText().toLocal8Bit();
    QByteArray text5 = comBox5->currentText().toLocal8Bit();

    if(checkBox1->checkState() == 2){
        sprintf(kehumingcheng,"and USERNAME='%s'",text1.data());
    }
    if(checkBox2->checkState() == 2){
        sprintf(gongchengmingcheng,"and GCNAME='%s'",text2.data());
    }
    if(checkBox3->checkState() == 2){
        sprintf(changdimingcheng,"and PlantName='%s'",text3.data());
    }
    if(checkBox6->checkState() == 2){
        sprintf(shengchanjizu,"and unit='%s'",text5.data());
    }

    sprintf(baobiaoSQL,"select *,round(SUM(SUMPS),1) from HISTDATA where CURDATE between '%s' and '%s'\
            %s %s %s %s  GROUP BY unit,CheTime ORDER BY USERNAME,unit,id;",\
            dateEdit1->date().toString("yyyy-MM-dd").toStdString().data(),\
            dateEdit2->date().addDays(1).toString("yyyy-MM-dd").toStdString().data(),kehumingcheng,gongchengmingcheng,\
            changdimingcheng,shengchanjizu);
    if(library->load()){
        typedef void (*pFunc)(const char *,const char *);
        pFunc function=(pFunc)library->resolve("loadmyreport");
        if(function){
            function("./report/report10.fr3",baobiaoSQL);
        }
    }
    else{
        QMessageBox::information(this,tr("错误"),library->errorString());
    }
    delete [] baobiaoSQL;
}

void shengchanmingxibiaoDlg::on_meipanxiaohao()
{
    char *baobiaoSQL = new char[2000];
    memset(baobiaoSQL,0,2000);

    char kehumingcheng[200]      = {0};
    char gongchengmingcheng[100] = {0};
    char changdimingcheng[100]   = {0};
    char shengchanjizu[100]      = {0};

    //utf8--->gbk
    QByteArray text1 = comBox1->currentText().toLocal8Bit();
    QByteArray text2 = comBox2->currentText().toLocal8Bit();
    QByteArray text3 = comBox3->currentText().toLocal8Bit();
    QByteArray text5 = comBox5->currentText().toLocal8Bit();

    if(checkBox1->checkState() == 2){
        sprintf(kehumingcheng,"and USERNAME='%s'",text1.data());
    }
    if(checkBox2->checkState() == 2){
        sprintf(gongchengmingcheng,"and GCNAME='%s'",text2.data());
    }
    if(checkBox3->checkState() == 2){
        sprintf(changdimingcheng,"and PlantName='%s'",text3.data());
    }
    if(checkBox6->checkState() == 2){
        sprintf(shengchanjizu,"and unit='%s'",text5.data());
    }

    sprintf(baobiaoSQL,"select *,round(SUM(SUMPS),1) from HISTDATA where CURDATE between '%s' and '%s'\
            %s %s %s %s GROUP BY unit,CheTime ORDER BY USERNAME,unit,id;",\
            dateEdit1->date().toString("yyyy-MM-dd").toStdString().data(),\
            dateEdit2->date().addDays(1).toString("yyyy-MM-dd").toStdString().data(),kehumingcheng,gongchengmingcheng,\
            changdimingcheng,shengchanjizu);
    if(library->load()){
        typedef void (*pFunc)(const char *,const char *);
        pFunc function=(pFunc)library->resolve("loadmyreport");
        if(function){
            function("./report/report8.fr3",baobiaoSQL);
        }
    }
    else{
        QMessageBox::information(this,tr("错误"),library->errorString());
    }
    delete [] baobiaoSQL;
}

void shengchanmingxibiaoDlg::on_xiaohaohuizong()
{
    char *baobiaoSQL = new char[2000];
    memset(baobiaoSQL,0,2000);

    char kehumingcheng[200]      = {0};
    char gongchengmingcheng[100] = {0};
    char changdimingcheng[100]   = {0};
    char shengchanjizu[100]      = {0};
    char yuanliaomingcheng[100]  = {0};

    //utf8--->gbk
    QByteArray text1 = comBox1->currentText().toLocal8Bit();
    QByteArray text2 = comBox2->currentText().toLocal8Bit();
    QByteArray text3 = comBox3->currentText().toLocal8Bit();
    QByteArray text4 = comBox4->currentText().toLocal8Bit();
    QByteArray text5 = comBox5->currentText().toLocal8Bit();

    if(checkBox1->checkState() == 2){
        sprintf(kehumingcheng,"and USERNAME='%s'",text1.data());
    }
    if(checkBox2->checkState() == 2){
        sprintf(gongchengmingcheng,"and GCNAME='%s'",text2.data());
    }
    if(checkBox3->checkState() == 2){
        sprintf(changdimingcheng,"and PlantName='%s'",text3.data());
    }
    if(checkBox4->checkState() == 2){
        sprintf(yuanliaomingcheng,"and MATNAME='%s'",text4.data());
    }
    if(checkBox6->checkState() == 2){
        sprintf(shengchanjizu,"and unit='%s'",text5.data());
    }

    sprintf(baobiaoSQL,"SELECT *,ROUND(SUM(SJMAT),1) FROM HISTDATA2 A \
            left join (select id,USERNAME,GCNAME,PlantName,unit from HISTDATA) B ON (A.ID=B.id) \
            where A.CURDATA between '%s' and '%s'\
            %s %s %s %s %s GROUP BY A.MATNAME ORDER BY A.FILED;",\
            dateEdit1->date().toString("yyyy-MM-dd").toStdString().data(),\
            dateEdit2->date().addDays(1).toString("yyyy-MM-dd").toStdString().data(),kehumingcheng,gongchengmingcheng,\
            changdimingcheng,shengchanjizu,yuanliaomingcheng);
    if(library->load()){
        typedef void (*pFunc)(const char *,const char *);
        pFunc function=(pFunc)library->resolve("loadmyreport");
        if(function){
            function("./report/report9.fr3",baobiaoSQL);
        }
    }
    else{
        QMessageBox::information(this,tr("错误"),library->errorString());
    }
    delete [] baobiaoSQL;
}

void shengchanmingxibiaoDlg::on_cangweixiaohao()
{
    char *baobiaoSQL = new char[2000];
    memset(baobiaoSQL,0,2000);

    char kehumingcheng[200]      = {0};
    char gongchengmingcheng[100] = {0};
    char changdimingcheng[100]   = {0};
    char shengchanjizu[100]      = {0};
    char yuanliaomingcheng[100]  = {0};

    //utf8--->gbk
    QByteArray text1 = comBox1->currentText().toLocal8Bit();
    QByteArray text2 = comBox2->currentText().toLocal8Bit();
    QByteArray text3 = comBox3->currentText().toLocal8Bit();
    QByteArray text4 = comBox4->currentText().toLocal8Bit();
    QByteArray text5 = comBox5->currentText().toLocal8Bit();

    if(checkBox1->checkState() == 2){
        sprintf(kehumingcheng,"and USERNAME='%s'",text1.data());
    }
    if(checkBox2->checkState() == 2){
        sprintf(gongchengmingcheng,"and GCNAME='%s'",text2.data());
    }
    if(checkBox3->checkState() == 2){
        sprintf(changdimingcheng,"and PlantName='%s'",text3.data());
    }
    if(checkBox4->checkState() == 2){
        sprintf(yuanliaomingcheng,"and MATNAME='%s'",text4.data());
    }
    if(checkBox6->checkState() == 2){
        sprintf(shengchanjizu,"and unit='%s'",text5.data());
    }

    sprintf(baobiaoSQL,"select *,ROUND(SUM(A.SJMAT),1) from HISTDATA2 A  \
            left join \
            (select CorrespondingField,Position from UnitMaterialCorrespondsToERPMaterial) B \
            on (A.FILED=B.CorrespondingField)\
            left join\
            (select id,USERNAME,GCNAME,PlantName,unit from HISTDATA) C\
            ON (A.ID=C.id) \
            where A.CURDATA between '%s' and '%s'\
            %s %s %s %s %s group by B.Position,A.MATNAME ORDER BY A.FILED;",\
            dateEdit1->date().toString("yyyy-MM-dd").toStdString().data(),\
            dateEdit2->date().addDays(1).toString("yyyy-MM-dd").toStdString().data(),kehumingcheng,gongchengmingcheng,\
            changdimingcheng,shengchanjizu,yuanliaomingcheng);
    if(library->load()){
        typedef void (*pFunc)(const char *,const char *);
        pFunc function=(pFunc)library->resolve("loadmyreport");
        if(function){
            function("./report/report10.fr3",baobiaoSQL);
        }
    }
    else{
        QMessageBox::information(this,tr("错误"),library->errorString());
    }
    delete [] baobiaoSQL;
}

void shengchanmingxibiaoDlg::on_chanpinxiaohao()
{
    char *baobiaoSQL = new char[2000];
    memset(baobiaoSQL,0,2000);

    char kehumingcheng[200]      = {0};
    char gongchengmingcheng[100] = {0};
    char changdimingcheng[100]   = {0};
    char shengchanjizu[100]      = {0};
    char yuanliaomingcheng[100]  = {0};

    //utf8--->gbk
    QByteArray text1 = comBox1->currentText().toLocal8Bit();
    QByteArray text2 = comBox2->currentText().toLocal8Bit();
    QByteArray text3 = comBox3->currentText().toLocal8Bit();
    QByteArray text4 = comBox4->currentText().toLocal8Bit();
    QByteArray text5 = comBox5->currentText().toLocal8Bit();

    if(checkBox1->checkState() == 2){
        sprintf(kehumingcheng,"and USERNAME='%s'",text1.data());
    }
    if(checkBox2->checkState() == 2){
        sprintf(gongchengmingcheng,"and GCNAME='%s'",text2.data());
    }
    if(checkBox3->checkState() == 2){
        sprintf(changdimingcheng,"and PlantName='%s'",text3.data());
    }
    if(checkBox4->checkState() == 2){
        sprintf(yuanliaomingcheng,"and MATNAME='%s'",text4.data());
    }
    if(checkBox6->checkState() == 2){
        sprintf(shengchanjizu,"and unit='%s'",text5.data());
    }

    sprintf(baobiaoSQL,"select *,ROUND(SUM(A.SJMAT),1) from HISTDATA2 A  \
            left join (select id,GCNAME,USERNAME,unit,PlantName,QDUDJ from HISTDATA) B on (A.ID=B.id)\
            where A.CURDATA between '%s' and '%s'\
            %s %s %s %s %s group by B.QDUDJ,A.MATNAME ORDER BY B.QDUDJ,A.FILED;",\
            dateEdit1->date().toString("yyyy-MM-dd").toStdString().data(),\
            dateEdit2->date().addDays(1).toString("yyyy-MM-dd").toStdString().data(),kehumingcheng,gongchengmingcheng,\
            changdimingcheng,shengchanjizu,yuanliaomingcheng);
    if(library->load()){
        typedef void (*pFunc)(const char *,const char *);
        pFunc function=(pFunc)library->resolve("loadmyreport");
        if(function){
            function("./report/report11.fr3",baobiaoSQL);
        }
    }
    else{
        QMessageBox::information(this,tr("错误"),library->errorString());
    }
    delete [] baobiaoSQL;
}

void shengchanmingxibiaoDlg::on_kehuxiaohao()
{
    char *baobiaoSQL = new char[2000];
    memset(baobiaoSQL,0,2000);

    char kehumingcheng[200]      = {0};
    char gongchengmingcheng[100] = {0};
    char changdimingcheng[100]   = {0};
    char shengchanjizu[100]      = {0};
    char yuanliaomingcheng[100]  = {0};

    //utf8--->gbk
    QByteArray text1 = comBox1->currentText().toLocal8Bit();
    QByteArray text2 = comBox2->currentText().toLocal8Bit();
    QByteArray text3 = comBox3->currentText().toLocal8Bit();
    QByteArray text4 = comBox4->currentText().toLocal8Bit();
    QByteArray text5 = comBox5->currentText().toLocal8Bit();

    if(checkBox1->checkState() == 2){
        sprintf(kehumingcheng,"and USERNAME='%s'",text1.data());
    }
    if(checkBox2->checkState() == 2){
        sprintf(gongchengmingcheng,"and GCNAME='%s'",text2.data());
    }
    if(checkBox3->checkState() == 2){
        sprintf(changdimingcheng,"and PlantName='%s'",text3.data());
    }
    if(checkBox4->checkState() == 2){
        sprintf(yuanliaomingcheng,"and MATNAME='%s'",text4.data());
    }
    if(checkBox6->checkState() == 2){
        sprintf(shengchanjizu,"and unit='%s'",text5.data());
    }

    sprintf(baobiaoSQL,"select *,ROUND(SUM(A.SJMAT),1) from HISTDATA2 A  \
            left join (select id,GCNAME,PlantName,unit,USERNAME from HISTDATA) B on (A.ID=B.id) \
            where A.CURDATA between '%s' and '%s'\
            %s %s %s %s %s group by B.USERNAME,A.MATNAME ORDER BY B.USERNAME,A.FILED;",\
            dateEdit1->date().toString("yyyy-MM-dd").toStdString().data(),\
            dateEdit2->date().addDays(1).toString("yyyy-MM-dd").toStdString().data(),kehumingcheng,gongchengmingcheng,\
            changdimingcheng,shengchanjizu,yuanliaomingcheng);
    if(library->load()){
        typedef void (*pFunc)(const char *,const char *);
        pFunc function=(pFunc)library->resolve("loadmyreport");
        if(function){
            function("./report/report12.fr3",baobiaoSQL);
        }
    }
    else{
        QMessageBox::information(this,tr("错误"),library->errorString());
    }
    delete [] baobiaoSQL;
}

void shengchanmingxibiaoDlg::on_biaohaohuizong()
{
    char *baobiaoSQL = new char[2000];
    memset(baobiaoSQL,0,2000);

    char kehumingcheng[200]      = {0};
    char gongchengmingcheng[100] = {0};
    char changdimingcheng[100]   = {0};
    char shengchanjizu[100]      = {0};

    //utf8--->gbk
    QByteArray text1 = comBox1->currentText().toLocal8Bit();
    QByteArray text2 = comBox2->currentText().toLocal8Bit();
    QByteArray text3 = comBox3->currentText().toLocal8Bit();
    QByteArray text5 = comBox5->currentText().toLocal8Bit();

    if(checkBox1->checkState() == 2){
        sprintf(kehumingcheng,"and USERNAME='%s'",text1.data());
    }
    if(checkBox2->checkState() == 2){
        sprintf(gongchengmingcheng,"and GCNAME='%s'",text2.data());
    }
    if(checkBox3->checkState() == 2){
        sprintf(changdimingcheng,"and PlantName='%s'",text3.data());
    }
    if(checkBox6->checkState() == 2){
        sprintf(shengchanjizu,"and unit='%s'",text5.data());
    }

    sprintf(baobiaoSQL,"select *,ROUND(SUM(SUMPS),1)  from HISTDATA  A \
            LEFT join (select id,sum(SUMPS) SUMSUMPS from HISTDATA) B ON (B.id LIKE '%%') \
            where A.CURDATE between '%s' and '%s' \
            %s %s %s %s group by QDUDJ ORDER BY ROUND(SUM(SUMPS),1) DESC;",\
            dateEdit1->date().toString("yyyy-MM-dd").toStdString().data(),\
            dateEdit2->date().addDays(1).toString("yyyy-MM-dd").toStdString().data(),kehumingcheng,gongchengmingcheng,\
            changdimingcheng,shengchanjizu);
    if(library->load()){
        typedef void (*pFunc)(const char *,const char *);
        pFunc function=(pFunc)library->resolve("loadmyreport");
        if(function){
            function("./report/report13.fr3",baobiaoSQL);
        }
    }
    else{
        QMessageBox::information(this,tr("错误"),library->errorString());
    }
    delete [] baobiaoSQL;
}

void shengchanmingxibiaoDlg::on_close()
{
    close();
}
