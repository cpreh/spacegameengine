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


#ifndef SGE_SPRITE_DETAIL_RENDER_RANGE_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_RENDER_RANGE_HPP_INCLUDED

#include <sge/renderer/context/core_fwd.hpp>
#include <sge/sprite/detail/render/inner.hpp>
#include <sge/sprite/detail/render/set_textures.hpp>
#include <sge/sprite/detail/render/unset_textures.hpp>
#include <sge/sprite/render/range_impl.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace render
{

template<
	typename Choices
>
void
range(
	sge::renderer::context::core &_render_context,
	sge::sprite::render::range<
		Choices
	> const &_range
)
{
	typedef sge::sprite::render::range<
		Choices
	> range_type;

	for(
		typename range_type::const_iterator it(
			_range.begin()
		);
		it != _range.end();
		++it
	)
	{
		sge::sprite::detail::render::set_textures(
			_render_context,
			*it
		);

		sge::sprite::detail::render::inner(
			_render_context,
			_range,
			*it
		);
	}

	sge::sprite::detail::render::unset_textures<
		Choices
	>(
		_render_context
	);
}

}
}
}
}

#endif
