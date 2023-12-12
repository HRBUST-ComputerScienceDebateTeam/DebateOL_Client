#include "videodeal.h"
#include<QMessageBox>
#include<QDebug>
#include<QTime>


VideoDeal::VideoDeal(int id , bool ishost,QObject *parent)
    : QObject{parent}
{

    myid = id;
    is_host = ishost;

    if(is_host==false){
        m_timer_toRefresh = new QTimer;
        connect( m_timer_toRefresh , SIGNAL(timeout())
                ,this , SLOT(slot_RefreshFrame()));
        m_timer_toRefresh->start(1000/FRAME_RATE - 10);

        m_timer_toDownload = new QTimer;
        connect( m_timer_toDownload , SIGNAL(timeout())
                ,this , SLOT(slot_DownloadFrame()));
        m_timer_toDownload->start(1000/Download_RATE - 10);
    }
}


VideoDeal::~VideoDeal()
{
    if(m_timer_toRefresh)
    {
        m_timer_toRefresh -> stop();
        delete m_timer_toRefresh;
        m_timer_toRefresh = NULL;
    }

    if(m_timer_toDownload)
    {
        m_timer_toDownload -> stop();
        delete m_timer_toDownload;
        m_timer_toDownload = NULL;
    }
}

void VideoDeal::slot_DownloadFrame()
{
    qDebug()<<__func__<<myid;
    QTime tm = QTime::currentTime();
    int timenum = tm.msec() + tm.second()*1000 + tm.minute()*60000;
    Q_EMIT SIG_DownloadFrame(myid , timenum);
}


void VideoDeal::slot_RefreshFrame(){
    qDebug()<<__func__<<myid;
    QTime tm = QTime::currentTime();
    int timenum = tm.msec() + tm.second()*1000 + tm.minute()*60000;
    Q_EMIT SIG_RefreshFrame(myid , timenum);
}


