/*
 * Complexor.h
 *
 *  Created on: 2017��5��8��
 *      Author: Peter
 */

#ifndef COMPLEXOR_H_
#define COMPLEXOR_H_

#include <iostream>
#include <iomanip>
#include <cstring>
#include "Matrix.hpp"
#include "../except_C++0x.hpp"

namespace complexor
{
	using namespace std;
	using namespace matrix;

	//��Ԫ��������
	template <class Type> class Complexor;

	template <class Type> const Complexor<Type> operator+(const Complexor<Type> &a, const Complexor<Type> &b) throw (invalid_argument);
	template <class Type> const Complexor<Type> operator-(const Complexor<Type> &a, const Complexor<Type> &b) throw (invalid_argument);

	template <class Type> const Complexor<Type> TransposeOf(const Complexor<Type> &src);

	template <class Type> const Complexor<Type> operator*(const Matrix &M, const Complexor<Type> &V) throw (invalid_argument);
	//�������������, ��������
	template <class Type> const Complexor<Type> operator*(const Complexor<Type> &V, const Matrix &M) throw (invalid_argument);
	//���������Ծ���, ��������
	template <class Type> const Type dot_product(const Complexor<Type> &a, const Complexor<Type> &b) throw (invalid_argument);
	//�������, ����ʵ��
	template <class Type> const Matrix operator*(const Complexor<Type> &a, const Complexor<Type> &b) throw (invalid_argument);
	//������������, ���ؾ���
	template <class Type> const Complexor<Type> operator*(const double &k, const Complexor<Type> &b); //��k��������
	template <class Type> const Complexor<Type> operator*(const Complexor<Type> &b, const double &k); //����������k
	template <class Type> Type abs(const Complexor<Type> &src); //������ģ
	template <class Type> Type angle(const Complexor<Type> &a, const Complexor<Type> &b) throw (invalid_argument);
	//�����н�

	//������
	template <class Type>
	class Complexor
	{
		protected:
			Type *p;
			int num;
			bool vertical; //Ĭ��������

			void mem_init()
			{
				try {
					p = new Type[num];
				} catch (const bad_alloc &exct) {
					num = 0;
					throw;
				}
			}

			void resize(int new_num)
			{ //TODO BUG
				bool alloc = false;
				if (alloc) {
					//new[] delete[]����
					Type *p_former = p;
					try {
						p = new Type[new_num];
						std::copy(p_former, p_former + std::min(num, new_num), p);
						num = new_num;
						delete[] p_former;
						p_former = NULL;
					} catch (const bad_alloc &exct) { //�ڴ����ʧ��
						delete[] p_former;
						num = 0;
						p_former = NULL;
						p = NULL;
						throw;
					}
				} else {
					//alloc����
					Type *p_new = (Type*) realloc(p, new_num * sizeof(Type));
					if (p_new == NULL) { //�ڴ����ʧ��
						num = 0;
						free(p);
						p = NULL;
						p_new = NULL;
						throw bad_alloc();
					} else { //�ڴ����ɹ�
						p = p_new;
						num = new_num;
						p_new = NULL;
					}
				}
			}

			void test_index(int num_test) const throw (out_of_range)
			{
				if (num_test < 0 || num_test >= num) {
					throw out_of_range("the complexor doesn't have the index");
				}
			}

		public:
			Complexor(const int num = 0, const bool if_set0 = true, const bool vertical = true) throw (bad_alloc);
			Complexor(const Complexor &src) throw (bad_alloc); //�������캯��
			Complexor(const Matrix &src, int index = 0, const bool vertical = true) throw (bad_alloc);
			Complexor(const Type src[], const int num, const bool vertical = true) throw (bad_alloc);
			Complexor(const int num, Type (*function)(), const bool vertical = true) throw (bad_alloc);
			Complexor(const int num, Type (*function)(int), const bool vertical = true) throw (bad_alloc);

#if __cplusplus >= 201103L //C++0x
			//Complexor Ϊ C++ 11 ׼����������: ���ó�ʼ���б���й���
			Complexor(initializer_list<Type> src);
#endif //C++0x

