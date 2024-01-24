#include "audiodeal.h"
#include<QTime>
#include <bits/stdc++.h>
using namespace std;

audiodeal::audiodeal(int pos , bool ishost, int id, QObject *parent)\
    : QObject{parent}
{
    mypos = pos;
    myid = id;
    is_host = ishost;
    m_timer_Audio_toRefresh = nullptr;
    m_timer_Audio_toDownload = nullptr;
    if(is_host==false){
        m_timer_Audio_toRefresh = new QTimer;
        connect( m_timer_Audio_toRefresh , SIGNAL(timeout())
                ,this , SLOT(slot_AudioRefreshFrame()));
        m_timer_Audio_toRefresh->start(1000/FRAME_RATE - 10);

        m_timer_Audio_toDownload = new QTimer;
        connect( m_timer_Audio_toDownload , SIGNAL(timeout())
                ,this , SLOT(slot_AudioDownloadFrame()));
        m_timer_Audio_toDownload->start(1000/Download_RATE - 10);
    }
}

audiodeal::~audiodeal()
{
    if(m_timer_Audio_toRefresh)
    {
        if(m_timer_Audio_toRefresh->isActive() == true){
            m_timer_Audio_toRefresh -> stop();
        }
//        delete m_timer_Audio_toRefresh;
//        m_timer_Audio_toRefresh = NULL;
    }

    if(m_timer_Audio_toDownload)
    {
        if(m_timer_Audio_toDownload->isActive() == true){
            m_timer_Audio_toDownload -> stop();
        }

//        delete m_timer_Audio_toDownload;
//        m_timer_Audio_toDownload = NULL;
    }
}

void audiodeal::slot_AudioRefreshFrame()
{
    //qDebug()<<__func__<<mypos;
    QTime tm = QTime::currentTime();
    int timenum = tm.msec() + tm.second()*1000 + tm.minute()*60000;
    if(myid!= 0){
        Q_EMIT SIG_AudioRefreshFrame(mypos , timenum);
    }
}

void audiodeal::slot_AudioDownloadFrame()
{
    //qDebug()<<__func__<<mypos;
    QTime tm = QTime::currentTime();
    int timenum = tm.msec() + tm.second()*1000 + tm.minute()*60000;
    if(myid!= 0){
        Q_EMIT SIG_AudioDownloadFrame(mypos , timenum);
    }

}
