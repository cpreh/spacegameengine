//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_VF_DISABLE_VERTEX_ATTRIB_ARRAY_HPP_INCLUDED
#define SGE_OPENGL_VF_DISABLE_VERTEX_ATTRIB_ARRAY_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/vf/attribute_context_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace vf
{

void
disable_vertex_attrib_array(
	sge::opengl::vf::attribute_context const &,
	GLuint index
);

}
}
}

#endif
