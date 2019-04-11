#include "bengchesijidlg.h"

extern mymysql db;
extern myTCPsocket *sockClient;

bengchesijiDlg::bengchesijiDlg(QWidget *parent) :
    QDialog(parent)
{
    SQL = "select DriverNo 司机编号,DriverName 司机姓名,Telephone 联系电话 from PumpDriver;";

    createAction();
    createTool();

    QLabel *label1 = new QLabel(tr("司机编号"),this);
    label1->setStyleSheet("color:red");
    label1->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label2 = new QLabel(tr("司机姓名"),this);
    label2->setStyleSheet("color:red");
    label2->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label3 = new QLabel(tr("联系电话"),this);
    label3->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

    lineEdit1 = new QLineEdit(this);
    lineEdit2 = new QLineEdit(this);
    lineEdit3 = new QLineEdit(this);


    view = new QTableView(this);
    db.showview(SQL,view,&model);
    connect(view,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick()));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label1,0,0);
    layout->addWidget(lineEdit1,0,1);
    layout->addWidget(view,0,2,10,1);
    layout->addWidget(label2,1,0);
    layout->addWidget(lineEdit2,1,1);
    layout->addWidget(label3,2,0);
    layout->addWidget(lineEdit3,2,1);
    layout->setColumnStretch(0,0);
    layout->setColumnStretch(1,0);
    layout->setColumnStretch(2,2);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(toolBar);
    vlayout->addLayout(layout);
}

void bengchesijiDlg::refresh()
{
    db.showview(SQL,view,&model);
}

void bengchesijiDlg::keyPressEvent(QKeyEvent *event)
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


void bengchesijiDlg::createAction()
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

void bengchesijiDlg::createTool()
{
    toolBar = new QToolBar(this);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar->addAction(newAction);
    toolBar->addAction(saveAction);
    toolBar->addAction(updateAction);
    toolBar->addAction(deleteAction);
}

void bengchesijiDlg::on_newAction()
{
    saveAction->setEnabled(true);
    updateAction->setEnabled(false);
    deleteAction->setEnabled(false);
    lineEdit1->setEnabled(true);

    lineEdit1->clear();
    lineEdit2->clear();
    lineEdit3->clear();
}

void bengchesijiDlg::on_saveAction()
{
    if(lineEdit1->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入司机编号"),0,0,0);
        return;
    }
    if(lineEdit2->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入司机姓名"),0,0,0);
        return;
    }
    QString saveSQL = QString("insert into PumpDriver (DriverNo,DriverName,Telephone) values \
                ('%1','%2','%3');").arg(lineEdit1->text(),lineEdit2->text(),lineEdit3->text());
    int res = db.sql_exec(saveSQL.toStdString().data());
    if(res == -1){
        if(strstr(db.geterror(),"PRIMARY") != NULL){
            QMessageBox::information(this,tr("错误"),tr("请检查司机编号是否重复"),0,0,0);
            return;
        }
    }
    else if(res == 0){
        sockClient->send_Msg3();
        on_newAction();
        QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
    }
}

void bengchesijiDlg::on_updateAction()
{
    if(lineEdit2->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入司机姓名"),0,0,0);
        return;
    }
    QString updateSQL = QString("update PumpDriver set DriverName='%1',Telephone='%2' where DriverNo='%3';")
            .arg(lineEdit2->text(),lineEdit3->text(),lineEdit1->text());
    int res = db.sql_exec(updateSQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();
        on_newAction();
        QMessageBox::information(this,tr("提示信息"),tr("修改成功"),0,0,0);
    }
}

void bengchesijiDlg::on_deleteAction()
{
    QString deleteSQL = QString("delete from PumpDriver where DriverNo='%1';").arg(lineEdit1->text());
    int res = db.sql_exec(deleteSQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();
        on_newAction();
        QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
    }
}

void bengchesijiDlg::ShowSupplyclick()
{
    updateAction->setEnabled(true);
    deleteAction->setEnabled(true);
    saveAction->setEnabled(false);
    lineEdit1->setEnabled(false);

    int row = view->currentIndex().row();
    lineEdit1->setText(model->item(row,0)->text());
    lineEdit2->setText(model->item(row,1)->text());
    lineEdit3->setText(model->item(row,2)->text());
}
