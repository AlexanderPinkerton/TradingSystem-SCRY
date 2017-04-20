#include "..\hpp\MovingAverageIndicator.h"



MovingAverageIndicator::MovingAverageIndicator()
{
}


MovingAverageIndicator::~MovingAverageIndicator()
{
}


MovingAverageIndicator::MovingAverageIndicator(int period, QColor color)
	: period(period)
{
	indicator->setColor(color);
}

MovingAverageIndicator::MovingAverageIndicator(TimeSeriesDataset & source, QColor color)
	:LineIndicator(source, color)
{
}

MovingAverageIndicator::MovingAverageIndicator(TimeSeriesDataset & source, int period, QColor color)
	: period(period), LineIndicator(source, color)
{
}

void MovingAverageIndicator::initialize()
{
	//TODO: Move this functionaility to an update method, which will allow only one pass of the data for all indicators
	//FOr each time series data peice, send it to each indicator with update.
	indicator->setName(QString::number(period) + "-Period Moving Average");
}

void MovingAverageIndicator::update(int timestamp, double value)
{
	int i = indicator->points().size();
	if (i < period) {
		sum = sum + value;
		indicator->append(i, sum / (i + 1));
	}
	else {
		sum = sum + value;
		sum = sum - indicator->at(i - period).y();
		indicator->append(i, sum / period);
	}
}