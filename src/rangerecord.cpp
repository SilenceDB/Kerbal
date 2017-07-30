/*
 * range.cpp
 *
 *  Created on: 2017��7��17��
 *      Author: Peter
 *      Fuction:
 */

#if __cplusplus < 201103L //C++0x
# pragma message("\n"\
"			* range ʹ���� C++ 11 ������, ��� C++ 11 ѡ���Ա�ʹ����Щ������"\
)
#else

#include "rangerecord.hpp"
namespace Range
{
	Range_record::Range_record(int to)
	{
		this->from = 0;
		if (to < 0) {
			this->to = to;
		} else {
			this->to = 0;
		}
		this->step = 1;
	}

	Range_record::Range_record(int from, int to, int step)
	{
		this->from = from;
		this->to = to;
		this->step = step;
	}

} /* End of namespace Range */

#endif /* End C++0x */
