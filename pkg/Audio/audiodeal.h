#ifndef AUDIODEAL_H
#define AUDIODEAL_H
#include<QTimer>


#define FRAME_RATE (30)
#define Download_RATE (10)
#define UPLOAD_RATE (10)

class audiodeal : public QObject
{
    Q_OBJECT
public:
    explicit audiodeal(int , bool , int ,   QObject *parent = nullptr);
    ~audiodeal();

signals:
    void SIG_AudioDownloadFrame(int userpos ,int tim);
    void SIG_AudioRefreshFrame(int userpos ,int tim);



public slots:

    void slot_AudioDownloadFrame();
    void slot_AudioRefreshFrame();

public:
    int mypos;
    int myid;
    bool is_host;

    QTimer *m_timer_Audio_toRefresh;
    QTimer *m_timer_Audio_toDownload;
};
#endif // AUDIODEAL_H
