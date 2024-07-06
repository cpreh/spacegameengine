//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_EGL_VERSION_OUTPUT_HPP_INCLUDED
#define SGE_OPENGL_EGL_VERSION_OUTPUT_HPP_INCLUDED

#include <sge/opengl/egl/version_fwd.hpp>
#include <fcppt/io/ostream_fwd.hpp>

namespace sge::opengl::egl
{

fcppt::io::ostream &operator<<(fcppt::io::ostream &, sge::opengl::egl::version const &);

}

#endif
