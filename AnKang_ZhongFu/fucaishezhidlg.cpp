#include "fucaishezhidlg.h"
#include <QDebug>

extern mymysql db;
extern QString userName;
extern myTCPsocket *sockClient;

fucaishezhiDlg::fucaishezhiDlg(QWidget *parent) :
    QDialog(parent)
{
    tabWidget = new QTabWidget;
    tianjiafucai = new QWidget;
    fucaileibieshezhi  = new QWidget;

    creatTabPage1();
    creatTabPage2();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tabWidget);
}

void fucaishezhiDlg::refresh()
{
    on_chaxun();
    db.show_treeview(SQL2,twoview,&twomodel);
    twocombox1->clear();
    const char *fillSQL = "select Class from AuxiliaryCategory;";
    db.sql_fillComboBoxItem(fillSQL,twocombox1);
}

void fucaishezhiDlg::keyPressEvent(QKeyEvent *event)
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

void fucaishezhiDlg::creatTabPage1()
{
    createAction();
    createTool();

    SQL1 = "select AuxiliaryNumber 辅材编号,MaterialName 辅材名称,MaterialSpecifications 辅材规格,\
            Company 单位,Operator 操作人,GenericClass 所属类别,SubordinateClass 所属小类,\
            Remarks  备注,MinimumInventory 最低库存 from AuxiliaryMaterialSetting";

    QLabel *label1 = new QLabel(tr("辅材编号"),this);
    label1->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label2 = new QLabel(tr("辅材名称"),this);
    label2->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label3 = new QLabel(tr("辅材规格"),this);
    label3->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label4 = new QLabel(tr("最低库存"),this);
    label4->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label5 = new QLabel(tr("单位"),this);
    label5->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label6 = new QLabel(tr("类别"),this);
    label6->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label7 = new QLabel(tr("小类"),this);
    label7->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label8 = new QLabel(tr("备注"),this);
    label8->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    lineEdit1 = new QLineEdit(this);
    lineEdit2 = new QLineEdit(this);
    lineEdit3 = new QLineEdit(this);
    lineEdit4 = new QLineEdit(this);
    lineEdit5 = new QLineEdit(this);
    lineEdit6 = new QLineEdit(this);
    lineEdit7 = new QLineEdit(this);
    lineEdit8 = new QLineEdit(this);

    checkBox1 = new QCheckBox(tr("类别"),this);
    checkBox2 = new QCheckBox(tr("辅材名称"),this);
    checkBox3 = new QCheckBox(tr("辅材编号"),this);

    combox1 = new QComboBox(this);
    const char *fillSQL1 = "select Class from AuxiliaryCategory";
    db.sql_fillComboBoxItem(fillSQL1,combox1);
    connect(combox1,SIGNAL(currentTextChanged(QString)),this,SLOT(fillComBox2()));

    combox2 = new QComboBox(this);

    combox3 = new QComboBox(this);
    const char *fillSQL2 = "select Class from AuxiliaryCategory";
    db.sql_fillComboBoxItem(fillSQL2,combox3);

    view = new QTableView(this);
    connect(view,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick()));
    db.showview(SQL1,view,&model);

    chaxun = new QPushButton(tr("查询"),this);
    connect(chaxun,SIGNAL(clicked()),this,SLOT(on_chaxun()));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label1,0,0);
    layout->addWidget(lineEdit1,0,1);
    layout->addWidget(label2,0,2);
    layout->addWidget(lineEdit2,0,3);
    layout->addWidget(label3,0,4);
    layout->addWidget(lineEdit3,0,5);
    layout->addWidget(label4,0,6);
    layout->addWidget(lineEdit4,0,7);
    layout->addWidget(label5,1,0);
    layout->addWidget(lineEdit5,1,1);
    layout->addWidget(label6,1,2);
    layout->addWidget(combox1,1,3);
    layout->addWidget(label7,1,4);
    layout->addWidget(combox2,1,5);
    layout->addWidget(label8,2,0);
    layout->addWidget(lineEdit6,2,1,1,5);
    layout->setColumnStretch(0,0);
    layout->setColumnStretch(1,1);
    layout->setColumnStretch(2,0);
    layout->setColumnStretch(3,1);
    layout->setColumnStretch(4,0);
    layout->setColumnStretch(5,1);
    layout->setColumnStretch(6,0);
    layout->setColumnStretch(7,1);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(checkBox1,0);
    hlayout->addWidget(combox3,1);
    hlayout->addWidget(checkBox2,0);
    hlayout->addWidget(lineEdit7,1);
    hlayout->addWidget(checkBox3,0);
    hlayout->addWidget(lineEdit8,1);
    hlayout->addWidget(chaxun,1);
    hlayout->addSpacing(100);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(toolBar);
    vlayout->addLayout(layout);
    vlayout->addSpacing(20);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(view);

    tianjiafucai->setLayout(vlayout);
