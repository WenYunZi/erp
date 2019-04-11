#include "yunfeishezhidlg.h"

extern mymysql db;
extern myTCPsocket *sockClient;

yunfeishezhiDlg::yunfeishezhiDlg(QWidget *parent) :
    QDialog(parent)
{
    SQL = "select No 编号,VehicleType 车辆类型,MinimumMileage 里程下限（＞）,MaximumMileage 里程上限（＜＝）,Freight 运费 \
            from ConcreteCarFreightSet;";

    createAction();
    createTool();

    QLabel *label1 = new QLabel(tr("编号"),this);
    label1->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    label1->setHidden(true);
    QLabel *label2 = new QLabel(tr("车辆类型"),this);
    label2->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label3 = new QLabel(tr("里程下限"),this);
    label3->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label4 = new QLabel(tr("公里"),this);
    label4->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label5 = new QLabel(tr("里程上限"),this);
    label5->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label6 = new QLabel(tr("公里"),this);
    label6->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label7 = new QLabel(tr("运费"),this);
    label7->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label8 = new QLabel(tr("注意：里程指往返距离"),this);
    label8->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    label8->setStyleSheet("color:red");

    lineEdit1 = new QLineEdit(this);
    lineEdit1->setHidden(true);
    lineEdit2 = new QLineEdit(this);
    lineEdit3 = new QLineEdit(this);
    lineEdit4 = new QLineEdit(this);

    comBox1 = new QComboBox(this);
    comBox1->setView(new QListView(this));
    comBox1->addItem(tr(""));
    comBox1->addItem(tr("自有车辆"));

    view = new QTableView(this);
    db.showview_num(SQL,view,&model,2);
    view->setColumnHidden(0,true);
    connect(view,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick()));
    view->sortByColumn(2,Qt::AscendingOrder);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(label1,0);
    hlayout->addWidget(lineEdit1,1);
    hlayout->addWidget(label2,0);
    hlayout->addWidget(comBox1,1);
    hlayout->addWidget(label3,0);
    hlayout->addWidget(lineEdit2,1);
    hlayout->addWidget(label4,0);
    hlayout->addSpacing(15);
    hlayout->addWidget(label5,0);
    hlayout->addWidget(lineEdit3,1);
    hlayout->addWidget(label6,0);
    hlayout->addSpacing(15);
    hlayout->addWidget(label7,0);
    hlayout->addWidget(lineEdit4,1);
    hlayout->addWidget(label8,0);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(toolBar);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(view);
}

void yunfeishezhiDlg::refresh()
{
    db.showview_num(SQL,view,&model,2);
}

void yunfeishezhiDlg::keyPressEvent(QKeyEvent *event)
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

void yunfeishezhiDlg::createAction()
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

void yunfeishezhiDlg::createTool()
{
    toolBar = new QToolBar(this);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar->addAction(newAction);
    toolBar->addAction(saveAction);
    toolBar->addAction(updateAction);
    toolBar->addAction(deleteAction);
}

void yunfeishezhiDlg::on_newAction()
{
    saveAction->setEnabled(true);
    updateAction->setEnabled(false);
    deleteAction->setEnabled(false);

    lineEdit1->clear();
    lineEdit2->clear();
    lineEdit3->clear();
    lineEdit4->clear();
    comBox1->setCurrentIndex(0);
}

void yunfeishezhiDlg::on_saveAction()
{
    if(comBox1->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择车辆类型"),0,0,0);
        return;
    }
    if(lineEdit2->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入里程下限"),0,0,0);
        return;
    }
    if(lineEdit3->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入里程上限"),0,0,0);
        return;
    }
    if(lineEdit4->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入运费"),0,0,0);
        return;
    }
    QString saveSQL = QString("insert into ConcreteCarFreightSet (VehicleType,MinimumMileage,MaximumMileage,Freight) values ('%1','%2','%3','%4');").arg(comBox1->currentText(),lineEdit2->text(),lineEdit3->text(),lineEdit4->text());
    int res = db.sql_exec(saveSQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();
        on_newAction();
        QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
    }
}

void yunfeishezhiDlg::on_updateAction()
{
    if(comBox1->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择车辆类型"),0,0,0);
        return;
    }
    if(lineEdit2->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入里程下限"),0,0,0);
        return;
    }
    if(lineEdit3->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入里程上限"),0,0,0);
        return;
    }
    if(lineEdit4->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入运费"),0,0,0);
        return;
    }
    QString updateSQL = QString("update ConcreteCarFreightSet set VehicleType='%1',MinimumMileage='%2',MaximumMileage='%3',Freight='%4' where No='%5';").arg(comBox1->currentText(),lineEdit2->text(),lineEdit3->text(),lineEdit4->text(),lineEdit1->text());
    int res = db.sql_exec(updateSQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();
        on_newAction();
        QMessageBox::information(this,tr("提示信息"),tr("修改成功"),0,0,0);
    }
}

void yunfeishezhiDlg::on_deleteAction()
{
    QString deleteSQL = QString("delete from ConcreteCarFreightSet where No='%1';").arg(lineEdit1->text());
    int res = db.sql_exec(deleteSQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();
        on_newAction();
        QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
    }
}

void yunfeishezhiDlg::ShowSupplyclick()
{
    saveAction->setEnabled(false);
    updateAction->setEnabled(true);
    deleteAction->setEnabled(true);

    int row = view->currentIndex().row();
    lineEdit1->setText(model->item(row,0)->text());
    lineEdit2->setText(model->item(row,2)->text());
    lineEdit3->setText(model->item(row,3)->text());
    lineEdit4->setText(model->item(row,4)->text());
    comBox1->setCurrentText(model->item(row,1)->text());
}

