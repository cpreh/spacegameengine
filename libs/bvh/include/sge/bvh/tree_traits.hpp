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
