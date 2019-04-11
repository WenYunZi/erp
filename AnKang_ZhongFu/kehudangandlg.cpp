#include "kehudangandlg.h"

extern mymysql db;
extern myTCPsocket *sockClient;

kehudanganDlg::kehudanganDlg(QWidget *parent) :
    QDialog(parent)
{
    SQL = "select CustomerNumber 客户编号,CustomerName 客户名称,Contacts\
            联系人,MobilePhone 联系电话,DebtLimit 欠款限额,Address 地址,GroupOfGenus 所属部门,\
            WhetherKeyCustomers 是否属于重点客户,Remarks 备注 from CustomerFiles;";

    createAction();
    createTool();
    this->setWindowFlags(windowFlags()& ~Qt::WindowContextHelpButtonHint);
    this->setWindowTitle(tr("客户信息维护"));

    QLabel *label1 = new QLabel(tr("客户编号"),this);
    label1->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label2 = new QLabel(tr("客户名称"),this);
    label2->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label3 = new QLabel(tr("联系人"),this);
    label3->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label5 = new QLabel(tr("欠款限额"),this);
    label5->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label6 = new QLabel(tr("移动电话"),this);
    label6->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label7 = new QLabel(tr("所属部门"),this);
    label7->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label8 = new QLabel(tr("地址"),this);
    label8->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label9 = new QLabel(tr("备注"),this);
    label9->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label10 = new QLabel(tr("元"),this);
    label10->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);

    lineEdit1 = new QLineEdit(this);
    lineEdit1->setReadOnly(true);
    lineEdit2 = new QLineEdit(this);
    lineEdit3 = new QLineEdit(this);
    lineEdit5 = new QLineEdit(this);
    lineEdit6 = new QLineEdit(this);
    lineEdit8 = new QLineEdit(this);
    lineEdit9 = new QLineEdit(this);

    combo = new QComboBox(this);
    const char *fillSQL = "select DepartmentName from SectorSettings;";
    db.sql_fillComboBoxItem(fillSQL,combo);

    checkBox = new QCheckBox(tr("是否属于重点客户"),this);

    view = new QTableView(this);
    connect(view,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick()));
    db.showview_num(SQL,view,&model,0);//显示表格
    view->setColumnWidth(1,300);
    view->setColumnWidth(7,120);

    QGridLayout *layout1 = new QGridLayout;
    layout1->addWidget(label1,0,0);
    layout1->addWidget(lineEdit1,0,1);
    layout1->addWidget(label2,0,2);
    layout1->addWidget(lineEdit2,0,3,1,2);
    layout1->addWidget(label3,0,5);
    layout1->addWidget(lineEdit3,0,6);
    layout1->addWidget(checkBox,1,0,1,2,Qt::AlignCenter);
    layout1->addWidget(label5,1,2);
    layout1->addWidget(lineEdit5,1,3);
    layout1->addWidget(label10,1,4);
    layout1->addWidget(label6,1,5);
    layout1->addWidget(lineEdit6,1,6);
    layout1->addWidget(label7,2,0);
    layout1->addWidget(combo,2,1);
    layout1->addWidget(label8,2,2);
    layout1->addWidget(lineEdit8,2,3,1,2);
    layout1->addWidget(label9,3,0);
    layout1->addWidget(lineEdit9,3,1,1,4);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(toolBar);
    vlayout->addLayout(layout1);
    vlayout->addWidget(view);
}

kehudanganDlg::~kehudanganDlg()
{
    delete model;
}

void kehudanganDlg::refresh()
{

}

void kehudanganDlg::keyPressEvent(QKeyEvent *event)
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

void kehudanganDlg::on_newAction()
{
    lineEdit1->setFocus();
    saveAction->setEnabled(true);
    updateAction->setEnabled(false);
    deleteAction->setEnabled(false);


    QString searchSQL = QString("select CustomerNumber from CustomerFiles order by CustomerNumber+0 desc limit 1");
    lineEdit1->setText(QString::number(db.sql_fetchrow_plus(searchSQL.toStdString().data(),0).toDouble()+1));
    lineEdit2->clear();
    lineEdit3->clear();
    lineEdit5->clear();
    lineEdit6->clear();
    lineEdit8->clear();
    lineEdit9->clear();
    combo->setCurrentIndex(0);
    checkBox->setCheckState(Qt::Unchecked);
}

