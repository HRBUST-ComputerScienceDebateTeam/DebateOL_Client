#ifndef VIDEOREAD_H
#define VIDEOREAD_H

#include <QObject>
#include<QImage>
#include<QTimer>
#include"./common.h"
#include<map>


//图片的宽高
#define IMAGE_WIDTH (240)
#define IMAGE_HEIGHT (240)

class VideoRead : public QObject
{
    Q_OBJECT
public:
    explicit VideoRead(int , bool , QObject *parent = nullptr);
    ~VideoRead();
signals:
    void SIG_sendvideoFrame(QImage img);
    void SIG_dealVideoFrameRq(int userid ,int tim);
    void SIG_refresh(int userid,int tim);
public slots:
    void slot_torefresh();
    void slot_getVideoFrame();
    void slot_Download();
    void slot_openVideo();
    void slot_closeVideo();

private:
    QTimer *m_timer;
    int myid;
    bool is_host;
    QTimer *m_timer_toupdata;
    QTimer *m_timer_toDownload;
    //opencv获取图片对象
    cv::VideoCapture cap;
};

#endif // VIDEOREAD_H
