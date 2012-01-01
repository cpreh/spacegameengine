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


#include <sge/image/color/any/convert.hpp>
#include <sge/line_drawer/line.hpp>


sge::line_drawer::line::line(
	sge::renderer::vector3 const &_begin,
	sge::renderer::vector3 const &_end,
	sge::image::color::any::object const &_begin_color,
	sge::image::color::any::object const &_end_color)
:
	begin_(
		_begin),
	end_(
		_end),
	begin_color_(
		sge::image::color::any::convert<color_format>(
			_begin_color)),
	end_color_(
		sge::image::color::any::convert<color_format>(
			_end_color))
{
}

sge::renderer::vector3 const &
sge::line_drawer::line::begin() const
{
	return begin_;
}

sge::renderer::vector3 const &
sge::line_drawer::line::end() const
{
	return end_;
}

sge::line_drawer::color const &
sge::line_drawer::line::begin_color() const
{
	return begin_color_;
}

sge::line_drawer::color const &
sge::line_drawer::line::end_color() const
{
	return end_color_;
}
