#include "ckernel.h"
#include"qDebug"

#define NetPackMap(a) m_netPackMap[a - DEF_PACK_BASE]


Ckernel::Ckernel(QObject *parent)
    : QObject{parent}
{
    m_pCamera =new Camera;
    connect(m_pCamera , SIGNAL(SIG_close())
            ,this,SLOT(slot_destory()));
    //m_pVideoRead = new VideoRead;
    /*connect(m_pVideoRead, SIGNAL(SIG_sendVideoFrame(QImage))
            ,this,SLOT(SIG_sendVideoFrame(QImage)));*/
    m_pCamera->show();
}
//回收
void Ckernel::slot_destory()
{
    qDebug()<<__func__;
    if(m_pCamera)
    {
        delete m_pCamera;m_pCamera = NULL;
    }
}

