/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/xrandr/choose_resolution.hpp>
#include <sge/opengl/xrandr/current_display_mode.hpp>
#include <sge/opengl/xrandr/get_version.hpp>
#include <sge/opengl/xrandr/resolution.hpp>
#include <sge/opengl/xrandr/resolution_unique_ptr.hpp>
#include <sge/opengl/xrandr/state.hpp>
#include <sge/renderer/display_mode/object.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <awl/backends/x11/window/object.hpp>


sge::opengl::xrandr::state::state(
	awl::backends::x11::window::object &_window,
	sge::renderer::display_mode::optional_object const &_display_mode
)
:
	version_(
		sge::opengl::xrandr::get_version(
			_window.display()
		)
	),
	config_(
		_window
	),
	resolution_(
		_display_mode
		?
			sge::opengl::xrandr::choose_resolution(
				config_,
				_window,
				*_display_mode
			)
		:
			sge::opengl::xrandr::resolution_unique_ptr()
	)
{
}

sge::opengl::xrandr::state::~state()
{
}

sge::renderer::display_mode::object const
sge::opengl::xrandr::state::display_mode() const
{
	return
		sge::opengl::xrandr::current_display_mode(
			config_
		);
}
