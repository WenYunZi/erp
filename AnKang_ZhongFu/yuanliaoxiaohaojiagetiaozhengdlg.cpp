#include "yuanliaoxiaohaojiagetiaozhengdlg.h"

yuanliaoxiaohaojiagetiaozhengDlg::yuanliaoxiaohaojiagetiaozhengDlg(QWidget *parent) :
    QDialog(parent)
{
    tabWidget = new QTabWidget(this);
    yuanliaoxiaohaojiagetiaozheng = new QWidget(this);
    tiaozhengjiluchaxun  = new QWidget(this);
    yuanliaomingchengtiaozheng = new QWidget(this);
    mingchengtiaozhengjilu  = new QWidget(this);

    creatTabPage1();
    creatTabPage2();
    creatTabPage3();
    creatTabPage4();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tabWidget);
}

void yuanliaoxiaohaojiagetiaozhengDlg::refresh()
{

}

void yuanliaoxiaohaojiagetiaozhengDlg::keyPressEvent(QKeyEvent *event)
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

void yuanliaoxiaohaojiagetiaozhengDlg::creatTabPage1()
{
    QLabel *label1 = new QLabel(tr("生产日期"),this);
    label1->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label2 = new QLabel(tr("--"),this);
    label2->setAlignment(Qt::AlignCenter);
    QLabel *label3 = new QLabel(tr("原料名称"),this);
    label3->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label4 = new QLabel(tr("新价格"),this);
    label4->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label5 = new QLabel(tr("元/公斤"),this);
    label5->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label6 = new QLabel(tr("调整人"),this);
    label6->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    lineEdit1 = new QLineEdit(this);
    lineEdit2 = new QLineEdit(this);
    comBox1 = new QComboBox(this);
    comBox2 = new QComboBox(this);
    comBox3 = new QComboBox(this);
    checkBox1 = new QCheckBox(tr("厂地"),this);
    checkBox2 = new QCheckBox(tr("客户名称"),this);
    datetimeEdit1 = new QDateTimeEdit(QDateTime::currentDateTime(),this);
    datetimeEdit1->setCalendarPopup(true);
    datetimeEdit2 = new QDateTimeEdit(QDateTime::currentDateTime(),this);
    datetimeEdit2->setCalendarPopup(true);
    Btn1 = new QPushButton(tr("消耗记录查询"),this);
    Btn1->setFixedWidth(300);
    Btn2 = new QPushButton(tr("价格调整"),this);
    Btn2->setFixedWidth(150);
    Btn3 = new QPushButton(tr("导出"),this);
    Btn3->setFixedWidth(150);
    view = new QTableView(this);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label1,0,0);
    layout->addWidget(datetimeEdit1,0,1);
    layout->addWidget(label2,0,2);
    layout->addWidget(datetimeEdit2,0,3,1,2);
    layout->addWidget(checkBox1,0,5);
    layout->addWidget(comBox1,0,6);
    layout->addWidget(checkBox2,0,7);
    layout->addWidget(comBox2,0,8);
    layout->addWidget(label3,1,0);
    layout->addWidget(comBox3,1,1);
    layout->addWidget(label4,1,2);
    layout->addWidget(lineEdit1,1,3);
    layout->addWidget(label5,1,4);
    layout->addWidget(label6,1,5);
    layout->addWidget(lineEdit2,1,6);
    layout->setColumnStretch(0,0);
    layout->setColumnStretch(1,1);
    layout->setColumnStretch(2,0);
    layout->setColumnStretch(3,1);
    layout->setColumnStretch(4,0);
    layout->setColumnStretch(5,0);
    layout->setColumnStretch(6,1);
    layout->setColumnStretch(7,0);
    layout->setColumnStretch(8,1);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addSpacing(500);
    hlayout->addWidget(Btn2);
    hlayout->addWidget(Btn3);
    hlayout->addSpacing(500);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(layout);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(Btn1);
    vlayout->addWidget(view);

    yuanliaoxiaohaojiagetiaozheng->setLayout(vlayout);
    tabWidget->addTab(yuanliaoxiaohaojiagetiaozheng,tr("原料消耗价格调整"));
}

void yuanliaoxiaohaojiagetiaozhengDlg::creatTabPage2()
{
    QLabel *label1 = new QLabel(tr("原料名称"),this);
    label1->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    twocomBox = new QComboBox(this);
    twoBtn1 = new QPushButton(tr("筛选"),this);
    twoBtn2 = new QPushButton(tr("全部"),this);
    twoBtn3 = new QPushButton(tr("导出"),this);
    twoview = new QTableView(this);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(label1,0);
    hlayout->addWidget(twocomBox,2);
    hlayout->addWidget(twoBtn1,1);
    hlayout->addWidget(twoBtn2,1);
    hlayout->addWidget(twoBtn3,1);
    hlayout->addSpacing(500);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(twoview);

    tiaozhengjiluchaxun->setLayout(vlayout);
    tabWidget->addTab(tiaozhengjiluchaxun,tr("调整记录查询"));
}

