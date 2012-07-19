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
#include <sge/opengl/context/system/base.hpp>
#include <sge/opengl/context/system/id.hpp>
#include <sge/opengl/context/system/make_id.hpp>
#include <sge/opengl/glew/is_supported.hpp>
#include <sge/opengl/occlusion_query/context.hpp>
#include <fcppt/null_ptr.hpp>


// ARB could be supported if necessary

sge::opengl::occlusion_query::context::context()
:
	sge::opengl::context::system::base(),
	has_native_(
		sge::opengl::glew::is_supported(
			"GL_VERSION_1_5"
		)
	),
	gen_queries_(
		has_native_
		?
			glGenQueries
		:
			fcppt::null_ptr()
	),
	delete_queries_(
		has_native_
		?
			glDeleteQueries
		:
			fcppt::null_ptr()
	),
	begin_query_(
		has_native_
		?
			glBeginQuery
		:
			fcppt::null_ptr()
	),
	end_query_(
		has_native_
		?
			glEndQuery
		:
			fcppt::null_ptr()
	),
	get_query_object_iv_(
		has_native_
		?
			glGetQueryObjectiv
		:
			fcppt::null_ptr()
	),
	get_query_object_uiv_(
		has_native_
		?
			glGetQueryObjectuiv
		:
			fcppt::null_ptr()
	),
	samples_target_(
		has_native_
		?
			GL_SAMPLES_PASSED
		:
			0
	),
	query_result_available_(
		has_native_
		?
			GL_QUERY_RESULT_AVAILABLE
		:
			0
	),
	query_result_(
		has_native_
		?
			GL_QUERY_RESULT
		:
			0
	)
{
}

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

GLenum
sge::opengl::occlusion_query::context::samples_target() const
{
	return
		samples_target_;
}

GLenum
sge::opengl::occlusion_query::context::query_result_available() const
{
	return
		query_result_available_;
}

GLenum
sge::opengl::occlusion_query::context::query_result() const
{
	return
		query_result_;
}

sge::opengl::context::system::id const
sge::opengl::occlusion_query::context::static_id(
	sge::opengl::context::system::make_id()
);
