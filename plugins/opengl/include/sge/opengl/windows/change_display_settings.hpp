//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_WINDOWS_CHANGE_DISPLAY_SETTINGS_HPP_INCLUDED
#define SGE_OPENGL_WINDOWS_CHANGE_DISPLAY_SETTINGS_HPP_INCLUDED

#include <sge/renderer/display_mode/object_fwd.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace windows
{

void
change_display_settings(
	fcppt::log::object &,
	sge::renderer::display_mode::object const &
);

}
}
}

#endif