void yuanliaoxiaohaojiagetiaozhengDlg::creatTabPage3()
{
    QLabel *label1 = new QLabel(tr("生产日期"),this);
    label1->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label2 = new QLabel(tr("--"),this);
    label2->setAlignment(Qt::AlignCenter);
    QLabel *label3 = new QLabel(tr("新原料名称"),this);
    label3->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label4 = new QLabel(tr("原料名称"),this);
    label4->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label5 = new QLabel(tr("调整数量"),this);
    label5->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    QLabel *label6 = new QLabel(tr("调整人"),this);
    label6->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    threedatetimeEdit1 = new QDateTimeEdit(QDateTime::currentDateTime(),this);
    threedatetimeEdit1->setCalendarPopup(true);
    threedatetimeEdit2 = new QDateTimeEdit(QDateTime::currentDateTime(),this);
    threedatetimeEdit2->setCalendarPopup(true);
    threecheckBox1 = new QCheckBox(tr("厂地"),this);
    threecheckBox2 = new QCheckBox(tr("产品"),this);
    threecheckBox3 = new QCheckBox(tr("客户名称"),this);
    threecheckBox4 = new QCheckBox(tr("工程名称"),this);
    threecomBox1 = new QComboBox(this);
    threecomBox2 = new QComboBox(this);
    threecomBox3 = new QComboBox(this);
    threecomBox4 = new QComboBox(this);
    threecomBox5 = new QComboBox(this);
    threecomBox6 = new QComboBox(this);
    threelineEdit1 = new QLineEdit(this);
    threelineEdit2 = new QLineEdit(this);
    threeBtn1 = new QPushButton(tr("原料名称调整"),this);
    threeBtn1->setFixedWidth(150);
    threeBtn2 = new QPushButton(tr("导出"),this);
    threeBtn2->setFixedWidth(150);
    threeBtn3 = new QPushButton(tr("消耗记录查询"),this);
    threeBtn3->setFixedWidth(300);
    threeview = new QTableView(this);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label1,0,0);
    layout->addWidget(threedatetimeEdit1,0,1);
    layout->addWidget(label2,0,2);
    layout->addWidget(threedatetimeEdit2,0,3);
    layout->addWidget(threecheckBox1,0,4);
    layout->addWidget(threecomBox1,0,5);
    layout->addWidget(label3,0,6);
    layout->addWidget(threecomBox2,0,7);
    layout->addWidget(label4,1,0);
    layout->addWidget(threecomBox3,1,1,1,3);
    layout->addWidget(threecheckBox2,1,4);
    layout->addWidget(threecomBox4,1,5);
    layout->addWidget(label5,1,6);
    layout->addWidget(threelineEdit1,1,7);
    layout->addWidget(threecheckBox3,2,0);
    layout->addWidget(threecomBox5,2,1,1,3);
    layout->addWidget(label6,2,4);
    layout->addWidget(threelineEdit2,2,5);
    layout->addWidget(threecheckBox4,3,0);
    layout->addWidget(threecomBox6,3,1,1,3);
    layout->setColumnStretch(0,0);
    layout->setColumnStretch(1,1);
    layout->setColumnStretch(2,0);
    layout->setColumnStretch(3,1);
    layout->setColumnStretch(4,0);
    layout->setColumnStretch(5,1);
    layout->setColumnStretch(6,0);
    layout->setColumnStretch(7,1);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addSpacing(500);
    hlayout->addWidget(threeBtn1);
    hlayout->addWidget(threeBtn2);
    hlayout->addSpacing(500);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(layout);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(threeBtn3);
    vlayout->addWidget(threeview);

    yuanliaomingchengtiaozheng->setLayout(vlayout);
    tabWidget->addTab(yuanliaomingchengtiaozheng,tr("原料名称调整"));
}

void yuanliaoxiaohaojiagetiaozhengDlg::creatTabPage4()
{
    QLabel *label1 = new QLabel(tr("新原料名称"),this);
    label1->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    fourcomBox = new QComboBox(this);
    fourBtn1 = new QPushButton(tr("筛选"),this);
    fourBtn2 = new QPushButton(tr("全部"),this);
    fourBtn3 = new QPushButton(tr("导出"),this);
    fourview = new QTableView(this);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(label1,0);
    hlayout->addWidget(fourcomBox,2);
    hlayout->addWidget(fourBtn1,1);
    hlayout->addWidget(fourBtn2,1);
    hlayout->addWidget(fourBtn3,1);
    hlayout->addSpacing(500);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(fourview);

    mingchengtiaozhengjilu->setLayout(vlayout);
    tabWidget->addTab(mingchengtiaozhengjilu,tr("名称调整记录"));
}
