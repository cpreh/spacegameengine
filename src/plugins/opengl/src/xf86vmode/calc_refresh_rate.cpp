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


#include <sge/opengl/xf86vmode/calc_refresh_rate.hpp>
#include <fcppt/math/ceil_div.hpp>

unsigned
sge::opengl::xf86vmode::calc_refresh_rate(
	XF86VidModeModeInfo const &mode
)
{
	return
		fcppt::math::ceil_div(
			static_cast<
				unsigned
			>(
				1000 * mode.dotclock
			),
			static_cast<
				unsigned
			>(
				mode.htotal * mode.vtotal
			)
		);
}
