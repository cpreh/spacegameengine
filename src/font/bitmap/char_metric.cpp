/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/font/bitmap/char_metric.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/variant/object_impl.hpp>

sge::font::bitmap::char_metric::char_metric(
	font::const_image_view const &_pixmap,
	font::pos const &_offset,
	font::unit const _x_advance
)
:
	pixmap_(_pixmap),
	offset_(_offset),
	x_advance_(_x_advance)
{}

sge::font::bitmap::char_metric::~char_metric()
{}

sge::font::const_image_view const
sge::font::bitmap::char_metric::pixmap() const
{
	return pixmap_;
}

sge::font::pos const
sge::font::bitmap::char_metric::offset() const
{
	return offset_;
}

sge::font::unit
sge::font::bitmap::char_metric::x_advance() const
{
	return x_advance_;
}
