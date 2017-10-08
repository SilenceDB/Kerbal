/*
 * choose.hpp
 *
 *  Created on: 2017��7��8��
 *      Author: Peter
 *      Fuction: �ṩ�� choose ������֧��
 */

#ifndef CHOOSE_HPP_
#define CHOOSE_HPP_

#include <iostream>
#include <cstdarg>
#include "except_C++0x.hpp"

#if __cplusplus >= 201103L //C++0x
# include <initializer_list>
#endif /* End C++0x */

namespace _choose
{
	namespace
	{
		using namespace std;
	}

	//����
	/*	choose: �ɱ��������� choose ����*/
	template <class T> T choose(int index, T value0, ...) throw (invalid_argument);

#if __cplusplus >= 201103L //C++0x
	/*  choose Ϊ C++ 11 ׼����������: ��ʼ���б���� choose ����*/
	template <class T> T choose(int index, initializer_list<T> src) throw (invalid_argument, out_of_range);

	/*	choose_c11 Ϊ C++ 11 ׼����������: �ɱ����ģ����� choose ����*/
	template <class T, class ...Args> T choose_c11(int index, T head, Args ... args) throw (invalid_argument, out_of_range);
#endif

	/*	ʵ�� */

	/*	choose: �ɱ��������� choose ������ʵ��*/
	template <class T>
	T choose(int index, T value0, ...) throw (invalid_argument)
	{
		if (index < 0) {
			throw invalid_argument("index<0");
		} else if (index == 0) {
			return value0;
		}

		va_list arg_ptr; //ָ�������ָ��
		va_start(arg_ptr, value0);

		for (int i = 1; i < index; i++) {
			va_arg(arg_ptr, T);
		}
		va_end(arg_ptr);
		return va_arg(arg_ptr, T);
	}

	/*
	 * Ϊ��ҪΪ [signed/unsigned]char , [unsigned]short , float ���͵���д choose ����, ��ο�:
	 * http://www.cppblog.com/ownwaterloo/archive/2009/04/21/unacceptable_type_in_va_arg.html
	 */
	namespace
	{
		template <class T>
		T choose_int(int index, const T &value0, va_list &arg_ptr) throw (invalid_argument)
		{
			if (index < 0) {
				throw invalid_argument("index<0");
			} else if (index == 0) {
				return value0;
			}

			for (int i = 1; i < index; i++) {
				va_arg(arg_ptr, int);
			}
			return va_arg(arg_ptr, int);
		}

		template <class T>
		T choose_float(int index, const T &value0, va_list &arg_ptr) throw (invalid_argument)
		{
			if (index < 0) {
				throw invalid_argument("index<0");
			} else if (index == 0) {
				return value0;
			}

			for (int i = 1; i < index; i++) {
				va_arg(arg_ptr, double);
			}
			return va_arg(arg_ptr, double);
		}
	}

	char choose(int index, char value0, ...) throw (invalid_argument);
	unsigned char choose(int index, unsigned char value0, ...) throw (invalid_argument);
	signed char choose(int index, signed char value0, ...) throw (invalid_argument);

	short choose(int index, short value0, ...) throw (invalid_argument);
	unsigned short choose(int index, unsigned short value0, ...) throw (invalid_argument);

	float choose(int index, float value0, ...) throw (invalid_argument);

#if __cplusplus >= 201103L //C++0x
//choose Ϊ C++ 11 ׼����������: ��ʼ���б���� choose ����
	template <class T>
	T choose(int index, initializer_list<T> src) throw (invalid_argument, out_of_range)
	{
		if (index < 0) {
			throw invalid_argument("index<0");
		} else if (index >= src.size()) {
			throw out_of_range("index is out of range");
		}
		return *(src.begin() + index);
	}
#endif //C++0x

#if __cplusplus >= 201103L //C++0x
//choose_c11 Ϊ C++ 11 ׼����������: �ɱ����ģ����� choose ����
	namespace //���������ռ��ڵ����ݶ��ļ��ⲻ�ɼ�
	{
//		int choose_unpack(int total);

		template <class T, class ...Args>
		T choose_unpack(int total, T head, Args ... rest)
		{ //չ������
			if (total == 0) {
				return head;
			} else {
				return (T) choose_unpack(total - 1, rest...);
			}
		}
	}/* Namespace */

	template <class T, class ...Args>
	T choose_c11(int index, T head, Args ... args) throw (invalid_argument, out_of_range)
	{
		if (index < 0) {
			throw invalid_argument("index < 0");
		} else if (index > (int) sizeof...(Args)) {
			throw out_of_range("index is out of range");
		} else if (index == 0) {
			return head;
		} else {
			return choose_unpack(index - 1, args...);
		}
	}
#endif

}/* Namespace _choose */

#endif /* End CHOOSE_HPP_ */
