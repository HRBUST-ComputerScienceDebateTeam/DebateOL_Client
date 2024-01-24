#include <QtNetwork>
#include <QString>
#include <QVariant>
#include "../thrift_json/thrift_json_config.h"
#include "../../Room_main/room_main.h"
#include "../../config.h"
#include "../../ckernel.h"
#include <cstdio>
#include <conio.h>
#include <QObject>

//单例
//必须先初始化才能使用单例
typedef void* (Room_main::*ROOMMAIN_CALL_FUN)(void *);
typedef void* (Ckernel::*KERNEL_CALL_FUN  )(void *);


class MYNET_ROOM: public QObject{
    Q_OBJECT

private:
    MYNET_ROOM();
    ~MYNET_ROOM();
    MYNET_ROOM(const MYNET_ROOM & );
    MYNET_ROOM(MYNET_ROOM & );
    const MYNET_ROOM &operator=(const MYNET_ROOM &signal);

public:
    static MYNET_ROOM* getinstance();//别忘初始化！
    static void Init(Room_main*);


private slots:
    void slot_replyFinished(QNetworkReply*);
public:
    QString GET_VIDEODL_URL(struct  Video_Download_SendInfo &);
    //执行事件结果异步的发送给对应的回调函数
    void NETGET(QString url , int tim , ROOMMAIN_CALL_FUN);
    void NETPOST(QString url , std::string &data, int tim, ROOMMAIN_CALL_FUN);
    std::string NETPOST_BLOCK(QString url , std::string &data);//对应url发送对应信息 阻塞回收
private:
    //网络大管家 pmanager负责通讯
    QNetworkAccessManager * pmanager_room;
    static MYNET_ROOM * pnet_room;
    static Room_main* rp;//用于处理回调函数
    //事件注册表
    void* (Room_main::*net_event[MAX_EVENTNUM])(void *);
};



class MYNET_KERNEL: public QObject{
    Q_OBJECT

private:
    MYNET_KERNEL();
    ~MYNET_KERNEL();
    MYNET_KERNEL(const MYNET_KERNEL & );
    MYNET_KERNEL(MYNET_KERNEL & );
    const MYNET_KERNEL &operator=(const MYNET_KERNEL &signal);

public:
    static MYNET_KERNEL* getinstance();//别忘初始化！
    static void Init(Ckernel*);


private slots:
    void slot_replyFinished(QNetworkReply*);
public:
    //执行事件结果异步的发送给对应的回调函数
    void NETGET(QString url , int tim , KERNEL_CALL_FUN);
    void NETPOST(QString url , std::string &data, int tim, KERNEL_CALL_FUN);
    std::string NETPOST_BLOCK(QString url , std::string &data);//对应url发送对应信息 阻塞回收
private:
    //网络大管家 pmanager负责通讯
    QNetworkAccessManager * pmanager_kernel;
    static MYNET_KERNEL * pnet_kernel;
    static Ckernel* kp;//用于处理回调函数
    //事件注册表
    void* (Ckernel::*net_event[MAX_EVENTNUM])(void *);
};

