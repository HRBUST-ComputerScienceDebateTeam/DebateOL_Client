#include <QtNetwork>
#include <QString>
#include <QVariant>
#include "../thrift_json/thrift_json_config.h"
#include "../../Room_main/room_main.h"
#include "../../config.h"
#include <cstdio>
#include <conio.h>
#include <QObject>

//单例
//必须先初始化才能使用单例
typedef void* (Room_main::*ROOMMAIN_CALL_FUN)(void *);
class MYNET: public QObject{
    Q_OBJECT

private:
    MYNET();
    ~MYNET();
    MYNET(const MYNET & );
    MYNET(MYNET & );
    const MYNET &operator=(const MYNET &signal);

public:
    static MYNET* getinstance();//别忘初始化！
    static void Init(Room_main*);


private slots:
    void slot_replyFinished(QNetworkReply*);
public:
    QString GET_VIDEODL_URL(struct  Video_Download_SendInfo &);
    //执行事件结果异步的发送给对应的回调函数
    void NETGET(QString url , int tim , ROOMMAIN_CALL_FUN);
    void NETPOST(QString url , std::string &data, int tim, ROOMMAIN_CALL_FUN);
private:
    //网络大管家 pmanager负责通讯
    QNetworkAccessManager * pmanager;
    static MYNET * pnet;
    static Room_main* rp;//用于处理回调函数
    //事件注册表
    void* (Room_main::*net_event[MAX_EVENTNUM])(void *);
};


