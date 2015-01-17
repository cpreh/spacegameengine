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


#include <sge/image/exception.hpp>
#include <sge/image/color/rgb32f.hpp>
#include <sge/image/color/rgb8.hpp>
#include <sge/image/color/rgba32f.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/any/from_string.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image/color/init/alpha.hpp>
#include <sge/image/color/init/blue.hpp>
#include <sge/image/color/init/green.hpp>
#include <sge/image/color/init/red.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <istream>
#include <sstream>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace
{
template<typename Char,typename CharTraits>
sge::image::color::any::object const
rgb8_from_hex_string(
	std::basic_string<Char,CharTraits> _string)
{
	typedef
	std::basic_string<Char,CharTraits>
	string;

	FCPPT_ASSERT_PRE(
		_string.length() == 7u || _string.length() == 9u);

	// Store the channels in unsigned instead of uint8_t because it
	// might be interpreted as a character instead of a number by the
	// iostreams. Also, store 4 channels, although we might only read
	// 3 in case of rgb.
	typedef
	std::array<unsigned,4u>
	channel_array;

	channel_array channels;

	// Start at 1, omitting the #
	typename string::size_type current_position =
		1u;

	typedef
	std::basic_istringstream<Char,CharTraits>
	stringstream_type;

	// Initialize the stringstream once for performance
	stringstream_type ss;

	for(
		channel_array::iterator it =
			channels.begin();
		it != channels.end();
		++it)
	{
		ss.clear();
		ss.str(
			_string.substr(
				current_position,
				2u));

		// We cannot output the color string here without character
		// conversion, sorry.
		if(!(ss >> std::hex >> (*it)) || !ss.eof())
			throw
				sge::image::exception(
					FCPPT_TEXT("Invalid color component, cannot convert"));

		current_position +=
			2u;

		// Stop! Hammer time!
		// We might have only 3 channels
		if(current_position == _string.length())
			break;
	}

	typedef
	sge::image::color::rgb8::format::channel_type
	channel_type;

	return
		_string.length() == 6u
		?
			sge::image::color::any::object(
				sge::image::color::rgb8(
					(sge::image::color::init::red() = static_cast<channel_type>(channels[0]))
					(sge::image::color::init::green() = static_cast<channel_type>(channels[1]))
					(sge::image::color::init::blue() = static_cast<channel_type>(channels[2]))))
		:
			sge::image::color::any::object(
				sge::image::color::rgba8(
					(sge::image::color::init::red() = static_cast<channel_type>(channels[0]))
					(sge::image::color::init::green() = static_cast<channel_type>(channels[1]))
					(sge::image::color::init::blue() = static_cast<channel_type>(channels[2]))
					(sge::image::color::init::alpha() = static_cast<channel_type>(channels[3]))));
}
}

namespace
{
char
widen_if_necessary(
	std::istringstream &,
	char const _c)
{
	return
		_c;
}

wchar_t
widen_if_necessary(
	std::wistringstream &_ss,
	char const _c)
{
	return
		_ss.widen(
			_c);
}

template<typename Char,typename CharTraits>
sge::image::color::any::object const
rgb32f_from_string(
	std::basic_string<Char,CharTraits> _string)
{
	typedef
	std::basic_string<Char,CharTraits>
	string;

	FCPPT_ASSERT_PRE(
		!_string.empty());

	// Store the channels in unsigned instead of uint8_t because it
	// might be interpreted as a character instead of a number by the
	// iostreams. Also, store 4 channels, although we might only read
	// 3 in case of rgb.
	typedef
	float
	scalar;

	typedef
	std::array<scalar,4u>
	channel_array;

	channel_array channels;

	typedef
	std::basic_istringstream<Char,CharTraits>
	stringstream_type;

	_string.erase(
		_string.begin());

	// Initialize the stringstream once for performance
	stringstream_type ss(
		_string);

	if(!(ss >> channels[0] >> std::ws) || static_cast<Char>(ss.peek()) != widen_if_necessary(ss,','))
		throw
			sge::image::exception(
				FCPPT_TEXT("Invalid floating point color string (first channel), cannot convert"));

	ss.ignore();

	if(!(ss >> channels[1] >> std::ws) || static_cast<Char>(ss.peek()) != widen_if_necessary(ss,','))
		throw
			sge::image::exception(
				FCPPT_TEXT("Invalid floating point color string (second channel), cannot convert"));

	ss.ignore();

	if(!(ss >> channels[2]))
		throw
			sge::image::exception(
				FCPPT_TEXT("Invalid floating point color string (third channel), cannot convert"));

	// Only three channels?
	if(static_cast<Char>(ss.peek()) == widen_if_necessary(ss,')'))
	{
		ss.ignore();

		if(!ss.str().substr(static_cast<typename string::size_type>(ss.tellg())).empty())
			throw
				sge::image::exception(
					FCPPT_TEXT("Invalid floating point color string (trailing characters), cannot convert"));

		return
			sge::image::color::any::object(
				sge::image::color::rgb32f(
					(sge::image::color::init::red() %= channels[0])
					(sge::image::color::init::green() %= channels[1])
					(sge::image::color::init::blue() %= channels[2])));
	}

	if(static_cast<Char>(ss.peek()) != widen_if_necessary(ss,','))
		throw
			sge::image::exception(
				FCPPT_TEXT("Invalid floating point color string (fourth channel separator), cannot convert"));

	ss.ignore();

	if(!(ss >> channels[3]))
		throw
			sge::image::exception(
				FCPPT_TEXT("Invalid floating point color string (fourth channel), cannot convert"));

	if(static_cast<Char>(ss.peek()) != widen_if_necessary(ss,')'))
		throw
			sge::image::exception(
				FCPPT_TEXT("Invalid floating point color string (end separator), cannot convert"));

	ss.ignore();

	if(!ss.str().substr(static_cast<typename string::size_type>(ss.tellg())).empty())
		throw
			sge::image::exception(
				FCPPT_TEXT("Invalid floating point color string (trailing characters), cannot convert"));

	return
		sge::image::color::any::object(
			sge::image::color::rgba32f(
				(sge::image::color::init::red() %= channels[0])
				(sge::image::color::init::green() %= channels[1])
				(sge::image::color::init::blue() %= channels[2])
				(sge::image::color::init::alpha() %= channels[3])));
}
}

namespace
{
template<typename Char,typename CharTraits>
sge::image::color::any::object const
from_string_impl(
	std::basic_string<Char,CharTraits> const &_string)
{
	FCPPT_ASSERT_PRE(
		!_string.empty());

	// FIXME: I only instantiate the stringstream here so I can call widen
	// a few lines below. Isn't there a global widen function?
	typedef
	std::basic_istringstream<Char,CharTraits>
	stringstream_type;

	stringstream_type ss;

	// Hex color?
	if(_string[0] == widen_if_necessary(ss,'#'))
		return
			rgb8_from_hex_string(
				_string);

	return
		rgb32f_from_string(
			_string);
}
}

sge::image::color::any::object const
sge::image::color::any::from_string(
	std::string const &_string)
{
	return
		from_string_impl(
			_string);
}

sge::image::color::any::object const
sge::image::color::any::from_string(
	std::wstring const &_string)
{
	return
		from_string_impl(
			_string);
}
