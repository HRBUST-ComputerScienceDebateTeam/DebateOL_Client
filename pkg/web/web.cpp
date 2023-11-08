#include "./web.h"
#include "../../config.h"
#include <thread>
using namespace std;

QString NETGET(QString url){
    QNetworkAccessManager manager;
    QUrl q(url);
    QNetworkRequest request(q);
    QNetworkReply *reply = manager.get(request);

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    //错误处理
    if (reply->error() != QNetworkReply::NoError){
        qDebug()<<"request protobufHttp handle errors here";
        QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        qDebug( "request protobufHttp found error ....code: %d %d\n", statusCodeV.toInt(), (int)reply->error());
        qDebug(qPrintable(reply->errorString()));
    }

    QByteArray response = reply->readAll();
//    qDebug() << response.size();
//    qDebug()<< QString().fromStdString(response.toStdString()).size();

    reply->deleteLater();
    return QString().fromStdString(response.toStdString());
}


QString NETPOST(QString url , std::string data){
    QNetworkAccessManager manager;
    QUrl q(url);
    QNetworkRequest request(q);
    //application/json	作为请求头告诉服务端消息主体是序列化的JSON字符串。除低版本的IE，基本都支持
    request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json"));


    int times = RETRY_TIMES;
    while(times--){
        QByteArray qByteHttpData(data.c_str(),data.length());
        //qDebug()<<data;
        QNetworkReply *reply = manager.post(request , qByteHttpData);

        QEventLoop loop;
        QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        loop.exec();

        //错误处理
        if (reply->error() != QNetworkReply::NoError){
            if(times == 0){
                qDebug()<<"request protobufHttp handle errors here";
                QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
                qDebug( "request protobufHttp found error ....code: %d %d\n", statusCodeV.toInt(), (int)reply->error());
                qDebug(qPrintable(reply->errorString()));
            }else{
                continue;
            }
        }

        QByteArray response = reply->readAll();
        //qDebug() << response;

        reply->deleteLater();
        return response;
    }

}

QString GET_VIDEODL_URL(struct Video_Download_SendInfo sendinfo){
    QString ret = VIDEO_DOWNLOAD_GET_URL;
    ret += QString().number(sendinfo.type);
    ret += "-";
    ret += QString().number(sendinfo.roomId);
    ret += "-";
    ret += QString().number(sendinfo.userId);
    ret += "-";
    ret += QString().number(sendinfo.min);
    ret += "-";
    ret += QString().number(sendinfo.sec);
    ret += "-";
    ret += QString().number(sendinfo.msec);
    return ret;
}
