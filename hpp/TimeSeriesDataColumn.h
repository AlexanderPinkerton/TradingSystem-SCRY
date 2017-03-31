#pragma once

#include <string>
#include <vector>


class TimeSeriesDataColumn
{
public:
	TimeSeriesDataColumn();
	~TimeSeriesDataColumn();

	TimeSeriesDataColumn(std::string & name);

	int length;
	std::string field_name;
	std::vector<float> elements;

	void addElement(const float &);

	float& operator[] (int &&);
	float& operator[] (int &);

};

