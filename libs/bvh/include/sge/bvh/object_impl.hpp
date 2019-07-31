//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
