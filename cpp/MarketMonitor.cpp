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
	int start = std::time(0) - 100000;
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

	//Create the chart to house the data
	chart = new QChart();
	chart->setTheme(QChart::ChartThemeDark);
	chart->setTitle(QString::fromStdString(pair));
	//chart->setAnimationOptions(QChart::SeriesAnimations);
	
	//Create the vertical axis based on the prices
	QValueAxis *priceAxis = new QValueAxis();
	//Create the categories for the candlesticks.
	QBarCategoryAxis *timestampAxis = new QBarCategoryAxis();
	timestampAxis->setCategories(categories);



	//Add the candlestick series and set its axes
	chart->addSeries(acmeSeries);
	chart->setAxisX(timestampAxis, acmeSeries);
	chart->setAxisY(priceAxis, acmeSeries);


	//Add Indicators
	std::vector<LineIndicator*> indicators;
	indicators.push_back(new MovingAverageIndicator(set, 5, Qt::yellow));
	indicators.push_back(new MovingAverageIndicator(set, 20, Qt::green));
	indicators.push_back(new ExpMovingAverageIndicator(set, 10, Qt::red));
	//Initialize and attach all indicators and set their axes
	for (auto it = indicators.begin(); it != indicators.end(); it++) {
		(*it)->initialize();
		(*it)->attach(chart);
		chart->setAxisX(timestampAxis, (*it)->indicator);
		chart->setAxisY(priceAxis, (*it)->indicator);
	}

	

	//Add some space above and below the candle edges
	priceAxis->setMax(priceAxis->max() * 1.01);
	priceAxis->setMin(priceAxis->min() * 0.99);

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
	button->setText("Reset Zoom");
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
	
	chart->zoomReset();
}