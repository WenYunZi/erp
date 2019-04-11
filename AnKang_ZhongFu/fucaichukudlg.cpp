#include "fucaichukudlg.h"

extern mymysql db;
extern pubfunc pub;
extern QString userName;
extern myTCPsocket *sockClient;

fucaichukuDlg::fucaichukuDlg(QWidget *parent) :
    QDialog(parent)
{
    tabWidget = new QTabWidget(this);
    fucaichuku = new QWidget(this);
    chukuchaxun  = new QWidget(this);

    creatTabPage1();
    creatTabPage2();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tabWidget);
}

void fucaichukuDlg::refresh()
{
    on_twochaxunBtn();
}

void fucaichukuDlg::keyPressEvent(QKeyEvent *event)
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

void fucaichukuDlg::creatTabPage1()
{
    createAction();
    createTool();

    QLabel *label1 = new QLabel(tr("出库单号"),this);
    label1->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label2 = new QLabel(tr("出库日期"),this);
    label2->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label3 = new QLabel(tr("录入人员"),this);
    label3->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label4 = new QLabel(tr("领用部门"),this);
    label4->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label5 = new QLabel(tr("领用人员"),this);
    label5->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label6 = new QLabel(tr("领用类型"),this);
    label6->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label7 = new QLabel(tr("车牌/设备"),this);
    label7->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label8 = new QLabel(tr("备注"),this);
    label8->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label9 = new QLabel(tr("总金额"),this);
    label9->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    lineEdit1 = new QLineEdit(this);
    lineEdit1->setReadOnly(true);
    lineEdit1->setStyleSheet("color:black");
    lineEdit2 = new QLineEdit(userName,this);
    lineEdit2->setReadOnly(true);
    lineEdit3 = new QLineEdit(this);
    lineEdit3->setReadOnly(true);
    lineEdit4 = new QLineEdit(this);
    datetimeEdit = new QDateTimeEdit(QDateTime::currentDateTime(),this);
    datetimeEdit->setCalendarPopup(true);

    comBox1 = new QComboBox(this);
    const char *fillcomBox1SQL = "select DepartmentName from SectorSettings group by DepartmentName;";
    db.sql_fillComboBoxItem(fillcomBox1SQL,comBox1);

    comBox2 = new QComboBox(this);
    comBox2->setView(new QListView(this));
    comBox2->addItem(tr(""));
    comBox2->addItem(tr("砼车"));
    comBox2->addItem(tr("设备"));
    comBox2->addItem(tr("泵车"));
    comBox2->addItem(tr("办公/劳保"));

    comBox3 = new QComboBox(this);
    comBox3->setView(new QListView(this));
    comBox3->addItem(tr(""));
    comBox3->addItem(tr("自用"));
    comBox3->addItem(tr("非自用"));

    comBox4 = new QComboBox(this);
    comBox4->setEditable(true);

    //设置表头
    QStringList header;
    header.append(QObject::tr("辅材编号"));
    header.append(QObject::tr("辅材名称"));
    header.append(QObject::tr("所属大类"));
    header.append(QObject::tr("所属小类"));
    header.append(QObject::tr("规格"));
    header.append(QObject::tr("单位"));
    header.append(QObject::tr("数量"));
    header.append(QObject::tr("单价"));
    header.append(QObject::tr("金额"));

    view = new QTableWidget(this);
    view->setColumnCount(9);
    view->setRowCount(0);
    view->setItemDelegate(new fucaichukuDelegate(1));
    view->setHorizontalHeaderLabels(header);

    //设置view1的右键菜单
    zengjiaAction = new QAction(tr("增加"),this);
    zengjiaAction->setIcon(QIcon(":/image/zengjia.png"));
    shanchuAction = new QAction(tr("删除"),this);
    shanchuAction->setIcon(QIcon(":/image/shanchu.png"));
    connect(zengjiaAction,SIGNAL(triggered()),this,SLOT(Increasing()));
    connect(shanchuAction,SIGNAL(triggered()),this,SLOT(Decreasing()));
    view->addAction(zengjiaAction);
    view->addAction(shanchuAction);
    view->setContextMenuPolicy(Qt::ActionsContextMenu);
    connect(view,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(on_CalculateTotalAmount()));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label1,0,0);
    layout->addWidget(lineEdit1,0,1);
    layout->addWidget(label2,0,2);
    layout->addWidget(datetimeEdit,0,3);
    layout->addWidget(label3,0,4);
    layout->addWidget(lineEdit2,0,5);
    layout->addWidget(label4,0,6);
    layout->addWidget(comBox1,0,7);
    layout->addWidget(label6,1,0);
    layout->addWidget(comBox2,1,1);
    layout->addWidget(label7,1,2);
    layout->addWidget(comBox3,1,3);
    layout->addWidget(label9,1,4);
    layout->addWidget(lineEdit3,1,5);
    layout->addWidget(label5,1,6);
    layout->addWidget(comBox4,1,7);
    layout->addWidget(label8,2,0);
    layout->addWidget(lineEdit4,2,1,1,5);
    layout->setColumnStretch(0,0);
    layout->setColumnStretch(1,1);
    layout->setColumnStretch(2,0);
    layout->setColumnStretch(3,1);
    layout->setColumnStretch(4,0);
    layout->setColumnStretch(5,1);
    layout->setColumnStretch(6,0);
    layout->setColumnStretch(7,1);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(toolBar);
    vlayout->addLayout(layout);
    vlayout->addWidget(view);

    fucaichuku->setLayout(vlayout);
    tabWidget->addTab(fucaichuku,tr("辅材出库"));
}

