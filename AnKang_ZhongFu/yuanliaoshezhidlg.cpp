#include "yuanliaoshezhidlg.h"

extern mymysql db;
extern myTCPsocket *sockClient;

yuanliaoshezhiDlg::yuanliaoshezhiDlg(QWidget *parent) :
    QDialog(parent)
{
    tabWidget = new QTabWidget(this);
    yuanliaoshezhi = new QWidget(this);
    jizuyuanliaoduiyingERPyuanliao = new QWidget(this);
    jizuyuanliaoshezhi = new QWidget(this);

    creatTabPage1();
    creatTabPage2();
    creatTabPage3();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tabWidget);
}

yuanliaoshezhiDlg::~yuanliaoshezhiDlg()
{
    delete MaterialModel;
    delete twomodel;
    delete threemodel;
}

void yuanliaoshezhiDlg::refresh()
{
    db.showview(SQL1,MaterialView,&MaterialModel);//显示表格
    db.showview(SQL2,twoview,&twomodel);//显示表格
    db.showview(SQL3,threeview,&threemodel);//显示表格
}

void yuanliaoshezhiDlg::keyPressEvent(QKeyEvent *event)
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

void yuanliaoshezhiDlg::creatTabPage1()
{
    createAction();
    createTool();

    SQL1 = "select ID 原料编号,Material 原料名称,SpecificationModel 规格型号,Unit 单位,Type 类型,FoldOver 折方比,Remarks 备注 from MaterialSetting;";

    QLabel *MaterialNoLabel  = new QLabel(tr("原料编号"),this);
    MaterialNoLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *MaterialNameLabel  = new QLabel(tr("原料名称"),this);
    MaterialNameLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *SpecificationLabel  = new QLabel(tr("规格（型号）"),this);
    SpecificationLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *UnitLabel  = new QLabel(tr("单位"),this);
    UnitLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *MaterialTyepLabel  = new QLabel(tr("类型"),this);
    MaterialTyepLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *FoldOverLabel = new QLabel(tr("折方比"),this);
    FoldOverLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *InstructLabel = new QLabel(tr("1方=？公斤 如原料以方计算，请输入折方比"),this);
    QLabel *RemarksLabel = new QLabel(tr("备注"),this);
    RemarksLabel->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

    MaterialNoLineEdit = new QLineEdit(this);
    MaterialNoLineEdit->setStyleSheet("color:black");
    MaterialNameLineEdit = new QLineEdit(this);
    MaterialNameLineEdit->setStyleSheet("color:black");
    SpecificationLineEdit = new QLineEdit(this);
    SpecificationLineEdit->setStyleSheet("color:black");
    FoldOverLineEdit = new QLineEdit(this);
    RemarksLineEdit = new QLineEdit(this);

    UnitCombox = new QComboBox(this);
    UnitCombox->setView(new QListView(this));
    UnitCombox->setEditable(true);
    UnitCombox->addItem(tr("吨"));
    MaterialTyepCombox = new QComboBox(this);
    MaterialTyepCombox->setView(new QListView(this));
    MaterialTyepCombox->addItem(tr("砂"));
    MaterialTyepCombox->addItem(tr("水洗砂"));
    MaterialTyepCombox->addItem(tr("细石"));
    MaterialTyepCombox->addItem(tr("石子"));
    MaterialTyepCombox->addItem(tr("水泥"));
    MaterialTyepCombox->addItem(tr("矿粉"));
    MaterialTyepCombox->addItem(tr("粉煤灰"));
    MaterialTyepCombox->addItem(tr("膨胀剂"));
    MaterialTyepCombox->addItem(tr("减水剂"));
    MaterialTyepCombox->addItem(tr("外加剂"));
    MaterialTyepCombox->addItem(tr("石粉"));
    MaterialTyepCombox->addItem(tr("水"));
    MaterialTyepCombox->addItem(tr("柴油"));

    MaterialView = new QTableView(this);
    db.showview(SQL1,MaterialView,&MaterialModel);//显示表格
    connect(MaterialView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick()));


    QGridLayout *layout1 = new QGridLayout;
    layout1->addWidget(MaterialNoLabel,0,0);
    layout1->addWidget(MaterialNoLineEdit,0,1);
    layout1->addWidget(UnitLabel,0,2);
    layout1->addWidget(UnitCombox,0,3);
    layout1->addWidget(MaterialNameLabel,1,0);
    layout1->addWidget(MaterialNameLineEdit,1,1);
    layout1->addWidget(MaterialTyepLabel,1,2);
    layout1->addWidget(MaterialTyepCombox,1,3);
    layout1->addWidget(SpecificationLabel,2,0);
    layout1->addWidget(SpecificationLineEdit,2,1);
    layout1->addWidget(FoldOverLabel,2,2);
    layout1->addWidget(FoldOverLineEdit,2,3);
    layout1->addWidget(InstructLabel,2,4);
    layout1->addWidget(RemarksLabel,3,0);
    layout1->addWidget(RemarksLineEdit,3,1,1,3);
    layout1->setColumnStretch(0,0);
    layout1->setColumnStretch(1,1);
    layout1->setColumnStretch(2,0);
    layout1->setColumnStretch(3,1);
    layout1->setColumnStretch(4,0);
    layout1->setColumnStretch(5,1);
    layout1->setColumnStretch(6,0);
    layout1->setColumnStretch(7,0);


    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(toolBar);
    vlayout->addLayout(layout1);
    vlayout->addWidget(MaterialView);


    yuanliaoshezhi->setLayout(vlayout);
    tabWidget->addTab(yuanliaoshezhi,tr("原料设置"));
}

