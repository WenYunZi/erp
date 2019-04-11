#include "warehousewidget.h"

WarehouseWidget::WarehouseWidget(QWidget *parent)
    : QWidget(parent)

{
    //无窗体
    this->setWindowFlags(Qt::FramelessWindowHint);
    //背景透明
    this->setAttribute(Qt::WA_TranslucentBackground);

    NowProgres = 0;
    m_nNowProgres = 0;
    m_WarehouseColor = QColor(7,4,127,255);
    m_MaterialColor = QColor(224,143,36,255);
    m_nWarehouseWidth = 4;

    m_updateTimer = new QTimer(this);
    //间隔，微妙微单位。
    m_updateTimer->setInterval(2);
    connect(m_updateTimer,SIGNAL(timeout()),this,SLOT(UpdateView()));
    //启动定时器
    m_updateTimer->start();
}
WarehouseWidget::~WarehouseWidget()
{
    m_updateTimer->stop();
}
//重绘事件
void WarehouseWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing|QPainter::HighQualityAntialiasing);//设置反锯齿
    drawWarehouse(&painter);//画仓位
    event->accept();
}
//画仓位和原料
void WarehouseWidget::drawWarehouse(QPainter *painter)
{
    painter->save();
    //设置坐标原点在0,0点上
    painter->translate(0,0);
    painter->setPen(QPen(m_WarehouseColor,m_nWarehouseWidth,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    //绘制仓位图形
    QPainterPath WarehousePath;
    WarehousePath.moveTo(5,5);
    WarehousePath.lineTo(width()-5,5);
    WarehousePath.lineTo(width()-5,height()*0.7);
    WarehousePath.lineTo(width()*0.75,height()-5);
    WarehousePath.lineTo(width()*0.25,height()-5);
    WarehousePath.lineTo(5,height()*0.7);
    WarehousePath.lineTo(5,5);
    painter->drawPath(WarehousePath);
    painter->setPen(Qt::NoPen);

    qreal Height=((float)(m_nNowProgres/100.0)*(height()-20));
    emit onProgres(m_nNowProgres);
    painter->setBrush(QBrush(m_MaterialColor,Qt::SolidPattern));//设置画刷形式
    if(m_nNowProgres >= 30){
        QPoint polygon[6];
        polygon[0]=QPoint(width()*0.75-3,height()-10);
        polygon[1]=QPoint(width()*0.25+3,height()-10);
        polygon[2]=QPoint(10,height()*0.7-3);
        polygon[3]=QPoint(10,height()-10-Height);
        polygon[4]=QPoint(width()-10,height()-10-Height);
        polygon[5]=QPoint(width()-10,height()*0.7-3);
        painter->drawPolygon(polygon,6);
    }else{
        QPoint polygon[4];
        polygon[0]=QPoint(width()*0.75-3,height()-10);
        polygon[1]=QPoint(width()*0.25+3,height()-10);
        polygon[2]=QPoint((-Height/(7-0.3*height()))*(7-0.25*width())+0.25*width()+3,height()-10-Height);
        polygon[3]=QPoint((-Height/(0.3*height()-7))*(7-0.25*width())+0.75*width()-3,height()-10-Height);
        painter->drawPolygon(polygon,4);
    }
    painter->setPen(QPen(QColor(0,0,0,255),m_nWarehouseWidth,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
    QRect rec(10,10,width()-20,height()*0.7);
//    QFont ft;
//    ft.setPixelSize(10);
//    painter->setFont(ft);
    painter->drawText(rec,Qt::AlignCenter,text);
    painter->setPen(Qt::NoPen);
    painter->restore();
}
//更新画面
void WarehouseWidget::UpdateView()
{
    if(m_nNowProgres<NowProgres){
        m_nNowProgres++;
    }else{
        m_updateTimer->stop();
    }
    //刷新控件，会调用paintEvent函数
    update();
}
//设置仓位颜色
void WarehouseWidget::setWarehouseColor(QColor color)
{
    this->m_WarehouseColor = color;
}
//设置原材料颜色
void WarehouseWidget::setMaterialColor(QColor color)
{
    this->m_MaterialColor = color;
}
//设置文本
void WarehouseWidget::setText(QString cangwei,QString yuanliao,QString shengliao)
{
    text.clear();
    text.append(tr("仓位："));
    text.append(cangwei);
    text.append(tr("\n"));
    text.append(tr("原料："));
    text.append(yuanliao);
    text.append(tr("\n"));
    text.append(tr("库存："));
    text.append(shengliao);
    text.append(tr("\n"));
    text.append(QString::number(NowProgres));
    text.append("%");
}
//设置仓位的宽度
void WarehouseWidget::setWarehouseWidth(int width)
{
    this->m_nWarehouseWidth = width;
}
//设置最终进度
void WarehouseWidget::setWarehouseProgre(int progre)
{
    this->NowProgres = progre;
    if (progre>100)
    {
        this->NowProgres = 100;
    }
}
//设置当前进度
void WarehouseWidget::setProgre(int progre)
{
    this->m_nNowProgres = progre;
    update();
}

void WarehouseWidget::setUnit(QString unit)
{
    this->Unit = unit;
}
