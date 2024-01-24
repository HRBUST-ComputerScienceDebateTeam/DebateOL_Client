#include "./web.h"
#include "../../config.h"
#include "../../pkg/Openssl/openssl.h"
#include <thread>
#include <cstdio>
//#include <winsock2.h>
#include <conio.h>

#pragma comment(lib, "ws2_32.lib")
using namespace std;

#define WEB_ROUTING_ROOM(x) \
    case x##_TypeId:{ \
        x * dlreinfo = new x ( x::Deserialization(QString::fromLatin1(getinfo).toLatin1().toStdString())); \
        ROOMMAIN_CALL_FUN fp = net_event[dlreinfo->sendtime]; \
        if(!fp){ \
            cout << "err 事件没有注册" <<endl; \
            delete dlreinfo; \
        }else{ \
                net_event[dlreinfo->sendtime] = 0;\
                (rp->*fp)((void*)dlreinfo); \
        } \
    } \
    break;

#define WEB_ROUTING_KERNEL(x) \
    case x##_TypeId:{ \
        x * dlreinfo = new x ( x::Deserialization(QString::fromLatin1(getinfo).toLatin1().toStdString())); \
        KERNEL_CALL_FUN fp = net_event[dlreinfo->sendtime]; \
        if(!fp){ \
            cout << "err 事件没有注册" <<endl; \
            delete dlreinfo; \
        }else{ \
            net_event[dlreinfo->sendtime] = 0;\
            (kp->*fp)((void*)dlreinfo); \
        } \
    } \
    break;


void MYNET_ROOM::NETGET(QString url , int timid , ROOMMAIN_CALL_FUN fun){
    //cout << "NETGET" <<endl;
    QUrl q(url);
    QNetworkRequest request;
    request.setUrl(q);
    request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json"));
    request.setRawHeader("Connection", "keep-alive");
    request.setRawHeader("Content-Length" , 0);

    //注册事件 委托请求
    net_event[timid] = fun;
    pmanager_room->get(request);
}

void MYNET_ROOM::NETPOST(QString url , std::string& data ,int timid , ROOMMAIN_CALL_FUN fun){
    //cout << "NETPOST" <<endl;
    QUrl q(url);
    QNetworkRequest request(q);

    //application/json	作为请求头告诉服务端消息主体是序列化的JSON字符串。除低版本的IE，基本都支持
    request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json"));
    request.setRawHeader("Connection", "keep-alive");
    request.setRawHeader("Content-Length" , QByteArray().number(data.length()));

    QByteArray qByteHttpData(data.c_str(),data.length());

    //注册事件 委托请求
    if(net_event[timid] != 0 )return;
    net_event[timid] = fun;
    pmanager_room->post(request , qByteHttpData);
}



void MYNET_ROOM::slot_replyFinished(QNetworkReply* reply){
    //cout <<"slot_replyFinished" <<endl;
    //如果合法
    if (reply->error() != QNetworkReply::NoError){
        qDebug()<<"request protobufHttp handle errors here";
        QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        qDebug( "request protobufHttp found error ....code: %d %d\n", statusCodeV.toInt(), (int)reply->error());
        qDebug(qPrintable(reply->errorString()));
        return;
    }

    //取出数据
    QByteArray getinfo = reply->readAll();
    //qDebug()<<getinfo;
    //删除
    reply->deleteLater();

    //调用事件 - TODO ADD 线程池

    int etypeid = get_typeid(QString::fromLatin1(getinfo).toLatin1().toStdString());
    switch(etypeid){
            WEB_ROUTING_ROOM(Video_Download_RecvInfo  );
            WEB_ROUTING_ROOM(Video_Upload_RecvInfo  );
            WEB_ROUTING_ROOM(Audio_Download_RecvInfo  );
            WEB_ROUTING_ROOM(Audio_Upload_RecvInfo  );
    default:
        cout << "未识别的类型" << etypeid <<endl;
        return;
    }



}


