#include "room_main.h"
#include "../ui/ui_room_main.h"
#include<QMessageBox>
#include"../pkg/Video/videodeal.h"
#include"../pkg/thrift_json/thrift_json_config.h"
#include"../pkg/web/web.h"
#include <thread>
#include <mutex>

#include"../config.h"

int now_threadnum = 0;
std::mutex Lock;
void Add_threadnum(){
    Lock.lock();
    now_threadnum++;
    Lock.unlock();
}
void Sub_threadnum(){
    Lock.lock();
    now_threadnum--;
    Lock.unlock();
}
int Get_threadnum(){
    Lock.lock();
    int val = now_threadnum;
    Lock.unlock();
    return val;
}


Room_main::Room_main(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Room_main)
{
    ui->setupUi(this);

    myid = 1;
    m_camera = new Camera;
    m_audio = new Audio;
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
std::map<int,std::string>  Room_main::m_map[9];

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
    qDebug() << "现在的线程数量：" << Get_threadnum();
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


//声音采集开启
void Room_main::on_openaudio_clicked()
{
    qDebug()<<__func__;
    m_audio->slot_openAudio();
}

//声音采集关闭
void Room_main::on_closeaudio_clicked()
{
    m_audio->slot_closeAudio();
}

//上传
void Room_main::slot_UploadFrame(QImage img)
{

    //qDebug()<<__func__;
    QPixmap pix = QPixmap :: fromImage(img);
    //更新本地
    m_user_label[myid]->setPixmap(pix);
    m_user_label[myid]->update();
    if(Get_threadnum() >= 13) return;
    std::thread tmpthread(deal_Net_work_Upload , img);
    tmpthread.detach();
    Add_threadnum();
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
    if(Get_threadnum() >= 13) return;
    std::thread thr(deal_Net_work_Download , userid , tim );
    thr.detach();
    Add_threadnum();
}


void Room_main::deal_Net_work_Upload(QImage img ){
    //qDebug()<<__func__;
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
    send.type = 1;
    send.roomId = 7;
    send.userId = 2;
    NETPOST(VIDEO_UPLOAD_POST_URL , Video_Upload_SendInfo::Serialization(send));
    Sub_threadnum();
}



void Room_main::deal_Net_work_Download(int userid , int tim ){
    //qDebug()<<__func__;
    QTime tm = QTime::currentTime();
    Video_Download_SendInfo sendinfo;
    sendinfo.min = tm.minute();
    sendinfo.sec = tm.second();
    sendinfo.msec = tm.msec();
    sendinfo.type = 1;
    sendinfo.roomId = 7;
    sendinfo.userId = 2;

    QString DLret = NETGET(GET_VIDEODL_URL(sendinfo));
    if(DLret == "") {
        Sub_threadnum();
        return;
    }
    //qDebug()<<DLret.toStdString().size();

    Video_Download_RecvInfo dlreinfo = Video_Download_RecvInfo::Deserialization(DLret.toStdString());
    if(dlreinfo.status != 200) {
        Sub_threadnum();
        return;
    }
    QByteArray bt(dlreinfo.info.c_str() ,dlreinfo.info.size()) ;

    //Room_main::m_map[userid][1] = "1";
//    qDebug()<<userid;
//    qDebug()<<tim;
//    qDebug() << QString::fromLatin1(bt).toLatin1().toStdString().size();
//    qDebug() << m_map[userid].size();
    Room_main::m_map[userid][tim] = QString::fromLatin1(bt).toLatin1().toStdString();
    Sub_threadnum();
}

