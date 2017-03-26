#include <QApplication>
#include <QPushButton>
#include <QString>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

#include <QDebug>

#include <iostream>

#include "PoloniexClient.hpp"

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    PoloniexClient client;


    //Parse json test.
    std::string pair = "BTC_XMR";
    int start = std::time(0)-100000;
    int end = std::time(0);
    int seconds = 1800;

    QPushButton hello( "Hello world!", 0 );
    hello.resize( 100, 30 );
    a.setActiveWindow( &hello );
    hello.show();

    std::string result =  client.public_ChartData(pair, seconds, start, end);

    if(result != "FAIL"){
        QString qresult = QString::fromStdString(result);
        QJsonDocument doc = QJsonDocument::fromJson(qresult.toUtf8());
        QJsonArray candles = doc.array();

        for(unsigned int i=0;i<candles.size();i++){
            QJsonObject dateobj = candles[i].toObject();
            qDebug() << dateobj["high"];
        }


    }



    return a.exec();
}

