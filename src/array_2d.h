#ifndef _ARRAY_2D_H_
#define _ARRAY_2D_H_

#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <stdexcept>

#if __cplusplus < 201103L //C++0x
# pragma message("Array_2d ʹ���� C++ 11 ������, ��� C++ 11 ѡ���Ա�ʹ����Щ������")
#else
#include <initializer_list>
#endif //C++0x

#include "String_serve.h"

using namespace std;

template <class T>
inline int array_2d_row(const T &a) //���ؾ������
{
	return sizeof(a) / sizeof(a[0]);
}

template <class T>
inline int array_2d_column(const T &a) //���ؾ������
{
	return sizeof(a[0]) / siz0eof(a[0][0]);
}

template <class Type> class Array_2d;

template <class Type>
class safety  //���������ṩ�Զ�̬��ά����Array_2d����±�����İ�ȫ����
{

	protected:
		Array_2d<Type> *p_to_matrix;
		int row_want_to;
	public:
		safety(Array_2d<Type> *p_to_matrix, const int row_want_to)
		{
			this->p_to_matrix = p_to_matrix;
			this->row_want_to = row_want_to;
			//cout<<"safe:"<<this<<endl;
		}

		safety(const Array_2d<Type> * const p2, const int row)
		{
			this->p_to_matrix = (Array_2d<Type> *) p2;
			this->row_want_to = row;
			//cout<<"safe:"<<this<<endl;
		}

		~safety()
		{
			//cout<<"delete safe:"<<this<<endl;
		}

		bool is_const()
		{
			return false;
		}
		bool is_const() const
		{
			return true;
		}

		Type& operator[](int row) throw (out_of_range);
		const Type& operator[](int row) const throw (out_of_range);

		Type* begin()
		{
			return p_to_matrix->p[row_want_to];
		}

		Type* end()
		{
			return p_to_matrix->p[row_want_to] + p_to_matrix->column;
		}

		safety<Type> operator++(int)
		{
			safety<Type> tmp(*this);
			row_want_to++;
			return tmp;
		}

		friend bool operator<(const safety<Type> &a, const safety<Type> &b) throw (invalid_argument)
		{
			if (a.p_to_matrix == b.p_to_matrix) {
				return a.row_want_to < b.row_want_to;
			} else {
				throw invalid_argument("a and b is not point to same Array_2d");
			}
		}
};

template <class Type>
Type& safety<Type>::operator[](int column) throw (out_of_range)
{
	p_to_matrix->test_column(column);
	return p_to_matrix->p[row_want_to][column];
}

template <class Type>
const Type& safety<Type>::operator[](int column) const throw (out_of_range)
{
	p_to_matrix->test_column(column);
	return p_to_matrix->p[row_want_to][column];
}

enum Array_2d_input_info
{
	input_info_start, input_info_end
};

const Array_2d_input_info begin = input_info_start;
const Array_2d_input_info end = input_info_end;

template <class Type>
class Array_2d
{
	protected:
		int row;
		int column;
		Type **p = NULL;
		static int insert_times;

	public:
		friend class safety<Type> ;
		Array_2d()
		{
			row = 0;
			column = 0;
			this->p = NULL;
		}

		Array_2d(const int row, const int column, bool if_set0 = true);
//		Array_2d(const int row, const int column, int argc, ...);  //���ÿɱ��������й���

		template <class T>
		Array_2d(const T *src, const int row, const int column)
		{ //���ö�ά������й���
			if (row > 0 && column > 0) {
				this->row = row;
				this->column = column;

				//��̬����һ����pΪ�׵�ַ�ġ�row * column�Ķ�ά����
				p = new Type*[row]; //������
				for (int i = 0; i < row; i++) {
					p[i] = new Type[column]; //������
					for (int j = 0; j < column; j++) {
						p[i][j] = src[i][j];
					}
				}
			} else {
				this->row = 0;
				this->column = 0;
				this->p = NULL;
			}
		}

		Array_2d(Type arr[], int len, bool in_a_row = true); //����һά������й���

#if __cplusplus < 201103L //C++0x
//# pragma message("Array_2d Ϊ C++ 11 ׼����������: ���ó�ʼ���б���й���")
#else
		Array_2d(initializer_list<initializer_list<Type>> src); //���ö�ά��ʼ���б���й���
		Array_2d(initializer_list<Type> src); //����һά��ʼ���б���й���
#endif

		Array_2d(const Array_2d &src); //�������캯��

