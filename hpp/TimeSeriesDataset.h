#pragma once

#include <unordered_map>
#include <string>
#include <stdexcept>  

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QFile>

#include "TimeSeriesDataColumn.h"

class TimeSeriesDataset
{
	using columnMap_numeric = std::unordered_map<std::string, TimeSeriesDataColumn<double>>;
	using columnMap_string = std::unordered_map<std::string, TimeSeriesDataColumn<std::string>>;

public:
	int numElements = 0;;
	columnMap_numeric numeric_columns;
	columnMap_string string_columns;

	QStringList fieldNames;

	TimeSeriesDataset();
	~TimeSeriesDataset();

	TimeSeriesDataset(columnMap_numeric numeric_cols, columnMap_string string_cols);

	TimeSeriesDataColumn<double> get_numeric_column(std::string & fieldName);
	TimeSeriesDataColumn<std::string> get_string_column(std::string & fieldName);

	int size();

	template<class T>
	TimeSeriesDataColumn<T> operator[](std::string & fieldName);

	//Static
	static TimeSeriesDataset createFromJSON(std::string & jsonString);
	static TimeSeriesDataset createFromCSV();

	static std::string file2String(std::string & filename);

private:

};

