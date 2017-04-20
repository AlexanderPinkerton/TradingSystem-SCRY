#pragma once

#include <QtCharts>

#include "TimeSeriesDataset.h"

/** Interface defining operations of an Indicator **/
class Indicator
{
public:

	Indicator()
	{
	}

	~Indicator()
	{
	}

	QAbstractSeries* indicator;

	virtual void setName(std::string s) = 0;

	virtual void setDataSource(TimeSeriesDataset & source) = 0;

	virtual void initialize() = 0;

	virtual void attach(QChart * chart) = 0;

	virtual void update(int timestamp, double value) = 0;


};

