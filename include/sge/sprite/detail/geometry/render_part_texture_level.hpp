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


#ifndef SGE_SPRITE_DETAIL_GEOMETRY_RENDER_PART_TEXTURE_LEVEL_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_GEOMETRY_RENDER_PART_TEXTURE_LEVEL_HPP_INCLUDED

#include <sge/renderer/texture/const_planar_ptr.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/detail/roles/texture.hpp>
#include <sge/sprite/roles/texture.hpp>
#include <sge/texture/const_part_ptr.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace geometry
{

template<
	typename RenderPart,
	typename Choices
>
class render_part_texture_level
{
	FCPPT_NONASSIGNABLE(
		render_part_texture_level
	);
public:
	typedef sge::sprite::object<
		Choices
	> object;

	render_part_texture_level(
		RenderPart &_render_part,
		object const &_object
	)
	:
		render_part_(
			_render_part
		),
		object_(
			_object
		)
	{
	}

	typedef void result_type;

	template<
		typename Level
	>
	result_type
	operator()(
		Level const &
	) const
	{
		sge::texture::const_part_ptr const part(
			object_. template get<
				sge::sprite::roles::texture<
					Level::value
				>
			>()
		);

		render_part_. template set<
			sge::sprite::detail::roles::texture<
				Level::value
			>
		>(
			part
			?
				part->texture()
			:
				sge::renderer::texture::const_planar_ptr()
		);
	}
private:
	RenderPart &render_part_;

	object const &object_;
};

}
}
}
}

#endif