void yuanliaoshezhiDlg::creatTabPage2()
{
    createAction2();
    createTool2();

    SQL2 = "select ProductionUnit 生产机组,UnitMaterial 机组原料,ERPmaterial ERP原料,Position 仓位,ID from UnitMaterialCorrespondsToERPMaterial;";

    QLabel *label1  = new QLabel(tr("生产机组"),this);
    label1->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label2  = new QLabel(tr("ERP原料"),this);
    label2->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label3  = new QLabel(tr("机组原料"),this);
    label3->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label4  = new QLabel(tr("ERP仓位"),this);
    label4->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

    twocombo1 = new QComboBox(this);
    twocombo1->setStyleSheet("color:black");
    const char *fillSQL1 = "select UnitName from UnitSetting;";
    db.sql_fillComboBoxItem(fillSQL1,twocombo1);
    connect(twocombo1,SIGNAL(currentTextChanged(QString)),this,SLOT(twocombo3Change()));

    twocombo2 = new QComboBox(this);
    const char *fillSQL2 = "select Material from MaterialSetting;";
    db.sql_fillComboBoxItem(fillSQL2,twocombo2);
    connect(twocombo2,SIGNAL(currentTextChanged(QString)),this,SLOT(twocombo4Change()));

    twocombo3 = new QComboBox(this);
    twocombo3->setStyleSheet("color:black");

    twocombo4 = new QComboBox(this);

    twoview = new QTableView(this);
    db.showview(SQL2,twoview,&twomodel);//显示表格
    connect(twoview,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick2()));
    twoview->setColumnHidden(4,true);
    twoview->setColumnWidth(0,150);
    twoview->setColumnWidth(1,150);
    twoview->setColumnWidth(2,150);
    twoview->setColumnWidth(3,150);

    QGridLayout *layout1 = new QGridLayout;
    layout1->addWidget(label1,0,0);
    layout1->addWidget(twocombo1,0,1);
    layout1->addWidget(label2,0,2);
    layout1->addWidget(twocombo2,0,3);
    layout1->addWidget(label3,1,0);
    layout1->addWidget(twocombo3,1,1);
    layout1->addWidget(label4,1,2);
    layout1->addWidget(twocombo4,1,3);
    layout1->setColumnStretch(0,0);
    layout1->setColumnStretch(1,1);
    layout1->setColumnStretch(2,0);
    layout1->setColumnStretch(3,1);
    layout1->setColumnStretch(4,2);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(toolBar2);
    vlayout->addLayout(layout1);
    vlayout->addWidget(twoview);

    jizuyuanliaoduiyingERPyuanliao->setLayout(vlayout);
    tabWidget->addTab(jizuyuanliaoduiyingERPyuanliao,tr("机组原料对应ERP原料"));
}

