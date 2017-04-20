#pragma once
#include "LineIndicator.h"
class MovingAverageIndicator :
	public LineIndicator
{
public:
	MovingAverageIndicator();
	~MovingAverageIndicator();

	MovingAverageIndicator(int period, QColor color);
	MovingAverageIndicator(TimeSeriesDataset & source, QColor color);
	MovingAverageIndicator(TimeSeriesDataset & source, int period, QColor color);

	void initialize() override;
	void update(int timestamp, double value) override;

private:
	int period = 5;
	double sum = 0;
};

