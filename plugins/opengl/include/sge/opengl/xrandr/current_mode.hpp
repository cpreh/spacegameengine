//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_XRANDR_CURRENT_MODE_HPP_INCLUDED
#define SGE_OPENGL_XRANDR_CURRENT_MODE_HPP_INCLUDED

#include <sge/opengl/xrandr/configuration_fwd.hpp>
#include <sge/opengl/xrandr/mode_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace xrandr
{

sge::opengl::xrandr::mode
current_mode(
	sge::opengl::xrandr::configuration const &
);

}
}
}

#endif
