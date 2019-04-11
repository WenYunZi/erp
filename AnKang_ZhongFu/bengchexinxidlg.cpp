#include "bengchexinxidlg.h"

extern mymysql db;
extern myTCPsocket *sockClient;

bengchexinxiDlg::bengchexinxiDlg(QWidget *parent) :
    QDialog(parent)
{
    SQL = "select PumpNumber 泵车编号,LicensePlate 车牌,Driver1 司机1,Driver2 司机2,Driver3 司机3,\
            Driver4 司机4,PumpType 泵车类型,PumpXingHao 泵车型号,Pump 泵长,EnableDate 启用日期,\
            TheAnnualCycle 年审周期,DateOfProduction 出厂日期,\
            Manufacturer 生产厂家,ManufacturerNumber 厂家编号 from PumpCarInfo";

    createAction();
    createTool();

    QLabel *label1 = new QLabel(tr("泵车编号"),this);
    label1->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label2 = new QLabel(tr("车牌"),this);
    label2->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label3 = new QLabel(tr("司机1"),this);
    label3->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label4 = new QLabel(tr("司机2"),this);
    label4->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label5 = new QLabel(tr("司机3"),this);
    label5->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label6 = new QLabel(tr("司机4"),this);
    label6->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label7 = new QLabel(tr("泵车类型"),this);
    label7->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label8 = new QLabel(tr("泵车型号"),this);
    label8->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label9 = new QLabel(tr("泵长"),this);
    label9->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label10 = new QLabel(tr("启用日期"),this);
    label10->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label12 = new QLabel(tr("年审周期"),this);
    label12->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label13 = new QLabel(tr("出厂日期"),this);
    label13->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label14 = new QLabel(tr("生产厂家"),this);
    label14->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label15 = new QLabel(tr("厂家编号"),this);
    label15->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

    view = new QTableView(this);
    db.showview(SQL,view,&model);
    connect(view,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick()));

    lineEdit1 = new QLineEdit(this);
    lineEdit2 = new QLineEdit(this);
    lineEdit3 = new QLineEdit(this);
    lineEdit5 = new QLineEdit(this);
    lineEdit6 = new QLineEdit(this);
    lineEdit7 = new QLineEdit(this);
    const char *fillSQL = "SELECT DriverName FROM PumpDriver;";
    comBox1 = new QComboBox(this);
    db.sql_fillComboBoxItem(fillSQL,comBox1);
    comBox2 = new QComboBox(this);
    db.sql_fillComboBoxItem(fillSQL,comBox2);
    comBox3 = new QComboBox(this);
    db.sql_fillComboBoxItem(fillSQL,comBox3);
    comBox4 = new QComboBox(this);
    db.sql_fillComboBoxItem(fillSQL,comBox4);
    comBox5 = new QComboBox(this);
    comBox5->setView(new QListView(this));
    comBox5->setEditable(true);
    comBox5->addItem(tr(""));
    comBox5->addItem(tr("自有车辆"));
    comBox5->addItem(tr("租用车辆"));
    comBox6 = new QComboBox(this);
    comBox6->setView(new QListView(this));
    comBox6->setEditable(true);
    comBox6->addItem(tr(""));
    comBox6->addItem(tr("拖泵"));
    comBox6->addItem(tr("车泵"));
    comBox6->addItem(tr("车载泵"));
    comBox6->addItem(tr("电泵"));

    dateEdit1 = new QDateEdit(QDate::currentDate(),this);
    dateEdit1->setCalendarPopup(true);
    dateEdit2 = new QDateEdit(QDate::currentDate(),this);
    dateEdit2->setCalendarPopup(true);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label1,0,0);
    layout->addWidget(lineEdit1,0,1);
    layout->addWidget(view,0,2,18,1);
    layout->addWidget(label2,1,0);
    layout->addWidget(lineEdit2,1,1);
    layout->addWidget(label3,2,0);
    layout->addWidget(comBox1,2,1);
    layout->addWidget(label4,3,0);
    layout->addWidget(comBox2,3,1);
    layout->addWidget(label5,4,0);
    layout->addWidget(comBox3,4,1);
    layout->addWidget(label6,5,0);
    layout->addWidget(comBox4,5,1);
    layout->addWidget(label7,6,0);
    layout->addWidget(comBox5,6,1);
    layout->addWidget(label8,7,0);
    layout->addWidget(comBox6,7,1);
    layout->addWidget(label9,8,0);
    layout->addWidget(lineEdit3,8,1);
    layout->addWidget(label10,9,0);
    layout->addWidget(dateEdit1,9,1);
    layout->addWidget(label12,10,0);
    layout->addWidget(lineEdit5,10,1);
    layout->addWidget(label13,11,0);
    layout->addWidget(dateEdit2,11,1);
    layout->addWidget(label14,12,0);
    layout->addWidget(lineEdit6,12,1);
    layout->addWidget(label15,13,0);
    layout->addWidget(lineEdit7,13,1);
    layout->setColumnStretch(0,0);
    layout->setColumnStretch(1,0);
    layout->setColumnStretch(2,2);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(toolBar);
    vlayout->addLayout(layout);
}

void bengchexinxiDlg::refresh()
{
    db.showview(SQL,view,&model);
}

void bengchexinxiDlg::keyPressEvent(QKeyEvent *event)
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


void bengchexinxiDlg::createAction()
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

