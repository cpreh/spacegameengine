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


#include <sge/console/cursor.hpp>
#include <fcppt/text.hpp>

sge::console::cursor::cursor()
:
	line_(
		FCPPT_TEXT(" ")),
	pos_(
		static_cast<size_type>(
			0))
{
}

fcppt::string const
sge::console::cursor::edited(
	bool const _active
) const
{
	fcppt::string l = 
		line_;
	if (_active)
		l[pos_] = 
			FCPPT_TEXT('_');
	return 
		l;
}

fcppt::string const
sge::console::cursor::string() const
{
	// skip last space
	return 
		line_.substr(
			static_cast<size_type>(
				0),
			static_cast<size_type>(
				line_.length()-1));
}

void
sge::console::cursor::string(
	fcppt::string const &_line
)
{
	line_ = 
		_line+FCPPT_TEXT(' ');
	pos_ = 
		static_cast<size_type>(
			line_.length()-1);
}

void
sge::console::cursor::erase_word()
{
	if (line_.length() == static_cast<size_type>(1) || pos_ == static_cast<size_type>(0))
		return;

	size_type 
		s = 
			line_.rfind(
				FCPPT_TEXT(' '),
				static_cast<size_type>(
					pos_-1));

	if (s == fcppt::string::npos)
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
		line_.length() == 
			static_cast<size_type>(
				1);
}

void
sge::console::cursor::insert(
	fcppt::char_type const c
)
{
	line_.insert(
		pos_++,
		static_cast<size_type>(
			1),
		c
	);
}

bool
sge::console::cursor::at_start() const
{
	return 
		pos_ == 
			static_cast<size_type>(
				0);
}

void
sge::console::cursor::complete_word(
	function_map const &
)
{
	// TODO
}
