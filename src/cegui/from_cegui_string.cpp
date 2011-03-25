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


#include <sge/cegui/from_cegui_string.hpp>
#include <CEGUI/CEGUIBase.h>
#include <sge/charconv/convert.hpp>
#include <sge/charconv/encoding.hpp>
#include <sge/charconv/string_type.hpp>
#include <fcppt/from_std_wstring.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <iostream>

fcppt::string const
sge::cegui::from_cegui_string(
	CEGUI::String const &s,
	sge::charconv::system_ptr const charconv)
{
	typedef
	sge::charconv::string_type<sge::charconv::encoding::utf32>::type
	source_string;

	BOOST_STATIC_ASSERT((
		boost::is_same
		<
			source_string::value_type,
			CEGUI::utf32
		>::value));

	typedef
	sge::charconv::string_type<sge::charconv::encoding::wchar>::type
	dest_string;

	dest_string d = 
		sge::charconv::convert
			<
				sge::charconv::encoding::wchar, 
				sge::charconv::encoding::utf32
			>(
				charconv,
				source_string(
					s.begin(),
					s.end()));

	return fcppt::from_std_wstring(d);
}
