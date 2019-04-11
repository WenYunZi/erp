#ifndef MYCOMBOBOX_H
#define MYCOMBOBOX_H

#include <QComboBox>
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

class myComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit myComboBox(const char *sql, QWidget *parent = 0);
    explicit myComboBox(QWidget *parent = 0);

public:
    void setSQL(const char *sql);

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
    QString SQL;
    QStringList words; // 整个完成列表的车牌
    QListView *listView; // 完成列表
    QStringListModel *model; // 完成列表的model
};

#endif // MYCOMBOBOX_H
