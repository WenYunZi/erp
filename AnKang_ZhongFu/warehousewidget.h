#ifndef WAREHOUSEWIDGET_H
#define WAREHOUSEWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QFont>
#include <QRect>
#include <QDebug>
#include <QPainter>
#include <QPaintEvent>
#include <QSize>

class WarehouseWidget : public QWidget
{
    Q_OBJECT
public:
    WarehouseWidget(QWidget *parent);
    //设置仓位外壁的宽
    void setWarehouseWidth(int width);
    //设置仓位外边的颜色
    void setWarehouseColor(QColor color);
    //设置原材料的颜色
    void setMaterialColor(QColor color);
    //设置文本
    void setText(QString cangwei,QString yuanliao,QString shengliao);
    //设置最终进度
    void setWarehouseProgre(int progre);
    //设置当前进度
    void setProgre(int progre);
    //设置仓位所属生产线
    void setUnit(QString unit);
    ~WarehouseWidget();
protected:
    //重绘事件
    void paintEvent(QPaintEvent *);
private:
    //当前进度
    int m_nNowProgres;
    //设置仓位外壁的宽
    int m_nWarehouseWidth;
    //原材料的颜色
    QColor m_MaterialColor;
    //仓位外壁颜色
    QColor  m_WarehouseColor;
    //画仓位
    void drawWarehouse(QPainter* painter);
    //定时器
    QTimer* m_updateTimer;//定时器时间
    bool isFirstRotate;
    //文本
    QString text;
    //最终进度
    int NowProgres;
signals:
    void onProgres(int);
private slots:
    //自定义槽，更新角度旋转
    void UpdateView();
public:
    QString Unit;
};

#endif // WAREHOUSEWIDGET_H
