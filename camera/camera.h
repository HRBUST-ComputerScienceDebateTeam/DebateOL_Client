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
//#include"F:/opencv4.8.0/bin/opencv2/cvconfig.h"
//#include"F:/opencv4.8.0/bin/opencv2/opencv_modules.hpp"
#include"F:/opencv-build/opencv2/cvconfig.h"
#include"F:/opencv-build/opencv2/opencv_modules.hpp"
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
    void SIG_setImage(int userid,QImage& img);
public:
    Camera(QWidget *parent = nullptr);
    ~Camera();

    void closeEvent(QCloseEvent *event);
public slots:
    void slot_setImage(int userid,QImage& img);
    void paintEvent(QPaintEvent *event);
    //刷新图片显示
    //void slot_refreshVideo(QImage &img);
    void slot_dealVideoFrameRq(int userid ,int tim);
private slots:
    void on_openvideo_clicked();
    void on_closevideo_clicked();
    void slot_sendvideoFrame(QImage img);
    void slot_refresh(int userid,int tim);

public:
    static void deal_Net_work(int userid , int tim);
    //视频帧处理
/*signals:
    void SIG_videoPause();
    void SIG_videoStart();*/
private:
    int myid;
    Ui::Camera *ui;
    QLabel * m_user_label[9];
    QScopedPointer<QCamera> my_camera;
    QScopedPointer<QMediaRecorder> my_mediaRecorder;
    QMediaCaptureSession my_captureSession;
    QImage m_img;
    VideoRead * m_user_video[9];

    bool checkCameraAvailability(void);
public:
     static std::map<int,std::string>  m_map[9];

};
#endif // CAMERA_H



