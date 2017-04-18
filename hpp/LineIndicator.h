#pragma once

#include "Indicator.h"

class LineIndicator : Indicator
{
public:
	LineIndicator();
	~LineIndicator();

	QLineSeries * indicator;
	TimeSeriesDataset * dataSource;

	//Indicator interface methods
	void setName(std::string s) override;
	void setDataSource(TimeSeriesDataset & source) override;
	void initialize() override;
	void attach(QChart * chart) override;
	void update() override;

	QLineSeries * getSeries();
};

