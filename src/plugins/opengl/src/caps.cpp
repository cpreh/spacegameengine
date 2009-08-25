/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../caps.hpp"
#include "../common.hpp"
#include "../get_string.hpp"
#include "../get_int.hpp"
#include "../glsl/init.hpp"
#include <sge/renderer/caps.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/text.hpp>

sge::opengl::caps_auto_ptr
sge::opengl::create_caps()
{
	GLint const max_texture_size(
		get_int(
			GL_MAX_TEXTURE_SIZE
		)
	);

	return caps_auto_ptr(
		new renderer::caps(
			0,
			get_string(
				GL_VENDOR
			),
			get_string(
				GL_RENDERER
			)
			+ SGE_TEXT(' ')
			+ get_string(
				GL_VERSION
			),
			renderer::dim_type(
				max_texture_size,
				max_texture_size
			),
			GL_TEXTURE_MAX_ANISOTROPY_EXT,
			glGenFramebuffersEXT,
			glsl::is_supported(),
			sge::image::color::format::rgba8 // TODO: use bgra8 for nvidia instead!
		)
	);
}
