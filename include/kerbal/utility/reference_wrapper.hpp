/**
 * @file       reference_wrapper.hpp
 * @brief      
 * @date       2019-7-26
 * @author     peter
 * @copyright
 *      peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_REFERENCE_WRAPPER_HPP_
#define KERBAL_UTILITY_REFERENCE_WRAPPER_HPP_

#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/utility/addressof.hpp>

namespace kerbal
{
	namespace utility
	{
		template <typename Tp>
		class reference_wrapper
		{
			public:
				typedef Tp type;

			private:
				Tp * ptr;

			public:
				KERBAL_CONSTEXPR reference_wrapper(Tp & val) KERBAL_NOEXCEPT :
						ptr(kerbal::utility::addressof(val))
				{
				}

			# if __cplusplus >= 201103L
			
				constexpr reference_wrapper& operator=(const reference_wrapper&) noexcept = default;

			# endif

				KERBAL_CONSTEXPR operator Tp& () const KERBAL_NOEXCEPT
				{
					return *ptr;
				}
				
				KERBAL_CONSTEXPR Tp& get() const KERBAL_NOEXCEPT
				{
					return *ptr;
				}
		};
		
		template <typename Tp>
		KERBAL_CONSTEXPR
		reference_wrapper<Tp>
		ref(Tp & val) KERBAL_NOEXCEPT
		{
			return reference_wrapper<Tp>(val);
		}

		template <typename Tp>
		KERBAL_CONSTEXPR
		reference_wrapper<const Tp>
		cref(const Tp & val) KERBAL_NOEXCEPT
		{
			return reference_wrapper<const Tp>(val);
		}

	} // namespace utility

} // namespace kerbal

#endif /* KERBAL_UTILITY_REFERENCE_WRAPPER_HPP_ */
