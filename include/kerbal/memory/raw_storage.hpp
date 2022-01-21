/**
 * @file       raw_storage.hpp
 * @brief
 * @date       2019-4-19
 * @author     peter
 * @copyright
 *      peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_MEMORY_RAW_STORAGE_HPP
#define KERBAL_MEMORY_RAW_STORAGE_HPP

#include <kerbal/compatibility/alignof.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/method_overload_tag.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/memory/uninitialized.hpp>
#include <kerbal/memory/uninitialized_using_allocator.hpp>
#include <kerbal/type_traits/aligned_storage.hpp>
#include <kerbal/type_traits/array_traits.hpp>
#include <kerbal/utility/declval.hpp>
#include <kerbal/utility/in_place.hpp>
#include <kerbal/utility/noncopyable.hpp>

#if __cplusplus < 201103L
#	include <kerbal/macro/macro_concat.hpp>
#	include <kerbal/macro/ppexpand.hpp>
#endif

#if __cplusplus >= 201103L
#	include <kerbal/type_traits/conditional.hpp>
#	include <kerbal/utility/forward.hpp>
#endif

#if __cplusplus >= 201103L
#	include <type_traits>
#else
#	include <kerbal/type_traits/fundamental_deduction.hpp>
#	include <kerbal/type_traits/member_pointer_deduction.hpp>
#	include <kerbal/type_traits/pointer_deduction.hpp>
#endif


namespace kerbal
{

	namespace memory
	{

#	if __cplusplus < 201103L

		template <typename T>
		struct is_trivial_stored_type;

#	if __cplusplus >= 201103L

		template <typename T>
		struct is_trivial_stored_type:
				kerbal::type_traits::bool_constant<
					std::is_trivially_default_constructible<typename kerbal::type_traits::remove_all_extents<T>::type>::value &&
					std::is_trivially_destructible<typename kerbal::type_traits::remove_all_extents<T>::type>::value
				>
		{
		};

#	else

		template <typename T>
		struct is_trivial_stored_type:
				kerbal::type_traits::bool_constant<
					kerbal::type_traits::is_fundamental<typename kerbal::type_traits::remove_all_extents<T>::type>::value ||
					kerbal::type_traits::is_member_pointer<typename kerbal::type_traits::remove_all_extents<T>::type>::value ||
					kerbal::type_traits::is_pointer<typename kerbal::type_traits::remove_all_extents<T>::type>::value
				>
		{
		};

#	endif



		template <typename T, bool is_trivally_stored = is_trivial_stored_type<T>::value>
		class _K_rawst_base;

		template <typename T>
		class _K_rawst_base<T, true>:
				private kerbal::utility::noncopyable
		{
			protected:
				typedef T						value_type;
				typedef const value_type		const_type;
				typedef value_type&				reference;
				typedef const value_type&		const_reference;
				typedef value_type*				pointer;
				typedef const value_type*		const_pointer;

#		if __cplusplus >= 201103L
				typedef value_type&&			rvalue_reference;
				typedef const value_type&&		const_rvalue_reference;
#		endif

				typedef value_type				storage_type;

				storage_type _K_storage;

			protected:

#		if __cplusplus < 201103L
				_K_rawst_base() KERBAL_NOEXCEPT {}
#		else
				_K_rawst_base() = default;
#		endif

#			define EMPTY
#			define REMAINF(exp) exp
#			define LEFT_JOIN_COMMA(exp) , exp
#			define THEAD_NOT_EMPTY(exp) template <exp>
#			define TARGS_DECL(i) KERBAL_MACRO_CONCAT(typename Arg, i)
#			define ARGS_DECL(i) KERBAL_MACRO_CONCAT(const Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#			define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#			define FBODY(i) \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
				explicit _K_rawst_base(kerbal::utility::in_place_t KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) : \
						_K_storage(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_USE, i)) \
				{ \
				}

				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#			undef EMPTY
#			undef REMAINF
#			undef LEFT_JOIN_COMMA
#			undef THEAD_NOT_EMPTY
#			undef TARGS_DECL
#			undef ARGS_DECL
#			undef ARGS_USE
#			undef FBODY

			public:

				KERBAL_CONSTEXPR14 // note: mustn't be constexpr11 otherwise the compile can't distinguish this method with the const version
				reference raw_value() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->_K_storage;
				}

				KERBAL_CONSTEXPR14
				const_reference raw_value() const KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->_K_storage;
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				rvalue_reference raw_value() && noexcept
				{
					return static_cast<rvalue_reference>(this->_K_storage);
				}

				KERBAL_CONSTEXPR14
				const_rvalue_reference raw_value() const && noexcept
				{
					return static_cast<const_rvalue_reference>(this->_K_storage);
				}

#		endif

				KERBAL_CONSTEXPR14
				pointer raw_pointer() KERBAL_NOEXCEPT
				{
					return &(this->_K_storage);
				}

				KERBAL_CONSTEXPR14
				const_pointer raw_pointer() const KERBAL_NOEXCEPT
				{
					return &(this->_K_storage);
				}

				KERBAL_CONSTEXPR14
				void destroy() KERBAL_NOEXCEPT
				{
				}

		};

		template <typename T>
		class _K_rawst_base<T, false>:
				private kerbal::utility::noncopyable
		{
			protected:
				typedef T						value_type;
				typedef const value_type		const_type;
				typedef value_type&				reference;
				typedef const value_type&		const_reference;
				typedef value_type*				pointer;
				typedef const value_type*		const_pointer;

#		if __cplusplus >= 201103L
				typedef value_type&&			rvalue_reference;
				typedef const value_type&&		const_rvalue_reference;
#		endif

				typedef
					typename kerbal::type_traits::aligned_storage<sizeof(value_type), KERBAL_ALIGNOF(value_type)>::type
				storage_type;

				storage_type _K_storage;

			protected:

#		if __cplusplus < 201103L
				_K_rawst_base() KERBAL_NOEXCEPT {}
#		else
				_K_rawst_base() = default;
#		endif

#			define EMPTY
#			define LEFT_JOIN_COMMA(exp) , exp
#			define THEAD_NOT_EMPTY(exp) template <exp>
#			define TARGS_DECL(i) KERBAL_MACRO_CONCAT(typename Arg, i)
#			define ARGS_DECL(i) KERBAL_MACRO_CONCAT(const Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#			define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#			define FBODY(i) \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
				explicit _K_rawst_base(kerbal::utility::in_place_t KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
				{ \
					kerbal::memory::construct_at(this->raw_pointer() KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
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

			public:

				reference raw_value() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return *this->raw_pointer();
				}

				const_reference raw_value() const KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return *this->raw_pointer();
				}

#		if __cplusplus >= 201103L

				rvalue_reference raw_value() && noexcept
				{
					return static_cast<rvalue_reference>(*this->raw_pointer());
				}

				const_rvalue_reference raw_value() const && noexcept
				{
					return static_cast<const_rvalue_reference>(*this->raw_pointer());
				}

#		endif

				pointer raw_pointer() KERBAL_NOEXCEPT
				{
					return reinterpret_cast<pointer>(&(this->_K_storage));
				}

				const_pointer raw_pointer() const KERBAL_NOEXCEPT
				{
					return reinterpret_cast<const_pointer>(&(this->_K_storage));
				}

				void destroy() KERBAL_NOEXCEPT
				{
					kerbal::memory::destroy_at(this->raw_pointer());
				}

		};


#	else

		template <typename T>
		struct rawst_base_selector:
				kerbal::type_traits::conditional<
					!std::is_trivially_destructible<typename kerbal::type_traits::remove_all_extents<T>::type>::value,
					kerbal::type_traits::integral_constant<int, 0>,
					typename kerbal::type_traits::conditional<
						std::is_trivially_default_constructible<typename kerbal::type_traits::remove_all_extents<T>::type>::value,
						kerbal::type_traits::integral_constant<int, 1>,
						kerbal::type_traits::integral_constant<int, 2>
					>::type
				>::type
		{
		};


		template <typename T, int = rawst_base_selector<T>::value>
		class _K_rawst_base;

		template <typename T>
		class _K_rawst_base<T, 0>:
				private kerbal::utility::noncopyable
		{
			protected:
				typedef T						value_type;
				typedef const value_type		const_type;
				typedef value_type&				reference;
				typedef const value_type&		const_reference;
				typedef value_type*				pointer;
				typedef const value_type*		const_pointer;

#		if __cplusplus >= 201103L
				typedef value_type&&			rvalue_reference;
				typedef const value_type&&		const_rvalue_reference;
#		endif

				typedef union storage_type
				{
						value_type _K_val;

						KERBAL_CONSTEXPR20
						storage_type()
						{
						}

						template <typename ... Args>
						KERBAL_CONSTEXPR20
						explicit storage_type(kerbal::utility::in_place_t, Args&& ... args) :
								_K_val(kerbal::utility::forward<Args>(args)...)
						{
						}

						KERBAL_CONSTEXPR20
						~storage_type()
						{
						}

				} storage_type;

				storage_type _K_storage;

			public:

				_K_rawst_base() = default;

				template <typename ... Args>
				KERBAL_CONSTEXPR20
				explicit _K_rawst_base(kerbal::utility::in_place_t in_place, Args&& ... args) :
					_K_storage(in_place, kerbal::utility::forward<Args>(args)...)
				{
				}

			public:

				KERBAL_CONSTEXPR20
				reference raw_value() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->_K_storage._K_val;
				}

				KERBAL_CONSTEXPR20
				const_reference raw_value() const KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->_K_storage._K_val;
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				rvalue_reference raw_value() && noexcept
				{
					return static_cast<rvalue_reference>(this->_K_storage._K_val);
				}

				KERBAL_CONSTEXPR20
				const_rvalue_reference raw_value() const && noexcept
				{
					return static_cast<const_rvalue_reference>(this->_K_storage._K_val);
				}

#		endif

				KERBAL_CONSTEXPR20
				pointer raw_pointer() KERBAL_NOEXCEPT
				{
					return &(this->_K_storage._K_val);
				}

				KERBAL_CONSTEXPR20
				const_pointer raw_pointer() const KERBAL_NOEXCEPT
				{
					return &(this->_K_storage._K_val);
				}

				KERBAL_CONSTEXPR20
				void destroy() KERBAL_NOEXCEPT
				{
					kerbal::memory::destroy_at(this->raw_pointer());
				}

		};

		template <typename T>
		class _K_rawst_base<T, 1>:
				private kerbal::utility::noncopyable
		{
			protected:
				typedef T						value_type;
				typedef const value_type		const_type;
				typedef value_type&				reference;
				typedef const value_type&		const_reference;
				typedef value_type*				pointer;
				typedef const value_type*		const_pointer;

#		if __cplusplus >= 201103L
				typedef value_type&&			rvalue_reference;
				typedef const value_type&&		const_rvalue_reference;
#		endif

				typedef union storage_type
				{
						value_type _K_val;

						KERBAL_CONSTEXPR
						storage_type() :
								_K_val()
						{
						}

						template <typename ... Args>
						KERBAL_CONSTEXPR
						explicit storage_type(kerbal::utility::in_place_t, Args&& ... args) :
								_K_val(kerbal::utility::forward<Args>(args)...)
						{
						}

				} storage_type;

				storage_type _K_storage;

			public:

				_K_rawst_base() = default;

				template <typename ... Args>
				KERBAL_CONSTEXPR
				explicit _K_rawst_base(kerbal::utility::in_place_t in_place, Args&& ... args) :
					_K_storage(in_place, kerbal::utility::forward<Args>(args)...)
				{
				}

			public:

				KERBAL_CONSTEXPR14
				reference raw_value() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->_K_storage._K_val;
				}

				KERBAL_CONSTEXPR
				const_reference raw_value() const KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->_K_storage._K_val;
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				rvalue_reference raw_value() && noexcept
				{
					return static_cast<rvalue_reference>(this->_K_storage._K_val);
				}

				KERBAL_CONSTEXPR
				const_rvalue_reference raw_value() const && noexcept
				{
					return static_cast<const_rvalue_reference>(this->_K_storage._K_val);
				}

#		endif

				KERBAL_CONSTEXPR14
				pointer raw_pointer() KERBAL_NOEXCEPT
				{
					return &(this->_K_storage._K_val);
				}

				KERBAL_CONSTEXPR
				const_pointer raw_pointer() const KERBAL_NOEXCEPT
				{
					return &(this->_K_storage._K_val);
				}

				KERBAL_CONSTEXPR14
				void destroy() KERBAL_NOEXCEPT
				{
				}

		};

		template <typename T>
		class _K_rawst_base<T, 2>:
				private kerbal::utility::noncopyable
		{
			protected:
				typedef T						value_type;
				typedef const value_type		const_type;
				typedef value_type&				reference;
				typedef const value_type&		const_reference;
				typedef value_type*				pointer;
				typedef const value_type*		const_pointer;

#		if __cplusplus >= 201103L
				typedef value_type&&			rvalue_reference;
				typedef const value_type&&		const_rvalue_reference;
#		endif

				struct empty {};

				typedef union storage_type
				{
						value_type _K_val;
						empty _K_empty;

						KERBAL_CONSTEXPR
						storage_type() :
								_K_empty()
						{
						}

						template <typename ... Args>
						KERBAL_CONSTEXPR
						explicit storage_type(kerbal::utility::in_place_t, Args&& ... args) :
								_K_val(kerbal::utility::forward<Args>(args)...)
						{
						}

				} storage_type;

				storage_type _K_storage;

			public:

				_K_rawst_base() = default;

				template <typename ... Args>
				KERBAL_CONSTEXPR
				explicit _K_rawst_base(kerbal::utility::in_place_t in_place, Args&& ... args) :
					_K_storage(in_place, kerbal::utility::forward<Args>(args)...)
				{
				}

			public:

				KERBAL_CONSTEXPR14
				reference raw_value() KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->_K_storage._K_val;
				}

				KERBAL_CONSTEXPR
				const_reference raw_value() const KERBAL_REFERENCE_OVERLOAD_TAG KERBAL_NOEXCEPT
				{
					return this->_K_storage._K_val;
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				rvalue_reference raw_value() && noexcept
				{
					return static_cast<rvalue_reference>(this->_K_storage._K_val);
				}

				KERBAL_CONSTEXPR
				const_rvalue_reference raw_value() const && noexcept
				{
					return static_cast<const_rvalue_reference>(this->_K_storage._K_val);
				}

#		endif

				KERBAL_CONSTEXPR14
				pointer raw_pointer() KERBAL_NOEXCEPT
				{
					return &(this->_K_storage._K_val);
				}

				KERBAL_CONSTEXPR
				const_pointer raw_pointer() const KERBAL_NOEXCEPT
				{
					return &(this->_K_storage._K_val);
				}

				KERBAL_CONSTEXPR14
				void destroy() KERBAL_NOEXCEPT
				{
				}

		};

#	endif



		template <typename T>
		class _K_rawst_agent;

		template <typename T>
		class _K_rawst_agent:
				public kerbal::memory::_K_rawst_base<T>
		{
			private:
				typedef _K_rawst_agent this_type;
				typedef kerbal::memory::_K_rawst_base<T> super;

			protected:
				typedef typename super::value_type					value_type;
				typedef typename super::const_type					const_type;
				typedef typename super::reference					reference;
				typedef typename super::const_reference				const_reference;
				typedef typename super::pointer						pointer;
				typedef typename super::const_pointer				const_pointer;

#		if __cplusplus >= 201103L
				typedef typename super::rvalue_reference			rvalue_reference;
				typedef typename super::const_rvalue_reference		const_rvalue_reference;
#		endif

			protected:

#		if __cplusplus < 201103L

				_K_rawst_agent() KERBAL_NOEXCEPT {}

#			define EMPTY
#			define LEFT_JOIN_COMMA(exp) , exp
#			define THEAD_NOT_EMPTY(exp) template <exp>
#			define TARGS_DECL(i) KERBAL_MACRO_CONCAT(typename Arg, i)
#			define ARGS_DECL(i) KERBAL_MACRO_CONCAT(const Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#			define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#			define FBODY(i) \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
				explicit _K_rawst_agent(kerbal::utility::in_place_t in_place KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) : \
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
				using super::super;
#		endif

			public:

#		if __cplusplus < 201103L

#			define EMPTY
#			define REMAINF(exp) exp
#			define LEFT_JOIN_COMMA(exp) , exp
#			define THEAD_NOT_EMPTY(exp) template <exp>
#			define TARGS_DECL(i) KERBAL_MACRO_CONCAT(typename Arg, i)
#			define ARGS_DECL(i) KERBAL_MACRO_CONCAT(const Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#			define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#			define FBODY(i) \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
				void construct(KERBAL_OPT_PPEXPAND_WITH_COMMA_N(REMAINF, EMPTY, ARGS_DECL, i)) \
				{ \
					kerbal::memory::construct_at(this->raw_pointer() KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
				}

				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#			undef EMPTY
#			undef REMAINF
#			undef LEFT_JOIN_COMMA
#			undef THEAD_NOT_EMPTY
#			undef TARGS_DECL
#			undef ARGS_DECL
#			undef ARGS_USE
#			undef FBODY

#		else

				template <typename ... Args>
				KERBAL_CONSTEXPR14
				void construct(Args&& ... args)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(
								kerbal::memory::construct_at(
									kerbal::utility::declthis<this_type>()->raw_pointer(),
									kerbal::utility::forward<Args>(args)...
								)
							)
						)
				{
					kerbal::memory::construct_at(this->raw_pointer(), kerbal::utility::forward<Args>(args)...);
				}

#		endif


#		if __cplusplus < 201103L

#			define EMPTY
#			define LEFT_JOIN_COMMA(exp) , exp
#			define TARGS_DECL(i) KERBAL_MACRO_CONCAT(typename Arg, i)
#			define ARGS_DECL(i) KERBAL_MACRO_CONCAT(const Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#			define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#			define FBODY(i) \
				template <typename Alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, TARGS_DECL, i)> \
				void construct_using_allocator(Alloc & alloc KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
				{ \
					kerbal::memory::construct_at_using_allocator(alloc, this->raw_pointer() KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)); \
				}

				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#			undef EMPTY
#			undef LEFT_JOIN_COMMA
#			undef TARGS_DECL
#			undef ARGS_DECL
#			undef ARGS_USE
#			undef FBODY

#		else

				template <typename Alloc, typename ... Args>
				KERBAL_CONSTEXPR14
				void construct_using_allocator(Alloc & alloc, Args&& ... args)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(
								kerbal::memory::construct_at_using_allocator(
									alloc,
									kerbal::utility::declthis<this_type>()->raw_pointer(),
									kerbal::utility::forward<Args>(args)...
								)
							)
						)
				{
					kerbal::memory::construct_at_using_allocator(alloc, this->raw_pointer(), kerbal::utility::forward<Args>(args)...);
				}

#		endif

		};


		template <typename T, size_t N>
		class _K_rawst_agent<T[N]>:
				public kerbal::memory::_K_rawst_base<T[N]>
		{
			private:
				typedef _K_rawst_agent this_type;
				typedef kerbal::memory::_K_rawst_base<T[N]> super;

			protected:
				typedef typename super::value_type					value_type;
				typedef typename super::const_type					const_type;
				typedef typename super::reference					reference;
				typedef typename super::const_reference				const_reference;
				typedef typename super::pointer						pointer;
				typedef typename super::const_pointer				const_pointer;

#		if __cplusplus >= 201103L
				typedef typename super::rvalue_reference			rvalue_reference;
				typedef typename super::const_rvalue_reference		const_rvalue_reference;
#		endif

			protected:

#		if __cplusplus < 201103L

				_K_rawst_agent() KERBAL_NOEXCEPT {}

				explicit _K_rawst_agent(kerbal::utility::in_place_t in_place) :
						super(in_place)
				{
				}

				explicit _K_rawst_agent(kerbal::utility::in_place_t in_place, const_reference src) :
						super(in_place, src)
				{
				}

				template <typename Up>
				explicit _K_rawst_agent(kerbal::utility::in_place_t in_place, const Up (&src)[N]) :
						super(in_place, src)
				{
				}

#		else
				using super::super;
#		endif

			public:

				KERBAL_CONSTEXPR14
				void construct()
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::memory::construct_at(kerbal::utility::declthis<this_type>()->raw_pointer()))
						)
				{
					kerbal::memory::construct_at(this->raw_pointer());
				}

				template <typename Alloc>
				KERBAL_CONSTEXPR14
				void construct_using_allocator(Alloc & alloc)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::memory::construct_at_using_allocator(alloc, kerbal::utility::declthis<this_type>()->raw_pointer()))
						)
				{
					kerbal::memory::construct_at_using_allocator(alloc, this->raw_pointer());
				}

				KERBAL_CONSTEXPR14
				void construct(const_reference src)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::memory::construct_at(kerbal::utility::declthis<this_type>()->raw_pointer(), src))
						)
				{
					kerbal::memory::construct_at(this->raw_pointer(), src);
				}

				template <typename Alloc>
				KERBAL_CONSTEXPR14
				void construct_using_allocator(Alloc & alloc, const_reference src)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::memory::construct_at_using_allocator(alloc, kerbal::utility::declthis<this_type>()->raw_pointer(), src))
						)
				{
					kerbal::memory::construct_at_using_allocator(alloc, this->raw_pointer(), src);
				}

				template <typename Up>
				KERBAL_CONSTEXPR14
				void construct(const Up (&src)[N])
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::memory::construct_at(kerbal::utility::declthis<this_type>()->raw_pointer(), src))
						)
				{
					kerbal::memory::construct_at(this->raw_pointer(), src);
				}

				template <typename Alloc, typename Up>
				KERBAL_CONSTEXPR14
				void construct_using_allocator(Alloc & alloc, const Up (&src)[N])
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::memory::construct_at_using_allocator(alloc, kerbal::utility::declthis<this_type>()->raw_pointer(), src))
						)
				{
					kerbal::memory::construct_at_using_allocator(alloc, this->raw_pointer(), src);
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR14
				void construct(rvalue_reference src)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::memory::construct_at(
								kerbal::utility::declthis<this_type>()->raw_pointer(),
								kerbal::compatibility::move(src)
							))
						)
				{
					kerbal::memory::construct_at(this->raw_pointer(), kerbal::compatibility::move(src));
				}

				template <typename Alloc>
				KERBAL_CONSTEXPR14
				void construct_using_allocator(Alloc & alloc, rvalue_reference src)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::memory::construct_at_using_allocator(
								alloc,
								kerbal::utility::declthis<this_type>()->raw_pointer(),
								kerbal::compatibility::move(src)
							))
						)
				{
					kerbal::memory::construct_at_using_allocator(alloc, this->raw_pointer(), kerbal::compatibility::move(src));
				}

				template <typename Up>
				KERBAL_CONSTEXPR14
				void construct(Up (&&src)[N])
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::memory::construct_at(
								kerbal::utility::declthis<this_type>()->raw_pointer(),
								kerbal::compatibility::move(src)
							))
						)
				{
					kerbal::memory::construct_at(this->raw_pointer(), kerbal::compatibility::move(src));
				}

				template <typename Alloc, typename Up>
				KERBAL_CONSTEXPR14
				void construct_using_allocator(Alloc & alloc, Up (&&src)[N])
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::memory::construct_at_using_allocator(
								alloc,
								kerbal::utility::declthis<this_type>()->raw_pointer(),
								kerbal::compatibility::move(src)
							))
						)
				{
					kerbal::memory::construct_at_using_allocator(alloc, this->raw_pointer(), kerbal::compatibility::move(src));
				}

#		endif

		};



		template <typename T>
		class raw_storage: public kerbal::memory::_K_rawst_agent<T>
		{
			private:
				typedef raw_storage this_type;
				typedef kerbal::memory::_K_rawst_agent<T> super;

			public:
				typedef typename super::value_type					value_type;
				typedef typename super::const_type					const_type;
				typedef typename super::reference					reference;
				typedef typename super::const_reference				const_reference;
				typedef typename super::pointer						pointer;
				typedef typename super::const_pointer				const_pointer;

#		if __cplusplus >= 201103L
				typedef typename super::rvalue_reference			rvalue_reference;
				typedef typename super::const_rvalue_reference		const_rvalue_reference;
#		endif

			public:

#		if __cplusplus < 201103L

				raw_storage()
				{
				}

#			define EMPTY
#			define REMAINF(exp) exp
#			define LEFT_JOIN_COMMA(exp) , exp
#			define THEAD_NOT_EMPTY(exp) template <exp>
#			define TARGS_DECL(i) KERBAL_MACRO_CONCAT(typename Arg, i)
#			define ARGS_DECL(i) KERBAL_MACRO_CONCAT(const Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#			define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#			define FBODY(i) \
				KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
				explicit raw_storage(kerbal::utility::in_place_t in_place KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) : \
						super(in_place KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)) \
				{ \
				}

				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
				KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#			undef EMPTY
#			undef REMAINF
#			undef LEFT_JOIN_COMMA
#			undef THEAD_NOT_EMPTY
#			undef TARGS_DECL
#			undef ARGS_DECL
#			undef ARGS_USE
#			undef FBODY

#		else
				using super::super;
#		endif

				KERBAL_CONSTEXPR14
				void default_construct()
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::memory::default_construct_at(kerbal::utility::declthis<this_type>()->raw_pointer()))
						)
				{
					kerbal::memory::default_construct_at(this->raw_pointer());
				}

				template <typename Alloc>
				KERBAL_CONSTEXPR14
				void destroy_using_allocator(Alloc & alloc)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(kerbal::memory::destroy_at_using_allocator(alloc, kerbal::utility::declthis<this_type>()->raw_pointer()))
						)
				{
					kerbal::memory::destroy_at_using_allocator(alloc, this->raw_pointer());
				}

		};

	} // namespace memory

} // namespace kerbal


#endif // KERBAL_MEMORY_RAW_STORAGE_HPP
