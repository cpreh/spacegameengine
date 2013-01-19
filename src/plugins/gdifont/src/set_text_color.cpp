/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/gdifont/device_context.hpp>
#include <sge/gdifont/include_windows.hpp>
#include <sge/gdifont/set_text_color.hpp>
#include <fcppt/text.hpp>


void
sge::gdifont::set_text_color(
	sge::gdifont::device_context const &_device_context,
	COLORREF const _color
)
{
	if(
		::SetTextColor(
			_device_context.get(),
			_color
		)
		==
		CLR_INVALID
	)
		throw sge::font::exception(
			FCPPT_TEXT("SetTextColor failed")
		);
}
