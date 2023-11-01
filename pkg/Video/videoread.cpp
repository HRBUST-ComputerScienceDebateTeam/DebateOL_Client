#include "videoread.h"
#include<QMessageBox>
#include<QDebug>

VideoRead::VideoRead(QObject *parent)
    : QObject{parent}
{
    m_timer =new QTimer;
    connect( m_timer , SIGNAL(timeout())
            ,this , SLOT(slot_getVideoFrame()));
}

VideoRead::~VideoRead()
{
    if(m_timer)
    {
        m_timer -> stop();
        delete m_timer;
        m_timer = NULL;
    }
}
//采集摄像头
void VideoRead::slot_getVideoFrame()
{
    //从摄像头读取数据
    Mat frame;//Mat 对象存储
    if(!cap.read(frame))
    {
        return;
    }
    //Mat 图像不是显示和传输格式（RGB）
    //格式转换 opencv 采集的格式BGR 显示RGB
    cvtColor(frame,frame,CV_BGR2RGB);
    //定义QImage对象，用于发送数据以及图片显示
    QImage image((unsigned const char*)frame.data,frame.cols,frame.rows,QImage::Format_RGB888);
    //转换为大小更小的图片
    image = image.scaled(IMAGE_WIDTH,IMAGE_HEIGHT,Qt::KeepAspectRatio);
    //发送图片
    Q_EMIT SIG_sendVideoFrame(image);
}

void VideoRead::slot_openVideo()
{
    m_timer->start(1000/FRAME_RATE - 10);
    //打开摄像头
    cap.open(0);//默认设备
    if(!cap.isOpened())
    {
        QMessageBox::information(NULL,tr("提示"),tr("视频未打开"));
        return;
    }
}

void VideoRead::slot_closeVideo()
{
    m_timer ->stop();
    //关闭摄像头
    if(cap.isOpened())
    {
        cap.release();
    }
}
