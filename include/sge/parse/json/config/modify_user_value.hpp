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


#ifndef SGE_PARSE_JSON_CONFIG_MODIFY_USER_VALUE_HPP_INCLUDED
#define SGE_PARSE_JSON_CONFIG_MODIFY_USER_VALUE_HPP_INCLUDED

#include <sge/parse/json/path_fwd.hpp>
#include <sge/parse/json/object_fwd.hpp>
#include <sge/parse/json/value.hpp>
#include <sge/parse/symbol.hpp>

namespace sge
{
namespace parse
{
namespace json
{
namespace config
{
/*
	This is a more specific function. It takes as arguments:

	- a "structure" json. This json object specifies how the "complete"
    configuration tree looks. Anything that's not in the structure
    tree doesn't exist and is considered invalid.
	- a "user" json. This stores a subset of the structure json and
    contains the configuration options the user specified him/herself.
	- a path to a specific option
	- the option's new value
 */
SGE_PARSE_SYMBOL void
modify_user_value(
	json::object const &structure_json,
	json::object &user_json,
	json::path const &path,
	json::value const &new_value);
}
}
}
}

#endif
