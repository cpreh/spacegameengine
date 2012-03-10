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


#include <sge/opengl/xrandr/check_extension.hpp>
#include <sge/opengl/xrandr/choose_resolution.hpp>
#include <sge/opengl/xrandr/configuration.hpp>
#include <sge/opengl/xrandr/current_resolution.hpp>
#include <sge/opengl/xrandr/mode.hpp>
#include <sge/opengl/xrandr/resolution.hpp>
#include <sge/renderer/display_mode.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/screen_unit.hpp>
#include <awl/backends/x11/window/instance.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/move.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>


sge::opengl::xrandr::resolution_unique_ptr
sge::opengl::xrandr::choose_resolution(
	awl::backends::x11::window::instance &_window,
	sge::renderer::display_mode const &_mode
)
{
	sge::opengl::xrandr::check_extension(
		_window.display()
	);

	sge::opengl::xrandr::configuration_unique_ptr config(
		fcppt::make_unique_ptr<
			sge::opengl::xrandr::configuration
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
		int index = 0;
		index < nsizes;
		++index
	)
		if(
			static_cast<
				sge::renderer::screen_unit
			>(
				sizes[
					index
				].width
			)
			== _mode.size().w()
			&&
			static_cast<
				sge::renderer::screen_unit
			>(
				sizes[
					index
				].height
			)
			== _mode.size().h()
		)
		{
			sge::opengl::xrandr::configuration &config_ref(
				*config
			);

			return
				sge::opengl::xrandr::resolution_unique_ptr(
					fcppt::make_unique_ptr<
						sge::opengl::xrandr::resolution
					>(
						fcppt::ref(
							_window
						),
						fcppt::move(
							config
						),
						sge::opengl::xrandr::mode(
							index,
							RR_Rotate_0,
							_mode.refresh_rate()
						),
						sge::opengl::xrandr::current_resolution(
							config_ref
						)
					)
				);
		}

	throw sge::renderer::exception(
		FCPPT_TEXT("No matching resolution found!")
	);
}
