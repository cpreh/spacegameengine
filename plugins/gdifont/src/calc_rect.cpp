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


#include <sge/font/rect.hpp>
#include <sge/font/string.hpp>
#include <sge/font/align_h/center.hpp>
#include <sge/font/align_h/extract_max_width.hpp>
#include <sge/font/align_h/left_fwd.hpp>
#include <sge/font/align_h/right.hpp>
#include <sge/font/align_h/variant.hpp>
#include <sge/gdifont/calc_rect.hpp>
#include <sge/gdifont/device_context_fwd.hpp>
#include <sge/gdifont/draw_text.hpp>
#include <sge/gdifont/format.hpp>
#include <sge/gdifont/include_windows.hpp>
#include <sge/gdifont/scoped_select.hpp>
#include <fcppt/const.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/variant/match.hpp>


sge::font::rect
sge::gdifont::calc_rect(
	sge::gdifont::device_context const &_device_context,
	HFONT const _font,
	sge::font::string const &_string,
	sge::font::align_h::variant const &_align_h,
	sge::gdifont::format const _format
)
{
	sge::gdifont::scoped_select const select_font(
		_device_context,
		_font
	);

	LONG const zero{
		0
	};

	RECT const result{
		sge::gdifont::draw_text(
			_device_context,
			_string,
			RECT{
				zero,
				zero,
				fcppt::optional::maybe(
					sge::font::align_h::extract_max_width(
						_align_h
					),
					fcppt::const_(
						zero
					),
					[](
						sge::font::align_h::max_width const _max_width
					)
					{
						return
							fcppt::cast::size<
								LONG
							>(
								_max_width.get()
							);
					}
				),
				zero
			},
			_format.get()
			|
			DT_CALCRECT
		)
	};

	FCPPT_ASSERT_ERROR(
		result.left
		==
		zero
		&&
		result.top
		==
		zero
	);

	LONG const width{
		result.right
	};

	LONG const pos_x{
		fcppt::variant::match(
			_align_h,
			[
				zero
			](
				sge::font::align_h::left const &
			)
			{
				return
					zero;
			},
			[
				width
			](
				sge::font::align_h::center const &_center
			)
			{
				return
					(
						fcppt::cast::size<
							LONG
						>(
							_center.max_width().get()
						)
						-
						width
					)
					/
					LONG{
						2
					};
			},
			[
				width
			](
				sge::font::align_h::right const &_right
			)
			{
				return
					fcppt::cast::size<
						LONG
					>(
						_right.max_width().get()
					)
					-
					width;
			}
		)
	};

	return
		sge::font::rect(
			sge::font::rect::vector(
				fcppt::cast::size<
					sge::font::rect::value_type
				>(
					pos_x
				),
				fcppt::cast::size<
					sge::font::rect::value_type
				>(
					zero
				)
			),
			sge::font::rect::dim(
				fcppt::cast::size<
					sge::font::rect::value_type
				>(
					pos_x
					+
					width
				),
				fcppt::cast::size<
					sge::font::rect::value_type
				>(
					result.bottom
				)
			)
		);
}
