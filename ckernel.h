#ifndef CKERNEL_H
#define CKERNEL_H

#include <QObject>
#include "Room_main/room_main.h"


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
    Room_main * m_room;
    //std::map<int> m_mapIDToUserShow;
};

#endif // CKERNEL_H
