//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_GLX_VSYNC_HPP_INCLUDED
#define SGE_OPENGL_GLX_VSYNC_HPP_INCLUDED

#include <sge/opengl/glx/swap_functions_fwd.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sge::opengl::glx
{

void
vsync(
	fcppt::log::object &, // NOLINT(google-runtime-references)
	sge::opengl::glx::swap_functions const &,
	awl::backends::x11::display & // NOLINT(google-runtime-references)
); // NOLINT(google-runtime-references)

}

#endif
