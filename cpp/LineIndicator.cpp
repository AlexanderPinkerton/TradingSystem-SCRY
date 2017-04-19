#include "..\hpp\LineIndicator.h"



LineIndicator::LineIndicator()
{
	indicator = new QLineSeries();
}


LineIndicator::~LineIndicator()
{
	delete indicator;
	indicator = nullptr;
}

LineIndicator::LineIndicator(TimeSeriesDataset & source, QColor color)
	:dataSource(&source)
{
	indicator = new QLineSeries();
	indicator->setColor(color);
}

void LineIndicator::setName(std::string s)
{
	indicator->setName(QString::fromStdString(s));
}

void LineIndicator::setDataSource(TimeSeriesDataset & data)
{
	dataSource = &data;
}

void LineIndicator::initialize()
{
	//TODO: Pass in a lambda which will calculate indicator

	//Add each datapoint into the indicator
	for (int i = 0; i < dataSource->numElements; i++) {

		int period = 10;

		if (i > period) {
			double movAvg10c = 0;

			for (int j = i - period; j < i; j++) {
				movAvg10c = movAvg10c + dataSource->get_numeric_column(std::string("close"))[j];
			}
			movAvg10c = movAvg10c / period;
			indicator->append(i, movAvg10c);
		}

		//indicator->append(i, dataSource->get_numeric_column(std::string("close"))[i]);
	}

}

void LineIndicator::attach(QChart * chart)
{
	chart->addSeries(indicator);
}

void LineIndicator::update()
{
}

QLineSeries * LineIndicator::getSeries()
{
	return indicator;
}
