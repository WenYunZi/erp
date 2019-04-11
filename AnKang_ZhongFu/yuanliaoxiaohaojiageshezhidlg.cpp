#include "yuanliaoxiaohaojiageshezhidlg.h"

extern mymysql db;

yuanliaoxiaohaojiageshezhiDlg::yuanliaoxiaohaojiageshezhiDlg(QWidget *parent) :
    QDialog(parent)
{
    SQL = "select MatName 原料名称,SpecificationModel 原料规格,startDate 启用日期,Price 启用价格 from MatXiaohaoPriceSetting;";

    createAction();
    createTool();

    QLabel *label1 = new QLabel(tr("原料名称"),this);
    label1->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label2 = new QLabel(tr("原料规格"),this);
    label2->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label3 = new QLabel(tr("启用日期"),this);
    label3->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label4 = new QLabel(tr("启用价格"),this);
    label4->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    lineEdit1 = new QLineEdit(this);
    lineEdit1->setReadOnly(true);
    lineEdit2 = new QLineEdit(this);

    comBox = new QComboBox(this);
    const char *fillSQL = "select Material from MaterialSetting group by Material;";
    db.sql_fillComboBoxItem(fillSQL,comBox);
    connect(comBox,SIGNAL(currentIndexChanged(int)),this,SLOT(comBoxReply()));

    dateEdit1 = new QDateEdit(QDate::currentDate(),this);
    dateEdit1->setCalendarPopup(true);
    dateEdit1->setDisplayFormat("yyyy-MM-dd");

    view1 = new QTableView(this);
    db.showview(SQL,view1,&model);
    view1->setColumnWidth(2,170);
    connect(view1,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick()));

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(label1,0);
    hlayout->addWidget(comBox,1);
    hlayout->addWidget(label2,0);
    hlayout->addWidget(lineEdit1,1);
    hlayout->addWidget(label3,0);
    hlayout->addWidget(dateEdit1,1);
    hlayout->addWidget(label4,0);
    hlayout->addWidget(lineEdit2,1);
    hlayout->addStretch(2);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(toolBar);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(view1);
}

void yuanliaoxiaohaojiageshezhiDlg::keyPressEvent(QKeyEvent *event)
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

void yuanliaoxiaohaojiageshezhiDlg::on_newAction()
{
    comBox->setEnabled(true);
    saveAction->setEnabled(true);
    deleteAction->setEnabled(false);

    comBox->setCurrentIndex(0);
    lineEdit1->clear();
    lineEdit2->clear();
}

void yuanliaoxiaohaojiageshezhiDlg::on_saveAction()
{
    if(comBox->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择原料名称"),0,0,0);
        return;
    }
    QString saveSQL = QString("insert into MatXiaohaoPriceSetting (MatName,SpecificationModel,startDate,Price) values ('%1','%2','%3','%4');")
                        .arg(comBox->currentText(),lineEdit1->text(),dateEdit1->date().toString("yyyy-MM-dd 00:00:00"),lineEdit2->text());
    int res = db.sql_exec(saveSQL.toStdString().data());
    if(res == 0){
        db.showview(SQL,view1,&model);//发送刷新消息
        on_newAction();
        QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
    }
}

void yuanliaoxiaohaojiageshezhiDlg::on_deleteAction()
{
    QString deleteSQL = QString("delete from MatXiaohaoPriceSetting where MatName='%1' and startDate='%2';")
            .arg(comBox->currentText(),dateEdit1->date().toString("yyyy-MM-dd 00:00:00"));
    int res = db.sql_exec(deleteSQL.toStdString().data());
    if(res == 0){
        db.showview(SQL,view1,&model);//发送刷新消息
        on_newAction();
        QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
    }
}

void yuanliaoxiaohaojiageshezhiDlg::ShowSupplyclick()
{
    deleteAction->setEnabled(true);
    saveAction->setEnabled(false);
    comBox->setEnabled(false);

    int row = view1->currentIndex().row();
    comBox->setCurrentText(model->item(row,0)->text());
    lineEdit1->setText(model->item(row,1)->text());
    lineEdit2->setText(model->item(row,3)->text());
    dateEdit1->setDate(QDate::fromString(model->item(row,2)->text().left(10),"yyyy-MM-dd"));
}

void yuanliaoxiaohaojiageshezhiDlg::comBoxReply()
{
    QString searchSQL = QString("select SpecificationModel from MaterialSetting where Material='%1';").arg(comBox->currentText());
    lineEdit1->setText(db.sql_fetchrow_plus(searchSQL.toStdString().data(),0));
}

void yuanliaoxiaohaojiageshezhiDlg::createAction()
{
    newAction = new QAction(tr("新增"),this);
    newAction->setIcon(QIcon(":/image/new.png"));
    connect(newAction,SIGNAL(triggered()),this,SLOT(on_newAction()));
    saveAction = new QAction(tr("保存"),this);
    saveAction->setIcon(QIcon(":/image/save.png"));
    connect(saveAction,SIGNAL(triggered()),this,SLOT(on_saveAction()));
    deleteAction = new QAction(tr("删除"),this);
    deleteAction->setEnabled(false);
    deleteAction->setIcon(QIcon(":/image/delete.png"));
    connect(deleteAction,SIGNAL(triggered()),this,SLOT(on_deleteAction()));
}

void yuanliaoxiaohaojiageshezhiDlg::createTool()
{
    toolBar = new QToolBar(this);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar->addAction(newAction);
    toolBar->addAction(saveAction);
    toolBar->addAction(deleteAction);
}
