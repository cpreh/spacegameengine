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
#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/convert/to_gl_enum.hpp>
#include <sge/opengl/info/cast_function.hpp>
#include <sge/opengl/info/context.hpp>
#include <sge/opengl/info/major_version.hpp>
#include <sge/opengl/info/minor_version.hpp>
#include <sge/opengl/info/version_at_least.hpp>
#include <sge/opengl/occlusion_query/config.hpp>
#include <sge/opengl/occlusion_query/context.hpp>
#include <sge/opengl/occlusion_query/optional_config.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


// TODO: ARB could be supported if necessary

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wold-style-cast)

sge::opengl::occlusion_query::context::context(
	sge::opengl::info::context const &_info
)
:
	sge::opengl::context::base(),
	config_(
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
			sge::opengl::occlusion_query::optional_config{
				sge::opengl::occlusion_query::config{
					sge::opengl::deref_fun_ptr(
						sge::opengl::info::cast_function<
							PFNGLGENQUERIESPROC
						>(
							_info.load_function(
								"glGenQueries"
							)
						)
					),
					sge::opengl::deref_fun_ptr(
						sge::opengl::info::cast_function<
							PFNGLDELETEQUERIESPROC
						>(
							_info.load_function(
								"glDeleteQueries"
							)
						)
					),
					sge::opengl::deref_fun_ptr(
						sge::opengl::info::cast_function<
							PFNGLBEGINQUERYPROC
						>(
							_info.load_function(
								"glBeginQuery"
							)
						)
					),
					sge::opengl::deref_fun_ptr(
						sge::opengl::info::cast_function<
							PFNGLENDQUERYPROC
						>(
							_info.load_function(
								"glEndQuery"
							)
						)
					),
					sge::opengl::deref_fun_ptr(
						sge::opengl::info::cast_function<
							PFNGLGETQUERYOBJECTIVPROC
						>(
							_info.load_function(
								"glGetQueryObjectiv"
							)
						)
					),
					sge::opengl::deref_fun_ptr(
						sge::opengl::info::cast_function<
							PFNGLGETQUERYOBJECTUIVPROC
						>(
							_info.load_function(
								"glGetQueryObjectuiv"
							)
						)
					),
					sge::opengl::convert::to_gl_enum<
						GL_SAMPLES_PASSED
					>(),
					sge::opengl::convert::to_gl_enum<
						GL_QUERY_RESULT_AVAILABLE
					>(),
					sge::opengl::convert::to_gl_enum<
						GL_QUERY_RESULT
					>()
				}
			}
		:
			sge::opengl::occlusion_query::optional_config{}
	)
{
}

FCPPT_PP_POP_WARNING

sge::opengl::occlusion_query::context::~context()
{
}

sge::opengl::occlusion_query::optional_config const &
sge::opengl::occlusion_query::context::config() const
{
	return
		config_;
}

sge::opengl::context::id const
sge::opengl::occlusion_query::context::static_id(
	sge::opengl::context::make_id()
);
