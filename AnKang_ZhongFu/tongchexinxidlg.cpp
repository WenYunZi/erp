#include "tongchexinxidlg.h"

extern mymysql db;
extern myTCPsocket *sockClient;

tongchexinxiDlg::tongchexinxiDlg(QWidget *parent) :
    QDialog(parent)
{
    createAction();
    createTool();

    SQL = "select Vehiclenumber 车辆编号,Driver1 司机1,Driver2 司机2,VehicleType 车辆类型,LicensePlate 车牌,\
            VehicleXingHao 车辆型号,FactoryOwnedLand 所属厂地,EnableDate 启用日期,TwoDimensionalPeriod  二维周期,\
            TheAnnualCycle  年审周期,DateOfProduction 出厂日期,Manufacturer 生产厂家,ManufacturerNumber 厂家编号,\
            SetTheTare 设定皮重,CardNumber 卡号,VehicleStat 值班状态 from ConcreteVehicleInformation;";

    QLabel *label1 = new QLabel(tr("车辆编号"),this);
    label1->setStyleSheet("color:red");
    label1->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label2 = new QLabel(tr("车牌"),this);
    label2->setStyleSheet("color:red");
    label2->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label3 = new QLabel(tr("司机1"),this);
    label3->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label4 = new QLabel(tr("司机2"),this);
    label4->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label5 = new QLabel(tr("车辆类型"),this);
    label5->setStyleSheet("color:red");
    label5->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label6 = new QLabel(tr("车辆型号"),this);
    label6->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label7 = new QLabel(tr("所属厂地"),this);
    label7->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label8 = new QLabel(tr("启用日期"),this);
    label8->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label9 = new QLabel(tr("值班状态"),this);
    label9->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label10 = new QLabel(tr("年审周期"),this);
    label10->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label11 = new QLabel(tr("出厂日期"),this);
    label11->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label12 = new QLabel(tr("生产厂家"),this);
    label12->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label13 = new QLabel(tr("厂家编号"),this);
    label13->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label14 = new QLabel(tr("设定皮重"),this);
    label14->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label15 = new QLabel(tr("卡号"),this);
    label15->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label17 = new QLabel(tr("月"),this);
    label17->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label18 = new QLabel(tr("KG"),this);
    label18->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

    lineEdit1 = new QLineEdit(this);
    lineEdit1->setStyleSheet("color:black");
    lineEdit2 = new QLineEdit(this);
    lineEdit4 = new QLineEdit(this);
    lineEdit5 = new QLineEdit(this);
    lineEdit6 = new QLineEdit(this);
    lineEdit7 = new QLineEdit(this);
    lineEdit8 = new QLineEdit(this);

    view = new QTableView(this);
    connect(view,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick()));
    db.showview(SQL,view,&model);//显示表格

    dateEidt1 = new QDateEdit(QDate::currentDate(),this);
    dateEidt1->setCalendarPopup(true);
    dateEidt2 = new QDateEdit(QDate::currentDate(),this);
    dateEidt2->setCalendarPopup(true);

    combo1 = new QComboBox(this);
    const char *mySQL = "select DriverName from ConcreteTruckDriver;";
    db.sql_fillComboBoxItem(mySQL,combo1);
    combo2 = new QComboBox(this);
    const char *mySQL1 = "select DriverName from ConcreteTruckDriver;";
    db.sql_fillComboBoxItem(mySQL1,combo2);
    combo3 = new QComboBox(this);
    combo3->setEditable(true);
    combo3->setView(new QListView(this));
    combo3->addItem(tr(""));
    combo3->addItem(tr("自有车辆"));
    combo3->addItem(tr("租用车辆"));
    combo3->addItem(tr("临时车辆"));
    combo4 = new QComboBox(this);
    combo4->setEditable(true);
    combo4->setView(new QListView(this));
    combo4->setEditable(true);
    combo4->addItem(tr(""));
    combo4->addItem(tr("12方"));
    combo4->addItem(tr("15方"));
    combo4->addItem(tr("16方"));
    combo4->addItem(tr("20方"));
    combo4->addItem(tr("21方"));
    combo5 = new QComboBox(this);
    combo5->setEditable(true);
    const char *fillSQL5 = "select PlantName from FactorySetting group by PlantName;";
    db.sql_fillComboBoxItem(fillSQL5,combo5);
    combo6 = new QComboBox(this);
    combo6->setView(new QListView(this));
    combo6->addItem(tr(""));
    combo6->addItem(tr("主班"));
    combo6->addItem(tr("休班"));
    combo6->addItem(tr("副班"));
    combo6->addItem(tr("无班"));


    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label1,0,0);
    layout->addWidget(lineEdit1,0,1,1,2);
    layout->addWidget(view,0,3,17,1);
    layout->addWidget(label2,1,0);
    layout->addWidget(lineEdit2,1,1,1,2);
    layout->addWidget(label3,2,0);
    layout->addWidget(combo1,2,1,1,2);
    layout->addWidget(label4,3,0);
    layout->addWidget(combo2,3,1,1,2);
    layout->addWidget(label5,4,0);
    layout->addWidget(combo3,4,1,1,2);
    layout->addWidget(label6,5,0);
    layout->addWidget(combo4,5,1,1,2);
    layout->addWidget(label7,6,0);
    layout->addWidget(combo5,6,1,1,2);
    layout->addWidget(label8,7,0);
    layout->addWidget(dateEidt1,7,1,1,2);
    layout->addWidget(label9,8,0);
    layout->addWidget(combo6,8,1,1,2);
    layout->addWidget(label10,9,0);
    layout->addWidget(lineEdit4,9,1);
    layout->addWidget(label17,9,2);
    layout->addWidget(label11,10,0);
    layout->addWidget(dateEidt2,10,1,1,2);
    layout->addWidget(label12,11,0);
    layout->addWidget(lineEdit5,11,1,1,2);
    layout->addWidget(label13,12,0);
    layout->addWidget(lineEdit6,12,1,1,2);
    layout->addWidget(label14,13,0);
    layout->addWidget(lineEdit7,13,1);
    layout->addWidget(label18,13,2);
    layout->addWidget(label15,14,0);
    layout->addWidget(lineEdit8,14,1,1,2);
    layout->setColumnStretch(0,0);
    layout->setColumnStretch(1,0);
    layout->setColumnStretch(2,0);
    layout->setColumnStretch(3,2);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(toolBar);
    vlayout->addLayout(layout);
}

