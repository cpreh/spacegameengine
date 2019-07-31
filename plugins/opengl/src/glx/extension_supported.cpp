//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/extension_supported.hpp>
#include <sge/opengl/glx/extension.hpp>
#include <sge/opengl/glx/extension_set.hpp>
#include <sge/opengl/glx/extension_supported.hpp>


bool
sge::opengl::glx::extension_supported(
	sge::opengl::glx::extension_set const &_extensions,
	sge::opengl::glx::extension const &_extension
)
{
	return
		sge::opengl::extension_supported(
			_extensions,
			_extension
		);
}
