#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <fstream>
#include <cmath>

#include "../array_2d.hpp"

namespace matrix
{
	namespace
	{
		using namespace std;
	}
	using namespace array_2d;

	enum Frame
	{
		Fr_RtMatrix, Fr_RdMatrix, Fr_Det, Fr_double, Fr_Null
	};

	static const string Corner_RtMatrix[] = { "��", "��", "��", "��", "��" };
	static const string Corner_RdMatrix[] = { "�q", "�r", "�t", "�s", "��" };
	static const string Corner_Det[] = { " ", " ", " ", " ", "��" };
	static const string Corner_double[] = { " ", " ", " ", " ", "�U" };

	class Matrix: public Array_2d<double>
	{
		public:
			Matrix();
//			Matrix(const int row, const int column, bool if_set0 = true);
			Matrix(const int row, const int column);
			Matrix(const int row, const int column, const double &val);
			Matrix(const int row, const int column, bool para, double (*function)());
			Matrix(const int row, const int column, bool para, double (*function)(int, int));

			template <class T> Matrix(const T * const src, const int row, const int column); //���ö�ά������й���
			Matrix(const double arr[], int len, bool in_a_row = true); //����һά������й���

#if __cplusplus >= 201103L //C++0x
			Matrix(initializer_list<initializer_list<double>> src); //���ö�ά��ʼ���б���й���
			Matrix(initializer_list<double> src); //����һά��ʼ���б���й���

			Matrix(Matrix &&src); //ת�ƹ��캯��
#endif //C++0x

			Matrix(const Matrix &src); //�������캯��

			virtual ~Matrix();

			friend const Matrix eye(int n); //����һ����λ����

			virtual void print(Frame frame = Fr_RtMatrix, bool print_corner = true, ostream &output = cout) const;
			void save(const string &file_name) const throw (runtime_error);
			friend Matrix load_from(const string &file_name);

			void switch_rows(const int row1, const int row2) throw (out_of_range);
			void switch_columns(const int column1, const int column2) throw (out_of_range);
			void k_multiply_a_row(const double k, const int row_dest) throw (out_of_range);
			void k_multiply_a_row_plus_to_another(const double k, const int row_from, const int row_dest) throw (out_of_range);
			void k_multiply_a_column(const double k, const int column_dest) throw (out_of_range);
			void k_multiply_a_column_plus_to_another(const double k, const int column_from, const int column_dest) throw (out_of_range);

			void do_optimize_rows() throw (invalid_argument); //�Ա���������Ż�

			double Det() const throw (invalid_argument);
			Matrix Adjugate_matrix() const throw (invalid_argument); //���ر�����İ������
			Matrix Inverse_matrix() const throw (invalid_argument); //���ر�����������,������󲻴���ʱ�׳��쳣

			//���������
			friend const Matrix operator+(const Matrix &A, const Matrix &B) throw (invalid_argument);
			friend const Matrix operator-(const Matrix &A, const Matrix &B) throw (invalid_argument);
			friend const Matrix operator*(const double k, const Matrix &A); //��k�˾���
			friend const Matrix operator*(const Matrix &A, const double k); //�������k
			friend const Matrix operator*(const Matrix &A, const Matrix &B) throw (invalid_argument); //����˾���
			friend const Matrix fma(const Matrix &A, const Matrix &B, const Matrix &C) throw (invalid_argument); //return the result of A*B+C , but much faster
			friend const Matrix dot_product(const Matrix &A, const Matrix &B) throw (invalid_argument); //�����˾���
			friend const Matrix operator^(const Matrix &A, const int n) throw (invalid_argument); //�������

			friend const Matrix operator&&(const Matrix &A, const Matrix &B) throw (invalid_argument); //������������ֱ��������
			friend const Matrix operator||(const Matrix &A, const Matrix &B) throw (invalid_argument); //����������ˮƽ��������

			friend void operator<<=(Matrix &tar, Matrix &src); //������src���ʲ�ת�Ƹ�tar, src��Ϊ��ԭ��ͬ����С���������
			Matrix& operator=(const Matrix &src);

			template <class T> friend Matrix Cat(const T &a);

#if __cplusplus >= 201103L //C++0x
			const Matrix& operator=(Matrix &&src);
#endif //C++0x

			//����
			friend const Matrix pow(const Matrix &A, const int n) throw (invalid_argument);
			friend double tr(const Matrix &src) throw (invalid_argument); //���ط���ļ�
			friend const Matrix TransposeOf(const Matrix &A); //�������A��ת�þ���
			void doTranspose()
			{
				this->operator=(TransposeOf(*this));
			}
			friend const Matrix CofactorOf(const Matrix &A, const int x, const int y) throw (out_of_range); //�������A������ʽA(x,y)
			void do_Cofactor(const int row_tar, const int column_tar) throw (out_of_range); //����һ������ȥrow_tar �к� column_tar �к�ľ���
			friend bool Matcmp(const Matrix &A, const Matrix &B, double eps);

			virtual void test_row(const int row_test) const throw (out_of_range);
			virtual void test_column(const int column_test) const throw (out_of_range);
			void test_square() const throw (invalid_argument);

			friend const Matrix conv2(const Matrix &core, const Matrix &B, int size = 0); //������
	};

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

			Matrix result(row_total, column_total);
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

	Matrix load_from(const string &file_name);

//Ӧ�ò���

	const Matrix rotate_X(double sigma);
	const Matrix rotate_Y(double sigma);
	const Matrix rotate_Z(double sigma);

	void rotate_X(double sigma, const double& x0, double& y0, double& z0);
	void rotate_Y(double sigma, double& x0, const double& y0, double& z0);
	void rotate_Z(double sigma, double& x0, double& y0, const double& z0);

	template <class T>
	Matrix::Matrix(const T * const src, const int row, const int column) //���ö�ά������й���
	{
		if (row > 0 && column > 0) {
			this->row = row;
			this->column = column;

			const size_t size_of_a_row = column * sizeof(double); //��һ��Ϊ�ӿ��ٶȶ�����

			p = new double*[row]; //������
			for (int i = 0; i < row; i++) {
				p[i] = new double[column]; //������
				memcpy(p[i], src + i, size_of_a_row);
			}
		} else {
			this->row = 0;
			this->column = 0;
			this->p = NULL;
		}
	}

} /* namespace matrix */

#endif	/* End _MATRIX_H_ */
