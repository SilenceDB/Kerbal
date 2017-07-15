#include <algorithm>

#include "Matrix.h"
#include "..\String_serve.h"
//#pragma message(__DATE__ "  " __TIME__"  ���ڱ���"__FILE__)

#if __cplusplus < 201103L //C++0x
# pragma message("Matrix ʹ���� C++ 11 ������, ��� C++ 11 ѡ���Ա�ʹ����Щ������")
#else
#include <initializer_list>
#endif //C++0x

using namespace std;

Matrix::Matrix()
{
	row = 0;
	column = 0;
	this->p = NULL;
}

Matrix::Matrix(const int row, const int column, bool if_set0) :
		Array_2d(row, column, if_set0)
{
	//cout<<this<<endl;
}

Matrix::Matrix(const int row, const int column, const double rand_min, const double rand_max)
{ //����һ���������
	if (row > 0 && column > 0) {
		this->row = row;
		this->column = column;

		p = new double*[row]; //������
		for (int i = 0; i < row; i++) {
			double *p_to_first = p[i] = new double[column]; //������
			for (int j = 0; j < column; j++) {
				p_to_first[j] = rand_between(rand_min, rand_max);
			}
		}
	} else {
		this->row = 0;
		this->column = 0;
		this->p = NULL;
	}
}

//Matrix::Matrix(const int row, const int column, int argc, ...) :
//		Array_2d(row, column, false)
//{
//	//���ÿɱ��������й���
//
//	//if(argc>row*column){
//	//	argc
//	//}
//	//cout<<this<<endl;
//	va_list arg_ptr;	//ָ�������ָ��
//	va_start(arg_ptr, argc);
//
//	for (int i = 0; i < row; i++) {
//		for (int j = 0; j < column; j++) {
//			p[i][j] = va_arg(arg_ptr, double);
//		}
//	}
//
//	va_end(arg_ptr);
//}

Matrix::Matrix(double arr[], int len, bool in_a_row)
{ //����һά������й���
	if (len > 0) {
		if (in_a_row) {
			this->row = 1;
			this->column = len;

			p = new double*[1];
			memcpy(p[0] = new double[column], arr, column * sizeof(double));
		} else {
			this->row = len;
			this->column = 1;

			p = new double*[row];
			for (int i = 0; i < row; i++) {
				p[i] = new double[1]; //������
				p[i][0] = arr[i];
			}
		}
	} else {
		this->row = 0;
		this->column = 0;
		this->p = NULL;
	}
}

#if __cplusplus < 201103L //C++0x
//# pragma message("Matrix Ϊ C++ 11 ׼����������: ���ó�ʼ���б���й���")
#else
Matrix::Matrix(initializer_list<initializer_list<double>> src)
{ //���ö�ά��ʼ���б���й���
  //ɨ������������
	unsigned int tmp = 0;
	for (auto j : src) {
		if (j.size() > tmp) {
			tmp = j.size();
		}
	}

	const int row_pre = src.size(); //���ն��µ�����
	const int column_pre = tmp; //���ն��µ�����

	if (row_pre > 0 && column_pre > 0) {
		this->row = row_pre;
		this->column = column_pre;

		//��̬����һ����pΪ�׵�ַ�ġ�row * column�Ķ�ά����
		p = new double*[row]; //������
		auto begin_to_src = src.begin();
		for (int i = 0; i < row; i++) {
			double *p_to_first = p[i] = new double[column];
			const initializer_list<double> &list_row = *(begin_to_src + i);
			auto begin_to_list_row = list_row.begin();
			for (unsigned int j = 0; j < list_row.size(); j++) {
				p_to_first[j] = *(begin_to_list_row + j);
			}
		}
	} else {
		this->row = 0;
		this->column = 0;
		this->p = NULL;
	}
}

Matrix::Matrix(initializer_list<double> src)
{ //����һά��ʼ���б���й���
	const int column_pre = src.size(); //���ն��µ�����

	if (column_pre > 0) {
		this->row = 1;
		this->column = column_pre;

		//��̬����һ����pΪ�׵�ַ�ġ�1 * column�Ķ�ά����
		p = new double*[1]; //������
		double *p_to_first = p[0] = new double[column];
		for (int i = 0; i < column; i++) {
			p_to_first[i] = *(src.begin() + i);
		}

	} else {
		this->row = 0;
		this->column = 0;
		this->p = NULL;
	}
}