void MYNET_ROOM::Init(Room_main* _rp){
    if(!rp){
        cout << "rp 初始化"<<endl;
        rp = _rp;
    }
}
MYNET_ROOM::MYNET_ROOM(){
    //cout << "pmanager 初始化" <<endl;
    pmanager_room = new QNetworkAccessManager;
    //readyRead(QNetworkReply*)
    connect(pmanager_room,  SIGNAL(finished(QNetworkReply*)), this , SLOT(slot_replyFinished(QNetworkReply*)));


}

MYNET_ROOM::~MYNET_ROOM(){
    delete pmanager_room;
    delete pnet_room;
    //不能处理rp
}
MYNET_ROOM* MYNET_ROOM::getinstance(){
    if(!rp){
        cout << "err : kp haven't init" <<endl;
        return nullptr;
    }
    if(!pnet_room){
        cout << "pnet_kernel 初始化" <<endl;
        pnet_room = new MYNET_ROOM;//必须先初始化才能使用单例
    }
    return pnet_room;
}
MYNET_ROOM * MYNET_ROOM::pnet_room;
Room_main * MYNET_ROOM::rp;



void MYNET_KERNEL::NETGET(QString url , int timid , KERNEL_CALL_FUN fun){
    //cout << "NETGET" <<endl;
    QUrl q(url);
    QNetworkRequest request;
    request.setUrl(q);
    request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json"));
    request.setRawHeader("Connection", "keep-alive");
    request.setRawHeader("Content-Length" , 0);

    //注册事件 委托请求
    net_event[timid] = fun;
    pmanager_kernel->get(request);
}

void MYNET_KERNEL::NETPOST(QString url , std::string& data ,int timid , KERNEL_CALL_FUN fun){
    //cout << "MYNET_KERNEL::NETPOST" <<endl;
    QUrl q(url);
    QNetworkRequest request(q);

    //application/json	作为请求头告诉服务端消息主体是序列化的JSON字符串。除低版本的IE，基本都支持
    request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json"));
    request.setRawHeader("Connection", "keep-alive");
    request.setRawHeader("Content-Length" , QByteArray().number(data.length()));
    QByteArray qByteHttpData(data.c_str(),data.length());

    //注册事件 委托请求
    if(net_event[timid] != 0 )return;
    net_event[timid] = fun;
    pmanager_kernel->post(request , qByteHttpData);
}


void MYNET_KERNEL::slot_replyFinished(QNetworkReply* reply){
    cout <<"slot_replyFinished" <<endl;
    //如果合法
    if (reply->error() != QNetworkReply::NoError){
        qDebug()<<"request protobufHttp handle errors here";
        QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        qDebug( "request protobufHttp found error ....code: %d %d\n", statusCodeV.toInt(), (int)reply->error());
        qDebug(qPrintable(reply->errorString()));
        return;
    }

    //取出数据
    QByteArray getinfo = reply->readAll();
    //qDebug()<<getinfo;
    //删除
    reply->deleteLater();

    //调用事件 - TODO ADD 线程池
    if(getinfo.size() == 0) return;
    int etypeid = get_typeid(QString::fromLatin1(getinfo).toLatin1().toStdString());
    switch(etypeid){
        WEB_ROUTING_KERNEL(User_login_RecvInfo);
        WEB_ROUTING_KERNEL(User_GetBaseInfo_RecvInfo      );
        WEB_ROUTING_KERNEL(User_GetSocialInfo_RecvInfo    );
        WEB_ROUTING_KERNEL(User_GetExInfo_RecvInfo     );
        WEB_ROUTING_KERNEL(User_reg_RecvInfo              );
        WEB_ROUTING_KERNEL(User_logoff_RecvInfo           );
        WEB_ROUTING_KERNEL(User_refresh_jwt1_RecvInfo     );
        WEB_ROUTING_KERNEL(User_refresh_jwt2_RecvInfo     );
        WEB_ROUTING_KERNEL(User_friend_RecvInfo           );
        WEB_ROUTING_KERNEL(User_follow_RecvInfo           );
        WEB_ROUTING_KERNEL(User_followed_RecvInfo         );
        WEB_ROUTING_KERNEL(User_ModifyBaseInfo_RecvInfo   );
        WEB_ROUTING_KERNEL(User_ModifySocialInfo_RecvInfo );
        WEB_ROUTING_KERNEL(User_ModifyExInfo_RecvInfo     );
        WEB_ROUTING_KERNEL(Room_GetBaseInfo_RecvInfo      );
        WEB_ROUTING_KERNEL(Room_GetExInfo_RecvInfo        );
        WEB_ROUTING_KERNEL(Room_GetURrelation_RecvInfo    );
        WEB_ROUTING_KERNEL(Room_Create_RecvInfo           );
        WEB_ROUTING_KERNEL(Room_Joinroom_RecvInfo         );
        WEB_ROUTING_KERNEL(Room_Exitroom_RecvInfo         );
        WEB_ROUTING_KERNEL(Room_ChangePasswd_RecvInfo     );
        WEB_ROUTING_KERNEL(Room_ChangeExtraInfo_RecvInfo  );
        WEB_ROUTING_KERNEL(Room_ChangeDebatePos_RecvInfo  );
        default:
            cout << "Web： we don't know this type:" << etypeid <<endl;
                return;
    }



}


