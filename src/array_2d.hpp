#ifndef _ARRAY_2D_H_
#define _ARRAY_2D_H_

#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include "except_C++0x.hpp"

#if __cplusplus >= 201103L //C++0x
# include <initializer_list>
#endif //C++0x

#include "String_serve.hpp"

template <class T>
inline int array_2d_row(const T &a) //返回矩阵的行
{
	return sizeof(a) / sizeof(a[0]);
}

template <class T>
inline int array_2d_column(const T &a) //返回矩阵的列
{
	return sizeof(a[0]) / siz0eof(a[0][0]);
}

namespace array_2d
{
	namespace
	{
		using namespace std;
	}

	template <class Type> class Array_2d;
//供safety使用的的前向申明

	template <class Type>
	class safety  //本类用来提供对动态二维数组Array_2d类的下标运算的安全访问
	{
		protected:
			Array_2d<Type> *p_to_matrix;
			mutable int row_point_to;
		public:
			safety(Array_2d<Type> *p_to_matrix, const int row_point_to)
			{
				this->p_to_matrix = p_to_matrix;
				this->row_point_to = row_point_to;
				//cout<<"safe:"<<this<<endl;
			}

			safety(const Array_2d<Type> * const p2, const int row)
			{
				this->p_to_matrix = (Array_2d<Type> *) p2;
				this->row_point_to = row;
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
				return p_to_matrix->p[row_point_to];
			}

			const Type* begin() const
			{
				return p_to_matrix->p[row_point_to];
			}

			Type* end()
			{
				return p_to_matrix->p[row_point_to] + p_to_matrix->column;
			}

			const Type* end() const
			{
				return p_to_matrix->p[row_point_to] + p_to_matrix->column;
			}

			safety<Type> operator++()
			{
				++row_point_to;
				return *this;
			}

			friend bool operator!=(const safety<Type> &a, const safety<Type> &b) throw (invalid_argument)
			{
				if (a.p_to_matrix == b.p_to_matrix) {
					return a.row_point_to != b.row_point_to;
				} else {
					throw invalid_argument("a and b is not point to same Array_2d");
				}
			}
	};

	template <class Type>
	Type& safety<Type>::operator[](int column) throw (out_of_range)
	{
		p_to_matrix->test_column(column);
		return p_to_matrix->p[row_point_to][column];
	}

