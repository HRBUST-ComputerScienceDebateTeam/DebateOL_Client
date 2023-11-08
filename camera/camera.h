//icysamon@outlook.com

#ifndef CAMERA_H
#define CAMERA_H

#include <QMainWindow>
#include <QCamera>
#include <QPixmap>
#include <QVideoWidget>
#include <QMediaCaptureSession>
#include <QMediaDevices>
#include <QImageCapture>
#include <QMediaRecorder>
#include<QCloseEvent>
#include<Qlabel>
#include"../pkg/Video/videoread.h"
#include"F:/opencv4.8.0/bin/opencv2/cvconfig.h"
#include"F:/opencv4.8.0/bin/opencv2/opencv_modules.hpp"
#include<qpainter.h>
#include<QBuffer>
#include<QTime>



QT_BEGIN_NAMESPACE
namespace Ui { class Camera; }
QT_END_NAMESPACE


class Camera : public QMainWindow
{
    Q_OBJECT
signals:
    void SIG_close();
public:
    Camera(QWidget *parent = nullptr);
    ~Camera();

    void closeEvent(QCloseEvent *event);
public slots:
    void slot_setImage(QImage& img);
    void paintEvent(QPaintEvent *event);
    //刷新图片显示
    //void slot_refreshVideo(QImage &img);
    void slot_dealVideoFrameRq();
private slots:
    void on_openvideo_clicked();
    void on_closevideo_clicked();
    void slot_sendvideoFrame(QImage img);
    //视频帧处理
/*signals:
    void SIG_videoPause();
    void SIG_videoStart();*/
private:
    Ui::Camera *ui;
    //QScopedPointer<QCamera> my_camera;
    //QScopedPointer<QMediaRecorder> my_mediaRecorder;
    //QMediaCaptureSession my_captureSession;
    QImage m_img;
    VideoRead * m_pVideoRead;
    VideoRead * m_popen;

    bool checkCameraAvailability(void);

};
#endif // CAMERA_H