			operator Matrix();
			virtual ~Complexor();
			bool is_const();
			bool is_const() const;

			bool empty() const;
			void clear();

			const Complexor call(Type (*__pf)(Type));

			void set_element(int index, const Type &value) throw (out_of_range)
			{
				test_index(index);
				p[index] = value;
			}

			Type& get_element(int index) throw (out_of_range)
			{
				test_index(index);
				return p[index];
			}

			const Type& get_element(int index) const throw (out_of_range)
			{
				test_index(index);
				return p[index];
			}

			int get_num() const
			{
				return num;
			}

			bool is_vertical() const
			{
				return vertical;
			}

			void print() const;

			const Type* get_data() const
			{
				return p;
			}

			size_t get_digit_size() const
			{
				return num * sizeof(Type);
			}

			Complexor& operator=(const Complexor &src);
			Type& operator[](int index) throw (out_of_range);
			const Type& operator[](int index) const throw (out_of_range);

			friend const Complexor operator+<>(const Complexor &a, const Complexor &b) throw (invalid_argument);
			//�����ӷ�, ����ͬһ�ɷ���������
			friend const Complexor operator-<>(const Complexor &a, const Complexor &b) throw (invalid_argument);
			//��������, ����ͬһ�ɷ���������

			Complexor& operator+=(const Complexor &with) throw (invalid_argument);  //�����ӷ�
			Complexor& operator-=(const Complexor &with) throw (invalid_argument);  //�����ӷ�

			const Complexor operator+() const; //���������ķ���ͬ������
			const Complexor operator-() const; //���������ķ���ͬ������

			Complexor& doTranspose();
			friend const Complexor TransposeOf<>(const Complexor &src);

			friend const Complexor operator*<>(const Matrix &M, const Complexor &V) throw (invalid_argument);
			//�������������, ��������
			friend const Complexor operator*<>(const Complexor &V, const Matrix &M) throw (invalid_argument);
			//���������Ծ���, ��������
			friend const Type dot_product<>(const Complexor &a, const Complexor &b) throw (invalid_argument);
			//�������, ����ʵ��
			friend const Matrix operator*<>(const Complexor &a, const Complexor &b) throw (invalid_argument);
			//������������, ���ؾ���
			friend const Complexor operator*<>(const double &k, const Complexor &b); //��k��������
			friend const Complexor operator*<>(const Complexor &b, const double &k); //����������k

			friend Type abs<>(const Complexor &src); //������ģ

//			friend void print_array_to_file(const Complexor &src, string separator, string file_name, bool if_output_number =
//					false) throw (invalid_argument);

			Type* const begin() const
			{
				return p;
			}

			Type* const end() const
			{
				return p + num;
			}

			friend Type angle<>(const Complexor &a, const Complexor &b) throw (invalid_argument);
			//�����н�
//			friend const Complexor<Type> eqution(Matrix m) throw (invalid_argument);
	};
#if __cplusplus >= 201103L //C++0x
	template <class Type1, class Type2>
	auto operator+(const Complexor<Type1> &a, const Complexor<Type2> &b) throw (invalid_argument) ->const Complexor<decltype(a[0]+b[0])>;
	//������ͬ���������ļӷ�, ����ͬһ�ɷ���������, �Զ��Ƶ���������, ��: Complexor<int> + Complexor<double> = Complexor<double>

	template <class Type1, class Type2>
	auto operator-(const Complexor<Type1> &a, const Complexor<Type2> &b) throw (invalid_argument)->const Complexor<decltype(a[0]-b[0])>;
//������ͬ���������ļ���, ����ͬһ�ɷ���������, �Զ��Ƶ���������, ��: Complexor<int> - Complexor<double> = Complexor<double>

	template <class Type1, class Type2>
	auto dot_product(const Complexor<Type1> &a, const Complexor<Type2> &b) throw (invalid_argument) ->const decltype(a[0]*b[0]);
//�������
#endif //c++0x

} /* namespace complexor */

#endif /* COMPLEXOR_H_ */

#include "Complexor_base.hpp" /* ʵ�� */
