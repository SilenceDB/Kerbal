/**
 * @file       incr_decr.hpp
 * @brief      
 * @date       2019-7-14
 * @author     peter
 * @copyright
 *      peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_OPERATORS_INCR_DECR_HPP_
#define KERBAL_OPERATORS_INCR_DECR_HPP_

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>

#if __cplusplus >= 201103L
#	include <type_traits>
#endif

namespace kerbal
{
	namespace operators
	{
		template <typename Tp>
		struct incrementable
		{
				friend KERBAL_CONSTEXPR14 Tp operator++(Tp& x, int)
						KERBAL_CONDITIONAL_NOEXCEPT(
								std::is_nothrow_copy_constructible<Tp>::value &&
								noexcept(++x)
						)
				{
					Tp tmp(x);
					++x;
					return tmp;
				}
		};

		template <class Tp>
		struct decrementable
		{
				friend KERBAL_CONSTEXPR14 Tp operator--(Tp& x, int)
						KERBAL_CONDITIONAL_NOEXCEPT(
								std::is_nothrow_copy_constructible<Tp>::value &&
								noexcept(--x)
						)
				{
					Tp tmp(x);
					--x;
					return tmp;
				}
		};

	} // namespace operators

} // namespace kerbal

#endif /* KERBAL_OPERATORS_INCR_DECR_HPP_ */
