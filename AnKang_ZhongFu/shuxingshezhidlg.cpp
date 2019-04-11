#include "shuxingshezhidlg.h"
#include "mainwindow.h"

extern mymysql db;
extern myTCPsocket *sockClient;

shuxingshezhiDlg::shuxingshezhiDlg(QWidget *parent) :
    QDialog(parent)
{
    tabWidget = new QTabWidget;
    tabWidget->resize(1000,700);
    chanpinshuxing = new QWidget;
    jiaozhubuwei = new QWidget;
    jiaozhufangfa = new QWidget;
    this->setWindowFlags(windowFlags()& ~Qt::WindowContextHelpButtonHint);
    this->setWindowTitle(tr("属性设置"));

    creatTabPage1();
    creatTabPage2();
    creatTabPage3();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tabWidget);
}

shuxingshezhiDlg::~shuxingshezhiDlg()
{
    delete onemodel;
    delete twomodel;
    delete threemodel;
}

void shuxingshezhiDlg::refresh()
{
    db.showview(SQL1,oneview,&onemodel);//显示表格
    db.showview(SQL2,twoview,&twomodel);//显示表格
    db.showview(SQL3,threeview,&threemodel);//显示表格
}

void shuxingshezhiDlg::keyPressEvent(QKeyEvent *event)
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

void shuxingshezhiDlg::creatTabPage1()
{
    createAction();
    createTool();
    SQL1 = "select ID 属性编号,AttributeName 属性名称,Price 价格 from ProductAttributes;";

    QLabel *label1  = new QLabel(tr("属性编号"));
    label1->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label2  = new QLabel(tr("属性名称"));
    label1->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label3  = new QLabel(tr("标准价格"));
    label1->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label4  = new QLabel(tr("元/方"));
    label1->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);

    onelineEdit1 = new QLineEdit;
    onelineEdit1->setStyleSheet("color:black");
    onelineEdit2 = new QLineEdit;
    onelineEdit3 = new QLineEdit;

    oneview = new QTableView;
    connect(oneview,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick()));
    db.showview(SQL1,oneview,&onemodel);//显示表格
    oneview->setColumnWidth(0,150);
    oneview->setColumnWidth(1,150);
    oneview->setColumnWidth(2,150);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(label1);
    hlayout->addWidget(onelineEdit1);
    hlayout->addWidget(label2);
    hlayout->addWidget(onelineEdit2);
    hlayout->addWidget(label3);
    hlayout->addWidget(onelineEdit3);
    hlayout->addWidget(label4);
    hlayout->addStretch(2);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(toolBar);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(oneview);

    chanpinshuxing->setLayout(vlayout);
    tabWidget->addTab(chanpinshuxing,tr("产品属性"));
}

void shuxingshezhiDlg::creatTabPage2()
{
    createAction2();
    createTool2();
    SQL2 = "select PouringPosition 浇筑部位,ID from PouringPosition;";

    QLabel *label1  = new QLabel(tr("浇筑部位"));
    twolineEdit1 = new QLineEdit;

    twoview = new QTableView;
    connect(twoview,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick2()));
    db.showview(SQL2,twoview,&twomodel);//显示表格
    twoview->setColumnWidth(0,300);
    twoview->setColumnHidden(1,true);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(label1);
    hlayout->addWidget(twolineEdit1,1);
    hlayout->addStretch(5);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(toolBar2);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(twoview);

    jiaozhubuwei->setLayout(vlayout);
    tabWidget->addTab(jiaozhubuwei,tr("浇筑部位"));
}

void shuxingshezhiDlg::creatTabPage3()
{
    createAction3();
    createTool3();
    SQL3 = "select PouringMethod 浇筑方法,ID from PouringMethod;";

    QLabel *label1  = new QLabel(tr("浇筑方法"));
    threelineEdit1 = new QLineEdit;

    threeview = new QTableView;
    connect(threeview,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick3()));
    db.showview(SQL3,threeview,&threemodel);//显示表格
    threeview->setModel(threemodel);
    threeview->setColumnWidth(0,300);
    threeview->setColumnHidden(1,true);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(label1);
    hlayout->addWidget(threelineEdit1,1);
    hlayout->addStretch(5);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(toolBar3);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(threeview);

    jiaozhufangfa->setLayout(vlayout);
    tabWidget->addTab(jiaozhufangfa,tr("浇筑方法"));
}

void shuxingshezhiDlg::on_newAction()
{
    onelineEdit1->setFocus();
    saveAction->setEnabled(true);
    updateAction->setEnabled(false);
    deleteAction->setEnabled(false);

    onelineEdit1->clear();
    onelineEdit1->setEnabled(true);
    onelineEdit2->clear();
    onelineEdit3->clear();
}

