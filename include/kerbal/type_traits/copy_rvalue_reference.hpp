/**
 * @file       copy_rvalue_reference.hpp
 * @brief
 * @date       2022-10-29
 * @author     Peter
 * @remark     split up from kerbal/type_traits/reference_deduction.hpp, 2019-4-29
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_COPY_RVALUE_REFERENCE_HPP
#define KERBAL_TYPE_TRAITS_COPY_RVALUE_REFERENCE_HPP

#if __cplusplus < 201103L
#	error This file requires compiler and library support for the ISO C++ 2011 standard.
#endif

#include <kerbal/ts/modules_ts/modules_ts.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/add_rvalue_reference.hpp>
#include <kerbal/type_traits/is_rvalue_reference.hpp>


namespace kerbal
{

	namespace type_traits
	{

		MODULE_EXPORT
		template <typename From, typename To>
		struct copy_rvalue_reference :
				kerbal::type_traits::conditional<
					kerbal::type_traits::is_rvalue_reference<From>::value,
					kerbal::type_traits::add_rvalue_reference<To>,
					To
				>
		{
		};

	} // namespace type_traits

} // namespace kerbal


#endif // KERBAL_TYPE_TRAITS_COPY_RVALUE_REFERENCE_HPP
