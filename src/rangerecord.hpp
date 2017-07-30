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

#ifndef RANGERECORD_HPP_
#define RANGERECORD_HPP_

#if __cplusplus >= 201103L //C++0x

#include <algorithm>

using namespace std;

namespace Range
{
	class it final
	{
		protected:
		int now, step;

		it(int now, int step = 1)
		{
			this->now = now;
			this->step = step;
		}

		friend class Range_record;

		public:
		int operator*() const
		{
			return now;
		}

		it& operator++()
		{
			//ǰ����
			now += step;
			return *this;
		}

		bool operator!=(const it &with) const
		{
			return this->now != with.now;
		}
	};

	class Range_record final
	{
		protected:
		int from, to, step;

		Range_record(int to);
		Range_record(int from, int to, int step = 1);

		friend Range_record range(int to);
		friend Range_record range(int from, int to, int step);

		public:
		it begin() const
		{
			return it(from, step);
		}

		it end() const
		{
			return it(to, step);
		}
	};

	inline Range_record range(int from, int to, int step = 1)
	{
		return Range_record(from, to, step);
	}

	inline Range_record range(int to)
	{
		return Range_record(0, to, 1);
	}

} /* End of namespace Range */
using namespace Range;

#endif /* End C++0x */

#endif /* End RANGERECORD_HPP_ */
