#include "Request.hpp"


//Constructor taking the complete url to be sent to API
Request::Request(const std::string & baseUri, std::string & query)
  :baseUri(baseUri), query(query)
{}

//This method should return false if the request was bad
//It should also update the response if success
bool Request::sendRequest()
{
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    // the HTTP request
    QUrl url(QString::fromStdString(Request::baseUri));
    url.setQuery(QString::fromStdString(query));

    QNetworkRequest req( url );
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec(); // blocks stack until "finished()" has been called

    if (reply->error() == QNetworkReply::NoError) {
        //success
        QByteArray bytes = reply->readAll();
        QString result(bytes);
        Request::response = result.toUtf8().constData();
        delete reply;
        return true;
    }
    else {
        //failure
        qDebug() << "Failure" <<reply->errorString();
        delete reply;
        return false;
    }

}
