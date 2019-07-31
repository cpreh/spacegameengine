//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_JSON_CONFIG_MODIFY_USER_VALUE_HPP_INCLUDED
#define SGE_PARSE_JSON_CONFIG_MODIFY_USER_VALUE_HPP_INCLUDED

#include <sge/parse/json/object_fwd.hpp>
#include <sge/parse/json/path_fwd.hpp>
#include <sge/parse/json/value.hpp>
#include <sge/parse/json/detail/symbol.hpp>


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
SGE_PARSE_JSON_DETAIL_SYMBOL
void
modify_user_value(
	sge::parse::json::object const &structure_json,
	sge::parse::json::object &user_json,
	sge::parse::json::path const &path,
	sge::parse::json::value const &new_value
);

}
}
}
}

#endif
