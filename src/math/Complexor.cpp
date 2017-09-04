/*
 * Complexor.cpp
 *
 *  Created on: 2017年5月8日
 *      Author: Peter
 */

#include "Complexor.hpp"

#include <cmath>

#if __cplusplus < 201103L //C++0x
# pragma message("\n"\
"			* Complexor 使用了 C++ 11 新特性, 请打开 C++ 11 选项以便使用这些新特性\n"\
"					* Complexor 为 C++ 11 准备的新特性: 利用初始化列表进行构造"\
)
#endif //C++0x

namespace complexor
{
	using namespace std;
	using namespace matrix;

	Complexor::Complexor(const int num, const bool if_set0, const bool vertical) throw (bad_alloc)
	{
		if (num > 0) {
			this->num = num;
			p = new double[num];
			if (if_set0) {
				memset(p, 0, num * sizeof(double));
			}
		} else {
			this->num = 0;
			this->p = NULL;
		}
		this->vertical = vertical;
	}

	Complexor::Complexor(const Complexor &src) throw (bad_alloc)
	{
		if (src.num > 0) {
			this->num = src.num;
			this->p = new double[num];
			for (int i = 0; i < num; i++) {
				this->p[i] = src.p[i];
			}
		} else {
			this->num = 0;
			this->p = NULL;
		}
		this->vertical = src.vertical;
	}

	Complexor::Complexor(const Matrix &src, int index, const bool vertical) throw (bad_alloc)
	{
		if (vertical) {
			this->num = src.get_row();
			this->p = new double[num];
			for (int i = 0; i < num; i++) {
				p[i] = src[i][index];
			}
		} else {
			this->num = src.get_column();
			this->p = new double[num];
			for (int i = 0; i < num; i++) {
				p[i] = src[index][i];
			}
		}
		this->vertical = vertical;
	}

	Complexor::Complexor(const double src[], const int num, const bool vertical) throw (bad_alloc)
	{
		if (num > 0) {
			this->num = num;
			this->p = new double[num];
			for (int i = 0; i < num; i++) {
				p[i] = src[i];
			}
		} else {
			this->num = 0;
			p = NULL;
		}
		this->vertical = vertical;
	}

	Complexor::Complexor(const int num, double (*function)(), const bool vertical) throw (bad_alloc)
	{
		if (num > 0) {
			this->num = num;
			this->p = new double[num];
			for (int i = 0; i < num; i++) {
				p[i] = function();
			}
		} else {
			this->num = 0;
			p = NULL;
		}
		this->vertical = vertical;
	}

	Complexor::Complexor(const int num, double (*function)(int), const bool vertical) throw (bad_alloc)
	{
		if (num > 0) {
			this->num = num;
			this->p = new double[num];
			for (int i = 0; i < num; i++) {
				p[i] = function(i);
			}
		} else {
			this->num = 0;
			p = NULL;
		}
		this->vertical = vertical;
	}

	Complexor::~Complexor()
	{
		delete[] p;
		p = NULL;
	}

	bool Complexor::is_const()
	{
		return false;
	}

	bool Complexor::is_const() const
	{
		return true;
	}

	bool Complexor::empty() const
	{
		if (num == 0) {
			return true;
		} else {
			return false;
		}
	}

	void Complexor::clear()
	{
		delete[] p;
		p = NULL;
		num = 0;
	}

	Complexor operator+(const Complexor &a, const Complexor &b) throw (invalid_argument) //向量加法, 方向不同一律返回列向量
	{
		if (a.num != b.num) {
			throw invalid_argument("error: length(a) ≠ length(b)");
		}

		const int &num = a.num;
		Complexor result(num, false, a.vertical == b.vertical ? a.vertical : true);
		for (int i = 0; i < num; i++) {
			result.p[i] = a.p[i] + b.p[i];
		}
		return result;
	}

	Complexor& Complexor::operator+=(const Complexor &with) throw (invalid_argument)  //向量加法
	{
		if (num != with.num) {
			throw invalid_argument("error: length(a) ≠ length(b)");
		}

		for (int i = 0; i < num; i++) {
			p[i] += with.p[i];
		}

		return *this;
	}

	Complexor Complexor::operator+() const //返回向量的同向同长向量
	{
		return Complexor(*this);
	}

	Complexor operator-(const Complexor &a, const Complexor &b) throw (invalid_argument) //向量减法, 返回列向量
	{
		if (a.num != b.num) {
			throw invalid_argument("error: length(a) ≠ length(b)");
		}

		const int &num = a.num;
		Complexor result(num, false, a.vertical == b.vertical ? a.vertical : true);
		for (int i = 0; i < num; i++) {
			result.p[i] = a.p[i] - b.p[i];
		}
		return result;
	}

	Complexor& Complexor::operator-=(const Complexor &with) throw (invalid_argument)  //向量加法
	{
		if (num != with.num) {
			throw invalid_argument("error: length(a) ≠ length(b)");
		}

		for (int i = 0; i < num; i++) {
			p[i] -= with.p[i];
		}

		return *this;
	}

	Complexor Complexor::operator-() const //返回向量的反向同长向量
	{
		Complexor result(num, false, vertical);
		for (int i = 0; i < num; i++) {
			result.p[i] = -p[i];
		}
		return result;
	}

