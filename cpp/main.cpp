#include <QApplication>
#include <QPushButton>

#include <iostream>

#include "PoloniexClient.hpp"

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    PoloniexClient client;

    QPushButton hello( "Hello world!", 0 );
    hello.resize( 100, 30 );

    //    a.setMainWidget( &hello );
    a.setActiveWindow( &hello );

    hello.show();

    return a.exec();
}

