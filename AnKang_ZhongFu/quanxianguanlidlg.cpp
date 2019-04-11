#include "quanxianguanlidlg.h"

extern mymysql db;

quanxianguanliDlg::quanxianguanliDlg(QWidget *parent) :
    QDialog(parent)
{
    SQL = "select UserName 用户名,RealName 真实姓名,CustomerType 用户类型,SubordinateDepartment 所属部门,MobilePhone 手机,\
            WeighingPermissions 过磅权限,Jurisdiction from UserManagement where CustomerType!='管理员';";

    view = new QTableView;
    db.showview(SQL,view,&model);//显示表格
    view->setColumnHidden(6,true);
    connect(view,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(ShowSupplyclick()));

    treeWidget = new QTreeWidget;
    connect(treeWidget,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(on_leafstateChanged()));
    treeWidget->setEnabled(false);
    QLabel *label = new QLabel(tr("用户名"));
    label->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    lineEdit = new QLineEdit;
    lineEdit->setEnabled(false);
    lineEdit->setStyleSheet("color:black");
    Btn = new QPushButton;
    Btn->setText(tr("保存权限"));
    connect(Btn,SIGNAL(clicked()),this,SLOT(on_updateAction()));
    Btn->setEnabled(false);
    Btn1 = new QPushButton;
    Btn1->setText(tr("刷新"));
    connect(Btn1,SIGNAL(clicked()),this,SLOT(on_refresh()));
    checkBox = new QCheckBox;
    checkBox->setText(tr("全选"));
    checkBox->setEnabled(false);
    connect(checkBox,SIGNAL(stateChanged(int)),this,SLOT(on_stateChanged()));

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(view,0,0,1,5);
    layout->addWidget(treeWidget,0,5,1,5);
    layout->addWidget(label,1,0,Qt::AlignTop);
    layout->addWidget(lineEdit,1,1,Qt::AlignTop);
    layout->addWidget(Btn1,1,3,Qt::AlignTop);
    layout->addWidget(Btn,1,4,Qt::AlignTop);
    layout->addWidget(checkBox,1,5,Qt::AlignTop);
    layout->setColumnStretch(0,0);
    layout->setColumnStretch(1,1);
    layout->setColumnStretch(2,1);
    layout->setColumnStretch(3,1);
    layout->setColumnStretch(4,1);
    layout->setColumnStretch(5,1);
    layout->setColumnStretch(6,2);
    layout->setColumnStretch(7,1);
    layout->setRowStretch(0,8);
    layout->setRowStretch(1,1);

    //treeWidget添加权限选择checkbox
    treeWidget->setColumnCount(1);
    treeWidget->setHeaderHidden(true);


    //采购管理
    root1 = new QTreeWidgetItem(treeWidget, QStringList("采购管理菜单"));
    treeWidget->setItemExpanded(root1,true);
    itemList.append(root1);
    leaf12 = new QTreeWidgetItem(root1, QStringList("采购合同管理"));
    itemList.append(leaf12);
    leaf14 = new QTreeWidgetItem(root1, QStringList("原料消耗价格设置"));
    itemList.append(leaf14);
    leaf16 = new QTreeWidgetItem(root1, QStringList("辅材供应商档案"));
    itemList.append(leaf16);

    //原料管理
    root2 = new QTreeWidgetItem(treeWidget, QStringList("原料管理菜单"));
    treeWidget->setItemExpanded(root2,true);
    itemList.append(root2);
    leaf21 = new QTreeWidgetItem(root2, QStringList("库存查询"));
    itemList.append(leaf21);
    leaf22 = new QTreeWidgetItem(root2, QStringList("库存调整"));
    itemList.append(leaf22);

    //辅材管理
    root3 = new QTreeWidgetItem(treeWidget, QStringList("辅材管理菜单"));
    treeWidget->setItemExpanded(root3,true);
    itemList.append(root3);
    leaf31 = new QTreeWidgetItem(root3, QStringList("辅材设置"));
    itemList.append(leaf31);
    leaf32 = new QTreeWidgetItem(root3, QStringList("辅材入库"));
    itemList.append(leaf32);
    leaf33 = new QTreeWidgetItem(root3, QStringList("辅材出库"));
    itemList.append(leaf33);
    leaf34 = new QTreeWidgetItem(root3, QStringList("辅材库存"));
    itemList.append(leaf34);
    leaf35 = new QTreeWidgetItem(root3, QStringList("辅材耗用统计"));
    itemList.append(leaf35);

    //磅房管理
    root4 = new QTreeWidgetItem(treeWidget, QStringList("磅房管理菜单"));
    treeWidget->setItemExpanded(root4,true);
    itemList.append(root4);
    leaf41 = new QTreeWidgetItem(root4, QStringList("采购入库"));
    itemList.append(leaf41);

    //销售管理
    root5 = new QTreeWidgetItem(treeWidget, QStringList("销售管理菜单"));
    treeWidget->setItemExpanded(root5,true);
    itemList.append(root5);
    leaf51 = new QTreeWidgetItem(root5, QStringList("客户信息维护"));
    itemList.append(leaf51);
    leaf52 = new QTreeWidgetItem(root5, QStringList("销售合同管理"));
    itemList.append(leaf52);
    leaf57 = new QTreeWidgetItem(root5, QStringList("合同执行情况"));
    itemList.append(leaf57);
    leaf59 = new QTreeWidgetItem(root5, QStringList("销售收款条件"));
    itemList.append(leaf59);
    leaf510 = new QTreeWidgetItem(root5, QStringList("生产预警"));
    itemList.append(leaf510);

    //调度管理
    root6 = new QTreeWidgetItem(treeWidget, QStringList("调度管理菜单"));
    treeWidget->setItemExpanded(root6,true);
    itemList.append(root6);
    leaf61 = new QTreeWidgetItem(root6, QStringList("生产任务单"));
    itemList.append(leaf61);
    leaf62 = new QTreeWidgetItem(root6, QStringList("生产任务安排"));
    itemList.append(leaf62);

    //实验室管理
    root7 = new QTreeWidgetItem(treeWidget, QStringList("实验室管理菜单"));
    treeWidget->setItemExpanded(root7,true);
    itemList.append(root7);
    leaf71 = new QTreeWidgetItem(root7, QStringList("配合比模板维护"));
    itemList.append(leaf71);
    leaf73 = new QTreeWidgetItem(root7, QStringList("配合比通知单"));
    itemList.append(leaf73);

    //生产管理
    root8 = new QTreeWidgetItem(treeWidget, QStringList("生产管理菜单"));
    treeWidget->setItemExpanded(root8,true);
    itemList.append(root8);
    leaf81 = new QTreeWidgetItem(root8, QStringList("发货确认"));
    itemList.append(leaf81);
    leaf83 = new QTreeWidgetItem(root8, QStringList("机组接口"));
    itemList.append(leaf83);

    //财务管理
    root9 = new QTreeWidgetItem(treeWidget, QStringList("财务管理菜单"));
    treeWidget->setItemExpanded(root9,true);
    itemList.append(root9);
    leaf91 = new QTreeWidgetItem(root9, QStringList("砼发货明细"));
    itemList.append(leaf91);
    leaf92 = new QTreeWidgetItem(root9, QStringList("采购入库明细"));
    itemList.append(leaf92);
    leaf93 = new QTreeWidgetItem(root9, QStringList("销售总账"));
    itemList.append(leaf93);
    leaf94 = new QTreeWidgetItem(root9, QStringList("采购总账"));
    itemList.append(leaf94);
    leaf910 = new QTreeWidgetItem(root9, QStringList("发货价格批量调整"));
    itemList.append(leaf910);
    leaf911 = new QTreeWidgetItem(root9, QStringList("发货数据调整"));
    itemList.append(leaf911);
    leaf913 = new QTreeWidgetItem(root9, QStringList("原料入库数据调整"));
    itemList.append(leaf913);
//    leaf914 = new QTreeWidgetItem(root9, QStringList("供货对账单"));
//    itemList.append(leaf914);

    //报表查询
    root10 = new QTreeWidgetItem(treeWidget, QStringList("报表查询菜单"));
    treeWidget->setItemExpanded(root10,true);
    itemList.append(root10);
    leaf101 = new QTreeWidgetItem(root10, QStringList("采购明细表"));
    itemList.append(leaf101);
    leaf102 = new QTreeWidgetItem(root10, QStringList("销售明细表"));
    itemList.append(leaf102);
//    leaf103 = new QTreeWidgetItem(root10, QStringList("理论消耗表"));
//    itemList.append(leaf103);
    leaf104 = new QTreeWidgetItem(root10, QStringList("生产消耗表"));
    itemList.append(leaf104);
    leaf105 = new QTreeWidgetItem(root10, QStringList("车辆运输报表"));
    itemList.append(leaf105);
//    leaf106 = new QTreeWidgetItem(root10, QStringList("方量查询"));
//    itemList.append(leaf106);
    leaf107 = new QTreeWidgetItem(root10, QStringList("生产分布"));
    itemList.append(leaf107);
    leaf108 = new QTreeWidgetItem(root10, QStringList("生产方量省料"));
    itemList.append(leaf108);
//    leaf109 = new QTreeWidgetItem(root10, QStringList("结算单"));
//    itemList.append(leaf109);
//    leaf1010 = new QTreeWidgetItem(root10, QStringList("每盘消耗统计"));
//    itemList.append(leaf1010);

    //砼车管理
    root11 = new QTreeWidgetItem(treeWidget, QStringList("砼车管理菜单"));
    treeWidget->setItemExpanded(root11,true);
    itemList.append(root11);
    leaf111 = new QTreeWidgetItem(root11, QStringList("砼车司机"));
    itemList.append(leaf111);
    leaf112 = new QTreeWidgetItem(root11, QStringList("砼车信息"));
    itemList.append(leaf112);
//    leaf113 = new QTreeWidgetItem(root11, QStringList("砼车加油"));
//    itemList.append(leaf113);
//    leaf114 = new QTreeWidgetItem(root11, QStringList("运费结算"));
//    itemList.append(leaf114);
    leaf115 = new QTreeWidgetItem(root11, QStringList("运费设置"));
    itemList.append(leaf115);
//    leaf116 = new QTreeWidgetItem(root11, QStringList("排队管理"));
//    itemList.append(leaf116);
    leaf117 = new QTreeWidgetItem(root11, QStringList("工程运距确认"));
    itemList.append(leaf117);

    //add liwenxiu 2017-11-2
    leaf118 = new QTreeWidgetItem(root11, QStringList("车辆维修费用"));
    itemList.append(leaf118);
//    leaf119 = new QTreeWidgetItem(root11, QStringList("维修厂商设置"));
//    itemList.append(leaf119);
    //end liwenxiu 2017-11-2

    //泵车管理
    root12 = new QTreeWidgetItem(treeWidget, QStringList("泵车管理菜单"));
    treeWidget->setItemExpanded(root12,true);
    itemList.append(root12);
    leaf121 = new QTreeWidgetItem(root12, QStringList("泵车司机"));
    itemList.append(leaf121);
    leaf122 = new QTreeWidgetItem(root12, QStringList("泵车信息"));
    itemList.append(leaf122);
//    leaf123 = new QTreeWidgetItem(root12, QStringList("泵车加油"));
//    itemList.append(leaf123);
//    leaf124 = new QTreeWidgetItem(root12, QStringList("泵费结算"));
//    itemList.append(leaf124);
//    leaf125 = new QTreeWidgetItem(root12, QStringList("泵费设置"));
//    itemList.append(leaf125);

    //设备管理
//    root13 = new QTreeWidgetItem(treeWidget, QStringList("设备管理菜单"));
//    treeWidget->setItemExpanded(root13,true);
//    itemList.append(root13);
//    leaf131 = new QTreeWidgetItem(root13, QStringList("设备档案"));
//    itemList.append(leaf131);

    //决策分析
//    root15 = new QTreeWidgetItem(treeWidget, QStringList("决策分析菜单"));
//    treeWidget->setItemExpanded(root15,true);
//    itemList.append(root15);
//    leaf151 = new QTreeWidgetItem(root15, QStringList("生产销售分析"));
//    itemList.append(leaf151);
//    leaf152 = new QTreeWidgetItem(root15, QStringList("原料消耗分析"));
//    itemList.append(leaf152);
//    leaf154 = new QTreeWidgetItem(root15, QStringList("辅材耗用分析"));
//    itemList.append(leaf154);
//    leaf156 = new QTreeWidgetItem(root15, QStringList("公司汇总统计"));
//    itemList.append(leaf156);

    //系统设置
    root16 = new QTreeWidgetItem(treeWidget, QStringList("系统设置菜单"));
    treeWidget->setItemExpanded(root16,true);
    itemList.append(root16);
    leaf161 = new QTreeWidgetItem(root16, QStringList("厂地设置"));
    itemList.append(leaf161);
    leaf162 = new QTreeWidgetItem(root16, QStringList("部门设置"));
    itemList.append(leaf162);
    leaf163 = new QTreeWidgetItem(root16, QStringList("原料设置"));
    itemList.append(leaf163);
    leaf164 = new QTreeWidgetItem(root16, QStringList("仓位设置"));
    itemList.append(leaf164);
    leaf165 = new QTreeWidgetItem(root16, QStringList("产品设置"));
    itemList.append(leaf165);
    leaf166 = new QTreeWidgetItem(root16, QStringList("属性设置"));
    itemList.append(leaf166);
    leaf167 = new QTreeWidgetItem(root16, QStringList("用户管理"));
    itemList.append(leaf167);
    leaf168 = new QTreeWidgetItem(root16, QStringList("权限管理"));
    itemList.append(leaf168);
    leaf169 = new QTreeWidgetItem(root16, QStringList("密码修改"));
    itemList.append(leaf169);
//    leaf1610 = new QTreeWidgetItem(root16, QStringList("采购合同审核人"));
//    itemList.append(leaf1610);
//    leaf1611 = new QTreeWidgetItem(root16, QStringList("销售合同审核人"));
//    itemList.append(leaf1611);
    // add liwenxiu 2017-11-1
    leaf1612 = new QTreeWidgetItem(root16, QStringList("基本参数设置"));
    itemList.append(leaf1612);
    //end liwenxiu 2017-11-1

    int num = itemList.size();
    for(int i = 0; i<num; i++){
        itemList.at(i)->setCheckState(0,Qt::Unchecked);
    }
}

