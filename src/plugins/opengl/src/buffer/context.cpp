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
#include <sge/opengl/deref_fun_ptr.hpp>
#include <sge/opengl/buffer/context.hpp>
#include <sge/opengl/buffer/hardware_config.hpp>
#include <sge/opengl/buffer/optional_hardware_config.hpp>
#include <sge/opengl/convert/from_gl_bool.hpp>
#include <sge/opengl/context/system/base.hpp>
#include <sge/opengl/context/system/id.hpp>
#include <sge/opengl/context/system/make_id.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wold-style-cast)

sge::opengl::buffer::context::context()
:
	sge::opengl::context::system::base(),
	hardware_config_(
		sge::opengl::convert::from_gl_bool(
			GLEW_VERSION_1_5
		)
		?
			sge::opengl::buffer::optional_hardware_config(
				sge::opengl::buffer::hardware_config(
					sge::opengl::buffer::is_native{
						true
					},
					sge::opengl::deref_fun_ptr(
						glGenBuffers
					),
					sge::opengl::deref_fun_ptr(
						glDeleteBuffers
					),
					sge::opengl::deref_fun_ptr(
						glBindBuffer
					),
					sge::opengl::deref_fun_ptr(
						glMapBuffer
					),
					sge::opengl::deref_fun_ptr(
						glUnmapBuffer
					),
					sge::opengl::deref_fun_ptr(
						glBufferData
					),
					sge::opengl::deref_fun_ptr(
						glBufferSubData
					),
					sge::opengl::buffer::hardware_config::optional_gl_map_buffer_range(
						sge::opengl::deref_fun_ptr(
							glMapBufferRange
						)
					)
				)
			)
			:
			sge::opengl::convert::from_gl_bool(
				GLEW_ARB_vertex_buffer_object
			)
			?
				sge::opengl::buffer::optional_hardware_config(
					sge::opengl::buffer::hardware_config(
						sge::opengl::buffer::is_native{
							false
						},
						sge::opengl::deref_fun_ptr(
							glGenBuffersARB
						),
						sge::opengl::deref_fun_ptr(
							glDeleteBuffersARB
						),
						sge::opengl::deref_fun_ptr(
							glBindBufferARB
						),
						sge::opengl::deref_fun_ptr(
							glMapBufferARB
						),
						sge::opengl::deref_fun_ptr(
							glUnmapBufferARB
						),
						sge::opengl::deref_fun_ptr(
							glBufferDataARB
						),
						sge::opengl::deref_fun_ptr(
							glBufferSubDataARB
						),
						sge::opengl::buffer::hardware_config::optional_gl_map_buffer_range()
					)
				)
			:
				sge::opengl::buffer::optional_hardware_config()
	)
{
}

FCPPT_PP_POP_WARNING

sge::opengl::buffer::context::~context()
{
}

sge::opengl::buffer::optional_hardware_config const &
sge::opengl::buffer::context::hardware_config() const
{
	return
		hardware_config_;
}

sge::opengl::context::system::id const
sge::opengl::buffer::context::static_id(
	sge::opengl::context::system::make_id()
);
