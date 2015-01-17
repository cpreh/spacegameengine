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
#include <sge/opengl/optional_enum.hpp>
#include <sge/opengl/context/system/base.hpp>
#include <sge/opengl/context/system/id.hpp>
#include <sge/opengl/context/system/make_id.hpp>
#include <sge/opengl/convert/from_gl_bool.hpp>
#include <sge/opengl/occlusion_query/context.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


// ARB could be supported if necessary

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wold-style-cast)

sge::opengl::occlusion_query::context::context()
:
	sge::opengl::context::system::base(),
	has_native_(
		sge::opengl::convert::from_gl_bool(
			GLEW_VERSION_1_5
		)
	),
	gen_queries_(
		has_native_
		?
			glGenQueries
		:
			nullptr
	),
	delete_queries_(
		has_native_
		?
			glDeleteQueries
		:
			nullptr
	),
	begin_query_(
		has_native_
		?
			glBeginQuery
		:
			nullptr
	),
	end_query_(
		has_native_
		?
			glEndQuery
		:
			nullptr
	),
	get_query_object_iv_(
		has_native_
		?
			glGetQueryObjectiv
		:
			nullptr
	),
	get_query_object_uiv_(
		has_native_
		?
			glGetQueryObjectuiv
		:
			nullptr
	),
	samples_target_(
		has_native_
		?
			sge::opengl::optional_enum(
				static_cast<
					GLenum
				>(
					GL_SAMPLES_PASSED
				)
			)
		:
			sge::opengl::optional_enum()
	),
	query_result_available_(
		has_native_
		?
			sge::opengl::optional_enum(
				static_cast<
					GLenum
				>(
					GL_QUERY_RESULT_AVAILABLE
				)
			)
		:
			sge::opengl::optional_enum()
	),
	query_result_(
		has_native_
		?
			sge::opengl::optional_enum(
				static_cast<
					GLenum
				>(
					GL_QUERY_RESULT
				)
			)
		:
			sge::opengl::optional_enum()
	)
{
}

FCPPT_PP_POP_WARNING

sge::opengl::occlusion_query::context::~context()
{
}

bool
sge::opengl::occlusion_query::context::is_supported() const
{
	return
		has_native_;
}

sge::opengl::occlusion_query::context::gl_gen_queries
sge::opengl::occlusion_query::context::gen_queries() const
{
	return
		gen_queries_;
}

sge::opengl::occlusion_query::context::gl_delete_queries
sge::opengl::occlusion_query::context::delete_queries() const
{
	return
		delete_queries_;
}

sge::opengl::occlusion_query::context::gl_begin_query
sge::opengl::occlusion_query::context::begin_query() const
{
	return
		begin_query_;
}

sge::opengl::occlusion_query::context::gl_end_query
sge::opengl::occlusion_query::context::end_query() const
{
	return
		end_query_;
}

sge::opengl::occlusion_query::context::gl_get_query_object_iv
sge::opengl::occlusion_query::context::get_query_object_iv() const
{
	return
		get_query_object_iv_;
}

sge::opengl::occlusion_query::context::gl_get_query_object_uiv
sge::opengl::occlusion_query::context::get_query_object_uiv() const
{
	return
		get_query_object_uiv_;
}

sge::opengl::optional_enum const
sge::opengl::occlusion_query::context::samples_target() const
{
	return
		samples_target_;
}

sge::opengl::optional_enum const
sge::opengl::occlusion_query::context::query_result_available() const
{
	return
		query_result_available_;
}

sge::opengl::optional_enum const
sge::opengl::occlusion_query::context::query_result() const
{
	return
		query_result_;
}

sge::opengl::context::system::id const
sge::opengl::occlusion_query::context::static_id(
	sge::opengl::context::system::make_id()
);
