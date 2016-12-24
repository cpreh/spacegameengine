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


#include <sge/opengl/xrandr/configuration_fwd.hpp>
#include <sge/opengl/xrandr/mode.hpp>
#include <sge/opengl/xrandr/mode_index.hpp>
#include <sge/opengl/xrandr/optional_refresh_rate.hpp>
#include <sge/opengl/xrandr/resolution.hpp>
#include <sge/opengl/xrandr/refresh_rate.hpp>
#include <sge/opengl/xrandr/rotation.hpp>
#include <sge/opengl/xrandr/set_resolution.hpp>
#include <sge/renderer/display_mode/optional_refresh_rate.hpp>
#include <sge/renderer/display_mode/refresh_rate.hpp>
#include <awl/backends/x11/window/object_fwd.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/randr.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::xrandr::resolution::resolution(
	awl::backends::x11::window::object &_window,
	sge::opengl::xrandr::configuration const &_config,
	sge::opengl::xrandr::mode_index const _mode_index,
	sge::renderer::display_mode::optional_refresh_rate const &_opt_rate,
	sge::opengl::xrandr::mode const &_old_mode
)
:
	window_{
		_window
	},
	config_{
		_config
	},
	old_mode_{
		_old_mode
	}
{
	sge::opengl::xrandr::set_resolution(
		_window,
		config_,
		_mode_index,
		sge::opengl::xrandr::rotation{
			fcppt::cast::size<
				unsigned short
			>(
				fcppt::cast::to_unsigned(
					RR_Rotate_0
				)
			)
		},
		fcppt::optional::map(
			_opt_rate,
			[](
				sge::renderer::display_mode::refresh_rate const _rate
			)
			{
				return
					fcppt::strong_typedef_construct_cast<
						sge::opengl::xrandr::refresh_rate,
						fcppt::cast::size_fun
					>(
						fcppt::cast::to_signed(
							_rate.get()
						)
					);
			}
		)
	);
}

sge::opengl::xrandr::resolution::~resolution()
{
	sge::opengl::xrandr::set_resolution(
		window_,
		config_,
		old_mode_.index(),
		old_mode_.rotation(),
		sge::opengl::xrandr::optional_refresh_rate(
			old_mode_.rate()
		)
	);
}
