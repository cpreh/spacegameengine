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


#include <sge/charconv/fcppt_string_to_utf8.hpp>
#include <sge/charconv/utf8_string.hpp>
#include <sge/src/charconv/fcppt_is_utf8.hpp>
#include <fcppt/string.hpp>
#if !defined(SGE_CHARCONV_FCPPT_IS_UTF8)
#include <sge/charconv/convert.hpp>
#include <sge/charconv/encoding.hpp>
#include <fcppt/to_std_wstring.hpp>
#endif


sge::charconv::utf8_string
sge::charconv::fcppt_string_to_utf8(
	fcppt::string const &_string
)
{
	return
#if defined(SGE_CHARCONV_FCPPT_IS_UTF8)
		sge::charconv::utf8_string(
			_string.begin(),
			_string.end()
		);
#else
		sge::charconv::convert<
			sge::charconv::encoding::utf8,
			sge::charconv::encoding::wchar
		>(
			fcppt::to_std_wstring(
				_string
			)
		);
#endif
}
