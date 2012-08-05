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


#include <sge/charconv/convert.hpp>
#include <sge/charconv/encoding.hpp>
#include <sge/charconv/system_fwd.hpp>
#include <sge/charconv/utf8_string.hpp>
#include <sge/font/flags.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/pango/create_text_layout.hpp>
#include <sge/pango/glib_deleter.hpp>
#include <sge/pango/pango_layout_unique_ptr.hpp>
#include <sge/pango/convert/alignment.hpp>
#include <sge/pango/convert/to_unit.hpp>
#include <fcppt/move.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pango/pango-layout.h>
#include <fcppt/config/external_end.hpp>


sge::pango::pango_layout_unique_ptr
sge::pango::create_text_layout(
	sge::charconv::system &_charconv_system,
	PangoLayout &_layout,
	sge::font::string const &_string,
	sge::font::text_parameters const &_text_parameters
)
{
	sge::pango::pango_layout_unique_ptr layout(
		::pango_layout_copy(
			&_layout
		)
	);

	{
		sge::charconv::utf8_string const converted_string(
			sge::charconv::convert<
				sge::charconv::encoding::utf8,
				sge::charconv::encoding::wchar
			>(
				_charconv_system,
				_string
			)
		);

		::pango_layout_set_text(
			layout.get(),
			reinterpret_cast<
				char const *
			>(
				converted_string.data()
			),
			static_cast<
				int
			>(
				converted_string.size()
			)
		);
	}

	::pango_layout_set_alignment(
		layout.get(),
		sge::pango::convert::alignment(
			_text_parameters.align_h()
		)
	);

	if(
		_text_parameters.max_width()
	)
		::pango_layout_set_width(
			layout.get(),
			sge::pango::convert::to_unit(
				*_text_parameters.max_width()
			)
		);

	::pango_layout_set_wrap(
		layout.get(),
		(
			_text_parameters.flags()
			&
			sge::font::flags::no_word_wrap
		)
		?
			PANGO_WRAP_CHAR
		:
			PANGO_WRAP_WORD
	);

	::pango_layout_set_ellipsize(
		layout.get(),
		PANGO_ELLIPSIZE_NONE
	);

	::pango_layout_set_indent(
		layout.get(),
		0
	);

	return
		fcppt::move(
			layout
		);
}
