/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "string_square.hpp"
#include <sge/gui/unit.hpp>
#include <sge/font/text/lit.hpp>
#include <fcppt/math/dim/basic_impl.hpp>

sge::font::text::string const
sge::gui::utility::string_square(
	dim const &s
)
{
	sge::font::text::string const line(
		static_cast<sge::font::text::string::size_type>(s.w()),
		FCPPT_TEXT('W')
	);

	sge::font::text::string result;
	for (unit i = 0; i < s.h(); ++i)
		result += line + SGE_FONT_TEXT_LIT('\n');
	return result;
}
