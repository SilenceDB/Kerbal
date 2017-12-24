/*
 * dbstream.cpp
 *
 *  Created on: 2017��9��2��
 *      Author: Peter
 */

#include "dbstream.hpp"

#include <iostream>

namespace kerbal
{
	namespace utility
	{
		namespace dbstream
		{
			Dbstream cdb;

			Dbstream::Dbstream() :
					new_line(true), out(&std::cout)
			{

			}

			void Dbstream::why_cannot_use()
			{
				if (debug) {
				} else {
					std::cout << "ֻ���ڵ���program_start����ʱ,is_debugֵ�������true,����������Ż������Ϣ" << std::endl;
				}
			}

			Dbstream& Dbstream::operator<<(Dbstream& (*f)(Dbstream& __os))
			{
				f(*this);
				return *this;
			}

		} /* namespace dbstream */

	} /* namespace utility */

} /* namespace kerbal */
