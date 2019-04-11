#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QMouseEvent>

class myLabel : public QLabel
{
    Q_OBJECT
public:
    explicit myLabel(int ID, QWidget *parent = 0);

private:
    int ID;

signals:
    void isDoubleClick(int ID);

public slots:

private:
    void mouseDoubleClickEvent(QMouseEvent *event);

};

#endif // MYLABEL_H
