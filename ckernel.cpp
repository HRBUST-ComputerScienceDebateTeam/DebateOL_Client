#include "ckernel.h"
#include "./config.h"
#include "./pkg/JsonChange/jsonchange.h"
#include "./pkg/JWT/jwt.h"
#include "./pkg/web/web.h"
#include "./pkg/Openssl/openssl.h"
#include"qDebug"
#include<QInputDialog>

#define NetPackMap(a) m_netPackMap[a - DEF_PACK_BASE]


Ckernel::Ckernel(QObject *parent)
    : QObject{parent}
{
    //m_room = new Room_main;
    We_Chat =new WeChatDialog;
    m_pLoginDlg =new LoginDialog;
    connect(m_pLoginDlg,SIGNAL(SIG_loginCommit(QString,QString))
            ,this,SLOT(slot_loginCommit(QString,QString)));
    connect(m_pLoginDlg,SIGNAL(SIG_registerCommit(QString,QString))
            ,this,SLOT(slot_registerCommit(QString,QString)));

    connect(We_Chat,SIGNAL(SIG_createRoom())
            ,this,SLOT(slot_createRoom()));
    connect(We_Chat,SIGNAL(SIG_joinRoom())
            ,this,SLOT(slot_joinRoom()));

//    connect(m_room , SIGNAL(SIG_close())
//            ,this,SLOT(slot_destory()));
    connect(We_Chat , SIGNAL(SIG_closechat())
           ,this,SLOT(slot_destorychat()));
    //m_pVideoRead = new VideoRead;
    m_pLoginDlg->show();
    //m_room->show();
    //We_Chat->show();

}
//个人信息
int    Ckernel::myuid                    =-1;
string Ckernel::my_jwt_token             ="";
string Ckernel::my_refresh_jwt_token     ="";


//回收
void Ckernel::slot_destory()
{
    qDebug()<<__func__;
    if(m_room)
    {
        delete m_room;
        m_room = NULL;
    }  
}

void Ckernel::slot_destorychat()
{
    qDebug()<<__func__;
    if(We_Chat)
    {
        delete We_Chat;
        We_Chat = NULL;
    }
}

//发送注册
void Ckernel::slot_registerCommit(QString tel, QString pass, QString name)
{
    std::string strTel = tel.toStdString();
    std::string strPass= pass.toStdString();
    std::string strName = name.toStdString();

    User_reg_SendInfo reg_req;

    QTime tm = QTime::currentTime();
    int timid = tm.minute()*60000 + tm.second() * 1000 + tm.msec();

    reg_req.tel=strTel;
    reg_req.passwd=sha256(Base64Encode(strPass));
    reg_req.sendtime =timid;
    reg_req.usernum=strName;
    reg_req.type =User_Reg_SendInfo_TypeId;

    string sendreq = User_reg_SendInfo::Serialization(reg_req);
    //网络请求
    MYNET_KERNEL::Init(this);
    MYNET_KERNEL * netptr = MYNET_KERNEL::getinstance();//获取单例

    netptr->NETPOST(USER_LOGIN_URL ,sendreq , timid  ,  &Ckernel::SIGDEAL_reg );
}
//创建房间
void Ckernel::slot_createRoom()
{
    if(room_id != 0)
    {
        QMessageBox::about(We_Chat,"提示","在房间内，无法创建，先退出");
        return;
    }
    //发命令 创建房间

}
//加入房间
void Ckernel::slot_joinRoom()
{   //判断是否在房间内 m_roomid
    if(room_id != 0)
    {
        QMessageBox::about(We_Chat,"提示","在房间内，无法加入，先退出");
        return;
    }
    QString strRoom = QInputDialog::getText( We_Chat , "加入房间" ,"输入房间号");
    //发命令 加入房间
}


//发送登录
void Ckernel::slot_loginCommit(QString tel, QString pass)
{
    std::string strTel = tel.toStdString();
    std::string strPass = pass.toStdString();
    //下面是封装发送
    User_login_Tel_SendInfo login_req;

    //这个tid是 分钟*60000 + 秒*1000+ 毫秒的
    QTime tm = QTime::currentTime();
    int timid = tm.minute()*60000 + tm.second() * 1000 + tm.msec();

    login_req.sendtime = timid;
    login_req.passwd = sha256(Base64Encode(strPass));
    login_req.tel = strTel;
    login_req.type = User_LoginTel_SendInfo_TypeId;
    string sendreq = User_login_Tel_SendInfo::Serialization(login_req);
    //网络请求
    MYNET_KERNEL::Init(this);
    MYNET_KERNEL * netptr = MYNET_KERNEL::getinstance();//获取单例

    netptr->NETPOST(USER_LOGIN_URL ,sendreq , timid  ,  &Ckernel::SIGDEAL_login );
}

void * Ckernel::SIGDEAL_reg(void * arg)
{
    User_reg_RecvInfo * recvinfo = (User_reg_RecvInfo *) arg;
    if(recvinfo->status != 200)
    {
        switch (recvinfo->status) {
        case User_Reg_Havethisnum:
            QMessageBox::about(m_pLoginDlg,"提示","用户名已经被使用");
            //qDebug()<<"账户已经被注册";
            break;
        case User_Reg_Havethistel:
            QMessageBox::about(m_pLoginDlg,"提示","手机号已经被注册");
            //qDebug()<<"手机号已经被注册";
            break;
        default:
            cout << " not find status" <<endl;
            break;
        }
    }
    //存到本地
    //个人信息
}

void * Ckernel::SIGDEAL_login (void * arg){
    //强转
    User_login_RecvInfo * recvinfo = (User_login_RecvInfo *) arg;
    if(recvinfo->status != 200 ){
        switch(recvinfo->status){
            case USER_ERR_REQINFO://请求体有误
                return nullptr;
                break;
            case USER_LOGIN_ERRINFO://登陆失败 - 账号密码不对应
                //调用提醒函数
                //qDebug()<<"err login info";
                QMessageBox::about(m_pLoginDlg,"提示","密码或账号错误");
                return nullptr;
            default:
                cout << " not find status" <<endl;
                break;
            }
    }
    //存到本地
    //个人信息
    Ckernel::myuid                    = stoi(((JWT_token::jwt_decode(recvinfo->jwt_token)).getpayloadmap())["aud"]) ;
    Ckernel::my_jwt_token             = recvinfo->jwt_token;
    Ckernel::my_refresh_jwt_token     = recvinfo->refresh_jwt_token;
    cout << "SIGDEAL_login" << " OK" <<endl;

    m_pLoginDlg->hide();
    We_Chat->show();
}
    //测试
//    cout << "Ckernel::myuid                   " <<     Ckernel::myuid                    <<endl;
//    cout << "Ckernel::my_jwt_token            " <<     Ckernel::my_jwt_token             <<endl;
//    cout << "Ckernel::my_refresh_jwt_token    " <<     Ckernel::my_refresh_jwt_token     <<endl;

//>>>>>>> fed663280e59afc461ecebd74b16f35e1f8a526e

