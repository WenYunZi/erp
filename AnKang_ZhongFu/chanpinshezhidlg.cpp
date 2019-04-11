#include "chanpinshezhidlg.h"

extern mymysql db;
extern myTCPsocket *sockClient;

chanpinshezhiDlg::chanpinshezhiDlg(QWidget *parent) :
    QDialog(parent)
{
    SQL = "select ID 产品编号,ProductName 产品名称,SpecificationModel 规格（型号）,Unit 单位,CumulativeTest 累计检验,Remarks 备注,Price 价格 from ProductSetting;";

    createAction();
    createTool();

    QLabel *label1 = new QLabel(tr("产品编号"),this);
    label1->setStyleSheet("color:red");
    label1->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label2 = new QLabel(tr("规格（型号）"),this);
    label2->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label3 = new QLabel(tr("累计检验"),this);
    label3->setStyleSheet("color:red");
    label3->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label4 = new QLabel(tr("吨"),this);
    label4->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    QLabel *label5 = new QLabel(tr("产品名称"),this);
    label5->setStyleSheet("color:red");
    label5->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label6 = new QLabel(tr("单位"),this);
    label6->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label7 = new QLabel(tr("标准价格"),this);
    label7->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label8 = new QLabel(tr("元/方"),this);
    label8->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label9 = new QLabel(tr("备注"),this);
    label9->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

    lineEdit1 = new QLineEdit(this);
    lineEdit1->setStyleSheet("color:black");
    lineEdit2 = new QLineEdit(this);
    lineEdit3 = new QLineEdit(this);
    lineEdit4 = new QLineEdit(this);
    lineEdit5 = new QLineEdit(this);
    lineEdit6 = new QLineEdit(this);


    view = new QTableView(this);
    connect(view,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick()));
    db.showview(SQL,view,&model);//显示表格

    combo1 = new QComboBox(this);
    combo1->setEditable(true);
    combo1->addItem(tr("方"));
    combo1->addItem(tr("公斤"));
    combo1->addItem(tr("吨"));
    combo1->addItem(tr("方/公斤"));
    combo1->addItem(tr("方/吨"));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label1,0,0);
    layout->addWidget(lineEdit1,0,1);
    layout->addWidget(label2,0,2);
    layout->addWidget(lineEdit2,0,3);
    layout->addWidget(label3,0,4);
    layout->addWidget(lineEdit3,0,5);
    layout->addWidget(label4,0,6);
    layout->addWidget(label5,1,0);
    layout->addWidget(lineEdit4,1,1);
    layout->addWidget(label6,1,2);
    layout->addWidget(combo1,1,3);
    layout->addWidget(label7,1,4);
    layout->addWidget(lineEdit5,1,5);
    layout->addWidget(label8,1,6);
    layout->addWidget(label9,2,0);
    layout->addWidget(lineEdit6,2,1,1,3);
    layout->setColumnStretch(0,0);
    layout->setColumnStretch(1,1);
    layout->setColumnStretch(2,0);
    layout->setColumnStretch(3,1);
    layout->setColumnStretch(4,0);
    layout->setColumnStretch(5,1);
    layout->setColumnStretch(6,0);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(toolBar);
    vlayout->addLayout(layout);
    vlayout->addWidget(view);
}

chanpinshezhiDlg::~chanpinshezhiDlg()
{
    delete model;
}

void chanpinshezhiDlg::refresh()
{
    db.showview(SQL,view,&model);//显示表格
}

void chanpinshezhiDlg::keyPressEvent(QKeyEvent *event)
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

void chanpinshezhiDlg::on_newAction()
{
    lineEdit1->setFocus();
    saveAction->setEnabled(true);
    updateAction->setEnabled(false);
    deleteAction->setEnabled(false);

    lineEdit1->clear();
    lineEdit1->setEnabled(true);
    lineEdit2->clear();
    lineEdit3->clear();
    lineEdit4->clear();
    lineEdit5->clear();
    lineEdit6->clear();
    combo1->setCurrentIndex(0);
}

void chanpinshezhiDlg::on_saveAction()
{
    if(lineEdit1->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入产品编号"),0,0,0);
        return;
    }
    if(lineEdit3->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入累计检验数量"),0,0,0);
        return;
    }
    if(lineEdit4->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入产品名称"),0,0,0);
        return;
    }

    QString saveSQL = QString("insert into ProductSetting (ID,ProductName,SpecificationModel,Unit,CumulativeTest,Remarks,Price) values ('%1','%2','%3','%4','%5','%6','%7');")
                    .arg(lineEdit1->text(),lineEdit4->text(),lineEdit2->text(),combo1->currentText(),lineEdit3->text(),lineEdit6->text(),lineEdit5->text());
    int res = db.sql_exec(saveSQL.toStdString().data());
    if(res == -1){
        if((strstr(db.geterror(),"PRIMARY")) != NULL){
            QMessageBox::information(this, tr("失败"),tr("请检查产品编号是否重复"),0,0,0);
            return;
        }
    }
    else if(res == 0){
        sockClient->send_Msg3();
        on_newAction();
        QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
    }
}

void chanpinshezhiDlg::on_updateAction()
{
    if(lineEdit1->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入产品编号"),0,0,0);
        return;
    }
    if(lineEdit3->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入累计检验数量"),0,0,0);
        return;
    }
    if(lineEdit4->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入产品名称"),0,0,0);
        return;
    }

    QString updateSQL = QString("update ProductSetting set ProductName='%1',SpecificationModel='%2',Unit='%3',CumulativeTest='%4',Remarks='%5',Price='%6' where ID='%7';")
            .arg(lineEdit4->text(),lineEdit2->text(),combo1->currentText(),lineEdit3->text(),lineEdit6->text(),lineEdit5->text(),lineEdit1->text());

    int res = db.sql_exec(updateSQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();
        on_newAction();
        QMessageBox::information(this,tr("提示信息"),tr("修改成功"),0,0,0);
    }
}

void chanpinshezhiDlg::on_deleteAction()
{
    QString deleteSQL = QString("delete from ProductSetting where ID='%1';").arg(lineEdit1->text());
    int res = db.sql_exec(deleteSQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();
        on_newAction();
        QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
    }
}

void chanpinshezhiDlg::ShowSupplyclick()
{
    lineEdit1->setEnabled(false);
    updateAction->setEnabled(true);
    deleteAction->setEnabled(true);
    saveAction->setEnabled(false);
    int row = view->currentIndex().row();

    lineEdit1->setText(model->item(row,0)->text());
    lineEdit2->setText(model->item(row,2)->text());
    lineEdit3->setText(model->item(row,4)->text());
    lineEdit4->setText(model->item(row,1)->text());
    lineEdit5->setText(model->item(row,6)->text());
    lineEdit6->setText(model->item(row,5)->text());
    combo1->setCurrentText(model->item(row,3)->text());
}

void chanpinshezhiDlg::createAction()
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

void chanpinshezhiDlg::createTool()
{
    toolBar = new QToolBar(this);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar->addAction(newAction);
    toolBar->addAction(saveAction);
    toolBar->addAction(updateAction);
    toolBar->addAction(deleteAction);
}
