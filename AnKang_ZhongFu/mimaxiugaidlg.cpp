#include "mimaxiugaidlg.h"

extern mymysql db;

mimaxiugaiDlg::mimaxiugaiDlg(QWidget *parent) :
    QDialog(parent)
{
    QLabel *label1  = new QLabel(tr("用户名"),this);
    label1->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label2  = new QLabel(tr("原密码"),this);
    label2->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label3  = new QLabel(tr("新密码"),this);
    label3->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    QLabel *label4  = new QLabel(tr("确认新密码"),this);
    label4->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

    lineEdit1 = new QLineEdit(this);
    lineEdit1->setEchoMode(QLineEdit::Password);//设置为密码框;
    lineEdit2 = new QLineEdit(this);
    lineEdit2->setEchoMode(QLineEdit::Password);//设置为密码框
    lineEdit3 = new QLineEdit(this);
    lineEdit3->setEchoMode(QLineEdit::Password);//设置为密码框

    combo1 = new QComboBox(this);
    const char *mySQL = "select UserName from UserManagement;";
    db.sql_fillComboBoxItem(mySQL,combo1);

    Btn = new QPushButton(tr("修改"),this);
    connect(Btn,SIGNAL(clicked()),this,SLOT(on_updateAction()));

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(label1,0,0);
    layout->addWidget(combo1,0,1);
    layout->addWidget(label2,1,0);
    layout->addWidget(lineEdit1,1,1);
    layout->addWidget(label3,2,0);
    layout->addWidget(lineEdit2,2,1);
    layout->addWidget(label4,3,0);
    layout->addWidget(lineEdit3,3,1);
    layout->addWidget(Btn,4,1);
    layout->setColumnStretch(0,0);
    layout->setColumnStretch(1,1);

    QGroupBox *box = new QGroupBox(this);
    box->setTitle(tr("密码修改"));
    box->setFixedSize(300,400);
    box->setLayout(layout);
    box->setGeometry(50,30,300,400);
}

void mimaxiugaiDlg::keyPressEvent(QKeyEvent *event)
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

void mimaxiugaiDlg::on_updateAction()
{
    if(lineEdit1->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入原密码"),0,0,0);
        return;
    }
    if(lineEdit2->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请输入新密码"),0,0,0);
        return;
    }
    if(lineEdit3->text().isEmpty()){
        QMessageBox::information(this,tr("提示信息"),tr("请再次输入新密码"),0,0,0);
        return;
    }
    if(lineEdit2->text() != lineEdit3->text()){
        QMessageBox::information(this,tr("错误"),tr("两次密码输入不一致，请重新输入"),0,0,0);
        return;
    }
    QString SQL1 = QString("select * from UserManagement where UserName='%1' and Password1='%2';").arg(combo1->currentText(),lineEdit1->text());
    int res = db.row_count(SQL1);
    if(res == 0){
        QMessageBox::information(this,tr("错误"),tr("原密码输入错误，请重新输入"),0,0,0);
        return;
    }
    QString SQL = QString("update UserManagement set Password1='%1',Password2='%2' where UserName='%3';")
            .arg(lineEdit2->text(),lineEdit3->text(),combo1->currentText());
    int ret = db.sql_exec(SQL.toStdString().data());
    if(ret == 0){
        lineEdit1->clear();
        lineEdit2->clear();
        lineEdit3->clear();
        QMessageBox::information(this,tr("提示信息"),tr("密码修改成功"),0,0,0);
    }
}
