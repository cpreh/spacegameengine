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


#ifndef SGE_BVH_OBJECT_IMPL_HPP_INCLUDED
#define SGE_BVH_OBJECT_IMPL_HPP_INCLUDED

#include <sge/bvh/construct_median_cut.hpp>
#include <sge/bvh/object_decl.hpp>

template<typename Traits>
sge::bvh::object<Traits>::object()
:
	leaves_(),
	representation_(
		sge::bvh::empty_node())
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

	typename traits::leaf_wrapper_sequence leaf_wrappers;
	for(
		typename leaf_sequence::iterator it =
			leaves_.begin();
		it != leaves_.end();
		++it)
		leaf_wrappers.push_back(
			typename traits::leaf_wrapper(
				*it));

	representation_.clear();

	sge::bvh::construct_median_cut<traits>(
		leaf_wrappers,
		representation_);
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
