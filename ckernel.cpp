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
    m_pAudioRead = new AudioRead;
    connect(m_pLoginDlg,SIGNAL(SIG_loginCommit(QString,QString))
            ,this,SLOT(slot_loginCommit(QString,QString)));
    connect(m_pLoginDlg,SIGNAL(SIG_registerCommit(QString,QString,QString))
            ,this,SLOT(slot_registerCommit(QString,QString,QString)));

    connect(We_Chat,SIGNAL(SIG_createRoom(std::string))
            ,this,SLOT(slot_createRoom(std::string)));
    connect(We_Chat,SIGNAL(SIG_joinRoom(std::string))
            ,this,SLOT(slot_joinRoom(std::string)));


    //m_pVideoRead = new VideoRead;
    m_pLoginDlg->show();
    //m_room->show();
    //We_Chat->show();

}
//个人信息
int    Ckernel::myuid                    =-1;
string Ckernel::my_jwt_token             ="";
string Ckernel::my_refresh_jwt_token     ="";

//void Ckernel::~Ckernel(){
//    if(m_room){
//        delete m_room;
//        m_room = nullptr;
//    }
//}

//回收
void Ckernel::slot_destory()
{
    //发送下线请求

    //qDebug()<<__func__;
    if(We_Chat)
    {
        We_Chat->hide();
        delete We_Chat;
        We_Chat = NULL;
    }
    if(m_pLoginDlg)
    {
        m_pLoginDlg->hide();
        delete m_pLoginDlg;
        m_pLoginDlg = NULL;
    }
    if(m_pAudioRead)
    {
        m_pAudioRead->pause();
        delete m_pAudioRead;
        m_pAudioRead = NULL;
    }
    if(m_room)
    {
        delete m_room;
        m_room = NULL;
    }  
}

void Ckernel::slot_destorychat()
{
    //qDebug()<<__func__;
    if(We_Chat)
    {
        delete We_Chat;
        We_Chat = NULL;
    }
}


