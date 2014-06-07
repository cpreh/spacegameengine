/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/xrandr/configuration_fwd.hpp>
#include <sge/opengl/xrandr/mode.hpp>
#include <sge/opengl/xrandr/resolution.hpp>
#include <sge/opengl/xrandr/set_resolution.hpp>
#include <awl/backends/x11/window/object_fwd.hpp>


sge::opengl::xrandr::resolution::resolution(
	awl::backends::x11::window::object &_window,
	sge::opengl::xrandr::configuration const &_config,
	sge::opengl::xrandr::mode const &_new_mode,
	sge::opengl::xrandr::mode const &_old_mode
)
:
	window_(
		_window
	),
	config_(
		_config
	),
	old_mode_(
		_old_mode
	)
{
	sge::opengl::xrandr::set_resolution(
		_window,
		config_,
		_new_mode
	);
}

sge::opengl::xrandr::resolution::~resolution()
{
	sge::opengl::xrandr::set_resolution(
		window_,
		config_,
		old_mode_
	);
}
