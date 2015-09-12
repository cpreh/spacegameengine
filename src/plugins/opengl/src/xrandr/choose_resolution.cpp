/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/opengl/xrandr/configuration.hpp>
#include <sge/opengl/xrandr/current_mode.hpp>
#include <sge/opengl/xrandr/mode.hpp>
#include <sge/opengl/xrandr/resolution.hpp>
#include <sge/opengl/xrandr/resolution_unique_ptr.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/display_mode/object.hpp>
#include <awl/backends/x11/window/object.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/dim/comparison.hpp>
#include <fcppt/math/dim/static.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/dim/to_unsigned.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::xrandr::resolution_unique_ptr
sge::opengl::xrandr::choose_resolution(
	sge::opengl::xrandr::configuration const &_config,
	awl::backends::x11::window::object &_window,
	sge::renderer::display_mode::object const &_mode
)
{
	int nsizes;

	::XRRScreenSize *const sizes(
		::XRRConfigSizes(
			_config.get(),
			&nsizes
		)
	);

	for(
		int const index
		:
		fcppt::make_int_range_count(
			nsizes
		)
	)
	{
		::XRRScreenSize const &current(
			sizes[
				index
			]
		);

		fcppt::math::dim::static_<
			int,
			2
		> const current_size(
			current.width,
			current.height
		);

		if(
			fcppt::math::dim::structure_cast<
				sge::renderer::screen_size,
				fcppt::cast::size_fun
			>(
				fcppt::math::dim::to_unsigned(
					current_size
				)
			)
			==
			_mode.pixel_size().get()
		)
			return
				fcppt::make_unique_ptr<
					sge::opengl::xrandr::resolution
				>(
					_window,
					_config,
					sge::opengl::xrandr::mode(
						static_cast<
							SizeID
						>(
							index
						),
						RR_Rotate_0,
						_mode.refresh_rate()
					),
					sge::opengl::xrandr::current_mode(
						_config
					)
				);
	}

	throw sge::renderer::exception(
		FCPPT_TEXT("No matching resolution found!")
	);
}
