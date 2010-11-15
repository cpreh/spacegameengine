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


#ifndef SGE_CONSOLE_FUNCTION_HPP_INCLUDED
#define SGE_CONSOLE_FUNCTION_HPP_INCLUDED

#include <sge/console/signal.hpp>
#include <sge/console/symbol.hpp>
#include <fcppt/string.hpp>

namespace sge
{
namespace console
{

class function
{
public:
	SGE_CONSOLE_SYMBOL explicit function(
		fcppt::string const &short_desc,
		fcppt::string const &long_desc
	);

	SGE_CONSOLE_SYMBOL sge::console::signal &
	signal();

	SGE_CONSOLE_SYMBOL fcppt::string const &
	short_description() const;

	SGE_CONSOLE_SYMBOL fcppt::string const &
	long_description() const;
private:
	sge::console::signal signal_;
	fcppt::string short_description_,long_description_;
};

}
}

#endif