	template <class Type>
	const Type& safety<Type>::operator[](int column) const throw (out_of_range)
	{
		p_to_matrix->test_column(column);
		return p_to_matrix->p[row_point_to][column];
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
//		Array_2d(const int row, const int column, int argc, ...);  //利用可变参数表进行构造

			Array_2d(const int row, const int column, Type (*function)());
			//动态开辟一个以p为首地址的、row * column的二维数组, 并使用 function() 初始化每个元素
			Array_2d(const int row, const int column, Type (*function)(int, int));
			//动态开辟一个以p为首地址的、row * column的二维数组, 并使用 function(i,j) 初始化每个元素

			template <class T>
			Array_2d(const T *src, const int row, const int column)
			{ //利用二维数组进行构造
				if (row > 0 && column > 0) {
					this->row = row;
					this->column = column;

					//动态开辟一个以p为首地址的、row * column的二维数组
					p = new Type*[row]; //开辟行
					for (int i = 0; i < row; i++) {
						p[i] = new Type[column]; //开辟列
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

			Array_2d(Type arr[], int len, bool in_a_row = true); //利用一维数组进行构造

#if __cplusplus >= 201103L //C++0x
			Array_2d(initializer_list<initializer_list<Type>> src) throw (invalid_argument); //利用二维初始化列表进行构造
			Array_2d(initializer_list<Type> src); //利用一维初始化列表进行构造
#endif //C++0x

			Array_2d(const Array_2d &src); //拷贝构造函数

			virtual ~Array_2d();
			bool empty() const;
			void clear();

			void resize(int new_row, int new_column);

			inline int get_row() const;
			inline int get_column() const;
			inline const Type** get_data() const;
			inline bool is_const();
			inline bool is_const() const;

			const Type& get_element(int row, int column) const throw (out_of_range);
			Type& get_element(int row, int column) throw (out_of_range);

			void set_element(int row, int column, Type value) throw (out_of_range);
			template <class T> void set_element(const T *src, int row, int column); //根据二维数组设值
			Array_2d<Type> call(Type (*__pf)(Type)) const;

			Array_2d<Type>& operator <<(const Type &value) throw (out_of_range); //输入
			Array_2d<Type>& operator <<(const Array_2d_input_info &value);
			Array_2d<Type>& operator <<(const string & src) throw (out_of_range); //字符串输入
			Array_2d<Type>& operator <<(ostream& (*__pf)(ostream&)); //支持endl
			friend ostream& operator <<(ostream &output, Array_2d<Type> &src) //重载输出
			{
				src.print(true, true, output);
				return output;
			}
			void print(bool print_frame = true, bool print_corner = true, ostream &output = cout) const;
			//void print_to_file(char file_name[],bool if_output_frame) const;

			safety<Type> operator[](int row) throw (out_of_range);
			const safety<Type> operator[](int row) const throw (out_of_range);

			size_t get_digit_size() const;

			friend inline void swap(Array_2d<Type> &A, Array_2d<Type> &B)
			{
				swap(A.row, B.row);
				swap(A.column, B.column);
				swap(A.p, B.p);
			}

			void test_row(const int row_test) const throw (out_of_range);
			void test_column(const int column_test) const throw (out_of_range);

			bool operator==(const Array_2d<Type> &with) const;
			bool operator!=(const Array_2d<Type> &with) const;

			void do_reflect_row();
			void do_reflect_column();
			void do_rotate_180();
			void do_rotate_90(); // 逆时针转90度
			void do_rotate_270(); // 逆时针转270度

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

			friend Array_2d<Type> sub_of(const Array_2d<Type> &src, int up, int down, int left, int right) throw (invalid_argument, out_of_range);
	};

	template <class Type>
	Array_2d<Type> sub_of(const Array_2d<Type> &src, int up, int down, int left, int right) throw (invalid_argument, out_of_range)
	{
		if (up > down || left > right) {
			throw new invalid_argument("up > down or left > right");
		}

		src.test_row(up);
		src.test_row(down);
		src.test_column(left);
		src.test_column(right);

		Array_2d<Type> result(down - up + 1, right - left + 1, false);
		for (int i = 0; i < result.row; ++i) {
			for (int j = 0; j < result.column; ++j) {
				result.p[i][j] = src.p[i + up][j + left];
			}
		}
		return result;
	}

	template <class Type>
	Array_2d<Type>::Array_2d(const int row, const int column, bool if_set0)
	{
		//int row, int column, bool if_set0 默认 = true
		//动态开辟一个以p为首地址的、row * column的二维数组
		if (row > 0 && column > 0) {
			this->row = row;
			this->column = column;

			p = new Type*[row]; //开辟行
			if (if_set0) {
				const size_t size_of_a_row = column * sizeof(Type); //这一行为加快速度而存在
				for (int i = 0; i < row; i++) {
					memset(p[i] = new Type[column], 0, size_of_a_row);
				}
			} else {
				for (int i = 0; i < row; i++) {
					p[i] = new Type[column]; //开辟列
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
//	//动态开辟一个以p为首地址的、row * column的二维数组
//	if (row > 0 && column > 0) {
//		this->row = row;
//		this->column = column;
//
//		p = new Type*[row]; //开辟行
//
////if(argc>row*column){
////	argc
////}
//		va_list arg_ptr; //指向参数的指针
//		va_start(arg_ptr, argc);
//
//		for (int i = 0; i < row; i++) {
//			p[i] = new Type[column]; //开辟列
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
	Array_2d<Type>::Array_2d(const int row, const int column, Type (*function)())
	{
		//动态开辟一个以p为首地址的、row * column的二维数组, 并使用 function() 初始化每个元素
		if (row > 0 && column > 0) {
			this->row = row;
			this->column = column;

			p = new Type*[row]; //开辟行
			for (int i = 0; i < row; i++) {
				p[i] = new Type[column]; //开辟列
				for (int j = 0; j < column; j++) {
					p[i][j] = function();
				}
			}

		} else {
			this->row = 0;
			this->column = 0;
			this->p = NULL;
		}
	}

	template <class Type>
	Array_2d<Type>::Array_2d(const int row, const int column, Type (*function)(int, int))
	{
		//动态开辟一个以p为首地址的、row * column的二维数组, 并使用 function(i,j) 初始化每个元素
		if (row > 0 && column > 0) {
			this->row = row;
			this->column = column;

			p = new Type*[row]; //开辟行
			for (int i = 0; i < row; i++) {
				p[i] = new Type[column]; //开辟列
				for (int j = 0; j < column; j++) {
					p[i][j] = function(i, j);
				}
			}

		} else {
			this->row = 0;
			this->column = 0;
			this->p = NULL;
		}
	}

	template <class Type>
	Array_2d<Type>::Array_2d(Type arr[], int len, bool in_a_row)
	{ //利用一维数组进行构造
		if (len > 0) {
			if (in_a_row) {
				this->row = 1;
				this->column = len;
				p = new Type*[1];
				p[0] = new Type[column]; //开辟列

				for (int j = 0; j < column; j++) {
					p[0][j] = arr[j];
				}
			} else {
				this->row = len;
				this->column = 1;

				p = new Type*[row];
				for (int i = 0; i < row; i++) {
					p[i] = new Type[1]; //开辟列
					p[i][0] = arr[i];
				}
			}
		} else {
			this->row = 0;
			this->column = 0;
			this->p = NULL;
		}
	}

#if __cplusplus >= 201103L //C++0x

	template <class Type>
	Array_2d<Type>::Array_2d(initializer_list<initializer_list<Type>> src) throw (invalid_argument)
	{
		//利用二维初始化列表进行构造

		const int row_pre = src.size(); //最终定下的行数
		const int column_pre = src.begin()->size(); //最终定下的列数
		//扫描src每行的列数, 不一致则抛异常
		for (auto j : src) {
			if (j.size() != (unsigned) column_pre) {
				throw invalid_argument("the initializer list is not a standard Array_2d");
			}
		}

		if (row_pre > 0 && column_pre > 0) {
			this->row = row_pre;
			this->column = column_pre;

			//动态开辟一个以p为首地址的、row * column的二维数组
			p = new Type*[row]; //开辟行
			auto begin_to_src = src.begin();
			for (int i = 0; i < row; i++) {
				Type *p_to_first = p[i] = new Type[column];
				const initializer_list<Type> &list_row = *(begin_to_src + i);
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

	template <class Type>
	Array_2d<Type>::Array_2d(initializer_list<Type> src)
	{
		//利用一维初始化列表进行构造
		const int column_pre = src.size(); //最终定下的列数

		if (column_pre > 0) {
			this->row = 1;
			this->column = column_pre;

			//动态开辟一个以p为首地址的、1 * column的二维数组
			p = new Type*[1]; //开辟行
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

#endif //C++0x

	template <class Type>
	Array_2d<Type>::Array_2d(const Array_2d<Type> &src) //拷贝构造函数
	{
		if (src.row > 0 && src.column > 0) {
			this->row = src.row;
			this->column = src.column;

			p = new Type*[row]; //开辟行
			for (int i = 0; i < row; i++) {
				p[i] = new Type[column]; //开辟列
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
		//归还一个row行的二维数组
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
		//归还一个row行的二维数组
		for (int i = 0; i < row; ++i)
			delete[] p[i];
		delete[] p;
		p = NULL;
		row = 0;
		column = 0;
	}

	template <class Type>
	void Array_2d<Type>::resize(int new_row, int new_column)
	{
		if (new_row <= 0 || new_column <= 0) { //防止非正数
			this->clear();
			return;
		}
		if (row == new_row) {
			if (column == new_column) { //大小与原来一致
				return;
			} else { //行数相等, 列数不等
				for (int i = 0; i < row; ++i) {
					delete[] p[i];
					p[i] = new Type[new_column];
				}
				column = new_column;
			}
		} else {
			if (column == new_column) { //行数不等, 列数相等
				//TODO 查BUG
				Type **p_former = p;
				p = new Type*[new_row];
				if (new_row < row) { //行数减少
					for (int i = 0; i < new_row; ++i) {
						p[i] = p_former[i];
					}
					for (int i = new_row; i < row; ++i) {
						delete[] p_former[i];
					}
				} else { //行数增多
					for (int i = 0; i < row; ++i) {
						p[i] = p_former[i];
					}
					for (int i = row; i < new_row; ++i) {
						p[i] = new Type[column];
					}
				}
				delete[] p_former; //TODO
				row = new_row;
			} else { //行数不等, 列数不等
				//TODO 查bug
				for (int i = 0; i < row; ++i)
					delete[] p[i];
				delete[] p;
				row = new_row;
				column = new_column;
				p = new Type*[row];
				for (int i = 0; i < row; ++i) {
					p[i] = new Type[column];
				}
			}
		}
	}

	template <class Type>
	inline int Array_2d<Type>::get_row() const
	{
		return row;
	}

	template <class Type>
	inline int Array_2d<Type>::get_column() const
	{
		return column;
	}

	template <class Type>
	inline const Type** Array_2d<Type>::get_data() const
	{
		return p;
	}

	template <class Type>
	inline bool Array_2d<Type>::is_const()
	{
		return false;
	}

	template <class Type>
	inline bool Array_2d<Type>::is_const() const
	{
		return true;
	}

	template <class Type>
	inline Type& Array_2d<Type>::get_element(int row, int column) throw (out_of_range)
	{
		test_row(row);
		test_column(column);
		return p[row][column];
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
	void Array_2d<Type>::set_element(const T *src, int row, int column) //通过数组赋值///此函数内有BUG
	{
		this->clear();

		this->row = row;
		this->column = column;

		p = new Type*[row]; //开辟行
		for (int i = 0; i < row; i++) {
			p[i] = new Type[column]; //开辟列
			for (int j = 0; j < column; j++) {
				p[i][j] = src[i][j];
			}
		}
	}

	template <class Type>
	Array_2d<Type> Array_2d<Type>::call(Type (*__pf)(Type)) const
	{
		Array_2d<Type> result(row, column, false);
		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < column; ++j) {
				result.p[i][j] = __pf(this->p[i][j]);
			}
		}
		return result;
	}

//利用插入运算符给动态二维数组赋值
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
			throw out_of_range(
					"尝试给[" + to_string(insert_times / column) + "][" + to_string(insert_times % column) + "]赋值"
							+ to_string(value));
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
//利用插入运算符给动态二维数组赋值

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
				throw out_of_range(
						"尝试给[" + to_string(insert_times / column) + "][" + to_string(insert_times % column) + "]赋值");
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
	void Array_2d<Type>::print(bool print_frame, bool print_corner, ostream &output) const
	{
		//void Array_2d<Type>::print(bool print_frame = true, bool print_corner = true, ostream &output = cout) const
		int i, j;
		output << resetiosflags(ios::right) << setiosflags(ios::left) << setfill(' '); //清除右对齐, 设置左对齐, 设置不足补空格

		if (print_frame) {
			{ //上边框
				output << "┌";
				for (j = 0; j < column; j++) {
					output << "  " << setw(12) << " ";
				}
				output << " ┐" << endl;
			}

			for (i = 0; i < row; i++) {
				output << "│";
				for (j = 0; j < column; j++) {
					output << "  " << setw(12) << p[i][j];
				}
				output << " │" << endl;
			}

			{ //下边框
				output << "└";
				for (j = 0; j < column; j++) {
					output << "  " << setw(12) << " ";
				}
				output << " ┘";
				if (print_corner) {
					output << " " << row << " × " << column;
				}
				output << endl;
			}
		} else {
			for (i = 0; i < row; i++) {
				for (j = 0; j < column; j++) {
					output << "  " << setw(12) << p[i][j];
				}
				output << endl;
			}
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
			throw out_of_range(
					"The " + to_string(this->row) + " × " + to_string(this->column) + " Array doesn't have the no."
							+ to_string(row_test) + " row!");
		}
	}

	template <class Type>
	inline void Array_2d<Type>::test_column(const int column_test) const throw (out_of_range)
	{
		if (column_test < 0 || column_test >= this->column) {
			throw out_of_range(
					"The " + to_string(this->row) + " × " + to_string(this->column) + " Array doesn't have the no."
							+ to_string(column_test) + " column!");
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
				if (this->p[i][j] != with.p[i][j]) {
					return false;
				}
			}
		}
		return true;
	}

	template <class Type>
	bool Array_2d<Type>::operator!=(const Array_2d<Type> &with) const
	{
		return !(this->operator==(with));
	}

	template <class Type>
	void Array_2d<Type>::do_reflect_row()
	{
		for (int i = 0; i < row / 2; ++i) {
			swap(p[i], p[row - 1 - i]);
		}
	}

	template <class Type>
	void Array_2d<Type>::do_reflect_column()
	{
		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < column / 2; ++j) {
				swap(p[i][j], p[i][column - 1 - j]);
			}
		}
	}

	template <class Type>
	void Array_2d<Type>::do_rotate_180()
	{
		do_reflect_row();
		do_reflect_column();
	}

	template <class Type>
	void Array_2d<Type>::do_rotate_90()
	{ // 逆时针转90度
		swap(row, column);

		Type **p_former = p;
		p = new Type*[row];
		for (int i = 0; i < row; ++i) {
			p[i] = new Type[column];
			for (int j = 0; j < column; ++j) {
				p[i][j] = p_former[j][row - 1 - i];
			}
		}
		for (int i = 0; i < column; ++i) {
			delete[] p_former[i];
		}
		delete[] p_former;
	}

	template <class Type>
	void Array_2d<Type>::do_rotate_270()
	{ // 逆时针转270度
		swap(row, column);

		Type **p_former = p;
		p = new Type*[row];
		for (int i = 0; i < row; ++i) {
			p[i] = new Type[column];
			for (int j = 0; j < column; ++j) {
				p[i][j] = p_former[column - 1 - j][i];
			}
		}
		for (int i = 0; i < column; ++i) {
			delete[] p_former[i];
		}
		delete[] p_former;
	}

}/* Namespace array_2d */
#endif	/* End _ARRAY_2D_H_ */