void fucaichukuDlg::creatTabPage2()
{
    SQL2 = "select WarehouseNumber  出库单号,Outdate  出库日期,EntryPersonnel  录入人员,\
            CollarDepartment  领用部门,CollarPerson 领用人员,type  类型,LicensePlateEquipment  车牌设备,\
            TotalAmount  总金额,Remarks  备注,AuxiliaryNumber  辅材编号,MaterialName  辅材名称,\
            GenericClass 所属大类,SubordinateClass  所属小类,Specifications  规格,Company  单位,\
            Number  数量,round(UnitPrice,2)  单价,AmountMoney  金额,WhetherAudit 是否审核 \
            from AuxiliaryOutput where WarehouseNumber is null;";

    QLabel *label1 = new QLabel(tr("出库日期"),this);
    label1->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label2 = new QLabel(tr("--"),this);
    label2->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    twodateEdit1 = new QDateEdit(QDate::currentDate(),this);
    twodateEdit1->setCalendarPopup(true);
    twodateEdit2 = new QDateEdit(QDate::currentDate(),this);
    twodateEdit2->setCalendarPopup(true);
    twocomBox1 = new QComboBox(this);
    twocomBox1->setHidden(true);
    twocomBox2 = new QComboBox(this);
    const char *fillcomBox2SQL = "select DepartmentName from SectorSettings group by DepartmentName;";
    db.sql_fillComboBoxItem(fillcomBox2SQL,twocomBox2);
    twocheckBox1 = new QCheckBox(tr("类别"),this);
    twocheckBox1->setHidden(true);
    twocheckBox2 = new QCheckBox(tr("领用部门"),this);
    twochaxun = new QPushButton(tr("查询"),this);
    connect(twochaxun,SIGNAL(clicked()),this,SLOT(on_twochaxunBtn()));

    twoview = new QTableView(this);
    db.showview(SQL2,twoview,&twomodel);
    connect(twoview,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick()));
    twoview->setColumnWidth(1,130);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(label1,0);
    hlayout->addWidget(twodateEdit1,1);
    hlayout->addWidget(label2,0);
    hlayout->addWidget(twodateEdit2,1);
    hlayout->addWidget(twocheckBox1,0);
    hlayout->addWidget(twocomBox1,1);
    hlayout->addWidget(twocheckBox2,0);
    hlayout->addWidget(twocomBox2,1);
    hlayout->addWidget(twochaxun,1);
    hlayout->addStretch(4);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(twoview);

    chukuchaxun->setLayout(vlayout);
    tabWidget->addTab(chukuchaxun,tr("出库查询"));
}

