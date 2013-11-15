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


#include <sge/opengl/xrandr/combine_rates.hpp>
#include <sge/renderer/display_mode/optional_refresh_rate.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


sge::renderer::display_mode::optional_refresh_rate const
sge::opengl::xrandr::combine_rates(
	sge::renderer::display_mode::optional_refresh_rate const _rate_a,
	sge::renderer::display_mode::optional_refresh_rate const _rate_b
)
{
	if(
		!_rate_a
	)
		return
			_rate_b;

	if(
		!_rate_b
	)
		return
			_rate_a;

	return
		sge::renderer::display_mode::optional_refresh_rate(
			std::max(
				*_rate_a,
				*_rate_b
			)
		);
}