		virtual ~Array_2d();
		bool empty() const;
		void clear();

		int get_row() const;
		int get_column() const;
		bool is_const();
		bool is_const() const;

		const Type& get_element(int row, int column) const throw (out_of_range);

		void set_element(int row, int column, Type value) throw (out_of_range);
		template <class T> void set_element(const T *src, int row, int column);
		Array_2d<Type> call(Type (*__pf)(Type)) const;

		Array_2d<Type>& operator <<(const Type &value) throw (out_of_range); //����
		Array_2d<Type>& operator <<(const Array_2d_input_info &value);
		Array_2d<Type>& operator <<(const string & src) throw (out_of_range); //�ַ�������
		Array_2d<Type>& operator <<(ostream& (*__pf)(ostream&)); //֧��endl
		friend ostream& operator <<(ostream &output, Array_2d<Type> &src) //�������
		{
			src.print(true, true, output);
			return output;
		}
		void print(bool print_frame, bool print_corner, ostream& output) const;
		//void print_to_file(char file_name[],bool if_output_frame) const;

		safety<Type> operator[](int row) throw (out_of_range);
		const safety<Type> operator[](int row) const throw (out_of_range);

		size_t get_digit_size() const;
		void test_row(const int row_test) const throw (out_of_range);
		void test_column(const int column_test) const throw (out_of_range);

		bool operator==(const Array_2d<Type> &with) const;
		bool operator!=(const Array_2d<Type> &with) const;
//		static void memcpy(Type* Dst, Type* Src, size_t Size_of_src, bool deep);

//		friend void memcpy(Type* Dst, const Type* Src, size_t Size_of_src)
//		{
//			const int n = Size_of_src / sizeof(*Src);
//			for (int i = 0; i < n; i++) {
//				Dst[i] = Src[i];
//			}
//		}

		safety<Type> begin()
		{
			return safety<Type>(this, 0);
		}

		const safety<Type> begin() const
		{
			return safety<Type>(this, 0);
		}

		safety<Type> end()
		{
			return safety<Type>(this, row);
		}

		const safety<Type> end() const
		{
			return safety<Type>(this, row);
		}
};

template <class Type>
Array_2d<Type>::Array_2d(const int row, const int column, bool if_set0)
{
	//int row, int column, bool if_set0 Ĭ�� = true
	//��̬����һ����pΪ�׵�ַ�ġ�row * column�Ķ�ά����
	if (row > 0 && column > 0) {
		this->row = row;
		this->column = column;

		p = new Type*[row]; //������
		if (if_set0) {
			const size_t size_of_a_row = column * sizeof(Type); //��һ��Ϊ�ӿ��ٶȶ�����
			for (int i = 0; i < row; i++) {
				memset(p[i] = new Type[column], 0, size_of_a_row);
			}
		} else {
			for (int i = 0; i < row; i++) {
				p[i] = new Type[column]; //������
			}
		}
	} else {
		this->row = 0;
		this->column = 0;
		this->p = NULL;
	}
}

//template <class Type>
//Array_2d<Type>::Array_2d(const int row, const int column, int argc, ...)
//{
//	//��̬����һ����pΪ�׵�ַ�ġ�row * column�Ķ�ά����
//	if (row > 0 && column > 0) {
//		this->row = row;
//		this->column = column;
//
//		p = new Type*[row]; //������
//
////if(argc>row*column){
////	argc
////}
//		va_list arg_ptr; //ָ�������ָ��
//		va_start(arg_ptr, argc);
//
//		for (int i = 0; i < row; i++) {
//			p[i] = new Type[column]; //������
//			for (int j = 0; j < column; j++) {
//				p[i][j] = va_arg(arg_ptr, Type);
//			}
//		}
//		va_end(arg_ptr);
//	} else {
//		this->row = 0;
//		this->column = 0;
//		this->p = NULL;
//	}
//}

