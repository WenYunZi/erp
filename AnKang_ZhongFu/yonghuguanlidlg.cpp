#include "yonghuguanlidlg.h"

extern mymysql db;
extern myTCPsocket *sockClient;

yonghuguanliDlg::yonghuguanliDlg(QWidget *parent) :
    QDialog(parent)
{
    SQL = "select UserName 用户名,RealName 真实姓名,CustomerType 用户类型,SubordinateDepartment 所属部门,MobilePhone 手机,\
            WeighingPermissions 审核下发权限,cheliang 车辆下班权限 from UserManagement where UserName!='admin';";

    createAction();
    createTool();

    QLabel *label1  = new QLabel(tr("用户名"),this);
    label1->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label2  = new QLabel(tr("密码"),this);
    label2->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label3  = new QLabel(tr("密码确认"),this);
    label3->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label4  = new QLabel(tr("真实姓名"),this);
    label4->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label5  = new QLabel(tr("所属部门"),this);
    label5->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label6  = new QLabel(tr("手机号"),this);
    label6->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label7  = new QLabel(tr("注意：修改按钮只修改所属部门、手机号、审核下发权限"),this);
    label7->setAlignment(Qt::AlignCenter);
    label7->setStyleSheet("color:red");

    lineEdit1 = new QLineEdit(this);
    lineEdit1->setStyleSheet("color:black");
    lineEdit2 = new QLineEdit(this);
    lineEdit2->setStyleSheet("color:black");
    lineEdit2->setEchoMode(QLineEdit::Password);
    lineEdit3 = new QLineEdit(this);
    lineEdit3->setStyleSheet("color:black");
    lineEdit3->setEchoMode(QLineEdit::Password);
    lineEdit4 = new QLineEdit(this);
    lineEdit4->setStyleSheet("color:black");
    lineEdit5 = new QLineEdit(this);

    combo1 = new QComboBox(this);
    const char *fillSQL = "select DepartmentName from SectorSettings;";
    db.sql_fillComboBoxItem(fillSQL,combo1);

    radioBtn1 = new QRadioButton(tr("管理员"),this);
    radioBtn2 = new QRadioButton(tr("普通用户"),this);

    Btngroup = new QButtonGroup(this);
    Btngroup->addButton(radioBtn1,0);
    Btngroup->addButton(radioBtn2,1);
    radioBtn2->setChecked(true);

    checkBox1 = new QCheckBox(tr("具有审核下发权限"),this);
    checkBox2 = new QCheckBox(tr("具有车辆下班权限"),this);

    view = new QTableView(this);
    db.showview(SQL,view,&model);//显示表格
    connect(view,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick()));
    view->setColumnWidth(0,150);
    view->setColumnWidth(1,150);
    view->setColumnWidth(2,150);
    view->setColumnWidth(3,150);
    view->setColumnWidth(4,150);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label1,0,0);
    layout->addWidget(lineEdit1,0,1);
    layout->addWidget(label2,0,2);
    layout->addWidget(lineEdit2,0,3);
    layout->addWidget(label5,0,4);
    layout->addWidget(combo1,0,5);
    layout->addWidget(label4,1,0);
    layout->addWidget(lineEdit4,1,1);
    layout->addWidget(label3,1,2);
    layout->addWidget(lineEdit3,1,3);
    layout->addWidget(label6,1,4);
    layout->addWidget(lineEdit5,1,5);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(radioBtn1);
    hlayout->addWidget(radioBtn2);
    hlayout->addSpacing(15);
    hlayout->addWidget(checkBox1);
    hlayout->addWidget(checkBox2);
    hlayout->addSpacing(15);
    hlayout->addWidget(label7);
    hlayout->addStretch(50);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(toolBar);
    vlayout->addLayout(layout);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(view);
}

yonghuguanliDlg::~yonghuguanliDlg()
{
    delete model;
}

void yonghuguanliDlg::refresh()
{
    db.showview(SQL,view,&model);//显示表格
}

void yonghuguanliDlg::keyPressEvent(QKeyEvent *event)
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

void yonghuguanliDlg::on_newAction()
{
    lineEdit1->setFocus();
    saveAction->setEnabled(true);
    updateAction->setEnabled(false);
    deleteAction->setEnabled(false);
    radioBtn1->setEnabled(true);
    radioBtn2->setEnabled(true);

    lineEdit1->clear();
    lineEdit1->setEnabled(true);
    lineEdit2->clear();
    lineEdit2->setEnabled(true);
    lineEdit3->clear();
    lineEdit3->setEnabled(true);
    lineEdit4->clear();
    lineEdit4->setEnabled(true);
    lineEdit5->clear();
    combo1->setCurrentIndex(0);
    checkBox1->setCheckState(Qt::Unchecked);
    checkBox2->setCheckState(Qt::Unchecked);
    radioBtn2->setChecked(true);
}

