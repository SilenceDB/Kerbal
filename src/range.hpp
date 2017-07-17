/*
 * range.hpp
 *
 *  Created on: 2017��7��17��
 *      Author: Peter
 *      Fuction:
 */

#ifndef RANGE_HPP_
#define RANGE_HPP_

#if __cplusplus < 201103L //C++0x
//# pragma message("range ʹ���� C++ 11 ������, ��� C++ 11 ѡ���Ա�ʹ����Щ������")
#else

#include <algorithm>

using namespace std;

namespace range
{

	class it final
	{
		protected:
			int now;
			it(int now);
			friend class range;

		public:
			int operator*() const;
			it& operator++(); //ǰ����
			bool operator!=(const it &with) const;
	};

	class range final
	{
		protected:
			int from, to;
		public:
			range(int to);
			range(int from, int to);

			it begin() const;
			it end() const;
	};

} /* End of namespace range */
using namespace range;

#endif /* End C++0x */

#endif /* End RANGE_HPP_ */
