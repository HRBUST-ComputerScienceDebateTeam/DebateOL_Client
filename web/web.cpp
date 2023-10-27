#include "./web.h"

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
    //qDebug() << response;

    reply->deleteLater();
    return response;
}



QString NETPOST(QString url , QString data){
    QNetworkAccessManager manager;
    QUrl q(url);
    QNetworkRequest request(q);
    //application/json	作为请求头告诉服务端消息主体是序列化的JSON字符串。除低版本的IE，基本都支持
    request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json"));
    QByteArray qByteHttpData =data.toStdString().c_str();
    QNetworkReply *reply = manager.post(request , qByteHttpData);

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
    //qDebug() << response;

    reply->deleteLater();
    return response;
}

