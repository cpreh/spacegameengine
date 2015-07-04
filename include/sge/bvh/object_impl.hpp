/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_BVH_OBJECT_IMPL_HPP_INCLUDED
#define SGE_BVH_OBJECT_IMPL_HPP_INCLUDED

#include <sge/bvh/construct_median_cut.hpp>
#include <sge/bvh/object_decl.hpp>
#include <fcppt/algorithm/map.hpp>


template<typename Traits>
sge::bvh::object<Traits>::object()
:
	leaves_(),
	representation_(
		typename
		traits::node_or_leaf_variant(
			sge::bvh::empty_node()
		)
	)
{
}

template<typename Traits>
void
sge::bvh::object<Traits>::insert(
	leaf_sequence const &_leaves)
{
	leaves_.insert(
		leaves_.end(),
		_leaves.begin(),
		_leaves.end());

	representation_.clear();

	sge::bvh::construct_median_cut<
		traits
	>(
		fcppt::algorithm::map<
			typename
			traits::leaf_wrapper_sequence
		>(
			leaves_,
			[](
				typename
				leaf_sequence::value_type &_leaf
			)
			{
				return
					typename
					traits::leaf_wrapper(
						_leaf
					);
			}
		),
		representation_
	);
}

template<typename Traits>
typename sge::bvh::object<Traits>::tree_representation const &
sge::bvh::object<Traits>::representation() const
{
	return
		representation_;
}

template<typename Traits>
sge::bvh::object<Traits>::~object()
{
}

#endif
