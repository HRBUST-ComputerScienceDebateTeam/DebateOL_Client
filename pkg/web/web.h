#include <QtNetwork>
#include <QString>
#include <QVariant>
#include "../thrift_json/thrift_json_config.h"

QString NETGET(QString url);
QString GET_VIDEODL_URL(struct Video_Download_SendInfo);
QString NETPOST(QString url , std::string data);



