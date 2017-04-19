#pragma once
#include "LineIndicator.h"
class MovingAverageIndicator :
	public LineIndicator
{
public:
	MovingAverageIndicator();
	~MovingAverageIndicator();

	MovingAverageIndicator(TimeSeriesDataset & source, QColor color);
	MovingAverageIndicator(TimeSeriesDataset & source, int period, QColor color);

	void initialize() override;

private:
	int period = 5;
};

