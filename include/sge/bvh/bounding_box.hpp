/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
	typedef
	typename
	Traits::box
	box_type;

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
