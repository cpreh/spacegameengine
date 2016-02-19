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


#include <sge/opengl/xrandr/combine_pixel_sizes.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/display_mode/optional_pixel_size.hpp>
#include <sge/renderer/display_mode/pixel_size.hpp>


sge::renderer::display_mode::optional_pixel_size
sge::opengl::xrandr::combine_pixel_sizes(
	sge::renderer::display_mode::optional_pixel_size const _previous,
	sge::renderer::display_mode::pixel_size const _next
)
{
	return
		_previous.has_value()
		?
			sge::renderer::display_mode::optional_pixel_size()
		:
			sge::renderer::display_mode::optional_pixel_size(
				_next
			)
		;
}
