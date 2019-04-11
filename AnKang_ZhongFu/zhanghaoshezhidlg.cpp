#include "zhanghaoshezhidlg.h"

extern mymysql db;
extern QString userName;
extern myTCPsocket *sockClient;

zhanghaoshezhiDlg::zhanghaoshezhiDlg(QWidget *parent) :
    QDialog(parent)
{
    SQL = "select AccountName 账号名称,AccountAmount 账号金额,SetPeople 设置人,SetupTime 设置时间,ID from FinancialAccount;";

    createAction();
    createTool();

    QLabel *label1 = new QLabel(tr("账号名称"));
    label1->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label2 = new QLabel(tr("账号金额"));
    label2->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

    lineEdit1 = new QLineEdit;
    lineEdit1->setStyleSheet("color:black");
    lineEdit2 = new QLineEdit;

    view = new QTableView;
    db.showview(SQL,view,&model);
    connect(view,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick()));
    view->setColumnWidth(3,130);
    view->setColumnHidden(4,true);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(label1);
    hlayout->addWidget(lineEdit1);
    hlayout->addWidget(label2);
    hlayout->addWidget(lineEdit2);
    hlayout->addSpacing(500);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(toolBar);
    layout->addLayout(hlayout);
    layout->addWidget(view);
}

void zhanghaoshezhiDlg::refresh()
{
    db.showview(SQL,view,&model);
}

void zhanghaoshezhiDlg::keyPressEvent(QKeyEvent *event)
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

void zhanghaoshezhiDlg::createAction()
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

void zhanghaoshezhiDlg::createTool()
{
    toolBar = new QToolBar;
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar->addAction(newAction);
    toolBar->addAction(saveAction);
    toolBar->addAction(updateAction);
    toolBar->addAction(deleteAction);
}

void zhanghaoshezhiDlg::on_newAction()
{
    saveAction->setEnabled(true);
    updateAction->setEnabled(false);
    deleteAction->setEnabled(false);
    lineEdit1->setEnabled(true);

    lineEdit1->clear();
    lineEdit2->clear();
}

void zhanghaoshezhiDlg::on_saveAction()
{
    if(lineEdit1->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入账号名称"),0,0,0);
        return;
    }
    if(lineEdit2->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入账号金额"),0,0,0);
        return;
    }
    QString saveSQL = QString("insert into FinancialAccount (AccountName,AccountAmount,SetPeople,SetupTime) values ('%1','%2','%3','%4');")
            .arg(lineEdit1->text(),lineEdit2->text(),userName,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    int res = db.sql_exec(saveSQL.toStdString().data());
    if(res == -1){
        if(strstr(db.geterror(),"AccountName")!=NULL){
            QMessageBox::information(this,tr("提示信息"),tr("账号名称重复"),0,0,0);
            return;
        }
    }
    else if(res == 0){
        sockClient->send_Msg3();
        QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
        on_newAction();
    }
}

void zhanghaoshezhiDlg::on_updateAction()
{
    if(lineEdit2->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入账号金额"),0,0,0);
        return;
    }
    QString updateSQL = QString("update FinancialAccount set AccountAmount='%1',SetPeople='%2',SetupTime='%3' where AccountName='%4';")
            .arg(lineEdit2->text(),userName,QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"),lineEdit1->text());
    int res = db.sql_exec(updateSQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();
        QMessageBox::information(this,tr("提示信息"),tr("修改成功"),0,0,0);
        on_newAction();
    }
}

void zhanghaoshezhiDlg::on_deleteAction()
{
    QString deleteSQL = QString("delete from FinancialAccount where AccountName='%1';").arg(lineEdit1->text());
    int res = db.sql_exec(deleteSQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();
        QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
        on_newAction();
    }
}

void zhanghaoshezhiDlg::ShowSupplyclick()
{
    saveAction->setEnabled(false);
    updateAction->setEnabled(true);
    deleteAction->setEnabled(true);
    lineEdit1->setEnabled(false);

    int row = view->currentIndex().row();
    lineEdit1->setText(model->item(row,0)->text());
    lineEdit2->setText(model->item(row,1)->text());
}
