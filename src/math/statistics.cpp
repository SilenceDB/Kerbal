#include <math.h>

#include "statistics.hpp"

#include "basic_math.hpp"

double sum(int argc, ...)
{
	double sum = 0.0;
	va_list arg_ptr; //ָ�������ָ��
	va_start(arg_ptr, argc);
	for (int i = 0; i <= argc - 1; i++) {
		sum += va_arg(arg_ptr, double);
	}

	va_end(arg_ptr);
	return sum;
}

unsigned __int64 fact(unsigned int n) //����׳�, Ŀǰ���㵽20!
{
	unsigned __int64 result = 1;
	if (n >= 2) {
		for (unsigned int i = 2; i <= n; i++) {
			result *= i;
		}
	}
	return result;
}

unsigned long combine(int n, int r) throw (invalid_argument)
{
	//cout<< m <<","<<n<<endl;

	if (r > n) {
		throw(invalid_argument("while compute C(n,r) , r>n"));
	}

	if (n - r > r) {
		r = n - r;
	}
	int i, j, s = 1;
	for (i = 0, j = 1; i < r; ++i) {
		s *= (n - i);
		while (j <= r && s % j == 0) {
			s /= j;
			j++;
		}
	}
	return s;
}

double normdist(double x, double sigma, double miu) //��̬�ֲ��ĸ����ܶȺ���, miu=ave, sigma=expect
{
	return exp(pow((x - miu) / sigma, 2) / (-2)) / sqrt(2 * M_PI) / sigma;
}

double std_normdist(double x) //��׼��̬�ֲ��ĸ����ܶȺ���, miu=ave, sigma=expect
{
	return exp(x * x / (-2)) / sqrt(2 * M_PI);
}

double broad_combine(double a, unsigned int r)
{
	/*����

	 (  a  )
	 (  r  )

	 */
	double result = 1.0;
	if (r == 0) {
		result = 1.0;
	} else {
		for (unsigned int i = 0; i <= r - 1; i++) {
			result *= (a - i) / (r - i);
		}
	}
	return result;
}

double regression(double x[], double y[], int len, double &a, double &b) //���Իع�
{
	double x_ave = ave(x, len);
	double y_ave = ave(y, len);
	double sum_dist = 0.0, sum_dist_x = 0.0, sum_dist_y = 0.0;

	for (int i = 0; i < len; i++) {
		sum_dist += (x[i] - x_ave) * (y[i] - y_ave);
		sum_dist_x += (x[i] - x_ave) * (x[i] - x_ave);
		sum_dist_y += (y[i] - y_ave) * (y[i] - y_ave);
	}
	b = sum_dist / sum_dist_x;
	a = y_ave - b * x_ave;
	return (sum_dist / sqrt(sum_dist_x * sum_dist_y));
}