void shuxingshezhiDlg::on_saveAction()
{
    if(onelineEdit1->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入属性编号"),0,0,0);
        return;
    }
    if(onelineEdit2->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入属性名称"),0,0,0);
        return;
    }
    QString saveSQL = QString("insert into ProductAttributes (ID,AttributeName,Price) values ('%1','%2','%3');").arg(onelineEdit1->text(),onelineEdit2->text(),onelineEdit3->text());
    int res = db.sql_exec(saveSQL.toStdString().data());
    if(res == -1){
        if((strstr(db.geterror(),"PRIMARY")) != NULL){
            QMessageBox::information(this, tr("失败"),tr("请检查属性编号是否重复"),0,0,0);
            return;
        }
        else if((strstr(db.geterror(),"AttributeName")) != NULL){
            QMessageBox::information(this, tr("失败"),tr("请检查属性名称是否重复"),0,0,0);
            return;
        }
    }else if(res == 0){
        sockClient->send_Msg3();//发送刷新消息
        on_newAction();
        QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
    }
}

void shuxingshezhiDlg::on_updateAction()
{
    if(onelineEdit1->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入属性编号"),0,0,0);
        return;
    }
    if(onelineEdit2->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入属性名称"),0,0,0);
        return;
    }
    QString updateSQL = QString("update ProductAttributes set AttributeName='%1',Price='%2' where ID='%3';").arg(onelineEdit2->text(),onelineEdit3->text(),onelineEdit1->text());
    int res = db.sql_exec(updateSQL.toStdString().data());
    if(res == -1){
        if((strstr(db.geterror(),"AttributeName")) != NULL){
            QMessageBox::information(this, tr("失败"),tr("请检查属性名称是否重复"),0,0,0);
            return;
        }
    }else if(res == 0){
        sockClient->send_Msg3();//发送刷新消息
        on_newAction();
        QMessageBox::information(this,tr("提示信息"),tr("修改成功"),0,0,0);
    }
}

void shuxingshezhiDlg::on_deleteAction()
{
    QString deleteSQL = QString("delete from ProductAttributes where ID='%1';").arg(onelineEdit1->text());
    int res = db.sql_exec(deleteSQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();//发送刷新消息
        on_newAction();
        QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
    }
}

void shuxingshezhiDlg::on_newAction2()
{
    twolineEdit1->setFocus();
    saveAction2->setEnabled(true);
    updateAction2->setEnabled(false);
    deleteAction2->setEnabled(false);

    twolineEdit1->clear();
    twolineEdit1->setEnabled(true);
}

void shuxingshezhiDlg::on_saveAction2()
{
    if(twolineEdit1->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入浇筑部位"),0,0,0);
        return;
    }
    QString save2SQL = QString("insert into PouringPosition (PouringPosition) values ('%1');").arg(twolineEdit1->text());
    int res = db.sql_exec(save2SQL.toStdString().data());
    if(res == -1){
        if(strstr(db.geterror(),"PouringPosition") != NULL){
            QMessageBox::information(this, tr("失败"),tr("请检查浇筑部位是否重复"),0,0,0);
            return;
        }
    }else if(res == 0){
        sockClient->send_Msg3();//发送刷新消息
        on_newAction2();
        QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
    }
}

void shuxingshezhiDlg::on_updateAction2()
{
    if(twolineEdit1->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入浇筑部位"),0,0,0);
        return;
    }
    QString update2SQL = QString("update PouringPosition set PouringPosition='%1' where ID=%2;").arg(twolineEdit1->text(),twostr2.toInt());
    int res = db.sql_exec(update2SQL.toStdString().data());
    if(res == -1){
        if(strstr(db.geterror(),"PouringPosition") != NULL){
            QMessageBox::information(this, tr("失败"),tr("请检查浇筑部位是否重复"),0,0,0);
            return;
        }
    }else if(res == 0){
        sockClient->send_Msg3();//发送刷新消息
        on_newAction2();
        QMessageBox::information(this,tr("提示信息"),tr("修改成功"),0,0,0);
    }
}

void shuxingshezhiDlg::on_deleteAction2()
{
    QString delete2SQL = QString("delete from PouringPosition where ID=%1;").arg(twostr2.toInt());
    int res = db.sql_exec(delete2SQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();//发送刷新消息
        on_newAction2();
        QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
    }
}

void shuxingshezhiDlg::on_newAction3()
{
    threelineEdit1->setFocus();
    saveAction3->setEnabled(true);
    updateAction3->setEnabled(false);
    deleteAction3->setEnabled(false);

    threelineEdit1->clear();
    threelineEdit1->setEnabled(true);
}

