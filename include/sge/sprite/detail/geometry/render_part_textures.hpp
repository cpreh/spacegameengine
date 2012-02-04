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


#ifndef SGE_SPRITE_DETAIL_GEOMETRY_RENDER_PART_TEXTURES_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_GEOMETRY_RENDER_PART_TEXTURES_HPP_INCLUDED

#include <sge/sprite/object_fwd.hpp>
#include <sge/sprite/detail/apply_texture_levels.hpp>
#include <sge/sprite/detail/config/has_texture_levels.hpp>
#include <sge/sprite/detail/config/texture_levels.hpp>
#include <sge/sprite/detail/geometry/render_part_texture_level.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
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
	typename Choices,
	typename RenderPart
>
typename boost::enable_if<
	sge::sprite::detail::config::has_texture_levels<
		Choices
	>,
	void
>::type
render_part_textures(
	RenderPart &_render_part,
	sge::sprite::object<
		Choices
	> const &_object
)
{
	sge::sprite::detail::apply_texture_levels<
		typename sge::sprite::detail::config::texture_levels<
			Choices
		>::type
	>(
		sge::sprite::detail::geometry::render_part_texture_level<
			RenderPart,
			Choices
		>(
			_render_part,
			_object
		)
	);
}

template<
	typename Choices,
	typename RenderPart
>
typename boost::disable_if<
	sge::sprite::detail::config::has_texture_levels<
		Choices
	>,
	void
>::type
render_part_textures(
	RenderPart &,
	sge::sprite::object<
		Choices
	> const &
)
{
}

}
}
}
}

#endif
