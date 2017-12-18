#include "statistics.hpp"
#include <math.h>

namespace kerbal
{
	namespace math
	{
		namespace statistics
		{

			unsigned long long fact(unsigned int n) //����׳�, Ŀǰ���㵽20!
			{
				unsigned long long result = 1;
				for (unsigned int i = 2; i <= n; i++) {
					result *= i;
				}
				return result;
			}

			unsigned long combine(int n, int r) throw (std::invalid_argument)
			{
				if (r > n) {
					throw std::invalid_argument("while compute C(n,r) , r>n");
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

			double broad_combine(double a, unsigned int r)
			{
				/*����

				 (  a  )
				 (  r  )

				 */
				double result = 1.0;

				for (unsigned int i = 0; i < r; i++) {
					result *= (a - i) / (r - i);
				}

				return result;
			}

			double regression(const double x[], const double y[], int len, double &a, double &b) //���Իع�
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

		}/* namespace statistics */
		using namespace statistics;
	} /* namespace math */
	using namespace math;
} /* namespace kerbal */
