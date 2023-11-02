#include "./mainwindow/mainwindow.h"
#include "./camera/camera.h"//摄像头

#include "./config.h"
#include "./ckernel.h"
#include "./pkg/thrift_json/thrift_json_config.h"
#include "./pkg/web/web.h"


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mainw;
    mainw.show();
    Ckernel::GetInstance();

    //QApplication::addLibraryPath(R"(C:\qt\6.6.0\mingw_64\plugins)");
    //Camera Ca_w;//创建窗口类
    //Ca_w.setWindowTitle("Camera");//设置窗口标题
    //Ca_w.show();//显示窗口

    //简单通讯
    qDebug()<<NETGET(TEST_GET_URL);
    qDebug()<<NETPOST(TEST_GET_URL , std::string("你好"));

    //序列化
    std::string echojson = Echo_SendInfo::Serialization( Echo_SendInfo({uint32_t(1),string("你好 - echo请求")}));
    //qDebug() << echojson;

    //发送
    QString srecv = NETPOST(ECHO_POST_URL , echojson);


    //反序列化
    Echo_RecvInfo recvinfo = Echo_RecvInfo::Deserialization(srecv.toStdString());

    qDebug() << "返回id ： " << recvinfo.id;
    qDebug() << "返回info ： " << QString().fromStdString(recvinfo.info);
    qDebug() << "返回time ： " << recvinfo.time;

    //上传请求
    Video_Upload_SendInfo send;
    send.info = "这是一条视频";
    send.min = 21;
    send.sec = 22;
    send.msec = 523;
    send.type = 1;
    send.roomId = 7;
    send.userId = 3;

    //qDebug().noquote()<< QString().fromStdString(Video_Upload_SendInfo::Serialization(send));
    QString ULret = NETPOST(VIDEO_UPLOAD_POST_URL , Video_Upload_SendInfo::Serialization(send));
    Video_Upload_RecvInfo ulreinfo = Video_Upload_RecvInfo::Deserialization(ULret.toStdString());
    qDebug() << "返回的请求状态 ： " << ulreinfo.status;
    qDebug() << "返回的房间号 ： " << ulreinfo.roomId;
    qDebug() << "返回的用户号 ： " << ulreinfo.userId;
    qDebug() << "返回的时间 ： " << ulreinfo.min << "-" <<ulreinfo.sec << "-" << ulreinfo.sec;




   //下载请求
    Video_Download_SendInfo sendinfo;
    sendinfo.min = 21;
    sendinfo.sec = 22;
    sendinfo.msec = 525;
    sendinfo.type = 1;
    sendinfo.roomId = 7;
    sendinfo.userId = 3;

    //qDebug().noquote()<< QString().fromStdString(Video_Download_SendInfo::Serialization(sendinfo));
    //qDebug().noquote()<< GET_VIDEODL_URL(sendinfo);
    QString DLret = NETGET(GET_VIDEODL_URL(sendinfo));
    Video_Download_RecvInfo dlreinfo = Video_Download_RecvInfo::Deserialization(DLret.toStdString());
    qDebug() << "返回的请求状态 ： " << dlreinfo.status;
    qDebug() << "返回的房间号 ： " << dlreinfo.roomId;
    qDebug() << "返回的用户号 ： " << dlreinfo.userId;
    qDebug() << "返回的时间 ： " << dlreinfo.min << "-" <<dlreinfo.sec << "-" << dlreinfo.sec;
    qDebug()<< "返回的信息" <<QString().fromStdString(dlreinfo.info);
    return a.exec();
}
