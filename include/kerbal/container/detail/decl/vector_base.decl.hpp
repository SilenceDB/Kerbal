/**
 * @file       vector_base.hpp
 * @brief
 * @date       2020-08-19
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_DECL_VECTOR_BASE_DECL_HPP
#define KERBAL_CONTAINER_DETAIL_DECL_VECTOR_BASE_DECL_HPP

#include <kerbal/container/detail/vector_iterator.hpp>

#include <kerbal/algorithm/swap.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/iterator/iterator_traits.hpp>
#include <kerbal/iterator/reverse_iterator.hpp>
#include <kerbal/memory/allocator_traits.hpp>
#include <kerbal/type_traits/array_traits.hpp>
#include <kerbal/type_traits/conditional.hpp>
#include <kerbal/type_traits/enable_if.hpp>
#include <kerbal/type_traits/integral_constant.hpp>
#include <kerbal/utility/member_compress_helper.hpp>

#include <limits>

#if __cplusplus >= 201103L
#	include <type_traits>
#endif


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			template <typename Tp>
			class vector_allocator_unrelated
			{
				public:
					typedef Tp							value_type;
					typedef const value_type			const_type;
					typedef value_type&					reference;
					typedef const value_type&			const_reference;
					typedef value_type*					pointer;
					typedef const value_type*			const_pointer;

#		if __cplusplus >= 201103L
					typedef value_type&&				rvalue_reference;
					typedef const value_type&&			const_rvalue_reference;
#		endif

					typedef std::size_t					size_type;
					typedef std::ptrdiff_t				difference_type;

					typedef typename kerbal::type_traits::remove_all_extents<value_type>::type remove_all_extents_t;

					typedef kerbal::container::detail::vec_iter<value_type>		iterator;
					typedef kerbal::container::detail::vec_kiter<value_type>	const_iterator;
					typedef kerbal::iterator::reverse_iterator<iterator>		reverse_iterator;
					typedef kerbal::iterator::reverse_iterator<const_iterator>	const_reverse_iterator;

				protected:
					pointer _K_buffer;
					size_type _K_capacity;
					size_type _K_size;

				public:

				//===================
				// construct/copy/destroy

					KERBAL_CONSTEXPR
					vector_allocator_unrelated() KERBAL_NOEXCEPT;

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					vector_allocator_unrelated(Allocator & alloc, size_type count);

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					vector_allocator_unrelated(Allocator & alloc, size_type count, const_reference value);

				private:

					template <typename Allocator, typename InputIterator>
					KERBAL_CONSTEXPR20
					void _K_range_copy_cnstrct_impl(Allocator & alloc, InputIterator first, InputIterator last, std::input_iterator_tag);

					template <typename Allocator, typename ForwardIterator>
					KERBAL_CONSTEXPR20
					void _K_range_copy_cnstrct_impl(Allocator & alloc, ForwardIterator first, ForwardIterator last, std::forward_iterator_tag);

				public:

					template <typename Allocator, typename InputIterator>
					KERBAL_CONSTEXPR20
					vector_allocator_unrelated(Allocator & alloc, InputIterator first, InputIterator last);

#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR14
					vector_allocator_unrelated(vector_allocator_unrelated && src) KERBAL_NOEXCEPT;

				private:

					template <typename Allocator>
					KERBAL_CONSTEXPR14
					void _K_move_cnstrct_with_aa_allocator_equal(Allocator & alloc, vector_allocator_unrelated && src) KERBAL_NOEXCEPT;

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void _K_move_cnstrct_with_aa_allocator_not_equal(Allocator & alloc, Allocator && src_alloc, vector_allocator_unrelated && src);

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void _K_move_cnstrct_with_aa_helper(Allocator & alloc, Allocator && src_alloc, vector_allocator_unrelated && src,
														kerbal::type_traits::false_type /*is_always_equal*/);

					template <typename Allocator>
					KERBAL_CONSTEXPR14
					void _K_move_cnstrct_with_aa_helper(Allocator & alloc, Allocator && src_alloc, vector_allocator_unrelated && src,
														kerbal::type_traits::true_type /*is_always_equal*/) KERBAL_NOEXCEPT;

				public:

					template <typename Allocator>
					KERBAL_CONSTEXPR14
					vector_allocator_unrelated(Allocator & alloc, Allocator && src_alloc, vector_allocator_unrelated && src)
							KERBAL_CONDITIONAL_NOEXCEPT(
									kerbal::memory::allocator_traits<Allocator>::is_always_equal::value
							)
					;

