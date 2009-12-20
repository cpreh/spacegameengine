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


#ifndef SGE_CONSOLE_DETAIL_CURSOR_HPP_INCLUDED
#define SGE_CONSOLE_DETAIL_CURSOR_HPP_INCLUDED

#include <sge/console/variable_map.hpp>
#include <sge/console/function_map.hpp>
#include <fcppt/string.hpp>

namespace sge
{
namespace console
{
namespace detail
{

class cursor
{
public:
	cursor();
	void reset();
	fcppt::string const edited(bool) const;
	fcppt::string const string() const;
	void string(fcppt::string const &);
	void erase_word();
	void erase_char();
	void left();
	void right();
	void to_start();
	void to_end();
	bool empty() const;
	void insert(char_type);
	bool at_start() const;
	void complete_word(
		variable_map const &,
		function_map const &
	);
private:
	fcppt::string line_;
	fcppt::string::size_type pos_;
};

}
}
}

#endif
