#ifndef CKERNEL_H
#define CKERNEL_H

#include <QObject>
#include"camera/camera.h"

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
private:
    Camera * m_pCamera;
};

#endif // CKERNEL_H
