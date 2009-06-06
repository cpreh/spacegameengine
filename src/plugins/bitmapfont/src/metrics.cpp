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
#include <sge/parse/json/parse_file.hpp>
#include <sge/filesystem/replace_extension.hpp>
#include <sge/font/char_not_available.hpp>
#include <sge/text.hpp>

sge::bitmapfont::metrics::metrics(
	filesystem::path const &path)
:
	line_height_(),
	char_map_()
{
	sge::parse::json::object result;

	parse::json::parse_file(
		filesystem::replace_extension(
			path,
			SGE_TEXT("json")
		),
		result
	);
}

sge::font::char_metric_ptr const
sge::bitmapfont::metrics::load_char(
	char_type const c)
{
	char_map::const_iterator const it(
		char_map_.find(
			c
		)
	);

	if(it == char_map_.end())
		throw font::char_not_available(
			c
		);
	
	return it->second;
}

sge::font::unit
sge::bitmapfont::metrics::line_height() const
{
	return line_height_;
}