Matrix::Matrix(Matrix &&src)
{ //ת�ƹ��캯��
	row = src.row;
	column = src.column;
	p = src.p;

	src.row = 0;
	src.column = 0;
	src.p = NULL;
}

#endif

Matrix::Matrix(const Matrix &src)
{
	//�������캯��
	//cout<<this<<" cpy= "<<&src<<endl;
	cout << "�������캯��" << endl;
	if (src.row > 0 && src.column > 0) {
		this->row = src.row;
		this->column = src.column;

		const size_t size_of_a_row = column * sizeof(double); //��һ��Ϊ�ӿ��ٶȶ�����

		p = new double*[row]; //������
		for (int i = 0; i < row; i++) {
			memcpy(p[i] = new double[column], src.p[i], size_of_a_row);
		}
	} else {
		this->row = 0;
		this->column = 0;
		this->p = NULL;
	}
}

Matrix::~Matrix()
{
	//�黹һ��row�еĶ�ά����
//	for (int i = 0; i < row; i++)
//		delete[] p[i];
//	delete[] p;
//	p = NULL;
}

Matrix Matrix::call(double (*__pf)(double)) const
{
	Matrix result(row, column, false);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			result[i][j] = __pf(p[i][j]);
		}
	}
	return result;
}

void Matrix::print(Frame frame, bool print_corner, ostream &output) const
{
	//Frame frame Ĭ��= Fr_RtMatrix, bool print_corner Ĭ��= true, ostream &output = output
	int i, j;
	string *corner = NULL;
	switch (frame) {
		case Fr_RtMatrix:
			Array_2d<double>::print(true, print_corner, output);
			return;
		case Fr_RdMatrix:
			corner = Corner_RdMatrix;
			break;
		case Fr_Det:
			corner = Corner_Det;
			break;
		case Fr_double:
			corner = Corner_double;
			break;
		case Fr_Null:
			Array_2d<double>::print(false, false, output);
			return;
	}

	output << corner[0];
	for (j = 0; j < column; j++) {
		output << "  " << setw(12) << " ";
	}
	output << " " << corner[1] << endl;

	for (i = 0; i < row; i++) {
		output << corner[4];

		for (j = 0; j < column; j++) {
			output << "  " << setw(12) << p[i][j];
		}
		output << " " << corner[4] << endl;
	}

	output << corner[2];
	for (j = 0; j < column; j++) {
		output << "  " << setw(12) << " ";
	}
	output << " " << corner[3];
	if (print_corner) {
		output << " " << row << " �� " << column;
	}
	output << endl;
}

void Matrix::switch_rows(const int row1, const int row2) throw (out_of_range)
{
	//�������������

	this->test_row(row1);
	this->test_row(row2);

//	void *temp;
//	const size_t size_of_a_row = column * sizeof(Type); //��һ��Ϊ�ӿ��ٶȶ�����
//	temp = malloc(size_of_a_row);
//	memcpy(temp, p[row1], size_of_a_row);
//	memcpy(p[row1], p[row2], size_of_a_row);
//	memcpy(p[row2], temp, size_of_a_row);
//	free(temp);
	swap(p[row1], p[row2]);
}

void Matrix::k_multiply_a_row(const double k, const int row_dest) throw (out_of_range)
{
	test_row(row_dest);

	for (int i = 0; i < column; i++) {
		p[row_dest][i] *= k;
	}
}

void Matrix::k_multiply_a_row_plus_to_another(const double k, const int row_from, const int row_dest) throw (out_of_range)
{
	test_row(row_from);
	test_row(row_dest);

	if (k == 0.0) {
		return;
	}

	for (int i = 0; i < column; i++) {
		p[row_dest][i] += k * p[row_from][i];
	}
}

void Matrix::optimize_rows() throw (invalid_argument)
{
	//������ʽ����н����Ż�
	test_square();
	bool k = false; //�Ƿ�ȡ�෴��
	const int &n = row;
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < n - i; j++) {
			//bool condition1 = p[j][0] != 0 && p[j + 1][0] == 0;
			//bool condition2 = p[j][0] != 0 && fabs(p[j][0]) < fabs(p[j + 1][0]);
			if (p[j][0] != 0 && p[j + 1][0] == 0) {
				swap(p[j], p[j + 1]);
				k = !k;
			} else {
				if (p[j][0] != 0 && fabs(p[j][0]) < fabs(p[j + 1][0])) {
					swap(p[j], p[j + 1]);
					k = !k;
				}
			}
		}
	}
	for (int i = 0; i < n - 1; i++) {
		if (p[i][0] != 0.0) {
			double ra = p[i][0] / p[n - 1][0];
			for (int j = 0; j < n; j++) { //��ѭ��
				p[i][j] -= ra * p[n - 1][j];
			}
		}
	}

	if (k) { //k == true
		for (int j = 0; j < n; j++) { //��ѭ��
			p[j][0] = -p[j][0];
		}
	}
}

