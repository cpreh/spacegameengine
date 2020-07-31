//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_BVH_TREE_TRAITS_HPP_INCLUDED
#define SGE_BVH_TREE_TRAITS_HPP_INCLUDED

#include <sge/bvh/empty_node.hpp>
#include <sge/bvh/leaf_wrapper.hpp>
#include <sge/bvh/node_wrapper.hpp>
#include <fcppt/container/tree/object.hpp>
#include <fcppt/variant/object_impl.hpp>
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
	using
	node
	=
	Node;

	using
	leaf
	=
	Leaf;

	using
	box
	=
	Box;

	using
	leaf_wrapper
	=
	sge::bvh::leaf_wrapper<
		leaf
	>;

	using
	node_wrapper
	=
	sge::bvh::node_wrapper<
		node,
		box
	>;

	using
	leaf_sequence
	=
	std::vector<
		leaf
	>;

	using
	leaf_wrapper_sequence
	=
	std::vector<
		leaf_wrapper
	>;

	using
	node_or_leaf_variant
	=
	fcppt::variant::object<
		node_wrapper,
		leaf_wrapper_sequence,
		sge::bvh::empty_node
	>;

	using
	tree_representation
	=
	fcppt::container::tree::object<
		node_or_leaf_variant
	>;
};

}
}

#endif
