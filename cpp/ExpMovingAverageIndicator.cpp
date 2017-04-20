#include "..\hpp\ExpMovingAverageIndicator.h"


ExpMovingAverageIndicator::ExpMovingAverageIndicator()
{
}


ExpMovingAverageIndicator::~ExpMovingAverageIndicator()
{
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
	indicator->setName(QString::number(period) + "-Period Exponential Moving Average");

	multiplier = 2.0 / (period + 1);

	double sum = 0;
	//Add each datapoint into the indicator
	for (int i = 0; i < dataSource->numElements; i++) {
		if (i < period) {
			sum = sum + dataSource->get_numeric_column(std::string("close"))[i];
			indicator->append(i, sum / (i + 1));
		}
		else {
			//ema = ((dataSource->get_numeric_column(std::string("close"))[i] - indicator->at(i - 1).y()) * multiplier) + indicator->at(i - 1).y();
			ema = (dataSource->get_numeric_column(std::string("close"))[i] * multiplier) + (indicator->at(i - 1).y() * (1 - multiplier));
			indicator->append(i, ema);
		}

	}
}