void yuanliaoshezhiDlg::creatTabPage3()
{
    createAction3();
    createTool3();

    SQL3 = "select Material 机组原料,Specifications 规格,SubordinateUnit 生产机组,\
            CorrespondingField 对应字段,id from UnitMaterialSetting order by SubordinateUnit,Material;";

    QLabel *label1  = new QLabel(tr("机组原料"),this);
    label1->setStyleSheet("color:red");
    QLabel *label2  = new QLabel(tr("规格"),this);
    QLabel *label3  = new QLabel(tr("生产机组"),this);
    QLabel *label4  = new QLabel(tr("对应字段"),this);
    label4->setStyleSheet("color:red");

    threecombo1 = new QComboBox(this);
    const char *fillSQL1 = "select UnitName from UnitSetting;";
    db.sql_fillComboBoxItem(fillSQL1,threecombo1);

    threelineEdit1 = new QLineEdit(this);
    threelineEdit2 = new QLineEdit(this);
    threelineEdit3 = new QLineEdit(this);
    threelineEdit3->setStyleSheet("color:black");

    threeview = new QTableView(this);
    db.showview(SQL3,threeview,&threemodel);//显示表格
    connect(threeview,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick3()));
    threeview->setColumnWidth(0,150);
    threeview->setColumnWidth(1,150);
    threeview->setColumnWidth(2,150);
    threeview->setColumnWidth(3,150);
    threeview->setColumnHidden(4,true);
    threeview->setSortingEnabled(true);

    QHBoxLayout *layout1 = new QHBoxLayout;
    layout1->addWidget(label1,0);
    layout1->addWidget(threelineEdit1,1);
    layout1->addWidget(label2,0);
    layout1->addWidget(threelineEdit2,1);
    layout1->addWidget(label3,0);
    layout1->addWidget(threecombo1,1);
    layout1->addWidget(label4,0);
    layout1->addWidget(threelineEdit3,1);
    layout1->addSpacing(300);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(toolBar3);
    vlayout->addLayout(layout1);
    vlayout->addWidget(threeview);

    jizuyuanliaoshezhi->setLayout(vlayout);
    tabWidget->addTab(jizuyuanliaoshezhi,tr("机组原料设置"));
}

void yuanliaoshezhiDlg::ShowSupplyclick()
{
    MaterialNoLineEdit->setEnabled(false);
    MaterialNameLineEdit->setEnabled(false);
    updateAction->setEnabled(true);
    deleteAction->setEnabled(true);
    saveAction->setEnabled(false);

    int row = MaterialView->currentIndex().row();
    MaterialNoLineEdit->setText(MaterialModel->item(row,0)->text());
    MaterialNameLineEdit->setText(MaterialModel->item(row,1)->text());
    SpecificationLineEdit->setText(MaterialModel->item(row,2)->text());
    UnitCombox->setCurrentText(MaterialModel->item(row,3)->text());
    MaterialTyepCombox->setCurrentText(MaterialModel->item(row,4)->text());
    FoldOverLineEdit->setText(MaterialModel->item(row,5)->text());
    RemarksLineEdit->setText(MaterialModel->item(row,6)->text());
}

void yuanliaoshezhiDlg::ShowSupplyclick2()
{
    twocombo1->setEnabled(false);
    twocombo3->setEnabled(false);
    updateAction2->setEnabled(true);
    deleteAction2->setEnabled(true);
    saveAction2->setEnabled(false);
    int row = twoview->currentIndex().row();

    twocombo1->setCurrentText(twomodel->item(row,0)->text());
    twocombo2->setCurrentText(twomodel->item(row,2)->text());
    twocombo3->setCurrentText(twomodel->item(row,1)->text());
    twocombo4->setCurrentText(twomodel->item(row,3)->text());
    twostr5 = twomodel->item(row,4)->text();
}

void yuanliaoshezhiDlg::ShowSupplyclick3()
{
    threelineEdit3->setEnabled(false);
    updateAction3->setEnabled(true);
    deleteAction3->setEnabled(true);
    saveAction3->setEnabled(false);
    int row = threeview->currentIndex().row();

    threelineEdit1->setText(threemodel->item(row,0)->text());
    threelineEdit2->setText(threemodel->item(row,1)->text());
    threelineEdit3->setText(threemodel->item(row,3)->text());
    threecombo1->setCurrentText(threemodel->item(row,2)->text());
    id = threemodel->item(row,4)->text();
}

