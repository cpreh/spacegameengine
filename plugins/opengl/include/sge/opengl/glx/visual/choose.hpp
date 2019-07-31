//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_GLX_VISUAL_CHOOSE_HPP_INCLUDED
#define SGE_OPENGL_GLX_VISUAL_CHOOSE_HPP_INCLUDED

#include <sge/opengl/glx/visual/attribute_container.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <awl/backends/x11/screen.hpp>
#include <awl/backends/x11/visual/info_unique_ptr.hpp>


namespace sge
{
namespace opengl
{
namespace glx
{
namespace visual
{

awl::backends::x11::visual::info_unique_ptr
choose(
	awl::backends::x11::display const &,
	awl::backends::x11::screen,
	sge::opengl::glx::visual::attribute_container const &
);

}
}
}
}

#endif
