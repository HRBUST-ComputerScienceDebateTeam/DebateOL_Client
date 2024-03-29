#include "logindialog.h"
#include "ui_logindialog.h"
#include"QMessageBox"
#include <QRegularExpressionValidator>


LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    this->setWindowTitle("登录你的账号");
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}
//提交登录信息
void LoginDialog::on_commit_clicked()
{
    QString strTel = ui->le_tel->text();
    QString strPassword =ui->le_password->text();


    //校验
    QString temTel =strTel;
    QString temPass =strPassword;
    if(temTel.remove(" ").isEmpty()||temPass.remove(" ").isEmpty())
    {
        QMessageBox::about(this,"提示","手机号密码不能为空格");
        return;
    }
    //手机号
    //QRegularExpression reg("^1[3-8][0-9]\{6,9\}$");
    //reg.match(temTel);
    //密码
    Q_EMIT SIG_loginCommit(strTel,strPassword);
}

//清空注册信息
void LoginDialog::on_clear_3_clicked()
{
    ui->le_password_register->setText("");
    ui->le_password_cofirm->setText("");
    ui->le_tel_register->setText("");
    ui->le_noname->setText("");
}

//提交注册信息
void LoginDialog::on_commit_3_clicked()
{
    QString strTel = ui->le_tel_register->text();
    QString strPassword =ui->le_password_register->text();
    QString strConfirm = ui->le_password_cofirm->text();
    QString strName =ui->le_noname->text();

    QString temTel =strTel;
    QString temPass =strPassword;
    QString temName =strName;
    if(temTel.remove(" ").isEmpty()||temPass.remove(" ").isEmpty()||
        temName.remove(" ").isEmpty())
    {
        QMessageBox::about(this,"提示","手机号,密码,账号不能为空格");
        return;
    }
    if(strPassword != strConfirm)
    {
        QMessageBox::about(this,"提示","密码不一致!");
        return;
    }
    Q_EMIT SIG_registerCommit(strTel,strPassword,strName);
}

//清空登录信息
void LoginDialog::on_clear_clicked()
{
    ui->le_password->setText("");
    ui->le_tel->setText("");
}

