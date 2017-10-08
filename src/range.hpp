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

#include "except_C++0x.hpp"

namespace Range
{

#if __cplusplus >= 201103L //C++0x

	class Range_record;
	//��Range_iteratorʹ�õ�ǰ����������
	class Range_iterator final
	{
		protected:
			friend class Range_record;
			int now;
			const Range_record * parent_ptr;

			Range_iterator(int now, const Range_record &parent);

		public:
			int operator*() const;
			Range_iterator& operator++();
			bool operator!=(const Range_iterator &with) const;
	};

	class Range_record final
	{
		protected:
			friend class Range_iterator;

			int from, to, step;

			Range_record(int to);
			Range_record(int from, int to, int step = 1) throw (std::invalid_argument);

			friend Range_record range(int to);
			friend Range_record range(int from, int to, int step);

		public:
			Range_iterator begin() const
			{
				if ((from < to && step < 0) || from == to || (from > to && step > 0)) {
					return end();
				}
				return Range_iterator(from, *this);
			}

			Range_iterator end() const
			{
				return Range_iterator(to, *this);
			}

			bool whether_in(int x) const
			{ //����α�x�Ƿ��ڷ�Χ��
				if (from < to) {
					return (from <= x && x < to);
				} else {
					return (to < x && x <= from);
				}
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

#endif /* End C++0x */

} /* namespace Range */

#endif /* End RANGE_HPP_ */
