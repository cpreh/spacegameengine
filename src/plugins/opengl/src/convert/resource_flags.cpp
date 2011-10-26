/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/convert/resource_flags.hpp>
#include <sge/opengl/common.hpp>
#include <sge/renderer/resource_flags.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>


GLuint
sge::opengl::convert::resource_flags(
	renderer::resource_flags_field const &_flags
)
{
	return
		static_cast<
			GLuint
		>(
			(_flags & renderer::resource_flags::dynamic)
			?
				GL_DYNAMIC_DRAW
			:
				GL_STATIC_DRAW
		);
}
