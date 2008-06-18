/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/string.hpp>
#include <utility>

sge::ft::metrics::metrics(
	library& lib,
	const path& font_path,
	const unsigned font_height)
: face_(lib, font_path),
  pixel_size(static_cast<font::unit>(font_height))
{
	if(FT_Select_Charmap(face_.get(), FT_ENCODING_UNICODE) != 0)
		throw exception(SGE_TEXT("No Unicode code map found!"));

	if(FT_Set_Pixel_Sizes(face_.get(), 0, font_height))
		throw exception(SGE_TEXT("FT_Set_Pixel_Sizes() failed!"));
}

const sge::font::char_metric_ptr
sge::ft::metrics::load_char(
	const char_type c)
{
	{
		const buffer_type::const_iterator it = buffer.find(c);
		if(it != buffer.end())
			return it->second;
	}

	const font::char_metric_ptr metric(new char_metric(face_, c, line_height()));
	buffer.insert(std::make_pair(c, metric));
	return metric;
}

sge::font::unit sge::ft::metrics::line_height() const
{
	return pixel_size;
}
