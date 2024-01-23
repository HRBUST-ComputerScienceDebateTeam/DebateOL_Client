#ifndef CKERNEL_H
#define CKERNEL_H

#include <QObject>
#include "Room_main/room_main.h"
#include"./WeChatDialog/wechatdialog.h"
#include"./LoginDialog/logindialog.h"


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
    void slot_registerCommit(QString tel,QString pass,QString num);
    //void slot_refreshUser( int id,QImage &img);
    void slot_createRoom(std::string s);
    void slot_joinRoom(std::string s);
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
private:
    //回调函数
    void* SIGDEAL_login(void * arg);
    void* SIGDEAL_reg(void * arg);
    void* SIGDEAL_CreateRoom(void* arg);
    void* SIGDEAL_JoinRoom(void* arg);
};

#endif // CKERNEL_H
