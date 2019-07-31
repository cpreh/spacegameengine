//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_OCCLUSION_QUERY_CONFIG_HPP_INCLUDED
#define SGE_OPENGL_OCCLUSION_QUERY_CONFIG_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/fun_ref.hpp>
#include <sge/opengl/occlusion_query/config_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace occlusion_query
{

class config
{
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

	GLenum samples_target_;

	GLenum query_result_available_;

	GLenum query_result_;
};

}
}
}

#endif
