/**
 * @file       member_compress_helper.hpp
 * @brief
 * @date       2020-09-20
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_UTILITY_MEMBER_COMPRESS_HELPER_HPP
#define KERBAL_UTILITY_MEMBER_COMPRESS_HELPER_HPP

#include <kerbal/utility/member_compress_helper/member_compress_helper.fwd.hpp>

#include <kerbal/assign/ilist.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/method_overload_tag.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/operators/generic_assign.hpp>
#include <kerbal/type_traits/can_be_empty_base.hpp>
#include <kerbal/type_traits/reference_deduction.hpp>
#include <kerbal/type_traits/volatile_deduction.hpp>
#include <kerbal/utility/declval.hpp>
#include <kerbal/utility/in_place.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#	include <kerbal/utility/integer_sequence.hpp>
#else
#	include <kerbal/algorithm/modifier.hpp>
#endif

#include <cstddef>

#if __cplusplus >= 201103L
#	include <initializer_list>
#endif


namespace kerbal
{

	namespace utility
	{

		namespace detail
		{

			template <typename T, bool = kerbal::type_traits::can_be_empty_base<T>::value>
			class member_compress_helper_impl;

			template <typename T>
			class member_compress_helper_impl<T, false>
			{
				public:
					T _K_member;

				public:
					typedef kerbal::type_traits::false_type IS_COMPRESSED;

					typedef T																	value_type;
					typedef typename kerbal::type_traits::add_lvalue_reference<T>::type			reference;
					typedef typename kerbal::type_traits::add_const_lvalue_reference<T>::type	const_reference;

#			if __cplusplus >= 201103L
					typedef typename kerbal::type_traits::add_rvalue_reference<T>::type			rvalue_reference;
					typedef typename kerbal::type_traits::add_const_rvalue_reference<T>::type	const_rvalue_reference;
#			endif

				public:

#			if __cplusplus >= 201103L

					member_compress_helper_impl() = default;

#			else

					member_compress_helper_impl()
					{
					}

#			endif

#			if __cplusplus >= 201103L

					template <typename ... Args>
					KERBAL_CONSTEXPR
					explicit member_compress_helper_impl(kerbal::utility::in_place_t, Args&& ... args)
									KERBAL_CONDITIONAL_NOEXCEPT(
											(std::is_nothrow_constructible<T, Args&&...>::value)
									) :
							_K_member(kerbal::utility::forward<Args>(args)...)
					{
					}

#			else

#				define EMPTY
#				define REMAINF(exp) exp
#				define LEFT_JOIN_COMMA(exp) , exp
#				define THEAD_NOT_EMPTY(exp) template <exp>
#				define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#				define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#				define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#				define FBODY(i) \
					KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
					explicit member_compress_helper_impl(kerbal::utility::in_place_t KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)): \
							_K_member(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_USE, i)) \
					{ \
					}

					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#				undef EMPTY
#				undef REMAINF
#				undef LEFT_JOIN_COMMA
#				undef THEAD_NOT_EMPTY
#				undef TARGS_DECL
#				undef ARGS_DECL
#				undef ARGS_USE
#				undef FBODY

#			endif

					template <typename U, std::size_t J>
					KERBAL_CONSTEXPR
					explicit member_compress_helper_impl(const kerbal::utility::member_compress_helper<U, J> & src)
									KERBAL_CONDITIONAL_NOEXCEPT((
											std::is_nothrow_constructible<
													T,
													typename kerbal::utility::member_compress_helper<U, J>::const_reference
											>::value
									)) :
							_K_member(src.member())
					{
					}

#			if __cplusplus >= 201103L

					template <typename U, std::size_t J>
					KERBAL_CONSTEXPR
					explicit member_compress_helper_impl(kerbal::utility::member_compress_helper<U, J> && src)
								KERBAL_CONDITIONAL_NOEXCEPT((
										std::is_nothrow_constructible<
												T,
												typename kerbal::utility::member_compress_helper<U, J>::rvalue_reference
										>::value
								)) :
							_K_member(kerbal::compatibility::move(src).member())
					{
					}

#			endif

					KERBAL_CONSTEXPR14
					reference member() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return this->_K_member;
					}

					KERBAL_CONSTEXPR
					const_reference member() KERBAL_CONST_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return this->_K_member;
					}

#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR14
					rvalue_reference member() && KERBAL_NOEXCEPT
					{
						return kerbal::compatibility::move(*this)._K_member;
					}

					KERBAL_CONSTEXPR
					const_rvalue_reference member() const && KERBAL_NOEXCEPT
					{
						return kerbal::compatibility::move(*this)._K_member;
					}

#			endif

			};

			template <typename T>
			class member_compress_helper_impl<T, true>:
					private kerbal::type_traits::remove_volatile<T>::type
			{
				private:
					typedef typename kerbal::type_traits::remove_volatile<T>::type super;

				public:
					typedef kerbal::type_traits::true_type IS_COMPRESSED;

					typedef T																	value_type;
					typedef typename kerbal::type_traits::add_lvalue_reference<T>::type			reference;
					typedef typename kerbal::type_traits::add_const_lvalue_reference<T>::type	const_reference;

#			if __cplusplus >= 201103L
					typedef typename kerbal::type_traits::add_rvalue_reference<T>::type			rvalue_reference;
					typedef typename kerbal::type_traits::add_const_rvalue_reference<T>::type	const_rvalue_reference;
#			endif

				public:

#			if __cplusplus >= 201103L

					member_compress_helper_impl() = default;

#			else

					member_compress_helper_impl()
					{
					}

#			endif

#			if __cplusplus >= 201103L

					template <typename ... Args>
					KERBAL_CONSTEXPR
					explicit member_compress_helper_impl(kerbal::utility::in_place_t, Args&& ... args)
									KERBAL_CONDITIONAL_NOEXCEPT(
											(std::is_nothrow_constructible<super, Args&&...>::value)
									) :
							super(kerbal::utility::forward<Args>(args)...)
					{
					}

#			else

#				define EMPTY
#				define REMAINF(exp) exp
#				define LEFT_JOIN_COMMA(exp) , exp
#				define THEAD_NOT_EMPTY(exp) template <exp>
#				define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#				define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#				define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#				define FBODY(i) \
					KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
					explicit member_compress_helper_impl(kerbal::utility::in_place_t KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)): \
							super(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_USE, i)) \
					{ \
					}

					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#				undef EMPTY
#				undef REMAINF
#				undef LEFT_JOIN_COMMA
#				undef THEAD_NOT_EMPTY
#				undef TARGS_DECL
#				undef ARGS_DECL
#				undef ARGS_USE
#				undef FBODY

#			endif

					template <typename U, std::size_t J>
					KERBAL_CONSTEXPR
					explicit member_compress_helper_impl(const kerbal::utility::member_compress_helper<U, J> & src)
									KERBAL_CONDITIONAL_NOEXCEPT((
											std::is_nothrow_constructible<
													T,
													typename kerbal::utility::member_compress_helper<U, J>::const_reference
											>::value
									)) :
							super(src.member())
					{
					}

#			if __cplusplus >= 201103L

					template <typename U, std::size_t J>
					KERBAL_CONSTEXPR
					explicit member_compress_helper_impl(kerbal::utility::member_compress_helper<U, J> && src)
									KERBAL_CONDITIONAL_NOEXCEPT((
											std::is_nothrow_constructible<
													T,
													typename kerbal::utility::member_compress_helper<U, J>::rvalue_reference
											>::value
									)) :
							super(kerbal::compatibility::move(src).member())
					{
					}

#			endif

					KERBAL_CONSTEXPR14
					reference member() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return static_cast<reference>(*this);
					}

					KERBAL_CONSTEXPR
					const_reference member() KERBAL_CONST_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return static_cast<const_reference>(*this);
					}

#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR14
					rvalue_reference member() && KERBAL_NOEXCEPT
					{
						return static_cast<rvalue_reference>(*this);
					}

					KERBAL_CONSTEXPR
					const_rvalue_reference member() const && KERBAL_NOEXCEPT
					{
						return static_cast<const_rvalue_reference>(*this);
					}

#			endif

			};

			template <typename T>
			class member_compress_helper_impl<const T, true>:
					private kerbal::type_traits::remove_volatile<T>::type
			{
				private:
					typedef typename kerbal::type_traits::remove_volatile<T>::type super;

				public:
					typedef kerbal::type_traits::true_type IS_COMPRESSED;

					typedef const T																		value_type;
					typedef typename kerbal::type_traits::add_lvalue_reference<const T>::type			reference;
					typedef typename kerbal::type_traits::add_const_lvalue_reference<const T>::type		const_reference;

#			if __cplusplus >= 201103L
					typedef typename kerbal::type_traits::add_rvalue_reference<const T>::type			rvalue_reference;
					typedef typename kerbal::type_traits::add_const_rvalue_reference<const T>::type		const_rvalue_reference;
#			endif

				public:

#			if __cplusplus >= 201103L

					member_compress_helper_impl() = default;

#			else

					member_compress_helper_impl()
					{
					}

#			endif

#			if __cplusplus >= 201103L

					template <typename ... Args>
					KERBAL_CONSTEXPR
					explicit member_compress_helper_impl(kerbal::utility::in_place_t, Args&& ... args)
									KERBAL_CONDITIONAL_NOEXCEPT(
											(std::is_nothrow_constructible<super, Args...>::value)
									) :
							super(kerbal::utility::forward<Args>(args)...)
					{
					}

#			else

#				define EMPTY
#				define REMAINF(exp) exp
#				define LEFT_JOIN_COMMA(exp) , exp
#				define THEAD_NOT_EMPTY(exp) template <exp>
#				define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#				define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#				define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#				define FBODY(i) \
					KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
					explicit member_compress_helper_impl(kerbal::utility::in_place_t KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)): \
							super(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_USE, i)) \
					{ \
					}

					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#				undef EMPTY
#				undef REMAINF
#				undef LEFT_JOIN_COMMA
#				undef THEAD_NOT_EMPTY
#				undef TARGS_DECL
#				undef ARGS_DECL
#				undef ARGS_USE
#				undef FBODY

#			endif

					template <typename U, std::size_t J>
					KERBAL_CONSTEXPR
					explicit member_compress_helper_impl(const kerbal::utility::member_compress_helper<U, J> & src)
									KERBAL_CONDITIONAL_NOEXCEPT((
											std::is_nothrow_constructible<
													const T,
													typename kerbal::utility::member_compress_helper<U, J>::const_reference
											>::value
									)) :
							super(src.member())
					{
					}

#			if __cplusplus >= 201103L

					template <typename U, std::size_t J>
					KERBAL_CONSTEXPR
					explicit member_compress_helper_impl(kerbal::utility::member_compress_helper<U, J> && src)
									KERBAL_CONDITIONAL_NOEXCEPT((
											std::is_nothrow_constructible<
													const T,
													typename kerbal::utility::member_compress_helper<U, J>::rvalue_reference
											>::value
									)) :
							super(kerbal::compatibility::move(src).member())
					{
					}

#			endif


				// note: `member_compress_helper_impl` couldn't inherit from `noncopyassignable` in pursuit of more effective compression effect

#			if __cplusplus < 201103L

				private:
					member_compress_helper_impl& operator=(const member_compress_helper_impl &);

#			else

				public:
					member_compress_helper_impl& operator=(const member_compress_helper_impl &) = delete;
					member_compress_helper_impl& operator=(member_compress_helper_impl &&) = delete;

#			endif

				public:

					KERBAL_CONSTEXPR14
					reference member() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return static_cast<reference>(*this);
					}

					KERBAL_CONSTEXPR
					const_reference member() KERBAL_CONST_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
					{
						return static_cast<const_reference>(*this);
					}

#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR14
					rvalue_reference member() && KERBAL_NOEXCEPT
					{
						return static_cast<rvalue_reference>(*this);
					}

					KERBAL_CONSTEXPR
					const_rvalue_reference member() const && KERBAL_NOEXCEPT
					{
						return static_cast<const_rvalue_reference>(*this);
					}

#			endif

			};

		} // namespace detail

		template <typename T, std::size_t I>
		class member_compress_helper: public detail::member_compress_helper_impl<T>
		{
			private:
				typedef kerbal::utility::detail::member_compress_helper_impl<T> super;

			public:
				typedef typename super::value_type					value_type;
				typedef typename super::reference					reference;
				typedef typename super::const_reference				const_reference;

#		if __cplusplus >= 201103L
				typedef typename super::rvalue_reference			rvalue_reference;
				typedef typename super::const_rvalue_reference		const_rvalue_reference;
#		endif

			public:

#		if __cplusplus < 201103L

				member_compress_helper()
				{
				}

#		else

				member_compress_helper() = default;

#		endif


#		if __cplusplus < 201103L

#			define EMPTY
#			define LEFT_JOIN_COMMA(exp) , exp
#			define THEAD_NOT_EMPTY(exp) template <exp>
#			define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#			define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#			define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#			define FBODY(i) \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
				explicit member_compress_helper(kerbal::utility::in_place_t in_place KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)): \
						super(in_place KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)) \
				{ \
				}

				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#			undef EMPTY
#			undef LEFT_JOIN_COMMA
#			undef THEAD_NOT_EMPTY
#			undef TARGS_DECL
#			undef ARGS_DECL
#			undef ARGS_USE
#			undef FBODY

#		else

				template <typename ... Args>
				KERBAL_CONSTEXPR
				explicit member_compress_helper(kerbal::utility::in_place_t in_place, Args&& ... args)
						KERBAL_CONDITIONAL_NOEXCEPT((
							std::is_nothrow_constructible<super, kerbal::utility::in_place_t, Args&&...>::value
						)) :
						super(in_place, kerbal::utility::forward<Args>(args)...)
				{
				}

#		endif


				template <typename U, std::size_t J>
				KERBAL_CONSTEXPR
				explicit member_compress_helper(const kerbal::utility::member_compress_helper<U, J> & src)
						KERBAL_CONDITIONAL_NOEXCEPT((
							std::is_nothrow_constructible<
								T,
								const kerbal::utility::member_compress_helper<U, J> &
							>::value
						)) :
						super(src)
				{
				}


#		if __cplusplus >= 201103L

				template <typename U, std::size_t J>
				KERBAL_CONSTEXPR
				explicit member_compress_helper(kerbal::utility::member_compress_helper<U, J> && src)
						KERBAL_CONDITIONAL_NOEXCEPT((
							std::is_nothrow_constructible<
								super,
								kerbal::utility::member_compress_helper<U, J> &&
							>::value
						)) :
						super(kerbal::compatibility::move(src))
				{
				}

#		endif


#		if __cplusplus < 201103L

				template <typename U>
				void assign(const U & arg)
				{
					kerbal::operators::generic_assign(this->member(), arg);
				}

#		else

				template <typename U>
				KERBAL_CONSTEXPR14
				void assign(U && arg)
						KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(kerbal::operators::generic_assign(
										kerbal::utility::declthis<member_compress_helper>()->member(),
										kerbal::utility::forward<U>(arg)
								))
						)
				{
					kerbal::operators::generic_assign(this->member(), kerbal::utility::forward<U>(arg));
				}

#		endif


				template <typename U, std::size_t J>
				KERBAL_CONSTEXPR14
				member_compress_helper& operator=(const member_compress_helper<U, J> & arg)
						KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(kerbal::operators::generic_assign(
										kerbal::utility::declthis<member_compress_helper>()->member(),
										arg.member()
								))
						)
				{
					kerbal::operators::generic_assign(this->member(), arg.member());
					return *this;
				}

#		if __cplusplus >= 201103L

				template <typename U, std::size_t J>
				KERBAL_CONSTEXPR14
				member_compress_helper& operator=(member_compress_helper<U, J> && arg)
						KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(kerbal::operators::generic_assign(
										kerbal::utility::declthis<member_compress_helper>()->member(),
										kerbal::compatibility::move(arg).member()
								))
						)
				{
					kerbal::operators::generic_assign(this->member(), kerbal::compatibility::move(arg).member());
					return *this;
				}

#		endif

		};


		template <typename T, std::size_t I, std::size_t N>
		class member_compress_helper<T[N], I>
		{
			public:
				T _K_member[N];

			public:
				typedef kerbal::type_traits::false_type IS_COMPRESSED;

				typedef T value_type[N];
				typedef typename kerbal::type_traits::add_lvalue_reference<value_type>::type			reference;
				typedef typename kerbal::type_traits::add_const_lvalue_reference<value_type>::type		const_reference;

#		if __cplusplus >= 201103L
				typedef typename kerbal::type_traits::add_rvalue_reference<value_type>::type			rvalue_reference;
				typedef typename kerbal::type_traits::add_const_rvalue_reference<value_type>::type		const_rvalue_reference;
#		endif

			public:

#		if __cplusplus >= 201103L

				member_compress_helper() = default;

#		else

				member_compress_helper()
				{
				}

#		endif


				KERBAL_CONSTEXPR
				explicit member_compress_helper(kerbal::utility::in_place_t in_place)
						KERBAL_CONDITIONAL_NOEXCEPT(
								(std::is_nothrow_default_constructible<T>::value)
						)
				{
				}


#		if __cplusplus >= 201103L

			private:

				template <std::size_t ... I2, typename U>
				KERBAL_CONSTEXPR
				explicit member_compress_helper(kerbal::utility::in_place_t, kerbal::utility::index_sequence<I2...>, const U (&src)[N])
						KERBAL_CONDITIONAL_NOEXCEPT(
								(std::is_nothrow_constructible<T, const U &>::value)
						) :
						_K_member{src[I2]...}
				{
				}

			public:

				template <typename U>
				KERBAL_CONSTEXPR
				explicit member_compress_helper(kerbal::utility::in_place_t in_place, const U (&src)[N])
						KERBAL_CONDITIONAL_NOEXCEPT(
								(std::is_nothrow_constructible<T, const U &>::value)
						) :
						member_compress_helper(in_place, kerbal::utility::make_index_sequence<N>(), src)
				{
				}

#		else

				template <typename U>
				explicit member_compress_helper(kerbal::utility::in_place_t in_place, const U (&src)[N])
				{
					kerbal::algorithm::copy(src + 0, src + N, this->_K_member + 0);
				}

#		endif


#		if __cplusplus >= 201103L

			private:

				template <std::size_t ... I2, typename U>
				KERBAL_CONSTEXPR
				explicit member_compress_helper(kerbal::utility::in_place_t, kerbal::utility::index_sequence<I2...>, U (&&src)[N])
						KERBAL_CONDITIONAL_NOEXCEPT(
								(std::is_nothrow_constructible<T, U &&>::value)
						) :
						_K_member{kerbal::compatibility::move(src[I2])...}
				{
				}

			public:

				template <typename U>
				KERBAL_CONSTEXPR
				explicit member_compress_helper(kerbal::utility::in_place_t in_place, U (&&src)[N])
						KERBAL_CONDITIONAL_NOEXCEPT(
								(std::is_nothrow_constructible<T, U &&>::value)
						) :
						member_compress_helper(in_place, kerbal::utility::make_index_sequence<N>(), kerbal::compatibility::move(src))
				{
				}

#		endif


#		if __cplusplus >= 201103L

				template <typename U>
				KERBAL_CONSTEXPR
				explicit member_compress_helper(kerbal::utility::in_place_t, std::initializer_list<U> ilist)
						KERBAL_CONDITIONAL_NOEXCEPT(
								(std::is_nothrow_constructible<T, const U &>::value)
						) :
						_K_member{ilist}
				{
				}

#		else

				template <typename U>
				explicit member_compress_helper(kerbal::utility::in_place_t, const kerbal::assign::assign_list<U> & ilist)
				{
					kerbal::algorithm::copy(ilist.cbegin(), ilist.cend(), this->_K_member + 0);
				}

#		endif


#		if __cplusplus >= 201103L

			private:

				template <std::size_t ... I2, typename U, std::size_t J>
				KERBAL_CONSTEXPR
				explicit member_compress_helper(kerbal::utility::in_place_t, kerbal::utility::index_sequence<I2...>, const kerbal::utility::member_compress_helper<U, J> & src)
						: _K_member{src.member()[I2]...}
				{
				}

			public:

				template <typename U, std::size_t J>
				KERBAL_CONSTEXPR
				explicit member_compress_helper(const kerbal::utility::member_compress_helper<U, J> & src)
						: member_compress_helper(
							kerbal::utility::in_place_t(),
							kerbal::utility::make_index_sequence<N>(),
							src
						)
				{
				}

#		else

				template <typename U, std::size_t J>
				KERBAL_CONSTEXPR
				explicit member_compress_helper(const kerbal::utility::member_compress_helper<U, J> & src)
				{
					kerbal::algorithm::copy(src.member() + 0, src.member() + N, this->_K_member + 0);
				}

#		endif


#		if __cplusplus >= 201103L

			private:

				template <std::size_t ... I2, typename U, std::size_t J>
				KERBAL_CONSTEXPR
				explicit member_compress_helper(kerbal::utility::in_place_t, kerbal::utility::index_sequence<I2...>, kerbal::utility::member_compress_helper<U, J> && src)
						: _K_member{kerbal::compatibility::move(src).member()[I2]...}
				{
				}

			public:

				template <typename U, std::size_t J>
				KERBAL_CONSTEXPR
				explicit member_compress_helper(kerbal::utility::member_compress_helper<U, J> && src)
						: member_compress_helper(
							kerbal::utility::in_place_t(),
							kerbal::utility::make_index_sequence<N>(),
							kerbal::compatibility::move(src)
						)
				{
				}

#		endif

				KERBAL_CONSTEXPR14
				reference member() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->_K_member;
				}

				KERBAL_CONSTEXPR
				const_reference member() KERBAL_CONST_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->_K_member;
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				rvalue_reference member() && KERBAL_NOEXCEPT
				{
//					return kerbal::compatibility::move(*this)._K_member; // compile failed in msvc2017
					return static_cast<rvalue_reference>(kerbal::compatibility::move(*this)._K_member);
				}

				KERBAL_CONSTEXPR
				const_rvalue_reference member() const && KERBAL_NOEXCEPT
				{
					return static_cast<const_rvalue_reference>(kerbal::compatibility::move(*this)._K_member);
				}

#		endif

		};


		template <typename T, std::size_t I>
		class member_compress_helper<T&, I>
		{
			public:
				typedef kerbal::type_traits::false_type IS_COMPRESSED;

				typedef T&																	value_type;
				typedef typename kerbal::type_traits::add_lvalue_reference<T&>::type		reference;
				typedef typename kerbal::type_traits::add_const_lvalue_reference<T&>::type	const_reference;

#		if __cplusplus >= 201103L
				typedef typename kerbal::type_traits::add_rvalue_reference<T&>::type		rvalue_reference;
				typedef typename kerbal::type_traits::add_const_rvalue_reference<T&>::type	const_rvalue_reference;
#		endif

			private:
				T & _K_member;

			public:

				KERBAL_CONSTEXPR14
				explicit member_compress_helper(kerbal::utility::in_place_t, reference arg0) KERBAL_NOEXCEPT:
						_K_member(arg0)
				{
				}

#		if __cplusplus >= 201103L

				explicit member_compress_helper(const member_compress_helper & arg) = default;

#		endif

				template <std::size_t J>
				KERBAL_CONSTEXPR14
				explicit member_compress_helper(const member_compress_helper<T, J> & arg) KERBAL_NOEXCEPT:
						_K_member(arg.member())
				{
				}

				template <std::size_t J>
				KERBAL_CONSTEXPR14
				explicit member_compress_helper(const member_compress_helper<T&, J> & arg) KERBAL_NOEXCEPT:
						_K_member(arg.member())
				{
				}

				KERBAL_CONSTEXPR14
				void assign(T & arg)
				{
					kerbal::operators::generic_assign(this->member(), arg);
				}

				KERBAL_CONSTEXPR14
				member_compress_helper& operator=(const member_compress_helper & arg)
						KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(kerbal::operators::generic_assign(
										kerbal::utility::declthis<member_compress_helper>()->member(),
										arg.member()
								))
						)
				{
					kerbal::operators::generic_assign(this->member(), arg.member());
					return *this;
				}

				template <typename U, std::size_t J>
				KERBAL_CONSTEXPR14
				member_compress_helper& operator=(const member_compress_helper<U, J> & arg)
						KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(kerbal::operators::generic_assign(
										kerbal::utility::declthis<member_compress_helper>()->member(),
										arg.member()
								))
						)
				{
					kerbal::operators::generic_assign(this->member(), arg.member());
					return *this;
				}

				KERBAL_CONSTEXPR14
				reference member() const KERBAL_NOEXCEPT
				{
					return this->_K_member;
				}

		};

	} // namespace utility

} // namespace kerbal

#endif // KERBAL_UTILITY_MEMBER_COMPRESS_HELPER_HPP
