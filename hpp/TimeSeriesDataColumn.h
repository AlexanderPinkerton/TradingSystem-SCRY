#pragma once

#include <string>
#include <vector>

template<class T>
class TimeSeriesDataColumn
{
public:
	TimeSeriesDataColumn();
	~TimeSeriesDataColumn();

	TimeSeriesDataColumn(std::string & name);

	int length=0;
	std::string field_name;
	std::vector<T> elements;

	void addElement(const T &);

	T& operator[] (int &&);
	T& operator[] (int &);

};

template<class T>
inline TimeSeriesDataColumn<T>::TimeSeriesDataColumn()
{
}

template<class T>
inline TimeSeriesDataColumn<T>::~TimeSeriesDataColumn()
{
}

template<class T>
inline TimeSeriesDataColumn<T>::TimeSeriesDataColumn(std::string & name)
	:field_name(name)
{
}

template<class T>
inline void TimeSeriesDataColumn<T>::addElement(const T & newElement)
{
	elements.push_back(newElement);
	length++;
}

template<class T>
inline T & TimeSeriesDataColumn<T>::operator[](int && index)
{
	// TODO: insert return statement here
	return elements.at(index);
}

template<class T>
inline T & TimeSeriesDataColumn<T>::operator[](int & index)
{
	// TODO: insert return statement here
	return elements.at(index);
}


