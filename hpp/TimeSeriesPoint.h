#pragma once

#include <vector>
#include <string>
#include <unordered_map>

/**Class which encapsulates all data which corresponds to a point in time in time series data**/
class TimeSeriesPoint
{
public:

	long unix_timestamp;

	//Candlestick components
	double open, close, high, low;

	//Other important information
	double volume;
	double quotevolume;
	double weightedAverage;


	void setFeatureVector(int size, double vector[]);
	double* getFeatureVector();

private:
	//Feature vector to be used in training of models.
	double featureVector[];

	



	TimeSeriesPoint();
	~TimeSeriesPoint();
};

