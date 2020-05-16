//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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

template<
	typename Char,
	typename CharTraits
>
sge::image::color::any::object
rgb8_from_hex_string(
	std::basic_string<
		Char,
		CharTraits
	> _string
)
{
	using
	string
	=
	std::basic_string<
		Char,
		CharTraits
	>;

	FCPPT_ASSERT_PRE(
		_string.length() == 7U
		||
		_string.length() == 9U
	);

	// Store the channels in unsigned instead of uint8_t because it
	// might be interpreted as a character instead of a number by the
	// iostreams. Also, store 4 channels, although we might only read
	// 3 in case of rgb.
	using
	channel_array
	=
	std::array<
		unsigned,
		4U
	>;

	channel_array channels;

	// Start at 1, omitting the #
	typename string::size_type current_position{
		1U
	};

	using
	stringstream_type
	=
	std::basic_istringstream<
		Char,
		CharTraits
	>;

	// Initialize the stringstream once for performance
	stringstream_type ss{};

	for(
		auto &channel
		:
		channels
	)
	{
		ss.clear();

		ss.str(
			_string.substr(
				current_position,
				2U
			)
		);

		// We cannot output the color string here without character
		// conversion, sorry.
		if(!(ss >> std::hex >> channel) || !ss.eof())
		{
			throw
				sge::image::exception{
					FCPPT_TEXT("Invalid color component, cannot convert")
				};
		}

		current_position +=
			2U;

		// Stop! Hammer time!
		// We might have only 3 channels
		if(
			current_position == _string.length()
		)
		{
			break;
		}
	}

	using
	channel_type
	=
	sge::image::color::rgb8::format::channel_type;

	return
		_string.length() == 6U // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
		?
			sge::image::color::any::object(
				sge::image::color::rgb8(
					(sge::image::color::init::red() = static_cast<channel_type>(channels[0]))
					(sge::image::color::init::green() = static_cast<channel_type>(channels[1]))
					(sge::image::color::init::blue() = static_cast<channel_type>(channels[2]))
				)
			)
		:
			sge::image::color::any::object(
				sge::image::color::rgba8(
					(sge::image::color::init::red() = static_cast<channel_type>(channels[0]))
					(sge::image::color::init::green() = static_cast<channel_type>(channels[1]))
					(sge::image::color::init::blue() = static_cast<channel_type>(channels[2]))
					(sge::image::color::init::alpha() = static_cast<channel_type>(channels[3]))
				)
			);
}
}

namespace
{

char
widen_if_necessary(
	std::istringstream &,
	char const _c
)
{
	return
		_c;
}

wchar_t
widen_if_necessary(
	std::wistringstream &_ss,
	char const _c
)
{
	return
		_ss.widen(
			_c
		);
}

template<
	typename Char,
	typename CharTraits
>
sge::image::color::any::object
rgb32f_from_string(
	std::basic_string<
		Char,
		CharTraits
	> _string
)
{
	using
	string
	=
	std::basic_string<
		Char,
		CharTraits
	>;

	FCPPT_ASSERT_PRE(
		!_string.empty()
	);

	// Store the channels in unsigned instead of uint8_t because it
	// might be interpreted as a character instead of a number by the
	// iostreams. Also, store 4 channels, although we might only read
	// 3 in case of rgb.
	using
	scalar
	=
	float;

	using
	channel_array
	=
	std::array<
		scalar,
		4U
	>;

	channel_array channels;

	using
	stringstream_type
	=
	std::basic_istringstream<
		Char,
		CharTraits
	>;

	_string.erase(
		_string.begin()
	);

	// Initialize the stringstream once for performance
	stringstream_type ss(
		_string
	);

	if(!(ss >> channels[0] >> std::ws) || static_cast<Char>(ss.peek()) != widen_if_necessary(ss,','))
	{
		throw
			sge::image::exception{
				FCPPT_TEXT("Invalid floating point color string (first channel), cannot convert")
			};
	}

	ss.ignore();

	if(!(ss >> channels[1] >> std::ws) || static_cast<Char>(ss.peek()) != widen_if_necessary(ss,','))
	{
		throw
			sge::image::exception{
				FCPPT_TEXT("Invalid floating point color string (second channel), cannot convert")
			};
	}

	ss.ignore();

	if(!(ss >> channels[2]))
	{
		throw
			sge::image::exception{
				FCPPT_TEXT("Invalid floating point color string (third channel), cannot convert")
			};
	}

	// Only three channels?
	if(static_cast<Char>(ss.peek()) == widen_if_necessary(ss,')'))
	{
		ss.ignore();

		if(!ss.str().substr(static_cast<typename string::size_type>(ss.tellg())).empty())
		{
			throw
				sge::image::exception{
					FCPPT_TEXT("Invalid floating point color string (trailing characters), cannot convert")
				};
		}

		return
			sge::image::color::any::object(
				sge::image::color::rgb32f(
					(sge::image::color::init::red() %= channels[0])
					(sge::image::color::init::green() %= channels[1])
					(sge::image::color::init::blue() %= channels[2])
				)
			);
	}

	if(static_cast<Char>(ss.peek()) != widen_if_necessary(ss,','))
	{
		throw
			sge::image::exception{
				FCPPT_TEXT("Invalid floating point color string (fourth channel separator), cannot convert")
			};
	}

	ss.ignore();

	if(!(ss >> channels[3]))
	{
		throw
			sge::image::exception{
				FCPPT_TEXT("Invalid floating point color string (fourth channel), cannot convert")
			};
	}

	if(static_cast<Char>(ss.peek()) != widen_if_necessary(ss,')'))
	{
		throw
			sge::image::exception{
				FCPPT_TEXT("Invalid floating point color string (end separator), cannot convert")
			};
	}

	ss.ignore();

	if(!ss.str().substr(static_cast<typename string::size_type>(ss.tellg())).empty())
	{
		throw
			sge::image::exception{
				FCPPT_TEXT("Invalid floating point color string (trailing characters), cannot convert")
			};
	}

	return
		sge::image::color::any::object(
			sge::image::color::rgba32f(
				(sge::image::color::init::red() %= channels[0])
				(sge::image::color::init::green() %= channels[1])
				(sge::image::color::init::blue() %= channels[2])
				(sge::image::color::init::alpha() %= channels[3])
			)
		);
}

}

namespace
{

template<
	typename Char,
	typename CharTraits
>
sge::image::color::any::object
from_string_impl(
	std::basic_string<
		Char,
		CharTraits
	> const &_string
)
{
	FCPPT_ASSERT_PRE(
		!_string.empty()
	);

	// FIXME: I only instantiate the stringstream here so I can call widen
	// a few lines below. Isn't there a global widen function?
	using
	stringstream_type
	=
	std::basic_istringstream<
		Char,
		CharTraits
	>;

	stringstream_type ss;

	// Hex color?
	if(_string[0] == widen_if_necessary(ss,'#'))
	{
		return
			rgb8_from_hex_string(
				_string
			);
	}

	return
		rgb32f_from_string(
			_string
		);
}

}

sge::image::color::any::object
sge::image::color::any::from_string(
	std::string const &_string
)
{
	return
		from_string_impl(
			_string
		);
}

sge::image::color::any::object
sge::image::color::any::from_string(
	std::wstring const &_string
)
{
	return
		from_string_impl(
			_string
		);
}
