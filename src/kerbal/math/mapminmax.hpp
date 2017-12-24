/*
 * mapminmax.cpp
 *
 *  Created on: 2017��7��13��
 *      Author: Peter
 *      Fuction:
 */

#ifndef MAPMINMAX_HPP_
#define MAPMINMAX_HPP_

#include "../except_C++0x.hpp"

namespace kerbal
{
	namespace math
	{
		namespace mapminmax
		{

			void mapminmax(double array[], size_t len);
			void anti_mapminmax(double array[]) throw (std::invalid_argument);
			double anti_mapminmax(double element, double reference[]) throw (std::invalid_argument);

			inline double mapto(double X, double x1, double y1, double x2, double y2)
			{
				/*
				 * mapto �������ǽ�һ�����������Լ�����ķ�Χת������һ����Χ������Ϊmap(X,x1,y1,x2,y2)
				 * XΪһ����Ҫת���ı�����x1,y1Ϊ������������ķ�Χ��x2,y2Ϊ�������Ҫӳ�䵽�ķ�Χ��
				 *
				 */

				return (X - x1) / (y1 - x1) * (y2 - x2) + x2;
			}

		} /* namespace mapminmax */

	} /* namespace math */

} /* namespace kerbal */

#endif /* End MAPMINMAX_HPP_ */
