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


#include <sge/font/align_h.hpp>
#include <sge/font/optional_unit.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/string.hpp>
#include <sge/gdifont/calc_rect.hpp>
#include <sge/gdifont/device_context_fwd.hpp>
#include <sge/gdifont/draw_text.hpp>
#include <sge/gdifont/format.hpp>
#include <sge/gdifont/include_windows.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <limits>
#include <fcppt/config/external_end.hpp>


sge::font::rect const
sge::gdifont::calc_rect(
	sge::gdifont::device_context const &_device_context,
	sge::font::string const &_string,
	sge::font::align_h::type const _align_h,
	sge::font::optional_unit const &_max_width,
	sge::gdifont::format const _format
)
{
	LONG const max_unit(
		std::numeric_limits<
			LONG
		>::max()
	);

	RECT result =
	{
		0,
		0,
		_max_width
		?
			static_cast<
				LONG
			>(
				*_max_width
			)
		:
			max_unit
		,
		max_unit
	};

	sge::gdifont::draw_text(
		_device_context,
		_string,
		result,
		_format.get()
		|
		DT_CALCRECT
	);

	FCPPT_ASSERT_ERROR(
		result.left == 0
		&&
		result.top == 0
	);

	switch(
		_align_h
	)
	{
	case sge::font::align_h::left:
		break;
	case sge::font::align_h::right:
		result.left = *_max_width - result.right;

		result.right = *_max_width;

		break;
	case sge::font::align_h::center:
		result.left = (*_max_width - result.right) / 2;

		result.right = (*_max_width + result.right) / 2;

		break;	
	}

	return
		sge::font::rect(
			sge::font::rect::vector(
				static_cast<
					sge::font::rect::value_type
				>(
					result.left
				),
				static_cast<
					sge::font::rect::value_type
				>(
					result.top
				)
			),
			sge::font::rect::dim(
				static_cast<
					sge::font::rect::value_type
				>(
					result.right - result.left
				),
				static_cast<
					sge::font::rect::value_type
				>(
					result.bottom - result.top
				)
			)
		);
}
