#include "camera.h"//摄像头
#include "../camera/camera.h" //摄像头
#include "../ui/ui_camera.h"

Camera::Camera(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Camera)
{
    ui->setupUi(this);

    //qDebug("Camera Device Check:%d",Camera::checkCameraAvailability());//摄像头驱动检测debug测试

    my_camera.reset(new QCamera(QMediaDevices::defaultVideoInput()));//新建并设置摄像头使用默认驱动
    my_captureSession.setCamera(my_camera.data());//捕获摄像头画面
    my_captureSession.setVideoOutput(ui->me);//设置捕捉画面显示窗口

    on_openvideo_clicked();
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



void Camera::on_openvideo_clicked()
{
      ui->me->show();
      my_camera->start();//启动摄像头
}


void Camera::on_closevideo_clicked(bool checked)
{
      my_camera->stop();
      //清空显示屏 假装清空
      ui->me->hide();//隐藏
}

