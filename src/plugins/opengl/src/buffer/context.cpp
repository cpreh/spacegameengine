/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/info/cast_function.hpp>
#include <sge/opengl/info/context.hpp>
#include <sge/opengl/info/extension.hpp>
#include <sge/opengl/info/extension_supported.hpp>
#include <sge/opengl/info/major_version.hpp>
#include <sge/opengl/info/minor_version.hpp>
#include <sge/opengl/info/version_at_least.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wold-style-cast)

sge::opengl::buffer::context::context(
	sge::opengl::info::context const &_info
)
:
	sge::opengl::context::base(),
	hardware_config_(
		sge::opengl::info::version_at_least(
			_info.version(),
			sge::opengl::info::major_version{
				1u
			},
			sge::opengl::info::minor_version{
				5u
			}
		)
		?
			sge::opengl::buffer::optional_hardware_config(
				sge::opengl::buffer::hardware_config(
					sge::opengl::buffer::is_native{
						true
					},
					sge::opengl::deref_fun_ptr(
						sge::opengl::info::cast_function<
							PFNGLGENBUFFERSPROC
						>(
							_info.load_function(
								"glGenBuffers"
							)
						)
					),
					sge::opengl::deref_fun_ptr(
						sge::opengl::info::cast_function<
							PFNGLDELETEBUFFERSPROC
						>(
							_info.load_function(
								"glDeleteBuffers"
							)
						)
					),
					sge::opengl::deref_fun_ptr(
						sge::opengl::info::cast_function<
							PFNGLBINDBUFFERPROC
						>(
							_info.load_function(
								"glBindBuffer"
							)
						)
					),
					sge::opengl::deref_fun_ptr(
						sge::opengl::info::cast_function<
							PFNGLMAPBUFFERPROC
						>(
							_info.load_function(
								"glMapBuffer"
							)
						)
					),
					sge::opengl::deref_fun_ptr(
						sge::opengl::info::cast_function<
							PFNGLUNMAPBUFFERPROC
						>(
							_info.load_function(
								"glUnmapBuffer"
							)
						)
					),
					sge::opengl::deref_fun_ptr(
						sge::opengl::info::cast_function<
							PFNGLBUFFERDATAPROC
						>(
							_info.load_function(
								"glBufferData"
							)
						)
					),
					sge::opengl::deref_fun_ptr(
						sge::opengl::info::cast_function<
							PFNGLBUFFERSUBDATAPROC
						>(
							_info.load_function(
								"glBufferSubData"
							)
						)
					),
					sge::opengl::buffer::hardware_config::optional_gl_map_buffer_range(
						fcppt::make_ref(
							sge::opengl::deref_fun_ptr(
								sge::opengl::info::cast_function<
									PFNGLMAPBUFFERRANGEPROC
								>(
									_info.load_function(
										"glMapBufferRange"
									)
								)
							)
						)
					)
				)
			)
		:
			sge::opengl::info::extension_supported(
				_info.extensions(),
				sge::opengl::info::extension{
					"GL_ARB_vertex_buffer_object"
				}
			)
			?
				sge::opengl::buffer::optional_hardware_config(
					sge::opengl::buffer::hardware_config(
						sge::opengl::buffer::is_native{
							false
						},
						sge::opengl::deref_fun_ptr(
							sge::opengl::info::cast_function<
								PFNGLGENBUFFERSPROC
							>(
								_info.load_function(
									"glGenBuffersARB"
								)
							)
						),
						sge::opengl::deref_fun_ptr(
							sge::opengl::info::cast_function<
								PFNGLDELETEBUFFERSPROC
							>(
								_info.load_function(
									"glDeleteBuffersARB"
								)
							)
						),
						sge::opengl::deref_fun_ptr(
							sge::opengl::info::cast_function<
								PFNGLBINDBUFFERPROC
							>(
								_info.load_function(
									"glBindBufferARB"
								)
							)
						),
						sge::opengl::deref_fun_ptr(
							sge::opengl::info::cast_function<
								PFNGLMAPBUFFERPROC
							>(
								_info.load_function(
									"glMapBufferARB"
								)
							)
						),
						sge::opengl::deref_fun_ptr(
							sge::opengl::info::cast_function<
								PFNGLUNMAPBUFFERPROC
							>(
								_info.load_function(
									"glUnmapBufferARB"
								)
							)
						),
						sge::opengl::deref_fun_ptr(
							sge::opengl::info::cast_function<
								PFNGLBUFFERDATAPROC
							>(
								_info.load_function(
									"glBufferDataARB"
								)
							)
						),
						sge::opengl::deref_fun_ptr(
							sge::opengl::info::cast_function<
								PFNGLBUFFERSUBDATAPROC
							>(
								_info.load_function(
									"glBufferSubDataARB"
								)
							)
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

sge::opengl::context::id const
sge::opengl::buffer::context::static_id(
	sge::opengl::context::make_id()
);
