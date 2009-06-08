/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../metrics.hpp"
#include "../glyph.hpp"
#include "../char_metric.hpp"
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <utility>

sge::ft::metrics::metrics(
	library &lib,
	filesystem::path const &font_path,
	font::size_type const font_height)
:
	face_(lib, font_path),
	pixel_size(font_height)
{
	if(FT_Select_Charmap(face_.get(), FT_ENCODING_UNICODE) != 0)
		throw exception(SGE_TEXT("No Unicode code map found!"));

	if(FT_Set_Pixel_Sizes(face_.get(), 0, font_height))
		throw exception(SGE_TEXT("FT_Set_Pixel_Sizes() failed!"));
}

sge::font::char_metric_ptr const
sge::ft::metrics::load_char(
	char_type const c)
{
	{
		buffer_type::const_iterator const it = buffer.find(c);
		if(it != buffer.end())
			return it->second;
	}

	font::char_metric_ptr const metric(
		new char_metric(
			face_,
			c));
	buffer.insert(std::make_pair(c, metric));
	return metric;
}

sge::font::unit
sge::ft::metrics::line_height() const
{
	return static_cast<
		font::unit
	>(
		face_->size->metrics.height / 64);
}
