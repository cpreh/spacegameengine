//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_BVH_BOUNDING_BOX_HPP_INCLUDED
#define SGE_BVH_BOUNDING_BOX_HPP_INCLUDED

#include <sge/bvh/traits/box.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/math/box/extend_bounding_box.hpp>
#include <fcppt/math/box/null.hpp>


namespace sge
{
namespace bvh
{

template<
	typename Traits
>
typename
Traits::box
bounding_box(
	typename Traits::leaf_wrapper_sequence const &_leaves
)
{
	using
	box_type
	=
	typename
	Traits::box;

	return
		fcppt::algorithm::fold(
			_leaves,
			fcppt::math::box::null<
				box_type
			>(),
			[](
				typename Traits::leaf_wrapper_sequence::value_type const &_cur,
				box_type const &_box
			)
			{
				return
					fcppt::math::box::extend_bounding_box(
						_box,
						sge::bvh::traits::box<
							typename
							Traits::leaf
						>::extract_box(
							_cur.value()
						)
					);
			}
		);
}

}
}

#endif