void yuanliaoshezhiDlg::twocombo3Change()
{
    twocombo3->clear();
    QString fillSQL3 = QString("select Material from UnitMaterialSetting where SubordinateUnit='%1';").arg(twocombo1->currentText());
    db.sql_fillComboBoxItem(fillSQL3.toStdString().data(),twocombo3);
}

void yuanliaoshezhiDlg::twocombo4Change()
{
    twocombo4->clear();
    QString fillSQL4 = QString("select PositionName from PositionSetting where Material='%1';").arg(twocombo2->currentText());
    db.sql_fillComboBoxItem(fillSQL4.toStdString().data(),twocombo4);
}



void yuanliaoshezhiDlg::on_newAction()
{
    MaterialNoLineEdit->setFocus();
    saveAction->setEnabled(true);
    updateAction->setEnabled(false);
    deleteAction->setEnabled(false);

    MaterialNoLineEdit->clear();
    MaterialNoLineEdit->setEnabled(true);
    MaterialNameLineEdit->clear();
    MaterialNameLineEdit->setEnabled(true);
    SpecificationLineEdit->clear();
    SpecificationLineEdit->setEnabled(true);
    FoldOverLineEdit->clear();
    RemarksLineEdit->clear();
    UnitCombox->setCurrentIndex(0);
    MaterialTyepCombox->setCurrentIndex(0);
}

void yuanliaoshezhiDlg::on_saveAction()
{
    if(MaterialNoLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入原料编号"),0,0,0);
        return;
    }
    if(MaterialNameLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入原料名称"),0,0,0);
        return;
    }
    if(UnitCombox->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择单位"),0,0,0);
        return;
    }
    if(MaterialTyepCombox->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择类型"),0,0,0);
        return;
    }

    QString saveSQL = QString("insert into MaterialSetting (ID,Material,SpecificationModel,Unit,Type,FoldOver,Remarks) values ('%1','%2','%3','%4','%5','%6','%7')")
                    .arg(MaterialNoLineEdit->text(),MaterialNameLineEdit->text(),SpecificationLineEdit->text(),UnitCombox->currentText(),\
                         MaterialTyepCombox->currentText(),FoldOverLineEdit->text(),RemarksLineEdit->text());

    int res = db.sql_exec(saveSQL.toStdString().data());
    if(res == -1){
        QMessageBox::information(this, tr("失败"),tr("重复的原材料"),0,0,0);
        return;
    }
    else if(res == 0){
        db.showview(SQL1,MaterialView,&MaterialModel);//显示表格
        on_newAction();
        const char *fillSQL2 = "select Material from MaterialSetting;";
        twocombo2->clear();
        db.sql_fillComboBoxItem(fillSQL2,twocombo2);
        QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
    }
}

void yuanliaoshezhiDlg::on_updateAction()
{
    if(MaterialNoLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入原料编号"),0,0,0);
        return;
    }
    if(MaterialNameLineEdit->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入原料名称"),0,0,0);
        return;
    }
    if(UnitCombox->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择单位"),0,0,0);
        return;
    }
    if(MaterialTyepCombox->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择类型"),0,0,0);
        return;
    }


    QString updateSQL = QString("update MaterialSetting set Material='%1',SpecificationModel='%2',Unit='%3',Type='%4',FoldOver='%5',Remarks='%6' where ID='%7'")
            .arg(MaterialNameLineEdit->text(),SpecificationLineEdit->text(),UnitCombox->currentText(),MaterialTyepCombox->currentText(),FoldOverLineEdit->text(),
                 RemarksLineEdit->text(),MaterialNoLineEdit->text());

    int res = db.sql_exec(updateSQL.toStdString().data());
    if(res == -1){
        QMessageBox::information(this, tr("失败"),tr("重复的原材料"),0,0,0);
        return;
    }
    else if(res == 0){
        db.showview(SQL1,MaterialView,&MaterialModel);//显示表格
        on_newAction();
        const char *fillSQL2 = "select Material from MaterialSetting;";
        twocombo2->clear();
        db.sql_fillComboBoxItem(fillSQL2,twocombo2);
        QMessageBox::information(this,tr("提示信息"),tr("修改成功"),0,0,0);
    }
}

