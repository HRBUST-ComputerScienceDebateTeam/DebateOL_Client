#include"audioread.h"



AudioRead::AudioRead(QObject *parent) : QObject(parent)
{
    //speex 初始化
    /*speex_bits_init(&bits_enc);
    Enc_State = speex_encoder_init(speex_lib_get_mode(SPEEX_MODEID_NB));*/
//设置压缩质量
//#define SPEEX_QUALITY (8)
    //设置质量为 8(15kbps)
    /*int tmp = SPEEX_QUALITY;
    speex_encoder_ctl(Enc_State,SPEEX_SET_QUALITY,&tmp);*/


    //声卡采样格式
    format.setSampleRate(8000);
    format.setChannelCount(1);
    format.setSampleFormat(QAudioFormat::Int16);
    QAudioDevice info = QMediaDevices::defaultAudioInput();
    //QAudioDevice::defaultInputDevice()
    /*format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);
    QAudioDevice info = QAudioDevice::defaultInputDevice();
    if (!info.isFormatSupported(format)) {
        QMessageBox::information(NULL , "提示", "打开音频设备失败");
        format = info.nearestFormat(format);
    }*/
    m_audio_in = NULL;
    m_buffer_in = NULL;

    m_timer = new QTimer;
    connect( m_timer , SIGNAL(timeout()),
            this,SLOT(ReadMore()));


    m_audioState = stopped;   
}

AudioRead::~AudioRead()
{
    if(m_timer)
    {
        m_timer->stop();
        delete m_timer;
    }
    if(m_audio_in)
    {
        m_audio_in->stop();
        delete m_audio_in;
    }
}

void AudioRead::ReadMore()
{
    //qDebug()<<__func__;
    if (!m_audio_in)
        return;
    QByteArray m_buffer(2048,0);
    qint64 len = m_audio_in->bytesAvailable();
    if (len < 640)
    {
        return;
    }
    qint64 l = m_buffer_in->read(m_buffer.data(), 640);

    QByteArray frame;
    frame.append(m_buffer.data(),640);
    Q_EMIT SIG_audioFrame( frame );

}

void AudioRead::start()
{
    if(m_audioState == stopped || m_audioState == pausing)
    {
        m_audio_in = new QAudioSource(format,this);
        m_buffer_in = m_audio_in->start();//采集开始

        m_timer->start(1000/40);

        m_audioState = playing;
    }
}

void AudioRead::pause()
{
    if(m_audioState == playing)
    {
        m_timer->stop();
        if(m_audio_in)
        {
            m_audio_in->stop();
            delete m_audio_in;
            m_audio_in = NULL;
        }
        m_audioState = pausing;
    }
}