Matrix optimize_rows(Matrix a) throw (invalid_argument)
{
	a.test_square();
	const int &n = a.row;
	bool k = false; //�Ƿ�ȡ�෴��
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < n - i; j++) {
			double * &p1 = a.p[j];
			double * &p2 = a.p[j + 1];
			if (p2[0] != 0) {
				if (p1[0] == 0 || fabs(p1[0]) < fabs(p2[0])) {
					swap(p1, p2);
					k = !k;
				}
			}
		}
	}

	for (int i = 0; i < n - 1; i++) {
		if (a.p[i][0] != 0.0) {
			double ra = a.p[i][0] / a.p[n - 1][0];
			for (int j = 0; j < n; j++) { //��ѭ��
				a.p[i][j] -= ra * a.p[n - 1][j];
			}
		}
	}

	if (k) { //k == true
		for (int j = 0; j < n; j++) { //��ѭ��
			double *p_to_first = a.p[j];
			p_to_first[0] = -p_to_first[0];
		}
	}

	return a;
}

void Matrix::switch_columns(const int column1, const int column2) throw (out_of_range)
{
	this->test_column(column1);
	this->test_column(column2);

	for (int i = 0; i < row; i++) {
		swap(p[i][column1], p[i][column2]);
	}
}

Matrix Matrix::Cofactor(const int row_tar, const int column_tar) const throw (out_of_range)
{
	//����һ������ȥrow_tar �к� column_tar �к�ľ���

	this->test_row(row_tar);
	this->test_column(column_tar);

	Matrix result(row - 1, column - 1, false);

	const size_t size_of_a_row_of_a_left = column_tar * sizeof(double); //��һ��Ϊ�ӿ��ٶȶ�����
	const size_t size_of_a_row_of_a_right = (column - 1 - column_tar) * sizeof(double); //��һ��Ϊ�ӿ��ٶȶ�����
	for (int i = 0; i < row_tar; i++) {
		memcpy(result.p[i], p[i], size_of_a_row_of_a_left);
		memcpy(result.p[i] + column_tar, p[i] + column_tar + 1, size_of_a_row_of_a_right);
	}
	for (int i = row_tar + 1; i < row; i++) {
		memcpy(result.p[i - 1], p[i], size_of_a_row_of_a_left);
		memcpy(result.p[i - 1] + column_tar, p[i] + column_tar + 1, size_of_a_row_of_a_right);
	}
	return result;
}

double Matrix::Det() const throw (invalid_argument)
{
	this->test_square();

	const int &n = row;
	switch (n) {
		case 1:
			return p[0][0];
		case 2:
			return p[0][0] * p[1][1] - p[0][1] * p[1][0];
		case 3:
			return p[0][0] * (p[1][1] * p[2][2] - p[1][2] * p[2][1]) - p[0][1] * (p[1][0] * p[2][2] - p[1][2] * p[2][0]) + p[0][2] * (p[1][0] * p[2][1] - p[1][1] * p[2][0]);
	}

	double sum = 0.0;
	double det;

	for (register int i = 0; i < n; i++) {
		if (p[i][0] != 0.0) { //p[0][i]!=0
			Matrix daishu(Cofactor(i, 0));

			if (n - 1 >= 4) {
				//�����������ʽ��4�׼�����,��������Ż�
				daishu.optimize_rows();
				//daishu = optimize_rows(daishu);
			}

			det = daishu.Det();
			if (i % 2) {
				//iΪ����
				sum -= p[i][0] * det;
			} else {
				//iΪż��
				sum += p[i][0] * det;
			}
		}
	}
	return sum;
}

Matrix Matrix::Adjugate_matrix() const throw (invalid_argument)
{
	//���ر�����İ������

	this->test_square();
	Matrix result(row, column, false);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			if ((i + j) % 2) {
				//i+jΪ����
				result.p[j][i] = -this->Cofactor(i, j).Det();
			} else {
				//i+jΪż��
				result.p[j][i] = this->Cofactor(i, j).Det();
			}
		}
	}
	return result;
}

