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
#include <sge/src/font/bitmap/char_metric_ref_vector.hpp>
#include <sge/src/font/bitmap/line.hpp>


sge::font::bitmap::line::line(
	sge::font::bitmap::char_metric_ref_vector const &_char_metrics,
	sge::font::unit const _width
)
:
	char_metrics_(
		_char_metrics
	),
	width_(
		_width
	)
{
}

sge::font::bitmap::line::line(
	line &&
) = default;

sge::font::bitmap::line &
sge::font::bitmap::line::operator=(
	line &&
) = default;

sge::font::bitmap::line::~line()
{
}

sge::font::bitmap::char_metric_ref_vector const &
sge::font::bitmap::line::char_metrics() const
{
	return
		char_metrics_;
}

sge::font::unit
sge::font::bitmap::line::width() const
{
	return
		width_;
}
