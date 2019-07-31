//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PARSE_JSON_MAKE_RECURSIVE_OBJECTS_HPP_INCLUDED
#define SGE_PARSE_JSON_MAKE_RECURSIVE_OBJECTS_HPP_INCLUDED

#include <sge/parse/json/object_fwd.hpp>
#include <sge/parse/json/path_fwd.hpp>
#include <sge/parse/json/detail/symbol.hpp>


namespace sge
{
namespace parse
{
namespace json
{

SGE_PARSE_JSON_DETAIL_SYMBOL
sge::parse::json::object &
make_recursive_objects(
	sge::parse::json::object &,
	sge::parse::json::path const &
);

}
}
}

#endif
