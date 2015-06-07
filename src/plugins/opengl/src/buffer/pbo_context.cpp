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


#include <sge/opengl/common.hpp>
#include <sge/opengl/buffer/base.hpp>
#include <sge/opengl/buffer/context.hpp>
#include <sge/opengl/buffer/make_hardware.hpp>
#include <sge/opengl/buffer/make_software.hpp>
#include <sge/opengl/buffer/pbo_context.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/context/system/base.hpp>
#include <sge/opengl/context/system/id.hpp>
#include <sge/opengl/context/system/make_id.hpp>
#include <sge/opengl/context/system/object.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wold-style-cast)

sge::opengl::buffer::pbo_context::pbo_context(
	sge::opengl::context::system::object &_system_context
)
:
	sge::opengl::context::system::base(),
	buffers_(
		fcppt::maybe(
			sge::opengl::context::use<
				sge::opengl::buffer::context
			>(
				_system_context
			).hardware_config(),
			[]{
				return
					sge::opengl::buffer::make_software<
						buffer_array
					>();
			},
			[](
				sge::opengl::buffer::hardware_config const &_config
			)
			{
				return
					GLEW_VERSION_2_1
					?
						sge::opengl::buffer::make_hardware(
							_config,
							GL_PIXEL_PACK_BUFFER,
							GL_PIXEL_UNPACK_BUFFER
						)
					:
						GLEW_ARB_pixel_buffer_object
						?
							sge::opengl::buffer::make_hardware(
								_config,
								GL_PIXEL_PACK_BUFFER_ARB,
								GL_PIXEL_UNPACK_BUFFER_ARB
							)
						:
							sge::opengl::buffer::make_software<
								buffer_array
							>()
					;
			}
		)
	)
{
}

FCPPT_PP_POP_WARNING

sge::opengl::buffer::pbo_context::~pbo_context()
{
}

sge::opengl::buffer::base &
sge::opengl::buffer::pbo_context::pack_buffer() const
{
	return
		*buffers_[
			0
		];
}

sge::opengl::buffer::base &
sge::opengl::buffer::pbo_context::unpack_buffer() const
{
	return
		*buffers_[
			1
		];
}

sge::opengl::context::system::id const
sge::opengl::buffer::pbo_context::static_id(
	sge::opengl::context::system::make_id()
);
