/*
 * range.cpp
 *
 *  Created on: 2017��7��17��
 *      Author: Peter
 *      Fuction:
 */

#if __cplusplus < 201103L //C++0x
//# pragma message("range ʹ���� C++ 11 ������, ��� C++ 11 ѡ���Ա�ʹ����Щ������")
#else

#include "rangerecord.hpp"
namespace Range
{
	Range_record::Range_record(int to)
	{
		if (to < 0) {
			this->from = to;
		} else {
			this->from = 0;
		}
		this->to = to;
	}

	Range_record::Range_record(int from, int to)
	{
		if (from > to) {
			this->from = to;
		} else {
			this->from = from;
		}
		this->to = to;
	}

} /* End of namespace Range */

#endif /* End C++0x */
