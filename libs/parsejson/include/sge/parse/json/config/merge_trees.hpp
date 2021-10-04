//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_JSON_CONFIG_MERGE_TREES_HPP_INCLUDED
#define SGE_PARSE_JSON_CONFIG_MERGE_TREES_HPP_INCLUDED

#include <sge/parse/json/object.hpp>
#include <sge/parse/json/detail/symbol.hpp>


namespace sge::parse::json::config
{

SGE_PARSE_JSON_DETAIL_SYMBOL
sge::parse::json::object
merge_trees(
	sge::parse::json::object const &original,
	sge::parse::json::object const &update
);

}

#endif