Matrix Matrix::Inverse_matrix() const throw (invalid_argument)
{
	//���ر�����������
	this->test_square();

	double D = this->Det();
	if (D == 0.0) {
		throw invalid_argument("A does not have an inverse matrix");
	}
	Matrix result(this->Adjugate_matrix());
	const double k = 1.0 / D;
	return k * result;
}

//���������
Matrix operator+(const Matrix &A, const Matrix &B) throw (invalid_argument)
{
	int i, j;

	//���A,B�Ƿ�ͬ����С
	if (A.row != B.row) {
		throw invalid_argument("error: row(A) �� row(B)");
	}
	if (A.column != B.column) {
		throw invalid_argument("error: column(A) �� column(B)");
	}
	const int &row = A.row;
	const int &column = A.column;

	Matrix result(row, column, false);

	for (i = 0; i < row; i++) {
		for (j = 0; j < column; j++) {
			result.p[i][j] = A.p[i][j] + B.p[i][j];
		}
	}

	return result;
}

Matrix operator-(const Matrix &A, const Matrix &B) throw (invalid_argument)
{
	int i, j;

	//���A,B�Ƿ�ͬ����С
	if (A.row != B.row) {
		throw invalid_argument("error: row(A) �� row(B)");
	}
	if (A.column != B.column) {
		throw invalid_argument("error: column(A) �� column(B)");
	}
	const int &row = A.row;
	const int &column = A.column;

	Matrix result(row, column, false);

	for (i = 0; i < row; i++) {
		for (j = 0; j < column; j++) {
			result.p[i][j] = A.p[i][j] - B.p[i][j];
		}
	}

	return result;
}

Matrix operator*(const double k, const Matrix &A)
{
	//��k�˾���
	if (k == 1) {
		return A;
	}
	Matrix result(A);
	int i, j;
	for (i = 0; i < A.row; i++) {
		for (j = 0; j < A.column; j++) {
			result.p[i][j] *= k;
		}
	}
	return result;
}

Matrix operator*(const Matrix &A, const Matrix &B) throw (invalid_argument)
{
	//����˾���

	//���A�������Ƿ����B������
	if (A.column != B.row) {
		throw invalid_argument("error: column(A) �� row(B)");
	}
	const int &row = A.row;
	const int &column = B.column;

	Matrix result(row, column, false);

	int i, j, k;
	for (i = 0; i < row; i++) {
		for (j = 0; j < column; j++) {
			result.p[i][j] = 0.0;
			for (k = 0; k < A.column; k++) {
				result.p[i][j] += A.p[i][k] * B.p[k][j];
			}
		}
	}
	return result;
}

Matrix dot_product(const Matrix &A, const Matrix &B) throw (invalid_argument)
{
	int i, j;

	//���A,B�Ƿ�ͬ����С
	if (A.row == 1 && A.row == 1) {
		return A.p[0][0] * B;
	} else if (B.row == 1 && B.row == 1) {
		return B.p[0][0] * A;
	} else if (A.row != B.row) {
		throw invalid_argument("error: row(A) �� row(B)");
	} else if (A.column != B.column) {
		throw invalid_argument("error: column(A) �� column(B)");
	}
	const int &row = A.row;
	const int &column = A.column;

	Matrix result(row, column, false);

	for (i = 0; i < row; i++) {
		for (j = 0; j < column; j++) {
			result.p[i][j] = A.p[i][j] * B.p[i][j];
		}
	}

	return result;
}

Matrix operator^(const Matrix &A, const int n) throw (invalid_argument)
{
	A.test_square();
	if (n <= 0) {
		throw invalid_argument("unreasonable n:" + to_string(n));
	}
//	Matrix tmp(A);
//	for (int i = 1; i < n; i++) {
//		tmp = tmp * A;
//	}
//	return tmp;

	if (n == 1) {
		return A;
	} else if (n == 2) {
		return A * A;
	} else {
		Matrix tmp(A ^ (n / 2));
		tmp = tmp * tmp;
		if (n % 2) {
			//ָ��Ϊ����
			tmp = tmp * A;
		}
		return tmp;
	}
}

