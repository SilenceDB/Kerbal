/*
 * Mapminmax.hpp
 *
 *  Created on: 2017��7��13��
 *      Author: Peter
 *      Fuction: ���ļ��ṩ�˶����ݹ�һ�������һ����֧��
 */

#ifndef MAPMINMAX_HPP_
#define MAPMINMAX_HPP_

#include <map>
#include "statistics.hpp"
#include "../except_C++0x.hpp"

namespace statistics
{
	namespace
	{
		class Record
		{
			public:
				size_t len;
				double max;
				double min;

				Record();
				Record(size_t len, double max, double min);
		};
	}

	class Mapminmax
	{
		protected:
			static std::map<double *, Record> arr_record;
		public:
			static void mapminmax(double array[], size_t len);
			static void anti_mapminmax(double array[]) throw (std::invalid_argument); //�������һ��
			static double anti_mapminmax(double a, double reference[]) throw (std::invalid_argument);
	};

	inline void mapminmax(double array[], size_t len)
	{
		//���ݹ�һ��
		Mapminmax::mapminmax(array, len);
	}

	inline void anti_mapminmax(double array[])
	{
		//�������һ��
		Mapminmax::anti_mapminmax(array);
	}

	inline double anti_mapminmax(double element, double reference[])
	{
		return Mapminmax::anti_mapminmax(element, reference);
	}

	inline double mapto(double X, double x1, double y1, double x2, double y2)
	{
//	mapto �������ǽ�һ�����������Լ�����ķ�Χת������һ����Χ������Ϊmap(X,x1,y1,x2,y2)
//	XΪһ����Ҫת���ı�����x1,y1Ϊ������������ķ�Χ��x2,y2Ϊ�������Ҫӳ�䵽�ķ�Χ��
		return (X - x1) / (y1 - x1) * (y2 - x2) + x2;
	}

} /* namespace statistics */

#endif /* End MAPMINMAX_HPP_ */
