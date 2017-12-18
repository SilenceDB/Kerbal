#ifndef _ARRAY_2D_HPP_
#define _ARRAY_2D_HPP_

#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include "except_C++0x.hpp"
#include "String_serve.hpp"

#if __cplusplus >= 201103L //C++0x
#	include <initializer_list>
#endif //C++0x

template <class Type, size_t M, size_t N>
inline size_t array_2d_row(const Type (&arr)[M][N]) //���ض�ά�������
{
	return M;
}

template <class Type, size_t M, size_t N>
inline size_t array_2d_column(const Type (&arr)[M][N])  //���ض�ά�������
{
	return N;
}

namespace array_2d
{
	//ǰ����������
	template <class Type> class Array_2d;

	template <class Type> inline std::ostream& operator<<(std::ostream &output, const Array_2d<Type> &src); //�������

}/* Namespace array_2d */

namespace std
{
	template <class Type> void swap(array_2d::Array_2d<Type> &A, array_2d::Array_2d<Type> &B) throw ();
//ǰ����������
}/* Namespace std */

namespace array_2d
{
	namespace
	{
		using namespace _String;
	}

	template <class Type>
	class safety  //���������ṩ�Զ�̬��ά����Array_2d����±�����İ�ȫ����
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

			virtual ~safety()
			{
				//cout<<"delete safe:"<<this<<endl;
			}

			inline bool is_const() throw ();
			inline bool is_const() const throw ();

			inline Type& operator[](int row) throw (std::out_of_range);
			inline const Type& operator[](int row) const throw (std::out_of_range);

			inline Type* begin();
			inline const Type* begin() const;

			inline Type* end();
			inline const Type* end() const;

			inline safety<Type>& operator++() const;

			inline bool operator!=(const safety<Type> &with) const throw (std::invalid_argument);
	};

	template <class Type>
	inline bool safety<Type>::operator!=(const safety<Type> &with) const throw (std::invalid_argument)
	{
		if (this->p_to_matrix == with.p_to_matrix) {
			return this->row_point_to != with.row_point_to;
		} else {
			throw std::invalid_argument("comparation between two iterators not belong to same Array_2d");
		}
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

			void mem_init();

		public:
			friend class safety<Type> ;
			Array_2d() throw () :
					row(0), column(0), p(NULL)
			{
			}

			Array_2d(const int row, const int column);
			Array_2d(const int row, const int column, const Type &val);
			Array_2d(Type (*function)(), const int row, const int column, bool para);
			//��̬����һ����pΪ�׵�ַ�ġ�row * column�Ķ�ά����, ��ʹ�� function() ��ʼ��ÿ��Ԫ��
			Array_2d(Type (*function)(int, int), const int row, const int column, bool para);
			//��̬����һ����pΪ�׵�ַ�ġ�row * column�Ķ�ά����, ��ʹ�� function(i,j) ��ʼ��ÿ��Ԫ��

			template <size_t M, size_t N>
			Array_2d(const Type (&src)[M][N], const int row, const int column); //���ö�ά������й���

			Array_2d(const Type arr[], int len, bool in_a_row = true); //����һά������й���

#	if __cplusplus >= 201103L //C++0x
			Array_2d(std::initializer_list<std::initializer_list<Type>> src) throw (std::invalid_argument); //���ö�ά��ʼ���б���й���
			Array_2d(std::initializer_list<Type> src); //����һά��ʼ���б���й���
#	endif //C++0x

			Array_2d(const Array_2d &src); //�������캯��

			virtual ~Array_2d();
			bool empty() const throw ();
			void clear() throw ();

			void resize(int new_row, int new_column);

			inline int get_row() const;
			inline int get_column() const;
			inline const Type** get_data() const;
			inline bool is_const();
			inline bool is_const() const;

			Type& get(int row, int column) throw (std::out_of_range);
			const Type& get(int row, int column) const throw (std::out_of_range);

			inline void set(int row, int column, const Type &value) throw (std::out_of_range);
			template <class T> void set(const T src[], int row, int column); //���ݶ�ά������ֵ
			void do_call(Type (*__pf)(Type));
			void do_call(Type (*__pf)(int, int));
			void do_call(Type (*__pf)(Type, int, int));
			const Array_2d<Type> call_of(Type (*__pf)(Type)) const;
			const Array_2d<Type> call_of(Type (*__pf)(int, int)) const;
			const Array_2d<Type> call_of(Type (*__pf)(Type, int, int)) const;

			Array_2d<Type>& operator<<(const Type &value) throw (std::out_of_range); //����
			Array_2d<Type>& operator<<(const Array_2d_input_info &value);
			Array_2d<Type>& operator<<(const std::string & src) throw (std::out_of_range); //�ַ�������
			Array_2d<Type>& operator<<(std::ostream& (*__pf)(std::ostream&)); //֧��endl

			virtual void print(bool print_frame = true, bool print_corner = true, std::ostream &output = std::cout) const;
			//void print_to_file(char file_name[],bool if_output_frame) const;

			inline safety<Type> operator[](int row) throw (std::out_of_range);
			inline const safety<Type> operator[](int row) const throw (std::out_of_range);
			inline Type& operator()(int row, int column) throw (std::out_of_range);
			inline const Type& operator()(int row, int column) const throw (std::out_of_range);

			virtual size_t get_digit_size() const;

			friend void std::swap<>(Array_2d<Type> &A, Array_2d<Type> &B) throw ();

			virtual void test_row(const int row_test) const throw (std::out_of_range);
			virtual void test_column(const int column_test) const throw (std::out_of_range);

			virtual bool operator==(const Array_2d<Type> &with) const;
			virtual bool operator!=(const Array_2d<Type> &with) const;

			void do_reflect_row() throw ();
			void do_reflect_column(); //�����п��ܻ��׳��쳣, ����᲻��ȡ���� swap(Type&, Type&)
			void do_rotate_180();
			void do_rotate_90(); // ��ʱ��ת90��
			void do_rotate_270(); // ��ʱ��ת270��

			const Array_2d<Type> sub_of(int up, int down, int left, int right) const throw (std::invalid_argument, std::out_of_range);

	};
}/* Namespace array_2d */

namespace std
{
	template <class Type>
	void swap(array_2d::Array_2d<Type> &A, array_2d::Array_2d<Type> &B) throw ()
	{
		std::swap(A.row, B.row);
		std::swap(A.column, B.column);
		std::swap(A.p, B.p);
	}
}/* Namespace std */

#include "array_2d_base.hpp"
#endif	/* End _ARRAY_2D_HPP_ */
