#include"audiowrite.h"
AudioWrite::AudioWrite(QObject *parent)  :  QObject(parent)
{
    //speex 初始化
    //speex_bits_init(&bits_dec);
    //Dec_State = speex_decoder_init(speex_lib_get_mode(SPEEX_MODEID_NB));

    format.setSampleRate(8000);
    format.setChannelCount(1);
    format.setSampleFormat(QAudioFormat::Int16);
    QAudioDevice info = QMediaDevices::defaultAudioOutput();


    m_audio_out = new QAudioSink(format,this);//new QAudioSink(format,this);
    m_buffer_out = m_audio_out->start();
    //向buffer里面存数据就会播放声音
}
void AudioWrite::slot_playAudio(QByteArray ba)
{
    if(ba.size()<640) return;
    m_buffer_out->write(ba.data(),640);
}
