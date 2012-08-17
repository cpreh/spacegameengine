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


#ifndef SGE_OPENGL_OCCLUSION_QUERY_CONTEXT_HPP_INCLUDED
#define SGE_OPENGL_OCCLUSION_QUERY_CONTEXT_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/optional_enum.hpp>
#include <sge/opengl/context/system/base.hpp>
#include <sge/opengl/context/system/id.hpp>
#include <sge/opengl/occlusion_query/context_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace occlusion_query
{

class context
:
	public sge::opengl::context::system::base
{
	FCPPT_NONCOPYABLE(
		context
	);
public:
	context();

	~context();

	bool
	is_supported() const;

	typedef PFNGLGENQUERIESPROC gl_gen_queries;

	typedef PFNGLDELETEQUERIESPROC gl_delete_queries;

	typedef PFNGLBEGINQUERYPROC gl_begin_query;

	typedef PFNGLENDQUERYPROC gl_end_query;

	typedef PFNGLGETQUERYOBJECTIVPROC gl_get_query_object_iv;

	typedef PFNGLGETQUERYOBJECTUIVPROC gl_get_query_object_uiv;

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

	sge::opengl::optional_enum const
	samples_target() const;

	sge::opengl::optional_enum const
	query_result_available() const;

	sge::opengl::optional_enum const
	query_result() const;

	typedef void needs_before;

	static sge::opengl::context::system::id const static_id;
private:
	bool const has_native_;

	gl_gen_queries const gen_queries_;

	gl_delete_queries const delete_queries_;

	gl_begin_query const begin_query_;

	gl_end_query const end_query_;

	gl_get_query_object_iv const get_query_object_iv_;

	gl_get_query_object_uiv const get_query_object_uiv_;

	sge::opengl::optional_enum const
		samples_target_,
		query_result_available_,
		query_result_;
};

}
}
}

#endif
