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


#include <sge/font/exception.hpp>
#include <sge/font/parameters.hpp>
#include <sge/font/parameters_to_string.hpp>
#include <sge/pango/create_layout.hpp>
#include <sge/pango/font_description.hpp>
#include <sge/pango/glib_deleter.hpp>
#include <sge/pango/pango_layout_unique_ptr.hpp>
#include <fcppt/move.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pango/pango-layout.h>
#include <pango/pango-types.h>
#include <fcppt/config/external_end.hpp>


sge::pango::pango_layout_unique_ptr
sge::pango::create_layout(
	PangoContext &_context,
	sge::font::parameters const &_parameters
)
{
	sge::pango::font_description font_description;

	if(
		_parameters.ttf_size()
	)
		font_description.ttf_size(
			*_parameters.ttf_size()
		);

	if(
		_parameters.family()
	)
		font_description.family(
			*_parameters.family()
		);

	if(
		_parameters.weight()
	)
		font_description.weight(
			*_parameters.weight()
		);

	if(
		_parameters.italic()
	)
		font_description.italic();

	sge::pango::pango_layout_unique_ptr result(
		::pango_layout_new(
			&_context
		)
	);

	::pango_layout_set_font_description(
		result.get(),
		font_description.get()
	);

	/*
	if(
		!result
	)
		throw sge::font::exception(
			FCPPT_TEXT("Nothing matched the following font: ")
			+
			sge::font::parameters_to_string(
				_parameters
			)
		);*/

	return
		fcppt::move(
			result
		);
}
