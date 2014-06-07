/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_CONSOLE_GFX_CURSOR_HPP_INCLUDED
#define SGE_CONSOLE_GFX_CURSOR_HPP_INCLUDED

#include <sge/console/function_map.hpp>
#include <sge/console/gfx/cursor_fwd.hpp>
#include <sge/console/gfx/symbol.hpp>
#include <sge/font/char_type.hpp>
#include <sge/font/string.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace console
{
namespace gfx
{

class cursor
{
	FCPPT_NONCOPYABLE(
		cursor
	);
public:
	typedef
	sge::font::string::size_type
	size_type;

	SGE_CONSOLE_GFX_SYMBOL
	cursor();

	SGE_CONSOLE_GFX_SYMBOL
	~cursor();

	SGE_CONSOLE_GFX_SYMBOL
	sge::font::string
	edited(
		bool
	) const;

	SGE_CONSOLE_GFX_SYMBOL
	sge::font::string
	string() const;

	SGE_CONSOLE_GFX_SYMBOL
	void
	string(
		sge::font::string const &
	);

	SGE_CONSOLE_GFX_SYMBOL
	void
	erase_word();

	SGE_CONSOLE_GFX_SYMBOL
	void
	erase_char();

	SGE_CONSOLE_GFX_SYMBOL
	void
	left();

	SGE_CONSOLE_GFX_SYMBOL
	void
	right();

	SGE_CONSOLE_GFX_SYMBOL
	void
	to_start();

	SGE_CONSOLE_GFX_SYMBOL
	void
	to_end();

	SGE_CONSOLE_GFX_SYMBOL
	bool
	empty() const;

	SGE_CONSOLE_GFX_SYMBOL
	void
	insert(
		sge::font::char_type
	);

	SGE_CONSOLE_GFX_SYMBOL
	bool
	at_start() const;

	SGE_CONSOLE_GFX_SYMBOL
	void
	complete_word(
		sge::console::function_map const &
	);
private:
	sge::font::string line_;

	size_type pos_;
};

}
}
}

#endif
