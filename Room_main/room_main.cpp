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
std::map<int,std::string>  Room_main::m_map_Audio[9];
int Room_main::pos_id[9] = {/*0*/0 , /*1*/0 , /*2*/0 , /*3*/0 , /*4*/0 , /*5*/0 , /*6*/0 , /*7*/0 , /*8*/0  };
int Room_main::id_pos[9] = {/*0*/0 , /*1*/0 , /*2*/0 , /*3*/0 , /*4*/0 , /*5*/0 , /*6*/0 , /*7*/0 , /*8*/0 };


Room_main::Room_main(int roomid , string roomnum , int userid , int userpos , string jwt_token1 , string jwt_token2 ,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Room_main)
{
    ui->setupUi(this);
    //使用者辩位
    mypos = userpos;
    myroomnum = roomnum;
    myroomid = roomid;
    myid = userid;


    //定时器 获取辩位
    m_timer_getDebatePos = new QTimer;
    connect( m_timer_getDebatePos , SIGNAL(timeout())
            ,this , SLOT(slot_getDebatePos()));
    m_timer_getDebatePos->start(1000);
    //音频
    m_pAudioRead = new AudioRead;
    m_pAudioWrite[mypos] = new AudioWrite;

    //m_pAudioWrite = new AudioWrite;

    connect(m_pAudioRead,SIGNAL(SIG_audioFrame(QByteArray))
            ,m_pAudioWrite[mypos],SLOT(slot_playAudio(QByteArray)));
    connect(m_pAudioRead,SIGNAL(SIG_audioFrame(QByteArray))
            ,this,SLOT(slot_UploadaudioFrame(QByteArray)));


    //使用者token
    my_jwt_token = jwt_token1;
    my_refresh_jwt_token = jwt_token2;

    m_camera = new Camera;

    //定时器更新辩位


    //相框的设定
    m_user_label[1] = ui->qlabel;
    m_user_label[2] = ui->qlabel_2;
    m_user_label[3] = ui->qlabel_3;
    m_user_label[4] = ui->qlabel_4;
    m_user_label[5] = ui->qlabel_5;
    m_user_label[6] = ui->qlabel_6;
    m_user_label[7] = ui->qlabel_7;
    m_user_label[8] = ui->qlabel_8;
    for(int i=1;i<=8;i++)
    {
        m_user_video[i] = new VideoDeal(i ,mypos==i, 0  , this);
        m_user_audio[i] = new audiodeal(i ,mypos==i, 0  , this);
        if(i != mypos){
            m_pAudioWrite[i] = new AudioWrite;
        }

        connect(m_user_video[i],SIGNAL(SIG_RefreshFrame(int,int))
                ,this,SLOT(slot_RefreshFrame(int,int)));
        connect(m_user_video[i],SIGNAL(SIG_DownloadFrame(int,int))
                ,this,SLOT(slot_DownloadFrame(int,int)));
        connect(m_user_audio[i],SIGNAL(SIG_AudioDownloadFrame(int,int))
                ,this,SLOT(slot_DownloadaudioFrame(int,int)));
        connect(m_user_audio[i],SIGNAL(SIG_AudioRefreshFrame(int,int))
                ,this,SLOT(slot_AudioRefreshFrame(int,int)));
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
                         this->height()-ui->lb_roomnum->height(),Qt::KeepAspectRatio);
    QPixmap pix=QPixmap::fromImage(m_img);
    int x=this->width()-pix.width();
    x=x/2;
    int y =this->height()-pix.height() - ui->lb_roomnum->height();
    y=ui->lb_roomnum->height()+y/2;
    painter.drawPixmap(QPoint(x,y),pix);
    painter.end();
}

//消类
Room_main::~Room_main(){
    if(m_timer_getDebatePos){
        m_timer_getDebatePos -> stop();
    }
    for(int i = 1;i<=8;i++){
        if(m_pAudioWrite[i]){
            delete m_pAudioWrite[i];
        }
        if(m_user_audio[i]){
            delete m_user_audio[i];
        }
        if(m_user_video[i]){
            delete m_user_video[i];
        }
        if(m_user_label[i]){
            delete m_user_label[i];
        }

    }
    if(m_camera){
        delete m_camera;
    }
    if(m_pAudioRead){
        delete m_pAudioRead;
    }
    delete ui;
}