void fucaichukuDlg::createAction()
{
    newAction = new QAction(tr("新增"),this);
    newAction->setIcon(QIcon(":/image/new.png"));
    connect(newAction,SIGNAL(triggered()),this,SLOT(on_newAction_plus()));
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
    checkAction = new QAction(tr("审核"),this);
    checkAction->setEnabled(false);
    checkAction->setIcon(QIcon(":/image/check.png"));
    connect(checkAction,SIGNAL(triggered()),this,SLOT(on_checkAction()));
}

void fucaichukuDlg::createTool()
{
    toolBar = new QToolBar(this);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar->addAction(newAction);
    toolBar->addAction(saveAction);
    toolBar->addAction(updateAction);
    toolBar->addAction(deleteAction);
    toolBar->addAction(checkAction);
}

void fucaichukuDlg::on_newAction()
{
    saveAction->setEnabled(true);
    updateAction->setEnabled(false);
    deleteAction->setEnabled(false);
    checkAction->setEnabled(false);

    lineEdit1->clear();
    lineEdit3->clear();
    lineEdit4->clear();
    comBox1->setCurrentIndex(0);
    comBox2->setCurrentIndex(0);
    comBox3->setCurrentIndex(0);
    view->setRowCount(0);
}

void fucaichukuDlg::on_newAction_plus()
{
    saveAction->setEnabled(true);
    updateAction->setEnabled(false);
    deleteAction->setEnabled(false);
    checkAction->setEnabled(false);

    lineEdit1->setText(pub.newAuxiliaryOutputNo());
    lineEdit3->clear();
    lineEdit4->clear();
    comBox1->setCurrentIndex(0);
    comBox2->setCurrentIndex(0);
    comBox3->setCurrentIndex(0);
    view->setRowCount(0);
}

