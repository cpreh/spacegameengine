/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_OPENGL_X11_SYSTEM_HPP_INCLUDED
#define SGE_OPENGL_X11_SYSTEM_HPP_INCLUDED

#include <sge/opengl/platform/device_state_unique_ptr.hpp>
#include <sge/opengl/platform/system.hpp>
#include <sge/opengl/x11/fullscreen_atom.hpp>
#include <sge/opengl/x11/state_atom.hpp>
#include <sge/opengl/xrandr/optional_system_unique_ptr.hpp>
#include <sge/renderer/display_mode/optional_fullscreen_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <awl/backends/x11/system/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace x11
{

class system
:
	public sge::opengl::platform::system
{
	FCPPT_NONCOPYABLE(
		system
	);
public:
	system(
		fcppt::log::object &,
		awl::backends::x11::system::object &
	);

	~system()
	override;
private:
	sge::opengl::platform::device_state_unique_ptr
	create_device_state(
		sge::renderer::display_mode::optional_fullscreen const &,
		sge::window::object &
	)
	override;

	fcppt::log::object &log_;

	sge::opengl::xrandr::optional_system_unique_ptr const xrandr_system_;

	sge::opengl::x11::state_atom const wm_state_;

	sge::opengl::x11::fullscreen_atom const wm_fullscreen_;
};

}
}
}

#endif
