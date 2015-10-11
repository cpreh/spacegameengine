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


#ifndef SGE_IMAGE_COLOR_RGB8_FROM_HEX_STRING_HPP_INCLUDED
#define SGE_IMAGE_COLOR_RGB8_FROM_HEX_STRING_HPP_INCLUDED

#include <sge/image/exception.hpp>
#include <sge/image/color/rgb8.hpp>
#include <sge/image/color/init/blue.hpp>
#include <sge/image/color/init/green.hpp>
#include <sge/image/color/init/red.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <iomanip>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace image
{
namespace color
{
// NOTES
// -----
//
// - I deliberately decided not to use fcppt::type_traits::is_string here to reduce compile time.
// - I wasn't sure if this function might be called for a string that
//   is not std::string or std::wstring (like a utf8 string), so I
//   kept this a template instead of two overloaded functions.
template<typename String>
sge::image::color::rgb8
rgb8_from_hex_string(
	String const &_string)
{
	FCPPT_ASSERT_PRE(
		_string.length() == 6u);

	// Store the channels in unsigned instead of uint8_t because it
	// might be interpreted as a character instead of a number by the
	// iostreams
	typedef
	std::array<unsigned,3u>
	channel_array;

	channel_array channels;

	std::string::size_type current_position =
		0u;

	typedef
	std::basic_istringstream<typename String::value_type,typename String::traits_type>
	stringstream_type;

	// Initialize the stringstream once for performance
	stringstream_type ss;

	for(
		auto &channel : channels)
	{
		ss.clear();
		ss.str(
			_string.substr(
				current_position,
				2u));
		// We cannot output the color string here without character
		// conversion, sorry.
		if(!(ss >> std::hex >> channel) || !ss.eof())
			throw sge::image::exception(
				FCPPT_TEXT("Invalid color component, cannot convert"));

		current_position +=
			2u;
	}

	typedef
	sge::image::color::rgb8::format::channel_type
	channel_type;

	return
		sge::image::color::rgb8(
			(sge::image::color::init::red() = static_cast<channel_type>(channels[0]))
			(sge::image::color::init::green() = static_cast<channel_type>(channels[1]))
			(sge::image::color::init::blue() = static_cast<channel_type>(channels[2])));
}
}
}
}

#endif
