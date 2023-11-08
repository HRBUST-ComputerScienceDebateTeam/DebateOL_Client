#include "camera.h"//摄像头
#include "../ui/ui_camera.h"
#include<QMessageBox>
#include"../pkg/Video/videoread.h"
#include"../ckernel.h"
#include"../pkg/thrift_json/thrift_json_config.h"
#include"../pkg/web/web.h"
#include"../config.h"


Camera::Camera(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Camera)
{
    qDebug()<<__func__;
     ui->setupUi(this);

    qDebug("Camera Device Check:%d",Camera::checkCameraAvailability());//摄像头驱动检测debug测试

    //my_camera.reset(new QCamera(QMediaDevices::defaultVideoInput()));//新建并设置摄像头使用默认驱动
    //my_captureSession.setCamera(my_camera.data());//捕获摄像头画面
    //my_captureSession.setVideoOutput(ui->me);//设置捕捉画面显示窗口
    m_pVideoRead = new VideoRead();
    m_popen = new VideoRead();
    connect(m_pVideoRead,SIGNAL(SIG_sendvideoFrame(QImage))
            ,this,SLOT(slot_sendvideoFrame(QImage)));
    connect(m_popen,SIGNAL(SIG_dealVideoFrameRq())
            ,this,SLOT(slot_dealVideoFrameRq()));

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
    qDebug()<<__func__;
    delete ui;
}