void Ckernel::slot_closeroom(){

    //回收的时候发送下线请求
    MYNET_KERNEL * net = MYNET_KERNEL::getinstance();
    //先更新jwt_token;
    QTime tim = QTime::currentTime();
    User_refresh_jwt1_SendInfo sd1;
    sd1.jwt_token = this->my_jwt_token;
    sd1.type      = User_refresh_jwt1_SendInfo_TypeId;
    sd1.sendtime = tim.minute()*60000 + tim.second()*1000+ tim.msec();
    sd1.refresh_jwt_token = this->my_refresh_jwt_token;
    string data1 = User_refresh_jwt1_SendInfo::Serialization(sd1);
    string recv1 = net->NETPOST_BLOCK(User_refresh_jwt1_URL , data1);
    if(recv1 == ""){
        cout << "user :" << this->myuid << "wrong out" <<endl;
        return;
    }else{
        User_refresh_jwt1_RecvInfo rcv = User_refresh_jwt1_RecvInfo::Deserialization(recv1);
        if(rcv.status == User_JWT_NOTOUTTIME){//没过期
            ;
        }else if(rcv.status == USER_ACTION_OK){
            this->my_jwt_token = rcv.jwt_token;
        }else if(rcv.status == USER_TIMEOUT_JWT){
            //用户jwt超时
            //去更新rejwt
            User_refresh_jwt2_SendInfo sd2;
            sd2.jwt_token = this->my_jwt_token;
            sd2.type      = User_refresh_jwt1_SendInfo_TypeId;
            sd2.sendtime = tim.minute()*60000 + tim.second()*1000+ tim.msec();
            sd2.refresh_jwt_token = this->my_refresh_jwt_token;
            string data2 = User_refresh_jwt2_SendInfo::Serialization(sd2);
            string recv2 = net->NETPOST_BLOCK(User_refresh_jwt2_URL , data2);
            if(recv2 == ""){
                cout << "user :" << this->myuid << "wrong out" <<endl;
                return;
            }else{
                User_refresh_jwt2_RecvInfo rcv2 = User_refresh_jwt2_RecvInfo::Deserialization(recv2);
                if(rcv2.status == USER_ACTION_OK){
                    this->my_refresh_jwt_token = rcv2.refresh_jwt_token;
                    this->my_jwt_token = rcv2.jwt_token;
                }else{
                    cout << "user :" << this->myuid << "wrong out" <<endl;
                    return;
                }
            }
        }else{
            cout << "user :" << this->myuid << "wrong out" <<endl;
            return;
        }
    }
    Room_Exitroom_SendInfo sd;
    QTime tm = QTime::currentTime();
    sd.type = Room_Exitroom_SendInfo_TypeId;
    sd.sendtime = tm.minute()*60000 + tm.second()*1000+ tm.msec();
    sd.roomnum = this->roomnum;
    sd.jwt_token = this->my_jwt_token;
    string data = Room_Exitroom_SendInfo::Serialization(sd);
    string recv = net->NETPOST_BLOCK(Room_Exitroom_URL , data);
    Room_Exitroom_RecvInfo  rcv3 = Room_Exitroom_RecvInfo::Deserialization(recv);
    if(rcv3.status == USER_ACTION_OK){
        cout << "user :" << this->myuid << "success out" <<endl;
    }else{
        cout << "user :" << this->myuid << "wrong out" <<endl;
    }

    if(m_room){
        this->m_room->hide();
        delete m_room;
        m_room = nullptr;
    }
    this->room_id = INT_DEFAULT;
    this->roomnum = STR_DEFAULT;
    this->We_Chat->show();
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


        //音频内容添加
    /*AudioWrite *aw =NULL;
     //为每个人创建播放对象
    if(m_mapIDToAudioWrite.count(/*结构体///->userID) == 0)
        {
        aw = new AudioWrite;
        m_mapIDToAudioWrite[/*结构体///->userID] = aw;
    }*/


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

//获取辩位信息
void Ckernel::slot_SendDebatePostoRoom(){
    Room_GetURrelation_SendInfo sdinfo;
    sdinfo.type = Room_GetURrelation_SendInfo_TypeId;
    sdinfo.Aim_Roomnum = roomnum;
    QTime mytim= QTime::currentTime();
    sdinfo.sendtime = mytim.minute()*60000+mytim.second()*1000+mytim.msec();
    sdinfo.jwt_token = my_jwt_token;
    sdinfo.info = "" ;

    MYNET_KERNEL::Init(this);
    MYNET_KERNEL * netptr = MYNET_KERNEL::getinstance();//获取单例
    std::string ss = Room_GetURrelation_SendInfo::Serialization(sdinfo);
    netptr->NETPOST(Room_GetURrelation_URL ,ss , sdinfo.sendtime  ,  &Ckernel::SIGDEAL_SendDebatePostoRoom );
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


    //获取房间号 myuid;
    map<string , string> mp = JsonstringToMap(recvinfo->info);
    room_id = std::stoi(mp["Roomid"]);
    roomnum = mp["Roomnum"];
    m_room = new Room_main(room_id , roomnum , myuid , stoi(mp["Debate_pos"]) , my_jwt_token , my_refresh_jwt_token);
    connect(We_Chat , SIGNAL(SIG_closechat()),this,SLOT(slot_destorychat()));
    connect(m_room , SIGNAL(SIG_SendDebatePostoRoom()) , this , SLOT(slot_SendDebatePostoRoom()));
    connect(m_room , SIGNAL(SIG_closeroom()) , this , SLOT(slot_closeroom()));
    //加入
    cout << "Room Join success ! " <<endl;
    We_Chat->hide();
    m_room->show();

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
    cout << "Roomcreate_success" <<endl;
    //获取房间号 myuid;
    map<string , string> mp = JsonstringToMap(recvinfo->info);
    room_id = std::stoi(mp["Roomid"]);
    roomnum = mp["Roomnum"];
    m_room = new Room_main(room_id , roomnum , myuid , stoi(mp["Debate_pos"]) , my_jwt_token , my_refresh_jwt_token);
    connect(We_Chat , SIGNAL(SIG_closechat()),this,SLOT(slot_destorychat()));
    We_Chat->hide();
    m_room->show();
    return nullptr;
}

void * Ckernel::SIGDEAL_SendDebatePostoRoom(void * arg){
    Room_GetURrelation_RecvInfo* recvinfo = (Room_GetURrelation_RecvInfo *) arg;
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

    if(recvinfo->info_UR_pos == STR_DEFAULT){
        qDebug()<<__func__ << "房间更新辩位信息获取为空";
        return nullptr;
    }

    qDebug()<<__func__ << "房间更新辩位信息成功";
    m_room->ToUpdateDebatePos(recvinfo->info_UR_pos);
    return nullptr;
}

