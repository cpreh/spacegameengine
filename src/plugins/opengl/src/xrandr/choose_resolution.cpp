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
#include <sge/opengl/xrandr/configuration.hpp>
#include <sge/opengl/xrandr/current_resolution.hpp>
#include <sge/opengl/xrandr/mode.hpp>
#include <sge/opengl/xrandr/resolution.hpp>
#include <sge/opengl/xrandr/resolution_unique_ptr.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/screen_unit.hpp>
#include <sge/renderer/display_mode/object.hpp>
#include <awl/backends/x11/window/object.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
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
		int index = 0;
		index < nsizes;
		++index
	)
	{
		::XRRScreenSize const &current(
			sizes[
				index
			]
		);

		if(
			static_cast<
				sge::renderer::screen_unit
			>(
				current.width
			)
			== _mode.pixel_size().get().w()
			&&
			static_cast<
				sge::renderer::screen_unit
			>(
				current.height
			)
			== _mode.pixel_size().get().h()
		)
		{
			return
				sge::opengl::xrandr::resolution_unique_ptr(
					fcppt::make_unique_ptr<
						sge::opengl::xrandr::resolution
					>(
						fcppt::ref(
							_window
						),
						fcppt::cref(
							_config
						),
						sge::opengl::xrandr::mode(
							static_cast<
								SizeID
							>(
								index
							),
							RR_Rotate_0,
							_mode.refresh_rate()
						),
						sge::opengl::xrandr::current_resolution(
							_config
						)
					)
				);
		}
	}

	throw sge::renderer::exception(
		FCPPT_TEXT("No matching resolution found!")
	);
}
