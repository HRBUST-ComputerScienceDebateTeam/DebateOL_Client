#include "ckernel.h"
#include"qDebug"
Ckernel::Ckernel(QObject *parent)
    : QObject{parent}
{
    m_pCamera =new Camera;
    connect(m_pCamera , SIGNAL(SIG_close())
            ,this,SLOT(slot_destory()));

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

