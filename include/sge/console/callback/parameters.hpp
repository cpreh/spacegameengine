/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_CONSOLE_CALLBACK_PARAMETERS_HPP_INCLUDED
#define SGE_CONSOLE_CALLBACK_PARAMETERS_HPP_INCLUDED

#include <sge/console/symbol.hpp>
#include <sge/console/callback/function.hpp>
#include <sge/console/callback/name.hpp>
#include <sge/font/text/string.hpp>
#include <fcppt/nonassignable.hpp>

namespace sge
{
namespace console
{
namespace callback
{
class parameters
{
FCPPT_NONASSIGNABLE(
	parameters);
public:
	SGE_CONSOLE_SYMBOL explicit
	parameters(
		callback::function const &,
		callback::name const &);

	SGE_CONSOLE_SYMBOL parameters &
	short_description(
		font::text::string const &);

	SGE_CONSOLE_SYMBOL parameters &
	long_description(
		font::text::string const &);

	SGE_CONSOLE_SYMBOL callback::function const &
	function() const;

	SGE_CONSOLE_SYMBOL font::text::string const &
	name() const;

	SGE_CONSOLE_SYMBOL font::text::string const &
	short_description() const;

	SGE_CONSOLE_SYMBOL font::text::string const &
	long_description() const;
private:
	callback::function const function_;
	font::text::string const name_;
	font::text::string short_description_;
	font::text::string long_description_;
};
}
}
}

#endif
