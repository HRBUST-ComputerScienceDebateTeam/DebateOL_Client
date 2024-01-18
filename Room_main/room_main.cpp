#include "room_main.h"
#include "../ui/ui_room_main.h"
#include<QMessageBox>
#include"../pkg/Video/videodeal.h"
#include"../pkg/thrift_json/thrift_json_config.h"
#include"../pkg/web/web.h"
#include <thread>
#include"../pkg/audioread/audioread.h"
#include"../pkg/audiowrite/audiowrite.h"
#include <mutex>
#include"../config.h"



std::map<int,std::string>  Room_main::m_map[9];
int Room_main::pos_id[9] = {0 , 1 , 3};
int Room_main::id_pos[9] = {0 , 1 , 2};


Room_main::Room_main(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Room_main)
{
    ui->setupUi(this);
    //音频

    m_pAudioRead = new AudioRead;

    m_pAudioWrite = new AudioWrite;

    connect(m_pAudioRead,SIGNAL(SIG_audioFrame(QByteArray))
            ,m_pAudioWrite,SLOT(slot_playAudio(QByteArray)));


    myid = 2;
    m_camera = new Camera;
    m_user_label[1] = ui->me;
    m_user_label[2] = ui->second;
    for(int i=1;i<3;i++)
    {
        m_user_video[i] = new VideoDeal(i , myid==i);
        connect(m_user_video[i],SIGNAL(SIG_RefreshFrame(int,int))
                ,this,SLOT(slot_RefreshFrame(int,int)));
        connect(m_user_video[i],SIGNAL(SIG_DownloadFrame(int ,int))
                ,this,SLOT(slot_DownloadFrame(int,int)));
    }
    connect(this,SIGNAL(SIG_setImage(int,QImage&))
            ,this,SLOT(slot_setImage(int,QImage&)));
    connect( m_camera,SIGNAL(SIG_UploadFrame(QImage))
            ,this,SLOT(slot_UploadFrame(QImage)));


}

void Room_main::paintEvent(QPaintEvent *event)
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

//消类
Room_main::~Room_main()
{
    delete ui;
}

//关闭事件
void  Room_main::closeEvent(QCloseEvent *event)
{
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

//对某个相框设置相片
void Room_main::slot_setImage(int userid,QImage &img)
{
    if(img.size() == QSize(0,0)) return;
    QPixmap pix = QPixmap :: fromImage(img);
    m_user_label[userid]->setPixmap(pix);
    m_user_label[userid]->update();

    qDebug() <<QDateTime::currentDateTime().toString("hh:mm:ss.zzz ") << "更新成功";

}


//相机开机
void Room_main::on_openvideo_clicked()
{
    m_camera->slot_openCamera();
}

//相机关机
void Room_main::on_closevideo_clicked()
{
    m_camera->slot_closeCamera();
}


//上传
void Room_main::slot_UploadFrame(QImage img)
{
    //qDebug()<<__func__;
    QPixmap pix = QPixmap :: fromImage(img);
    //更新本地
    m_user_label[myid]->setPixmap(pix);
    m_user_label[myid]->update();
    QByteArray ba;
    QBuffer qbuf(&ba); // QBuffer 与 QByteArray 字节数组联立联系
    img.save( &qbuf , "JPEG" , 50 ); //将图片的数据写入 ba

    //m_pClient->sendData(0,buf,nPackSize);
    QTime tm = QTime::currentTime();
    Video_Upload_SendInfo send;
    //QString str =QString(ba);
    send.info = ba.toStdString();
    send.min = tm.minute();
    send.sec = tm.second();
    send.msec = tm.msec();
    send.type = Video_Upload_SendInfo_TypeId;
    send.roomId = 10;
    send.userId = pos_id[myid];
    send.sendtime = send.min*60000 + send.sec * 10000 + send.msec;
    MYNET * np = MYNET::getinstance();
    np->Init(this);
    std::string s =  Video_Upload_SendInfo::Serialization(send);
    np->NETPOST(VIDEO_UPLOAD_POST_URL , s ,send.sendtime, &Room_main::SIGDEAL_UploadFrame);

}

//刷新
void Room_main::slot_RefreshFrame(int userid,int tim)
{
    if(m_map[userid].size()==0)
    {
        return;
    }
    auto it =m_map[userid].lower_bound(tim);
    if(it==m_map[userid].begin())
    {
        it = m_map[userid].end();
    }
    --it;

    QByteArray bt((it->second).c_str() ,(it->second).size()) ;
    QImage img;
    img.loadFromData(bt);
    //更新本地照片
    Q_EMIT SIG_setImage(userid,img);
}

//下载
void Room_main::slot_DownloadFrame(int userid , int tim)
{
//    std::thread thr(deal_Net_work_Download , userid , tim );
//    thr.detach();
    //qDebug()<<__func__;
    QTime tm = QTime::currentTime();
    Video_Download_SendInfo sendinfo;
    sendinfo.min = tm.minute();
    sendinfo.sec = tm.second();
    sendinfo.msec = tm.msec();
    sendinfo.type = Video_Download_SendInfo_TypeId;
    sendinfo.roomId = 10;
    sendinfo.userId = pos_id[userid];
    sendinfo.sendtime = sendinfo.min*60000 + sendinfo.sec*1000 + sendinfo.msec;

    MYNET::Init(this);
    MYNET * np = MYNET::getinstance();

    np->NETGET(np->GET_VIDEODL_URL(sendinfo) , sendinfo.sendtime ,  &Room_main::SIGDEAL_DownloadFrame);
}

void Room_main::on_pb_start_clicked()
{
    m_pAudioRead->start();
}


void Room_main::on_pb_pause_clicked()
{
    m_pAudioRead->pause();
}


//接受的是反序列化后的答案
void* Room_main::SIGDEAL_DownloadFrame(void * arg){
    //cout << __func__<<endl;
    Video_Download_RecvInfo * dlreinfo = (Video_Download_RecvInfo *)arg;

    if(dlreinfo->status != 200) {
        delete dlreinfo;
        return nullptr;
    }
    QByteArray bt(dlreinfo->info.c_str() ,dlreinfo->info.size()) ;
    //cout << QString::fromLatin1(bt).toLatin1().toStdString().length() <<endl;
    Room_main::m_map[id_pos[dlreinfo->userId]][dlreinfo->min*60000 + dlreinfo->sec*1000 + dlreinfo->msec] = QString::fromLatin1(bt).toLatin1().toStdString();
    qDebug() <<QDateTime::currentDateTime().toString("hh:mm:ss.zzz ") << "插入了" << QString("%1:%2:%3").arg(dlreinfo->min).arg(dlreinfo->sec).arg(dlreinfo->msec) << "的照片";
    delete dlreinfo;
    qDebug() <<QDateTime::currentDateTime().toString("hh:mm:ss.zzz ") << "下载成功";
}

void* Room_main::SIGDEAL_UploadFrame(void * arg){
    //cout << __func__<<endl;
    Video_Download_RecvInfo * dlreinfo = (Video_Download_RecvInfo *)arg;
    qDebug() <<QDateTime::currentDateTime().toString("hh:mm:ss.zzz ") <<"上传成功";
    qDebug() <<QDateTime::currentDateTime().toString("hh:mm:ss.zzz ") <<"上传了"<< QString("%1:%2:%3").arg(dlreinfo->min).arg(dlreinfo->sec).arg(dlreinfo->msec) << "的照片";
    return nullptr;
}
