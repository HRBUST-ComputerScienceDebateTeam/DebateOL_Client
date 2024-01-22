#ifndef CKERNEL_H
#define CKERNEL_H

#include <QObject>
#include "Room_main/room_main.h"
#include"./WeChatDialog/wechatdialog.h"
#include"./LoginDialog/logindialog.h"
#include"./pkg/audioread/audioread.h"
#include"./pkg/audiowrite/audiowrite.h"

class Ckernel : public QObject
{
    Q_OBJECT
public:
    explicit Ckernel(QObject *parent = nullptr);

    static Ckernel* GetInstance()
    {
        static Ckernel kernel;
        return & kernel;
    }
signals:

public slots:
    void slot_destory();
    void slot_destorychat();
    //发送登录请求
    void slot_loginCommit(QString tel,QString pass);
    void slot_registerCommit(QString tel,QString pass,QString name);
    //void slot_refreshUser( int id,QImage &img);
    void slot_createRoom();
    void  slot_joinRoom();

private:
    Room_main * m_room;
    LoginDialog *m_pLoginDlg;
    WeChatDialog * We_Chat;
    //std::map<int> m_mapIDToUserShow;
public:
    //个人信息
    static int myuid;
    static string my_jwt_token;
    static string my_refresh_jwt_token;
    int room_id;

    //音频使用 音频一个采集多个播放，每个房间成员使用map映射
    AudioRead *m_pAudioRead;
    std::map<int , AudioWrite*> m_mapIDToAudioWrite;
private:
    //回调函数
    void* SIGDEAL_login(void * arg);
    void* SIGDEAL_reg(void * arg);
};

#endif // CKERNEL_H
