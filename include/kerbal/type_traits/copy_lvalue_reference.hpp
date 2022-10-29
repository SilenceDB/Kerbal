/**
 * @file       copy_lvalue_reference.hpp
 * @brief
 * @date       2022-10-29
 * @author     Peter
 * @remark     split up from kerbal/type_traits/reference_deduction.hpp, 2019-4-29
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_TYPE_TRAITS_COPY_LVALUE_REFERENCE_HPP
#define KERBAL_TYPE_TRAITS_COPY_LVALUE_REFERENCE_HPP

#include <kerbal/ts/modules_ts/modules_ts.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/add_lvalue_reference.hpp>
#include <kerbal/type_traits/is_lvalue_reference.hpp>


namespace kerbal
{

	namespace type_traits
	{

		MODULE_EXPORT
		template <typename From, typename To>
		struct copy_lvalue_reference :
				kerbal::type_traits::conditional<
					kerbal::type_traits::is_lvalue_reference<From>::value,
					typename kerbal::type_traits::add_lvalue_reference<To>::type,
					To
				>
		{
		};

	} // namespace type_traits

} // namespace kerbal


#endif // KERBAL_TYPE_TRAITS_COPY_LVALUE_REFERENCE_HPP
