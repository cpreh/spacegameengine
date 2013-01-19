/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/console/cursor.hpp>
#include <sge/console/function_map.hpp>
#include <sge/font/char_type.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/string.hpp>


sge::console::cursor::cursor()
:
	line_(
		SGE_FONT_LIT(" ")
	),
	pos_(
		0u
	)
{
}

sge::console::cursor::~cursor()
{
}

sge::font::string const
sge::console::cursor::edited(
	bool const _active
) const
{
	sge::font::string l =
		line_;

	if (_active)
		l[pos_] =
			SGE_FONT_LIT('_');
	return
		l;
}

sge::font::string const
sge::console::cursor::string() const
{
	// skip last space
	return
		line_.substr(
			0u,
			line_.length()-1u
		);
}

void
sge::console::cursor::string(
	sge::font::string const &_line
)
{
	line_ =
		_line + SGE_FONT_LIT(' ');
	pos_ =
		line_.length()-1u;
}

void
sge::console::cursor::erase_word()
{
	if(
		this->empty()
		||
		this->at_start()
	)
		return;

	size_type
		s =
			line_.rfind(
				SGE_FONT_LIT(' '),
				static_cast<size_type>(
					pos_-1));

	if (s == sge::font::string::npos)
		s =
			static_cast<size_type>(
				0);

	line_.erase(
		s,
		static_cast<size_type>(
			pos_-s));
	pos_ =
		s;
}

void
sge::console::cursor::erase_char()
{
	if (pos_ == static_cast<size_type>(line_.length()-1))
		return;

	line_.erase(
		pos_,
		static_cast<size_type>(
			1));
}

void
sge::console::cursor::left()
{
	if (pos_ == static_cast<size_type>(0))
		return;
	pos_ =
		static_cast<size_type>(
			pos_-1);
}

void
sge::console::cursor::right()
{
	if (pos_ == static_cast<size_type>(line_.length()-1))
		return;
	pos_++;
}

void
sge::console::cursor::to_start()
{
	pos_ =
		static_cast<size_type>(
			0);
}

void
sge::console::cursor::to_end()
{
	pos_ =
		static_cast<size_type>(
			line_.length()-1);
}

bool
sge::console::cursor::empty() const
{
	return
		line_.length() == 1u;
}

void
sge::console::cursor::insert(
	sge::font::char_type const _char
)
{
	line_.insert(
		pos_++,
		1u,
		_char
	);
}

bool
sge::console::cursor::at_start() const
{
	return
		pos_ == 0u;
}

void
sge::console::cursor::complete_word(
	sge::console::function_map const &_map
)
{
}
