/*
 * range.hpp
 *
 *  Created on: 2017��7��17��
 *      Author: Peter
 *      Fuction: ���ļ��ṩ�˶� range ��֧��, ʹ�ÿ����� Python ��һ��ʹ�� for_each ����ѭ����
 *      		  ���ļ���Ҫ C++ 11 �����ϰ汾��������֧��
 *
 * Python ��ѭ��
 * for i in range(10, 20):
 *     print(i)
 *
 * C++ 11 ���
 * for (int i : range(10, 20)) {
 *     cout << i << endl;
 * }
 *
 *
 * Python ��ѭ��
 * for i in range(10):
 *     print(i)
 *
 * C++ 11 ���
 * for (int i : range(10)) {
 *     cout << i << endl;
 * }
 *
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
