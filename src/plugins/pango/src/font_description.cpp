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


#include <sge/font/ttf_size.hpp>
#include <sge/font/weight/unit.hpp>
#include <sge/pango/font_description.hpp>
#include <fcppt/string.hpp>
#include <fcppt/to_std_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pango/pango-font.h>
#include <glib.h>
#include <fcppt/config/external_end.hpp>


sge::pango::font_description::font_description()
:
	impl_(
		::pango_font_description_new()
	)
{
}

sge::pango::font_description::~font_description()
{
	::pango_font_description_free(
		impl_
	);
}

void
sge::pango::font_description::ttf_size(
	sge::font::ttf_size const _ttf_size
)
{
	::pango_font_description_set_size(
		impl_,
		static_cast<
			gint
		>(
			_ttf_size
		)
	);
}

void
sge::pango::font_description::family(
	fcppt::string const &_family
)
{
	::pango_font_description_set_family(
		impl_,
		fcppt::to_std_string(
			_family
		).c_str()
	);
}

void
sge::pango::font_description::weight(
	sge::font::weight::unit const _weight
)
{
	::pango_font_description_set_weight(
		impl_,
		static_cast<
			PangoWeight
		>(
			_weight
		)
	);
}

void
sge::pango::font_description::italic()
{
	::pango_font_description_set_style(
		impl_,
		PANGO_STYLE_ITALIC
	);
}

PangoFontDescription *
sge::pango::font_description::get()
{
	return impl_;
}
