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
#include <sge/opengl/occlusion_query/config.hpp>


sge::opengl::occlusion_query::config::config(
	gl_gen_queries _gen_queries,
	gl_delete_queries _delete_queries,
	gl_begin_query _begin_query,
	gl_end_query _end_query,
	gl_get_query_object_iv _get_query_object_iv,
	gl_get_query_object_uiv _get_query_object_uiv,
	GLenum const _samples_target,
	GLenum const _query_result_available,
	GLenum const _query_result
)
:
	gen_queries_(
		_gen_queries
	),
	delete_queries_(
		_delete_queries
	),
	begin_query_(
		_begin_query
	),
	end_query_(
		_end_query
	),
	get_query_object_iv_(
		_get_query_object_iv
	),
	get_query_object_uiv_(
		_get_query_object_uiv
	),
	samples_target_(
		_samples_target
	),
	query_result_available_(
		_query_result_available
	),
	query_result_(
		_query_result
	)
{
}

sge::opengl::occlusion_query::config::gl_gen_queries
sge::opengl::occlusion_query::config::gen_queries() const
{
	return
		gen_queries_;
}

sge::opengl::occlusion_query::config::gl_delete_queries
sge::opengl::occlusion_query::config::delete_queries() const
{
	return
		delete_queries_;
}

sge::opengl::occlusion_query::config::gl_begin_query
sge::opengl::occlusion_query::config::begin_query() const
{
	return
		begin_query_;
}

sge::opengl::occlusion_query::config::gl_end_query
sge::opengl::occlusion_query::config::end_query() const
{
	return
		end_query_;
}

sge::opengl::occlusion_query::config::gl_get_query_object_iv
sge::opengl::occlusion_query::config::get_query_object_iv() const
{
	return
		get_query_object_iv_;
}

sge::opengl::occlusion_query::config::gl_get_query_object_uiv
sge::opengl::occlusion_query::config::get_query_object_uiv() const
{
	return
		get_query_object_uiv_;
}

GLenum
sge::opengl::occlusion_query::config::samples_target() const
{
	return
		samples_target_;
}

GLenum
sge::opengl::occlusion_query::config::query_result_available() const
{
	return
		query_result_available_;
}

GLenum
sge::opengl::occlusion_query::config::query_result() const
{
	return
		query_result_;
}
