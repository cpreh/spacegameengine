/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include "../../../heap_deleter.hpp"
#include "../font_system.hpp"
#include "../font_metrics.hpp"

sge::font_metrics_ptr sge::ft::font_system::create_font(const std::string& font_name, const unsigned font_size)
{
	loaded_fonts_list::mapped_type &wfptr = loaded_fonts[
		loaded_fonts_list::key_type(
			font_size,
			font_name
		)
	];

	font_metrics_ptr fptr(wfptr.lock());
	if (!fptr)
	{
		fptr.reset(new font_metrics(_library, font_name, font_size));
		wfptr = fptr.get_boost_ptr();
	}
	return fptr;
}
