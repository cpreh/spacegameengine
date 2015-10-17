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


#ifndef SGE_BVH_TREE_TRAITS_HPP_INCLUDED
#define SGE_BVH_TREE_TRAITS_HPP_INCLUDED

#include <sge/bvh/empty_node.hpp>
#include <sge/bvh/leaf_wrapper.hpp>
#include <sge/bvh/node_wrapper.hpp>
#include <fcppt/container/tree/object.hpp>
#include <fcppt/variant/variadic.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace bvh
{

template<
	typename Node,
	typename Leaf,
	typename Box
>
struct tree_traits
{
	typedef
	Node
	node;

	typedef
	Leaf
	leaf;

	typedef
	Box
	box;

	typedef
	sge::bvh::leaf_wrapper<
		leaf
	>
	leaf_wrapper;

	typedef
	sge::bvh::node_wrapper<
		node,
		box
	>
	node_wrapper;

	typedef
	std::vector<
		leaf
	>
	leaf_sequence;

	typedef
	std::vector<
		leaf_wrapper
	>
	leaf_wrapper_sequence;

	typedef
	fcppt::variant::variadic<
		node_wrapper,
		leaf_wrapper_sequence,
		sge::bvh::empty_node
	>
	node_or_leaf_variant;

	typedef
	fcppt::container::tree::object<
		node_or_leaf_variant
	>
	tree_representation;
};

}
}

#endif
