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


#include <sge/font/unit.hpp>
#include <sge/font/vector.hpp>
#include <sge/src/font/bitmap/char_metric.hpp>
#include <sge/src/font/bitmap/const_view.hpp>


sge::font::bitmap::char_metric::char_metric(
	sge::font::bitmap::const_view const &_view,
	sge::font::vector const &_offset,
	sge::font::unit const _x_advance
)
:
	view_(
		_view
	),
	offset_(
		_offset
	),
	x_advance_(
		_x_advance
	)
{
}

sge::font::bitmap::char_metric::~char_metric()
{
}

sge::font::bitmap::const_view const
sge::font::bitmap::char_metric::view() const
{
	return view_;
}

sge::font::vector const
sge::font::bitmap::char_metric::offset() const
{
	return offset_;
}

sge::font::unit
sge::font::bitmap::char_metric::x_advance() const
{
	return x_advance_;
}
