//#pragma once

#ifndef _BASIC_MATH_H_
#define _BASIC_MATH_H_

//#pragma message(__DATE__ "  " __TIME__"  ���ڱ���"__FILE__)

#include <iostream>
#include <cmath>
#include <stdexcept>
#include "String.h"

using namespace std;

#if __cplusplus < 201103L

#else
const double M_E = 2.7182818284590452354;
const double M_LOG2E = 1.4426950408889634074;
const double M_LOG10E = 0.43429448190325182765;
const double M_LN2 = 0.69314718055994530942;
const double M_LN10 = 2.30258509299404568402;
const double M_PI = 3.14159265358979323846;
const double M_PI_2 = 1.57079632679489661923;
const double M_PI_4 = 0.78539816339744830962;
const double M_1_PI = 0.31830988618379067154;
const double M_2_PI = 0.63661977236758134308;
const double M_2_SQRTPI = 1.12837916709551257390;
const double M_SQRT2 = 1.41421356237309504880;
const double M_SQRT1_2 = 0.70710678118654752440;
#endif

double round(double x, int digits);
inline bool diff(int m, int n) //m,n�Ƿ����
{
	return ((unsigned) (m ^ n) >> (8 * sizeof(int) - 1));
}

inline double decimal(double a)
{
	return a - (int) a;
}

inline float decimal(float a)
{
	return a - (int) a;
}

double baremainder(double x, double y); //�����������������������ķ����������ͬ
unsigned short float_num(double a, double digits); //BUG
double up(double x, int digits);
int gcd(int a, int b); //�������������Լ��
int lcm(int a, int b); //������������С������
bool is_prime(int x);
string fraction(double a);



#endif	/* End _BASIC_MATH_H_ */
