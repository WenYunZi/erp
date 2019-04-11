#include "gongchengmingchengdlg.h"

extern mymysql db;

gongchengmingchengDlg::gongchengmingchengDlg(QWidget *parent) :
    QDialog(parent)
{
    SQL = "select ProjectNo 工程编号,ProjectName  工程名称,Remarks 备注 from ProjectName;";

    createAction();
    createTool();
    this->setWindowFlags(windowFlags()& ~Qt::WindowContextHelpButtonHint);
    this->setWindowTitle(tr("工程名称"));

    QLabel *label1 = new QLabel(tr("工程编号"));
    label1->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label2 = new QLabel(tr("工程名称"));
    label2->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label3 = new QLabel(tr("备注"));
    label3->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

    lineEdit1 = new QLineEdit;
    lineEdit1->setStyleSheet("color:black");
    lineEdit2 = new QLineEdit;
    lineEdit3 = new QLineEdit;

    view = new QTableView;
    connect(view,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick()));
    db.showview(SQL,view,&model);
    view->setColumnWidth(1,400);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label1,0,0);
    layout->addWidget(lineEdit1,0,1);
    layout->addWidget(label2,0,2);
    layout->addWidget(lineEdit2,0,3);
    layout->addWidget(label3,1,0);
    layout->addWidget(lineEdit3,1,1,1,3);
    layout->addWidget(view,2,0,5,4);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(toolBar);
    vlayout->addLayout(layout);
}

gongchengmingchengDlg::~gongchengmingchengDlg()
{
    delete model;
}

void gongchengmingchengDlg::keyPressEvent(QKeyEvent *event)
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

void gongchengmingchengDlg::createAction()
{
    newAction = new QAction(tr("新增"),this);
    newAction->setIcon(QIcon(":/image/new.png"));
    connect(newAction,SIGNAL(triggered()),this,SLOT(on_newAction()));
    saveAction = new QAction(tr("保存"),this);
    saveAction->setIcon(QIcon(":/image/save.png"));
    connect(saveAction,SIGNAL(triggered()),this,SLOT(on_saveAction()));
    updateAction = new QAction(tr("修改"),this);
    updateAction->setEnabled(false);
    updateAction->setIcon(QIcon(":/image/new.png"));
    connect(updateAction,SIGNAL(triggered()),this,SLOT(on_updateAction()));
    deleteAction = new QAction(tr("删除"),this);
    deleteAction->setEnabled(false);
    deleteAction->setIcon(QIcon(":/image/new.png"));
    connect(deleteAction,SIGNAL(triggered()),this,SLOT(on_deleteAction()));
}

void gongchengmingchengDlg::createTool()
{
    toolBar = new QToolBar;
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar->addAction(newAction);
    toolBar->addAction(saveAction);
    toolBar->addAction(updateAction);
    toolBar->addAction(deleteAction);
}

void gongchengmingchengDlg::on_newAction()
{
    lineEdit1->clear();
    lineEdit2->clear();
    lineEdit3->clear();
    lineEdit1->setFocus();
    lineEdit1->setEnabled(true);
    saveAction->setEnabled(true);
    updateAction->setEnabled(false);
    deleteAction->setEnabled(false);
}

void gongchengmingchengDlg::on_saveAction()
{
    char *saveSQL = new char[1000];
    memset(saveSQL,0,1000);
    if(lineEdit1->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入工程编号"),0,0,0);
        return;
    }
    if(lineEdit2->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入工程名称"),0,0,0);
        return;
    }
    sprintf(saveSQL,"insert into ProjectName (ProjectNo,ProjectName,Remarks) values \
            ('%s','%s','%s');",lineEdit1->text().toStdString().data(),\
            lineEdit2->text().toStdString().data(),lineEdit3->text().toStdString().data());
    db.sql_exec(saveSQL);
    if(strstr(db.geterror(),"PRIMARY") != NULL){
        QMessageBox::information(this,tr("提示信息"),tr("请检查工程编号是否重复"),0,0,0);
        return;
    }
    if(strstr(db.geterror(),"ProjectName") != NULL){
        QMessageBox::information(this,tr("提示信息"),tr("请检查工程名称是否重复"),0,0,0);
        return;
    }
    db.showview(SQL,view,&model);
    on_newAction();
    delete [] saveSQL;
    QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
}

void gongchengmingchengDlg::on_updateAction()
{
    char *updateSQL = new char[1000];
    memset(updateSQL,0,1000);
    if(lineEdit2->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入工程名称"),0,0,0);
        return;
    }
    sprintf(updateSQL,"update ProjectName set ProjectName='%s',Remarks='%s' where ProjectNo='%s';",\
            lineEdit2->text().toStdString().data(),lineEdit3->text().toStdString().data(),\
            lineEdit1->text().toStdString().data());
    db.sql_exec(updateSQL);
    if(strstr(db.geterror(),"ProjectName") != NULL){
        QMessageBox::information(this,tr("错误"),tr("请检查工程名称是否重复"),0,0,0);
        return;
    }
    db.showview(SQL,view,&model);
    on_newAction();
    delete [] updateSQL;
    QMessageBox::information(this,tr("提示信息"),tr("修改成功"),0,0,0);
}

void gongchengmingchengDlg::on_deleteAction()
{
    char deleteSQL[200] = {0};
    sprintf(deleteSQL,"delete from ProjectName where ProjectNo='%s';",\
            lineEdit1->text().toStdString().data());
    db.sql_exec(deleteSQL);
    db.showview(SQL,view,&model);
    on_newAction();
    QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
}

void gongchengmingchengDlg::ShowSupplyclick()
{
    int row = view->currentIndex().row();
    lineEdit1->setText(model->item(row,0)->text());
    lineEdit2->setText(model->item(row,1)->text());
    lineEdit3->setText(model->item(row,2)->text());
    saveAction->setEnabled(false);
    updateAction->setEnabled(true);
    deleteAction->setEnabled(true);
    lineEdit1->setEnabled(false);
}
