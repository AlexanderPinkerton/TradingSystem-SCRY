#include "..\hpp\ExpMovingAverageIndicator.h"


ExpMovingAverageIndicator::ExpMovingAverageIndicator()
{
	
}


ExpMovingAverageIndicator::~ExpMovingAverageIndicator()
{
}

ExpMovingAverageIndicator::ExpMovingAverageIndicator(int period, QColor color)
	:period(period), LineIndicator()
{
	indicator->setColor(color);
	multiplier = 2.0 / (period + 1);
}

ExpMovingAverageIndicator::ExpMovingAverageIndicator(TimeSeriesDataset & source, QColor color)
	:LineIndicator(source, color)
{
}

ExpMovingAverageIndicator::ExpMovingAverageIndicator(TimeSeriesDataset & source, int period, QColor color)
	: period(period), LineIndicator(source, color)
{
}

void ExpMovingAverageIndicator::initialize()
{
	//This may need to be removed.
	indicator->setName(QString::number(period) + "-Period Exponential Moving Average");
}

/* This function should will accept new values and update the indicator */
void ExpMovingAverageIndicator::update(int timestamp, double value)
{
	//Use a simple moving average until it is possible to generate a EMA of the full period
	int i = indicator->points().size();
	if (i < period) {
		sum = sum + value;
		indicator->append(i, sum / (i + 1));
	}
	else {
		//ema = ((dataSource->get_numeric_column(std::string("close"))[i] - indicator->at(i - 1).y()) * multiplier) + indicator->at(i - 1).y();
		ema = (value * multiplier) + (indicator->at(i - 1).y() * (1 - multiplier));
		indicator->append(i, ema);
	}

}