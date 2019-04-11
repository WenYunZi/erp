#include "cangweishezhidlg.h"

extern mymysql db;
extern myTCPsocket *sockClient;

cangweishezhiDlg::cangweishezhiDlg(QWidget *parent) :
    QDialog(parent)
{
    SQL = "select ID 仓位编号,PositionName 仓位名称,InventoryCeiling 存货上限,\
        SubordinateDepartment 所属部门,DivisionOfGenus 所属机组,Material 存放原料,PlateName 厂地名称 from PositionSetting;";

    createAction();
    createTool();

    QLabel *label1 = new QLabel(tr("仓位编号"),this);
    label1->setStyleSheet("color:red");
    QLabel *label2 = new QLabel(tr("仓位名称"),this);
    label2->setStyleSheet("color:red");
    QLabel *label3 = new QLabel(tr("存货上限"),this);
    QLabel *label4 = new QLabel(tr("吨"),this);
    QLabel *label5 = new QLabel(tr("所属部门"),this);
    label5->setStyleSheet("color:red");
    QLabel *label6 = new QLabel(tr("所属机组"),this);
    label6->setStyleSheet("color:red");
    QLabel *label7 = new QLabel(tr("存放原料"),this);
    label7->setStyleSheet("color:red");
    QLabel *label8 = new QLabel(tr("如果仓位内已存有原料，原料\n不可修改，该仓位不能删除；"),this);
    label8->setStyleSheet("color:red");
    label8->setAlignment(Qt::AlignCenter);
    QLabel *label9 = new QLabel(tr("外加剂合成原料不设置仓位，\n只按库存存放"),this);
    label9->setStyleSheet("color:red");
    label9->setAlignment(Qt::AlignCenter);
    QLabel *label10 = new QLabel(tr("厂地名称"),this);
    label10->setStyleSheet("color:red");

    lineEdit1 = new QLineEdit(this);
    lineEdit1->setStyleSheet("color:black");
    lineEdit2 = new QLineEdit(this);
    lineEdit3 = new QLineEdit(this);

    view = new QTableView(this);
    connect(view,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick()));
    db.showview(SQL,view,&model);//显示表格

    combo1 = new QComboBox(this);
    const char *fillSQL1 = "select DepartmentName from SectorSettings where WhetherProduct='是';";
    db.sql_fillComboBoxItem(fillSQL1,combo1);
    combo2 = new QComboBox(this);
    const char *fillSQL2 = "select UnitName from UnitSetting;";
    db.sql_fillComboBoxItem(fillSQL2,combo2);
    combo3 = new QComboBox(this);
    const char *fillSQL3 = "select Material from MaterialSetting;";
    db.sql_fillComboBoxItem(fillSQL3,combo3);
    combo4 = new QComboBox(this);
    const char *fillSQL4 = "select PlantName from FactorySetting;";
    db.sql_fillComboBoxItem(fillSQL4,combo4);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label1,0,0);
    layout->addWidget(lineEdit1,0,1);
    layout->addWidget(view,0,3,12,1);
    layout->addWidget(label2,1,0);
    layout->addWidget(lineEdit2,1,1);
    layout->addWidget(label3,2,0);
    layout->addWidget(lineEdit3,2,1);
    layout->addWidget(label4,2,2);
    layout->addWidget(label5,3,0);
    layout->addWidget(combo1,3,1);
    layout->addWidget(label6,4,0);
    layout->addWidget(combo2,4,1);
    layout->addWidget(label7,5,0);
    layout->addWidget(combo3,5,1);
    layout->addWidget(label10,6,0);
    layout->addWidget(combo4,6,1);
    layout->addWidget(label8,7,0,1,2);
    layout->addWidget(label9,8,0,1,2);
    layout->setColumnStretch(0,0);
    layout->setColumnStretch(1,1);
    layout->setColumnStretch(2,0);
    layout->setColumnStretch(3,4);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(toolBar);
    vlayout->addLayout(layout);
}

