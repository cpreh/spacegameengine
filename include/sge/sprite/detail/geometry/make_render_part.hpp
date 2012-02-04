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


#ifndef SGE_SPRITE_DETAIL_GEOMETRY_MAKE_RENDER_PART_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_GEOMETRY_MAKE_RENDER_PART_HPP_INCLUDED

#include <sge/sprite/count.hpp>
#include <sge/sprite/object_fwd.hpp>
#include <sge/sprite/buffers/slice_fwd.hpp>
#include <sge/sprite/detail/geometry/render_part_common.hpp>
#include <sge/sprite/detail/geometry/render_part_index.hpp>
#include <sge/sprite/detail/geometry/render_part_textures.hpp>
#include <sge/sprite/detail/render/range_part_object.hpp>
#include <sge/sprite/render/range_part_impl.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace geometry
{

template<
	typename Choices
>
sge::sprite::render::range_part<
	Choices
> const
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
	typedef typename sge::sprite::detail::render::range_part_object<
		Choices
	>::type range_part_object;

	range_part_object object;

	sge::sprite::detail::geometry::render_part_common(
		object,
		_slice,
		_offset,
		_count
	);

	sge::sprite::detail::geometry::render_part_textures(
		object,
		_current
	);

	sge::sprite::detail::geometry::render_part_index(
		object,
		_slice,
		_offset,
		_count
	);

	return
		sge::sprite::render::range_part<
			Choices
		>(
			object
		);
}

}
}
}
}

#endif
