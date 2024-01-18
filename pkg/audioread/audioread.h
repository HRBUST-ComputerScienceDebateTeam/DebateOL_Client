#ifndef AUDIOREAD_H
#define AUDIOREAD_H

#include<QObject>
#include"../../world.h"
//#include"../../tttmp.cpp"

class AudioRead: public QObject
{
    Q_OBJECT
public:
    explicit AudioRead(QObject *parent = 0);
public slots:
    //定时超时，从缓冲区读取音频数据
    void ReadMore();

    void start();
    void pause();

signals:
    void SIG_audioFrame(QByteArray bt);
private:
    QAudioSource * m_audio_in;//采集声卡
    QIODevice * m_buffer_in;//对应的缓冲区
    QTimer *m_timer;//计时器
    int m_audioState;
    QAudioFormat format;


};



#endif //AUDIOREAD_H
