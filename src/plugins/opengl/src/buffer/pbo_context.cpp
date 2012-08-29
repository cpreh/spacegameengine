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


#include <sge/opengl/common.hpp>
#include <sge/opengl/buffer/base.hpp>
#include <sge/opengl/buffer/create.hpp>
#include <sge/opengl/buffer/make_type.hpp>
#include <sge/opengl/buffer/pbo_context.hpp>
#include <sge/opengl/buffer/type.hpp>
#include <sge/opengl/context/system/base.hpp>
#include <sge/opengl/context/system/id.hpp>
#include <sge/opengl/context/system/make_id.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wold-style-cast)

sge::opengl::buffer::pbo_context::pbo_context()
:
	sge::opengl::context::system::base(),
	impl_(
		sge::opengl::buffer::create(
			GLEW_VERSION_2_1
			||
			GLEW_ARB_pixel_buffer_object
		)
	),
	pixel_pack_buffer_type_(
		SGE_OPENGL_BUFFER_MAKE_TYPE(
			impl_->hardware_supported(),
			GLEW_VERSION_2_1,
			GL_PIXEL_PACK_BUFFER,
			GLEW_ARB_pixel_buffer_object,
			GL_PIXEL_PACK_BUFFER_ARB
		)
	),
	pixel_unpack_buffer_type_(
		SGE_OPENGL_BUFFER_MAKE_TYPE(
			impl_->hardware_supported(),
			GLEW_VERSION_2_1,
			GL_PIXEL_UNPACK_BUFFER,
			GLEW_ARB_pixel_buffer_object,
			GL_PIXEL_UNPACK_BUFFER_ARB
		)
	)
{
}

FCPPT_PP_POP_WARNING

sge::opengl::buffer::pbo_context::~pbo_context()
{
}

sge::opengl::buffer::base &
sge::opengl::buffer::pbo_context::impl()
{
	return *impl_;
}

sge::opengl::buffer::type const
sge::opengl::buffer::pbo_context::pixel_pack_buffer_type() const
{
	return pixel_pack_buffer_type_;
}

sge::opengl::buffer::type const
sge::opengl::buffer::pbo_context::pixel_unpack_buffer_type() const
{
	return pixel_unpack_buffer_type_;
}

sge::opengl::context::system::id const
sge::opengl::buffer::pbo_context::static_id(
	sge::opengl::context::system::make_id()
);
