/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_CONSOLE_CURSOR_HPP_INCLUDED
#define SGE_CONSOLE_CURSOR_HPP_INCLUDED

#include <sge/console/function_map.hpp>
#include <sge/console/symbol.hpp>
#include <fcppt/string.hpp>
#include <fcppt/char_type.hpp>

namespace sge
{
namespace console
{
class cursor
{
public:
	typedef 
	fcppt::string::size_type 
	size_type;

	SGE_CONSOLE_SYMBOL cursor();

	SGE_CONSOLE_SYMBOL fcppt::string const
	edited(
		bool
	) const;

	SGE_CONSOLE_SYMBOL fcppt::string const
	string() const;

	SGE_CONSOLE_SYMBOL void
	string(
		fcppt::string const &
	);

	SGE_CONSOLE_SYMBOL void
	erase_word();

	SGE_CONSOLE_SYMBOL void
	erase_char();

	SGE_CONSOLE_SYMBOL void
	left();

	SGE_CONSOLE_SYMBOL void
	right();

	SGE_CONSOLE_SYMBOL void
	to_start();

	SGE_CONSOLE_SYMBOL void
	to_end();

	SGE_CONSOLE_SYMBOL bool
	empty() const;

	SGE_CONSOLE_SYMBOL void
	insert(
		fcppt::char_type
	);

	SGE_CONSOLE_SYMBOL bool
	at_start() const;

	SGE_CONSOLE_SYMBOL void
	complete_word(
		function_map const &
	);
private:
	fcppt::string line_;
	size_type pos_;
};
}
}

#endif
