#include "bumenshezhidlg.h"

extern mymysql db;
extern myTCPsocket *sockClient;

bumenshezhiDlg::bumenshezhiDlg(QWidget *parent) :
    QDialog(parent)
{
    tabWidget = new QTabWidget(this);
    bumenshezhi = new QWidget(this);
    jizushezhi = new QWidget(this);

    creatTabPage1();
    creatTabPage2();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tabWidget);
}

bumenshezhiDlg::~bumenshezhiDlg()
{
    delete onemodel;
    delete twomodel;
}

void bumenshezhiDlg::refresh()
{
    db.showview(SQL1,oneview,&onemodel);//显示表格
    db.showview(SQL2,twoview,&twomodel);//显示表格
}

void bumenshezhiDlg::keyPressEvent(QKeyEvent *event)
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

void bumenshezhiDlg::creatTabPage1()
{

    createAction();
    createTool();

    SQL1 = "select DepartmentNo 部门编号,DepartmentName 部门名称,WhetherProduct 是否生产部门, \
                Telephone 电话,PersonInCharge 负责人,PlantName 厂地名称 from SectorSettings;";

    QLabel *label1 = new QLabel(tr("部门编号"),this);
    label1->setStyleSheet("color:red");
    label1->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label2 = new QLabel(tr("部门名称"),this);
    label2->setStyleSheet("color:red");
    label2->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label3 = new QLabel(tr("联系电话"),this);
    label3->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label4 = new QLabel(tr("负责人"),this);
    label4->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label5 = new QLabel(tr("厂地名称"),this);
    label5->setStyleSheet("color:red");
    label5->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

    onelineEdit1 = new QLineEdit(this);
    onelineEdit1->setStyleSheet("color:black");
    onelineEdit2 = new QLineEdit(this);
    onelineEdit3 = new QLineEdit(this);
    onelineEdit4 = new QLineEdit(this);


    oneview = new QTableView(this);
    db.showview(SQL1,oneview,&onemodel);//显示表格
    connect(oneview,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick()));

    onecombo = new QComboBox(this);
    onecombo->setEditable(true);
    const char *fillSQL = "select PlantName from FactorySetting;";
    db.sql_fillComboBoxItem(fillSQL,onecombo);

    onecheckBox = new QCheckBox(this);
    onecheckBox->setText(tr("生产部门"));
    onecheckBox->setStyleSheet("color:red");

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label1,0,0);
    layout->addWidget(onelineEdit1,0,1);
    layout->addWidget(oneview,0,2,8,1);
    layout->addWidget(label2,1,0);
    layout->addWidget(onelineEdit2,1,1);
    layout->addWidget(label3,2,0);
    layout->addWidget(onelineEdit3,2,1);
    layout->addWidget(label4,3,0);
    layout->addWidget(onelineEdit4,3,1);
    layout->addWidget(label5,4,0);
    layout->addWidget(onecombo,4,1);
    layout->addWidget(onecheckBox,5,1);
    layout->setColumnStretch(0,0);
    layout->setColumnStretch(1,1);
    layout->setColumnStretch(2,4);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(toolBar);
    vlayout->addLayout(layout);

    bumenshezhi->setLayout(vlayout);
    tabWidget->addTab(bumenshezhi,tr("部门设置"));
}

void bumenshezhiDlg::creatTabPage2()
{
    createAction2();
    createTool2();

    SQL2 = "select UnitNumber 机组编号,UnitName 机组名称,SubDepartment 所属部门 from UnitSetting;";

    QLabel *label1 = new QLabel(tr("机组编号"),this);
    label1->setStyleSheet("color:red");
    label1->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label2 = new QLabel(tr("机组名称"),this);
    label2->setStyleSheet("color:red");
    label2->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label3 = new QLabel(tr("所属部门"),this);
    label3->setStyleSheet("color:red");
    label3->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

    twolineEdit1 = new QLineEdit(this);
    twolineEdit1->setStyleSheet("color:black");
    twocombo1 = new QComboBox(this);
    twocombo1->setView(new QListView(this));
    twocombo1->addItem(tr(""));
    twocombo1->addItem(tr("1#机组"));
    twocombo1->addItem(tr("2#机组"));
    twocombo1->addItem(tr("3#机组"));

    twoview = new QTableView(this);
    db.showview(SQL2,twoview,&twomodel);//显示表格
    connect(twoview,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick2()));

    twocombo = new QComboBox(this);
    const char *mySQL = "select DepartmentName from SectorSettings where WhetherProduct='是';";
    db.sql_fillComboBoxItem(mySQL,twocombo);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label1,0,0);
    layout->addWidget(twolineEdit1,0,1);
    layout->addWidget(twoview,0,2,8,1);
    layout->addWidget(label2,1,0);
    layout->addWidget(twocombo1,1,1);
    layout->addWidget(label3,2,0);
    layout->addWidget(twocombo,2,1);
    layout->setColumnStretch(0,0);
    layout->setColumnStretch(1,1);
    layout->setColumnStretch(2,4);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(toolBar2);
    vlayout->addLayout(layout);

    jizushezhi->setLayout(vlayout);
    tabWidget->addTab(jizushezhi,tr("机组设置"));
}

