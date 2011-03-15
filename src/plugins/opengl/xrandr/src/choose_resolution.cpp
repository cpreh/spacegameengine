/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../choose_resolution.hpp"
#include "../configuration.hpp"
#include "../resolution.hpp"
#include "../mode.hpp"
#include "../current_resolution.hpp"
#include "../check_extension.hpp"
#include <sge/renderer/display_mode.hpp>
#include <sge/renderer/screen_unit.hpp>
#include <sge/renderer/exception.hpp>
#include <awl/backends/x11/window/instance.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>

sge::opengl::xrandr::resolution_ptr const
sge::opengl::xrandr::choose_resolution(
	awl::backends::x11::window::instance &_window,
	renderer::display_mode const &_mode
)
{
	xrandr::check_extension(
		_window.display()
	);

	xrandr::configuration_ptr const config(
		fcppt::make_shared_ptr<
			xrandr::configuration
		>(
			fcppt::ref(
				_window
			)
		)
	);

	int nsizes;

	::XRRScreenSize *const sizes(
		::XRRConfigSizes(
			config->get(),
			&nsizes
		)
	);

	for(
		int i = 0;
		i < nsizes;
		++i
	)
		if(
			static_cast<
				renderer::screen_unit
			>(
				sizes[i].width
			)
			== _mode.size().w()
			&&
			static_cast<
				renderer::screen_unit
			>(
				sizes[i].height
			)
			== _mode.size().h()
		)
			return
				xrandr::resolution_ptr(
					fcppt::make_shared_ptr<
						xrandr::resolution
					>(
						fcppt::ref(
							_window
						),
						config,
						xrandr::mode(
							i,
							RR_Rotate_0,
							_mode.refresh_rate()
						),
						xrandr::current_resolution(
							config
						)
					)
				);

	throw sge::renderer::exception(
		FCPPT_TEXT("No matching resolution found!")
	);
}