void bengchexinxiDlg::createTool()
{
    toolBar = new QToolBar(this);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar->addAction(newAction);
    toolBar->addAction(saveAction);
    toolBar->addAction(updateAction);
    toolBar->addAction(deleteAction);
}

void bengchexinxiDlg::on_newAction()
{
    lineEdit1->setFocus();
    saveAction->setEnabled(true);
    updateAction->setEnabled(false);
    deleteAction->setEnabled(false);

    lineEdit1->clear();
    lineEdit1->setEnabled(true);
    lineEdit2->clear();
    lineEdit3->clear();
    lineEdit5->clear();
    lineEdit6->clear();
    lineEdit7->clear();

    comBox1->clear();
    comBox2->clear();
    comBox3->clear();
    comBox4->clear();
    const char *fillSQL = "SELECT DriverName FROM PumpDriver;";
    db.sql_fillComboBoxItem(fillSQL,comBox1);
    db.sql_fillComboBoxItem(fillSQL,comBox2);
    db.sql_fillComboBoxItem(fillSQL,comBox3);
    db.sql_fillComboBoxItem(fillSQL,comBox4);

    comBox5->setCurrentIndex(0);
    comBox6->setCurrentIndex(0);
    dateEdit1->setDate(QDate::currentDate());
    dateEdit2->setDate(QDate::currentDate());
}

void bengchexinxiDlg::on_saveAction()
{
    QString saveSQL = QString("insert into PumpCarInfo (PumpNumber,LicensePlate,Driver1,\
                              Driver2,Driver3,Driver4,PumpType,PumpXingHao,Pump,EnableDate,\
                              TheAnnualCycle,DateOfProduction,Manufacturer,\
                              ManufacturerNumber) values ('%1','%2','%3','%4','%5','%6','%7','%8',\
                              '%9','%10','%11','%12','%13','%14');")
     .arg(lineEdit1->text(),lineEdit2->text(),comBox1->currentText(),comBox2->currentText(),
         comBox3->currentText(),comBox4->currentText(),comBox5->currentText(),comBox6->currentText(),
         lineEdit3->text())
     .arg(dateEdit1->date().toString("yyyy-MM-dd"),lineEdit5->text(),
         dateEdit2->date().toString("yyyy-MM-dd"),lineEdit6->text(),lineEdit7->text());

    int res = db.sql_exec(saveSQL.toStdString().data());
    if(res == -1){
        if(strstr(db.geterror(),"PRIMARY") != NULL){
            QMessageBox::information(this, tr("失败"),tr("请检查司机编号是否重复"),0,0,0);
        }
        return;
    }
    else if(res == 0){
        sockClient->send_Msg3();
        on_newAction();
        QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
    }
}

void bengchexinxiDlg::on_updateAction()
{
    QString updateSQL = QString("update PumpCarInfo set LicensePlate='%1',Driver1='%2',Driver2='%3',\
                                Driver3='%4',Driver4='%5',PumpType='%6',PumpXingHao='%7',Pump='%8',EnableDate='%9',\
                                TheAnnualCycle='%11',DateOfProduction='%12',Manufacturer='%13',\
                                ManufacturerNumber='%14' where PumpNumber='%15';")
     .arg(lineEdit2->text(),comBox1->currentText(),comBox2->currentText(),
         comBox3->currentText(),comBox4->currentText(),comBox5->currentText(),comBox6->currentText(),
         lineEdit3->text())
     .arg(dateEdit1->date().toString("yyyy-MM-dd"),lineEdit5->text(),
         dateEdit2->date().toString("yyyy-MM-dd"),lineEdit6->text(),lineEdit7->text(),lineEdit1->text());
    int res = db.sql_exec(updateSQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();
        on_newAction();
        QMessageBox::information(this,tr("提示信息"),tr("修改成功"),0,0,0);
    }
}

void bengchexinxiDlg::on_deleteAction()
{
    QString deleteSQL = QString("delete from PumpCarInfo where PumpNumber='%1';").arg(lineEdit1->text());
    int res = db.sql_exec(deleteSQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();
        on_newAction();
        QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
    }
}

void bengchexinxiDlg::ShowSupplyclick()
{
    lineEdit1->setEnabled(false);
    updateAction->setEnabled(true);
    deleteAction->setEnabled(true);
    saveAction->setEnabled(false);

    int row = view->currentIndex().row();
    lineEdit1->setText(model->item(row,0)->text());
    lineEdit2->setText(model->item(row,1)->text());
    lineEdit3->setText(model->item(row,8)->text());
    lineEdit5->setText(model->item(row,10)->text());
    lineEdit6->setText(model->item(row,12)->text());
    lineEdit7->setText(model->item(row,13)->text());
    comBox1->setCurrentText(model->item(row,2)->text());
    comBox2->setCurrentText(model->item(row,3)->text());
    comBox3->setCurrentText(model->item(row,4)->text());
    comBox4->setCurrentText(model->item(row,5)->text());
    comBox5->setCurrentText(model->item(row,6)->text());
    comBox6->setCurrentText(model->item(row,7)->text());
    dateEdit1->setDate(QDate::fromString(model->item(row,9)->text(),"yyyy-MM-dd"));
    dateEdit2->setDate(QDate::fromString(model->item(row,11)->text(),"yyyy-MM-dd"));
}
