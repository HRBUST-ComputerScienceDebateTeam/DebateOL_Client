#include "ckernel.h"
#include "./config.h"
#include "./pkg/JsonChange/jsonchange.h"
#include "./pkg/JWT/jwt.h"
#include "./pkg/Openssl/openssl.h"
#include"qDebug"

#define NetPackMap(a) m_netPackMap[a - DEF_PACK_BASE]


Ckernel::Ckernel(QObject *parent)
    : QObject{parent}
{
    //m_room = new Room_main;
//    We_Chat =new WeChatDialog;
    m_pLoginDlg =new LoginDialog;
    connect(m_pLoginDlg,SIGNAL(SIG_loginCommit(QString,QString))
            ,this,SLOT(slot_loginCommit(QString,QString)));
//    connect(m_room , SIGNAL(SIG_close())
//            ,this,SLOT(slot_destory()));
//    connect(We_Chat , SIGNAL(SIG_closechat())
//            ,this,SLOT(slot_destorychat()));
    //m_pVideoRead = new VideoRead;
    /*connect(m_pVideoRead, SIGNAL(SIG_sendVideoFrame(QImage))
            ,this,SLOT(SIG_sendVideoFrame(QImage)));*/
    m_pLoginDlg->show();
    //m_room->show();
    //We_Chat->show();
}
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
//发送登录
void Ckernel::slot_loginCommit(QString tel, QString pass)
{
    std::string strTel = tel.toStdString();
    std::string strPass = pass.toStdString();
    //下面是封装发送

//    User_login_Tel_SendInfo login_req;
//    time_t timenow;
//    time(&timenow); // 64int
//    login_req.sendtime = timenow;
//    login_req.passwd = sha256(Base64Encode(strPass));
//    login_req.tel = strTel;
//    login_req.type = User_LoginTel_SendInfo_TypeId;

//    string sendreq = User_login_Tel_SendInfo::Serialization(login_req);
//    //网络请求
//    MyNet_kernel::init();
//    MyNet_kernel * netptr = //获取单例

//    netptr->post(url , timenow , sendreq , 回调函数 );
}

//void * 回调函数 (void * arg){
//强转
//    User_login_RecvInfo * recvinfo = (User_login_RecvInfo *) arg;
//    if(recvinfo->status != 200 ){
//        switch(recvinfo->status){
//            case 300:
//                return;
//                break;
//            //
//            default:
//                cout << " not find status";

//            }
//    }
//    //存到本地
//    save = recvinfo->jwt_token ; //save是类内成员
//    save = recvinfo->refresh_jwt_token;
//    saveid = stoi((JWT_token::jwt_decode(recvinfo->jwt_token).getpayloadmap())["aud"]);

//}

