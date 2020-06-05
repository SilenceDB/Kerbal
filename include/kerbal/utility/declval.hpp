/**
 * @file       declval.hpp
 * @brief
 * @date       2019-11-30
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */


#ifndef KERBAL_UTILITY_DECLVAL_HPP
#define KERBAL_UTILITY_DECLVAL_HPP

#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/type_traits/reference_deduction.hpp>

namespace kerbal
{
	namespace utility
	{

#	if __cplusplus >= 201103L

		template <typename Tp>
		typename kerbal::type_traits::add_rvalue_reference<Tp>::type
		declval() KERBAL_NOEXCEPT;

#	else

		template <typename Tp>
		typename kerbal::type_traits::add_lvalue_reference<Tp>::type
		declval() KERBAL_NOEXCEPT;

#	endif

		template <typename Tp>
		Tp*
		declthis() KERBAL_NOEXCEPT;


	}
}

#endif //KERBAL_UTILITY_DECLVAL_HPP