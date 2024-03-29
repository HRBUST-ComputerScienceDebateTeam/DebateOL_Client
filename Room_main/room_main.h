﻿#ifndef ROOM_MAIN_H
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
#include"../pkg/audioread/audioread.h"
#include"../pkg/audiowrite/audiowrite.h"
#include"../pkg/JWT/jwt.h"

#include"../pkg/Audio/audiodeal.h"
#include"../pkg/Camera/camera.h"
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
    void SIG_closeroom();
    void SIG_setImage(int userpos,QImage& img);
    void SIG_SendDebatePostoRoom();

public:
    //explicit Room_main(QWidget *parent = nullptr);
    explicit Room_main( int roomid , string roomnum , int userid , int userpos \
                       ,  string jwt_token1 , string jwt_token2 ,QWidget *parent = nullptr );
    ~Room_main();
    void closeEvent(QCloseEvent *event);

public slots:
    //绘图相关
    void slot_setImage(int userpos,QImage& img);
    void paintEvent(QPaintEvent *event);

    //照片 上传下载更新相关
    void slot_UploadFrame(QImage img);
    void slot_DownloadFrame(int userpos ,int tim);
    void slot_RefreshFrame(int userpos,int tim);

    //发送音频帧
    void slot_UploadaudioFrame(QByteArray ba);
    //音频下载
    void slot_DownloadaudioFrame(int userpos ,int tim);
    //音频刷新
    void slot_AudioRefreshFrame(int userpos,int tim);

    //定时器 发送获取辩位信息
    void slot_getDebatePos();
    //调用以设置辩位
    void ToUpdateDebatePos(string s);
private slots:
    //控制相关
    void on_openvideo_clicked();
    void on_closevideo_clicked();

    void on_pb_start_clicked();
    void on_pb_pause_clicked();




public slots:
    void* SIGDEAL_DownloadFrame(void *);
    void* SIGDEAL_UploadFrame(void *);
    void* SIGDEAL_UploadAudioFrame(void *);
    void* SIGDEAL_DownloadAudioFrame(void *);

public:
    //使用者辩位
    int mypos;

    //房间号
    int myroomid;
    string myroomnum;

    //使用者id;
    int myid;

    //使用者token
    string my_jwt_token;
    string my_refresh_jwt_token;


    //本地更新队列
    static std::map<int,std::string>  m_map[9];
    static std::map<int,std::string>  m_map_Audio[9];
    static int pos_id[9];
    static int id_pos[9];

private:
    Ui::Room_main *ui;

    //各个相框
    QImage m_img;
    Camera * m_camera;
    QLabel * m_user_label[9];
    VideoDeal * m_user_video[9];
    audiodeal * m_user_audio[9];

    AudioRead *m_pAudioRead;
    //AudioWrite *m_pAudioWrite;
    AudioWrite *m_pAudioWrite[9];
public:
    //定时器 - 更新房间信息
    QTimer *m_timer_getDebatePos;
};

#endif // ROOM_MAIN_H
