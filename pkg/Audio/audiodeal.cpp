#include "audiodeal.h"
#include<QTime>

audiodeal::audiodeal(int pos , bool ishost,QObject *parent)\
    : QObject{parent}
{
    mypos = pos;
}

void audiodeal::slot_AudioDownloadFrame()
{
    //qDebug()<<__func__<<mypos;
    QTime tm = QTime::currentTime();
    int timenum = tm.msec() + tm.second()*1000 + tm.minute()*60000;
    Q_EMIT SIG_AudioDownloadFrame(mypos , timenum);
}
