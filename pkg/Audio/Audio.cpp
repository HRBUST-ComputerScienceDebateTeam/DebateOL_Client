#include "Audio.h"
#include <QAudioSource>
#include <QAudioInput>
#include <QAudioFormat>
#include <QAudioDevice>
#include <QMediaDevices>
#include <QFile>
#include <QTimer>
#include <iostream>
#include <QDir>
#include <QFileDialog>

Audio::Audio(QObject *parent)
    : QObject(parent)
{
    audioRecorder = new QMediaRecorder(this);
    //audioRecorder = new QMediaRecorder;
    captureSession.setRecorder(audioRecorder);
    captureSession.setAudioInput(new QAudioInput(this));


    connect(audioRecorder, &QMediaRecorder::durationChanged, this, &Audio::updateProgress);
    connect(audioRecorder, &QMediaRecorder::errorChanged, this, &Audio::displayErrorMessage);

    captureSession.audioInput()->setDevice(QMediaDevices::defaultAudioInput());
    qDebug()<<QMediaDevices::defaultAudioInput().description();
    QMediaFormat format;
    format.setFileFormat(QMediaFormat::AAC);
    format.setAudioCodec(QMediaFormat::AudioCodec::AAC);
    audioRecorder->setMediaFormat(format);
    audioRecorder->setAudioSampleRate(44100);
    audioRecorder->setAudioBitRate(0);
    audioRecorder->setAudioChannelCount(2);
    audioRecorder->setQuality(QMediaRecorder::HighQuality);
    audioRecorder->setEncodingMode(QMediaRecorder::ConstantQualityEncoding);
    audioRecorder->setOutputLocation(QUrl::fromLocalFile(QDir::currentPath() + "/output1.aac"));

}

Audio::~Audio()
{

}

/*void Audio::stopRecording()
{
    audioRecorder->stop();
}*/


void Audio::updateProgress(qint64 duration)
{
    qDebug()<<duration;
}


void Audio::displayErrorMessage()
{
    qDebug()<<audioRecorder->errorString();
}


/*void Audio::on_pushButton_2_clicked()
{
    audioRecorder->record();
}*/

void Audio::slot_getAudioFrame()
{
    //qDebug()<<__func__;
    //qDebug()<<audioRecorder->recorderState();
    if (audioRecorder->recorderState() == QMediaRecorder::StoppedState)
    {
        /*captureSession.audioInput()->setDevice(QMediaDevices::defaultAudioInput());
        qDebug()<<QMediaDevices::defaultAudioInput().description();
        QMediaFormat format;
        format.setFileFormat(QMediaFormat::AAC);
        format.setAudioCodec(QMediaFormat::AudioCodec::AAC);
        audioRecorder->setMediaFormat(format);
        audioRecorder->setAudioSampleRate(44100);
        audioRecorder->setAudioBitRate(0);
        audioRecorder->setAudioChannelCount(2);
        audioRecorder->setQuality(QMediaRecorder::HighQuality);
        audioRecorder->setEncodingMode(QMediaRecorder::ConstantQualityEncoding);
        audioRecorder->setOutputLocation(QUrl::fromLocalFile(QDir::currentPath() + "/output1.aac"));*/

        audioRecorder->record();
        qDebug()<<audioRecorder->recorderState();
        qDebug()<<audioRecorder->outputLocation();
    }
}

void Audio::slot_openAudio()
{
    //qDebug()<<__func__;
    this->slot_getAudioFrame();
}

void Audio::slot_closeAudio()
{
    audioRecorder->stop();
}
