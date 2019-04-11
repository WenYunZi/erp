#ifndef MYCOMPLETERLINEEDIT_H
#define MYCOMPLETERLINEEDIT_H

#include <QLineEdit>
#include <QStringList>
#include <QFile>
#include <QTextCodec>
#include <QDebug>
#include <QKeyEvent>
#include <QListView>
#include <QStringListModel>
#include "mymysql.h"

class QListView;
class QStringListModel;
class QModelIndex;


class MyCompleterLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit MyCompleterLineEdit(QLineEdit *lineedit1,QLineEdit *lineedit2,QWidget *parent = 0);

signals:

public slots:
    void setCompleter(const QString &text); // 动态的显示完成列表
    void completeText(const QModelIndex &index); // 点击完成列表中的项，使用此项自动完成输入的单词
protected:
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void focusOutEvent(QFocusEvent *event);
    virtual void focusInEvent(QFocusEvent *event);
private slots:
    void replyMoveSignal();
private:
    QStringList words; // 整个完成列表的车牌
    QListView *listView; // 完成列表
    QStringListModel *model; // 完成列表的model
    QLineEdit *lineedit1;
    QLineEdit *lineedit2;
};

#endif // MYCOMPLETERLINEEDIT_H


