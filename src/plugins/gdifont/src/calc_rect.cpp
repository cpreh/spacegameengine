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


#include <sge/font/optional_unit.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/string.hpp>
#include <sge/font/unit.hpp>
#include <sge/gdifont/calc_rect.hpp>
#include <sge/gdifont/device_context_fwd.hpp>
#include <sge/gdifont/draw_text.hpp>
#include <sge/gdifont/include_windows.hpp>


sge::font::rect const
sge::gdifont::calc_rect(
	sge::gdifont::device_context const &_device_context,
	sge::font::string const &_string,
	sge::font::optional_unit const &_max_width,
	UINT const _format
)
{
	RECT result;

	sge::gdifont::draw_text(
		_device_context,
		_string,
		result,
		_format
		|
		DT_CALCRECT
	);

	sge::font::unit const width(
		static_cast<
			sge::font::unit
		>(
			result.right - result.left
		)
	);

	sge::font::unit const height(
		static_cast<
			sge::font::unit
		>(
			result.bottom - result.top
		)
	);

	return
		sge::font::rect(
			sge::font::rect::vector(
				_format & DT_RIGHT
				?
					*_max_width
					- width
				:
					0
				,
				0
			),
			sge::font::rect::dim(
				width,
				height
			)
		);
}
