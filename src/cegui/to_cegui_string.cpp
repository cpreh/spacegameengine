/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <fcppt/to_std_wstring.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/static_assert.hpp>
#include <string>

CEGUI::String const
sge::cegui::to_cegui_string(
	fcppt::string const &s,
	sge::charconv::system_ptr const charconv)
{
	typedef
	sge::charconv::string_type<sge::charconv::encoding::utf8>::type
	utf8_string;

	BOOST_STATIC_ASSERT((
		boost::is_same
		<
			utf8_string::value_type,
			CEGUI::utf8
		>::value));

	return 
		CEGUI::String(
			sge::charconv::convert
			<
				sge::charconv::encoding::utf8, 
				sge::charconv::encoding::wchar
			>(
				charconv,
				fcppt::to_std_wstring(
					s)).c_str());
}
