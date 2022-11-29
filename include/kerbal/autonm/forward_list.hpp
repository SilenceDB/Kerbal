/**
 * @file       forward_list.hpp
 * @brief
 * @date       2021-01-27
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_AUTONM_FORWARD_LIST_HPP
#define KERBAL_AUTONM_FORWARD_LIST_HPP

#include <kerbal/container/detail/container_rebind_allocator_overload.hpp>
#include <kerbal/container/detail/single_list_base/single_list_node.hpp>
#include <kerbal/container/detail/forward_list_base/forward_list_iterator.hpp>
#include <kerbal/container/detail/forward_list_base.hpp>

#include <kerbal/compare/sequence_compare.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/compatibility/move.hpp>
#include <kerbal/compatibility/noexcept.hpp>
#include <kerbal/utility/declval.hpp>
#include <kerbal/utility/noncopyable.hpp>

#if __cplusplus >= 201103L
#	include <kerbal/utility/forward.hpp>
#endif


namespace kerbal
{

	namespace autonm
	{

		namespace detail
		{

			template <typename Tp>
			class autonm_sl_node :
					public kerbal::container::detail::sl_node<Tp>
			{
				private:
					typedef kerbal::container::detail::sl_node<Tp> super;

				public:
					KERBAL_CONSTEXPR
					autonm_sl_node() :
							super(kerbal::utility::in_place_t())
					{
					}


#		if __cplusplus >= 201103L

					template <typename ... Args>
					KERBAL_CONSTEXPR
					explicit autonm_sl_node(kerbal::utility::in_place_t in_place, Args&& ... args)
							: super(in_place, kerbal::utility::forward<Args>(args)...)
					{
					}

#		else

#				define EMPTY
#				define LEFT_JOIN_COMMA(exp) , exp
#				define THEAD_NOT_EMPTY(exp) template <exp>
#				define TARGS_DECL(i) typename KERBAL_MACRO_CONCAT(Arg, i)
#				define ARGS_DECL(i) const KERBAL_MACRO_CONCAT(Arg, i) & KERBAL_MACRO_CONCAT(arg, i)
#				define ARGS_USE(i) KERBAL_MACRO_CONCAT(arg, i)
#				define FBODY(i) \
					KERBAL_OPT_PPEXPAND_WITH_COMMA_N(THEAD_NOT_EMPTY, EMPTY, TARGS_DECL, i) \
					explicit autonm_sl_node(kerbal::utility::in_place_t in_place KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_DECL, i)) \
							: super(in_place KERBAL_OPT_PPEXPAND_WITH_COMMA_N(LEFT_JOIN_COMMA, EMPTY, ARGS_USE, i)) \
					{ \
					}

					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 0)
					KERBAL_PPEXPAND_N(FBODY, KERBAL_PPEXPAND_EMPTY_SEPARATOR, 20)

#				undef EMPTY
#				undef LEFT_JOIN_COMMA
#				undef THEAD_NOT_EMPTY
#				undef TARGS_DECL
#				undef ARGS_DECL
#				undef ARGS_USE
#				undef FBODY

#		endif

			};

			template <typename Tp, typename SemiAllocator>
			struct fl_typedef_helper
			{
					typedef kerbal::autonm::detail::autonm_sl_node<Tp>										auto_node;
					typedef SemiAllocator																	semi_allocator_type;
					typedef kerbal::container::detail::container_rebind_allocator_overload<
						semi_allocator_type, auto_node
					>																						fl_semi_allocator_overload;
			};

		} // namespace detail

		template <typename Tp, typename SemiAllocator>
		class forward_list :
				protected kerbal::autonm::detail::fl_typedef_helper<Tp, SemiAllocator>::fl_semi_allocator_overload,
				protected kerbal::container::detail::fl_allocator_unrelated<Tp>,
				private kerbal::utility::noncopyable
		{
			private:
				typedef kerbal::autonm::detail::fl_typedef_helper<Tp, SemiAllocator>	fl_typedef_helper;
				typedef kerbal::container::detail::fl_type_unrelated					fl_type_unrelated;
				typedef typename fl_typedef_helper::fl_semi_allocator_overload			fl_semi_allocator_overload;
				typedef kerbal::container::detail::fl_allocator_unrelated<Tp>			fl_allocator_unrelated;

			public:
				typedef typename fl_typedef_helper::auto_node				auto_node;

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

				typedef typename fl_allocator_unrelated::iterator					iterator;
				typedef typename fl_allocator_unrelated::const_iterator 			const_iterator;

			public:
				typedef SemiAllocator										semi_allocator_type;

			private:
				typedef typename fl_semi_allocator_overload::rebind_allocator_type	 		node_semi_allocator_type;
				typedef typename fl_semi_allocator_overload::rebind_allocator_traits		node_semi_allocator_traits;

			private:
				KERBAL_CONSTEXPR14
				node_semi_allocator_type & semi_alloc() KERBAL_NOEXCEPT
				{
					return this->fl_semi_allocator_overload::alloc();
				}

				KERBAL_CONSTEXPR
				const node_semi_allocator_type & semi_alloc() const KERBAL_NOEXCEPT
				{
					return this->fl_semi_allocator_overload::alloc();
				}

			public:

			//===================
			// construct/copy/destroy

				KERBAL_CONSTEXPR20
				forward_list()
						KERBAL_CONDITIONAL_NOEXCEPT(
								fl_allocator_unrelated::is_nothrow_default_constrctible::value
						) :
						fl_allocator_unrelated()
				{
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				forward_list(forward_list && src)
						KERBAL_CONDITIONAL_NOEXCEPT(
								fl_allocator_unrelated::is_nothrow_move_constrctible::value
						) :
						fl_allocator_unrelated(kerbal::compatibility::move(src))
				{
				}

#		endif

				KERBAL_CONSTEXPR20
				~forward_list()
				{
					this->fl_allocator_unrelated::destroy_using_allocator(this->semi_alloc());
				}

			public:

			//===================
			// element access

				using fl_allocator_unrelated::front;

			//===================
			// iterator

				using fl_allocator_unrelated::before_begin;
				using fl_allocator_unrelated::cbefore_begin;

				using fl_allocator_unrelated::begin;
				using fl_allocator_unrelated::end;

				using fl_allocator_unrelated::cbegin;
				using fl_allocator_unrelated::cend;

				using fl_allocator_unrelated::nth;
				using fl_allocator_unrelated::index_of;

			//===================
			// capacity

				using fl_type_unrelated::empty;
				using fl_type_unrelated::size;

			//===================
			// insert

				KERBAL_CONSTEXPR20
				void push_front(auto_node & node) KERBAL_NOEXCEPT
				{
					fl_type_unrelated::_K_hook_node_after(this->basic_before_begin(), &node);
				}

				KERBAL_CONSTEXPR20
				iterator insert_after(const_iterator pos, auto_node & node) KERBAL_NOEXCEPT
				{
					fl_type_unrelated::_K_hook_node_after(pos, &node);
					return (++pos).cast_to_mutable();
				}

				template <typename ForwardIterator>
				KERBAL_CONSTEXPR20
				typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_forward_compatible_iterator<ForwardIterator>::value,
						typename forward_list<Tp, SemiAllocator>::iterator
				>::type
				insert_after(const_iterator pos, ForwardIterator first, ForwardIterator last)
				{
					if (first == last) {
						return pos.cast_to_mutable();
					}

					ForwardIterator it(first);
					ForwardIterator next(first); ++next;

					while (next != last) {
						(*it).next = &*next;
						it = next;
						++next;
					}

					fl_type_unrelated::_K_hook_node_after(pos, &*first, &*it);
					return iterator(&*it);
				}


/*
				template <typename ForwardIterator>
				KERBAL_CONSTEXPR20
				typename kerbal::type_traits::enable_if<
						kerbal::iterator::is_forward_compatible_iterator<ForwardIterator>::value,
						typename forward_list<Tp, SemiAllocator>::iterator
				>::type
				insert_after(const_iterator pos, ForwardIterator first, ForwardIterator last)
				{
					if (first == last) {
						return pos.cast_to_mutable();
					}
					do {
						fl_type_unrelated::_K_hook_node_after(pos, &*first);
						++first;
						++pos;
					} while (first != last);
					return pos.cast_to_mutable();
				}
*/

			//===================
			// erase

				KERBAL_CONSTEXPR20
				void clear()
				{
					this->fl_allocator_unrelated::clear_using_allocator(this->semi_alloc());
				}

				KERBAL_CONSTEXPR20
				iterator erase_after(const_iterator pos)
				{
					return fl_allocator_unrelated::erase_after_using_allocator(this->semi_alloc(), pos);
				}

				KERBAL_CONSTEXPR20
				iterator erase_after(const_iterator first, const_iterator last)
				{
					return fl_allocator_unrelated::erase_after_using_allocator(this->semi_alloc(), first, last);
				}

				KERBAL_CONSTEXPR20
				void pop_front()
				{
					this->fl_allocator_unrelated::pop_front_using_allocator(this->semi_alloc());
				}

			//===================
			// operation

				KERBAL_CONSTEXPR20
				void reverse_after(const_iterator first, const_iterator last) KERBAL_NOEXCEPT
				{
					fl_type_unrelated::_K_reverse_after(first, last);
				}

				KERBAL_CONSTEXPR20
				void reverse() KERBAL_NOEXCEPT
				{
					this->fl_allocator_unrelated::reverse();
				}

				template <typename BinaryPredict>
				KERBAL_CONSTEXPR20
				void merge(forward_list & other, BinaryPredict cmp)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(
								kerbal::utility::declthis<forward_list>()->fl_allocator_unrelated::_K_merge(static_cast<fl_allocator_unrelated&>(other), cmp)
							)
						)
				{
					fl_allocator_unrelated::_K_merge(static_cast<fl_allocator_unrelated&>(other), cmp);
				}

				KERBAL_CONSTEXPR20
				void merge(forward_list & other)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(
								kerbal::utility::declthis<forward_list>()->fl_allocator_unrelated::_K_merge(static_cast<fl_allocator_unrelated&>(other))
							)
						)
				{
					this->fl_allocator_unrelated::_K_merge(static_cast<fl_allocator_unrelated&>(other));
				}

				template <typename BinaryPredict>
				KERBAL_CONSTEXPR20
				void sort_after(const_iterator first, const_iterator last, BinaryPredict cmp)
				{
					fl_allocator_unrelated::_K_sort_after(first, last, cmp);
				}

				KERBAL_CONSTEXPR20
				void sort_after(const_iterator first, const_iterator last)
				{
					fl_allocator_unrelated::_K_sort_after(first, last);
				}

				template <typename BinaryPredict>
				KERBAL_CONSTEXPR20
				void sort(BinaryPredict cmp)
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(
								kerbal::utility::declthis<forward_list>()->fl_allocator_unrelated::_K_sort(cmp)
							)
						)
				{
					this->fl_allocator_unrelated::_K_sort(cmp);
				}

				KERBAL_CONSTEXPR20
				void sort()
						KERBAL_CONDITIONAL_NOEXCEPT(
							noexcept(
								kerbal::utility::declthis<forward_list>()->fl_allocator_unrelated::_K_sort()
							)
						)
				{
					this->fl_allocator_unrelated::_K_sort();
				}

				template <typename UnaryPredicate>
				KERBAL_CONSTEXPR20
				size_type remove_after_if(const_iterator first, const_iterator last, UnaryPredicate predicate)
				{
					return fl_allocator_unrelated::remove_after_if_using_allocator(this->semi_alloc(), first, last, predicate);
				}

				template <typename UnaryPredicate>
				KERBAL_CONSTEXPR20
				size_type remove_if(UnaryPredicate predicate)
				{
					return fl_allocator_unrelated::remove_if_using_allocator(this->semi_alloc(), predicate);
				}

				KERBAL_CONSTEXPR20
				size_type remove_after(const_iterator first, const_iterator last, const_reference val)
				{
					return fl_allocator_unrelated::remove_after_using_allocator(this->semi_alloc(), first, last, val);
				}

				KERBAL_CONSTEXPR20
				size_type remove(const_reference val)
				{
					return fl_allocator_unrelated::remove_using_allocator(this->semi_alloc(), val);
				}

				template <typename BinaryPredict>
				KERBAL_CONSTEXPR20
				size_type unique(const_iterator first, const_iterator last, BinaryPredict equal_to)
				{
					return fl_allocator_unrelated::unique_using_allocator(this->semi_alloc(), first, last, equal_to);
				}

				KERBAL_CONSTEXPR20
				size_type unique(const_iterator first, const_iterator last)
				{
					return fl_allocator_unrelated::unique_using_allocator(this->semi_alloc(), first, last);
				}

				template <typename BinaryPredict>
				KERBAL_CONSTEXPR20
				size_type unique(BinaryPredict equal_to)
				{
					return fl_allocator_unrelated::unique_using_allocator(this->semi_alloc(), equal_to);
				}

				KERBAL_CONSTEXPR20
				size_type unique()
				{
					return fl_allocator_unrelated::unique_using_allocator(this->semi_alloc());
				}

				KERBAL_CONSTEXPR20
				void splice_after(const_iterator pos, forward_list & other) KERBAL_NOEXCEPT
				{
					fl_type_unrelated::_K_splice_after(pos, other);
				}

				KERBAL_CONSTEXPR20
				void splice_after(const_iterator pos, forward_list & /*other*/, const_iterator opos) KERBAL_NOEXCEPT
				{
					fl_type_unrelated::_K_splice_after(pos, opos);
				}

				KERBAL_CONSTEXPR20
				void splice_after(const_iterator pos, forward_list & /*other*/, const_iterator first, const_iterator last) KERBAL_NOEXCEPT
				{
					fl_type_unrelated::_K_splice_after(pos, first, last);
				}

