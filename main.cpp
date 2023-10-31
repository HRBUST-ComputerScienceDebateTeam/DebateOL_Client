#include "./mainwindow/mainwindow.h"
#include "./camera/camera.h"//摄像头
#include "./web/web.h"
#include "./config.h"
#include "./ckernel.h"


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

    qDebug()<<NETGET(TEST_GET_URL);
    qDebug()<<NETPOST(TEST_GET_URL , "你好");



    return a.exec();
}