void fucaichukuDlg::on_saveAction()
{
    if(lineEdit1->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请新增出库单号"),0,0,0);
        return;
    }
    if(comBox1->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择领用部门"),0,0,0);
        return;
    }
    if(comBox4->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入领用人员"),0,0,0);
        return;
    }
    if(comBox2->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择领用类型"),0,0,0);
        return;
    }
    QString str1,str2,str3,str4,str5,str6,str7,str8,str9,str10;
    int rowcount = view->rowCount();
    for(int i = 0; i < rowcount; i++){
/*辅材编号****************************************************************************************/
        if(!view->item(i,0) || view->item(i,0)->text().isEmpty()){
            QMessageBox::information(this,tr("提示信息"),tr("请检查辅材编号是否有空行"),0,0,0);
            return;
        }else{
            str1.append(view->item(i,0)->text() + " ");
        }
/*辅材名称****************************************************************************************/
        if(!view->item(i,1) || view->item(i,1)->text().isEmpty()){
            QMessageBox::information(this,tr("提示信息"),tr("请检查辅材是否有空行"),0,0,0);
            return;
        }else{
            str2.append(view->item(i,1)->text() + " ");
        }
/*所属大类****************************************************************************************/
        if(!view->item(i,2) || view->item(i,2)->text().isEmpty()){
            str3.append(" ");
        }else{
            str3.append(view->item(i,2)->text() + " ");
        }
/*所属小类****************************************************************************************/
        if(!view->item(i,3) || view->item(i,3)->text().isEmpty()){
            str4.append(" ");
        }else{
            str4.append(view->item(i,3)->text() + " ");
        }
/*规格****************************************************************************************/
        if(!view->item(i,4) || view->item(i,4)->text().isEmpty()){
            str5.append(" ");
        }else{
            str5.append(view->item(i,4)->text() + " ");
        }

/*辅材单位****************************************************************************************/
        if(!view->item(i,5) || view->item(i,5)->text().isEmpty()){
            QMessageBox::information(this,tr("提示信息"),tr("请输入辅材单位"),0,0,0);
            return;
        }else{
            str6.append(view->item(i,5)->text() + " ");
        }
/*辅材数量****************************************************************************************/
        if(!view->item(i,6) || view->item(i,6)->text().isEmpty()){
            QMessageBox::information(this,tr("提示信息"),tr("请添加辅材数量"),0,0,0);
            return;
        }else{
            str7.append(view->item(i,6)->text() + " ");
        }
/*辅材单价****************************************************************************************/
        if(!view->item(i,7) || view->item(i,7)->text().isEmpty()){
            QMessageBox::information(this,tr("提示信息"),tr("请输入辅材单价"),0,0,0);
            return;
        }else{
            str8.append(view->item(i,7)->text() + " ");
        }
/*辅材金额****************************************************************************************/
        if(!view->item(i,8) || view->item(i,8)->text().isEmpty()){
            str9.append(" ");
        }else{
            str9.append(view->item(i,8)->text() + " ");
        }
    }
    if(str1.isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请添加辅材"),0,0,0);
        return;
    }

    QString saveSQL = QString("insert into AuxiliaryOutput (WarehouseNumber,Outdate,\
                              EntryPersonnel,CollarDepartment,CollarPerson,type,LicensePlateEquipment,\
                              TotalAmount,Remarks,AuxiliaryNumber,MaterialName,GenericClass,\
                              SubordinateClass,Specifications,Company,Number,UnitPrice,AmountMoney,\
                              WhetherAudit) values ('%1','%2','%3','%4','%5','%6',\
                            '%7','%8','%9','%10','%11','%12','%13','%14','%15','%16','%17','%18','否');")
                        .arg(lineEdit1->text(),datetimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"),lineEdit2->text(),
                             comBox1->currentText(),comBox4->currentText(),comBox2->currentText(),comBox3->currentText(),lineEdit3->text(),
                             lineEdit4->text())
                        .arg(str1,str2,str3,str4,str5,str6,str7,str8,str9);
    int res = db.sql_exec(saveSQL.toStdString().data());
    qDebug()<<db.geterror()<<saveSQL;
    if(res == -1){
        if((strstr(db.geterror(),"PRIMARY")) != NULL)
        {
            QMessageBox::information(this,tr("错误"),tr("请检查出库单号是否重复"),0,0,0);
            return;
        }
    }
    else if(res == 0){
        sockClient->send_Msg3();
        on_newAction();
        lineEdit1->clear();
        QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
    }
}