void yuanliaoshezhiDlg::on_deleteAction()
{
    QString deleteSQL = QString("delete from MaterialSetting where ID='%1';").arg(MaterialNoLineEdit->text());
    QString chaxunkucunSQL = QString("select Quantity from InventoryQueryTmp where MaterialNumber='%1';").arg(MaterialNoLineEdit->text());
    QString count = db.sql_fetchrow_plus(chaxunkucunSQL.toStdString().data(),0);

    if(count.toInt() > 0){
        QMessageBox::information(this,tr("提示信息"),tr("原料有剩余，无法删除"),0,0,0);
        return;
    }
    else{
        int res = db.sql_exec(deleteSQL.toStdString().data());
        if(res == 0){
            db.showview(SQL1,MaterialView,&MaterialModel);//显示表格
            QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
            const char *fillSQL2 = "select Material from MaterialSetting;";
            twocombo2->clear();
            db.sql_fillComboBoxItem(fillSQL2,twocombo2);
            on_newAction();
        }
    }
}

void yuanliaoshezhiDlg::on_newAction2()
{
    twocombo1->setEnabled(true);
    twocombo3->setEnabled(true);
    saveAction2->setEnabled(true);
    updateAction2->setEnabled(false);
    deleteAction2->setEnabled(false);

    twocombo1->setCurrentIndex(0);
    twocombo2->setCurrentIndex(0);
    twocombo3->setCurrentIndex(0);
    twocombo4->setCurrentIndex(0);
}

void yuanliaoshezhiDlg::on_saveAction2()
{
    CorrespondingField.clear();
    if(twocombo1->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择生产机组"),0,0,0);
        return;
    }
    if(twocombo2->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择ERP原料"),0,0,0);
        return;
    }
    if(twocombo3->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择机组原料"),0,0,0);
        return;
    }
    if(twocombo4->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择ERP仓位"),0,0,0);
        return;
    }
    QString searchSQL = QString("select CorrespondingField from UnitMaterialSetting where SubordinateUnit='%1' and Material='%2';").arg(twocombo1->currentText(),twocombo3->currentText());
    CorrespondingField = db.sql_fetchrow_plus(searchSQL.toStdString().data(),0);

    QString save2SQL = QString("insert into UnitMaterialCorrespondsToERPMaterial (ProductionUnit,UnitMaterial,\
                               ERPmaterial,Position,CorrespondingField) values ('%1','%2','%3','%4','%5');")
                    .arg(twocombo1->currentText(),twocombo3->currentText(),twocombo2->currentText(),twocombo4->currentText(),CorrespondingField);
    int res = db.sql_exec(save2SQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();
        on_newAction2();
        QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
    }
}

void yuanliaoshezhiDlg::on_updateAction2()
{
    if(twocombo2->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择ERP原料"),0,0,0);
    }
    if(twocombo4->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择ERP仓位"),0,0,0);
    }
    QString update2SQL = QString("update UnitMaterialCorrespondsToERPMaterial set ERPmaterial='%1',Position='%2' where ID=%3;")
                    .arg(twocombo2->currentText(),twocombo4->currentText()).arg(twostr5.toInt());
    int res = db.sql_exec(update2SQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();
        on_newAction2();
        QMessageBox::information(this,tr("提示信息"),tr("修改成功"),0,0,0);
    }
}

void yuanliaoshezhiDlg::on_deleteAction2()
{
    QString delete2SQL = QString("delete from UnitMaterialCorrespondsToERPMaterial where ID=%1;").arg(twostr5.toInt());
    int res = db.sql_exec(delete2SQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();
        on_newAction2();
        QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
    }
}

void yuanliaoshezhiDlg::on_newAction3()
{
    threelineEdit3->setEnabled(true);
    threelineEdit1->setFocus();
    saveAction3->setEnabled(true);
    updateAction3->setEnabled(false);
    deleteAction3->setEnabled(false);

    threelineEdit1->clear();
    threelineEdit2->clear();
    threelineEdit3->clear();
    threecombo1->setCurrentIndex(0);
}

