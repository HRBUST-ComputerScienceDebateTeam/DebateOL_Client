#ifndef AUDIODEAL_H
#define AUDIODEAL_H
#include<QTimer>


class audiodeal : public QObject
{
    Q_OBJECT
public:
    explicit audiodeal(int , bool , QObject *parent = nullptr);
    ~audiodeal();

signals:
    void SIG_AudioDownloadFrame(int userpos ,int tim);


public slots:

    void slot_AudioDownloadFrame();

private:
    int mypos;
    bool is_host;

    QTimer *m_timer_Audio_toRefresh;
    QTimer *m_timer_Audio_toDownload;
};
#endif // AUDIODEAL_H
