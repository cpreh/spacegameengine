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

#include "var_map.hpp"
#include "callback_map.hpp"
#include "callback.hpp"
#include "signal.hpp"
#include "../signals/connection.hpp"
#include "../filesystem/path.hpp"
#include "../string.hpp"
#include "../export.hpp"
#include <map>

namespace sge
{
namespace con
{

class var_base;

struct singleton {
	typedef std::map<
		string,
		string
	> config_map;

	var_map vars;
	callback_map funcs;
	config_map config_vars;
	signal chat;
	string::value_type prefix;

	singleton();

	void
	add(
		string const &,
		var_base &);

	signals::connection const
	add(
		string const &,
		callback const &);

	void erase(
		string const &);

	void eval(
		string const &);

	void read_config(
		filesystem::path const &);

	string const
	var(
		string const &);

	void var(
		string const &,
		string const &);

	void latch(
		string const &,
		string const &);
};

singleton &instance();

}
}

#endif
