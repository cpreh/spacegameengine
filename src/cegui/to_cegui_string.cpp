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


#include <sge/cegui/to_cegui_string.hpp>
#include <sge/charconv/convert.hpp>
#include <sge/charconv/encoding.hpp>
#include <fcppt/string.hpp>
#include <fcppt/to_std_wstring.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Base.h>
#include <CEGUI/String.h>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


CEGUI::String
sge::cegui::to_cegui_string(
	fcppt::string const &_string
)
{
	if(
		_string.empty()
	)
		return
			CEGUI::String();

	return
		CEGUI::String(
			sge::charconv::convert
			<
				sge::charconv::encoding::utf8,
				sge::charconv::encoding::wchar
			>(
				fcppt::to_std_wstring(
					_string
				)
			).c_str()
		);
}
