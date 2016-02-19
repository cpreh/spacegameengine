/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/font/parameters.hpp>
#include <sge/font/ttf_size.hpp>
#include <sge/font/weight/unit.hpp>
#include <sge/pango/create_layout.hpp>
#include <sge/pango/font_description.hpp>
#include <sge/pango/glib_deleter.hpp>
#include <sge/pango/pango_layout_unique_ptr.hpp>
#include <fcppt/string.hpp>
#include <fcppt/optional/maybe_void.hpp>
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

	fcppt::optional::maybe_void(
		_parameters.ttf_size(),
		[
			&font_description
		](
			sge::font::ttf_size const _ttf_size
		)
		{
			font_description.ttf_size(
				_ttf_size
				*
				PANGO_SCALE
			);
		}
	);

	fcppt::optional::maybe_void(
		_parameters.family(),
		[
			&font_description
		](
			fcppt::string const &_family
		)
		{
			font_description.family(
				_family
			);
		}
	);

	fcppt::optional::maybe_void(
		_parameters.weight(),
		[
			&font_description
		](
			sge::font::weight::unit const _weight
		)
		{
			font_description.weight(
				_weight
			);
		}
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
		result.get_pointer(),
		font_description.get()
	);

	return
		result;
}