void MYNET_KERNEL::Init(Ckernel* _kp){
    if(!kp){
        cout << "kp 初始化"<<endl;
            kp = _kp;
    }
}
MYNET_KERNEL::MYNET_KERNEL(){
    cout << "pmanager_kp 初始化" <<endl;
    pmanager_kernel = new QNetworkAccessManager;
    //readyRead(QNetworkReply*)
    connect(pmanager_kernel,  SIGNAL(finished(QNetworkReply*)), this , SLOT(slot_replyFinished(QNetworkReply*)));


}

MYNET_KERNEL::~MYNET_KERNEL(){
    delete pmanager_kernel;
    delete pnet_kernel;
    //不能处理kp
}
MYNET_KERNEL* MYNET_KERNEL::getinstance(){
    if(!kp){
        cout << "err : kp haven't init" <<endl;
        return nullptr;
    }
    if(!pnet_kernel){
        cout << "pnet_kernel 初始化" <<endl;
            pnet_kernel = new MYNET_KERNEL;//必须先初始化才能使用单例
    }
    return pnet_kernel;
}

std::string MYNET_ROOM::NETPOST_BLOCK(QString url , std::string &data){//对应url发送对应信息 阻塞回收
    //cout << "MYNET_room::NETPOST block" <<endl;
    const QUrl qurl = QUrl::fromUserInput(url);
    QNetworkRequest qnr(url);

    //application/json	作为请求头告诉服务端消息主体是序列化的JSON字符串。除低版本的IE，基本都支持
    qnr.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json"));
    qnr.setRawHeader("Connection", "keep-alive");
    qnr.setRawHeader("Content-Length" , QByteArray().number(data.length()));
    QByteArray qByteHttpData(data.c_str(),data.length());

    QNetworkAccessManager q;
    QNetworkReply* reply = q.post(qnr ,qByteHttpData); //m_qnam是QNetworkAccessManager对象
    QEventLoop eventLoop;
    connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);

    string replyDate = reply->readAll().toStdString();

    return replyDate;
}
std::string  MYNET_KERNEL::NETPOST_BLOCK(QString url , std::string &data){//对应url发送对应信息 阻塞回收
    //cout << "MYNET_room::NETPOST block" <<endl;
    const QUrl qurl = QUrl::fromUserInput(url);
    QNetworkRequest qnr(url);

    //application/json	作为请求头告诉服务端消息主体是序列化的JSON字符串。除低版本的IE，基本都支持
    qnr.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json"));
    qnr.setRawHeader("Connection", "keep-alive");
    qnr.setRawHeader("Content-Length" , QByteArray().number(data.length()));

    QNetworkAccessManager q;
    QByteArray qByteHttpData(data.c_str(),data.length());
    cerr<<qByteHttpData.toStdString()<<endl;
    QNetworkReply* reply = q.post(qnr ,qByteHttpData); //m_qnam是QNetworkAccessManager对象
    QEventLoop eventLoop;
    connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);

    string replyDate = reply->readAll().toStdString();

    return replyDate;
}

MYNET_KERNEL * MYNET_KERNEL::pnet_kernel;
Ckernel * MYNET_KERNEL::kp;
