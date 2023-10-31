//icysamon@outlook.com

#ifndef CAMERA_H
#define CAMERA_H

#include <QMainWindow>
#include <QCamera>
#include <QVideoWidget>
#include <QMediaCaptureSession>
#include <QMediaDevices>
#include <QImageCapture>
#include <QMediaRecorder>
#include<QCloseEvent>


QT_BEGIN_NAMESPACE
namespace Ui { class Camera; }
QT_END_NAMESPACE


class Camera : public QMainWindow
{
    Q_OBJECT
signals:
    void SIG_close();
public:
    Camera(QWidget *parent = nullptr);
    ~Camera();

    void closeEvent(QCloseEvent *event);

private slots:
    void on_openvideo_clicked();
    void on_closevideo_clicked(bool checked);
/*signals:
    void SIG_videoPause();
    void SIG_videoStart();*/
private:
    Ui::Camera *ui;
    QScopedPointer<QCamera> my_camera;
    QScopedPointer<QMediaRecorder> my_mediaRecorder;
    QMediaCaptureSession my_captureSession;

    bool checkCameraAvailability(void);

};
#endif // CAMERA_H



