#include <hpp/MarketMonitor.h>


MarketMonitor::MarketMonitor()
{
}


MarketMonitor::~MarketMonitor()
{
}

void MarketMonitor::initialize()
{
	PoloniexClient client;

	//qDebug() << QSslSocket::sslLibraryBuildVersionString();

	//Parse json test.
	std::string pair = "BTC_XMR";
	int start = std::time(0) - 50000;
	int end = std::time(0);
	int seconds = 900;
	//300, 900, 1800, 7200, 14400, and 86400
	//5min  15  30  2hr 4hr 1day



	//Create candlestick series for graph and set its colors.
	QCandlestickSeries *acmeSeries = new QCandlestickSeries();
	acmeSeries->setName("Acme Ltd");
	acmeSeries->setIncreasingColor(QColor(125, 249, 255));
	acmeSeries->setDecreasingColor(QColor(Qt::darkMagenta));
	QStringList categories;

	//Grab the chartData from poloniexAPI and construct dataset.
	TimeSeriesDataset set = TimeSeriesDataset::createFromJSON(client.public_ChartData(pair, seconds, start, end));

	//For each datapoint in the dataset, add it to the candlestick series.
	for (int i = 0; i < set.numElements; i++) {
		QCandlestickSet *candlestickSet = new QCandlestickSet(set.get_numeric_column(std::string("date"))[i]);
		candlestickSet->setOpen(set.get_numeric_column(std::string("open"))[i]);
		candlestickSet->setHigh(set.get_numeric_column(std::string("high"))[i]);
		candlestickSet->setLow(set.get_numeric_column(std::string("low"))[i]);
		candlestickSet->setClose(set.get_numeric_column(std::string("close"))[i]);

		acmeSeries->append(candlestickSet);
		categories << QDateTime::fromMSecsSinceEpoch(candlestickSet->timestamp()).toString();
	}



	QChart *chart = new QChart();
	chart->setTheme(QChart::ChartThemeDark);
	chart->addSeries(acmeSeries);
	chart->setTitle(QString::fromStdString(pair));
	chart->setAnimationOptions(QChart::SeriesAnimations);
	chart->createDefaultAxes();
	chart->legend()->setVisible(true);
	chart->legend()->setAlignment(Qt::AlignBottom);

	QBarCategoryAxis *axisX = qobject_cast<QBarCategoryAxis *>(chart->axes(Qt::Horizontal).at(0));
	axisX->setCategories(categories);

	QValueAxis *axisY = qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).at(0));
	axisY->setMax(axisY->max() * 1.01);
	axisY->setMin(axisY->min() * 0.99);

	QChartView *chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);
	chartView->setRubberBand(QChartView::HorizontalRubberBand);



	QWidget *window = new QWidget;
	QVBoxLayout *box = new QVBoxLayout;


	QPushButton * button = new QPushButton();
	button->resize(100, 50);
	button->setText("UpdateChart");
	QObject::connect(button, SIGNAL(clicked()), this, SLOT(button_update()));

	//add widgets to layout.
	box->addWidget(button);
	box->addWidget(chartView);
	window->resize(800, 600);
	//set windows layout.
	window->setLayout(box);
	window->show();

	qDebug() << "MarketMonitor Created";

}


void MarketMonitor::button_update() {

	qDebug() << "button clicked";

}