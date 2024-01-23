#include "wechatdialog.h"
#include "qevent.h"
#include "ui_wechatdialog.h"
#include<QMessageBox>
#include "../pkg/QT_Multiple_info/QT_Multiple_info.h"
#include "../pkg/web/web.h"
#include "../pkg/thrift_json/thrift_json_config.h"
#include <QInputDialog>
#include <QFormLayout >
#include <QSpinBox>
#include <QDialogButtonBox>
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
    /*弹出一个小界面 去设定相关信息 之后把信息返回回来 之后调用创建 提示结果
        需要信息：
        struct Room_Create_SendInfo {
            1:i32 type,
            2:string jwt_token,
            3:i32 sendtime,
            4:string Roomnum,
            5:i32 Islocking,
            6:string Roomname,
            7:string passwd,
            8:i32 Debate_pos
        }
    */
    //获取信息
    std::map<std::string,std::string> mp;
    mp["Roomnum"] = "";
    mp["Islocking"] = "";
    mp["Roomname"] = "";
    mp["passwd"] = "";
    mp["Debate_pos"] = "";
    std::string morinfo = "请输入创建房间需要的参数";
    My_Multiple_Info * myMinfo= new My_Multiple_Info(this , MapToJsonstring(mp) , morinfo);
    std::string  s = myMinfo->run();
    delete myMinfo;
    if(s == "") return;
    Q_EMIT SIG_createRoom(s);
}


void WeChatDialog::on_pb_join_clicked()
{
    //TODO查询是否有密码 - 阻塞

    //获取信息
    std::map<std::string,std::string> mp;
    mp["roomnum"] = "";
    mp["Debate_pos"] = "";
    mp["passwd"] = "";
    std::string morinfo = "请输入加入房间信息 如果没有密码请忽略";
    My_Multiple_Info * myMinfo= new My_Multiple_Info(this , MapToJsonstring(mp) , morinfo);
    std::string  s = myMinfo->run();
    delete myMinfo;

    Q_EMIT SIG_joinRoom(s);
}

