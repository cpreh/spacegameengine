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


#include <sge/font/rect.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/view_fwd.hpp>
#include <sge/src/font/bitmap/char_map.hpp>
#include <sge/src/font/bitmap/text.hpp>


sge::font::bitmap::text::text(
	sge::font::bitmap::char_map &_char_map,
	sge::font::string const &_string,
	sge::font::text_parameters const &_text_parameters
)
:
	char_map_(
		_char_map
	),
	string_(
		_string
	),
	text_parameters_(
		_text_parameters
	)
{
}

sge::font::bitmap::text::~text()
{
}

void
sge::font::bitmap::text::render(
	sge::font::view const &_view
)
{
}

sge::font::rect const
sge::font::bitmap::text::rect()
{
}
