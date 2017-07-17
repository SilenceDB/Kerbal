#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <stdarg.h>

#include "basic_math.h"
#include "..\array_serve.h"
#include "..\array_2d.h"
#include "randnum.h"

//#pragma message(__DATE__ "  " __TIME__"  ���ڱ���"__FILE__)

using namespace std;

enum Frame
{
	Fr_RtMatrix, Fr_RdMatrix, Fr_Det, Fr_double, Fr_Null
};

static string Corner_RtMatrix[] = { "��", "��", "��", "��", "��" };
static string Corner_RdMatrix[] = { "�q", "�r", "�t", "�s", "��" };
static string Corner_Det[] = { " ", " ", " ", " ", "��" };
static string Corner_double[] = { " ", " ", " ", " ", "�U" };

class Matrix: public Array_2d<double>
{

	public:
		Matrix();
		Matrix(const int row, const int column, bool if_set0 = true);
		Matrix(const int row, const int column, const double rand_min, const double rand_max); //����һ���������
//		Matrix(const int row, const int column, int argc, ...); //���ÿɱ��������й���

		template <class T> Matrix(const T *src, const int row, const int column); //���ö�ά������й���
		Matrix(double arr[], int len, bool in_a_row = true); //����һά������й���

#if __cplusplus < 201103L //C++0x
//# pragma message("Matrix Ϊ C++ 11 ׼����������: ���ó�ʼ���б���й���")
#else
		Matrix(initializer_list<initializer_list<double>> src); //���ö�ά��ʼ���б���й���
		Matrix(initializer_list<double> src); //����һά��ʼ���б���й���

//		Matrix(Matrix &&src); //ת�ƹ��캯��
#endif

		Matrix(const Matrix &src); //�������캯��

		~Matrix();

		Matrix call(double (*__pf)(double)) const;

		void print(Frame frame = Fr_RtMatrix, bool print_corner = true, ostream &output = cout) const;
		//void print_to_file(char file_name[],bool if_output_frame) const;

		void switch_columns(const int column1, const int column2) throw (out_of_range);
		void k_multiply_a_row(const double k, const int row_dest) throw (out_of_range);
		void k_multiply_a_row_plus_to_another(const double k, const int row_from, const int row_dest) throw (out_of_range);
		void optimize_rows() throw (invalid_argument); //�Ա���������Ż�
		friend Matrix optimize_rows(Matrix a) throw (invalid_argument);
		void switch_rows(const int row1, const int row2) throw (out_of_range);
		Matrix Cofactor(const int row_tar, const int column_tar) const throw (out_of_range); //����һ������ȥrow_tar �к� column_tar �к�ľ���

		double Det() const throw (invalid_argument);
		Matrix Adjugate_matrix() const throw (invalid_argument); //���ر�����İ������
		Matrix Inverse_matrix() const throw (invalid_argument); //���ر�����������,������󲻴���ʱ�׳��쳣

		//���������
		friend Matrix operator+(const Matrix &A, const Matrix &B) throw (invalid_argument);
		friend Matrix operator-(const Matrix &A, const Matrix &B) throw (invalid_argument);
		friend Matrix operator*(const double k, const Matrix &A); //��k�˾���
		friend Matrix operator*(const Matrix &A, const double k); //�������k
		friend Matrix operator*(const Matrix &A, const Matrix &B) throw (invalid_argument); //����˾���
		friend Matrix dot_product(const Matrix &A, const Matrix &B) throw (invalid_argument); //�����˾���
		friend Matrix operator^(const Matrix &A, const int n) throw (invalid_argument); //�������

		friend Matrix operator&&(const Matrix &A, const Matrix &B) throw (invalid_argument); //������������ֱ��������
		friend Matrix operator||(const Matrix &A, const Matrix &B) throw (invalid_argument); //����������ˮƽ��������

		friend void operator<<=(Matrix &tar, Matrix &src); //������src���ʲ�ת�Ƹ�tar
		const Matrix& operator=(const Matrix &src);

		template <class T> friend Matrix Cat(const T &a);
//#if __cplusplus < 201103L //C++0x
////# pragma message("Matrix Ϊ C++ 11 ׼����������: ת�Ƹ�ֵ�����")
//#else
//		const Matrix& operator=(Matrix &&src);
//#endif

		bool operator==(const Matrix &with) const;
		bool operator!=(const Matrix &with) const;

		//����
		friend Matrix pow(const Matrix &A, const int n);
		friend double tr(const Matrix &src) throw (invalid_argument);		//���ط���ļ�
		friend Matrix Transpose(const Matrix &A);
		friend Matrix Cofactor(const Matrix &A, const int x, const int y) throw (out_of_range); //���췽��A������ʽA(x,y)
		friend bool Matcmp(const Matrix &A, const Matrix &B, double eps);
		friend inline void swap(Matrix &A, Matrix &B)
		{
			swap(A.row, B.row);
			swap(A.column, B.column);
			swap(A.p, B.p);
		}

		void test_row(const int row_test) const throw (out_of_range);
		void test_column(const int column_test) const throw (out_of_range);
		void test_square() const throw (invalid_argument);
};

template <class T>
Matrix::Matrix(const T *src, const int row, const int column) //���ö�ά������й���
{
	if (row > 0 && column > 0) {
		this->row = row;
		this->column = column;

		const size_t size_of_a_row = column * sizeof(double); //��һ��Ϊ�ӿ��ٶȶ�����

		p = new double*[row]; //������
		for (int i = 0; i < row; i++) {
			p[i] = new double[column]; //������
			memcpy(p[i], src + i * size_of_a_row, size_of_a_row);
		}
	} else {
		this->row = 0;
		this->column = 0;
		this->p = NULL;
	}
}

template <class T>
Matrix Cat(const T &a)
{
	if (array_dimension(a) == 1) {
		int row_total = a[0].row;
		int column_total = a[0].column;
		for (int i = 1; i < arraylen(a); i++) {
			if (a[i].row != row_total) {
				cerr << "�����ľ����������һ��" << endl;
				throw 0;
			} else {
				column_total += a[i].column;
			}
		}

		Matrix result(row_total, column_total, false);
		for (int i = 0, column_covered = 0; i < arraylen(a); i++) { //����ѭ��
			for (int j = 0; j < row_total; j++) { //��ѭ��
				for (int k = 0; k < a[i].get_column(); k++) { //һ�������ڵ���ѭ��
					result.p[j][column_covered + k] = a[i].p[j][k];
				}
			}
			column_covered += a[i].column;
		}
		return result;
	} else if (array_dimension(a) == 2) {
		return Matrix(1, 1);
	} else {
		throw 0;
	}
}

//Ӧ�ò���

Matrix rotate_X(double sigma);
Matrix rotate_Y(double sigma);
Matrix rotate_Z(double sigma);

void rotate_X(double sigma, const double& x0, double& y0, double& z0);
void rotate_Y(double sigma, double& x0, const double& y0, double& z0);
void rotate_Z(double sigma, double& x0, double& y0, const double& z0);

#endif	/* End _MATRIX_H_ */
