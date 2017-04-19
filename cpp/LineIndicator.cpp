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
		indicator->append(i, dataSource->get_numeric_column(std::string("close"))[i]);
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
