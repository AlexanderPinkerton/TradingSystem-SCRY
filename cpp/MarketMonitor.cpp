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



	////Create candlestick series for graph and set its colors.
	QCandlestickSeries *acmeSeries = new QCandlestickSeries();
	acmeSeries->setName(QString::fromStdString(pair));
	acmeSeries->setIncreasingColor(QColor(125, 249, 255));
	acmeSeries->setDecreasingColor(QColor(Qt::darkMagenta));
	QStringList categories;



	//Grab the chartData from poloniexAPI and construct dataset.
	TimeSeriesDataset set = TimeSeriesDataset::createFromJSON(client.public_ChartData(pair, seconds, start, end));
	//TimeSeriesDataset set = TimeSeriesDataset::createFromJSON(TimeSeriesDataset::file2String(std::string("chartdata.json")));

	//For each datapoint in the dataset, add it to the candlestick series.
	for (int i = 0; i < set.numElements; i++) {
		QCandlestickSet *candlestickSet = new QCandlestickSet(set.get_numeric_column(std::string("date"))[i]);
		candlestickSet->setOpen(set.get_numeric_column(std::string("open"))[i]);
		candlestickSet->setHigh(set.get_numeric_column(std::string("high"))[i]);
		candlestickSet->setLow(set.get_numeric_column(std::string("low"))[i]);
		candlestickSet->setClose(set.get_numeric_column(std::string("close"))[i]);

		acmeSeries->append(candlestickSet);
		categories << QDateTime::fromSecsSinceEpoch(candlestickSet->timestamp()).toString();
	}


	//Create some test indicators.
	QLineSeries* indicator = new QLineSeries();
	indicator->setName("ClosePrice");
	for (int i = 0; i < set.numElements; i++) {
		indicator->append(i, set.get_numeric_column(std::string("close"))[i]);
	}
	indicator->setColor(Qt::red);
	QLineSeries* indicator2 = new QLineSeries();
	indicator->setName("Mid");
	for (int i = 0; i < set.numElements; i++) {
		indicator2->append(i,
			(set.get_numeric_column(std::string("open"))[i] + set.get_numeric_column(std::string("close"))[i]) / 2
		);
	}
	indicator2->setColor(Qt::yellow);
	QLineSeries* indicator3 = new QLineSeries();
	indicator->setName("OpenPrice");
	for (int i = 0; i < set.numElements; i++) {
		indicator3->append(i, set.get_numeric_column(std::string("open"))[i]);
	}
	indicator3->setColor(Qt::green);



	QChart *chart = new QChart();
	chart->setTheme(QChart::ChartThemeDark);

	

	chart->addSeries(acmeSeries);
	//Add Indicators

	LineIndicator * indicator1 = new LineIndicator();
	indicator1->setDataSource(set);
	indicator1->initialize();
	indicator1->getSeries()->setColor(Qt::blue);
	indicator1->attach(chart);

	//chart->addSeries(indicator);
	chart->addSeries(indicator2);
	chart->addSeries(indicator3);

	chart->setTitle(QString::fromStdString(pair));
	//chart->setAnimationOptions(QChart::SeriesAnimations);


	//chart->createDefaultAxes();

	//Create the categories for the candlesticks.
	QBarCategoryAxis *timestampAxis = new QBarCategoryAxis();
	timestampAxis->setCategories(categories);

	//Set the X-Axis for all of the series.
	//chart->setAxisX(timestampAxis, indicator);
	chart->setAxisX(timestampAxis, indicator2);
	chart->setAxisX(timestampAxis, indicator3);
	chart->setAxisX(timestampAxis, acmeSeries);
	chart->setAxisX(timestampAxis, indicator1->indicator);

	//Create the vertical axis based on the prices
	QValueAxis *priceAxis = new QValueAxis();
	priceAxis->setMax(priceAxis->max() * 1.01);
	priceAxis->setMin(priceAxis->min() * 0.99);

	//Set the Y-Axis for all of the series.
	//chart->setAxisY(priceAxis, indicator);
	chart->setAxisY(priceAxis, indicator2);
	chart->setAxisY(priceAxis, indicator3);
	chart->setAxisY(priceAxis, acmeSeries);
	chart->setAxisY(priceAxis, indicator1->indicator);



	chart->legend()->setVisible(true);
	chart->legend()->setAlignment(Qt::AlignBottom);


	QChartView *chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);
	chartView->setRubberBand(QChartView::HorizontalRubberBand);
	//chartView->setDragMode(QGraphicsView::DragMode::ScrollHandDrag);


	

	


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