/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/xrandr/refresh_rate_from_mode.hpp>
#include <sge/renderer/display_mode/optional_refresh_rate.hpp>
#include <sge/renderer/display_mode/refresh_rate.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/Xrandr.h>
#include <cmath>
#include <fcppt/config/external_end.hpp>


sge::renderer::display_mode::optional_refresh_rate const
sge::opengl::xrandr::refresh_rate_from_mode(
	XRRModeInfo const &_info
)
{
	unsigned long long const denom(
		_info.hTotal
		*
		_info.vTotal
	);

	typedef
	double
	float_type;

	return
		denom
		==
		0u
		?
			sge::renderer::display_mode::optional_refresh_rate()
		:
			sge::renderer::display_mode::optional_refresh_rate(
				fcppt::strong_typedef_construct_cast<
					sge::renderer::display_mode::refresh_rate
				>(
					std::round(
						fcppt::cast::int_to_float<
							float_type
						>(
							_info.dotClock
						)
						/
						fcppt::cast::int_to_float<
							float_type
						>(
							denom
						)
					)
				)
			)
		;
}
