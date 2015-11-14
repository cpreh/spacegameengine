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
#include <sge/opengl/buffer/vbo_context.hpp>
#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/context/object.hpp>
#include <sge/opengl/context/use.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wold-style-cast)

sge::opengl::buffer::vbo_context::vbo_context(
	sge::opengl::context::object &_context
)
:
	sge::opengl::context::base(),
	buffers_(
		fcppt::maybe(
			sge::opengl::context::use<
				sge::opengl::buffer::context
			>(
				_context,
				_context.info()
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
					_config.is_native().get()
					?
						sge::opengl::buffer::make_hardware(
							_config,
							GL_ELEMENT_ARRAY_BUFFER,
							GL_ARRAY_BUFFER
						)
					:
						sge::opengl::buffer::make_hardware(
							_config,
							GL_ELEMENT_ARRAY_BUFFER_ARB,
							GL_ARRAY_BUFFER_ARB
						)
					;
			}
		)
	)
{
}

FCPPT_PP_POP_WARNING

sge::opengl::buffer::vbo_context::~vbo_context()
{
}

sge::opengl::buffer::base &
sge::opengl::buffer::vbo_context::index_buffer() const
{
	return
		*std::get<
			0
		>(
			buffers_
		);
}

sge::opengl::buffer::base &
sge::opengl::buffer::vbo_context::vertex_buffer() const
{
	return
		*std::get<
			1
		>(
			buffers_
		);
}

sge::opengl::context::id const
sge::opengl::buffer::vbo_context::static_id(
	sge::opengl::context::make_id()
);