quanxianguanliDlg::~quanxianguanliDlg()
{
    delete model;
}

void quanxianguanliDlg::refresh()
{

}

void quanxianguanliDlg::keyPressEvent(QKeyEvent *event)
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

void quanxianguanliDlg::on_stateChanged()
{
    int num = itemList.size();
    if(2 == checkBox->checkState())//如果checkBox被选中
    {
        for(int i = 0; i<num; i++){
            itemList.at(i)->setCheckState(0,Qt::Checked);
        }
    }
    else if(0 == checkBox->checkState())//如果checkBox没有被选中
    {
        for(int i = 0; i<num; i++){
            itemList.at(i)->setCheckState(0,Qt::Unchecked);
        }
    }
}

void quanxianguanliDlg::on_leafstateChanged()
{
    int num = itemList.size();//获取item的个数

    QTreeWidgetItem *item = NULL;
    for(int i = 0; i<num; i++){
        item = itemList.at(i);
        if(item->checkState(0) == 2){//子item被选中，父item也被选中
            if(item->childCount() == 0){
                item->parent()->setCheckState(0,Qt::Checked);
            }
        }
        //当一个父item的所有子item都没有选中时，该父item也不被选中
        bool checkStatus = false;
        if(int childcount = item->childCount() != 0){
            for(int j = 0; j<childcount; j++){
                if(item->child(j)->checkState(0) == 2){
                    checkStatus = true;
                }
            }
            if(checkStatus == false){
                item->setCheckState(0,Qt::Unchecked);
            }
        }

    }
}

