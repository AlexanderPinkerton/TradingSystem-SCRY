#pragma once

#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <iostream>
#include <string>

/*** This class is used to perform an HTTP request to a RESTful webservice
 *   It will return the JSON response which will need to handled seperately.
 ***/

class Request {

private:

    QEventLoop eventLoop;
    QNetworkAccessManager mgr;

    std::string baseUri;
    std::string query;

public:

    std::string response = "";

    //Constructor taking the complete url to be sent to API
    Request(const std::string &baseUri, std::string &query);

    //This method should return false if the request was bad
    //It should also update the response if success
    bool sendRequest();


};
