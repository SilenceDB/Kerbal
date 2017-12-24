#ifndef _INTEGRAL_HPP_
#define _INTEGRAL_HPP_

double dy(double x, double dx, double (*f)(double)); //΢y
double derivative(double x, double (*f)(double), double dx = 0.001); //����
double ladder(double a, double b, double dx, double (*f)(double)); //���η�����
double simpson(double a, double b, double dx, double (*f)(double)); //��������ʽ����
double normal_integral(double b, double dx); //��׼��̬�ֲ�����

double B(int n); //���㲮Ŭ����
double Stirling(double x); //˹���ֹ�ʽ
double logGamma(double z);
double Gamma(double z);
double Beta(double P, double Q);

#endif	/* End _INTEGRAL_HPP_ */
