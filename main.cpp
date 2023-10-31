#include "./mainwindow/mainwindow.h"
#include "./camera/camera.h"//摄像头
#include "./web/web.h"
#include "./config.h"
#include "./ckernel.h"
#include "./pkg/thrift_json/thrift_json_config.h"


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow mainw;
    //mainw.show();
    Ckernel::GetInstance();

    //QApplication::addLibraryPath(R"(C:\qt\6.6.0\mingw_64\plugins)");
    Camera Ca_w;//创建窗口类
    Ca_w.setWindowTitle("Camera");//设置窗口标题
    Ca_w.show();//显示窗口

    //简单通讯
    //qDebug()<<NETGET(TEST_GET_URL);
    //qDebug()<<NETPOST(TEST_GET_URL , std::string("你好"));

    //序列化
    std::string echojson = Echo_SendInfo::Serialization( Echo_SendInfo({uint32_t(1),string("你好 - echo请求")}));
    //qDebug() << echojson;

    //发送
    QString srecv = NETPOST(ECHO_POST_URL , echojson);


    //反序列化
    Echo_RecvInfo recvinfo = Echo_RecvInfo::Deserialization(srecv.toStdString());

    qDebug() << "返回id ： " << recvinfo.id;
    qDebug() << "返回info ： " << recvinfo.info;
    qDebug() << "返回time ： " << recvinfo.time;



    return a.exec();
}
