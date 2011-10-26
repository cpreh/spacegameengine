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


#include <sge/opengl/xf86vmode/choose_mode.hpp>
#include <sge/opengl/xf86vmode/modes.hpp>
#include <sge/opengl/xf86vmode/calc_refresh_rate.hpp>
#include <sge/opengl/xf86vmode/resolution.hpp>
#include <sge/renderer/display_mode.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>


sge::opengl::xf86vmode::resolution_ptr const
sge::opengl::xf86vmode::choose_mode(
	renderer::display_mode const &_display_mode,
	xf86vmode::modes const &_modes
)
{
	int best = -1;

	for(
		modes::size_type index = 1;
		index < _modes.size();
		++index
	)
	{
		XF86VidModeModeInfo const &mode(
			_modes[
				index
			]
		);

		unsigned const rate(
			xf86vmode::calc_refresh_rate(
				mode
			)
		);

		if(
			mode.hdisplay == _display_mode.size().w()
			&&
			mode.vdisplay == _display_mode.size().h()
			&&
			rate  >= _display_mode.refresh_rate().get()
			&&
			(
				best == -1
				||
				rate >=
				xf86vmode::calc_refresh_rate(
					_modes[
						static_cast<
							modes::size_type
						>(
							best
						)
					]
				)
			)
		)
			best = static_cast<int>(index);
	}

	if(
		best == -1
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("No matching resolution found in xf86vmode!")
		);

	return
		resolution_ptr(
			fcppt::make_shared_ptr<
				xf86vmode::resolution
			>(
				fcppt::ref(
					_modes.display()
				),
				_modes.screen(),
				_modes[
					static_cast<
						modes::size_type
					>(
						best
					)
				],
				_modes[0]
			)
		);
}