cangweishezhiDlg::~cangweishezhiDlg()
{
    delete model;
}

void cangweishezhiDlg::refresh()
{
    db.showview(SQL,view,&model);//显示表格
}

void cangweishezhiDlg::keyPressEvent(QKeyEvent *event)
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

void cangweishezhiDlg::on_newAction()
{
    lineEdit1->setFocus();
    saveAction->setEnabled(true);
    updateAction->setEnabled(false);
    deleteAction->setEnabled(false);
    combo3->setEnabled(true);

    lineEdit1->clear();
    lineEdit1->setEnabled(true);
    lineEdit2->clear();
    lineEdit3->clear();
    combo1->setCurrentIndex(0);
    combo2->setCurrentIndex(0);
    combo3->setCurrentIndex(0);
    combo4->setCurrentIndex(0);
}

void cangweishezhiDlg::on_saveAction()
{
    if(lineEdit1->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),"请输入仓位编号",0,0,0);
        return;
    }
    if(lineEdit2->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),"请输入仓位名称",0,0,0);
        return;
    }
    QString saveSQL = QString("insert into PositionSetting (ID, PositionName , InventoryCeiling,SubordinateDepartment,\
                              DivisionOfGenus,Material,PlateName) values ('%1','%2','%3','%4','%5','%6','%7');")
                    .arg(lineEdit1->text(),lineEdit2->text(),lineEdit3->text(),combo1->currentText(),combo2->currentText(),
                         combo3->currentText(),combo4->currentText());
    int res = db.sql_exec(saveSQL.toStdString().data());
    if(res == -1){
        if((strstr(db.geterror(),"PRIMARY")) != NULL){
            QMessageBox::information(this, tr("失败"),tr("请检查仓位编号是否重复"),0,0,0);
            return;
        }
        if((strstr(db.geterror(),"PositionName")) != NULL){
            QMessageBox::information(this, tr("失败"),tr("请检查仓位名称是否重复"),0,0,0);
            return;
        }
    }else if(res == 0){
        //获取原材料编号
        QString MaterialNoSQL = QString("select ID from MaterialSetting where Material='%1';").arg(combo3->currentText());
        QString materialNo = db.sql_fetchrow_plus(MaterialNoSQL.toStdString().data(),0);
        //临时库存插入SQL语句
        QString kucunTmpSQL = QString("insert into InventoryQueryTmp (DepartmentName,PositionNumber,PositionName,Unit,Material,\
                                      Quantity,Factory,Time,MaterialNumber) values ('%1','%2','%3','%4','%5','0','%6','%7','%8');")
                            .arg(combo1->currentText(),lineEdit1->text(),lineEdit2->text(),combo2->currentText(),combo3->currentText(),
                                 combo4->currentText(),date.currentDate().toString("yyyy-MM-dd"),materialNo);
        db.sql_exec(kucunTmpSQL.toStdString().data());
        sockClient->send_Msg3();
        on_newAction();
        QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
    }
}

