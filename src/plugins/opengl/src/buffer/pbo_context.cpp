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


#include <sge/opengl/buffer/pbo_context.hpp>
#include <sge/opengl/buffer/base.hpp>
#include <sge/opengl/buffer/create.hpp>
#include <sge/opengl/buffer/make_type.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/glew/is_supported.hpp>

sge::opengl::buffer::pbo_context::pbo_context()
:
	impl_(
		opengl::buffer::create(
			glew::is_supported("GL_VERSION_2_1")
			|| glew::is_supported("GL_ARB_pixel_buffer_object")
		)
	),
	pixel_pack_buffer_type_(
		opengl::buffer::make_type(
			impl_->hardware_supported(),
			"GL_VERSION_2_1",
			GL_PIXEL_PACK_BUFFER,
			"GL_ARB_pixel_buffer_object",
			GL_PIXEL_PACK_BUFFER_ARB
		)
	),
	pixel_unpack_buffer_type_(
		opengl::buffer::make_type(
			impl_->hardware_supported(),
			"GL_VERSION_2_1",
			GL_PIXEL_UNPACK_BUFFER,
			"GL_ARB_pixel_buffer_object",
			GL_PIXEL_UNPACK_BUFFER_ARB
		)
	)
{
}

sge::opengl::buffer::pbo_context::~pbo_context()
{
}

sge::opengl::buffer::base &
sge::opengl::buffer::pbo_context::impl()
{
	return *impl_;
}

GLenum
sge::opengl::buffer::pbo_context::pixel_pack_buffer_type() const
{
	return pixel_pack_buffer_type_;
}

GLenum
sge::opengl::buffer::pbo_context::pixel_unpack_buffer_type() const
{
	return pixel_unpack_buffer_type_;
}

sge::opengl::context::id const
sge::opengl::buffer::pbo_context::static_id(
	sge::opengl::context::make_id()
);
