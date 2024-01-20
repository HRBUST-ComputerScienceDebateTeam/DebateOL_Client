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