//关闭事件
void  Room_main::closeEvent(QCloseEvent *event)
{
    if(QMessageBox::question(this,"提示","是否退出？")
        == QMessageBox::Yes)
    {
        Q_EMIT SIG_closeroom();
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

//对某个相框设置相片
void Room_main::slot_setImage(int userpos,QImage &img)
{
    if(img.size() == QSize(0,0)) return;
    QPixmap pix = QPixmap :: fromImage(img);
    m_user_label[userpos]->setPixmap(pix);
    m_user_label[userpos]->update();

    qDebug() <<QDateTime::currentDateTime().toString("hh:mm:ss.zzz ") << "更新成功";

}


//定时器 发送获取辩位信息
void Room_main::slot_getDebatePos(){
    Q_EMIT SIG_SendDebatePostoRoom();
}

//调用以设置辩位
void Room_main::ToUpdateDebatePos(string s){
    map<string , string > mp = JsonstringToMap(s);
    for(auto it:mp){
        pos_id[stoi(it.second)] = stoi(it.first);
        id_pos[stoi(it.first)] = stoi(it.second);
    }
    for(int i = 1;i<=8;i++){
        if(pos_id[i] != 0){
            m_user_video[i]->myid = pos_id[i];
            m_user_audio[i]->myid = pos_id[i];
        }
    }
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


//视频上传
void Room_main::slot_UploadFrame(QImage img)
{
    //qDebug()<<__func__;
    QPixmap pix = QPixmap :: fromImage(img);
    //更新本地
    m_user_label[mypos]->setPixmap(pix);
    m_user_label[mypos]->update();
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
    send.roomId = myroomid;
    send.userId = myid;
    send.sendtime = send.min*60000 + send.sec * 10000 + send.msec;
    std::string s =  Video_Upload_SendInfo::Serialization(send);
    //获得单例指针
    MYNET_ROOM::Init(this);//安全
    MYNET_ROOM * np = MYNET_ROOM::getinstance();

    //url , 序列化信息 回调函数
    np->NETPOST(VIDEO_UPLOAD_POST_URL , s ,send.sendtime, &Room_main::SIGDEAL_UploadFrame);
}

//视频刷新
void Room_main::slot_RefreshFrame(int userpos,int tim)
{
    if(m_map[pos_id[userpos]].size()==0)
    {
        return;
    }
    auto it =m_map[pos_id[userpos]].lower_bound(tim);
    if(it==m_map[pos_id[userpos]].begin())
    {
        it = m_map[pos_id[userpos]].end();
    }
    --it;

    QByteArray bt((it->second).c_str() ,(it->second).size()) ;
    QImage img;
    img.loadFromData(bt);
    //更新本地照片
    Q_EMIT SIG_setImage(userpos,img);
}

//视频下载
void Room_main::slot_DownloadFrame(int userpos , int tim)
{
    //    std::thread thr(deal_Net_work_Download , userpos , tim );
    //    thr.detach();
    //qDebug()<<__func__;
    QTime tm = QTime::currentTime();
    Video_Download_SendInfo sendinfo;
    sendinfo.min = tm.minute();
    sendinfo.sec = tm.second();
    sendinfo.msec = tm.msec();
    sendinfo.type = Video_Download_SendInfo_TypeId;
    sendinfo.roomId = myroomid;
    sendinfo.userId = pos_id[userpos];
    sendinfo.sendtime = sendinfo.min*60000 + sendinfo.sec*1000 + sendinfo.msec;

    MYNET_ROOM::Init(this);
    MYNET_ROOM * np = MYNET_ROOM::getinstance();
    std::string s =  Video_Download_SendInfo::Serialization(sendinfo);
    np->NETPOST(VIDEO_DOWNLOAD_POST_URL , s , sendinfo.sendtime ,  &Room_main::SIGDEAL_DownloadFrame);
}




//音频上传
void Room_main::slot_UploadaudioFrame(QByteArray ba)
{
    //m_pClient->sendData(0,buf,nPackSize);
    QTime tm = QTime::currentTime();
    Audio_Upload_SendInfo send;
    //QString str =QString(ba);
    send.info = ba.toStdString();
    send.min = tm.minute();
    send.sec = tm.second();
    send.msec = tm.msec();
    send.type = Audio_Upload_SendInfo_TypeId;
    send.roomId = myroomid;
    send.userId = myid;
    send.sendtime = send.min*60000 + send.sec * 1000 + send.msec;
    std::string s =  Audio_Upload_SendInfo::Serialization(send);
    //获得单例指针
    MYNET_ROOM::Init(this);//安全
    MYNET_ROOM * np = MYNET_ROOM::getinstance();

    //url , 序列化信息 回调函数
    np->NETPOST(AUDIO_UPLOAD_POST_URL , s ,send.sendtime, &Room_main::SIGDEAL_UploadAudioFrame);
}
//音频下载
void Room_main::slot_DownloadaudioFrame(int userpos, int tim)
{
    QTime tm = QTime::currentTime();
    Audio_Download_SendInfo sendinfo;
    sendinfo.min = tm.minute();
    sendinfo.sec = tm.second();
    sendinfo.msec = tm.msec();
    sendinfo.type = Audio_Download_SendInfo_TypeId;
    sendinfo.roomId = myroomid;
    sendinfo.userId = pos_id[userpos];
    sendinfo.sendtime = sendinfo.min*60000 + sendinfo.sec*1000 + sendinfo.msec;

    MYNET_ROOM::Init(this);
    MYNET_ROOM * np = MYNET_ROOM::getinstance();

    np->NETGET(AUDIO_DOWNLOAD_POST_URL , sendinfo.sendtime ,  &Room_main::SIGDEAL_DownloadAudioFrame);
}
//音频刷新
void Room_main::slot_AudioRefreshFrame(int userpos,int tim){
    if(m_map_Audio[pos_id[userpos]].size()==0)
    {
        return;
    }
    auto it =m_map_Audio[pos_id[userpos]].lower_bound(tim);
    if(it==m_map_Audio[pos_id[userpos]].begin())
    {
        it = m_map_Audio[pos_id[userpos]].end();
    }
    --it;
    //放出声音

    QByteArray bt((it->second).c_str() ,(it->second).size()) ;
    m_pAudioWrite[userpos]->slot_playAudio(bt);
}



void Room_main::on_pb_start_clicked()
{
    m_pAudioRead->start();
}


void Room_main::on_pb_pause_clicked()
{
    m_pAudioRead->pause();
}

// 回调函数
//接受的是反序列化后的答案
//不要求是槽函数 不要求静态
void* Room_main::SIGDEAL_DownloadFrame(void * arg){
    //cout << __func__<<endl;
    Video_Download_RecvInfo * dlreinfo = (Video_Download_RecvInfo *)arg;
    if(dlreinfo->status == 300){
        cout << "NO photo now !" <<endl;
        delete dlreinfo;
        return nullptr;
    }
    if(dlreinfo->status != 200) {
        delete dlreinfo;
        return nullptr;
    }
    if(dlreinfo->info.empty()){
        delete dlreinfo;
        return nullptr;
    }
    QByteArray bt(dlreinfo->info.c_str() ,dlreinfo->info.size()) ;
    //cout << QString::fromLatin1(bt).toLatin1().toStdString().length() <<endl;
    Room_main::m_map[dlreinfo->userId][dlreinfo->min*60000 + dlreinfo->sec*1000 + dlreinfo->msec] = QString::fromLatin1(bt).toLatin1().toStdString();
    qDebug() <<QDateTime::currentDateTime().toString("hh:mm:ss.zzz ") << "插入了" << QString("%1:%2:%3").arg(dlreinfo->min).arg(dlreinfo->sec).arg(dlreinfo->msec) << "的照片";
    delete dlreinfo;
    qDebug() <<QDateTime::currentDateTime().toString("hh:mm:ss.zzz ") << "下载成功";
}

void* Room_main::SIGDEAL_UploadFrame(void * arg){
    //cout << __func__<<endl;
    Video_Download_RecvInfo * dlreinfo = (Video_Download_RecvInfo *)arg;
    qDebug() <<QDateTime::currentDateTime().toString("hh:mm:ss.zzz ") <<"上传了"<< QString("%1:%2:%3").arg(dlreinfo->min).arg(dlreinfo->sec).arg(dlreinfo->msec) << "的照片";
    return nullptr;
}

void* Room_main::SIGDEAL_UploadAudioFrame(void * arg)
{
    Audio_Download_RecvInfo * dlreinfo = (Audio_Download_RecvInfo *)arg;
    qDebug() <<QDateTime::currentDateTime().toString("hh:mm:ss.zzz ") <<"上传了"<< QString("%1:%2:%3").arg(dlreinfo->min).arg(dlreinfo->sec).arg(dlreinfo->msec) << "的音频";
    return nullptr;
}

void *Room_main::SIGDEAL_DownloadAudioFrame(void *arg)
{
    Audio_Download_RecvInfo * dlreinfo = (Audio_Download_RecvInfo *)arg;

    if(dlreinfo->status == 300){
        cout << "NO Audio now !" <<endl;
        delete dlreinfo;
        return nullptr;
    }

    if(dlreinfo->status != 200) {
        delete dlreinfo;
        return nullptr;
    }

    if(dlreinfo->info.empty()){
        delete dlreinfo;
        return nullptr;
    }

    QByteArray bt(dlreinfo->info.c_str() ,dlreinfo->info.size()) ;
    //cout << QString::fromLatin1(bt).toLatin1().toStdString().length() <<endl;
    Room_main::m_map_Audio[dlreinfo->userId][dlreinfo->min*60000 + dlreinfo->sec*1000 + dlreinfo->msec] = QString::fromLatin1(bt).toLatin1().toStdString();
    qDebug() <<QDateTime::currentDateTime().toString("hh:mm:ss.zzz ") << "插入了" << QString("%1:%2:%3").arg(dlreinfo->min).arg(dlreinfo->sec).arg(dlreinfo->msec) << "的音频";
    delete dlreinfo;

}

