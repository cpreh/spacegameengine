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


#include <utility>
#include "../../../renderer/transform.hpp"
#include "../font_metrics.hpp"
#include "../glyph.hpp"
#include "../char_metric.hpp"

sge::ft::font_metrics::font_metrics(library& lib, const std::string& font_path, const unsigned font_height)
: _face(lib, font_path)
{
	if(FT_Select_Charmap(_face.get(), FT_ENCODING_UNICODE) != 0)
		throw exception("No Unicode code map found!");

	if(FT_Set_Pixel_Sizes(_face.get(), 0, font_height))
		throw exception("FT_Set_Pixel_Sizes() failed");

	pixel_size = font_height;
	//pixel_size =  _face->ascender / 64 - _face->descender / 64;
}

const sge::char_metric_ptr sge::ft::font_metrics::load_char(const font_char c)
{
	{
		const buffer_type::const_iterator it = buffer.find(c);
		if(it != buffer.end())
			return it->second;
	}

	const char_metric_ptr metric(new char_metric(_face, c, line_height()));
	buffer.insert(std::make_pair(c, metric));
	return metric;
}

sge::font_unit sge::ft::font_metrics::line_height() const
{
	return pixel_size;
}
