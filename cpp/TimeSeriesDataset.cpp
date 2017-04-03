#include "..\hpp\TimeSeriesDataset.h"



TimeSeriesDataset::TimeSeriesDataset()
{
}


TimeSeriesDataset::~TimeSeriesDataset()
{
}

TimeSeriesDataset::TimeSeriesDataset(columnMap_numeric numeric_cols, columnMap_string string_cols)
	:numeric_columns(numeric_cols), string_columns(string_cols)
{
}

TimeSeriesDataColumn<double> TimeSeriesDataset::get_numeric_column(std::string & fieldName)
{
	try {
		return numeric_columns[fieldName];
	}
	catch (const std::out_of_range& oor) {
		qDebug() << "Out of Range error: " << oor.what() << '\n';
	}
}

TimeSeriesDataColumn<std::string> TimeSeriesDataset::get_string_column(std::string & fieldName)
{
	try {
		return string_columns[fieldName];
	}
	catch (const std::out_of_range& oor) {
		qDebug() << "Out of Range error: " << oor.what() << '\n';
	}
}

int TimeSeriesDataset::size()
{
	return numElements;
}

//----------------------Static Functions--------------------------------

TimeSeriesDataset TimeSeriesDataset::createFromJSON(std::string & jsonString)
{
	//Currently this requires JSON to be in poloniex chartData format.
	//TODO Define json schema and parse that way

	TimeSeriesDataset result;
	
	//The main storage of the columns
	columnMap_numeric numeric_columns;
	columnMap_string string_columns;

	//Convert json string to Qstring
	QString qresult = QString::fromStdString(jsonString);
	//Create Json document from string
	QJsonDocument doc = QJsonDocument::fromJson(qresult.toUtf8());

	//TODO: Need to examine document and create all columns at this point look at the json to know if they are numeric or text and store in map
	
	//Since all data is contained as an array
	QJsonArray datapoints = doc.array();

	QJsonObject first = datapoints.at(0).toObject();

	//Use the first object to set the fieldnames
	result.fieldNames = first.keys();
	//Set the number of elements in the dataset
	result.numElements = datapoints.size();

	//Create Columns of dataset using the keys of the first object
	for (auto key : first.keys()) {
		//If field is numeric, add numeric column
		if (first.take(key).isDouble()) {
			TimeSeriesDataColumn<double> col;
			col.field_name = key.toStdString();
			numeric_columns[col.field_name] = col;
		}
		//If field is a string, add string column
		else if (first.take(key).isString()) {
			TimeSeriesDataColumn<std::string> col;
			col.field_name = key.toStdString();
			string_columns[col.field_name] = col;
		}
		else {
			qDebug() << "Key is undefined";
		}
	}
	
	//Insert the data into the columnss
	for (int i = 0; i < datapoints.size(); i++) {
		QJsonObject datapoint = datapoints[i].toObject();

		for (auto key : datapoint.keys()) {
			//Add the data to either they numeric cols or string cols
			if (datapoint[key].isDouble()) {
				numeric_columns[key.toStdString()].addElement(datapoint[key].toDouble());
			}
			else if (datapoint[key].isString()) {
				string_columns[key.toStdString()].addElement(datapoint[key].toString().toStdString());
			}
			else {
				qDebug() << "Key is undefined";
			}
		}
	}
	

	//Set the dataset columns
	result.numeric_columns = numeric_columns;
	result.string_columns = string_columns;
	
	//TimeSeriesDataset result(numeric_columns, string_columns);

	return result;
}