//关闭事件
void  Camera::closeEvent(QCloseEvent *event)
{
    qDebug()<<__func__;
    if(QMessageBox::question(this,"提示","是否退出？")
        == QMessageBox::Yes)
    {
        Q_EMIT SIG_close();
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void Camera::slot_setImage(QImage &img)
{
    qDebug()<<__func__;
    //qDebug()<<m_img;
    qDebug()<<img;
    //m_img = img;
    QPixmap pix = QPixmap :: fromImage(img);
    //qDebug()<<m_img;
    ui->second->setPixmap(pix);
    ui->second->update();
}

void Camera::paintEvent(QPaintEvent *event)
{
    //画黑背景
    QPainter painter(this);
    painter.setBrush(Qt::black);
    painter.drawRect(-1,0,this->width()+1,this->height());

    if(m_img.size().height()<=0)return;
    //画视频帧
    //等比例缩放
    m_img =m_img.scaled(this->width(),
                         this->height()-ui->lb_name->height(),Qt::KeepAspectRatio);
    QPixmap pix=QPixmap::fromImage(m_img);
    int x=this->width()-pix.width();
    x=x/2;
    int y =this->height()-pix.height() - ui->lb_name->height();
    y=ui->lb_name->height()+y/2;
    painter.drawPixmap(QPoint(x,y),pix);
    painter.end();
}

/*void Camera::slot_refreshVideo(QImage &img)
{
    //qDebug()<<img;
    this->slot_setImage(img);
}*/


void Camera::on_openvideo_clicked()
{
    m_pVideoRead ->slot_openVideo();
    m_popen->slot_openVideo();
}


void Camera::on_closevideo_clicked()
{
      m_pVideoRead ->slot_closeVideo();
}


void Camera::slot_sendvideoFrame(QImage img)
{
      qDebug()<<__func__;
      QPixmap pix = QPixmap :: fromImage(img);
      //qDebug()<<img;
      ui->me->setPixmap(pix);
      //更新
      ui->me->update();
      //显示图片 todo
      //显示别人图片
      //slot_setImage(img);
      //压缩
      //压缩图片从 RGB24 格式压缩到 JPEG 格式, 发送出去
      QByteArray ba;
      QBuffer qbuf(&ba); // QBuffer 与 QByteArray 字节数组联立联系
      img.save( &qbuf , "JPEG" , 50 ); //将图片的数据写入 ba

      //写视频帧 发送

      ///视频数据帧
      ///成员描述
      /// int type;
      /// int userId;
      /// int roomId;
      /// int min;
      /// int sec;
      /// int msec;
      ///
      /*int nPackSize=6*sizeof(int)+ba.size();
      char *buf = new char[nPackSize];
      char *tmp= buf;

      *(int*)tmp = 1;
      tmp+=sizeof(int);
      *(int*)tmp = 1;
      tmp+=sizeof(int);
      *(int*)tmp = 1;
      tmp+=sizeof(int);
      //用于延迟过久舍弃帧的参考时间
      QTime tm = QTime::currentTime();
      *(int*)tmp = tm.minute();
      tmp +=sizeof(int);
      *(int*)tmp = tm.second();
      tmp +=sizeof(int);
      *(int*)tmp = tm.msec();
      tmp +=sizeof(int);

      memcpy(tmp,ba.data(),ba.size());*/

      //m_pClient->sendData(0,buf,nPackSize);
      QTime tm = QTime::currentTime();
      Video_Upload_SendInfo send;
      //QString str =QString(ba);
      send.info = ba.toStdString();
      send.min = tm.minute();
      send.sec = tm.second();
      send.msec = tm.msec();
      send.type = 1;
      send.roomId = 7;
      send.userId = 1;
      //qDebug()<<send.info;
      //qDebug()<<ba.size();
      //qDebug().noquote()<<Video_Upload_SendInfo::Serialization(send);
      //cout<<send.info;
      //qDebug()<<Video_Upload_SendInfo::Serialization(send).size();
      //qDebug()<<send.info.size();
      //NETPOST(VIDEO_UPLOAD_POST_URL,Video_Upload_SendInfo::Serialization(send));
      QString ULret = NETPOST(VIDEO_UPLOAD_POST_URL , Video_Upload_SendInfo::Serialization(send));
      Video_Upload_RecvInfo ulreinfo = Video_Upload_RecvInfo::Deserialization(ULret.toStdString());
      /*qDebug() << "返回的请求状态 ： " << ulreinfo.status;
      qDebug() << "返回的房间号 ： " << ulreinfo.roomId;
      qDebug() << "返回的用户号 ： " << ulreinfo.userId;
      qDebug() << "返回的时间 ： " << ulreinfo.min << "-" <<ulreinfo.sec << "-" << ulreinfo.sec;*/

}

void Camera::slot_dealVideoFrameRq()
{
      qDebug()<<__func__;
      /*char *tmp = buf;
      tmp+=sizeof(int);
      int userId = *(int*)tmp;
      tmp+=sizeof(int);
      int roomId = *(int*)tmp;
      tmp+=sizeof(int);

      tmp+=sizeof(int);
      tmp+=sizeof(int);
      tmp+=sizeof(int);

      int datalen = len - 6*sizeof(int);
      QByteArray bt(tmp,datalen);
      QImage img;
      img.loadFromData(bt);

      slot_refreshVideo(img);*/
      QTime tm = QTime::currentTime();
      Video_Download_SendInfo sendinfo;
      sendinfo.min = tm.minute();
      sendinfo.sec = tm.second();
      sendinfo.msec = tm.msec();
      sendinfo.type = 1;
      sendinfo.roomId = 7;
      sendinfo.userId = 2;


      QString DLret = NETGET(GET_VIDEODL_URL(sendinfo));
      Video_Download_RecvInfo dlreinfo = Video_Download_RecvInfo::Deserialization(DLret.toStdString());
      /*qDebug() << "返回的请求状态 ： " << dlreinfo.status;
      qDebug() << "返回的房间号 ： " << dlreinfo.roomId;
      qDebug() << "返回的用户号 ： " << dlreinfo.userId;
      qDebug() << "返回的时间 ： " << dlreinfo.min << "-" <<dlreinfo.sec << "-" << dlreinfo.sec;
      qDebug()<< "返回的信息" <<QString().fromStdString(dlreinfo.info);*/
      /*QByteArray ba;
      QBuffer qbuf(&ba); // QBuffer 与 QByteArray 字节数组联立联系
      img.save( &qbuf , "JPEG" , 50 ); //将图片的数据写入 ba*/

      QByteArray bt=QByteArray(dlreinfo.info.c_str(),dlreinfo.info.size());
      QImage img;
      img.loadFromData(bt);

      //qDebug()<<bt.size();
      //qDebug()<<img.size();
      slot_setImage(img);
      /*int datalen = len - 6*sizeof(int);
      QByteArray bt(tmp,datalen);
      QImage img;
      img.loadFromData(bt);
        */
      //slot_refreshVideo(img);
      /*QByteArray imageData = QByteArray::fromBase64(data.toLatin1());
      QImage image;
      image.loadFromData(imageData);
      return image;*/
}