void shuxingshezhiDlg::on_saveAction3()
{
    if(threelineEdit1->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入浇筑方法"),0,0,0);
        return;
    }
    QString save3SQL = QString("insert into PouringMethod (PouringMethod) values ('%1');").arg(threelineEdit1->text());
    int res = db.sql_exec(save3SQL.toStdString().data());
    if(res == -1){
        if(strstr(db.geterror(),"PouringMethod") != NULL){
            QMessageBox::information(this, tr("失败"),tr("请检查浇筑方法是否重复"),0,0,0);
            return;
        }
    }else if(res == 0){
        sockClient->send_Msg3();//发送刷新消息
        on_newAction3();
        QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
    }
}

void shuxingshezhiDlg::on_updateAction3()
{
    if(threelineEdit1->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入浇筑方法"),0,0,0);
        return;
    }
    QString update3SQL = QString("update PouringMethod set PouringMethod='%1' where ID=%2;").arg(threelineEdit1->text(),threestr2.toInt());
    int res = db.sql_exec(update3SQL.toStdString().data());
    if(res == -1){
        if(strstr(db.geterror(),"PouringMethod") != NULL){
            QMessageBox::information(this, tr("失败"),tr("请检查浇筑方法是否重复"),0,0,0);
            return;
        }
    }else if(res == 0){
        sockClient->send_Msg3();//发送刷新消息
        on_newAction3();
        QMessageBox::information(this,tr("提示信息"),tr("修改成功"),0,0,0);
    }
}

void shuxingshezhiDlg::on_deleteAction3()
{
    QString delete3SQL = QString("delete from PouringMethod where ID=%1;").arg(threestr2.toInt());
    int res = db.sql_exec(delete3SQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();//发送刷新消息
        on_newAction3();
        QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
    }
}

void shuxingshezhiDlg::ShowSupplyclick()
{
    onelineEdit1->setEnabled(false);
    updateAction->setEnabled(true);
    deleteAction->setEnabled(true);
    saveAction->setEnabled(false);
    int row = oneview->currentIndex().row();

    onelineEdit1->setText(onemodel->item(row,0)->text());
    onelineEdit2->setText(onemodel->item(row,1)->text());
    onelineEdit3->setText(onemodel->item(row,2)->text());
}

void shuxingshezhiDlg::ShowSupplyclick2()
{
    updateAction2->setEnabled(true);
    deleteAction2->setEnabled(true);
    saveAction2->setEnabled(false);
    int row = twoview->currentIndex().row();

    twolineEdit1->setText(twomodel->item(row,0)->text());
    twostr2 = twomodel->item(row,1)->text();
}

void shuxingshezhiDlg::ShowSupplyclick3()
{
    updateAction3->setEnabled(true);
    deleteAction3->setEnabled(true);
    saveAction3->setEnabled(false);
    int row = threeview->currentIndex().row();

    threelineEdit1->setText(threemodel->item(row,0)->text());
    threestr2 = threemodel->item(row,1)->text();
}

void shuxingshezhiDlg::createAction()
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

void shuxingshezhiDlg::createTool()
{
    toolBar = new QToolBar;
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar->addAction(newAction);
    toolBar->addAction(saveAction);
    toolBar->addAction(updateAction);
    toolBar->addAction(deleteAction);
}

void shuxingshezhiDlg::createAction2()
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

void shuxingshezhiDlg::createTool2()
{
    toolBar2 = new QToolBar;
    toolBar2->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar2->addAction(newAction2);
    toolBar2->addAction(saveAction2);
    toolBar2->addAction(updateAction2);
    toolBar2->addAction(deleteAction2);
}

void shuxingshezhiDlg::createAction3()
{
    newAction3 = new QAction(tr("新增"),this);
    newAction3->setIcon(QIcon(":/image/new.png"));
    connect(newAction3,SIGNAL(triggered()),this,SLOT(on_newAction3()));
    saveAction3 = new QAction(tr("保存"),this);
    saveAction3->setIcon(QIcon(":/image/save.png"));
    connect(saveAction3,SIGNAL(triggered()),this,SLOT(on_saveAction3()));
    updateAction3 = new QAction(tr("修改"),this);
    updateAction3->setEnabled(false);
    updateAction3->setIcon(QIcon(":/image/update.png"));
    connect(updateAction3,SIGNAL(triggered()),this,SLOT(on_updateAction3()));
    deleteAction3 = new QAction(tr("删除"),this);
    deleteAction3->setEnabled(false);
    deleteAction3->setIcon(QIcon(":/image/delete.png"));
    connect(deleteAction3,SIGNAL(triggered()),this,SLOT(on_deleteAction3()));
}

void shuxingshezhiDlg::createTool3()
{
    toolBar3 = new QToolBar;
    toolBar3->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar3->addAction(newAction3);
    toolBar3->addAction(saveAction3);
    toolBar3->addAction(updateAction3);
    toolBar3->addAction(deleteAction3);
}
