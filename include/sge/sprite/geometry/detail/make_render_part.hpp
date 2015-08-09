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


#ifndef SGE_SPRITE_GEOMETRY_DETAIL_MAKE_RENDER_PART_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_DETAIL_MAKE_RENDER_PART_HPP_INCLUDED

#include <sge/sprite/count.hpp>
#include <sge/sprite/object_fwd.hpp>
#include <sge/sprite/buffers/slice_fwd.hpp>
#include <sge/sprite/geometry/detail/render_part_element.hpp>
#include <sge/sprite/detail/render/range_part_object.hpp>
#include <sge/sprite/render/range_part_impl.hpp>
#include <majutsu/init.hpp>


namespace sge
{
namespace sprite
{
namespace geometry
{
namespace detail
{

template<
	typename Choices
>
inline
sge::sprite::render::range_part<
	Choices
>
make_render_part(
	sge::sprite::buffers::slice<
		Choices
	> const &_slice,
	sge::sprite::count const _offset,
	sge::sprite::count const _count,
	sge::sprite::object<
		Choices
	> const &_current
)
{
	return
		sge::sprite::render::range_part<
			Choices
		>(
			majutsu::init<
				typename
				sge::sprite::detail::render::range_part_object<
					Choices
				>::type
			>(
				sge::sprite::geometry::detail::render_part_element<
					Choices
				>(
					_slice,
					_offset,
					_count,
					_current
				)
			)
		);
}

}
}
}
}

#endif
