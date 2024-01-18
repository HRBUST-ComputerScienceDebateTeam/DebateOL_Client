#ifndef VIDEODEAL_H
#define VIDEODEAL_H

#include <QObject>
#include"./video_config.h"
#include<map>


//图片的宽高
#define IMAGE_WIDTH (240)
#define IMAGE_HEIGHT (240)

class VideoDeal : public QObject
{
    Q_OBJECT
public:
    explicit VideoDeal(int , bool , QObject *parent = nullptr);
    ~VideoDeal();

signals:
    void SIG_DownloadFrame(int userpos ,int tim);
    void SIG_RefreshFrame(int userpos,int tim);

public slots:
    void slot_RefreshFrame();
    void slot_DownloadFrame();

private:
    int mypos;
    bool is_host;

    QTimer *m_timer_toRefresh;
    QTimer *m_timer_toDownload;
};

#endif // VIDEODEAL_H
