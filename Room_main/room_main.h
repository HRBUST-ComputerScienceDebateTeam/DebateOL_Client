#ifndef ROOM_MAIN_H
#define ROOM_MAIN_H

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
#include"../pkg/Video/videodeal.h"
//#include"F:/opencv4.8.0/bin/opencv2/cvconfig.h"
//#include"F:/opencv4.8.0/bin/opencv2/opencv_modules.hpp"
#include"F:/opencv-build/opencv2/cvconfig.h"
#include"F:/opencv-build/opencv2/opencv_modules.hpp"
#include"../pkg/Camera/camera.h"
#include"../pkg/Audio/Audio.h"

#include<qpainter.h>
#include<QBuffer>
#include<QTime>

namespace Ui {
class Room_main;
}

class Room_main : public QMainWindow
{
    Q_OBJECT


signals:
    void SIG_close();
    void SIG_setImage(int userid,QImage& img);

public:
    explicit Room_main(QWidget *parent = nullptr);
    ~Room_main();
    void closeEvent(QCloseEvent *event);

public slots:
    //绘图相关
    void slot_setImage(int userid,QImage& img);
    void paintEvent(QPaintEvent *event);

    //照片 上传下载更新相关
    void slot_UploadFrame(QImage img);
    void slot_DownloadFrame(int userid ,int tim);
    void slot_RefreshFrame(int userid,int tim);

private slots:
    //控制相关
    void on_openvideo_clicked();
    void on_closevideo_clicked();

    void on_openaudio_clicked();

    void on_closeaudio_clicked();

public slots:
    void* SIGDEAL_DownloadFrame(void *);
    void* SIGDEAL_UploadFrame(void *);


public:
    //使用者辩位
    int myid;
    //本地更新队列
    static std::map<int,std::string>  m_map[9];

private:
    Ui::Room_main *ui;

    //各个相框
    QImage m_img;
    Camera * m_camera;
    Audio * m_audio;
    QLabel * m_user_label[9];
    VideoDeal * m_user_video[9];
};

#endif // ROOM_MAIN_H
