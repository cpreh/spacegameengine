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


#include <sge/charconv/utf8_string.hpp>
#include <sge/charconv/utf8_string_to_fcppt.hpp>
#include <sge/charconv/impl/fcppt_is_utf8.hpp>
#include <fcppt/optional_string.hpp>
#include <fcppt/string.hpp>
#if !defined(SGE_CHARCONV_IMPL_FCPPT_IS_UTF8)
#include <sge/charconv/convert.hpp>
#include <sge/charconv/encoding.hpp>
#include <fcppt/from_std_wstring.hpp>
#endif


fcppt::optional_string
sge::charconv::utf8_string_to_fcppt(
	sge::charconv::utf8_string const &_string
)
{
#if defined(SGE_CHARCONV_IMPL_FCPPT_IS_UTF8)
	return
		fcppt::optional_string{
			fcppt::string{
				_string.begin(),
				_string.end()
			}
		};
#else
	return
		fcppt::from_std_wstring(
			sge::charconv::convert<
				sge::charconv::encoding::wchar,
				sge::charconv::encoding::utf8
			>(
				_string
			)
		);
#endif
}
