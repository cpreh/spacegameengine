/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_BVH_CONSTRUCT_MEDIAN_CUT_HPP_INCLUDED
#define SGE_BVH_CONSTRUCT_MEDIAN_CUT_HPP_INCLUDED

#include <sge/bvh/bounding_box.hpp>
#include <sge/bvh/empty_node.hpp>
#include <sge/bvh/traits/box.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/box/center.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/next_prior.hpp>
#include <boost/range/algorithm/max_element.hpp>
#include <boost/range/algorithm/sort.hpp>
#include <iterator>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace bvh
{
namespace detail
{
class construct_median_cut_comparator
{
public:
	explicit
	construct_median_cut_comparator(
		fcppt::math::size_type const _axis)
	:
		axis_(
			_axis)
	{
	}

	template<typename LeafWrapper>
	bool
	operator()(
		LeafWrapper const &_left,
		LeafWrapper const &_right) const
	{
		typedef typename
		LeafWrapper::leaf
		leaf;

		return
			fcppt::math::box::center(
				sge::bvh::traits::box<leaf>::extract_box(
					_left.value()))[axis_]
			<
			fcppt::math::box::center(
				sge::bvh::traits::box<leaf>::extract_box(
					_right.value()))[axis_];
	}
private:
	fcppt::math::size_type axis_;
};
}

template<typename Traits>
void
construct_median_cut(
	typename Traits::leaf_wrapper_sequence _leaves,
	typename Traits::tree_representation &_tree)
{
	FCPPT_ASSERT_PRE(
		_tree.empty());

	if(_leaves.size() <= 1u)
	{
		_tree.value(
			typename Traits::node_or_leaf_variant(
				_leaves));
		return;
	}

	typename Traits::box const bounding_box =
		sge::bvh::bounding_box<Traits>(
			_leaves);

	typename Traits::box::dim const bounding_box_size =
		bounding_box.size();

	_tree.value(
		typename Traits::node_or_leaf_variant(
			typename Traits::node_wrapper(
				typename Traits::node(
					bounding_box),
				bounding_box)));


	boost::range::sort(
		_leaves,
		sge::bvh::detail::construct_median_cut_comparator(
			static_cast<fcppt::math::size_type>(
				std::distance(
					bounding_box_size.begin(),
					boost::range::max_element(
						bounding_box_size)))));

	_tree.push_back(
		typename Traits::node_or_leaf_variant(
			sge::bvh::empty_node()));

	_tree.push_back(
		typename Traits::node_or_leaf_variant(
			sge::bvh::empty_node()));

	sge::bvh::construct_median_cut<Traits>(
		typename Traits::leaf_wrapper_sequence(
			_leaves.begin(),
			boost::next(
				_leaves.begin(),
				static_cast<typename Traits::leaf_wrapper_sequence::difference_type>(
					_leaves.size()/2u))),
		_tree.front());

	sge::bvh::construct_median_cut<Traits>(
		typename Traits::leaf_wrapper_sequence(
			boost::next(
				_leaves.begin(),
				static_cast<typename Traits::leaf_wrapper_sequence::difference_type>(
					_leaves.size()/2u)),
			_leaves.end()),
		*boost::next(
			_tree.begin()));
}
}
}

#endif
