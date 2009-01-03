/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_CON_CONSOLE_HPP_INCLUDED
#define SGE_CON_CONSOLE_HPP_INCLUDED

#include "types.hpp"
#include "../filesystem/path.hpp"
#include "../string.hpp"
#include "../export.hpp"

namespace sge
{
namespace con
{

SGE_SYMBOL void prefix(
	string::value_type const &);

SGE_SYMBOL string::value_type prefix();

SGE_SYMBOL void add(
	string const &,
	callback const &);

SGE_SYMBOL void eval(
	string const &);

SGE_SYMBOL void chat_callback(
	callback const &);

SGE_SYMBOL void read_config(
	filesystem::path const &);

SGE_SYMBOL var_map const &
vars();

SGE_SYMBOL callback_map const &
funcs();

SGE_SYMBOL sge::string const
get_var(
	sge::string const &);

SGE_SYMBOL void set_var(
	sge::string const &,
	sge::string const &);

SGE_SYMBOL void latch(
	sge::string const &,
	sge::string const &);

}
}

#endif
