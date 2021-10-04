//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_GLX_VISUAL_GET_SRGB_FLAG_HPP_INCLUDED
#define SGE_OPENGL_GLX_VISUAL_GET_SRGB_FLAG_HPP_INCLUDED

#include <sge/opengl/glx/extension_set.hpp>
#include <sge/opengl/glx/visual/optional_srgb_flag.hpp>


namespace sge::opengl::glx::visual
{

sge::opengl::glx::visual::optional_srgb_flag
get_srgb_flag(
	sge::opengl::glx::extension_set const &
);

}

#endif
