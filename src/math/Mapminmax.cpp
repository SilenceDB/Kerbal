/*
 * Mapminmax.cpp
 *
 *  Created on: 2017��7��13��
 *      Author: Peter
 *      Fuction:
 */

#include "Mapminmax.hpp"

namespace statistics
{
	namespace
	{
		Record::Record()
		{
			this->len = 0;
			this->max = 0;
			this->min = 0;
		}

		Record::Record(size_t len, double max, double min)
		{
			this->len = len;
			this->max = max;
			this->min = min;
		}
	}

	std::map<double *, Record> Mapminmax::arr_record = std::map<double *, Record>();

	void Mapminmax::mapminmax(double array[], size_t len)
	{
		if (arr_record.find(array) == arr_record.end()) { //δ�ҵ�
			double MaxValue;
			double MinValue;
			max_and_min(array, len, MaxValue, MinValue);

			arr_record[array] = Record(len, MaxValue, MinValue);

			double k = 1.0 * 2 / (MaxValue - MinValue);
			double b = -(MaxValue + MinValue) / 2.0;
			for (unsigned int i = 0; i < len; i++) {
				array[i] = k * (array[i] + b);
			}
		}
	}

	void Mapminmax::anti_mapminmax(double array[]) throw (std::invalid_argument)
	{
		//�������һ��
		std::map<double *, Record>::iterator it = arr_record.find(array);
		if (it == arr_record.end()) { //δ�ҵ�
			throw std::invalid_argument("un mapped");
		} else { //���ҵ�
			int len = it->second.len;
			double MaxValue = it->second.max;
			double MinValue = it->second.min;
			double k = 1.0 * 2 / (MaxValue - MinValue);
			double b = -(MaxValue + MinValue) / 2.0;
			for (int i = 0; i < len; i++) {
				array[i] = array[i] / k - b;
			}
			arr_record.erase(it);
		}
	}

	double Mapminmax::anti_mapminmax(double element, double reference[]) throw (std::invalid_argument)
	{
		//�������һ��
		std::map<double *, Record>::iterator it = arr_record.find(reference);
		if (it == arr_record.end()) { //δ�ҵ�
			throw std::invalid_argument("un mapped");
		} else { //���ҵ�
			double MaxValue = it->second.max;
			double MinValue = it->second.min;
			double k = 1.0 * 2 / (MaxValue - MinValue);
			double b = -(MaxValue + MinValue) / 2.0;
			return element / k - b;
		}
	}
} /* namespace statistics */