#			endif

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void destroy_using_allocator(Allocator & alloc) KERBAL_NOEXCEPT;

				//===================
				// assign

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void assign_using_allocator(Allocator & alloc, size_type new_size, const_reference value);

				private:

					template <typename Allocator, typename InputIterator>
					KERBAL_CONSTEXPR20
					void _K_range_assign_using_allocator_impl(Allocator & alloc, InputIterator first, InputIterator last, std::input_iterator_tag);

					template <typename Allocator, typename ForwardIterator>
					KERBAL_CONSTEXPR20
					void _K_range_assign_using_allocator_impl(Allocator & alloc, ForwardIterator first, ForwardIterator last, std::forward_iterator_tag);

				public:

					template <typename Allocator, typename InputIterator>
					KERBAL_CONSTEXPR20
					typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value
					>::type
					assign_using_allocator(Allocator & alloc, InputIterator first, InputIterator last);

				private:

					typedef kerbal::type_traits::integral_constant<int, 0> CPYASS_VER_NOT_PROPAGATE;
					typedef kerbal::type_traits::integral_constant<int, 1> CPYASS_VER_PROPAGATE;
					typedef kerbal::type_traits::integral_constant<int, 2> CPYASS_VER_ALWAYS_EQUAL;

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void _K_cpyass_vec_ua_impl(Allocator & alloc, const Allocator & src_alloc, const vector_allocator_unrelated & src, CPYASS_VER_NOT_PROPAGATE);

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void _K_cpyass_vec_ua_impl(Allocator & alloc, const Allocator & src_alloc, const vector_allocator_unrelated & src, CPYASS_VER_PROPAGATE);

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void _K_cpyass_vec_ua_impl(Allocator & alloc, const Allocator & src_alloc, const vector_allocator_unrelated & src, CPYASS_VER_ALWAYS_EQUAL);

				public:

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void assign_using_allocator(Allocator & alloc, const Allocator & src_alloc, const vector_allocator_unrelated & src);

#			if __cplusplus >= 201103L

				private:

					// move assign vector using allocator, allocator is equal
					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void _K_mvass_vec_ua_ae(Allocator & alloc, vector_allocator_unrelated && src) KERBAL_NOEXCEPT;

					// move assign vector using allocator, allocator is not equal
					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void _K_mvass_vec_ua_nae(Allocator & alloc, Allocator && src_alloc, vector_allocator_unrelated && src);

					typedef kerbal::type_traits::integral_constant<int, 0> MOVASS_VER_NOT_PROPAGATE;
					typedef kerbal::type_traits::integral_constant<int, 1> MOVASS_VER_PROPAGATE;
					typedef kerbal::type_traits::integral_constant<int, 2> MOVASS_VER_ALWAYS_EQUAL;

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void _K_mvass_vec_ua_impl(Allocator & alloc, Allocator && src_alloc, vector_allocator_unrelated && src, MOVASS_VER_NOT_PROPAGATE);

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void _K_mvass_vec_ua_impl(Allocator & alloc, Allocator && src_alloc, vector_allocator_unrelated && src, MOVASS_VER_PROPAGATE);

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void _K_mvass_vec_ua_impl(Allocator & alloc, Allocator && /*src_alloc*/, vector_allocator_unrelated && src, MOVASS_VER_ALWAYS_EQUAL) KERBAL_NOEXCEPT;

				public:

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void assign_using_allocator(Allocator & alloc, Allocator && src_alloc, vector_allocator_unrelated && src) KERBAL_CONDITIONAL_NOEXCEPT(
							kerbal::memory::allocator_traits<Allocator>::is_always_equal::value
					);

