#pragma once
#include "LineIndicator.h"
class ExpMovingAverageIndicator :
	public LineIndicator
{
public:
	ExpMovingAverageIndicator();
	~ExpMovingAverageIndicator();

	ExpMovingAverageIndicator(TimeSeriesDataset & source, QColor color);
	ExpMovingAverageIndicator(TimeSeriesDataset & source, int period, QColor color);

	void initialize() override;

private:
	int period = 5;
	double multiplier = 1;
	double ema = 0;
};

