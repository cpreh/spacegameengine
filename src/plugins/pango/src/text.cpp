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


#include <sge/charconv/system_fwd.hpp>
#include <sge/font/flags.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/view_fwd.hpp>
#include <sge/pango/create_text_layout.hpp>
#include <sge/pango/glib_deleter.hpp>
#include <sge/pango/ink_rect.hpp>
#include <sge/pango/text.hpp>
#include <sge/pango/freetype/make_bitmap.hpp>
#include <fcppt/null_ptr.hpp>
#include <fcppt/scoped_ptr_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pango/pango-layout.h>
#include <pango/pangoft2.h>
#include <fcppt/config/external_end.hpp>


sge::pango::text::text(
	sge::charconv::system &_charconv_system,
	PangoLayout &_layout,
	sge::font::string const &_string,
	sge::font::text_parameters const &_text_parameters
)
:
	layout_(
		sge::pango::create_text_layout(
			_charconv_system,
			_layout,
			_string,
			_text_parameters
		)
	),
	no_multi_line_(
		_text_parameters.flags()
		&
		sge::font::flags::no_multi_line
	),
	ink_rect_(
		sge::pango::ink_rect(
			*layout_
		)
	)
{
}

sge::pango::text::~text()
{
}

void
sge::pango::text::render(
	sge::font::view const &_view
)
{
	FT_Bitmap bitmap(
		sge::pango::freetype::make_bitmap(
			_view
		)
	);

	int const pos_x(
		- ink_rect_.left()
	);

	int const pos_y(
		- ink_rect_.top()
	);

	if(
		no_multi_line_
	)
	{
		PangoLayoutLine *const line(
			::pango_layout_get_line(
				layout_.get(),
				0
			)
		);

		if(
			line == fcppt::null_ptr()
		)
			return;

		::pango_ft2_render_layout_line(
			&bitmap,
			line,
			pos_x,
			pos_y
		);
	}
	else
		::pango_ft2_render_layout(
			&bitmap,
			layout_.get(),
			pos_x,
			pos_y
		);
}

sge::font::rect const
sge::pango::text::rect()
{
	return ink_rect_;
}