void yuanliaoshezhiDlg::on_saveAction3()
{
    if(threelineEdit1->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入机组原料"),0,0,0);
        return;
    }
    if(threelineEdit3->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入对应字段"),0,0,0);
        return;
    }
    if(threecombo1->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选择生产机组"),0,0,0);
        return;
    }
    QString cmpSQL1 = QString("select Material from UnitMaterialSetting where SubordinateUnit='%1';").arg(threecombo1->currentText());
    int ret1 = db.sql_whetherRepeat(cmpSQL1.toStdString().data(),threelineEdit1->text());
    if(ret1 == -3){
        QMessageBox::information(this,tr("错误"),tr("请检查机组原料是否重复"),0,0,0);
        return;
    }
    QString cmpSQL2 = QString("select CorrespondingField from UnitMaterialSetting where SubordinateUnit='%1';").arg(threecombo1->currentText());
    int ret2 = db.sql_whetherRepeat(cmpSQL2.toStdString().data(),threelineEdit3->text());
    if(ret2 == -3){
        QMessageBox::information(this,tr("错误"),tr("请检查对应字段是否重复"),0,0,0);
        return;
    }
    QString save3SQL = QString("insert into UnitMaterialSetting (Material,Specifications,SubordinateUnit,CorrespondingField) values ('%1','%2','%3','%4');")
                    .arg(threelineEdit1->text(),threelineEdit2->text(),threecombo1->currentText(),threelineEdit3->text());
    int res = db.sql_exec(save3SQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();
        on_newAction3();
        QMessageBox::information(this,tr("提示信息"),tr("保存成功"),0,0,0);
    }
}

void yuanliaoshezhiDlg::on_updateAction3()
{
    if(threelineEdit1->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入机组原料"),0,0,0);
        return;
    }
    if(threecombo1->currentText().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请选中生产机组"),0,0,0);
        return;
    }

    QString cmpSQL = QString("select Material from UnitMaterialSetting where SubordinateUnit='%1';").arg(threecombo1->currentText());
    int ret = db.sql_whetherRepeat(cmpSQL.toStdString().data(),threelineEdit1->text());
    if(ret == -3){
        QMessageBox::information(this,tr("错误"),tr("请检查机组原料是否重复"),0,0,0);
        return;
    }

    QString update3SQL = QString("update UnitMaterialSetting set Material='%1',Specifications='%2',SubordinateUnit='%3' where id='%4';")
                    .arg(threelineEdit1->text(),threelineEdit2->text(),threecombo1->currentText(),id);
    int res = db.sql_exec(update3SQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();
        on_newAction3();
        QMessageBox::information(this,tr("提示信息"),tr("修改成功"),0,0,0);
    }
}

void yuanliaoshezhiDlg::on_deleteAction3()
{
    QString delete3SQL = QString("delete from UnitMaterialSetting where id='%1';").arg(id);
    int res = db.sql_exec(delete3SQL.toStdString().data());
    if(res == 0){
        sockClient->send_Msg3();
        on_newAction3();
        QMessageBox::information(this,tr("提示信息"),tr("删除成功"),0,0,0);
    }
}


void yuanliaoshezhiDlg::createAction()
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

void yuanliaoshezhiDlg::createTool()
{
    toolBar = new QToolBar(this);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar->addAction(newAction);
    toolBar->addAction(saveAction);
    toolBar->addAction(updateAction);
    toolBar->addAction(deleteAction);
}

void yuanliaoshezhiDlg::createAction2()
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

void yuanliaoshezhiDlg::createTool2()
{
    toolBar2 = new QToolBar(this);
    toolBar2->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar2->addAction(newAction2);
    toolBar2->addAction(saveAction2);
    toolBar2->addAction(updateAction2);
    toolBar2->addAction(deleteAction2);
}

void yuanliaoshezhiDlg::createAction3()
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

void yuanliaoshezhiDlg::createTool3()
{
    toolBar3 = new QToolBar(this);
    toolBar3->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar3->addAction(newAction3);
    toolBar3->addAction(saveAction3);
    toolBar3->addAction(updateAction3);
    toolBar3->addAction(deleteAction3);
}
