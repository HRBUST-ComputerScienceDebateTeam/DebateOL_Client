#include "ckernel.h"
#include"qDebug"

#define NetPackMap(a) m_netPackMap[a - DEF_PACK_BASE]


Ckernel::Ckernel(QObject *parent)
    : QObject{parent}
{
    m_room = new Room_main;
    We_Chat =new WeChatDialog;
    m_pLoginDlg =new LoginDialog;
    connect(m_pLoginDlg,SIGNAL(SIG_loginCommit(QString,QString))
            ,this,SLOT(slot_loginCommit(QString,QString)));
    connect(m_room , SIGNAL(SIG_close())
            ,this,SLOT(slot_destory()));
    connect(We_Chat , SIGNAL(SIG_closechat())
            ,this,SLOT(slot_destorychat()));
    //m_pVideoRead = new VideoRead;
    /*connect(m_pVideoRead, SIGNAL(SIG_sendVideoFrame(QImage))
            ,this,SLOT(SIG_sendVideoFrame(QImage)));*/
    m_pLoginDlg->show();
    //m_room->show();
    //We_Chat->show();
}
//回收
void Ckernel::slot_destory()
{
    qDebug()<<__func__;
    if(m_room)
    {
        delete m_room;
        m_room = NULL;
    }  
}

void Ckernel::slot_destorychat()
{
    qDebug()<<__func__;
    if(We_Chat)
    {
        delete We_Chat;
        We_Chat = NULL;
    }
}
//发送登录
void Ckernel::slot_loginCommit(QString tel, QString pass)
{
    std::string strTel = tel.toStdString();
    std::string strPass = pass.toStdString();
    //下面是封装发送

}
