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


#include "log.hpp"
#include <sge/gui/canvas/object.hpp>
#include <sge/gui/canvas/font_drawer.hpp>
#include <sge/font/object.hpp>
#include <sge/font/text_size.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/assert.hpp>
#include <fcppt/text.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <algorithm>

void sge::gui::canvas::object::draw_text(
	font_info const &font,
	fcppt::string const &text,
	point const &pos,
	dim const &max_size,
	font::align_h::type const h,
	font::align_v::type const v,
	font::flag_t const f,
	optional_character_pos cp,
	point *const p)
{
	FCPPT_ASSERT(!cp || *cp < text.length());

	// determine which invisible characters have to be filtered
	if (cp)
	{
		fcppt::string::size_type const filter =
			std::count(
				text.begin(),
				text.begin()+(*cp)+1,
				FCPPT_TEXT('\n'));

		cp = (*cp) - filter;
	}

	font::object(
		font.metrics(),
		fcppt::make_shared_ptr<
			canvas::font_drawer
		>(
			std::tr1::ref(
				view_
			),
			font.color(),
			cp,
			p
		)
	).draw_text(
		text,
		pos,
		max_size,
		h,
		v,
		f
	);
}