//    tabWidget->addTab(tianjiafucai,tr("添加辅材"));
}

void fucaishezhiDlg::creatTabPage2()
{
    createAction2();
    createTool2();

    SQL2 = "select * from AuxiliaryCategory;";

    QLabel *label1 = new QLabel(tr("类别名称"),this);
    label1->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    label2 = new QLabel(tr("所属父类"),this);
    label2->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    twolineEdit1 = new QLineEdit(this);

    twocombox1 = new QComboBox(this);
    const char *fillSQL = "select Class from AuxiliaryCategory;";
    db.sql_fillComboBoxItem(fillSQL,twocombox1);

    tworadioBtn1 = new QRadioButton(tr("大类"),this);
    tworadioBtn2 = new QRadioButton(tr("小类"),this);

    twoBtnGroup = new QButtonGroup(this);
    twoBtnGroup->addButton(tworadioBtn1,1);
    twoBtnGroup->addButton(tworadioBtn2,2);
    tworadioBtn1->setChecked(true);
    connect(twoBtnGroup,SIGNAL(buttonClicked(int)),this,SLOT(on_layout_change()));

    twoview = new QTreeView(this);
    db.show_treeview(SQL2,twoview,&twomodel);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(tworadioBtn1);
    hlayout->addSpacing(40);
    hlayout->addWidget(tworadioBtn2);
    hlayout->setMargin(0);

    layout = new QGridLayout;
    layout->addWidget(label1,0,0);
    layout->addWidget(twolineEdit1,0,1);
    layout->addWidget(twoview,0,2,6,1);
    layout->addLayout(hlayout,1,0,1,2,Qt::AlignHCenter);
    layout->addWidget(label2,2,0);
    layout->addWidget(twocombox1,2,1);
    label2->setHidden(true);
    twocombox1->setHidden(true);

    layout->setColumnStretch(0,0);
    layout->setColumnStretch(1,1);
    layout->setColumnStretch(2,3);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(toolBar2);
    vlayout->addLayout(layout);

    fucaileibieshezhi->setLayout(vlayout);
    tabWidget->addTab(fucaileibieshezhi,tr("辅材类别设置"));
}

void fucaishezhiDlg::on_newAction()
{
    lineEdit1->setEnabled(true);
    saveAction->setEnabled(true);
    updateAction->setEnabled(false);
    deleteAction->setEnabled(false);

    lineEdit1->clear();
    lineEdit1->setFocus();
    lineEdit2->clear();
    lineEdit3->clear();
    lineEdit4->clear();
    lineEdit5->clear();
    lineEdit6->clear();
    const char *fillSQL = "select Class from AuxiliaryCategory";
    disconnect(combox1,SIGNAL(currentTextChanged(QString)),this,SLOT(fillComBox2()));
    combox1->clear();
    db.sql_fillComboBoxItem(fillSQL,combox1);
    connect(combox1,SIGNAL(currentTextChanged(QString)),this,SLOT(fillComBox2()));
    combox3->clear();
    db.sql_fillComboBoxItem(fillSQL,combox3);
    combox2->setCurrentIndex(0);
}

