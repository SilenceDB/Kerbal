/*
 * mapminmax.cpp
 *
 *  Created on: 2017��7��13��
 *      Author: Peter
 *      Fuction:
 */

#ifndef MAPMINMAX_HPP_
#define MAPMINMAX_HPP_

#include <map>
#include "../except_C++0x.hpp"

namespace kerbal
{
	namespace math
	{
		namespace mapminmax
		{

			namespace
			{
				class Record;
			}

#if __cplusplus >= 201103L
#	define CXX_FINAL final
#else
#	define CXX_FINAL
#endif

			class Mapminmax CXX_FINAL
			{

#undef CXX_FINAL

				protected:
				typedef std::map<double *, Record> map_type;

				static map_type arr_record;

#if __cplusplus < 201103L
				Mapminmax()
				{
				}
#else
				Mapminmax() = delete;
#endif

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
				/*
				 * mapto �������ǽ�һ�����������Լ�����ķ�Χת������һ����Χ������Ϊmap(X,x1,y1,x2,y2)
				 * XΪһ����Ҫת���ı�����x1,y1Ϊ������������ķ�Χ��x2,y2Ϊ�������Ҫӳ�䵽�ķ�Χ��
				 *
				 */

				return (X - x1) / (y1 - x1) * (y2 - x2) + x2;
			}

		} /* namespace mapminmax */
		using namespace mapminmax;

	} /* namespace math */
	using namespace math;

} /* namespace kerbal */

#endif /* End MAPMINMAX_HPP_ */
