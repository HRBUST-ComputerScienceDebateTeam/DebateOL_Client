#ifndef CKERNEL_H
#define CKERNEL_H

#include <QObject>
#include "Room_main/room_main.h"
#include"./pkg/WeChatDialog/wechatdialog.h"
#include"./pkg/LoginDialog/logindialog.h"


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
    //void slot_refreshUser( int id,QImage &img);
private:
    Room_main * m_room;
    LoginDialog *m_pLoginDlg;
    WeChatDialog * We_Chat;
    //std::map<int> m_mapIDToUserShow;
};

#endif // CKERNEL_H