#			endif

				//===================
				// element access

					KERBAL_CONSTEXPR20
					reference at(size_type index);

					KERBAL_CONSTEXPR20
					const_reference at(size_type index) const;

					KERBAL_CONSTEXPR20
					reference operator[](size_type index) KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					const_reference operator[](size_type index) const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR20
					reference front();

					KERBAL_CONSTEXPR20
					const_reference front() const;

					KERBAL_CONSTEXPR20
					reference back();

					KERBAL_CONSTEXPR20
					const_reference back() const;

					KERBAL_CONSTEXPR
					const_pointer data() const KERBAL_NOEXCEPT;

				//===================
				// iterator

					KERBAL_CONSTEXPR14
					iterator begin() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					iterator end() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR
					const_iterator begin() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR
					const_iterator end() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR
					const_iterator cbegin() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR
					const_iterator cend() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					reverse_iterator rbegin() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					reverse_iterator rend() KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					const_reverse_iterator rbegin() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					const_reverse_iterator rend() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					const_reverse_iterator crbegin() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					const_reverse_iterator crend() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR14
					iterator nth(size_type index);

					KERBAL_CONSTEXPR
					const_iterator nth(size_type index) const;

					KERBAL_CONSTEXPR
					const_iterator cnth(size_type index) const;

					KERBAL_CONSTEXPR14
					size_type index_of(iterator it);

					KERBAL_CONSTEXPR
					size_type index_of(const_iterator it) const;

				//===================
				// capacity

					KERBAL_CONSTEXPR
					bool empty() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR
					size_type size() const KERBAL_NOEXCEPT;

					KERBAL_CONSTEXPR
					size_type capacity() const KERBAL_NOEXCEPT;

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void reserve_using_allocator(Allocator & alloc, size_type new_capacity);

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void shrink_to_fit_using_allocator(Allocator & alloc);

				//===================
				// insert

				private:
					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void emplace_realloc_aux(Allocator & alloc, size_type insert_pos_index, pointer new_buffer, size_type new_capacity);

				public:

#			if __cplusplus >= 201103L

					template <typename Allocator, typename ... Args>
					KERBAL_CONSTEXPR20
					iterator emplace_using_allocator(Allocator & alloc, const_iterator pos, Args&& ...args);

#			else

					template <typename Allocator>
					iterator emplace_using_allocator(Allocator & alloc, const_iterator pos);

					template <typename Allocator, typename Arg0>
					iterator emplace_using_allocator(Allocator & alloc, const_iterator pos, const Arg0& arg0);

					template <typename Allocator, typename Arg0, typename Arg1>
					iterator emplace_using_allocator(Allocator & alloc, const_iterator pos, const Arg0& arg0, const Arg1& arg1);

					template <typename Allocator, typename Arg0, typename Arg1, typename Arg2>
					iterator emplace_using_allocator(Allocator & alloc, const_iterator pos, const Arg0& arg0, const Arg1& arg1, const Arg2& arg2);

#			endif

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					iterator insert_using_allocator(Allocator & alloc, const_iterator pos, const_reference val);

#			if __cplusplus >= 201103L

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					iterator insert_using_allocator(Allocator & alloc, const_iterator pos, rvalue_reference val);

#			endif

				private:
					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void insert_realloc_aux(Allocator & alloc, size_type insert_pos_index, size_type n, pointer new_buffer, size_type new_capacity, size_type new_size);

				public:

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					iterator insert_using_allocator(Allocator & alloc, const_iterator pos, size_type n, const_reference val);

				private:

					template <typename Allocator, typename InputIterator>
					KERBAL_CONSTEXPR20
					iterator _K_range_insert_using_allocator_impl(Allocator & alloc, const_iterator pos, InputIterator first, InputIterator last, std::input_iterator_tag);

					template <typename Allocator, typename ForwardIterator>
					KERBAL_CONSTEXPR20
					iterator _K_range_insert_using_allocator_impl(Allocator & alloc, const_iterator pos, ForwardIterator first, ForwardIterator last, std::forward_iterator_tag);

				public:
					template <typename Allocator, typename InputIterator>
					KERBAL_CONSTEXPR20
					typename kerbal::type_traits::enable_if<
							kerbal::iterator::is_input_compatible_iterator<InputIterator>::value,
							iterator
					>::type
					insert_using_allocator(Allocator & alloc, const_iterator pos, InputIterator first, InputIterator last);

				private:
					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void emplace_back_realloc_aux(Allocator & alloc, pointer new_buffer, size_type new_capacity);

				public:

