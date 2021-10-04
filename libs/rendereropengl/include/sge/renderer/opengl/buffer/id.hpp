//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_OPENGL_BUFFER_ID_HPP_INCLUDED
#define SGE_RENDERER_OPENGL_BUFFER_ID_HPP_INCLUDED

#include <sge/renderer/opengl/glinclude.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sge::renderer::opengl::buffer
{

FCPPT_MAKE_STRONG_TYPEDEF(
	GLuint,
	id
);

}

#endif
