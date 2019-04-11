#include "yidakaichuangkoumenu.h"
#include "mainwindow.h"
#include <QDebug>

yiDaKaiChuangKouMenu::yiDaKaiChuangKouMenu(MainWindow *main_w, mainTitle *main_title, QWidget *parent) :
    QWidget(parent)
{
    this->main_w = main_w;
    this->main_title = main_title;
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Popup);
    this->setObjectName(QString("openWindow"));
    this->isMouseOnWindow = false;


    signalMapper = new QSignalMapper(this);
    QGridLayout *layout = new QGridLayout(this);
    layout->setMargin(5);

    int count = this->main_w->mdiArea->subWindowList().size();
    count_except_menu = count;

    for(int i = 0; i < count; i++)
    {
        QString name = this->main_w->mdiArea->subWindowList().at(i)->windowTitle();
        if(name.contains(tr("菜单"))){
            count_except_menu -= 1;
            continue;
        }
        QPushButton *btn = new QPushButton(this);
        btn->setFixedSize(120,120);
        btn->setObjectName(QString("btn%1").arg(i));
        btn->setStyleSheet(QString("QPushButton[objectName=\"btn%1\"]{border:0px;background-image:url(:/menupic/%2)}"
                           "QPushButton[objectName=\"btn%3\"]:hover{border:1px solid rgb(7,4,127);background-image:url(:/menupic/%4)}"
                           "QPushButton[objectName=\"btn%5\"]:pressed{border:2px solid rgb(7,4,127);background-image:url(:/menupic/%6)}")
                           .arg(i).arg(replace(name)).arg(i).arg(replace(name)).arg(i).arg(replace(name)));
        connect(btn, SIGNAL(clicked()), signalMapper, SLOT(map()));
        //connect(btn,SIGNAL())
        signalMapper->setMapping(btn, name);
        layout->addWidget(btn,i / 8,i % 8);
    }
    connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(openWindow(QString)));

    this->setStyleSheet("QWidget[objectName=\"openWindow\"]{background-color: rgb(7,4,127)}");
}

void yiDaKaiChuangKouMenu::leaveEvent(QEvent *)
{
    this->close();
}

void yiDaKaiChuangKouMenu::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Escape:
           event->ignore();
           break;
        default:
           QWidget::keyPressEvent(event);
    }
}

void yiDaKaiChuangKouMenu::openWindow(QString windowTitle)
{
    int count = this->main_w->mdiArea->subWindowList().size();
    for(int i = 0; i < count; i++)
    {
        this->close();
        if(windowTitle == this->main_w->mdiArea->subWindowList().at(i)->windowTitle())
        {
            this->main_title->title->setText(windowTitle);
            this->main_w->mdiArea->subWindowList().at(i)->showMaximized();
        }
    }
    this->close();
}