Matrix operator&&(const Matrix &A, const Matrix &B) throw (invalid_argument)
{
	//������������ֱ��������

	if (A.column != B.column) {
		throw invalid_argument("�����ľ����������һ��");
	}

	const int row_total = A.row + B.row;
	const int &column_total = A.column;

	Matrix result(row_total, column_total, false);

	const size_t size_of_a_row = column_total * sizeof(double);
	for (int i = 0; i < A.row; i++) { //��ѭ��
		memcpy(result.p[i], A.p[i], size_of_a_row);
	}

	for (int i = 0; i < B.row; i++) { //��ѭ��
		memcpy(result.p[A.row + i], B.p[i], size_of_a_row);
	}

	return result;
}

Matrix operator||(const Matrix &A, const Matrix &B) throw (invalid_argument)
{
	//����������ˮƽ��������
	if (A.row != B.row) {
		throw invalid_argument("�����ľ����������һ��");
	}
	const int &row_total = A.row;
	const int column_total = A.column + B.column;

	Matrix result(row_total, column_total, false);

	const size_t size_of_a_row_of_a_left = A.column * sizeof(double);
	const size_t size_of_a_row_of_a_right = B.column * sizeof(double);
	for (int i = 0; i < row_total; i++) { //��ѭ��
		memcpy(result.p[i], A.p[i], size_of_a_row_of_a_left);
		memcpy(result.p[i] + A.column, B.p[i], size_of_a_row_of_a_right);
	}

	return result;
}

void operator<<=(Matrix &tar, Matrix &src)
{ //������src���ʲ�ת�Ƹ�tar
	tar.clear();
	tar.row = src.row;
	tar.column = src.column;
	tar.p = src.p;
	src.p = NULL;
	src.row = 0;
	src.column = 0;
}

const Matrix& Matrix::operator=(const Matrix &src)
{
	//cout << this << " = " << &src << endl;
	if (row == src.row) {
		if (column == src.column) { //��,��������ԭ�����
			const size_t size_of_a_row = src.column * sizeof(double);
			for (int i = 0; i < src.row; i++) {
				memcpy(p[i], src.p[i], size_of_a_row);
			}
		} else { //������ԭ�����, ��������
			for (int i = 0; i < row; i++)
				delete[] p[i];
			const size_t size_of_a_row = src.column * sizeof(double);
			for (int i = 0; i < src.row; i++) {
				p[i] = new double[src.column]; //������
				memcpy(p[i], src.p[i], size_of_a_row);
			}
		}
	} else {
		for (int i = 0; i < row; i++)
			delete[] p[i];
		delete[] p;

		p = new double*[src.row]; //������
		const size_t size_of_a_row = src.column * sizeof(double);
		for (int i = 0; i < src.row; i++) {
			p[i] = new double[src.column]; //������
			memcpy(p[i], src.p[i], size_of_a_row);
		}

		this->row = src.row;
		this->column = src.column;
	}

	return *this;
}

bool Matrix::operator==(const Matrix &with) const
{
	if (row != with.row || column != with.column) {
		return false;
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			if (this->p[i][j] == with.p[i][j]) {
				return false;
			}
		}
	}
	return true;
}

bool Matrix::operator!=(const Matrix &with) const
{
	return !(this->operator ==(with));
}

Matrix pow(const Matrix &A, const int n)
{
	return A ^ n;
}

double tr(const Matrix &src) throw (invalid_argument) //���ط���ļ�
{
	src.test_square();
	double result = 0;
	for (int i = 0; i < src.row; i++) {
		result += src.p[i][i];
	}
	return result;
}

void Matrix::test_row(const int row_test) const throw (out_of_range)
{
	if (row_test < 0 || row_test >= this->row) {
		throw out_of_range("The " + to_string(this->row) + " �� " + to_string(this->column) + " Matrix doesn't have the no." + to_string(row_test) + " row!");
	}
}

void Matrix::test_column(const int column_test) const throw (out_of_range)
{
	if (column_test < 0 || column_test >= this->column) {
		throw out_of_range("The " + to_string(this->row) + " �� " + to_string(this->column) + " Matrix doesn't have the no." + to_string(column_test) + " column!");
	}
}

void Matrix::test_square() const throw (invalid_argument)
{
	if (row != column) {
		throw invalid_argument("A is not a square matrix");
	}
}

//����
bool Matcmp(const Matrix &A, const Matrix &B, double eps)
{
	for (int i = 0; i < A.row; i++) {
		for (int j = 0; j < A.column; j++) {
			if (fabs(A.p[i][j] - B.p[i][j]) > eps) {
				return false;
			}
		}
	}
	return true;
}

