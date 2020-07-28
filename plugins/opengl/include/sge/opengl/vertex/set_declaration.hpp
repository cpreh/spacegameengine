//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_VERTEX_SET_DECLARATION_HPP_INCLUDED
#define SGE_OPENGL_VERTEX_SET_DECLARATION_HPP_INCLUDED

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/renderer/vertex/const_optional_declaration_ref_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace vertex
{

void
set_declaration(
	sge::opengl::context::object &, // NOLINT(google-runtime-references)
	sge::renderer::vertex::const_optional_declaration_ref const &
);

}
}
}

#endif