#			if __cplusplus >= 201103L

					template <typename Allocator, typename ... Args>
					KERBAL_CONSTEXPR20
					reference emplace_back_using_allocator(Allocator & alloc, Args&& ...args);

#			else

					template <typename Allocator>
					reference emplace_back_using_allocator(Allocator & alloc);

					template <typename Allocator, typename Arg0>
					reference emplace_back_using_allocator(Allocator & alloc, const Arg0 & arg0);

					template <typename Allocator, typename Arg0, typename Arg1>
					reference emplace_back_using_allocator(Allocator & alloc, const Arg0 & arg0, const Arg1 & arg1);

					template <typename Allocator, typename Arg0, typename Arg1, typename Arg2>
					reference emplace_back_using_allocator(Allocator & alloc, const Arg0 & arg0, const Arg1 & arg1, const Arg2 & arg2);

#			endif

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void push_back_using_allocator(Allocator & alloc, const_reference src);

#			if __cplusplus >= 201103L

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void push_back_using_allocator(Allocator & alloc, rvalue_reference src);

#			endif

				//===================
				// erase

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					iterator erase_using_allocator(Allocator & alloc, const_iterator pos);

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					iterator erase_using_allocator(Allocator & alloc, const_iterator first, const_iterator last);

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void pop_back_using_allocator(Allocator & alloc) KERBAL_NOEXCEPT;

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void clear_using_allocator(Allocator & alloc) KERBAL_NOEXCEPT;

				//===================
				// operation

				private:
					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void resize_realloc_aux(Allocator & alloc, pointer new_buffer, size_type new_capacity, size_type new_size);

				public:
					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void resize_using_allocator(Allocator & alloc, size_type new_size);

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					void resize_using_allocator(Allocator & alloc, size_type new_size, const_reference value);

					KERBAL_CONSTEXPR14
					static void _K_swap_type_unrelated(vector_allocator_unrelated & lhs, vector_allocator_unrelated & rhs) KERBAL_NOEXCEPT;


				private:

#			if __cplusplus >= 201103L
					typedef kerbal::type_traits::integral_constant<int, 0> UIMIN_VER_MOVE;
#			endif
					typedef kerbal::type_traits::integral_constant<int, 1> UIMIN_VER_COPY;


#			if __cplusplus >= 201103L
					typedef typename kerbal::type_traits::conditional<
							std::is_nothrow_move_constructible<value_type>::value,
							UIMIN_VER_MOVE,
							UIMIN_VER_COPY
					>::type UIMIN_VER;
#			else
					typedef UIMIN_VER_COPY UIMIN_VER;
#			endif


#			if __cplusplus >= 201103L
					template <typename Allocator>
					KERBAL_CONSTEXPR20
					static void ui_move_if_noexcept_ow_copy_phase1_impl(Allocator & alloc, pointer first, pointer last, pointer to, UIMIN_VER_MOVE) KERBAL_NOEXCEPT;
#			endif

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					static void ui_move_if_noexcept_ow_copy_phase1_impl(Allocator & alloc, pointer first, pointer last, pointer to, UIMIN_VER_COPY);

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					static void ui_move_if_noexcept_ow_copy_phase1(Allocator & alloc, pointer first, pointer last, pointer to) KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(ui_move_if_noexcept_ow_copy_phase1_impl(alloc, first, last, to, UIMIN_VER()))
					);


