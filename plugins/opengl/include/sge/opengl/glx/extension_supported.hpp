//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_GLX_EXTENSION_SUPPORTED_HPP_INCLUDED
#define SGE_OPENGL_GLX_EXTENSION_SUPPORTED_HPP_INCLUDED

#include <sge/opengl/glx/extension.hpp>
#include <sge/opengl/glx/extension_set.hpp>


namespace sge
{
namespace opengl
{
namespace glx
{

bool
extension_supported(
	sge::opengl::glx::extension_set const &,
	sge::opengl::glx::extension const &
);

}
}
}

#endif
