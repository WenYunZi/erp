#ifndef TITLEWIDGET_H
#define TITLEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QToolButton>
#include <QHBoxLayout>
#include <QPainter>
#include <QLinearGradient>
#include <QIcon>

class titleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit titleWidget(QWidget *parent = 0);

private:
    QLabel *titleText;
    QToolButton *btnClose;

signals:
    void myClose();

public:
    void paintEvent(QPaintEvent *);
    void setTitleText(QString title);

};

#endif // TITLEWIDGET_H
