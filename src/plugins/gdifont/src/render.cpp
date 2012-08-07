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
#include <sge/font/string.hpp>
#include <sge/gdifont/device_context_fwd.hpp>
#include <sge/gdifont/draw_text.hpp>
#include <sge/gdifont/include_windows.hpp>
#include <sge/gdifont/render.hpp>
#include <fcppt/config/external_begin.hpp>
#include <limits>
#include <fcppt/config/external_end.hpp>


void
sge::gdifont::render(
	sge::gdifont::device_context const &_device_context,
	sge::font::string const &_string,
	sge::font::optional_unit const &_optional_width,
	UINT const _format
)
{
	sge::font::unit const max_unit(
		std::numeric_limits<
			sge::font::unit
		>::max()
	);

	RECT source;

	source.left = 0;
	
	source.top = 0;

	source.right = 
		_optional_width
		?
			*_optional_width
		:
			max_unit
		;

	source.bottom = max_unit;

	sge::gdifont::draw_text(
		_device_context,
		_string,
		source,
		_format
	);
}