tongchexinxiDlg::~tongchexinxiDlg()
{
    delete model;
}

void tongchexinxiDlg::refresh()
{
    db.showview(SQL,view,&model);//显示表格
}

void tongchexinxiDlg::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Escape:
           event->ignore();
           break;
        default:
           QDialog::keyPressEvent(event);
    }
}

void tongchexinxiDlg::on_newAction()
{
    lineEdit1->setFocus();
    saveAction->setEnabled(true);
    updateAction->setEnabled(false);
    deleteAction->setEnabled(false);

    lineEdit1->clear();
    lineEdit1->setEnabled(true);
    lineEdit2->clear();
    lineEdit4->clear();
    lineEdit5->clear();
    lineEdit6->clear();
    lineEdit7->clear();
    lineEdit8->clear();
    combo1->setCurrentIndex(0);
    combo2->setCurrentIndex(0);
    combo3->setCurrentIndex(0);
    combo4->setCurrentIndex(0);
    combo5->setCurrentIndex(0);
    combo6->setCurrentIndex(0);
    dateEidt1->setDate(QDate::currentDate());
    dateEidt2->setDate(QDate::currentDate());
}

void tongchexinxiDlg::on_saveAction()
{
    if(lineEdit1->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入车辆编号"),0,0,0);
        return;
    }
    if(lineEdit2->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入车牌"),0,0,0);
        return;
    }
    if(lineEdit7->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请设定皮重"),0,0,0);
        return;
    }
    if(combo6->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择值班状态"),0,0,0);
        return;
    }
    QString saveSQL = QString("insert into ConcreteVehicleInformation (Vehiclenumber,Driver1,Driver2,VehicleType,\
                              LicensePlate,VehicleXingHao,FactoryOwnedLand,EnableDate,\
                              TheAnnualCycle,DateOfProduction,Manufacturer,ManufacturerNumber,SetTheTare,CardNumber,VehicleStat) \
            values ('%1','%2','%3','%4','%5','%6','%7','%8','%9','%10','%11','%12','%13','%14','%15');")
    .arg(lineEdit1->text(),combo1->currentText(),combo2->currentText(),combo3->currentText(),lineEdit2->text(),
         combo4->currentText(),combo5->currentText(),dateEidt1->date().toString("yyyy-MM-dd"))
            .arg(lineEdit4->text(),dateEidt2->date().toString("yyyy-MM-dd"),lineEdit5->text(),lineEdit6->text(),
                 lineEdit7->text(),lineEdit8->text(),combo6->currentText());

    int res = db.sql_exec(saveSQL.toStdString().data());
    if(res == -1){
        if(strstr(db.geterror(),"PRIMARY") != NULL){
            QMessageBox::information(this, tr("失败"),tr("请检查司机编号是否重复"),0,0,0);
        }
        return;
    }else if(res == 0){
        sockClient->send_Msg3();//发送刷新消息
        on_newAction();
        QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
    }

}

