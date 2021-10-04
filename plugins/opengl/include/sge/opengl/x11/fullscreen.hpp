//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_X11_FULLSCREEN_HPP_INCLUDED
#define SGE_OPENGL_X11_FULLSCREEN_HPP_INCLUDED

#include <sge/opengl/x11/fullscreen_atom.hpp>
#include <sge/opengl/x11/state_atom.hpp>
#include <awl/backends/x11/window/base_fwd.hpp>


namespace sge::opengl::x11
{

void
fullscreen(
	awl::backends::x11::window::base &, // NOLINT(google-runtime-references)
	sge::opengl::x11::state_atom,
	sge::opengl::x11::fullscreen_atom,
	bool
);

}

#endif
