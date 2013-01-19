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


#include <sge/font/text_parameters.hpp>
#include <sge/gdifont/format.hpp>
#include <sge/gdifont/include_windows.hpp>
#include <sge/gdifont/make_flags.hpp>
#include <sge/gdifont/convert/align_h.hpp>
#include <sge/gdifont/convert/flags.hpp>


sge::gdifont::format const
sge::gdifont::make_flags(
	sge::font::text_parameters const &_parameters
)
{
	return
		sge::gdifont::format(
			sge::gdifont::convert::flags(
				_parameters.flags()
			)
			|
			sge::gdifont::convert::align_h(
				_parameters.align_h()
			)
		);
}
