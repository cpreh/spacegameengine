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


#ifndef SGE_OPENGL_TEXTURE_CUBE_SIDE_ARRAY_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_CUBE_SIDE_ARRAY_HPP_INCLUDED

#include <sge/opengl/texture/buffer_type.hpp>
#include <sge/renderer/texture/cube_side.hpp>
#include <fcppt/enum_size.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <cstddef>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

typedef std::array<
	sge::opengl::texture::buffer_type,
	static_cast<
		std::size_t
	>(
		fcppt::enum_size<
			sge::renderer::texture::cube_side
		>::value
	)
> cube_side_array;

}
}
}

#endif
