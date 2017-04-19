#include "..\hpp\MovingAverageIndicator.h"



MovingAverageIndicator::MovingAverageIndicator()
{
}


MovingAverageIndicator::~MovingAverageIndicator()
{
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
	indicator->setName(QString::number(period) + "-Day Moving Average");

	//Add each datapoint into the indicator
	for (int i = 0; i < dataSource->numElements; i++) {
		if (i > period) {
			double movAvg10c = 0;
			for (int j = i - period; j < i; j++) {
				movAvg10c = movAvg10c + dataSource->get_numeric_column(std::string("close"))[j];
			}
			movAvg10c = movAvg10c / period;
			indicator->append(i, movAvg10c);
		}
	}
}
