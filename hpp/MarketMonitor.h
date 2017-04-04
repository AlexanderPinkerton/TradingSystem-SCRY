#pragma once

#include "PoloniexClient.hpp"
#include "TimeSeriesDataset.h"

#include <QPushButton>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include <QtCharts>

#include <QDebug>

#include <iostream>
#include <ctime>

class MarketMonitor : QObject
{
	Q_OBJECT
public:
	MarketMonitor();
	~MarketMonitor();

	int lastUpdate = std::time(0);

	void initialize();
	

public slots:
	void button_update();
};

