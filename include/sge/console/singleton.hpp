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


#ifndef SGE_CON_SINGLETON_HPP_INCLUDED
#define SGE_CON_SINGLETON_HPP_INCLUDED

#include "console.hpp"
#include <map>

namespace sge
{
namespace con
{

struct singleton
{
	typedef std::map<string,string> config_map;

	var_map vars;
	callback_map funcs;
	config_map config_vars;
	callback chat;
	string::value_type prefix;

	singleton();

	void add(const string &,var_base &);
	void erase(const string &);
	void add(const string &,const callback &);
	void eval(const string &);
	void read_config(const path &);
	string get_var(const string &);
	void set_var(const string &,const string &);
	void latch(const string &,const string &);
};

singleton &instance();

}
}

#endif
