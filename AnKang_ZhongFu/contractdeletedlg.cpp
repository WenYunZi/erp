#include "contractdeletedlg.h"

extern QString userName;
extern mymysql db;

ContractDeleteDlg::ContractDeleteDlg(QWidget *parent) :
    QDialog(parent)
{
    this->setWindowTitle(tr("删除确认"));
    isOnOkBtn = false;

    QLabel *warningLabel = new QLabel(tr("该操作会删除跟合同相关的所有的工程，确实要删除？"),this);

    QLabel *PassWordLabel = new QLabel(tr("密码"),this);

    PassWordLineEdit = new QLineEdit(this);
    PassWordLineEdit->setEchoMode(QLineEdit::Password);//设置为密码框

    OkBtn = new QPushButton(tr("确认"),this);
    connect(OkBtn,SIGNAL(clicked()),this,SLOT(on_OkBtn()));

    CancelBtn = new QPushButton(tr("取消"),this);
    connect(CancelBtn,SIGNAL(clicked()),this,SLOT(on_CancelBtn()));

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(warningLabel,0,0,1,2);
    gridLayout->addWidget(PassWordLabel,1,0);
    gridLayout->addWidget(PassWordLineEdit,1,1);

    QHBoxLayout *hBtnLayout = new QHBoxLayout;
    hBtnLayout->addWidget(OkBtn,1);
    hBtnLayout->addWidget(CancelBtn,1);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addLayout(gridLayout);
    vlayout->addLayout(hBtnLayout);
}

void ContractDeleteDlg::on_OkBtn()
{
    QString searchSQL = QString("select 1 from UserManagement where RealName='%1' and Password1='%2'").arg(userName,PassWordLineEdit->text());
    if(db.row_count(searchSQL) != 1){
        return;
    }

    isOnOkBtn = true;
    this->close();
}

void ContractDeleteDlg::on_CancelBtn()
{
    isOnOkBtn = false;
    this->close();
}
