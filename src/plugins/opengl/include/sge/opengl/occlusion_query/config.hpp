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


#ifndef SGE_OPENGL_OCCLUSION_QUERY_CONFIG_HPP_INCLUDED
#define SGE_OPENGL_OCCLUSION_QUERY_CONFIG_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/fun_ref.hpp>
#include <sge/opengl/occlusion_query/config_fwd.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace opengl
{
namespace occlusion_query
{

class config
{
	FCPPT_NONASSIGNABLE(
		config
	);
public:
	typedef
	sge::opengl::fun_ref<
		PFNGLGENQUERIESPROC
	>
	gl_gen_queries;

	typedef
	sge::opengl::fun_ref<
		PFNGLDELETEQUERIESPROC
	>
	gl_delete_queries;

	typedef
	sge::opengl::fun_ref<
		PFNGLBEGINQUERYPROC
	>
	gl_begin_query;

	typedef
	sge::opengl::fun_ref<
		PFNGLENDQUERYPROC
	>
	gl_end_query;

	typedef
	sge::opengl::fun_ref<
		PFNGLGETQUERYOBJECTIVPROC
	>
	gl_get_query_object_iv;

	typedef
	sge::opengl::fun_ref<
		PFNGLGETQUERYOBJECTUIVPROC
	>
	gl_get_query_object_uiv;

	config(
		gl_gen_queries,
		gl_delete_queries,
		gl_begin_query,
		gl_end_query,
		gl_get_query_object_iv,
		gl_get_query_object_uiv,
		GLenum samples_target_,
		GLenum query_result_available_,
		GLenum query_result_
	);

	gl_gen_queries
	gen_queries() const;

	gl_delete_queries
	delete_queries() const;

	gl_begin_query
	begin_query() const;

	gl_end_query
	end_query() const;

	gl_get_query_object_iv
	get_query_object_iv() const;

	gl_get_query_object_uiv
	get_query_object_uiv() const;

	GLenum
	samples_target() const;

	GLenum
	query_result_available() const;

	GLenum
	query_result() const;
private:
	gl_gen_queries gen_queries_;

	gl_delete_queries delete_queries_;

	gl_begin_query begin_query_;

	gl_end_query end_query_;

	gl_get_query_object_iv get_query_object_iv_;

	gl_get_query_object_uiv get_query_object_uiv_;

	GLenum const samples_target_;

	GLenum const query_result_available_;

	GLenum const query_result_;
};

}
}
}

#endif