void fucaichukuDlg::on_updateAction()
{
    if(comBox1->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择领用部门"),0,0,0);
        return;
    }
    if(comBox4->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入领用人员"),0,0,0);
        return;
    }
    if(comBox2->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择领用类型"),0,0,0);
        return;
    }
    QString str1,str2,str3,str4,str5,str6,str7,str8,str9,str10;
    int rowcount = view->rowCount();
    for(int i = 0; i < rowcount; i++){
/*辅材编号****************************************************************************************/
        if(!view->item(i,0) || view->item(i,0)->text().isEmpty()){
            QMessageBox::information(this,tr("提示信息"),tr("请检查辅材编号是否有空行"),0,0,0);
            return;
        }else{
            str1.append(view->item(i,0)->text() + " ");
        }
/*辅材名称****************************************************************************************/
        if(!view->item(i,1) || view->item(i,1)->text().isEmpty()){
            QMessageBox::information(this,tr("提示信息"),tr("请检查辅材是否有空行"),0,0,0);
            return;
        }else{
            str2.append(view->item(i,1)->text() + " ");
        }
/*所属大类****************************************************************************************/
        if(!view->item(i,2) || view->item(i,2)->text().isEmpty()){
            str3.append(" ");
        }else{
            str3.append(view->item(i,2)->text() + " ");
        }
/*所属小类****************************************************************************************/
        if(!view->item(i,3) || view->item(i,3)->text().isEmpty()){
            str4.append(" ");
        }else{
            str4.append(view->item(i,3)->text() + " ");
        }
/*规格****************************************************************************************/
        if(!view->item(i,4) || view->item(i,4)->text().isEmpty()){
            str5.append(" ");
        }else{
            str5.append(view->item(i,4)->text() + " ");
        }

/*辅材单位****************************************************************************************/
        if(!view->item(i,5) || view->item(i,5)->text().isEmpty()){
            QMessageBox::information(this,tr("提示信息"),tr("请输入辅材单位"),0,0,0);
            return;
        }else{
            str6.append(view->item(i,5)->text() + " ");
        }
/*辅材数量****************************************************************************************/
        if(!view->item(i,6) || view->item(i,6)->text().isEmpty()){
            QMessageBox::information(this,tr("提示信息"),tr("请添加辅材数量"),0,0,0);
            return;
        }else{
            str7.append(view->item(i,6)->text() + " ");
        }
/*辅材单价****************************************************************************************/
        if(!view->item(i,7) || view->item(i,7)->text().isEmpty()){
            QMessageBox::information(this,tr("提示信息"),tr("请输入辅材单价"),0,0,0);
            return;
        }else{
            str8.append(view->item(i,7)->text() + " ");
        }
/*辅材金额****************************************************************************************/
        if(!view->item(i,8) || view->item(i,8)->text().isEmpty()){
            str9.append(" ");
        }else{
            str9.append(view->item(i,8)->text() + " ");
        }
    }
    if(str1.isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请添加辅材"),0,0,0);
        return;
    }

    QString updateSQL = QString("update AuxiliaryOutput set Outdate='%1',EntryPersonnel='%2',CollarDepartment='%3',\
                              CollarPerson='%4',type='%5',LicensePlateEquipment='%6',TotalAmount='%7',Remarks='%8',\
                              AuxiliaryNumber='%9',MaterialName='%10',GenericClass='%11',SubordinateClass='%12',\
                              Specifications='%13',Company='%14',Number='%15',UnitPrice='%16',AmountMoney='%17' where WarehouseNumber='%18'")
                        .arg(datetimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"),lineEdit2->text(),
                             comBox1->currentText(),comBox4->currentText(),comBox2->currentText(),comBox3->currentText(),lineEdit3->text(),
                             lineEdit4->text(),str1)
                        .arg(str2,str3,str4,str5,str6,str7,str8,str9,lineEdit1->text());
    int res = db.sql_exec(updateSQL.toStdString().data());
    qDebug()<<db.geterror()<<updateSQL;
    if(res == 0){
        sockClient->send_Msg3();
        on_newAction();
        lineEdit1->clear();
        QMessageBox::information(this,tr("提示信息"),tr("修改成功"),0,0,0);
    }
}

void fucaichukuDlg::on_deleteAction()
{
    QString deleteSQL = QString("delete from AuxiliaryOutput where WarehouseNumber ='%1';").arg(lineEdit1->text());
    int res = db.sql_exec(deleteSQL.toStdString().data());
    qDebug()<<db.geterror()<<deleteSQL;
    if(res == 0){
        sockClient->send_Msg3();
        on_newAction();
        lineEdit1->clear();
        QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
    }
}

