//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_X11_FULLSCREEN_ATOM_HPP_INCLUDED
#define SGE_OPENGL_X11_FULLSCREEN_ATOM_HPP_INCLUDED

#include <awl/backends/x11/atom.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef_impl.hpp>


namespace sge::opengl::x11
{

FCPPT_MAKE_STRONG_TYPEDEF(
	awl::backends::x11::atom,
	fullscreen_atom
);

}

#endif
