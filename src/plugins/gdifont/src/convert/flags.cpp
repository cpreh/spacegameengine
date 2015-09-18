/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/font/flags.hpp>
#include <sge/font/flags_field.hpp>
#include <sge/gdifont/include_windows.hpp>
#include <sge/gdifont/convert/flags.hpp>
#include <fcppt/container/bitfield/operators.hpp>


UINT
sge::gdifont::convert::flags(
	sge::font::flags_field const &_flags
)
{
	DWORD ret(
		0u
	);

	if(
		_flags
		&
		sge::font::flags::no_multi_line
	)
		ret |= DT_SINGLELINE;

	if(
		!(
			_flags
			&
			sge::font::flags::no_word_wrap
		)
	)
		ret |= DT_WORDBREAK;

	return ret;
}
