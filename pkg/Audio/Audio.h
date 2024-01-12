#ifndef AUDIO_H
#define AUDIO_H

#include <QWidget>
#include <QAudioSource>
#include <QFile>
#include <QMediaFormat>
#include <QMediaRecorder>
#include <QUrl>
#include <QMediaCaptureSession>
#include <QTimer>


QT_BEGIN_NAMESPACE
namespace Ui { class Audio; }
QT_END_NAMESPACE

class Audio : public QObject
{
    Q_OBJECT

public:
    Audio(QObject *parent = nullptr);
    ~Audio();

private slots:
    //void stopRecording();
    void updateProgress(qint64 duration);
    void displayErrorMessage();


    //void on_pushButton_2_clicked();
    //void on_pushButton_clicked();

public slots:
    void slot_getAudioFrame();
    void slot_openAudio();
    void slot_closeAudio();
private:
    Ui::Audio *ui;
    ///

    //Audio * m_Audio;
    //QWidget *m_audioRecorder;
    QMediaRecorder *audioRecorder = nullptr;
    QMediaCaptureSession captureSession;
};
#endif // AUDIO_H

