#include "ckernel.h"
#include "./config.h"
#include "./pkg/JsonChange/jsonchange.h"
#include "./pkg/JWT/jwt.h"
#include "./pkg/web/web.h"
#include "./pkg/Openssl/openssl.h"
#include"qDebug"
#include<QInputDialog>
#include <QMessageBox>

#define NetPackMap(a) m_netPackMap[a - DEF_PACK_BASE]


Ckernel::Ckernel(QObject *parent)
    : QObject{parent}
{
    m_room = nullptr;
    We_Chat =new WeChatDialog;
    m_pLoginDlg =new LoginDialog;
    connect(m_pLoginDlg,SIGNAL(SIG_loginCommit(QString,QString))
            ,this,SLOT(slot_loginCommit(QString,QString)));
    connect(m_pLoginDlg,SIGNAL(SIG_registerCommit(QString,QString,QString))
            ,this,SLOT(slot_registerCommit(QString,QString,QString)));

    connect(We_Chat,SIGNAL(SIG_createRoom(std::string))
            ,this,SLOT(slot_createRoom(std::string)));
    connect(We_Chat,SIGNAL(SIG_joinRoom(std::string))
            ,this,SLOT(slot_joinRoom(std::string)));

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
    //发送下线请求

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
void Ckernel::slot_registerCommit(QString tel, QString pass, QString num)
{
    std::string strTel = tel.toStdString();
    std::string strPass= pass.toStdString();
    std::string strNum = num.toStdString();

    User_reg_SendInfo reg_req;

    QTime tm = QTime::currentTime();
    int timid = tm.minute()*60000 + tm.second() * 1000 + tm.msec();

    reg_req.tel=strTel;
    reg_req.passwd=sha256(Base64Encode(strPass));
    reg_req.sendtime =timid;
    reg_req.usernum=strNum;
    reg_req.type =User_reg_SendInfo_TypeId;

    string sendreq = User_reg_SendInfo::Serialization(reg_req);
    //网络请求
    MYNET_KERNEL::Init(this);
    MYNET_KERNEL * netptr = MYNET_KERNEL::getinstance();//获取单例

    netptr->NETPOST(USER_REG_URL ,sendreq , timid  ,  &Ckernel::SIGDEAL_reg );
}
//创建房间
void Ckernel::slot_createRoom(std::string s)
{
    if(room_id != 0)
    {
        QMessageBox::about(We_Chat,"提示","在房间内，无法创建，先退出");
        return;
    }
    //创建任务 创建房间
    std::map<std::string , std::string>mp1 = JsonstringToMap(s);
    mp1["type"] = to_string(Room_Create_SendInfo_TypeId);
    mp1["jwt_token"] = my_jwt_token;
    //时间
    QTime tm = QTime::currentTime();
    int tid = tm.minute()*60000+tm.second()*1000+tm.msec();
    mp1["sendtime"] =to_string(tid);

    Room_Create_SendInfo sendinfo;
    sendinfo.Roomname = mp1["Roomname"];
    sendinfo.Roomnum = mp1["Roomnum"];
    sendinfo.Debate_pos = stoi(mp1["Debate_pos"]);
    sendinfo.Islocking = stoi(mp1["Islocking"]);
    sendinfo.jwt_token = mp1["jwt_token"];
    sendinfo.passwd = mp1["passwd"];
    sendinfo.sendtime = stoi(mp1["sendtime"]);
    sendinfo.type = stoi(mp1["type"]);

    MYNET_KERNEL::Init(this);
    MYNET_KERNEL * netptr = MYNET_KERNEL::getinstance();//获取单例
    std::string ss = Room_Create_SendInfo::Serialization(sendinfo);
    netptr->NETPOST(Room_Create_URL , ss, tid  ,  &Ckernel::SIGDEAL_CreateRoom );
}

//加入房间
void Ckernel::slot_joinRoom(std::string s)
{   //判断是否在房间内 m_roomid
    if(room_id != 0)
    {
        QMessageBox::about(We_Chat,"提示","在房间内，无法加入，先退出");
        return;
    }
    //QString strRoom = QInputDialog::getText( We_Chat , "加入房间" ,"输入房间号");
    //创建任务 加入房间
    std::map<std::string , std::string>mp1 = JsonstringToMap(s);
    mp1["type"] = to_string(Room_Joinroom_SendInfo_TypeId);
    mp1["jwt_token"] = my_jwt_token;
    //时间
    QTime tm = QTime::currentTime();
    int tid = tm.minute()*60000+tm.second()*1000+tm.msec();
    mp1["sendtime"] =to_string(tid);

    MYNET_KERNEL::Init(this);
    MYNET_KERNEL * netptr = MYNET_KERNEL::getinstance();//获取单例
    Room_Joinroom_SendInfo sendinfo;
    sendinfo.type = stoi(mp1["type"]);
    sendinfo.sendtime = stoi(mp1["sendtime"]);
    sendinfo.jwt_token = mp1["jwt_token"];
    sendinfo.Debate_pos = stoi(mp1["Debate_pos"]);
    sendinfo.roomnum = mp1["roomnum"];
    sendinfo.passwd = mp1["passwd"];

    std::string ss = Room_Joinroom_SendInfo::Serialization(sendinfo);
    netptr->NETPOST(Room_Joinroom_URL ,ss , tid  ,  &Ckernel::SIGDEAL_JoinRoom );
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
    login_req.passwd = sha256(Base64Encode(strPass));//多一层base64 -否则解析错误
    login_req.tel = strTel;
    login_req.type = User_loginTel_SendInfo_TypeId;
    string sendreq = User_login_Tel_SendInfo::Serialization(login_req);
    //网络请求
    MYNET_KERNEL::Init(this);
    MYNET_KERNEL * netptr = MYNET_KERNEL::getinstance();//获取单例

    netptr->NETPOST(USER_LOGINTEL_URL ,sendreq , timid  ,  &Ckernel::SIGDEAL_login );
}


//---回调函数
void * Ckernel::SIGDEAL_reg(void * arg)
{
    User_reg_RecvInfo * recvinfo = (User_reg_RecvInfo *) arg;
    if(recvinfo->status != 200)
    {
        switch (recvinfo->status) {
        case USER_ERR_REQINFO:
            QMessageBox::about(m_pLoginDlg,"提示","请求包不合法");
            qDebug()<<__func__ << "注册失败 - 请求包不合法";
            break;
        case User_Reg_Havethisnum:
            QMessageBox::about(m_pLoginDlg,"提示","账户已经被使用");
            qDebug()<<__func__ << "注册失败 - 手机号已经被注册";
            break;
        case User_Reg_Havethistel:
            QMessageBox::about(m_pLoginDlg,"提示","手机号已经被注册");
            qDebug()<<__func__ << "注册失败 - 手机号已经被注册";
            break;
        default:
            QMessageBox::about(m_pLoginDlg,"提示","未知错误");
            cout << __func__ << " not find status" << recvinfo->status <<endl;
            break;
        }
        return nullptr;
    }
    QMessageBox::about(m_pLoginDlg,"提示","注册成功");
    qDebug()<<__func__ << "注册成功";

}

void * Ckernel::SIGDEAL_login (void * arg){
    //强转
    User_login_RecvInfo * recvinfo = (User_login_RecvInfo *) arg;
    if(recvinfo->status != 200 ){
        switch(recvinfo->status){
        case USER_ERR_REQINFO://请求体有误
            QMessageBox::about(m_pLoginDlg,"提示","请求体有误");
            qDebug()<<__func__ << "请求体有误";
            break;
        case USER_LOGIN_ERRINFO://登陆失败 - 账号密码不对应
            //调用提醒函数
            QMessageBox::about(m_pLoginDlg,"提示","密码或账号错误");
            qDebug()<<__func__ << "密码或账号错误";
            return nullptr;
        case USER_DAL_ERR:
            QMessageBox::about(m_pLoginDlg,"提示","服务器内部错误");
            qDebug()<<__func__ << "服务器内部错误";
            return nullptr;
        default:
            QMessageBox::about(m_pLoginDlg,"提示","未知错误");
            cout << __func__ << " not find status" << recvinfo->status <<endl;
            break;
        }
        return nullptr;
    }

    //存到本地
    //个人信息
    Ckernel::myuid                    = stoi(((JWT_token::jwt_decode(recvinfo->jwt_token)).getpayloadmap())["aud"]) ;
    Ckernel::my_jwt_token             = recvinfo->jwt_token;
    Ckernel::my_refresh_jwt_token     = recvinfo->refresh_jwt_token;
    cout << "Userid 为 : " << myuid << "登录成功" <<endl;

    //TODO: 阻塞获取 个人信息 设置wechat更新界面

    m_pLoginDlg->hide();
    We_Chat->show();
}

void * Ckernel::SIGDEAL_JoinRoom(void * arg){
    Room_Joinroom_RecvInfo * recvinfo = (Room_Joinroom_RecvInfo *)arg;

    if(recvinfo->status != ROOM_ACTION_OK ){
        switch(recvinfo->status){
        case ROOM_ERR_REQINFO://请求体有误
            QMessageBox::about(m_pLoginDlg,"提示","请求体有误");
            qDebug()<<__func__ << "请求体有误";
            break;
        case ROOM_Create_Havethisnum://num重复
            //调用提醒函数
            QMessageBox::about(m_pLoginDlg,"提示","已经有这个num的房间了");
            qDebug()<<__func__ << "已经有这个num的房间了";
            return nullptr;
        case ROOM_DAL_ERR:
            QMessageBox::about(m_pLoginDlg,"提示","服务器内部错误");
            qDebug()<<__func__ << "服务器内部错误";
            return nullptr;
        case ROOM_JOINROOM_ERRPASSWD:
            QMessageBox::about(m_pLoginDlg,"提示","错误的密码");
            qDebug()<<__func__ << "错误的密码";
            return nullptr;
        case ROOM_Changepos_Havepeo:
            QMessageBox::about(m_pLoginDlg,"提示","位置上有人了");
            qDebug()<<__func__ << "位置上有人了";
            return nullptr;
        case ROOM_NoSuchRoomInfo:
            QMessageBox::about(m_pLoginDlg,"提示","没有这个房间");
            qDebug()<<__func__ << "没有这个房间";
            return nullptr;
        case ROOM_PlayerInotherRoom:
            QMessageBox::about(m_pLoginDlg,"提示","用户在别的房间了");
            qDebug()<<__func__ << "服务器内部错误";
            return nullptr;
        default:
            QMessageBox::about(m_pLoginDlg,"提示","未知错误");
            cout << __func__ << " not find status" << recvinfo->status <<endl;
            break;
        }
        return nullptr;
    }

    //创建成功
    cout << "Room Join success ! " <<endl;
    return nullptr;

}

void * Ckernel::SIGDEAL_CreateRoom(void * arg){
    Room_Create_RecvInfo * recvinfo = (Room_Create_RecvInfo *)arg;

    if(recvinfo->status != 200 ){
        switch(recvinfo->status){
        case ROOM_ERR_REQINFO://请求体有误
            QMessageBox::about(m_pLoginDlg,"提示","请求体有误");
            qDebug()<<__func__ << "请求体有误";
            break;
        case ROOM_Create_Havethisnum://num重复
            //调用提醒函数
            QMessageBox::about(m_pLoginDlg,"提示","已经有这个num的房间了");
            qDebug()<<__func__ << "已经有这个num的房间了";
            return nullptr;
        case ROOM_DAL_ERR:
            QMessageBox::about(m_pLoginDlg,"提示","服务器内部错误");
            qDebug()<<__func__ << "服务器内部错误";
            return nullptr;
        case ROOM_PlayerInotherRoom:
            QMessageBox::about(m_pLoginDlg,"提示","用户在别的房间了");
            qDebug()<<__func__ << "服务器内部错误";
            return nullptr;
        default:
            QMessageBox::about(m_pLoginDlg,"提示","未知错误");
            cout << __func__ << " not find status" << recvinfo->status <<endl;
            break;
        }
        return nullptr;
    }

    //创建成功
    cout << "Room创建成功" <<endl;
        return nullptr;
}
