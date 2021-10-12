/**
 * @file       single_list_base.fwd.hpp
 * @brief
 * @date       2021-10-12
 * @author     Peter
 * @copyright
 *      Peter of [ThinkSpirit Laboratory](http://thinkspirit.org/)
 *   of [Nanjing University of Information Science & Technology](http://www.nuist.edu.cn/)
 *   all rights reserved
 */

#ifndef KERBAL_CONTAINER_DETAIL_FWD_SINGLE_LIST_BASE_FWD_HPP
#define KERBAL_CONTAINER_DETAIL_FWD_SINGLE_LIST_BASE_FWD_HPP


namespace kerbal
{

	namespace container
	{

		namespace detail
		{

			class sl_type_unrelated;

			template <typename Tp>
			class sl_allocator_unrelated;

			template <typename Tp, typename Allocator>
			class sl_allocator_overload;

			class sl_node_base;

			template <typename Tp>
			class sl_node;

			class sl_iter_type_unrelated;

			class sl_kiter_type_unrelated;

			template <typename Tp>
			class sl_iter;

			template <typename Tp>
			class sl_kiter;

		} // namespace detail

	} // namespace container

} // namespace kerbal

#endif // KERBAL_CONTAINER_DETAIL_FWD_SINGLE_LIST_BASE_FWD_HPP
