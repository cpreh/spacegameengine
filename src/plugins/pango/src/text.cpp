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


#include <sge/font/ascent.hpp>
#include <sge/font/dim.hpp>
#include <sge/font/flags.hpp>
#include <sge/font/index.hpp>
#include <sge/font/optional_index.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/vector.hpp>
#include <sge/font/view_fwd.hpp>
#include <sge/image/color/a8.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image/color/init/alpha.hpp>
#include <sge/image2d/algorithm/fill.hpp>
#include <sge/pango/create_text_layout.hpp>
#include <sge/pango/get_extents.hpp>
#include <sge/pango/text.hpp>
#include <sge/pango/convert/from_rect_scale.hpp>
#include <sge/pango/convert/to_unit.hpp>
#include <sge/pango/freetype/make_bitmap.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pango/pango-layout.h>
#include <pango/pangoft2.h>
#include <fcppt/config/external_end.hpp>


sge::pango::text::text(
	PangoLayout &_layout,
	sge::font::ascent const _ascent,
	sge::font::string const &_string,
	sge::font::text_parameters const &_text_parameters
)
:
	ascent_{
		_ascent
	},
	layout_(
		sge::pango::create_text_layout(
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
	extents_(
		sge::pango::get_extents(
			*layout_,
			no_multi_line_
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

	// TODO: do this properly
	sge::image2d::algorithm::fill(
		_view,
		sge::image::color::any::object(
			sge::image::color::a8(
				sge::image::color::init::alpha() %= 0.f
			)
		)
	);

	int const pos_x(
		fcppt::cast::size<
			int
		>(
			- extents_.ink_rect().get().left()
		)
	);

	int const pos_y(
		fcppt::cast::size<
			int
		>(
			- extents_.ink_rect().get().top()
		)
	);

	if(
		no_multi_line_.get()
	)
	{
		PangoLayoutLine *const line(
			::pango_layout_get_line(
				layout_.get(),
				0
			)
		);

		if(
			line
			==
			nullptr
		)
			return;

		// Line extents start at the base line while layout extents
		// start at the top-left
		::pango_ft2_render_layout_line(
			&bitmap,
			line,
			pos_x,
			pos_y
			-
			ascent_.get()
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
sge::pango::text::rect() const
{
	return
		extents_.ink_rect().get();
}

sge::font::dim const
sge::pango::text::logical_size() const
{
	return
		extents_.logical_rect().get().size();
}

sge::font::rect const
sge::pango::text::cursor_rect(
	sge::font::index const _index
) const
{
	PangoRectangle
		strong_pos,
		weak_pos;

	::pango_layout_get_cursor_pos(
		layout_.get(),
		fcppt::cast::size<
			int
		>(
			fcppt::cast::to_signed(
				_index
			)
		),
		&strong_pos,
		&weak_pos
	);

	return
		sge::pango::convert::from_rect_scale(
			strong_pos
		);
}

sge::font::optional_index const
sge::pango::text::pos_to_index(
	sge::font::vector const _pos
) const
{
	int result;

	int trailing;

	return
		::pango_layout_xy_to_index(
			layout_.get(),
			sge::pango::convert::to_unit(
				_pos.x()
			),
			sge::pango::convert::to_unit(
				_pos.y()
			),
			&result,
			&trailing
		)
		==
		TRUE
		?
			sge::font::optional_index(
				fcppt::cast::to_unsigned(
					trailing
					+
					result
				)
			)
		:
			sge::font::optional_index()
		;
}
