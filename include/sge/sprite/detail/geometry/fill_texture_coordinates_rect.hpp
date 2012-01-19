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


#ifndef SGE_SPRITE_DETAIL_GEOMETRY_FILL_TEXTURE_COORDINATES_RECT_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_GEOMETRY_FILL_TEXTURE_COORDINATES_RECT_HPP_INCLUDED

#include <sge/sprite/texture_coordinates.hpp>
#include <sge/sprite/detail/geometry/vector_float.hpp>
#include <sge/sprite/detail/vf/texpos.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/at.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace geometry
{

template<
	typename Level,
	typename Choices,
	typename Iterator
>
void
fill_texture_coordinates_rect(
	Iterator _iterator,
	typename sge::sprite::texture_coordinates<
		Choices
	>::type const &_rt
)
{
	typedef typename sge::sprite::detail::geometry::vector_float<
		Choices
	>::type tex_pos;

	typedef typename boost::mpl::at<
		typename sge::sprite::detail::vf::texpos<
			Choices
		>::type,
		Level
	>::type vertex_texpos;

	(*_iterator++). template set<
		vertex_texpos
	>(
		tex_pos(
			_rt.first.x(),
			_rt.first.y()
		)
	);

	(*_iterator++). template set<
		vertex_texpos
	>(
		tex_pos(
			_rt.second.x(),
			_rt.first.y()
		)
	);

	(*_iterator++). template set<
		vertex_texpos
	>(
		tex_pos(
			_rt.second.x(),
			_rt.second.y()
		)
	);

	(*_iterator++). template set<
		vertex_texpos
	>(
		tex_pos(
			_rt.first.x(),
			_rt.second.y()
		)
	);
}

}
}
}
}

#endif
