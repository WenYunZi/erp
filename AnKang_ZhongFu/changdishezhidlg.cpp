#include "changdishezhidlg.h"

extern mymysql db;
extern myTCPsocket *sockClient;

changdishezhiDlg::changdishezhiDlg(QWidget *parent) :
    QDialog(parent)
{
    createAction();
    createTool();

    SQL = "select PlantNo 厂地编号,PlantName 厂地名称 from FactorySetting;";

    QLabel *label1 = new QLabel(tr("厂地编号"),this);
    label1->setStyleSheet("color:red");
    QLabel *label2 = new QLabel(tr("厂地名称"),this);
    label2->setStyleSheet("color:red");

    lineEdit1 = new QLineEdit(this);
    lineEdit1->setStyleSheet("color:black");
    lineEdit2 = new QLineEdit(this);

    view = new QTableView(this);
    connect(view,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick()));
    db.showview(SQL,view,&model);//显示表格
    view->setColumnWidth(0,150);
    view->setColumnWidth(1,500);
    view->setColumnWidth(2,300);

    QHBoxLayout *layout1 = new QHBoxLayout;
    layout1->addWidget(label1);
    layout1->addWidget(lineEdit1);
    layout1->addWidget(label2);
    layout1->addWidget(lineEdit2);
    layout1->addStretch(4);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(toolBar);
    vlayout->addLayout(layout1);
    vlayout->addWidget(view);
}

changdishezhiDlg::~changdishezhiDlg()
{
    delete model;
}

void changdishezhiDlg::refresh()
{
    db.showview(SQL,view,&model);//显示表格
}

void changdishezhiDlg::keyPressEvent(QKeyEvent *event)
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

void changdishezhiDlg::on_newAction()
{
    lineEdit1->setFocus();
    saveAction->setEnabled(true);
    updateAction->setEnabled(false);
    deleteAction->setEnabled(false);

    lineEdit1->clear();
    lineEdit1->setEnabled(true);
    lineEdit2->clear();
}

void changdishezhiDlg::on_saveAction()
{
    if(lineEdit1->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入厂地编号"),0,0,0);
        return;
    }
    if(lineEdit2->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入厂地名称"),0,0,0);
        return;
    }

    QString saveSQL = QString("insert into FactorySetting (PlantNo, PlantName) values ('%1','%2');").arg(lineEdit1->text(),lineEdit2->text());
    int res = db.sql_exec(saveSQL.toStdString().data());
    if(res == -1){
        if((strstr(db.geterror(),"PRIMARY")) != NULL){
            QMessageBox::information(this, tr("失败"),tr("请检查厂地编号是否重复"),0,0,0);
        }
        return;
    }
    else if(res == 0){
        sockClient->send_Msg3();
        on_newAction();
        QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
    }
}

void changdishezhiDlg::on_updateAction()
{
    if(lineEdit2->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入司机姓名"),0,0,0);
        return;
    }
    QString updateSQL = QString("update FactorySetting set PlantName='%1' where PlantNo='%3';").arg(lineEdit2->text(),lineEdit1->text());
    int res = db.sql_exec(updateSQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();
        on_newAction();
        QMessageBox::information(this,tr("提示信息"),tr("修改成功"),0,0,0);
    }
}

void changdishezhiDlg::on_deleteAction()
{
    QString deleteSQL = QString("delete from FactorySetting where PlantNo='%1';").arg(lineEdit1->text());
    int res = db.sql_exec(deleteSQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();
        on_newAction();
        QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
    }
}

void changdishezhiDlg::ShowSupplyclick()
{
    lineEdit1->setEnabled(false);
    updateAction->setEnabled(true);
    deleteAction->setEnabled(true);
    saveAction->setEnabled(false);
    int row = view->currentIndex().row();

    lineEdit1->setText(model->item(row,0)->text());
    lineEdit2->setText(model->item(row,1)->text());
}

void changdishezhiDlg::createAction()
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

void changdishezhiDlg::createTool()
{
    toolBar = new QToolBar(this);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar->addAction(newAction);
    toolBar->addAction(saveAction);
    toolBar->addAction(updateAction);
    toolBar->addAction(deleteAction);
}
