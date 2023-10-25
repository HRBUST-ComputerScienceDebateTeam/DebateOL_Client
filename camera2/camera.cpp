#include "camera.h"//摄像头
#include "./ui_camera.h"//CMakeLists.txt构建后产生文件

Camera::Camera(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Camera)
{
    ui->setupUi(this);

    //qDebug("Camera Device Check:%d",Camera::checkCameraAvailability());//摄像头驱动检测debug测试

    my_camera.reset(new QCamera(QMediaDevices::defaultVideoInput()));//新建并设置摄像头使用默认驱动
    my_captureSession.setCamera(my_camera.data());//捕获摄像头画面
    my_captureSession.setVideoOutput(ui->viewfinder);//设置捕捉画面显示窗口
    my_camera->start();//启动摄像头

}


//检测摄像头驱动能否识别
bool Camera::checkCameraAvailability()
{
    if (QMediaDevices::videoInputs().count() > 0)
        return true;//检测到摄像头驱动
    else
        return false;//没有检测到摄像头驱动
}

//消类
Camera::~Camera()
{
    delete ui;
}


