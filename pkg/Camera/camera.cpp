#include "./camera.h"
#include "../Video/video_config.h"
Camera::Camera(QObject *parent)
    : QObject{parent}
{
    init_myCamera();

    //初始化定时器以及任务
    m_timer_upload =new QTimer;
    connect( m_timer_upload , SIGNAL(timeout())
            ,this , SLOT(slot_getCameraFrame()));
}

Camera:: ~Camera(){
    delete m_timer_upload;
}


//初始化摄像头
void Camera::init_myCamera(){
    qDebug("Camera Device Check:%d",Camera::checkCameraAvailability());//摄像头驱动检测debug测试
    my_camera.reset(new QCamera(QMediaDevices::defaultVideoInput()));//新建并设置摄像头使用默认驱动
    my_captureSession.setCamera(my_camera.data());//捕获摄像头画面
}

//检测摄像头驱动能否识别
bool Camera::checkCameraAvailability()
{
    if (QMediaDevices::videoInputs().count() > 0)
        return true;//检测到摄像头驱动
    else
        return false;//没有检测到摄像头驱动
}

//采集摄像头
void Camera::slot_getCameraFrame()
{
    //qDebug()<<__func__;
    Mat frame;
    if(!cap.read(frame))
    {
        return;
    }
    cvtColor(frame,frame,COLOR_BGR2RGB);

    //定义QImage对象，用于发送数据以及图片显示
    QImage image((unsigned const char*)frame.data,frame.cols,frame.rows,QImage::Format_RGB888);

    //转换为大小更小的图片
    image = image.scaled(IMAGE_WIDTH,IMAGE_HEIGHT,Qt::KeepAspectRatio);

    //发送图片
    Q_EMIT SIG_UploadFrame(image);
}

//打开摄像头
void Camera::slot_openCamera()
{
    //qDebug()<<__func__ ;
    m_timer_upload->start(1000/UPLOAD_RATE - 10);

    //打开摄像头
    cap.open(0);//默认设备

    if(!cap.isOpened())
    {
        QMessageBox::information(NULL,tr("提示"),tr("视频未打开"));
        return;
    }
}

//关闭摄像头
void Camera::slot_closeCamera()
{
    qDebug()<<__func__;
    m_timer_upload->stop();
    //关闭摄像头
    if(cap.isOpened())
    {
        cap.release();
    }

}
