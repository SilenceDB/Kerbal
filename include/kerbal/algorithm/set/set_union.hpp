/**
 * @file       set_union.hpp
 * @brief
 * @date       2021-06-13
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_ALGORITHM_SET_SET_UNION_HPP
#define KERBAL_ALGORITHM_SET_SET_UNION_HPP

#include <kerbal/algorithm/modifier.hpp>
#include <kerbal/compatibility/constexpr.hpp>
#include <kerbal/operators/generic_assign.hpp>
#include <kerbal/iterator/iterator_traits.hpp>

#include <functional>


namespace kerbal
{

	namespace algorithm
	{

		template <typename InputIterator1, typename InputIterator2, typename OutputIterator, typename BinaryPredict>
		KERBAL_CONSTEXPR14
		OutputIterator set_union(InputIterator1 first1, InputIterator1 last1,
								 InputIterator2 first2, InputIterator2 last2,
								 OutputIterator d_first, BinaryPredict cmp)
		{
			while (first1 != last1) {
				if (first2 != last2) {
					if (cmp(*first2, *first1)) { // *first2 < *first1
						kerbal::operators::generic_assign(*d_first, *first2);
						++d_first;
						++first2;
					} else { // *first1 <= *first2
						bool b = static_cast<bool>(cmp(*first1, *first2));
						kerbal::operators::generic_assign(*d_first, *first1);
						++d_first;
						++first1;
						if (!b) { // *first1 == *first2
							++first2;
						}
					}
				} else {
					return kerbal::algorithm::copy(first1, last1, d_first);
				}
			}
			return kerbal::algorithm::copy(first2, last2, d_first);
		}

		template <typename InputIterator1, typename InputIterator2, typename OutputIterator>
		KERBAL_CONSTEXPR14
		OutputIterator set_union(InputIterator1 first1, InputIterator1 last1,
								 InputIterator2 first2, InputIterator2 last2,
								 OutputIterator d_first)
		{
			typedef InputIterator1 iterator1;
//			typedef InputIterator2 iterator2;
			typedef typename kerbal::iterator::iterator_traits<iterator1>::value_type value_type1;
//			typedef typename kerbal::iterator::iterator_traits<iterator2>::value_type value_type2;
			return kerbal::algorithm::set_union(first1, last1, first2, last2, d_first, std::less<value_type1>());
		}

	} // namespace algorithm

} // namespace kerbal

#endif // KERBAL_ALGORITHM_SET_SET_UNION_HPP