void bumenshezhiDlg::on_newAction()
{
    onelineEdit1->setFocus();
    saveAction->setEnabled(true);
    updateAction->setEnabled(false);
    deleteAction->setEnabled(false);

    onelineEdit1->clear();
    onelineEdit1->setEnabled(true);
    onelineEdit2->clear();
    onelineEdit3->clear();
    onelineEdit4->clear();
    onecombo->setCurrentIndex(0);
    onecheckBox->setCheckState(Qt::Unchecked);
}

void bumenshezhiDlg::on_saveAction()
{
    if(onelineEdit1->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入部门编号"),0,0,0);
        return;
    }
    if(onelineEdit2->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入部门名称"),0,0,0);
        return;
    }
    if(onecombo->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择公司"),0,0,0);
        return;
    }
    if(0 == onecheckBox->checkState()){//如果onecheckBox没有被选中
        str6 = "否";
    }
    else if(2 == onecheckBox->checkState()){//如果onecheckBox被选中
        str6 = "是";
    }

    QString saveSQL = QString("insert into SectorSettings (DepartmentNo, DepartmentName , WhetherProduct,Telephone, PersonInCharge, PlantName) values ('%1','%2','%3','%4','%5','%6');")
                    .arg(onelineEdit1->text(),onelineEdit2->text(),str6,onelineEdit3->text(),onelineEdit4->text(),onecombo->currentText());

    int res = db.sql_exec(saveSQL.toStdString().data());
    if(res == -1){
        if((strstr(db.geterror(),"PRIMARY")) != NULL){
            QMessageBox::information(this, tr("失败"),tr("请检查部门编号是否重复"),0,0,0);
            return;
        }
        if((strstr(db.geterror(),"DepartmentName")) != NULL){
            QMessageBox::information(this, tr("失败"),tr("部门已经存在"),0,0,0);
            return;
        }
    }
    else if(res == 0){
        on_newAction();
        twocombo->clear();
        const char *mySQL = "select DepartmentName from SectorSettings where WhetherProduct='是';";
        db.sql_fillComboBoxItem(mySQL,twocombo);
        sockClient->send_Msg3();
        QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
    }
}

void bumenshezhiDlg::on_updateAction()
{
    if(onelineEdit2->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入部门名称"),0,0,0);
        return;
    }
    if(0 == onecheckBox->checkState()){//如果onecheckBox没有被选中
        str6 = "否";
    }
    else if(2 == onecheckBox->checkState()){//如果onecheckBox被选中
        str6 = "是";
    }

    QString updateSQL = QString("update SectorSettings set DepartmentName='%1', WhetherProduct='%2',Telephone='%3',PersonInCharge='%4',PlantName='%5' where DepartmentNo='%6';")
            .arg(onelineEdit2->text(),str6,onelineEdit3->text(),onelineEdit4->text(),onecombo->currentText(),onelineEdit1->text());

    int res = db.sql_exec(updateSQL.toStdString().data());
    if(res == 0){
        on_newAction();
        twocombo->clear();
        const char *mySQL = "select DepartmentName from SectorSettings where WhetherProduct='是';";
        db.sql_fillComboBoxItem(mySQL,twocombo);
        sockClient->send_Msg3();
        QMessageBox::information(this,tr("提示信息"),tr("修改成功"),0,0,0);
    }
}

void bumenshezhiDlg::on_deleteAction()
{
    QString deleteSQL = QString("delete from SectorSettings where DepartmentNo='%1';").arg(onelineEdit1->text());
    int res = db.sql_exec(deleteSQL.toStdString().data());
    if(res == 0){
        on_newAction();
        twocombo->clear();
        const char *mySQL = "select DepartmentName from SectorSettings where WhetherProduct='是';";
        db.sql_fillComboBoxItem(mySQL,twocombo);
        sockClient->send_Msg3();
        QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
    }
}

void bumenshezhiDlg::ShowSupplyclick()
{
    onelineEdit1->setEnabled(false);
    updateAction->setEnabled(true);
    deleteAction->setEnabled(true);
    saveAction->setEnabled(false);
    int row = oneview->currentIndex().row();

    onelineEdit1->setText(onemodel->item(row,0)->text());
    onelineEdit2->setText(onemodel->item(row,1)->text());
    onelineEdit3->setText(onemodel->item(row,3)->text());
    onelineEdit4->setText(onemodel->item(row,4)->text());
    onecombo->setCurrentText(onemodel->item(row,5)->text());
    if(onemodel->item(row,2)->text() == "是"){
        onecheckBox->setCheckState(Qt::Checked);
    }
    else if(onemodel->item(row,2)->text() == "否"){
        onecheckBox->setCheckState(Qt::Unchecked);
    }
}



