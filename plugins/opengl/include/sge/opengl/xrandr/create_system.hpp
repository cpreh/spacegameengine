//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_XRANDR_CREATE_SYSTEM_HPP_INCLUDED
#define SGE_OPENGL_XRANDR_CREATE_SYSTEM_HPP_INCLUDED

#include <sge/opengl/xrandr/optional_system_unique_ptr.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace xrandr
{

sge::opengl::xrandr::optional_system_unique_ptr
create_system(
	fcppt::log::object &,
	awl::backends::x11::display &
);

}
}
}

#endif
