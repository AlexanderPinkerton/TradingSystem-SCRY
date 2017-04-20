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
	double sum = 0;
	//Add each datapoint into the indicator
	for (int i = 0; i < dataSource->numElements; i++) {
		if (i < period) {
			sum = sum + dataSource->get_numeric_column(std::string("close"))[i];
			indicator->append(i, sum/(i+1));
		}
		else {
			sum = sum + dataSource->get_numeric_column(std::string("close"))[i];
			sum = sum - indicator->at(i - period).y();
			indicator->append(i, sum / period);
		}

	}
}