	Complexor& Complexor::operator=(const Complexor &src)
	{
		if (this->num != src.num) {
			delete[] p;
			this->num = src.num;
			p = new double[num];
		}

		for (int i = 0; i < num; i++) {
			p[i] = src.p[i];
		}
		this->vertical = src.vertical;
		return *this;
	}

	double& Complexor::operator[](int index) throw (out_of_range)
	{
		test_index(index);
		return p[index];
	}

	const double& Complexor::operator[](int index) const throw (out_of_range)
	{
		test_index(index);
		return p[index];
	}

	Complexor & Complexor::doTranspose()
	{
		vertical = !vertical;
		return *this;
	}

	Complexor TransposeOf(const Complexor &src)
	{
		Complexor result(src);
		return result.doTranspose();
	}

	Complexor operator*(const Matrix &M, const Complexor &V) throw (invalid_argument) //矩阵乘以列向量
	{
		if (V.vertical) {
			if (M.get_column() != V.num) {
				throw invalid_argument("column(M)!=num(V)");
			}
			const int &m = M.get_row();
			const int &n = V.num;
			Complexor result(m, true, true);
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++) {
					result.p[i] += M.get_element(i, j) * V.p[j];
				}
			}
			return result;
		} else {
			throw invalid_argument("V must be a vector in vertical"); //向量必须为列向量
		}
	}

	Complexor operator*(const Complexor &V, const Matrix &M) throw (invalid_argument) //行向量乘以矩阵
	{
		if (V.vertical) {
			throw invalid_argument("V must be a vector in horizontal");
		} else {
			if (V.num != M.get_row()) {
				throw invalid_argument("num(V)!=row(M)");
			}
			const int &m = V.num;
			const int &n = M.get_column();

			Complexor result(n, true, false);

			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					result.p[i] += V.p[j] * M.get_element(j, i);
				}
			}
			return result;
		}
	}

	double dot_product(const Complexor &a, const Complexor &b) throw (invalid_argument) //向量点积
	{
		if (a.num != b.num) {
			throw invalid_argument("num(a)!=num(b)");
		}
		const int &num = a.num;

		double result = 0.0;
		for (int i = 0; i < num; i++) {
			result += a.p[i] * b.p[i];
		}
		return result;
	}

	Matrix operator*(const Complexor &a, const Complexor &b) throw (invalid_argument) //向量乘以向量, 返回矩阵
	{
		if (a.vertical == true && b.vertical == false) {
			const int &m = a.num;
			const int &n = b.num;

			Matrix result(m, n, false);
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++) {
					result.get_element(i, j) = a.p[i] * b.p[j];
				}
			}
			return result;
		} else {
			if (a.num != b.num) {
				throw invalid_argument("num(a)!=num(b)");
			}
			Matrix result(1, 1, false);
			result.get_element(0, 0) = dot_product(a, b);
			return result;
		}
	}

	Complexor operator*(const int &k, const Complexor &b) //数k乘以向量
	{
		Complexor result(b);
		for (int i = 0; i < b.num; i++) {
			result.p[i] *= k;
		}
		return result;
	}

	Complexor operator*(const Complexor &b, const int &k) //向量乘以数k
	{
		Complexor result(b);
		for (int i = 0; i < b.num; i++) {
			result.p[i] *= k;
		}
		return result;
	}

	double abs(const Complexor &src) //向量的模
	{
		double sum = 0.0;
		for (int i = 0; i < src.num; i++) {
			sum += src.p[i] * src.p[i];
		}
		return sqrt(sum);
	}

//void print_array_to_file(const Complexor &src, string separator, string file_name, bool if_output_number) throw (invalid_argument)
//{
//	print_array_to_file(src.p, src.num, separator, file_name, if_output_number);
//}

	double operator^(const Complexor &a, const Complexor &b) throw (invalid_argument) //向量夹角
	{
		return acos(dot_product(a, b) / abs(a) / abs(b));
	}

	Complexor eqution(Matrix m) throw (invalid_argument)
	{
		const int &row = m.get_row();
		const int &column = m.get_column() - 1;
		if (row != column) {
			throw invalid_argument("不合法的增广矩阵");
		}
		const int &n = row;

		for (int k = 0; k < n - 1; k++) {

			double max_ele = 0;
			int i1 = 0;
			int j1 = 0;

			for (int i = k; i < n; i++) {
				for (int j = k; j < n; j++) {
					double ele = m.get_element(i, j);
					if (fabs(ele) > fabs(max_ele)) {
						max_ele = ele;
						i1 = i;
						j1 = j;
					}
				}
			}

			if (max_ele == 0) {
				throw invalid_argument("不合法的增广矩阵");
			}
			m.switch_rows(k, i1);
			m.switch_columns(k, j1);

			for (int j = k + 1; j <= n; j++) {
				//m[k][j] /= m[k][k];
				m.get_element(k, j) /= m.get_element(k, k);
			}

			for (int i = k + 1; i < n; i++) {
				for (int j = k + 1; j <= n; j++) {
					m[i][j] -= m[i][k] * m[k][j];
				}
			}
		}

		Complexor x(n, false, true);
		x[n - 1] = m[n - 1][n] / m[n - 1][n - 1];
		for (int i = n - 2; i >= 0; i--) {
			double sum = 0;
			for (int j = i + 1; j < n; j++) {
				sum += m[i][j] * x[j];
			}
			x[i] = m[i][n] - sum;
		}

		return x;

	}
} /* namespace complexor */