#			if __cplusplus >= 201103L
					template <typename Allocator>
					KERBAL_CONSTEXPR20
					static void ui_move_if_noexcept_ow_copy_phase2_impl(Allocator & /*alloc*/, pointer /*first*/, pointer /*last*/, UIMIN_VER_MOVE) KERBAL_NOEXCEPT;
#			endif

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					static void ui_move_if_noexcept_ow_copy_phase2_impl(Allocator & alloc, pointer first, pointer last, UIMIN_VER_COPY) KERBAL_NOEXCEPT;

					template <typename Allocator>
					KERBAL_CONSTEXPR20
					static void ui_move_if_noexcept_ow_copy_phase2(Allocator & alloc, pointer first, pointer last) KERBAL_NOEXCEPT;

			};


			template <typename Allocator>
			class vector_allocator_overload:
					private kerbal::utility::member_compress_helper<Allocator>
			{
				private:
					typedef kerbal::utility::member_compress_helper<Allocator> super;

				protected:
					typedef Allocator allocator_type;
					typedef kerbal::memory::allocator_traits<allocator_type>		allocator_traits;

				public:

					KERBAL_CONSTEXPR
					vector_allocator_overload()
								KERBAL_CONDITIONAL_NOEXCEPT((
										std::is_nothrow_constructible<super, kerbal::utility::in_place_t>::value
								))
							: super(kerbal::utility::in_place_t())
					{
					}

					KERBAL_CONSTEXPR
					explicit
					vector_allocator_overload(const allocator_type & allocator)
								KERBAL_CONDITIONAL_NOEXCEPT((
										std::is_nothrow_constructible<super, kerbal::utility::in_place_t, const allocator_type &>::value
								))
							: super(kerbal::utility::in_place_t(), allocator)
					{
					}

#			if __cplusplus >= 201103L

					KERBAL_CONSTEXPR
					explicit
					vector_allocator_overload(allocator_type && allocator)
								KERBAL_CONDITIONAL_NOEXCEPT((
										std::is_nothrow_constructible<super, kerbal::utility::in_place_t, allocator_type &&>::value
								))
							: super(kerbal::utility::in_place_t(), kerbal::compatibility::move(allocator))
					{
					}

#			endif

					KERBAL_CONSTEXPR14
					allocator_type& alloc() KERBAL_NOEXCEPT
					{
						return super::member();
					}

					KERBAL_CONSTEXPR14
					const allocator_type& alloc() const KERBAL_NOEXCEPT
					{
						return super::member();
					}

				private:

					KERBAL_CONSTEXPR14
					static void _K_swap_allocator_if_propagate_impl(vector_allocator_overload & /*lhs*/, vector_allocator_overload & /*rhs*/,
													   kerbal::type_traits::false_type /*propagate_on_container_swap*/) KERBAL_NOEXCEPT
					{
					}

					KERBAL_CONSTEXPR14
					static void _K_swap_allocator_if_propagate_impl(vector_allocator_overload & lhs, vector_allocator_overload & rhs,
													   kerbal::type_traits::true_type /*propagate_on_container_swap*/)
							KERBAL_CONDITIONAL_NOEXCEPT(
								noexcept(kerbal::algorithm::swap(lhs.alloc(), rhs.alloc()))
							)
					{
						kerbal::algorithm::swap(lhs.alloc(), rhs.alloc());
					}

				public:

					KERBAL_CONSTEXPR14
					static void _K_swap_allocator_if_propagate(vector_allocator_overload & lhs, vector_allocator_overload & rhs)
							KERBAL_CONDITIONAL_NOEXCEPT(
									noexcept(_K_swap_allocator_if_propagate_impl(lhs, rhs, typename allocator_traits::propagate_on_container_swap()))
							)
					{
						typedef typename allocator_traits::propagate_on_container_swap propagate_on_container_swap;
						_K_swap_allocator_if_propagate_impl(lhs, rhs, propagate_on_container_swap());
					}

			};

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_DECL_VECTOR_BASE_DECL_HPP