#ifndef CAMERA_H
#define CAMERA_H

#include <QCamera>
#include <QPixmap>
#include <QVideoWidget>
#include <QMediaCaptureSession>
#include <QMediaDevices>
#include <QImageCapture>
#include <QMessageBox>
#include <QMediaRecorder>
#include"F:/opencv-build/opencv2/cvconfig.h"
#include"F:/opencv-build/opencv2/opencv_modules.hpp"
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include"opencv2/core/core.hpp"
//#include"F:/opencv4.8.0/bin/opencv2/cvconfig.h"
//#include"F:/opencv4.8.0/bin/opencv2/opencv_modules.hpp"
#include<QTime>
#include<QTimer>
#include <QObject>
#include<QImage>

using namespace cv;


//图片的宽高
#define IMAGE_WIDTH (240)
#define IMAGE_HEIGHT (240)
#define UPLOAD_RATE (30)


class Camera : public QObject
{
    Q_OBJECT
public:
    explicit Camera(QObject *parent = nullptr);
    ~Camera();
private:
    //检查摄像头是否有效
    bool checkCameraAvailability();
    //相机初始化
    void init_myCamera();


//槽函数
public slots:
    //获取摄像头的一帧相片
    void slot_getCameraFrame();
    //开启摄像头 并且上传照片
    void slot_openCamera();
    //关闭摄像头 并且结束上传照片
    void slot_closeCamera();

signals:
    void SIG_UploadFrame(QImage img);

public:
    QScopedPointer<QCamera> my_camera;
    QScopedPointer<QMediaRecorder> my_mediaRecorder;
    QMediaCaptureSession my_captureSession;

    //定时器
    QTimer *m_timer_upload;
    //摄像头
    cv::VideoCapture cap;
};



#endif // CAMERA_H