Matrix Transpose(const Matrix &A)
{
	//���ؾ���A��ת�þ���
	Matrix result(A.column, A.row, false);
	for (int i = 0; i < A.column; i++) {
		for (int j = 0; j < A.row; j++) {
			result.p[i][j] = A.p[j][i];
		}
	}
	return result;
}

Matrix Cofactor(const Matrix &A, const int x, const int y) throw (out_of_range)
{
	//���췽��A������ʽA(x,y)
	return A.Cofactor(x, y);
}

//Ӧ�ò���

Matrix rotate_X(double sigma)
{
	double cosine = cos(sigma);
	double sine = sin(sigma);
	double a[3][3] = { 1, 0, 0, 0, cosine, -sine, 0, sine, cosine };
	return Matrix(a, 3, 3);
}

Matrix rotate_Y(double sigma)
{
	double cosine = cos(sigma);
	double sine = sin(sigma);
	double a[3][3] = { cosine, 0, sine, 0, 1, 0, -sine, 0, cosine };
	return Matrix(a, 3, 3);
}

Matrix rotate_Z(double sigma)
{
	double cosine = cos(sigma);
	double sine = sin(sigma);
	double a[3][3] = { cosine, -sine, 0, sine, cosine, 0, 0, 0, 1 };
	return Matrix(a, 3, 3);
}

void rotate_X(double sigma, const double& x0, double& y0, double& z0)
{
	double cosine = cos(sigma);
	double sine = sin(sigma);
	double y1 = y0 * cosine - z0 * sine;
	double z1 = y0 * sine + z0 * cosine;

	y0 = y1;
	z0 = z1;
}

void rotate_Y(double sigma, double& x0, const double& y0, double& z0)
{
	double cosine = cos(sigma);
	double sine = sin(sigma);
	double x1 = x0 * cosine + z0 * sine;
	double z1 = -x0 * sine + z0 * cosine;

	x0 = x1;
	z0 = z1;
}

void rotate_Z(double sigma, double& x0, double& y0, const double& z0)
{
	double cosine = cos(sigma);
	double sine = sin(sigma);
	double x1 = x0 * cosine - y0 * sine;
	double y1 = x0 * sine + y0 * cosine;

	x0 = x1;
	y0 = y1;
}

/*void Matrix::print_to_file(char file_name[],bool if_output_frame) const
 {


 // ����cout��������ָ��
 streambuf* coutBuf = cout.rdbuf();

 ofstream of(file_name);
 // ��ȡ�ļ�out.txt��������ָ��
 streambuf* fileBuf = of.rdbuf();

 // ����cout��������ָ��Ϊout.txt����������ָ��
 cout.rdbuf(fileBuf);

 this->print();

 of.flush();
 of.close();

 // �ָ�coutԭ������������ָ��
 cout.rdbuf(coutBuf);
 //cout << "Write Personal Information over..." << endl;



 //	int i,j;
 //	string separator="\t";
 //
 //
 //	cout<<"��";
 //	for(j=0; j<=column-1; j++) {
 //		cout<<"\t";
 //	}
 //	cout<<" ��"<<endl;
 //
 //
 //	for(i=0; i<=row-1; i++) {
 //		//cout<<"\t";
 //		for(j=0; j<=column-1; j++) {
 //			if(j==0) {
 //				cout<<"�� ";
 //			} else {
 //				cout<<"   ";
 //			}
 //			cout<<p[i][j];
 //			if(j!=column-1) {
 //				cout<<" "<<separator;
 //			}
 //		}
 //		cout<<"\t ��"<<endl;
 //	}
 //
 //
 //	cout<<"��";
 //	for(j=0; j<=column-1; j++) {
 //		cout<<"\t";
 //	}
 //	cout<<" ��"<<endl;

 }*/

//��������ʽ���㹦�ܵĴ���
/*	unsigned long k;

 #define N 20
 int a[N][N];
 for(int i=0; i<=N-1; i++) {
 for(int j=0; j<=N-1; j++) {
 a[i][j]=(int)rand_between(-10,10);
 }
 }

 Matrix B(a);
 B.print();
 Matrix C=1.5*B;
 cout<<C.get_element(2,2)<<endl;
 C.print();

 k=GetTickCount();
 printf("%.5f\n",B.Det());
 cout<<GetTickCount()-k<<"ms"<<endl;*/