void yonghuguanliDlg::on_saveAction()
{
    if(lineEdit1->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入用户名"),0,0,0);
        return;
    }
    if(lineEdit2->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入密码"),0,0,0);
        return;
    }
    if(lineEdit3->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请重复输入密码"),0,0,0);
        return;
    }
    if(lineEdit2->text() != lineEdit3->text()){
        QMessageBox::information(this,tr("提示信息"),tr("两次密码输入不一致"),0,0,0);
        return;
    }
    if(lineEdit4->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入真实姓名"),0,0,0);
        return;
    }
    if(lineEdit5->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入手机号"),0,0,0);
        return;
    }
    if((Btngroup->checkedId()) == 1){
        if(combo1->currentText().isEmpty()) {
            QMessageBox::information(this,tr("提示信息"),tr("请选择所属部门"),0,0,0);
            return;
        }
    }
    switch(Btngroup->checkedId())
    {
    case 0:
        str7 = "管理员";
        break;
    case 1:
        str7 = "普通用户";
        break;
    }
    switch((int)(checkBox1->checkState()))
    {
    case 0:
        str8 = "无";
        break;
    case 2:
        str8 = "有";
        break;
    }
    switch((int)(checkBox2->checkState()))
    {
    case 0:
        str9 = "无";
        break;
    case 2:
        str9 = "有";
        break;
    }
    QString saveSQL = QString("insert into UserManagement (UserName,RealName,CustomerType,SubordinateDepartment,MobilePhone,\
                              Password1,Password2,WeighingPermissions,cheliang) values ('%1','%2','%3','%4','%5','%6',\
                              '%7','%8','%9');")
                    .arg(lineEdit1->text(),lineEdit4->text(),str7,combo1->currentText(),lineEdit5->text(),lineEdit2->text(),lineEdit3->text(),str8,str9);
    int res = db.sql_exec(saveSQL.toStdString().data());
    if(res == -1){
        if((strncmp("Duplicate entry",db.geterror(),15)) == 0){
            QMessageBox::information(this, tr("失败"),tr("请检查用户名是否重复"),0,0,0);
        }
        return;
    }else if(res == 0){
        sockClient->send_Msg3();//发送刷新消息
        on_newAction();
        QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
    }
}

void yonghuguanliDlg::on_updateAction()
{
    if(lineEdit5->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入手机号"),0,0,0);
        return;
    }
    if((Btngroup->checkedId()) == 1){
        if(combo1->currentText().isEmpty()){
            QMessageBox::information(this,tr("提示信息"),tr("请选择所属部门"),0,0,0);
            return;
        }
    }
    switch((int)(checkBox1->checkState()))
    {
    case 0:
        str8 = "无";
        break;
    case 2:
        str8 = "有";
        break;
    }
    switch((int)(checkBox2->checkState()))
    {
    case 0:
        str9 = "无";
        break;
    case 2:
        str9 = "有";
        break;
    }
    QString updateSQL = QString("update UserManagement set SubordinateDepartment='%1', MobilePhone='%2',WeighingPermissions='%3',cheliang='%4' where UserName='%5';")
                    .arg(combo1->currentText(),lineEdit5->text(),str8,str9,lineEdit1->text());
    int res = db.sql_exec(updateSQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();//发送刷新消息
        on_newAction();
        QMessageBox::information(this,tr("提示信息"),tr("修改成功"),0,0,0);
    }
}

void yonghuguanliDlg::on_deleteAction()
{
    QString deleteSQL = QString("delete from UserManagement where UserName='%1';").arg(lineEdit1->text());
    int res = db.sql_exec(deleteSQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();//发送刷新消息
        on_newAction();
        QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
    }
}

void yonghuguanliDlg::ShowSupplyclick()
{
    lineEdit1->setEnabled(false);
    lineEdit4->setEnabled(false);
    lineEdit2->setEnabled(false);
    lineEdit3->setEnabled(false);
    radioBtn1->setEnabled(false);
    radioBtn2->setEnabled(false);
    updateAction->setEnabled(true);
    deleteAction->setEnabled(true);
    saveAction->setEnabled(false);

    int row = view->currentIndex().row();
    lineEdit1->setText(model->item(row,0)->text());
    lineEdit4->setText(model->item(row,1)->text());
    lineEdit5->setText(model->item(row,4)->text());
    combo1->setCurrentText(model->item(row,3)->text());
    if(model->item(row,2)->text() == "管理员"){
        radioBtn1->setChecked(true);
    }else{
        radioBtn2->setChecked(true);
    }
    if(model->item(row,5)->text() == "有"){
        checkBox1->setCheckState(Qt::Checked);
    }else{
        checkBox1->setCheckState(Qt::Unchecked);
    }
    if(model->item(row,6)->text() == "有"){
        checkBox2->setCheckState(Qt::Checked);
    }else{
        checkBox2->setCheckState(Qt::Unchecked);
    }
}

void yonghuguanliDlg::createAction()
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

void yonghuguanliDlg::createTool()
{
    toolBar = new QToolBar(this);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar->addAction(newAction);
    toolBar->addAction(saveAction);
    toolBar->addAction(updateAction);
    toolBar->addAction(deleteAction);
}
