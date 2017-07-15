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
#include <stdexcept>

#include "Matrix.h"

using namespace std;

#if __cplusplus < 201103L //C++0x
# pragma message("Complexor ʹ���� C++ 11 ������, ��� C++ 11 ѡ���Ա�ʹ����Щ������")
#else
#include <initializer_list>
#endif //C++0x

class Complexor //: public Matrix
{
	protected:
		double *p;
		int num;
		bool vertical; //Ĭ��������

		void test_index(int num_test) const throw (out_of_range)
		{
			if (num_test < 0 || num_test >= num) {
				throw out_of_range("");
			}
		}

	public:
		Complexor(const int num = 0, const bool if_set0 = true, const bool vertical = true);
		Complexor(const Complexor &src);
		Complexor(const Matrix &src, int index = 0, const bool vertical = true);
		Complexor(double src[], const int num, const bool vertical = true);

#if __cplusplus < 201103L //C++0x
//# pragma message("Complexor Ϊ C++ 11 ׼����������: ���ó�ʼ���б���й���")
#else
		Complexor(initializer_list<double> a)
		{
			num = a.size();
			p = new double[num];
			vertical = true;

			int i = 0;
			for (auto ele : a) {
				p[i] = ele;
				i++;
			}
		}
#endif

		/*explicit */
		operator Matrix()
		{
			if (this->vertical) {
				Matrix result(num, 1, false);
				for (int i = 0; i < num; i++) {
					result.set_element(i, 0, p[i]);
				}
				return result;
			} else {
				Matrix result(1, num, false);
				for (int i = 0; i < num; i++) {
					result.set_element(0, i, p[i]);
				}
				return result;
			}
		}
		virtual ~Complexor();
		bool is_const();
		bool is_const() const;

		bool empty() const;
		void clear();

		void set_element(int index, int value) throw (out_of_range)
		{
			test_index(index);
			p[index] = value;
		}

		double get_element(int index) const throw (out_of_range)
		{
			test_index(index);
			return p[index];
		}

		int get_num() const
		{
			return num;
		}

		void print() const
		{
			cout << resetiosflags(ios::right) << setiosflags(ios::left) << setfill(' '); //����Ҷ���, ���������, ���ò��㲹�ո�
			cout << "(";

			if (!empty()) {
				cout << "  " << setw(10) << p[0];
				for (int i = 1; i < num; i++) {
					cout << ", " << setw(10) << p[i];
				}
			}

			cout << " )";
			if (this->vertical) {
				cout << " T";
			}
			cout << endl;
		}

		size_t get_digit_size() const
		{
			return num * sizeof(double);
		}

		friend Complexor operator+(const Complexor &a, const Complexor &b) throw (invalid_argument); //�����ӷ�, ����������
		friend Complexor operator-(const Complexor &a, const Complexor &b) throw (invalid_argument); //��������, ����������
		Complexor operator-() const; //���������ķ���ͬ������
		const Complexor& operator=(const Complexor &src);
		double& operator[](int index) throw (out_of_range);
		const double& operator[](int index) const throw (out_of_range);

		friend Complexor Transpose(const Complexor &src);

		friend Complexor operator*(const Matrix &M, const Complexor &V) throw (invalid_argument); //�������������, ��������
		friend Complexor operator*(const Complexor &V, const Matrix &M) throw (invalid_argument); //���������Ծ���, ��������
		friend double dot_product(const Complexor &a, const Complexor &b) throw (invalid_argument); //�������, ����ʵ��
		friend Matrix operator*(const Complexor &a, const Complexor &b) throw (invalid_argument); //������������, ���ؾ���
		friend Complexor operator*(const int &k, const Complexor &b); //��k��������
		friend Complexor operator*(const Complexor &b, const int &k); //����������k

		friend double abs(const Complexor &src); //������ģ

		friend void print_array_to_file(const Complexor &src, string separator, string file_name, bool if_output_number = false) throw (invalid_argument);

};
double operator^(const Complexor &a, const Complexor &b) throw (invalid_argument);
//�����н�
Complexor eqution(Matrix m) throw (invalid_argument);

#endif /* COMPLEXOR_H_ */