QString yiDaKaiChuangKouMenu::replace(QString name)
{
    if(name == "首页"){
       return QString("shouyebtn.png");
    }
    else if(name == "供应商维护"){
        return QString("gongyingshangdanganbtn.png");
    }
    else if(name == "采购合同管理"){
        return QString("caigouhetongguanli.png");
    }
    else if(name == "采购合同审核变更"){
        return QString("hetongshenhebiangeng.png");
    }
    else if(name == "采购结算"){
        return QString("caigoujiesuan.png");
    }
    else if(name == "原料入库数据调整"){
        return QString("shujutiaozhengbtn.png");
    }
    else if(name == "辅材供应商档案"){
        return QString("fucaigongyingshangdanganbtn.png");
    }
    else if(name == "采购入库"){
        return QString("guobangrukubtn.png");
    }
    else if(name == "库存查询"){
        return QString("cangweikucunbtn.png");
    }
    else if(name == "库存调整"){
        return QString("kucuntiaozhengbtn.png");
    }
    else if(name == "供货质量排序"){
        return QString("gonghuozhiliangpaixubtn.png");
    }
    else if(name == "手动打料"){
        return QString("shoudongdaliaobtn.png");
    }
    else if(name == "辅材设置"){
        return QString("fucaishezhibtn.png");
    }
    else if(name == "辅材入库"){
        return QString("fucairukubtn.png");
    }
    else if(name == "辅材出库"){
        return QString("fucaichukubtn.png");
    }
    else if(name == "辅材库存"){
        return QString("fucaikucunbtn.png");
    }
    else if(name == "辅材耗用统计"){
        return QString("fucaihaoyongtongjibtn.png");
    }
    else if(name == "客户信息维护"){
        return QString("kehudanganbtn.png");
    }
    else if(name == "销售合同管理"){
        return QString("xiaoshouhetongguanlibtn.png");
    }
    else if(name == "销售合同审核变更"){
        return QString("xiaoshouhetongshenhebiangengbtn.png");
    }
    else if(name == "现金合同"){
        return QString("xianjinhetongbtn.png");
    }
    else if(name == "工程档案"){
        return QString("gongchengdanganBtn.png");
    }
    else if(name == "发货价格批量调整"){
        return QString("fahuojiagepiliangtiaozhengbtn.png");
    }
    else if(name == "销售结算"){
        return QString("xiaoshoujiesuanbtn.png");
    }
    else if(name == "合同执行情况"){
        return QString("hetongzhixingqingkuangbtn.png");
    }
    else if(name == "生产方量省料"){
        return QString("shengchanfangliangshengliaoBtn.png");
    }
    else if(name == "业务员确认"){
        return QString("yewuyuanquerenbtn.png");
    }
    else if(name == "销售收款条件"){
        return QString("xiaoshoushoukuantiaojianbtn.png");
    }
    else if(name == "生产预警"){
        return QString("shengchanyujingbtn.png");
    }
    else if(name == "生产任务单"){
        return QString("shengchanrenwudanbtn.png");
    }
    else if(name == "任务监控"){
        return QString("");
    }
    else if(name == "配合比模板维护"){
        return QString("peihebimubanweihubtn.png");
    }
    else if(name == "原料检验"){
        return QString("yuanliaojianyanbtn.png");
    }
    else if(name == "产品检验"){
        return QString("chanpinjianyanbtn.png");
    }
    else if(name == "外加剂合成管理"){
        return QString("waijiajihechengguanlibtn.png");
    }
    else if(name == "生产任务接收"){
        return QString("shengchanrenwujieshoubtn.png");
    }
    else if(name == "配合比通知单"){
        return QString("peihebitongzhidanbtn.png");
    }
    else if(name == "生产任务安排"){
        return QString("diaodupaichebtn.png");
    }
    else if(name == "发货数据调整"){
        return QString("fahuoshujutiaozheng.png");
    }
    else if(name == "车辆行程"){
        return QString("cheliangxingcheng.png");
    }
    else if(name == "发货确认"){
        return QString("fahuoquerenbtn.png");
    }
    else if(name == "机组接口"){
        return QString("jizujiekoubtn.png");
    }
    else if(name == "采购付款"){
        return QString("caigoufukuanbtn.png");
    }
    else if(name == "采购总账"){
        return QString("caigouzongzhangbtn.png");
    }
    else if(name == "销售收款"){
        return QString("xiaoshoushoukuan.png");
    }
    else if(name == "销售总账"){
        return QString("xiaoshouzongzhangbtn.png");
    }
    else if(name == "车辆费用付款"){
        return QString("cheliangfeiyongfukuanbtn.png");
    }
    else if(name == "其他费用设置"){
        return QString("qitafeiyongshezhibtn.png");
    }
    else if(name == "其他费用付款"){
        return QString("qitafeiyongfukuanbtn.png");
    }
    else if(name == "辅材付款"){
        return QString("facaifukuanbtn.png");
    }
    else if(name == "账号设置"){
        return QString("zhanghaoshezhibtn.png");
    }
    else if(name == "原料消耗价格调整"){
        return QString("yuanliaoxiaohaojiagetiaozhengbtn.png");
    }
    else if(name == "账期管理"){
        return QString("zhangqiguanlibtn.png");
    }
    else if(name == "采购明细表"){
        return QString("caigoumingxibiaobtn.png");
    }
    else if(name == "销售明细表"){
        return QString("xiaoshoumingxibiaobtn.png");
    }
    else if(name == "理论消耗表"){
        return QString("lilunxiaohaobiaobtn.png");
    }
    else if(name == "生产消耗表"){
        return QString("shengchanxiaohaobiaobtn.png");
    }
    else if(name == "车辆运输报表"){
        return QString("cheliangyunshubaobiaobtn.png");
    }
    else if(name == "方量查询"){
        return QString("fangliangchaxunbtn.png");
    }
    else if(name == "生产分布"){
        return QString("shengchanfenbubtn.png");
    }
    else if(name == "对数单"){
        return QString("duishudanbtn.png");
    }
    else if(name == "结算单"){
        return QString("jiesuandanbtn.png");
    }
    else if(name == "每盘消耗统计"){
        return QString("meipanxiaohaotongjibtn.png");
    }
    else if(name == "砼车司机"){
        return QString("tongchesijibtn.png");
    }
    else if(name == "砼车信息"){
        return QString("tongchexinxibtn.png");
    }
    else if(name == "砼车加油"){
        return QString("tongchejiayoubtn.png");
    }
    else if(name == "运费结算"){
        return QString("yunfeijiesuanbtn.png");
    }
    else if(name == "运费设置"){
        return QString("yunfeishezhibtn.png");
    }
    else if(name == "排队管理"){
        return QString("paiduiguanlibtn.png");
    }
    else if(name == "工程运距确认"){
        return QString("gongchengyunjuquerenbtn.png");
    }
    else if(name == "泵车司机"){
        return QString("bengchesijibtn.png");
    }
    else if(name == "泵车信息"){
        return QString("bengchexinxibtn.png");
    }
    else if(name == "泵车加油"){
        return QString("bengchejiayoubtn.png");
    }
    else if(name == "泵费结算"){
        return QString("bengfeijiesuanbtn.png");
    }
    else if(name == "泵费设置"){
        return QString("bengfeishezhibtn.png");
    }
    else if(name == "设备档案"){
        return QString("shebeidanganbtn.png");
    }
    else if(name == "辅材耗用分析"){
        return QString("fucaihaoyongfenxibtn.png");
    }
    else if(name == "生产销售分析"){
        return QString("shengchanxiaoshoufenxibtn.png");
    }
    else if(name == "原料消耗分析"){
        return QString("yuanliaoxiaohaofenxibtn.png");
    }
    else if(name == "油耗分析"){
        return QString("youhaofenxibtn.png");
    }
    else if(name == "销售经营月报"){
        return QString("xiaoshoujingyingyuebaobtn.png");
    }
    else if(name == "公司汇总统计"){
        return QString("gongsihuizongtongji.png");
    }
    else if(name == "厂地设置"){
        return QString("changdishezhibtn.png");
    }
    else if(name == "部门设置"){
        return QString("bumenshezhibtn.png");
    }
    else if(name == "原料设置"){
        return QString("yuanliaoshezhibtn.png");
    }
    else if(name == "仓位设置"){
        return QString("cangweishezhibtn.png");
    }
    else if(name == "产品设置"){
        return QString("chanpinshezhibtn.png");
    }
    else if(name == "属性设置"){
        return QString("shuxingshezhibtn.png");
    }
    else if(name == "用户管理"){
        return QString("yonghuguanlibtn.png");
    }
    else if(name == "权限管理"){
        return QString("quanxianguanlibtn.png");
    }
    else if(name == "密码修改"){
        return QString("mimaxiugaibtn.png");
    }
    else if(name == "采购合同审核人"){
        return QString("caigouhetongshenherenbtn.png");
    }
    else if(name == "销售合同审核人"){
        return QString("xiaoshouhetongshenherenbtn.png");
    }
    else if(name == "车辆维修费用"){
        return QString("cheliangweixiufeiyong.png");
    }
    else if(name == "砼发货明细"){
        return QString("tongfahuomingxihedui.png");
    }
    else if(name == "采购入库明细"){
        return QString("caigourukumingxihedui.png");
    }
    else if(name == "供货对账单"){
        return QString("caigoujiesuan.png");
    }
    else{
        return QString("");
    }
}
