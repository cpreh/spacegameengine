/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../keyboard_keys.hpp"
#include "../translation.hpp"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <sge/x11/sentry.hpp>
#include <sge/input/key_type.hpp>
#include <sge/log/headers.hpp>
#include <sge/log/global.hpp>
#include <fcppt/text.hpp>
#include <sge/string.hpp>
#include <sge/iconv.hpp>
#include <tr1/array>
#include <map>
#include <ostream>
#include <utility>
#include <limits>

namespace
{

sge::string const
get_key_name(
	KeySym const ks);

}

sge::input::key_type const
sge::x11input::keyboard_key(
	XKeyEvent const &xev)
{
	XComposeStatus state;
	KeySym ks;
	std::tr1::array<char, 32> keybuf;

	SGE_X11_SENTRY

	int const num_chars = XLookupString(
		const_cast<XKeyEvent *>(&xev),
		keybuf.data(),
		static_cast<int>(keybuf.size()),
		&ks,
		&state);

	// xev does it this way
	char const code =
		ks > static_cast<KeySym>(std::numeric_limits<char>::max())
		? static_cast<char>(0)
		: static_cast<char>(ks);

	if(num_chars > 1)
	{
		FCPPT_LOG_WARNING(
			log::global(),
			log::_
				<< FCPPT_TEXT("stub: character '")
				<< code
				<< FCPPT_TEXT("' in XLookupString has ")
				<< num_chars
				<< FCPPT_TEXT(" bytes!"));
		return input::key_type();
	}

	return input::key_type(
		get_key_name(ks),
		translate_key_code(ks),
		code);
}

namespace
{

sge::string const
get_key_name(
	KeySym const ks)
{
	typedef std::map<
		KeySym,
		sge::string
	> name_map;

	static name_map names;

	name_map::const_iterator const it(
		names.find(ks));

	if(names.find(ks) != names.end())
		return it->second;

	SGE_X11_SENTRY

	char const* const name = XKeysymToString(ks);
	return names.insert(
		std::make_pair(
			ks,
			name
			? sge::iconv(name)
			: FCPPT_TEXT("unknown"))).first->second;
}

}
