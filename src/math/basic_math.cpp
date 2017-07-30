#include "basic_math.hpp"

#include <cmath>
#include "../String_serve.hpp"

using namespace std;

double round(double x, int digits)
{
	double result = (int) (x * pow(10, -digits) + 0.5) / pow(10, -digits);
	if (x >= 0) {
		return result;
	} else {
		return -result;
	}
}

double baremainder(double x, double y) //������������������� ����ķ����������ͬ��
{
	int quotient;
	if (x / y > 0) {
		quotient = x / y;
	} else {
		quotient = (int) (x / y) - 1;
	}
	return x - y * quotient;
}

unsigned short float_num(double a, double digits) //BUG
{
	return abs((int) (10 * decimal(a * pow(10, -digits))));
}

double up(double x, int digits)
{
	if (x >= 0) {
		//cout << float_num(-12.3456,-2)<<endl;

		if (float_num(x, digits - 1) <= 4) {
			x += 5 * pow(10, digits - 1);
		}

		return (int) (x * pow(10, -digits) + 0.5) / pow(10, -digits);
	} else {
		return -(int) (-x * pow(10, -digits) + 0.5) / pow(10, -digits);
	}
}

int gcd(int a, int b)
{
	int temp;
	while (b) {
		temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}

int lcm(int a, int b)
{
	return a / gcd(a, b) * b;
}

bool is_prime(int x)
{
	for (int i = 2; i * i <= x; i++) {
		if (!(x % i)) {
			return false;
		}
	}
	return true;
}

void fraction(double a, int &i, int &j) throw (int)
{
	double x = fabs(a);
	int zhengshu = int(x);
	double xiaoshu = x - zhengshu;

	if (fabs(xiaoshu) <= 0.0000000000001) {
		i = x;
		j = 1;
		return;
	} else if (fabs(xiaoshu - 1) <= 0.0000000000001) {
		i = x + 1;
		j = 1;
		return;
	}

	i = 1;
	j = 2;
	double eps;
	for (int counter = 0; i < 10000 && j < 10000; counter++) {
		eps = double(i) / double(j) - xiaoshu;
		if (fabs(eps) <= 0.0000000000001) {
			i = (zhengshu * j + i);
			return;
		} else if (eps > 0) {
			j++;
		} else {
			i++;
		}
	}
	throw 0;

	//	try {
	//		fraction(n,i,j);
	//		if(n<0) {
	//			cout<<"-";
	//		}
	//		if(j==1) {
	//			cout<<i<<endl;
	//		} else {
	//			cout<<i<<"/"<<j<<endl;
	//		}
	//	} catch(int) {
	//		printf("%.25f\n",n);
	//	}
}

string a_divide_b(double a) throw (int)
{
	double x;
	int i, j;
	string result = "";
	try {
		//���a/b��
		x = fabs(a);
		fraction(x, i, j);
		if (a < 0) {
			result += "-";
		}
		if (j == 1) {
			result += to_string(i);
		} else {
			result += to_string(i) + "/" + to_string(j);
		}
		return result;
	} catch (int) {
		throw 0;
	}
}

string a_PI_divide_b(double a) throw (int)
{
	double x;
	int i, j;
	string result = "";
	try {
		//���a��/b��
		x = fabs(a) / M_PI;
		fraction(x, i, j);
		if (a < 0) {
			result += "-";
		}
		if (j == 1) {
			if (i == 1) {
				result += "��";
			} else {
				result += to_string(i) + "��";
			}
		} else {
			if (i == 1) {
				result += "��/" + to_string(j);
			} else {
				result += to_string(i) + "��/" + to_string(j);
			}
		}
		return result;
	} catch (int) {
		throw 0;
	}
}

string a_divide_b_PI(double a) throw (int)
{
	double x;
	int i, j;
	string result = "";
	try {
		//���a/b����
		x = fabs(a) * M_PI;
		fraction(x, i, j);
		if (a < 0) {
			result += "-";
		}
		if (j == 1) {
			result += to_string(i) + "/��";
		} else {
			result += to_string(i) + "/" + to_string(j) + "��";
		}
		return result;
	} catch (int) {
		throw 0;
	}
}

string a_E_divide_b(double a) throw (int)
{
	double x;
	int i, j;
	string result = "";
	try {
		//���ae/b��
		x = fabs(a) / M_E;
		fraction(x, i, j);
		if (a < 0) {
			result += "-";
		}
		if (j == 1) {
			if (i == 1) {
				result += "e";
			} else {
				result += to_string(i) + "e";
			}
		} else {
			if (i == 1) {
				result += "e/" + j;
			} else {
				result += to_string(i) + "e/" + to_string(j);
			}
		}
		return result;
	} catch (int) {
		throw 0;
	}
}

string a_divide_b_E(double a) throw (int)
{
	double x;
	int i, j;
	string result = "";
	try {
		//���a/be��
		x = fabs(a) * M_E;
		fraction(x, i, j);
		if (a < 0) {
			result += "-";
		}
		if (j == 1) {
			result += to_string(i) + "/e";
		} else {
			result += to_string(i) + "/" + to_string(j) + "e";
		}
		return result;
	} catch (int) {
		throw 0;
	}
}

string sqrt_a_divide_b(double a) throw (int)
{
	double x;
	int i, j;
	string result = "";
	try {
		//����(a/b)��
		x = a * a;
		fraction(x, i, j);
		if (a < 0) {
			result += "-";
		}
		if (j == 1) {
			result += "��(" + to_string(i) + ")";
		} else {
			int temp = sqrt(i);
			if (temp * temp == i) {
				//i���������
				result += to_string(temp) + "/��(" + to_string(j) + ")";
			} else {
				temp = sqrt(j);
				if (temp * temp == j) {
					//j���������
					result += "��(" + to_string(i) + ")/" + to_string(temp);
				} else {
					result += "��(" + to_string(i) + "/" + to_string(j) + ")";
				}
			}
		}
		return result;
	} catch (int) {
		throw 0;
	}
}

string ln_a_divide_b(double a) throw (int)
{
	double x;
	int i, j;
	string result = "";
	try {
		x = exp(a);
		fraction(x, i, j);
		if (a < 0) {
			result += "-";
		}
		if (j == 1) {
			result += "ln(" + to_string(i) + ")";
		} else {
			result += "ln(" + to_string(i) + "/" + to_string(j) + ")";
		}
		return result;
	} catch (int) {
		throw 0;
	}
}

string log_2_a_divide_b(double a) throw (int)
{
	double x;
	int i, j;
	string result = "";
	try {
		x = pow(2, a);
		fraction(x, i, j);
		if (a < 0) {
			result += "-";
		}
		if (j == 1) {
			result += "log_2(" + to_string(i) + ")";
		} else {
			result += "log_2(" + to_string(i) + "/" + to_string(j) + ")";
		}
		return result;
	} catch (int) {
		throw 0;
	}
}

string log_10_a_divide_b(double a) throw (int)
{
	double x;
	int i, j;
	string result = "";
	try {
		x = pow(10, a);
		fraction(x, i, j);
		if (a < 0) {
			result += "-";
		}
		if (j == 1) {
			result += "log_10(" + to_string(i) + ")";
		} else {
			result += "log_10(" + to_string(i) + "/" + to_string(j) + ")";
		}
		return result;
	} catch (int) {
		throw 0;
	}
}

string sin_a_divide_b(double a) throw (int)
{
	double x;
	int i, j;
	string result = "";
	try {
		//���sin(a/b)��,ע��a/b>90ʱ�޷�ʶ��
		x = asin(a) * 180 / M_PI;
		fraction(x, i, j);
		if (a < 0) {
			result += "-";
		}
		if (j == 1) {
			result += "sin(" + to_string(i) + "deg)";
		} else {
			result += "sin(" + to_string(i) + "/" + to_string(j) + "deg)";
		}
		return result;
	} catch (int) {
		throw 0;
	}
}

string tan_a_divide_b(double a) throw (int)
{
	double x;
	int i, j;
	string result = "";
	try {
		//���tan(a/b)��,ע��/*a/b>90ʱ�޷�ʶ��*/
		x = atan(a) * 180 / M_PI;
		fraction(x, i, j);
		if (a < 0) {
			result += "-";
		}
		if (j == 1) {
			result += "tan(" + to_string(i) + "deg)";
		} else {
			result += "tan(" + to_string(i) + "/" + to_string(j) + "deg)";
		}
		return result;
	} catch (int) {
		throw 0;
	}
}

string asin_a_divide_b(double a) throw (int)
{
	double x;
	int i, j;
	string result = "";
	try {
//���asin(a/b)��
		x = sin(a);
		fraction(x, i, j);
		if (a < 0) {
			result += "-";
		}
		if (j == 1) {
			result += "asin(" + to_string(i) + ")";
		} else {
			result += "asin(" + to_string(i) + "/" + to_string(j) + ")";
		}
		return result;
	} catch (int) {
		throw 0;
	}
}

string atan_a_divide_b(double a) throw (int)
{
	double x;
	int i, j;
	string result = "";
	try {
//���atan(a/b)��
		x = tan(a);
		fraction(x, i, j);
		if (a < 0) {
			result += "-";
		}
		if (j == 1) {
			result += "atan(" + to_string(i) + ")";
		} else {
			result += "atan(" + to_string(i) + "/" + to_string(j) + ")";
		}
		return result;
	} catch (int) {
		throw 0;
	}
}

string fraction(double a)
{
	try {
//���a/b��
		return a_divide_b(a);
	} catch (int) {
		goto a_PI_divide_b;
	}

	a_PI_divide_b: try {
//���a��/b��
		return a_PI_divide_b(a);
	} catch (int) {
		goto a_divide_b_PI;
	}

	a_divide_b_PI: try {
//���a/b����
		return a_divide_b_PI(a);
	} catch (int) {
		goto a_E_divide_b;
	}

	a_E_divide_b: try {
//���ae/b��
		return a_E_divide_b(a);
	} catch (int) {
		goto a_divide_b_E;
	}

	a_divide_b_E: try {
//���a/be��
		return a_divide_b_E(a);
	} catch (int) {
		goto sqrt_a_divide_b;
	}

	sqrt_a_divide_b: try {
//����(a/b)��
		return sqrt_a_divide_b(a);
	} catch (int) {
		goto ln_a_divide_b;
	}

	ln_a_divide_b: try {
//���ln(a/b)��
		return ln_a_divide_b(a);
	} catch (int) {
		goto log_2_a_divide_b;
	}

	log_2_a_divide_b: try {
//���ln(a/b)��
		return log_2_a_divide_b(a);
	} catch (int) {
		goto log_10_a_divide_b;
	}

	log_10_a_divide_b: try {
//���ln(a/b)��
		return log_10_a_divide_b(a);
	} catch (int) {
		goto sin_a_divide_b;
	}

	sin_a_divide_b: try {
//���sin(a/b)��
		return sin_a_divide_b(a);
	} catch (int) {
		goto tan_a_divide_b;
	}

	tan_a_divide_b: try {
//���tan(a/b)��
		return tan_a_divide_b(a);
	} catch (int) {
//cout<<"���ܲ��"<<endl;
		goto asin_a_divide_b;
	}

	asin_a_divide_b: try {
//���asin(a/b)��
		return asin_a_divide_b(a);
	} catch (int) {
		goto atan_a_divide_b;
	}

	atan_a_divide_b: try {
//���atan(a/b)��
		return atan_a_divide_b(a);
	} catch (int) {
		goto fail;
	}

	fail:

	return to_string(a);

	//	if(x==M_LOG2E) {
	//		if(a<0) {
	//			cout<<"-";
	//		}
	//		return "M_LOG2E";
	//	} else if(x==M_LOG10E) {
	//		if(a<0) {
	//			cout<<"-";
	//		}
	//		return "M_LOG10E";
	//	} else if(x==M_2_SQRTPI) {
	//		if(a<0) {
	//			cout<<"-";
	//		}
	//		return "2/��(��)";
	//	} else {
	//		return to_string(a);
	//	}

}

