#include "wechatdialog.h"
#include "qevent.h"
#include "ui_wechatdialog.h"
#include<QMessageBox>

WeChatDialog::WeChatDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WeChatDialog)
{
    ui->setupUi(this);
}

WeChatDialog::~WeChatDialog()
{
    delete ui;
}

void WeChatDialog::closeEvent(QCloseEvent *event)
{
    if(QMessageBox::question(this,"提示","是否退出") == QMessageBox::Yes)
    {
        Q_EMIT SIG_closechat();
        event->accept();
    }
    else
    {
        event->ignore();
    }

}
//设置名字，头像，个性签名
void WeChatDialog::setInfo(QString name, QString name_style, int icon)
{
    ui->lb_name->setText(name);
    ui->lb_style->setText(name_style);
}

void WeChatDialog::on_pb_create_clicked()
{
    Q_EMIT SIG_createRoom();
}


void WeChatDialog::on_pb_join_clicked()
{
    Q_EMIT SIG_joinRoom();
}

