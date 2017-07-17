/*
 * Mapminmax.hpp
 *
 *  Created on: 2017��7��13��
 *      Author: Peter
 *      Fuction: �ṩ�˶����ݹ�һ�������һ����֧��
 */

#ifndef MAPMINMAX_HPP_
#define MAPMINMAX_HPP_

#include <vector>
#include "statistics.h"

using namespace std;

namespace statistics
{
	class Record
	{
		public:
			double* p;
			int len;
			double max;
			double min;

			Record(double *p, int len, double max, double min)
			{
				this->p = p;
				this->len = len;
				this->max = max;
				this->min = min;
			}
	};

	class Mapminmax
	{
		protected:
			static vector<Record> arr_record;
		public:
			static void mapminmax(double a[], int len);
			static void anti_mapminmax(double a[]);		//�������һ��
			static double anti_mapminmax(double a, double reference[]) throw (invalid_argument);
	};

} /* End of namespace statistics */
using namespace statistics;

inline void mapminmax(double a[], int len)		//���ݹ�һ��
{
	Mapminmax::mapminmax(a, len);
}

inline void anti_mapminmax(double a[])		//�������һ��
{
	Mapminmax::anti_mapminmax(a);
}

inline double anti_mapminmax(double a, double reference[]) throw (invalid_argument)
{
	return Mapminmax::anti_mapminmax(a, reference);
}

#endif /* End MAPMINMAX_HPP_ */