void fucaichukuDlg::on_checkAction()
{
    QString searchSQL = QString("select WhetherAudit from AuxiliaryOutput where WarehouseNumber='%1'").arg(lineEdit1->text());
    if(db.sql_fetchrow_plus(searchSQL.toStdString().data(),0) == "是"){
        QMessageBox::information(this,tr("提示信息"),tr("已审核的出库单不可再次审核"),0,0,0);
        return;
    }
    int count = view->rowCount();
    for(int i = 0; i < count; i++){
        QString searchAuxiliaryInventorySQL = QString("select Number from AuxiliaryInventory where AuxiliaryNumber='%1';").arg(view->item(i,0)->text());
        if(db.sql_fetchrow_plus(searchAuxiliaryInventorySQL.toStdString().data(),0).toDouble()<view->item(i,6)->text().toDouble()){
            QMessageBox::information(this,tr("提示信息"),view->item(i,1)->text().append("库存不足"),0,0,0);
            return;
        }
    }
    //事务开始
    db.sql_exec("begin");
    for(int i = 0; i < count; i++){
        //更新辅材库存
        QString updateSQL = QString("update AuxiliaryInventory set MaterialName ='%1',Specifications ='%2',\
                            Number =Number-'%3',Company ='%4',Price ='%5',AmountOfMoney=AmountOfMoney-'%6',\
                            GenericClass='%7',SubordinateClass='%8' where AuxiliaryNumber ='%9'")
                .arg(view->item(i,1)->text(),view->item(i,4)->text(),view->item(i,6)->text(),
                         view->item(i,5)->text(),view->item(i,7)->text(),view->item(i,8)->text(),
                         view->item(i,2)->text(),view->item(i,3)->text(),view->item(i,0)->text());
        int res = db.sql_exec(updateSQL.toStdString().data());
        if(res == -1){
            db.sql_exec("rollback");
            return;
        }
        //向辅材耗用统计表中插入相应的出库记录
        QString insertSQL = QString("insert into MaterialConsumptionStatistics (RecordNumber,AuxiliaryNumber,MaterialName,\
                                    Specifications,QuantitiesConsumed,Company,UnitPrice,amountOfConsumption,Outdate,DeviceType,\
                                    LicensePlateOrDeviceName,CollarMan,Reviewer,GenericClass,SubordinateClass) values ('%1',\
                                    '%2','%3','%4','%5','%6','%7','%8','%9','%10','%11','%12','%13','%14','%15');")
                        .arg(lineEdit1->text(),view->item(i,0)->text(),view->item(i,1)->text(),view->item(i,4)->text(),view->item(i,6)->text(),
                             view->item(i,5)->text(),view->item(i,7)->text(),view->item(i,8)->text(),datetimeEdit->dateTime().toString("yyyy-MM-dd hh:mm"))
                        .arg(comBox2->currentText(),comBox3->currentText(),comBox4->currentText(),userName,view->item(i,2)->text(),view->item(i,3)->text());
        res = db.sql_exec(insertSQL.toStdString().data());
        if(res == -1){
            db.sql_exec("rollback");
            return;
        }
    }
    //删除辅材库存表中的库存为0的辅材
    QString deleteSQL = QString("delete from AuxiliaryInventory where Number='0';");
    int res = db.sql_exec(deleteSQL.toStdString().data());
    if(res == -1){
        db.sql_exec("rollback");
        return;
    }
    QString updateSQL = QString("update AuxiliaryOutput set WhetherAudit='是' where WarehouseNumber='%1'").arg(lineEdit1->text());
    res = db.sql_exec(updateSQL.toStdString().data());
    if(res == -1){
        db.sql_exec("rollback");
        return;
    }
    //事务结束
    db.sql_exec("commit");

    sockClient->send_Msg3();
    on_newAction();
    lineEdit1->clear();
    QMessageBox::information(this,tr("提示信息"),tr("审核成功"),0,0,0);
}