template <class Type>
Array_2d<Type>::Array_2d(Type arr[], int len, bool in_a_row)
{ //����һά������й���
	if (len > 0) {
		if (in_a_row) {
			this->row = 1;
			this->column = len;
			p = new Type*[1];
			p[0] = new Type[column]; //������

			for (int j = 0; j < column; j++) {
				p[0][j] = arr[j];
			}
		} else {
			this->row = len;
			this->column = 1;

			p = new Type*[row];
			for (int i = 0; i < row; i++) {
				p[i] = new Type[1]; //������
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
//# pragma message("Array_2d Ϊ C++ 11 ׼����������: ���ó�ʼ���б���й���")
#else
template <class Type>
Array_2d<Type>::Array_2d(initializer_list<initializer_list<Type>> src)
{ //���ö�ά��ʼ���б���й���
  //ɨ������������
	int tmp = 0;
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
		p = new Type*[row]; //������
		auto begin_to_src = src.begin();
		for (int i = 0; i < row; i++) {
			Type *p_to_first = p[i] = new Type[column];
			const initializer_list<Type> &list_row = *(begin_to_src + i);
			auto begin_to_list_row = list_row.begin();
			for (int j = 0; j < list_row.size(); j++) {
				p_to_first[j] = *(begin_to_list_row + j);
			}
		}
	} else {
		this->row = 0;
		this->column = 0;
		this->p = NULL;
	}
}

template <class Type>
Array_2d<Type>::Array_2d(initializer_list<Type> src)
{ //����һά��ʼ���б���й���
	const int column_pre = src.size(); //���ն��µ�����

	if (column_pre > 0) {
		this->row = 1;
		this->column = column_pre;

		//��̬����һ����pΪ�׵�ַ�ġ�1 * column�Ķ�ά����
		p = new Type*[1]; //������
		Type *p_to_first = p[0] = new Type[column];
		for (int i = 0; i < column; i++) {
			p_to_first[i] = *(src.begin() + i);
		}

	} else {
		this->row = 0;
		this->column = 0;
		this->p = NULL;
	}
}
#endif

template <class Type>
Array_2d<Type>::Array_2d(const Array_2d<Type> &src) //�������캯��
{
	if (src.row > 0 && src.column > 0) {
		this->row = src.row;
		this->column = src.column;

		p = new Type*[row]; //������
		for (int i = 0; i < row; i++) {
			p[i] = new Type[column]; //������
			for (int j = 0; j < column; j++) {
				p[i][j] = src.p[i][j];
			}
		}
	} else {
		this->row = 0;
		this->column = 0;
		this->p = NULL;
	}
}

template <class Type>
Array_2d<Type>::~Array_2d() // virtual
{
	//�黹һ��row�еĶ�ά����
	for (int i = 0; i < row; i++)
		delete[] p[i];
	delete[] p;
	p = NULL;
}

template <class Type>
bool Array_2d<Type>::empty() const
{
	if (row == 0 || column == 0) {
		return true;
	} else {
		return false;
	}
}

template <class Type>
void Array_2d<Type>::clear()
{
	//�黹һ��row�еĶ�ά����
	for (int i = 0; i < row; i++)
		delete[] p[i];
	delete[] p;
	p = NULL;
	row = 0;
	column = 0;
}

template <class Type>
int Array_2d<Type>::get_row() const
{
	return row;
}

template <class Type>
int Array_2d<Type>::get_column() const
{
	return column;
}

template <class Type>
bool Array_2d<Type>::is_const()
{
	return false;
}

template <class Type>
bool Array_2d<Type>::is_const() const
{
	return true;
}

template <class Type>
inline const Type& Array_2d<Type>::get_element(int row, int column) const throw (out_of_range)
{
	test_row(row);
	test_column(column);
	return p[row][column];
}

template <class Type>
safety<Type> Array_2d<Type>::operator[](int row) throw (out_of_range)
{
	test_row(row);
	return safety<Type>(this, row);
}

template <class Type>
const safety<Type> Array_2d<Type>::operator[](int row) const throw (out_of_range)
{
	test_row(row);
	return safety<Type>(this, row);
}

template <class Type>
inline void Array_2d<Type>::set_element(int row, int column, Type value) throw (out_of_range)
{
	test_row(row);
	test_column(column);
	p[row][column] = value;
}

template <class Type>
template <class T>
void Array_2d<Type>::set_element(const T *src, int row, int column) //ͨ�����鸳ֵ///�˺�������BUG
{
	this->clear();

	this->row = row;
	this->column = column;

	p = new Type*[row]; //������
	for (int i = 0; i < row; i++) {
		p[i] = new Type[column]; //������
		for (int j = 0; j < column; j++) {
			p[i][j] = src[i][j];
		}
	}
}

template <class Type>
Array_2d<Type> Array_2d<Type>::call(Type (*__pf)(Type)) const
{
	Array_2d<Type> result(row, column, false);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			result[i][j] = __pf(p[i][j]);
		}
	}
	return result;
}

//���ò������������̬��ά���鸳ֵ
template <class Type>
int Array_2d<Type>::insert_times = 0;

template <class Type>
Array_2d<Type>& Array_2d<Type>::operator <<(const Type &value) throw (out_of_range)
{
	static Array_2d<Type> *last_Arry = NULL;
	if (last_Arry != this) {
		last_Arry = this;
		insert_times = 0;
	} else if (insert_times >= row * column) {
		throw out_of_range("���Ը�[" + to_string(insert_times / column) + "][" + to_string(insert_times % column) + "]��ֵ" + to_string(value));
	}

	//p[insert_times / row][insert_times % row] = value;
	p[insert_times / column][insert_times % column] = value;

	insert_times++;
	return *this;
}

template <class Type>
Array_2d<Type>& Array_2d<Type>::operator <<(const Array_2d_input_info &value)
{
	switch (value) {
		case input_info_start:
			insert_times = 0;
			break;
		case input_info_end:
			insert_times = 0;
			break;
	}
	return *this;
}
//���ò������������̬��ά���鸳ֵ

template <class Type>
Array_2d<Type>& Array_2d<Type>::operator <<(const string & src) throw (out_of_range)
{
	static Array_2d<Type> *last_Arry = NULL;

	if (last_Arry != this) {
		last_Arry = this;
		insert_times = 0;
	}

	stringstream ss;
	ss << src;
	Type tmp;

	while (ss >> tmp) {
		if (insert_times >= row * column) {
			throw out_of_range("���Ը�[" + to_string(insert_times / column) + "][" + to_string(insert_times % column) + "]��ֵ");
		}
		//p[insert_times / row][insert_times % row] = tmp;
		p[insert_times / column][insert_times % column] = tmp;
		insert_times++;
	}
	return *this;
}

template <class Type>
Array_2d<Type>& Array_2d<Type>::operator <<(ostream& (*__pf)(ostream&))
{
	if (insert_times % column)
		insert_times = insert_times / column * column + column;
	return *this;
}

template <class Type>
void Array_2d<Type>::print(bool print_frame = true, bool print_corner = true, ostream &output = cout) const
{
	int i, j;
	output << resetiosflags(ios::right) << setiosflags(ios::left) << setfill(' '); //����Ҷ���, ���������, ���ò��㲹�ո�

	if (print_frame) {
		output << "��";
		for (j = 0; j < column; j++) {
			output << "  " << setw(12) << " ";
		}
		output << " ��" << endl;
	}

	for (i = 0; i < row; i++) {
		if (print_frame) {
			output << "��";
		}
		for (j = 0; j < column; j++) {
			output << "  " << setw(12) << p[i][j];
		}
		if (print_frame) {
			output << " ��" << endl;
		}
	}

	if (print_frame) {
		output << "��";
		for (j = 0; j < column; j++) {
			output << "  " << setw(12) << " ";
		}
		output << " ��";
		if (print_corner) {
			output << " " << row << " �� " << column;
		}
		output << endl;
	}
}

template <class Type>
size_t Array_2d<Type>::get_digit_size() const
{
	return row * (sizeof(Type*) + column * sizeof(Type));
}

template <class Type>
inline void Array_2d<Type>::test_row(const int row_test) const throw (out_of_range)
{
	if (row_test < 0 || row_test >= this->row) {
		throw out_of_range("The " + to_string(this->row) + " �� " + to_string(this->column) + " Array doesn't have the no." + to_string(row_test) + " row!");
	}
}

template <class Type>
inline void Array_2d<Type>::test_column(const int column_test) const throw (out_of_range)
{
	if (column_test < 0 || column_test >= this->column) {
		throw out_of_range("The " + to_string(this->row) + " �� " + to_string(this->column) + " Array doesn't have the no." + to_string(column_test) + " column!");
	}
}

template <class Type>
bool Array_2d<Type>::operator==(const Array_2d<Type> &with) const
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

template <class Type>
bool Array_2d<Type>::operator!=(const Array_2d<Type> &with) const
{
	return !(this->operator ==(with));
}

//template <class Type>
//void Array_2d<Type>::memcpy(Type* Dst, Type* Src, size_t Size_of_src, bool deep)
//{
//	cout << 123456 << endl;
//	const int n = Size_of_src / sizeof(*Src);
//	for (int i = 0; i < n; i++) {
//		Dst[i] = Src[i];
//	}
//}

#endif	/* End _ARRAY_2D_H_ */
