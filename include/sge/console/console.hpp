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
#include "../string.hpp"
#include "../path.hpp"
#include "../export.hpp"

namespace sge
{
namespace con
{

SGE_SYMBOL void prefix(const string::value_type &);
SGE_SYMBOL string::value_type prefix();
SGE_SYMBOL void add(const string &,const callback &);
SGE_SYMBOL void eval(const string &);
SGE_SYMBOL void chat_callback(const callback &);
SGE_SYMBOL void read_config(const path &);
SGE_SYMBOL const var_map &vars();
SGE_SYMBOL const callback_map &funcs();
SGE_SYMBOL sge::string const get_var(const sge::string &);
SGE_SYMBOL void set_var(const sge::string &,const sge::string &);
SGE_SYMBOL void latch(const sge::string &,const sge::string &);

}
}

#endif
