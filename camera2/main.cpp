#include <QApplication>//Qt必要头文件

#include "camera.h"//摄像头

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);//Qt初始化
    QApplication::addLibraryPath(R"(F:\qt\6.6.0\mingw_64\plugins)");
    Camera w;//创建窗口类
    w.setWindowTitle("Camera");//设置窗口标题
    w.show();//显示窗口

    return a.exec();//程序结束
}



