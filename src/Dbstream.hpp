/*
 * Dbstream.hpp
 *
 *  Created on: 2017��9��2��
 *      Author: Peter
 */

#ifndef DBSTREAM_HPP_
#define DBSTREAM_HPP_

#include <iostream>

extern bool debug;

namespace dbstream
{

	class Dbstream
	{
		protected:
			bool new_line;
			std::ostream *out;

			friend inline Dbstream& endl(Dbstream& __dbs);

		public:
			Dbstream();
			void why_cannot_use();
			Dbstream& operator<<(Dbstream& (*f)(Dbstream& __os));

			template <class T>
			Dbstream& operator<<(const T &z)
			{
				if (debug) {
					if (this->new_line) {
						*out << "- ";
						this->new_line = false;
					}
					*out << z;
				}
				return *this;
			}
	};

	extern Dbstream cdb;

	inline Dbstream& endl(Dbstream& __dbs)
	{
		if (debug) {
			if (__dbs.new_line) {
				*__dbs.out << "- ";
			}

			__dbs.new_line = true;
			*__dbs.out << std::endl;

		}
		return __dbs;
	}

} /* namespace dbstream */

#endif /* DBSTREAM_HPP_ */