#		if __cplusplus >= 201103L

				KERBAL_CONSTEXPR20
				void splice_after(const_iterator pos, forward_list && other) KERBAL_NOEXCEPT
				{
					fl_type_unrelated::_K_splice_after(pos, other);
				}

#		endif

				KERBAL_CONSTEXPR20
				void swap(forward_list & with) KERBAL_NOEXCEPT
				{
					fl_semi_allocator_overload::k_swap_allocator_if_propagate(
						static_cast<fl_semi_allocator_overload&>(*this),
						static_cast<fl_semi_allocator_overload&>(with)
					);
					fl_type_unrelated ::_K_swap_type_unrelated(
						static_cast<fl_type_unrelated &>(*this),
						static_cast<fl_type_unrelated &>(with)
					);
				}

		};

		template <typename Tp, typename SemiAllocator>
		KERBAL_CONSTEXPR20
		bool operator==(const forward_list<Tp, SemiAllocator> & lhs, const forward_list<Tp, SemiAllocator> & rhs)
		{
			return kerbal::compare::sequence_equal_to(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename SemiAllocator>
		KERBAL_CONSTEXPR20
		bool operator!=(const forward_list<Tp, SemiAllocator> & lhs, const forward_list<Tp, SemiAllocator> & rhs)
		{
			return kerbal::compare::sequence_not_equal_to(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename SemiAllocator>
		KERBAL_CONSTEXPR20
		bool operator<(const forward_list<Tp, SemiAllocator> & lhs, const forward_list<Tp, SemiAllocator> & rhs)
		{
			return kerbal::compare::sequence_less(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename SemiAllocator>
		KERBAL_CONSTEXPR20
		bool operator>(const forward_list<Tp, SemiAllocator> & lhs, const forward_list<Tp, SemiAllocator> & rhs)
		{
			return kerbal::compare::sequence_greater(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename SemiAllocator>
		KERBAL_CONSTEXPR20
		bool operator<=(const forward_list<Tp, SemiAllocator> & lhs, const forward_list<Tp, SemiAllocator> & rhs)
		{
			return kerbal::compare::sequence_less_equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

		template <typename Tp, typename SemiAllocator>
		KERBAL_CONSTEXPR20
		bool operator>=(const forward_list<Tp, SemiAllocator> & lhs, const forward_list<Tp, SemiAllocator> & rhs)
		{
			return kerbal::compare::sequence_greater_equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
		}

	} // namespace autonm

	namespace algorithm
	{

		template <typename Tp, typename SemiAllocator>
		KERBAL_CONSTEXPR20
		void swap(kerbal::autonm::forward_list<Tp, SemiAllocator> & a, kerbal::autonm::forward_list<Tp, SemiAllocator> & b)
				KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
		{
			a.swap(b);
		}

	} // namespace algorithm

} // namespace kerbal


KERBAL_NAMESPACE_STD_BEGIN

	template <typename Tp, typename SemiAllocator>
	KERBAL_CONSTEXPR20
	void swap(kerbal::autonm::forward_list<Tp, SemiAllocator> & a, kerbal::autonm::forward_list<Tp, SemiAllocator> & b)
			KERBAL_CONDITIONAL_NOEXCEPT(noexcept(a.swap(b)))
	{
		a.swap(b);
	}

KERBAL_NAMESPACE_STD_END

#endif // KERBAL_AUTONM_FORWARD_LIST_HPP