void fucaishezhiDlg::on_saveAction()
{
    if(lineEdit1->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入辅材编号"),0,0,0);
        return;
    }
    if(lineEdit2->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入辅材名称"),0,0,0);
        return;
    }
    if(lineEdit5->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入辅材单位"),0,0,0);
        return;
    }
    if(combox1->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择类别"),0,0,0);
        return;
    }
    if(combox2->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择小类"),0,0,0);
        return;
    }
    QString saveSQL = QString("insert into AuxiliaryMaterialSetting (AuxiliaryNumber,MaterialName,\
                              MaterialSpecifications,Company,Operator,GenericClass,SubordinateClass,\
                              Remarks,MinimumInventory) values ('%1','%2','%3','%4','%5','%6','%7','%8','%9');")
            .arg(lineEdit1->text(),lineEdit2->text(),lineEdit3->text(),lineEdit5->text(),userName,
                 combox1->currentText(),combox2->currentText(),lineEdit6->text(),lineEdit4->text());

    int res = db.sql_exec(saveSQL.toStdString().data());
    if(res == -1){
        if((strstr(db.geterror(),"PRIMARY")) != NULL)
        {
            QMessageBox::information(this,tr("错误"),tr("请检查辅材编号是否重复"),0,0,0);
            return;
        }
    }
    else if(res == 0){
        sockClient->send_Msg3();
        on_newAction();
        QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
    }
}

void fucaishezhiDlg::on_updateAction()
{
    if(lineEdit2->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入辅材名称"),0,0,0);
        return;
    }
    if(lineEdit5->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入辅材单位"),0,0,0);
        return;
    }
    if(combox1->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择类别"),0,0,0);
        return;
    }
    if(combox2->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择小类"),0,0,0);
        return;
    }

    QString updateSQL = QString("update AuxiliaryMaterialSetting set MaterialName ='%1',MaterialSpecifications ='%2',Company ='%3',\
                              Operator ='%4',GenericClass ='%5',SubordinateClass ='%6',Remarks ='%7',MinimumInventory='%8' where AuxiliaryNumber ='%9';")
                    .arg(lineEdit2->text(),lineEdit3->text(),lineEdit5->text(),userName,combox1->currentText(),combox2->currentText(),lineEdit6->text(),lineEdit4->text(),lineEdit1->text());
    int res = db.sql_exec(updateSQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();
        on_newAction();
        QMessageBox::information(this,tr("提示信息"),tr("修改成功"),0,0,0);
    }
}

void fucaishezhiDlg::on_deleteAction()
{
    QString deleteSQL = QString("delete from AuxiliaryMaterialSetting where AuxiliaryNumber ='%1';").arg(lineEdit1->text());
    int res = db.sql_exec(deleteSQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();
        on_newAction();
        QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
    }
}

void fucaishezhiDlg::ShowSupplyclick()
{
    updateAction->setEnabled(true);
    deleteAction->setEnabled(true);
    saveAction->setEnabled(false);
    lineEdit1->setEnabled(false);

    int row = view->currentIndex().row();
    lineEdit1->setText(model->item(row,0)->text());
    lineEdit2->setText(model->item(row,1)->text());
    lineEdit3->setText(model->item(row,2)->text());
    lineEdit4->setText(model->item(row,8)->text());
    lineEdit5->setText(model->item(row,3)->text());
    lineEdit6->setText(model->item(row,7)->text());
    combox1->setCurrentText(model->item(row,5)->text());
    combox2->setCurrentText(model->item(row,6)->text());
}

void fucaishezhiDlg::on_saveAction2()
{
    if(twolineEdit1->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入类别名称"),0,0);
        return;
    }
    if(twoBtnGroup->checkedId() == 1){
        QString saveSQL = QString("insert into AuxiliaryCategory (Class) values ('%1');").arg(twolineEdit1->text());
        int res = db.sql_exec(saveSQL.toStdString().data());
        if(res == -1){
            if((strstr(db.geterror(),"PRIMARY")) != NULL){
                QMessageBox::information(this,tr("错误"),tr("请检查类别名称是否重复"),0,0,0);
                return;
            }
        }
    }

    if(twoBtnGroup->checkedId() ==2){
        if(twocombox1->currentText().isEmpty()){
            QMessageBox::information(this,tr("错误"),tr("请选择所属大类"),0,0,0);
            return;
        }
        int num =twomodel->rowCount();//大类数量
        for(int i = 0;i < num; i++){
            if(twomodel->item(i,0)->text() == twocombox1->currentText()){
                num = i;
                break;
            }
        }
        int count = twomodel->rowCount(twomodel->index(num,0));//小类数量
        for(int i = 0;i < count;i++){
            if(twomodel->item(num,0)->child(i,0)->text() == twolineEdit1->text()){
                QMessageBox::information(this,tr("错误"),tr("请检查类别名称是否重复"),0,0,0);
                return;
            }
        }
        QString updateSQL = QString("update AuxiliaryCategory set Class%1='%2' where Class='%3';").arg(count+1).arg(twolineEdit1->text(),twocombox1->currentText());
        db.sql_exec(updateSQL.toStdString().data());
    }
    sockClient->send_Msg3();
    on_newAction();
    twolineEdit1->clear();
    QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
}

