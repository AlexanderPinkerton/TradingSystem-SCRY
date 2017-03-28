#include <QApplication>
#include <QPushButton>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include <QtCharts>

#include "../hpp/MarketMonitor.h"

int main(int argc, char **argv)
{
    QApplication a(argc, argv);

	MarketMonitor monitor;
	monitor.initialize();
	
    return a.exec();
}