void quanxianguanliDlg::ShowSupplyclick()
{
    treeWidget->setEnabled(true);
    lineEdit->setReadOnly(true);
    Btn->setEnabled(true);
    checkBox->setEnabled(true);

    int row = view->currentIndex().row();
    lineEdit->setText(model->item(row,0)->text());
    QString Jurisdiction = model->item(row,6)->text();//获取用户权限

    int itemcount = itemList.size();
    for(int i = 0; i<itemcount; i++){
        itemList.at(i)->setCheckState(0,Qt::Unchecked);
        if(Jurisdiction.contains(itemList.at(i)->text(0))){
            itemList.at(i)->setCheckState(0,Qt::Checked);
        }
    }
}

void quanxianguanliDlg::on_updateAction()
{
    QString Jurisdiction;
    QTreeWidgetItem * item = NULL;
    int itemcount = itemList.size();
    for(int i = 0; i<itemcount; i++){
        item = itemList.at(i);
        if(item->checkState(0) == 2){
            Jurisdiction.append(item->text(0) + " ");
        }
    }

    QString updateSQL = QString("update UserManagement set Jurisdiction='%1' where UserName='%2';").arg(Jurisdiction,lineEdit->text());
    int res = db.sql_exec(updateSQL.toStdString().data());
    if(res == 0){
        lineEdit->clear();
        Btn->setEnabled(false);
        treeWidget->setEnabled(false);
        for(int i = 0; i<itemcount; i++){
            itemList.at(i)->setCheckState(0,Qt::Unchecked);
        }
        QMessageBox::information(this,tr("提示信息"),tr("保存权限成功"),0,0,0);
    }

   db.showview(SQL,view,&model);//显示表格
}

void quanxianguanliDlg::on_refresh()
{
    db.showview(SQL,view,&model);//显示表格
}
