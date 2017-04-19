#pragma once

#include "Indicator.h"

class LineIndicator : public Indicator
{
public:
	LineIndicator();
	~LineIndicator();

	LineIndicator(TimeSeriesDataset & source, QColor color);

	QLineSeries * indicator;
	TimeSeriesDataset * dataSource;

	//Indicator interface methods
	void setName(std::string s) override;
	void setDataSource(TimeSeriesDataset & source) override;
	virtual void initialize() override;
	void attach(QChart * chart) override;
	void update() override;

	QLineSeries * getSeries();
};