void cangweishezhiDlg::on_updateAction()
{
//    QString panduanSQL = QString("select Quantity from InventoryQueryTmp where PositionNumber='%1';").arg(lineEdit1->text());
//    double SurplusNum = db.sql_fetchrow_plus(panduanSQL.toStdString().data(),0).toDouble();
//    if(SurplusNum <= 0){
        if(lineEdit1->text().isEmpty()){
            QMessageBox::information(this,tr("提示信息"),tr("请输入仓位编号"),0,0,0);
            return;
        }
        if(lineEdit2->text().isEmpty()){
            QMessageBox::information(this,tr("提示信息"),tr("请输入仓位名称"),0,0,0);
            return;
        }
        QString updateSQL = QString("update PositionSetting set PositionName='%1', PlateName='%2',InventoryCeiling='%3',\
                                    SubordinateDepartment='%4',DivisionOfGenus='%5',Material='%6' where ID='%7';")
                        .arg(lineEdit2->text(),combo4->currentText(), lineEdit3->text(),combo1->currentText(),combo2->currentText(),
                             combo3->currentText(),lineEdit1->text());
        int res = db.sql_exec(updateSQL.toStdString().data());
        if(res == -1){
            if((strstr(db.geterror(),"PositionName")) != NULL){
                QMessageBox::information(this, tr("失败"),tr("请检查仓位名称是否重复"),0,0,0);
                return;
            }
        }else if(res == 0){
            //获取原材料编号
            QString MaterialNoSQL = QString("select ID from MaterialSetting where Material='%1';").arg(combo3->currentText());
            QString materialNo = db.sql_fetchrow_plus(MaterialNoSQL.toStdString().data(),0);
            //临时库存更新SQL语句
            QString kucunTmpSQL = QString("update InventoryQueryTmp set DepartmentName='%1',PositionName='%2',Unit='%3',\
                                          Material='%4',Factory='%5',Time='%6',MaterialNumber='%7' where PositionNumber='%8';")
                                .arg(combo1->currentText(),lineEdit2->text(),combo2->currentText(),combo3->currentText(),
                                     combo4->currentText(),date.currentDate().toString("yyyy-MM-dd"),materialNo,lineEdit1->text());
            db.sql_exec(kucunTmpSQL.toStdString().data());
            sockClient->send_Msg3();//发送刷新消息
            on_newAction();
            QMessageBox::information(this,tr("提示信息"),tr("修改成功"),0,0,0);
        }
//    }else{
//        QMessageBox::information(this,tr("提示信息"),tr("仓位内已有原料，不能修改"),0,0,0);
//        return;
//    }
}

void cangweishezhiDlg::on_deleteAction()
{
    QString panduanSQL = QString("select Quantity from InventoryQueryTmp where PositionNumber='%1';").arg(lineEdit1->text());
    double SurplusNum = db.sql_fetchrow_plus(panduanSQL.toStdString().data(),0).toDouble();
    if(SurplusNum <= 0){
        QString deleteSQL = QString("delete from PositionSetting where ID='%1';").arg(lineEdit1->text());
        int res = db.sql_exec(deleteSQL.toStdString().data());
        if(res == 0){
            QString deleteSQL = QString("delete from InventoryQueryTmp where PositionNumber='%1';").arg(lineEdit1->text());
            db.sql_exec(deleteSQL.toStdString().data());
            sockClient->send_Msg3();//发送刷新消息
            on_newAction();
            QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
        }
    }else{
        QMessageBox::information(this,tr("提示信息"),tr("仓位内已有原料，不能删除"),0,0,0);
        return;
    }
}

void cangweishezhiDlg::ShowSupplyclick()
{
    lineEdit1->setEnabled(false);
    updateAction->setEnabled(true);
    deleteAction->setEnabled(true);
    saveAction->setEnabled(false);

    int row = view->currentIndex().row();
    lineEdit1->setText(model->item(row,0)->text());
    lineEdit2->setText(model->item(row,1)->text());
    lineEdit3->setText(model->item(row,2)->text());
    combo1->setCurrentText(model->item(row,3)->text());
    combo2->setCurrentText(model->item(row,4)->text());
    combo3->setCurrentText(model->item(row,5)->text());
    combo4->setCurrentText(model->item(row,6)->text());

//    QString panduanSQL = QString("select Quantity from InventoryQueryTmp where PositionNumber='%1';").arg(lineEdit1->text());
//    double SurplusNum = db.sql_fetchrow_plus(panduanSQL.toStdString().data(),0).toDouble();
//    if(SurplusNum > 0){
//        combo3->setEnabled(false);
//        combo3->setStyleSheet("color:black");
//    }else{
//        combo3->setEnabled(true);
//    }
}

void cangweishezhiDlg::createAction()
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

void cangweishezhiDlg::createTool()
{
    toolBar = new QToolBar(this);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar->addAction(newAction);
    toolBar->addAction(saveAction);
    toolBar->addAction(updateAction);
    toolBar->addAction(deleteAction);
}
