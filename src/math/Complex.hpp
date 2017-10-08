#ifndef _COMPLEX_H_
#define _COMPLEX_H_

#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <sstream>

#include "../except_C++0x.hpp"
#include "../String_serve.hpp"

namespace complex
{
	namespace
	{
		using namespace std;
	}

	class Complex
	{
		public:
			//��Ա
			double real;
			double imag;

			Complex(double real = 0.0, double imag = 0.0)
			{ //��ʼ��
				this->real = real;
				this->imag = imag;
			}

			operator double() throw (invalid_argument)
			{
				if (imag == 0) {
					return real;
				} else {
#if __cplusplus>= 201103L //C++0x
					throw invalid_argument("error:imag=" + std::to_string(imag));
#else
					throw invalid_argument("error:imag=" + _String::to_string(imag));
#endif
				}
			}

			//����
			string to_string() const;
			void display() const;
			double moudle() const; //���ظ�����ģ��
			double argz() const; //���ظ����ķ���

			//���������
			friend const Complex operator+(const Complex &a, const Complex &b);
			friend const Complex operator+(const Complex &a, double b);
			friend const Complex operator+(double a, const Complex &b);
			Complex& operator+=(const Complex &with);
			Complex& operator+=(const double &with);

			friend const Complex operator-(const Complex &a, const Complex &b);
			friend const Complex operator-(const Complex &a, double b);
			friend const Complex operator-(double a, const Complex &b);
			Complex& operator-=(const Complex &with);
			Complex& operator-=(const double &with);

			friend const Complex operator*(const Complex &a, const Complex &b);
			friend const Complex operator*(const Complex &a, double b);
			friend const Complex operator*(double a, const Complex &b);
			Complex& operator*=(const Complex &with);
			Complex& operator*=(const double &with);

			friend const Complex operator/(const Complex &a, const Complex &b) throw (invalid_argument);
			friend const Complex operator/(const Complex &a, double b) throw (invalid_argument);
			friend const Complex operator/(double a, const Complex &b) throw (invalid_argument);
			Complex& operator/=(const Complex &with) throw (invalid_argument);
			Complex& operator/=(const double &with) throw (invalid_argument);

			friend bool operator==(const Complex &a, const Complex &b);
			friend bool operator==(const Complex &a, double b);
			friend bool operator==(double a, const Complex &b);

			friend bool operator!=(const Complex &a, const Complex &b);
			friend bool operator!=(const Complex &a, double b);
			friend bool operator!=(double a, const Complex &b);

			friend ostream& operator <<(ostream &output, const Complex &z);
			friend istream& operator >>(istream &input, Complex &z);

			friend const Complex operator+(const Complex &a);
			friend const Complex operator-(const Complex &a);
			friend const Complex operator~(const Complex &a); //����һ�������Ĺ����
	};

	const Complex imag(0, 1.0);

	//����

	const Complex trans(double r, double thita); //����ģ���ͷ��Ƿ���һ������
	const Complex zpow(const Complex &z, int n); //����һ����������
	const Complex zln(const Complex &z); //����һ����������Ȼ��������ֵLnz=lnz+2*k*pi*i , lnz=ln|z|+i*argz(z)
	string to_string(const Complex &z);

	void quac_equ(double a, double b, double c, Complex &x1, Complex &x2, short &num) throw (invalid_argument);
//һԪ���η���

} /* End of namespace complex */

//#pragma message(__DATE__ "  " __TIME__"  �������"__FILE__)

#endif	/* End _COMPLEX_H_ */
