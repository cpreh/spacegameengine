/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/renderer/display_mode/object.hpp>
#include <sge/renderer/display_mode/optional_dimensions.hpp>
#include <sge/renderer/display_mode/optional_refresh_rate.hpp>
#include <sge/renderer/display_mode/pixel_size.hpp>


sge::renderer::display_mode::object::object(
	sge::renderer::display_mode::pixel_size const &_pixel_size,
	sge::renderer::display_mode::optional_dimensions const &_dimensions,
	sge::renderer::display_mode::optional_refresh_rate const _refresh_rate
)
:
	pixel_size_(
		_pixel_size
	),
	dimensions_(
		_dimensions
	),
	refresh_rate_(
		_refresh_rate
	)
{
}

sge::renderer::display_mode::pixel_size const &
sge::renderer::display_mode::object::pixel_size() const
{
	return pixel_size_;
}

sge::renderer::display_mode::optional_dimensions const &
sge::renderer::display_mode::object::dimensions() const
{
	return dimensions_;
}

sge::renderer::display_mode::optional_refresh_rate const
sge::renderer::display_mode::object::refresh_rate() const
{
	return refresh_rate_;
}