void fucaichukuDlg::ShowSupplyclick()
{
    updateAction->setEnabled(true);
    deleteAction->setEnabled(true);
    checkAction->setEnabled(true);
    saveAction->setEnabled(false);
    lineEdit1->setEnabled(false);

    int row = twoview->currentIndex().row();
    lineEdit1->setText(twomodel->item(row,0)->text());
    lineEdit2->setText(twomodel->item(row,2)->text());
    lineEdit3->setText(twomodel->item(row,7)->text());
    lineEdit4->setText(twomodel->item(row,8)->text());
    datetimeEdit->setDateTime(QDateTime::fromString(twomodel->item(row,1)->text(),"yyyy-MM-dd hh:mm:ss"));
    comBox1->setCurrentText(twomodel->item(row,3)->text());
    comBox2->setCurrentText(twomodel->item(row,5)->text());
    comBox3->setCurrentText(twomodel->item(row,6)->text());
    comBox4->setCurrentText(twomodel->item(row,4)->text());

    int count = twomodel->item(row,9)->text().count(" ");//求出辅材个数
    view->setColumnCount(9);
    view->setRowCount(count);
    for(int i = 0; i < count; i++){
        view->setItem(i,0,new QTableWidgetItem(twomodel->item(row,9)->text().section(" ",i,i)));
        view->setItem(i,1,new QTableWidgetItem(twomodel->item(row,10)->text().section(" ",i,i)));
        view->setItem(i,2,new QTableWidgetItem(twomodel->item(row,11)->text().section(" ",i,i)));
        view->setItem(i,3,new QTableWidgetItem(twomodel->item(row,12)->text().section(" ",i,i)));
        view->setItem(i,4,new QTableWidgetItem(twomodel->item(row,13)->text().section(" ",i,i)));
        view->setItem(i,5,new QTableWidgetItem(twomodel->item(row,14)->text().section(" ",i,i)));
        view->setItem(i,6,new QTableWidgetItem(twomodel->item(row,15)->text().section(" ",i,i)));
        view->setItem(i,7,new QTableWidgetItem(twomodel->item(row,16)->text().section(" ",i,i)));
        view->setItem(i,8,new QTableWidgetItem(twomodel->item(row,17)->text().section(" ",i,i)));
    }
    tabWidget->setCurrentIndex(0);
}

void fucaichukuDlg::Increasing()
{
    row = view->rowCount(); //获取表格行数
    view->setRowCount(++row);//表格加一行
}

void fucaichukuDlg::Decreasing()
{
    int row = view->rowCount();
    if(row == 0){
        return;
    }
    row = view->currentRow();
    this->view->removeRow(row);
}

void fucaichukuDlg::on_twochaxunBtn()
{
    QString lingyongbumen;
    lingyongbumen.clear();

    if(twocheckBox2->checkState() == 2){
        lingyongbumen = QString(" and CollarDepartment='%1'").arg(twocomBox2->currentText());
    }

    QString searchSQL = QString("select WarehouseNumber  出库单号,Outdate  出库日期,EntryPersonnel  录入人员,\
                                CollarDepartment 领用部门,CollarPerson 领用人员,type  类型,LicensePlateEquipment  车牌设备,\
                                TotalAmount 总金额,Remarks  备注,AuxiliaryNumber  辅材编号,MaterialName  辅材名称,\
                                GenericClass 所属大类,SubordinateClass  所属小类,Specifications  规格,Company  单位,\
                                Number  数量,round(UnitPrice,2)  单价,AmountMoney  金额,WhetherAudit 是否审核 \
                                from AuxiliaryOutput where Outdate between '%1' and '%2'%3;")
            .arg(twodateEdit1->date().toString(("yyyy-MM-dd")),twodateEdit2->date().addDays(1).toString(("yyyy-MM-dd")),
                 lingyongbumen);
    db.showview(searchSQL.toStdString().data(),twoview,&twomodel);
    qDebug()<<db.geterror();
}

void fucaichukuDlg::on_CalculateTotalAmount()
{
    double total = 0;
    int rowcount = view->rowCount();
    for(int i = 0; i<rowcount; i++){
        if(view->item(i,8)){
            total += view->item(i,8)->text().toDouble();
        }
    }
    lineEdit3->setText(QString::number(total,'f',2));
}