void bumenshezhiDlg::createAction()
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

void bumenshezhiDlg::createTool()
{
    toolBar = new QToolBar(this);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar->addAction(newAction);
    toolBar->addAction(saveAction);
    toolBar->addAction(updateAction);
    toolBar->addAction(deleteAction);
}

void bumenshezhiDlg::on_newAction2()
{
    twolineEdit1->setFocus();
    saveAction2->setEnabled(true);
    updateAction2->setEnabled(false);
    deleteAction2->setEnabled(false);

    twolineEdit1->clear();
    twolineEdit1->setEnabled(true);
    twocombo1->setCurrentIndex(0);
    twocombo->setCurrentIndex(0);
}

void bumenshezhiDlg::on_saveAction2()
{
    if(twolineEdit1->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入机组编号"),0,0,0);
        return;
    }
    if(twocombo1->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入机组名称"),0,0,0);
        return;
    }
    if(twocombo->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择所属部门"),0,0,0);
        return;
    }

    QString save2SQL = QString("insert into UnitSetting (UnitNumber, UnitName , SubDepartment) values ('%1','%2','%3');").arg(twolineEdit1->text(),twocombo1->currentText(),twocombo->currentText());

    int res = db.sql_exec(save2SQL.toStdString().data());
    if(res == -1){
        if((strstr(db.geterror(),"PRIMARY")) != NULL){
            QMessageBox::information(this, tr("失败"),tr("请检查机组编号是否重复"),0,0,0);
            return;
        }
        else if((strstr(db.geterror(),"UnitName")) != NULL){
            QMessageBox::information(this, tr("失败"),tr("请检查机组名称是否重复"),0,0,0);
            return;
        }
    }
    else if(res == 0){
        on_newAction2();
        twocombo->clear();
        const char *mySQL = "select DepartmentName from SectorSettings where WhetherProduct='是';";
        db.sql_fillComboBoxItem(mySQL,twocombo);
        sockClient->send_Msg3();
        QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
    }
}

void bumenshezhiDlg::on_updateAction2()
{
    if(twocombo1->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入机组名称"),0,0,0);
        return;
    }
    if(twocombo->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择所属部门"),0,0,0);
        return;
    }

    QString update2SQL = QString("update UnitSetting set UnitName='%1', SubDepartment='%2' where UnitNumber='%3';").arg(twocombo1->currentText(),twocombo->currentText(),twolineEdit1->text());
    int res = db.sql_exec(update2SQL.toStdString().data());
    if(res == 0){
        on_newAction2();
        sockClient->send_Msg3();
        QMessageBox::information(this,tr("提示信息"),tr("修改成功"),0,0,0);
    }
}

void bumenshezhiDlg::on_deleteAction2()
{
    QString delete2SQL = QString("delete from UnitSetting where UnitNumber='%1';").arg(twolineEdit1->text());
    int res = db.sql_exec(delete2SQL.toStdString().data());
    if(res == 0){
        on_newAction2();
        sockClient->send_Msg3();
        QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
    }
}

void bumenshezhiDlg::ShowSupplyclick2()
{
    twolineEdit1->setEnabled(false);
    updateAction2->setEnabled(true);
    deleteAction2->setEnabled(true);
    saveAction2->setEnabled(false);
    int row = twoview->currentIndex().row();

    twolineEdit1->setText(twomodel->item(row,0)->text());
    twocombo1->setCurrentText(twomodel->item(row,1)->text());
    twocombo->setCurrentText(twomodel->item(row,2)->text());
}


void bumenshezhiDlg::createAction2()
{
    newAction2 = new QAction(tr("新增"),this);
    newAction2->setIcon(QIcon(":/image/new.png"));
    connect(newAction2,SIGNAL(triggered()),this,SLOT(on_newAction2()));
    saveAction2 = new QAction(tr("保存"),this);
    saveAction2->setIcon(QIcon(":/image/save.png"));
    connect(saveAction2,SIGNAL(triggered()),this,SLOT(on_saveAction2()));
    updateAction2 = new QAction(tr("修改"),this);
    updateAction2->setEnabled(false);
    updateAction2->setIcon(QIcon(":/image/update.png"));
    connect(updateAction2,SIGNAL(triggered()),this,SLOT(on_updateAction2()));
    deleteAction2 = new QAction(tr("删除"),this);
    deleteAction2->setEnabled(false);
    deleteAction2->setIcon(QIcon(":/image/delete.png"));
    connect(deleteAction2,SIGNAL(triggered()),this,SLOT(on_deleteAction2()));
}

void bumenshezhiDlg::createTool2()
{
    toolBar2 = new QToolBar(this);
    toolBar2->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar2->addAction(newAction2);
    toolBar2->addAction(saveAction2);
    toolBar2->addAction(updateAction2);
    toolBar2->addAction(deleteAction2);
}
