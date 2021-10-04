//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_CG_PROGRAM_TRANSFORM_VERTEX_HPP_INCLUDED
#define SGE_OPENGL_CG_PROGRAM_TRANSFORM_VERTEX_HPP_INCLUDED

#include <sge/cg/program/source.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>


namespace sge::opengl::cg::program
{

sge::cg::program::source
transform_vertex(
	sge::renderer::vertex::declaration const &,
	sge::cg::program::source const &
);

}

#endif
