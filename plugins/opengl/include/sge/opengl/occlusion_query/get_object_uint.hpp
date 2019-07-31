//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_OCCLUSION_QUERY_GET_OBJECT_UINT_HPP_INCLUDED
#define SGE_OPENGL_OCCLUSION_QUERY_GET_OBJECT_UINT_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/occlusion_query/config_fwd.hpp>
#include <sge/opengl/occlusion_query/id.hpp>


namespace sge
{
namespace opengl
{
namespace occlusion_query
{

GLuint
get_object_uint(
	sge::opengl::occlusion_query::config const &,
	sge::opengl::occlusion_query::id,
	GLenum what
);

}
}
}

#endif