void fucaishezhiDlg::on_deleteAction2()
{
    QModelIndex myindex = twoview->currentIndex();
    if(myindex.parent().row() == -1){
        QString deleteSQL = QString("delete from AuxiliaryCategory where Class='%1';").arg(myindex.data().toString());
        int res = db.sql_exec(deleteSQL.toStdString().data());
        if(res == 0){
            sockClient->send_Msg3();
            QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
        }
    }
    else{
        int count = myindex.row();
        QString deleteSQL = QString("update AuxiliaryCategory set Class%1='' where Class='%2';").arg(count+1).arg(myindex.parent().data().toString());
        int res = db.sql_exec(deleteSQL.toStdString().data());
        if(res == 0){
            sockClient->send_Msg3();
            QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
        }
    }
}

void fucaishezhiDlg::createAction()
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
    //deleteAction->setEnabled(false);
    deleteAction->setIcon(QIcon(":/image/delete.png"));
    connect(deleteAction,SIGNAL(triggered()),this,SLOT(on_deleteAction()));
}

void fucaishezhiDlg::createTool()
{
    toolBar = new QToolBar(this);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar->addAction(newAction);
    toolBar->addAction(saveAction);
    toolBar->addAction(updateAction);
    toolBar->addAction(deleteAction);
}

void fucaishezhiDlg::createAction2()
{
    saveAction2 = new QAction(tr("保存"),this);
    saveAction2->setIcon(QIcon(":/image/save.png"));
    connect(saveAction2,SIGNAL(triggered()),this,SLOT(on_saveAction2()));
    deleteAction2 = new QAction(tr("删除"),this);
    deleteAction2->setIcon(QIcon(":/image/delete.png"));
    connect(deleteAction2,SIGNAL(triggered()),this,SLOT(on_deleteAction2()));
}

void fucaishezhiDlg::createTool2()
{
    toolBar2 = new QToolBar(this);
    toolBar2->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar2->addAction(saveAction2);
    toolBar2->addAction(deleteAction2);
}

void fucaishezhiDlg::on_layout_change()
{
    if(twoBtnGroup->checkedId() == 2){
        label2->setHidden(false);
        twocombox1->setHidden(false);
    }
    if(twoBtnGroup->checkedId() == 1){
        label2->setHidden(true);
        twocombox1->setHidden(true);
    }
}

void fucaishezhiDlg::fillComBox2()
{
    QString fillSQL2 = QString("select * from AuxiliaryCategory where Class='%1';").arg(combox1->currentText());
    combox2->clear();
    db.sql_fillComboBoxItem2(fillSQL2.toStdString().data(),combox2);
}

void fucaishezhiDlg::on_chaxun()
{
    QString str1,str2,str3;
    if(checkBox1->checkState() == 2){
        str1 = QString(" and GenericClass='%1'").arg(combox3->currentText());
    }
    if(checkBox2->checkState() == 2){
        str2 = QString(" and MaterialName='%1'").arg(lineEdit7->text());
    }
    if(checkBox3->checkState() == 2){
        str3 = QString(" and AuxiliaryNumber='%1'").arg(lineEdit8->text());
    }

    QString searchSQL = QString("select AuxiliaryNumber 辅材编号,MaterialName 辅材名称,MaterialSpecifications 辅材规格,Company 单位,Operator 操作人,GenericClass 所属类别,SubordinateClass 所属小类,Remarks 备注,MinimumInventory 最低库存 \
                                from AuxiliaryMaterialSetting where bak is null%1%2%3;").arg(str1,str2,str3);
    db.showview(searchSQL.toStdString().data(),view,&model);
}
