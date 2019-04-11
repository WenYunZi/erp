#include "mycombobox.h"

myComboBox::myComboBox(const char *sql,QWidget *parent) :
    QComboBox(parent)   //, words(words)
{
    SQL = sql;
    listView = new QListView(this);//用于显示下拉列表
    model = new QStringListModel(this);
    listView->setWindowFlags(Qt::ToolTip);//设置下拉列表的样式
    connect(this, SIGNAL(editTextChanged(QString)), this, SLOT(setCompleter(const QString &)));
    connect(listView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(completeText(const QModelIndex &)));
}

myComboBox::myComboBox(QWidget *parent) :
    QComboBox(parent)
{
    this->setEditable(true);
    listView = new QListView(this);//用于显示下拉列表
    model = new QStringListModel(this);
    listView->setWindowFlags(Qt::ToolTip);//设置下拉列表的样式
    connect(this, SIGNAL(editTextChanged(QString)), this, SLOT(setCompleter(const QString &)));
    connect(listView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(completeText(const QModelIndex &)));
}

void myComboBox::setSQL(const char *sql)
{
    this->SQL = sql;
}

void myComboBox::setCompleter(const QString &text)
{
    if (text.isEmpty()){//没有输入内容的情况
        listView->hide();
        return;
    }
    if ((text.length() > 1) && (!listView->isHidden())){
        return;
    }
    // 如果完整的完成列表中的某个单词包含输入的文本，则加入要显示的完成列表串中
    QStringList sl;
    foreach(QString word, words){
        //填充模式一
        if (word.contains(text,Qt::CaseInsensitive)){//只要包含该输入内容就显示，大小写不敏感
            sl << word;
        }
        //填充模式二
//        if(word.indexOf(text,0,Qt::CaseInsensitive)==0)//必需与句首内容相同
//            sl<<word;
    }
    model->setStringList(sl);
    listView->setModel(model);
    if(model->rowCount() == 0){
        return;
    }

    //设置列表的显示大小

    if(sl.size() <= 10){
        listView->setFixedSize(width(),sl.size() * 20 + 4);
    }
    else{
        listView->setFixedSize(width(),204);
    }
    listView->setMinimumWidth(width());
    listView->setMaximumWidth(width());

    //设置列表的显示位置
    QPoint p(0, this->height());
    int x = mapToGlobal(p).x();
    int y = mapToGlobal(p).y();
    listView->move(x,y);
    if(sl.size() == 1){
        if(sl.at(0) == this->currentText()){
            return;
        }
    }
    listView->show();
}

void myComboBox::completeText(const QModelIndex &index)
{
    QString text = index.data().toString();

    this->setCurrentText(text);

    listView->hide();
}


void myComboBox::keyPressEvent(QKeyEvent *event)
{
    if(!listView->isHidden()){
        int key = event->key();
        int count = listView->model()->rowCount();
        QModelIndex currentIndex = listView->currentIndex();
        if(Qt::Key_Down == key){
            // 按向下方向键时
            int row = currentIndex.row() + 1;
            if (row >= count){
                row = 0;
            }
            QModelIndex index = listView->model()->index(row, 0);
            listView->setCurrentIndex(index);
        }else if(Qt::Key_Up == key){
            // 按向上方向键时
            int row = currentIndex.row() - 1;
            if (row < 0){
                row = count - 1;
            }
            QModelIndex index = listView->model()->index(row, 0);
            listView->setCurrentIndex(index);
        }else if(Qt::Key_Escape == key){
            // 按下Esc键时隐藏完成列表
            listView->hide();
        }else if(Qt::Key_Enter == key || Qt::Key_Return == key){
            // 按下回车键时，使用完成列表中选中的项，并隐藏完成列表
            if (currentIndex.isValid()){
                QString text = listView->currentIndex().data().toString();
                setCurrentText(text);
            }
            listView->hide();
        }else{
           // 其他情况，隐藏完成列表，并使用QLineEdit的键盘按下事件
            listView->hide();
            QComboBox::keyPressEvent(event);
        }
    }else{
        QComboBox::keyPressEvent(event);
    }
}

void myComboBox::focusOutEvent(QFocusEvent *event)
{
    words.clear();
    listView->hide();//当输入行不是焦点时，隐藏自动补全的下拉列表
    QComboBox::focusOutEvent(event);
}

void myComboBox::focusInEvent(QFocusEvent *event)
{
    words.clear();
    int itemNum = this->count();
    for(int i = 0;i<itemNum;i++){
        words.append(this->itemText(i));
    }

    QComboBox::focusInEvent(event);
}

void myComboBox::replyMoveSignal()
{
    listView->hide();//当输入行不是焦点时，隐藏自动补全的下拉列表
}