void kehudanganDlg::on_saveAction()
{
    if(lineEdit1->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入客户编号"),0,0,0);
        return;
    }
    if(lineEdit2->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入客户名称"),0,0,0);
        return;
    }
    if(lineEdit5->text().isEmpty()){
        str5 = "0";
    }
    if(checkBox->checkState() == 0){
        str4 = "";
    }
    if(checkBox->checkState() == 2){
        str4 = "重点客户";
    }

    QString saveSQL = QString("insert into CustomerFiles (CustomerNumber,CustomerName,Contacts,MobilePhone,DebtLimit,Address,GroupOfGenus,\
                              WhetherKeyCustomers,Remarks) values ('%1','%2','%3','%4','%5','%6','%7','%8','%9');")
                    .arg(lineEdit1->text(),lineEdit2->text(),lineEdit3->text(),lineEdit6->text(),lineEdit5->text(),lineEdit8->text(),combo->currentText(),str4,lineEdit9->text());

    int res = db.sql_exec(saveSQL.toStdString().data());
    if(res == -1){
        if(strstr(db.geterror(),"PRIMARY") != NULL){
            QMessageBox::information(this,tr("错误"),tr("请检查客户编号是否重复"),0,0,0);
        }
        return;
    }
    else if(res == 0){
        db.showview_num(SQL,view,&model,0);//发送刷新消息
        on_newAction();
        lineEdit1->clear();
        QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
    }
}

void kehudanganDlg::on_updateAction()
{
    if(lineEdit2->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入客户名称"),0,0,0);
        return;
    }
    if(lineEdit5->text().isEmpty()){
        str5 = "0";
    }
    if(checkBox->checkState() == 0){
        str4 = "";
    }
    else if(checkBox->checkState() == 2){
        str4 = "重点客户";
    }

    QString updateSQL = QString("update CustomerFiles set CustomerName='%1',Contacts='%2',MobilePhone='%3',DebtLimit='%4',Address='%5',GroupOfGenus='%6',\
                                WhetherKeyCustomers='%7',Remarks='%8' where CustomerNumber='%9';")
                    .arg(lineEdit2->text(),lineEdit3->text(),lineEdit6->text(),lineEdit5->text(),lineEdit8->text(),combo->currentText(),str4,lineEdit9->text(),lineEdit1->text());

    int res = db.sql_exec(updateSQL.toStdString().data());
    if(res == 0){
        db.showview_num(SQL,view,&model,0);//发送刷新消息
        on_newAction();
        lineEdit1->clear();
        QMessageBox::information(this,tr("提示信息"),tr("修改成功"),0,0,0);
    }
}

void kehudanganDlg::on_deleteAction()
{
    QString deleteSQL = QString("delete from CustomerFiles where CustomerNumber='%1';").arg(lineEdit1->text());
    int res = db.sql_exec(deleteSQL.toStdString().data());
    if(res == 0){
        db.showview_num(SQL,view,&model,0);//发送刷新消息
        on_newAction();
        lineEdit1->clear();
        QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
    }
}

void kehudanganDlg::ShowSupplyclick()
{
    updateAction->setEnabled(true);
    deleteAction->setEnabled(true);
    saveAction->setEnabled(false);
    int row = view->currentIndex().row();

    lineEdit1->setText(model->item(row,0)->text());
    lineEdit2->setText(model->item(row,1)->text());
    lineEdit3->setText(model->item(row,2)->text());
    lineEdit5->setText(model->item(row,4)->text());
    lineEdit6->setText(model->item(row,3)->text());
    lineEdit8->setText(model->item(row,5)->text());
    lineEdit9->setText(model->item(row,8)->text());
    if(strcmp("重点客户",model->item(row,7)->text().toStdString().data()) == 0){
        checkBox->setCheckState(Qt::Checked);
    }else{
        checkBox->setCheckState(Qt::Unchecked);
    }
    combo->setCurrentText(model->item(row,6)->text());
}

void kehudanganDlg::createAction()
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

void kehudanganDlg::createTool()
{
    toolBar = new QToolBar(this);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar->addAction(newAction);
    toolBar->addAction(saveAction);
    toolBar->addAction(updateAction);
    toolBar->addAction(deleteAction);
}
