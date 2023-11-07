#ifndef CKERNEL_H
#define CKERNEL_H

#include <QObject>
#include"camera/camera.h"

#include"./Video/videoread.h"

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
    //void slot_refreshUser( int id,QImage &img);
private:
    Camera * m_pCamera;
    //std::map<int> m_mapIDToUserShow;


    VideoRead * m_pVideoRead;
};

#endif // CKERNEL_H