void tongchexinxiDlg::on_updateAction()
{
    if(lineEdit1->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入车辆编号"),0,0,0);
        return;
    }
    if(lineEdit2->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入车牌"),0,0,0);
        return;
    }
    if(lineEdit7->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请设定皮重"),0,0,0);
        return;
    }
    if(combo6->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择值班状态"),0,0,0);
        return;
    }
    QString updateSQL = QString("update ConcreteVehicleInformation set Driver1='%1',Driver2='%2',VehicleType='%3',\
                                LicensePlate='%4',VehicleXingHao='%5',FactoryOwnedLand='%6',EnableDate='%7',\
                                VehicleStat='%8',TheAnnualCycle='%9',DateOfProduction='%10',Manufacturer='%11',\
                                ManufacturerNumber='%12',SetTheTare='%13',CardNumber='%14' where Vehiclenumber='%15';")
                    .arg(combo1->currentText(),combo2->currentText(),combo3->currentText(),lineEdit2->text(),
                         combo4->currentText(),combo5->currentText(),dateEidt1->date().toString("yyyy-MM-dd"),combo6->currentText())
                    .arg(lineEdit4->text(),dateEidt2->date().toString("yyyy-MM-dd"),lineEdit5->text(),lineEdit6->text(),
                         lineEdit7->text(),lineEdit8->text(),lineEdit1->text());
    int res = db.sql_exec(updateSQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();//发送刷新消息
        on_newAction();
        QMessageBox::information(this,tr("提示信息"),tr("修改成功"),0,0,0);
    }
}

void tongchexinxiDlg::on_deleteAction()
{
    QString deleteSQL = QString("delete from ConcreteVehicleInformation where Vehiclenumber='%1';").arg(lineEdit1->text());
    int res = db.sql_exec(deleteSQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();//发送刷新消息
        on_newAction();
        QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
    }
}

void tongchexinxiDlg::ShowSupplyclick()
{
    lineEdit1->setEnabled(false);
    updateAction->setEnabled(true);
    deleteAction->setEnabled(true);
    saveAction->setEnabled(false);

    int row = view->currentIndex().row();
    lineEdit1->setText(model->item(row,0)->text());
    lineEdit2->setText(model->item(row,4)->text());
    lineEdit4->setText(model->item(row,9)->text());
    lineEdit5->setText(model->item(row,11)->text());
    lineEdit6->setText(model->item(row,12)->text());
    lineEdit7->setText(model->item(row,13)->text());
    lineEdit8->setText(model->item(row,14)->text());
    combo1->setCurrentText(model->item(row,1)->text());
    combo2->setCurrentText(model->item(row,2)->text());
    combo3->setCurrentText(model->item(row,3)->text());
    combo4->setCurrentText(model->item(row,5)->text());
    combo5->setCurrentText(model->item(row,6)->text());
    combo6->setCurrentText(model->item(row,15)->text());
    dateEidt1->setDate(QDate::fromString(model->item(row,7)->text(),"yyyy-MM-dd"));
    dateEidt2->setDate(QDate::fromString(model->item(row,10)->text(),"yyyy-MM-dd"));
}

void tongchexinxiDlg::createAction()
{
    newAction = new QAction(tr("新增"),this);
    newAction->setIcon(QIcon(":/image/new.png"));
    connect(newAction,SIGNAL(triggered()),this,SLOT(on_newAction()));
    saveAction = new QAction(tr("保存"),this);
    saveAction->setIcon(QIcon(":/image/save.png"));
    connect(saveAction,SIGNAL(triggered()),this,SLOT(on_saveAction()));
    updateAction = new QAction(tr("修改"),this);
    updateAction->setEnabled(false);
    updateAction->setIcon(QIcon(":/image/update.png"));
    connect(updateAction,SIGNAL(triggered()),this,SLOT(on_updateAction()));
    deleteAction = new QAction(tr("删除"),this);
    deleteAction->setEnabled(false);
    deleteAction->setIcon(QIcon(":/image/delete.png"));
    connect(deleteAction,SIGNAL(triggered()),this,SLOT(on_deleteAction()));
}

void tongchexinxiDlg::createTool()
{
    toolBar = new QToolBar;
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar->addAction(newAction);
    toolBar->addAction(saveAction);
    toolBar->addAction(updateAction);
    toolBar->addAction(deleteAction);
}
